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
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "Util/SFTimeUtil.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"
#include "String/SFToString.h"
#include "Net/SFNetToString.h"

#include "Protocol/SFProtocol.h"


// define if emulate packet loss
//#ifdef _DEBUG
//#define UDP_PACKETLOS_EMULATE
//#endif


#ifdef UDP_PACKETLOS_EMULATE
	#define UDP_PACKETLOS_RATE	5
	#define UDP_PACKETLOS_BOUND	1
#endif // #ifdef UDP_PACKETLOS_EMULATE


namespace SF {
namespace Net {

	

	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//


	// Constructor
	ConnectionUDPServerPeer::ConnectionUDPServerPeer(IHeap& heap, SocketIO* ioHandler)
		: ConnectionUDP(heap, ioHandler)
	{
		// limit server net retry maximum
		SetHeartbeatTry( Const::SVR_HEARTBEAT_TIME_PEER );
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );
	}

	ConnectionUDPServerPeer::~ConnectionUDPServerPeer()
	{
		m_RecvReliableWindow.ClearWindow();
		m_SendReliableWindow.ClearWindow();
	}


	// Initialize packet synchronization
	Result ConnectionUDPServerPeer::InitSynchronization()
	{
		Result hr = ResultCode::SUCCESS;

		netChk(ConnectionUDP::InitSynchronization() );

		m_RecvReliableWindow.ClearWindow();
		m_SendReliableWindow.ClearWindow();

	Proc_End:


		return hr;
	}
	
	// Process network control message
	Result ConnectionUDPServerPeer::ProcNetCtrl( const MsgNetCtrl* pNetCtrl )
	{
		Result hr = ResultCode::SUCCESS;


		netChk(ConnectionUDP::ProcNetCtrl( pNetCtrl ) );


		switch( pNetCtrl->msgID.IDs.MsgCode )
		{
		case NetCtrlCode_Connect:
			switch (GetConnectionState())
			{
			case ConnectionState::CONNECTED:
				// This case could be a reconnected case while  this connection didn't realized the disconnect
				//InitSynchronization();
				break;
			default:
				break;
			};
		default:
			break;
		};


	Proc_End:

		return hr;
	}


	//// Update net control, process connection heartbeat, ... etc
	//Result ConnectionUDPServerPeer::TickUpdate()
	//{
	//	Result hr = ResultCode::SUCCESS;

	//	netChk(ConnectionUDP::TickUpdate() );


	//Proc_End:

	//	SendFlush();

	//	return hr;
	//}





	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server UDP Network connection class
	//

	// Constructor
	ConnectionUDPServer::ConnectionUDPServer(IHeap& heap, SocketIO* ioHandler)
		: ConnectionUDP(heap, ioHandler)
	{
		// limit server net retry maximum
		SetHeartbeatTry( Const::SVR_HEARTBEAT_TIME_UDP );
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );
	}

	ConnectionUDPServer::~ConnectionUDPServer()
	{
		ClearQueues();
	}


	//// Update net control, process connection heartbeat, ... etc
	//Result ConnectionUDPServer::TickUpdate()
	//{
	//	Result hr = ResultCode::SUCCESS;

	//	netChk(ConnectionUDP::TickUpdate() );


	//Proc_End:

	//	SendFlush();

	//	return hr;
	//}

	



	////////////////////////////////////////////////////////////////////////////////
	//
	//	client UDP Network connection class
	//


	ConnectionUDPClient::MyNetSocketIOAdapter::MyNetSocketIOAdapter(ConnectionUDPClient &owner)
		: SocketIOUDP(owner.GetHeap())
		, m_Owner(owner)
	{
		SetUserSocketID(m_Owner.GetCID());
	}


	Result ConnectionUDPClient::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS;

		if (pIOBuffer != nullptr && pIOBuffer->Operation != IOBUFFER_OPERATION::OP_UDPREAD)
		{
			netErr(ResultCode::UNEXPECTED);
		}


		// Pending recv count and registered status should be checked together so that we can prevent infinit pending recv
		// And PendingRecv should be decreased after new pending is happened
		if (GetIsIORegistered())
		{

			if (hrRes)
			{
				netChkPtr(pIOBuffer);

				if (!(hr = m_Owner.OnRecv(pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->buffer)))
					SFLog(Net, Debug3, "Read IO failed with CID {0}, hr={1:X8}", m_Owner.GetCID(), hr);

				m_Owner.PendingRecv();
			}
			else
			{
				// TODO: need to mark close connection
				m_Owner.Disconnect("Recv failed");
			}
		}

	Proc_End:

		// decrease should be happened at last, and always
		if (NetSystem::IsProactorSystem())
			DecPendingRecvCount();

		if (pIOBuffer != nullptr)
		{
			pIOBuffer->SetPendingFalse();
			Util::SafeDelete(pIOBuffer);
		}


		return hr;

	}

	Result ConnectionUDPClient::MyNetSocketIOAdapter::OnWriteReady()
	{
		// We will not need this feature
		return ProcessSendQueue();

	}


	// Send message to connection with network device
	Result ConnectionUDPClient::MyNetSocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		auto result = SocketIOUDP::WriteBuffer(pSendBuffer);
		switch ((uint32_t)result)
		{
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTCONN:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// Send fail by connection close
			// Need to disconnect
			result = ResultCode::IO_CONNECTION_CLOSED;
			m_Owner.Disconnect("SendBufferUDP is failed");
			break;
		}

		return result;

		//return m_Owner.SendBufferUDP(pSendBuffer);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//	client UDP Network connection class
	//

	// Constructor
	ConnectionUDPClient::ConnectionUDPClient(IHeap& heap)
		: ConnectionUDP(heap, &m_NetIOAdapter)
		, m_NetIOAdapter(*this)
	{
		// limit client net retry maximum
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );

		SetLocalClass( NetClass::Client );


		// We will share the write queue for UDP
		//SetWriteQueue(new WriteBufferQueue);
	}

	ConnectionUDPClient::~ConnectionUDPClient()
	{
		ClearQueues();

		//if (GetWriteQueue()) GetHeap().Delete(GetWriteQueue());
	}

	void ConnectionUDPClient::Dispose()
	{
		ConnectionUDP::Dispose();
		ClearQueues();
		m_NetIOAdapter.CloseSocket();
	}


	// Pending recv New one
	Result ConnectionUDPClient::PendingRecv()
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;
		IOBUFFER_READ *pOver = nullptr;

		if (!NetSystem::IsProactorSystem())
			return ResultCode::SUCCESS;

		m_NetIOAdapter.IncPendingRecvCount();


		while(1)
		{
			pOver = new(GetHeap()) IOBUFFER_READ;
			hrErr = m_NetIOAdapter.Recv(pOver);
			switch ((uint32_t)hrErr)
			{
			case (uint32_t)ResultCode::SUCCESS:
			case (uint32_t)ResultCode::IO_IO_PENDING:
			case (uint32_t)ResultCode::IO_WOULDBLOCK:
				pOver = nullptr;
				goto Proc_End;// success
				break;
			case (uint32_t)ResultCode::IO_TRY_AGAIN:
			default:
				Disconnect("Pending recv is failed");
				goto Proc_End;
			}
		}


	Proc_End:

		Util::SafeDelete(pOver);

		return hr;
	}


	// Initialize connection
	Result ConnectionUDPClient::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		m_NetIOAdapter.ResetPendingRecvCount();
		m_NetIOAdapter.ResetPendingSendCount();

		return Connection::InitConnection(local, remote);
	}


	// Connect to remote. InitConnection + Connect 
	// Local address will be auto detected
	Result ConnectionUDPClient::Connect(PeerInfo local, const PeerInfo& remote)
	{
		Result hr = ResultCode::SUCCESS;
		SF_SOCKET socket = INVALID_SOCKET;
		sockaddr_storage bindAddr;


		if (remote.PeerAddress.SocketFamily == SockFamily::IPV4)
			Net::GetLocalAddressIPv4(local.PeerAddress);
		else
			Net::GetLocalAddressIPv6(local.PeerAddress);

		socket = Service::NetSystem->Socket(local.PeerAddress.SocketFamily, SockType::DataGram);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "Failed to Open Client Socket {0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::DataGram, local.PeerAddress.SocketFamily, socket));

		bindAddr = (sockaddr_storage)local.PeerAddress;
		if (bind(socket, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}
		local.PeerAddress = bindAddr;


		netChk(InitConnection(local, remote));
		SFLog(Net, Info, "Initialize connection CID:{0}, Addr:{1}", GetCID(), remote.PeerAddress);

		m_NetIOAdapter.SetSocket(local.PeerAddress.SocketFamily, SockType::DataGram, socket);

		socket = INVALID_SOCKET;

		netChk(Service::NetSystem->RegisterSocket(&m_NetIOAdapter));

		netChk(PendingRecv());

		//netChk(Service::ConnectionManager->PendingWaitConnection(pConn));

		//netChk( CliSystem::AddConnectionTask( &GetConnectionManager(), pConn ) );


	Proc_End:

		if (socket != INVALID_SOCKET)
			Service::NetSystem->CloseSocket(socket);

		return hr;
	}


	// Reinitialize and set remote address
	Result ConnectionUDPClient::ReInitialize( const sockaddr_storage& socAddr )
	{
		SetConnectionState(ConnectionState::CONNECTING);

		UpdateConnectionTime();// m_tConnectionTime = Util::Time.GetTimeMs();

		SetRemoteAddress( socAddr );

		m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
		m_ulNetCtrlTime = Util::Time.GetTimeMs();

		SetLocalClass( NetClass::Client );

		return ResultCode::SUCCESS;
	}


	// Update Send buffer Queue, TCP and UDP client connection
	Result ConnectionUDPClient::UpdateSendBufferQueue()
	{
		return m_NetIOAdapter.ProcessSendQueue();
	}


} // namespace Net
} // namespace SF


