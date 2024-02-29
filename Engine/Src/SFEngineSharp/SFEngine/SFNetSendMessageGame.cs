////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Game Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;
#nullable enable



namespace SF.Net
{
 

	public class SendMessageGame : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageGame()
		{
 		} // public  SendMessageGame()
		public  SendMessageGame( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageGame( SF.SFConnection connection ) : base(connection)

		// C2S: Client heartbeat
		public int  HeartbeatC2SEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameHeartbeatC2SEvt(m_Connection.NativeHandle);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.HeartbeatC2SEvt);
			return result;
		} // public int  HeartbeatC2SEvt(  )


		// Cmd: Player connected from a login server and moved to game server
		public int  JoinGameServerCmd( System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinGameServerCmd(InTransactionID, InAccID, InTicket, InLoginEntityUID, callback);
		} // public int  JoinGameServerCmd( System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		public int  JoinGameServerCmd( SF.TransactionID InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinGameServerCmd(m_Connection.NativeHandle,ref InTransactionID, InAccID, InTicket, InLoginEntityUID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinGameServerCmd, callback);
			return result;
		} // public int  JoinGameServerCmd( SF.TransactionID InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )

		// Cmd: player complition statues
		public int  GetAchievementStatsCmd( System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetAchievementStatsCmd(InTransactionID, InCharacterID, InAchievementStatIDFrom, InAchievementStatIDTo, callback);
		} // public int  GetAchievementStatsCmd( System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		public int  GetAchievementStatsCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetAchievementStatsCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID, InAchievementStatIDFrom, InAchievementStatIDTo);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetAchievementStatsCmd, callback);
			return result;
		} // public int  GetAchievementStatsCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )

		// Cmd: Player complition state
		public int  Dummy1Cmd( System.String InComplitionState, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return Dummy1Cmd(InTransactionID, InComplitionState, callback);
		} // public int  Dummy1Cmd( System.String InComplitionState, Action<SFMessage>? callback = null )
		public int  Dummy1Cmd( SF.TransactionID InTransactionID, System.String InComplitionState, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDummy1Cmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InComplitionState + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.Dummy1Cmd, callback);
			return result;
		} // public int  Dummy1Cmd( SF.TransactionID InTransactionID, System.String InComplitionState, Action<SFMessage>? callback = null )

		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public int  RegisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RegisterGCMCmd(InTransactionID, InGCMRegisteredID, callback);
		} // public int  RegisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		public int  RegisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRegisterGCMCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RegisterGCMCmd, callback);
			return result;
		} // public int  RegisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )

		// Cmd: Unregister Google notification service ID
		public int  UnregisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UnregisterGCMCmd(InTransactionID, InGCMRegisteredID, callback);
		} // public int  UnregisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		public int  UnregisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameUnregisterGCMCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.UnregisterGCMCmd, callback);
			return result;
		} // public int  UnregisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )

		// Cmd: Invite friend
		public int  InviteFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return InviteFriendCmd(InTransactionID, InFriendID, callback);
		} // public int  InviteFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		public int  InviteFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameInviteFriendCmd(m_Connection.NativeHandle,ref InTransactionID, InFriendID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.InviteFriendCmd, callback);
			return result;
		} // public int  InviteFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )

		// Cmd: Accept friend request
		public int  AcceptFriendRequestCmd( System.UInt64 InInviterID, SF.PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AcceptFriendRequestCmd(InTransactionID, InInviterID, InInviterPlatformId, callback);
		} // public int  AcceptFriendRequestCmd( System.UInt64 InInviterID, SF.PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		public int  AcceptFriendRequestCmd( SF.TransactionID InTransactionID, System.UInt64 InInviterID, SF.PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameAcceptFriendRequestCmd(m_Connection.NativeHandle,ref InTransactionID, InInviterID,ref InInviterPlatformId);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.AcceptFriendRequestCmd, callback);
			return result;
		} // public int  AcceptFriendRequestCmd( SF.TransactionID InTransactionID, System.UInt64 InInviterID, SF.PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )

		// Cmd: Remove friden form the friend list
		public int  RemoveFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RemoveFriendCmd(InTransactionID, InFriendID, callback);
		} // public int  RemoveFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		public int  RemoveFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRemoveFriendCmd(m_Connection.NativeHandle,ref InTransactionID, InFriendID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RemoveFriendCmd, callback);
			return result;
		} // public int  RemoveFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )

		// Cmd: Get friend list
		public int  GetFriendListCmd( System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetFriendListCmd(InTransactionID, InStartIndex, InCount, callback);
		} // public int  GetFriendListCmd( System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		public int  GetFriendListCmd( SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetFriendListCmd(m_Connection.NativeHandle,ref InTransactionID, InStartIndex, InCount);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetFriendListCmd, callback);
			return result;
		} // public int  GetFriendListCmd( SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )

		// Cmd: Query notification list
		public int  GetNotificationListCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetNotificationListCmd(InTransactionID, callback);
		} // public int  GetNotificationListCmd( Action<SFMessage>? callback = null )
		public int  GetNotificationListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetNotificationListCmd(m_Connection.NativeHandle,ref InTransactionID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetNotificationListCmd, callback);
			return result;
		} // public int  GetNotificationListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Delete notification
		public int  DeleteNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DeleteNotificationCmd(InTransactionID, InNotificationID, callback);
		} // public int  DeleteNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		public int  DeleteNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDeleteNotificationCmd(m_Connection.NativeHandle,ref InTransactionID, InNotificationID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.DeleteNotificationCmd, callback);
			return result;
		} // public int  DeleteNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: Set notification is read
		public int  SetNotificationReadCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SetNotificationReadCmd(InTransactionID, InNotificationID, callback);
		} // public int  SetNotificationReadCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		public int  SetNotificationReadCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSetNotificationReadCmd(m_Connection.NativeHandle,ref InTransactionID, InNotificationID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SetNotificationReadCmd, callback);
			return result;
		} // public int  SetNotificationReadCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: Accept notification
		public int  AcceptNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AcceptNotificationCmd(InTransactionID, InNotificationID, callback);
		} // public int  AcceptNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		public int  AcceptNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameAcceptNotificationCmd(m_Connection.NativeHandle,ref InTransactionID, InNotificationID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.AcceptNotificationCmd, callback);
			return result;
		} // public int  AcceptNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: PlayerId Conversion
		public int  FindPlayerByPlatformIdCmd( SF.PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByPlatformIdCmd(InTransactionID, InPlatformPlayerId, callback);
		} // public int  FindPlayerByPlatformIdCmd( SF.PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		public int  FindPlayerByPlatformIdCmd( SF.TransactionID InTransactionID, SF.PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlatformIdCmd(m_Connection.NativeHandle,ref InTransactionID,ref InPlatformPlayerId);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByPlatformIdCmd, callback);
			return result;
		} // public int  FindPlayerByPlatformIdCmd( SF.TransactionID InTransactionID, SF.PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )

		// Cmd: PlayerId conversion
		public int  FindPlayerByCharacterNameCmd( System.String InCharacterName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByCharacterNameCmd(InTransactionID, InCharacterName, callback);
		} // public int  FindPlayerByCharacterNameCmd( System.String InCharacterName, Action<SFMessage>? callback = null )
		public int  FindPlayerByCharacterNameCmd( SF.TransactionID InTransactionID, System.String InCharacterName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByCharacterNameCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InCharacterName + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByCharacterNameCmd, callback);
			return result;
		} // public int  FindPlayerByCharacterNameCmd( SF.TransactionID InTransactionID, System.String InCharacterName, Action<SFMessage>? callback = null )

		// Cmd: PlayerId Conversion
		public int  FindPlayerByPlatformUserNameCmd( System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByPlatformUserNameCmd(InTransactionID, InPlatformType, InPlatformUserName, callback);
		} // public int  FindPlayerByPlatformUserNameCmd( System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		public int  FindPlayerByPlatformUserNameCmd( SF.TransactionID InTransactionID, System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlatformUserNameCmd(m_Connection.NativeHandle,ref InTransactionID, InPlatformType,System.Text.Encoding.UTF8.GetBytes(InPlatformUserName + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByPlatformUserNameCmd, callback);
			return result;
		} // public int  FindPlayerByPlatformUserNameCmd( SF.TransactionID InTransactionID, System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )

		// Cmd: Query playerID list
		public int  FindPlayerByEMailCmd( System.String InPlayerEMail, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByEMailCmd(InTransactionID, InPlayerEMail, callback);
		} // public int  FindPlayerByEMailCmd( System.String InPlayerEMail, Action<SFMessage>? callback = null )
		public int  FindPlayerByEMailCmd( SF.TransactionID InTransactionID, System.String InPlayerEMail, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByEMailCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InPlayerEMail + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByEMailCmd, callback);
			return result;
		} // public int  FindPlayerByEMailCmd( SF.TransactionID InTransactionID, System.String InPlayerEMail, Action<SFMessage>? callback = null )

		// Cmd: Query playerID list
		public int  FindPlayerByPlayerIDCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByPlayerIDCmd(InTransactionID, InPlayerID, callback);
		} // public int  FindPlayerByPlayerIDCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public int  FindPlayerByPlayerIDCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlayerIDCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayerID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByPlayerIDCmd, callback);
			return result;
		} // public int  FindPlayerByPlayerIDCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: *Request Player Status Update
		public int  RequestPlayerStatusUpdateCmd( System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestPlayerStatusUpdateCmd(InTransactionID, InTargetPlayerID, callback);
		} // public int  RequestPlayerStatusUpdateCmd( System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )
		public int  RequestPlayerStatusUpdateCmd( SF.TransactionID InTransactionID, System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd(m_Connection.NativeHandle,ref InTransactionID,(ushort)InTargetPlayerID.Length, InTargetPlayerID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestPlayerStatusUpdateCmd, callback);
			return result;
		} // public int  RequestPlayerStatusUpdateCmd( SF.TransactionID InTransactionID, System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Get Ranking list
		public int  GetRankingListCmd( System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetRankingListCmd(InTransactionID, InRankingType, InBaseRanking, InCount, callback);
		} // public int  GetRankingListCmd( System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		public int  GetRankingListCmd( SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetRankingListCmd(m_Connection.NativeHandle,ref InTransactionID, InRankingType, InBaseRanking, InCount);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetRankingListCmd, callback);
			return result;
		} // public int  GetRankingListCmd( SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )

		// Cmd: Game user game play information
		public int  GetUserGamePlayerInfoCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetUserGamePlayerInfoCmd(InTransactionID, callback);
		} // public int  GetUserGamePlayerInfoCmd( Action<SFMessage>? callback = null )
		public int  GetUserGamePlayerInfoCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetUserGamePlayerInfoCmd(m_Connection.NativeHandle,ref InTransactionID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetUserGamePlayerInfoCmd, callback);
			return result;
		} // public int  GetUserGamePlayerInfoCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Game game play information
		public int  GetGamePlayerInfoCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetGamePlayerInfoCmd(InTransactionID, InPlayerID, callback);
		} // public int  GetGamePlayerInfoCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public int  GetGamePlayerInfoCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetGamePlayerInfoCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayerID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetGamePlayerInfoCmd, callback);
			return result;
		} // public int  GetGamePlayerInfoCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Change NickName
		public int  SetNickNameCmd( System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SetNickNameCmd(InTransactionID, InNickName, InIsCostFree, callback);
		} // public int  SetNickNameCmd( System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		public int  SetNickNameCmd( SF.TransactionID InTransactionID, System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSetNickNameCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InIsCostFree);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SetNickNameCmd, callback);
			return result;
		} // public int  SetNickNameCmd( SF.TransactionID InTransactionID, System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )

		// Cmd: Create Party
		public int  CreatePartyCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreatePartyCmd(InTransactionID, callback);
		} // public int  CreatePartyCmd( Action<SFMessage>? callback = null )
		public int  CreatePartyCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCreatePartyCmd(m_Connection.NativeHandle,ref InTransactionID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CreatePartyCmd, callback);
			return result;
		} // public int  CreatePartyCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Join party
		public int  JoinPartyCmd( System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinPartyCmd(InTransactionID, InPartyUID, InInviterID, callback);
		} // public int  JoinPartyCmd( System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )
		public int  JoinPartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinPartyCmd(m_Connection.NativeHandle,ref InTransactionID, InPartyUID, InInviterID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinPartyCmd, callback);
			return result;
		} // public int  JoinPartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )

		// Cmd: Leave party command
		public int  LeavePartyCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LeavePartyCmd(InTransactionID, InPartyUID, InPlayerID, callback);
		} // public int  LeavePartyCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public int  LeavePartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLeavePartyCmd(m_Connection.NativeHandle,ref InTransactionID, InPartyUID, InPlayerID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.LeavePartyCmd, callback);
			return result;
		} // public int  LeavePartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Kick player from the party
		public int  PartyKickPlayerCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyKickPlayerCmd(InTransactionID, InPartyUID, InPlayerID, InPlayerToKick, callback);
		} // public int  PartyKickPlayerCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		public int  PartyKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyKickPlayerCmd(m_Connection.NativeHandle,ref InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyKickPlayerCmd, callback);
			return result;
		} // public int  PartyKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )

		// Cmd: Invite a player to the party
		public int  PartyInviteCmd( System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyInviteCmd(InTransactionID, InInviteTargetID, callback);
		} // public int  PartyInviteCmd( System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )
		public int  PartyInviteCmd( SF.TransactionID InTransactionID, System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteCmd(m_Connection.NativeHandle,ref InTransactionID, InInviteTargetID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyInviteCmd, callback);
			return result;
		} // public int  PartyInviteCmd( SF.TransactionID InTransactionID, System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )

		// Cmd: Send Party quick chat message
		public int  PartyQuickChatMessageCmd( System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyQuickChatMessageCmd(InTransactionID, InQuickChatID, callback);
		} // public int  PartyQuickChatMessageCmd( System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		public int  PartyQuickChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InQuickChatID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyQuickChatMessageCmd, callback);
			return result;
		} // public int  PartyQuickChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )

		// Cmd: Party chatting
		public int  PartyChatMessageCmd( System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyChatMessageCmd(InTransactionID, InChatMessage, callback);
		} // public int  PartyChatMessageCmd( System.String InChatMessage, Action<SFMessage>? callback = null )
		public int  PartyChatMessageCmd( SF.TransactionID InTransactionID, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyChatMessageCmd, callback);
			return result;
		} // public int  PartyChatMessageCmd( SF.TransactionID InTransactionID, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Join to a game instance
		public int  JoinGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinGameInstanceCmd(InTransactionID, InInsUID, callback);
		} // public int  JoinGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		public int  JoinGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InInsUID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinGameInstanceCmd, callback);
			return result;
		} // public int  JoinGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )

		// Cmd: Leave game instance
		public int  LeaveGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LeaveGameInstanceCmd(InTransactionID, InInsUID, callback);
		} // public int  LeaveGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		public int  LeaveGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InInsUID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.LeaveGameInstanceCmd, callback);
			return result;
		} // public int  LeaveGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )

		// Cmd: Search game instance
		public int  SearchGameInstanceCmd( System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SearchGameInstanceCmd(InTransactionID, InSearchKeyword, InZoneTableID, callback);
		} // public int  SearchGameInstanceCmd( System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )
		public int  SearchGameInstanceCmd( SF.TransactionID InTransactionID, System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSearchGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InSearchKeyword + "\0"), InZoneTableID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SearchGameInstanceCmd, callback);
			return result;
		} // public int  SearchGameInstanceCmd( SF.TransactionID InTransactionID, System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )

		// Cmd: Search game instance
		public int  GetCharacterDataInGameInstanceCmd( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetCharacterDataInGameInstanceCmd(InTransactionID, InGameInsUID, InPlayerID, callback);
		} // public int  GetCharacterDataInGameInstanceCmd( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public int  GetCharacterDataInGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InGameInsUID, InPlayerID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetCharacterDataInGameInstanceCmd, callback);
			return result;
		} // public int  GetCharacterDataInGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Request Game match
		public int  RequestGameMatchCmd( System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestGameMatchCmd(InTransactionID, InNumPlayer, InRequestRole, callback);
		} // public int  RequestGameMatchCmd( System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		public int  RequestGameMatchCmd( SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestGameMatchCmd(m_Connection.NativeHandle,ref InTransactionID, InNumPlayer, InRequestRole);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestGameMatchCmd, callback);
			return result;
		} // public int  RequestGameMatchCmd( SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )

		// Cmd: Cancel Game match
		public int  CancelGameMatchCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CancelGameMatchCmd(InTransactionID, callback);
		} // public int  CancelGameMatchCmd( Action<SFMessage>? callback = null )
		public int  CancelGameMatchCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCancelGameMatchCmd(m_Connection.NativeHandle,ref InTransactionID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CancelGameMatchCmd, callback);
			return result;
		} // public int  CancelGameMatchCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Request UGC template list
		public int  GetUGCTemplatesCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetUGCTemplatesCmd(InTransactionID, InTags, callback);
		} // public int  GetUGCTemplatesCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		public int  GetUGCTemplatesCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			using (var InTagsArray = new ArrayObjectString(InTags))
			{
			result = CSSFNetAdapter_GameGetUGCTemplatesCmd(m_Connection.NativeHandle,ref InTransactionID,InTagsArray.NativeHandle);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetUGCTemplatesCmd, callback);
			return result;
		} // public int  GetUGCTemplatesCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )

		// Cmd: Save UGC content data
		public int  SaveUGCCmd( SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SaveUGCCmd(InTransactionID, InUGCMetaData, InUGCContents, callback);
		} // public int  SaveUGCCmd( SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )
		public int  SaveUGCCmd( SF.TransactionID InTransactionID, SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InUGCMetaData_ = InUGCMetaData.ToByteArray();
			var InUGCContents_ = InUGCContents.ToByteArray();
			using (var InUGCMetaData_PinnedPtr_ = new PinnedByteBuffer(InUGCMetaData_))
			using (var InUGCContents_PinnedPtr_ = new PinnedByteBuffer(InUGCContents_))
			{
			result = CSSFNetAdapter_GameSaveUGCCmd(m_Connection.NativeHandle,ref InTransactionID,(ushort)InUGCMetaData_.Length, InUGCMetaData_PinnedPtr_.Ptr,(ushort)InUGCContents_.Length, InUGCContents_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SaveUGCCmd, callback);
			return result;
		} // public int  SaveUGCCmd( SF.TransactionID InTransactionID, SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )

		// Cmd: Request WhiteboardSharing
		public int  SearchUGCCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SearchUGCCmd(InTransactionID, InTags, callback);
		} // public int  SearchUGCCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		public int  SearchUGCCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			using (var InTagsArray = new ArrayObjectString(InTags))
			{
			result = CSSFNetAdapter_GameSearchUGCCmd(m_Connection.NativeHandle,ref InTransactionID,InTagsArray.NativeHandle);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SearchUGCCmd, callback);
			return result;
		} // public int  SearchUGCCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )

		// Cmd: Get UGC content info, name, thumb image and so on
		public int  GetUGCContentInfoCmd( System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetUGCContentInfoCmd(InTransactionID, InUGCID, callback);
		} // public int  GetUGCContentInfoCmd( System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		public int  GetUGCContentInfoCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetUGCContentInfoCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetUGCContentInfoCmd, callback);
			return result;
		} // public int  GetUGCContentInfoCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, Action<SFMessage>? callback = null )

		// Cmd: Request WhiteboardSharing
		public int  DownloadUGCContentCmd( System.UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DownloadUGCContentCmd(InTransactionID, InUGCID, InIsIncludeMetaData, callback);
		} // public int  DownloadUGCContentCmd( System.UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )
		public int  DownloadUGCContentCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDownloadUGCContentCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID, InIsIncludeMetaData);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.DownloadUGCContentCmd, callback);
			return result;
		} // public int  DownloadUGCContentCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )

		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Limit(?)
		public int  RequestUGCZoneInstanceCmd( System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestUGCZoneInstanceCmd(InTransactionID, InUGCID, callback);
		} // public int  RequestUGCZoneInstanceCmd( System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		public int  RequestUGCZoneInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestUGCZoneInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestUGCZoneInstanceCmd, callback);
			return result;
		} // public int  RequestUGCZoneInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, Action<SFMessage>? callback = null )

		// Cmd: Request ugc zone instance
		public int  RequestUGCZoneInstanceCmd( System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestUGCZoneInstanceCmd(InTransactionID, InUGCID, callback);
		} // public int  RequestUGCZoneInstanceCmd( System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		public int  RequestUGCZoneInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestUGCZoneInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestUGCZoneInstanceCmd, callback);
			return result;
		} // public int  RequestUGCZoneInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InUGCID, Action<SFMessage>? callback = null )

		// Cmd: Buy shop item prepare
		public int  BuyShopItemPrepareCmd( System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return BuyShopItemPrepareCmd(InTransactionID, InShopItemID, callback);
		} // public int  BuyShopItemPrepareCmd( System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		public int  BuyShopItemPrepareCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemPrepareCmd(m_Connection.NativeHandle,ref InTransactionID, InShopItemID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.BuyShopItemPrepareCmd, callback);
			return result;
		} // public int  BuyShopItemPrepareCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, Action<SFMessage>? callback = null )

		// Cmd: Buy shop item
		public int  BuyShopItemCmd( System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return BuyShopItemCmd(InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken, callback);
		} // public int  BuyShopItemCmd( System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		public int  BuyShopItemCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemCmd(m_Connection.NativeHandle,ref InTransactionID, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPlatform + "\0"),System.Text.Encoding.UTF8.GetBytes(InPackageName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPurchaseTransactionID + "\0"),(ushort)InPurchaseToken.Length, InPurchaseToken);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.BuyShopItemCmd, callback);
			return result;
		} // public int  BuyShopItemCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )

		// Cmd: Create or Join Chat channel
		public int  CreateOrJoinChatChannelCmd( System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreateOrJoinChatChannelCmd(InTransactionID, InChannelName, InPasscode, callback);
		} // public int  CreateOrJoinChatChannelCmd( System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		public int  CreateOrJoinChatChannelCmd( SF.TransactionID InTransactionID, System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCreateOrJoinChatChannelCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChannelName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CreateOrJoinChatChannelCmd, callback);
			return result;
		} // public int  CreateOrJoinChatChannelCmd( SF.TransactionID InTransactionID, System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )

		// Cmd: Join
		public int  JoinChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinChatChannelCmd(InTransactionID, InChatUID, InInviterID, InPasscode, callback);
		} // public int  JoinChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		public int  JoinChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinChatChannelCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID, InInviterID,System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinChatChannelCmd, callback);
			return result;
		} // public int  JoinChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )

		// Cmd: Leave ChatChannel command
		public int  LeaveChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LeaveChatChannelCmd(InTransactionID, InChatUID, InPlayerID, callback);
		} // public int  LeaveChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public int  LeaveChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLeaveChatChannelCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID, InPlayerID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.LeaveChatChannelCmd, callback);
			return result;
		} // public int  LeaveChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Kick player from the ChatChannel
		public int  ChatChannelKickPlayerCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return ChatChannelKickPlayerCmd(InTransactionID, InChatUID, InPlayerID, InPlayerToKick, callback);
		} // public int  ChatChannelKickPlayerCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		public int  ChatChannelKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelKickPlayerCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.ChatChannelKickPlayerCmd, callback);
			return result;
		} // public int  ChatChannelKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )

		// Cmd: Chat channel sending chatting message
		public int  ChatChannelChatMessageCmd( System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return ChatChannelChatMessageCmd(InTransactionID, InChatUID, InChatMetaData, InChatMessage, callback);
		} // public int  ChatChannelChatMessageCmd( System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		public int  ChatChannelChatMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.ChatChannelChatMessageCmd, callback);
			return result;
		} // public int  ChatChannelChatMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Whisper(tell) other player chatting
		public int  WhisperMessageCmd( System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return WhisperMessageCmd(InTransactionID, InReceiverID, InReceiverName, InChatMetaData, InChatMessage, callback);
		} // public int  WhisperMessageCmd( System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		public int  WhisperMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameWhisperMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InReceiverID,System.Text.Encoding.UTF8.GetBytes(InReceiverName + "\0"),(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.WhisperMessageCmd, callback);
			return result;
		} // public int  WhisperMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Create character
		public int  CreateCharacterCmd( System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreateCharacterCmd(InTransactionID, InCharacterName, InPublicData, InPrivateData, callback);
		} // public int  CreateCharacterCmd( System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		public int  CreateCharacterCmd( SF.TransactionID InTransactionID, System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InPublicData_ = InPublicData.ToByteArray();
			var InPrivateData_ = InPrivateData.ToByteArray();
			using (var InPublicData_PinnedPtr_ = new PinnedByteBuffer(InPublicData_))
			using (var InPrivateData_PinnedPtr_ = new PinnedByteBuffer(InPrivateData_))
			{
			result = CSSFNetAdapter_GameCreateCharacterCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InCharacterName + "\0"),(ushort)InPublicData_.Length, InPublicData_PinnedPtr_.Ptr,(ushort)InPrivateData_.Length, InPrivateData_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CreateCharacterCmd, callback);
			return result;
		} // public int  CreateCharacterCmd( SF.TransactionID InTransactionID, System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )

		// Cmd: Delete character
		public int  DeleteCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DeleteCharacterCmd(InTransactionID, InCharacterID, callback);
		} // public int  DeleteCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		public int  DeleteCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDeleteCharacterCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.DeleteCharacterCmd, callback);
			return result;
		} // public int  DeleteCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Get character list
		public int  GetCharacterListCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetCharacterListCmd(InTransactionID, callback);
		} // public int  GetCharacterListCmd( Action<SFMessage>? callback = null )
		public int  GetCharacterListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterListCmd(m_Connection.NativeHandle,ref InTransactionID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetCharacterListCmd, callback);
			return result;
		} // public int  GetCharacterListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: 
		public int  GetCharacterDataCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetCharacterDataCmd(InTransactionID, InCharacterID, callback);
		} // public int  GetCharacterDataCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		public int  GetCharacterDataCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterDataCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetCharacterDataCmd, callback);
			return result;
		} // public int  GetCharacterDataCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Select character
		public int  SelectCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SelectCharacterCmd(InTransactionID, InCharacterID, callback);
		} // public int  SelectCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		public int  SelectCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSelectCharacterCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SelectCharacterCmd, callback);
			return result;
		} // public int  SelectCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public int  RequestServerNoticeUpdateCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestServerNoticeUpdateCmd(InTransactionID, callback);
		} // public int  RequestServerNoticeUpdateCmd( Action<SFMessage>? callback = null )
		public int  RequestServerNoticeUpdateCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestServerNoticeUpdateCmd(m_Connection.NativeHandle,ref InTransactionID);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestServerNoticeUpdateCmd, callback);
			return result;
		} // public int  RequestServerNoticeUpdateCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: To call general functionality
		public int  CallFunctionCmd( System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CallFunctionCmd(InTransactionID, InFunctionName, InParameters, callback);
		} // public int  CallFunctionCmd( System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		public int  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = CSSFNetAdapter_GameCallFunctionCmd(m_Connection.NativeHandle,ref InTransactionID, InFunctionName,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CallFunctionCmd, callback);
			return result;
		} // public int  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )

		#region Native Interfaces 
		// C2S: Client heartbeat
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameHeartbeatC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameHeartbeatC2SEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Player connected from a login server and moved to game server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameServerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameServerCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );


		// Cmd: player complition statues
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetAchievementStatsCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetAchievementStatsCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo );


		// Cmd: Player complition state
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDummy1Cmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDummy1Cmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InComplitionState );


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRegisterGCMCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRegisterGCMCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InGCMRegisteredID );


		// Cmd: Unregister Google notification service ID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameUnregisterGCMCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameUnregisterGCMCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InGCMRegisteredID );


		// Cmd: Invite friend
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameInviteFriendCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameInviteFriendCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InFriendID );


		// Cmd: Accept friend request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptFriendRequestCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptFriendRequestCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InInviterID, ref SF.PlayerPlatformID InInviterPlatformId );


		// Cmd: Remove friden form the friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveFriendCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveFriendCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InFriendID );


		// Cmd: Get friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetFriendListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetFriendListCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount );


		// Cmd: Query notification list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetNotificationListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetNotificationListCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID );


		// Cmd: Delete notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteNotificationCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteNotificationCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InNotificationID );


		// Cmd: Set notification is read
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNotificationReadCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNotificationReadCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InNotificationID );


		// Cmd: Accept notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptNotificationCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptNotificationCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InNotificationID );


		// Cmd: PlayerId Conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlatformIdCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformIdCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, ref SF.PlayerPlatformID InPlatformPlayerId );


		// Cmd: PlayerId conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByCharacterNameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByCharacterNameCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InCharacterName );


		// Cmd: PlayerId Conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlatformUserNameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformUserNameCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Byte InPlatformType, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlatformUserName );


		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByEMailCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByEMailCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerEMail );


		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlayerIDCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlayerIDCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayerID );


		// Cmd: *Request Player Status Update
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt16 _sizeOfInTargetPlayerID,System.UInt64[] InTargetPlayerID );


		// Cmd: Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetRankingListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetRankingListCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount );


		// Cmd: Game user game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUserGamePlayerInfoCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUserGamePlayerInfoCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID );


		// Cmd: Game game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetGamePlayerInfoCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetGamePlayerInfoCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPlayerID );


		// Cmd: Change NickName
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNickNameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNickNameCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.Byte InIsCostFree );


		// Cmd: Create Party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreatePartyCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreatePartyCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID );


		// Cmd: Join party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinPartyCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinPartyCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID );


		// Cmd: Leave party command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeavePartyCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeavePartyCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID );


		// Cmd: Kick player from the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyKickPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyKickPlayerCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick );


		// Cmd: Invite a player to the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyInviteCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyInviteCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InInviteTargetID );


		// Cmd: Send Party quick chat message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyQuickChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyQuickChatMessageCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InQuickChatID );


		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyChatMessageCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Join to a game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InInsUID );


		// Cmd: Leave game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InInsUID );


		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchGameInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSearchKeyword, System.UInt32 InZoneTableID );


		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID );


		// Cmd: Request Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestGameMatchCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestGameMatchCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole );


		// Cmd: Cancel Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCancelGameMatchCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCancelGameMatchCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID );


		// Cmd: Request UGC template list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUGCTemplatesCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUGCTemplatesCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, IntPtr InTags );


		// Cmd: Save UGC content data
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSaveUGCCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSaveUGCCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt16 _sizeOfInUGCMetaData,IntPtr InUGCMetaData, System.UInt16 _sizeOfInUGCContents,IntPtr InUGCContents );


		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchUGCCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchUGCCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, IntPtr InTags );


		// Cmd: Get UGC content info, name, thumb image and so on
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUGCContentInfoCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUGCContentInfoCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InUGCID );


		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDownloadUGCContentCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDownloadUGCContentCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InUGCID, System.Byte InIsIncludeMetaData );


		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Limit(?)
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestUGCZoneInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestUGCZoneInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InUGCID );


		// Cmd: Request ugc zone instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestUGCZoneInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestUGCZoneInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InUGCID );


		// Cmd: Buy shop item prepare
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemPrepareCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemPrepareCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InShopItemID );


		// Cmd: Buy shop item
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InShopItemID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlatform, [MarshalAs(UnmanagedType.LPArray)] byte[] InPackageName, [MarshalAs(UnmanagedType.LPArray)] byte[] InPurchaseTransactionID, System.UInt16 _sizeOfInPurchaseToken,System.Byte[] InPurchaseToken );


		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateOrJoinChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateOrJoinChatChannelCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InChannelName, [MarshalAs(UnmanagedType.LPArray)] byte[] InPasscode );


		// Cmd: Join
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinChatChannelCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPasscode );


		// Cmd: Leave ChatChannel command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveChatChannelCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID );


		// Cmd: Kick player from the ChatChannel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelKickPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelKickPlayerCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick );


		// Cmd: Chat channel sending chatting message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Whisper(tell) other player chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameWhisperMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameWhisperMessageCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InReceiverID, [MarshalAs(UnmanagedType.LPArray)] byte[] InReceiverName, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Create character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateCharacterCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InCharacterName, System.UInt16 _sizeOfInPublicData,IntPtr InPublicData, System.UInt16 _sizeOfInPrivateData,IntPtr InPrivateData );


		// Cmd: Delete character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteCharacterCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InCharacterID );


		// Cmd: Get character list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterListCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID );


		// Cmd: 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InCharacterID );


		// Cmd: Select character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSelectCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSelectCharacterCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InCharacterID );


		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestServerNoticeUpdateCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestServerNoticeUpdateCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID );


		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCallFunctionCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCallFunctionCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt32 InFunctionName, System.UInt16 _sizeOfInParameters,IntPtr InParameters );


		#endregion //Native Interfaces 
	}; // public class SendMessageGame : SendMessage
	public class SendMessageSvrGame : SendMessage
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif


		public  SendMessageSvrGame()
		{
 		} // public  SendMessageSvrGame()
		public  SendMessageSvrGame( SF.SFConnection connection ) : base(connection)
		{
 		} // public  SendMessageSvrGame( SF.SFConnection connection ) : base(connection)

		// Cmd: Player connected from a login server and moved to game server
		public int  JoinGameServerRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinGameServerRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InGameUID, InPartyUID, InPartyLeaderID,ref InMatchingTicket);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinGameServerRes);
			return result;
		} // public int  JoinGameServerRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )


		// Cmd: player complition statues
		public int  GetAchievementStatsRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.AchievementStat[] InAchievementStats )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetAchievementStatsRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InAchievementStats.Length, InAchievementStats);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetAchievementStatsRes);
			return result;
		} // public int  GetAchievementStatsRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.AchievementStat[] InAchievementStats )


		// Cmd: Player complition state
		public int  Dummy1Res( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDummy1Res(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.Dummy1Res);
			return result;
		} // public int  Dummy1Res( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public int  RegisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRegisterGCMRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RegisterGCMRes);
			return result;
		} // public int  RegisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Unregister Google notification service ID
		public int  UnregisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameUnregisterGCMRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.UnregisterGCMRes);
			return result;
		} // public int  UnregisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Invite friend
		public int  InviteFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameInviteFriendRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.InviteFriendRes);
			return result;
		} // public int  InviteFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Accept friend request
		public int  AcceptFriendRequestRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.FriendInformation InNewFriend )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameAcceptFriendRequestRes(m_Connection.NativeHandle,ref InTransactionID, InResult,ref InNewFriend);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.AcceptFriendRequestRes);
			return result;
		} // public int  AcceptFriendRequestRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.FriendInformation InNewFriend )


		// S2C: Notification for friend request is accepted
		public int  FriendRequestAcceptedS2CEvt( SF.FriendInformation InAccepter )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(m_Connection.NativeHandle,ref InAccepter);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FriendRequestAcceptedS2CEvt);
			return result;
		} // public int  FriendRequestAcceptedS2CEvt( SF.FriendInformation InAccepter )


		// Cmd: Remove friden form the friend list
		public int  RemoveFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRemoveFriendRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InFriendID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RemoveFriendRes);
			return result;
		} // public int  RemoveFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )


		// S2C: Friend removed
		public int  FriendRemovedS2CEvt( System.UInt64 InFriendID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFriendRemovedS2CEvt(m_Connection.NativeHandle, InFriendID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FriendRemovedS2CEvt);
			return result;
		} // public int  FriendRemovedS2CEvt( System.UInt64 InFriendID )


		// Cmd: Get friend list
		public int  GetFriendListRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.FriendInformation[] InFriendList )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetFriendListRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,(ushort)InFriendList.Length, InFriendList);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetFriendListRes);
			return result;
		} // public int  GetFriendListRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.FriendInformation[] InFriendList )


		// Cmd: Query notification list
		public int  GetNotificationListRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetNotificationListRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetNotificationListRes);
			return result;
		} // public int  GetNotificationListRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Delete notification
		public int  DeleteNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDeleteNotificationRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InNotificationID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.DeleteNotificationRes);
			return result;
		} // public int  DeleteNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Set notification is read
		public int  SetNotificationReadRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSetNotificationReadRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InNotificationID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SetNotificationReadRes);
			return result;
		} // public int  SetNotificationReadRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Accept notification
		public int  AcceptNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameAcceptNotificationRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InNotificationID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.AcceptNotificationRes);
			return result;
		} // public int  AcceptNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// S2C: Notify new notification
		public int  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, SF.VariableTable InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = CSSFNetAdapter_GameNotifyS2CEvt(m_Connection.NativeHandle, InNotificationID, InNotificationType,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr, InIsRead, InTimeStamp);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.NotifyS2CEvt);
			return result;
		} // public int  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, SF.VariableTable InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp )


		// Cmd: PlayerId Conversion
		public int  FindPlayerByPlatformIdRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, SF.PlayerPlatformID InPlayerPlatformId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlatformIdRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerId,ref InPlayerPlatformId);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByPlatformIdRes);
			return result;
		} // public int  FindPlayerByPlatformIdRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, SF.PlayerPlatformID InPlayerPlatformId )


		// Cmd: PlayerId conversion
		public int  FindPlayerByCharacterNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByCharacterNameRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerId);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByCharacterNameRes);
			return result;
		} // public int  FindPlayerByCharacterNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId )


		// Cmd: PlayerId Conversion
		public int  FindPlayerByPlatformUserNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, SF.PlayerPlatformID InPlayerPlatformId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerId,ref InPlayerPlatformId);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByPlatformUserNameRes);
			return result;
		} // public int  FindPlayerByPlatformUserNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, SF.PlayerPlatformID InPlayerPlatformId )


		// Cmd: Query playerID list
		public int  FindPlayerByEMailRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByEMailRes(m_Connection.NativeHandle,ref InTransactionID, InResult,ref InPlayer);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByEMailRes);
			return result;
		} // public int  FindPlayerByEMailRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: Query playerID list
		public int  FindPlayerByPlayerIDRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlayerIDRes(m_Connection.NativeHandle,ref InTransactionID, InResult,ref InPlayer);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByPlayerIDRes);
			return result;
		} // public int  FindPlayerByPlayerIDRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: *Request Player Status Update
		public int  RequestPlayerStatusUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestPlayerStatusUpdateRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestPlayerStatusUpdateRes);
			return result;
		} // public int  RequestPlayerStatusUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: *Notify Player Status Updated
		public int  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt(m_Connection.NativeHandle, InPlayerID, InLatestActiveTime, InIsInGame);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.NotifyPlayerStatusUpdatedS2CEvt);
			return result;
		} // public int  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )


		// Cmd: Get Ranking list
		public int  GetRankingListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetRankingListRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetRankingListRes);
			return result;
		} // public int  GetRankingListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: Game user game play information
		public int  GetUserGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameGetUserGamePlayerInfoRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetUserGamePlayerInfoRes);
			return result;
		} // public int  GetUserGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )


		// Cmd: Game game play information
		public int  GetGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameGetGamePlayerInfoRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetGamePlayerInfoRes);
			return result;
		} // public int  GetGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// S2C: Player level up event
		public int  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLevelUpS2CEvt(m_Connection.NativeHandle, InCurrentTotalExp, InCurrentLevel);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LevelUpS2CEvt);
			return result;
		} // public int  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )


		// Cmd: Change NickName
		public int  SetNickNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSetNickNameRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SetNickNameRes);
			return result;
		} // public int  SetNickNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Create Party
		public int  CreatePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCreatePartyRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPartyUID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CreatePartyRes);
			return result;
		} // public int  CreatePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )


		// Cmd: Join party
		public int  JoinPartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinPartyRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPartyUID, InPartyLeaderID,(ushort)InChatHistoryData.Length, InChatHistoryData);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinPartyRes);
			return result;
		} // public int  JoinPartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )


		// S2C: Player Joined event
		public int  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt(m_Connection.NativeHandle, InPartyUID,ref InJoinedPlayer);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyPlayerJoinedS2CEvt);
			return result;
		} // public int  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: Party leader changed event
		public int  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyLeaderChangedS2CEvt(m_Connection.NativeHandle, InPartyUID, InNewLeaderID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyLeaderChangedS2CEvt);
			return result;
		} // public int  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave party command
		public int  LeavePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLeavePartyRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LeavePartyRes);
			return result;
		} // public int  LeavePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Player left event
		public int  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerLeftS2CEvt(m_Connection.NativeHandle, InPartyUID, InLeftPlayerID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyPlayerLeftS2CEvt);
			return result;
		} // public int  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the party
		public int  PartyKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyKickPlayerRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyKickPlayerRes);
			return result;
		} // public int  PartyKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Player kicked message
		public int  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerKickedS2CEvt(m_Connection.NativeHandle, InPartyUID, InKickedPlayerID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyPlayerKickedS2CEvt);
			return result;
		} // public int  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )


		// Cmd: Invite a player to the party
		public int  PartyInviteRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyInviteRes);
			return result;
		} // public int  PartyInviteRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party invite requested
		public int  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteRequestedS2CEvt(m_Connection.NativeHandle, InInviterID,System.Text.Encoding.UTF8.GetBytes(InInviterName + "\0"), InPartyToJoinUID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyInviteRequestedS2CEvt);
			return result;
		} // public int  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )


		// Cmd: Send Party quick chat message
		public int  PartyQuickChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyQuickChatMessageRes);
			return result;
		} // public int  PartyQuickChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public int  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID, InQuickChatID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyQuickChatMessageS2CEvt);
			return result;
		} // public int  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )


		// Cmd: Party chatting
		public int  PartyChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyChatMessageRes);
			return result;
		} // public int  PartyChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public int  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,System.Text.Encoding.UTF8.GetBytes(InSenderName + "\0"),System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyChatMessageS2CEvt);
			return result;
		} // public int  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )


		// Cmd: Join to a game instance
		public int  JoinGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.String InServerPublicAddress )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InInsUID,System.Text.Encoding.UTF8.GetBytes(InServerPublicAddress + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinGameInstanceRes);
			return result;
		} // public int  JoinGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.String InServerPublicAddress )


		// Cmd: Leave game instance
		public int  LeaveGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LeaveGameInstanceRes);
			return result;
		} // public int  LeaveGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Search game instance
		public int  SearchGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InGameInstances )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InGameInstances_ = InGameInstances.ToByteArray();
			using (var InGameInstances_PinnedPtr_ = new PinnedByteBuffer(InGameInstances_))
			{
			result = CSSFNetAdapter_GameSearchGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InGameInstances_.Length, InGameInstances_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SearchGameInstanceRes);
			return result;
		} // public int  SearchGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InGameInstances )


		// Cmd: Search game instance
		public int  GetCharacterDataInGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InGameInstances_ = InGameInstances.ToByteArray();
			using (var InGameInstances_PinnedPtr_ = new PinnedByteBuffer(InGameInstances_))
			{
			result = CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerID,(ushort)InGameInstances_.Length, InGameInstances_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetCharacterDataInGameInstanceRes);
			return result;
		} // public int  GetCharacterDataInGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )


		// Cmd: Request Game match
		public int  RequestGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestGameMatchRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestGameMatchRes);
			return result;
		} // public int  RequestGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game matched
		public int  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGameMatchedS2CEvt(m_Connection.NativeHandle, InInsUID, InTimeStamp,(int) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,(ushort)InChatHistoryData.Length, InChatHistoryData,(ushort)InGameLogData.Length, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchedS2CEvt);
			return result;
		} // public int  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game match failed
		public int  GameMatchFailedS2CEvt( System.Int32 InFailedReason )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGameMatchFailedS2CEvt(m_Connection.NativeHandle, InFailedReason);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchFailedS2CEvt);
			return result;
		} // public int  GameMatchFailedS2CEvt( System.Int32 InFailedReason )


		// S2C: Game matching started
		public int  GameMatchingStartedS2CEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGameMatchingStartedS2CEvt(m_Connection.NativeHandle);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchingStartedS2CEvt);
			return result;
		} // public int  GameMatchingStartedS2CEvt(  )


		// Cmd: Cancel Game match
		public int  CancelGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCancelGameMatchRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CancelGameMatchRes);
			return result;
		} // public int  CancelGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: game matching canceled
		public int  GameMatchingCanceledS2CEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGameMatchingCanceledS2CEvt(m_Connection.NativeHandle);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchingCanceledS2CEvt);
			return result;
		} // public int  GameMatchingCanceledS2CEvt(  )


		// Cmd: Request UGC template list
		public int  GetUGCTemplatesRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InUGCIDs )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameGetUGCTemplatesRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InUGCIDs);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetUGCTemplatesRes);
			return result;
		} // public int  GetUGCTemplatesRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InUGCIDs )


		// Cmd: Save UGC content data
		public int  SaveUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InUGCID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSaveUGCRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InUGCID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SaveUGCRes);
			return result;
		} // public int  SaveUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InUGCID )


		// Cmd: Request WhiteboardSharing
		public int  SearchUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameSearchUGCRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SearchUGCRes);
			return result;
		} // public int  SearchUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Get UGC content info, name, thumb image and so on
		public int  GetUGCContentInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InUGCMetaData_ = InUGCMetaData.ToByteArray();
			using (var InUGCMetaData_PinnedPtr_ = new PinnedByteBuffer(InUGCMetaData_))
			{
			result = CSSFNetAdapter_GameGetUGCContentInfoRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InUGCMetaData_.Length, InUGCMetaData_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetUGCContentInfoRes);
			return result;
		} // public int  GetUGCContentInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )


		// Cmd: Request WhiteboardSharing
		public int  DownloadUGCContentRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InUGCMetaData_ = InUGCMetaData.ToByteArray();
			using (var InUGCMetaData_PinnedPtr_ = new PinnedByteBuffer(InUGCMetaData_))
			{
			result = CSSFNetAdapter_GameDownloadUGCContentRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InUGCMetaData_.Length, InUGCMetaData_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.DownloadUGCContentRes);
			return result;
		} // public int  DownloadUGCContentRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )


		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Limit(?)
		public int  RequestUGCZoneInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InGameInstance )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InGameInstance_ = InGameInstance.ToByteArray();
			using (var InGameInstance_PinnedPtr_ = new PinnedByteBuffer(InGameInstance_))
			{
			result = CSSFNetAdapter_GameRequestUGCZoneInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InGameInstance_.Length, InGameInstance_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestUGCZoneInstanceRes);
			return result;
		} // public int  RequestUGCZoneInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InGameInstance )


		// Cmd: Request ugc zone instance
		public int  RequestUGCZoneInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InGameInstance )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InGameInstance_ = InGameInstance.ToByteArray();
			using (var InGameInstance_PinnedPtr_ = new PinnedByteBuffer(InGameInstance_))
			{
			result = CSSFNetAdapter_GameRequestUGCZoneInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InGameInstance_.Length, InGameInstance_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestUGCZoneInstanceRes);
			return result;
		} // public int  RequestUGCZoneInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InGameInstance )


		// Cmd: Buy shop item prepare
		public int  BuyShopItemPrepareRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemPrepareRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPurchaseID + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.BuyShopItemPrepareRes);
			return result;
		} // public int  BuyShopItemPrepareRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )


		// Cmd: Buy shop item
		public int  BuyShopItemRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InShopItemID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.BuyShopItemRes);
			return result;
		} // public int  BuyShopItemRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )


		// Cmd: Create or Join Chat channel
		public int  CreateOrJoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCreateOrJoinChatChannelRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InChatUID, InChannelLeaderID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CreateOrJoinChatChannelRes);
			return result;
		} // public int  CreateOrJoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )


		// Cmd: Join
		public int  JoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameJoinChatChannelRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InChatUID, InChannelLeaderID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinChatChannelRes);
			return result;
		} // public int  JoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )


		// S2C: Player Joined event
		public int  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt(m_Connection.NativeHandle, InChatUID,ref InJoinedPlayer);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelPlayerJoinedS2CEvt);
			return result;
		} // public int  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: ChatChannel leader changed event
		public int  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt(m_Connection.NativeHandle, InChatUID, InNewLeaderID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelLeaderChangedS2CEvt);
			return result;
		} // public int  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave ChatChannel command
		public int  LeaveChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameLeaveChatChannelRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LeaveChatChannelRes);
			return result;
		} // public int  LeaveChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player left event
		public int  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt(m_Connection.NativeHandle, InChatUID, InLeftPlayerID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelPlayerLeftS2CEvt);
			return result;
		} // public int  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the ChatChannel
		public int  ChatChannelKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelKickPlayerRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelKickPlayerRes);
			return result;
		} // public int  ChatChannelKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player kicked message
		public int  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt(m_Connection.NativeHandle, InChatUID, InKickedPlayerID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelPlayerKickedS2CEvt);
			return result;
		} // public int  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )


		// Cmd: Chat channel sending chatting message
		public int  ChatChannelChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelChatMessageRes);
			return result;
		} // public int  ChatChannelChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Chatting message event
		public int  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelChatMessageS2CEvt);
			return result;
		} // public int  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Whisper(tell) other player chatting
		public int  WhisperMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameWhisperMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.WhisperMessageRes);
			return result;
		} // public int  WhisperMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Other player whispered(tell) to me message event
		public int  WhisperMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameWhisperMessageS2CEvt(m_Connection.NativeHandle, InSenderID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.WhisperMessageS2CEvt);
			return result;
		} // public int  WhisperMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Create character
		public int  CreateCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameCreateCharacterRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InCharacterID);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CreateCharacterRes);
			return result;
		} // public int  CreateCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID )


		// Cmd: Delete character
		public int  DeleteCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameDeleteCharacterRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.DeleteCharacterRes);
			return result;
		} // public int  DeleteCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Get character list
		public int  GetCharacterListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InCharacters )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InCharacters_ = InCharacters.ToByteArray();
			using (var InCharacters_PinnedPtr_ = new PinnedByteBuffer(InCharacters_))
			{
			result = CSSFNetAdapter_GameGetCharacterListRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InCharacters_.Length, InCharacters_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetCharacterListRes);
			return result;
		} // public int  GetCharacterListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InCharacters )


		// Cmd: 
		public int  GetCharacterDataRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InPrivateData, SF.VariableTable InEquipData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InPrivateData_ = InPrivateData.ToByteArray();
			var InEquipData_ = InEquipData.ToByteArray();
			using (var InPrivateData_PinnedPtr_ = new PinnedByteBuffer(InPrivateData_))
			using (var InEquipData_PinnedPtr_ = new PinnedByteBuffer(InEquipData_))
			{
			result = CSSFNetAdapter_GameGetCharacterDataRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InPrivateData_.Length, InPrivateData_PinnedPtr_.Ptr,(ushort)InEquipData_.Length, InEquipData_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetCharacterDataRes);
			return result;
		} // public int  GetCharacterDataRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InPrivateData, SF.VariableTable InEquipData )


		// Cmd: Select character
		public int  SelectCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, SF.VariableTable InAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameSelectCharacterRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InCharacterID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SelectCharacterRes);
			return result;
		} // public int  SelectCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, SF.VariableTable InAttributes )


		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public int  RequestServerNoticeUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameRequestServerNoticeUpdateRes(m_Connection.NativeHandle,ref InTransactionID, InResult);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestServerNoticeUpdateRes);
			return result;
		} // public int  RequestServerNoticeUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Server Notice updated event
		public int  ServerNoticeS2CEvt( System.SByte InNoticeCategory, System.String InServerNoticeMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			{
			result = CSSFNetAdapter_GameServerNoticeS2CEvt(m_Connection.NativeHandle, InNoticeCategory,System.Text.Encoding.UTF8.GetBytes(InServerNoticeMessage + "\0"));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ServerNoticeS2CEvt);
			return result;
		} // public int  ServerNoticeS2CEvt( System.SByte InNoticeCategory, System.String InServerNoticeMessage )


		// Cmd: To call general functionality
		public int  CallFunctionRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InResults )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			int result;
			var InResults_ = InResults.ToByteArray();
			using (var InResults_PinnedPtr_ = new PinnedByteBuffer(InResults_))
			{
			result = CSSFNetAdapter_GameCallFunctionRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InResults_.Length, InResults_PinnedPtr_.Ptr);
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CallFunctionRes);
			return result;
		} // public int  CallFunctionRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InResults )


		#region Native Interfaces 
		// Cmd: Player connected from a login server and moved to game server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameServerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameServerRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, ref SF.MatchingQueueTicket InMatchingTicket );



		// Cmd: player complition statues
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetAchievementStatsRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetAchievementStatsRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInAchievementStats,SF.AchievementStat[] InAchievementStats );



		// Cmd: Player complition state
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDummy1Res", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDummy1Res(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRegisterGCMRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRegisterGCMRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Unregister Google notification service ID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameUnregisterGCMRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameUnregisterGCMRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Invite friend
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameInviteFriendRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameInviteFriendRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Accept friend request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptFriendRequestRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptFriendRequestRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, ref SF.FriendInformation InNewFriend );



		// S2C: Notification for friend request is accepted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(System.IntPtr InNativeConnectionHandle, ref SF.FriendInformation InAccepter );



		// Cmd: Remove friden form the friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveFriendRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveFriendRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InFriendID );



		// S2C: Friend removed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFriendRemovedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFriendRemovedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InFriendID );



		// Cmd: Get friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetFriendListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetFriendListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, System.UInt16 _sizeOfInFriendList,SF.FriendInformation[] InFriendList );



		// Cmd: Query notification list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetNotificationListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetNotificationListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Delete notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteNotificationRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteNotificationRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID );



		// Cmd: Set notification is read
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNotificationReadRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNotificationReadRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID );



		// Cmd: Accept notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptNotificationRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptNotificationRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID );



		// S2C: Notify new notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameNotifyS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameNotifyS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InNotificationID, System.UInt32 InNotificationType, System.UInt16 _sizeOfInParameters,IntPtr InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp );



		// Cmd: PlayerId Conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlatformIdRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformIdRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, ref SF.PlayerPlatformID InPlayerPlatformId );



		// Cmd: PlayerId conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByCharacterNameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByCharacterNameRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId );



		// Cmd: PlayerId Conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, ref SF.PlayerPlatformID InPlayerPlatformId );



		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByEMailRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByEMailRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, ref SF.PlayerInformation InPlayer );



		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlayerIDRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlayerIDRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, ref SF.PlayerInformation InPlayer );



		// Cmd: *Request Player Status Update
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestPlayerStatusUpdateRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestPlayerStatusUpdateRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: *Notify Player Status Updated
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame );



		// Cmd: Get Ranking list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetRankingListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetRankingListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRanking,SF.TotalRankingPlayerInformation[] InRanking );



		// Cmd: Game user game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUserGamePlayerInfoRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUserGamePlayerInfoRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: Game game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetGamePlayerInfoRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetGamePlayerInfoRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// S2C: Player level up event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLevelUpS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLevelUpS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel );



		// Cmd: Change NickName
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNickNameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNickNameRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// Cmd: Create Party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreatePartyRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreatePartyRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID );



		// Cmd: Join party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinPartyRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinPartyRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.UInt16 _sizeOfInChatHistoryData,System.Byte[] InChatHistoryData );



		// S2C: Player Joined event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, ref SF.PlayerInformation InJoinedPlayer );



		// S2C: Party leader changed event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyLeaderChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyLeaderChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InNewLeaderID );



		// Cmd: Leave party command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeavePartyRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeavePartyRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Party Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyPlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyPlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID );



		// Cmd: Kick player from the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyKickPlayerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyKickPlayerRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Party Player kicked message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyPlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyPlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID );



		// Cmd: Invite a player to the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyInviteRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyInviteRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Party invite requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyInviteRequestedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyInviteRequestedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InInviterID, [MarshalAs(UnmanagedType.LPArray)] byte[] InInviterName, System.UInt64 InPartyToJoinUID );



		// Cmd: Send Party quick chat message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyQuickChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyQuickChatMessageRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Party Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.UInt32 InQuickChatID );



		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyChatMessageRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Party Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSenderName, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Join to a game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InServerPublicAddress );



		// Cmd: Leave game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchGameInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInGameInstances,IntPtr InGameInstances );



		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, System.UInt16 _sizeOfInGameInstances,IntPtr InGameInstances );



		// Cmd: Request Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestGameMatchRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestGameMatchRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// S2C: Game matched
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameMatchedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameMatchedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InInsUID, System.UInt32 InTimeStamp, int InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.UInt16 _sizeOfInChatHistoryData,System.Byte[] InChatHistoryData, System.UInt16 _sizeOfInGameLogData,System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// S2C: Game match failed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameMatchFailedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameMatchFailedS2CEvt(System.IntPtr InNativeConnectionHandle, System.Int32 InFailedReason );



		// S2C: Game matching started
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameMatchingStartedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameMatchingStartedS2CEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Cancel Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCancelGameMatchRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCancelGameMatchRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: game matching canceled
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameMatchingCanceledS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameMatchingCanceledS2CEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Request UGC template list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUGCTemplatesRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUGCTemplatesRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InUGCIDs );



		// Cmd: Save UGC content data
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSaveUGCRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSaveUGCRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InUGCID );



		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchUGCRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchUGCRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Get UGC content info, name, thumb image and so on
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUGCContentInfoRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUGCContentInfoRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInUGCMetaData,IntPtr InUGCMetaData );



		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDownloadUGCContentRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDownloadUGCContentRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInUGCMetaData,IntPtr InUGCMetaData );



		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Limit(?)
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestUGCZoneInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestUGCZoneInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInGameInstance,IntPtr InGameInstance );



		// Cmd: Request ugc zone instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestUGCZoneInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestUGCZoneInstanceRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInGameInstance,IntPtr InGameInstance );



		// Cmd: Buy shop item prepare
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemPrepareRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemPrepareRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPurchaseID );



		// Cmd: Buy shop item
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID );



		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateOrJoinChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateOrJoinChatChannelRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID );



		// Cmd: Join
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinChatChannelRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID );



		// S2C: Player Joined event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, ref SF.PlayerInformation InJoinedPlayer );



		// S2C: ChatChannel leader changed event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, System.UInt64 InNewLeaderID );



		// Cmd: Leave ChatChannel command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveChatChannelRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, System.UInt64 InLeftPlayerID );



		// Cmd: Kick player from the ChatChannel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelKickPlayerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelKickPlayerRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Player kicked message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, System.UInt64 InKickedPlayerID );



		// Cmd: Chat channel sending chatting message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Whisper(tell) other player chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameWhisperMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameWhisperMessageRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Other player whispered(tell) to me message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameWhisperMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameWhisperMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Create character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateCharacterRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID );



		// Cmd: Delete character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteCharacterRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Get character list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInCharacters,IntPtr InCharacters );



		// Cmd: 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInPrivateData,IntPtr InPrivateData, System.UInt16 _sizeOfInEquipData,IntPtr InEquipData );



		// Cmd: Select character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSelectCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSelectCharacterRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestServerNoticeUpdateRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestServerNoticeUpdateRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// S2C: Server Notice updated event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameServerNoticeS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameServerNoticeS2CEvt(System.IntPtr InNativeConnectionHandle, System.SByte InNoticeCategory, [MarshalAs(UnmanagedType.LPArray)] byte[] InServerNoticeMessage );



		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCallFunctionRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCallFunctionRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInResults,IntPtr InResults );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrGame : SendMessage




} // namespace SF.Net
#nullable restore


