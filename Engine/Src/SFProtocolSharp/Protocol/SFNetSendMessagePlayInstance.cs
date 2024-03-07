////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;
#nullable enable



namespace SF.Net
{
 

	public class SendMessagePlayInstance : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessagePlayInstance()
		{
 		} // public  SendMessagePlayInstance()
		public  SendMessagePlayInstance( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessagePlayInstance( SF.SFConnection connection ) : base(connection)

		// Cmd: Player Join request.
		public Result  JoinPlayInstanceCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinPlayInstanceCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InPlayerIdentifier, callback);
		} // public Result  JoinPlayInstanceCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier, Action<SFMessage>? callback = null )
		public Result  JoinPlayInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID,System.Text.Encoding.UTF8.GetBytes(InPlayerIdentifier + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.JoinPlayInstanceCmd, callback);
			return result;
		} // public Result  JoinPlayInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier, Action<SFMessage>? callback = null )

		// C2S: Play packet
		public Result  PlayPacketC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask,(ushort)InPayload.Length, InPayload));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.PlayPacketC2SEvt);
			return result;
		} // public Result  PlayPacketC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )


		// C2S: Player Movement
		public Result  PlayerMovementC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ActorMovement InMovement )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,ref InMovement));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.PlayerMovementC2SEvt);
			return result;
		} // public Result  PlayerMovementC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ActorMovement InMovement )


		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public Result  ClientSyncReliableC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InSyncData_ = InSyncData.ToByteArray();
			using (var InSyncData_PinnedPtr_ = new PinnedByteBuffer(InSyncData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InSyncData_.Length, InSyncData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.ClientSyncReliableC2SEvt);
			return result;
		} // public Result  ClientSyncReliableC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )


		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public Result  ClientSyncC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InSyncData_ = InSyncData.ToByteArray();
			using (var InSyncData_PinnedPtr_ = new PinnedByteBuffer(InSyncData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceClientSyncC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InSyncData_.Length, InSyncData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.ClientSyncC2SEvt);
			return result;
		} // public Result  ClientSyncC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )


		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		public Result  SetCharacterPublicMessageCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SetCharacterPublicMessageCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InPublicMessage, callback);
		} // public Result  SetCharacterPublicMessageCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )
		public Result  SetCharacterPublicMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID,System.Text.Encoding.UTF8.GetBytes(InPublicMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.SetCharacterPublicMessageCmd, callback);
			return result;
		} // public Result  SetCharacterPublicMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPublicMessage, Action<SFMessage>? callback = null )

		// Cmd: Request WhiteboardSharing
		public Result  RequestWhiteboardSharingCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestWhiteboardSharingCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InTargetPlayerID, InWhiteboardInfo, callback);
		} // public Result  RequestWhiteboardSharingCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )
		public Result  RequestWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InWhiteboardInfo_ = InWhiteboardInfo.ToByteArray();
			using (var InWhiteboardInfo_PinnedPtr_ = new PinnedByteBuffer(InWhiteboardInfo_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InTargetPlayerID,(ushort)InWhiteboardInfo_.Length, InWhiteboardInfo_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.RequestWhiteboardSharingCmd, callback);
			return result;
		} // public Result  RequestWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InTargetPlayerID, SF.VariableTable InWhiteboardInfo, Action<SFMessage>? callback = null )

		// Cmd: Accept WhiteboardSharing
		public Result  AcceptWhiteboardSharingCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AcceptWhiteboardSharingCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InRequestedPlayerID, InAnswer, callback);
		} // public Result  AcceptWhiteboardSharingCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )
		public Result  AcceptWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InRequestedPlayerID, InAnswer));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.AcceptWhiteboardSharingCmd, callback);
			return result;
		} // public Result  AcceptWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID, System.Byte InAnswer, Action<SFMessage>? callback = null )

		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		public Result  CloseWhiteboardSharingCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CloseWhiteboardSharingCmd(InTransactionID, InPlayInstanceUID, InPlayerID, callback);
		} // public Result  CloseWhiteboardSharingCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public Result  CloseWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.CloseWhiteboardSharingCmd, callback);
			return result;
		} // public Result  CloseWhiteboardSharingCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  AddWhiteboardSharingLogEntryCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AddWhiteboardSharingLogEntryCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntry, callback);
		} // public Result  AddWhiteboardSharingLogEntryCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		public Result  AddWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InLogEntry_ = InLogEntry.ToByteArray();
			using (var InLogEntry_PinnedPtr_ = new PinnedByteBuffer(InLogEntry_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID,(ushort)InLogEntry_.Length, InLogEntry_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.AddWhiteboardSharingLogEntryCmd, callback);
			return result;
		} // public Result  AddWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )

		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  UpdateWhiteboardSharingLogEntryCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UpdateWhiteboardSharingLogEntryCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntry, callback);
		} // public Result  UpdateWhiteboardSharingLogEntryCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		public Result  UpdateWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InLogEntry_ = InLogEntry.ToByteArray();
			using (var InLogEntry_PinnedPtr_ = new PinnedByteBuffer(InLogEntry_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID,(ushort)InLogEntry_.Length, InLogEntry_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.UpdateWhiteboardSharingLogEntryCmd, callback);
			return result;
		} // public Result  UpdateWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry, Action<SFMessage>? callback = null )

		// Cmd: Update whiteboard log entry
		public Result  RemoveWhiteboardSharingLogEntryCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RemoveWhiteboardSharingLogEntryCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntryID, callback);
		} // public Result  RemoveWhiteboardSharingLogEntryCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )
		public Result  RemoveWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InLogEntryID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.RemoveWhiteboardSharingLogEntryCmd, callback);
			return result;
		} // public Result  RemoveWhiteboardSharingLogEntryCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID, Action<SFMessage>? callback = null )

		// Cmd: Occupy map object
		public Result  OccupyMapObjectCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return OccupyMapObjectCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId, callback);
		} // public Result  OccupyMapObjectCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )
		public Result  OccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.OccupyMapObjectCmd, callback);
			return result;
		} // public Result  OccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId, Action<SFMessage>? callback = null )

		// Cmd: Unoccupy map object
		public Result  UnoccupyMapObjectCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UnoccupyMapObjectCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, callback);
		} // public Result  UnoccupyMapObjectCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )
		public Result  UnoccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.UnoccupyMapObjectCmd, callback);
			return result;
		} // public Result  UnoccupyMapObjectCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, Action<SFMessage>? callback = null )

		// Cmd: Use map object
		public Result  UseMapObjectCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UseMapObjectCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUseParameters, callback);
		} // public Result  UseMapObjectCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )
		public Result  UseMapObjectCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InUseParameters_ = InUseParameters.ToByteArray();
			using (var InUseParameters_PinnedPtr_ = new PinnedByteBuffer(InUseParameters_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceUseMapObjectCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId,(ushort)InUseParameters_.Length, InUseParameters_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.UseMapObjectCmd, callback);
			return result;
		} // public Result  UseMapObjectCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters, Action<SFMessage>? callback = null )

		// Cmd: Send zone chatting
		public Result  ZoneChatCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return ZoneChatCmd(InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType, InChatMetaData, InChatMessage, callback);
		} // public Result  ZoneChatCmd( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		public Result  ZoneChatCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceZoneChatCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.ZoneChatCmd, callback);
			return result;
		} // public Result  ZoneChatCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: To call general functionality
		public Result  CallFunctionCmd( System.UInt32 InFunctionName, System.UInt64 InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CallFunctionCmd(InTransactionID, InFunctionName, InPlayerID, InParameters, callback);
		} // public Result  CallFunctionCmd( System.UInt32 InFunctionName, System.UInt64 InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, System.UInt64 InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCallFunctionCmd(m_Connection.NativeHandle,ref InTransactionID, InFunctionName, InPlayerID,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.CallFunctionCmd, callback);
			return result;
		} // public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, System.UInt64 InPlayerID, SF.VariableTable InParameters, Action<SFMessage>? callback = null )

		// C2S: Send coded voice data to server
		public Result  SendVoiceDataC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceSendVoiceDataC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InFrameIndex,(ushort)InVoiceData.Length, InVoiceData));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.SendVoiceDataC2SEvt);
			return result;
		} // public Result  SendVoiceDataC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )


		// Cmd: Create stream instance
		public Result  CreateStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreateStreamCmd(InTransactionID, InTicket, InStreamName, callback);
		} // public Result  CreateStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		public Result  CreateStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCreateStreamCmd(m_Connection.NativeHandle,ref InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.CreateStreamCmd, callback);
			return result;
		} // public Result  CreateStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )

		// Cmd: Open stream instance
		public Result  FindStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindStreamCmd(InTransactionID, InTicket, InStreamName, callback);
		} // public Result  FindStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		public Result  FindStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceFindStreamCmd(m_Connection.NativeHandle,ref InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.FindStreamCmd, callback);
			return result;
		} // public Result  FindStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )

		// Cmd: Delete stream instance
		public Result  DeleteStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DeleteStreamCmd(InTransactionID, InTicket, InStreamName, callback);
		} // public Result  DeleteStreamCmd( System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		public Result  DeleteStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceDeleteStreamCmd(m_Connection.NativeHandle,ref InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.DeleteStreamCmd, callback);
			return result;
		} // public Result  DeleteStreamCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, System.String InStreamName, Action<SFMessage>? callback = null )

		// Cmd: Get stream list
		public Result  GetStreamListCmd( System.UInt64 InTicket, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetStreamListCmd(InTransactionID, InTicket, callback);
		} // public Result  GetStreamListCmd( System.UInt64 InTicket, Action<SFMessage>? callback = null )
		public Result  GetStreamListCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceGetStreamListCmd(m_Connection.NativeHandle,ref InTransactionID, InTicket));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDPlayInstance.GetStreamListCmd, callback);
			return result;
		} // public Result  GetStreamListCmd( SF.TransactionID InTransactionID, System.UInt64 InTicket, Action<SFMessage>? callback = null )

		#region Native Interfaces 
		// Cmd: Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerIdentifier );


		// C2S: Play packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayPacketC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.UInt16 _sizeOfInPayload,System.Byte[] InPayload );



		// C2S: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref ActorMovement InMovement );



		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInSyncData,IntPtr InSyncData );



		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceClientSyncC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceClientSyncC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInSyncData,IntPtr InSyncData );



		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPublicMessage );


		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InTargetPlayerID, System.UInt16 _sizeOfInWhiteboardInfo,IntPtr InWhiteboardInfo );


		// Cmd: Accept WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID, System.Byte InAnswer );


		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID );


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInLogEntry,IntPtr InLogEntry );


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInLogEntry,IntPtr InLogEntry );


		// Cmd: Update whiteboard log entry
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID );


		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId );


		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );


		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUseMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUseMapObjectCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt16 _sizeOfInUseParameters,IntPtr InUseParameters );


		// Cmd: Send zone chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceZoneChatCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceZoneChatCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCallFunctionCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCallFunctionCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InFunctionName, System.UInt64 InPlayerID, System.UInt16 _sizeOfInParameters,IntPtr InParameters );


		// C2S: Send coded voice data to server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceSendVoiceDataC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceSendVoiceDataC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 InFrameIndex, System.UInt16 _sizeOfInVoiceData,System.Byte[] InVoiceData );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InTicket );


		#endregion //Native Interfaces 
	}; // public class SendMessagePlayInstance : SendMessage
	public class SendMessageSvrPlayInstance : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageSvrPlayInstance()
		{
 		} // public  SendMessageSvrPlayInstance()
		public  SendMessageSvrPlayInstance( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageSvrPlayInstance( SF.SFConnection connection ) : base(connection)

		// Cmd: Player Join request.
		public Result  JoinPlayInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InCharacterID, SF.VariableTable InCharacterPrivateData, ActorMovement InMovement )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InCharacterPrivateData_ = InCharacterPrivateData.ToByteArray();
			using (var InCharacterPrivateData_PinnedPtr_ = new PinnedByteBuffer(InCharacterPrivateData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InCharacterID,(ushort)InCharacterPrivateData_.Length, InCharacterPrivateData_PinnedPtr_.Ptr,ref InMovement));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.JoinPlayInstanceRes);
			return result;
		} // public Result  JoinPlayInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InCharacterID, SF.VariableTable InCharacterPrivateData, ActorMovement InMovement )


		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public Result  PlayerKickedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InKickedPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.PlayerKickedS2CEvt);
			return result;
		} // public Result  PlayerKickedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID )


		// S2C: New actor in get view
		public Result  NewActorInViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, PlayerPlatformID InPlayerPlatformId, SF.VariableTable InPublicData, SF.VariableTable InEquipData, ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InPublicData_ = InPublicData.ToByteArray();
			var InEquipData_ = InEquipData.ToByteArray();
			var InStateValues_ = InStateValues.ToByteArray();
			using (var InPublicData_PinnedPtr_ = new PinnedByteBuffer(InPublicData_))
			using (var InEquipData_PinnedPtr_ = new PinnedByteBuffer(InEquipData_))
			using (var InStateValues_PinnedPtr_ = new PinnedByteBuffer(InStateValues_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,ref InPlayerPlatformId,(ushort)InPublicData_.Length, InPublicData_PinnedPtr_.Ptr,(ushort)InEquipData_.Length, InEquipData_PinnedPtr_.Ptr,ref InMovement, InState,(ushort)InStateValues_.Length, InStateValues_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.NewActorInViewS2CEvt);
			return result;
		} // public Result  NewActorInViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, PlayerPlatformID InPlayerPlatformId, SF.VariableTable InPublicData, SF.VariableTable InEquipData, ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )


		// S2C: Remove actor from view
		public Result  RemoveActorFromViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InActorID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InActorID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.RemoveActorFromViewS2CEvt);
			return result;
		} // public Result  RemoveActorFromViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InActorID )


		// S2C: Player Movement
		public Result  ActorMovementS2CEvt( System.UInt64 InPlayInstanceUID, ActorMovement InMovement )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceActorMovementS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID,ref InMovement));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.ActorMovementS2CEvt);
			return result;
		} // public Result  ActorMovementS2CEvt( System.UInt64 InPlayInstanceUID, ActorMovement InMovement )


		// S2C: Player Movement
		public Result  ActorMovementsS2CEvt( System.UInt64 InPlayInstanceUID, ActorMovement[] InMovement )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID,(ushort)InMovement.Length, InMovement));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.ActorMovementsS2CEvt);
			return result;
		} // public Result  ActorMovementsS2CEvt( System.UInt64 InPlayInstanceUID, ActorMovement[] InMovement )


		// S2C: Player state change
		public Result  PlayerStateChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.Vector4 InPosition, SF.VariableTable InStateValues )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InStateValues_ = InStateValues.ToByteArray();
			using (var InStateValues_PinnedPtr_ = new PinnedByteBuffer(InStateValues_))
			{
			result = new Result(CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InState, InMoveFrame,ref InPosition,(ushort)InStateValues_.Length, InStateValues_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.PlayerStateChangedS2CEvt);
			return result;
		} // public Result  PlayerStateChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.Vector4 InPosition, SF.VariableTable InStateValues )


		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		public Result  SetCharacterPublicMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.SetCharacterPublicMessageRes);
			return result;
		} // public Result  SetCharacterPublicMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Character's private data has changed
		public Result  CharacterPrivateDataChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InCharacterID, SF.VariableTable InPrivateData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InPrivateData_ = InPrivateData.ToByteArray();
			using (var InPrivateData_PinnedPtr_ = new PinnedByteBuffer(InPrivateData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCharacterPrivateDataChangedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InCharacterID,(ushort)InPrivateData_.Length, InPrivateData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.CharacterPrivateDataChangedS2CEvt);
			return result;
		} // public Result  CharacterPrivateDataChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InCharacterID, SF.VariableTable InPrivateData )


		// S2C: Player public data has been changed
		public Result  CharacterPublicDataChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InPublicData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InPublicData_ = InPublicData.ToByteArray();
			using (var InPublicData_PinnedPtr_ = new PinnedByteBuffer(InPublicData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCharacterPublicDataChangedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InPublicData_.Length, InPublicData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.CharacterPublicDataChangedS2CEvt);
			return result;
		} // public Result  CharacterPublicDataChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InPublicData )


		// Cmd: Request WhiteboardSharing
		public Result  RequestWhiteboardSharingRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.RequestWhiteboardSharingRes);
			return result;
		} // public Result  RequestWhiteboardSharingRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Accept WhiteboardSharing
		public Result  AcceptWhiteboardSharingRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.AcceptWhiteboardSharingRes);
			return result;
		} // public Result  AcceptWhiteboardSharingRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		public Result  CloseWhiteboardSharingRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.CloseWhiteboardSharingRes);
			return result;
		} // public Result  CloseWhiteboardSharingRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  AddWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, System.Int32 InResult, UInt32 InLogEntryID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InLogEntryID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.AddWhiteboardSharingLogEntryRes);
			return result;
		} // public Result  AddWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, System.Int32 InResult, UInt32 InLogEntryID )


		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		public Result  UpdateWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.UpdateWhiteboardSharingLogEntryRes);
			return result;
		} // public Result  UpdateWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Update whiteboard log entry
		public Result  RemoveWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.RemoveWhiteboardSharingLogEntryRes);
			return result;
		} // public Result  RemoveWhiteboardSharingLogEntryRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: WhiteboardSharing has been requested
		public Result  WhiteboardSharingRequestedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingRequestedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InRequestedPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingRequestedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingRequestedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID )


		// S2C: WhiteboardSharing has been requested
		public Result  WhiteboardSharingRejectedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRejectedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingRejectedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InRejectedPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingRejectedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingRejectedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRejectedPlayerID )


		// S2C: WhiteboardSharing has been started
		public Result  WhiteboardSharingStartedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InOtherPlayerID, SF.VariableTable InWhiteboardInfo )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InWhiteboardInfo_ = InWhiteboardInfo.ToByteArray();
			using (var InWhiteboardInfo_PinnedPtr_ = new PinnedByteBuffer(InWhiteboardInfo_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingStartedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InOtherPlayerID,(ushort)InWhiteboardInfo_.Length, InWhiteboardInfo_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingStartedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingStartedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InOtherPlayerID, SF.VariableTable InWhiteboardInfo )


		// S2C: WhiteboardSharing has been closed
		public Result  WhiteboardSharingHasClosedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InClosedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingHasClosedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InClosedPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingHasClosedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingHasClosedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InClosedPlayerID )


		// S2C: WhiteboardSharing new log entry has been added
		public Result  WhiteboardSharingNewLogEntryAddedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InLogEntry_ = InLogEntry.ToByteArray();
			using (var InLogEntry_PinnedPtr_ = new PinnedByteBuffer(InLogEntry_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InLogEntry_.Length, InLogEntry_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingNewLogEntryAddedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingNewLogEntryAddedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry )


		// S2C: WhiteboardSharing new log entry has been removed
		public Result  WhiteboardSharingNewLogEntryRemovedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InLogEntryID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingNewLogEntryRemovedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingNewLogEntryRemovedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID )


		// S2C: WhiteboardSharing new log entry has been updated
		public Result  WhiteboardSharingNewLogEntryUpdatedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InLogEntry_ = InLogEntry.ToByteArray();
			using (var InLogEntry_PinnedPtr_ = new PinnedByteBuffer(InLogEntry_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InLogEntry_.Length, InLogEntry_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.WhiteboardSharingNewLogEntryUpdatedS2CEvt);
			return result;
		} // public Result  WhiteboardSharingNewLogEntryUpdatedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InLogEntry )


		// Cmd: Occupy map object
		public Result  OccupyMapObjectRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceOccupyMapObjectRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.OccupyMapObjectRes);
			return result;
		} // public Result  OccupyMapObjectRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Unoccupy map object
		public Result  UnoccupyMapObjectRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.UnoccupyMapObjectRes);
			return result;
		} // public Result  UnoccupyMapObjectRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Use map object
		public Result  UseMapObjectRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InResultAttributes_ = InResultAttributes.ToByteArray();
			using (var InResultAttributes_PinnedPtr_ = new PinnedByteBuffer(InResultAttributes_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceUseMapObjectRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId,(ushort)InResultAttributes_.Length, InResultAttributes_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.UseMapObjectRes);
			return result;
		} // public Result  UseMapObjectRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )


		// Cmd: Send zone chatting
		public Result  ZoneChatRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceZoneChatRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.ZoneChatRes);
			return result;
		} // public Result  ZoneChatRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Player state change
		public Result  ZoneChatS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InSenderID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceZoneChatS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InSenderID, InMessageType,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.ZoneChatS2CEvt);
			return result;
		} // public Result  ZoneChatS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InSenderID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// S2C: Effect modifier initial sync
		public Result  LevelUpS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.Int64 InCurrentExp, System.Int32 InCurrentLevel )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceLevelUpS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InCurrentExp, InCurrentLevel));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.LevelUpS2CEvt);
			return result;
		} // public Result  LevelUpS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.Int64 InCurrentExp, System.Int32 InCurrentLevel )


		// Cmd: To call general functionality
		public Result  CallFunctionRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InResults )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InResults_ = InResults.ToByteArray();
			using (var InResults_PinnedPtr_ = new PinnedByteBuffer(InResults_))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCallFunctionRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InResults_.Length, InResults_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.CallFunctionRes);
			return result;
		} // public Result  CallFunctionRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InResults )


		// S2C: Voice data
		public Result  VoiceDataS2CEvt( System.UInt32 InActorID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceVoiceDataS2CEvt(m_Connection.NativeHandle, InActorID, InFrameIndex,(ushort)InVoiceData.Length, InVoiceData));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.VoiceDataS2CEvt);
			return result;
		} // public Result  VoiceDataS2CEvt( System.UInt32 InActorID, System.UInt16 InFrameIndex, System.Byte[] InVoiceData )


		// Cmd: Create stream instance
		public Result  CreateStreamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InStreamName )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceCreateStreamRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.CreateStreamRes);
			return result;
		} // public Result  CreateStreamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InStreamName )


		// Cmd: Open stream instance
		public Result  FindStreamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InStreamName )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceFindStreamRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.FindStreamRes);
			return result;
		} // public Result  FindStreamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InStreamName )


		// Cmd: Delete stream instance
		public Result  DeleteStreamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InStreamName )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_PlayInstanceDeleteStreamRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.DeleteStreamRes);
			return result;
		} // public Result  DeleteStreamRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InStreamName )


		// Cmd: Get stream list
		public Result  GetStreamListRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String[] InStreamNames )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			using (var InStreamNamesArray = new ArrayObjectString(InStreamNames))
			{
			result = new Result(CSSFNetAdapter_PlayInstanceGetStreamListRes(m_Connection.NativeHandle,ref InTransactionID, InResult,InStreamNamesArray.NativeHandle));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDPlayInstance.GetStreamListRes);
			return result;
		} // public Result  GetStreamListRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String[] InStreamNames )


		#region Native Interfaces 
		// Cmd: Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InCharacterID, System.UInt16 _sizeOfInCharacterPrivateData,IntPtr InCharacterPrivateData, ref ActorMovement InMovement );



		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID );



		// S2C: New actor in get view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref PlayerPlatformID InPlayerPlatformId, System.UInt16 _sizeOfInPublicData,IntPtr InPublicData, System.UInt16 _sizeOfInEquipData,IntPtr InEquipData, ref ActorMovement InMovement, System.UInt32 InState, System.UInt16 _sizeOfInStateValues,IntPtr InStateValues );



		// S2C: Remove actor from view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt32 InActorID );



		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceActorMovementS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceActorMovementS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, ref ActorMovement InMovement );



		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt16 _sizeOfInMovement,ActorMovement[] InMovement );



		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, ref SF.Vector4 InPosition, System.UInt16 _sizeOfInStateValues,IntPtr InStateValues );



		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceSetCharacterPublicMessageRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Character's private data has changed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCharacterPrivateDataChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCharacterPrivateDataChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InCharacterID, System.UInt16 _sizeOfInPrivateData,IntPtr InPrivateData );



		// S2C: Player public data has been changed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCharacterPublicDataChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCharacterPublicDataChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInPublicData,IntPtr InPublicData );



		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRequestWhiteboardSharingRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Accept WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceAcceptWhiteboardSharingRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCloseWhiteboardSharingRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceAddWhiteboardSharingLogEntryRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, UInt32 InLogEntryID );



		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUpdateWhiteboardSharingLogEntryRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Update whiteboard log entry
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRemoveWhiteboardSharingLogEntryRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: WhiteboardSharing has been requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingRequestedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingRequestedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRequestedPlayerID );



		// S2C: WhiteboardSharing has been requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingRejectedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingRejectedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InRejectedPlayerID );



		// S2C: WhiteboardSharing has been started
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingStartedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingStartedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InOtherPlayerID, System.UInt16 _sizeOfInWhiteboardInfo,IntPtr InWhiteboardInfo );



		// S2C: WhiteboardSharing has been closed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingHasClosedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingHasClosedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt64 InClosedPlayerID );



		// S2C: WhiteboardSharing new log entry has been added
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryAddedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInLogEntry,IntPtr InLogEntry );



		// S2C: WhiteboardSharing new log entry has been removed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryRemovedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, UInt32 InLogEntryID );



		// S2C: WhiteboardSharing new log entry has been updated
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceWhiteboardSharingNewLogEntryUpdatedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInLogEntry,IntPtr InLogEntry );



		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceOccupyMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceOccupyMapObjectRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );



		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );



		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUseMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUseMapObjectRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt16 _sizeOfInResultAttributes,IntPtr InResultAttributes );



		// Cmd: Send zone chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceZoneChatRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceZoneChatRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceZoneChatS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceZoneChatS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InSenderID, System.SByte InMessageType, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// S2C: Effect modifier initial sync
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceLevelUpS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceLevelUpS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.Int64 InCurrentExp, System.Int32 InCurrentLevel );



		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCallFunctionRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCallFunctionRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInResults,IntPtr InResults );



		// S2C: Voice data
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceVoiceDataS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceVoiceDataS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InActorID, System.UInt16 InFrameIndex, System.UInt16 _sizeOfInVoiceData,System.Byte[] InVoiceData );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, IntPtr InStreamNames );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrPlayInstance : SendMessage




} // namespace SF.Net
#nullable restore


