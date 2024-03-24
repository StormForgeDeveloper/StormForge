////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "MemoryManager/SFMemory.h"
#include "Util/SFToString.h"

#include "Net/SFConnectionUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetToString.h"



namespace SF {
namespace Net {


	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Recv message window
	//

	RecvMsgWindow::RecvMsgWindow(IHeap& heap)
		: m_uiSyncMask(0)
		, m_uiBaseSequence(0)
		, m_uiMsgCount(0)
	{
		m_pMsgWnd = new(heap) MessageElement[MessageWindow::MESSAGE_QUEUE_SIZE]{};
		for (uint32_t iMsg = 0; iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
		{
			uint32_t expectedSeq = MessageSequence::Normalize(iMsg - MessageWindow::MESSAGE_QUEUE_SIZE); // using 16bit part only
			m_pMsgWnd[iMsg].Sequence = expectedSeq;
			m_pMsgWnd[iMsg].pMsg = nullptr;
		}
	}

	RecvMsgWindow::~RecvMsgWindow()
	{
		ClearWindow();
		IHeap::Delete(m_pMsgWnd);
	}

	// Add message
	Result RecvMsgWindow::AddMsg( SharedPointerT<MessageData>& pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		auto msgSeq = pIMsg->GetMessageHeader()->GetSequence();

		// Base sequence should be locked until actual swap is happened
		// There is a chance m_uiBaseSequence increase before the message is actually added if a message is added on different thread at the same time.
		//TicketScopeLock scopeLock(TicketLock::LockMode::NonExclusive, m_SequenceLock);
		int diff = MessageSequence::Difference(msgSeq, m_uiBaseSequence);

		if (diff >= GetAcceptableSequenceRange())
		{
			return ResultCode::IO_SEQUENCE_OVERFLOW; // No room for new message
		}

		if (diff < 0)
		{
			return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
		}

		int iPosIdx = msgSeq % MessageWindow::MESSAGE_QUEUE_SIZE;

		uint32_t expectedStoredSeq = MessageSequence::Normalize(msgSeq - MessageWindow::MESSAGE_QUEUE_SIZE); // using 11bit part only
		bool bExchanged = m_pMsgWnd[iPosIdx].Sequence.compare_exchange_strong(expectedStoredSeq, msgSeq);
		if (!bExchanged)
		{
			// Somebody already took the spot. let's drop it
			if (MessageSequence::Difference(expectedStoredSeq, msgSeq) <= 0)
			{
				// newer message already took place
				return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
			}
			else
			{
				// The sequence is way earlier. let's drop it
				return ResultCode::IO_SEQUENCE_OVERFLOW;
			}
		}

		// I have reserved the spot
		m_uiSyncMask.fetch_or(((uint64_t)1) << iPosIdx, std::memory_order_relaxed);

		// we already tested validity, just swap it
		m_pMsgWnd[iPosIdx].pMsg.Swap(pIMsg);
		uint messageCount = m_uiMsgCount.fetch_add(1, std::memory_order_release) + 1;
		unused(messageCount);

		return hr;
	}

	// Non-thread safe
	// Pop message and return it if can
	Result RecvMsgWindow::PopMsg(SharedPointerT<MessageData> &pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		auto baseSequence = m_uiBaseSequence.load(std::memory_order_acquire);
		int iPosIdx = baseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;
		if (m_pMsgWnd == nullptr )//|| m_pMsgWnd[iPosIdx].load(std::memory_order_relaxed) == nullptr)
			return ResultCode::FAIL;

		// Base sequence should be locked during actual pop operation
		//TicketScopeLock scopeLock(TicketLock::LockMode::Exclusive, m_SequenceLock);

		pIMsg = std::forward<SharedPointerAtomicT<MessageData>>(m_pMsgWnd[iPosIdx].pMsg);
		if (pIMsg == nullptr)
			return ResultCode::FAIL;

		// If the message is not the one with correct sequence, it is wrong and need to be dropped
		if (MessageSequence::Difference(pIMsg->GetMessageHeader()->GetSequence(), baseSequence) != 0)
		{
			pIMsg = nullptr;
			return ResultCode::FAIL;
		}
	
		auto prevSeq = m_uiBaseSequence.fetch_add(1,std::memory_order_release);// Message window clear can't cross base sequence change, and this will make sure the previous sync mask change is commited.
		unused(prevSeq);

		// Between previous exchange and sequence update, the message can be arrived again
		// This will make sure the message is cleaned up
		// Circular case will be prohibited in AddMsg
		m_pMsgWnd[iPosIdx].pMsg = nullptr;

		m_uiMsgCount.fetch_sub(1, std::memory_order_relaxed);

		auto messageMask = ((uint64_t)1) << iPosIdx;
		m_uiSyncMask.fetch_and(~messageMask, std::memory_order_release);

		return hr;

	}

	
	// Get SyncMask
	uint64_t RecvMsgWindow::GetSyncMask()
	{
		auto baseSeq = m_uiBaseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;

		uint64_t resultSyncMask = m_uiSyncMask.load(std::memory_order_acquire);
		if (baseSeq != 0)
		{
			auto least = resultSyncMask >> baseSeq;
			auto most = resultSyncMask << (MessageWindow::MESSAGE_QUEUE_SIZE - baseSeq + 1);
			most >>= 1; // clear MSB
			resultSyncMask = least | most;
		}

//#ifdef DEBUG
		//uint64_t uiSyncMask = 0;
		//for (int uiIdx = 0, iSeq = baseSeq; uiIdx < GetAcceptableSequenceRange(); uiIdx++, iSeq++)
		//{
		//	int iPosIdx = iSeq % MESSAGE_QUEUE_SIZE;
		//	if( m_pMsgWnd[ iPosIdx ].load(std::memory_order_relaxed) != nullptr )
		//	{
		//		uiSyncMask |= ((uint64_t)1)<<uiIdx;
		//	}
		//}
		//AssertRel(resultSyncMask == uiSyncMask);
//#endif
		return resultSyncMask;
	}

	
	// Clear window element
	void RecvMsgWindow::ClearWindow()
	{
		if (m_pMsgWnd)
		{
			for (uint32_t iMsg = 0; iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
			{
				uint32_t expectedSeq = MessageSequence::Normalize(iMsg - MessageWindow::MESSAGE_QUEUE_SIZE); // using 16bit part only
				m_pMsgWnd[iMsg].Sequence = expectedSeq;
				m_pMsgWnd[iMsg].pMsg = nullptr;
			}
		}
		m_uiBaseSequence.store(0, std::memory_order_release);
		m_uiMsgCount.store(0, std::memory_order_release);
		m_uiSyncMask.store(0, std::memory_order_release);
	}
	


    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Recv message window
    //

    RecvMsgWindow2::RecvMsgWindow2()
        : m_uiSyncMask(0)
        , m_uiBaseSequence(0)
        , m_uiMsgCount(0)
    {
        ResetWindowData();
    }

    RecvMsgWindow2::~RecvMsgWindow2()
    {
    }

    void RecvMsgWindow2::ResetWindowData()
    {
        for (uint32_t iMsg = 0; iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
        {
            uint32_t expectedSeq = MessageSequence::Normalize(iMsg - MessageWindow::MESSAGE_QUEUE_SIZE); // using 16bit part only
            m_pMsgWnd[iMsg].Sequence = expectedSeq;
            m_pMsgWnd[iMsg].pMsgData = nullptr;
        }
    }

    // Add message
    Result RecvMsgWindow2::AddMsg(const MessageHeader* pHeader)
    {
        Result hr;

        MessageSequence msgSeq = pHeader->GetSequence();

        // Base sequence should be locked until actual swap is happened
        // There is a chance m_uiBaseSequence increase before the message is actually added if a message is added on different thread at the same time.
        int diff = msgSeq - m_uiBaseSequence;
        if (diff >= GetAcceptableSequenceRange())
        {
            return ResultCode::IO_SEQUENCE_OVERFLOW; // No room for new message
        }

        if (diff < 0)
        {
            return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
        }

        int iPosIdx = msgSeq % MessageWindow::MESSAGE_QUEUE_SIZE;

        // We expect previous sequence is stored
        uint32_t expectedStoredSeq = MessageSequence::Normalize(msgSeq.Sequence - MessageWindow::MESSAGE_QUEUE_SIZE); // using 11bit part only
        bool bExchanged = m_pMsgWnd[iPosIdx].Sequence.compare_exchange_strong(expectedStoredSeq, msgSeq);
        if (!bExchanged)
        {
            // Somebody already took the spot. let's drop it
            if (MessageSequence::Difference(expectedStoredSeq, msgSeq) <= 0)
            {
                // newer message already took place
                return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
            }
            else
            {
                // The sequence is way earlier. let's drop it
                return ResultCode::IO_SEQUENCE_OVERFLOW;
            }
        }

        // I have reserved the spot
        m_uiSyncMask.fetch_or(((uint64_t)1) << iPosIdx, std::memory_order_relaxed);

        MessageBuffer::ItemWritePtr itemPtr = m_MessageDataBuffer.AllocateWrite(pHeader->MessageSize);
        memcpy(itemPtr.data(), pHeader, pHeader->MessageSize);

        // we already tested validity, just swap it
        assert(m_pMsgWnd[iPosIdx].pMsgData == nullptr);
        MessageBuffer::BufferItem* pPrev = m_pMsgWnd[iPosIdx].pMsgData.exchange(itemPtr.GetBufferItem());
        itemPtr.Reset();

        // whichever left need to be released
        if (pPrev != nullptr)
        {
            m_MessageDataBuffer.ForceReleaseRead(pPrev);
        }

        uint messageCount = m_uiMsgCount.fetch_add(1, std::memory_order_release) + 1;
        unused(messageCount);

        return hr;
    }

    // Non-thread safe
    // Pop message and return it if can
    Result RecvMsgWindow2::PopMsg(MessageBuffer::ItemReadPtr& messageData)
    {
        Result hr;
        uint16_t baseSequence = m_uiBaseSequence.load(std::memory_order_acquire);
        int iPosIdx = baseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;

        MessageBuffer::BufferItem* pMsgData = m_pMsgWnd[iPosIdx].pMsgData.exchange(nullptr);
        if (pMsgData == nullptr)
            return ResultCode::NO_DATA_EXIST;

        if (!pMsgData->AcquireRead())
            return ResultCode::UNEXPECTED;

        messageData = MessageBuffer::ItemReadPtr(&m_MessageDataBuffer, pMsgData);
        if (!messageData.IsValid())
            return ResultCode::FAIL;

        const MessageHeader* pHeader = reinterpret_cast<const MessageHeader*>(messageData.data());
        // If the message is not the one with correct sequence, it is wrong and need to be dropped
        if (MessageSequence::Difference(pHeader->GetSequence(), baseSequence) != 0)
        {
            messageData.Reset();
            return ResultCode::FAIL;
        }

        auto prevSeq = m_uiBaseSequence.fetch_add(1, std::memory_order_release);// Message window clear can't cross base sequence change, and this will make sure the previous sync mask change is commited.
        unused(prevSeq);

        // Between previous exchange and sequence update, the message can be arrived again
        // This will make sure the message is cleaned up
        // Circular case will be prohibited in AddMsg
        MessageBuffer::BufferItem* pBufferItem = m_pMsgWnd[iPosIdx].pMsgData.exchange(nullptr);
        if (pBufferItem)
        {
            m_MessageDataBuffer.ForceReleaseRead(pBufferItem);
        }

        m_uiMsgCount.fetch_sub(1, std::memory_order_relaxed);

        uint64_t messageMask = ((uint64_t)1) << iPosIdx;
        m_uiSyncMask.fetch_and(~messageMask, std::memory_order_release);

        return hr;

    }


    // Get SyncMask
    uint64_t RecvMsgWindow2::GetSyncMask()
    {
        auto baseSeq = m_uiBaseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;

        uint64_t resultSyncMask = m_uiSyncMask.load(std::memory_order_acquire);
        if (baseSeq != 0)
        {
            auto least = resultSyncMask >> baseSeq;
            auto most = resultSyncMask << (MessageWindow::MESSAGE_QUEUE_SIZE - baseSeq + 1);
            most >>= 1; // clear MSB
            resultSyncMask = least | most;
        }

        //#ifdef DEBUG
                //uint64_t uiSyncMask = 0;
                //for (int uiIdx = 0, iSeq = baseSeq; uiIdx < GetAcceptableSequenceRange(); uiIdx++, iSeq++)
                //{
                //	int iPosIdx = iSeq % MESSAGE_QUEUE_SIZE;
                //	if( m_pMsgWnd[ iPosIdx ].load(std::memory_order_relaxed) != nullptr )
                //	{
                //		uiSyncMask |= ((uint64_t)1)<<uiIdx;
                //	}
                //}
                //AssertRel(resultSyncMask == uiSyncMask);
        //#endif
        return resultSyncMask;
    }


    // Clear window element
    void RecvMsgWindow2::Reset()
    {
        ResetWindowData();

        m_MessageDataBuffer.Reset();

        m_uiBaseSequence.store(0, std::memory_order_release);
        m_uiMsgCount.store(0, std::memory_order_release);
        m_uiSyncMask.store(0, std::memory_order_release);
    }

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Send message window
	//


	SendMsgWindow::SendMsgWindow(IHeap& heap)
        : m_ReleasedMessageSequences(heap, 64, 4)
	{
		m_pMsgWnd = new(heap) WindowMessageData[MessageWindow::MESSAGE_QUEUE_SIZE];
	}

	SendMsgWindow::~SendMsgWindow()
	{
		ClearWindow();
		if (m_pMsgWnd != nullptr)
			IHeap::Delete(m_pMsgWnd);
		m_pMsgWnd = nullptr;
	}

	// Clear window element
	void SendMsgWindow::ClearWindow()
	{
		//MutexScopeLock localLock(GetLock());

		if (m_pMsgWnd)
		{
			for (int iMsg = 0; iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
			{
				m_pMsgWnd[iMsg].Clear();
			}
			//memset( m_pMsgWnd, 0, sizeof(MessageElement)*GetAcceptableSequenceRange() );
		}
		m_uiBaseSequence = 0;
		m_uiMsgCount = 0;

		m_uiHeadSequence = m_uiBaseSequence;
	}


	// Get message info in window, index based on window base
	Result SendMsgWindow::GetAt(uint32_t uiIdx, WindowMessageData* &pMessageElement)
	{
		uint32_t iIdxCur = (m_uiBaseSequence + uiIdx) % MessageWindow::MESSAGE_QUEUE_SIZE;

		if (m_pMsgWnd == NULL)
			return ResultCode::FAIL;

		pMessageElement = &m_pMsgWnd[iIdxCur];

		return ResultCode::SUCCESS;
	}


	// Add a message at the end
	Result SendMsgWindow::EnqueueMessage( TimeStampMS ulTimeStampMS, SharedPointerT<MessageData>& pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		int iIdx = 0;

		if( GetAvailableSize() == 0 )
			return ResultCode::IO_NOT_ENOUGH_WINDOWSPACE;

		if( pIMsg == nullptr )
			return ResultCode::INVALID_POINTER;

		// assign head sequence
		AssertRel(pIMsg->GetMessageHeader()->GetSequence() == 0);
		pIMsg->AssignSequence( m_uiHeadSequence );

		iIdx = MessageSequence::Difference(m_uiHeadSequence, m_uiBaseSequence);

		if (iIdx >= GetAcceptableSequenceRange())
		{
			return ResultCode::IO_NOT_ENOUGH_WINDOWSPACE;
		}

		Assert(iIdx >= 0);
		if (iIdx < 0 || iIdx >= GetAcceptableSequenceRange())
			return ResultCode::IO_INVALID_SEQUENCE;

		// To window queue array index
		iIdx = (m_uiBaseSequence + iIdx) % MessageWindow::MESSAGE_QUEUE_SIZE;

		// check duplicated transaction
		Assert(m_pMsgWnd[ iIdx ].State == ItemState::Free );

		m_pMsgWnd[iIdx].ulTimeStamp = ulTimeStampMS;
		m_pMsgWnd[iIdx].pMsg = pIMsg;
		m_pMsgWnd[iIdx].State = ItemState::Filled;

		m_uiHeadSequence++;
		m_uiMsgCount++;

		return hr;
	}

    Result SendMsgWindow::QueueReleasedSequence(uint16_t uiSequence)
    {
        if (m_pMsgWnd == NULL)
            return ResultCode::SUCCESS;// nothing to release

        int iIdx = MessageSequence::Difference(uiSequence, m_uiBaseSequence.load(MemoryOrder::memory_order_acquire));
        if (iIdx >= GetAcceptableSequenceRange())
        {
            return ResultCode::IO_INVALID_SEQUENCE; // Out of range
        }
        else if (iIdx < 0)
        {
            return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
        }

        return m_ReleasedMessageSequences.Enqueue(ToQueuedSequence(uiSequence));
    }

    Result SendMsgWindow::QueueReleasedSequence(uint16_t uiSequenceBase, uint64_t uiMsgMask)
    {
        Result hr;

        if (m_pMsgWnd == NULL)
            return ResultCode::SUCCESS;// nothing to release

        uint32_t uiCurBit = 0, uiSyncMaskCur = 1;

        auto baseSequence = m_uiBaseSequence.load(MemoryOrder::memory_order_acquire);
        int iIdx = MessageSequence::Difference(uiSequenceBase, baseSequence);
        if(  iIdx < 0 )
        {
        	// SKip already processed message ids
        	uint32_t uiIdx = (uint32_t)(-iIdx);
        	iIdx = 0;

            // Check already processed bits
        	// For some reason, peer sent old sync index, skip those indexes, but make sure it's fully send, otherwise it's protocol error
        	for (; uiCurBit < uiIdx; uiCurBit++, uiSyncMaskCur <<= 1)
        	{
        		if ((uiMsgMask & uiSyncMaskCur) == 0)
        		{
        			// If client use same port for different connect this will be happened, and the connection need to be closed
        			netCheck(ResultCode::UNEXPECTED);
        		}
        	}
        }
        else if (iIdx > 0)
        {
            // everything before Idx has acked
        	auto maxRelease = (uint32_t)std::min(iIdx, GetAcceptableSequenceRange());
        	for (; uiCurBit < maxRelease; uiCurBit++)
        	{
                netCheck(m_ReleasedMessageSequences.Enqueue(ToQueuedSequence(baseSequence + uiCurBit)));
        	}

        	if (iIdx >= GetAcceptableSequenceRange())
        	{
        		//SlidWindow();
        		return ResultCode::SUCCESS;
        	}
        }

        // Process remain bits
        // At this point iIdx will have offset from local base sequence
        for (; uiCurBit < MessageWindow::SYNC_MASK_BITS_MAX; uiCurBit++, uiSyncMaskCur <<= 1, iIdx++)
        {
        	if ((uiMsgMask & uiSyncMaskCur) == 0) continue;

            netCheck(m_ReleasedMessageSequences.Enqueue(ToQueuedSequence(baseSequence + iIdx)));

        }

        return hr;
    }

    Result SendMsgWindow::UpdateReleasedSequences()
    {
        Result hr;

        auto uiSequenceBase = m_uiBaseSequence.load(MemoryOrder::memory_order_acquire);
        uint32_t sequence{};
        while (m_ReleasedMessageSequences.Dequeue(sequence))
        {
            sequence = FromQueuedSequence(sequence);
            int iIdx = MessageSequence::Difference(sequence, uiSequenceBase);
            if (iIdx < 0)
                continue;

            WindowMessageData& windowElement = m_pMsgWnd[sequence % MessageWindow::MESSAGE_QUEUE_SIZE];
            windowElement.pMsg = nullptr;
            // Double free can happen. skip the assert
            //AssertRel(windowElement.State != ItemState::Free);
            windowElement.State = ItemState::CanFree;
        }

        SlidWindow();

        return hr;
    }

	//// Release message sequence and slide window if can
	//Result SendMsgWindow::ReleaseSingleMessage( uint16_t uiSequence )
	//{
	//	// TODO: make this function thread safe because this function can be called from other thread
	//	//MutexScopeLock localLock(m_Lock);

	//	ScopeContext hr;
	//	int iIdx;
	//	//uint32_t iPosIdx;

	//	if( m_pMsgWnd == NULL )
	//		return ResultCode::SUCCESS;// nothing to release


	//	iIdx = Message::SequenceDifference(uiSequence, m_uiBaseSequence);

	//	if( iIdx >= GetAcceptableSequenceRange() )
	//	{
	//		netCheck( ResultCode::IO_INVALID_SEQUENCE ); // Out of range
	//	}
	//	else if(  iIdx < 0 )
	//	{
	//		return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
	//	}

	//	ReleaseMessageInternal(iIdx);

	//	// No sliding window for this because this can be called from other thread

	//	return hr;
	//}


	//// Release message sequence and slide window if can
	//Result SendMsgWindow::ReleaseMsg( uint16_t uiSequenceBase, uint64_t uiMsgMask )
	//{
	//	Result hr = ResultCode::SUCCESS;
	//	int iIdx;

	//	//MutexScopeLock localLock(m_Lock);

	//	if( m_pMsgWnd == nullptr )
	//		return ResultCode::SUCCESS;// nothing to release

	//	uint32_t uiCurBit = 0, uiSyncMaskCur = 1;

	//	iIdx = Message::SequenceDifference(uiSequenceBase, m_uiBaseSequence);

	//	if(  iIdx < 0 )
	//	{
	//		// SKip already processed message ids
	//		uint32_t uiIdx = (uint32_t)(-iIdx);
	//		iIdx = 0;

	//		// For some reason, peer sent old sync index, skip those indexes, but make sure it's fully send, otherwise it's protocol error
	//		for (; uiCurBit < uiIdx; uiCurBit++, uiSyncMaskCur <<= 1)
	//		{
	//			if ((uiMsgMask & uiSyncMaskCur) == 0)
	//			{
	//				// If client use same port for different connect this will be happened, and the connection need to be closed
	//				netCheck(ResultCode::UNEXPECTED);
	//			}
	//		}
	//	}
	//	else if (iIdx > 0)
	//	{
	//		auto maxRelease = (uint32_t)std::min(iIdx, GetAcceptableSequenceRange());
	//		for (; uiCurBit < maxRelease; uiCurBit++)
	//		{
	//			ReleaseMessageInternal(uiCurBit);
	//		}

	//		if (iIdx >= GetAcceptableSequenceRange())
	//		{
	//			//SlidWindow();
	//			return ResultCode::SUCCESS;
	//		}

	//	}

	//	// At this point iIdx will have offset from local base sequence
	//	for (; uiCurBit < MessageWindow::SYNC_MASK_BITS_MAX; uiCurBit++, uiSyncMaskCur <<= 1, iIdx++)
	//	{
	//		if ((uiMsgMask & uiSyncMaskCur) == 0) continue;

	//		ReleaseMessageInternal((uint32_t)iIdx);

	//	}

	//	// window sliding happens on connection tick

	//	return hr;
	//}



	// Release message sequence
	void SendMsgWindow::ReleaseMessageInternal(uint16_t iOffset)
	{
		uint32_t iPosIdx = (m_uiBaseSequence + iOffset) % MessageWindow::MESSAGE_QUEUE_SIZE;
        WindowMessageData& windowElement = m_pMsgWnd[iPosIdx];

        windowElement.pMsg = nullptr;
        AssertRel(windowElement.State != ItemState::Free);
        windowElement.State = ItemState::CanFree;

        // Mark it as can-be-freed
        //ItemState expectedState = ItemState::Filled;
        //while (!windowElement.State.compare_exchange_weak(expectedState, ItemState::CanFree, std::memory_order_relaxed, std::memory_order_acquire))
        //{
        //    if (expectedState == ItemState::Free || expectedState == ItemState::CanFree)
        //    {
        //        // Nothing need to be done
        //        return;
        //    }
        //    expectedState = ItemState::Filled;
        //}
	}


	void SendMsgWindow::SlidWindow()
	{
		auto windowSeq = m_uiBaseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;
		for (int iMsg = 0; m_pMsgWnd[windowSeq].State == ItemState::CanFree && iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
		{
            m_pMsgWnd[windowSeq].pMsg = nullptr;
            m_pMsgWnd[windowSeq].State = ItemState::Free;
			m_uiMsgCount--;
			m_uiBaseSequence++;
			windowSeq = m_uiBaseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;
		}

	}

} // namespace Net
} // namespace SF


