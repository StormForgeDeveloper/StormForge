////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Login Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public class SendMessageLogin : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageLogin()
		{
 		} // public  SendMessageLogin()
		public  SendMessageLogin( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageLogin( SF.SFConnection connection ) : base(connection)

		// Cmd: Login request
		public int  LoginCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.String InID, System.String InPassword )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginLoginCmd(m_Connection.NativeHandle, InTransactionID, InGameID,System.Text.Encoding.UTF8.GetBytes(InID + "\0"),System.Text.Encoding.UTF8.GetBytes(InPassword + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.LoginCmd);
			return result;
		} // public int  LoginCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.String InID, System.String InPassword )

		// Cmd: Login request with Facebook UID
		public int  LoginByFacebookCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.UInt64 InUID, System.String InFaceBookName, System.String InEMail, System.String InFacebookToken )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginLoginByFacebookCmd(m_Connection.NativeHandle, InTransactionID, InGameID, InUID,System.Text.Encoding.UTF8.GetBytes(InFaceBookName + "\0"),System.Text.Encoding.UTF8.GetBytes(InEMail + "\0"),System.Text.Encoding.UTF8.GetBytes(InFacebookToken + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.LoginByFacebookCmd);
			return result;
		} // public int  LoginByFacebookCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.UInt64 InUID, System.String InFaceBookName, System.String InEMail, System.String InFacebookToken )

		// Cmd: Login request with Facebook UID
		public int  LoginBySteamCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.UInt64 InSteamUserID, System.String InSteamUserName, System.String InSteamUserToken )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginLoginBySteamCmd(m_Connection.NativeHandle, InTransactionID, InGameID, InSteamUserID,System.Text.Encoding.UTF8.GetBytes(InSteamUserName + "\0"),System.Text.Encoding.UTF8.GetBytes(InSteamUserToken + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.LoginBySteamCmd);
			return result;
		} // public int  LoginBySteamCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.UInt64 InSteamUserID, System.String InSteamUserName, System.String InSteamUserToken )

		// Cmd: Login request
		public int  CreateRandomUserCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.String InCellPhone )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginCreateRandomUserCmd(m_Connection.NativeHandle, InTransactionID, InGameID,System.Text.Encoding.UTF8.GetBytes(InCellPhone + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.CreateRandomUserCmd);
			return result;
		} // public int  CreateRandomUserCmd( System.UInt64 InTransactionID, System.UInt32 InGameID, System.String InCellPhone )

		// Cmd: Update my score and Get Ranking list
		public int  UpdateMyScoreCmd( System.UInt64 InTransactionID, System.UInt64 InRankingScore, SF.RankingType InRankingType, System.UInt16 InCount )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginUpdateMyScoreCmd(m_Connection.NativeHandle, InTransactionID, InRankingScore,(int) InRankingType, InCount);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.UpdateMyScoreCmd);
			return result;
		} // public int  UpdateMyScoreCmd( System.UInt64 InTransactionID, System.UInt64 InRankingScore, SF.RankingType InRankingType, System.UInt16 InCount )

		// Cmd: Get Ranking lise
		public int  GetRankingListCmd( System.UInt64 InTransactionID, SF.RankingType InRankingType, System.Byte InBaseRanking, System.Byte InCount )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginGetRankingListCmd(m_Connection.NativeHandle, InTransactionID,(int) InRankingType, InBaseRanking, InCount);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.GetRankingListCmd);
			return result;
		} // public int  GetRankingListCmd( System.UInt64 InTransactionID, SF.RankingType InRankingType, System.Byte InBaseRanking, System.Byte InCount )

		// Cmd: For network test
		public int  DataTestCmd( System.UInt64 InTransactionID, System.Byte[] InTestData )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginDataTestCmd(m_Connection.NativeHandle, InTransactionID,(ushort)InTestData.Length, InTestData);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.DataTestCmd);
			return result;
		} // public int  DataTestCmd( System.UInt64 InTransactionID, System.Byte[] InTestData )

		// C2S: Heartbeat
		public int  HeartbeatC2SEvt(  )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginHeartbeatC2SEvt(m_Connection.NativeHandle);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.HeartbeatC2SEvt);
			return result;
		} // public int  HeartbeatC2SEvt(  )


		// Cmd: Write All!! User Score and Ranking list
		public int  DebugPrintALLRankingCmd( System.UInt64 InTransactionID, System.String InFileName )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginDebugPrintALLRankingCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InFileName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.DebugPrintALLRankingCmd);
			return result;
		} // public int  DebugPrintALLRankingCmd( System.UInt64 InTransactionID, System.String InFileName )

		#region Native Interfaces 
		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InGameID, [MarshalAs(UnmanagedType.LPArray)] byte[] InID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPassword );


		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginByFacebookCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginByFacebookCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InGameID, System.UInt64 InUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InFaceBookName, [MarshalAs(UnmanagedType.LPArray)] byte[] InEMail, [MarshalAs(UnmanagedType.LPArray)] byte[] InFacebookToken );


		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginBySteamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginBySteamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InGameID, System.UInt64 InSteamUserID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSteamUserName, [MarshalAs(UnmanagedType.LPArray)] byte[] InSteamUserToken );


		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginCreateRandomUserCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginCreateRandomUserCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InGameID, [MarshalAs(UnmanagedType.LPArray)] byte[] InCellPhone );


		// Cmd: Update my score and Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginUpdateMyScoreCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginUpdateMyScoreCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InRankingScore, int InRankingType, System.UInt16 InCount );


		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginGetRankingListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginGetRankingListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, int InRankingType, System.Byte InBaseRanking, System.Byte InCount );


		// Cmd: For network test
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDataTestCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDataTestCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt16 _sizeOfInTestData,System.Byte[] InTestData );


		// C2S: Heartbeat
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginHeartbeatC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginHeartbeatC2SEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Write All!! User Score and Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDebugPrintALLRankingCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDebugPrintALLRankingCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InFileName );


		#endregion //Native Interfaces 
	}; // public class SendMessageLogin : SendMessage
	public class SendMessageSvrLogin : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageSvrLogin()
		{
 		} // public  SendMessageSvrLogin()
		public  SendMessageSvrLogin( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageSvrLogin( SF.SFConnection connection ) : base(connection)

		// Cmd: Login request
		public int  LoginRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginLoginRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InGameServerAddr,ref InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.LoginRes);
			return result;
		} // public int  LoginRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )


		// Cmd: Login request with Facebook UID
		public int  LoginByFacebookRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginLoginByFacebookRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InGameServerAddr,ref InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.LoginByFacebookRes);
			return result;
		} // public int  LoginByFacebookRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )


		// Cmd: Login request with Facebook UID
		public int  LoginBySteamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginLoginBySteamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InGameServerAddr,ref InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.LoginBySteamRes);
			return result;
		} // public int  LoginBySteamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )


		// Cmd: Login request
		public int  CreateRandomUserRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginCreateRandomUserRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InGameServerAddr,ref InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.CreateRandomUserRes);
			return result;
		} // public int  CreateRandomUserRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InGameServerAddr, SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )


		// Cmd: Update my score and Get Ranking list
		public int  UpdateMyScoreRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginUpdateMyScoreRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.UpdateMyScoreRes);
			return result;
		} // public int  UpdateMyScoreRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: Get Ranking lise
		public int  GetRankingListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginGetRankingListRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.GetRankingListRes);
			return result;
		} // public int  GetRankingListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: For network test
		public int  DataTestRes( System.UInt64 InTransactionID, System.Int32 InResult, System.Byte[] InTestData )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginDataTestRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InTestData.Length, InTestData);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.DataTestRes);
			return result;
		} // public int  DataTestRes( System.UInt64 InTransactionID, System.Int32 InResult, System.Byte[] InTestData )


		// Cmd: Write All!! User Score and Ranking list
		public int  DebugPrintALLRankingRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_LoginDebugPrintALLRankingRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDLogin.DebugPrintALLRankingRes);
			return result;
		} // public int  DebugPrintALLRankingRes( System.UInt64 InTransactionID, System.Int32 InResult )


		#region Native Interfaces 
		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InGameServerAddr, ref SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );



		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginByFacebookRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginByFacebookRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InGameServerAddr, ref SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );



		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginBySteamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginBySteamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InGameServerAddr, ref SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );



		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginCreateRandomUserRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginCreateRandomUserRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InGameServerAddr, ref SF.NetAddress InGameServerAddrIPV4, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );



		// Cmd: Update my score and Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginUpdateMyScoreRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginUpdateMyScoreRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRanking,SF.TotalRankingPlayerInformation[] InRanking );



		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginGetRankingListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginGetRankingListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRanking,SF.TotalRankingPlayerInformation[] InRanking );



		// Cmd: For network test
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDataTestRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDataTestRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInTestData,System.Byte[] InTestData );



		// Cmd: Write All!! User Score and Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDebugPrintALLRankingRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDebugPrintALLRankingRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrLogin : SendMessage




} // namespace SF.Net


