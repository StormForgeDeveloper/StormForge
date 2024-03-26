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
			constexpr MessageID MID_JoinPlayInstanceCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,0);
			constexpr MessageID MID_JoinPlayInstanceRes(EMessageType::Result,1,MessageProtocol::PlayInstance,0);

			// S2C: Player kicked event. this event will be broadcasted when a player kicked.
			constexpr MessageID MID_PlayerKickedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,1);
			// C2S: Play packet
			constexpr MessageID MID_PlayPacketC2SEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,2);
			// S2C: New actor in get view
			constexpr MessageID MID_NewActorInViewS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,3);
			// S2C: Remove actor from view
			constexpr MessageID MID_RemoveActorFromViewS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,4);
			// C2S: Player Movement
			constexpr MessageID MID_PlayerMovementC2SEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,5);
			// S2C: Player Movement
			constexpr MessageID MID_ActorMovementS2CEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,6);
			// S2C: Player Movement
			constexpr MessageID MID_ActorMovementsS2CEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,7);
			// S2C: Player state change
			constexpr MessageID MID_PlayerStateChangedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,8);
			// C2S: Reliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			constexpr MessageID MID_ClientSyncReliableC2SEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,9);
			// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
			constexpr MessageID MID_ClientSyncC2SEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,10);
			// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
			constexpr MessageID MID_SetCharacterPublicMessageCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,11);
			constexpr MessageID MID_SetCharacterPublicMessageRes(EMessageType::Result,1,MessageProtocol::PlayInstance,11);

			// S2C: Character's private data has changed
			constexpr MessageID MID_CharacterPrivateDataChangedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,12);
			// S2C: Player public data has been changed
			constexpr MessageID MID_CharacterPublicDataChangedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,13);
			// Cmd: Request WhiteboardSharing
			constexpr MessageID MID_RequestWhiteboardSharingCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,14);
			constexpr MessageID MID_RequestWhiteboardSharingRes(EMessageType::Result,1,MessageProtocol::PlayInstance,14);

			// Cmd: Accept WhiteboardSharing
			constexpr MessageID MID_AcceptWhiteboardSharingCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,15);
			constexpr MessageID MID_AcceptWhiteboardSharingRes(EMessageType::Result,1,MessageProtocol::PlayInstance,15);

			// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
			constexpr MessageID MID_CloseWhiteboardSharingCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,16);
			constexpr MessageID MID_CloseWhiteboardSharingRes(EMessageType::Result,1,MessageProtocol::PlayInstance,16);

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			constexpr MessageID MID_AddWhiteboardSharingLogEntryCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,17);
			constexpr MessageID MID_AddWhiteboardSharingLogEntryRes(EMessageType::Result,1,MessageProtocol::PlayInstance,17);

			// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
			constexpr MessageID MID_UpdateWhiteboardSharingLogEntryCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,18);
			constexpr MessageID MID_UpdateWhiteboardSharingLogEntryRes(EMessageType::Result,1,MessageProtocol::PlayInstance,18);

			// Cmd: Update whiteboard log entry
			constexpr MessageID MID_RemoveWhiteboardSharingLogEntryCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,19);
			constexpr MessageID MID_RemoveWhiteboardSharingLogEntryRes(EMessageType::Result,1,MessageProtocol::PlayInstance,19);

			// S2C: WhiteboardSharing has been requested
			constexpr MessageID MID_WhiteboardSharingRequestedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,20);
			// S2C: WhiteboardSharing has been requested
			constexpr MessageID MID_WhiteboardSharingRejectedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,21);
			// S2C: WhiteboardSharing has been started
			constexpr MessageID MID_WhiteboardSharingStartedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,22);
			// S2C: WhiteboardSharing has been closed
			constexpr MessageID MID_WhiteboardSharingHasClosedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,23);
			// S2C: WhiteboardSharing new log entry has been added
			constexpr MessageID MID_WhiteboardSharingNewLogEntryAddedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,24);
			// S2C: WhiteboardSharing new log entry has been removed
			constexpr MessageID MID_WhiteboardSharingNewLogEntryRemovedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,25);
			// S2C: WhiteboardSharing new log entry has been updated
			constexpr MessageID MID_WhiteboardSharingNewLogEntryUpdatedS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,26);
			// Cmd: Occupy map object
			constexpr MessageID MID_OccupyMapObjectCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,27);
			constexpr MessageID MID_OccupyMapObjectRes(EMessageType::Result,1,MessageProtocol::PlayInstance,27);

			// Cmd: Unoccupy map object
			constexpr MessageID MID_UnoccupyMapObjectCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,28);
			constexpr MessageID MID_UnoccupyMapObjectRes(EMessageType::Result,1,MessageProtocol::PlayInstance,28);

			// Cmd: Use map object
			constexpr MessageID MID_UseMapObjectCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,29);
			constexpr MessageID MID_UseMapObjectRes(EMessageType::Result,1,MessageProtocol::PlayInstance,29);

			// Cmd: Send zone chatting
			constexpr MessageID MID_ZoneChatCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,30);
			constexpr MessageID MID_ZoneChatRes(EMessageType::Result,1,MessageProtocol::PlayInstance,30);

			// S2C: Player state change
			constexpr MessageID MID_ZoneChatS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,31);
			// S2C: Effect modifier initial sync
			constexpr MessageID MID_LevelUpS2CEvt(EMessageType::Event,1,MessageProtocol::PlayInstance,32);
			// Cmd: To call general functionality
			constexpr MessageID MID_CallFunctionCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,33);
			constexpr MessageID MID_CallFunctionRes(EMessageType::Result,1,MessageProtocol::PlayInstance,33);

			// C2S: Send coded voice data to server
			constexpr MessageID MID_SendVoiceDataC2SEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,34);
			// S2C: Voice data
			constexpr MessageID MID_VoiceDataS2CEvt(EMessageType::Event,0,MessageProtocol::PlayInstance,35);
			// Cmd: Create stream instance
			constexpr MessageID MID_CreateStreamCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,36);
			constexpr MessageID MID_CreateStreamRes(EMessageType::Result,1,MessageProtocol::PlayInstance,36);

			// Cmd: Open stream instance
			constexpr MessageID MID_FindStreamCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,37);
			constexpr MessageID MID_FindStreamRes(EMessageType::Result,1,MessageProtocol::PlayInstance,37);

			// Cmd: Delete stream instance
			constexpr MessageID MID_DeleteStreamCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,38);
			constexpr MessageID MID_DeleteStreamRes(EMessageType::Result,1,MessageProtocol::PlayInstance,38);

			// Cmd: Get stream list
			constexpr MessageID MID_GetStreamListCmd(EMessageType::Command,1,MessageProtocol::PlayInstance,39);
			constexpr MessageID MID_GetStreamListRes(EMessageType::Result,1,MessageProtocol::PlayInstance,39);



		} // namespace PlayInstance
	} // namespace Message
} // namespace SF



