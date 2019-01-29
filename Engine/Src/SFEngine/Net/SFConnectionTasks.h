////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net connection classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFConnection.h"
#include "EngineObject/SFEngineTask.h"


namespace SF {
namespace Net {

	class ConnectionTask : public EngineTask
	{
	private:
		WeakPointerT<Connection> m_pConnection;

	public:

		ConnectionTask(WeakPointerT<Connection>&& pConnection, EngineTaskTick tick = EngineTaskTick::SyncPreTick);

		WeakPointerT<Connection>& GetConnection() { return m_pConnection; }
	};


	class ConnectionTask_DisconnectNClose : public EngineTask
	{
	private:
		const char* m_Reason = nullptr;
		SharedPointerT<Connection> m_pConnection;
		TimeStampMS m_EnqueuedTime;
		EngineTaskPtr m_RemoveConnectionManagerTask;
		bool m_RemovedFromConnectionManagerRequested = false;

	public:
		ConnectionTask_DisconnectNClose(Connection* pConnection, const char* reason);
		~ConnectionTask_DisconnectNClose();

		virtual void Run() override;
	};


}  // namespace Net

	//extern template class SharedPointerT <Net::Connection>;
	//extern template class WeakPointerT < Net::Connection >;

	//template<> inline SharedPointerT<Net::Connection> DefaultValue<SharedPointerT<Net::Connection>>() { return SharedPointerT<Net::Connection>(); }
	//template<> inline WeakPointerT<Net::Connection> DefaultValue<WeakPointerT<Net::Connection>>() { return WeakPointerT<Net::Connection>(); }


}; // namespace SF



