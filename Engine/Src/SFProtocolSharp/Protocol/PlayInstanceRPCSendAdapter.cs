////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network RPC send adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using SF;
using SF.Flat;
using SF.Flat.PlayInstance;
#nullable enable



namespace SF.Net
{
 

	public class PlayInstanceRPCSendAdapter : RPCAdapter
	{
 


		public  PlayInstanceRPCSendAdapter()
		{
 		} // public  PlayInstanceRPCSendAdapter()
		public  PlayInstanceRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  PlayInstanceRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Player Join request.
		public Result  JoinPlayInstanceCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPlayerIdentifier, System.UInt32 InCustomZoneDataVersion, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinPlayInstanceCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InPlayerIdentifier, InCustomZoneDataVersion, callback);
		} // public Result  JoinPlayInstanceCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPlayerIdentifier, System.UInt32 InCustomZoneDataVersion, Action<SFMessage>? callback = null )
		public Result  JoinPlayInstanceCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPlayerIdentifier, System.UInt32 InCustomZoneDataVersion, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var PlayerIdentifierOffset = builder.CreateString(InPlayerIdentifier);
			SF.Flat.PlayInstance.JoinPlayInstanceCmd.StartJoinPlayInstanceCmd(builder);
			SF.Flat.PlayInstance.JoinPlayInstanceCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceCmd.AddPlayerIdentifier(builder, PlayerIdentifierOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceCmd.AddCustomZoneDataVersion(builder, InCustomZoneDataVersion);
			var packetOffset = SF.Flat.PlayInstance.JoinPlayInstanceCmd.EndJoinPlayInstanceCmd(builder);
			result = SendMessage(MessageIDPlayInstance.JoinPlayInstanceCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  JoinPlayInstanceCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPlayerIdentifier, System.UInt32 InCustomZoneDataVersion, Action<SFMessage>? callback = null )

		// C2S: Play packet
		public Result  PlayPacketC2SEvt( SF.GameInstanceUID InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PayloadOffset = builder.Createuint8Vector(InPayload);
			SF.Flat.PlayInstance.PlayPacketC2SEvt.StartPlayPacketC2SEvt(builder);
			SF.Flat.PlayInstance.PlayPacketC2SEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.PlayPacketC2SEvt.AddSenderEndpointId(builder, InSenderEndpointID);
			SF.Flat.PlayInstance.PlayPacketC2SEvt.AddTargetEndpointMask(builder, InTargetEndpointMask);
			SF.Flat.PlayInstance.PlayPacketC2SEvt.AddPayload(builder, PayloadOffset);
			var packetOffset = SF.Flat.PlayInstance.PlayPacketC2SEvt.EndPlayPacketC2SEvt(builder);
			result = SendMessage(MessageIDPlayInstance.PlayPacketC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PlayPacketC2SEvt( SF.GameInstanceUID InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )


		// C2S: Player Movement
		public Result  PlayerMovementC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, ActorMovement InMovement )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var MovementOffset = builder.CreateActorMovement(InMovement);
			SF.Flat.PlayInstance.PlayerMovementC2SEvt.StartPlayerMovementC2SEvt(builder);
			SF.Flat.PlayInstance.PlayerMovementC2SEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.PlayerMovementC2SEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.PlayerMovementC2SEvt.AddMovement(builder, MovementOffset);
			var packetOffset = SF.Flat.PlayInstance.PlayerMovementC2SEvt.EndPlayerMovementC2SEvt(builder);
			result = SendMessage(MessageIDPlayInstance.PlayerMovementC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PlayerMovementC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, ActorMovement InMovement )


		// C2S: Reliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public Result  ClientSyncReliableC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InSyncData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var SyncDataOffset = builder.CreateVariableTable(InSyncData);
			SF.Flat.PlayInstance.ClientSyncReliableC2SEvt.StartClientSyncReliableC2SEvt(builder);
			SF.Flat.PlayInstance.ClientSyncReliableC2SEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.ClientSyncReliableC2SEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.ClientSyncReliableC2SEvt.AddSyncData(builder, SyncDataOffset);
			var packetOffset = SF.Flat.PlayInstance.ClientSyncReliableC2SEvt.EndClientSyncReliableC2SEvt(builder);
			result = SendMessage(MessageIDPlayInstance.ClientSyncReliableC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ClientSyncReliableC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InSyncData )


		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public Result  ClientSyncC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InSyncData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var SyncDataOffset = builder.CreateVariableTable(InSyncData);
			SF.Flat.PlayInstance.ClientSyncC2SEvt.StartClientSyncC2SEvt(builder);
			SF.Flat.PlayInstance.ClientSyncC2SEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.ClientSyncC2SEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.ClientSyncC2SEvt.AddSyncData(builder, SyncDataOffset);
			var packetOffset = SF.Flat.PlayInstance.ClientSyncC2SEvt.EndClientSyncC2SEvt(builder);
			result = SendMessage(MessageIDPlayInstance.ClientSyncC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ClientSyncC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InSyncData )


		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		public Result  SetCharacterPublicMessageCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SetCharacterPublicMessageCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InPublicMessage, callback);
		} // public Result  SetCharacterPublicMessageCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )
		public Result  SetCharacterPublicMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var PublicMessageOffset = builder.CreateString(InPublicMessage);
			SF.Flat.PlayInstance.SetCharacterPublicMessageCmd.StartSetCharacterPublicMessageCmd(builder);
			SF.Flat.PlayInstance.SetCharacterPublicMessageCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.SetCharacterPublicMessageCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.SetCharacterPublicMessageCmd.AddPublicMessage(builder, PublicMessageOffset);
			var packetOffset = SF.Flat.PlayInstance.SetCharacterPublicMessageCmd.EndSetCharacterPublicMessageCmd(builder);
			result = SendMessage(MessageIDPlayInstance.SetCharacterPublicMessageCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  SetCharacterPublicMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )

		// Cmd: Request WhiteboardSharing
		public Result  RequestWhiteboardSharingCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestWhiteboardSharingCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InTargetPlayerID, InWhiteboardInfo, callback);
		} // public Result  RequestWhiteboardSharingCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )
		public Result  RequestWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var TargetPlayerIDOffset = builder.CreatePlayerID(InTargetPlayerID);
			var WhiteboardInfoOffset = builder.CreateVariableTable(InWhiteboardInfo);
			SF.Flat.PlayInstance.RequestWhiteboardSharingCmd.StartRequestWhiteboardSharingCmd(builder);
			SF.Flat.PlayInstance.RequestWhiteboardSharingCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.RequestWhiteboardSharingCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.RequestWhiteboardSharingCmd.AddTargetPlayerId(builder, TargetPlayerIDOffset);
			SF.Flat.PlayInstance.RequestWhiteboardSharingCmd.AddWhiteboardInfo(builder, WhiteboardInfoOffset);
			var packetOffset = SF.Flat.PlayInstance.RequestWhiteboardSharingCmd.EndRequestWhiteboardSharingCmd(builder);
			result = SendMessage(MessageIDPlayInstance.RequestWhiteboardSharingCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RequestWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )

		// Cmd: Accept WhiteboardSharing
		public Result  AcceptWhiteboardSharingCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AcceptWhiteboardSharingCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InRequestedPlayerID, InAnswer, callback);
		} // public Result  AcceptWhiteboardSharingCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )
		public Result  AcceptWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var RequestedPlayerIDOffset = builder.CreatePlayerID(InRequestedPlayerID);
			SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd.StartAcceptWhiteboardSharingCmd(builder);
			SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd.AddRequestedPlayerId(builder, RequestedPlayerIDOffset);
			SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd.AddAnswer(builder, InAnswer);
			var packetOffset = SF.Flat.PlayInstance.AcceptWhiteboardSharingCmd.EndAcceptWhiteboardSharingCmd(builder);
			result = SendMessage(MessageIDPlayInstance.AcceptWhiteboardSharingCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  AcceptWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )

		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		public Result  CloseWhiteboardSharingCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CloseWhiteboardSharingCmd(InTransactionID, InPlayInstanceUID, InPlayerID, callback);
		} // public Result  CloseWhiteboardSharingCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		public Result  CloseWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.CloseWhiteboardSharingCmd.StartCloseWhiteboardSharingCmd(builder);
			SF.Flat.PlayInstance.CloseWhiteboardSharingCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.CloseWhiteboardSharingCmd.AddPlayerId(builder, PlayerIDOffset);
			var packetOffset = SF.Flat.PlayInstance.CloseWhiteboardSharingCmd.EndCloseWhiteboardSharingCmd(builder);
			result = SendMessage(MessageIDPlayInstance.CloseWhiteboardSharingCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CloseWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  AddWhiteboardSharingLogEntryCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AddWhiteboardSharingLogEntryCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntry, callback);
		} // public Result  AddWhiteboardSharingLogEntryCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		public Result  AddWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var LogEntryOffset = builder.CreateVariableTable(InLogEntry);
			SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryCmd.StartAddWhiteboardSharingLogEntryCmd(builder);
			SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryCmd.AddLogEntry(builder, LogEntryOffset);
			var packetOffset = SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryCmd.EndAddWhiteboardSharingLogEntryCmd(builder);
			result = SendMessage(MessageIDPlayInstance.AddWhiteboardSharingLogEntryCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  AddWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )

		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  UpdateWhiteboardSharingLogEntryCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UpdateWhiteboardSharingLogEntryCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntry, callback);
		} // public Result  UpdateWhiteboardSharingLogEntryCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		public Result  UpdateWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var LogEntryOffset = builder.CreateVariableTable(InLogEntry);
			SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd.StartUpdateWhiteboardSharingLogEntryCmd(builder);
			SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd.AddLogEntry(builder, LogEntryOffset);
			var packetOffset = SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd.EndUpdateWhiteboardSharingLogEntryCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UpdateWhiteboardSharingLogEntryCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UpdateWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )

		// Cmd: Update whiteboard log entry
		public Result  RemoveWhiteboardSharingLogEntryCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RemoveWhiteboardSharingLogEntryCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntryID, callback);
		} // public Result  RemoveWhiteboardSharingLogEntryCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )
		public Result  RemoveWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryCmd.StartRemoveWhiteboardSharingLogEntryCmd(builder);
			SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryCmd.AddLogEntryId(builder, InLogEntryID);
			var packetOffset = SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryCmd.EndRemoveWhiteboardSharingLogEntryCmd(builder);
			result = SendMessage(MessageIDPlayInstance.RemoveWhiteboardSharingLogEntryCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  RemoveWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )

		// Cmd: Occupy map object
		public Result  OccupyMapObjectCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return OccupyMapObjectCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId, callback);
		} // public Result  OccupyMapObjectCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )
		public Result  OccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.OccupyMapObjectCmd.StartOccupyMapObjectCmd(builder);
			SF.Flat.PlayInstance.OccupyMapObjectCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.OccupyMapObjectCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.OccupyMapObjectCmd.AddMapObjectId(builder, InMapObjectId);
			SF.Flat.PlayInstance.OccupyMapObjectCmd.AddUsageId(builder, InUsageId);
			var packetOffset = SF.Flat.PlayInstance.OccupyMapObjectCmd.EndOccupyMapObjectCmd(builder);
			result = SendMessage(MessageIDPlayInstance.OccupyMapObjectCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  OccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )

		// Cmd: Unoccupy map object
		public Result  UnoccupyMapObjectCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UnoccupyMapObjectCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, callback);
		} // public Result  UnoccupyMapObjectCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )
		public Result  UnoccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.UnoccupyMapObjectCmd.StartUnoccupyMapObjectCmd(builder);
			SF.Flat.PlayInstance.UnoccupyMapObjectCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UnoccupyMapObjectCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.UnoccupyMapObjectCmd.AddMapObjectId(builder, InMapObjectId);
			var packetOffset = SF.Flat.PlayInstance.UnoccupyMapObjectCmd.EndUnoccupyMapObjectCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UnoccupyMapObjectCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UnoccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )

		// Cmd: Use map object
		public Result  UseMapObjectCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UseMapObjectCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUseParameters, callback);
		} // public Result  UseMapObjectCmd( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )
		public Result  UseMapObjectCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var UseParametersOffset = builder.CreateVariableTable(InUseParameters);
			SF.Flat.PlayInstance.UseMapObjectCmd.StartUseMapObjectCmd(builder);
			SF.Flat.PlayInstance.UseMapObjectCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UseMapObjectCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.UseMapObjectCmd.AddMapObjectId(builder, InMapObjectId);
			SF.Flat.PlayInstance.UseMapObjectCmd.AddUseParameters(builder, UseParametersOffset);
			var packetOffset = SF.Flat.PlayInstance.UseMapObjectCmd.EndUseMapObjectCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UseMapObjectCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UseMapObjectCmd( SF.TransactionID InTransactionID, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )

		// Cmd: Send zone chatting
		public Result  ZoneChatCmd( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return ZoneChatCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType, InChatMetaData, InChatMessage, callback);
		} // public Result  ZoneChatCmd( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		public Result  ZoneChatCmd( SF.TransactionID InTransactionID, SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var ChatMetaDataOffset = builder.CreateVariableTable(InChatMetaData);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.PlayInstance.ZoneChatCmd.StartZoneChatCmd(builder);
			SF.Flat.PlayInstance.ZoneChatCmd.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.ZoneChatCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.ZoneChatCmd.AddMessageType(builder, InMessageType);
			SF.Flat.PlayInstance.ZoneChatCmd.AddChatMetaData(builder, ChatMetaDataOffset);
			SF.Flat.PlayInstance.ZoneChatCmd.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.PlayInstance.ZoneChatCmd.EndZoneChatCmd(builder);
			result = SendMessage(MessageIDPlayInstance.ZoneChatCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  ZoneChatCmd( SF.TransactionID InTransactionID, SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: To call general functionality
		public Result  CallFunctionCmd( System.UInt32 InFunctionName, SF.AccountID InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CallFunctionCmd(InTransactionID, InFunctionName, InPlayerID, InParameters, callback);
		} // public Result  CallFunctionCmd( System.UInt32 InFunctionName, SF.AccountID InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.AccountID InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var ParametersOffset = builder.CreateVariableTable(InParameters);
			SF.Flat.PlayInstance.CallFunctionCmd.StartCallFunctionCmd(builder);
			SF.Flat.PlayInstance.CallFunctionCmd.AddFunctionName(builder, InFunctionName);
			SF.Flat.PlayInstance.CallFunctionCmd.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.CallFunctionCmd.AddParameters(builder, ParametersOffset);
			var packetOffset = SF.Flat.PlayInstance.CallFunctionCmd.EndCallFunctionCmd(builder);
			result = SendMessage(MessageIDPlayInstance.CallFunctionCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.AccountID InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )

		// C2S: Send coded voice data to server
		public Result  SendVoiceDataC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var VoiceDataOffset = builder.Createuint8Vector(InVoiceData);
			SF.Flat.PlayInstance.SendVoiceDataC2SEvt.StartSendVoiceDataC2SEvt(builder);
			SF.Flat.PlayInstance.SendVoiceDataC2SEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.SendVoiceDataC2SEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.SendVoiceDataC2SEvt.AddFrameIndex(builder, InFrameIndex);
			SF.Flat.PlayInstance.SendVoiceDataC2SEvt.AddVoiceData(builder, VoiceDataOffset);
			var packetOffset = SF.Flat.PlayInstance.SendVoiceDataC2SEvt.EndSendVoiceDataC2SEvt(builder);
			result = SendMessage(MessageIDPlayInstance.SendVoiceDataC2SEvt, builder, packetOffset.Value);
			return result;
		} // public Result  SendVoiceDataC2SEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )


		// Cmd: UGC zone edit command
		public Result  UGCEditAddCmd( System.UInt32 InEntityType, System.UInt32 InTableId, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UGCEditAddCmd(InTransactionID, InEntityType, InTableId, InPosition, InRotation, InScale, callback);
		} // public Result  UGCEditAddCmd( System.UInt32 InEntityType, System.UInt32 InTableId, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )
		public Result  UGCEditAddCmd( SF.TransactionID InTransactionID, System.UInt32 InEntityType, System.UInt32 InTableId, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PositionOffset = builder.CreateVector4(InPosition);
			var RotationOffset = builder.CreateVector4(InRotation);
			var ScaleOffset = builder.CreateVector4(InScale);
			SF.Flat.PlayInstance.UGCEditAddCmd.StartUGCEditAddCmd(builder);
			SF.Flat.PlayInstance.UGCEditAddCmd.AddEntityType(builder, InEntityType);
			SF.Flat.PlayInstance.UGCEditAddCmd.AddTableId(builder, InTableId);
			SF.Flat.PlayInstance.UGCEditAddCmd.AddPosition(builder, PositionOffset);
			SF.Flat.PlayInstance.UGCEditAddCmd.AddRotation(builder, RotationOffset);
			SF.Flat.PlayInstance.UGCEditAddCmd.AddScale(builder, ScaleOffset);
			var packetOffset = SF.Flat.PlayInstance.UGCEditAddCmd.EndUGCEditAddCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditAddCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UGCEditAddCmd( SF.TransactionID InTransactionID, System.UInt32 InEntityType, System.UInt32 InTableId, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )

		// Cmd: UGC zone edit command
		public Result  UGCEditMoveCmd( System.UInt32 InInstanceId, System.UInt32 InEntityType, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UGCEditMoveCmd(InTransactionID, InInstanceId, InEntityType, InPosition, InRotation, InScale, callback);
		} // public Result  UGCEditMoveCmd( System.UInt32 InInstanceId, System.UInt32 InEntityType, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )
		public Result  UGCEditMoveCmd( SF.TransactionID InTransactionID, System.UInt32 InInstanceId, System.UInt32 InEntityType, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PositionOffset = builder.CreateVector4(InPosition);
			var RotationOffset = builder.CreateVector4(InRotation);
			var ScaleOffset = builder.CreateVector4(InScale);
			SF.Flat.PlayInstance.UGCEditMoveCmd.StartUGCEditMoveCmd(builder);
			SF.Flat.PlayInstance.UGCEditMoveCmd.AddInstanceId(builder, InInstanceId);
			SF.Flat.PlayInstance.UGCEditMoveCmd.AddEntityType(builder, InEntityType);
			SF.Flat.PlayInstance.UGCEditMoveCmd.AddPosition(builder, PositionOffset);
			SF.Flat.PlayInstance.UGCEditMoveCmd.AddRotation(builder, RotationOffset);
			SF.Flat.PlayInstance.UGCEditMoveCmd.AddScale(builder, ScaleOffset);
			var packetOffset = SF.Flat.PlayInstance.UGCEditMoveCmd.EndUGCEditMoveCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditMoveCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UGCEditMoveCmd( SF.TransactionID InTransactionID, System.UInt32 InInstanceId, System.UInt32 InEntityType, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, Action<SFMessage>? callback = null )

		// Cmd: UGC zone edit command
		public Result  UGCEditDeleteCmd( System.UInt32 InInstanceId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UGCEditDeleteCmd(InTransactionID, InInstanceId, callback);
		} // public Result  UGCEditDeleteCmd( System.UInt32 InInstanceId, Action<SFMessage>? callback = null )
		public Result  UGCEditDeleteCmd( SF.TransactionID InTransactionID, System.UInt32 InInstanceId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.UGCEditDeleteCmd.StartUGCEditDeleteCmd(builder);
			SF.Flat.PlayInstance.UGCEditDeleteCmd.AddInstanceId(builder, InInstanceId);
			var packetOffset = SF.Flat.PlayInstance.UGCEditDeleteCmd.EndUGCEditDeleteCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditDeleteCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UGCEditDeleteCmd( SF.TransactionID InTransactionID, System.UInt32 InInstanceId, Action<SFMessage>? callback = null )

		// Cmd: UGC zone edit command
		public Result  UGCEditClaimBackCmd( System.UInt32 InInstanceId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UGCEditClaimBackCmd(InTransactionID, InInstanceId, callback);
		} // public Result  UGCEditClaimBackCmd( System.UInt32 InInstanceId, Action<SFMessage>? callback = null )
		public Result  UGCEditClaimBackCmd( SF.TransactionID InTransactionID, System.UInt32 InInstanceId, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.UGCEditClaimBackCmd.StartUGCEditClaimBackCmd(builder);
			SF.Flat.PlayInstance.UGCEditClaimBackCmd.AddInstanceId(builder, InInstanceId);
			var packetOffset = SF.Flat.PlayInstance.UGCEditClaimBackCmd.EndUGCEditClaimBackCmd(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditClaimBackCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  UGCEditClaimBackCmd( SF.TransactionID InTransactionID, System.UInt32 InInstanceId, Action<SFMessage>? callback = null )

		// Cmd: Create stream instance
		public Result  CreateStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreateStreamCmd(InTransactionID, InTicket, InStreamName, callback);
		} // public Result  CreateStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		public Result  CreateStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNameOffset = builder.CreateString(InStreamName);
			SF.Flat.PlayInstance.CreateStreamCmd.StartCreateStreamCmd(builder);
			SF.Flat.PlayInstance.CreateStreamCmd.AddTicket(builder, InTicket);
			SF.Flat.PlayInstance.CreateStreamCmd.AddStreamName(builder, StreamNameOffset);
			var packetOffset = SF.Flat.PlayInstance.CreateStreamCmd.EndCreateStreamCmd(builder);
			result = SendMessage(MessageIDPlayInstance.CreateStreamCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  CreateStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )

		// Cmd: Open stream instance
		public Result  FindStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindStreamCmd(InTransactionID, InTicket, InStreamName, callback);
		} // public Result  FindStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		public Result  FindStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNameOffset = builder.CreateString(InStreamName);
			SF.Flat.PlayInstance.FindStreamCmd.StartFindStreamCmd(builder);
			SF.Flat.PlayInstance.FindStreamCmd.AddTicket(builder, InTicket);
			SF.Flat.PlayInstance.FindStreamCmd.AddStreamName(builder, StreamNameOffset);
			var packetOffset = SF.Flat.PlayInstance.FindStreamCmd.EndFindStreamCmd(builder);
			result = SendMessage(MessageIDPlayInstance.FindStreamCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  FindStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )

		// Cmd: Delete stream instance
		public Result  DeleteStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DeleteStreamCmd(InTransactionID, InTicket, InStreamName, callback);
		} // public Result  DeleteStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		public Result  DeleteStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNameOffset = builder.CreateString(InStreamName);
			SF.Flat.PlayInstance.DeleteStreamCmd.StartDeleteStreamCmd(builder);
			SF.Flat.PlayInstance.DeleteStreamCmd.AddTicket(builder, InTicket);
			SF.Flat.PlayInstance.DeleteStreamCmd.AddStreamName(builder, StreamNameOffset);
			var packetOffset = SF.Flat.PlayInstance.DeleteStreamCmd.EndDeleteStreamCmd(builder);
			result = SendMessage(MessageIDPlayInstance.DeleteStreamCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  DeleteStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )

		// Cmd: Get stream list
		public Result  GetStreamListCmd( System.UInt64 InTicket, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetStreamListCmd(InTransactionID, InTicket, callback);
		} // public Result  GetStreamListCmd( System.UInt64 InTicket, Action<SFMessage>? callback = null )
		public Result  GetStreamListCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, Action<SFMessage>? callback = null )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.GetStreamListCmd.StartGetStreamListCmd(builder);
			SF.Flat.PlayInstance.GetStreamListCmd.AddTicket(builder, InTicket);
			var packetOffset = SF.Flat.PlayInstance.GetStreamListCmd.EndGetStreamListCmd(builder);
			result = SendMessage(MessageIDPlayInstance.GetStreamListCmd, builder, packetOffset.Value, transactionId:InTransactionID , callback:callback);
			return result;
		} // public Result  GetStreamListCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, Action<SFMessage>? callback = null )

	}; // public class PlayInstanceRPCSendAdapter : RPCAdapter
	public class PlayInstanceSvrRPCSendAdapter : RPCAdapter
	{
 


		public  PlayInstanceSvrRPCSendAdapter()
		{
 		} // public  PlayInstanceSvrRPCSendAdapter()
		public  PlayInstanceSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)
		{
 		} // public  PlayInstanceSvrRPCSendAdapter( SF.IEndpoint endpoint ) : base(endpoint)

		// Cmd: Player Join request.
		public Result  JoinPlayInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.CharacterID InCharacterID, SF.VariableTable InCharacterPrivateData, ActorMovement InMovement )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			var CharacterPrivateDataOffset = builder.CreateVariableTable(InCharacterPrivateData);
			var MovementOffset = builder.CreateActorMovement(InMovement);
			SF.Flat.PlayInstance.JoinPlayInstanceRes.StartJoinPlayInstanceRes(builder);
			SF.Flat.PlayInstance.JoinPlayInstanceRes.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceRes.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceRes.AddCharacterId(builder, CharacterIDOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceRes.AddCharacterPrivateData(builder, CharacterPrivateDataOffset);
			SF.Flat.PlayInstance.JoinPlayInstanceRes.AddMovement(builder, MovementOffset);
			var packetOffset = SF.Flat.PlayInstance.JoinPlayInstanceRes.EndJoinPlayInstanceRes(builder);
			result = SendMessage(MessageIDPlayInstance.JoinPlayInstanceRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  JoinPlayInstanceRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.CharacterID InCharacterID, SF.VariableTable InCharacterPrivateData, ActorMovement InMovement )


		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public Result  PlayerKickedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InKickedPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var KickedPlayerIDOffset = builder.CreatePlayerID(InKickedPlayerID);
			SF.Flat.PlayInstance.PlayerKickedS2CEvt.StartPlayerKickedS2CEvt(builder);
			SF.Flat.PlayInstance.PlayerKickedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.PlayerKickedS2CEvt.AddKickedPlayerId(builder, KickedPlayerIDOffset);
			var packetOffset = SF.Flat.PlayInstance.PlayerKickedS2CEvt.EndPlayerKickedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.PlayerKickedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PlayerKickedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InKickedPlayerID )


		// S2C: New actor in get view
		public Result  NewActorInViewS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, PlayerPlatformID InPlayerPlatformId, SF.VariableTable InPublicData, SF.VariableTable InEquipData, ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var PlayerPlatformIdOffset = builder.CreatePlayerPlatformID(InPlayerPlatformId);
			var PublicDataOffset = builder.CreateVariableTable(InPublicData);
			var EquipDataOffset = builder.CreateVariableTable(InEquipData);
			var MovementOffset = builder.CreateActorMovement(InMovement);
			var StateValuesOffset = builder.CreateVariableTable(InStateValues);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.StartNewActorInViewS2CEvt(builder);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddPlayerPlatformId(builder, PlayerPlatformIdOffset);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddPublicData(builder, PublicDataOffset);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddEquipData(builder, EquipDataOffset);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddMovement(builder, MovementOffset);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddState(builder, InState);
			SF.Flat.PlayInstance.NewActorInViewS2CEvt.AddStateValues(builder, StateValuesOffset);
			var packetOffset = SF.Flat.PlayInstance.NewActorInViewS2CEvt.EndNewActorInViewS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.NewActorInViewS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  NewActorInViewS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, PlayerPlatformID InPlayerPlatformId, SF.VariableTable InPublicData, SF.VariableTable InEquipData, ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )


		// S2C: Remove actor from view
		public Result  RemoveActorFromViewS2CEvt( SF.GameInstanceUID InPlayInstanceUID, System.UInt32 InActorID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt.StartRemoveActorFromViewS2CEvt(builder);
			SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt.AddActorId(builder, InActorID);
			var packetOffset = SF.Flat.PlayInstance.RemoveActorFromViewS2CEvt.EndRemoveActorFromViewS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.RemoveActorFromViewS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  RemoveActorFromViewS2CEvt( SF.GameInstanceUID InPlayInstanceUID, System.UInt32 InActorID )


		// S2C: Player Movement
		public Result  ActorMovementS2CEvt( SF.GameInstanceUID InPlayInstanceUID, ActorMovement InMovement )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var MovementOffset = builder.CreateActorMovement(InMovement);
			SF.Flat.PlayInstance.ActorMovementS2CEvt.StartActorMovementS2CEvt(builder);
			SF.Flat.PlayInstance.ActorMovementS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.ActorMovementS2CEvt.AddMovement(builder, MovementOffset);
			var packetOffset = SF.Flat.PlayInstance.ActorMovementS2CEvt.EndActorMovementS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.ActorMovementS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ActorMovementS2CEvt( SF.GameInstanceUID InPlayInstanceUID, ActorMovement InMovement )


		// S2C: Player Movement
		public Result  ActorMovementsS2CEvt( SF.GameInstanceUID InPlayInstanceUID, ActorMovement[] InMovement )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var MovementOffset = builder.CreateActorMovementVector(InMovement);
			SF.Flat.PlayInstance.ActorMovementsS2CEvt.StartActorMovementsS2CEvt(builder);
			SF.Flat.PlayInstance.ActorMovementsS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.ActorMovementsS2CEvt.AddMovement(builder, MovementOffset);
			var packetOffset = SF.Flat.PlayInstance.ActorMovementsS2CEvt.EndActorMovementsS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.ActorMovementsS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ActorMovementsS2CEvt( SF.GameInstanceUID InPlayInstanceUID, ActorMovement[] InMovement )


		// S2C: Player state change
		public Result  PlayerStateChangedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.SFVector4 InPosition, SF.VariableTable InStateValues )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var PositionOffset = builder.CreateVector4(InPosition);
			var StateValuesOffset = builder.CreateVariableTable(InStateValues);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.StartPlayerStateChangedS2CEvt(builder);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.AddState(builder, InState);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.AddMoveFrame(builder, InMoveFrame);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.AddPosition(builder, PositionOffset);
			SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.AddStateValues(builder, StateValuesOffset);
			var packetOffset = SF.Flat.PlayInstance.PlayerStateChangedS2CEvt.EndPlayerStateChangedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.PlayerStateChangedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  PlayerStateChangedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.SFVector4 InPosition, SF.VariableTable InStateValues )


		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		public Result  SetCharacterPublicMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.SetCharacterPublicMessageRes.StartSetCharacterPublicMessageRes(builder);
			var packetOffset = SF.Flat.PlayInstance.SetCharacterPublicMessageRes.EndSetCharacterPublicMessageRes(builder);
			result = SendMessage(MessageIDPlayInstance.SetCharacterPublicMessageRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  SetCharacterPublicMessageRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Character's private data has changed
		public Result  CharacterPrivateDataChangedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.CharacterID InCharacterID, SF.VariableTable InPrivateData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var CharacterIDOffset = builder.CreateCharacterID(InCharacterID);
			var PrivateDataOffset = builder.CreateVariableTable(InPrivateData);
			SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt.StartCharacterPrivateDataChangedS2CEvt(builder);
			SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt.AddCharacterId(builder, CharacterIDOffset);
			SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt.AddPrivateData(builder, PrivateDataOffset);
			var packetOffset = SF.Flat.PlayInstance.CharacterPrivateDataChangedS2CEvt.EndCharacterPrivateDataChangedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.CharacterPrivateDataChangedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  CharacterPrivateDataChangedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.CharacterID InCharacterID, SF.VariableTable InPrivateData )


		// S2C: Player public data has been changed
		public Result  CharacterPublicDataChangedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InPublicData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var PublicDataOffset = builder.CreateVariableTable(InPublicData);
			SF.Flat.PlayInstance.CharacterPublicDataChangedS2CEvt.StartCharacterPublicDataChangedS2CEvt(builder);
			SF.Flat.PlayInstance.CharacterPublicDataChangedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.CharacterPublicDataChangedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.CharacterPublicDataChangedS2CEvt.AddPublicData(builder, PublicDataOffset);
			var packetOffset = SF.Flat.PlayInstance.CharacterPublicDataChangedS2CEvt.EndCharacterPublicDataChangedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.CharacterPublicDataChangedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  CharacterPublicDataChangedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InPublicData )


		// Cmd: Request WhiteboardSharing
		public Result  RequestWhiteboardSharingRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.RequestWhiteboardSharingRes.StartRequestWhiteboardSharingRes(builder);
			var packetOffset = SF.Flat.PlayInstance.RequestWhiteboardSharingRes.EndRequestWhiteboardSharingRes(builder);
			result = SendMessage(MessageIDPlayInstance.RequestWhiteboardSharingRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RequestWhiteboardSharingRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Accept WhiteboardSharing
		public Result  AcceptWhiteboardSharingRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.AcceptWhiteboardSharingRes.StartAcceptWhiteboardSharingRes(builder);
			var packetOffset = SF.Flat.PlayInstance.AcceptWhiteboardSharingRes.EndAcceptWhiteboardSharingRes(builder);
			result = SendMessage(MessageIDPlayInstance.AcceptWhiteboardSharingRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  AcceptWhiteboardSharingRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		public Result  CloseWhiteboardSharingRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.CloseWhiteboardSharingRes.StartCloseWhiteboardSharingRes(builder);
			var packetOffset = SF.Flat.PlayInstance.CloseWhiteboardSharingRes.EndCloseWhiteboardSharingRes(builder);
			result = SendMessage(MessageIDPlayInstance.CloseWhiteboardSharingRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CloseWhiteboardSharingRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  AddWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, SF.Result InResult, UInt32 InLogEntryID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryRes.StartAddWhiteboardSharingLogEntryRes(builder);
			SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryRes.AddLogEntryId(builder, InLogEntryID);
			var packetOffset = SF.Flat.PlayInstance.AddWhiteboardSharingLogEntryRes.EndAddWhiteboardSharingLogEntryRes(builder);
			result = SendMessage(MessageIDPlayInstance.AddWhiteboardSharingLogEntryRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  AddWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, SF.Result InResult, UInt32 InLogEntryID )


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  UpdateWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryRes.StartUpdateWhiteboardSharingLogEntryRes(builder);
			var packetOffset = SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryRes.EndUpdateWhiteboardSharingLogEntryRes(builder);
			result = SendMessage(MessageIDPlayInstance.UpdateWhiteboardSharingLogEntryRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UpdateWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: Update whiteboard log entry
		public Result  RemoveWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryRes.StartRemoveWhiteboardSharingLogEntryRes(builder);
			var packetOffset = SF.Flat.PlayInstance.RemoveWhiteboardSharingLogEntryRes.EndRemoveWhiteboardSharingLogEntryRes(builder);
			result = SendMessage(MessageIDPlayInstance.RemoveWhiteboardSharingLogEntryRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  RemoveWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: WhiteboardSharing has been requested
		public Result  WhiteboardSharingRequestedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRequestedPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var RequestedPlayerIDOffset = builder.CreatePlayerID(InRequestedPlayerID);
			SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt.StartWhiteboardSharingRequestedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt.AddRequestedPlayerId(builder, RequestedPlayerIDOffset);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingRequestedS2CEvt.EndWhiteboardSharingRequestedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingRequestedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingRequestedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRequestedPlayerID )


		// S2C: WhiteboardSharing has been requested
		public Result  WhiteboardSharingRejectedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRejectedPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var RejectedPlayerIDOffset = builder.CreatePlayerID(InRejectedPlayerID);
			SF.Flat.PlayInstance.WhiteboardSharingRejectedS2CEvt.StartWhiteboardSharingRejectedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingRejectedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingRejectedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingRejectedS2CEvt.AddRejectedPlayerId(builder, RejectedPlayerIDOffset);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingRejectedS2CEvt.EndWhiteboardSharingRejectedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingRejectedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingRejectedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InRejectedPlayerID )


		// S2C: WhiteboardSharing has been started
		public Result  WhiteboardSharingStartedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InOtherPlayerID, SF.VariableTable InWhiteboardInfo )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var OtherPlayerIDOffset = builder.CreatePlayerID(InOtherPlayerID);
			var WhiteboardInfoOffset = builder.CreateVariableTable(InWhiteboardInfo);
			SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt.StartWhiteboardSharingStartedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt.AddOtherPlayerId(builder, OtherPlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt.AddWhiteboardInfo(builder, WhiteboardInfoOffset);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingStartedS2CEvt.EndWhiteboardSharingStartedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingStartedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingStartedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InOtherPlayerID, SF.VariableTable InWhiteboardInfo )


		// S2C: WhiteboardSharing has been closed
		public Result  WhiteboardSharingHasClosedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InClosedPlayerID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var ClosedPlayerIDOffset = builder.CreatePlayerID(InClosedPlayerID);
			SF.Flat.PlayInstance.WhiteboardSharingHasClosedS2CEvt.StartWhiteboardSharingHasClosedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingHasClosedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingHasClosedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingHasClosedS2CEvt.AddClosedPlayerId(builder, ClosedPlayerIDOffset);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingHasClosedS2CEvt.EndWhiteboardSharingHasClosedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingHasClosedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingHasClosedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.AccountID InClosedPlayerID )


		// S2C: WhiteboardSharing new log entry has been added
		public Result  WhiteboardSharingNewLogEntryAddedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var LogEntryOffset = builder.CreateVariableTable(InLogEntry);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt.StartWhiteboardSharingNewLogEntryAddedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt.AddLogEntry(builder, LogEntryOffset);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt.EndWhiteboardSharingNewLogEntryAddedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingNewLogEntryAddedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry )


		// S2C: WhiteboardSharing new log entry has been removed
		public Result  WhiteboardSharingNewLogEntryRemovedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, UInt32 InLogEntryID )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt.StartWhiteboardSharingNewLogEntryRemovedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt.AddLogEntryId(builder, InLogEntryID);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt.EndWhiteboardSharingNewLogEntryRemovedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingNewLogEntryRemovedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, UInt32 InLogEntryID )


		// S2C: WhiteboardSharing new log entry has been updated
		public Result  WhiteboardSharingNewLogEntryUpdatedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var LogEntryOffset = builder.CreateVariableTable(InLogEntry);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt.StartWhiteboardSharingNewLogEntryUpdatedS2CEvt(builder);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt.AddLogEntry(builder, LogEntryOffset);
			var packetOffset = SF.Flat.PlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt.EndWhiteboardSharingNewLogEntryUpdatedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  WhiteboardSharingNewLogEntryUpdatedS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, SF.VariableTable InLogEntry )


		// Cmd: Occupy map object
		public Result  OccupyMapObjectRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.OccupyMapObjectRes.StartOccupyMapObjectRes(builder);
			SF.Flat.PlayInstance.OccupyMapObjectRes.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.OccupyMapObjectRes.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.OccupyMapObjectRes.AddMapObjectId(builder, InMapObjectId);
			var packetOffset = SF.Flat.PlayInstance.OccupyMapObjectRes.EndOccupyMapObjectRes(builder);
			result = SendMessage(MessageIDPlayInstance.OccupyMapObjectRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  OccupyMapObjectRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Unoccupy map object
		public Result  UnoccupyMapObjectRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.UnoccupyMapObjectRes.StartUnoccupyMapObjectRes(builder);
			SF.Flat.PlayInstance.UnoccupyMapObjectRes.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UnoccupyMapObjectRes.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.UnoccupyMapObjectRes.AddMapObjectId(builder, InMapObjectId);
			var packetOffset = SF.Flat.PlayInstance.UnoccupyMapObjectRes.EndUnoccupyMapObjectRes(builder);
			result = SendMessage(MessageIDPlayInstance.UnoccupyMapObjectRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UnoccupyMapObjectRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Use map object
		public Result  UseMapObjectRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			var ResultAttributesOffset = builder.CreateVariableTable(InResultAttributes);
			SF.Flat.PlayInstance.UseMapObjectRes.StartUseMapObjectRes(builder);
			SF.Flat.PlayInstance.UseMapObjectRes.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UseMapObjectRes.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.UseMapObjectRes.AddMapObjectId(builder, InMapObjectId);
			SF.Flat.PlayInstance.UseMapObjectRes.AddResultAttributes(builder, ResultAttributesOffset);
			var packetOffset = SF.Flat.PlayInstance.UseMapObjectRes.EndUseMapObjectRes(builder);
			result = SendMessage(MessageIDPlayInstance.UseMapObjectRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UseMapObjectRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )


		// Cmd: Send zone chatting
		public Result  ZoneChatRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.ZoneChatRes.StartZoneChatRes(builder);
			var packetOffset = SF.Flat.PlayInstance.ZoneChatRes.EndZoneChatRes(builder);
			result = SendMessage(MessageIDPlayInstance.ZoneChatRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  ZoneChatRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// S2C: Player state change
		public Result  ZoneChatS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InSenderID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var SenderIDOffset = builder.CreatePlayerID(InSenderID);
			var ChatMetaDataOffset = builder.CreateVariableTable(InChatMetaData);
			var ChatMessageOffset = builder.CreateString(InChatMessage);
			SF.Flat.PlayInstance.ZoneChatS2CEvt.StartZoneChatS2CEvt(builder);
			SF.Flat.PlayInstance.ZoneChatS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.ZoneChatS2CEvt.AddSenderId(builder, SenderIDOffset);
			SF.Flat.PlayInstance.ZoneChatS2CEvt.AddMessageType(builder, InMessageType);
			SF.Flat.PlayInstance.ZoneChatS2CEvt.AddChatMetaData(builder, ChatMetaDataOffset);
			SF.Flat.PlayInstance.ZoneChatS2CEvt.AddChatMessage(builder, ChatMessageOffset);
			var packetOffset = SF.Flat.PlayInstance.ZoneChatS2CEvt.EndZoneChatS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.ZoneChatS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  ZoneChatS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InSenderID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// S2C: Effect modifier initial sync
		public Result  LevelUpS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.Int64 InCurrentExp, System.Int32 InCurrentLevel )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateEntityUID(InPlayInstanceUID);
			var PlayerIDOffset = builder.CreatePlayerID(InPlayerID);
			SF.Flat.PlayInstance.LevelUpS2CEvt.StartLevelUpS2CEvt(builder);
			SF.Flat.PlayInstance.LevelUpS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.LevelUpS2CEvt.AddPlayerId(builder, PlayerIDOffset);
			SF.Flat.PlayInstance.LevelUpS2CEvt.AddCurrentExp(builder, InCurrentExp);
			SF.Flat.PlayInstance.LevelUpS2CEvt.AddCurrentLevel(builder, InCurrentLevel);
			var packetOffset = SF.Flat.PlayInstance.LevelUpS2CEvt.EndLevelUpS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.LevelUpS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  LevelUpS2CEvt( System.UInt32 InPlayInstanceUID, SF.AccountID InPlayerID, System.Int64 InCurrentExp, System.Int32 InCurrentLevel )


		// Cmd: To call general functionality
		public Result  CallFunctionRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InResults )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var ResultsOffset = builder.CreateVariableTable(InResults);
			SF.Flat.PlayInstance.CallFunctionRes.StartCallFunctionRes(builder);
			SF.Flat.PlayInstance.CallFunctionRes.AddResults(builder, ResultsOffset);
			var packetOffset = SF.Flat.PlayInstance.CallFunctionRes.EndCallFunctionRes(builder);
			result = SendMessage(MessageIDPlayInstance.CallFunctionRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CallFunctionRes( SF.TransactionID InTransactionID, SF.Result InResult, SF.VariableTable InResults )


		// S2C: Voice data
		public Result  VoiceDataS2CEvt( System.UInt32 InActorID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var VoiceDataOffset = builder.Createuint8Vector(InVoiceData);
			SF.Flat.PlayInstance.VoiceDataS2CEvt.StartVoiceDataS2CEvt(builder);
			SF.Flat.PlayInstance.VoiceDataS2CEvt.AddActorId(builder, InActorID);
			SF.Flat.PlayInstance.VoiceDataS2CEvt.AddFrameIndex(builder, InFrameIndex);
			SF.Flat.PlayInstance.VoiceDataS2CEvt.AddVoiceData(builder, VoiceDataOffset);
			var packetOffset = SF.Flat.PlayInstance.VoiceDataS2CEvt.EndVoiceDataS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.VoiceDataS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  VoiceDataS2CEvt( System.UInt32 InActorID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )


		// Cmd: UGC zone edit command
		public Result  UGCEditAddRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InInstanceId, System.UInt32 InTimeOffset, SF.VariableTable[] InInvenChanges )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InvenChangesOffset = builder.CreateVariableTableVector(InInvenChanges);
			SF.Flat.PlayInstance.UGCEditAddRes.StartUGCEditAddRes(builder);
			SF.Flat.PlayInstance.UGCEditAddRes.AddInstanceId(builder, InInstanceId);
			SF.Flat.PlayInstance.UGCEditAddRes.AddTimeOffset(builder, InTimeOffset);
			SF.Flat.PlayInstance.UGCEditAddRes.AddInvenChanges(builder, InvenChangesOffset);
			var packetOffset = SF.Flat.PlayInstance.UGCEditAddRes.EndUGCEditAddRes(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditAddRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UGCEditAddRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InInstanceId, System.UInt32 InTimeOffset, SF.VariableTable[] InInvenChanges )


		// Cmd: UGC zone edit command
		public Result  UGCEditMoveRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.UGCEditMoveRes.StartUGCEditMoveRes(builder);
			var packetOffset = SF.Flat.PlayInstance.UGCEditMoveRes.EndUGCEditMoveRes(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditMoveRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UGCEditMoveRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: UGC zone edit command
		public Result  UGCEditDeleteRes( SF.TransactionID InTransactionID, SF.Result InResult )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			SF.Flat.PlayInstance.UGCEditDeleteRes.StartUGCEditDeleteRes(builder);
			var packetOffset = SF.Flat.PlayInstance.UGCEditDeleteRes.EndUGCEditDeleteRes(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditDeleteRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UGCEditDeleteRes( SF.TransactionID InTransactionID, SF.Result InResult )


		// Cmd: UGC zone edit command
		public Result  UGCEditClaimBackRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InInstanceId, SF.VariableTable[] InInvenChanges )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var InvenChangesOffset = builder.CreateVariableTableVector(InInvenChanges);
			SF.Flat.PlayInstance.UGCEditClaimBackRes.StartUGCEditClaimBackRes(builder);
			SF.Flat.PlayInstance.UGCEditClaimBackRes.AddInstanceId(builder, InInstanceId);
			SF.Flat.PlayInstance.UGCEditClaimBackRes.AddInvenChanges(builder, InvenChangesOffset);
			var packetOffset = SF.Flat.PlayInstance.UGCEditClaimBackRes.EndUGCEditClaimBackRes(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditClaimBackRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  UGCEditClaimBackRes( SF.TransactionID InTransactionID, SF.Result InResult, System.UInt32 InInstanceId, SF.VariableTable[] InInvenChanges )


		// S2C: UGC zone edited event
		public Result  UGCEditAddedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InOperatorPlayerID, System.UInt32 InEntityType, System.UInt32 InTableId, System.UInt32 InTimeOffset, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, System.UInt32 InInstanceId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var OperatorPlayerIDOffset = builder.CreatePlayerID(InOperatorPlayerID);
			var PositionOffset = builder.CreateVector4(InPosition);
			var RotationOffset = builder.CreateVector4(InRotation);
			var ScaleOffset = builder.CreateVector4(InScale);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.StartUGCEditAddedS2CEvt(builder);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddOperatorPlayerId(builder, OperatorPlayerIDOffset);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddEntityType(builder, InEntityType);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddTableId(builder, InTableId);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddTimeOffset(builder, InTimeOffset);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddPosition(builder, PositionOffset);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddRotation(builder, RotationOffset);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddScale(builder, ScaleOffset);
			SF.Flat.PlayInstance.UGCEditAddedS2CEvt.AddInstanceId(builder, InInstanceId);
			var packetOffset = SF.Flat.PlayInstance.UGCEditAddedS2CEvt.EndUGCEditAddedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditAddedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  UGCEditAddedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InOperatorPlayerID, System.UInt32 InEntityType, System.UInt32 InTableId, System.UInt32 InTimeOffset, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale, System.UInt32 InInstanceId )


		// S2C: UGC zone edited event
		public Result  UGCEditRemovedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InOperatorPlayerID, System.UInt32 InInstanceId )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var OperatorPlayerIDOffset = builder.CreatePlayerID(InOperatorPlayerID);
			SF.Flat.PlayInstance.UGCEditRemovedS2CEvt.StartUGCEditRemovedS2CEvt(builder);
			SF.Flat.PlayInstance.UGCEditRemovedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UGCEditRemovedS2CEvt.AddOperatorPlayerId(builder, OperatorPlayerIDOffset);
			SF.Flat.PlayInstance.UGCEditRemovedS2CEvt.AddInstanceId(builder, InInstanceId);
			var packetOffset = SF.Flat.PlayInstance.UGCEditRemovedS2CEvt.EndUGCEditRemovedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditRemovedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  UGCEditRemovedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InOperatorPlayerID, System.UInt32 InInstanceId )


		// S2C: UGC zone edited event
		public Result  UGCEditMovedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InOperatorPlayerID, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var PlayInstanceUIDOffset = builder.CreateGameInstanceUID(InPlayInstanceUID);
			var OperatorPlayerIDOffset = builder.CreatePlayerID(InOperatorPlayerID);
			var PositionOffset = builder.CreateVector4(InPosition);
			var RotationOffset = builder.CreateVector4(InRotation);
			var ScaleOffset = builder.CreateVector4(InScale);
			SF.Flat.PlayInstance.UGCEditMovedS2CEvt.StartUGCEditMovedS2CEvt(builder);
			SF.Flat.PlayInstance.UGCEditMovedS2CEvt.AddPlayInstanceUid(builder, PlayInstanceUIDOffset);
			SF.Flat.PlayInstance.UGCEditMovedS2CEvt.AddOperatorPlayerId(builder, OperatorPlayerIDOffset);
			SF.Flat.PlayInstance.UGCEditMovedS2CEvt.AddPosition(builder, PositionOffset);
			SF.Flat.PlayInstance.UGCEditMovedS2CEvt.AddRotation(builder, RotationOffset);
			SF.Flat.PlayInstance.UGCEditMovedS2CEvt.AddScale(builder, ScaleOffset);
			var packetOffset = SF.Flat.PlayInstance.UGCEditMovedS2CEvt.EndUGCEditMovedS2CEvt(builder);
			result = SendMessage(MessageIDPlayInstance.UGCEditMovedS2CEvt, builder, packetOffset.Value);
			return result;
		} // public Result  UGCEditMovedS2CEvt( SF.GameInstanceUID InPlayInstanceUID, SF.AccountID InOperatorPlayerID, SF.SFVector4 InPosition, SF.SFVector4 InRotation, SF.SFVector4 InScale )


		// Cmd: Create stream instance
		public Result  CreateStreamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InStreamName )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNameOffset = builder.CreateString(InStreamName);
			SF.Flat.PlayInstance.CreateStreamRes.StartCreateStreamRes(builder);
			SF.Flat.PlayInstance.CreateStreamRes.AddStreamName(builder, StreamNameOffset);
			var packetOffset = SF.Flat.PlayInstance.CreateStreamRes.EndCreateStreamRes(builder);
			result = SendMessage(MessageIDPlayInstance.CreateStreamRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  CreateStreamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InStreamName )


		// Cmd: Open stream instance
		public Result  FindStreamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InStreamName )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNameOffset = builder.CreateString(InStreamName);
			SF.Flat.PlayInstance.FindStreamRes.StartFindStreamRes(builder);
			SF.Flat.PlayInstance.FindStreamRes.AddStreamName(builder, StreamNameOffset);
			var packetOffset = SF.Flat.PlayInstance.FindStreamRes.EndFindStreamRes(builder);
			result = SendMessage(MessageIDPlayInstance.FindStreamRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  FindStreamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InStreamName )


		// Cmd: Delete stream instance
		public Result  DeleteStreamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InStreamName )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNameOffset = builder.CreateString(InStreamName);
			SF.Flat.PlayInstance.DeleteStreamRes.StartDeleteStreamRes(builder);
			SF.Flat.PlayInstance.DeleteStreamRes.AddStreamName(builder, StreamNameOffset);
			var packetOffset = SF.Flat.PlayInstance.DeleteStreamRes.EndDeleteStreamRes(builder);
			result = SendMessage(MessageIDPlayInstance.DeleteStreamRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  DeleteStreamRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String InStreamName )


		// Cmd: Get stream list
		public Result  GetStreamListRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String[] InStreamNames )
		{
 			if (Endpoint == null) return ResultCode.IO_NOT_CONNECTED;
			Result result = ResultCode.SUCCESS;
			var builder = new Google.FlatBuffers.FlatBufferBuilder(1024);
			var StreamNamesOffset = builder.CreateStringVector(InStreamNames);
			SF.Flat.PlayInstance.GetStreamListRes.StartGetStreamListRes(builder);
			SF.Flat.PlayInstance.GetStreamListRes.AddStreamNames(builder, StreamNamesOffset);
			var packetOffset = SF.Flat.PlayInstance.GetStreamListRes.EndGetStreamListRes(builder);
			result = SendMessage(MessageIDPlayInstance.GetStreamListRes, builder, packetOffset.Value, transactionId:InTransactionID, result:InResult);
			return result;
		} // public Result  GetStreamListRes( SF.TransactionID InTransactionID, SF.Result InResult, System.String[] InStreamNames )


	}; // public class PlayInstanceSvrRPCSendAdapter : RPCAdapter




} // namespace SF.Net
#nullable restore


