////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Relay Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public class SendMessageRelay
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessageRelay( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessageRelay( SF.SFConnection connection )

		// C2S: Event for Player Join request.
		public int  JoinRelayInstanceC2SEvt( System.UInt32 InRelayInstanceID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayJoinRelayInstanceC2SEvt(m_Connection.NativeHandle, InRelayInstanceID, InPlayerID,System.Text.Encoding.UTF8.GetBytes(InPlayerIdentifier + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.JoinRelayInstanceC2SEvt);
			return result;
		} // public int  JoinRelayInstanceC2SEvt( System.UInt32 InRelayInstanceID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )


		// C2S: Event for Player Join request.
		public int  LeaveRelayInstanceC2SEvt( System.UInt32 InRelayInstanceID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayLeaveRelayInstanceC2SEvt(m_Connection.NativeHandle, InRelayInstanceID, InPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.LeaveRelayInstanceC2SEvt);
			return result;
		} // public int  LeaveRelayInstanceC2SEvt( System.UInt32 InRelayInstanceID, System.UInt64 InPlayerID )


		// C2S: Relay packet
		public int  RelayPacketC2SEvt( System.UInt32 InRelayInstanceID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayRelayPacketC2SEvt(m_Connection.NativeHandle, InRelayInstanceID, InSenderEndpointID, InTargetEndpointMask,(ushort)InPayload.Length, InPayload);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.RelayPacketC2SEvt);
			return result;
		} // public int  RelayPacketC2SEvt( System.UInt32 InRelayInstanceID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )


		// Cmd: Create stream instance
		public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayCreateStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.CreateStreamCmd);
			return result;
		} // public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Open stream instance
		public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayFindStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.FindStreamCmd);
			return result;
		} // public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Delete stream instance
		public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayDeleteStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.DeleteStreamCmd);
			return result;
		} // public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Get stream list
		public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayGetStreamListCmd(m_Connection.NativeHandle, InTransactionID, InTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.GetStreamListCmd);
			return result;
		} // public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )

		#region Native Interfaces 
		// C2S: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayJoinRelayInstanceC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayJoinRelayInstanceC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InRelayInstanceID, System.UInt64 InPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerIdentifier );



		// C2S: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayLeaveRelayInstanceC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayLeaveRelayInstanceC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InRelayInstanceID, System.UInt64 InPlayerID );



		// C2S: Relay packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayRelayPacketC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayRelayPacketC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InRelayInstanceID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.UInt16 _sizeOfInPayload,System.Byte[] InPayload );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayCreateStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayCreateStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayFindStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayFindStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayDeleteStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayDeleteStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayGetStreamListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayGetStreamListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket );


		#endregion //Native Interfaces 
	}; // public class SendMessageRelay
	public class SendMessageSvrRelay
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessageSvrRelay( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessageSvrRelay( SF.SFConnection connection )

		// S2C: Event for joined player
		public int  JoinRelayInstanceResS2CEvt( System.Int32 InResult, System.UInt32 InRelayInstanceID, System.UInt32 InMyEndpointID, SF.RelayPlayerInfo[] InMemberInfos )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayJoinRelayInstanceResS2CEvt(m_Connection.NativeHandle, InResult, InRelayInstanceID, InMyEndpointID,(ushort)InMemberInfos.Length, InMemberInfos);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.JoinRelayInstanceResS2CEvt);
			return result;
		} // public int  JoinRelayInstanceResS2CEvt( System.Int32 InResult, System.UInt32 InRelayInstanceID, System.UInt32 InMyEndpointID, SF.RelayPlayerInfo[] InMemberInfos )


		// S2C: Event for Player joined.
		public int  PlayerJoinS2CEvt( System.UInt32 InRelayInstanceID, SF.RelayPlayerInfo InJoinedPlayerInfo )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayPlayerJoinS2CEvt(m_Connection.NativeHandle, InRelayInstanceID,ref InJoinedPlayerInfo);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.PlayerJoinS2CEvt);
			return result;
		} // public int  PlayerJoinS2CEvt( System.UInt32 InRelayInstanceID, SF.RelayPlayerInfo InJoinedPlayerInfo )


		// S2C: Event for Player left.
		public int  PlayerLeftS2CEvt( System.UInt32 InRelayInstanceID, System.UInt64 InLeftPlayerID, System.UInt32 InKickedReason )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayPlayerLeftS2CEvt(m_Connection.NativeHandle, InRelayInstanceID, InLeftPlayerID, InKickedReason);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.PlayerLeftS2CEvt);
			return result;
		} // public int  PlayerLeftS2CEvt( System.UInt32 InRelayInstanceID, System.UInt64 InLeftPlayerID, System.UInt32 InKickedReason )


		// Cmd: Create stream instance
		public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayCreateStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InStreamServerAddr,ref InStreamServerAddrIPV4,System.Text.Encoding.UTF8.GetBytes(InStreamUID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.CreateStreamRes);
			return result;
		} // public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )


		// Cmd: Open stream instance
		public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayFindStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InStreamServerAddr,ref InStreamServerAddrIPV4,System.Text.Encoding.UTF8.GetBytes(InStreamUID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.FindStreamRes);
			return result;
		} // public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )


		// Cmd: Delete stream instance
		public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_RelayDeleteStreamRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.DeleteStreamRes);
			return result;
		} // public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Get stream list
		public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )
		{
 			int result;
			using (var InStreamNamesArray = new ArrayObjectString(InStreamNames))
			{
			result = CSSFNetAdapter_RelayGetStreamListRes(m_Connection.NativeHandle, InTransactionID, InResult,InStreamNamesArray.NativeHandle);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDRelay.GetStreamListRes);
			return result;
		} // public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )


		#region Native Interfaces 
		// S2C: Event for joined player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayJoinRelayInstanceResS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayJoinRelayInstanceResS2CEvt(System.IntPtr InNativeConnectionHandle, System.Int32 InResult, System.UInt32 InRelayInstanceID, System.UInt32 InMyEndpointID, System.UInt16 _sizeOfInMemberInfos,SF.RelayPlayerInfo[] InMemberInfos );



		// S2C: Event for Player joined.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayPlayerJoinS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayPlayerJoinS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InRelayInstanceID, ref SF.RelayPlayerInfo InJoinedPlayerInfo );



		// S2C: Event for Player left.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayPlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayPlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InRelayInstanceID, System.UInt64 InLeftPlayerID, System.UInt32 InKickedReason );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayCreateStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayCreateStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InStreamServerAddr, ref SF.NetAddress InStreamServerAddrIPV4, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamUID );



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayFindStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayFindStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InStreamServerAddr, ref SF.NetAddress InStreamServerAddrIPV4, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamUID );



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayDeleteStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayDeleteStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_RelayGetStreamListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_RelayGetStreamListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, IntPtr InStreamNames );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrRelay




} // namespace SF.Net


