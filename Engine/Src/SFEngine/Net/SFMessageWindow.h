////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net message window classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFCircularPageQueue.h"
#include "Thread/SFSystemSynchronization.h"
#include "Net/SFConnection.h"


namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Packet message Sorting Window class
	//

	class MsgWindow
	{
	public:

		enum MessageElementState
		{
			MSGSTATE_FREE,
			MSGSTATE_DATA,
			MSGSTATE_CANFREE
		};

		// Message element
		struct MessageElement
		{
			MessageElementState state;
			TimeStampMS ulTimeStamp;
			SharedPointerT<Message::MessageData> pMsg;

			MessageElement()
				: state(MSGSTATE_FREE)
				, ulTimeStamp(DurationMS(0))
			{
			}

			void Clear()
			{
				state = MSGSTATE_FREE;
				ulTimeStamp = TimeStampMS(DurationMS(0));
				pMsg = nullptr;
			}
		};

	protected:
		// Base sequence value( sequence Head)
		uint		m_uiBaseSequence;

		// Window base index
		uint		m_uiWndBaseIndex;

		// Window size
		uint		m_uiWndSize;

		// Message count in window
		uint		m_uiMsgCount;

		// Message data array
		MessageElement*	m_pMsgWnd;

	public:
		// Constructor
		MsgWindow(IHeap& memoryManager, INT iWndSize );
		virtual ~MsgWindow();

		// get window size
		INT GetWindowSize();

		// get message count in window
		uint GetMsgCount();

		// get message base sequence
		uint GetBaseSequence();

		// Get message info in window, index based on window base
		Result GetAt( uint uiIdx, MsgWindow::MessageElement* &pTimeMsg );
		
		// Clear window element
		virtual void ClearWindow();

	};

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Recv message window
	//

	class RecvMsgWindow
	{
	public:

		typedef SharedPointerAtomicT<Message::MessageData> MessageElement;

		enum { 
			CIRCULAR_QUEUE_SIZE = 64,
			SYNC_MASK_BITS = 1,
			MESSAGE_WINDOW_SIZE = CIRCULAR_QUEUE_SIZE - SYNC_MASK_BITS,
		};

	private:

		// sequence lock
		TicketLock m_SequenceLock;

		std::atomic<uint64_t>			m_uiSyncMask;

		// Base sequence value( sequence Head)
		std::atomic<uint16_t>			m_uiBaseSequence;

		// Message count in window
		std::atomic<uint>			m_uiMsgCount;

		// Message data array
		MessageElement*	m_pMsgWnd;

	public:
		// Constructor
		RecvMsgWindow(IHeap& memoryManager);
		~RecvMsgWindow();

		// get window size
		FORCEINLINE INT GetWindowSize()						{ return MESSAGE_WINDOW_SIZE; }

		// get message count in window
		FORCEINLINE uint GetMsgCount()						{ return m_uiMsgCount.load(std::memory_order_relaxed); }

		// get message base sequence
		FORCEINLINE uint16_t GetBaseSequence()					{ return m_uiBaseSequence.load(std::memory_order_consume); }

		// Add message
		Result AddMsg(SharedPointerT<Message::MessageData>& pIMsg );

		// Pop message and return it if can
		Result PopMsg(SharedPointerT<Message::MessageData>& pIMsg );

		// Get SyncMask
		uint64_t GetSyncMask();
		
		// Clear window element
		void ClearWindow();
	};
	
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Send message window
	//

	class SendMsgWindow : public MsgWindow
	{
	public:

	private:
		uint m_uiHeadSequence;

		// Until this can do thread safe release
		CriticalSection m_Lock;

	private:
		// Release message sequence and slide window if can
		void ReleaseMessage(uint iIdx);


	public:
		// Constructor
		SendMsgWindow(IHeap& memoryManager, INT iWndSize );
		~SendMsgWindow();

		CriticalSection& GetLock()				{ return m_Lock; }

		// Clear window element
		virtual void ClearWindow();

		// Get available size at the end
		uint GetAvailableSize();
		
		// Add a message at the end
		Result EnqueueMessage(TimeStampMS ulTimeStampMS, SharedPointerT<Message::MessageData>& pIMsg );

		// Release message sequence and slide window if can
		// This can be called from another thread
		Result ReleaseMsg( uint16_t uiSequence );
		// Release message by message mask
		Result ReleaseMsg( uint16_t uiSequenceBase, uint64_t uiMsgMask );

	};

	class SendMsgWindowMT
	{
	public:

	private:
		enum {
			CIRCULAR_QUEUE_SIZE = 64,
			SYNC_MASK_BITS = 1,
			MESSAGE_WINDOW_SIZE = CIRCULAR_QUEUE_SIZE - SYNC_MASK_BITS,
		};

		// Message element
		struct MessageElement
		{
			std::atomic<uint64_t> ulTimeStamp;
			SharedPointerAtomicT<Message::MessageData> pMsg;

			MessageElement()
				: ulTimeStamp(0)
			{
			}

			void Clear()
			{
				ulTimeStamp = 0;
				pMsg = nullptr;
			}
		};


	private:
		std::atomic<uint>	m_uiHeadSequence;

		// Base sequence value( sequence Head)
		std::atomic<uint>	m_uiBaseSequence;

		// Message count in window
		std::atomic<uint>	m_uiMsgCount;

		// Message data array
		MessageElement*	m_pMsgWnd;

	private:
		// Release message sequence and slide window if can
		void ReleaseMessage(uint uiSequence);


	public:
		// Constructor
		SendMsgWindowMT(IHeap& memoryManager);
		~SendMsgWindowMT();

		// get window size
		FORCEINLINE INT GetWindowSize()						{ return MESSAGE_WINDOW_SIZE; }

		// get message count in window
		FORCEINLINE uint GetMsgCount()						{ return m_uiMsgCount.load(std::memory_order_relaxed); }

		// Clear window element
		virtual void ClearWindow();

		// Get available size at the end
		INT GetAvailableSize();

		// Add a message at the end
		Result EnqueueMessage(TimeStampMS ulTimeStampMS, SharedPointerT<Message::MessageData>& pIMsg);

		// Release message sequence and slide window if can
		//Result ReleaseMsg(uint16_t uiSequence);

		// Release message by message mask
		Result ReleaseMsg(uint16_t uiSequenceBase, uint64_t uiMsgMask);

	};


	#include "SFMessageWindow.inl"

}  // namespace Net
}; // namespace SF



