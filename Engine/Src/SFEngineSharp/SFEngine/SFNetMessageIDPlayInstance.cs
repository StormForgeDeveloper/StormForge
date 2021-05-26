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
		// Cmd: Event for Player Join request.
		public static int JoinGameInstanceCmd { get { return CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd(); } }

		public static int JoinGameInstanceRes { get { return CSSFNetMessageID_PlayInstanceJoinGameInstanceRes(); } }


		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public static int PlayerKickedS2CEvt { get { return CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt(); } }

		// C2S: Play packet
		public static int PlayPacketC2SEvt { get { return CSSFNetMessageID_PlayInstancePlayPacketC2SEvt(); } }

		// S2C: New Player in get view
		public static int NewPlayerInViewS2CEvt { get { return CSSFNetMessageID_PlayInstanceNewPlayerInViewS2CEvt(); } }

		// S2C: Remove player from view
		public static int RemovePlayerFromViewS2CEvt { get { return CSSFNetMessageID_PlayInstanceRemovePlayerFromViewS2CEvt(); } }

		// C2S: Player Movement
		public static int PlayerMovementC2SEvt { get { return CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt(); } }

		// S2C: Player Movement
		public static int PlayerMovementS2CEvt { get { return CSSFNetMessageID_PlayInstancePlayerMovementS2CEvt(); } }

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


		// Cmd: Havest area
		public static int HarvestAreaCmd { get { return CSSFNetMessageID_PlayInstanceHarvestAreaCmd(); } }

		public static int HarvestAreaRes { get { return CSSFNetMessageID_PlayInstanceHarvestAreaRes(); } }


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
		// Cmd: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceJoinGameInstanceRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceJoinGameInstanceRes();



		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerKickedS2CEvt();


		// C2S: Play packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayPacketC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayPacketC2SEvt();


		// S2C: New Player in get view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceNewPlayerInViewS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceNewPlayerInViewS2CEvt();


		// S2C: Remove player from view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceRemovePlayerFromViewS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceRemovePlayerFromViewS2CEvt();


		// C2S: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerMovementC2SEvt();


		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerMovementS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerMovementS2CEvt();


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



		// Cmd: Havest area
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceHarvestAreaCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceHarvestAreaCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceHarvestAreaRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceHarvestAreaRes();



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


