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
#include "Net/SFConnectionUDPBase.h"
#include "Net/SFMessageWindow.h"


namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//

	class ConnectionUDP : public ConnectionUDPBase
	{
	public:

		using super = ConnectionUDPBase;

	public:
		
		ConnectionUDP(IHeap& heap, SocketIO* ioHandler)
			: ConnectionUDPBase(heap, ioHandler)
		{}

		// called when incoming message occur
		virtual Result OnRecv( uint uiBuffSize, const uint8_t* pBuff );
		virtual Result OnRecv(SharedPointerT<Message::MessageData>& pMsg );

		// Update net control, process connection heartbeat, ... etc
		virtual Result TickUpdate() override;
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//

	class ConnectionUDPServerPeer : public ConnectionUDP
	{
	public:

	protected:


	public:
		// Constructor
		ConnectionUDPServerPeer(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionUDPServerPeer();


		// Initialize packet synchronization
		virtual Result InitSynchronization() override;

		Result ProcNetCtrl( const MsgNetCtrl* pNetCtrl ) override;

		// Update net control, process connection heartbeat, ... etc
		//virtual Result TickUpdate() override;
	};

	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//

	class ConnectionUDPServer : public ConnectionUDP
	{
	public:

	protected:


	public:
		// Constructor
		ConnectionUDPServer(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionUDPServer();

		// Update net control, process connection heartbeat, ... etc
		//virtual Result TickUpdate() override;
	};
	



	////////////////////////////////////////////////////////////////////////////////
	//
	//	client UDP Network connection class
	//

	class ConnectionUDPClient : public ConnectionUDP
	{
	public:

		class MyNetSocketIOAdapter : public SocketIOUDP
		{
		private:

			ConnectionUDPClient &m_Owner;

		public:

			MyNetSocketIOAdapter(ConnectionUDPClient &owner);


			// Send message to connection with network device
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

			// called when receiving TCP message
			virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) override;

			virtual Result OnWriteReady() override;
		};

	private:

		MyNetSocketIOAdapter m_NetIOAdapter;

	protected:
		// Send packet buffer to connection with network device
		//virtual Result SendBufferUDP(IOBUFFER_WRITE *pSendBuffer) override;
		//virtual Result EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer) override;

		// Send message to connection with network device
		//virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

	public:
		// Constructor
		ConnectionUDPClient(IHeap& memoryManager);
		~ConnectionUDPClient();

		virtual void Dispose() override;


		// Pending recv New one
		Result PendingRecv();


		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote) override;

		// Connect to remote. InitConnection + Connect 
		// Local address will be auto detected
		// @local: NetClass and ID should be assigned
		// @remote: remote information. Address should to be assigned
		Result Connect(PeerInfo local, const PeerInfo& remote) override;

		// Reinitialize and set remote address
		Result ReInitialize( const sockaddr_storage& socAddr );


		// Update net control, process connection heartbeat, ... etc
		//virtual Result TickUpdate() override;

		// Update Send buffer Queue, TCP and UDP client connection
		virtual Result UpdateSendBufferQueue() override;
	};


}  // namespace Net
} // namespace SF



