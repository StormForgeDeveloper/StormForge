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
#include "Thread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeEngine.h"


#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "Util/SFTimeUtil.h"
#include "Protocol/SFProtocol.h"
#include "String/SFToString.h"

#include "Net/SFConnectionActions.h"
#include "Net/SFConnectionMUDP.h"
#include "Net/SFConnection.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFMessage.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetToString.h"




namespace SF {
namespace Net {




	Result ConnectionMessageAction_MUDPHandleAck::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;

		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);
		if (pNetCtrl->rtnMsgID.IDs.Type == Message::MSGTYPE_NETCONTROL)// connecting process
		{
			GetConnection()->OnHeartbeatPacket();

			switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
			{
			case NetCtrlCode_Disconnect:
				if (GetConnectionState() == ConnectionState::DISCONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
				{
					SFLog(Net, Info, "RECV Disconnected CID:{0}", GetCID());
					netChk(CloseConnection("Received Disconnect ack"));
				}
				break;
			case NetCtrlCode_Connect:
				if (GetConnectionState() == ConnectionState::CONNECTING)
				{
					GetConnection()->SetRemoteInfo((NetClass)pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->PeerID);

					if(GetRemoteInfo().PeerClass != NetClass::Unknown)
					{
						OnConnectionResult(ResultCode::SUCCESS);
					}
				}
				break;
			case NetCtrlCode_Heartbeat:
			case NetCtrlCode_SyncReliable:
				break;
			case NetCtrlCode_TimeSync:

				break;
			default:
				SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netChk(Disconnect("Invalid packet"));
				netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
				break;
			};
		}
		else // general message
		{
			SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netChk(Disconnect("Invalid packet"));
			netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

	Proc_End:
		return hr;
	}




	Result ConnectionMessageAction_MUDPHandleNack::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;

		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);
		if (pNetCtrl->rtnMsgID.IDs.Type == Message::MSGTYPE_NETCONTROL)// connecting process
		{
			switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
			{
			case NetCtrlCode_Connect:
				if (GetConnectionState() == ConnectionState::CONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
				{
					// Protocol version mismatch
					OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
				}
				netChk(Disconnect("Protocal mismatch"));
				break;
			default:
				break;
			};
		}

	Proc_End:
		return hr;
	}


	Result ConnectionMessageAction_HandleHeartbeat::Run(const Message::MessageHeader* pNetCtrl)
	{
		Result hr;

		netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID, GetLocalInfo().PeerID));

	Proc_End:
		return hr;
	}


	Result ConnectionMessageAction_HandleTimeSync::Run(const Message::MessageHeader* pNetCtrl)
	{
		Result hr;

		// Pass back the value in rtn msg id
		auto pNetCtrlData = (MsgNetCtrl*)(pNetCtrl);

		netChk(SendNetCtrl(PACKET_NETCTRL_TIMESYNC_RTN, 0, pNetCtrlData->rtnMsgID, Util::Time.GetRawUTCSec().time_since_epoch().count()));

	Proc_End:
		return hr;
	}

	Result ConnectionMessageAction_HandleTimeSyncRtn::Run(const Message::MessageHeader* pNetCtrl)
	{
		Result hr;

		auto pNetCtrlData = (MsgNetCtrl*)(pNetCtrl);

		auto sentTime = TimeStampMS(DurationMS(pNetCtrlData->rtnMsgID.ID));

		auto roundTripTime = (Util::Time.GetRawTimeMs() - sentTime);

		auto halfRoundTripSec = (roundTripTime.count() >> 1) / 1000;

		auto serverTime = TimeStampSec(DurationSec(pNetCtrlData->PeerID + halfRoundTripSec));
		
		Util::Time.UpdateUTCOffset(TimeStampMS(roundTripTime));

		GetConnection()->OnTimeSyncRtn(roundTripTime);

		return hr;
	}


	Result ConnectionMessageAction_MUDPHandleSyncReliableServer::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;
		Result hrTem;

		ConnectionMUDP* pConnUDP = GetConnection();
		auto& sendWindow = pConnUDP->GetSendReliableWindow();
		auto& recvWindow = pConnUDP->GetRecvReliableWindow();
		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);

		//MutexScopeLock localLock(sendReliableWindow.GetLock());

		MsgMobileNetCtrlSync *pSyncCtrl = (MsgMobileNetCtrlSync*)pNetCtrl;
		if (pSyncCtrl->Length != sizeof(MsgMobileNetCtrlSync))
			netErr(ResultCode::IO_BADPACKET_SIZE);

		hrTem = sendWindow.ReleaseMsg(pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask);
		if (hrTem)
		{
			SFLog(Net, Debug, "NetCtrl Recv SendMask : CID:{0}: mySeq:{1}, seq:{2}, mask:{3:X8}",
				GetCID(), sendWindow.GetBaseSequence(), pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask);
		}
		else
		{
			SFLog(Net, Debug, "NetCtrl Recv SendMask Failed : CID:{0} mySeq:{1}, seq:{2}, mask:{3:X8}, hr={4:X8}",
				GetCID(), sendWindow.GetBaseSequence(), pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask, hrTem);
		}

		if (hrTem == Result(ResultCode::UNEXPECTED))
			CloseConnection("Unexpected send window sequence");

		netChk(hrTem);

		netChk(GetConnection()->SendSync(recvWindow.GetBaseSequence(), recvWindow.GetSyncMask()));

		// poke send network only when there is something to send
		// Actually send proc also handles recv window
		if (GetEventHandler() != nullptr)
		{
			pConnUDP->SetSendBoost(Const::RELIABLE_SEND_BOOST);

			hrTem = GetEventHandler()->OnNetSyncMessage(pConnUDP);
			if (hrTem != ResultCode::NOT_IMPLEMENTED)
			{
				netChk(hrTem);
			}
		}
		else
		{
			pConnUDP->GetNetSyncMessageDelegates().Invoke((Connection*)pConnUDP);
		}

	Proc_End:

		return hr;
	}


	Result ConnectionMessageAction_MUDPHandleSyncReliableClient::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;
		Result hrTem;

		ConnectionMUDP* pConnUDP = GetConnection();
		auto& sendReliableWindow = pConnUDP->GetSendReliableWindow();
		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);

		//MutexScopeLock localLock(sendReliableWindow.GetLock());

		MsgMobileNetCtrlSync *pSyncCtrl = (MsgMobileNetCtrlSync*)pNetCtrl;
		if (pSyncCtrl->Length != sizeof(MsgMobileNetCtrlSync))
			netErr(ResultCode::IO_BADPACKET_SIZE);

		hrTem = sendReliableWindow.ReleaseMsg(pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask);
		SFLog(Net, Custom10, "NetCtrl Recv SendReliableMask : CID:{0}:{1}, seq:{2}, mask:{3:X8}, hr={4:X8}",
			GetCID(), sendReliableWindow.GetBaseSequence(), pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask, hrTem);

		if (hrTem == ResultCode::UNEXPECTED)
			CloseConnection("Unexpected send window sequence");

		GetConnection()->UpdateNetCtrlTime();

		netChk(hrTem);

		if (sendReliableWindow.GetHeadSequence() != sendReliableWindow.GetBaseSequence())
			pConnUDP->SetSendBoost(Const::RELIABLE_SEND_BOOST); // for regular ping. maybe I can get rid of this later

	Proc_End:
		return hr;
	}



	Result ConnectionMessageAction_MUDPHandleConnect::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;

		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);
		uint ProtocolVersion = pNetCtrl->rtnMsgID.ID;
		NetClass RemoteClass = (NetClass)pNetCtrl->msgID.IDSeq.Sequence;
		switch (GetConnectionState())
		{
		case  ConnectionState::CONNECTING:
			if (ProtocolVersion != SF_PROTOCOL_VERSION)
			{
				netChk(SendNetCtrl(PACKET_NETCTRL_NACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID, GetLocalInfo().PeerID));
				OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
				netChk(Disconnect("Protocol mismatch"));
				break;
			}
			else if (GetRemoteInfo().PeerClass != NetClass::Unknown && RemoteClass != GetRemoteInfo().PeerClass)
			{
				netChk(SendNetCtrl(PACKET_NETCTRL_NACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID, GetLocalInfo().PeerID));
				OnConnectionResult(ResultCode::IO_INVALID_NETCLASS);
				netChk(Disconnect("Invalid netclass"));
				break;
			}

			netChk(SendNetCtrl(PACKET_NETCTRL_ACK, (uint)GetLocalInfo().PeerClass, pNetCtrl->msgID, GetLocalInfo().PeerID));

			SFLog(Net, Debug3, "UDP Recv Connecting CID({0}) : C:{1}, Ver:{2})", GetCID(), RemoteClass, ProtocolVersion);
			GetConnection()->SetRemoteInfo(RemoteClass, pNetCtrl->PeerID);

			// Set connection is succeeded and connected
			OnConnectionResult(ResultCode::SUCCESS);
			break;
		case ConnectionState::CONNECTED:
			netChk(SendNetCtrl(PACKET_NETCTRL_ACK, (uint)GetLocalInfo().PeerClass, pNetCtrl->msgID, GetLocalInfo().PeerID));
			break;
		default:
			break;
		}

	Proc_End:

		return hr;
	}


	Result ConnectionMessageAction_UDPHandleDisconnect::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;

		auto pNetCtrl = netCtrlMsg;
		netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID, GetLocalInfo().PeerID));
		SFLog(Net, Info, "Disconnect from remote CID:{0}", GetCID());
		netChk(CloseConnection("Received disconnect"));


	Proc_End:
		return hr;
	}






	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection state Action
	//


	Result ConnectionStateAction_DisposeOnExpire::Run()
	{
		if (GetConnectionState() != ConnectionState::DISCONNECTED)
			CloseConnection("Dispose on expire");

		if (GetConnection()->CanDelete() || Util::TimeSince(m_Start) > DurationMS(2*60))
		{
			GetConnection()->Dispose();
		}

		return ResultCode::SUCCESS;
	}



	Result ConnectionStateAction_TimeoutConnecting::Run()
	{
		Result hr;
		if (Util::TimeSince(GetNetCtrlTime()) > DurationMS(GetConnection()->GetConnectingTimeOut())) // connection time out
		{
			SFLog(Net, Info, "Connecting Timeout CID:{0}, ({1})", GetCID(), GetConnection()->GetConnectingTimeOut());
			netCheck(CloseConnection("Connection time out"));
		}

		return hr;
	}

	Result ConnectionStateAction_SendConnect::Run()
	{
		Result hr;

		if (Util::TimeSince(GetNetCtrlTryTime()) > Const::CONNECTION_RETRY_TIME) // retry
		{
			UpdateNetCtrlTryTime();
			SFLog(Net, Debug2, "Send Connecting CID({0}) : C:{1}, V:{2})", GetCID(), GetLocalInfo().PeerClass, (uint32_t)SF_PROTOCOL_VERSION);
			netCheck(GetConnection()->SendNetCtrl(PACKET_NETCTRL_CONNECT, (uint)GetLocalInfo().PeerClass, Message::MessageID(SF_PROTOCOL_VERSION), GetLocalInfo().PeerID));
		}

	Proc_End:

		return hr;
	}


	Result ConnectionStateAction_TimeoutHeartbeat::Run()
	{
		Result hr;

		if (Util::TimeSince(GetNetCtrlTime()) > Const::HEARTBEAT_TIMEOUT) // connection time out
		{
			SFLog(Net, Debug, "UDP Connection Timeout CID:{0}", GetCID());
			netCheck(Disconnect("Connection TimeOut"));
			netCheck(CloseConnection("Heart bit timeout"));
		}

		return hr;
	}

	Result ConnectionStateAction_SendHeartbeat::Run()
	{
		Result hr;
		Message::MessageID msgIDDummy;
		msgIDDummy.ID = PACKET_NETCTRL_NONE;

		if (Util::TimeSince(GetNetCtrlTryTime()) > GetConnection()->GetHeartbeatTry()) // heart bit time
		{
			UpdateNetCtrlTryTime();
			netCheck(GetConnection()->SendPending(PACKET_NETCTRL_HEARTBEAT, 0, msgIDDummy));
		}

		return hr;
	}


	Result ConnectionStateAction_TimeoutDisconnecting::Run()
	{
		Result hr;

		if (Util::TimeSince(GetNetCtrlTime()) > Const::DISCONNECT_TIMEOUT) // connection time out
		{
			SFLog(Net, Debug, "Disconnecting Timeout CID:{0}", GetCID());
			netCheck(CloseConnection("Disconnecting"));
		}

		return hr;
	}

	Result ConnectionStateAction_SendDisconnect::Run()
	{
		Result hr;
		Message::MessageID msgIDDummy;
		msgIDDummy.ID = PACKET_NETCTRL_NONE;

		if (Util::TimeSince(GetNetCtrlTryTime()) > Const::DISCONNECT_RETRY_TIME) // retry
		{
			UpdateNetCtrlTryTime();
			netChk(GetConnection()->SendPending(PACKET_NETCTRL_DISCONNECT, 0, msgIDDummy));
		}

	Proc_End:

		return hr;
	}


	Result ConnectionStateAction_SendSync::Run()
	{
		Result hr = ResultCode::SUCCESS;
		auto sendBoost = GetConnection()->GetSendBoost();
		auto syncTimeout = sendBoost > 0 ? DurationMS(Const::RELIABLE_SYNC_POLLING_TIME_BOOSTED / sendBoost) : DurationMS(Const::RELIABLE_SYNC_POLLING_TIME);

		if (Util::TimeSince(m_ReliableSyncTime) < syncTimeout)
			return hr;

		m_ReliableSyncTime = Util::Time.GetTimeMs();

		auto& recvWindow = GetConnection()->GetRecvReliableWindow();

		GetConnection()->DecSendBoost();

		netChk(GetConnection()->SendSync(recvWindow.GetBaseSequence(), recvWindow.GetSyncMask()));

	Proc_End:

		return hr;
	}


	Result ConnectionStateAction_SendSyncSvr::Run()
	{
		Result hr = ResultCode::SUCCESS;

		if (GetConnection()->GetSendBoost() <= 0)
			return hr;

		m_ReliableSyncTime = Util::Time.GetTimeMs();

		auto& recvWindow = GetConnection()->GetRecvReliableWindow();

		GetConnection()->DecSendBoost();

		//netChk(GetConnection()->SendSync(recvWindow.GetBaseSequence(), recvWindow.GetSyncMask()));

	Proc_End:

		if (GetEventHandler() != nullptr)
		{
			GetEventHandler()->OnNetSyncMessage(GetConnection());
		}
		else
		{
			GetConnection()->GetNetSyncMessageDelegates().Invoke(GetConnection());
		}

		return hr;
	}

	Result ConnectionStateAction_SendReliableQueue::Run()
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pIMsg;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();

		//assert(ThisThread::GetThreadID() ==  GetConnection()->GetRunningThreadID());

		auto& sendWindow = GetConnection()->GetSendReliableWindow();
		auto& sendGuaQueue = GetConnection()->GetSendGuaQueue();

		// Send guaranteed message process
		CounterType NumProc = sendWindow.GetAvailableSize();
		CounterType uiNumPacket = sendGuaQueue.size();
		NumProc = Util::Min(NumProc, uiNumPacket);
		for (CounterType uiPacket = 0; uiPacket < NumProc; uiPacket++)
		{
			if (!(sendGuaQueue.Dequeue(pIMsg)))
				break;

			AssertRel(pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence == 0);

			// check sending window size
			hr = sendWindow.EnqueueMessage(ulTimeCur, pIMsg);
			if (!(hr))
			{
				netErr(hr);
			}

			SFLog(Net, Debug2, "SENDENQReliable : CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
				pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
				pIMsg->GetMessageHeader()->msgID,
				pIMsg->GetMessageHeader()->Length);

			// don't bother network with might not be able to processed
			if ((sendWindow.GetHeadSequence() - sendWindow.GetBaseSequence()) < GetConnection()->GetMaxGuarantedRetryAtOnce())
			{
				netChk(GetConnection()->SendPending(pIMsg));
			}
			pIMsg = nullptr;
		}


	Proc_End:

		if (!(hr))
			Disconnect("Failed to send reliable packets");

		return hr;
	}


	Result ConnectionStateAction_SendReliableRetry::Run()
	{
		Result hr = ResultCode::SUCCESS;
		SendMsgWindow::MessageData *pMessageElement = nullptr;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();
		auto sendBoost = GetConnection()->GetSendBoost();
		auto retryTimeout = sendBoost > 0 ? DurationMS(Const::MUDP_SEND_RETRY_TIME / sendBoost) : DurationMS(Const::MUDP_SEND_RETRY_TIME);

		//assert(ThisThread::GetThreadID() == GetRunningThreadID());
		auto& sendWindow = GetConnection()->GetSendReliableWindow();

		// Guaranteed retry
		//MutexScopeLock localLock(sendWindow.GetLock());// until ReleaseMsg( uint16_t uiSequence ) is thread safe, we need to lock the window
		uint uiMaxProcess = Util::Min(sendWindow.GetMsgCount(), GetConnection()->GetMaxGuarantedRetryAtOnce());
		for (uint uiIdx = 0, uiMsgProcessed = 0; uiIdx < (uint)sendWindow.GetAcceptableSequenceRange() && uiMsgProcessed < uiMaxProcess; uiIdx++)
		{
			if (!sendWindow.GetAt(uiIdx, pMessageElement))
			{
				pMessageElement = nullptr;
				continue;
			}

			if (pMessageElement == nullptr || pMessageElement->pMsg == nullptr)
			{
				//AssertRel(pMessageElement->State == MessageWindow::ItemState::Free || pMessageElement->State == MessageWindow::ItemState::CanFree);
				continue;
			}

			if (Util::TimeSince(pMessageElement->ulTimeStamp) <= retryTimeout)
				break;

			uint totalGatheredSize = GetConnection()->GetGatheredBufferSize() + pMessageElement->pMsg->GetMessageSize();
			if (GetConnection()->GetGatheredBufferSize() > 0 && totalGatheredSize > Const::PACKET_GATHER_SIZE_MAX)
			{
				// too big to send
				// stop gathering here, and send
				pMessageElement = nullptr;
				break;
			}

			SFLog(Net, Debug2, "SENDReliableRetry : CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
				pMessageElement->pMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
				pMessageElement->pMsg->GetMessageHeader()->msgID,
				pMessageElement->pMsg->GetMessageHeader()->Length);

			pMessageElement->ulTimeStamp = ulTimeCur;

			// Creating new reference object will increase reference count of the message instance.
			// And more importantly, SendPending is taking reference of the variable and clear it when it done sending
			auto tempMsg = pMessageElement->pMsg;
			GetConnection()->SendPending(tempMsg);
			pMessageElement = nullptr;
		}


		//Proc_End:

		return hr;
	}




} // namespace Net
} // namespace SF


