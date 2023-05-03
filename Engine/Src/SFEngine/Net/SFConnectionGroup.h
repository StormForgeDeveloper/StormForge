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
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFCircularPageQueue.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"



namespace SF {
namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection group
	//		Handle connection event for group of connection
	//

	class ConnectionGroup : public SharedObject, public IConnectionEventHandler
	{
	public:

		struct EventInformation
		{
			WeakPointerT<Connection> pConnection;
			std::atomic<uint64_t> Event;
			SharedPointerT<MessageData> pMsg;

			EventInformation();
			EventInformation(const EventInformation& src);
			EventInformation& operator = (const EventInformation& src);

			bool operator == (const EventInformation& src) const;
			bool operator != (const EventInformation& src) const;
		};

	private:

		CircularPageQueue<EventInformation> m_ConnectionEvents;

	public:

		ConnectionGroup(IHeap& memoryManager, int maximumQueueBufferSize);
		virtual ~ConnectionGroup();

		virtual void Dispose() override;

		virtual void OnConnectionEvent(Connection* pConn, const ConnectionEvent& evt) override;
		virtual Result OnRecvMessage(Connection* pConn, SharedPointerT<MessageData>& pMsg) override;
		virtual Result OnNetSyncMessage(Connection* pConn) override;
		// Net send message
		virtual Result OnNetSendReadyMessage(Connection* pConn)override;

		size_t GetQueuedEventCount();
		Result DequeueEvent(EventInformation& eventInfo);
	};


	typedef SharedPointerT <ConnectionGroup> ConnectionGroupPtr;

}  // namespace Net


	extern template class SharedPointerT <Net::ConnectionGroup>;
	extern template class WeakPointerT < Net::ConnectionGroup >;



}; // namespace SF



