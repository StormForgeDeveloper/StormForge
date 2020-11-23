////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Relay Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public partial class MessageIDRelay
	{
 		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		// C2S: Event for Player Join request.
		public static int JoinRelayInstanceC2SEvt { get { return CSSFNetMessageID_RelayJoinRelayInstanceC2SEvt(); } }

		// S2C: Event for joined player
		public static int JoinRelayInstanceResS2CEvt { get { return CSSFNetMessageID_RelayJoinRelayInstanceResS2CEvt(); } }

		// C2S: Event for Player Join request.
		public static int LeaveRelayInstanceC2SEvt { get { return CSSFNetMessageID_RelayLeaveRelayInstanceC2SEvt(); } }

		// S2C: Event for Player joined.
		public static int PlayerJoinS2CEvt { get { return CSSFNetMessageID_RelayPlayerJoinS2CEvt(); } }

		// S2C: Event for Player left.
		public static int PlayerLeftS2CEvt { get { return CSSFNetMessageID_RelayPlayerLeftS2CEvt(); } }

		// C2S: Relay packet
		public static int RelayPacketC2SEvt { get { return CSSFNetMessageID_RelayRelayPacketC2SEvt(); } }

		// Cmd: Create stream instance
		public static int CreateStreamCmd { get { return CSSFNetMessageID_RelayCreateStreamCmd(); } }

		public static int CreateStreamRes { get { return CSSFNetMessageID_RelayCreateStreamRes(); } }


		// Cmd: Open stream instance
		public static int FindStreamCmd { get { return CSSFNetMessageID_RelayFindStreamCmd(); } }

		public static int FindStreamRes { get { return CSSFNetMessageID_RelayFindStreamRes(); } }


		// Cmd: Delete stream instance
		public static int DeleteStreamCmd { get { return CSSFNetMessageID_RelayDeleteStreamCmd(); } }

		public static int DeleteStreamRes { get { return CSSFNetMessageID_RelayDeleteStreamRes(); } }


		// Cmd: Get stream list
		public static int GetStreamListCmd { get { return CSSFNetMessageID_RelayGetStreamListCmd(); } }

		public static int GetStreamListRes { get { return CSSFNetMessageID_RelayGetStreamListRes(); } }


		#region Native Interfaces 
		// C2S: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayJoinRelayInstanceC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayJoinRelayInstanceC2SEvt();


		// S2C: Event for joined player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayJoinRelayInstanceResS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayJoinRelayInstanceResS2CEvt();


		// C2S: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayLeaveRelayInstanceC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayLeaveRelayInstanceC2SEvt();


		// S2C: Event for Player joined.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayPlayerJoinS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayPlayerJoinS2CEvt();


		// S2C: Event for Player left.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayPlayerLeftS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayPlayerLeftS2CEvt();


		// C2S: Relay packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayRelayPacketC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayRelayPacketC2SEvt();


		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayCreateStreamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayCreateStreamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayCreateStreamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayCreateStreamRes();



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayFindStreamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayFindStreamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayFindStreamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayFindStreamRes();



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayDeleteStreamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayDeleteStreamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayDeleteStreamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayDeleteStreamRes();



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayGetStreamListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayGetStreamListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_RelayGetStreamListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_RelayGetStreamListRes();



		#endregion //Native Interfaces 
	}; // public partial class MessageIDRelay




} // namespace SF.Net


