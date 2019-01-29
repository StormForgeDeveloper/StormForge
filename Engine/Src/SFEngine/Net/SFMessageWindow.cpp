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
	//	Packet message Sorting Window class
	//

	// Constructor
	MsgWindow::MsgWindow(IHeap& memoryManager, INT iWndSize )
	:	m_uiBaseSequence(0)
	, m_uiWndBaseIndex(0)
	, m_uiWndSize( iWndSize )
	, m_uiMsgCount( 0 )
	, m_pMsgWnd(nullptr)
	{
		m_pMsgWnd = new(memoryManager) MessageElement[GetWindowSize()];
		//memset( m_pMsgWnd, 0, sizeof(MessageElement)*GetWindowSize() );
	}

	MsgWindow::~MsgWindow()
	{
		ClearWindow();
		// delete[] m_pMsgWnd;
		GetSystemHeap().Delete(m_pMsgWnd);
	}


	// Get message info in window, index based on window base
	Result MsgWindow::GetAt( uint uiIdx, MsgWindow::MessageElement* &pMessageElement )
	{
		uint iIdxCur = (uiIdx+m_uiWndBaseIndex)%GetWindowSize();

		if( m_pMsgWnd == NULL )
			return ResultCode::FAIL;

		pMessageElement = &m_pMsgWnd[iIdxCur];

		return ResultCode::SUCCESS;
	}


	// Clear window element
	void MsgWindow::ClearWindow()
	{
		if( m_pMsgWnd )
		{
			for( INT iMsg = 0; iMsg < GetWindowSize(); iMsg++ )
			{
				m_pMsgWnd[iMsg].Clear();
			}
			//memset( m_pMsgWnd, 0, sizeof(MessageElement)*GetWindowSize() );
		}
		m_uiBaseSequence = 0;
		m_uiWndBaseIndex = 0;
		m_uiMsgCount = 0;
	}

	
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Recv message window
	//

	RecvMsgWindow::RecvMsgWindow(IHeap& memoryManager)
		: m_uiSyncMask(0)
		, m_uiBaseSequence(0)
		, m_uiMsgCount(0)
		, m_pMsgWnd(nullptr)
	{
		m_pMsgWnd = new(memoryManager) MessageElement[CIRCULAR_QUEUE_SIZE];
	}

	RecvMsgWindow::~RecvMsgWindow()
	{
		ClearWindow();
		//delete[] m_pMsgWnd;
		GetSystemHeap().Delete(m_pMsgWnd);
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


		int iPosIdx = msgSeq % CIRCULAR_QUEUE_SIZE;
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
		INT iPosIdx = baseSequence % CIRCULAR_QUEUE_SIZE;
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
		auto baseSeq = m_uiBaseSequence % CIRCULAR_QUEUE_SIZE;

		uint64_t resultSyncMask = m_uiSyncMask.load(std::memory_order_acquire);
		if (baseSeq != 0)
		{
			auto least = resultSyncMask >> baseSeq;
			auto most = resultSyncMask << (CIRCULAR_QUEUE_SIZE - baseSeq + SYNC_MASK_BITS);
			most >>= SYNC_MASK_BITS; // clear MSB
			resultSyncMask = least | most;
		}

//#ifdef DEBUG
		//uint64_t uiSyncMask = 0;
		//for (INT uiIdx = 0, iSeq = baseSeq; uiIdx < GetWindowSize(); uiIdx++, iSeq++)
		//{
		//	INT iPosIdx = iSeq % CIRCULAR_QUEUE_SIZE;
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
			for (INT iMsg = 0; iMsg < CIRCULAR_QUEUE_SIZE; iMsg++)
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


	SendMsgWindow::SendMsgWindow(IHeap& memoryManager, INT  iWndSize )
		: MsgWindow(memoryManager, iWndSize)
		, m_uiHeadSequence(0)
	{
	}

	SendMsgWindow::~SendMsgWindow()
	{
	}

	// Clear window element
	void SendMsgWindow::ClearWindow()
	{
		MutexScopeLock localLock(GetLock());

		MsgWindow::ClearWindow();
		m_uiHeadSequence = m_uiBaseSequence;
	}

	// Get available size at the end
	uint SendMsgWindow::GetAvailableSize()
	{
		return GetWindowSize() - (m_uiHeadSequence - GetBaseSequence());
	}

	// Add a message at the end
	Result SendMsgWindow::EnqueueMessage( TimeStampMS ulTimeStampMS, SharedPointerT<Message::MessageData>& pIMsg )
	{
		Result hr = ResultCode::SUCCESS;
		INT iIdx = 0;

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
		iIdx = (m_uiWndBaseIndex + iIdx)%m_uiWndSize;

		// check duplicated transaction
		Assert(m_pMsgWnd[ iIdx ].state == MSGSTATE_FREE );

		m_pMsgWnd[ iIdx ].ulTimeStamp = ulTimeStampMS;
		m_pMsgWnd[ iIdx ].pMsg = pIMsg;
		m_pMsgWnd[ iIdx ].state = MSGSTATE_DATA;

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
		INT iIdx;
		uint iPosIdx;

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

		iPosIdx = (m_uiWndBaseIndex + iIdx)%GetWindowSize();

		// Makr it as a can-be-freed
		if( m_pMsgWnd[ iPosIdx ].state != MSGSTATE_FREE )
		{
			auto pMsg = *m_pMsgWnd[iPosIdx].pMsg;
			if(pMsg != nullptr )
			{
				if(pMsg->GetMessageHeader()->msgID.IDSeq.Sequence != uiSequence )
				{
					SFLog(Net, Info, "Validation error : Message has Invalid Sequence {0}, {1} Required, msg:{2:X8}", pMsg->GetMessageHeader()->msgID.IDSeq.Sequence, uiSequence, pMsg->GetMessageHeader()->msgID.ID );
				}

				m_pMsgWnd[iPosIdx].pMsg = nullptr;
				m_pMsgWnd[ iPosIdx ].state = MSGSTATE_CANFREE;
			}
		}

		// No sliding window for this because this can be called from other thread
		// We only can mark can free for this
		//// Slide window
		//for( INT iMsg = 0; m_pMsgWnd[ m_uiWndBaseIndex ].state == MSGSTATE_CANFREE && iMsg < GetWindowSize();  )
		//{
		//	m_uiBaseSequence++;
		//	m_pMsgWnd[ m_uiWndBaseIndex ].state = MSGSTATE_FREE;
		//	m_uiMsgCount--;
		//	iMsg++;
		//	m_uiWndBaseIndex = (m_uiWndBaseIndex+1)%GetWindowSize();
		//}

	Proc_End:

		return hr;
	}


	// Release message sequence and slide window if can
	Result SendMsgWindow::ReleaseMsg( uint16_t uiSequenceBase, uint64_t uiMsgMask )
	{
		Result hr = ResultCode::SUCCESS;
		INT iIdx;

		MutexScopeLock localLock(m_Lock);

		if( m_pMsgWnd == nullptr )
			return ResultCode::SUCCESS;// nothing to release

		uint uiCurBit = 0, uiSyncMaskCur = 1;

		iIdx = Message::SequenceDifference(uiSequenceBase, m_uiBaseSequence);

		if( iIdx >= GetWindowSize() )
		{
			netErr( ResultCode::IO_INVALID_SEQUENCE ); // Out of range
		}

		if(  iIdx < 0 )
		{
			// SKip already processed message ids
			uint uiIdx = (uint)(-iIdx);
			iIdx = 0;

			// If client use same port for different connect this will be happened, and the connection need to be closed
			for (; uiCurBit < uiIdx; uiCurBit++, uiSyncMaskCur <<= 1)
			{
				if ((uiMsgMask & uiSyncMaskCur) == 0)
				{
					netErr(ResultCode::UNEXPECTED);
				}
			}
		}
		else if (iIdx > 0)
		{
			// Using other variable is common, but I used uiCurBit because it need to be increased anyway.
			for (; uiCurBit < (uint)iIdx; uiCurBit++)
			{
				ReleaseMessage(uiCurBit);
			}
		}

		// At this point iIdx will have offset from local base sequence
		for (; uiCurBit < 64; uiCurBit++, uiSyncMaskCur <<= 1, iIdx++)
		{
			if ((uiMsgMask & uiSyncMaskCur) == 0) continue;

			ReleaseMessage((uint)iIdx);

		}

		// Slide window
		for (INT iMsg = 0; m_pMsgWnd[m_uiWndBaseIndex].state == MSGSTATE_CANFREE && iMsg < GetWindowSize(); iMsg++)
		{
			m_uiBaseSequence++;
			m_pMsgWnd[ m_uiWndBaseIndex ].state = MSGSTATE_FREE;
			m_uiMsgCount--;
			m_uiWndBaseIndex = (m_uiWndBaseIndex+1)%GetWindowSize();
			hr = ResultCode::SUCCESS_FALSE;
		}


	Proc_End:

		return hr;
	}



	// Release message sequence
	void SendMsgWindow::ReleaseMessage(uint iIdx)
	{
		uint iPosIdx = (m_uiWndBaseIndex + iIdx)%GetWindowSize();

		// Mark it as can-be-freed
		if( m_pMsgWnd[ iPosIdx ].state == MSGSTATE_FREE || m_pMsgWnd[ iPosIdx ].state == MSGSTATE_CANFREE )
		{
			m_pMsgWnd[iPosIdx].pMsg = nullptr;
			return;
			//continue;
		}
			
		m_pMsgWnd[iPosIdx].pMsg = nullptr;
		m_pMsgWnd[ iPosIdx ].state = MSGSTATE_CANFREE;
	}




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SendMsgWindowMT
	//

	SendMsgWindowMT::SendMsgWindowMT(IHeap& memoryManager)
		: m_uiHeadSequence(0)
		, m_uiBaseSequence(0)
		, m_uiMsgCount(0)
		, m_pMsgWnd(nullptr)
	{
		auto messageElements = new(memoryManager) MessageElement[CIRCULAR_QUEUE_SIZE];
		//memset(messageElements, 0, sizeof(MessageElement)*CIRCULAR_QUEUE_SIZE);
		m_pMsgWnd = messageElements;
	}

	SendMsgWindowMT::~SendMsgWindowMT()
	{
		GetSystemHeap().Delete(m_pMsgWnd);
	}

	// Clear window element
	void SendMsgWindowMT::ClearWindow()
	{
		for (int iMsg = 0; iMsg < CIRCULAR_QUEUE_SIZE; iMsg++)
		{
			m_pMsgWnd[iMsg].Clear();
			//auto pMsg = m_pMsgWnd[iMsg].pMsg.load(std::memory_order_relaxed);
			//Util::SafeRelease(pMsg);
		}
		m_uiHeadSequence = 0;
		m_uiBaseSequence = 0;
		m_uiMsgCount = 0;
	}

	// Get available size at the end
	INT SendMsgWindowMT::GetAvailableSize()
	{
		return GetWindowSize() - (m_uiHeadSequence.load(std::memory_order_relaxed) - m_uiBaseSequence.load(std::memory_order_relaxed));
	}

	// Add a message at the end
	Result SendMsgWindowMT::EnqueueMessage(TimeStampMS ulTimeStampMS, SharedPointerT<Message::MessageData>& pIMsg)
	{
		Result hr = ResultCode::SUCCESS;
		INT iIdx = 0;
		Message::MessageData* expectedMsg;
		uint expectedID;

		if (pIMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		if (GetAvailableSize() <= 0)
			return ResultCode::IO_NOT_ENOUGH_WINDOWSPACE;

		AssertRel(pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence == 0);

		// start from head sequence
		auto sequence = m_uiHeadSequence.load(std::memory_order_acquire);

		expectedMsg = nullptr;
		//do {
			if (expectedMsg != nullptr)
			{
				// It's occupied. let's try next slot
				sequence++;
				if (Message::SequenceDifference(sequence, m_uiBaseSequence.load(std::memory_order_relaxed)) > GetWindowSize())
				{
					// out of sequence, this will very suck.
					Assert(false);
					pIMsg->ClearAssignedSequence();
					netErr(ResultCode::IO_NOT_ENOUGH_WINDOWSPACE);
				}
				expectedMsg = nullptr;
			}

			iIdx = sequence % CIRCULAR_QUEUE_SIZE;
			pIMsg->ClearAssignedSequence();
			pIMsg->AssignSequence(sequence);

			m_pMsgWnd[iIdx].pMsg = std::forward<SharedPointerT<Message::MessageData>>(pIMsg);

		//} while (!m_pMsgWnd[iIdx].pMsg.compare_exchange_weak(expectedMsg, pIMsg, std::memory_order_acquire));


		m_pMsgWnd[iIdx].ulTimeStamp.store(ulTimeStampMS.time_since_epoch().count(), std::memory_order_relaxed);

		expectedID = sequence;
		while (!m_uiHeadSequence.compare_exchange_weak(expectedID, sequence + 1, std::memory_order_release))
		{
			if (expectedID > sequence)
				break; // somebody already moved on
		}

		m_uiMsgCount.fetch_add(1, std::memory_order_relaxed);


	Proc_End:

		return hr;
	}


	// Release message sequence and slide window if can
	Result SendMsgWindowMT::ReleaseMsg(uint16_t uiSequenceBase, uint64_t uiMsgMask)
	{
		Result hr = ResultCode::SUCCESS;
		INT iIdx;
		uint sequence;

		if (m_pMsgWnd == nullptr)
			return ResultCode::SUCCESS;// nothing to release

		uint uiCurBit = 0, uiSyncMaskCur = 1;

		iIdx = Message::SequenceDifference(uiSequenceBase, m_uiBaseSequence.load(std::memory_order_acquire));

		if (iIdx >= GetWindowSize())
		{
			netErr(ResultCode::IO_INVALID_SEQUENCE); // Out of range
		}

		if (iIdx < 0)
		{
			// SKip already processed message ids
			uint uiIdx = (uint)(-iIdx);
			iIdx = 0;
			uiSequenceBase += (uint16_t)uiIdx;

			for (; uiCurBit < uiIdx; uiCurBit++, uiSyncMaskCur <<= 1)
			{
				AssertRel((uiMsgMask & uiSyncMaskCur) != 0);
			}
		}
		else if (iIdx > 0)
		{
			// Using other variable is common, but I used uiCurBit because it need to be increased anyway.
			for (; uiCurBit < (uint)iIdx; uiCurBit++, uiSequenceBase++)
			{
				ReleaseMessage(uiSequenceBase);
			}
		}

		// At this point iIdx will have offset from local base sequence
		for (; uiCurBit < 64; uiCurBit++, uiSyncMaskCur <<= 1, uiSequenceBase++)
		{
			if ((uiMsgMask & uiSyncMaskCur) == 0) continue;

			ReleaseMessage(uiSequenceBase);
		}


		// Slide window
		sequence = m_uiBaseSequence.load(std::memory_order_acquire);
		while (sequence < m_uiHeadSequence.load(std::memory_order_acquire))
		{
			uint iPosIdx = sequence % CIRCULAR_QUEUE_SIZE;

			auto pMsg = *m_pMsgWnd[iPosIdx].pMsg;
			if (pMsg == nullptr)
			{
				auto expected = sequence;
				while (!m_uiBaseSequence.compare_exchange_weak(expected, sequence + 1, std::memory_order_release))
				{
					if (expected != sequence)
					{
						// somebody released this sequence already, let's move on to next
						Assert(expected > sequence);
						break;
					}
				}
			}
			else
			{
				// We've done shifting
				break;
			}

			sequence++;
		}


	Proc_End:

		return hr;
	}

	// Release message sequence and slide window if can
	void SendMsgWindowMT::ReleaseMessage(uint uiSequence)
	{
		uint iPosIdx = uiSequence % CIRCULAR_QUEUE_SIZE;
		m_pMsgWnd[iPosIdx].ulTimeStamp.store(0, std::memory_order_relaxed);
		SharedPointerT<Message::MessageData> pIMsg;
		pIMsg = std::forward<SharedPointerAtomicT<Message::MessageData>>(m_pMsgWnd[iPosIdx].pMsg);
		//auto pIMsg = m_pMsgWnd[iPosIdx].pMsg.exchange(nullptr, std::memory_order_release);
		if (pIMsg != nullptr)
		{
			m_uiMsgCount.fetch_sub(1, std::memory_order_relaxed);
		}
	}



} // namespace Net
} // namespace SF


