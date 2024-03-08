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
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/PlayInstanceMsgParsing.h"
#include "Protocol/PlayInstanceMsgClass.h"



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
 			// Cmd: Player Join request.
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::JoinPlayInstanceCmd::MID.ID,&Message::PlayInstance::JoinPlayInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::JoinPlayInstanceCmd::MID.ID,&Message::PlayInstance::JoinPlayInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::JoinPlayInstanceRes::MID.ID,&Message::PlayInstance::JoinPlayInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::JoinPlayInstanceRes::MID.ID,&Message::PlayInstance::JoinPlayInstanceRes::ParseMessageToMessageBase));
			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayerKickedS2CEvt::MID.ID,&Message::PlayInstance::PlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayerKickedS2CEvt::MID.ID,&Message::PlayInstance::PlayerKickedS2CEvt::ParseMessageToMessageBase));
			// C2S: Play packet
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayPacketC2SEvt::MID.ID,&Message::PlayInstance::PlayPacketC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayPacketC2SEvt::MID.ID,&Message::PlayInstance::PlayPacketC2SEvt::ParseMessageToMessageBase));
			// S2C: New actor in get view
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::NewActorInViewS2CEvt::MID.ID,&Message::PlayInstance::NewActorInViewS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::NewActorInViewS2CEvt::MID.ID,&Message::PlayInstance::NewActorInViewS2CEvt::ParseMessageToMessageBase));
			// S2C: Remove actor from view
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::RemoveActorFromViewS2CEvt::MID.ID,&Message::PlayInstance::RemoveActorFromViewS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::RemoveActorFromViewS2CEvt::MID.ID,&Message::PlayInstance::RemoveActorFromViewS2CEvt::ParseMessageToMessageBase));
			// C2S: Player Movement
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementC2SEvt::MID.ID,&Message::PlayInstance::PlayerMovementC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementC2SEvt::MID.ID,&Message::PlayInstance::PlayerMovementC2SEvt::ParseMessageToMessageBase));
			// S2C: Player Movement
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ActorMovementS2CEvt::MID.ID,&Message::PlayInstance::ActorMovementS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ActorMovementS2CEvt::MID.ID,&Message::PlayInstance::ActorMovementS2CEvt::ParseMessageToMessageBase));
			// S2C: Player Movement
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ActorMovementsS2CEvt::MID.ID,&Message::PlayInstance::ActorMovementsS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ActorMovementsS2CEvt::MID.ID,&Message::PlayInstance::ActorMovementsS2CEvt::ParseMessageToMessageBase));
			// S2C: Player state change
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::PlayerStateChangedS2CEvt::MID.ID,&Message::PlayInstance::PlayerStateChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::PlayerStateChangedS2CEvt::MID.ID,&Message::PlayInstance::PlayerStateChangedS2CEvt::ParseMessageToMessageBase));
			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ClientSyncReliableC2SEvt::MID.ID,&Message::PlayInstance::ClientSyncReliableC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ClientSyncReliableC2SEvt::MID.ID,&Message::PlayInstance::ClientSyncReliableC2SEvt::ParseMessageToMessageBase));
			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ClientSyncC2SEvt::MID.ID,&Message::PlayInstance::ClientSyncC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ClientSyncC2SEvt::MID.ID,&Message::PlayInstance::ClientSyncC2SEvt::ParseMessageToMessageBase));
			// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::SetCharacterPublicMessageCmd::MID.ID,&Message::PlayInstance::SetCharacterPublicMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::SetCharacterPublicMessageCmd::MID.ID,&Message::PlayInstance::SetCharacterPublicMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::SetCharacterPublicMessageRes::MID.ID,&Message::PlayInstance::SetCharacterPublicMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::SetCharacterPublicMessageRes::MID.ID,&Message::PlayInstance::SetCharacterPublicMessageRes::ParseMessageToMessageBase));
			// S2C: Character's private data has changed
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::MID.ID,&Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::MID.ID,&Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::ParseMessageToMessageBase));
			// S2C: Player public data has been changed
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CharacterPublicDataChangedS2CEvt::MID.ID,&Message::PlayInstance::CharacterPublicDataChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CharacterPublicDataChangedS2CEvt::MID.ID,&Message::PlayInstance::CharacterPublicDataChangedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Request WhiteboardSharing
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::RequestWhiteboardSharingCmd::MID.ID,&Message::PlayInstance::RequestWhiteboardSharingCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::RequestWhiteboardSharingCmd::MID.ID,&Message::PlayInstance::RequestWhiteboardSharingCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::RequestWhiteboardSharingRes::MID.ID,&Message::PlayInstance::RequestWhiteboardSharingRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::RequestWhiteboardSharingRes::MID.ID,&Message::PlayInstance::RequestWhiteboardSharingRes::ParseMessageToMessageBase));
			// Cmd: Accept WhiteboardSharing
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::AcceptWhiteboardSharingCmd::MID.ID,&Message::PlayInstance::AcceptWhiteboardSharingCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::AcceptWhiteboardSharingCmd::MID.ID,&Message::PlayInstance::AcceptWhiteboardSharingCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::AcceptWhiteboardSharingRes::MID.ID,&Message::PlayInstance::AcceptWhiteboardSharingRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::AcceptWhiteboardSharingRes::MID.ID,&Message::PlayInstance::AcceptWhiteboardSharingRes::ParseMessageToMessageBase));
			// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CloseWhiteboardSharingCmd::MID.ID,&Message::PlayInstance::CloseWhiteboardSharingCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CloseWhiteboardSharingCmd::MID.ID,&Message::PlayInstance::CloseWhiteboardSharingCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CloseWhiteboardSharingRes::MID.ID,&Message::PlayInstance::CloseWhiteboardSharingRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CloseWhiteboardSharingRes::MID.ID,&Message::PlayInstance::CloseWhiteboardSharingRes::ParseMessageToMessageBase));
			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::MID.ID,&Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::MID.ID,&Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::AddWhiteboardSharingLogEntryRes::MID.ID,&Message::PlayInstance::AddWhiteboardSharingLogEntryRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::AddWhiteboardSharingLogEntryRes::MID.ID,&Message::PlayInstance::AddWhiteboardSharingLogEntryRes::ParseMessageToMessageBase));
			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::MID.ID,&Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::MID.ID,&Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::MID.ID,&Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::MID.ID,&Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::ParseMessageToMessageBase));
			// Cmd: Update whiteboard log entry
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::MID.ID,&Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::MID.ID,&Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::MID.ID,&Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::MID.ID,&Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing has been requested
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing has been requested
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing has been started
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingStartedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingStartedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingStartedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingStartedS2CEvt::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing has been closed
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing new log entry has been added
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing new log entry has been removed
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::ParseMessageToMessageBase));
			// S2C: WhiteboardSharing new log entry has been updated
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::MID.ID,&Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Occupy map object
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectCmd::MID.ID,&Message::PlayInstance::OccupyMapObjectCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectCmd::MID.ID,&Message::PlayInstance::OccupyMapObjectCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectRes::MID.ID,&Message::PlayInstance::OccupyMapObjectRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectRes::MID.ID,&Message::PlayInstance::OccupyMapObjectRes::ParseMessageToMessageBase));
			// Cmd: Unoccupy map object
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectCmd::MID.ID,&Message::PlayInstance::UnoccupyMapObjectCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectCmd::MID.ID,&Message::PlayInstance::UnoccupyMapObjectCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectRes::MID.ID,&Message::PlayInstance::UnoccupyMapObjectRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectRes::MID.ID,&Message::PlayInstance::UnoccupyMapObjectRes::ParseMessageToMessageBase));
			// Cmd: Use map object
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectCmd::MID.ID,&Message::PlayInstance::UseMapObjectCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectCmd::MID.ID,&Message::PlayInstance::UseMapObjectCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectRes::MID.ID,&Message::PlayInstance::UseMapObjectRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectRes::MID.ID,&Message::PlayInstance::UseMapObjectRes::ParseMessageToMessageBase));
			// Cmd: Send zone chatting
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ZoneChatCmd::MID.ID,&Message::PlayInstance::ZoneChatCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ZoneChatCmd::MID.ID,&Message::PlayInstance::ZoneChatCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ZoneChatRes::MID.ID,&Message::PlayInstance::ZoneChatRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ZoneChatRes::MID.ID,&Message::PlayInstance::ZoneChatRes::ParseMessageToMessageBase));
			// S2C: Player state change
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::ZoneChatS2CEvt::MID.ID,&Message::PlayInstance::ZoneChatS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::ZoneChatS2CEvt::MID.ID,&Message::PlayInstance::ZoneChatS2CEvt::ParseMessageToMessageBase));
			// S2C: Effect modifier initial sync
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::LevelUpS2CEvt::MID.ID,&Message::PlayInstance::LevelUpS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::LevelUpS2CEvt::MID.ID,&Message::PlayInstance::LevelUpS2CEvt::ParseMessageToMessageBase));
			// Cmd: To call general functionality
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CallFunctionCmd::MID.ID,&Message::PlayInstance::CallFunctionCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CallFunctionCmd::MID.ID,&Message::PlayInstance::CallFunctionCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CallFunctionRes::MID.ID,&Message::PlayInstance::CallFunctionRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CallFunctionRes::MID.ID,&Message::PlayInstance::CallFunctionRes::ParseMessageToMessageBase));
			// C2S: Send coded voice data to server
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::SendVoiceDataC2SEvt::MID.ID,&Message::PlayInstance::SendVoiceDataC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::SendVoiceDataC2SEvt::MID.ID,&Message::PlayInstance::SendVoiceDataC2SEvt::ParseMessageToMessageBase));
			// S2C: Voice data
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::VoiceDataS2CEvt::MID.ID,&Message::PlayInstance::VoiceDataS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::VoiceDataS2CEvt::MID.ID,&Message::PlayInstance::VoiceDataS2CEvt::ParseMessageToMessageBase));
			// Cmd: Create stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CreateStreamCmd::MID.ID,&Message::PlayInstance::CreateStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CreateStreamCmd::MID.ID,&Message::PlayInstance::CreateStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::CreateStreamRes::MID.ID,&Message::PlayInstance::CreateStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::CreateStreamRes::MID.ID,&Message::PlayInstance::CreateStreamRes::ParseMessageToMessageBase));
			// Cmd: Open stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::FindStreamCmd::MID.ID,&Message::PlayInstance::FindStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::FindStreamCmd::MID.ID,&Message::PlayInstance::FindStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::FindStreamRes::MID.ID,&Message::PlayInstance::FindStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::FindStreamRes::MID.ID,&Message::PlayInstance::FindStreamRes::ParseMessageToMessageBase));
			// Cmd: Delete stream instance
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamCmd::MID.ID,&Message::PlayInstance::DeleteStreamCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamCmd::MID.ID,&Message::PlayInstance::DeleteStreamCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamRes::MID.ID,&Message::PlayInstance::DeleteStreamRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::DeleteStreamRes::MID.ID,&Message::PlayInstance::DeleteStreamRes::ParseMessageToMessageBase));
			// Cmd: Get stream list
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::GetStreamListCmd::MID.ID,&Message::PlayInstance::GetStreamListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::GetStreamListCmd::MID.ID,&Message::PlayInstance::GetStreamListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::PlayInstance::GetStreamListRes::MID.ID,&Message::PlayInstance::GetStreamListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::PlayInstance::GetStreamListRes::MID.ID,&Message::PlayInstance::GetStreamListRes::ParseMessageToMessageBase));
		}; // void RegisterParserPlayInstance()


	}; // namespace Protocol
}; // namespace SF


