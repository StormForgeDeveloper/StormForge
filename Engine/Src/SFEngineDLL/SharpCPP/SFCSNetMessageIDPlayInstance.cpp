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
#include "SharpCPP/SFCSUtil.h"



using namespace SF;


// Cmd: Player Join request.
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinPlayInstanceCmd()
{
 	return SF::Message::PlayInstance::JoinPlayInstanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinPlayInstanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinPlayInstanceRes()
{
 	return SF::Message::PlayInstance::JoinPlayInstanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceJoinPlayInstanceRes()


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


// S2C: New actor in get view
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceNewActorInViewS2CEvt()
{
 	return SF::Message::PlayInstance::NewActorInViewS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceNewActorInViewS2CEvt()


// S2C: Remove actor from view
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceRemoveActorFromViewS2CEvt()
{
 	return SF::Message::PlayInstance::RemoveActorFromViewS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceRemoveActorFromViewS2CEvt()


// C2S: Player Movement
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt()
{
 	return SF::Message::PlayInstance::PlayerMovementC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt()


// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceActorMovementS2CEvt()
{
 	return SF::Message::PlayInstance::ActorMovementS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceActorMovementS2CEvt()


// S2C: Player Movement
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceActorMovementsS2CEvt()
{
 	return SF::Message::PlayInstance::ActorMovementsS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceActorMovementsS2CEvt()


// S2C: Player state change
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerStateChangedS2CEvt()
{
 	return SF::Message::PlayInstance::PlayerStateChangedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstancePlayerStateChangedS2CEvt()


// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceClientSyncReliableC2SEvt()
{
 	return SF::Message::PlayInstance::ClientSyncReliableC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceClientSyncReliableC2SEvt()


// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceClientSyncC2SEvt()
{
 	return SF::Message::PlayInstance::ClientSyncC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceClientSyncC2SEvt()


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


// Cmd: Send zone chatting
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceZoneChatCmd()
{
 	return SF::Message::PlayInstance::ZoneChatCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceZoneChatCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceZoneChatRes()
{
 	return SF::Message::PlayInstance::ZoneChatRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceZoneChatRes()


// S2C: Player state change
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceZoneChatS2CEvt()
{
 	return SF::Message::PlayInstance::ZoneChatS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceZoneChatS2CEvt()


// S2C: Effect modifier initial sync
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceLevelUpS2CEvt()
{
 	return SF::Message::PlayInstance::LevelUpS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceLevelUpS2CEvt()


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


// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCallFunctionCmd()
{
 	return SF::Message::PlayInstance::CallFunctionCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCallFunctionCmd()


SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCallFunctionRes()
{
 	return SF::Message::PlayInstance::CallFunctionRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_PlayInstanceCallFunctionRes()










