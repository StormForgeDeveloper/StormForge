////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
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
#nullable enable



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
		public int  LoginCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.String InID, System.String InPassword, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginLoginCmd(m_Connection.NativeHandle,ref InTransactionID, InGameID,System.Text.Encoding.UTF8.GetBytes(InID + "\0"),System.Text.Encoding.UTF8.GetBytes(InPassword + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.LoginCmd, callback);
			return result;
		} // public int  LoginCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.String InID, System.String InPassword, Action<SFMessage>? callback = null )

		// Cmd: Login request with Facebook UID
		public int  LoginByFacebookCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.UInt64 InUID, System.String InFaceBookName, System.String InEMail, System.String InFacebookToken, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginLoginByFacebookCmd(m_Connection.NativeHandle,ref InTransactionID, InGameID, InUID,System.Text.Encoding.UTF8.GetBytes(InFaceBookName + "\0"),System.Text.Encoding.UTF8.GetBytes(InEMail + "\0"),System.Text.Encoding.UTF8.GetBytes(InFacebookToken + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.LoginByFacebookCmd, callback);
			return result;
		} // public int  LoginByFacebookCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.UInt64 InUID, System.String InFaceBookName, System.String InEMail, System.String InFacebookToken, Action<SFMessage>? callback = null )

		// Cmd: Login request with Facebook UID
		public int  LoginBySteamCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.UInt64 InSteamUserID, System.String InSteamUserName, System.String InSteamUserToken, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginLoginBySteamCmd(m_Connection.NativeHandle,ref InTransactionID, InGameID, InSteamUserID,System.Text.Encoding.UTF8.GetBytes(InSteamUserName + "\0"),System.Text.Encoding.UTF8.GetBytes(InSteamUserToken + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.LoginBySteamCmd, callback);
			return result;
		} // public int  LoginBySteamCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.UInt64 InSteamUserID, System.String InSteamUserName, System.String InSteamUserToken, Action<SFMessage>? callback = null )

		// Cmd: Login request
		public int  CreateRandomUserCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.String InCellPhone, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginCreateRandomUserCmd(m_Connection.NativeHandle,ref InTransactionID, InGameID,System.Text.Encoding.UTF8.GetBytes(InCellPhone + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.CreateRandomUserCmd, callback);
			return result;
		} // public int  CreateRandomUserCmd( SF.TransactionID InTransactionID, System.UInt32 InGameID, System.String InCellPhone, Action<SFMessage>? callback = null )

		// Cmd: Update my score and Get Ranking list
		public int  UpdateMyScoreCmd( SF.TransactionID InTransactionID, System.UInt64 InRankingScore, SF.RankingType InRankingType, System.UInt16 InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginUpdateMyScoreCmd(m_Connection.NativeHandle,ref InTransactionID, InRankingScore,(int) InRankingType, InCount);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.UpdateMyScoreCmd, callback);
			return result;
		} // public int  UpdateMyScoreCmd( SF.TransactionID InTransactionID, System.UInt64 InRankingScore, SF.RankingType InRankingType, System.UInt16 InCount, Action<SFMessage>? callback = null )

		// Cmd: Get Ranking lise
		public int  GetRankingListCmd( SF.TransactionID InTransactionID, SF.RankingType InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginGetRankingListCmd(m_Connection.NativeHandle,ref InTransactionID,(int) InRankingType, InBaseRanking, InCount);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.GetRankingListCmd, callback);
			return result;
		} // public int  GetRankingListCmd( SF.TransactionID InTransactionID, SF.RankingType InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )

		// Cmd: For network test
		public int  DataTestCmd( SF.TransactionID InTransactionID, System.Byte[] InTestData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginDataTestCmd(m_Connection.NativeHandle,ref InTransactionID,(ushort)InTestData.Length, InTestData);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.DataTestCmd, callback);
			return result;
		} // public int  DataTestCmd( SF.TransactionID InTransactionID, System.Byte[] InTestData, Action<SFMessage>? callback = null )

		// C2S: Heartbeat
		public int  HeartbeatC2SEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginHeartbeatC2SEvt(m_Connection.NativeHandle);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.HeartbeatC2SEvt);
			return result;
		} // public int  HeartbeatC2SEvt(  )


		// Cmd: Write All!! User Score and Ranking list
		public int  DebugPrintALLRankingCmd( SF.TransactionID InTransactionID, System.String InFileName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginDebugPrintALLRankingCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InFileName + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.DebugPrintALLRankingCmd, callback);
			return result;
		} // public int  DebugPrintALLRankingCmd( SF.TransactionID InTransactionID, System.String InFileName, Action<SFMessage>? callback = null )

		#region Native Interfaces 
		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InGameID, [MarshalAs(UnmanagedType.LPArray)] byte[] InID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPassword );


		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginByFacebookCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginByFacebookCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InGameID, System.UInt64 InUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InFaceBookName, [MarshalAs(UnmanagedType.LPArray)] byte[] InEMail, [MarshalAs(UnmanagedType.LPArray)] byte[] InFacebookToken );


		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginBySteamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginBySteamCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InGameID, System.UInt64 InSteamUserID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSteamUserName, [MarshalAs(UnmanagedType.LPArray)] byte[] InSteamUserToken );


		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginCreateRandomUserCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginCreateRandomUserCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InGameID, [MarshalAs(UnmanagedType.LPArray)] byte[] InCellPhone );


		// Cmd: Update my score and Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginUpdateMyScoreCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginUpdateMyScoreCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InRankingScore, int InRankingType, System.UInt16 InCount );


		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginGetRankingListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginGetRankingListCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, int InRankingType, System.Byte InBaseRanking, System.Byte InCount );


		// Cmd: For network test
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDataTestCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDataTestCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt16 _sizeOfInTestData,System.Byte[] InTestData );


		// C2S: Heartbeat
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginHeartbeatC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginHeartbeatC2SEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Write All!! User Score and Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDebugPrintALLRankingCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDebugPrintALLRankingCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InFileName );


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
		public int  LoginRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, System.String InErrorReason )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginLoginRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InGameServerPublicAddress + "\0"), InAccID, InTicket, InLoginEntityUID,System.Text.Encoding.UTF8.GetBytes(InErrorReason + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.LoginRes);
			return result;
		} // public int  LoginRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, System.String InErrorReason )


		// Cmd: Login request with Facebook UID
		public int  LoginByFacebookRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, System.String InErrorReason )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginLoginByFacebookRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InGameServerPublicAddress + "\0"), InAccID, InTicket, InLoginEntityUID,System.Text.Encoding.UTF8.GetBytes(InErrorReason + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.LoginByFacebookRes);
			return result;
		} // public int  LoginByFacebookRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, System.String InErrorReason )


		// Cmd: Login request with Facebook UID
		public int  LoginBySteamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, System.String InErrorReason )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginLoginBySteamRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InGameServerPublicAddress + "\0"), InAccID, InTicket, InLoginEntityUID,System.Text.Encoding.UTF8.GetBytes(InErrorReason + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.LoginBySteamRes);
			return result;
		} // public int  LoginBySteamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, System.String InErrorReason )


		// Cmd: Login request
		public int  CreateRandomUserRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginCreateRandomUserRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InGameServerPublicAddress + "\0"), InAccID, InTicket, InLoginEntityUID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.CreateRandomUserRes);
			return result;
		} // public int  CreateRandomUserRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )


		// Cmd: Update my score and Get Ranking list
		public int  UpdateMyScoreRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginUpdateMyScoreRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.UpdateMyScoreRes);
			return result;
		} // public int  UpdateMyScoreRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: Get Ranking lise
		public int  GetRankingListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginGetRankingListRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.GetRankingListRes);
			return result;
		} // public int  GetRankingListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: For network test
		public int  DataTestRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.Byte[] InTestData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginDataTestRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InTestData.Length, InTestData);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.DataTestRes);
			return result;
		} // public int  DataTestRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.Byte[] InTestData )


		// Cmd: Write All!! User Score and Ranking list
		public int  DebugPrintALLRankingRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_LoginDebugPrintALLRankingRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.DebugPrintALLRankingRes);
			return result;
		} // public int  DebugPrintALLRankingRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		#region Native Interfaces 
		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InErrorReason );



		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginByFacebookRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginByFacebookRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InErrorReason );



		// Cmd: Login request with Facebook UID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginBySteamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginBySteamRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InErrorReason );



		// Cmd: Login request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginCreateRandomUserRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginCreateRandomUserRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameServerPublicAddress, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );



		// Cmd: Update my score and Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginUpdateMyScoreRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginUpdateMyScoreRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRanking,SF.TotalRankingPlayerInformation[] InRanking );



		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginGetRankingListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginGetRankingListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRanking,SF.TotalRankingPlayerInformation[] InRanking );



		// Cmd: For network test
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDataTestRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDataTestRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInTestData,System.Byte[] InTestData );



		// Cmd: Write All!! User Score and Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginDebugPrintALLRankingRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginDebugPrintALLRankingRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrLogin : SendMessage




} // namespace SF.Net
#nullable restore


