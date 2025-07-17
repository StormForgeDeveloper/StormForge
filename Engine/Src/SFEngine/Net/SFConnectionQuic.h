////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net connection classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFConnection.h"



namespace SF {
	namespace Net {



		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network connection class
		//

		class ConnectionQuic : public Connection
		{
		public:

			typedef Connection super;


		private:

            // send buffer queue size
            CriticalSection m_SendBufferQueueDequeueLock;
            CircularBufferQueue m_SendBufferQueue;

			// Temporary incoming buffer for fragmented incoming packet buffer
			uint	m_ReceivedDataSize;
			std::vector<uint8_t>	m_bufRecvTem;

		protected:

			// True, if this is client side connection
			bool m_IsClientConnection;

            Atomic<bool> m_bWriteIsReady;

			//ConnectionMessageAction_HandleAck m_HandleAck;
			//ConnectionMessageAction_HandleNack m_HandleNack;
			//ConnectionMessageAction_HandleHeartbeat m_HandleHeartbeat;
			//ConnectionMessageAction_HandleTimeSync m_HandleTimeSync;
			//ConnectionMessageAction_HandleConnect m_HandleConnect;
			//ConnectionMessageAction_HandleDisconnect m_HandleDisconnect;

		protected:

			Result SendRaw(const MessageHeader* pMsgHeader);
            Result ProcessSendQueue();

		public:
			// Constructor
			ConnectionQuic(IHeap& heap);
			virtual ~ConnectionQuic();


			virtual bool CanDelete() override;
			virtual void Dispose() override;

			SockFamily GetSocketFamily() const { return SockFamily::Quic; }

			// Clear Queue
			virtual Result ClearQueues() override;


			// Called on connection result
			virtual void OnConnectionResult(Result hrConnect) override;

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;

			// Connect to remote. InitConnection + Connect , doest InitConnection inside
			// Local address will be auto detected
			// @local: NetClass and ID should be assigned
			// @remote: remote information. Address should to be assigned
			virtual Result Connect(PeerInfo local, const PeerInfo& remote) override;

			// Close connection
			virtual Result CloseConnection(const char* reason) override;


			// Raw packet data recv
			virtual Result OnRecv(uint uiBuffSize, uint8_t* pBuff) override;

            // Parsed message data Recv
			virtual Result OnRecv(MessageHeader* pMsg) override;

			// Send message to connected entity
            virtual Result SendMsg(const MessageHeader* pMsg) override;

            virtual Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0) override;
            virtual Result SendPending(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0) override { return SendNetCtrl(uiCtrlCode, uiSequence, returnMsgID, parameter0); }

			// Update Send buffer Queue, TCP and UDP client connection
			//virtual Result UpdateSendBufferQueue() override;

			// Update net control, process connection heartbeat, ... etc
			virtual Result TickUpdate() override;

		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network client connection class
		//

		class ConnectionQuicClient : public ConnectionQuic
		{
		public:

			using super = ConnectionQuic;

		private:

			ConnectionMessageAction_HandleTimeSyncRtn m_HandleTimeSyncRtn;
            ConnectionStateAction_WaitRW m_WaitRW;
            ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
			ConnectionStateAction_SendConnect m_SendConnect;
			ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
			ConnectionStateAction_SendDisconnect m_SendDisconnect;


		public:
			// Constructor
			ConnectionQuicClient(IHeap& heap);
			~ConnectionQuicClient();

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;

		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network server connection class
		//

		class ConnectionQuicServer : public ConnectionQuic
		{
		public:

			using super = ConnectionQuic;

		private:
			ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
			ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
			ConnectionStateAction_SendDisconnect m_SendDisconnect;

		public:
			// Constructor
			ConnectionQuicServer(IHeap& heap);
			~ConnectionQuicServer();

		};



	}  // namespace Net
} // namespace SF



