////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
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
 

	public partial class MessageIDPlayInstance
	{
 		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		// Cmd: Player Join request.
		public static int JoinPlayInstanceCmd { get { return CSSFNetMessageID_PlayInstanceJoinPlayInstanceCmd(); } }

		public static int JoinPlayInstanceRes { get { return CSSFNetMessageID_PlayInstanceJoinPlayInstanceRes(); } }


		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public static int PlayerKickedS2CEvt { get { return CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt(); } }

		// C2S: Play packet
		public static int PlayPacketC2SEvt { get { return CSSFNetMessageID_PlayInstancePlayPacketC2SEvt(); } }

		// S2C: New actor in get view
		public static int NewActorInViewS2CEvt { get { return CSSFNetMessageID_PlayInstanceNewActorInViewS2CEvt(); } }

		// S2C: Remove actor from view
		public static int RemoveActorFromViewS2CEvt { get { return CSSFNetMessageID_PlayInstanceRemoveActorFromViewS2CEvt(); } }

		// C2S: Player Movement
		public static int PlayerMovementC2SEvt { get { return CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt(); } }

		// S2C: Player Movement
		public static int ActorMovementS2CEvt { get { return CSSFNetMessageID_PlayInstanceActorMovementS2CEvt(); } }

		// S2C: Player Movement
		public static int ActorMovementsS2CEvt { get { return CSSFNetMessageID_PlayInstanceActorMovementsS2CEvt(); } }

		// S2C: Player state change
		public static int PlayerStateChangedS2CEvt { get { return CSSFNetMessageID_PlayInstancePlayerStateChangedS2CEvt(); } }

		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public static int ClientSyncReliableC2SEvt { get { return CSSFNetMessageID_PlayInstanceClientSyncReliableC2SEvt(); } }

		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public static int ClientSyncC2SEvt { get { return CSSFNetMessageID_PlayInstanceClientSyncC2SEvt(); } }

		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		public static int SetCharacterPublicMessageCmd { get { return CSSFNetMessageID_PlayInstanceSetCharacterPublicMessageCmd(); } }

		public static int SetCharacterPublicMessageRes { get { return CSSFNetMessageID_PlayInstanceSetCharacterPublicMessageRes(); } }


		// S2C: Character's private data has changed
		public static int CharacterPrivateDataChangedS2CEvt { get { return CSSFNetMessageID_PlayInstanceCharacterPrivateDataChangedS2CEvt(); } }

		// S2C: Player public data has been changed
		public static int CharacterPublicDataChangedS2CEvt { get { return CSSFNetMessageID_PlayInstanceCharacterPublicDataChangedS2CEvt(); } }

		// Cmd: Request WhiteboardSharing
		public static int RequestWhiteboardSharingCmd { get { return CSSFNetMessageID_PlayInstanceRequestWhiteboardSharingCmd(); } }

		public static int RequestWhiteboardSharingRes { get { return CSSFNetMessageID_PlayInstanceRequestWhiteboardSharingRes(); } }


		// Cmd: Accept WhiteboardSharing
		public static int AcceptWhiteboardSharingCmd { get { return CSSFNetMessageID_PlayInstanceAcceptWhiteboardSharingCmd(); } }

		public static int AcceptWhiteboardSharingRes { get { return CSSFNetMessageID_PlayInstanceAcceptWhiteboardSharingRes(); } }


		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		public static int CloseWhiteboardSharingCmd { get { return CSSFNetMessageID_PlayInstanceCloseWhiteboardSharingCmd(); } }

		public static int CloseWhiteboardSharingRes { get { return CSSFNetMessageID_PlayInstanceCloseWhiteboardSharingRes(); } }


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public static int AddWhiteboardSharingLogEntryCmd { get { return CSSFNetMessageID_PlayInstanceAddWhiteboardSharingLogEntryCmd(); } }

		public static int AddWhiteboardSharingLogEntryRes { get { return CSSFNetMessageID_PlayInstanceAddWhiteboardSharingLogEntryRes(); } }


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public static int UpdateWhiteboardSharingLogEntryCmd { get { return CSSFNetMessageID_PlayInstanceUpdateWhiteboardSharingLogEntryCmd(); } }

		public static int UpdateWhiteboardSharingLogEntryRes { get { return CSSFNetMessageID_PlayInstanceUpdateWhiteboardSharingLogEntryRes(); } }


		// Cmd: Update whiteboard log entry
		public static int RemoveWhiteboardSharingLogEntryCmd { get { return CSSFNetMessageID_PlayInstanceRemoveWhiteboardSharingLogEntryCmd(); } }

		public static int RemoveWhiteboardSharingLogEntryRes { get { return CSSFNetMessageID_PlayInstanceRemoveWhiteboardSharingLogEntryRes(); } }


		// S2C: WhiteboardSharing has been requested
		public static int WhiteboardSharingRequestedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingRequestedS2CEvt(); } }

		// S2C: WhiteboardSharing has been requested
		public static int WhiteboardSharingRejectedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingRejectedS2CEvt(); } }

		// S2C: WhiteboardSharing has been started
		public static int WhiteboardSharingStartedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingStartedS2CEvt(); } }

		// S2C: WhiteboardSharing has been closed
		public static int WhiteboardSharingHasClosedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingHasClosedS2CEvt(); } }

		// S2C: WhiteboardSharing new log entry has been added
		public static int WhiteboardSharingNewLogEntryAddedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt(); } }

		// S2C: WhiteboardSharing new log entry has been removed
		public static int WhiteboardSharingNewLogEntryRemovedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt(); } }

		// S2C: WhiteboardSharing new log entry has been updated
		public static int WhiteboardSharingNewLogEntryUpdatedS2CEvt { get { return CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt(); } }

		// Cmd: Occupy map object
		public static int OccupyMapObjectCmd { get { return CSSFNetMessageID_PlayInstanceOccupyMapObjectCmd(); } }

		public static int OccupyMapObjectRes { get { return CSSFNetMessageID_PlayInstanceOccupyMapObjectRes(); } }


		// Cmd: Unoccupy map object
		public static int UnoccupyMapObjectCmd { get { return CSSFNetMessageID_PlayInstanceUnoccupyMapObjectCmd(); } }

		public static int UnoccupyMapObjectRes { get { return CSSFNetMessageID_PlayInstanceUnoccupyMapObjectRes(); } }


		// Cmd: Use map object
		public static int UseMapObjectCmd { get { return CSSFNetMessageID_PlayInstanceUseMapObjectCmd(); } }

		public static int UseMapObjectRes { get { return CSSFNetMessageID_PlayInstanceUseMapObjectRes(); } }


		// Cmd: Send zone chatting
		public static int ZoneChatCmd { get { return CSSFNetMessageID_PlayInstanceZoneChatCmd(); } }

		public static int ZoneChatRes { get { return CSSFNetMessageID_PlayInstanceZoneChatRes(); } }


		// S2C: Player state change
		public static int ZoneChatS2CEvt { get { return CSSFNetMessageID_PlayInstanceZoneChatS2CEvt(); } }

		// S2C: Effect modifier initial sync
		public static int LevelUpS2CEvt { get { return CSSFNetMessageID_PlayInstanceLevelUpS2CEvt(); } }

		// Cmd: To call general functionality
		public static int CallFunctionCmd { get { return CSSFNetMessageID_PlayInstanceCallFunctionCmd(); } }

		public static int CallFunctionRes { get { return CSSFNetMessageID_PlayInstanceCallFunctionRes(); } }


		// C2S: Send coded voice data to server
		public static int SendVoiceDataC2SEvt { get { return CSSFNetMessageID_PlayInstanceSendVoiceDataC2SEvt(); } }

		// S2C: Voice data
		public static int VoiceDataS2CEvt { get { return CSSFNetMessageID_PlayInstanceVoiceDataS2CEvt(); } }

		// Cmd: Create stream instance
		public static int CreateStreamCmd { get { return CSSFNetMessageID_PlayInstanceCreateStreamCmd(); } }

		public static int CreateStreamRes { get { return CSSFNetMessageID_PlayInstanceCreateStreamRes(); } }


		// Cmd: Open stream instance
		public static int FindStreamCmd { get { return CSSFNetMessageID_PlayInstanceFindStreamCmd(); } }

		public static int FindStreamRes { get { return CSSFNetMessageID_PlayInstanceFindStreamRes(); } }


		// Cmd: Delete stream instance
		public static int DeleteStreamCmd { get { return CSSFNetMessageID_PlayInstanceDeleteStreamCmd(); } }

		public static int DeleteStreamRes { get { return CSSFNetMessageID_PlayInstanceDeleteStreamRes(); } }


		// Cmd: Get stream list
		public static int GetStreamListCmd { get { return CSSFNetMessageID_PlayInstanceGetStreamListCmd(); } }

		public static int GetStreamListRes { get { return CSSFNetMessageID_PlayInstanceGetStreamListRes(); } }


		#region Native Interfaces 
		// Cmd: Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceJoinPlayInstanceCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceJoinPlayInstanceCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceJoinPlayInstanceRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceJoinPlayInstanceRes();



		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt();


		// C2S: Play packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayPacketC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayPacketC2SEvt();


		// S2C: New actor in get view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceNewActorInViewS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceNewActorInViewS2CEvt();


		// S2C: Remove actor from view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceRemoveActorFromViewS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceRemoveActorFromViewS2CEvt();


		// C2S: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt();


		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceActorMovementS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceActorMovementS2CEvt();


		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceActorMovementsS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceActorMovementsS2CEvt();


		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerStateChangedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerStateChangedS2CEvt();


		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceClientSyncReliableC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceClientSyncReliableC2SEvt();


		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceClientSyncC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceClientSyncC2SEvt();


		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceSetCharacterPublicMessageCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceSetCharacterPublicMessageCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceSetCharacterPublicMessageRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceSetCharacterPublicMessageRes();



		// S2C: Character's private data has changed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCharacterPrivateDataChangedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCharacterPrivateDataChangedS2CEvt();


		// S2C: Player public data has been changed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCharacterPublicDataChangedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCharacterPublicDataChangedS2CEvt();


		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceRequestWhiteboardSharingCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceRequestWhiteboardSharingCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceRequestWhiteboardSharingRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceRequestWhiteboardSharingRes();



		// Cmd: Accept WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceAcceptWhiteboardSharingCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceAcceptWhiteboardSharingCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceAcceptWhiteboardSharingRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceAcceptWhiteboardSharingRes();



		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCloseWhiteboardSharingCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCloseWhiteboardSharingCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCloseWhiteboardSharingRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCloseWhiteboardSharingRes();



		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceAddWhiteboardSharingLogEntryCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceAddWhiteboardSharingLogEntryCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceAddWhiteboardSharingLogEntryRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceAddWhiteboardSharingLogEntryRes();



		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceUpdateWhiteboardSharingLogEntryCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceUpdateWhiteboardSharingLogEntryCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceUpdateWhiteboardSharingLogEntryRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceUpdateWhiteboardSharingLogEntryRes();



		// Cmd: Update whiteboard log entry
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceRemoveWhiteboardSharingLogEntryCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceRemoveWhiteboardSharingLogEntryCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceRemoveWhiteboardSharingLogEntryRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceRemoveWhiteboardSharingLogEntryRes();



		// S2C: WhiteboardSharing has been requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingRequestedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingRequestedS2CEvt();


		// S2C: WhiteboardSharing has been requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingRejectedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingRejectedS2CEvt();


		// S2C: WhiteboardSharing has been started
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingStartedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingStartedS2CEvt();


		// S2C: WhiteboardSharing has been closed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingHasClosedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingHasClosedS2CEvt();


		// S2C: WhiteboardSharing new log entry has been added
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt();


		// S2C: WhiteboardSharing new log entry has been removed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt();


		// S2C: WhiteboardSharing new log entry has been updated
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt();


		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceOccupyMapObjectCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceOccupyMapObjectCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceOccupyMapObjectRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceOccupyMapObjectRes();



		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceUnoccupyMapObjectCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceUnoccupyMapObjectCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceUnoccupyMapObjectRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceUnoccupyMapObjectRes();



		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceUseMapObjectCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceUseMapObjectCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceUseMapObjectRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceUseMapObjectRes();



		// Cmd: Send zone chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceZoneChatCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceZoneChatCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceZoneChatRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceZoneChatRes();



		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceZoneChatS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceZoneChatS2CEvt();


		// S2C: Effect modifier initial sync
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceLevelUpS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceLevelUpS2CEvt();


		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCallFunctionCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCallFunctionCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCallFunctionRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCallFunctionRes();



		// C2S: Send coded voice data to server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceSendVoiceDataC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceSendVoiceDataC2SEvt();


		// S2C: Voice data
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceVoiceDataS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceVoiceDataS2CEvt();


		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCreateStreamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCreateStreamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCreateStreamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCreateStreamRes();



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceFindStreamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceFindStreamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceFindStreamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceFindStreamRes();



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceDeleteStreamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceDeleteStreamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceDeleteStreamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceDeleteStreamRes();



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceGetStreamListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceGetStreamListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceGetStreamListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceGetStreamListRes();



		#endregion //Native Interfaces 
	}; // public partial class MessageIDPlayInstance




} // namespace SF.Net


