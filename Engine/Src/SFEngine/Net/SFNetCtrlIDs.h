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
#include "Protocol/SFProtocol.h"



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

    static constexpr MessageID PACKET_NETCTRL_NONE = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_None);
    static constexpr MessageID PACKET_NETCTRL_ACK = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_Ack);
    static constexpr MessageID PACKET_NETCTRL_NACK = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_Nack);
    static constexpr MessageID PACKET_NETCTRL_HEARTBEAT = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_Heartbeat);
    static constexpr MessageID PACKET_NETCTRL_DISCONNECT = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_Disconnect);
    static constexpr MessageID PACKET_NETCTRL_CONNECT = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_Connect);
    static constexpr MessageID PACKET_NETCTRL_CONNECTPEER = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_ConnectPeer);
    static constexpr MessageID PACKET_NETCTRL_SYNCRELIABLE = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_SyncReliable);
    static constexpr MessageID PACKET_NETCTRL_TIMESYNC = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_TimeSync);
    static constexpr MessageID PACKET_NETCTRL_TIMESYNC_RTN = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_TimeSyncRtn);
	static constexpr MessageID PACKET_NETCTRL_SEQUENCE_FRAME   = MessageID(MSGTYPE_EVENT,      MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_NONE, NetCtrlCode_SequenceFrame);

    static constexpr MessageID PACKET_NETEXT_QOS = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetExt_QOS);
    static constexpr MessageID PACKET_NETEXT_STUN = MessageID(MSGTYPE_EVENT, MSGTYPE_NONE, MSGTYPE_NONE, PROTOCOLID_NONE, NetExt_Stun);

} // namespace Net
} // namespace SF



