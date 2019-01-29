////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Connection implementation
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "ResultCode/SFResultCodeEngine.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionGroup.h"
#include "Util/SFLog.h"
#include "Net/SFConnection.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetCtrl.h"
#include "Util/SFTimeUtil.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "Protocol/SFProtocol.h"
#include "String/SFToString.h"
#include "Net/SFNetToString.h"




namespace SF {

	template class SharedPointerT <Net::ConnectionGroup>;
	template class WeakPointerT < Net::ConnectionGroup >;

namespace Net {


	ConnectionGroup::EventInformation::EventInformation()
		: Event(0)
	{

	}

	ConnectionGroup::EventInformation::EventInformation(const EventInformation& src)
		: pConnection(src.pConnection)
		, Event(src.Event.load(std::memory_order_acquire))
		, pMsg(src.pMsg)
	{

	}

	ConnectionGroup::EventInformation& ConnectionGroup::EventInformation::operator = (const EventInformation& src)
	{
		pConnection = src.pConnection;
		Event = src.Event.load(std::memory_order_acquire);
		pMsg = src.pMsg;
		return *this;
	}

	bool ConnectionGroup::EventInformation::operator == (const EventInformation& src) const
	{
		return pConnection == src.pConnection && Event == src.Event && pMsg == src.pMsg;
	}

	bool ConnectionGroup::EventInformation::operator != (const EventInformation& src) const
	{
		return pConnection != src.pConnection || Event != src.Event || pMsg != src.pMsg;
	}



	ConnectionGroup::ConnectionGroup(IHeap& memoryManager, int maximumQueueBufferSize)
		: m_ConnectionEvents(memoryManager, 256, maximumQueueBufferSize / 256)
	{
	}

	ConnectionGroup::~ConnectionGroup()
	{
	}

	void ConnectionGroup::Dispose()
	{
		m_ConnectionEvents.ClearQueue();
	}

	void ConnectionGroup::OnConnectionEvent(Connection* pConn, const ConnectionEvent& evt)
	{
		EventInformation eventInfo;
		eventInfo.pConnection = WeakPointerT<Connection>(pConn);
		eventInfo.Event = evt.Composited;

		m_ConnectionEvents.Enqueue(std::forward<EventInformation>(eventInfo));
	}

	Result ConnectionGroup::OnRecvMessage(Connection* pConn, SharedPointerT<Message::MessageData>& pMsg)
	{
		EventInformation eventInfo;
		eventInfo.pConnection = WeakPointerT<Connection>(pConn);
		eventInfo.pMsg = std::forward<MessageDataPtr>(pMsg);

		return m_ConnectionEvents.Enqueue(std::forward<EventInformation>(eventInfo));
	}

	Result ConnectionGroup::OnNetSyncMessage(Connection* pConn)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}

	// Net send message
	Result ConnectionGroup::OnNetSendReadyMessage(Connection* pConn)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}



	size_t ConnectionGroup::GetQueuedEventCount()
	{
		return (size_t)m_ConnectionEvents.size();
	}

	Result ConnectionGroup::DequeueEvent(EventInformation& eventInfo)
	{
		return m_ConnectionEvents.Dequeue(eventInfo);
	}

	
} // namespace Net
} // namespace SF


