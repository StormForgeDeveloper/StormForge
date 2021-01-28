////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
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



namespace SF.Net
{
 

	public class SendMessageGame
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessageGame( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessageGame( SF.SFConnection connection )

		// C2S: Client heart bit
		public int  HeartBitC2SEvt(  )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameHeartBitC2SEvt(m_Connection.NativeHandle);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.HeartBitC2SEvt);
			return result;
		} // public int  HeartBitC2SEvt(  )


		// Cmd: Player connected from a login server and moved to game server
		public int  JoinGameServerCmd( System.UInt64 InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameServerCmd(m_Connection.NativeHandle, InTransactionID, InAccID, InTicket, InLoginEntityUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameServerCmd);
			return result;
		} // public int  JoinGameServerCmd( System.UInt64 InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )

		// Cmd: player complition statues
		public int  GetComplitionStateCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetComplitionStateCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetComplitionStateCmd);
			return result;
		} // public int  GetComplitionStateCmd( System.UInt64 InTransactionID )

		// Cmd: Player complition state
		public int  SetComplitionStateCmd( System.UInt64 InTransactionID, System.String InComplitionState )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetComplitionStateCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InComplitionState + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetComplitionStateCmd);
			return result;
		} // public int  SetComplitionStateCmd( System.UInt64 InTransactionID, System.String InComplitionState )

		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public int  RegisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRegisterGCMCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RegisterGCMCmd);
			return result;
		} // public int  RegisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )

		// Cmd: Unregister Google notification service ID
		public int  UnregisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameUnregisterGCMCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.UnregisterGCMCmd);
			return result;
		} // public int  UnregisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )

		// Cmd: Invite friend
		public int  InviteFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameInviteFriendCmd(m_Connection.NativeHandle, InTransactionID, InFriendID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.InviteFriendCmd);
			return result;
		} // public int  InviteFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )

		// Cmd: Accept friend request
		public int  AcceptFriendRequestCmd( System.UInt64 InTransactionID, System.UInt64 InInviterID, System.UInt64 InInviterFacebookUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptFriendRequestCmd(m_Connection.NativeHandle, InTransactionID, InInviterID, InInviterFacebookUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptFriendRequestCmd);
			return result;
		} // public int  AcceptFriendRequestCmd( System.UInt64 InTransactionID, System.UInt64 InInviterID, System.UInt64 InInviterFacebookUID )

		// Cmd: Remove friden form the friend list
		public int  RemoveFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRemoveFriendCmd(m_Connection.NativeHandle, InTransactionID, InFriendID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RemoveFriendCmd);
			return result;
		} // public int  RemoveFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )

		// Cmd: Get friend list
		public int  GetFriendListCmd( System.UInt64 InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetFriendListCmd(m_Connection.NativeHandle, InTransactionID, InStartIndex, InCount);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetFriendListCmd);
			return result;
		} // public int  GetFriendListCmd( System.UInt64 InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount )

		// Cmd: Query notification list
		public int  GetNotificationListCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetNotificationListCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetNotificationListCmd);
			return result;
		} // public int  GetNotificationListCmd( System.UInt64 InTransactionID )

		// Cmd: Delete notification
		public int  DeleteNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameDeleteNotificationCmd(m_Connection.NativeHandle, InTransactionID, InNotificationID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.DeleteNotificationCmd);
			return result;
		} // public int  DeleteNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )

		// Cmd: Set notification is read
		public int  SetNotificationReadCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNotificationReadCmd(m_Connection.NativeHandle, InTransactionID, InNotificationID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNotificationReadCmd);
			return result;
		} // public int  SetNotificationReadCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )

		// Cmd: Accept notification
		public int  AcceptNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptNotificationCmd(m_Connection.NativeHandle, InTransactionID, InNotificationID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptNotificationCmd);
			return result;
		} // public int  AcceptNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )

		// Cmd: Query playerID list
		public int  FindPlayerByEMailCmd( System.UInt64 InTransactionID, System.String InPlayerEMail )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByEMailCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InPlayerEMail + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByEMailCmd);
			return result;
		} // public int  FindPlayerByEMailCmd( System.UInt64 InTransactionID, System.String InPlayerEMail )

		// Cmd: Query playerID list
		public int  FindPlayerByPlayerIDCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlayerIDCmd(m_Connection.NativeHandle, InTransactionID, InPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByPlayerIDCmd);
			return result;
		} // public int  FindPlayerByPlayerIDCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )

		// Cmd: *Request Player Status Update
		public int  RequestPlayerStatusUpdateCmd( System.UInt64 InTransactionID, System.UInt64[] InTargetPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd(m_Connection.NativeHandle, InTransactionID,(ushort)InTargetPlayerID.Length, InTargetPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestPlayerStatusUpdateCmd);
			return result;
		} // public int  RequestPlayerStatusUpdateCmd( System.UInt64 InTransactionID, System.UInt64[] InTargetPlayerID )

		// Cmd: Get Ranking lise
		public int  GetRankingListCmd( System.UInt64 InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetRankingListCmd(m_Connection.NativeHandle, InTransactionID, InRankingType, InBaseRanking, InCount);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetRankingListCmd);
			return result;
		} // public int  GetRankingListCmd( System.UInt64 InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount )

		// Cmd: Game user game play information
		public int  GetUserGamePlayerInfoCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetUserGamePlayerInfoCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetUserGamePlayerInfoCmd);
			return result;
		} // public int  GetUserGamePlayerInfoCmd( System.UInt64 InTransactionID )

		// Cmd: Game game play information
		public int  GetGamePlayerInfoCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetGamePlayerInfoCmd(m_Connection.NativeHandle, InTransactionID, InPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetGamePlayerInfoCmd);
			return result;
		} // public int  GetGamePlayerInfoCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )

		// Cmd: Change NickName
		public int  SetNickNameCmd( System.UInt64 InTransactionID, System.String InNickName, System.Byte InIsCostFree )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNickNameCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InIsCostFree);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNickNameCmd);
			return result;
		} // public int  SetNickNameCmd( System.UInt64 InTransactionID, System.String InNickName, System.Byte InIsCostFree )

		// Cmd: Create Party
		public int  CreatePartyCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreatePartyCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreatePartyCmd);
			return result;
		} // public int  CreatePartyCmd( System.UInt64 InTransactionID )

		// Cmd: Join party
		public int  JoinPartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinPartyCmd(m_Connection.NativeHandle, InTransactionID, InPartyUID, InInviterID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinPartyCmd);
			return result;
		} // public int  JoinPartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID )

		// Cmd: Leave party command
		public int  LeavePartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeavePartyCmd(m_Connection.NativeHandle, InTransactionID, InPartyUID, InPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeavePartyCmd);
			return result;
		} // public int  LeavePartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID )

		// Cmd: Kick player from the party
		public int  PartyKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyKickPlayerCmd(m_Connection.NativeHandle, InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyKickPlayerCmd);
			return result;
		} // public int  PartyKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )

		// Cmd: Invite a player to the party
		public int  PartyInviteCmd( System.UInt64 InTransactionID, System.UInt64 InInviteTargetID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteCmd(m_Connection.NativeHandle, InTransactionID, InInviteTargetID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyInviteCmd);
			return result;
		} // public int  PartyInviteCmd( System.UInt64 InTransactionID, System.UInt64 InInviteTargetID )

		// Cmd: Send Party quick chat message
		public int  PartyQuickChatMessageCmd( System.UInt64 InTransactionID, System.UInt32 InQuickChatID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageCmd(m_Connection.NativeHandle, InTransactionID, InQuickChatID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyQuickChatMessageCmd);
			return result;
		} // public int  PartyQuickChatMessageCmd( System.UInt64 InTransactionID, System.UInt32 InQuickChatID )

		// Cmd: Party chatting
		public int  PartyChatMessageCmd( System.UInt64 InTransactionID, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyChatMessageCmd);
			return result;
		} // public int  PartyChatMessageCmd( System.UInt64 InTransactionID, System.String InChatMessage )

		// Cmd: Join to a game instance
		public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InInsUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameInstanceCmd);
			return result;
		} // public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )

		// Cmd: Leave game instance
		public int  LeaveGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InInsUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveGameInstanceCmd);
			return result;
		} // public int  LeaveGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )

		// Cmd: Search game instance
		public int  SearchGameInstanceCmd( System.UInt64 InTransactionID, System.String InSearchKeyword )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSearchGameInstanceCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InSearchKeyword + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SearchGameInstanceCmd);
			return result;
		} // public int  SearchGameInstanceCmd( System.UInt64 InTransactionID, System.String InSearchKeyword )

		// Cmd: Search game instance
		public int  GetCharacterDataInGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataInGameInstanceCmd);
			return result;
		} // public int  GetCharacterDataInGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID )

		// Cmd: Join to a game
		public int  JoinGameCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID, System.UInt64 InTicket, System.UInt64 InInsUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameCmd(m_Connection.NativeHandle, InTransactionID, InPlayerID, InTicket, InInsUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameCmd);
			return result;
		} // public int  JoinGameCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID, System.UInt64 InTicket, System.UInt64 InInsUID )

		// Cmd: Leave Game
		public int  LeaveGameCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID, InTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveGameCmd);
			return result;
		} // public int  LeaveGameCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )

		// Cmd: Kick player
		public int  KickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameKickPlayerCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID, InPlayerToKick);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.KickPlayerCmd);
			return result;
		} // public int  KickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )

		// Cmd: Assign role + Game state reset
		public int  AssignRoleCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAssignRoleCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID, InTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AssignRoleCmd);
			return result;
		} // public int  AssignRoleCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )

		// Cmd: Send chatting message to the game
		public int  ChatMessageCmd( System.UInt64 InTransactionID, System.String InChatMessage, System.Byte InRole )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatMessageCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"), InRole);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatMessageCmd);
			return result;
		} // public int  ChatMessageCmd( System.UInt64 InTransactionID, System.String InChatMessage, System.Byte InRole )

		// Cmd: Advance game
		public int  AdvanceGameCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAdvanceGameCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID, InTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AdvanceGameCmd);
			return result;
		} // public int  AdvanceGameCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )

		// Cmd: Vote game advance
		public int  VoteGameAdvanceCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameVoteGameAdvanceCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID, InTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.VoteGameAdvanceCmd);
			return result;
		} // public int  VoteGameAdvanceCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket )

		// Cmd: Vote
		public int  VoteCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket, System.UInt64 InVoteTarget, System.UInt32 InActionSerial )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameVoteCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID, InTicket, InVoteTarget, InActionSerial);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.VoteCmd);
			return result;
		} // public int  VoteCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket, System.UInt64 InVoteTarget, System.UInt32 InActionSerial )

		// Cmd: Play again with the current players
		public int  GamePlayAgainCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayAgainCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayAgainCmd);
			return result;
		} // public int  GamePlayAgainCmd( System.UInt64 InTransactionID )

		// Cmd: Player. reveal a player
		public int  GameRevealPlayerCmd( System.UInt64 InTransactionID, System.UInt64[] InTargetPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameRevealPlayerCmd(m_Connection.NativeHandle, InTransactionID,(ushort)InTargetPlayerID.Length, InTargetPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameRevealPlayerCmd);
			return result;
		} // public int  GameRevealPlayerCmd( System.UInt64 InTransactionID, System.UInt64[] InTargetPlayerID )

		// Cmd: Player. revive himself
		public int  GamePlayerReviveCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayerReviveCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayerReviveCmd);
			return result;
		} // public int  GamePlayerReviveCmd( System.UInt64 InTransactionID )

		// Cmd: Player. reset ranking
		public int  GamePlayerResetRankCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayerResetRankCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayerResetRankCmd);
			return result;
		} // public int  GamePlayerResetRankCmd( System.UInt64 InTransactionID )

		// Cmd: Request Game match
		public int  RequestGameMatchCmd( System.UInt64 InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestGameMatchCmd(m_Connection.NativeHandle, InTransactionID, InNumPlayer, InRequestRole);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestGameMatchCmd);
			return result;
		} // public int  RequestGameMatchCmd( System.UInt64 InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole )

		// Cmd: Cancel Game match
		public int  CancelGameMatchCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCancelGameMatchCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CancelGameMatchCmd);
			return result;
		} // public int  CancelGameMatchCmd( System.UInt64 InTransactionID )

		// Cmd: Buy shop item prepare
		public int  BuyShopItemPrepareCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemPrepareCmd(m_Connection.NativeHandle, InTransactionID, InShopItemID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemPrepareCmd);
			return result;
		} // public int  BuyShopItemPrepareCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID )

		// Cmd: Buy shop item
		public int  BuyShopItemCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemCmd(m_Connection.NativeHandle, InTransactionID, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPlatform + "\0"),System.Text.Encoding.UTF8.GetBytes(InPackageName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPurchaseTransactionID + "\0"),(ushort)InPurchaseToken.Length, InPurchaseToken);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemCmd);
			return result;
		} // public int  BuyShopItemCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken )

		// Cmd: Create or Join Chat channel
		public int  CreateOrJoinChatChannelCmd( System.UInt64 InTransactionID, System.String InChannelName, System.String InPasscode )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreateOrJoinChatChannelCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChannelName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateOrJoinChatChannelCmd);
			return result;
		} // public int  CreateOrJoinChatChannelCmd( System.UInt64 InTransactionID, System.String InChannelName, System.String InPasscode )

		// Cmd: Join
		public int  JoinChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinChatChannelCmd(m_Connection.NativeHandle, InTransactionID, InChatUID, InInviterID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinChatChannelCmd);
			return result;
		} // public int  JoinChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID )

		// Cmd: Leave ChatChannel command
		public int  LeaveChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveChatChannelCmd(m_Connection.NativeHandle, InTransactionID, InChatUID, InPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveChatChannelCmd);
			return result;
		} // public int  LeaveChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID )

		// Cmd: Kick player from the ChatChannel
		public int  ChatChannelKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelKickPlayerCmd(m_Connection.NativeHandle, InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelKickPlayerCmd);
			return result;
		} // public int  ChatChannelKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )

		// Cmd: Party chatting
		public int  ChatChannelChatMessageCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageCmd(m_Connection.NativeHandle, InTransactionID, InChatUID,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelChatMessageCmd);
			return result;
		} // public int  ChatChannelChatMessageCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.String InChatMessage )

		// Cmd: Create character
		public int  CreateCharacterCmd( System.UInt64 InTransactionID, System.String InCharacterName, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameCreateCharacterCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InCharacterName + "\0"),(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateCharacterCmd);
			return result;
		} // public int  CreateCharacterCmd( System.UInt64 InTransactionID, System.String InCharacterName, SF.VariableTable InAttributes )

		// Cmd: Remove character
		public int  RemoveCharacterCmd( System.UInt64 InTransactionID, System.Int32 InCharacterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRemoveCharacterCmd(m_Connection.NativeHandle, InTransactionID, InCharacterID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RemoveCharacterCmd);
			return result;
		} // public int  RemoveCharacterCmd( System.UInt64 InTransactionID, System.Int32 InCharacterID )

		// Cmd: Get character list
		public int  GetCharacterListCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterListCmd(m_Connection.NativeHandle, InTransactionID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterListCmd);
			return result;
		} // public int  GetCharacterListCmd( System.UInt64 InTransactionID )

		// Cmd: 
		public int  GetCharacterDataCmd( System.UInt64 InTransactionID, System.Int32 InCharacterID, System.String[] InAttributeNames )
		{
 			int result;
			using (var InAttributeNamesArray = new ArrayObjectString(InAttributeNames))
			{
			result = CSSFNetAdapter_GameGetCharacterDataCmd(m_Connection.NativeHandle, InTransactionID, InCharacterID,InAttributeNamesArray.NativeHandle);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataCmd);
			return result;
		} // public int  GetCharacterDataCmd( System.UInt64 InTransactionID, System.Int32 InCharacterID, System.String[] InAttributeNames )

		// Cmd: Give my stamina to other player
		public int  GiveStaminaCmd( System.UInt64 InTransactionID, System.UInt64 InTargetPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGiveStaminaCmd(m_Connection.NativeHandle, InTransactionID, InTargetPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GiveStaminaCmd);
			return result;
		} // public int  GiveStaminaCmd( System.UInt64 InTransactionID, System.UInt64 InTargetPlayer )

		// Cmd: For debug, Change configue preset
		public int  SetPresetGameConfigIDCmd( System.UInt64 InTransactionID, System.UInt32 InPresetID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetPresetGameConfigIDCmd(m_Connection.NativeHandle, InTransactionID, InPresetID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetPresetGameConfigIDCmd);
			return result;
		} // public int  SetPresetGameConfigIDCmd( System.UInt64 InTransactionID, System.UInt32 InPresetID )

		#region Native Interfaces 
		// C2S: Client heart bit
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameHeartBitC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameHeartBitC2SEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Player connected from a login server and moved to game server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameServerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameServerCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID );


		// Cmd: player complition statues
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetComplitionStateCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetComplitionStateCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Player complition state
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetComplitionStateCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetComplitionStateCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InComplitionState );


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRegisterGCMCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRegisterGCMCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InGCMRegisteredID );


		// Cmd: Unregister Google notification service ID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameUnregisterGCMCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameUnregisterGCMCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InGCMRegisteredID );


		// Cmd: Invite friend
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameInviteFriendCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameInviteFriendCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InFriendID );


		// Cmd: Accept friend request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptFriendRequestCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptFriendRequestCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InInviterID, System.UInt64 InInviterFacebookUID );


		// Cmd: Remove friden form the friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveFriendCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveFriendCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InFriendID );


		// Cmd: Get friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetFriendListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetFriendListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount );


		// Cmd: Query notification list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetNotificationListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetNotificationListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Delete notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteNotificationCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteNotificationCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InNotificationID );


		// Cmd: Set notification is read
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNotificationReadCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNotificationReadCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InNotificationID );


		// Cmd: Accept notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptNotificationCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptNotificationCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InNotificationID );


		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByEMailCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByEMailCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerEMail );


		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlayerIDCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlayerIDCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayerID );


		// Cmd: *Request Player Status Update
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt16 _sizeOfInTargetPlayerID,System.UInt64[] InTargetPlayerID );


		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetRankingListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetRankingListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount );


		// Cmd: Game user game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUserGamePlayerInfoCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUserGamePlayerInfoCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Game game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetGamePlayerInfoCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetGamePlayerInfoCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayerID );


		// Cmd: Change NickName
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNickNameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNickNameCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.Byte InIsCostFree );


		// Cmd: Create Party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreatePartyCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreatePartyCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Join party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinPartyCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinPartyCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID );


		// Cmd: Leave party command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeavePartyCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeavePartyCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID );


		// Cmd: Kick player from the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyKickPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyKickPlayerCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick );


		// Cmd: Invite a player to the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyInviteCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyInviteCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InInviteTargetID );


		// Cmd: Send Party quick chat message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyQuickChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyQuickChatMessageCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InQuickChatID );


		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyChatMessageCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Join to a game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InInsUID );


		// Cmd: Leave game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InInsUID );


		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSearchKeyword );


		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID );


		// Cmd: Join to a game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayerID, System.UInt64 InTicket, System.UInt64 InInsUID );


		// Cmd: Leave Game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket );


		// Cmd: Kick player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameKickPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameKickPlayerCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick );


		// Cmd: Assign role + Game state reset
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAssignRoleCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAssignRoleCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket );


		// Cmd: Send chatting message to the game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatMessageCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage, System.Byte InRole );


		// Cmd: Advance game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAdvanceGameCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAdvanceGameCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket );


		// Cmd: Vote game advance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameVoteGameAdvanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameVoteGameAdvanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket );


		// Cmd: Vote
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameVoteCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameVoteCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.UInt64 InTicket, System.UInt64 InVoteTarget, System.UInt32 InActionSerial );


		// Cmd: Play again with the current players
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayAgainCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayAgainCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Player. reveal a player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameRevealPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameRevealPlayerCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt16 _sizeOfInTargetPlayerID,System.UInt64[] InTargetPlayerID );


		// Cmd: Player. revive himself
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayerReviveCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayerReviveCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Player. reset ranking
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayerResetRankCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayerResetRankCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Request Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestGameMatchCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestGameMatchCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole );


		// Cmd: Cancel Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCancelGameMatchCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCancelGameMatchCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: Buy shop item prepare
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemPrepareCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemPrepareCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InShopItemID );


		// Cmd: Buy shop item
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InShopItemID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlatform, [MarshalAs(UnmanagedType.LPArray)] byte[] InPackageName, [MarshalAs(UnmanagedType.LPArray)] byte[] InPurchaseTransactionID, System.UInt16 _sizeOfInPurchaseToken,System.Byte[] InPurchaseToken );


		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateOrJoinChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateOrJoinChatChannelCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InChannelName, [MarshalAs(UnmanagedType.LPArray)] byte[] InPasscode );


		// Cmd: Join
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinChatChannelCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID );


		// Cmd: Leave ChatChannel command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveChatChannelCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID );


		// Cmd: Kick player from the ChatChannel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelKickPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelKickPlayerCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick );


		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Create character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateCharacterCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InCharacterName, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );


		// Cmd: Remove character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveCharacterCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InCharacterID );


		// Cmd: Get character list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InCharacterID, IntPtr InAttributeNames );


		// Cmd: Give my stamina to other player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGiveStaminaCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGiveStaminaCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTargetPlayer );


		// Cmd: For debug, Change configue preset
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetPresetGameConfigIDCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetPresetGameConfigIDCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InPresetID );


		#endregion //Native Interfaces 
	}; // public class SendMessageGame
	public class SendMessageSvrGame
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessageSvrGame( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessageSvrGame( SF.SFConnection connection )

		// Cmd: Player connected from a login server and moved to game server
		public int  JoinGameServerRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameServerRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InGameUID, InPartyUID, InPartyLeaderID,ref InMatchingTicket);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameServerRes);
			return result;
		} // public int  JoinGameServerRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )


		// Cmd: player complition statues
		public int  GetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InComplitionState )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetComplitionStateRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InComplitionState + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetComplitionStateRes);
			return result;
		} // public int  GetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InComplitionState )


		// Cmd: Player complition state
		public int  SetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetComplitionStateRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetComplitionStateRes);
			return result;
		} // public int  SetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public int  RegisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRegisterGCMRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RegisterGCMRes);
			return result;
		} // public int  RegisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Unregister Google notification service ID
		public int  UnregisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameUnregisterGCMRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.UnregisterGCMRes);
			return result;
		} // public int  UnregisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Invite friend
		public int  InviteFriendRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameInviteFriendRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.InviteFriendRes);
			return result;
		} // public int  InviteFriendRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Accept friend request
		public int  AcceptFriendRequestRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.FriendInformation InNewFriend )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptFriendRequestRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InNewFriend);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptFriendRequestRes);
			return result;
		} // public int  AcceptFriendRequestRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.FriendInformation InNewFriend )


		// S2C: Notification for friend request is accepted
		public int  FriendRequestAcceptedS2CEvt( SF.FriendInformation InAccepter )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(m_Connection.NativeHandle,ref InAccepter);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FriendRequestAcceptedS2CEvt);
			return result;
		} // public int  FriendRequestAcceptedS2CEvt( SF.FriendInformation InAccepter )


		// Cmd: Remove friden form the friend list
		public int  RemoveFriendRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRemoveFriendRes(m_Connection.NativeHandle, InTransactionID, InResult, InFriendID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RemoveFriendRes);
			return result;
		} // public int  RemoveFriendRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )


		// S2C: Friend removed
		public int  FriendRemovedS2CEvt( System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFriendRemovedS2CEvt(m_Connection.NativeHandle, InFriendID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FriendRemovedS2CEvt);
			return result;
		} // public int  FriendRemovedS2CEvt( System.UInt64 InFriendID )


		// Cmd: Get friend list
		public int  GetFriendListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.FriendInformation[] InFriendList )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetFriendListRes(m_Connection.NativeHandle, InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,(ushort)InFriendList.Length, InFriendList);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetFriendListRes);
			return result;
		} // public int  GetFriendListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.FriendInformation[] InFriendList )


		// Cmd: Query notification list
		public int  GetNotificationListRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetNotificationListRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetNotificationListRes);
			return result;
		} // public int  GetNotificationListRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Delete notification
		public int  DeleteNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameDeleteNotificationRes(m_Connection.NativeHandle, InTransactionID, InResult, InNotificationID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.DeleteNotificationRes);
			return result;
		} // public int  DeleteNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Set notification is read
		public int  SetNotificationReadRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNotificationReadRes(m_Connection.NativeHandle, InTransactionID, InResult, InNotificationID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNotificationReadRes);
			return result;
		} // public int  SetNotificationReadRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Accept notification
		public int  AcceptNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptNotificationRes(m_Connection.NativeHandle, InTransactionID, InResult, InNotificationID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptNotificationRes);
			return result;
		} // public int  AcceptNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// S2C: Notify new notification
		public int  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, System.UInt64 InMessageParam0, System.UInt64 InMessageParam1, System.String InMessageText, System.Byte InIsRead, System.UInt64 InTimeStamp )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameNotifyS2CEvt(m_Connection.NativeHandle, InNotificationID, InNotificationType, InMessageParam0, InMessageParam1,System.Text.Encoding.UTF8.GetBytes(InMessageText + "\0"), InIsRead, InTimeStamp);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.NotifyS2CEvt);
			return result;
		} // public int  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, System.UInt64 InMessageParam0, System.UInt64 InMessageParam1, System.String InMessageText, System.Byte InIsRead, System.UInt64 InTimeStamp )


		// Cmd: Query playerID list
		public int  FindPlayerByEMailRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByEMailRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByEMailRes);
			return result;
		} // public int  FindPlayerByEMailRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: Query playerID list
		public int  FindPlayerByPlayerIDRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlayerIDRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByPlayerIDRes);
			return result;
		} // public int  FindPlayerByPlayerIDRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: *Request Player Status Update
		public int  RequestPlayerStatusUpdateRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestPlayerStatusUpdateRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestPlayerStatusUpdateRes);
			return result;
		} // public int  RequestPlayerStatusUpdateRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: *Notify Player Status Updated
		public int  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt(m_Connection.NativeHandle, InPlayerID, InLatestActiveTime, InIsInGame);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.NotifyPlayerStatusUpdatedS2CEvt);
			return result;
		} // public int  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )


		// Cmd: Get Ranking lise
		public int  GetRankingListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetRankingListRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetRankingListRes);
			return result;
		} // public int  GetRankingListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )


		// Cmd: Game user game play information
		public int  GetUserGamePlayerInfoRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameGetUserGamePlayerInfoRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetUserGamePlayerInfoRes);
			return result;
		} // public int  GetUserGamePlayerInfoRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )


		// Cmd: Game game play information
		public int  GetGamePlayerInfoRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameGetGamePlayerInfoRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetGamePlayerInfoRes);
			return result;
		} // public int  GetGamePlayerInfoRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// S2C: Player level up event
		public int  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLevelUpS2CEvt(m_Connection.NativeHandle, InCurrentTotalExp, InCurrentLevel);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LevelUpS2CEvt);
			return result;
		} // public int  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )


		// Cmd: Change NickName
		public int  SetNickNameRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNickNameRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNickNameRes);
			return result;
		} // public int  SetNickNameRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Create Party
		public int  CreatePartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreatePartyRes(m_Connection.NativeHandle, InTransactionID, InResult, InPartyUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreatePartyRes);
			return result;
		} // public int  CreatePartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )


		// Cmd: Join party
		public int  JoinPartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinPartyRes(m_Connection.NativeHandle, InTransactionID, InResult, InPartyUID, InPartyLeaderID,(ushort)InChatHistoryData.Length, InChatHistoryData);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinPartyRes);
			return result;
		} // public int  JoinPartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )


		// S2C: Player Joined event
		public int  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt(m_Connection.NativeHandle, InPartyUID,ref InJoinedPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyPlayerJoinedS2CEvt);
			return result;
		} // public int  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: Party leader changed event
		public int  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyLeaderChangedS2CEvt(m_Connection.NativeHandle, InPartyUID, InNewLeaderID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyLeaderChangedS2CEvt);
			return result;
		} // public int  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave party command
		public int  LeavePartyRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeavePartyRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeavePartyRes);
			return result;
		} // public int  LeavePartyRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Player left event
		public int  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerLeftS2CEvt(m_Connection.NativeHandle, InPartyUID, InLeftPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyPlayerLeftS2CEvt);
			return result;
		} // public int  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the party
		public int  PartyKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyKickPlayerRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyKickPlayerRes);
			return result;
		} // public int  PartyKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Player kicked message
		public int  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerKickedS2CEvt(m_Connection.NativeHandle, InPartyUID, InKickedPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyPlayerKickedS2CEvt);
			return result;
		} // public int  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )


		// Cmd: Invite a player to the party
		public int  PartyInviteRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyInviteRes);
			return result;
		} // public int  PartyInviteRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party invite requested
		public int  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteRequestedS2CEvt(m_Connection.NativeHandle, InInviterID,System.Text.Encoding.UTF8.GetBytes(InInviterName + "\0"), InPartyToJoinUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyInviteRequestedS2CEvt);
			return result;
		} // public int  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )


		// Cmd: Send Party quick chat message
		public int  PartyQuickChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyQuickChatMessageRes);
			return result;
		} // public int  PartyQuickChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public int  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID, InQuickChatID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyQuickChatMessageS2CEvt);
			return result;
		} // public int  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )


		// Cmd: Party chatting
		public int  PartyChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyChatMessageRes);
			return result;
		} // public int  PartyChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public int  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,System.Text.Encoding.UTF8.GetBytes(InSenderName + "\0"),System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyChatMessageS2CEvt);
			return result;
		} // public int  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )


		// Cmd: Join to a game instance
		public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, SF.NetAddress InServerAddress, SF.NetAddress InServerAddress4 )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InInsUID,ref InServerAddress,ref InServerAddress4);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameInstanceRes);
			return result;
		} // public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, SF.NetAddress InServerAddress, SF.NetAddress InServerAddress4 )


		// Cmd: Leave game instance
		public int  LeaveGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveGameInstanceRes);
			return result;
		} // public int  LeaveGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Search game instance
		public int  SearchGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.GameInstanceInfo[] InGameInstances )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSearchGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InGameInstances.Length, InGameInstances);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SearchGameInstanceRes);
			return result;
		} // public int  SearchGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.GameInstanceInfo[] InGameInstances )


		// Cmd: Search game instance
		public int  GetCharacterDataInGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )
		{
 			int result;
			var InGameInstances_ = InGameInstances.ToByteArray();
			using (var InGameInstances_PinnedPtr_ = new PinnedByteBuffer(InGameInstances_))
			{
			result = CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayerID,(ushort)InGameInstances_.Length, InGameInstances_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataInGameInstanceRes);
			return result;
		} // public int  GetCharacterDataInGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )


		// Cmd: Join to a game
		public int  JoinGameRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameRes(m_Connection.NativeHandle, InTransactionID, InResult, InInsUID, InTimeStamp,(int) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,(ushort)InChatHistoryData.Length, InChatHistoryData,(ushort)InGameLogData.Length, InGameLogData);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameRes);
			return result;
		} // public int  JoinGameRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData )


		// S2C: Player Joined in the game
		public int  PlayerJoinedS2CEvt( System.UInt64 InGameInsUID, SF.PlayerInformation InJoinedPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePlayerJoinedS2CEvt(m_Connection.NativeHandle, InGameInsUID,ref InJoinedPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PlayerJoinedS2CEvt);
			return result;
		} // public int  PlayerJoinedS2CEvt( System.UInt64 InGameInsUID, SF.PlayerInformation InJoinedPlayer )


		// Cmd: Leave Game
		public int  LeaveGameRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveGameRes);
			return result;
		} // public int  LeaveGameRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Player left event
		public int  PlayerLeftS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InLeftPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePlayerLeftS2CEvt(m_Connection.NativeHandle, InGameInsUID, InLeftPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PlayerLeftS2CEvt);
			return result;
		} // public int  PlayerLeftS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player
		public int  KickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameKickPlayerRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.KickPlayerRes);
			return result;
		} // public int  KickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Player kicked
		public int  PlayerKickedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePlayerKickedS2CEvt(m_Connection.NativeHandle, InGameInsUID, InKickedPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PlayerKickedS2CEvt);
			return result;
		} // public int  PlayerKickedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InKickedPlayerID )


		// Cmd: Assign role + Game state reset
		public int  AssignRoleRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAssignRoleRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AssignRoleRes);
			return result;
		} // public int  AssignRoleRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Role assigned event
		public int  RoleAssignedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.Byte InRole )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRoleAssignedS2CEvt(m_Connection.NativeHandle, InGameInsUID, InPlayerID, InRole);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RoleAssignedS2CEvt);
			return result;
		} // public int  RoleAssignedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.Byte InRole )


		// Cmd: Send chatting message to the game
		public int  ChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatMessageRes);
			return result;
		} // public int  ChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Chatting message event 
		public int  ChatMessageS2CEvt( System.UInt64 InSenderID, System.Byte InRole, System.String InSenderName, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID, InRole,System.Text.Encoding.UTF8.GetBytes(InSenderName + "\0"),System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatMessageS2CEvt);
			return result;
		} // public int  ChatMessageS2CEvt( System.UInt64 InSenderID, System.Byte InRole, System.String InSenderName, System.String InChatMessage )


		// Cmd: Advance game
		public int  AdvanceGameRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAdvanceGameRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AdvanceGameRes);
			return result;
		} // public int  AdvanceGameRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: The game state is advanced
		public int  GameAdvancedS2CEvt( System.UInt64 InGameInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameAdvancedS2CEvt(m_Connection.NativeHandle, InGameInsUID, InTimeStamp,(int) InGameState, InDay);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameAdvancedS2CEvt);
			return result;
		} // public int  GameAdvancedS2CEvt( System.UInt64 InGameInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay )


		// S2C: Game is ended
		public int  GameEndedS2CEvt( System.UInt64 InGameInsUID, SF.GameWinner InWinner, System.UInt32 InGainedExp, System.UInt32 InGainedGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameEndedS2CEvt(m_Connection.NativeHandle, InGameInsUID,(int) InWinner, InGainedExp, InGainedGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameEndedS2CEvt);
			return result;
		} // public int  GameEndedS2CEvt( System.UInt64 InGameInsUID, SF.GameWinner InWinner, System.UInt32 InGainedExp, System.UInt32 InGainedGameMoney )


		// Cmd: Vote game advance
		public int  VoteGameAdvanceRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameVoteGameAdvanceRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.VoteGameAdvanceRes);
			return result;
		} // public int  VoteGameAdvanceRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: GameAdvance is Voted
		public int  GameAdvanceVotedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InVoter )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameAdvanceVotedS2CEvt(m_Connection.NativeHandle, InGameInsUID, InVoter);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameAdvanceVotedS2CEvt);
			return result;
		} // public int  GameAdvanceVotedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InVoter )


		// Cmd: Vote
		public int  VoteRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameVoteRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.VoteRes);
			return result;
		} // public int  VoteRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Player Voted
		public int  VotedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InVoter, System.UInt64 InVotedTarget )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameVotedS2CEvt(m_Connection.NativeHandle, InGameInsUID, InVoter, InVotedTarget);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.VotedS2CEvt);
			return result;
		} // public int  VotedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InVoter, System.UInt64 InVotedTarget )


		// S2C: Vote is ended
		public int  VoteEndS2CEvt( System.UInt64 InGameInsUID, System.UInt64[] InVoted )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameVoteEndS2CEvt(m_Connection.NativeHandle, InGameInsUID,(ushort)InVoted.Length, InVoted);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.VoteEndS2CEvt);
			return result;
		} // public int  VoteEndS2CEvt( System.UInt64 InGameInsUID, System.UInt64[] InVoted )


		// S2C: Player Killed
		public int  PlayerKilledS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InKilledPlayer, SF.PlayerKilledReason InReason )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePlayerKilledS2CEvt(m_Connection.NativeHandle, InGameInsUID, InKilledPlayer,(int) InReason);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PlayerKilledS2CEvt);
			return result;
		} // public int  PlayerKilledS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InKilledPlayer, SF.PlayerKilledReason InReason )


		// S2C: Player Voted
		public int  PlayerRevealedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InRevealedPlayerID, System.Byte InRole, SF.PlayerRevealedReason InReason )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePlayerRevealedS2CEvt(m_Connection.NativeHandle, InGameInsUID, InRevealedPlayerID, InRole,(int) InReason);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PlayerRevealedS2CEvt);
			return result;
		} // public int  PlayerRevealedS2CEvt( System.UInt64 InGameInsUID, System.UInt64 InRevealedPlayerID, System.Byte InRole, SF.PlayerRevealedReason InReason )


		// Cmd: Play again with the current players
		public int  GamePlayAgainRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayAgainRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayAgainRes);
			return result;
		} // public int  GamePlayAgainRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
		public int  GamePlayAgainS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeadPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayAgainS2CEvt(m_Connection.NativeHandle, InPartyUID, InLeadPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayAgainS2CEvt);
			return result;
		} // public int  GamePlayAgainS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeadPlayer )


		// Cmd: Player. reveal a player
		public int  GameRevealPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64[] InRevealedPlayerID, System.Byte[] InRevealedRole, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameRevealPlayerRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InRevealedPlayerID.Length, InRevealedPlayerID,(ushort)InRevealedRole.Length, InRevealedRole, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameRevealPlayerRes);
			return result;
		} // public int  GameRevealPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64[] InRevealedPlayerID, System.Byte[] InRevealedRole, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Player. revive himself
		public int  GamePlayerReviveRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayerReviveRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayerReviveRes);
			return result;
		} // public int  GamePlayerReviveRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Player is revived
		public int  GamePlayerRevivedS2CEvt( System.UInt64 InRevivedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayerRevivedS2CEvt(m_Connection.NativeHandle, InRevivedPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayerRevivedS2CEvt);
			return result;
		} // public int  GamePlayerRevivedS2CEvt( System.UInt64 InRevivedPlayerID )


		// Cmd: Player. reset ranking
		public int  GamePlayerResetRankRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGamePlayerResetRankRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GamePlayerResetRankRes);
			return result;
		} // public int  GamePlayerResetRankRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Request Game match
		public int  RequestGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestGameMatchRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestGameMatchRes);
			return result;
		} // public int  RequestGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game matched
		public int  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchedS2CEvt(m_Connection.NativeHandle, InInsUID, InTimeStamp,(int) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,(ushort)InChatHistoryData.Length, InChatHistoryData,(ushort)InGameLogData.Length, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchedS2CEvt);
			return result;
		} // public int  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game match failed
		public int  GameMatchFailedS2CEvt( System.Int32 InFailedReason )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchFailedS2CEvt(m_Connection.NativeHandle, InFailedReason);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchFailedS2CEvt);
			return result;
		} // public int  GameMatchFailedS2CEvt( System.Int32 InFailedReason )


		// S2C: Game matching started
		public int  GameMatchingStartedS2CEvt(  )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchingStartedS2CEvt(m_Connection.NativeHandle);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchingStartedS2CEvt);
			return result;
		} // public int  GameMatchingStartedS2CEvt(  )


		// Cmd: Cancel Game match
		public int  CancelGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCancelGameMatchRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CancelGameMatchRes);
			return result;
		} // public int  CancelGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: game matching canceled
		public int  GameMatchingCanceledS2CEvt(  )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchingCanceledS2CEvt(m_Connection.NativeHandle);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchingCanceledS2CEvt);
			return result;
		} // public int  GameMatchingCanceledS2CEvt(  )


		// Cmd: Buy shop item prepare
		public int  BuyShopItemPrepareRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemPrepareRes(m_Connection.NativeHandle, InTransactionID, InResult, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPurchaseID + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemPrepareRes);
			return result;
		} // public int  BuyShopItemPrepareRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )


		// Cmd: Buy shop item
		public int  BuyShopItemRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemRes(m_Connection.NativeHandle, InTransactionID, InResult, InShopItemID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemRes);
			return result;
		} // public int  BuyShopItemRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )


		// Cmd: Create or Join Chat channel
		public int  CreateOrJoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreateOrJoinChatChannelRes(m_Connection.NativeHandle, InTransactionID, InResult, InChatUID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateOrJoinChatChannelRes);
			return result;
		} // public int  CreateOrJoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID )


		// Cmd: Join
		public int  JoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinChatChannelRes(m_Connection.NativeHandle, InTransactionID, InResult, InPartyUID, InPartyLeaderID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinChatChannelRes);
			return result;
		} // public int  JoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID )


		// S2C: Player Joined event
		public int  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt(m_Connection.NativeHandle, InChatUID,ref InJoinedPlayer);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelPlayerJoinedS2CEvt);
			return result;
		} // public int  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: ChatChannel leader changed event
		public int  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt(m_Connection.NativeHandle, InChatUID, InNewLeaderID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelLeaderChangedS2CEvt);
			return result;
		} // public int  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave ChatChannel command
		public int  LeaveChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveChatChannelRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveChatChannelRes);
			return result;
		} // public int  LeaveChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player left event
		public int  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt(m_Connection.NativeHandle, InChatUID, InLeftPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelPlayerLeftS2CEvt);
			return result;
		} // public int  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the ChatChannel
		public int  ChatChannelKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelKickPlayerRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelKickPlayerRes);
			return result;
		} // public int  ChatChannelKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player kicked message
		public int  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt(m_Connection.NativeHandle, InChatUID, InKickedPlayerID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelPlayerKickedS2CEvt);
			return result;
		} // public int  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )


		// Cmd: Party chatting
		public int  ChatChannelChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelChatMessageRes);
			return result;
		} // public int  ChatChannelChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Chatting message event
		public int  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,System.Text.Encoding.UTF8.GetBytes(InSenderName + "\0"),System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelChatMessageS2CEvt);
			return result;
		} // public int  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )


		// Cmd: Create character
		public int  CreateCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult, System.Int32 InCharacterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreateCharacterRes(m_Connection.NativeHandle, InTransactionID, InResult, InCharacterID);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateCharacterRes);
			return result;
		} // public int  CreateCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult, System.Int32 InCharacterID )


		// Cmd: Remove character
		public int  RemoveCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRemoveCharacterRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RemoveCharacterRes);
			return result;
		} // public int  RemoveCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Get character list
		public int  GetCharacterListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.Int32[] InCharacterIDs )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterListRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InCharacterIDs.Length, InCharacterIDs);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterListRes);
			return result;
		} // public int  GetCharacterListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.Int32[] InCharacterIDs )


		// Cmd: 
		public int  GetCharacterDataRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameGetCharacterDataRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataRes);
			return result;
		} // public int  GetCharacterDataRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )


		// Cmd: Give my stamina to other player
		public int  GiveStaminaRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTargetPlayer, System.UInt64 InTimeStamp )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGiveStaminaRes(m_Connection.NativeHandle, InTransactionID, InResult, InTargetPlayer, InTimeStamp);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GiveStaminaRes);
			return result;
		} // public int  GiveStaminaRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTargetPlayer, System.UInt64 InTimeStamp )


		// Cmd: For debug, Change configue preset
		public int  SetPresetGameConfigIDRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetPresetGameConfigIDRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetPresetGameConfigIDRes);
			return result;
		} // public int  SetPresetGameConfigIDRes( System.UInt64 InTransactionID, System.Int32 InResult )


		#region Native Interfaces 
		// Cmd: Player connected from a login server and moved to game server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameServerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameServerRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, ref SF.MatchingQueueTicket InMatchingTicket );



		// Cmd: player complition statues
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetComplitionStateRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetComplitionStateRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, [MarshalAs(UnmanagedType.LPArray)] byte[] InComplitionState );



		// Cmd: Player complition state
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetComplitionStateRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetComplitionStateRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRegisterGCMRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRegisterGCMRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Unregister Google notification service ID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameUnregisterGCMRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameUnregisterGCMRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Invite friend
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameInviteFriendRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameInviteFriendRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Accept friend request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptFriendRequestRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptFriendRequestRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.FriendInformation InNewFriend );



		// S2C: Notification for friend request is accepted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(System.IntPtr InNativeConnectionHandle, ref SF.FriendInformation InAccepter );



		// Cmd: Remove friden form the friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveFriendRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveFriendRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InFriendID );



		// S2C: Friend removed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFriendRemovedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFriendRemovedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InFriendID );



		// Cmd: Get friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetFriendListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetFriendListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, System.UInt16 _sizeOfInFriendList,SF.FriendInformation[] InFriendList );



		// Cmd: Query notification list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetNotificationListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetNotificationListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Delete notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteNotificationRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteNotificationRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID );



		// Cmd: Set notification is read
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNotificationReadRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNotificationReadRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID );



		// Cmd: Accept notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAcceptNotificationRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAcceptNotificationRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID );



		// S2C: Notify new notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameNotifyS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameNotifyS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt32 InNotificationID, System.UInt32 InNotificationType, System.UInt64 InMessageParam0, System.UInt64 InMessageParam1, [MarshalAs(UnmanagedType.LPArray)] byte[] InMessageText, System.Byte InIsRead, System.UInt64 InTimeStamp );



		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByEMailRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByEMailRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.PlayerInformation InPlayer );



		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameFindPlayerByPlayerIDRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameFindPlayerByPlayerIDRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.PlayerInformation InPlayer );



		// Cmd: *Request Player Status Update
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestPlayerStatusUpdateRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestPlayerStatusUpdateRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: *Notify Player Status Updated
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame );



		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetRankingListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetRankingListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRanking,SF.TotalRankingPlayerInformation[] InRanking );



		// Cmd: Game user game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetUserGamePlayerInfoRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetUserGamePlayerInfoRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: Game game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetGamePlayerInfoRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetGamePlayerInfoRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// S2C: Player level up event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLevelUpS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLevelUpS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel );



		// Cmd: Change NickName
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetNickNameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetNickNameRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// Cmd: Create Party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreatePartyRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreatePartyRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID );



		// Cmd: Join party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinPartyRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinPartyRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.UInt16 _sizeOfInChatHistoryData,System.Byte[] InChatHistoryData );



		// S2C: Player Joined event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, ref SF.PlayerInformation InJoinedPlayer );



		// S2C: Party leader changed event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyLeaderChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyLeaderChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InNewLeaderID );



		// Cmd: Leave party command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeavePartyRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeavePartyRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Party Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyPlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyPlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID );



		// Cmd: Kick player from the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyKickPlayerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyKickPlayerRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Party Player kicked message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyPlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyPlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID );



		// Cmd: Invite a player to the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyInviteRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyInviteRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Party invite requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyInviteRequestedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyInviteRequestedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InInviterID, [MarshalAs(UnmanagedType.LPArray)] byte[] InInviterName, System.UInt64 InPartyToJoinUID );



		// Cmd: Send Party quick chat message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyQuickChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyQuickChatMessageRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Party Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.UInt32 InQuickChatID );



		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyChatMessageRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Party Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePartyChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePartyChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSenderName, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Join to a game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, ref SF.NetAddress InServerAddress, ref SF.NetAddress InServerAddress4 );



		// Cmd: Leave game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInGameInstances,SF.GameInstanceInfo[] InGameInstances );



		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, System.UInt16 _sizeOfInGameInstances,IntPtr InGameInstances );



		// Cmd: Join to a game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinGameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinGameRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, System.UInt32 InTimeStamp, int InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.UInt16 _sizeOfInChatHistoryData,System.Byte[] InChatHistoryData, System.UInt16 _sizeOfInGameLogData,System.Byte[] InGameLogData );



		// S2C: Player Joined in the game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePlayerJoinedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePlayerJoinedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, ref SF.PlayerInformation InJoinedPlayer );



		// Cmd: Leave Game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InLeftPlayerID );



		// Cmd: Kick player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameKickPlayerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameKickPlayerRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Player kicked
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InKickedPlayerID );



		// Cmd: Assign role + Game state reset
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAssignRoleRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAssignRoleRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Role assigned event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRoleAssignedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRoleAssignedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InPlayerID, System.Byte InRole );



		// Cmd: Send chatting message to the game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatMessageRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Chatting message event 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.Byte InRole, [MarshalAs(UnmanagedType.LPArray)] byte[] InSenderName, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Advance game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameAdvanceGameRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameAdvanceGameRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: The game state is advanced
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameAdvancedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameAdvancedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt32 InTimeStamp, int InGameState, System.Byte InDay );



		// S2C: Game is ended
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameEndedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameEndedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, int InWinner, System.UInt32 InGainedExp, System.UInt32 InGainedGameMoney );



		// Cmd: Vote game advance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameVoteGameAdvanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameVoteGameAdvanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: GameAdvance is Voted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameAdvanceVotedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameAdvanceVotedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InVoter );



		// Cmd: Vote
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameVoteRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameVoteRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Player Voted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameVotedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameVotedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InVoter, System.UInt64 InVotedTarget );



		// S2C: Vote is ended
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameVoteEndS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameVoteEndS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt16 _sizeOfInVoted,System.UInt64[] InVoted );



		// S2C: Player Killed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePlayerKilledS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePlayerKilledS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InKilledPlayer, int InReason );



		// S2C: Player Voted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GamePlayerRevealedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GamePlayerRevealedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InGameInsUID, System.UInt64 InRevealedPlayerID, System.Byte InRole, int InReason );



		// Cmd: Play again with the current players
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayAgainRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayAgainRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayAgainS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayAgainS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPartyUID, System.UInt64 InLeadPlayer );



		// Cmd: Player. reveal a player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameRevealPlayerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameRevealPlayerRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInRevealedPlayerID,System.UInt64[] InRevealedPlayerID, System.UInt16 _sizeOfInRevealedRole,System.Byte[] InRevealedRole, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// Cmd: Player. revive himself
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayerReviveRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayerReviveRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// S2C: Player is revived
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayerRevivedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayerRevivedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InRevivedPlayerID );



		// Cmd: Player. reset ranking
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGamePlayerResetRankRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGamePlayerResetRankRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



		// Cmd: Request Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRequestGameMatchRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRequestGameMatchRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney );



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
		static extern int CSSFNetAdapter_GameCancelGameMatchRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: game matching canceled
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGameMatchingCanceledS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGameMatchingCanceledS2CEvt(System.IntPtr InNativeConnectionHandle );



		// Cmd: Buy shop item prepare
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemPrepareRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemPrepareRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPurchaseID );



		// Cmd: Buy shop item
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameBuyShopItemRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameBuyShopItemRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID );



		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateOrJoinChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateOrJoinChatChannelRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID );



		// Cmd: Join
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinChatChannelRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID );



		// S2C: Player Joined event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, ref SF.PlayerInformation InJoinedPlayer );



		// S2C: ChatChannel leader changed event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, System.UInt64 InNewLeaderID );



		// Cmd: Leave ChatChannel command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveChatChannelRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, System.UInt64 InLeftPlayerID );



		// Cmd: Kick player from the ChatChannel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelKickPlayerRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelKickPlayerRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Player kicked message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InChatUID, System.UInt64 InKickedPlayerID );



		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSenderName, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Create character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateCharacterRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.Int32 InCharacterID );



		// Cmd: Remove character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameRemoveCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameRemoveCharacterRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Get character list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInCharacterIDs,System.Int32[] InCharacterIDs );



		// Cmd: 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: Give my stamina to other player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGiveStaminaRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGiveStaminaRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTargetPlayer, System.UInt64 InTimeStamp );



		// Cmd: For debug, Change configue preset
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSetPresetGameConfigIDRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSetPresetGameConfigIDRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrGame




} // namespace SF.Net


