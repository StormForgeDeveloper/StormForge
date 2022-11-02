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


		// Cmd: To call general functionality
		public static int CallFunctionCmd { get { return CSSFNetMessageID_PlayInstanceCallFunctionCmd(); } }

		public static int CallFunctionRes { get { return CSSFNetMessageID_PlayInstanceCallFunctionRes(); } }


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



		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCallFunctionCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCallFunctionCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceCallFunctionRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceCallFunctionRes();



		#endregion //Native Interfaces 
	}; // public partial class MessageIDPlayInstance




} // namespace SF.Net


