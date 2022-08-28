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
 			int result;
			{
			result = CSSFNetAdapter_GameHeartbeatC2SEvt(m_Connection.NativeHandle);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.HeartbeatC2SEvt);
			return result;
		} // public int  HeartbeatC2SEvt(  )


		// Cmd: Player connected from a login server and moved to game server
		public int  JoinGameServerCmd( System.UInt64 InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameServerCmd(m_Connection.NativeHandle, InTransactionID, InAccID, InTicket, InLoginEntityUID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameServerCmd);
			return result;
		} // public int  JoinGameServerCmd( System.UInt64 InTransactionID, System.UInt64 InAccID, System.UInt64 InTicket, System.UInt64 InLoginEntityUID )

		// Cmd: player complition statues
		public int  GetComplitionStateCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetComplitionStateCmd(m_Connection.NativeHandle, InTransactionID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetComplitionStateCmd);
			return result;
		} // public int  GetComplitionStateCmd( System.UInt64 InTransactionID )

		// Cmd: Player complition state
		public int  SetComplitionStateCmd( System.UInt64 InTransactionID, System.String InComplitionState )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetComplitionStateCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InComplitionState + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetComplitionStateCmd);
			return result;
		} // public int  SetComplitionStateCmd( System.UInt64 InTransactionID, System.String InComplitionState )

		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public int  RegisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRegisterGCMCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RegisterGCMCmd);
			return result;
		} // public int  RegisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )

		// Cmd: Unregister Google notification service ID
		public int  UnregisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameUnregisterGCMCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InGCMRegisteredID + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.UnregisterGCMCmd);
			return result;
		} // public int  UnregisterGCMCmd( System.UInt64 InTransactionID, System.String InGCMRegisteredID )

		// Cmd: Invite friend
		public int  InviteFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameInviteFriendCmd(m_Connection.NativeHandle, InTransactionID, InFriendID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.InviteFriendCmd);
			return result;
		} // public int  InviteFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )

		// Cmd: Accept friend request
		public int  AcceptFriendRequestCmd( System.UInt64 InTransactionID, System.UInt64 InInviterID, System.UInt64 InInviterFacebookUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptFriendRequestCmd(m_Connection.NativeHandle, InTransactionID, InInviterID, InInviterFacebookUID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptFriendRequestCmd);
			return result;
		} // public int  AcceptFriendRequestCmd( System.UInt64 InTransactionID, System.UInt64 InInviterID, System.UInt64 InInviterFacebookUID )

		// Cmd: Remove friden form the friend list
		public int  RemoveFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRemoveFriendCmd(m_Connection.NativeHandle, InTransactionID, InFriendID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RemoveFriendCmd);
			return result;
		} // public int  RemoveFriendCmd( System.UInt64 InTransactionID, System.UInt64 InFriendID )

		// Cmd: Get friend list
		public int  GetFriendListCmd( System.UInt64 InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetFriendListCmd(m_Connection.NativeHandle, InTransactionID, InStartIndex, InCount);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetFriendListCmd);
			return result;
		} // public int  GetFriendListCmd( System.UInt64 InTransactionID, System.UInt16 InStartIndex, System.UInt16 InCount )

		// Cmd: Query notification list
		public int  GetNotificationListCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetNotificationListCmd(m_Connection.NativeHandle, InTransactionID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetNotificationListCmd);
			return result;
		} // public int  GetNotificationListCmd( System.UInt64 InTransactionID )

		// Cmd: Delete notification
		public int  DeleteNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameDeleteNotificationCmd(m_Connection.NativeHandle, InTransactionID, InNotificationID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.DeleteNotificationCmd);
			return result;
		} // public int  DeleteNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )

		// Cmd: Set notification is read
		public int  SetNotificationReadCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNotificationReadCmd(m_Connection.NativeHandle, InTransactionID, InNotificationID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNotificationReadCmd);
			return result;
		} // public int  SetNotificationReadCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )

		// Cmd: Accept notification
		public int  AcceptNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptNotificationCmd(m_Connection.NativeHandle, InTransactionID, InNotificationID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptNotificationCmd);
			return result;
		} // public int  AcceptNotificationCmd( System.UInt64 InTransactionID, System.UInt32 InNotificationID )

		// Cmd: Query playerID list
		public int  FindPlayerByEMailCmd( System.UInt64 InTransactionID, System.String InPlayerEMail )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByEMailCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InPlayerEMail + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByEMailCmd);
			return result;
		} // public int  FindPlayerByEMailCmd( System.UInt64 InTransactionID, System.String InPlayerEMail )

		// Cmd: Query playerID list
		public int  FindPlayerByPlayerIDCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlayerIDCmd(m_Connection.NativeHandle, InTransactionID, InPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByPlayerIDCmd);
			return result;
		} // public int  FindPlayerByPlayerIDCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )

		// Cmd: *Request Player Status Update
		public int  RequestPlayerStatusUpdateCmd( System.UInt64 InTransactionID, System.UInt64[] InTargetPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd(m_Connection.NativeHandle, InTransactionID,(ushort)InTargetPlayerID.Length, InTargetPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestPlayerStatusUpdateCmd);
			return result;
		} // public int  RequestPlayerStatusUpdateCmd( System.UInt64 InTransactionID, System.UInt64[] InTargetPlayerID )

		// Cmd: Get Ranking list
		public int  GetRankingListCmd( System.UInt64 InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetRankingListCmd(m_Connection.NativeHandle, InTransactionID, InRankingType, InBaseRanking, InCount);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetRankingListCmd);
			return result;
		} // public int  GetRankingListCmd( System.UInt64 InTransactionID, System.Byte InRankingType, System.Byte InBaseRanking, System.Byte InCount )

		// Cmd: Game user game play information
		public int  GetUserGamePlayerInfoCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetUserGamePlayerInfoCmd(m_Connection.NativeHandle, InTransactionID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetUserGamePlayerInfoCmd);
			return result;
		} // public int  GetUserGamePlayerInfoCmd( System.UInt64 InTransactionID )

		// Cmd: Game game play information
		public int  GetGamePlayerInfoCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetGamePlayerInfoCmd(m_Connection.NativeHandle, InTransactionID, InPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetGamePlayerInfoCmd);
			return result;
		} // public int  GetGamePlayerInfoCmd( System.UInt64 InTransactionID, System.UInt64 InPlayerID )

		// Cmd: Change NickName
		public int  SetNickNameCmd( System.UInt64 InTransactionID, System.String InNickName, System.Byte InIsCostFree )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNickNameCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InIsCostFree);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNickNameCmd);
			return result;
		} // public int  SetNickNameCmd( System.UInt64 InTransactionID, System.String InNickName, System.Byte InIsCostFree )

		// Cmd: Create Party
		public int  CreatePartyCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreatePartyCmd(m_Connection.NativeHandle, InTransactionID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreatePartyCmd);
			return result;
		} // public int  CreatePartyCmd( System.UInt64 InTransactionID )

		// Cmd: Join party
		public int  JoinPartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinPartyCmd(m_Connection.NativeHandle, InTransactionID, InPartyUID, InInviterID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinPartyCmd);
			return result;
		} // public int  JoinPartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InInviterID )

		// Cmd: Leave party command
		public int  LeavePartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeavePartyCmd(m_Connection.NativeHandle, InTransactionID, InPartyUID, InPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeavePartyCmd);
			return result;
		} // public int  LeavePartyCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID )

		// Cmd: Kick player from the party
		public int  PartyKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyKickPlayerCmd(m_Connection.NativeHandle, InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyKickPlayerCmd);
			return result;
		} // public int  PartyKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InPartyUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )

		// Cmd: Invite a player to the party
		public int  PartyInviteCmd( System.UInt64 InTransactionID, System.UInt64 InInviteTargetID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteCmd(m_Connection.NativeHandle, InTransactionID, InInviteTargetID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyInviteCmd);
			return result;
		} // public int  PartyInviteCmd( System.UInt64 InTransactionID, System.UInt64 InInviteTargetID )

		// Cmd: Send Party quick chat message
		public int  PartyQuickChatMessageCmd( System.UInt64 InTransactionID, System.UInt32 InQuickChatID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageCmd(m_Connection.NativeHandle, InTransactionID, InQuickChatID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyQuickChatMessageCmd);
			return result;
		} // public int  PartyQuickChatMessageCmd( System.UInt64 InTransactionID, System.UInt32 InQuickChatID )

		// Cmd: Party chatting
		public int  PartyChatMessageCmd( System.UInt64 InTransactionID, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyChatMessageCmd);
			return result;
		} // public int  PartyChatMessageCmd( System.UInt64 InTransactionID, System.String InChatMessage )

		// Cmd: Join to a game instance
		public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InInsUID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameInstanceCmd);
			return result;
		} // public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )

		// Cmd: Leave game instance
		public int  LeaveGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InInsUID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveGameInstanceCmd);
			return result;
		} // public int  LeaveGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InInsUID )

		// Cmd: Search game instance
		public int  SearchGameInstanceCmd( System.UInt64 InTransactionID, System.String InSearchKeyword, System.UInt32 InZoneTableID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSearchGameInstanceCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InSearchKeyword + "\0"), InZoneTableID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SearchGameInstanceCmd);
			return result;
		} // public int  SearchGameInstanceCmd( System.UInt64 InTransactionID, System.String InSearchKeyword, System.UInt32 InZoneTableID )

		// Cmd: Search game instance
		public int  GetCharacterDataInGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InGameInsUID, InPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataInGameInstanceCmd);
			return result;
		} // public int  GetCharacterDataInGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID )

		// Cmd: Request Game match
		public int  RequestGameMatchCmd( System.UInt64 InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestGameMatchCmd(m_Connection.NativeHandle, InTransactionID, InNumPlayer, InRequestRole);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestGameMatchCmd);
			return result;
		} // public int  RequestGameMatchCmd( System.UInt64 InTransactionID, System.Byte InNumPlayer, System.Byte InRequestRole )

		// Cmd: Cancel Game match
		public int  CancelGameMatchCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCancelGameMatchCmd(m_Connection.NativeHandle, InTransactionID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CancelGameMatchCmd);
			return result;
		} // public int  CancelGameMatchCmd( System.UInt64 InTransactionID )

		// Cmd: Buy shop item prepare
		public int  BuyShopItemPrepareCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemPrepareCmd(m_Connection.NativeHandle, InTransactionID, InShopItemID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemPrepareCmd);
			return result;
		} // public int  BuyShopItemPrepareCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID )

		// Cmd: Buy shop item
		public int  BuyShopItemCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemCmd(m_Connection.NativeHandle, InTransactionID, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPlatform + "\0"),System.Text.Encoding.UTF8.GetBytes(InPackageName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPurchaseTransactionID + "\0"),(ushort)InPurchaseToken.Length, InPurchaseToken);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemCmd);
			return result;
		} // public int  BuyShopItemCmd( System.UInt64 InTransactionID, System.UInt32 InShopItemID, System.String InPlatform, System.String InPackageName, System.String InPurchaseTransactionID, System.Byte[] InPurchaseToken )

		// Cmd: Create or Join Chat channel
		public int  CreateOrJoinChatChannelCmd( System.UInt64 InTransactionID, System.String InChannelName, System.String InPasscode )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreateOrJoinChatChannelCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InChannelName + "\0"),System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateOrJoinChatChannelCmd);
			return result;
		} // public int  CreateOrJoinChatChannelCmd( System.UInt64 InTransactionID, System.String InChannelName, System.String InPasscode )

		// Cmd: Join
		public int  JoinChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinChatChannelCmd(m_Connection.NativeHandle, InTransactionID, InChatUID, InInviterID,System.Text.Encoding.UTF8.GetBytes(InPasscode + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinChatChannelCmd);
			return result;
		} // public int  JoinChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, System.String InPasscode )

		// Cmd: Leave ChatChannel command
		public int  LeaveChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveChatChannelCmd(m_Connection.NativeHandle, InTransactionID, InChatUID, InPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveChatChannelCmd);
			return result;
		} // public int  LeaveChatChannelCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID )

		// Cmd: Kick player from the ChatChannel
		public int  ChatChannelKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelKickPlayerCmd(m_Connection.NativeHandle, InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelKickPlayerCmd);
			return result;
		} // public int  ChatChannelKickPlayerCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick )

		// Cmd: Chat channel sending chatting message
		public int  ChatChannelChatMessageCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageCmd(m_Connection.NativeHandle, InTransactionID, InChatUID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelChatMessageCmd);
			return result;
		} // public int  ChatChannelChatMessageCmd( System.UInt64 InTransactionID, System.UInt64 InChatUID, SF.VariableTable InChatMetaData, System.String InChatMessage )

		// Cmd: Whisper(tell) other player chatting
		public int  WhisperMessageCmd( System.UInt64 InTransactionID, System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameWhisperMessageCmd(m_Connection.NativeHandle, InTransactionID, InReceiverID,System.Text.Encoding.UTF8.GetBytes(InReceiverName + "\0"),(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.WhisperMessageCmd);
			return result;
		} // public int  WhisperMessageCmd( System.UInt64 InTransactionID, System.UInt64 InReceiverID, System.String InReceiverName, SF.VariableTable InChatMetaData, System.String InChatMessage )

		// Cmd: Create character
		public int  CreateCharacterCmd( System.UInt64 InTransactionID, System.String InCharacterName, SF.VariableTable InVisualData, SF.VariableTable InAttributes )
		{
 			int result;
			var InVisualData_ = InVisualData.ToByteArray();
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InVisualData_PinnedPtr_ = new PinnedByteBuffer(InVisualData_))
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameCreateCharacterCmd(m_Connection.NativeHandle, InTransactionID,System.Text.Encoding.UTF8.GetBytes(InCharacterName + "\0"),(ushort)InVisualData_.Length, InVisualData_PinnedPtr_.Ptr,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateCharacterCmd);
			return result;
		} // public int  CreateCharacterCmd( System.UInt64 InTransactionID, System.String InCharacterName, SF.VariableTable InVisualData, SF.VariableTable InAttributes )

		// Cmd: Delete character
		public int  DeleteCharacterCmd( System.UInt64 InTransactionID, System.UInt32 InCharacterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameDeleteCharacterCmd(m_Connection.NativeHandle, InTransactionID, InCharacterID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.DeleteCharacterCmd);
			return result;
		} // public int  DeleteCharacterCmd( System.UInt64 InTransactionID, System.UInt32 InCharacterID )

		// Cmd: Get character list
		public int  GetCharacterListCmd( System.UInt64 InTransactionID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterListCmd(m_Connection.NativeHandle, InTransactionID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterListCmd);
			return result;
		} // public int  GetCharacterListCmd( System.UInt64 InTransactionID )

		// Cmd: 
		public int  GetCharacterDataCmd( System.UInt64 InTransactionID, System.UInt32 InCharacterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterDataCmd(m_Connection.NativeHandle, InTransactionID, InCharacterID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataCmd);
			return result;
		} // public int  GetCharacterDataCmd( System.UInt64 InTransactionID, System.UInt32 InCharacterID )

		// Cmd: Select character
		public int  SelectCharacterCmd( System.UInt64 InTransactionID, System.UInt32 InCharacterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSelectCharacterCmd(m_Connection.NativeHandle, InTransactionID, InCharacterID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SelectCharacterCmd);
			return result;
		} // public int  SelectCharacterCmd( System.UInt64 InTransactionID, System.UInt32 InCharacterID )

		// Cmd: To call general functionality
		public int  CallFunctionCmd( System.UInt64 InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters )
		{
 			int result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = CSSFNetAdapter_GameCallFunctionCmd(m_Connection.NativeHandle, InTransactionID, InFunctionName,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CallFunctionCmd);
			return result;
		} // public int  CallFunctionCmd( System.UInt64 InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters )

		#region Native Interfaces 
		// C2S: Client heartbeat
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameHeartbeatC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameHeartbeatC2SEvt(System.IntPtr InNativeConnectionHandle );



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


		// Cmd: Get Ranking list
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
		static extern int CSSFNetAdapter_GameSearchGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InSearchKeyword, System.UInt32 InZoneTableID );


		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InGameInsUID, System.UInt64 InPlayerID );


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
		static extern int CSSFNetAdapter_GameJoinChatChannelCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InInviterID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPasscode );


		// Cmd: Leave ChatChannel command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveChatChannelCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveChatChannelCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID );


		// Cmd: Kick player from the ChatChannel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelKickPlayerCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelKickPlayerCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt64 InPlayerID, System.UInt64 InPlayerToKick );


		// Cmd: Chat channel sending chatting message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InChatUID, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Whisper(tell) other player chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameWhisperMessageCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameWhisperMessageCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InReceiverID, [MarshalAs(UnmanagedType.LPArray)] byte[] InReceiverName, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );


		// Cmd: Create character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateCharacterCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, [MarshalAs(UnmanagedType.LPArray)] byte[] InCharacterName, System.UInt16 _sizeOfInVisualData,IntPtr InVisualData, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );


		// Cmd: Delete character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteCharacterCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InCharacterID );


		// Cmd: Get character list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID );


		// Cmd: 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InCharacterID );


		// Cmd: Select character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSelectCharacterCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSelectCharacterCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InCharacterID );


		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCallFunctionCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCallFunctionCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InFunctionName, System.UInt16 _sizeOfInParameters,IntPtr InParameters );


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
		public int  JoinGameServerRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameServerRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InNickName + "\0"), InGameUID, InPartyUID, InPartyLeaderID,ref InMatchingTicket);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameServerRes);
			return result;
		} // public int  JoinGameServerRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InNickName, System.UInt64 InGameUID, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, SF.MatchingQueueTicket InMatchingTicket )


		// Cmd: player complition statues
		public int  GetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InComplitionState )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetComplitionStateRes(m_Connection.NativeHandle, InTransactionID, InResult,System.Text.Encoding.UTF8.GetBytes(InComplitionState + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetComplitionStateRes);
			return result;
		} // public int  GetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String InComplitionState )


		// Cmd: Player complition state
		public int  SetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetComplitionStateRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetComplitionStateRes);
			return result;
		} // public int  SetComplitionStateRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public int  RegisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRegisterGCMRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RegisterGCMRes);
			return result;
		} // public int  RegisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Unregister Google notification service ID
		public int  UnregisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameUnregisterGCMRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.UnregisterGCMRes);
			return result;
		} // public int  UnregisterGCMRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Invite friend
		public int  InviteFriendRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameInviteFriendRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.InviteFriendRes);
			return result;
		} // public int  InviteFriendRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Accept friend request
		public int  AcceptFriendRequestRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.FriendInformation InNewFriend )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptFriendRequestRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InNewFriend);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptFriendRequestRes);
			return result;
		} // public int  AcceptFriendRequestRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.FriendInformation InNewFriend )


		// S2C: Notification for friend request is accepted
		public int  FriendRequestAcceptedS2CEvt( SF.FriendInformation InAccepter )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt(m_Connection.NativeHandle,ref InAccepter);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FriendRequestAcceptedS2CEvt);
			return result;
		} // public int  FriendRequestAcceptedS2CEvt( SF.FriendInformation InAccepter )


		// Cmd: Remove friden form the friend list
		public int  RemoveFriendRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRemoveFriendRes(m_Connection.NativeHandle, InTransactionID, InResult, InFriendID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RemoveFriendRes);
			return result;
		} // public int  RemoveFriendRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InFriendID )


		// S2C: Friend removed
		public int  FriendRemovedS2CEvt( System.UInt64 InFriendID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFriendRemovedS2CEvt(m_Connection.NativeHandle, InFriendID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FriendRemovedS2CEvt);
			return result;
		} // public int  FriendRemovedS2CEvt( System.UInt64 InFriendID )


		// Cmd: Get friend list
		public int  GetFriendListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.FriendInformation[] InFriendList )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetFriendListRes(m_Connection.NativeHandle, InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,(ushort)InFriendList.Length, InFriendList);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetFriendListRes);
			return result;
		} // public int  GetFriendListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 InMaxFriendSlot, System.UInt16 InTotalNumberOfFriends, System.UInt16 InStartIndex, SF.FriendInformation[] InFriendList )


		// Cmd: Query notification list
		public int  GetNotificationListRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetNotificationListRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetNotificationListRes);
			return result;
		} // public int  GetNotificationListRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Delete notification
		public int  DeleteNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameDeleteNotificationRes(m_Connection.NativeHandle, InTransactionID, InResult, InNotificationID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.DeleteNotificationRes);
			return result;
		} // public int  DeleteNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Set notification is read
		public int  SetNotificationReadRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNotificationReadRes(m_Connection.NativeHandle, InTransactionID, InResult, InNotificationID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNotificationReadRes);
			return result;
		} // public int  SetNotificationReadRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// Cmd: Accept notification
		public int  AcceptNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameAcceptNotificationRes(m_Connection.NativeHandle, InTransactionID, InResult, InNotificationID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.AcceptNotificationRes);
			return result;
		} // public int  AcceptNotificationRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InNotificationID )


		// S2C: Notify new notification
		public int  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, System.UInt64 InMessageParam0, System.UInt64 InMessageParam1, System.String InMessageText, System.Byte InIsRead, System.UInt64 InTimeStamp )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameNotifyS2CEvt(m_Connection.NativeHandle, InNotificationID, InNotificationType, InMessageParam0, InMessageParam1,System.Text.Encoding.UTF8.GetBytes(InMessageText + "\0"), InIsRead, InTimeStamp);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.NotifyS2CEvt);
			return result;
		} // public int  NotifyS2CEvt( System.UInt32 InNotificationID, System.UInt32 InNotificationType, System.UInt64 InMessageParam0, System.UInt64 InMessageParam1, System.String InMessageText, System.Byte InIsRead, System.UInt64 InTimeStamp )


		// Cmd: Query playerID list
		public int  FindPlayerByEMailRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByEMailRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InPlayer);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByEMailRes);
			return result;
		} // public int  FindPlayerByEMailRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: Query playerID list
		public int  FindPlayerByPlayerIDRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameFindPlayerByPlayerIDRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InPlayer);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.FindPlayerByPlayerIDRes);
			return result;
		} // public int  FindPlayerByPlayerIDRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.PlayerInformation InPlayer )


		// Cmd: *Request Player Status Update
		public int  RequestPlayerStatusUpdateRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestPlayerStatusUpdateRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestPlayerStatusUpdateRes);
			return result;
		} // public int  RequestPlayerStatusUpdateRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: *Notify Player Status Updated
		public int  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt(m_Connection.NativeHandle, InPlayerID, InLatestActiveTime, InIsInGame);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.NotifyPlayerStatusUpdatedS2CEvt);
			return result;
		} // public int  NotifyPlayerStatusUpdatedS2CEvt( System.UInt64 InPlayerID, System.UInt32 InLatestActiveTime, System.Byte InIsInGame )


		// Cmd: Get Ranking list
		public int  GetRankingListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.TotalRankingPlayerInformation[] InRanking )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetRankingListRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InRanking.Length, InRanking);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetRankingListRes);
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
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetUserGamePlayerInfoRes);
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
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetGamePlayerInfoRes);
			return result;
		} // public int  GetGamePlayerInfoRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InAttributes )


		// S2C: Player level up event
		public int  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLevelUpS2CEvt(m_Connection.NativeHandle, InCurrentTotalExp, InCurrentLevel);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LevelUpS2CEvt);
			return result;
		} // public int  LevelUpS2CEvt( System.UInt64 InCurrentTotalExp, System.UInt32 InCurrentLevel )


		// Cmd: Change NickName
		public int  SetNickNameRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSetNickNameRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SetNickNameRes);
			return result;
		} // public int  SetNickNameRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// Cmd: Create Party
		public int  CreatePartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreatePartyRes(m_Connection.NativeHandle, InTransactionID, InResult, InPartyUID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreatePartyRes);
			return result;
		} // public int  CreatePartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID )


		// Cmd: Join party
		public int  JoinPartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinPartyRes(m_Connection.NativeHandle, InTransactionID, InResult, InPartyUID, InPartyLeaderID,(ushort)InChatHistoryData.Length, InChatHistoryData);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinPartyRes);
			return result;
		} // public int  JoinPartyRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPartyUID, System.UInt64 InPartyLeaderID, System.Byte[] InChatHistoryData )


		// S2C: Player Joined event
		public int  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt(m_Connection.NativeHandle, InPartyUID,ref InJoinedPlayer);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyPlayerJoinedS2CEvt);
			return result;
		} // public int  PartyPlayerJoinedS2CEvt( System.UInt64 InPartyUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: Party leader changed event
		public int  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyLeaderChangedS2CEvt(m_Connection.NativeHandle, InPartyUID, InNewLeaderID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyLeaderChangedS2CEvt);
			return result;
		} // public int  PartyLeaderChangedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave party command
		public int  LeavePartyRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeavePartyRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeavePartyRes);
			return result;
		} // public int  LeavePartyRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Player left event
		public int  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerLeftS2CEvt(m_Connection.NativeHandle, InPartyUID, InLeftPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyPlayerLeftS2CEvt);
			return result;
		} // public int  PartyPlayerLeftS2CEvt( System.UInt64 InPartyUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the party
		public int  PartyKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyKickPlayerRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyKickPlayerRes);
			return result;
		} // public int  PartyKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Player kicked message
		public int  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyPlayerKickedS2CEvt(m_Connection.NativeHandle, InPartyUID, InKickedPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyPlayerKickedS2CEvt);
			return result;
		} // public int  PartyPlayerKickedS2CEvt( System.UInt64 InPartyUID, System.UInt64 InKickedPlayerID )


		// Cmd: Invite a player to the party
		public int  PartyInviteRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyInviteRes);
			return result;
		} // public int  PartyInviteRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party invite requested
		public int  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyInviteRequestedS2CEvt(m_Connection.NativeHandle, InInviterID,System.Text.Encoding.UTF8.GetBytes(InInviterName + "\0"), InPartyToJoinUID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyInviteRequestedS2CEvt);
			return result;
		} // public int  PartyInviteRequestedS2CEvt( System.UInt64 InInviterID, System.String InInviterName, System.UInt64 InPartyToJoinUID )


		// Cmd: Send Party quick chat message
		public int  PartyQuickChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyQuickChatMessageRes);
			return result;
		} // public int  PartyQuickChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public int  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID, InQuickChatID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyQuickChatMessageS2CEvt);
			return result;
		} // public int  PartyQuickChatMessageS2CEvt( System.UInt64 InSenderID, System.UInt32 InQuickChatID )


		// Cmd: Party chatting
		public int  PartyChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyChatMessageRes);
			return result;
		} // public int  PartyChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Party Chatting message event
		public int  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )
		{
 			int result;
			{
			result = CSSFNetAdapter_GamePartyChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,System.Text.Encoding.UTF8.GetBytes(InSenderName + "\0"),System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.PartyChatMessageS2CEvt);
			return result;
		} // public int  PartyChatMessageS2CEvt( System.UInt64 InSenderID, System.String InSenderName, System.String InChatMessage )


		// Cmd: Join to a game instance
		public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, SF.NetAddress InServerAddress4, SF.NetAddress InServerAddress6 )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InInsUID,ref InServerAddress4,ref InServerAddress6);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinGameInstanceRes);
			return result;
		} // public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, SF.NetAddress InServerAddress4, SF.NetAddress InServerAddress6 )


		// Cmd: Leave game instance
		public int  LeaveGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveGameInstanceRes);
			return result;
		} // public int  LeaveGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Search game instance
		public int  SearchGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable[] InGameInstances )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameSearchGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InGameInstances.Length, InGameInstances);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SearchGameInstanceRes);
			return result;
		} // public int  SearchGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable[] InGameInstances )


		// Cmd: Search game instance
		public int  GetCharacterDataInGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )
		{
 			int result;
			var InGameInstances_ = InGameInstances.ToByteArray();
			using (var InGameInstances_PinnedPtr_ = new PinnedByteBuffer(InGameInstances_))
			{
			result = CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayerID,(ushort)InGameInstances_.Length, InGameInstances_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataInGameInstanceRes);
			return result;
		} // public int  GetCharacterDataInGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, SF.VariableTable InGameInstances )


		// Cmd: Request Game match
		public int  RequestGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameRequestGameMatchRes(m_Connection.NativeHandle, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.RequestGameMatchRes);
			return result;
		} // public int  RequestGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game matched
		public int  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchedS2CEvt(m_Connection.NativeHandle, InInsUID, InTimeStamp,(int) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,(ushort)InChatHistoryData.Length, InChatHistoryData,(ushort)InGameLogData.Length, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchedS2CEvt);
			return result;
		} // public int  GameMatchedS2CEvt( System.UInt64 InInsUID, System.UInt32 InTimeStamp, SF.GameStateID InGameState, System.Byte InDay, System.Byte InMaxPlayer, System.Byte InPlayerIndex, System.Byte InPlayerCharacter, System.Byte InRole, System.Byte InDead, System.Byte[] InChatHistoryData, System.Byte[] InGameLogData, System.UInt32 InStamina, System.UInt64 InTotalGem, System.UInt64 InTotalGameMoney )


		// S2C: Game match failed
		public int  GameMatchFailedS2CEvt( System.Int32 InFailedReason )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchFailedS2CEvt(m_Connection.NativeHandle, InFailedReason);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchFailedS2CEvt);
			return result;
		} // public int  GameMatchFailedS2CEvt( System.Int32 InFailedReason )


		// S2C: Game matching started
		public int  GameMatchingStartedS2CEvt(  )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchingStartedS2CEvt(m_Connection.NativeHandle);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchingStartedS2CEvt);
			return result;
		} // public int  GameMatchingStartedS2CEvt(  )


		// Cmd: Cancel Game match
		public int  CancelGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCancelGameMatchRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CancelGameMatchRes);
			return result;
		} // public int  CancelGameMatchRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: game matching canceled
		public int  GameMatchingCanceledS2CEvt(  )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGameMatchingCanceledS2CEvt(m_Connection.NativeHandle);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GameMatchingCanceledS2CEvt);
			return result;
		} // public int  GameMatchingCanceledS2CEvt(  )


		// Cmd: Buy shop item prepare
		public int  BuyShopItemPrepareRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemPrepareRes(m_Connection.NativeHandle, InTransactionID, InResult, InShopItemID,System.Text.Encoding.UTF8.GetBytes(InPurchaseID + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemPrepareRes);
			return result;
		} // public int  BuyShopItemPrepareRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID, System.String InPurchaseID )


		// Cmd: Buy shop item
		public int  BuyShopItemRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameBuyShopItemRes(m_Connection.NativeHandle, InTransactionID, InResult, InShopItemID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.BuyShopItemRes);
			return result;
		} // public int  BuyShopItemRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InShopItemID )


		// Cmd: Create or Join Chat channel
		public int  CreateOrJoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreateOrJoinChatChannelRes(m_Connection.NativeHandle, InTransactionID, InResult, InChatUID, InChannelLeaderID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateOrJoinChatChannelRes);
			return result;
		} // public int  CreateOrJoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )


		// Cmd: Join
		public int  JoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameJoinChatChannelRes(m_Connection.NativeHandle, InTransactionID, InResult, InChatUID, InChannelLeaderID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.JoinChatChannelRes);
			return result;
		} // public int  JoinChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID )


		// S2C: Player Joined event
		public int  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt(m_Connection.NativeHandle, InChatUID,ref InJoinedPlayer);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelPlayerJoinedS2CEvt);
			return result;
		} // public int  ChatChannelPlayerJoinedS2CEvt( System.UInt64 InChatUID, SF.PlayerInformation InJoinedPlayer )


		// S2C: ChatChannel leader changed event
		public int  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt(m_Connection.NativeHandle, InChatUID, InNewLeaderID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelLeaderChangedS2CEvt);
			return result;
		} // public int  ChatChannelLeaderChangedS2CEvt( System.UInt64 InChatUID, System.UInt64 InNewLeaderID )


		// Cmd: Leave ChatChannel command
		public int  LeaveChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameLeaveChatChannelRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.LeaveChatChannelRes);
			return result;
		} // public int  LeaveChatChannelRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player left event
		public int  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt(m_Connection.NativeHandle, InChatUID, InLeftPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelPlayerLeftS2CEvt);
			return result;
		} // public int  ChatChannelPlayerLeftS2CEvt( System.UInt64 InChatUID, System.UInt64 InLeftPlayerID )


		// Cmd: Kick player from the ChatChannel
		public int  ChatChannelKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelKickPlayerRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelKickPlayerRes);
			return result;
		} // public int  ChatChannelKickPlayerRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Player kicked message
		public int  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt(m_Connection.NativeHandle, InChatUID, InKickedPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelPlayerKickedS2CEvt);
			return result;
		} // public int  ChatChannelPlayerKickedS2CEvt( System.UInt64 InChatUID, System.UInt64 InKickedPlayerID )


		// Cmd: Chat channel sending chatting message
		public int  ChatChannelChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelChatMessageRes);
			return result;
		} // public int  ChatChannelChatMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: ChatChannel Chatting message event
		public int  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(m_Connection.NativeHandle, InSenderID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.ChatChannelChatMessageS2CEvt);
			return result;
		} // public int  ChatChannelChatMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Whisper(tell) other player chatting
		public int  WhisperMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameWhisperMessageRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.WhisperMessageRes);
			return result;
		} // public int  WhisperMessageRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// S2C: Other player whispered(tell) to me message event
		public int  WhisperMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )
		{
 			int result;
			var InChatMetaData_ = InChatMetaData.ToByteArray();
			using (var InChatMetaData_PinnedPtr_ = new PinnedByteBuffer(InChatMetaData_))
			{
			result = CSSFNetAdapter_GameWhisperMessageS2CEvt(m_Connection.NativeHandle, InSenderID,(ushort)InChatMetaData_.Length, InChatMetaData_PinnedPtr_.Ptr,System.Text.Encoding.UTF8.GetBytes(InChatMessage + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.WhisperMessageS2CEvt);
			return result;
		} // public int  WhisperMessageS2CEvt( System.UInt64 InSenderID, SF.VariableTable InChatMetaData, System.String InChatMessage )


		// Cmd: Create character
		public int  CreateCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameCreateCharacterRes(m_Connection.NativeHandle, InTransactionID, InResult, InCharacterID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CreateCharacterRes);
			return result;
		} // public int  CreateCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID )


		// Cmd: Delete character
		public int  DeleteCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameDeleteCharacterRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.DeleteCharacterRes);
			return result;
		} // public int  DeleteCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Get character list
		public int  GetCharacterListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable[] InCharacters )
		{
 			int result;
			{
			result = CSSFNetAdapter_GameGetCharacterListRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InCharacters.Length, InCharacters);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterListRes);
			return result;
		} // public int  GetCharacterListRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable[] InCharacters )


		// Cmd: 
		public int  GetCharacterDataRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameGetCharacterDataRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.GetCharacterDataRes);
			return result;
		} // public int  GetCharacterDataRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InAttributes )


		// Cmd: Select character
		public int  SelectCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, SF.VariableTable InAttributes )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			{
			result = CSSFNetAdapter_GameSelectCharacterRes(m_Connection.NativeHandle, InTransactionID, InResult, InCharacterID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.SelectCharacterRes);
			return result;
		} // public int  SelectCharacterRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, SF.VariableTable InAttributes )


		// Cmd: To call general functionality
		public int  CallFunctionRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InResults )
		{
 			int result;
			var InResults_ = InResults.ToByteArray();
			using (var InResults_PinnedPtr_ = new PinnedByteBuffer(InResults_))
			{
			result = CSSFNetAdapter_GameCallFunctionRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InResults_.Length, InResults_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDGame.CallFunctionRes);
			return result;
		} // public int  CallFunctionRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InResults )


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



		// Cmd: Get Ranking list
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
		static extern int CSSFNetAdapter_GameJoinGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InInsUID, ref SF.NetAddress InServerAddress4, ref SF.NetAddress InServerAddress6 );



		// Cmd: Leave game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameLeaveGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameLeaveGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSearchGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSearchGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInGameInstances,SF.VariableTable[] InGameInstances );



		// Cmd: Search game instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayerID, System.UInt16 _sizeOfInGameInstances,IntPtr InGameInstances );



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
		static extern int CSSFNetAdapter_GameCreateOrJoinChatChannelRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID );



		// Cmd: Join
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameJoinChatChannelRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameJoinChatChannelRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InChatUID, System.UInt64 InChannelLeaderID );



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



		// Cmd: Chat channel sending chatting message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: ChatChannel Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameChatChannelChatMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameChatChannelChatMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Whisper(tell) other player chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameWhisperMessageRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameWhisperMessageRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// S2C: Other player whispered(tell) to me message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameWhisperMessageS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameWhisperMessageS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InSenderID, System.UInt16 _sizeOfInChatMetaData,IntPtr InChatMetaData, [MarshalAs(UnmanagedType.LPArray)] byte[] InChatMessage );



		// Cmd: Create character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCreateCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCreateCharacterRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID );



		// Cmd: Delete character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameDeleteCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameDeleteCharacterRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Get character list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInCharacters,SF.VariableTable[] InCharacters );



		// Cmd: 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameGetCharacterDataRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameGetCharacterDataRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: Select character
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameSelectCharacterRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameSelectCharacterRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt32 InCharacterID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes );



		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_GameCallFunctionRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_GameCallFunctionRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInResults,IntPtr InResults );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrGame : SendMessage




} // namespace SF.Net


