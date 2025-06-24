////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Generic Network RPC send adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using SF;
using SF.Flat;
using SF.Flat.Generic;
#nullable enable



namespace SF.Net
{
 

	public class GenericRPCSendAdapter : RPCAdapter
	{
 


		public  GenericRPCSendAdapter()
		{
 		} // public  GenericRPCSendAdapter()
		public  GenericRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  GenericRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Generic failure message
		public Result  GenericFailureCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.GenericFailureCmd.StartGenericFailureCmd(builder);
			var packetOffset = SF.Flat.Generic.GenericFailureCmd.EndGenericFailureCmd(builder);
			result = SendMessage(MessageIDGeneric.GenericFailureCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GenericFailureCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Generic transaction result
		public Result  GenericTransactionCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.GenericTransactionCmd.StartGenericTransactionCmd(builder);
			var packetOffset = SF.Flat.Generic.GenericTransactionCmd.EndGenericTransactionCmd(builder);
			result = SendMessage(MessageIDGeneric.GenericTransactionCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GenericTransactionCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// C2S: Client heartbeat
		public Result  HeartbeatC2SEvt(  )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.HeartbeatC2SEvt.StartHeartbeatC2SEvt(builder);
			var packetOffset = SF.Flat.Generic.HeartbeatC2SEvt.EndHeartbeatC2SEvt(builder);
			result = SendMessage(MessageIDGeneric.HeartbeatC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  HeartbeatC2SEvt(  )


		// Cmd: Post log data through gateway
		public Result  PostLogDataCmd( SF.TransactionID InTransactionID, System.String InDestLogChannel, System.Byte[] InMessageData, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var DestLogChannelOffset = builder.CreateString(InDestLogChannel);
			var MessageDataOffset = builder.Createuint8Vector(InMessageData);
			SF.Flat.Generic.PostLogDataCmd.StartPostLogDataCmd(builder);
			SF.Flat.Generic.PostLogDataCmd.AddDestLogChannel(builder, DestLogChannelOffset);
			SF.Flat.Generic.PostLogDataCmd.AddMessageData(builder, MessageDataOffset);
			var packetOffset = SF.Flat.Generic.PostLogDataCmd.EndPostLogDataCmd(builder);
			result = SendMessage(MessageIDGeneric.PostLogDataCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PostLogDataCmd( SF.TransactionID InTransactionID, System.String InDestLogChannel, System.Byte[] InMessageData, Action<SFMessage>? callback = null )

	}; // public class GenericRPCSendAdapter : RPCAdapter
	public class GenericSvrRPCSendAdapter : RPCAdapter
	{
 


		public  GenericSvrRPCSendAdapter()
		{
 		} // public  GenericSvrRPCSendAdapter()
		public  GenericSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  GenericSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Generic failure message
		public Result  GenericFailureRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.GenericFailureRes.StartGenericFailureRes(builder);
			var packetOffset = SF.Flat.Generic.GenericFailureRes.EndGenericFailureRes(builder);
			result = SendMessage(MessageIDGeneric.GenericFailureRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GenericFailureRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Generic transaction result
		public Result  GenericTransactionRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.TransactionID InFinishedTransaction, System.String InSignature )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var FinishedTransactionOffset = builder.CreateTransactionID(InFinishedTransaction);
			var SignatureOffset = builder.CreateString(InSignature);
			SF.Flat.Generic.GenericTransactionRes.StartGenericTransactionRes(builder);
			SF.Flat.Generic.GenericTransactionRes.AddFinishedTransaction(builder, FinishedTransactionOffset);
			SF.Flat.Generic.GenericTransactionRes.AddSignature(builder, SignatureOffset);
			var packetOffset = SF.Flat.Generic.GenericTransactionRes.EndGenericTransactionRes(builder);
			result = SendMessage(MessageIDGeneric.GenericTransactionRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GenericTransactionRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.TransactionID InFinishedTransaction, System.String InSignature )


		// Cmd: Post log data through gateway
		public Result  PostLogDataRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.PostLogDataRes.StartPostLogDataRes(builder);
			var packetOffset = SF.Flat.Generic.PostLogDataRes.EndPostLogDataRes(builder);
			result = SendMessage(MessageIDGeneric.PostLogDataRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PostLogDataRes( SF.TransactionID InTransactionID, SF.Result InResult )


	}; // public class GenericSvrRPCSendAdapter : RPCAdapter




} // namespace SF.Net
#nullable restore


