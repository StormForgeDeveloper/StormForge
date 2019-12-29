////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 KyungKun Ko
// 
// Author : KyungKun Ko
//
// Description : Network relay RelayNetwork
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Thread/SFThread.h"

#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "String/SFToString.h"
#include "Service/SFEngineService.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetToString.h"
#include "Net/SFNetRelayNetwork.h"

#include "Protocol/Message/RelayMsgClass.h"



namespace SF {

	template class SharedPointerT <Net::RelayNetwork>;
	template class WeakPointerT < Net::RelayNetwork >;

namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network RelayNetwork base class
	//


	RelayNetwork::RelayNetwork(IHeap& heap)
		: EngineObject(new(heap) IHeap("RelayNetwork", &heap),"RelayNetwork")
		, m_RelayNetworkState(RelayNetworkState::Disconnected)
		, m_RawUDP(GetHeap())
		, m_EventQueue(GetHeap())
		, m_RecvQueue(GetHeap())
	{
	}

	RelayNetwork::~RelayNetwork()
	{
		assert(m_RawUDP.CanDelete());
	}

	bool RelayNetwork::CanDelete()
	{
		if (!EngineObject::CanDelete())
			return false;

		return m_RawUDP.CanDelete();
	}

	void RelayNetwork::Dispose()
	{
		if(m_RelayNetworkState != RelayNetworkState::Disconnected && m_RelayNetworkState != RelayNetworkState::None)
			m_RawUDP.TerminateNet();

		m_RelayNetworkState = RelayNetworkState::Disconnected;

		EngineObject::Dispose();
	}

	// Message count currently in recv queue
	SysUInt RelayNetwork::GetRecvMessageCount()
	{
		return m_RecvQueue.size();
	}

	// Called on RelayNetwork result
	void RelayNetwork::OnRelayNetworkResult( Result hrConnect )
	{
		if( !hrConnect )
		{
			EnqueueRelayNetworkEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, hrConnect));

			SFLog(Net, Info, "RelayNetwork failed Dst={0}:{1}, hr={2}", m_RelaySockAddr, m_RelayInstanceID, hrConnect);
			if (GetRelayNetworkState() != RelayNetworkState::Disconnected)
			{
				m_RawUDP.TerminateNet();
			}
		}
		else
		{
			SFLog(Net, Info, "Connected Dst={0}:{1}", m_RelaySockAddr, m_RelayInstanceID);
			if (GetRelayNetworkState() == RelayNetworkState::Connecting)
			{
				SetRelayNetworkState(RelayNetworkState::Connected);

				EnqueueRelayNetworkEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, hrConnect));
			}
			else
			{
				EnqueueRelayNetworkEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, hrConnect));
			}
		}
	}

	// Disconnect RelayNetwork
	Result RelayNetwork::Disconnect(const char* reason)
	{
		FunctionContext hr;

		if( GetRelayNetworkState() != RelayNetworkState::Disconnected)
		{
			if (reason == nullptr)
				reason = "Unknown";

			auto previsouState = GetRelayNetworkState();

			SetRelayNetworkState(RelayNetworkState::Disconnecting);

			if (previsouState == RelayNetworkState::Connecting)
			{
				OnRelayNetworkResult(ResultCode::IO_CANCELED);
			}


			// Sending quit message, this can arrive or not, but server will time out the client anyway
			MessageDataPtr pMessage = Message::Relay::LeaveRelayInstanceC2SEvt::Create(m_RawUDP.GetHeap(), GetRelayInstanceID(), GetLocalPlayerID());
			if (pMessage == nullptr)
				return hr = ResultCode::OUT_OF_MEMORY;

			m_RawUDP.SendMsg(m_RelaySockAddr, pMessage);

			EnqueueRelayNetworkEvent(ConnectionEvent(ConnectionEvent::EVT_DISCONNECTED, ResultCode::IO_DISCONNECTED));

			SFLog(Net, Info, "Entering Disconnect :{0}:{1}, {2}", m_RelaySockAddr, m_RelayInstanceID, reason);
		}

		return hr;
	}


	// Close RelayNetwork
	Result RelayNetwork::CloseConnection(const char* reason)
	{
		FunctionContext hr;
		auto orgState = GetRelayNetworkState();

		if (orgState == RelayNetworkState::Disconnected)
			return hr;

		SetRelayNetworkState(RelayNetworkState::Disconnected);

		if (orgState == RelayNetworkState::Connecting)
		{
			OnRelayNetworkResult(ResultCode::IO_DISCONNECTED);
		}

		m_RawUDP.TerminateNet();

		SFLog(Net, Info, "RelayNetwork Closed ID:{0}, reason:{1}", GetRelayInstanceID(), reason);

		EnqueueRelayNetworkEvent(ConnectionEvent(ConnectionEvent::EVT_DISCONNECTED, ConnectionState::DISCONNECTED));

		return hr;
	}

	//void RelayNetwork::DisconnectNRelease(const char* reason)
	//{
	//	SetTickFlags(0);
	//	// This guy should not belong to RelayNetwork heap
	//	SharedPointerT<EngineTask> pTask = new(GetSystemHeap()) RelayNetworkTask_DisconnectNClose(this, reason);
	//	pTask->Request();
	//}


	Result RelayNetwork::OnRecv(const sockaddr_storage& remoteAddr, SharedPointerT<Message::MessageData>& pMsg)
	{
		FunctionContext hr;
	
		if (pMsg == nullptr)
			return hr;

		auto msgID = pMsg->GetMessageHeader()->msgID;

		// All messages must be decrypted before came here
		Assert(!msgID.IDs.Encrypted);

		// 
		Protocol::PrintDebugMessage( "Recv", pMsg );

		Assert(pMsg->GetDataLength() == 0 || pMsg->GetMessageHeader()->Crc32 != 0);

		netCheck(m_RecvQueue.Enqueue(std::forward<SharedPointerT<Message::MessageData>>(pMsg)));

		pMsg = nullptr;

		return hr;
	}


	// Query RelayNetwork event
	Result RelayNetwork::DequeueRelayNetworkEvent( ConnectionEvent& curEvent )
	{
		return m_EventQueue.Dequeue(curEvent.Composited);
	}

	// Add network event to queue
	Result RelayNetwork::EnqueueRelayNetworkEvent(const ConnectionEvent &evt)
	{
		return m_EventQueue.Enqueue(evt.Composited);
	}


	// Get received Message
	Result RelayNetwork::GetRecvMessage( SharedPointerT<Message::MessageData> &pIMsg )
	{
		FunctionContext hr;

		pIMsg = nullptr;

		if( !m_RecvQueue.Dequeue( pIMsg ) )
			return hr = ResultCode::FAIL;

		Message::MessageHeader* pMsgHeader = pIMsg->GetMessageHeader();
		uint uiPolicy = pMsgHeader->msgID.IDs.Policy;
		if (uiPolicy == 0
			|| uiPolicy >= PROTOCOLID_NETMAX) // invalid policy
		{
			return hr = ResultCode::IO_BADPACKET_NOTEXPECTED;
		}

		return hr;
	}


	Result RelayNetwork::OnTick(EngineTaskTick tick)
	{
		//SetRunningThreadID(ThisThread::GetThreadID());

		if (GetRelayNetworkState() == RelayNetworkState::Disconnecting)
			CloseConnection("Disconnecting");

		super::OnTick(tick);

		return ResultCode::SUCCESS;
	}

	
} // namespace Net
} // namespace SF


