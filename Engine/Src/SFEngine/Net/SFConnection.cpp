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
#include "SFProtocol.h"
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

        Result MessageEndpointConnection::SendMsg(const MessageHeader* messageData)
        {
            auto pConnection = m_pConnection.AsSharedPtr<Connection>();
            if (pConnection != nullptr)
            {
                return pConnection->SendMsg(messageData);
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
			, m_ConnectionEventDelegates(GetHeap())
			, m_RecvMessageDelegates(GetHeap())
			, m_IOHandler(ioHandler)
			, m_EventQueue(GetHeap())
			, m_ulConnectingTimeOut(Const::CONNECTION_TIMEOUT)
			, m_usSeqNone(0)
			, m_ulZeroLengthRecvCount(0)
			, m_IsSocketOwner(false)
			, m_UseAddressMap(false)
			, m_UsePeerIDMap(false)
			, m_RunningThreadID(ThisThread::GetThreadID())
            , m_Heartbeat(DurationMS(10 * 1000)) // heartbeat send time, Const::HEARTBEAT_TIMEOUT for timeout
			, m_ulNetCtrlTime(DurationMS(0))
			, m_ulNetCtrlTryTime(DurationMS(0))
		{
			// Initialize state tick action array
			m_ActionsByState = (StaticArray<ConnectionAction*, 32>*)m_Array2DBufferForConnectionAction;
			for (int iState = 0; iState < (int)ConnectionState::Max; iState++)
			{
				new((void*)&m_ActionsByState[iState]) ConnectionActionArray(GetHeap());
			}

            AddStateAction(ConnectionState::CONNECTED, &m_Heartbeat);
        }

		Connection::~Connection()
		{
			SetTickGroup(EngineTaskTick::None);

			// Not need with abstract class
            m_RecvMessageQueue.Reset();
			m_EventQueue.Reset();

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
            m_RecvMessageQueue.Reset();
			m_EventQueue.Reset();

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
            m_RecvMessageQueue.Reset();

			// When the queue is cleared these synchronization variables need to be cleared
			m_usSeqNone = 0;
			return ResultCode::SUCCESS;
		}

		// Request time sync, round trip time will be recorded
		Result Connection::TimeSync()
		{
			TimeStampMS reqTime = Util::Time.GetRawTimeMs();
			MessageID msgID;
			msgID.ID = reqTime.time_since_epoch().count();
			return SendNetCtrl(PACKET_NETCTRL_TIMESYNC, 0, msgID);
		}

		void Connection::OnTimeSyncRtn(DurationMS roundTripTime)
		{
			m_RoundTripDelay = roundTripTime;

			EnqueueConnectionEvent(ConnectionEvent(ConnectionEvent::EVT_TIMESYNC_RESULT, ResultCode::SUCCESS));
		}

		void Connection::OnHeartbeatPacket()
		{
            m_Heartbeat.OnHeartbeatPacket();
		}

		Result Connection::ProcConnectionStateAction()
		{
			Net::ConnectionState state = GetConnectionState();
			int iState = (int)state;
			if (iState < 0 || iState >= (int)ConnectionState::Max)
			{
				assert(false);
				return ResultCode::SUCCESS;
			}

			Net::Connection::ConnectionActionArray& actionListForState = m_ActionsByState[(int)state];
			for (Net::ConnectionAction* itAction : actionListForState)
			{
				itAction->Run();
			}

			return ResultCode::SUCCESS;
		}

        Result Connection::MakeNetCtrl(MessageHeader* pHeader, uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0)
        {
            Result hr;

            assert(pHeader->MessageSize >= sizeof(MsgNetCtrlBuffer)); // the available buffer should be bigger than we need
            pHeader->MessageId = uiCtrlCode;
            pHeader->SetSequence(uiSequence);
            pHeader->MessageSize = pHeader->GetHeaderSize();

            if (uiCtrlCode == PACKET_NETCTRL_SYNCRELIABLE)
            {
                MsgMobileNetCtrlSync* pCtlMsg = static_cast<MsgMobileNetCtrlSync*>(pHeader->GetPayloadPtr());
                pCtlMsg->MessageMask = parameter0;
                pHeader->MessageSize += sizeof(MsgMobileNetCtrlSync);
            }
            else if (uiCtrlCode == PACKET_NETCTRL_TIMESYNC || uiCtrlCode == PACKET_NETCTRL_TIMESYNC_RTN)
            {
                MsgNetCtrlTimeSync* pCtlMsg = static_cast<MsgNetCtrlTimeSync*>(pHeader->GetPayloadPtr());
                pCtlMsg->ClientTimeStamp = returnMsgID.ID;
                pCtlMsg->ServerTimeStamp = uint32_t(parameter0);
                pHeader->MessageSize += sizeof(MsgNetCtrlTimeSync);
            }
            else
            {
                MsgNetCtrl* pCtlMsg = static_cast<MsgNetCtrl*>(pHeader->GetPayloadPtr());
                pCtlMsg->rtnMsgID = returnMsgID;
                pHeader->MessageSize += sizeof(MsgNetCtrl);

                if (uiCtrlCode == PACKET_NETCTRL_CONNECT || returnMsgID.GetMessageID() == PACKET_NETCTRL_CONNECT)
                {
                    MsgNetCtrlConnect* pConMsg = reinterpret_cast<MsgNetCtrlConnect*>(pCtlMsg + 1);
                    pConMsg->ProtocolVersion = SF_PROTOCOL_VERSION;
                    pConMsg->Peer = GetLocalInfo();
                    pHeader->MessageSize += sizeof(MsgNetCtrlConnect);
                }
            }

            //SFLog(Net, Debug, "MakeNetCtrl {0}", pHeader->msgID, pHeader->Length);

            return hr;
        }

        Result Connection::SendCollection(const MessageCollection* pCollection)
        {
            Result hr;

            netCheckPtr(pCollection);

            for (auto itMsg = pCollection->begin(); itMsg; ++itMsg)
            {
                netCheck(SendMsg(itMsg));
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

            m_RecvMessageQueue.Reset();

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
		Result Connection::ProcNetCtrl(const MsgNetCtrlBuffer* pNetCtrlBuffer)
		{
			Result hr = ResultCode::SUCCESS;
			ConnectionMessageAction* pAction = nullptr;
			if (pNetCtrlBuffer->Header.MessageSize < sizeof(MsgNetCtrl))
			{
				SFLog(Net, Info, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netCheck(Disconnect("Invalid packet"));
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

            if (pNetCtrlBuffer->Header.GetMessageID().IDs.MsgCode >= countof(m_NetCtrlAction))
            {
                SFLog(Net, Error, "Invalid packet CID:{0}, Addr:{1}, msgId:{2}", GetCID(), GetRemoteInfo().PeerAddress, pNetCtrlBuffer->Header.GetMessageID());
                netCheck(Disconnect("Invalid packet"));
                netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
            }

			pAction = m_NetCtrlAction[pNetCtrlBuffer->Header.GetMessageID().IDs.MsgCode];
			if (pAction != nullptr)
			{
				return pAction->Run(&pNetCtrlBuffer->Header);
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
				m_MessageEndpoint = new(GetHeap()) MessageEndpointConnection(const_cast<Connection*>(this));
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
			if (m_MessageEndpoint == nullptr)
				m_MessageEndpoint = new(GetHeap()) MessageEndpointConnection(this);

			m_EventQueue.Reset();

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

				ConnectionState previsouState = GetConnectionState();

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

		Result Connection::OnRecv(MessageHeader* pMsgHeader)
		{
		    Result hr;

			if (pMsgHeader == nullptr)
				return hr;

			MessageID msgID = pMsgHeader->GetMessageID();

			// 
			Protocol::PrintDebugMessage("Recv", pMsgHeader);

			//Assert( MemoryPool::CheckMemoryHeader( *pMsg ) );
            assert(pMsgHeader->GetPayloadSize() == 0 // 0 crc for zero size packet
                || pMsgHeader->MessageSize > 1024); // Multiple sub framed message can't have crc value. each sub frame does

            uint uiPolicy = msgID.IDs.Protocol;
            if (uiPolicy == 0 // Net control
                || uiPolicy >= MessageProtocol::Max) // invalid policy
            {
                netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
            }

			if (GetEventFireMode() == EventFireMode::Immediate)
			{
				GetRecvMessageDelegates().Invoke(this, pMsgHeader);
			}
			else
			{
                MessageItemWritePtr msgItemPtr = m_RecvMessageQueue.AllocateWrite(pMsgHeader->MessageSize);
                if (msgItemPtr.IsValid())
                {
                    memcpy(msgItemPtr.data(), pMsgHeader, pMsgHeader->MessageSize);
                }
			}

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
			if (GetEventFireMode() == EventFireMode::Immediate)
			{
				GetConnectionEventDelegates().Invoke(this, evt);
			}
			else
			{
				return m_EventQueue.Enqueue(evt.Composited);
			}

			return ResultCode::SUCCESS;
		}

		Result Connection::UpdateGameTick()
		{
			uint32_t messageCount = GetRecvMessageCount();
			for (uint iMessage = 0; iMessage < messageCount; iMessage++)
			{
                MessageHeader* pHeader = nullptr;
                MessageItemReadPtr itemPtr = m_RecvMessageQueue.DequeueRead();
                if (!itemPtr)
                {
                    break;
                }

                pHeader = reinterpret_cast<MessageHeader*>(itemPtr.data());

				GetRecvMessageDelegates().Invoke(this, pHeader);
			}

			auto eventCount = m_EventQueue.size();
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
			MessageID msgIDTem;

			hr = ProcConnectionStateAction();
			if (!hr.IsSuccess())
			{
				SFLog(Net, Info, "Process Connection state failed {0:X8}", hr);
			}

			return hr;
		}


	} // namespace Net
} // namespace SF

