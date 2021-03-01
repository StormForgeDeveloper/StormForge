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
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnection.h"
#include "Net/SFMessageWindow.h"

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
		// Receive Sorted messages
		RecvMsgWindow		m_RecvReliableWindow;

		// Send Guaranteed Messages
		SendMsgWindow		m_SendReliableWindow;

		// Maximum guaranteed retry at once
		uint				m_uiMaxGuarantedRetryAtOnce;

		// packet gathering buffer
		uint				m_uiGatheredSize;
		uint8_t*			m_pGatheringBuffer;


		// Recv guaranteed Message Queue, to enable MT enqueue
		//MsgQueue			 m_RecvGuaQueue;

		// subframe message
		SharedPointerT<Message::MessageData>		m_SubFrameMessage;

		// UDP send queue
		WriteBufferQueue*			m_pWriteQueuesUDP;

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


	protected:
		
		CriticalSection& GetUpdateLock() { return m_UpdateLock; }

		WriteBufferQueue* GetWriteQueueUDP() { return m_pWriteQueuesUDP; }

		// Send packet buffer to connection with network device
		virtual Result EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer);

		virtual Result SendRaw(const SharedPointerT<Message::MessageData> &pMsg) override;

		virtual Result ProcNetCtrl(const MsgNetCtrl* pNetCtrl) override;

		Result OnGuarrentedMessageRecv(SharedPointerT<Message::MessageData>& pMsg);

	public:
		// Constructor
		ConnectionUDPBase(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionUDPBase();

		void SetSendBoost(int value) { m_SendBoost = value; }
		int GetSendBoost() { return m_SendBoost; }
		void DecSendBoost() { if (m_SendBoost > 0) m_SendBoost--; }

		void SetWriteQueueUDP(WriteBufferQueue* writeQueue);


		// Set maximum guaranteed retry count
		uint GetMaxGuarantedRetryAtOnce() { return m_uiMaxGuarantedRetryAtOnce; }
		void SetMaxGuarantedRetry(uint uiMaxGuarantedRetry) { m_uiMaxGuarantedRetryAtOnce = uiMaxGuarantedRetry; }


		SendMsgWindow& GetSendReliableWindow() { return m_SendReliableWindow; }
		RecvMsgWindow& GetRecvReliableWindow() { return m_RecvReliableWindow; }


		// gathering
		virtual Result SendPending( uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID = 0 ) override;
		virtual Result SendPending(SharedPointerT<Message::MessageData>& pMsg );
		Result SendFlush();

		// Prepare gathering buffer
		Result PrepareGatheringBuffer( uint uiRequiredSize );
		uint GetGatheredBufferSize() { return m_uiGatheredSize; }


		// frame sequence
		Result SendFrameSequenceMessage(SharedPointerT<Message::MessageData>& pMsg);
		Result OnFrameSequenceMessage(SharedPointerT<Message::MessageData>& pMsg, const std::function<void(SharedPointerT<Message::MessageData>& pMsgData)>& action);

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
		virtual Result Send(const SharedPointerT<Message::MessageData> &pMsg ) override;

		// called when incoming message occur
		virtual Result OnRecv(uint uiBuffSize, const uint8_t* pBuff) override;
		virtual Result OnRecv(SharedPointerT<Message::MessageData>& pMsg) override;

		// Update Send buffer Queue, TCP and UDP client connection
		virtual Result UpdateSendBufferQueue() override;

		// We need this for event handling on server
		virtual Result UpdateSendQueue() override;

	};


}  // namespace Net
} // namespace SF

