////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Connection action
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Multithread/SFThread.h"
#include "Util/SFUtility.h"


#include "Net/SFConnection.h"
#include "Net/SFConnectionMUDP.h"
#include "Net/SFConnectionAction.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"




namespace SF {
namespace Net {




	ConnectionActionBase::ConnectionActionBase()
		: m_pConnection(nullptr)
	{
	}

	ConnectionActionBase::~ConnectionActionBase()
	{
	}


	// Get Connection info
	const PeerInfo& ConnectionActionBase::GetLocalInfo() const { return m_pConnection->GetLocalInfo(); }
	const PeerInfo& ConnectionActionBase::GetRemoteInfo() const { return m_pConnection->GetRemoteInfo(); }

	// Get Connection ID
	uint64_t ConnectionActionBase::GetCID() const { return m_pConnection->GetCID(); }

	// Get connection state
	const ConnectionState ConnectionActionBase::GetConnectionState() const { return m_pConnection->GetConnectionState(); }


	Result ConnectionActionBase::SendNetCtrl(uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID)
	{
		return m_pConnection->SendNetCtrl(uiCtrlCode, uiSequence, msgID, UID);
	}

	Result ConnectionActionBase::Disconnect(const char* reason)
	{
		return m_pConnection->Disconnect(reason);
	}

	Result ConnectionActionBase::CloseConnection(const char* reason)
	{
		return m_pConnection->CloseConnection(reason);
	}




	void ConnectionMessageAction::OnConnectionResult(Result hrConnect)
	{
		GetConnection()->OnConnectionResult(hrConnect);
	}


	TimeStampMS ConnectionActionBase::GetNetCtrlTime() { return GetConnection()->GetNetCtrlTime(); }
	TimeStampMS ConnectionActionBase::GetNetCtrlTryTime() { return GetConnection()->GetNetCtrlTryTime(); }
	void ConnectionActionBase::UpdateNetCtrlTryTime() { GetConnection()->UpdateNetCtrlTryTime(); }

	IConnectionEventHandler* ConnectionActionBase::GetEventHandler()
	{
		return m_pConnection->GetEventHandler();
	}

	ConnectionUDPBase* ConnectionActionUDP::GetConnection()
	{
		return static_cast<ConnectionUDPBase*>(ConnectionActionBase::GetConnection());
	}

	ConnectionMUDP* ConnectionActionMUDP::GetConnection()
	{
		return static_cast<ConnectionMUDP*>(ConnectionActionBase::GetConnection());
	}


	ConnectionMUDP* ConnectionMessageActionMUDP::GetConnection()
	{
		return static_cast<ConnectionMUDP*>(ConnectionActionBase::GetConnection());
	}



} // namespace Net
} // namespace SF


