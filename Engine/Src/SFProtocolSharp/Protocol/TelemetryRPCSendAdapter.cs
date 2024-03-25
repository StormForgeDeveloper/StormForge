////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Telemetry Network RPC send adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using SF;
using SF.Flat;
using SF.Flat.Telemetry;
#nullable enable



namespace SF.Net
{
 

	public class TelemetryRPCSendAdapter : RPCAdapter
	{
 


		public  TelemetryRPCSendAdapter()
		{
 		} // public  TelemetryRPCSendAdapter()
		public  TelemetryRPCSendAdapter( SF.SFConnection connection ) : base(connection)
		{
 		} // public  TelemetryRPCSendAdapter( SF.SFConnection connection ) : base(connection)

		// Cmd: Post telemetry event
		public Result  PostEventCmd( System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, SF.AccountID InAccountID, System.Boolean InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PostEventCmd(InTransactionID, InEventName, InTimeStamp, InAppID, InMachineID, InEventID, InAccountID, InIsPlayEvent, InSessionID, InAttributes, callback);
		} // public Result  PostEventCmd( System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, SF.AccountID InAccountID, System.Boolean InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )
		public Result  PostEventCmd( SF.TransactionID InTransactionID, System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, SF.AccountID InAccountID, System.Boolean InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var EventNameOffset = builder.CreateString(InEventName);
			var AppIDOffset = builder.CreateString(InAppID);
			var MachineIDOffset = builder.CreateString(InMachineID);
			var AccountIDOffset = builder.CreateAccountID(InAccountID);
			var SessionIDOffset = builder.Createuint8Vector(InSessionID);
			var AttributesOffset = builder.CreateNamedVariableVector(InAttributes);
			SF.Flat.Telemetry.PostEventCmd.StartPostEventCmd(builder);
			SF.Flat.Telemetry.PostEventCmd.AddEventName(builder, EventNameOffset);
			SF.Flat.Telemetry.PostEventCmd.AddTimeStamp(builder, InTimeStamp);
			SF.Flat.Telemetry.PostEventCmd.AddAppId(builder, AppIDOffset);
			SF.Flat.Telemetry.PostEventCmd.AddMachineId(builder, MachineIDOffset);
			SF.Flat.Telemetry.PostEventCmd.AddEventId(builder, InEventID);
			SF.Flat.Telemetry.PostEventCmd.AddAccountId(builder, AccountIDOffset);
			SF.Flat.Telemetry.PostEventCmd.AddIsPlayEvent(builder, InIsPlayEvent);
			SF.Flat.Telemetry.PostEventCmd.AddSessionId(builder, SessionIDOffset);
			SF.Flat.Telemetry.PostEventCmd.AddAttributes(builder, AttributesOffset);
			var packetOffset = SF.Flat.Telemetry.PostEventCmd.EndPostEventCmd(builder);
			result = SendMessage(MessageIDTelemetry.PostEventCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PostEventCmd( SF.TransactionID InTransactionID, System.String InEventName, System.UInt64 InTimeStamp, System.String InAppID, System.String InMachineID, System.UInt32 InEventID, SF.AccountID InAccountID, System.Boolean InIsPlayEvent, System.Byte[] InSessionID, SF.NamedVariable[] InAttributes, Action<SFMessage>? callback = null )

	}; // public class TelemetryRPCSendAdapter : RPCAdapter
	public class TelemetrySvrRPCSendAdapter : RPCAdapter
	{
 


		public  TelemetrySvrRPCSendAdapter()
		{
 		} // public  TelemetrySvrRPCSendAdapter()
		public  TelemetrySvrRPCSendAdapter( SF.SFConnection connection ) : base(connection)
		{
 		} // public  TelemetrySvrRPCSendAdapter( SF.SFConnection connection ) : base(connection)

		// Cmd: Post telemetry event
		public Result  PostEventRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Telemetry.PostEventRes.StartPostEventRes(builder);
			var packetOffset = SF.Flat.Telemetry.PostEventRes.EndPostEventRes(builder);
			result = SendMessage(MessageIDTelemetry.PostEventRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PostEventRes( SF.TransactionID InTransactionID, SF.Result InResult )


	}; // public class TelemetrySvrRPCSendAdapter : RPCAdapter




} // namespace SF.Net
#nullable restore


