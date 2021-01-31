////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// S2C: Event for Player joined.
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerJoinS2CEvt()
{
 	return SF::Message::PlayInstance::PlayerJoinS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerJoinS2CEvt()


// S2C: Event for Player left.
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerLeftS2CEvt()
{
 	return SF::Message::PlayInstance::PlayerLeftS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerLeftS2CEvt()


// C2S: Play packet
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayPacketC2SEvt()
{
 	return SF::Message::PlayInstance::PlayPacketC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayPacketC2SEvt()


// S2C: New Player in get view
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceNewPlayerInViewS2CEvt()
{
 	return SF::Message::PlayInstance::NewPlayerInViewS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceNewPlayerInViewS2CEvt()


// S2C: Remove player from view
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceRemovePlayerFromViewS2CEvt()
{
 	return SF::Message::PlayInstance::RemovePlayerFromViewS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceRemovePlayerFromViewS2CEvt()


// C2S: Player Movement
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt()
{
 	return SF::Message::PlayInstance::PlayerMovementC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt()


// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerMovementS2CEvt()
{
 	return SF::Message::PlayInstance::PlayerMovementS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerMovementS2CEvt()


// Cmd: Create stream instance
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCreateStreamCmd()
{
 	return SF::Message::PlayInstance::CreateStreamCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCreateStreamCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCreateStreamRes()
{
 	return SF::Message::PlayInstance::CreateStreamRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCreateStreamRes()


// Cmd: Open stream instance
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceFindStreamCmd()
{
 	return SF::Message::PlayInstance::FindStreamCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceFindStreamCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceFindStreamRes()
{
 	return SF::Message::PlayInstance::FindStreamRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceFindStreamRes()


// Cmd: Delete stream instance
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceDeleteStreamCmd()
{
 	return SF::Message::PlayInstance::DeleteStreamCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceDeleteStreamCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceDeleteStreamRes()
{
 	return SF::Message::PlayInstance::DeleteStreamRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceDeleteStreamRes()


// Cmd: Get stream list
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceGetStreamListCmd()
{
 	return SF::Message::PlayInstance::GetStreamListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceGetStreamListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceGetStreamListRes()
{
 	return SF::Message::PlayInstance::GetStreamListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceGetStreamListRes()










