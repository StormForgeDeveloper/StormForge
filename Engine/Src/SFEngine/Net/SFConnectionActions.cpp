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
			GetConnection()->OnHeartBitPacket();

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
			case NetCtrlCode_HeartBit:
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


	Result ConnectionMessageAction_HandleHeartBit::Run(const Message::MessageHeader* pNetCtrl)
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
		
		Util::Time.UpdateUTCPeerOffset(serverTime);

		GetConnection()->OnTimeSyncRtn(roundTripTime);

		return hr;
	}


	Result ConnectionMessageAction_MUDPHandleSyncReliableServer::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;
		Result hrTem;

		ConnectionMUDP* pConnUDP = (ConnectionMUDP*)GetConnection();
		auto& sendReliableWindow = pConnUDP->GetSendReliableWindow();
		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);

		MutexScopeLock localLock(sendReliableWindow.GetLock());

		MsgMobileNetCtrlSync *pSyncCtrl = (MsgMobileNetCtrlSync*)pNetCtrl;
		if (pSyncCtrl->Length != sizeof(MsgMobileNetCtrlSync))
			netErr(ResultCode::IO_BADPACKET_SIZE);

		hrTem = sendReliableWindow.ReleaseMsg(pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask);
		if (hrTem)
		{
			SFLog(Net, Debug, "NetCtrl Recv SendMask : CID:{0}: mySeq:{1}, seq:{2}, mask:{3:X8}",
				GetCID(), sendReliableWindow.GetBaseSequence(), pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask);
		}
		else
		{
			SFLog(Net, Debug, "NetCtrl Recv SendMask Failed : CID:{0} mySeq:{1}, seq:{2}, mask:{3:X8}, hr={4:X8}",
				GetCID(), sendReliableWindow.GetBaseSequence(), pSyncCtrl->msgID.IDSeq.Sequence, pSyncCtrl->MessageMask, hrTem);
		}

		if (hrTem == Result(ResultCode::UNEXPECTED))
			CloseConnection("Unexpected send window sequence");

		netChk(hrTem);


		// poke send network only when there is something to send
		// Actually send proc also handles recv window
		if (GetConnection()->GetEventHandler() != nullptr /*&& (pConnUDP->GetSendGuaQueue().size() > 0 || sendReliableWindow.GetMsgCount() > 0)*/)
		{
			pConnUDP->SetSendSyncThisTick(true);
			hrTem = GetConnection()->GetEventHandler()->OnNetSyncMessage(pConnUDP);
			if (hrTem != ResultCode::NOT_IMPLEMENTED)
			{
				netChk(hrTem);
			}
		}
		else
		{
			// Threading problem
			//pConnUDP->UpdateSendQueue();
		}

	Proc_End:

		return hr;
	}


	Result ConnectionMessageAction_MUDPHandleSyncReliableClient::Run(const Message::MessageHeader* netCtrlMsg)
	{
		Result hr;
		Result hrTem;

		ConnectionMUDP* pConnUDP = (ConnectionMUDP*)GetConnection();
		auto& sendReliableWindow = pConnUDP->GetSendReliableWindow();
		const MsgMobileNetCtrl* pNetCtrl = (MsgMobileNetCtrl*)(netCtrlMsg);

		MutexScopeLock localLock(sendReliableWindow.GetLock());

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
		pConnUDP->SetSendSyncThisTick(true); // for regular ping. maybe I can get rid of this later

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



	Result ConnectionStateAction_SendConnect::Run()
	{
		Result hr;
		if (Util::TimeSince(GetNetCtrlTime()) > DurationMS(GetConnection()->GetConnectingTimeOut())) // connection time out
		{
			SFLog(Net, Info, "Connecting Timeout CID:{0}, ({1})", GetCID(), GetConnection()->GetConnectingTimeOut());
			netChk(CloseConnection("Connection time out"));
		}
		else if (Util::TimeSince(GetNetCtrlTryTime()) > Const::CONNECTION_RETRY_TIME) // retry
		{
			UpdateNetCtrlTryTime();
			SFLog(Net, Debug2, "Send Connecting CID({0}) : C:{1}, V:{2})", GetCID(), GetLocalInfo().PeerClass, (uint32_t)SF_PROTOCOL_VERSION);
			netChk(GetConnection()->SendNetCtrl(PACKET_NETCTRL_CONNECT, (uint)GetLocalInfo().PeerClass, Message::MessageID(SF_PROTOCOL_VERSION), GetLocalInfo().PeerID));
		}

	Proc_End:

		return hr;
	}


	Result ConnectionStateAction_SendHeartBit::Run()
	{
		Result hr;
		Message::MessageID msgIDDummy;
		msgIDDummy.ID = PACKET_NETCTRL_NONE;

		if (Util::TimeSince(GetNetCtrlTime()) > Const::HEARTBIT_TIMEOUT) // connection time out
		{
			SFLog(Net, Debug, "UDP Connection Timeout CID:{0}", GetCID());
			netChk(Disconnect("Connection TimeOut"));
			netChk(CloseConnection("Heart bit timeout"));
			goto Proc_End;
		}
		else if (Util::TimeSince(GetNetCtrlTryTime()) > GetConnection()->GetHeartbitTry()) // heart bit time
		{
			UpdateNetCtrlTryTime();
			netChk(GetConnection()->SendPending(PACKET_NETCTRL_HEARTBIT, 0, msgIDDummy));
		}


	Proc_End:

		return hr;
	}


	Result ConnectionStateAction_SendDisconnect::Run()
	{
		Result hr;
		Message::MessageID msgIDDummy;
		msgIDDummy.ID = PACKET_NETCTRL_NONE;

		if (Util::TimeSince(GetNetCtrlTime()) > Const::DISCONNECT_TIMEOUT) // connection time out
		{
			SFLog(Net, Debug, "Disconnecting Timeout CID:{0}", GetCID());
			netChk(CloseConnection("Disconnecting"));
		}
		else if (Util::TimeSince(GetNetCtrlTryTime()) > Const::DISCONNECT_RETRY_TIME) // retry
		{
			UpdateNetCtrlTryTime();
			netChk(GetConnection()->SendPending(PACKET_NETCTRL_DISCONNECT, 0, msgIDDummy));
		}

	Proc_End:

		return hr;
	}

} // namespace Net
} // namespace SF


