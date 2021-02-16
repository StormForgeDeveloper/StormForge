////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network connection manager
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFToString.h"

#include "Net/SFConnection.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFConnectionMUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFConnectionManager.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetToString.h"





namespace SF {
	
	
	

	ConnectionManagerService::Sockaddress::Sockaddress(const sockaddr_storage& src)
	{
		memcpy(this, &src, sizeof(src));
	}


	bool ConnectionManagerService::Sockaddress::operator >(const Sockaddress& src)
	{
		if (ss_family > src.ss_family) return true;

		if (ss_family == AF_INET6)
		{
			auto op1 = (sockaddr_in6*)this;
			auto op2 = (sockaddr_in6*)&src;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			auto& rawAddress = op1->sin6_addr.s6_addr;
			auto& rawAddressSrc = op2->sin6_addr.s6_addr;
			for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
				if (rawAddress[iAddr] > rawAddressSrc[iAddr]) return true;
#elif SF_PLATFORM == SF_PLATFORM_LINUX
			auto& rawAddress = op1->sin6_addr.s6_addr32;
			auto& rawAddressSrc = op2->sin6_addr.s6_addr32;
			for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
				if (rawAddress[iAddr] > rawAddressSrc[iAddr]) return true;
#endif
			if (op1->sin6_port > op2->sin6_port) return true;
		}
		else
		{
			auto op1 = (sockaddr_in*)this;
			auto op2 = (sockaddr_in*)&src;

			if (op1->sin_addr.s_addr > op2->sin_addr.s_addr) return true;
			if (op1->sin_port > op2->sin_port) return true;
		}


		return false;
	}

	bool ConnectionManagerService::Sockaddress::operator ==(const Sockaddress& src)
	{
		if (ss_family != src.ss_family) return false;

		if (ss_family == AF_INET6)
		{
			auto op1 = (sockaddr_in6*)this;
			auto op2 = (sockaddr_in6*)&src;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			auto& rawAddress = op1->sin6_addr.s6_addr;
			auto& rawAddressSrc = op2->sin6_addr.s6_addr;
			for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
				if (rawAddress[iAddr] != rawAddressSrc[iAddr]) return false;
#elif SF_PLATFORM == SF_PLATFORM_IOS
			auto& rawAddress = op1->sin6_addr.s6_addr;
			auto& rawAddressSrc = op2->sin6_addr.s6_addr;
			for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
				if (rawAddress[iAddr] != rawAddressSrc[iAddr]) return false;
#else
			auto& rawAddress = op1->sin6_addr.s6_addr32;
			auto& rawAddressSrc = op2->sin6_addr.s6_addr32;
			for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
				if (rawAddress[iAddr] != rawAddressSrc[iAddr]) return false;
#endif

			if (op1->sin6_port != op2->sin6_port) return false;
		}
		else
		{
			auto op1 = (sockaddr_in*)this;
			auto op2 = (sockaddr_in*)&src;

			if (op1->sin_addr.s_addr != op2->sin_addr.s_addr) return false;
			if (op1->sin_port != op2->sin_port) return false;
		}

		return true;
	}

	bool ConnectionManagerService::Sockaddress::operator !=(const Sockaddress& src)
	{
		return !((*this) == src);
	}

	
namespace Net {





	////////////////////////////////////////////////////////////////////////////////
	//
	//	ConnectionManager
	//
	constexpr StringCrc64 ConnectionManager::TypeName;

	ConnectionManager::ConnectionManager(uint uiBucketSize )
		: LibraryComponent("ConnectionManager")
		, m_Heap("ConnectionManager", GetSystemHeap())
		, m_AddrMap(GetHeap(), uiBucketSize)
		, m_CIDMap(GetHeap(), uiBucketSize)
		, m_PeerIDMap(GetHeap(), uiBucketSize)
		, m_CIDGen(m_Heap)
	{
	}

	ConnectionManager::~ConnectionManager()
	{
		m_AddrMap.Clear();
		m_CIDMap.Clear();
		m_PeerIDMap.Clear();
	}


	// Initialize component
	Result ConnectionManager::InitializeComponent()
	{
		LibraryComponent::InitializeComponent();

		Service::ConnectionManager = this;

		return ResultCode::SUCCESS;
	}

	// Terminate component
	void ConnectionManager::DeinitializeComponent()
	{
		DisconnectAllConnection();

		m_AddrMap.Clear();
		m_CIDMap.Clear();
		m_PeerIDMap.Clear();

		LibraryComponent::DeinitializeComponent();

		Service::ConnectionManager = nullptr;
	}


	void ConnectionManager::AddConnection(SharedPointerT<Connection>& pConn)
	{
		Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPostTick, [pConn, this]()
		{
			AddConnection_Internal(pConn);
		});
	}

	// mapping Add/Remove
	Result ConnectionManager::AddConnection_Internal(const ConnectionPtr& pConn )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Connection> pConnPtr;
		SharedPointerT<Connection> pPtr;

		netChkPtr( pConn );

		if (pConn->GetCID() == 0)
		{
			pConn->SetCID(NewCID());
		}

		if (pConn->GetUseAddressMap())
		{
			if (pConn->GetRemoteSockAddr().ss_family != 0 && (m_AddrMap.Find(pConn->GetRemoteSockAddr(), pPtr)))
			{
				if (pPtr != pConn)
				{
					// same address with different connection.
					// Can be happened when client reuse same address
					// remove previous one
					SFLog(Net, Warning, "Duplicated connection, releasing previous connection CID:{0}", pPtr->GetCID());
					RemoveConnection_Internal(pPtr);

					assert(!m_AddrMap.Find(pConn->GetRemoteSockAddr(), pPtr));
				}
				else
				{
					// already in map
					netErr(ResultCode::INVALID_ARG);
				}
			}
		}

		if ((m_CIDMap.Find(pConn->GetCID(), pConnPtr)))
		{
			// already in map
			netErr( ResultCode::INVALID_ARG );
		}

		if (pConn->GetUseAddressMap() && pConn->GetRemoteSockAddr().ss_family != 0)
		{
			netChk(m_AddrMap.Insert(pConn->GetRemoteSockAddr(), SharedPointerT<Connection>(pConn)));
		}

		if (!(m_CIDMap.Insert(pConn->GetCID(), pConn)))
		{
			// remove
			m_AddrMap.Erase(pConn->GetRemoteSockAddr(), pPtr);
			netErr( ResultCode::UNEXPECTED );
		}

		if ((pConn->GetUsePeerIDMap() && pConn->GetRemoteInfo().PeerID != 0 && !(m_PeerIDMap.Insert(pConn->GetRemoteInfo().PeerID, SharedPointerT<Connection>(pConn)))))
		{
			// remove
			m_AddrMap.Erase(pConn->GetRemoteSockAddr(), pPtr);
			m_CIDMap.Erase(pConn->GetCID(), pConnPtr);
			netErr( ResultCode::UNEXPECTED );
		}

	Proc_End:

		return hr;
	}



	void ConnectionManager::NewMUDPAddress(IHeap& memMgr, ServerNet* pNet, SF_SOCKET socket, const PeerInfo& local, const PeerInfo& remote)
	{
		Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPostTick, [&memMgr, pNet, socket, local, remote, this]()
		{
			NewUDPAddress_Internal<ConnectionMUDPServer>(memMgr, pNet, socket, local, remote);
		});
	}

	void ConnectionManager::NewUDPAddress(IHeap& memMgr, ServerNet* pNet, SF_SOCKET socket, const PeerInfo& local, const PeerInfo& remote)
	{
		Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPostTick, [&memMgr, pNet, socket, local, remote, this]()
		{
			NewUDPAddress_Internal<ConnectionUDPServer>(memMgr, pNet, socket, local, remote);
		});
	}

	void ConnectionManager::AddressRemap(SharedPointerT<Connection>& pConn, const sockaddr_storage &addressOrg, const sockaddr_storage &newAddress)
	{
		Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPostTick, [pConn, addressOrg, newAddress, this]()
		{
			AddressRemap_Internal(pConn, addressOrg, newAddress);
		});
	}

	void ConnectionManager::AddressRemap_Internal(const ConnectionPtr& pConn, const sockaddr_storage &addressOrg, const sockaddr_storage &newAddress)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Connection> pPtr;

		netChk(pConn->GetUseAddressMap());

		if (!(m_AddrMap.Erase(addressOrg, pPtr)))
		{
			SFLog(Net, Warning, "Old address is not found ignoring:{0}", pConn->GetRemoteInfo().PeerAddress);
		}

		netChk(m_AddrMap.Insert(newAddress, SharedPointerT<Connection>(pConn)));

	Proc_End:

		return;
	}

	EngineTaskPtr ConnectionManager::RemoveConnection(SharedPointerT<Connection>& pConn)
	{
		return std::forward<EngineTaskPtr>(Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPostTick, [pConn, this]()
		{
			RemoveConnection_Internal(pConn);
		}));
	}

	void ConnectionManager::RemoveConnection_Internal(const ConnectionPtr& pConn)
	{
		if (pConn == nullptr)
			return;

		RemoveMap(pConn);

		if (pConn->GetCID() != 0)
		{
			FreeCID((uint)pConn->GetCID());
			pConn->ClearCID(); // clear after free
		}

		// This is not true anymore, the connection can be removed anytime.
		// However, it will lost CID as it removed from connection manager
		//AssertRel(pConn->GetConnectionState() == ConnectionState::DISCONNECTED);
	}

	// Remap PeerID
	void ConnectionManager::RemapPeerID(SharedPointerT<Connection>& pConn, uint64_t ticket)
	{
		Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPostTick, [pConn, ticket, this]()
		{
			RemapPeerID_Internal(pConn, ticket);
		});
	}

	// Remap PeerID
	void ConnectionManager::RemapPeerID_Internal(const ConnectionPtr& pConn, uint64_t ticket )
	{
		Result hr = ResultCode::SUCCESS;
		Result hrTem = ResultCode::SUCCESS;
		SharedPointerT<Connection> pConnMapPtr;

		if( pConn->GetRemoteInfo().PeerID != 0 )
		{
			if ((m_PeerIDMap.Erase(pConn->GetRemoteInfo().PeerID, pConnMapPtr)))
			{
				//Assert(pConn == pConnMapPtr);
			}
		}

#ifdef DEBUG
		Assert(pConn->GetRemoteInfo().PeerID != 0xcdcdcdcdcdcdcdcd);
#endif

		pConn->SetRemoteID(ticket);

		if( ticket != 0 )
		{
			//m_PeerIDMap.erase( pConn );
			netChk(m_PeerIDMap.Insert(pConn->GetRemoteInfo().PeerID, SharedPointerT<Connection>(pConn)));
		}

		netChk( hr );
		netChk( hrTem );

	Proc_End:

		return;
	}


	Result ConnectionManager::RemoveMap(const ConnectionPtr& pConn)
	{
		Result hr = ResultCode::SUCCESS;
		Result hrTem = ResultCode::SUCCESS;
		SharedPointerT<Connection> pConnPtr;
		SharedPointerT<Connection> pPtr;

		if (pConn->GetCID() != 0)
		{
			if (pConn->GetUseAddressMap())
				hr = m_AddrMap.Erase(pConn->GetRemoteSockAddr(), pPtr);

			if (pConn->GetCID() != 0)
				hrTem = m_CIDMap.Erase(pConn->GetCID(), pConnPtr);
		}

		if (pConn->GetRemoteInfo().PeerID != 0)
			m_PeerIDMap.Erase(pConn->GetRemoteInfo().PeerID, pPtr);

		//netChk(hr);
		//netChk(hrTem);

	//Proc_End:

		return hr;
	}



	// Disconnect all connection
	Result ConnectionManager::DisconnectAllConnection()
	{
		// clear connection queue
		m_CIDMap.for_each([&](const uint64_t& key, SharedPointerT<Connection> pConn)-> bool
		{
			pConn->Disconnect("DisconnectAllConnection");
			return true;
		});

		return ResultCode::SUCCESS;
	}


	// Find and return connection
	Result ConnectionManager::GetConnectionByAddr(const sockaddr_storage& sockAddr, SharedPointerT<Connection> &pConn)
	{
		if((m_AddrMap.Find(sockAddr, pConn)))
		{
		}
		return pConn != nullptr ? ResultCode::SUCCESS : ResultCode::FAIL;
	}


	// Find and return connection
	Result ConnectionManager::GetConnectionByCID(uint64_t uiCID, SharedPointerT<Connection> &pConn)
	{
		return m_CIDMap.Find(uiCID, pConn);
	}
	
	// Find and return connection
	Result ConnectionManager::GetConnectionByPeerID(uint64_t peerID, SharedPointerT<Connection> &pConn)
	{
		if (peerID == 0)
			return ResultCode::FAIL;

		if ((m_PeerIDMap.Find(peerID, pConn)))
		{
			return ResultCode::SUCCESS;
		}

		return ResultCode::FAIL;
	}


} // namespace Net
} // namespace SF

