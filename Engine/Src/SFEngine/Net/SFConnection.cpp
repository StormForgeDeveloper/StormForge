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
#include "Net/SFConnection.h"
#include "Net/SFConnectionTasks.h"


// define if emulate packet loss
//#ifdef _DEBUG
//#define UDP_PACKETLOS_EMULATE
//#endif


#ifdef UDP_PACKETLOS_EMULATE
	#define UDP_PACKETLOS_RATE	5
	#define UDP_PACKETLOS_BOUND	1
#endif // #ifdef UDP_PACKETLOS_EMULATE


namespace SF {

	template class SharedPointerT <Net::Connection>;
	template class WeakPointerT < Net::Connection >;

namespace Net {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network connection base class
	//


	Connection::Connection(IHeap& heap, SocketIO *ioHandler)
		: EngineObject(new(heap) IHeap("Connection", &heap),"Connection")
		, m_CID(0)
		, m_UData(0)
		, m_ConnectionState(ConnectionState::DISCONNECTED)
		, m_tConnectionTime(DurationMS(0))
		, m_pEventHandler(nullptr)
		, m_IOHandler(ioHandler)
		, m_RecvQueue(GetHeap())
		, m_EventQueue(GetHeap())
		, m_ulHeartbitTry(1000)
		, m_ulConnectingTimeOut(Const::CONNECTION_TIMEOUT)
		, m_usSeqNone(0)
		, m_ulZeroLengthRecvCount(0)
		, m_IsSocketOwner(false)
		, m_UseAddressMap(false)
		, m_UsePeerIDMap(false)
		, m_RunningThreadID(ThisThread::GetThreadID())
		, m_SendGuaQueue(GetHeap())
		, m_ulNetCtrlTime(DurationMS(0))
		, m_ulNetCtrlTryTime(DurationMS(0))
	{
		memset(m_NetCtrlAction, 0, sizeof(m_NetCtrlAction));

		// Initialize state tick action array
		m_ActionsByState = (StaticArray<ConnectionAction*, 32>*)m_Array2DBufferForConnectionAction;
		for (int iState = 0; iState < (int)ConnectionState::Max; iState++)
		{
			new((void*)&m_ActionsByState[iState]) ConnectionActionArray(GetHeap());
		}
	}

	Connection::~Connection()
	{
		SetTickFlags(0);

		// Not need with abstract class
		m_RecvQueue.ClearQueue();
		m_SendGuaQueue.ClearQueue();
		m_EventQueue.ClearQueue();

		// Release state tick action array
		if (m_ActionsByState != nullptr)
		{
			for (int iState = 0; iState < (int)ConnectionState::Max; iState++)
			{
				m_ActionsByState[iState].~ConnectionActionArray();
			}
			m_ActionsByState = nullptr;
		}

		// I created IHeap manually, so I need to check manually
		GetHeap().ReportLeak();
	}

	bool Connection::CanDelete()
	{
		if (!EngineObject::CanDelete())
			return false;

		return true;
	}

	void Connection::Dispose()
	{
		m_ConnectionState = ConnectionState::DISCONNECTED;
		// Not need with abstract class
		m_RecvQueue.ClearQueue();
		m_SendGuaQueue.ClearQueue();
		m_EventQueue.ClearQueue();

		EngineObject::Dispose();
	}

	void Connection::UpdateConnectionTime()
	{
		m_tConnectionTime = Util::Time.GetTimeMs();
	}

	IHeap& Connection::GetIOHeap()
	{
		return m_IOHandler != nullptr ? m_IOHandler->GetIOHeap() : Service::NetSystem->GetHeap();
	}


	Result Connection::ClearQueues()
	{
		m_RecvQueue.ClearQueue();
		m_SendGuaQueue.ClearQueue();

		// When the queue is cleared these synchronization variables need to be cleared
		m_usSeqNone = 0;
		return ResultCode::SUCCESS;
	}

	// Request time sync, round trip time will be recorded
	Result Connection::TimeSync()
	{
		auto reqTime = Util::Time.GetRawTimeMs();
		Message::MessageID msgID;
		msgID.ID = reqTime.time_since_epoch().count();
		return SendNetCtrl(PACKET_NETCTRL_TIMESYNC, 0, msgID, GetLocalInfo().PeerID);
	}


	void Connection::OnTimeSyncRtn(DurationMS roundTripTime)
	{
		m_RoundTripDelay = roundTripTime;
	}


	void Connection::OnHeartBitPacket()
	{
		m_ulNetCtrlTime = Util::Time.GetTimeMs();
	}

	Result Connection::ProcConnectionStateAction()
	{
		auto state = GetConnectionState();
		int iState = (int)state;
		if (iState < 0 || iState >= (int)ConnectionState::Max)
		{
			Assert(false);
			return ResultCode::SUCCESS;
		}


		auto& actionListForState = m_ActionsByState[(int)state];
		for (auto& itAction : actionListForState)
		{
			itAction->Run();
		}

		return ResultCode::SUCCESS;
	}

	// Make Ack packet and enqueue to SendNetCtrlqueue
	Result Connection::SendNetCtrl( uint uiCtrlCode, uint uiSequence, Message::MessageID returnMsgID, uint64_t UID )
	{
		Result hr = ResultCode::SUCCESS;
		Result hrTem;
		MsgNetCtrl *pAckMsg = nullptr;
		SharedPointerT<Message::MessageData> pMsg;

		if (uiCtrlCode == PACKET_NETCTRL_CONNECT || UID != 0)
		{
			netMem( pMsg = Message::MessageData::NewMessage(GetHeap(), uiCtrlCode, sizeof(MsgNetCtrlConnect) ) );
			MsgNetCtrlConnect *pConMsg = (MsgNetCtrlConnect*)pMsg->GetMessageBuff();
			pConMsg->Peer = GetLocalInfo();
		}
		else
		{
			netMem( pMsg = Message::MessageData::NewMessage(GetHeap(), uiCtrlCode, sizeof(MsgNetCtrl) ) );
		}

		pMsg->GetMessageHeader()->msgID.IDs.Mobile = false;

		pAckMsg = (MsgNetCtrl*)pMsg->GetMessageBuff();
		pAckMsg->msgID.SetSequence(uiSequence);
		pAckMsg->PeerID = UID;
		pAckMsg->rtnMsgID = returnMsgID;

		pMsg->UpdateChecksum();



		hrTem = SendRaw(pMsg);
		if( !(hrTem) )
		{
			SFLog(Net, Custom10, "NetCtrl Send failed : CID:{0}, msg:{1:X8}, seq:{2}, hr={3:X8}",
				GetCID(), 
				returnMsgID.ID,
				uiSequence, 
				hrTem );

			// ignore io send fail except connection closed
			if( hrTem == ((Result)ResultCode::IO_CONNECTION_CLOSED) )
			{
				goto Proc_End;
			}
		}

	Proc_End:

		return hr;
	}


	// Change remote Address
	void Connection::SetRemoteAddress(const sockaddr_storage& socAddr)
	{
		GetRemoteInfo().PeerAddress = socAddr;

		m_sockAddrRemote = socAddr;
	}


	// Message count currently in recv queue
	SysUInt Connection::GetRecvMessageCount()
	{
		return m_RecvQueue.size();
	}

	// Called on connection result
	void Connection::OnConnectionResult( Result hrConnect )
	{
		if( !(hrConnect) )
		{
			EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, hrConnect));

			SFLog(Net, Info, "Connection failed CID:{0}, Dst={1}, hr={2}", GetCID(), GetRemoteInfo().PeerAddress, hrConnect);
			if (GetConnectionState() != ConnectionState::DISCONNECTED)
			{
				CloseConnection("Connection failed");
			}
		}
		else
		{
			SFLog(Net, Info, "Connected CID:{0}, Dst={1}", GetCID(), GetRemoteInfo().PeerAddress );
			if (GetConnectionState() == ConnectionState::CONNECTING)
			{
				SetConnectionState(ConnectionState::CONNECTED);
				Assert(GetRemoteInfo().PeerClass != NetClass::Unknown);

				EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, hrConnect));
				EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_STATE_CHANGE, GetConnectionState()));
			}
			else
			{
				EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_CONNECTION_RESULT, hrConnect));
			}
		}
	}

	// Initialize packet synchronization
	Result Connection::InitSynchronization()
	{
		UpdateConnectionTime();

		m_usSeqNone = 0;

		m_RecvQueue.ClearQueue();

		return ResultCode::SUCCESS;
	}

	void Connection::SetNetCtrlAction(NetCtrlIDs id, ConnectionMessageAction* action)
	{
		action->SetConnection(this);
		m_NetCtrlAction[(int)id] = action;
	}

	void Connection::AddStateAction(ConnectionState state, ConnectionAction* action)
	{
		int iState = (int)state;
		if (iState < 0 || iState >= (int)ConnectionState::Max)
		{
			Assert(false);
			return;
		}

		auto& actionListForState = m_ActionsByState[(int)state];
		for (auto& itAction : actionListForState)
		{
			if (itAction == action) return; // if already exist
		}


		action->SetConnection(this);
		actionListForState.push_back(action);
	}


	// Initialize connection
	Result Connection::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		Result hr = ResultCode::SUCCESS;

		Assert(GetConnectionState() == ConnectionState::DISCONNECTED);
		// Except client everybody should have port number when it gets here
		Assert(remote.PeerClass == NetClass::Client || remote.PeerAddress.Port != 0);
		if (GetConnectionState() != ConnectionState::DISCONNECTED)
			netChk( CloseConnection("InitConnection failed: Invalid State") );

		// event handler need to be reassigned after initconnection is called
		// - No they should be kept, but it need to be tested
		SetEventHandler(nullptr);

		m_EventQueue.ClearQueue();

		Assert(local.PeerClass != NetClass::Unknown);
		Assert(local.PeerClass == NetClass::Client || local.PeerID != 0);
		m_LocalInfo = local;
		m_RemoteInfo = remote;

		SetConnectionState(ConnectionState::CONNECTING);

		netChk( InitSynchronization() );

		m_ulZeroLengthRecvCount = 0;

		//SetSocket(socket, takeOverSocket);

		SetSockAddr(m_sockAddrRemote, m_RemoteInfo.PeerAddress.Address, m_RemoteInfo.PeerAddress.Port);

		m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
		m_ulNetCtrlTime = Util::Time.GetTimeMs();

		EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_STATE_CHANGE, GetConnectionState()));

	Proc_End:

		SFLog(Net, Info, "InitConnection CID:{0}, from:{1}, to:{2} hr:{3}", GetCID(), local.PeerAddress, remote.PeerAddress, hr);

		return hr;
	}

	// Disconnect connection
	Result Connection::Disconnect(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;

		if( GetConnectionState() != ConnectionState::DISCONNECTING
			&& GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			if (reason == nullptr)
				reason = "Unknown";

			auto previsouState = GetConnectionState();

			SetConnectionState(ConnectionState::DISCONNECTING);

			if (previsouState == ConnectionState::CONNECTING)
			{
				OnConnectionResult(ResultCode::IO_DISCONNECTED);
			}

			EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_STATE_CHANGE, GetConnectionState()));

			SFLog(Net, Info, "Entering Disconnect CID:{0}, sock:{1}, reason:{2}", GetCID(), GetSocket(), reason );
		}

	//Proc_End:

		return hr;
	}


	// Close connection
	Result Connection::CloseConnection(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;
		auto orgState = GetConnectionState();

		if (orgState == ConnectionState::DISCONNECTED)
			goto Proc_End;

		SetConnectionState(ConnectionState::DISCONNECTED);

		if (orgState == ConnectionState::CONNECTING)
		{
			OnConnectionResult(ResultCode::IO_DISCONNECTED);
		}

		m_ulNetCtrlTime = m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
		UpdateConnectionTime();

		SFLog(Net, Info, "Connection Closed CID:{0}, sock:{1}, Addr:{2}, reason:{3}", GetCID(), GetSocket(), GetRemoteInfo().PeerAddress, reason);

		EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_DISCONNECTED, GetConnectionState()));

	Proc_End:

		return hr;
	}


	void Connection::DisconnectNRelease(const char* reason)
	{
		SetTickFlags(0);
		// This guy should not belong to connection heap
		SharedPointerT<EngineTask> pTask = new(GetSystemHeap()) ConnectionTask_DisconnectNClose(this, reason);
		pTask->Request();
	}


	Result Connection::OnRecv( SharedPointerT<Message::MessageData>& pMsg )
	{
		Result hr = ResultCode::SUCCESS;
	
		if (pMsg == nullptr)
			return hr;

		auto msgID = pMsg->GetMessageHeader()->msgID;

		// All messages must be decrypted before came here
		Assert(!msgID.IDs.Encrypted);


		// 
		Protocol::PrintDebugMessage( "Recv", pMsg );

		//Assert( MemoryPool::CheckMemoryHeader( *pMsg ) );
		Assert(pMsg->GetDataLength() == 0 || pMsg->GetMessageHeader()->Crc32 != 0);

		if (GetEventHandler() == nullptr )
		{
			netChk(GetRecvQueue().Enqueue(pMsg));
		}
		else if (!(GetEventHandler()->OnRecvMessage(this, pMsg)))
		{
			SFLog(Net, Error, "Failed to route a message to recv msg:{0}", msgID);
			if (pMsg != nullptr)
			{
				netChk(GetRecvQueue().Enqueue(std::forward<SharedPointerT<Message::MessageData>>(pMsg)));
			}
		}

		pMsg = nullptr;


	Proc_End:

		Assert(!(hr) || pMsg == nullptr);

		return hr;
	}


	// Query connection event
	Result Connection::DequeueConnectionEvent( ConnectionEvent& curEvent )
	{
		return m_EventQueue.Dequeue(curEvent.Composited);
	}

	// Add network event to queue
	Result Connection::EnqueueConnectionEvent(const ConnectionEvent &evt)
	{
		if (GetEventHandler())
		{
			GetEventHandler()->OnConnectionEvent(this, evt);
		}
		else
		{
			return m_EventQueue.Enqueue(evt.Composited);
		}

		return ResultCode::SUCCESS;
	}


	// Get received Message
	Result Connection::GetRecvMessage( SharedPointerT<Message::MessageData> &pIMsg )
	{
		Result hr = ResultCode::SUCCESS;

		pIMsg = nullptr;

		if( !(GetRecvQueue().Dequeue( pIMsg )) )
		{
			hr = ResultCode::FAIL;
			goto Proc_End;
		}

		{
			Message::MessageHeader* pMsgHeader = pIMsg->GetMessageHeader();
			uint uiPolicy = pMsgHeader->msgID.IDs.Policy;
			if (uiPolicy == 0
				|| uiPolicy >= PROTOCOLID_NETMAX) // invalid policy
			{
				netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}
		}

	Proc_End:

		return hr;
	}

	// Update net ctrl time
	void Connection::UpdateNetCtrlTime()
	{
		m_ulNetCtrlTime = m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
	}

	void Connection::UpdateNetCtrlTryTime()
	{
		m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
	}


	Result Connection::OnTick(EngineTaskTick tick)
	{
		SetRunningThreadID(ThisThread::GetThreadID());

		return TickUpdate();
	}

	
} // namespace Net
} // namespace SF


