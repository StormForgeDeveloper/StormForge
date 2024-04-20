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
		public Result  GenericFailureCmd( Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GenericFailureCmd(InTransactionID, callback);
		} // public Result  GenericFailureCmd( Action<SFMessage>? callback = null )
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
		public Result  GenericTransactionCmd( Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GenericTransactionCmd(InTransactionID, callback);
		} // public Result  GenericTransactionCmd( Action<SFMessage>? callback = null )
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

		// Cmd: Message bus send message warpper through gateway. it conveys other message inside
		public Result  MessageBusSendCmd( Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return MessageBusSendCmd(InTransactionID, callback);
		} // public Result  MessageBusSendCmd( Action<SFMessage>? callback = null )
		public Result  MessageBusSendCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.MessageBusSendCmd.StartMessageBusSendCmd(builder);
			var packetOffset = SF.Flat.Generic.MessageBusSendCmd.EndMessageBusSendCmd(builder);
			result = SendMessage(MessageIDGeneric.MessageBusSendCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  MessageBusSendCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Listen to the message
		public Result  MessageBusListenCmd( Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return MessageBusListenCmd(InTransactionID, callback);
		} // public Result  MessageBusListenCmd( Action<SFMessage>? callback = null )
		public Result  MessageBusListenCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.MessageBusListenCmd.StartMessageBusListenCmd(builder);
			var packetOffset = SF.Flat.Generic.MessageBusListenCmd.EndMessageBusListenCmd(builder);
			result = SendMessage(MessageIDGeneric.MessageBusListenCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  MessageBusListenCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Post log data through gateway
		public Result  PostLogDataCmd( Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PostLogDataCmd(InTransactionID, callback);
		} // public Result  PostLogDataCmd( Action<SFMessage>? callback = null )
		public Result  PostLogDataCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.Generic.PostLogDataCmd.StartPostLogDataCmd(builder);
			var packetOffset = SF.Flat.Generic.PostLogDataCmd.EndPostLogDataCmd(builder);
			result = SendMessage(MessageIDGeneric.PostLogDataCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  PostLogDataCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

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


		// Cmd: Message bus send message warpper through gateway. it conveys other message inside
		public Result  MessageBusSendRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InDestChannel, System.Byte[] InMessageData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var DestChannelOffset = builder.CreateString(InDestChannel);
			var MessageDataOffset = builder.Createuint8Vector(InMessageData);
			SF.Flat.Generic.MessageBusSendRes.StartMessageBusSendRes(builder);
			SF.Flat.Generic.MessageBusSendRes.AddDestChannel(builder, DestChannelOffset);
			SF.Flat.Generic.MessageBusSendRes.AddMessageData(builder, MessageDataOffset);
			var packetOffset = SF.Flat.Generic.MessageBusSendRes.EndMessageBusSendRes(builder);
			result = SendMessage(MessageIDGeneric.MessageBusSendRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  MessageBusSendRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InDestChannel, System.Byte[] InMessageData )


		// Cmd: Listen to the message
		public Result  MessageBusListenRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InChannelToListen )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ChannelToListenOffset = builder.CreateString(InChannelToListen);
			SF.Flat.Generic.MessageBusListenRes.StartMessageBusListenRes(builder);
			SF.Flat.Generic.MessageBusListenRes.AddChannelToListen(builder, ChannelToListenOffset);
			var packetOffset = SF.Flat.Generic.MessageBusListenRes.EndMessageBusListenRes(builder);
			result = SendMessage(MessageIDGeneric.MessageBusListenRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  MessageBusListenRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InChannelToListen )


		// Cmd: Post log data through gateway
		public Result  PostLogDataRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InDestLogChannel, System.Byte[] InMessageData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var DestLogChannelOffset = builder.CreateString(InDestLogChannel);
			var MessageDataOffset = builder.Createuint8Vector(InMessageData);
			SF.Flat.Generic.PostLogDataRes.StartPostLogDataRes(builder);
			SF.Flat.Generic.PostLogDataRes.AddDestLogChannel(builder, DestLogChannelOffset);
			SF.Flat.Generic.PostLogDataRes.AddMessageData(builder, MessageDataOffset);
			var packetOffset = SF.Flat.Generic.PostLogDataRes.EndPostLogDataRes(builder);
			result = SendMessage(MessageIDGeneric.PostLogDataRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  PostLogDataRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InDestLogChannel, System.Byte[] InMessageData )


	}; // public class GenericSvrRPCSendAdapter : RPCAdapter




} // namespace SF.Net
#nullable restore


