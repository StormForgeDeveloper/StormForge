////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Connection action
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeEngine.h"

#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "Util/SFTimeUtil.h"
#include "SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"

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




	Result ConnectionMessageAction_UDPHandleAck::Run(const MessageHeader* pHeader)
	{
		Result hr;

		auto socketType = GetSocketType();

		const MsgNetCtrl* pNetCtrl = reinterpret_cast<const MsgNetCtrl*>(pHeader->GetPayloadPtr());
		if (pNetCtrl->rtnMsgID.GetMessageType() == EMessageType::NetCtrl)// connecting process
		{
			GetConnection()->OnHeartbeatPacket();

			switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
			{
			case NetCtrlCode_Disconnect:
				if (GetConnectionState() == ConnectionState::DISCONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
				{
					SFLog(Net, Info, "RECV Disconnected CID:{0}", GetCID());
					netCheck(CloseConnection("Received Disconnect ack"));
				}
				break;
			case NetCtrlCode_Connect:
				if (GetConnectionState() == ConnectionState::CONNECTING)
				{
                    const MsgNetCtrlConnect* pNetCtrlConnect = reinterpret_cast<const MsgNetCtrlConnect*>(pHeader->GetPayloadPtr());
					GetConnection()->SetRemoteInfo(pNetCtrlConnect->Peer.PeerClass, pNetCtrlConnect->Peer.PeerID);

					if (GetRemoteInfo().PeerClass != NetClass::Unknown)
					{
						OnConnectionResult(ResultCode::SUCCESS);
					}
				}
				break;
			case NetCtrlCode_Heartbeat:
				SFLog(Net, Debug6, "RECV Heartbeat Ack CID:{0}, socketType:{1}", GetCID(), socketType);
				break;
			case NetCtrlCode_SyncReliable:
			case NetCtrlCode_TimeSync:
				// Called already
				break;
			default:
				SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netCheck(Disconnect("Invalid packet"));
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
				break;
			};
		}
		else // general message
		{
			// Remove from Guaranteed queue
			if (pNetCtrl->rtnMsgID.IDs.Reliability)
			{
				auto* pConUDP = static_cast<ConnectionUDPBase*>(GetConnection());
				auto hrTem = pConUDP->GetSendReliableWindow().QueueReleasedSequence(pHeader->GetSequence());
				SFLog(Net, Debug5, "NetCtrl Recv GuaAck : CID:{0}:{1}, seq:{2}, rtnmsg:{3}, hr={4}, windows status, baseSeq:{5}, headSeq:{6}, remain:{7}, msgCount:{8}",
					GetCID(), pHeader->GetSequence(), pHeader->GetSequence(), pNetCtrl->rtnMsgID, hrTem,
					pConUDP->GetSendReliableWindow().GetBaseSequence(), pConUDP->GetSendReliableWindow().GetHeadSequence(), 
					pConUDP->GetSendReliableWindow().GetRemainSequenceCount(), pConUDP->GetSendReliableWindow().GetMsgCount());
				netCheck(hrTem);
			}
			else
			{
				SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netCheck(Disconnect("Invalid packet"));
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}
		}

		return hr;
	}

	Result ConnectionMessageAction_HandleAck::Run(const MessageHeader* pHeader)
	{
		Result hr;

		const MsgNetCtrl* pNetCtrl = (MsgNetCtrl*)(pHeader->GetPayloadPtr());
		if (pNetCtrl->rtnMsgID.GetMessageType() == EMessageType::NetCtrl)// connecting process
		{
			GetConnection()->OnHeartbeatPacket();

			switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
			{
			case NetCtrlCode_Disconnect:
				if (GetConnectionState() == ConnectionState::DISCONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
				{
					SFLog(Net, Info, "RECV Disconnected CID:{0}", GetCID());
					netCheck(CloseConnection("Received Disconnect ack"));
				}
				break;
			case NetCtrlCode_Connect:
				if (GetConnectionState() == ConnectionState::CONNECTING)
				{
                    const MsgNetCtrlConnect* pConMsg = reinterpret_cast<const MsgNetCtrlConnect*>(pNetCtrl + 1);
					GetConnection()->SetRemoteInfo(pConMsg->Peer.PeerClass, pConMsg->Peer.PeerID);

					if (GetRemoteInfo().PeerClass != NetClass::Unknown)
					{
						OnConnectionResult(ResultCode::SUCCESS);
					}
				}
				break;
			case NetCtrlCode_Heartbeat:
			case NetCtrlCode_SyncReliable:
			case NetCtrlCode_TimeSync:
				// Called already
				break;
			default:
				SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
				netCheck(Disconnect("Invalid packet"));
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
				break;
			};
		}
		else // general message
		{
			SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netCheck(Disconnect("Invalid packet"));
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

		return hr;
	}




	Result ConnectionMessageAction_UDPHandleNack::Run(const MessageHeader* pHeader)
	{
		Result hr;

		const MsgNetCtrl* pNetCtrl = (MsgNetCtrl*)(pHeader->GetPayloadPtr());
		if (pNetCtrl->rtnMsgID.GetMessageType() == EMessageType::NetCtrl)// connecting process
		{
			switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
			{
			case NetCtrlCode_Connect:
				if (GetConnectionState() == ConnectionState::CONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
				{
					// Protocol version mismatch
                    SFLog(Net, Warning, "Protocol version mismatch CID:{0}, Have:{1}", GetCID(), SF_PROTOCOL_VERSION);
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

	Result ConnectionMessageAction_HandleNack::Run(const MessageHeader* pHeader)
	{
		Result hr;

		const MsgNetCtrl* pNetCtrl = (MsgNetCtrl*)(pHeader->GetPayloadPtr());
		if (pNetCtrl->rtnMsgID.GetMessageType() == EMessageType::NetCtrl)// connecting process
		{
			switch (pNetCtrl->rtnMsgID.IDs.MsgCode)
			{
			case NetCtrlCode_Connect:
				// Protocol version mismatch
                SFLog(Net, Warning, "Protocol version mismatch CID:{0}, Have:{1}", GetCID(), SF_PROTOCOL_VERSION);
				OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
				netCheck(Disconnect("Protocol mismatch"));
				break;
			default:
				break;
			};
		}

		return hr;
	}


	Result ConnectionMessageAction_HandleHeartbeat::Run(const MessageHeader* pHeader)
	{
		Result hr;

		GetConnection()->OnHeartbeatPacket();
		SFLog(Net, Debug4, "Heartbeat CID:{0}, socketType:{1}", GetCID(), GetSocketType());
		netCheck(SendNetCtrl(PACKET_NETCTRL_ACK, pHeader->GetSequence(), pHeader->GetMessageID()));

		return hr;
	}


	Result ConnectionMessageAction_HandleTimeSync::Run(const MessageHeader* pHeader)
	{
		Result hr;

		// Pass back the value in rtn msg id
        MsgNetCtrlTimeSync* pNetCtrlData = (MsgNetCtrlTimeSync*)(pHeader->GetPayloadPtr());

		netCheck(SendNetCtrl(PACKET_NETCTRL_TIMESYNC_RTN, 0, pNetCtrlData->ClientTimeStamp, Util::Time.GetRawUTCSec().time_since_epoch().count()));

		return hr;
	}

	Result ConnectionMessageAction_HandleTimeSyncRtn::Run(const MessageHeader* pHeader)
	{
		Result hr;

        MsgNetCtrlTimeSync* pNetCtrlData = (MsgNetCtrlTimeSync*)(pHeader->GetPayloadPtr());

		auto sentTime = TimeStampMS(DurationMS(pNetCtrlData->ClientTimeStamp));

		auto roundTripTime = (Util::Time.GetRawTimeMs() - sentTime);

		auto halfRoundTripSec = (roundTripTime.count() >> 1) / 1000;

		auto serverTime = TimeStampSec(DurationSec(pNetCtrlData->ServerTimeStamp + halfRoundTripSec));
		
		Util::Time.UpdateUTCOffset(TimeStampMS(roundTripTime));

		GetConnection()->OnTimeSyncRtn(roundTripTime);

		return hr;
	}


	Result ConnectionMessageAction_MUDPHandleSyncReliableServer::Run(const MessageHeader* pHeader)
	{
		Result hr;
		Result hrTem;

		ConnectionMUDP* pConnUDP = GetConnection();
		auto& sendWindow = pConnUDP->GetSendReliableWindow();
		auto& recvWindow = pConnUDP->GetRecvReliableWindow();
		const MsgNetCtrl* pNetCtrl = (MsgNetCtrl*)(pHeader->GetPayloadPtr());

		//MutexScopeLock localLock(sendReliableWindow.GetLock());

		MsgMobileNetCtrlSync *pSyncCtrl = (MsgMobileNetCtrlSync*)pNetCtrl;
		if (pHeader->MessageSize != sizeof(MsgMobileNetCtrlSync))
			netCheck(ResultCode::IO_BADPACKET_SIZE);

		hrTem = sendWindow.QueueReleasedSequence(pHeader->GetSequence(), pSyncCtrl->MessageMask);
		if (hrTem)
		{
			SFLog(Net, Debug2, "NetCtrl Recv SendMask : CID:{0}: mySeq:{1}, seq:{2}, mask:{3}",
				GetCID(), sendWindow.GetBaseSequence(), pHeader->GetSequence(), pSyncCtrl->MessageMask);
		}
		else
		{
			SFLog(Net, Debug2, "NetCtrl Recv SendMask Failed : CID:{0} mySeq:{1}, seq:{2}, mask:{3}, hr={4}",
				GetCID(), sendWindow.GetBaseSequence(), pHeader->GetSequence(), pSyncCtrl->MessageMask, hrTem);
		}

		if (hrTem == Result(ResultCode::UNEXPECTED))
			CloseConnection("Unexpected send window sequence");

		netCheck(hrTem);

		netCheck(GetConnection()->SendSync(recvWindow.GetBaseSequence(), recvWindow.GetSyncMask()));

		return hr;
	}


	Result ConnectionMessageAction_MUDPHandleSyncReliableClient::Run(const MessageHeader* pHeader)
	{
		Result hr;
		Result hrTem;

		ConnectionMUDP* pConnUDP = GetConnection();
		auto& sendReliableWindow = pConnUDP->GetSendReliableWindow();
		const MsgNetCtrl* pNetCtrl = (MsgNetCtrl*)(pHeader->GetPayloadPtr());

		//MutexScopeLock localLock(sendReliableWindow.GetLock());

		MsgMobileNetCtrlSync *pSyncCtrl = (MsgMobileNetCtrlSync*)pNetCtrl;
		if (pHeader->MessageSize != sizeof(MsgMobileNetCtrlSync))
			netCheck(ResultCode::IO_BADPACKET_SIZE);

		hrTem = sendReliableWindow.QueueReleasedSequence(pHeader->GetSequence(), pSyncCtrl->MessageMask);
		SFLog(Net, Custom10, "NetCtrl Recv SendReliableMask : CID:{0}:{1}, seq:{2}, mask:{3}, hr={4}",
			GetCID(), sendReliableWindow.GetBaseSequence(), pHeader->GetSequence(), pSyncCtrl->MessageMask, hrTem);

		if (hrTem == ResultCode::UNEXPECTED)
			CloseConnection("Unexpected send window sequence");

		GetConnection()->UpdateNetCtrlTime();

		netCheck(hrTem);

		if (sendReliableWindow.GetHeadSequence() != sendReliableWindow.GetBaseSequence())
			pConnUDP->SetSendBoost(Const::RELIABLE_SEND_BOOST); // for regular ping. maybe I can get rid of this later

		return hr;
	}



	Result ConnectionMessageAction_UDPHandleConnect::Run(const MessageHeader* pHeader)
	{
		Result hr;

		const MsgNetCtrl* pNetCtrl = reinterpret_cast<MsgNetCtrl*>(pHeader->GetPayloadPtr());
        const MsgNetCtrlConnect* pNetCtrlConnect = reinterpret_cast<const MsgNetCtrlConnect*>(pNetCtrl+1);
		uint ProtocolVersion = pNetCtrlConnect->ProtocolVersion;
		NetClass RemoteClass = pNetCtrlConnect->Peer.PeerClass;
		switch (GetConnectionState())
		{
		case  ConnectionState::CONNECTING:
			if (ProtocolVersion != SF_PROTOCOL_VERSION)
			{
				netCheck(SendNetCtrl(PACKET_NETCTRL_NACK, pHeader->GetSequence(), pHeader->MessageId));
                SFLog(Net, Warning, "Protocol version mismatch CID:{0}, RecvVer:{1}, Expected:{2}", GetCID(), pNetCtrlConnect->ProtocolVersion, SF_PROTOCOL_VERSION);
				OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
				netCheck(Disconnect("Protocol mismatch"));
				break;
			}
			else if (GetRemoteInfo().PeerClass != NetClass::Unknown && RemoteClass != GetRemoteInfo().PeerClass)
			{
				netCheck(SendNetCtrl(PACKET_NETCTRL_NACK, pHeader->GetSequence(), pHeader->MessageId));
				OnConnectionResult(ResultCode::IO_INVALID_NETCLASS);
				netCheck(Disconnect("Invalid netclass"));
				break;
			}

			netCheck(SendNetCtrl(PACKET_NETCTRL_ACK, 0, pHeader->MessageId));

			SFLog(Net, Debug3, "UDP Recv Connecting CID({0}) : C:{1}, Ver:{2})", GetCID(), RemoteClass, ProtocolVersion);
			GetConnection()->SetRemoteInfo(RemoteClass, pNetCtrlConnect->Peer.PeerID);

			// Set connection is succeeded and connected
			OnConnectionResult(ResultCode::SUCCESS);
			break;
		case ConnectionState::CONNECTED:
			netCheck(SendNetCtrl(PACKET_NETCTRL_ACK, 0, pHeader->MessageId));
			break;
		default:
			break;
		}

		return hr;
	}

	Result ConnectionMessageAction_HandleConnect::Run(const MessageHeader* pHeader)
	{
		Result hr;

		const MsgNetCtrl* pNetCtrl = reinterpret_cast<const MsgNetCtrl*>(pHeader->GetPayloadPtr());
        const MsgNetCtrlConnect* pNetCtrlConnect = reinterpret_cast<const MsgNetCtrlConnect*>(pNetCtrl + 1);

		if (pHeader->MessageSize < (pHeader->GetHeaderSize() + sizeof(MsgNetCtrl) + sizeof(MsgNetCtrlConnect)))
		{
			SFLog(Net, Warning, "HackWarn : Invalid Connect packet CID:{0}, Addr:{1}, size:{2}", GetCID(), GetRemoteInfo().PeerAddress, pHeader->MessageSize);
			netCheck(CloseConnection("Invalid packet size during connect"));
			netCheck(ResultCode::UNEXPECTED);
		}

		switch (GetConnectionState())
		{
		case  ConnectionState::CONNECTING:
			if (pNetCtrlConnect->ProtocolVersion != SF_PROTOCOL_VERSION)
			{
				netCheck(SendNetCtrl(PACKET_NETCTRL_NACK, pHeader->GetSequence(), pHeader->MessageId));
                SFLog(Net, Warning, "Protocol version mismatch CID:{0}, RecvVer:{1}, Expected:{2}", GetCID(), pNetCtrlConnect->ProtocolVersion, SF_PROTOCOL_VERSION);
                OnConnectionResult(ResultCode::IO_PROTOCOL_VERSION_MISMATCH);
				netCheck(Disconnect("Protocol mismatch"));
				break;
			}

			netCheck(SendNetCtrl(PACKET_NETCTRL_ACK, (uint)GetLocalInfo().PeerClass, pHeader->MessageId));

			SFLog(Net, Debug3, "Recv Connecting CID({0}) : C:{1}, Ver:{2})", GetCID(), pNetCtrlConnect->Peer.PeerClass, pNetCtrlConnect->ProtocolVersion);
			GetConnection()->SetRemoteInfo(pNetCtrlConnect->Peer.PeerClass, pNetCtrlConnect->Peer.PeerID);

			// Set connection is succeeded and connected
			OnConnectionResult(ResultCode::SUCCESS);

            SFLog(Net, Info, "Connection connected CID({0}), State:{1}", GetCID(), GetConnectionState());
			break;
		case ConnectionState::CONNECTED:
			netCheck(SendNetCtrl(PACKET_NETCTRL_ACK, (uint)GetLocalInfo().PeerClass, pHeader->MessageId));
			break;
		default:
			break;
		}

		return hr;
	}

	Result ConnectionMessageAction_HandleDisconnect::Run(const MessageHeader* pHeader)
	{
		Result hr;

        netCheck(SendNetCtrl(PACKET_NETCTRL_ACK, pHeader->GetSequence(), pHeader->MessageId, GetLocalInfo().PeerID));
		SFLog(Net, Info, "Disconnect from remote CID:{0}", GetCID());
		netCheck(CloseConnection("Received disconnect"));

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


    Result ConnectionStateAction_WaitRW::Run()
    {
        Result hr;

        // TODO: select
        //GetConnection()->GetSocket()->

        return hr;
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

		if (!m_bSent && Util::TimeSince(GetNetCtrlTryTime()) > Const::CONNECTION_RETRY_TIME) // retry
		{
			UpdateNetCtrlTryTime();
			SFLog(Net, Debug2, "Send Connecting CID({0}) : C:{1}, V:{2})", GetCID(), GetLocalInfo().PeerClass, (uint32_t)SF_PROTOCOL_VERSION);
            netCheck(GetConnection()->SendNetCtrl(PACKET_NETCTRL_CONNECT, 0, {}));

            // With reliable stream socket we don't need to send multiple times
            // TODO: Socket reuse?
            if (GetConnection()->GetSocketType() == SocketType::Stream)
            {
                m_bSent = true;
            }
		}

		return hr;
	}

    ConnectionStateAction_Heartbeat::ConnectionStateAction_Heartbeat(DurationMS heartbeatRetry)
        : m_HeartbeatReceivedTime(Util::Time.GetTimeMs())
        , m_HeartbeatSendTime(Util::Time.GetTimeMs())
        , m_HeartbeatRetry(heartbeatRetry)
    {
    }

    void ConnectionStateAction_Heartbeat::OnHeartbeatPacket()
    {
        SFLog(Net, Debug4, "Connection heartbeat Received CID:{0}, sockType:{1}, remote:{2}", GetCID(), GetSocketType(), GetConnection()->GetRemoteInfo().PeerAddress);

        m_HeartbeatReceivedTime = Util::Time.GetTimeMs();
    }

    Result ConnectionStateAction_Heartbeat::Run()
    {
        Result hr;
        MessageID msgIDDummy;
        msgIDDummy.ID = PACKET_NETCTRL_NONE;

        DurationMS timeSinceLatestReceived = Util::TimeSince(m_HeartbeatReceivedTime);
        DurationMS timeSinceLatestSend = Util::TimeSince(m_HeartbeatSendTime);

        if (timeSinceLatestReceived > Const::HEARTBEAT_TIMEOUT) // connection time out
        {
            SFLog(Net, Debug, "Connection heartbeat Timeout CID:{0}, sockType:{1}, remote:{2}", GetCID(), GetSocketType(), GetConnection()->GetRemoteInfo().PeerAddress);
            netCheck(Disconnect("Connection TimeOut"));
            netCheck(CloseConnection("Heartbeat timeout"));
        }
        // send heartbeat
        else if (timeSinceLatestSend > m_HeartbeatRetry) // heartbeat time
        {
            SFLog(Net, Debug4, "Sending heartbeat CID:{0}, sockType:{1}, remote:{2}", GetCID(), GetSocketType(), GetConnection()->GetRemoteInfo().PeerAddress);
            m_HeartbeatSendTime = Util::Time.GetTimeMs();
            netCheck(GetConnection()->SendPending(PACKET_NETCTRL_HEARTBEAT, 0, msgIDDummy));
        }

        return hr;
    }


	Result ConnectionStateAction_StateTimeout::Run()
	{
		Result hr;

		if (m_StartTimeStamp == TimeStampMS(DurationMS(0)))
		{
			m_StartTimeStamp = Util::Time.GetRawTimeMs();
		}
		else
		{
			if (Util::TimeSince(m_StartTimeStamp) > m_Timeout)
			{
				SFLog(Net, Debug, "Disconnecting StateTimeout CID:{0}", GetCID());
				netCheck(CloseConnection("Disconnecting"));
			}
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
		MessageID msgIDDummy;
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
		Result hr;

		if (GetConnection()->GetSendBoost() <= 0)
			return hr;

		m_ReliableSyncTime = Util::Time.GetTimeMs();

		RecvMsgWindow2& recvWindow = GetConnection()->GetRecvReliableWindow();

		GetConnection()->DecSendBoost();

		netCheck(GetConnection()->SendSync(recvWindow.GetBaseSequence(), recvWindow.GetSyncMask()));

		return hr;
	}


    Result ConnectionStateAction_ValidateNetIOAdapter::Run()
    {
        Result hr;

        ConnectionMUDPClient* pConnection = static_cast<ConnectionMUDPClient*>(GetConnection());

        switch (GetConnectionState())
        {
        case ConnectionState::NONE:
        case ConnectionState::DISCONNECTING:
        case ConnectionState::DISCONNECTED:
        case ConnectionState::SLEEP:
            break;
        default:
            pConnection->GetNetIOAdapterManager().ValidateNetIOAdapter();
        }

        return hr;
    }

	Result ConnectionStateAction_SendReliableQueue::Run()
	{
		ScopeContext hr([this](Result hr) 
			{
				if (!hr.IsSuccess())
					Disconnect("Failed to send reliable packets");
			});
		SharedPointerT<MessageData> pIMsg;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();

		//assert(ThisThread::GetThreadID() ==  GetConnection()->GetRunningThreadID());

        SendMsgWindow& sendWindow = GetConnection()->GetSendReliableWindow();
        MsgQueue& sendGuaQueue = GetConnection()->GetSendGuaQueue();

		// make sure all acked messages are handled
		sendWindow.UpdateReleasedSequences();

		// Send guaranteed message process
		CounterType NumProc = sendWindow.GetRemainSequenceCount();
		CounterType uiNumPacket = sendGuaQueue.size();
		NumProc = Math::Min(NumProc, uiNumPacket);
		for (CounterType uiPacket = 0; uiPacket < NumProc; uiPacket++)
		{
			if (!sendGuaQueue.Dequeue(pIMsg))
				break;

			auto pMsgHeader = pIMsg->GetMessageHeader();
			auto msgID = pIMsg->GetMessageHeader()->MessageId;
			assert(msgID.IDs.Reliability);
			AssertRel(pMsgHeader->GetSequence() == 0);

			if (pMsgHeader->MessageSize > Const::INTER_PACKET_SIZE_MAX)
			{
				// They should be handled
				netCheck(ResultCode::IO_BADPACKET_TOOBIG);
			}
			else
			{
				// check sending window size
				netCheck(sendWindow.EnqueueMessage(ulTimeCur, pIMsg));
			}

			SFLog(Net, Debug4, "SENDENQReliable : CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
                msgID.GetSequence(),
                msgID,
				pMsgHeader->MessageSize);

			// don't bother network with might not be able to processed
			if ((sendWindow.GetHeadSequence() - sendWindow.GetBaseSequence()) < GetConnection()->GetMaxGuarantedRetryAtOnce())
			{
				netCheck(GetConnection()->SendRaw(pIMsg->GetMessageHeader()));
			}
			pIMsg = nullptr;
		}

		return hr;
	}


	Result ConnectionStateAction_SendReliableRetry::Run()
	{
		Result hr = ResultCode::SUCCESS;
		SendMsgWindow::WindowMessageData *pMessageElement = nullptr;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();
		auto sendBoost = GetConnection()->GetSendBoost();
		auto retryTimeout = DurationMS(Const::MUDP_SEND_RETRY_TIME);

		if (sendBoost > 0)
		{
			retryTimeout = DurationMS(Const::MUDP_SEND_RETRY_TIME_BOOSTED);
			GetConnection()->DecSendBoost();
		}

		auto& sendWindow = GetConnection()->GetSendReliableWindow();

		// Guaranteed retry
		//MutexScopeLock localLock(sendWindow.GetLock());// until ReleaseMsg( uint16_t uiSequence ) is thread safe, we need to lock the window
		uint uiMaxProcess = Math::Min(sendWindow.GetMsgCount(), GetConnection()->GetMaxGuarantedRetryAtOnce());
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

            SendMsgWindow::ItemState state = pMessageElement->State;
            if (state != SendMsgWindow::ItemState::Filled)
                continue;

			if (Util::TimeSince(pMessageElement->ulTimeStamp) <= retryTimeout)
				break;

            const MessageHeader* pHeader = pMessageElement->pMsg->GetMessageHeader();

			SFLog(Net, Debug2, "SENDReliableRetry : CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
				pHeader->GetSequence(),
				pHeader->MessageId,
				pHeader->MessageSize);

			pMessageElement->ulTimeStamp = ulTimeCur;

			// Creating new reference object will increase reference count of the message instance.
			// And more importantly, SendPending is taking reference of the variable and clear it when it done sending
			GetConnection()->SendRaw(pHeader);
			pMessageElement = nullptr;
		}

        // Now we can move window
        sendWindow.UpdateReleasedSequences();

		return hr;
	}

    Result ConnectionStateAction_FlushNet::Run()
    {
        Result hr;

        GetConnection()->SendFlush();

        return hr;
    }

} // namespace Net
} // namespace SF


