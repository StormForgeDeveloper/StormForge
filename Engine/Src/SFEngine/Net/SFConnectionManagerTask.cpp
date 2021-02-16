////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Network connection task
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "SFEngine.h"
#include "Multithread/SFThread.h"
#include "Protocol/SFProtocol.h"
#include "Service/SFEngineService.h"
#include "String/SFToString.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"

#include "Net/SFNetConst.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionManagerTask.h"
#include "Net/SFConnectionManager.h"
#include "Net/SFNetToString.h"





namespace SF {

	template class SharedPointerT<Net::ConnectionManagerTask>;
	template class WeakPointerT<Net::ConnectionManagerTask>;

namespace Net {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection TickTask
	//

	// Connection task
	ConnectionManagerTask::ConnectionManagerTask(EngineTaskTick tick)
		: EngineTask(tick)
	{
	}

	ConnectionManagerTask::~ConnectionManagerTask()
	{
	}

	// Get connection manager
	ConnectionManagerService* ConnectionManagerTask::GetConnectionManager()
	{
		return *Service::ConnectionManager;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection manager tasks
	//



	ConnectionManagerTask_RemapAddress::ConnectionManagerTask_RemapAddress(WeakPointerT<Connection>&& connection, const sockaddr_storage& orgAddress, const sockaddr_storage& newAddress)
		: m_Connection(std::forward<WeakPointerT<Connection>>(connection))
		, m_OrgAddress(orgAddress)
		, m_NewAddress(newAddress)
	{
	}

	void ConnectionManagerTask_RemapAddress::Run()
	{
		auto pConnectionManager = GetConnectionManager();
		if (pConnectionManager == nullptr)
			return;

		SharedPointerT<Connection> connectionPtr = m_Connection;
		if (connectionPtr == nullptr)
			return;

		pConnectionManager->AddressRemap(connectionPtr, m_OrgAddress, m_NewAddress);
		Finished();
	}


	ConnectionManagerTask_RemapPeerID::ConnectionManagerTask_RemapPeerID(WeakPointerT<Connection>&& connection, uint64_t peerID)
		: m_Connection(std::forward<WeakPointerT<Connection>>(connection))
		, m_PeerID(peerID)
	{
	}

	void ConnectionManagerTask_RemapPeerID::Run()
	{
		auto pConnectionManager = GetConnectionManager();
		if (pConnectionManager == nullptr)
			return;

		SharedPointerT<Connection> connectionPtr = m_Connection;
		if (connectionPtr == nullptr)
			return;

		pConnectionManager->RemapPeerID(connectionPtr, m_PeerID);
		Finished();
	}


	


} // namespace Net
} // namespace SF

