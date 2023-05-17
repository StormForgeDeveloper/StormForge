////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net connection classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Container/SFCircularPageQueue.h"
#include "Container/SFCircularBufferQueue.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnection.h"
#include "Net/SFMessageWindow.h"
#include "Net/SFNetMessageCollection.h"
#include "Net/SFNetPacketData.h"


namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP Network connection class
	//

	class ConnectionUDPBase : public Connection
	{
	public:
		using super = Connection;

	protected:

		// Receive guaranteed messages
		RecvMsgWindow2		m_RecvReliableWindow;

		// Send Guaranteed Messages
		SendMsgWindow		m_SendReliableWindow;

		// Maximum guaranteed retry at once
		uint				m_uiMaxGuarantedRetryAtOnce;


        // Guaranteed sending wait queue
        MsgQueue m_SendGuaQueue;

        // send message buffer queue
        // messages will be queue up here and pass to gathering buffer for send on connection tick.
        // If circular buffer is full, then net flush will be called on sender thread
        StaticCircularBufferQueue<Const::UDP_CONNECTION_SENDBUFFER_SIZE> m_GatheringBufferQueue;

        // Gathering buffer lock
        CriticalSection m_GatheringBufferLock;

        // packet gathering buffer
        SFUniquePtr<PacketData> m_GatheringBuffer;

        // Minimum gathered size for flush
        uint m_uiMinGatherSizeForFlush = 0;

		// subframe message 
        CriticalSection m_SubframeLock;
		SFUniquePtr<MessageHeader> m_SubFrameCollectionBuffer;

        // Include packet header for all packets. MUDP uses this to add peer id
        bool m_bIncludePacketHeader = false;

		int m_SendBoost = 0;

		CriticalSection		m_UpdateLock;

	private:

		ConnectionMessageAction_UDPHandleAck m_HandleAck;
		ConnectionMessageAction_UDPHandleNack m_HandleNack;
		ConnectionMessageAction_HandleHeartbeat m_HandleHeartbeat;
		ConnectionMessageAction_HandleTimeSync m_HandleTimeSync;
		ConnectionMessageAction_UDPHandleConnect m_HandleConnect;
		ConnectionMessageAction_HandleDisconnect m_HandleDisconnect;

		ConnectionStateAction_SendReliableQueue m_ActSendReliableQueue;
		ConnectionStateAction_SendReliableRetry m_ActSendReliableRetry;
        ConnectionStateAction_FlushNet m_ActFlushNet;


	protected:
		
		CriticalSection& GetUpdateLock() { return m_UpdateLock; }

		virtual Result ProcNetCtrl(const MsgNetCtrlBuffer* pNetCtrl) override;

		Result OnGuaranteedMessageRecv(const MessageHeader* pMsg);
		virtual Result SendReliableMessageAck(MessageID msgID);

	public:
		// Constructor
		ConnectionUDPBase(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionUDPBase();

        virtual void Dispose() override;

		void SetSendBoost(int value) { m_SendBoost = value; }
		int GetSendBoost() { return m_SendBoost; }
		void DecSendBoost() { if (m_SendBoost > 0) m_SendBoost--; }

		//void SetWriteQueueUDP(WriteBufferQueue* writeQueue);

		// Set maximum guaranteed retry count
		uint GetMaxGuarantedRetryAtOnce() { return m_uiMaxGuarantedRetryAtOnce; }
		void SetMaxGuarantedRetry(uint uiMaxGuarantedRetry) { m_uiMaxGuarantedRetryAtOnce = uiMaxGuarantedRetry; }

		SendMsgWindow& GetSendReliableWindow() { return m_SendReliableWindow; }
		RecvMsgWindow2& GetRecvReliableWindow() { return m_RecvReliableWindow; }

		// gathering
        virtual Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0 = 0) override;
		virtual Result SendPending(uint uiCtrlCode, uint uiSequence, MessageID msgID, uint64_t parameter0 = 0) override;
		Result SendFlush();

        // Access to send guaranteed queue
        MsgQueue& GetSendGuaQueue() { return m_SendGuaQueue; }

    protected:
        // Prepare gathering buffer
        Result AllocSendGatherBuffer();
        Result PrepareGatheringBuffer(uint uiRequiredSize);

        Result SendFlushGatheringBufferInternal();

		// frame sequence
		Result SendFrameSequenceMessage(const MessageHeader* pMsg);
		Result OnFrameSequenceMessage(const MessageHeader* pMsg);

    public:
        // Initialize connection
		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote) override;

		// Close connection
		virtual Result CloseConnection(const char* reason) override;

		// Clear Queue
		virtual Result ClearQueues() override;


		// Connect to remote. InitConnection + Connect 
		// Local address will be auto detected
		// @local: NetClass and ID should be assigned
		// @remote: remote information. Address should to be assigned
		virtual Result Connect(PeerInfo local, const PeerInfo& remote) override { return ResultCode::NOT_IMPLEMENTED; }

		// Disconnect connection
		virtual Result Disconnect(const char* reason) override;

		// Send message to connected entity
        virtual Result SendMsg(const MessageHeader* pMsg) override;
        Result SendRaw(const MessageHeader* pMsg);

		// called when incoming message occur
		virtual Result OnRecv(uint uiBuffSize, uint8_t* pBuff) override;
		virtual Result OnRecv(MessageHeader* pMsg) override;

		// We need this for event handling on server
		//virtual Result UpdateSendQueue() override;

	};

}  // namespace Net
} // namespace SF
