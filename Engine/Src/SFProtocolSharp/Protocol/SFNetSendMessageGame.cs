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
		public Result  HeartbeatC2SEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameHeartbeatC2SEvt(m_Connection.NativeHandle));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.HeartbeatC2SEvt);
			return result;
		} // public Result  HeartbeatC2SEvt(  )


		// Cmd: Player connected from a login server and moved to game server
		public Result  JoinGameServerCmd( System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinGameServerCmd(InTransactionID, InAccID, InTicket, InLoginEntityUID, callback);
		} // public Result  JoinGameServerCmd( System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		public Result  JoinGameServerCmd( SF.TransactionID InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinGameServerCmd(m_Connection.NativeHandle,ref InTransactionID, InAccID, InTicket, InLoginEntityUID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinGameServerCmd, callback);
			return result;
		} // public Result  JoinGameServerCmd( SF.TransactionID InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID, Action<SFMessage>? callback = null )

		// Cmd: player complition statues
		public Result  GetAchievementStatsCmd( System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetAchievementStatsCmd(InTransactionID, InCharacterID, InAchievementStatIDFrom, InAchievementStatIDTo, callback);
		} // public Result  GetAchievementStatsCmd( System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		public Result  GetAchievementStatsCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetAchievementStatsCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID, InAchievementStatIDFrom, InAchievementStatIDTo));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetAchievementStatsCmd, callback);
			return result;
		} // public Result  GetAchievementStatsCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, System.UInt32 InAchievementStatIDFrom, System.UInt32 InAchievementStatIDTo, Action<SFMessage>? callback = null )

		// Cmd: Player complition state
		public Result  Dummy1Cmd( System.String InComplitionState, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return Dummy1Cmd(InTransactionID, InComplitionState, callback);
		} // public Result  Dummy1Cmd( System.String InComplitionState, Action<SFMessage>? callback = null )
		public Result  Dummy1Cmd( SF.TransactionID InTransactionID, System.String InComplitionState, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDummy1Cmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InComplitionState + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.Dummy1Cmd, callback);
			return result;
		} // public Result  Dummy1Cmd( SF.TransactionID InTransactionID, System.String InComplitionState, Action<SFMessage>? callback = null )

		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public Result  RegisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RegisterGCMCmd(InTransactionID, InGCMRegisteredID, callback);
		} // public Result  RegisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		public Result  RegisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRegisterGCMCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RegisterGCMCmd, callback);
			return result;
		} // public Result  RegisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )

		// Cmd: Unregister Google notification service ID
		public Result  UnregisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return UnregisterGCMCmd(InTransactionID, InGCMRegisteredID, callback);
		} // public Result  UnregisterGCMCmd( System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		public Result  UnregisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameUnregisterGCMCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.UnregisterGCMCmd, callback);
			return result;
		} // public Result  UnregisterGCMCmd( SF.TransactionID InTransactionID, System.String InGCMRegisteredID, Action<SFMessage>? callback = null )

		// Cmd: Invite friend
		public Result  InviteFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return InviteFriendCmd(InTransactionID, InFriendID, callback);
		} // public Result  InviteFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		public Result  InviteFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameInviteFriendCmd(m_Connection.NativeHandle,ref InTransactionID, InFriendID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.InviteFriendCmd, callback);
			return result;
		} // public Result  InviteFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )

		// Cmd: Accept friend request
		public Result  AcceptFriendRequestCmd( System.UInt64 InInviterID, PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AcceptFriendRequestCmd(InTransactionID, InInviterID, InInviterPlatformId, callback);
		} // public Result  AcceptFriendRequestCmd( System.UInt64 InInviterID, PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		public Result  AcceptFriendRequestCmd( SF.TransactionID InTransactionID, System.UInt64 InInviterID, PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameAcceptFriendRequestCmd(m_Connection.NativeHandle,ref InTransactionID, InInviterID,ref InInviterPlatformId));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.AcceptFriendRequestCmd, callback);
			return result;
		} // public Result  AcceptFriendRequestCmd( SF.TransactionID InTransactionID, System.UInt64 InInviterID, PlayerPlatformID InInviterPlatformId, Action<SFMessage>? callback = null )

		// Cmd: Remove friden form the friend list
		public Result  RemoveFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RemoveFriendCmd(InTransactionID, InFriendID, callback);
		} // public Result  RemoveFriendCmd( System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		public Result  RemoveFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRemoveFriendCmd(m_Connection.NativeHandle,ref InTransactionID, InFriendID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RemoveFriendCmd, callback);
			return result;
		} // public Result  RemoveFriendCmd( SF.TransactionID InTransactionID, System.UInt64 InFriendID, Action<SFMessage>? callback = null )

		// Cmd: Get friend list
		public Result  GetFriendListCmd( System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetFriendListCmd(InTransactionID, InStartIndex, InCount, callback);
		} // public Result  GetFriendListCmd( System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		public Result  GetFriendListCmd( SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetFriendListCmd(m_Connection.NativeHandle,ref InTransactionID, InStartIndex, InCount));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetFriendListCmd, callback);
			return result;
		} // public Result  GetFriendListCmd( SF.TransactionID InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount, Action<SFMessage>? callback = null )

		// Cmd: Query notification list
		public Result  GetNotificationListCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetNotificationListCmd(InTransactionID, callback);
		} // public Result  GetNotificationListCmd( Action<SFMessage>? callback = null )
		public Result  GetNotificationListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetNotificationListCmd(m_Connection.NativeHandle,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetNotificationListCmd, callback);
			return result;
		} // public Result  GetNotificationListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Delete notification
		public Result  DeleteNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DeleteNotificationCmd(InTransactionID, InNotificationID, callback);
		} // public Result  DeleteNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		public Result  DeleteNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDeleteNotificationCmd(m_Connection.NativeHandle,ref InTransactionID, InNotificationID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.DeleteNotificationCmd, callback);
			return result;
		} // public Result  DeleteNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: Set notification is read
		public Result  SetNotificationReadCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SetNotificationReadCmd(InTransactionID, InNotificationID, callback);
		} // public Result  SetNotificationReadCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		public Result  SetNotificationReadCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSetNotificationReadCmd(m_Connection.NativeHandle,ref InTransactionID, InNotificationID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SetNotificationReadCmd, callback);
			return result;
		} // public Result  SetNotificationReadCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: Accept notification
		public Result  AcceptNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return AcceptNotificationCmd(InTransactionID, InNotificationID, callback);
		} // public Result  AcceptNotificationCmd( System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		public Result  AcceptNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameAcceptNotificationCmd(m_Connection.NativeHandle,ref InTransactionID, InNotificationID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.AcceptNotificationCmd, callback);
			return result;
		} // public Result  AcceptNotificationCmd( SF.TransactionID InTransactionID, System.UInt32 InNotificationID, Action<SFMessage>? callback = null )

		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformIdCmd( PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByPlatformIdCmd(InTransactionID, InPlatformPlayerId, callback);
		} // public Result  FindPlayerByPlatformIdCmd( PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		public Result  FindPlayerByPlatformIdCmd( SF.TransactionID InTransactionID, PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByPlatformIdCmd(m_Connection.NativeHandle,ref InTransactionID,ref InPlatformPlayerId));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByPlatformIdCmd, callback);
			return result;
		} // public Result  FindPlayerByPlatformIdCmd( SF.TransactionID InTransactionID, PlayerPlatformID InPlatformPlayerId, Action<SFMessage>? callback = null )

		// Cmd: PlayerId conversion
		public Result  FindPlayerByCharacterNameCmd( System.String InCharacterName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByCharacterNameCmd(InTransactionID, InCharacterName, callback);
		} // public Result  FindPlayerByCharacterNameCmd( System.String InCharacterName, Action<SFMessage>? callback = null )
		public Result  FindPlayerByCharacterNameCmd( SF.TransactionID InTransactionID, System.String InCharacterName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByCharacterNameCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InCharacterName + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByCharacterNameCmd, callback);
			return result;
		} // public Result  FindPlayerByCharacterNameCmd( SF.TransactionID InTransactionID, System.String InCharacterName, Action<SFMessage>? callback = null )

		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformUserNameCmd( System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByPlatformUserNameCmd(InTransactionID, InPlatformType, InPlatformUserName, callback);
		} // public Result  FindPlayerByPlatformUserNameCmd( System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		public Result  FindPlayerByPlatformUserNameCmd( SF.TransactionID InTransactionID, System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByPlatformUserNameCmd(m_Connection.NativeHandle,ref InTransactionID, InPlatformType,System.Text.Encoding.UTF8.GetBytes(InPlatformUserName + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByPlatformUserNameCmd, callback);
			return result;
		} // public Result  FindPlayerByPlatformUserNameCmd( SF.TransactionID InTransactionID, System.Byte InPlatformType, System.String InPlatformUserName, Action<SFMessage>? callback = null )

		// Cmd: Query playerID list
		public Result  FindPlayerByEMailCmd( System.String InPlayerEMail, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByEMailCmd(InTransactionID, InPlayerEMail, callback);
		} // public Result  FindPlayerByEMailCmd( System.String InPlayerEMail, Action<SFMessage>? callback = null )
		public Result  FindPlayerByEMailCmd( SF.TransactionID InTransactionID, System.String InPlayerEMail, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByEMailCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InPlayerEMail + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByEMailCmd, callback);
			return result;
		} // public Result  FindPlayerByEMailCmd( SF.TransactionID InTransactionID, System.String InPlayerEMail, Action<SFMessage>? callback = null )

		// Cmd: Query playerID list
		public Result  FindPlayerByPlayerIDCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return FindPlayerByPlayerIDCmd(InTransactionID, InPlayerID, callback);
		} // public Result  FindPlayerByPlayerIDCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public Result  FindPlayerByPlayerIDCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByPlayerIDCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.FindPlayerByPlayerIDCmd, callback);
			return result;
		} // public Result  FindPlayerByPlayerIDCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: *Request Player Status Update
		public Result  RequestPlayerStatusUpdateCmd( System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestPlayerStatusUpdateCmd(InTransactionID, InTargetPlayerID, callback);
		} // public Result  RequestPlayerStatusUpdateCmd( System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )
		public Result  RequestPlayerStatusUpdateCmd( SF.TransactionID InTransactionID, System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd(m_Connection.NativeHandle,ref InTransactionID,(ushort)InTargetPlayerID.Length, InTargetPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestPlayerStatusUpdateCmd, callback);
			return result;
		} // public Result  RequestPlayerStatusUpdateCmd( SF.TransactionID InTransactionID, System.UInt64[] InTargetPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Get Ranking list
		public Result  GetRankingListCmd( System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetRankingListCmd(InTransactionID, InRankingType, InBaseRanking, InCount, callback);
		} // public Result  GetRankingListCmd( System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		public Result  GetRankingListCmd( SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetRankingListCmd(m_Connection.NativeHandle,ref InTransactionID, InRankingType, InBaseRanking, InCount));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetRankingListCmd, callback);
			return result;
		} // public Result  GetRankingListCmd( SF.TransactionID InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount, Action<SFMessage>? callback = null )

		// Cmd: Game user game play information
		public Result  GetUserGamePlayerInfoCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetUserGamePlayerInfoCmd(InTransactionID, callback);
		} // public Result  GetUserGamePlayerInfoCmd( Action<SFMessage>? callback = null )
		public Result  GetUserGamePlayerInfoCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetUserGamePlayerInfoCmd(m_Connection.NativeHandle,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetUserGamePlayerInfoCmd, callback);
			return result;
		} // public Result  GetUserGamePlayerInfoCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Game game play information
		public Result  GetGamePlayerInfoCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetGamePlayerInfoCmd(InTransactionID, InPlayerID, callback);
		} // public Result  GetGamePlayerInfoCmd( System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public Result  GetGamePlayerInfoCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetGamePlayerInfoCmd(m_Connection.NativeHandle,ref InTransactionID, InPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetGamePlayerInfoCmd, callback);
			return result;
		} // public Result  GetGamePlayerInfoCmd( SF.TransactionID InTransactionID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Change NickName
		public Result  SetNickNameCmd( System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SetNickNameCmd(InTransactionID, InNickName, InIsCostFree, callback);
		} // public Result  SetNickNameCmd( System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		public Result  SetNickNameCmd( SF.TransactionID InTransactionID, System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSetNickNameCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InIsCostFree));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SetNickNameCmd, callback);
			return result;
		} // public Result  SetNickNameCmd( SF.TransactionID InTransactionID, System.String InNickName, System.Byte InIsCostFree, Action<SFMessage>? callback = null )

		// Cmd: Create Party
		public Result  CreatePartyCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreatePartyCmd(InTransactionID, callback);
		} // public Result  CreatePartyCmd( Action<SFMessage>? callback = null )
		public Result  CreatePartyCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCreatePartyCmd(m_Connection.NativeHandle,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CreatePartyCmd, callback);
			return result;
		} // public Result  CreatePartyCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Join party
		public Result  JoinPartyCmd( System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinPartyCmd(InTransactionID, InPartyUID, InInviterID, callback);
		} // public Result  JoinPartyCmd( System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )
		public Result  JoinPartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinPartyCmd(m_Connection.NativeHandle,ref InTransactionID, InPartyUID, InInviterID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinPartyCmd, callback);
			return result;
		} // public Result  JoinPartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID, Action<SFMessage>? callback = null )

		// Cmd: Leave party command
		public Result  LeavePartyCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LeavePartyCmd(InTransactionID, InPartyUID, InPlayerID, callback);
		} // public Result  LeavePartyCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public Result  LeavePartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLeavePartyCmd(m_Connection.NativeHandle,ref InTransactionID, InPartyUID, InPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.LeavePartyCmd, callback);
			return result;
		} // public Result  LeavePartyCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Kick player from the party
		public Result  PartyKickPlayerCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyKickPlayerCmd(InTransactionID, InPartyUID, InPlayerID, InPlayerToKick, callback);
		} // public Result  PartyKickPlayerCmd( System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		public Result  PartyKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyKickPlayerCmd(m_Connection.NativeHandle,ref InTransactionID, InPartyUID, InPlayerID, InPlayerToKick));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyKickPlayerCmd, callback);
			return result;
		} // public Result  PartyKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )

		// Cmd: Invite a player to the party
		public Result  PartyInviteCmd( System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyInviteCmd(InTransactionID, InInviteTargetID, callback);
		} // public Result  PartyInviteCmd( System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )
		public Result  PartyInviteCmd( SF.TransactionID InTransactionID, System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyInviteCmd(m_Connection.NativeHandle,ref InTransactionID, InInviteTargetID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyInviteCmd, callback);
			return result;
		} // public Result  PartyInviteCmd( SF.TransactionID InTransactionID, System.UInt64 InInviteTargetID, Action<SFMessage>? callback = null )

		// Cmd: Send Party quick chat message
		public Result  PartyQuickChatMessageCmd( System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyQuickChatMessageCmd(InTransactionID, InQuickChatID, callback);
		} // public Result  PartyQuickChatMessageCmd( System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		public Result  PartyQuickChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyQuickChatMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InQuickChatID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyQuickChatMessageCmd, callback);
			return result;
		} // public Result  PartyQuickChatMessageCmd( SF.TransactionID InTransactionID, System.UInt32 InQuickChatID, Action<SFMessage>? callback = null )

		// Cmd: Party chatting
		public Result  PartyChatMessageCmd( System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return PartyChatMessageCmd(InTransactionID, InChatMessage, callback);
		} // public Result  PartyChatMessageCmd( System.String InChatMessage, Action<SFMessage>? callback = null )
		public Result  PartyChatMessageCmd( SF.TransactionID InTransactionID, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyChatMessageCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.PartyChatMessageCmd, callback);
			return result;
		} // public Result  PartyChatMessageCmd( SF.TransactionID InTransactionID, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Join to a game instance
		public Result  JoinGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinGameInstanceCmd(InTransactionID, InInsUID, callback);
		} // public Result  JoinGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		public Result  JoinGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InInsUID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinGameInstanceCmd, callback);
			return result;
		} // public Result  JoinGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )

		// Cmd: Leave game instance
		public Result  LeaveGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LeaveGameInstanceCmd(InTransactionID, InInsUID, callback);
		} // public Result  LeaveGameInstanceCmd( System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		public Result  LeaveGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLeaveGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InInsUID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.LeaveGameInstanceCmd, callback);
			return result;
		} // public Result  LeaveGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InInsUID, Action<SFMessage>? callback = null )

		// Cmd: Search game instance
		public Result  SearchGameInstanceCmd( System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SearchGameInstanceCmd(InTransactionID, InSearchKeyword, InZoneTableID, callback);
		} // public Result  SearchGameInstanceCmd( System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )
		public Result  SearchGameInstanceCmd( SF.TransactionID InTransactionID, System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSearchGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InSearchKeyword + "\0"), InZoneTableID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SearchGameInstanceCmd, callback);
			return result;
		} // public Result  SearchGameInstanceCmd( SF.TransactionID InTransactionID, System.String InSearchKeyword, System.UInt32 InZoneTableID, Action<SFMessage>? callback = null )

		// Cmd: Search game instance
		public Result  GetCharacterDataInGameInstanceCmd( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetCharacterDataInGameInstanceCmd(InTransactionID, InGameInsUID, InPlayerID, callback);
		} // public Result  GetCharacterDataInGameInstanceCmd( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public Result  GetCharacterDataInGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InGameInsUID, InPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetCharacterDataInGameInstanceCmd, callback);
			return result;
		} // public Result  GetCharacterDataInGameInstanceCmd( SF.TransactionID InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Request Game match
		public Result  RequestGameMatchCmd( System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestGameMatchCmd(InTransactionID, InNumPlayer, InRequestRole, callback);
		} // public Result  RequestGameMatchCmd( System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		public Result  RequestGameMatchCmd( SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestGameMatchCmd(m_Connection.NativeHandle,ref InTransactionID, InNumPlayer, InRequestRole));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestGameMatchCmd, callback);
			return result;
		} // public Result  RequestGameMatchCmd( SF.TransactionID InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole, Action<SFMessage>? callback = null )

		// Cmd: Cancel Game match
		public Result  CancelGameMatchCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CancelGameMatchCmd(InTransactionID, callback);
		} // public Result  CancelGameMatchCmd( Action<SFMessage>? callback = null )
		public Result  CancelGameMatchCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCancelGameMatchCmd(m_Connection.NativeHandle,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CancelGameMatchCmd, callback);
			return result;
		} // public Result  CancelGameMatchCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: Request UGC template list
		public Result  GetUGCTemplatesCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetUGCTemplatesCmd(InTransactionID, InTags, callback);
		} // public Result  GetUGCTemplatesCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		public Result  GetUGCTemplatesCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			using (var InTagsArray = new ArrayObjectString(InTags))
			{
			result = new Result(CSSFNetAdapter_GameGetUGCTemplatesCmd(m_Connection.NativeHandle,ref InTransactionID,InTagsArray.NativeHandle));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetUGCTemplatesCmd, callback);
			return result;
		} // public Result  GetUGCTemplatesCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )

		// Cmd: Save UGC content data
		public Result  SaveUGCCmd( SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SaveUGCCmd(InTransactionID, InUGCMetaData, InUGCContents, callback);
		} // public Result  SaveUGCCmd( SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )
		public Result  SaveUGCCmd( SF.TransactionID InTransactionID, SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InUGCMetaData_ = InUGCMetaData.ToByteArray();
			var InUGCContents_ = InUGCContents.ToByteArray();
			using (var InUGCMetaData_PinnedPtr_ = new PinnedByteBuffer(InUGCMetaData_))
			using (var InUGCContents_PinnedPtr_ = new PinnedByteBuffer(InUGCContents_))
			{
			result = new Result(CSSFNetAdapter_GameSaveUGCCmd(m_Connection.NativeHandle,ref InTransactionID,(ushort)InUGCMetaData_.Length, InUGCMetaData_PinnedPtr_.Ptr,(ushort)InUGCContents_.Length, InUGCContents_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SaveUGCCmd, callback);
			return result;
		} // public Result  SaveUGCCmd( SF.TransactionID InTransactionID, SF.VariableTable InUGCMetaData, SF.VariableTable InUGCContents, Action<SFMessage>? callback = null )

		// Cmd: Request WhiteboardSharing
		public Result  SearchUGCCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SearchUGCCmd(InTransactionID, InTags, callback);
		} // public Result  SearchUGCCmd( System.String[] InTags, Action<SFMessage>? callback = null )
		public Result  SearchUGCCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			using (var InTagsArray = new ArrayObjectString(InTags))
			{
			result = new Result(CSSFNetAdapter_GameSearchUGCCmd(m_Connection.NativeHandle,ref InTransactionID,InTagsArray.NativeHandle));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SearchUGCCmd, callback);
			return result;
		} // public Result  SearchUGCCmd( SF.TransactionID InTransactionID, System.String[] InTags, Action<SFMessage>? callback = null )

		// Cmd: Get UGC content info, name, thumb image and so on
		public Result  GetUGCContentInfoCmd( UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetUGCContentInfoCmd(InTransactionID, InUGCID, callback);
		} // public Result  GetUGCContentInfoCmd( UInt64 InUGCID, Action<SFMessage>? callback = null )
		public Result  GetUGCContentInfoCmd( SF.TransactionID InTransactionID, UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetUGCContentInfoCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetUGCContentInfoCmd, callback);
			return result;
		} // public Result  GetUGCContentInfoCmd( SF.TransactionID InTransactionID, UInt64 InUGCID, Action<SFMessage>? callback = null )

		// Cmd: Request WhiteboardSharing
		public Result  DownloadUGCContentCmd( UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DownloadUGCContentCmd(InTransactionID, InUGCID, InIsIncludeMetaData, callback);
		} // public Result  DownloadUGCContentCmd( UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )
		public Result  DownloadUGCContentCmd( SF.TransactionID InTransactionID, UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDownloadUGCContentCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID, InIsIncludeMetaData));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.DownloadUGCContentCmd, callback);
			return result;
		} // public Result  DownloadUGCContentCmd( SF.TransactionID InTransactionID, UInt64 InUGCID, System.Byte InIsIncludeMetaData, Action<SFMessage>? callback = null )

		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
		public Result  RequestUGCZoneInstanceCmd( UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestUGCZoneInstanceCmd(InTransactionID, InUGCID, callback);
		} // public Result  RequestUGCZoneInstanceCmd( UInt64 InUGCID, Action<SFMessage>? callback = null )
		public Result  RequestUGCZoneInstanceCmd( SF.TransactionID InTransactionID, UInt64 InUGCID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestUGCZoneInstanceCmd(m_Connection.NativeHandle,ref InTransactionID, InUGCID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestUGCZoneInstanceCmd, callback);
			return result;
		} // public Result  RequestUGCZoneInstanceCmd( SF.TransactionID InTransactionID, UInt64 InUGCID, Action<SFMessage>? callback = null )

		// Cmd: Buy shop item prepare
		public Result  BuyShopItemPrepareCmd( System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return BuyShopItemPrepareCmd(InTransactionID, InShopItemID, callback);
		} // public Result  BuyShopItemPrepareCmd( System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		public Result  BuyShopItemPrepareCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameBuyShopItemPrepareCmd(m_Connection.NativeHandle,ref InTransactionID, InShopItemID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.BuyShopItemPrepareCmd, callback);
			return result;
		} // public Result  BuyShopItemPrepareCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, Action<SFMessage>? callback = null )

		// Cmd: Buy shop item
		public Result  BuyShopItemCmd( System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return BuyShopItemCmd(InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken, callback);
		} // public Result  BuyShopItemCmd( System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		public Result  BuyShopItemCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameBuyShopItemCmd(m_Connection.NativeHandle,ref InTransactionID, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPlatform + "\0"),System.Text.Encoding.UTF8.GetBytes(InPackageName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPurchaseTransactionID + "\0"),(ushort)InPurchaseToken.Length, InPurchaseToken));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.BuyShopItemCmd, callback);
			return result;
		} // public Result  BuyShopItemCmd( SF.TransactionID InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken, Action<SFMessage>? callback = null )

		// Cmd: Create or Join Chat channel
		public Result  CreateOrJoinChatChannelCmd( System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreateOrJoinChatChannelCmd(InTransactionID, InChannelName, InPasscode, callback);
		} // public Result  CreateOrJoinChatChannelCmd( System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		public Result  CreateOrJoinChatChannelCmd( SF.TransactionID InTransactionID, System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCreateOrJoinChatChannelCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChannelName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CreateOrJoinChatChannelCmd, callback);
			return result;
		} // public Result  CreateOrJoinChatChannelCmd( SF.TransactionID InTransactionID, System.String InChannelName, System.String InPasscode, Action<SFMessage>? callback = null )

		// Cmd: Join
		public Result  JoinChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return JoinChatChannelCmd(InTransactionID, InChatUID, InInviterID, InPasscode, callback);
		} // public Result  JoinChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		public Result  JoinChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinChatChannelCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID, InInviterID,System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.JoinChatChannelCmd, callback);
			return result;
		} // public Result  JoinChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode, Action<SFMessage>? callback = null )

		// Cmd: Leave ChatChannel command
		public Result  LeaveChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return LeaveChatChannelCmd(InTransactionID, InChatUID, InPlayerID, callback);
		} // public Result  LeaveChatChannelCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		public Result  LeaveChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLeaveChatChannelCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID, InPlayerID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.LeaveChatChannelCmd, callback);
			return result;
		} // public Result  LeaveChatChannelCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, Action<SFMessage>? callback = null )

		// Cmd: Kick player from the ChatChannel
		public Result  ChatChannelKickPlayerCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return ChatChannelKickPlayerCmd(InTransactionID, InChatUID, InPlayerID, InPlayerToKick, callback);
		} // public Result  ChatChannelKickPlayerCmd( System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		public Result  ChatChannelKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelKickPlayerCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID, InPlayerID, InPlayerToKick));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.ChatChannelKickPlayerCmd, callback);
			return result;
		} // public Result  ChatChannelKickPlayerCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick, Action<SFMessage>? callback = null )

		// Cmd: Chat channel sending chatting message
		public Result  ChatChannelChatMessageCmd( System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return ChatChannelChatMessageCmd(InTransactionID, InChatUID, InChatMetaData, InChatMessage, callback);
		} // public Result  ChatChannelChatMessageCmd( System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		public Result  ChatChannelChatMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = new Result(CSSFNetAdapter_GameChatChannelChatMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InChatUID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.ChatChannelChatMessageCmd, callback);
			return result;
		} // public Result  ChatChannelChatMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Whisper(tell) other player chatting
		public Result  WhisperMessageCmd( System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return WhisperMessageCmd(InTransactionID, InReceiverID, InReceiverName, InChatMetaData, InChatMessage, callback);
		} // public Result  WhisperMessageCmd( System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		public Result  WhisperMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = new Result(CSSFNetAdapter_GameWhisperMessageCmd(m_Connection.NativeHandle,ref InTransactionID, InReceiverID,System.Text.Encoding.UTF8.GetBytes(InReceiverName + "\0"),(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.WhisperMessageCmd, callback);
			return result;
		} // public Result  WhisperMessageCmd( SF.TransactionID InTransactionID, System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage, Action<SFMessage>? callback = null )

		// Cmd: Create character
		public Result  CreateCharacterCmd( System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CreateCharacterCmd(InTransactionID, InCharacterName, InPublicData, InPrivateData, callback);
		} // public Result  CreateCharacterCmd( System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		public Result  CreateCharacterCmd( SF.TransactionID InTransactionID, System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InPublicData_ = InPublicData.ToByteArray();
			var InPrivateData_ = InPrivateData.ToByteArray();
			using (var InPublicData_PinnedPtr_ = new PinnedByteBuffer(InPublicData_))
			using (var InPrivateData_PinnedPtr_ = new PinnedByteBuffer(InPrivateData_))
			{
			result = new Result(CSSFNetAdapter_GameCreateCharacterCmd(m_Connection.NativeHandle,ref InTransactionID,System.Text.Encoding.UTF8.GetBytes(InCharacterName + "\0"),(ushort)InPublicData_.Length, InPublicData_PinnedPtr_.Ptr,(ushort)InPrivateData_.Length, InPrivateData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CreateCharacterCmd, callback);
			return result;
		} // public Result  CreateCharacterCmd( SF.TransactionID InTransactionID, System.String InCharacterName, SF.VariableTable InPublicData, SF.VariableTable InPrivateData, Action<SFMessage>? callback = null )

		// Cmd: Delete character
		public Result  DeleteCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return DeleteCharacterCmd(InTransactionID, InCharacterID, callback);
		} // public Result  DeleteCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		public Result  DeleteCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDeleteCharacterCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.DeleteCharacterCmd, callback);
			return result;
		} // public Result  DeleteCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Get character list
		public Result  GetCharacterListCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetCharacterListCmd(InTransactionID, callback);
		} // public Result  GetCharacterListCmd( Action<SFMessage>? callback = null )
		public Result  GetCharacterListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetCharacterListCmd(m_Connection.NativeHandle,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetCharacterListCmd, callback);
			return result;
		} // public Result  GetCharacterListCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: 
		public Result  GetCharacterDataCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return GetCharacterDataCmd(InTransactionID, InCharacterID, callback);
		} // public Result  GetCharacterDataCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		public Result  GetCharacterDataCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetCharacterDataCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.GetCharacterDataCmd, callback);
			return result;
		} // public Result  GetCharacterDataCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Select character
		public Result  SelectCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return SelectCharacterCmd(InTransactionID, InCharacterID, callback);
		} // public Result  SelectCharacterCmd( System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		public Result  SelectCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSelectCharacterCmd(m_Connection.NativeHandle,ref InTransactionID, InCharacterID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.SelectCharacterCmd, callback);
			return result;
		} // public Result  SelectCharacterCmd( SF.TransactionID InTransactionID, System.UInt32 InCharacterID, Action<SFMessage>? callback = null )

		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public Result  RequestServerNoticeUpdateCmd( Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return RequestServerNoticeUpdateCmd(InTransactionID, callback);
		} // public Result  RequestServerNoticeUpdateCmd( Action<SFMessage>? callback = null )
		public Result  RequestServerNoticeUpdateCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestServerNoticeUpdateCmd(m_Connection.NativeHandle,ref InTransactionID));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.RequestServerNoticeUpdateCmd, callback);
			return result;
		} // public Result  RequestServerNoticeUpdateCmd( SF.TransactionID InTransactionID, Action<SFMessage>? callback = null )

		// Cmd: To call general functionality
		public Result  CallFunctionCmd( System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			TransactionID InTransactionID = NewTransactionID();
			return CallFunctionCmd(InTransactionID, InFunctionName, InParameters, callback);
		} // public Result  CallFunctionCmd( System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = new Result(CSSFNetAdapter_GameCallFunctionCmd(m_Connection.NativeHandle,ref InTransactionID, InFunctionName,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, InTransactionID, MessageIDGame.CallFunctionCmd, callback);
			return result;
		} // public Result  CallFunctionCmd( SF.TransactionID InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters, Action<SFMessage>? callback = null )

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
		static extern int CSSFNetAdapter_GameAcceptFriendRequestCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.UInt64 InInviterID, ref PlayerPlatformID InInviterPlatformId );


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
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformIdCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, ref PlayerPlatformID InPlatformPlayerId );


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
		static extern int CSSFNetAdapter_GameGetUGCContentInfoCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, UInt64 InUGCID );


		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDownloadUGCContentCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDownloadUGCContentCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, UInt64 InUGCID, System.Byte InIsIncludeMetaData );


		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestUGCZoneInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestUGCZoneInstanceCmd(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, UInt64 InUGCID );


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
		public Result  JoinGameServerRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinGameServerRes(m_Connection.NativeHandle,ref InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InGameUID, InPartyUID, InPartyLeaderID,ref InMatchingTicket));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinGameServerRes);
			return result;
		} // public Result  JoinGameServerRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )


		// Cmd: player complition statues
		public Result  GetAchievementStatsRes( SF.TransactionID InTransactionID, System.Int32 InResult, AchievementStat[] InAchievementStats )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetAchievementStatsRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InAchievementStats.Length, InAchievementStats));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetAchievementStatsRes);
			return result;
		} // public Result  GetAchievementStatsRes( SF.TransactionID InTransactionID, System.Int32 InResult, AchievementStat[] InAchievementStats )


		// Cmd: Player complition state
		public Result  Dummy1Res( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDummy1Res(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.Dummy1Res);
			return result;
		} // public Result  Dummy1Res( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public Result  RegisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRegisterGCMRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RegisterGCMRes);
			return result;
		} // public Result  RegisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Unregister Google notification service ID
		public Result  UnregisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameUnregisterGCMRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.UnregisterGCMRes);
			return result;
		} // public Result  UnregisterGCMRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Invite friend
		public Result  InviteFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameInviteFriendRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.InviteFriendRes);
			return result;
		} // public Result  InviteFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Accept friend request
		public Result  AcceptFriendRequestRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InNewFriend )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameAcceptFriendRequestRes(m_Connection.NativeHandle,ref InTransactionID, InResult,ref InNewFriend));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.AcceptFriendRequestRes);
			return result;
		} // public Result  AcceptFriendRequestRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InNewFriend )


		// S2C: Notification for friend request is accepted
		public Result  FriendRequestAcceptedS2CEvt( SF.PlayerInformation InAccepter )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(m_Connection.NativeHandle,ref InAccepter));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FriendRequestAcceptedS2CEvt);
			return result;
		} // public Result  FriendRequestAcceptedS2CEvt( SF.PlayerInformation InAccepter )


		// Cmd: Remove friden form the friend list
		public Result  RemoveFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRemoveFriendRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InFriendID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RemoveFriendRes);
			return result;
		} // public Result  RemoveFriendRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )


		// S2C: Friend removed
		public Result  FriendRemovedS2CEvt( System.UInt64 InFriendID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFriendRemovedS2CEvt(m_Connection.NativeHandle, InFriendID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FriendRemovedS2CEvt);
			return result;
		} // public Result  FriendRemovedS2CEvt( System.UInt64 InFriendID )


		// Cmd: Get friend list
		public Result  GetFriendListRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.PlayerInformation[] InFriendList )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetFriendListRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,(ushort)InFriendList.Length, InFriendList));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetFriendListRes);
			return result;
		} // public Result  GetFriendListRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.PlayerInformation[] InFriendList )


		// Cmd: Query notification list
		public Result  GetNotificationListRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetNotificationListRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetNotificationListRes);
			return result;
		} // public Result  GetNotificationListRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Delete notification
		public Result  DeleteNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDeleteNotificationRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InNotificationID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.DeleteNotificationRes);
			return result;
		} // public Result  DeleteNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Set notification is read
		public Result  SetNotificationReadRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSetNotificationReadRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InNotificationID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SetNotificationReadRes);
			return result;
		} // public Result  SetNotificationReadRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Accept notification
		public Result  AcceptNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameAcceptNotificationRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InNotificationID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.AcceptNotificationRes);
			return result;
		} // public Result  AcceptNotificationRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// S2C: Notify new notification
		public Result  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, SF.VariableTable InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = new Result(CSSFNetAdapter_GameNotifyS2CEvt(m_Connection.NativeHandle, InNotificationID, InNotificationType,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr, InIsRead, InTimeStamp));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.NotifyS2CEvt);
			return result;
		} // public Result  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, SF.VariableTable InParameters, System.Byte InIsRead, System.UInt64 InTimeStamp )


		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformIdRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, PlayerPlatformID InPlayerPlatformId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByPlatformIdRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerId,ref InPlayerPlatformId));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByPlatformIdRes);
			return result;
		} // public Result  FindPlayerByPlatformIdRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, PlayerPlatformID InPlayerPlatformId )


		// Cmd: PlayerId conversion
		public Result  FindPlayerByCharacterNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByCharacterNameRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerId));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByCharacterNameRes);
			return result;
		} // public Result  FindPlayerByCharacterNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId )


		// Cmd: PlayerId Conversion
		public Result  FindPlayerByPlatformUserNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, PlayerPlatformID InPlayerPlatformId )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerId,ref InPlayerPlatformId));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByPlatformUserNameRes);
			return result;
		} // public Result  FindPlayerByPlatformUserNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, PlayerPlatformID InPlayerPlatformId )


		// Cmd: Query playerID list
		public Result  FindPlayerByEMailRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByEMailRes(m_Connection.NativeHandle,ref InTransactionID, InResult,ref InPlayer));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByEMailRes);
			return result;
		} // public Result  FindPlayerByEMailRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: Query playerID list
		public Result  FindPlayerByPlayerIDRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameFindPlayerByPlayerIDRes(m_Connection.NativeHandle,ref InTransactionID, InResult,ref InPlayer));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.FindPlayerByPlayerIDRes);
			return result;
		} // public Result  FindPlayerByPlayerIDRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: *Request Player Status Update
		public Result  RequestPlayerStatusUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestPlayerStatusUpdateRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestPlayerStatusUpdateRes);
			return result;
		} // public Result  RequestPlayerStatusUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: *Notify Player Status Updated
		public Result  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt(m_Connection.NativeHandle, InPlayerID, InLatestActiveTime, InIsInGame));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.NotifyPlayerStatusUpdatedS2CEvt);
			return result;
		} // public Result  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )


		// Cmd: Get Ranking list
		public Result  GetRankingListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetRankingListRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InRanking.Length, InRanking));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetRankingListRes);
			return result;
		} // public Result  GetRankingListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: Game user game play information
		public Result  GetUserGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = new Result(CSSFNetAdapter_GameGetUserGamePlayerInfoRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetUserGamePlayerInfoRes);
			return result;
		} // public Result  GetUserGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )


		// Cmd: Game game play information
		public Result  GetGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = new Result(CSSFNetAdapter_GameGetGamePlayerInfoRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetGamePlayerInfoRes);
			return result;
		} // public Result  GetGamePlayerInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// S2C: Player level up event
		public Result  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLevelUpS2CEvt(m_Connection.NativeHandle, InCurrentTotalExp, InCurrentLevel));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LevelUpS2CEvt);
			return result;
		} // public Result  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )


		// Cmd: Change NickName
		public Result  SetNickNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSetNickNameRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InTotalGem, InTotalGameMoney));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SetNickNameRes);
			return result;
		} // public Result  SetNickNameRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Create Party
		public Result  CreatePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCreatePartyRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPartyUID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CreatePartyRes);
			return result;
		} // public Result  CreatePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )


		// Cmd: Join party
		public Result  JoinPartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinPartyRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPartyUID, InPartyLeaderID,(ushort)InChatHistoryData.Length, InChatHistoryData));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinPartyRes);
			return result;
		} // public Result  JoinPartyRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )


		// S2C: Player Joined event
		public Result  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt(m_Connection.NativeHandle, InPartyUID,ref InJoinedPlayer));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyPlayerJoinedS2CEvt);
			return result;
		} // public Result  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: Party leader changed event
		public Result  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyLeaderChangedS2CEvt(m_Connection.NativeHandle, InPartyUID, InNewLeaderID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyLeaderChangedS2CEvt);
			return result;
		} // public Result  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave party command
		public Result  LeavePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLeavePartyRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LeavePartyRes);
			return result;
		} // public Result  LeavePartyRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Player left event
		public Result  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyPlayerLeftS2CEvt(m_Connection.NativeHandle, InPartyUID, InLeftPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyPlayerLeftS2CEvt);
			return result;
		} // public Result  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the party
		public Result  PartyKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyKickPlayerRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyKickPlayerRes);
			return result;
		} // public Result  PartyKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Player kicked message
		public Result  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyPlayerKickedS2CEvt(m_Connection.NativeHandle, InPartyUID, InKickedPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyPlayerKickedS2CEvt);
			return result;
		} // public Result  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )


		// Cmd: Invite a player to the party
		public Result  PartyInviteRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyInviteRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyInviteRes);
			return result;
		} // public Result  PartyInviteRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party invite requested
		public Result  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyInviteRequestedS2CEvt(m_Connection.NativeHandle, InInviterID,System.Text.Encoding.UTF8.GetBytes(InInviterName + "\0"), InPartyToJoinUID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyInviteRequestedS2CEvt);
			return result;
		} // public Result  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )


		// Cmd: Send Party quick chat message
		public Result  PartyQuickChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyQuickChatMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyQuickChatMessageRes);
			return result;
		} // public Result  PartyQuickChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public Result  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID, InQuickChatID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyQuickChatMessageS2CEvt);
			return result;
		} // public Result  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )


		// Cmd: Party chatting
		public Result  PartyChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyChatMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyChatMessageRes);
			return result;
		} // public Result  PartyChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public Result  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GamePartyChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,System.Text.Encoding.UTF8.GetBytes(InSenderName + "\0"),System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.PartyChatMessageS2CEvt);
			return result;
		} // public Result  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )


		// Cmd: Join to a game instance
		public Result  JoinGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.String InServerPublicAddress )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InInsUID,System.Text.Encoding.UTF8.GetBytes(InServerPublicAddress + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinGameInstanceRes);
			return result;
		} // public Result  JoinGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.String InServerPublicAddress )


		// Cmd: Leave game instance
		public Result  LeaveGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLeaveGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LeaveGameInstanceRes);
			return result;
		} // public Result  LeaveGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Search game instance
		public Result  SearchGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InGameInstances )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InGameInstances_ = InGameInstances.ToByteArray();
			using (var InGameInstances_PinnedPtr_ = new PinnedByteBuffer(InGameInstances_))
			{
			result = new Result(CSSFNetAdapter_GameSearchGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InGameInstances_.Length, InGameInstances_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SearchGameInstanceRes);
			return result;
		} // public Result  SearchGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InGameInstances )


		// Cmd: Search game instance
		public Result  GetCharacterDataInGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InGameInstances_ = InGameInstances.ToByteArray();
			using (var InGameInstances_PinnedPtr_ = new PinnedByteBuffer(InGameInstances_))
			{
			result = new Result(CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InPlayerID,(ushort)InGameInstances_.Length, InGameInstances_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetCharacterDataInGameInstanceRes);
			return result;
		} // public Result  GetCharacterDataInGameInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )


		// Cmd: Request Game match
		public Result  RequestGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestGameMatchRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InTotalGem, InTotalGameMoney));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestGameMatchRes);
			return result;
		} // public Result  RequestGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game matched
		public Result  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGameMatchedS2CEvt(m_Connection.NativeHandle, InInsUID, InTimeStamp,(int) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,(ushort)InChatHistoryData.Length, InChatHistoryData,(ushort)InGameLogData.Length, InGameLogData, InStamina, InTotalGem, InTotalGameMoney));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchedS2CEvt);
			return result;
		} // public Result  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game match failed
		public Result  GameMatchFailedS2CEvt( System.Int32 InFailedReason )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGameMatchFailedS2CEvt(m_Connection.NativeHandle, InFailedReason));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchFailedS2CEvt);
			return result;
		} // public Result  GameMatchFailedS2CEvt( System.Int32 InFailedReason )


		// S2C: Game matching started
		public Result  GameMatchingStartedS2CEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGameMatchingStartedS2CEvt(m_Connection.NativeHandle));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchingStartedS2CEvt);
			return result;
		} // public Result  GameMatchingStartedS2CEvt(  )


		// Cmd: Cancel Game match
		public Result  CancelGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCancelGameMatchRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CancelGameMatchRes);
			return result;
		} // public Result  CancelGameMatchRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: game matching canceled
		public Result  GameMatchingCanceledS2CEvt(  )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGameMatchingCanceledS2CEvt(m_Connection.NativeHandle));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GameMatchingCanceledS2CEvt);
			return result;
		} // public Result  GameMatchingCanceledS2CEvt(  )


		// Cmd: Request UGC template list
		public Result  GetUGCTemplatesRes( SF.TransactionID InTransactionID, System.Int32 InResult, UInt64 InUGCIDs )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameGetUGCTemplatesRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InUGCIDs));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetUGCTemplatesRes);
			return result;
		} // public Result  GetUGCTemplatesRes( SF.TransactionID InTransactionID, System.Int32 InResult, UInt64 InUGCIDs )


		// Cmd: Save UGC content data
		public Result  SaveUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult, UInt64 InUGCID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSaveUGCRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InUGCID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SaveUGCRes);
			return result;
		} // public Result  SaveUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult, UInt64 InUGCID )


		// Cmd: Request WhiteboardSharing
		public Result  SearchUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameSearchUGCRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SearchUGCRes);
			return result;
		} // public Result  SearchUGCRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Get UGC content info, name, thumb image and so on
		public Result  GetUGCContentInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InUGCMetaData_ = InUGCMetaData.ToByteArray();
			using (var InUGCMetaData_PinnedPtr_ = new PinnedByteBuffer(InUGCMetaData_))
			{
			result = new Result(CSSFNetAdapter_GameGetUGCContentInfoRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InUGCMetaData_.Length, InUGCMetaData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetUGCContentInfoRes);
			return result;
		} // public Result  GetUGCContentInfoRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )


		// Cmd: Request WhiteboardSharing
		public Result  DownloadUGCContentRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InUGCMetaData_ = InUGCMetaData.ToByteArray();
			using (var InUGCMetaData_PinnedPtr_ = new PinnedByteBuffer(InUGCMetaData_))
			{
			result = new Result(CSSFNetAdapter_GameDownloadUGCContentRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InUGCMetaData_.Length, InUGCMetaData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.DownloadUGCContentRes);
			return result;
		} // public Result  DownloadUGCContentRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InUGCMetaData )


		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
		public Result  RequestUGCZoneInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InGameInstance )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InGameInstance_ = InGameInstance.ToByteArray();
			using (var InGameInstance_PinnedPtr_ = new PinnedByteBuffer(InGameInstance_))
			{
			result = new Result(CSSFNetAdapter_GameRequestUGCZoneInstanceRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InGameInstance_.Length, InGameInstance_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestUGCZoneInstanceRes);
			return result;
		} // public Result  RequestUGCZoneInstanceRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InGameInstance )


		// Cmd: Buy shop item prepare
		public Result  BuyShopItemPrepareRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameBuyShopItemPrepareRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPurchaseID + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.BuyShopItemPrepareRes);
			return result;
		} // public Result  BuyShopItemPrepareRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )


		// Cmd: Buy shop item
		public Result  BuyShopItemRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameBuyShopItemRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InShopItemID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.BuyShopItemRes);
			return result;
		} // public Result  BuyShopItemRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )


		// Cmd: Create or Join Chat channel
		public Result  CreateOrJoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCreateOrJoinChatChannelRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InChatUID, InChannelLeaderID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CreateOrJoinChatChannelRes);
			return result;
		} // public Result  CreateOrJoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )


		// Cmd: Join
		public Result  JoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameJoinChatChannelRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InChatUID, InChannelLeaderID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.JoinChatChannelRes);
			return result;
		} // public Result  JoinChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )


		// S2C: Player Joined event
		public Result  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt(m_Connection.NativeHandle, InChatUID,ref InJoinedPlayer));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelPlayerJoinedS2CEvt);
			return result;
		} // public Result  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: ChatChannel leader changed event
		public Result  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt(m_Connection.NativeHandle, InChatUID, InNewLeaderID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelLeaderChangedS2CEvt);
			return result;
		} // public Result  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave ChatChannel command
		public Result  LeaveChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameLeaveChatChannelRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.LeaveChatChannelRes);
			return result;
		} // public Result  LeaveChatChannelRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player left event
		public Result  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt(m_Connection.NativeHandle, InChatUID, InLeftPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelPlayerLeftS2CEvt);
			return result;
		} // public Result  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the ChatChannel
		public Result  ChatChannelKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelKickPlayerRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelKickPlayerRes);
			return result;
		} // public Result  ChatChannelKickPlayerRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player kicked message
		public Result  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt(m_Connection.NativeHandle, InChatUID, InKickedPlayerID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelPlayerKickedS2CEvt);
			return result;
		} // public Result  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )


		// Cmd: Chat channel sending chatting message
		public Result  ChatChannelChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameChatChannelChatMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelChatMessageRes);
			return result;
		} // public Result  ChatChannelChatMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Chatting message event
		public Result  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = new Result(CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ChatChannelChatMessageS2CEvt);
			return result;
		} // public Result  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Whisper(tell) other player chatting
		public Result  WhisperMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameWhisperMessageRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.WhisperMessageRes);
			return result;
		} // public Result  WhisperMessageRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Other player whispered(tell) to me message event
		public Result  WhisperMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = new Result(CSSFNetAdapter_GameWhisperMessageS2CEvt(m_Connection.NativeHandle, InSenderID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.WhisperMessageS2CEvt);
			return result;
		} // public Result  WhisperMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Create character
		public Result  CreateCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameCreateCharacterRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InCharacterID));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CreateCharacterRes);
			return result;
		} // public Result  CreateCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID )


		// Cmd: Delete character
		public Result  DeleteCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameDeleteCharacterRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.DeleteCharacterRes);
			return result;
		} // public Result  DeleteCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// Cmd: Get character list
		public Result  GetCharacterListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InCharacters )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InCharacters_ = InCharacters.ToByteArray();
			using (var InCharacters_PinnedPtr_ = new PinnedByteBuffer(InCharacters_))
			{
			result = new Result(CSSFNetAdapter_GameGetCharacterListRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InCharacters_.Length, InCharacters_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetCharacterListRes);
			return result;
		} // public Result  GetCharacterListRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable[] InCharacters )


		// Cmd: 
		public Result  GetCharacterDataRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InPrivateData, SF.VariableTable InEquipData )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InPrivateData_ = InPrivateData.ToByteArray();
			var InEquipData_ = InEquipData.ToByteArray();
			using (var InPrivateData_PinnedPtr_ = new PinnedByteBuffer(InPrivateData_))
			using (var InEquipData_PinnedPtr_ = new PinnedByteBuffer(InEquipData_))
			{
			result = new Result(CSSFNetAdapter_GameGetCharacterDataRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InPrivateData_.Length, InPrivateData_PinnedPtr_.Ptr,(ushort)InEquipData_.Length, InEquipData_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.GetCharacterDataRes);
			return result;
		} // public Result  GetCharacterDataRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InPrivateData, SF.VariableTable InEquipData )


		// Cmd: Select character
		public Result  SelectCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, SF.VariableTable InAttributes )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = new Result(CSSFNetAdapter_GameSelectCharacterRes(m_Connection.NativeHandle,ref InTransactionID, InResult, InCharacterID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.SelectCharacterRes);
			return result;
		} // public Result  SelectCharacterRes( SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, SF.VariableTable InAttributes )


		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public Result  RequestServerNoticeUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameRequestServerNoticeUpdateRes(m_Connection.NativeHandle,ref InTransactionID, InResult));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.RequestServerNoticeUpdateRes);
			return result;
		} // public Result  RequestServerNoticeUpdateRes( SF.TransactionID InTransactionID, System.Int32 InResult )


		// S2C: Server Notice updated event
		public Result  ServerNoticeS2CEvt( System.SByte InNoticeCategory, System.String InServerNoticeMessage )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			{
			result = new Result(CSSFNetAdapter_GameServerNoticeS2CEvt(m_Connection.NativeHandle, InNoticeCategory,System.Text.Encoding.UTF8.GetBytes(InServerNoticeMessage + "\0")));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.ServerNoticeS2CEvt);
			return result;
		} // public Result  ServerNoticeS2CEvt( System.SByte InNoticeCategory, System.String InServerNoticeMessage )


		// Cmd: To call general functionality
		public Result  CallFunctionRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InResults )
		{
 			if (m_Connection == null) return ResultCode.IO_NOT_CONNECTED;
			Result result;
			var InResults_ = InResults.ToByteArray();
			using (var InResults_PinnedPtr_ = new PinnedByteBuffer(InResults_))
			{
			result = new Result(CSSFNetAdapter_GameCallFunctionRes(m_Connection.NativeHandle,ref InTransactionID, InResult,(ushort)InResults_.Length, InResults_PinnedPtr_.Ptr));
			}
			m_Connection.HandleSentMessage(result, TransactionID.Empty, MessageIDGame.CallFunctionRes);
			return result;
		} // public Result  CallFunctionRes( SF.TransactionID InTransactionID, System.Int32 InResult, SF.VariableTable InResults )


		#region Native Interfaces 
		// Cmd: Player connected from a login server and moved to game server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameServerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameServerRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, ref SF.MatchingQueueTicket InMatchingTicket );



		// Cmd: player complition statues
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetAchievementStatsRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetAchievementStatsRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInAchievementStats,AchievementStat[] InAchievementStats );



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
		static extern int CSSFNetAdapter_GameAcceptFriendRequestRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, ref SF.PlayerInformation InNewFriend );



		// S2C: Notification for friend request is accepted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(System.IntPtr InNativeConnectionHandle, ref SF.PlayerInformation InAccepter );



		// Cmd: Remove friden form the friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveFriendRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveFriendRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InFriendID );



		// S2C: Friend removed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFriendRemovedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFriendRemovedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InFriendID );



		// Cmd: Get friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetFriendListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetFriendListRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, System.UInt16 _sizeOfInFriendList,SF.PlayerInformation[] InFriendList );



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
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformIdRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, ref PlayerPlatformID InPlayerPlatformId );



		// Cmd: PlayerId conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByCharacterNameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByCharacterNameRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId );



		// Cmd: PlayerId Conversion
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt64 InPlayerId, ref PlayerPlatformID InPlayerPlatformId );



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
		static extern int CSSFNetAdapter_GameGetUGCTemplatesRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, UInt64 InUGCIDs );



		// Cmd: Save UGC content data
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSaveUGCRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSaveUGCRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, UInt64 InUGCID );



		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchUGCRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchUGCRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult );



		// Cmd: Get UGC content info, name, thumb image and so on
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUGCContentInfoRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUGCContentInfoRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInUGCMetaData,IntPtr InUGCMetaData );



		// Cmd: Request WhiteboardSharing
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDownloadUGCContentRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDownloadUGCContentRes(System.IntPtr InNativeConnectionHandle, ref SF.TransactionID InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInUGCMetaData,IntPtr InUGCMetaData );



		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
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


