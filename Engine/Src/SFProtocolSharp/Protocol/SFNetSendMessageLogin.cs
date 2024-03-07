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

		// Cmd: Login with ID/PW request
		public Result  LoginCmd( System.String Inuser_id, System.String Inpassword, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LoginCmd(InTransactionID, Inuser_id, Inpassword, InGameID, callback);
		} // public Result  LoginCmd( System.String Inuser_id, System.String Inpassword, System.String InGameID, Action<SFMessage>? callback = null )
		public Result  LoginCmd( SF.TransactionID InTransactionID, System.String Inuser_id, System.String Inpassword, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_LoginLoginCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(Inuser_id + "\0"),System.Text.Encoding.UTF8.GetBytes(Inpassword + "\0"),System.Text.Encoding.UTF8.GetBytes(InGameID + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.LoginCmd, callback);
			return result;
		} // public Result  LoginCmd( SF.TransactionID InTransactionID, System.String Inuser_id, System.String Inpassword, System.String InGameID, Action<SFMessage>? callback = null )

		// Cmd: Login with steam login info
		public Result  LoginWithSteamCmd( System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LoginWithSteamCmd(InTransactionID, InSteamAppID, InSteamPlayerID, InSteamPlayerName, InSteamPlayerToken, InGameID, callback);
		} // public Result  LoginWithSteamCmd( System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )
		public Result  LoginWithSteamCmd( SF.TransactionID InTransactionID, System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_LoginLoginWithSteamCmd(m_Connection.NativeHandle,ref InTransactionID, InSteamAppID, InSteamPlayerID,System.Text.Encoding.UTF8.GetBytes(InSteamPlayerName + "\0"),System.Text.Encoding.UTF8.GetBytes(InSteamPlayerToken + "\0"),System.Text.Encoding.UTF8.GetBytes(InGameID + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDLogin.LoginWithSteamCmd, callback);
			return result;
		} // public Result  LoginWithSteamCmd( SF.TransactionID InTransactionID, System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, System.String InSteamPlayerName, System.String InSteamPlayerToken, System.String InGameID, Action<SFMessage>? callback = null )

		#region Native Interfaces 
		// Cmd: Login with ID/PW request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] Inuser_id, [MarshalAs(UnmanagedType.LPArray)] byte[] Inpassword, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameID );


		// Cmd: Login with steam login info
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginWithSteamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginWithSteamCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InSteamAppID, System.UInt64 InSteamPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSteamPlayerName, [MarshalAs(UnmanagedType.LPArray)] byte[] InSteamPlayerToken, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameID );


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

		// Cmd: Login with ID/PW request
		public Result  LoginRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_LoginLoginRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InAccountID, InAuthTicket,System.Text.Encoding.UTF8.GetBytes(InBannedReason + "\0"),System.Text.Encoding.UTF8.GetBytes(InGameServerAddress + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.LoginRes);
			return result;
		} // public Result  LoginRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )


		// Cmd: Login with steam login info
		public Result  LoginWithSteamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_LoginLoginWithSteamRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InAccountID, InAuthTicket,System.Text.Encoding.UTF8.GetBytes(InBannedReason + "\0"),System.Text.Encoding.UTF8.GetBytes(InGameServerAddress + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDLogin.LoginWithSteamRes);
			return result;
		} // public Result  LoginWithSteamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InAccountID, System.UInt64 InAuthTicket, System.String InBannedReason, System.String InGameServerAddress )


		#region Native Interfaces 
		// Cmd: Login with ID/PW request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.UInt64 InAccountID, System.UInt64 InAuthTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InBannedReason, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameServerAddress );



		// Cmd: Login with steam login info
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_LoginLoginWithSteamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_LoginLoginWithSteamRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.UInt64 InAccountID, System.UInt64 InAuthTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InBannedReason, [MarshalAs(UnmanagedType.LPArray)] byte[] InGameServerAddress );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrLogin : SendMessage




} // namespace SF.Net
#nullable restore


