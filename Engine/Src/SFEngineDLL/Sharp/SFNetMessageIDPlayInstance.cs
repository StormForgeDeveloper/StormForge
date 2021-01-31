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


		// S2C: Event for Player joined.
		public static int PlayerJoinS2CEvt { get { return CSSFNetMessageID_PlayInstancePlayerJoinS2CEvt(); } }

		// S2C: Event for Player left.
		public static int PlayerLeftS2CEvt { get { return CSSFNetMessageID_PlayInstancePlayerLeftS2CEvt(); } }

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
		// Cmd: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceJoinGameInstanceCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstanceJoinGameInstanceRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstanceJoinGameInstanceRes();



		// S2C: Event for Player joined.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerJoinS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerJoinS2CEvt();


		// S2C: Event for Player left.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_PlayInstancePlayerLeftS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_PlayInstancePlayerLeftS2CEvt();


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


