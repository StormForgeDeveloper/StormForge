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
#include "String/SFToStringEngineTypes.h"
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
		, m_RecvQueue(GetHeap())
		, m_EventQueue(GetHeap())
		, m_Players(GetHeap())
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
		m_RecvQueue.ClearQueue();

		EngineObject::Dispose();
	}

	Result RelayNetwork::Connect(const NetAddress& relayServerAddr, uint32_t relayInstanceID, PlayerID myPlayerID)
	{
		FunctionContext hr([this](Result result)
		{
			if (GetRelayNetworkState() == RelayNetworkState::Connecting)
				m_RelayNetworkState = RelayNetworkState::Disconnected;
		});

		if (GetRelayNetworkState() != RelayNetworkState::Initialized
			&& GetRelayNetworkState() != RelayNetworkState::Disconnected)
			return hr = ResultCode::INVALID_STATE;

		m_RelayNetworkState = RelayNetworkState::Connecting;
		m_RelayInstanceID = relayInstanceID;
		m_PlayerID = myPlayerID;

		MessageDataPtr pMessage = Message::Relay::JoinRelayInstanceC2SEvt::Create(m_RawUDP.GetHeap(), GetRelayInstanceID(), GetLocalPlayerID(), "TempUser");
		if (pMessage == nullptr)
			return hr = ResultCode::OUT_OF_MEMORY;

		return hr = m_RawUDP.SendMsg(m_RelaySockAddr, pMessage);
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

		if (msgID.GetMsgID() == Message::Relay::JoinRelayInstanceResS2CEvt::MID)
		{
			OnJoinRelayInstanceResS2CEvt(std::forward<MessageDataPtr>(pMsg));
		}
		else if(msgID.GetMsgID() == Message::Relay::PlayerJoinS2CEvt::MID)
		{
			OnPlayerJoinS2CEvt(std::forward<MessageDataPtr>(pMsg));
		}
		else if (msgID.GetMsgID() == Message::Relay::PlayerLeftS2CEvt::MID)
		{
			OnPlayerLeftS2CEvt(std::forward<MessageDataPtr>(pMsg));
		}
		else if (msgID.GetMsgID() == Message::Relay::RelayPacketC2SEvt::MID)
		{
			OnPlayerLeftS2CEvt(std::forward<MessageDataPtr>(pMsg));
		}
		else
		{
			//netCheck(m_RecvQueue.Enqueue(std::forward<SharedPointerT<Message::MessageData>>(pMsg)));
			SFLog(Net, Error, "RelayNetwork Unknown message for Instance:{0}", GetRelayInstanceID());
		}

		return hr;
	}

	Result RelayNetwork::OnJoinRelayInstanceResS2CEvt(MessageDataPtr&& pMsg)
	{
		FunctionContext hr;
		if (GetRelayNetworkState() != RelayNetworkState::Connecting)
			return hr;

		Message::Relay::JoinRelayInstanceResS2CEvt message(std::forward<MessageDataPtr>(pMsg));
		netCheck(message.ParseMsg());

		m_PlayerEndpointID = message.GetMyEndpointID();

		m_Players.Clear();

		if (message.GetResult())
		{
			MutexScopeLock lockScope(m_NetLock);
			for (auto& itOtherPlayerInfo : message.GetMemberInfos())
			{
				m_Players.push_back(itOtherPlayerInfo);
			}

			SetRelayNetworkState(RelayNetworkState::Connected);

			SFLog(Net, Info, "RelayNetwork connected, InstanceID:{0}", GetRelayInstanceID());
		}
		else
		{
			SFLog(Net, Error, "RelayNetwork failed to join InstanceID:{0}, result:{1}", GetRelayInstanceID(), message.GetResult());
		}

		EnqueueRelayNetworkEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, message.GetResult()));

		return hr;
	}

	Result RelayNetwork::OnPlayerJoinS2CEvt(MessageDataPtr&& pMsg)
	{
		FunctionContext hr;
		if (GetRelayNetworkState() != RelayNetworkState::Connecting)
			return hr;

		Message::Relay::PlayerJoinS2CEvt message(std::forward<MessageDataPtr>(pMsg));
		netCheck(message.ParseMsg());

		auto& joinedPlayerInfo = message.GetJoinedPlayerInfo();
		MutexScopeLock lockScope(m_NetLock);
		for (auto& itPlayer : m_Players)
		{
			// skip if we alread has the endpoint
			if(itPlayer == joinedPlayerInfo)
				return hr;
		}

		SFLog(Net, Info, "RelayNetwork Player joined, InstanceID:{0}, Player:{1}", GetRelayInstanceID(), joinedPlayerInfo);
		m_Players.push_back(message.GetJoinedPlayerInfo());
		//message.GetRelayInstanceID();
		//message.GetJoinedPlayerInfo();

		return hr;
	}

	Result RelayNetwork::OnPlayerLeftS2CEvt(MessageDataPtr&& pMsg)
	{
		FunctionContext hr;
		if (GetRelayNetworkState() != RelayNetworkState::Connecting)
			return hr;

		Message::Relay::PlayerLeftS2CEvt message(std::forward<MessageDataPtr>(pMsg));
		netCheck(message.ParseMsg());

		auto& leftPlayerID = message.GetLeftPlayerID();

		MutexScopeLock lockScope(m_NetLock);
		for (uint32_t iPlayer = 0; iPlayer < m_Players.size(); iPlayer++)
		{
			// skip if we already has the endpoint
			if (m_Players[iPlayer].RelayPlayerID == leftPlayerID)
			{
				m_Players.RemoveAt(iPlayer);
				SFLog(Net, Info, "RelayNetwork Player left, InstanceID:{0}, Player:{1}", GetRelayInstanceID(), leftPlayerID);
				break;
			}
		}

		return hr;
	}

	Result RelayNetwork::OnRelayPacketC2SEvt(MessageDataPtr&& pMsg)
	{
		FunctionContext hr;
		if (GetRelayNetworkState() != RelayNetworkState::Connecting)
			return hr;

		return m_RecvQueue.Enqueue(std::forward<MessageDataPtr>(pMsg));
		//Message::Relay::RelayPacketC2SEvt message(std::forward<MessageDataPtr>(pMsg));
		//netCheck(message.ParseMsg());

		//m_RecvHandler(message.GetSenderEndpointID(), message.GetPayload().size(), message.GetPayload().data());

		//return hr;
	}

	size_t RelayNetwork::GetRelayNetworkEventCount()
	{
		return m_EventQueue.size();
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

	// Send message to connected entity
	Result RelayNetwork::Send(uint32_t targetEndpointMask, size_t payloadSize, const void* payloadData)
	{
		FunctionContext hr;

		MessageDataPtr pMessage = Message::Relay::RelayPacketC2SEvt::Create(m_RawUDP.GetHeap(), 
			GetRelayInstanceID(), 
			GetLocalEndpointID(), 
			targetEndpointMask, 
			ExternalBufferArray(payloadSize, static_cast<const uint8_t*>(payloadData))
		);
		if (pMessage == nullptr)
			return hr = ResultCode::OUT_OF_MEMORY;

		return m_RawUDP.SendMsg(m_RelaySockAddr, pMessage);
	}


	// Message count currently in recv queue
	size_t RelayNetwork::GetRecvMessageCount()
	{
		return m_RecvQueue.size();
	}

	Result RelayNetwork::GetFrontRecvMessage(SharedPointerT<Message::MessageData> &pIMsg)
	{
		return m_RecvQueue.GetFront(pIMsg);
	}

	// Get received Message
	Result RelayNetwork::GetRecvMessage(SharedPointerT<Message::MessageData> &pIMsg)
	{
		return m_RecvQueue.Dequeue(pIMsg);
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


