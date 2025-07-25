﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;


namespace SF.Net
{
 

	public static class MessageIDPlayInstance
	{
 		// Cmd: Player Join request.
		public static readonly MessageID JoinPlayInstanceCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 0);
		public static readonly MessageID JoinPlayInstanceRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 0);

		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public static readonly MessageID PlayerKickedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 1);
		// C2S: Play packet
		public static readonly MessageID PlayPacketC2SEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 2);
		// S2C: New actor in get view
		public static readonly MessageID NewActorInViewS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 3);
		// S2C: Remove actor from view
		public static readonly MessageID RemoveActorFromViewS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 4);
		// C2S: Player Movement
		public static readonly MessageID PlayerMovementC2SEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 5);
		// S2C: Player Movement
		public static readonly MessageID ActorMovementS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 6);
		// S2C: Player Movement
		public static readonly MessageID ActorMovementsS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 7);
		// S2C: Player state change
		public static readonly MessageID PlayerStateChangedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 8);
		// C2S: Reliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public static readonly MessageID ClientSyncReliableC2SEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 9);
		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public static readonly MessageID ClientSyncC2SEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 10);
		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		public static readonly MessageID SetCharacterPublicMessageCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 11);
		public static readonly MessageID SetCharacterPublicMessageRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 11);

		// S2C: Character's private data has changed
		public static readonly MessageID CharacterPrivateDataChangedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 12);
		// S2C: Player public data has been changed
		public static readonly MessageID CharacterPublicDataChangedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 13);
		// Cmd: Request WhiteboardSharing
		public static readonly MessageID RequestWhiteboardSharingCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 14);
		public static readonly MessageID RequestWhiteboardSharingRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 14);

		// Cmd: Accept WhiteboardSharing
		public static readonly MessageID AcceptWhiteboardSharingCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 15);
		public static readonly MessageID AcceptWhiteboardSharingRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 15);

		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		public static readonly MessageID CloseWhiteboardSharingCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 16);
		public static readonly MessageID CloseWhiteboardSharingRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 16);

		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public static readonly MessageID AddWhiteboardSharingLogEntryCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 17);
		public static readonly MessageID AddWhiteboardSharingLogEntryRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 17);

		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public static readonly MessageID UpdateWhiteboardSharingLogEntryCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 18);
		public static readonly MessageID UpdateWhiteboardSharingLogEntryRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 18);

		// Cmd: Update whiteboard log entry
		public static readonly MessageID RemoveWhiteboardSharingLogEntryCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 19);
		public static readonly MessageID RemoveWhiteboardSharingLogEntryRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 19);

		// S2C: WhiteboardSharing has been requested
		public static readonly MessageID WhiteboardSharingRequestedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 20);
		// S2C: WhiteboardSharing has been requested
		public static readonly MessageID WhiteboardSharingRejectedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 21);
		// S2C: WhiteboardSharing has been started
		public static readonly MessageID WhiteboardSharingStartedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 22);
		// S2C: WhiteboardSharing has been closed
		public static readonly MessageID WhiteboardSharingHasClosedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 23);
		// S2C: WhiteboardSharing new log entry has been added
		public static readonly MessageID WhiteboardSharingNewLogEntryAddedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 24);
		// S2C: WhiteboardSharing new log entry has been removed
		public static readonly MessageID WhiteboardSharingNewLogEntryRemovedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 25);
		// S2C: WhiteboardSharing new log entry has been updated
		public static readonly MessageID WhiteboardSharingNewLogEntryUpdatedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 26);
		// Cmd: Occupy map object
		public static readonly MessageID OccupyMapObjectCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 27);
		public static readonly MessageID OccupyMapObjectRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 27);

		// Cmd: Unoccupy map object
		public static readonly MessageID UnoccupyMapObjectCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 28);
		public static readonly MessageID UnoccupyMapObjectRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 28);

		// Cmd: Use map object
		public static readonly MessageID UseMapObjectCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 29);
		public static readonly MessageID UseMapObjectRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 29);

		// Cmd: Send zone chatting
		public static readonly MessageID ZoneChatCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 30);
		public static readonly MessageID ZoneChatRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 30);

		// S2C: Player state change
		public static readonly MessageID ZoneChatS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 31);
		// S2C: Effect modifier initial sync
		public static readonly MessageID LevelUpS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 32);
		// Cmd: To call general functionality
		public static readonly MessageID CallFunctionCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 33);
		public static readonly MessageID CallFunctionRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 33);

		// C2S: Send coded voice data to server
		public static readonly MessageID SendVoiceDataC2SEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 34);
		// S2C: Voice data
		public static readonly MessageID VoiceDataS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 0, SF.MessageProtocol.PlayInstance, 35);
		// Cmd: UGC zone edit command
		public static readonly MessageID UGCEditAddCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 36);
		public static readonly MessageID UGCEditAddRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 36);

		// Cmd: UGC zone edit command
		public static readonly MessageID UGCEditMoveCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 37);
		public static readonly MessageID UGCEditMoveRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 37);

		// Cmd: UGC zone edit command
		public static readonly MessageID UGCEditDeleteCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 38);
		public static readonly MessageID UGCEditDeleteRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 38);

		// Cmd: UGC zone edit command
		public static readonly MessageID UGCEditClaimBackCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 39);
		public static readonly MessageID UGCEditClaimBackRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 39);

		// S2C: UGC zone edited event
		public static readonly MessageID UGCEditAddedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 40);
		// S2C: UGC zone edited event
		public static readonly MessageID UGCEditRemovedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 41);
		// S2C: UGC zone edited event
		public static readonly MessageID UGCEditMovedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 42);
		// S2C: UGC content added event
		public static readonly MessageID UGCContentAddedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.PlayInstance, 43);
		// Cmd: Create stream instance
		public static readonly MessageID CreateStreamCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 44);
		public static readonly MessageID CreateStreamRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 44);

		// Cmd: Open stream instance
		public static readonly MessageID FindStreamCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 45);
		public static readonly MessageID FindStreamRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 45);

		// Cmd: Delete stream instance
		public static readonly MessageID DeleteStreamCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 46);
		public static readonly MessageID DeleteStreamRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 46);

		// Cmd: Get stream list
		public static readonly MessageID GetStreamListCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.PlayInstance, 47);
		public static readonly MessageID GetStreamListRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.PlayInstance, 47);

	}; // public static class MessageIDPlayInstance




} // namespace SF.Net


