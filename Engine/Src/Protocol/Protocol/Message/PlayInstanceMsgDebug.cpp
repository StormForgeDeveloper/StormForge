////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : PlayInstance Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/PlayInstanceMsgDebug.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// PlayInstance Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTracePlayInstance()
		{
 			// Cmd: Event for Player Join request.
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::JoinGameInstanceCmd::MID.IDSeq.MsgID,&Message::PlayInstance::JoinGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::JoinGameInstanceRes::MID.IDSeq.MsgID,&Message::PlayInstance::JoinGameInstanceRes::TraceOut));
			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerKickedS2CEvt::TraceOut));
			// C2S: Play packet
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayPacketC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayPacketC2SEvt::TraceOut));
			// S2C: New Player in get view
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::NewPlayerInViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::NewPlayerInViewS2CEvt::TraceOut));
			// S2C: Remove player from view
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::RemovePlayerFromViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::RemovePlayerFromViewS2CEvt::TraceOut));
			// C2S: Player Movement
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementC2SEvt::TraceOut));
			// S2C: Player Movement
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementS2CEvt::TraceOut));
			// Cmd: Occupy map object
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectRes::TraceOut));
			// Cmd: Unoccupy map object
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectRes::TraceOut));
			// Cmd: Use map object
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectRes::TraceOut));
			// Cmd: Create stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CreateStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::CreateStreamCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CreateStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::CreateStreamRes::TraceOut));
			// Cmd: Open stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::FindStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::FindStreamCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::FindStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::FindStreamRes::TraceOut));
			// Cmd: Delete stream instance
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::DeleteStreamCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::DeleteStreamRes::TraceOut));
			// Cmd: Get stream list
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::GetStreamListCmd::MID.IDSeq.MsgID,&Message::PlayInstance::GetStreamListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::GetStreamListRes::MID.IDSeq.MsgID,&Message::PlayInstance::GetStreamListRes::TraceOut));
		}; // void RegisterDebugTracePlayInstance()


	}; // namespace Protocol
}; // namespace SF


