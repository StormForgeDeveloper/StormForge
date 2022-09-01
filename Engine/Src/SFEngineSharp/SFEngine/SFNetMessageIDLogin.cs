////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Login Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public partial class MessageIDLogin
	{
 		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		// Cmd: Login request
		public static int LoginCmd { get { return CSSFNetMessageID_LoginLoginCmd(); } }

		public static int LoginRes { get { return CSSFNetMessageID_LoginLoginRes(); } }


		// Cmd: Login request with Facebook UID
		public static int LoginByFacebookCmd { get { return CSSFNetMessageID_LoginLoginByFacebookCmd(); } }

		public static int LoginByFacebookRes { get { return CSSFNetMessageID_LoginLoginByFacebookRes(); } }


		// Cmd: Login request with Facebook UID
		public static int LoginBySteamCmd { get { return CSSFNetMessageID_LoginLoginBySteamCmd(); } }

		public static int LoginBySteamRes { get { return CSSFNetMessageID_LoginLoginBySteamRes(); } }


		// Cmd: Login request
		public static int CreateRandomUserCmd { get { return CSSFNetMessageID_LoginCreateRandomUserCmd(); } }

		public static int CreateRandomUserRes { get { return CSSFNetMessageID_LoginCreateRandomUserRes(); } }


		// Cmd: Update my score and Get Ranking list
		public static int UpdateMyScoreCmd { get { return CSSFNetMessageID_LoginUpdateMyScoreCmd(); } }

		public static int UpdateMyScoreRes { get { return CSSFNetMessageID_LoginUpdateMyScoreRes(); } }


		// Cmd: Get Ranking lise
		public static int GetRankingListCmd { get { return CSSFNetMessageID_LoginGetRankingListCmd(); } }

		public static int GetRankingListRes { get { return CSSFNetMessageID_LoginGetRankingListRes(); } }


		// Cmd: For network test
		public static int DataTestCmd { get { return CSSFNetMessageID_LoginDataTestCmd(); } }

		public static int DataTestRes { get { return CSSFNetMessageID_LoginDataTestRes(); } }


		// C2S: Heartbeat
		public static int HeartbeatC2SEvt { get { return CSSFNetMessageID_LoginHeartbeatC2SEvt(); } }

		// Cmd: Write All!! User Score and Ranking list
		public static int DebugPrintALLRankingCmd { get { return CSSFNetMessageID_LoginDebugPrintALLRankingCmd(); } }

		public static int DebugPrintALLRankingRes { get { return CSSFNetMessageID_LoginDebugPrintALLRankingRes(); } }


		#region Native Interfaces 
		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginLoginCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginLoginCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginLoginRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginLoginRes();



		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginLoginByFacebookCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginLoginByFacebookCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginLoginByFacebookRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginLoginByFacebookRes();



		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginLoginBySteamCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginLoginBySteamCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginLoginBySteamRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginLoginBySteamRes();



		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginCreateRandomUserCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginCreateRandomUserCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginCreateRandomUserRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginCreateRandomUserRes();



		// Cmd: Update my score and Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginUpdateMyScoreCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginUpdateMyScoreCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginUpdateMyScoreRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginUpdateMyScoreRes();



		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginGetRankingListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginGetRankingListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginGetRankingListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginGetRankingListRes();



		// Cmd: For network test
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginDataTestCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginDataTestCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginDataTestRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginDataTestRes();



		// C2S: Heartbeat
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginHeartbeatC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginHeartbeatC2SEvt();


		// Cmd: Write All!! User Score and Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginDebugPrintALLRankingCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginDebugPrintALLRankingCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_LoginDebugPrintALLRankingRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_LoginDebugPrintALLRankingRes();



		#endregion //Native Interfaces 
	}; // public partial class MessageIDLogin




} // namespace SF.Net


