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
#include "Multithread/SFSystemSynchronization.h"
#include "Net/SFConnection.h"
#include "Net/SFMessageData.h"
#include "Container/SFCircularBufferQueue.h"


namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Constants definitions
	//

	namespace MessageWindow
	{
		static constexpr uint32_t MESSAGE_QUEUE_SIZE			= 128;
		static constexpr uint32_t MESSAGE_ACCEPTABLE_SEQUENCE_RANGE			= MESSAGE_QUEUE_SIZE >> 1;
		static constexpr uint32_t SYNC_MASK_BITS_MAX			= 64; // we uses 64bit mask bits for packet
        static constexpr uint32_t RELIABLE_MESSAGE_BUFFER_SIZE = 256 * 1024;


		enum class ItemState
		{
			Free,
			Filled,
			CanFree
		};

	}

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Recv message window
	//

	class RecvMsgWindow
	{
	public:

		struct MessageElement
		{
			SharedPointerAtomicT<MessageData> pMsg;
			Atomic<uint32_t> Sequence = 0;
		};
		using ItemState = MessageWindow::ItemState;

	private:

		// sequence lock
		//TicketLock m_SequenceLock;

		Atomic<uint64_t>			m_uiSyncMask;

		// Base sequence value( sequence Head)
		Atomic<uint16_t>			m_uiBaseSequence;

		// Message count in window
		Atomic<uint32_t>			m_uiMsgCount;

		// Message data array
		MessageElement*			m_pMsgWnd = nullptr;

	public:
		// Constructor
		RecvMsgWindow(IHeap& heap);
		~RecvMsgWindow();

		// get window size
		SF_FORCEINLINE int GetAcceptableSequenceRange() const		{ return MessageWindow::MESSAGE_ACCEPTABLE_SEQUENCE_RANGE; }

		// get message count in window
		SF_FORCEINLINE uint32_t GetMsgCount()						{ return m_uiMsgCount.load(std::memory_order_relaxed); }

		// get message base sequence
		SF_FORCEINLINE uint16_t GetBaseSequence()					{ return m_uiBaseSequence.load(std::memory_order_consume); }

		// Add message
		Result AddMsg(SharedPointerT<MessageData>& pIMsg );

		// Pop message and return it if can
		Result PopMsg(SharedPointerT<MessageData>& pIMsg );

		// Get SyncMask
		uint64_t GetSyncMask();
		
		// Clear window element
		void ClearWindow();
	};


    class RecvMsgWindow2
    {
    public:

        using MessageBuffer = StaticCircularBufferQueue<MessageWindow::RELIABLE_MESSAGE_BUFFER_SIZE>;

#pragma pack(push,4)
        struct MessageInfo
        {
            Atomic<MessageBuffer::BufferItem*> pMsgData{};
            Atomic<uint32_t> Sequence{};
        };
#pragma pack(pop)


        //using ItemState = MessageWindow::ItemState;

    private:

        // Circular buffer for message data
        MessageBuffer m_MessageDataBuffer;

        // Sync mask
        Atomic<uint64_t> m_uiSyncMask;

        // Base sequence value( sequence Head)
        Atomic<uint16_t> m_uiBaseSequence;

        // Message count in window
        Atomic<uint32_t> m_uiMsgCount;

        // Message data array
        MessageInfo m_pMsgWnd[MessageWindow::MESSAGE_QUEUE_SIZE];

    public:
        // Constructor
        RecvMsgWindow2();
        ~RecvMsgWindow2();

        // get window size
        SF_FORCEINLINE int GetAcceptableSequenceRange() const { return MessageWindow::MESSAGE_ACCEPTABLE_SEQUENCE_RANGE; }

        // get message count in window
        SF_FORCEINLINE uint32_t GetMsgCount() { return m_uiMsgCount.load(std::memory_order_relaxed); }

        // get message base sequence
        SF_FORCEINLINE uint16_t GetBaseSequence() { return m_uiBaseSequence.load(std::memory_order_consume); }

        // Add message
        Result AddMsg(const MessageHeader* pHeader);

        // Pop message and return it if can
        Result PopMsg(MessageBuffer::ItemReadPtr& messageData);

        // Get SyncMask
        uint64_t GetSyncMask();

        // Clear window element
        void Reset();

    private:
        void ResetWindowData();
    };

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Send message window
	//

	class SendMsgWindow
	{
	public:

		using ItemState = MessageWindow::ItemState;

		// Message element
		struct WindowMessageData
		{
			ItemState State = ItemState::Free;
			TimeStampMS ulTimeStamp = TimeStampMS(DurationMS_Zero);
			SharedPointerT<MessageData> pMsg;

            WindowMessageData()
			{
			}

			void Clear()
			{
				State = ItemState::Free;
				ulTimeStamp = TimeStampMS(DurationMS_Zero);
				pMsg = nullptr;
			}
		};



	private:
		uint32_t		m_uiHeadSequence = 0;

		// Base sequence value( sequence Head)
		Atomic<uint32_t>	m_uiBaseSequence = 0;

		// Message count in window
		uint32_t		m_uiMsgCount = 0;

		// Message data array
        WindowMessageData*	m_pMsgWnd = nullptr;

		// we have multiple sync variables
		//CriticalSection m_Lock;

        // This is ack sequence queue. We will need a bit bigger ack queue.
        CircularPageQueue<uint32_t> m_ReleasedMessageSequences;

	private:

        // CircularPageQueue can't accept 0 as value
        SF_FORCEINLINE uint32_t ToQueuedSequence(uint32_t sequence) const { return (sequence << 1) | 1; }
        SF_FORCEINLINE uint32_t FromQueuedSequence(uint32_t sequence) const { return sequence >> 1; }

		// Release message sequence and slide window if can
		void ReleaseMessageInternal(uint16_t iOffset);

        // Slide window, if you are using ReleaseSingleMessage, you need to call this on connection tick
        void SlidWindow();

	public:
		// Constructor
		SendMsgWindow(IHeap& heap);
		~SendMsgWindow();

		//CriticalSection& GetLock()				{ return m_Lock; }


		// get acceptable sequence range
		constexpr int GetAcceptableSequenceRange() const { return MessageWindow::MESSAGE_ACCEPTABLE_SEQUENCE_RANGE; }

		// get message count in window
		uint32_t GetMsgCount() { return m_uiMsgCount; }

		// get Head sequence
		uint32_t GetHeadSequence() { return m_uiHeadSequence; }

		// get message base sequence
		uint32_t GetBaseSequence() { return m_uiBaseSequence; }

		// Get message info in window, index based on window base
		Result GetAt(uint32_t uiIdx, WindowMessageData* &pTimeMsg);

		// Clear window element
		void ClearWindow();

		// Get available size at the end
		SF_FORCEINLINE uint32_t GetAvailableSize() { return MessageWindow::MESSAGE_QUEUE_SIZE - (m_uiHeadSequence - GetBaseSequence() + 1); }
		uint32_t GetRemainSequenceCount() { return Math::Max<int32_t>(0, MessageWindow::MESSAGE_ACCEPTABLE_SEQUENCE_RANGE - (m_uiHeadSequence - GetBaseSequence() + 1)); }

		// Add a message at the end
		Result EnqueueMessage(TimeStampMS ulTimeStampMS, SharedPointerT<MessageData>& pIMsg );

        // Queue released sequence
        Result QueueReleasedSequence(uint16_t uiSequence);
        Result QueueReleasedSequence(uint16_t uiSequenceBase, uint64_t uiMsgMask);

        Result UpdateReleasedSequences();

		//// Release message sequence and slide window if can
		//// This can be called from another thread
		//Result ReleaseSingleMessage( uint16_t uiSequence );

		//// Release message by message mask
		//Result ReleaseMsg( uint16_t uiSequenceBase, uint64_t uiMsgMask );

	};


}  // namespace Net
} // namespace SF



