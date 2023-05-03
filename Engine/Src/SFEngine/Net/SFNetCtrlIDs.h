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
	//	Network Packetes for Network Control definitions
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
		NetCtrlCode_Max,
	};

    static const MessageID PACKET_NETCTRL_NONE = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_None);
    static const MessageID PACKET_NETCTRL_ACK = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Ack);
    static const MessageID PACKET_NETCTRL_NACK = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Nack);
    static const MessageID PACKET_NETCTRL_HEARTBEAT = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Heartbeat);
    static const MessageID PACKET_NETCTRL_DISCONNECT = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Disconnect);
    static const MessageID PACKET_NETCTRL_CONNECT = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Connect);
    static const MessageID PACKET_NETCTRL_CONNECTPEER = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_ConnectPeer);
    static const MessageID PACKET_NETCTRL_SYNCRELIABLE = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_SyncReliable);
    static const MessageID PACKET_NETCTRL_TIMESYNC = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_TimeSync);
    static const MessageID PACKET_NETCTRL_TIMESYNC_RTN = MessageID(MSGTYPE_NETCONTROL, MSGTYPE_NONE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_TimeSyncRtn);
	static const MessageID PACKET_NETCTRL_SEQUENCE_FRAME   = MessageID(MSGTYPE_EVENT,      MSGTYPE_RELIABLE, MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_SequenceFrame);


} // namespace Net
} // namespace SF



