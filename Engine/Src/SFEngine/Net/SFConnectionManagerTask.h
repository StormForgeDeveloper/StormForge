////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net Connection manager task
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "EngineObject/SFEngineTask.h"
#include "Object/SFSharedObject.h"
#include "Memory/SFMemoryPool.h"
#include "Service/SFEngineService.h"


namespace SF {
namespace Net {

	class ConnectionManager;

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection manager task base
	//

	class ConnectionManagerTask : public EngineTask
	{
	private:


	public:
		// Connection task
		ConnectionManagerTask(EngineTaskTick tick = EngineTaskTick::SyncPreTick);
		~ConnectionManagerTask();

		// Get connection manager
		ConnectionManagerService* GetConnectionManager();

		// Run the task
		//virtual void Run() override;
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Connection manager tasks
	//



	class ConnectionManagerTask_RemapAddress : public ConnectionManagerTask
	{
	private:
		WeakPointerT<Connection> m_Connection;
		sockaddr_storage m_OrgAddress;
		sockaddr_storage m_NewAddress;
	public:
		ConnectionManagerTask_RemapAddress(WeakPointerT<Connection>&& connection, const sockaddr_storage& orgAddress, const sockaddr_storage& newAddress);
		virtual void Run() override;
	};


	class ConnectionManagerTask_RemapPeerID : public ConnectionManagerTask
	{
	private:
		WeakPointerT<Connection> m_Connection;
		uint64_t m_PeerID;
	public:
		ConnectionManagerTask_RemapPeerID(WeakPointerT<Connection>&& connection, uint64_t peerID);
		virtual void Run() override;
	};



} // namespace Net

	extern template class SharedPointerT<Net::ConnectionManagerTask>;
	extern template class WeakPointerT<Net::ConnectionManagerTask>;


} // namespace SF



