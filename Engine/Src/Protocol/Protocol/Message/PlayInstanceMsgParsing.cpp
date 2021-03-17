////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : Generated
// 
// Description : PlayInstance Message parsing implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/PlayInstanceMsgParsing.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 
		///////////////////////////////////////////////////////////////
		// PlayInstance message parser mapping

		extern std::unordered_map<uint32_t,HandleParseMessageTo> MessageParseToVariableMap;
		extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

		void RegisterParserPlayInstance()
		{
 			// Cmd: Event for Player Join request.
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::JoinGameInstanceCmd::MID.IDSeq.MsgID,&Message::PlayInstance::JoinGameInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::JoinGameInstanceCmd::MID.IDSeq.MsgID,&Message::PlayInstance::JoinGameInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::JoinGameInstanceRes::MID.IDSeq.MsgID,&Message::PlayInstance::JoinGameInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::JoinGameInstanceRes::MID.IDSeq.MsgID,&Message::PlayInstance::JoinGameInstanceRes::ParseMessageToMessageBase));
			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerKickedS2CEvt::ParseMessageToMessageBase));
			// C2S: Play packet
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayPacketC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayPacketC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayPacketC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayPacketC2SEvt::ParseMessageToMessageBase));
			// S2C: New Player in get view
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::NewPlayerInViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::NewPlayerInViewS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::NewPlayerInViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::NewPlayerInViewS2CEvt::ParseMessageToMessageBase));
			// S2C: Remove player from view
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::RemovePlayerFromViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::RemovePlayerFromViewS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::RemovePlayerFromViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::RemovePlayerFromViewS2CEvt::ParseMessageToMessageBase));
			// C2S: Player Movement
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementC2SEvt::ParseMessageToMessageBase));
			// S2C: Player Movement
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementS2CEvt::ParseMessageToMessageBase));
			// Cmd: Occupy map object
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectRes::ParseMessageToMessageBase));
			// Cmd: Unoccupy map object
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectRes::ParseMessageToMessageBase));
			// Cmd: Use map object
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectRes::ParseMessageToMessageBase));
			// Cmd: Havest area
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::HarvestAreaCmd::MID.IDSeq.MsgID,&Message::PlayInstance::HarvestAreaCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::HarvestAreaCmd::MID.IDSeq.MsgID,&Message::PlayInstance::HarvestAreaCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::HarvestAreaRes::MID.IDSeq.MsgID,&Message::PlayInstance::HarvestAreaRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::HarvestAreaRes::MID.IDSeq.MsgID,&Message::PlayInstance::HarvestAreaRes::ParseMessageToMessageBase));
			// Cmd: Create stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CreateStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::CreateStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CreateStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::CreateStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CreateStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::CreateStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CreateStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::CreateStreamRes::ParseMessageToMessageBase));
			// Cmd: Open stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::FindStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::FindStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::FindStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::FindStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::FindStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::FindStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::FindStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::FindStreamRes::ParseMessageToMessageBase));
			// Cmd: Delete stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::DeleteStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamCmd::MID.IDSeq.MsgID,&Message::PlayInstance::DeleteStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::DeleteStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamRes::MID.IDSeq.MsgID,&Message::PlayInstance::DeleteStreamRes::ParseMessageToMessageBase));
			// Cmd: Get stream list
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::GetStreamListCmd::MID.IDSeq.MsgID,&Message::PlayInstance::GetStreamListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::GetStreamListCmd::MID.IDSeq.MsgID,&Message::PlayInstance::GetStreamListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::GetStreamListRes::MID.IDSeq.MsgID,&Message::PlayInstance::GetStreamListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::GetStreamListRes::MID.IDSeq.MsgID,&Message::PlayInstance::GetStreamListRes::ParseMessageToMessageBase));
		}; // void RegisterParserPlayInstance()


	}; // namespace Protocol
}; // namespace SF


