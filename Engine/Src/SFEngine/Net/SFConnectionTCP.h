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

				ConnectionTCP& m_Owner;

			public:

				MyNetSocketIOAdapter(ConnectionTCP& owner);

				ConnectionState GetConnectionState() { return m_Owner.GetConnectionState(); }
				uint64_t GetCID() { return m_Owner.GetCID(); }
				IConnectionEventHandler* GetEventHandler() { return m_Owner.GetEventHandler(); }

				void CloseConnection(const char* reason) { m_Owner.CloseConnection(reason); }


				// Send message to connection with network device
				virtual Result WriteBuffer(IOBUFFER_WRITE* pSendBuffer) override;

				virtual Result PendingRecv(IOBUFFER_READ* pRecvBuffer = nullptr) override;

				// called when receiving TCP message
				virtual Result Recv(IOBUFFER_READ* pIOBuffer) override;
				virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ*& pIOBuffer) override;

				virtual Result OnWriteReady() override;

			};


		private:

			MyNetSocketIOAdapter m_NetIOAdapter;


			// Guaranteed send/ack count
			std::atomic<int32_t> m_lGuarantedSent;
			std::atomic<int32_t> m_lGuarantedAck;


			// Temporary incoming buffer for fragmented incoming packet buffer
			uint	m_uiRecvTemUsed;
			std::vector<uint8_t>	m_bufRecvTem;

			// Recv overlapped buffer. recv 
			IOBUFFER_READ m_RecvBuffer;

			WriteBufferQueue m_WriteBuffer;

		protected:
			// Special net control packet count on the same connection state. ex)Connect packet
			uint m_uiSendNetCtrlCount;

			// True, if this is client side connection
			bool m_IsClientConnection;

			// Flag indicating whether TCP socket layer connection has been established.
			bool m_IsTCPSocketConnectionEstablished;

		protected:


			virtual Result SendRaw(SharedPointerT<Message::MessageData>& pMsg) override;

		public:
			// Constructor
			ConnectionTCP(IHeap& heap);
			virtual ~ConnectionTCP();


			virtual bool CanDelete() override;
			virtual void Dispose() override;

			MyNetSocketIOAdapter& GetMyNetIOAdapter() { return m_NetIOAdapter; }

			bool GetIsIORegistered() const { return m_NetIOAdapter.GetIsIORegistered(); }

			IOBUFFER_READ* GetRecvBuffer() { return &m_RecvBuffer; }

			// Process network control message
			Result ProcNetCtrl(const MsgNetCtrl* pNetCtrl);

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


			// called when incoming message occure
			virtual Result OnRecv(uint uiBuffSize, const uint8_t* pBuff) override;
			virtual Result OnRecv(SharedPointerT<Message::MessageData>& pMsg) override;

			// Send message to connected entity
			virtual Result Send(SharedPointerT<Message::MessageData>& pMsg) override;

			virtual Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID = 0) override;


			// Update send queue, Reliable UDP
			//virtual Result UpdateSendQueue() override;
			// Update Send buffer Queue, TCP and UDP client connection
			virtual Result UpdateSendBufferQueue() override;
		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network client connection class
		//

		class ConnectionTCPClient : public ConnectionTCP
		{
		public:

		public:
			// Constructor
			ConnectionTCPClient(IHeap& heap);
			~ConnectionTCPClient();

			// Initialize connection
			virtual Result InitConnection(const PeerInfo& local, const PeerInfo& remote) override;

			// Update net control, process connection heartbit, ... etc
			virtual Result TickUpdate() override;

		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network server connection class
		//

		class ConnectionTCPServer : public ConnectionTCP
		{
		public:

		private:

		public:
			// Constructor
			ConnectionTCPServer(IHeap& heap);
			~ConnectionTCPServer();

			// Update net control, process connection heart bit, ... etc
			virtual Result TickUpdate() override;

		};



		////////////////////////////////////////////////////////////////////////////////
		//
		//	TCP Network server connection class
		//

		class ConnectionPeerTCP : public ConnectionTCP
		{
		public:

		private:

		public:
			// Constructor
			ConnectionPeerTCP(IHeap& heap);
			~ConnectionPeerTCP();

			virtual void OnConnectionResult(Result hrConnect) override;

			// Update net control, process connection heart bit, ... etc
			virtual Result TickUpdate() override;

		};


	}  // namespace Net
} // namespace SF



