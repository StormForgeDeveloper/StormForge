////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
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
		public int  JoinPlayInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID,System.Text.Encoding.UTF8.GetBytes(InPlayerIdentifier + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.JoinPlayInstanceCmd);
			return result;
		} // public int  JoinPlayInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )

		// C2S: Play packet
		public int  PlayPacketC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask,(ushort)InPayload.Length, InPayload);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.PlayPacketC2SEvt);
			return result;
		} // public int  PlayPacketC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )


		// C2S: Player Movement
		public int  PlayerMovementC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,ref InMovement);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.PlayerMovementC2SEvt);
			return result;
		} // public int  PlayerMovementC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )


		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public int  ClientSyncReliableC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )
		{
 			int result;
			var InSyncData_ = InSyncData.ToByteArray();
			using (var InSyncData_PinnedPtr_ = new PinnedByteBuffer(InSyncData_))
			{
			result = CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InSyncData_.Length, InSyncData_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ClientSyncReliableC2SEvt);
			return result;
		} // public int  ClientSyncReliableC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )


		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public int  ClientSyncC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )
		{
 			int result;
			var InSyncData_ = InSyncData.ToByteArray();
			using (var InSyncData_PinnedPtr_ = new PinnedByteBuffer(InSyncData_))
			{
			result = CSSFNetAdapter_PlayInstanceClientSyncC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InSyncData_.Length, InSyncData_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ClientSyncC2SEvt);
			return result;
		} // public int  ClientSyncC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )


		// Cmd: Occupy map object
		public int  OccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.OccupyMapObjectCmd);
			return result;
		} // public int  OccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId )

		// Cmd: Unoccupy map object
		public int  UnoccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.UnoccupyMapObjectCmd);
			return result;
		} // public int  UnoccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )

		// Cmd: Use map object
		public int  UseMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters )
		{
 			int result;
			var InUseParameters_ = InUseParameters.ToByteArray();
			using (var InUseParameters_PinnedPtr_ = new PinnedByteBuffer(InUseParameters_))
			{
			result = CSSFNetAdapter_PlayInstanceUseMapObjectCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId,(ushort)InUseParameters_.Length, InUseParameters_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.UseMapObjectCmd);
			return result;
		} // public int  UseMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters )

		// Cmd: Send zone chatting
		public int  ZoneChatCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_PlayInstanceZoneChatCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMessageType,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ZoneChatCmd);
			return result;
		} // public int  ZoneChatCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )

		// Cmd: Create stream instance
		public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceCreateStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.CreateStreamCmd);
			return result;
		} // public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Open stream instance
		public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceFindStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.FindStreamCmd);
			return result;
		} // public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Delete stream instance
		public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceDeleteStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.DeleteStreamCmd);
			return result;
		} // public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Get stream list
		public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceGetStreamListCmd(m_Connection.NativeHandle, InTransactionID, InTicket);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.GetStreamListCmd);
			return result;
		} // public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )

		// Cmd: To call general functionality
		public int  CallFunctionCmd( System.UInt64 InTransactionID, System.UInt32 InFunctionName, System.UInt64 InPlayerID, SF.VariableTable InParameters )
		{
 			int result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = CSSFNetAdapter_PlayInstanceCallFunctionCmd(m_Connection.NativeHandle, InTransactionID, InFunctionName, InPlayerID,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.CallFunctionCmd);
			return result;
		} // public int  CallFunctionCmd( System.UInt64 InTransactionID, System.UInt32 InFunctionName, System.UInt64 InPlayerID, SF.VariableTable InParameters )

		#region Native Interfaces 
		// Cmd: Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinPlayInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerIdentifier );


		// C2S: Play packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayPacketC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.UInt16 _sizeOfInPayload,System.Byte[] InPayload );



		// C2S: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref SF.ActorMovement InMovement );



		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInSyncData,IntPtr InSyncData );



		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceClientSyncC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceClientSyncC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInSyncData,IntPtr InSyncData );



		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId );


		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );


		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUseMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUseMapObjectCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt16 _sizeOfInUseParameters,IntPtr InUseParameters );


		// Cmd: Send zone chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceZoneChatCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceZoneChatCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.SByte InMessageType, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket );


		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCallFunctionCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCallFunctionCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InFunctionName, System.UInt64 InPlayerID, System.UInt16 _sizeOfInParameters,IntPtr InParameters );


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
		public int  JoinPlayInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID,ref InMovement);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.JoinPlayInstanceRes);
			return result;
		} // public int  JoinPlayInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )


		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public int  PlayerKickedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InKickedPlayerID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.PlayerKickedS2CEvt);
			return result;
		} // public int  PlayerKickedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID )


		// S2C: New actor in get view
		public int  NewActorInViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.PlayerPlatformID InPlayerPlatformId, SF.VariableTable InAttributes, SF.ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			var InStateValues_ = InStateValues.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			using (var InStateValues_PinnedPtr_ = new PinnedByteBuffer(InStateValues_))
			{
			result = CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,ref InPlayerPlatformId,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr,ref InMovement, InState,(ushort)InStateValues_.Length, InStateValues_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.NewActorInViewS2CEvt);
			return result;
		} // public int  NewActorInViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.PlayerPlatformID InPlayerPlatformId, SF.VariableTable InAttributes, SF.ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )


		// S2C: Remove actor from view
		public int  RemoveActorFromViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InActorID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InActorID);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.RemoveActorFromViewS2CEvt);
			return result;
		} // public int  RemoveActorFromViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InActorID )


		// S2C: Player Movement
		public int  ActorMovementS2CEvt( System.UInt64 InPlayInstanceUID, SF.ActorMovement InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceActorMovementS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID,ref InMovement);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ActorMovementS2CEvt);
			return result;
		} // public int  ActorMovementS2CEvt( System.UInt64 InPlayInstanceUID, SF.ActorMovement InMovement )


		// S2C: Player Movement
		public int  ActorMovementsS2CEvt( System.UInt64 InPlayInstanceUID, SF.ActorMovement[] InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID,(ushort)InMovement.Length, InMovement);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ActorMovementsS2CEvt);
			return result;
		} // public int  ActorMovementsS2CEvt( System.UInt64 InPlayInstanceUID, SF.ActorMovement[] InMovement )


		// S2C: Player state change
		public int  PlayerStateChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.Vector4 InPosition, SF.VariableTable InStateValues )
		{
 			int result;
			var InStateValues_ = InStateValues.ToByteArray();
			using (var InStateValues_PinnedPtr_ = new PinnedByteBuffer(InStateValues_))
			{
			result = CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InState, InMoveFrame,ref InPosition,(ushort)InStateValues_.Length, InStateValues_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.PlayerStateChangedS2CEvt);
			return result;
		} // public int  PlayerStateChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.Vector4 InPosition, SF.VariableTable InStateValues )


		// Cmd: Occupy map object
		public int  OccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceOccupyMapObjectRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.OccupyMapObjectRes);
			return result;
		} // public int  OccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Unoccupy map object
		public int  UnoccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.UnoccupyMapObjectRes);
			return result;
		} // public int  UnoccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Use map object
		public int  UseMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )
		{
 			int result;
			var InResultAttributes_ = InResultAttributes.ToByteArray();
			using (var InResultAttributes_PinnedPtr_ = new PinnedByteBuffer(InResultAttributes_))
			{
			result = CSSFNetAdapter_PlayInstanceUseMapObjectRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId,(ushort)InResultAttributes_.Length, InResultAttributes_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.UseMapObjectRes);
			return result;
		} // public int  UseMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )


		// Cmd: Send zone chatting
		public int  ZoneChatRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceZoneChatRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ZoneChatRes);
			return result;
		} // public int  ZoneChatRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Player state change
		public int  ZoneChatS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InSenderID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_PlayInstanceZoneChatS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InSenderID, InMessageType,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.ZoneChatS2CEvt);
			return result;
		} // public int  ZoneChatS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InSenderID, System.SByte InMessageType, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Create stream instance
		public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceCreateStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.CreateStreamRes);
			return result;
		} // public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InStreamName )


		// Cmd: Open stream instance
		public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceFindStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.FindStreamRes);
			return result;
		} // public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InStreamName )


		// Cmd: Delete stream instance
		public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceDeleteStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.DeleteStreamRes);
			return result;
		} // public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InStreamName )


		// Cmd: Get stream list
		public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )
		{
 			int result;
			using (var InStreamNamesArray = new ArrayObjectString(InStreamNames))
			{
			result = CSSFNetAdapter_PlayInstanceGetStreamListRes(m_Connection.NativeHandle, InTransactionID, InResult,InStreamNamesArray.NativeHandle);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.GetStreamListRes);
			return result;
		} // public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )


		// Cmd: To call general functionality
		public int  CallFunctionRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InResults )
		{
 			int result;
			var InResults_ = InResults.ToByteArray();
			using (var InResults_PinnedPtr_ = new PinnedByteBuffer(InResults_))
			{
			result = CSSFNetAdapter_PlayInstanceCallFunctionRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InResults_.Length, InResults_PinnedPtr_.Ptr);
			}
			if (m_Connection != null) m_Connection.HandleSentMessage(result, MessageIDPlayInstance.CallFunctionRes);
			return result;
		} // public int  CallFunctionRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InResults )


		#region Native Interfaces 
		// Cmd: Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinPlayInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref SF.ActorMovement InMovement );



		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID );



		// S2C: New actor in get view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceNewActorInViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref SF.PlayerPlatformID InPlayerPlatformId, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes, ref SF.ActorMovement InMovement, System.UInt32 InState, System.UInt16 _sizeOfInStateValues,IntPtr InStateValues );



		// S2C: Remove actor from view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRemoveActorFromViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt32 InActorID );



		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceActorMovementS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceActorMovementS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, ref SF.ActorMovement InMovement );



		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceActorMovementsS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt16 _sizeOfInMovement,SF.ActorMovement[] InMovement );



		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, ref SF.Vector4 InPosition, System.UInt16 _sizeOfInStateValues,IntPtr InStateValues );



		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceOccupyMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceOccupyMapObjectRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );



		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );



		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUseMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUseMapObjectRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt16 _sizeOfInResultAttributes,IntPtr InResultAttributes );



		// Cmd: Send zone chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceZoneChatRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceZoneChatRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceZoneChatS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceZoneChatS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InSenderID, System.SByte InMessageType, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, IntPtr InStreamNames );



		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCallFunctionRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCallFunctionRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInResults,IntPtr InResults );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrPlayInstance : SendMessage




} // namespace SF.Net


