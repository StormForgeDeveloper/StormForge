////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network classes definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFProtocol.h"



namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packets for Network Control definitions
	//

	enum NetCtrlIDs
	{
		NetCtrlCode_None,
		NetCtrlCode_Ack,
		NetCtrlCode_Nack,
		NetCtrlCode_Heartbeat,
		NetCtrlCode_Disconnect,
		NetCtrlCode_Connect,
		NetCtrlCode_ConnectPeer,
		NetCtrlCode_SyncReliable,
		NetCtrlCode_TimeSync,
		NetCtrlCode_SequenceFrame,
		NetCtrlCode_TimeSyncRtn,

        // Not actual netctrl, but use it for convenience
        NetExt_QOS,
        NetExt_Stun,
		NetCtrlCode_Max,
	};

    static constexpr MessageID PACKET_NETCTRL_NONE = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_None);
    static constexpr MessageID PACKET_NETCTRL_ACK = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_Ack);
    static constexpr MessageID PACKET_NETCTRL_NACK = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_Nack);
    static constexpr MessageID PACKET_NETCTRL_HEARTBEAT = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_Heartbeat);
    static constexpr MessageID PACKET_NETCTRL_DISCONNECT = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_Disconnect);
    static constexpr MessageID PACKET_NETCTRL_CONNECT = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_Connect);
    static constexpr MessageID PACKET_NETCTRL_CONNECTPEER = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_ConnectPeer);
    static constexpr MessageID PACKET_NETCTRL_SYNCRELIABLE = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_SyncReliable);
    static constexpr MessageID PACKET_NETCTRL_TIMESYNC = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_TimeSync);
    static constexpr MessageID PACKET_NETCTRL_TIMESYNC_RTN = MessageID(EMessageType::NetCtrl, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_TimeSyncRtn);
	static constexpr MessageID PACKET_NETCTRL_SEQUENCE_FRAME   = MessageID(EMessageType::Event,      MSGTYPE_RELIABLE, MSGTYPE_NONE, MessageProtocol::None, NetCtrlCode_SequenceFrame);

    static constexpr MessageID PACKET_NETEXT_QOS = MessageID(EMessageType::Event, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetExt_QOS);
    static constexpr MessageID PACKET_NETEXT_STUN = MessageID(EMessageType::Event, MSGTYPE_NONE, MSGTYPE_NONE, MessageProtocol::None, NetExt_Stun);

} // namespace Net
} // namespace SF



