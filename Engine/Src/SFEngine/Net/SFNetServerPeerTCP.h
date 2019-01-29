////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Server Peer implementation 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Thread/SFThread.h"
#include "Thread/SFSynchronization.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetServerTCP.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSvrDef.h"



namespace SF {
namespace Svr {
namespace Config {
	class GenericServer;
};
};
};


namespace SF {
namespace Net {
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Peer Server network class
	//

	class ServerPeerTCP : public ServerTCP
	{
	public:

	private:

	public:
		ServerPeerTCP(ServerID InServerID, NetClass localClass);
		virtual ~ServerPeerTCP();


		/////////////////////////////////////////////////////////////////////////////////////////////
		//  Net callback

		// handle Socket accept
		virtual Result OnAcceptedSocket(SOCKET acceptedSocket, const sockaddr_storage& remoteSockAddr, const PeerInfo& remoteInfo, ConnectionPtr &pConnOut ) override;


		// Connect to other peer
		Result RegisterServerConnection(ServerID serverID, NetClass netClass, const NetAddress& netAddress, Net::ConnectionPtr &pConnection);

	};




} // namespace SF
} // namespace Net



