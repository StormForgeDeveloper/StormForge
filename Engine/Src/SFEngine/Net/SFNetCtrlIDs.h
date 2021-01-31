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

	static const Message::MessageID PACKET_NETCTRL_NONE				= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_None);
	static const Message::MessageID PACKET_NETCTRL_ACK				= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Ack);
	static const Message::MessageID PACKET_NETCTRL_NACK				= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Nack);
	static const Message::MessageID PACKET_NETCTRL_HEARTBEAT		= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Heartbeat);
	static const Message::MessageID PACKET_NETCTRL_DISCONNECT		= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Disconnect);
	static const Message::MessageID PACKET_NETCTRL_CONNECT			= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_Connect);
	static const Message::MessageID PACKET_NETCTRL_CONNECTPEER		= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_ConnectPeer);
	static const Message::MessageID PACKET_NETCTRL_SYNCRELIABLE		= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_SyncReliable);
	static const Message::MessageID PACKET_NETCTRL_TIMESYNC			= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,	 Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_TimeSync);
	static const Message::MessageID PACKET_NETCTRL_TIMESYNC_RTN		= Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_NONE,		Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_TimeSyncRtn);
	static const Message::MessageID PACKET_NETCTRL_SEQUENCE_FRAME   = Message::MessageID(Message::MSGTYPE_NETCONTROL, Message::MSGTYPE_RELIABLE, Message::MSGTYPE_MOBILE, PROTOCOLID_NONE, NetCtrlCode_SequenceFrame);


} // namespace Net
} // namespace SF



