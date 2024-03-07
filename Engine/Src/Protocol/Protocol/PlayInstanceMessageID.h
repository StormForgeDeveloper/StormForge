////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Message IDs
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Net/SFMessage.h"
#include "SFProtocol.h"


namespace SF
{
 	namespace Message
	{
 		namespace PlayInstance
		{
 

			// Cmd: Player Join request.
			constexpr MessageID MID_JoinPlayInstanceCmd(MessageType::Command,1,MessageProtocol::PlayInstance,0);
			constexpr MessageID MID_JoinPlayInstanceRes(MessageType::Result,1,MessageProtocol::PlayInstance,0);

			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			constexpr MessageID MID_PlayerKickedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,1);
			// C2S: Play packet
			constexpr MessageID MID_PlayPacketC2SEvt(MessageType::Event,0,MessageProtocol::PlayInstance,2);
			// S2C: New actor in get view
			constexpr MessageID MID_NewActorInViewS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,3);
			// S2C: Remove actor from view
			constexpr MessageID MID_RemoveActorFromViewS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,4);
			// C2S: Player Movement
			constexpr MessageID MID_PlayerMovementC2SEvt(MessageType::Event,0,MessageProtocol::PlayInstance,5);
			// S2C: Player Movement
			constexpr MessageID MID_ActorMovementS2CEvt(MessageType::Event,0,MessageProtocol::PlayInstance,6);
			// S2C: Player Movement
			constexpr MessageID MID_ActorMovementsS2CEvt(MessageType::Event,0,MessageProtocol::PlayInstance,7);
			// S2C: Player state change
			constexpr MessageID MID_PlayerStateChangedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,8);
			// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			constexpr MessageID MID_ClientSyncReliableC2SEvt(MessageType::Event,1,MessageProtocol::PlayInstance,9);
			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			constexpr MessageID MID_ClientSyncC2SEvt(MessageType::Event,0,MessageProtocol::PlayInstance,10);
			// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
			constexpr MessageID MID_SetCharacterPublicMessageCmd(MessageType::Command,1,MessageProtocol::PlayInstance,11);
			constexpr MessageID MID_SetCharacterPublicMessageRes(MessageType::Result,1,MessageProtocol::PlayInstance,11);

			// S2C: Character's private data has changed
			constexpr MessageID MID_CharacterPrivateDataChangedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,12);
			// S2C: Player public data has been changed
			constexpr MessageID MID_CharacterPublicDataChangedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,13);
			// Cmd: Request WhiteboardSharing
			constexpr MessageID MID_RequestWhiteboardSharingCmd(MessageType::Command,1,MessageProtocol::PlayInstance,14);
			constexpr MessageID MID_RequestWhiteboardSharingRes(MessageType::Result,1,MessageProtocol::PlayInstance,14);

			// Cmd: Accept WhiteboardSharing
			constexpr MessageID MID_AcceptWhiteboardSharingCmd(MessageType::Command,1,MessageProtocol::PlayInstance,15);
			constexpr MessageID MID_AcceptWhiteboardSharingRes(MessageType::Result,1,MessageProtocol::PlayInstance,15);

			// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
			constexpr MessageID MID_CloseWhiteboardSharingCmd(MessageType::Command,1,MessageProtocol::PlayInstance,16);
			constexpr MessageID MID_CloseWhiteboardSharingRes(MessageType::Result,1,MessageProtocol::PlayInstance,16);

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			constexpr MessageID MID_AddWhiteboardSharingLogEntryCmd(MessageType::Command,1,MessageProtocol::PlayInstance,17);
			constexpr MessageID MID_AddWhiteboardSharingLogEntryRes(MessageType::Result,1,MessageProtocol::PlayInstance,17);

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			constexpr MessageID MID_UpdateWhiteboardSharingLogEntryCmd(MessageType::Command,1,MessageProtocol::PlayInstance,18);
			constexpr MessageID MID_UpdateWhiteboardSharingLogEntryRes(MessageType::Result,1,MessageProtocol::PlayInstance,18);

			// Cmd: Update whiteboard log entry
			constexpr MessageID MID_RemoveWhiteboardSharingLogEntryCmd(MessageType::Command,1,MessageProtocol::PlayInstance,19);
			constexpr MessageID MID_RemoveWhiteboardSharingLogEntryRes(MessageType::Result,1,MessageProtocol::PlayInstance,19);

			// S2C: WhiteboardSharing has been requested
			constexpr MessageID MID_WhiteboardSharingRequestedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,20);
			// S2C: WhiteboardSharing has been requested
			constexpr MessageID MID_WhiteboardSharingRejectedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,21);
			// S2C: WhiteboardSharing has been started
			constexpr MessageID MID_WhiteboardSharingStartedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,22);
			// S2C: WhiteboardSharing has been closed
			constexpr MessageID MID_WhiteboardSharingHasClosedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,23);
			// S2C: WhiteboardSharing new log entry has been added
			constexpr MessageID MID_WhiteboardSharingNewLogEntryAddedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,24);
			// S2C: WhiteboardSharing new log entry has been removed
			constexpr MessageID MID_WhiteboardSharingNewLogEntryRemovedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,25);
			// S2C: WhiteboardSharing new log entry has been updated
			constexpr MessageID MID_WhiteboardSharingNewLogEntryUpdatedS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,26);
			// Cmd: Occupy map object
			constexpr MessageID MID_OccupyMapObjectCmd(MessageType::Command,1,MessageProtocol::PlayInstance,27);
			constexpr MessageID MID_OccupyMapObjectRes(MessageType::Result,1,MessageProtocol::PlayInstance,27);

			// Cmd: Unoccupy map object
			constexpr MessageID MID_UnoccupyMapObjectCmd(MessageType::Command,1,MessageProtocol::PlayInstance,28);
			constexpr MessageID MID_UnoccupyMapObjectRes(MessageType::Result,1,MessageProtocol::PlayInstance,28);

			// Cmd: Use map object
			constexpr MessageID MID_UseMapObjectCmd(MessageType::Command,1,MessageProtocol::PlayInstance,29);
			constexpr MessageID MID_UseMapObjectRes(MessageType::Result,1,MessageProtocol::PlayInstance,29);

			// Cmd: Send zone chatting
			constexpr MessageID MID_ZoneChatCmd(MessageType::Command,1,MessageProtocol::PlayInstance,30);
			constexpr MessageID MID_ZoneChatRes(MessageType::Result,1,MessageProtocol::PlayInstance,30);

			// S2C: Player state change
			constexpr MessageID MID_ZoneChatS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,31);
			// S2C: Effect modifier initial sync
			constexpr MessageID MID_LevelUpS2CEvt(MessageType::Event,1,MessageProtocol::PlayInstance,32);
			// Cmd: To call general functionality
			constexpr MessageID MID_CallFunctionCmd(MessageType::Command,1,MessageProtocol::PlayInstance,33);
			constexpr MessageID MID_CallFunctionRes(MessageType::Result,1,MessageProtocol::PlayInstance,33);

			// C2S: Send coded voice data to server
			constexpr MessageID MID_SendVoiceDataC2SEvt(MessageType::Event,0,MessageProtocol::PlayInstance,34);
			// S2C: Voice data
			constexpr MessageID MID_VoiceDataS2CEvt(MessageType::Event,0,MessageProtocol::PlayInstance,35);
			// Cmd: Create stream instance
			constexpr MessageID MID_CreateStreamCmd(MessageType::Command,1,MessageProtocol::PlayInstance,36);
			constexpr MessageID MID_CreateStreamRes(MessageType::Result,1,MessageProtocol::PlayInstance,36);

			// Cmd: Open stream instance
			constexpr MessageID MID_FindStreamCmd(MessageType::Command,1,MessageProtocol::PlayInstance,37);
			constexpr MessageID MID_FindStreamRes(MessageType::Result,1,MessageProtocol::PlayInstance,37);

			// Cmd: Delete stream instance
			constexpr MessageID MID_DeleteStreamCmd(MessageType::Command,1,MessageProtocol::PlayInstance,38);
			constexpr MessageID MID_DeleteStreamRes(MessageType::Result,1,MessageProtocol::PlayInstance,38);

			// Cmd: Get stream list
			constexpr MessageID MID_GetStreamListCmd(MessageType::Command,1,MessageProtocol::PlayInstance,39);
			constexpr MessageID MID_GetStreamListRes(MessageType::Result,1,MessageProtocol::PlayInstance,39);



		} // namespace PlayInstance
	} // namespace Message
} // namespace SF



