////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Telemetry Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;
#nullable enable



namespace SF.Net
{
 

	public class SendMessageTelemetry : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageTelemetry()
		{
 		} // public  SendMessageTelemetry()
		public  SendMessageTelemetry( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageTelemetry( SF.SFConnection connection ) : base(connection)

		// Cmd: Post telemetry event
		public Result  PostEventCmd( System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, System.UInt64 InAccountID, System.Byte InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PostEventCmd(InTransactionID, InEventName, InTimeStamp, InAppID, InMachineID, InEventID, InAccountID, InIsPlayEvent, InSessionID, InAttributes, callback);
		} // public Result  PostEventCmd( System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, System.UInt64 InAccountID, System.Byte InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )
		public Result  PostEventCmd( SF.TransactionID InTransactionID, System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, System.UInt64 InAccountID, System.Byte InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_TelemetryPostEventCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InEventName + "\0"), InTimeStamp,System.Text.Encoding.UTF8.GetBytes(InAppID + "\0"),System.Text.Encoding.UTF8.GetBytes(InMachineID + "\0"), InEventID, InAccountID, InIsPlayEvent,(ushort)InSessionID.Length, InSessionID,(ushort)InAttributes.Length, InAttributes));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDTelemetry.PostEventCmd, callback);
			return result;
		} // public Result  PostEventCmd( SF.TransactionID InTransactionID, System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, System.UInt64 InAccountID, System.Byte InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )

		#region Native Interfaces 
		// Cmd: Post telemetry event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_TelemetryPostEventCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_TelemetryPostEventCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InEventName, System.UInt64 InTimeStamp, [MarshalAs(UnmanagedType.LPArray)] byte[] InAppID, [MarshalAs(UnmanagedType.LPArray)] byte[] InMachineID, System.UInt32 InEventID, System.UInt64 InAccountID, System.Byte InIsPlayEvent, System.UInt16 _sizeOfInSessionID,System.Byte[] InSessionID, System.UInt16 _sizeOfInAttributes,SF.NamedVariable[] InAttributes );


		#endregion //Native Interfaces 
	}; // public class SendMessageTelemetry : SendMessage
	public class SendMessageSvrTelemetry : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageSvrTelemetry()
		{
 		} // public  SendMessageSvrTelemetry()
		public  SendMessageSvrTelemetry( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageSvrTelemetry( SF.SFConnection connection ) : base(connection)

		// Cmd: Post telemetry event
		public Result  PostEventRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_TelemetryPostEventRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDTelemetry.PostEventRes);
			return result;
		} // public Result  PostEventRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		#region Native Interfaces 
		// Cmd: Post telemetry event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_TelemetryPostEventRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_TelemetryPostEventRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrTelemetry : SendMessage




} // namespace SF.Net
#nullable restore


