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


	protected:
		// Recive Sorted messages
		RecvMsgWindow		m_RecvReliableWindow;

		// Send Guaranted Messages
		SendMsgWindow		m_SendReliableWindow;

		// Maximum guaranted retry at once
		uint				m_uiMaxGuarantedRetryAtOnce;

		// packet gathering buffer
		uint				m_uiGatheredSize;
		uint8_t*				m_pGatheringBuffer;


		// Recv guaranted Message Queue, to enable MT enqueue
		MsgQueue			 m_RecvGuaQueue;

		// subframe message
		SharedPointerT<Message::MessageData>		m_SubFrameMessage;

		// UDP send queue
		WriteBufferQueue*			m_pWriteQueuesUDP;


	protected:
		
		// Process network control message
		virtual Result ProcNetCtrl( const MsgNetCtrl* pNetCtrl ) = 0;


		// Process Recv queue
		virtual Result ProcRecvReliableQueue() = 0;

		// Process Send queue
		virtual Result ProcSendReliableQueue() = 0;
		
		// Process message window queue
		virtual Result ProcReliableSendRetry() = 0;



		WriteBufferQueue* GetWriteQueueUDP() { return m_pWriteQueuesUDP; }



		// Send packet buffer to connection with network device
		virtual Result EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer);

		virtual Result SendRaw(SharedPointerT<Message::MessageData> &pMsg) override;

	public:
		// Constructor
		ConnectionUDPBase(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionUDPBase();

		void SetWriteQueueUDP(WriteBufferQueue* writeQueue);


		// Set maximum guaranteed retry count
		void SetMaxGuarantedRetry(uint uiMaxGuarantedRetry) { m_uiMaxGuarantedRetryAtOnce = uiMaxGuarantedRetry; }

		// Set message window size connection
		Result SetMessageWindowSize( uint uiSend, uint uiRecv );

		SendMsgWindow& GetSendReliableWindow() { return m_SendReliableWindow; }


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
		virtual Result Send(SharedPointerT<Message::MessageData> &pMsg ) override;


		// Update Send buffer Queue, TCP and UDP client connection
		virtual Result UpdateSendBufferQueue() override;

		virtual Result ProcGuarrentedMessageWindow(const std::function<void(SharedPointerT<Message::MessageData>& pMsgData)>& action);

	};




}  // namespace Net
}; // namespace SF



