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
#include "Protocol/PlayInstanceMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// Cmd: Event for Player Join request.
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd()
{
 	return SF::Message::PlayInstance::JoinGameInstanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinGameInstanceRes()
{
 	return SF::Message::PlayInstance::JoinGameInstanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinGameInstanceRes()


// S2C: Player kicked event. this event will be broadcasted when a player kicked.
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt()
{
 	return SF::Message::PlayInstance::PlayerKickedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt()


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


// Cmd: Occupy map object
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceOccupyMapObjectCmd()
{
 	return SF::Message::PlayInstance::OccupyMapObjectCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceOccupyMapObjectCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceOccupyMapObjectRes()
{
 	return SF::Message::PlayInstance::OccupyMapObjectRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceOccupyMapObjectRes()


// Cmd: Unoccupy map object
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUnoccupyMapObjectCmd()
{
 	return SF::Message::PlayInstance::UnoccupyMapObjectCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUnoccupyMapObjectCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUnoccupyMapObjectRes()
{
 	return SF::Message::PlayInstance::UnoccupyMapObjectRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUnoccupyMapObjectRes()


// Cmd: Use map object
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUseMapObjectCmd()
{
 	return SF::Message::PlayInstance::UseMapObjectCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUseMapObjectCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUseMapObjectRes()
{
 	return SF::Message::PlayInstance::UseMapObjectRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceUseMapObjectRes()


// Cmd: Havest area
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceHarvestAreaCmd()
{
 	return SF::Message::PlayInstance::HarvestAreaCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceHarvestAreaCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceHarvestAreaRes()
{
 	return SF::Message::PlayInstance::HarvestAreaRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceHarvestAreaRes()


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










