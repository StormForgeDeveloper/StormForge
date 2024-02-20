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

		class ConnectionTCP : public Connection
		{
		public:

			typedef Connection super;

			class MyNetSocketIOAdapter : public SocketIOTCP
			{
			private:
                using super = SocketIOTCP;

				ConnectionTCP& m_Owner;

			public:

				MyNetSocketIOAdapter(ConnectionTCP& owner);

				ConnectionState GetConnectionState() { return m_Owner.GetConnectionState(); }
				uint64_t GetCID() { return m_Owner.GetCID(); }

				void CloseConnection(const char* reason) { m_Owner.CloseConnection(reason); }


				// Send message to connection with network device
				virtual Result WriteBuffer(IOBUFFER_WRITE* pSendBuffer) override;

				virtual Result PendingRecv(IOBUFFER_READ* pRecvBuffer = nullptr) override;

				// called when receiving TCP message
				virtual Result Recv(IOBUFFER_READ* pIOBuffer) override;
				virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ*& pIOBuffer) override;

				virtual Result OnWriteReady() override;
                virtual Result OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE* pIOBuffer) override;

			};


		private:

            // socket IO adapter
			MyNetSocketIOAdapter m_NetIOAdapter;

            // send buffer queue size
            CriticalSection m_SendBufferQueueDequeueLock;
            CircularBufferQueue m_SendBufferQueue;

            // TODO: refactor to traffic control unit
			//// Guaranteed send/ack count
			//std::atomic<int32_t> m_lGuarantedSent;
			//std::atomic<int32_t> m_lGuarantedAck;


			// Temporary incoming buffer for fragmented incoming packet buffer
			uint	m_ReceivedDataSize;
			std::vector<uint8_t>	m_bufRecvTem;

			// Recv overlapped buffer. recv 
			UniquePtr<IOBUFFER_READ> m_RecvBuffer;

			//WriteBufferQueue m_WriteBuffer;

		protected:
			// Special net control packet count on the same connection state. ex)Connect packet
			uint m_uiSendNetCtrlCount;

			// True, if this is client side connection
			bool m_IsClientConnection;

			// Flag indicating whether TCP socket layer connection has been established.
			bool m_IsTCPSocketConnectionEstablished;

            Atomic<bool> m_bWriteIsReady;

			ConnectionMessageAction_HandleAck m_HandleAck;
			ConnectionMessageAction_HandleNack m_HandleNack;
			ConnectionMessageAction_HandleHeartbeat m_HandleHeartbeat;
			ConnectionMessageAction_HandleTimeSync m_HandleTimeSync;
			ConnectionMessageAction_HandleConnect m_HandleConnect;
			ConnectionMessageAction_HandleDisconnect m_HandleDisconnect;

		protected:

			Result SendRaw(const MessageHeader* pMsgHeader);
            Result ProcessSendQueue();

		public:
			// Constructor
			ConnectionTCP(IHeap& heap);
			virtual ~ConnectionTCP();


			virtual bool CanDelete() override;
			virtual void Dispose() override;

			MyNetSocketIOAdapter& GetMyNetIOAdapter() { return m_NetIOAdapter; }

			bool GetIsIORegistered() const { return m_NetIOAdapter.GetIsIORegistered(); }

            bool IsSocketReadyToSend() const { return !m_IsClientConnection || m_IsTCPSocketConnectionEstablished; }

			IOBUFFER_READ* GetRecvBuffer() { return m_RecvBuffer.get(); }

			SockFamily GetSocketFamily() const { return GetLocalInfo().PeerAddress.SocketFamily; }


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

			// try connect with already given information
			Result Connect();

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

		class ConnectionTCPClient : public ConnectionTCP
		{
		public:

			using super = ConnectionTCP;

		private:

			ConnectionMessageAction_HandleTimeSyncRtn m_HandleTimeSyncRtn;
            ConnectionStateAction_WaitRW m_WaitRW;
            ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
			ConnectionStateAction_SendConnect m_SendConnect;
			ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
			ConnectionStateAction_SendDisconnect m_SendDisconnect;


		public:
			// Constructor
			ConnectionTCPClient(IHeap& heap);
			~ConnectionTCPClient();

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;

		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network server connection class
		//

		class ConnectionTCPServer : public ConnectionTCP
		{
		public:

			using super = ConnectionTCP;

		private:
			ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
			ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
			ConnectionStateAction_SendDisconnect m_SendDisconnect;

		public:
			// Constructor
			ConnectionTCPServer(IHeap& heap);
			~ConnectionTCPServer();

		};



		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network server connection class
		//

		class ConnectionPeerTCP : public ConnectionTCP
		{
		public:

			using super = ConnectionTCP;

		private:
			ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
			ConnectionStateAction_SendConnect m_SendConnect;
			ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
			ConnectionStateAction_SendDisconnect m_SendDisconnect;

		public:
			// Constructor
			ConnectionPeerTCP(IHeap& heap);
			~ConnectionPeerTCP();

			virtual void OnConnectionResult(Result hrConnect) override;

		};


	}  // namespace Net
} // namespace SF



