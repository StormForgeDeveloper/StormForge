////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Multithread/SFThread.h"

#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFToString.h"
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
		//	MessageEndpoint adapter
		//


		bool MessageEndpointConnection::IsSameEndpoint(const EndpointAddress& messageEndpoint)
		{
			auto pConnection = m_pConnection.AsSharedPtr<Connection>();

			if (pConnection == nullptr)
				return messageEndpoint.MessageServer.IsNullOrEmpty();

			auto& netAddress = pConnection->GetRemoteInfo().PeerAddress;
			char portString[64];
			StrUtil::Format(portString, "{0}", netAddress.Port);
			return messageEndpoint.Channel == portString && messageEndpoint.MessageServer == netAddress.Address;
		}

		Result MessageEndpointConnection::Send(const SharedPointerT<Message::MessageData>& messageData)
		{
			auto pConnection = m_pConnection.AsSharedPtr<Connection>();
			if (pConnection != nullptr)
			{
				return pConnection->Send(messageData);
			}

			return ResultCode::INVALID_STATE;
		}



		////////////////////////////////////////////////////////////////////////////////
		//
		//	Network connection base class
		//


		Connection::Connection(IHeap& heap, SocketIO* ioHandler)
			: EngineObject(new(heap) IHeap("Connection", &heap), "Connection")
			, m_CID(0)
			, m_UData(0)
			, m_ConnectionState(ConnectionState::DISCONNECTED)
			, m_tConnectionTime(DurationMS(0))
			, m_pEventHandler(nullptr)
			, m_ConnectionEventDelegates(GetHeap())
			, m_RecvMessageDelegates(GetHeap())
			, m_NetSyncMessageDelegates(GetHeap())
			, m_RecvMessageDelegatesByMsgId(GetHeap())
			, m_IOHandler(ioHandler)
			, m_RecvQueue(GetHeap())
			, m_EventQueue(GetHeap())
			, m_ulHeartbeatTry(1000)
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
			// Initialize state tick action array
			m_ActionsByState = (StaticArray<ConnectionAction*, 32>*)m_Array2DBufferForConnectionAction;
			for (int iState = 0; iState < (int)ConnectionState::Max; iState++)
			{
				new((void*)&m_ActionsByState[iState]) ConnectionActionArray(GetHeap());
			}
		}

		Connection::~Connection()
		{
			SetTickGroup(EngineTaskTick::None);

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

			m_RecvMessageDelegatesByMsgId.CommitChanges();
			m_RecvMessageDelegatesByMsgId.ForeachOrder(0, m_RecvMessageDelegatesByMsgId.size(), [](uint32_t, RecvMessageDelegates* pDelegate)
				{
					IHeap::Delete(pDelegate);
					return true;
				});
			m_RecvMessageDelegatesByMsgId.clear();

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

			EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_TIMESYNC_RESULT, ResultCode::SUCCESS));
		}

		void Connection::OnHeartbeatPacket()
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
		Result Connection::SendNetCtrl(uint uiCtrlCode, uint uiSequence, Message::MessageID returnMsgID, uint64_t UID)
		{
			Result hr = ResultCode::SUCCESS;
			Result hrTem;
			MsgNetCtrl* pAckMsg = nullptr;
			SharedPointerT<Message::MessageData> pMsg;

			if (uiCtrlCode == PACKET_NETCTRL_CONNECT || UID != 0)
			{
				netCheckMem(pMsg = Message::MessageData::NewMessage(GetHeap(), uiCtrlCode, sizeof(MsgNetCtrlConnect)));
				MsgNetCtrlConnect* pConMsg = (MsgNetCtrlConnect*)pMsg->GetMessageBuff();
				pConMsg->Peer = GetLocalInfo();
			}
			else
			{
				netCheckMem(pMsg = Message::MessageData::NewMessage(GetHeap(), uiCtrlCode, sizeof(MsgNetCtrl)));
			}

			pMsg->GetMessageHeader()->msgID.IDs.Mobile = false;

			pAckMsg = (MsgNetCtrl*)pMsg->GetMessageBuff();
			pAckMsg->msgID.SetSequence(uiSequence);
			pAckMsg->PeerID = UID;
			pAckMsg->rtnMsgID = returnMsgID;

			pMsg->UpdateChecksum();

			hrTem = SendRaw(pMsg);
			if (!hrTem)
			{
				SFLog(Net, Custom10, "NetCtrl Send failed : CID:{0}, msg:{1:X8}, seq:{2}, hr={3:X8}",
					GetCID(),
					returnMsgID.ID,
					uiSequence,
					hrTem);

				// ignore IO send fail except connection closed
				if (hrTem == ((Result)ResultCode::IO_CONNECTION_CLOSED))
				{
					return hr;
				}
			}

			return hr;
		}

		void Connection::SetConnectionState(ConnectionState newState)
		{
			m_ConnectionState.store(newState, std::memory_order_relaxed);;
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
		void Connection::OnConnectionResult(Result hrConnect)
		{
			if (!(hrConnect))
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
				SFLog(Net, Info, "Connected CID:{0}, Dst={1}", GetCID(), GetRemoteInfo().PeerAddress);
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

		void Connection::RemoveStateAction(ConnectionState state, ConnectionAction* action)
		{
			int iState = (int)state;
			if (iState < 0 || iState >= (int)ConnectionState::Max)
			{
				Assert(false);
				return;
			}

			// TODO: we might need critical section at some point
			auto& actionListForState = m_ActionsByState[(int)state];
			for (int iAction = 0; iAction < actionListForState.size(); iAction++)
			{
				if (actionListForState[iAction] == action)
				{
					actionListForState.RemoveAt(iAction);
				}
			}
		}

		// Process network control message
		Result Connection::ProcNetCtrl(const MsgNetCtrl* pNetCtrl)
		{
			//assert(ThisThread::GetThreadID() == GetRunningThreadID());

			Result hr = ResultCode::SUCCESS;
			ConnectionMessageAction* pAction = nullptr;

			if (pNetCtrl->msgID.IDs.Mobile == 1 || pNetCtrl->Length < sizeof(MsgNetCtrl))
			{
				SFLog(Net, Info, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netCheck(Disconnect("Invalid packet"));
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			pAction = m_NetCtrlAction[pNetCtrl->msgID.IDs.MsgCode];
			if (pAction != nullptr)
			{
				return pAction->Run(pNetCtrl);
			}
			else
			{
				// Not handle or invalid
				SFLog(Net, Warning, "HackWarn : Not handled or Invalid net control packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netCheck(CloseConnection("Invalid net ctrl action"));
				netCheck(ResultCode::UNEXPECTED);
			}

			return hr;
		}

		const SharedPointerT<MessageEndpoint>& Connection::GetMessageEndpoint() const
		{
			if (m_MessageEndpoint == nullptr)
			{
				// create endpoint adapter
				m_MessageEndpoint = new MessageEndpointConnection(const_cast<Connection*>(this));
			}

			return m_MessageEndpoint;
		}

		// Initialize connection
		Result Connection::InitConnection(const PeerInfo& local, const PeerInfo& remote)
		{
			Result hr = ResultCode::SUCCESS;

			if (GetConnectionState() != ConnectionState::DISCONNECTED)
			{
				SFLog(Net, Error, "Failed to initialize connection, invalid address, CID:{0}, from:{1}, to:{2} hr:{3}", GetCID(), local.PeerAddress, remote.PeerAddress, hr);
				return ResultCode::INVALID_STATE;
			}

			// Except client everybody should have port number when it gets here
			if (remote.PeerClass != NetClass::Client && remote.PeerAddress.Port == 0)
			{
				SFLog(Net, Error, "Failed to initialize connection, invalid address, CID:{0}, from:{1}, to:{2} hr:{3}", GetCID(), local.PeerAddress, remote.PeerAddress, hr);
				return ResultCode::IO_INVALID_ADDRESS;
			}

			if (GetConnectionState() != ConnectionState::DISCONNECTED)
				netCheck(CloseConnection("InitConnection failed: Invalid State"));

			// create endpoint adapter
			m_MessageEndpoint = new MessageEndpointConnection(this);

			// event handler need to be reassigned after initconnection is called
			// - No they should be kept, but it need to be tested
			SetEventHandler(nullptr);

			m_EventQueue.ClearQueue();

			Assert(local.PeerClass != NetClass::Unknown);
			Assert(local.PeerClass == NetClass::Client || local.PeerID != 0);
			m_LocalInfo = local;
			m_RemoteInfo = remote;

			SetConnectionState(ConnectionState::CONNECTING);

			netCheck(InitSynchronization());

			m_ulZeroLengthRecvCount = 0;

			//SetSocket(socket, takeOverSocket);

			SetSockAddr(m_sockAddrRemote, m_RemoteInfo.PeerAddress.Address, m_RemoteInfo.PeerAddress.Port);

			m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
			m_ulNetCtrlTime = Util::Time.GetTimeMs();

			EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_STATE_CHANGE, GetConnectionState()));

			SFLog(Net, Info, "InitConnection CID:{0}, from:{1}, to:{2} hr:{3}", GetCID(), local.PeerAddress, remote.PeerAddress, hr);

			return hr;
		}

		// Disconnect connection
		Result Connection::Disconnect(const char* reason)
		{
			Result hr = ResultCode::SUCCESS;

			if (GetConnectionState() != ConnectionState::DISCONNECTING
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

				SFLog(Net, Info, "Entering Disconnect CID:{0}, sock:{1}, reason:{2}", GetCID(), GetSocket(), reason);
			}

			return hr;
		}


		// Close connection
		Result Connection::CloseConnection(const char* reason)
		{
			Result hr = ResultCode::SUCCESS;
			auto orgState = GetConnectionState();

			if (orgState == ConnectionState::DISCONNECTED)
				return hr;

			SetConnectionState(ConnectionState::DISCONNECTED);

			if (orgState == ConnectionState::CONNECTING)
			{
				OnConnectionResult(ResultCode::IO_DISCONNECTED);
			}

			m_ulNetCtrlTime = m_ulNetCtrlTryTime = Util::Time.GetTimeMs();
			UpdateConnectionTime();

			SFLog(Net, Info, "Connection Closed CID:{0}, sock:{1}, Addr:{2}, reason:{3}", GetCID(), GetSocket(), GetRemoteInfo().PeerAddress, reason);

			EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_DISCONNECTED, GetConnectionState()));

			return hr;
		}


		void Connection::DisconnectNRelease(const char* reason)
		{
			SetTickGroup(EngineTaskTick::None);
			// This guy should not belong to connection heap
			SharedPointerT<EngineTask> pTask = new(GetSystemHeap()) ConnectionTask_DisconnectNClose(this, reason);
			pTask->Request();
		}


		Result Connection::OnRecv(SharedPointerT<Message::MessageData>& pMsg)
		{
			ScopeContext hr;

			if (pMsg == nullptr)
				return hr;

			auto msgID = pMsg->GetMessageHeader()->msgID;

			// All messages must be decrypted before came here
			Assert(!msgID.IDs.Encrypted);

			// 
			Protocol::PrintDebugMessage("Recv", pMsg);

			//Assert( MemoryPool::CheckMemoryHeader( *pMsg ) );
			Assert(pMsg->GetDataLength() == 0 || pMsg->GetMessageHeader()->Crc32 != 0);

			if (GetEventHandler() == nullptr)
			{
				if (GetEventFireMode() == EventFireMode::Immediate)
				{
					GetRecvMessageDelegates().Invoke(this, pMsg);

					RecvMessageDelegates* pMessageDelegate = nullptr;
					m_RecvMessageDelegatesByMsgId.Find(pMsg->GetMessageHeader()->msgID.GetMsgID(), pMessageDelegate);
					if (pMessageDelegate)
						pMessageDelegate->Invoke(this, pMsg);
				}
				else
				{
					netCheck(GetRecvQueue().Enqueue(pMsg));
				}
			}
			else if (!(GetEventHandler()->OnRecvMessage(this, pMsg)))
			{
				SFLog(Net, Error, "Failed to route a message to recv msg:{0}", msgID);
				netCheck(GetRecvQueue().Enqueue(std::forward<SharedPointerT<Message::MessageData>>(pMsg)));
			}

			pMsg = nullptr;

			Assert(!(hr) || pMsg == nullptr);

			return hr;
		}


		// Query connection event
		Result Connection::DequeueConnectionEvent(ConnectionEvent& curEvent)
		{
			return m_EventQueue.Dequeue(curEvent.Composited);
		}

		// Add network event to queue
		Result Connection::EnqueueConnectionEvent(const ConnectionEvent& evt)
		{
			if (GetEventHandler())
			{
				GetEventHandler()->OnConnectionEvent(this, evt);
			}
			else
			{
				if (GetEventFireMode() == EventFireMode::Immediate)
				{
					GetConnectionEventDelegates().Invoke(this, evt);
				}
				else
				{
					return m_EventQueue.Enqueue(evt.Composited);
				}
			}

			return ResultCode::SUCCESS;
		}


		// Get received Message
		Result Connection::GetRecvMessage(SharedPointerT<Message::MessageData>& pIMsg)
		{
			ScopeContext hr;

			pIMsg = nullptr;

			if (!(GetRecvQueue().Dequeue(pIMsg)))
			{
				netCheck(ResultCode::FAIL);
			}

			{
				Message::MessageHeader* pMsgHeader = pIMsg->GetMessageHeader();
				uint uiPolicy = pMsgHeader->msgID.IDs.Policy;
				if (uiPolicy == 0
					|| uiPolicy >= PROTOCOLID_NETMAX) // invalid policy
				{
					netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
				}
			}

			return hr;
		}

		Result Connection::UpdateGameTick()
		{
			uint32_t messageCount = GetRecvMessageCount();
			for (uint iMessage = 0; iMessage < messageCount; iMessage++)
			{
				MessageDataPtr pMsgData;
				if (!GetRecvMessage(pMsgData))
					continue;

				GetRecvMessageDelegates().Invoke(this, pMsgData);

				RecvMessageDelegates* pMessageDelegate = nullptr;
				m_RecvMessageDelegatesByMsgId.Find(pMsgData->GetMessageHeader()->msgID.GetMsgID(), pMessageDelegate);
				if (pMessageDelegate)
					pMessageDelegate->Invoke(this, pMsgData);
			}

			uint32_t eventCount = m_EventQueue.size();
			for (uint iEvent = 0; iEvent < eventCount; iEvent++)
			{
				ConnectionEvent curEvent{};
				if (!m_EventQueue.Dequeue(curEvent.Composited))
					continue;

				GetConnectionEventDelegates().Invoke(this, curEvent);
			}

			return ResultCode::SUCCESS;
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
			Result hr;

			SetRunningThreadID(ThisThread::GetThreadID());

			netCheck(super::OnTick(tick));

			return TickUpdate();
		}

		Result Connection::TickUpdate()
		{
			Result hr = ResultCode::SUCCESS;
			Message::MessageID msgIDTem;

			hr = ProcConnectionStateAction();
			if (!(hr))
			{
				SFLog(Net, Info, "Process Connection state failed {0:X8}", hr);
			}

			return hr;
		}


	} // namespace Net
} // namespace SF

