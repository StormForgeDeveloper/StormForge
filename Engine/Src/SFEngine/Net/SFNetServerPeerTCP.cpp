////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network Server Peer implementation 
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Thread/SFThread.h"
#include "Util/SFLog.h"
#include "Protocol/SFProtocol.h"
#include "String/SFStrUtil.h"
#include "String/SFToString.h"
#include "Object/SFSharedObject.h"

#include "Net/SFNetToString.h"
#include "Net/SFConnection.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetServerPeerTCP.h"
#include "Net/SFNetConst.h"
#include "Net/SFConnectionManagerTask.h"


namespace SF {
namespace Net {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Peer network class
	//

	ServerPeerTCP::ServerPeerTCP(IHeap& heap, ServerID InServerID, NetClass localClass)
		:ServerTCP(heap, InServerID, localClass )
	{
	}

	ServerPeerTCP::~ServerPeerTCP()
	{
	}


	// handle Socket accept
	Result ServerPeerTCP::OnAcceptedSocket(SF_SOCKET acceptedSocket, const sockaddr_storage& remoteSockAddr, const PeerInfo& remote, ConnectionPtr &pConn)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<ConnectionTCP> pConnection;
		PeerInfo local;
		uint64_t cid = 0;

		pConn = nullptr;

		// Connect to IOCP
		if ((Service::ConnectionManager->GetConnectionByAddr(remoteSockAddr, pConn)))
		{
			pConnection = pConn.StaticCast<ConnectionTCP>();
			pConnection->CloseConnection("Duplicated connection for server peer");
			Service::ConnectionManager->RemoveConnection(pConn);
			pConnection->DisconnectNRelease("PeerTCP Duplicated connection");
			pConn = SharedPointerT<Connection>();
			SFLog(Net, Warning, "Swap incoming connection socket with old server connection CID:{0}", pConnection->GetCID());
		}


		{
			// Create New connection for accept
			pConnection = NewObject<Net::ConnectionTCPServer>(GetHeap());
			//pConnection = new(GetHeap()) ConnectionTCPServer(GetHeap());
			if (pConnection == nullptr)// Maybe max connection ?
			{
				SFLog(Net, Error, "Failed to allocate a new connection now active:{0}", Service::ConnectionManager->GetNumActiveConnection());
				netErr(ResultCode::FAIL);
			}

			pConn = pConnection;
		}


		local.SetInfo(GetNetClass(), GetLocalAddress(), GetServerID());

		// Initialize connection
		netChk( pConnection->InitConnection( local, remote) );

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::Stream, pConnection->GetSocketFamily(), acceptedSocket));

		pConnection->GetMyNetIOAdapter().SetSocket(pConnection->GetSocketFamily(), SockType::Stream, acceptedSocket);

		acceptedSocket = INVALID_SOCKET;

		netChk(Service::NetSystem->RegisterSocket(&pConnection->GetMyNetIOAdapter()));

		pConn->SetCID(Service::ConnectionManager->NewCID());
		cid = pConnection->GetCID();

		SFLog(Net, Info, "Connection accepted CID:{0}, Local:{1}, Remote:{2}, sock:{3}", pConnection->GetCID(), local.PeerAddress, remote.PeerAddress, pConnection->GetSocket());


		pConn->SetTickGroup(EngineTaskTick::AsyncTick);
		Service::ConnectionManager->AddConnection(pConn);

		GetNewConnectionHandler()(pConn);

		pConn = nullptr;


	Proc_End:

		if (acceptedSocket != INVALID_SOCKET)
			Service::NetSystem->CloseSocket(acceptedSocket);

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
				SFLog(Net, Info, "Net Con Accept Svr:{0}, CID:{1}, From {2}", GetLocalAddress().Port, cid, remote.PeerAddress );
		}

		return hr;

	}




	// Connect to other peer
	Result ServerPeerTCP::RegisterServerConnection( ServerID serverID, NetClass netClass, const NetAddress& destAddress, Net::ConnectionPtr &pConnection )
	{
		Result hr = ResultCode::SUCCESS;
		uint64_t CID = 0;


		auto pConn = NewObject<ConnectionPeerTCP>(GetHeap());
		netMem(pConn);
		pConn->SetCID(Service::ConnectionManager->NewCID());

		CID = pConn->GetCID();

		netChk(pConn->Connect(GetLocalPeerInfo(), PeerInfo(netClass, destAddress, serverID)));


		pConnection = std::forward<Net::ConnectionPtr>(pConn.StaticCast<Connection>());
		pConn = nullptr;

	Proc_End:

		if( (hr) )
		{
			SFLog(Net, Info, "ServerPeer Allowing Server:{2}:{3}, {0}, CID:{1}", destAddress, CID, netClass, serverID);
		}

		if (pConn != nullptr)
		{
			pConn->CloseConnection("Connect failed during registering server entity");
		}

		return hr;
	}



} // namespace Net	
} // namespace SF

