////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
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
		public int  GenericFailureCmd( SF.SFRouteContext InRouteContext, System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GenericGenericFailureCmd(m_Connection.NativeHandle,ref InRouteContext, InTransactionID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDGeneric.GenericFailureCmd);
			return result;
		} // public int  GenericFailureCmd( SF.SFRouteContext InRouteContext, System.UInt64 InTransactionID )

		#region Native Interfaces 
		// Cmd: Generic failure message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GenericGenericFailureCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GenericGenericFailureCmd(System.IntPtr InNativeConnectionHandle, ref SF.SFRouteContext InRouteContext, System.UInt64 InTransactionID );


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
		public int  GenericFailureRes( SF.SFRouteContext InRouteContext, System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GenericGenericFailureRes(m_Connection.NativeHandle,ref InRouteContext, InTransactionID, InResult);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDGeneric.GenericFailureRes);
			return result;
		} // public int  GenericFailureRes( SF.SFRouteContext InRouteContext, System.UInt64 InTransactionID, System.Int32 InResult )


		#region Native Interfaces 
		// Cmd: Generic failure message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GenericGenericFailureRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GenericGenericFailureRes(System.IntPtr InNativeConnectionHandle, ref SF.SFRouteContext InRouteContext, System.UInt64 InTransactionID, System.Int32 InResult );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrGeneric : SendMessage




} // namespace SF.Net


