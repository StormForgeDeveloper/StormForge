////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net server base type definitions. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFConnectionManager.h"
#include "Net/SFNetSocket.h"


namespace SF {
namespace Net {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server network base interface
	//

	class ServerNet : public EngineObject
	{
	private:
		
		// local Address
		NetAddress m_LocalAddr;

		NetClass m_LocalClass;

		// Socket local address
		sockaddr_storage m_LocalSockAddr;

		// Server ID
		ServerID m_ServerID;

		// Enable new connection?
		bool m_IsEnableAccept = false;

		IConnectionEventHandler* m_DefaultConnectionEventHandler = nullptr;
		
		std::function<void(ConnectionPtr&)> m_NewConnectionhandler;

		SocketIO* m_SocketIO = nullptr;

	protected:

		// Set local address
		void SetLocalAddress( const NetAddress& localAddr )
		{
			m_LocalAddr = localAddr;
			Addr2SockAddr(m_LocalAddr, m_LocalSockAddr);
		}

		void SetNetClass(NetClass value) { m_LocalClass = value; }

		// Set socket
		//inline void SetSocket( SF_SOCKET sock );


		void SetSocketIO(SocketIO* socketIO) { m_SocketIO = socketIO; }

	public:

		ServerNet( ServerID InServerID, NetClass localClass );
		virtual ~ServerNet();

		IConnectionEventHandler* GetDefaultConnectionEventHandler() { return m_DefaultConnectionEventHandler; }
		void SetDefaultConnectionEventHandler(IConnectionEventHandler* value) { m_DefaultConnectionEventHandler = value; }

		ServerID GetServerID() const { return m_ServerID; }
		bool GetIsEnableAccept() const { return m_IsEnableAccept; }

		SocketIO* GetSocketIO() { return m_SocketIO; }
		const SocketIO* GetSocketIO() const { return m_SocketIO; }

		PeerInfo GetLocalPeerInfo() const { return PeerInfo(GetNetClass(), GetLocalAddress(), GetServerID()); }

		// change status of new connection allowance 
		virtual void SetIsEnableAccept(bool bIsEnable);

		// Get Socket address
		const sockaddr_storage& GetSocketAddr() const { return m_LocalSockAddr; }

		int GetSocketAddrSize() const { return m_LocalSockAddr.ss_family == AF_INET6 ? (int)sizeof(sockaddr_in6) : (int)sizeof(sockaddr_in); }

		// Get local address
		const NetAddress& GetLocalAddress() const { return m_LocalAddr; }

		inline NetClass GetNetClass()	 const { return m_LocalClass; }


		// Get Socket
		const SF_SOCKET GetSocket() const { return GetSocketIO() != nullptr ? GetSocketIO()->GetIOSocket() : INVALID_SOCKET; }

		const std::function<void(ConnectionPtr&)>& GetNewConnectionHandler() { return m_NewConnectionhandler; }
		void SetNewConnectionhandler(std::function<void(ConnectionPtr&)> handler);

		// check about initialize
		virtual bool IsReady();


		// Open host and start listen
		virtual Result HostOpen(NetClass netCls, const char *strLocalIP, uint16_t usLocalPort);

		// Close host and close all connections
		virtual Result HostClose();

	};



} // namespace Net
} // namespace SF



