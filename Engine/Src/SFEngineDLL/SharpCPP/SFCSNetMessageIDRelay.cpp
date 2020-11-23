////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Relay Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/RelayMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// C2S: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetMessageID_RelayJoinRelayInstanceC2SEvt()
{
 	return SF::Message::Relay::JoinRelayInstanceC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayJoinRelayInstanceC2SEvt()


// S2C: Event for joined player
SFDLL_EXPORT int  CSSFNetMessageID_RelayJoinRelayInstanceResS2CEvt()
{
 	return SF::Message::Relay::JoinRelayInstanceResS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayJoinRelayInstanceResS2CEvt()


// C2S: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetMessageID_RelayLeaveRelayInstanceC2SEvt()
{
 	return SF::Message::Relay::LeaveRelayInstanceC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayLeaveRelayInstanceC2SEvt()


// S2C: Event for Player joined.
SFDLL_EXPORT int  CSSFNetMessageID_RelayPlayerJoinS2CEvt()
{
 	return SF::Message::Relay::PlayerJoinS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayPlayerJoinS2CEvt()


// S2C: Event for Player left.
SFDLL_EXPORT int  CSSFNetMessageID_RelayPlayerLeftS2CEvt()
{
 	return SF::Message::Relay::PlayerLeftS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayPlayerLeftS2CEvt()


// C2S: Relay packet
SFDLL_EXPORT int  CSSFNetMessageID_RelayRelayPacketC2SEvt()
{
 	return SF::Message::Relay::RelayPacketC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayRelayPacketC2SEvt()


// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetMessageID_RelayCreateStreamCmd()
{
 	return SF::Message::Relay::CreateStreamCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayCreateStreamCmd()


SFDLL_EXPORT int  CSSFNetMessageID_RelayCreateStreamRes()
{
 	return SF::Message::Relay::CreateStreamRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayCreateStreamRes()


// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetMessageID_RelayFindStreamCmd()
{
 	return SF::Message::Relay::FindStreamCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayFindStreamCmd()


SFDLL_EXPORT int  CSSFNetMessageID_RelayFindStreamRes()
{
 	return SF::Message::Relay::FindStreamRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayFindStreamRes()


// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetMessageID_RelayDeleteStreamCmd()
{
 	return SF::Message::Relay::DeleteStreamCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayDeleteStreamCmd()


SFDLL_EXPORT int  CSSFNetMessageID_RelayDeleteStreamRes()
{
 	return SF::Message::Relay::DeleteStreamRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayDeleteStreamRes()


// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetMessageID_RelayGetStreamListCmd()
{
 	return SF::Message::Relay::GetStreamListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayGetStreamListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_RelayGetStreamListRes()
{
 	return SF::Message::Relay::GetStreamListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_RelayGetStreamListRes()










