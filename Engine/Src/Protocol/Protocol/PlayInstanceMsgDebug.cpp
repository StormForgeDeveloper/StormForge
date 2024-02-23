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
#include "Protocol/PlayInstanceMsgDebug.h"
#include "Protocol/PlayInstanceMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// PlayInstance Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTracePlayInstance()
		{
 			// Cmd: Player Join request.
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::JoinPlayInstanceCmd::MID.IDSeq.MsgID,&Message::PlayInstance::JoinPlayInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::JoinPlayInstanceRes::MID.IDSeq.MsgID,&Message::PlayInstance::JoinPlayInstanceRes::TraceOut));
			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerKickedS2CEvt::TraceOut));
			// C2S: Play packet
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayPacketC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayPacketC2SEvt::TraceOut));
			// S2C: New actor in get view
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::NewActorInViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::NewActorInViewS2CEvt::TraceOut));
			// S2C: Remove actor from view
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::RemoveActorFromViewS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::RemoveActorFromViewS2CEvt::TraceOut));
			// C2S: Player Movement
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayerMovementC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerMovementC2SEvt::TraceOut));
			// S2C: Player Movement
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ActorMovementS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::ActorMovementS2CEvt::TraceOut));
			// S2C: Player Movement
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ActorMovementsS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::ActorMovementsS2CEvt::TraceOut));
			// S2C: Player state change
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::PlayerStateChangedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::PlayerStateChangedS2CEvt::TraceOut));
			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ClientSyncReliableC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::ClientSyncReliableC2SEvt::TraceOut));
			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ClientSyncC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::ClientSyncC2SEvt::TraceOut));
			// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::SetCharacterPublicMessageCmd::MID.IDSeq.MsgID,&Message::PlayInstance::SetCharacterPublicMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::SetCharacterPublicMessageRes::MID.IDSeq.MsgID,&Message::PlayInstance::SetCharacterPublicMessageRes::TraceOut));
			// S2C: Character's private data has changed
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::CharacterPrivateDataChangedS2CEvt::TraceOut));
			// S2C: Player public data has been changed
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CharacterPublicDataChangedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::CharacterPublicDataChangedS2CEvt::TraceOut));
			// Cmd: Request WhiteboardSharing
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::RequestWhiteboardSharingCmd::MID.IDSeq.MsgID,&Message::PlayInstance::RequestWhiteboardSharingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::RequestWhiteboardSharingRes::MID.IDSeq.MsgID,&Message::PlayInstance::RequestWhiteboardSharingRes::TraceOut));
			// Cmd: Accept WhiteboardSharing
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::AcceptWhiteboardSharingCmd::MID.IDSeq.MsgID,&Message::PlayInstance::AcceptWhiteboardSharingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::AcceptWhiteboardSharingRes::MID.IDSeq.MsgID,&Message::PlayInstance::AcceptWhiteboardSharingRes::TraceOut));
			// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CloseWhiteboardSharingCmd::MID.IDSeq.MsgID,&Message::PlayInstance::CloseWhiteboardSharingCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CloseWhiteboardSharingRes::MID.IDSeq.MsgID,&Message::PlayInstance::CloseWhiteboardSharingRes::TraceOut));
			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::MID.IDSeq.MsgID,&Message::PlayInstance::AddWhiteboardSharingLogEntryCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::AddWhiteboardSharingLogEntryRes::MID.IDSeq.MsgID,&Message::PlayInstance::AddWhiteboardSharingLogEntryRes::TraceOut));
			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UpdateWhiteboardSharingLogEntryCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::MID.IDSeq.MsgID,&Message::PlayInstance::UpdateWhiteboardSharingLogEntryRes::TraceOut));
			// Cmd: Update whiteboard log entry
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::MID.IDSeq.MsgID,&Message::PlayInstance::RemoveWhiteboardSharingLogEntryCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::MID.IDSeq.MsgID,&Message::PlayInstance::RemoveWhiteboardSharingLogEntryRes::TraceOut));
			// S2C: WhiteboardSharing has been requested
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingRequestedS2CEvt::TraceOut));
			// S2C: WhiteboardSharing has been requested
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingRejectedS2CEvt::TraceOut));
			// S2C: WhiteboardSharing has been started
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingStartedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingStartedS2CEvt::TraceOut));
			// S2C: WhiteboardSharing has been closed
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingHasClosedS2CEvt::TraceOut));
			// S2C: WhiteboardSharing new log entry has been added
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingNewLogEntryAddedS2CEvt::TraceOut));
			// S2C: WhiteboardSharing new log entry has been removed
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingNewLogEntryRemovedS2CEvt::TraceOut));
			// S2C: WhiteboardSharing new log entry has been updated
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::WhiteboardSharingNewLogEntryUpdatedS2CEvt::TraceOut));
			// Cmd: Occupy map object
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::OccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::OccupyMapObjectRes::TraceOut));
			// Cmd: Unoccupy map object
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UnoccupyMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UnoccupyMapObjectRes::TraceOut));
			// Cmd: Use map object
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectCmd::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::UseMapObjectRes::MID.IDSeq.MsgID,&Message::PlayInstance::UseMapObjectRes::TraceOut));
			// Cmd: Send zone chatting
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ZoneChatCmd::MID.IDSeq.MsgID,&Message::PlayInstance::ZoneChatCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ZoneChatRes::MID.IDSeq.MsgID,&Message::PlayInstance::ZoneChatRes::TraceOut));
			// S2C: Player state change
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::ZoneChatS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::ZoneChatS2CEvt::TraceOut));
			// S2C: Effect modifier initial sync
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::LevelUpS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::LevelUpS2CEvt::TraceOut));
			// Cmd: To call general functionality
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CallFunctionCmd::MID.IDSeq.MsgID,&Message::PlayInstance::CallFunctionCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::CallFunctionRes::MID.IDSeq.MsgID,&Message::PlayInstance::CallFunctionRes::TraceOut));
			// C2S: Send coded voice data to server
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::SendVoiceDataC2SEvt::MID.IDSeq.MsgID,&Message::PlayInstance::SendVoiceDataC2SEvt::TraceOut));
			// S2C: Voice data
			MessageDebugTraceMap.insert(std::make_pair(Message::PlayInstance::VoiceDataS2CEvt::MID.IDSeq.MsgID,&Message::PlayInstance::VoiceDataS2CEvt::TraceOut));
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


