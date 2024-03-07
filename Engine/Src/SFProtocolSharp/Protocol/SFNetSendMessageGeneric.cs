////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Generic Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;
#nullable enable



namespace SF.Net
{
 

	public class SendMessageGeneric : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageGeneric()
		{
 		} // public  SendMessageGeneric()
		public  SendMessageGeneric( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageGeneric( SF.SFConnection connection ) : base(connection)

		// Cmd: Generic failure message
		public Result  GenericFailureCmd( SF.SFRouteContext InRouteContext, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GenericFailureCmd(InRouteContext, InTransactionID, callback);
		} // public Result  GenericFailureCmd( SF.SFRouteContext InRouteContext, Action<SFMessage>? callback = null )
		public Result  GenericFailureCmd( SF.SFRouteContext InRouteContext, SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GenericGenericFailureCmd(m_Connection.NativeHandle,ref InRouteContext,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGeneric.GenericFailureCmd, callback);
			return result;
		} // public Result  GenericFailureCmd( SF.SFRouteContext InRouteContext, SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		#region Native Interfaces 
		// Cmd: Generic failure message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GenericGenericFailureCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GenericGenericFailureCmd(System.IntPtr InNativeConnectionHandle, ref SF.SFRouteContext InRouteContext, ref SF.TransactionID InTransactionID );


		#endregion //Native Interfaces 
	}; // public class SendMessageGeneric : SendMessage
	public class SendMessageSvrGeneric : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageSvrGeneric()
		{
 		} // public  SendMessageSvrGeneric()
		public  SendMessageSvrGeneric( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageSvrGeneric( SF.SFConnection connection ) : base(connection)

		// Cmd: Generic failure message
		public Result  GenericFailureRes( SF.SFRouteContext InRouteContext, SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GenericGenericFailureRes(m_Connection.NativeHandle,ref InRouteContext,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGeneric.GenericFailureRes);
			return result;
		} // public Result  GenericFailureRes( SF.SFRouteContext InRouteContext, SF.TransactionID InTransactionID, System.Int32 InResult )


		#region Native Interfaces 
		// Cmd: Generic failure message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GenericGenericFailureRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GenericGenericFailureRes(System.IntPtr InNativeConnectionHandle, ref SF.SFRouteContext InRouteContext, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrGeneric : SendMessage




} // namespace SF.Net
#nullable restore


