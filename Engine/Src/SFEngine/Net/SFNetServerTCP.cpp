////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network Server implementation 
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Thread/SFThread.h"
#include "Util/SFLog.h"
#include "Protocol/SFProtocol.h"
#include "String/SFStrUtil.h"
#include "String/SFToString.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnection.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetServerTCP.h"
#include "Net/SFConnectionManagerTask.h"



namespace SF {
namespace Net {






	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Server socket IO adapter
	//


	// Pending Accept New one
	Result ServerTCP::MySocketIOAdapter::PendingAccept()
	{
		Result hr = ResultCode::SUCCESS;
		uint iMaxAccept = Util::Max((uint)Const::TCP_ACCEPT_PENDING_MAX, (uint)1);

		// skip if not accept mode
		if (!NetSystem::IsProactorSystem() || !m_Owner.GetIsEnableAccept())
			goto Proc_End;

		// if server not initialized
		if (GetIOSocket() == INVALID_SOCKET)
			goto Proc_End;

		// used buffer count == pended accept count
		while (m_PendingAccept.load(std::memory_order_acquire) < iMaxAccept)
		{
			IOBUFFER_ACCEPT* pAcceptInfo = nullptr;

			SFLog(Net, Info, "Pending accept : {0}, {1}", m_PendingAccept.load(std::memory_order_relaxed), Service::ConnectionManager->GetNumActiveConnection());

			netChk(Accept(pAcceptInfo));

			m_PendingAccept.fetch_add(1, std::memory_order_relaxed);

		}// while

	Proc_End:


		return hr;
	}

	Result ServerTCP::MySocketIOAdapter::Accept(IOBUFFER_ACCEPT* &pAcceptInfo)
	{
		Result hr = SocketIOTCP::Accept(pAcceptInfo);

		if (hr == ResultCode::IO_TRY_AGAIN)
		{
			SFLog(Net, Info, "TCP accept busy, try again {0} accepts are queued", GetPendingAccept());
		}

	//Proc_End:

		return hr;
	}

	// On New connection accepted
	Result ServerTCP::MySocketIOAdapter::OnIOAccept(Result hrRes, IOBUFFER_ACCEPT *pOverAccept)
	{
		Result hr = ResultCode::SUCCESS;
		sockaddr_storage remoteAddr;
		SOCKET sockSvr = GetIOSocket();
		SOCKET sockAccept = pOverAccept->sockAccept;
		Net::PeerInfo remote;

		netChkPtr(pOverAccept);

		if (NetSystem::IsProactorSystem())
			m_PendingAccept.fetch_sub(1, std::memory_order_relaxed);


		// skip if not accept mode
		if (!m_Owner.GetIsEnableAccept())
		{
			goto Proc_End;
		}

		if ((hrRes))
		{
			netChk(Service::NetSystem->HandleAcceptedSocket(sockSvr, pOverAccept, remoteAddr));

			remote.PeerAddress = remoteAddr;

			ConnectionPtr pConnOut;
			netChk(m_Owner.OnAcceptedSocket(sockAccept, remoteAddr, remote, pConnOut));

			sockAccept = INVALID_SOCKET;
		}
		else
		{
			hr = hrRes;
		}


	Proc_End:

		Util::SafeDelete(pOverAccept);

		if (sockAccept != INVALID_SOCKET)
		{
			Service::NetSystem->CloseSocket(sockAccept);
		}

		PendingAccept();

		return hr;
	}


	Result ServerTCP::MySocketIOAdapter::Recv(IOBUFFER_READ* pIOBuffer)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}

	// called when receiving message
	Result ServerTCP::MySocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		Assert(false);
		return ResultCode::NOT_IMPLEMENTED;
	}

	Result ServerTCP::MySocketIOAdapter::OnWriteReady()
	{
		return ProcessSendQueue();
	}

	Result ServerTCP::MySocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pIOBuffer)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	TCP Server class
	//

	ServerTCP::ServerTCP(ServerID InServerID, NetClass localClass)
		: ServerNet(InServerID, localClass)
		, m_MySocketIOAdapter(this)
	{
		// ServerTCP listen only for accept
		//SetWriteQueue(new WriteBufferQueue);
		SetSocketIO(&m_MySocketIOAdapter);
	}

	ServerTCP::~ServerTCP()
	{
		//if (GetWriteQueue()) GetHeap().Delete(GetWriteQueue());
	}
	
	// handle Socket accept
	Result ServerTCP::OnAcceptedSocket( SOCKET acceptedSocket, const sockaddr_storage& remoteSockAddr, const PeerInfo& remote, ConnectionPtr &pConn)
	{
		Result hr = ResultCode::SUCCESS;
		ConnectionTCP *pConnection = nullptr;

		uint64_t cid = 0;
		PeerInfo local;

		unused(remoteSockAddr);
		
		// Create New connection for accept
		pConnection = new(GetHeap()) ConnectionTCPServer(GetHeap());
		if( pConnection == nullptr )// Maybe max connection ?
		{
			SFLog(Net, Error, "Failed to allocated new connection now active:{0}", Service::ConnectionManager->GetNumActiveConnection() );
			netErr( ResultCode::FAIL );
		}


		pConn = pConnection;


		pConnection->SetConnectingTimeOut( Const::CONNECTION_TIMEOUT );

		local.SetInfo(GetNetClass(), GetLocalAddress(), GetServerID());

		// Initialize connection
		netChk( pConnection->InitConnection( local, remote ) );

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::Stream, pConnection->GetSocketFamily(), acceptedSocket));

		pConnection->GetMyNetIOAdapter().SetSocket(pConnection->GetSocketFamily(), SockType::Stream, acceptedSocket);
		acceptedSocket = INVALID_SOCKET;
		netChk(Service::NetSystem->RegisterSocket(&pConnection->GetMyNetIOAdapter()));

		pConn->SetCID(Service::ConnectionManager->NewCID());
		cid = pConnection->GetCID();

		SFLog(Net, Info, "Connection Accepted CID:{0}, local:{1}, remote:{2}, sock:{3}", pConn->GetCID(), local.PeerAddress, remote.PeerAddress, pConnection->GetSocket());

		pConnection->SetTickGroup(EngineTaskTick::AsyncTick);
		Service::ConnectionManager->AddConnection(pConn);
		GetNewConnectionHandler()(pConn);
		pConn = nullptr;

			
	Proc_End:

		if (acceptedSocket != INVALID_SOCKET)
		{
			Service::NetSystem->CloseSocket(acceptedSocket);
		}

		if( !(hr) )
		{
			if( pConn != nullptr )
			{
				pConn->CloseConnection("Accept socket failed");
				pConn->Dispose();
				pConn = nullptr;
			}

			SFLog(Net, Error, "Tcp Accept failed  hr = {0:X8}", hr );
		}
		else
		{
			if( pConn != nullptr )
				SFLog(Net, Info, "Net Con Accept Svr:{0}, CID:{1}, From {2}", GetLocalAddress(), cid, remote.PeerAddress );
		}

		return hr;

	}



	// Enable/Disable new connection acception
	void ServerTCP::SetIsEnableAccept( bool bIsEnable )
	{
		ServerNet::SetIsEnableAccept( bIsEnable );

		if( IsReady() )
			m_MySocketIOAdapter.PendingAccept();
	}

	// Open host and start listen
	Result ServerTCP::HostOpen( NetClass netCls, const char *strLocalIP, uint16_t usLocalPort )
	{
		Result hr = ResultCode::SUCCESS;
		SOCKET socket = INVALID_SOCKET;
		//int32_t iOptValue;
		int bOptValue;
		sockaddr_storage bindAddr;

		if( GetSocket() != INVALID_SOCKET )// already initialized?
			return ResultCode::SUCCESS;

		netChk(ServerNet::HostOpen( netCls, strLocalIP, usLocalPort ) );


		socket = Service::NetSystem->Socket(GetLocalAddress().SocketFamily, SockType::Stream);
		if( socket == INVALID_SOCKET )
		{
			SFLog(Net, Error, "Failed to Open Server Socket {0:X8}", GetLastNetSystemResult());
			netErr( ResultCode::UNEXPECTED );
		}

		SFLog(Net, Info, "Open Server TCP Host {0}:{1}, sock:{2}", strLocalIP, usLocalPort, socket);

		//iOptValue = Const::SVR_RECV_BUFFER_SIZE;
		//if( setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *)&iOptValue, sizeof(iOptValue)) == SOCKET_ERROR )
		//{
		//	SFLog(Net, Error, "Failed to change socket option SO_RCVBUF = {0}, err = {1:X8}", iOptValue, GetLastNetSystemResult() );
		//	netErr( ResultCode::UNEXPECTED );
		//}

		//iOptValue = Const::SVR_SEND_BUFFER_SIZE;
		//if( setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *)&iOptValue, sizeof(iOptValue)) == SOCKET_ERROR )
		//{
		//	SFLog(Net, Error, "Failed to change socket option SO_SNDBUF = {0}, err = {1:X8}", iOptValue, GetLastNetSystemResult() );
		//	netErr( ResultCode::UNEXPECTED );
		//}

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::Stream, GetLocalAddress().SocketFamily, socket));


		bOptValue = TRUE;
		if( setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptValue, sizeof(bOptValue)) == SOCKET_ERROR )
		{
			SFLog(Net, Error, "Failed to change socket option SO_REUSEADDR = {0}, err = {1:X8}", bOptValue, GetLastNetSystemResult() );
			netErr( ResultCode::UNEXPECTED );
		}

		//if (GetSocketAddr().ss_family== AF_INET6)
		//{
		//	iOptValue = FALSE;
		//	if (setsockopt(socket, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&iOptValue, sizeof(iOptValue)) == SOCKET_ERROR)
		//	{
		//		SFLog(Net, Error, "Failed to change socket option IPV6_V6ONLY = {0}, err = {1:X8}", iOptValue, GetLastNetSystemResult());
		//		netErr( ResultCode::UNEXPECTED );
		//	}
		//}

		GetAnyBindAddr(GetSocketAddr(), bindAddr);
		if (bind(socket, (sockaddr*)&bindAddr, GetSocketAddrSize()) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "Socket bind failed, TCP {0:X8}", GetLastNetSystemResult() );
			netErr( ResultCode::UNEXPECTED );
		}


		if( listen(socket, SOMAXCONN) == SOCKET_ERROR )
		{
			SFLog(Net, Error, "Failed to listen socket {0:X8}", GetLastNetSystemResult() );
			netErr( ResultCode::UNEXPECTED );
		}

		m_MySocketIOAdapter.SetSocket(GetLocalAddress().SocketFamily, SockType::Stream, socket );
		socket = INVALID_SOCKET;

		m_MySocketIOAdapter.GetIOFlagsEditable().IsListenSocket = 1;
		netChk(Service::NetSystem->RegisterSocket(&m_MySocketIOAdapter));


		netChk(m_MySocketIOAdapter.PendingAccept() );

	Proc_End:

		if( socket != INVALID_SOCKET )
			Service::NetSystem->CloseSocket( socket );

		SFLog(Net, Info, "HostOpen {0}, hr={1:X8}", GetLocalAddress(), hr );

		return hr;
	}

	// Close host and close all connections
	Result ServerTCP::HostClose()
	{
		Result hr = ResultCode::SUCCESS;


		netChk(ServerNet::HostClose() );

	Proc_End:

		SFLog(Net, Info, "HostClose {0}, hr={1:X8}", GetLocalAddress(), hr );

		return hr;
	}




} // namespace Net
} // namespace SF

