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
 

	public class SendMessagePlayInstance
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessagePlayInstance( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessagePlayInstance( SF.SFConnection connection )

		// Cmd: Event for Player Join request.
		public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt32 InPlayInstanceID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceID, InPlayerID,System.Text.Encoding.UTF8.GetBytes(InPlayerIdentifier + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.JoinGameInstanceCmd);
			return result;
		} // public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt32 InPlayInstanceID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )

		// C2S: Play packet
		public int  PlayPacketC2SEvt( System.UInt32 InPlayInstanceID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(m_Connection.NativeHandle, InPlayInstanceID, InSenderEndpointID, InTargetEndpointMask,(ushort)InPayload.Length, InPayload);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayPacketC2SEvt);
			return result;
		} // public int  PlayPacketC2SEvt( System.UInt32 InPlayInstanceID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )


		// C2S: Player Movement
		public int  PlayerMovementC2SEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(m_Connection.NativeHandle, InGameInsUID, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerMovementC2SEvt);
			return result;
		} // public int  PlayerMovementC2SEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// Cmd: Create stream instance
		public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceCreateStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.CreateStreamCmd);
			return result;
		} // public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Open stream instance
		public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceFindStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.FindStreamCmd);
			return result;
		} // public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Delete stream instance
		public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceDeleteStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.DeleteStreamCmd);
			return result;
		} // public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Get stream list
		public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceGetStreamListCmd(m_Connection.NativeHandle, InTransactionID, InTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.GetStreamListCmd);
			return result;
		} // public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )

		#region Native Interfaces 
		// Cmd: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InPlayInstanceID, System.UInt64 InPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerIdentifier );


		// C2S: Play packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayPacketC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InPlayInstanceID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.UInt16 _sizeOfInPayload,System.Byte[] InPayload );



		// C2S: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



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


		#endregion //Native Interfaces 
	}; // public class SendMessagePlayInstance
	public class SendMessageSvrPlayInstance
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessageSvrPlayInstance( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessageSvrPlayInstance( SF.SFConnection connection )

		// Cmd: Event for Player Join request.
		public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InPlayInstanceID, System.UInt32 InMyEndpointID, SF.PlayerInformation[] InMemberInfos )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceJoinGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceID, InMyEndpointID,(ushort)InMemberInfos.Length, InMemberInfos);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.JoinGameInstanceRes);
			return result;
		} // public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InPlayInstanceID, System.UInt32 InMyEndpointID, SF.PlayerInformation[] InMemberInfos )


		// S2C: Event for Player joined.
		public int  PlayerJoinS2CEvt( System.UInt32 InPlayInstanceID, SF.PlayerInformation InJoinedPlayerInfo )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerJoinS2CEvt(m_Connection.NativeHandle, InPlayInstanceID,ref InJoinedPlayerInfo);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerJoinS2CEvt);
			return result;
		} // public int  PlayerJoinS2CEvt( System.UInt32 InPlayInstanceID, SF.PlayerInformation InJoinedPlayerInfo )


		// S2C: Event for Player left.
		public int  PlayerLeftS2CEvt( System.UInt32 InPlayInstanceID, System.UInt64 InLeftPlayerID, System.UInt32 InKickedReason )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerLeftS2CEvt(m_Connection.NativeHandle, InPlayInstanceID, InLeftPlayerID, InKickedReason);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerLeftS2CEvt);
			return result;
		} // public int  PlayerLeftS2CEvt( System.UInt32 InPlayInstanceID, System.UInt64 InLeftPlayerID, System.UInt32 InKickedReason )


		// S2C: New Player in get view
		public int  NewPlayerInViewS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt(m_Connection.NativeHandle, InGameInsUID, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.NewPlayerInViewS2CEvt);
			return result;
		} // public int  NewPlayerInViewS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// S2C: Remove player from view
		public int  RemovePlayerFromViewS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt(m_Connection.NativeHandle, InGameInsUID, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.RemovePlayerFromViewS2CEvt);
			return result;
		} // public int  RemovePlayerFromViewS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// S2C: Player Movement
		public int  PlayerMovementS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt(m_Connection.NativeHandle, InGameInsUID, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerMovementS2CEvt);
			return result;
		} // public int  PlayerMovementS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// Cmd: Create stream instance
		public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceCreateStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InStreamServerAddr,ref InStreamServerAddrIPV4,System.Text.Encoding.UTF8.GetBytes(InStreamUID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.CreateStreamRes);
			return result;
		} // public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )


		// Cmd: Open stream instance
		public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceFindStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InStreamServerAddr,ref InStreamServerAddrIPV4,System.Text.Encoding.UTF8.GetBytes(InStreamUID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.FindStreamRes);
			return result;
		} // public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )


		// Cmd: Delete stream instance
		public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceDeleteStreamRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.DeleteStreamRes);
			return result;
		} // public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Get stream list
		public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )
		{
 			int result;
			using (var InStreamNamesArray = new ArrayObjectString(InStreamNames))
			{
			result = CSSFNetAdapter_PlayInstanceGetStreamListRes(m_Connection.NativeHandle, InTransactionID, InResult,InStreamNamesArray.NativeHandle);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.GetStreamListRes);
			return result;
		} // public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )


		#region Native Interfaces 
		// Cmd: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InPlayInstanceID, System.UInt32 InMyEndpointID, System.UInt16 _sizeOfInMemberInfos,SF.PlayerInformation[] InMemberInfos );



		// S2C: Event for Player joined.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerJoinS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerJoinS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InPlayInstanceID, ref SF.PlayerInformation InJoinedPlayerInfo );



		// S2C: Event for Player left.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InPlayInstanceID, System.UInt64 InLeftPlayerID, System.UInt32 InKickedReason );



		// S2C: New Player in get view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// S2C: Remove player from view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InStreamServerAddr, ref SF.NetAddress InStreamServerAddrIPV4, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamUID );



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InStreamServerAddr, ref SF.NetAddress InStreamServerAddrIPV4, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamUID );



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, IntPtr InStreamNames );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrPlayInstance




} // namespace SF.Net


