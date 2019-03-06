////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Memory/SFMemory.h"
#include "String/SFToString.h"

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
		m_pMsgWnd = new(heap) MessageElement[MessageWindow::MESSAGE_QUEUE_SIZE];
	}

	RecvMsgWindow::~RecvMsgWindow()
	{
		ClearWindow();
		delete[] m_pMsgWnd;
	}

	// Add message
	Result RecvMsgWindow::AddMsg( SharedPointerT<Message::MessageData>& pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		auto msgSeq = pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence;

		// Base sequence should be locked until actual swap is happened
		// There is a chance m_uiBaseSequence increase before the message is actually added if same message is added on different thread on the same time.
		// It will cause way beyond message in the message window
		TicketScopeLock scopeLock(TicketLock::LockMode::LOCK_NONEXCLUSIVE, m_SequenceLock);
		int diff = Message::SequenceDifference(msgSeq, m_uiBaseSequence);

		if (diff >= GetWindowSize())
		{
			return ResultCode::IO_SEQUENCE_OVERFLOW; // No room for new message
		}

		if (diff < 0)
		{
			return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
		}


		int iPosIdx = msgSeq % MessageWindow::MESSAGE_QUEUE_SIZE;
		m_uiSyncMask.fetch_or(((uint64_t)1) << iPosIdx, std::memory_order_relaxed);

		// check duplicated transaction
		m_pMsgWnd[iPosIdx].Swap(pIMsg);

		if (pIMsg == nullptr)
		{
			auto messageCount = m_uiMsgCount.fetch_add(1, std::memory_order_release) + 1;
			unused(messageCount);
			//AssertRel(messageCount <= MESSAGE_WINDOW_SIZE);
		}
		else
		{
			//SFLog(System, Info, "Added duplicate Message Seq:{0}", pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence);
		}


	//Proc_End:

		return hr;
	}

	// Non-thread safe
	// Pop message and return it if can
	Result RecvMsgWindow::PopMsg(SharedPointerT<Message::MessageData> &pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		auto baseSequence = m_uiBaseSequence.load(std::memory_order_acquire);
		int iPosIdx = baseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;
		if (m_pMsgWnd == nullptr )//|| m_pMsgWnd[iPosIdx].load(std::memory_order_relaxed) == nullptr)
			return ResultCode::FAIL;

		// Base sequence should be locked during actual pop operation
		TicketScopeLock scopeLock(TicketLock::LockMode::LOCK_EXCLUSIVE, m_SequenceLock);

		pIMsg = std::forward<SharedPointerAtomicT<Message::MessageData>>(m_pMsgWnd[iPosIdx]);
		if (pIMsg == nullptr)
			return ResultCode::FAIL;

		auto prevSeq = m_uiBaseSequence.fetch_add(1,std::memory_order_release);// Message window clear can't cross base sequence change, and this will make sure the previous sync mask change is commited.
		unused(prevSeq);
		Assert(Message::SequenceDifference(pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence, prevSeq) == 0);

		// Between previous exchange and sequence update, the message can be arrived again
		// This will make sure the message is cleaned up
		// Circular case will be probited in AddMsg
		m_pMsgWnd[iPosIdx] = nullptr;

		m_uiMsgCount.fetch_sub(1, std::memory_order_relaxed);

		auto messageMask = ((uint64_t)1) << iPosIdx;
		m_uiSyncMask.fetch_and(~messageMask, std::memory_order_release);

	//Proc_End:

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
		//for (int uiIdx = 0, iSeq = baseSeq; uiIdx < GetWindowSize(); uiIdx++, iSeq++)
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
			for (int iMsg = 0; iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
			{
				m_pMsgWnd[iMsg] = nullptr;
			}
		}
		m_uiBaseSequence.store(0, std::memory_order_release);
		m_uiMsgCount.store(0, std::memory_order_release);
		m_uiSyncMask.store(0, std::memory_order_release);
	}
	
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Send message window
	//


	SendMsgWindow::SendMsgWindow(IHeap& heap)
	{
		m_pMsgWnd = new(heap) MessageData[MessageWindow::MESSAGE_QUEUE_SIZE];
	}

	SendMsgWindow::~SendMsgWindow()
	{
		ClearWindow();
		if (m_pMsgWnd != nullptr)
			delete[] m_pMsgWnd;
		m_pMsgWnd = nullptr;
	}

	// Clear window element
	void SendMsgWindow::ClearWindow()
	{
		MutexScopeLock localLock(GetLock());

		if (m_pMsgWnd)
		{
			for (int iMsg = 0; iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
			{
				m_pMsgWnd[iMsg].Clear();
			}
			//memset( m_pMsgWnd, 0, sizeof(MessageElement)*GetWindowSize() );
		}
		m_uiBaseSequence = 0;
		m_uiMsgCount = 0;

		m_uiHeadSequence = m_uiBaseSequence;
	}


	// Get message info in window, index based on window base
	Result SendMsgWindow::GetAt(uint32_t uiIdx, MessageData* &pMessageElement)
	{
		uint32_t iIdxCur = (m_uiBaseSequence + uiIdx) % MessageWindow::MESSAGE_QUEUE_SIZE;

		if (m_pMsgWnd == NULL)
			return ResultCode::FAIL;

		pMessageElement = &m_pMsgWnd[iIdxCur];

		return ResultCode::SUCCESS;
	}


	// Add a message at the end
	Result SendMsgWindow::EnqueueMessage( TimeStampMS ulTimeStampMS, SharedPointerT<Message::MessageData>& pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		int iIdx = 0;

		if( GetAvailableSize() == 0 )
			return ResultCode::IO_NOT_ENOUGH_WINDOWSPACE;

		if( pIMsg == nullptr )
			return ResultCode::INVALID_POINTER;

		// assign head sequence
		AssertRel(pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence == 0);
		pIMsg->AssignSequence( m_uiHeadSequence );

		iIdx = Message::SequenceDifference(m_uiHeadSequence, m_uiBaseSequence);

		Assert(iIdx < GetWindowSize());
		Assert(iIdx >= 0);
		if (iIdx < 0 || iIdx >= GetWindowSize())
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

	// Release message sequence and slide window if can
	Result SendMsgWindow::ReleaseMsg( uint16_t uiSequence )
	{
		// TODO: math this function thread safe because this function can be called from other thread
		MutexScopeLock localLock(m_Lock);

		Result hr = ResultCode::SUCCESS;
		int iIdx;
		uint32_t iPosIdx;

		if( m_pMsgWnd == NULL )
			return ResultCode::SUCCESS;// nothing to release


		iIdx = Message::SequenceDifference(uiSequence, m_uiBaseSequence);

		if( iIdx >= GetWindowSize() )
		{
			netErr( ResultCode::IO_INVALID_SEQUENCE ); // Out of range
		}

		if(  iIdx < 0 )
		{
			return ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE;
		}

		iPosIdx = (m_uiBaseSequence + iIdx) % MessageWindow::MESSAGE_QUEUE_SIZE;

		// Make it as a can-be-freed
		if( m_pMsgWnd[ iPosIdx ].State != ItemState::Free )
		{
			auto pMsg = *m_pMsgWnd[iPosIdx].pMsg;
			if(pMsg != nullptr )
			{
				if(pMsg->GetMessageHeader()->msgID.IDSeq.Sequence != uiSequence )
				{
					SFLog(Net, Info, "Validation error : Message has Invalid Sequence {0}, {1} Required, msg:{2:X8}", pMsg->GetMessageHeader()->msgID.IDSeq.Sequence, uiSequence, pMsg->GetMessageHeader()->msgID.ID );
				}

				m_pMsgWnd[iPosIdx].pMsg = nullptr;
				m_pMsgWnd[ iPosIdx ].State = ItemState::CanFree;
			}
		}

		// No sliding window for this because this can be called from other thread

	Proc_End:

		return hr;
	}


	// Release message sequence and slide window if can
	Result SendMsgWindow::ReleaseMsg( uint16_t uiSequenceBase, uint64_t uiMsgMask )
	{
		Result hr = ResultCode::SUCCESS;
		int iIdx;

		MutexScopeLock localLock(m_Lock);

		if( m_pMsgWnd == nullptr )
			return ResultCode::SUCCESS;// nothing to release

		uint32_t uiCurBit = 0, uiSyncMaskCur = 1;

		iIdx = Message::SequenceDifference(uiSequenceBase, m_uiBaseSequence);

		if(  iIdx < 0 )
		{
			// SKip already processed message ids
			uint32_t uiIdx = (uint32_t)(-iIdx);
			iIdx = 0;

			// For some reason, peer sent old sync index, skip those indexes, but make sure it's fully send, otherwise it's protocol error
			for (; uiCurBit < uiIdx; uiCurBit++, uiSyncMaskCur <<= 1)
			{
				if ((uiMsgMask & uiSyncMaskCur) == 0)
				{
					// If client use same port for different connect this will be happened, and the connection need to be closed
					netErr(ResultCode::UNEXPECTED);
				}
			}
		}
		else if (iIdx > 0)
		{
			auto maxRelease = std::min((uint32_t)iIdx, MessageWindow::MESSAGE_WINDOW_SIZE);
			for (; uiCurBit < maxRelease; uiCurBit++)
			{
				ReleaseMessage(uiCurBit);
			}


			if (iIdx >= GetWindowSize())
			{
				SlidWindow();
				return ResultCode::SUCCESS;
			}

		}

		// At this point iIdx will have offset from local base sequence
		for (; uiCurBit < MessageWindow::SYNC_MASK_BITS_MAX; uiCurBit++, uiSyncMaskCur <<= 1, iIdx++)
		{
			if ((uiMsgMask & uiSyncMaskCur) == 0) continue;

			ReleaseMessage((uint32_t)iIdx);

		}

		// Slide window
		SlidWindow();

	Proc_End:

		return hr;
	}



	// Release message sequence
	void SendMsgWindow::ReleaseMessage(uint32_t iOffset)
	{
		uint32_t iPosIdx = (m_uiBaseSequence + iOffset) % MessageWindow::MESSAGE_QUEUE_SIZE;

		m_pMsgWnd[iPosIdx].pMsg = nullptr;

		// Mark it as can-be-freed
		if( m_pMsgWnd[ iPosIdx ].State == ItemState::Free || m_pMsgWnd[ iPosIdx ].State == ItemState::CanFree )
		{
			return;
		}
			
		m_pMsgWnd[iPosIdx].State = ItemState::CanFree;
	}


	void SendMsgWindow::SlidWindow()
	{
		auto windowSeq = m_uiBaseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;
		for (int iMsg = 0; m_pMsgWnd[windowSeq].State == ItemState::CanFree && iMsg < MessageWindow::MESSAGE_QUEUE_SIZE; iMsg++)
		{
			m_pMsgWnd[windowSeq].State = ItemState::Free;
			m_uiMsgCount--;
			m_uiBaseSequence++;
			windowSeq = m_uiBaseSequence % MessageWindow::MESSAGE_QUEUE_SIZE;
		}

	}

} // namespace Net
} // namespace SF


