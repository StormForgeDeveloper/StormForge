////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Game Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public partial class MessageIDGame
	{
 		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		// C2S: Client heart bit
		public static int HeartBitC2SEvt { get { return CSSFNetMessageID_GameHeartBitC2SEvt(); } }

		// Cmd: Player connected from a login server and moved to game server
		public static int JoinGameServerCmd { get { return CSSFNetMessageID_GameJoinGameServerCmd(); } }

		public static int JoinGameServerRes { get { return CSSFNetMessageID_GameJoinGameServerRes(); } }


		// Cmd: player complition statues
		public static int GetComplitionStateCmd { get { return CSSFNetMessageID_GameGetComplitionStateCmd(); } }

		public static int GetComplitionStateRes { get { return CSSFNetMessageID_GameGetComplitionStateRes(); } }


		// Cmd: Player complition state
		public static int SetComplitionStateCmd { get { return CSSFNetMessageID_GameSetComplitionStateCmd(); } }

		public static int SetComplitionStateRes { get { return CSSFNetMessageID_GameSetComplitionStateRes(); } }


		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public static int RegisterGCMCmd { get { return CSSFNetMessageID_GameRegisterGCMCmd(); } }

		public static int RegisterGCMRes { get { return CSSFNetMessageID_GameRegisterGCMRes(); } }


		// Cmd: Unregister Google notification service ID
		public static int UnregisterGCMCmd { get { return CSSFNetMessageID_GameUnregisterGCMCmd(); } }

		public static int UnregisterGCMRes { get { return CSSFNetMessageID_GameUnregisterGCMRes(); } }


		// Cmd: Invite friend
		public static int InviteFriendCmd { get { return CSSFNetMessageID_GameInviteFriendCmd(); } }

		public static int InviteFriendRes { get { return CSSFNetMessageID_GameInviteFriendRes(); } }


		// Cmd: Accept friend request
		public static int AcceptFriendRequestCmd { get { return CSSFNetMessageID_GameAcceptFriendRequestCmd(); } }

		public static int AcceptFriendRequestRes { get { return CSSFNetMessageID_GameAcceptFriendRequestRes(); } }


		// S2C: Notification for friend request is accepted
		public static int FriendRequestAcceptedS2CEvt { get { return CSSFNetMessageID_GameFriendRequestAcceptedS2CEvt(); } }

		// Cmd: Remove friden form the friend list
		public static int RemoveFriendCmd { get { return CSSFNetMessageID_GameRemoveFriendCmd(); } }

		public static int RemoveFriendRes { get { return CSSFNetMessageID_GameRemoveFriendRes(); } }


		// S2C: Friend removed
		public static int FriendRemovedS2CEvt { get { return CSSFNetMessageID_GameFriendRemovedS2CEvt(); } }

		// Cmd: Get friend list
		public static int GetFriendListCmd { get { return CSSFNetMessageID_GameGetFriendListCmd(); } }

		public static int GetFriendListRes { get { return CSSFNetMessageID_GameGetFriendListRes(); } }


		// Cmd: Query notification list
		public static int GetNotificationListCmd { get { return CSSFNetMessageID_GameGetNotificationListCmd(); } }

		public static int GetNotificationListRes { get { return CSSFNetMessageID_GameGetNotificationListRes(); } }


		// Cmd: Delete notification
		public static int DeleteNotificationCmd { get { return CSSFNetMessageID_GameDeleteNotificationCmd(); } }

		public static int DeleteNotificationRes { get { return CSSFNetMessageID_GameDeleteNotificationRes(); } }


		// Cmd: Set notification is read
		public static int SetNotificationReadCmd { get { return CSSFNetMessageID_GameSetNotificationReadCmd(); } }

		public static int SetNotificationReadRes { get { return CSSFNetMessageID_GameSetNotificationReadRes(); } }


		// Cmd: Accept notification
		public static int AcceptNotificationCmd { get { return CSSFNetMessageID_GameAcceptNotificationCmd(); } }

		public static int AcceptNotificationRes { get { return CSSFNetMessageID_GameAcceptNotificationRes(); } }


		// S2C: Notify new notification
		public static int NotifyS2CEvt { get { return CSSFNetMessageID_GameNotifyS2CEvt(); } }

		// Cmd: Query playerID list
		public static int FindPlayerByEMailCmd { get { return CSSFNetMessageID_GameFindPlayerByEMailCmd(); } }

		public static int FindPlayerByEMailRes { get { return CSSFNetMessageID_GameFindPlayerByEMailRes(); } }


		// Cmd: Query playerID list
		public static int FindPlayerByPlayerIDCmd { get { return CSSFNetMessageID_GameFindPlayerByPlayerIDCmd(); } }

		public static int FindPlayerByPlayerIDRes { get { return CSSFNetMessageID_GameFindPlayerByPlayerIDRes(); } }


		// Cmd: *Request Player Status Update
		public static int RequestPlayerStatusUpdateCmd { get { return CSSFNetMessageID_GameRequestPlayerStatusUpdateCmd(); } }

		public static int RequestPlayerStatusUpdateRes { get { return CSSFNetMessageID_GameRequestPlayerStatusUpdateRes(); } }


		// S2C: *Notify Player Status Updated
		public static int NotifyPlayerStatusUpdatedS2CEvt { get { return CSSFNetMessageID_GameNotifyPlayerStatusUpdatedS2CEvt(); } }

		// Cmd: Get Ranking lise
		public static int GetRankingListCmd { get { return CSSFNetMessageID_GameGetRankingListCmd(); } }

		public static int GetRankingListRes { get { return CSSFNetMessageID_GameGetRankingListRes(); } }


		// Cmd: Game user game play information
		public static int GetUserGamePlayerInfoCmd { get { return CSSFNetMessageID_GameGetUserGamePlayerInfoCmd(); } }

		public static int GetUserGamePlayerInfoRes { get { return CSSFNetMessageID_GameGetUserGamePlayerInfoRes(); } }


		// Cmd: Game game play information
		public static int GetGamePlayerInfoCmd { get { return CSSFNetMessageID_GameGetGamePlayerInfoCmd(); } }

		public static int GetGamePlayerInfoRes { get { return CSSFNetMessageID_GameGetGamePlayerInfoRes(); } }


		// S2C: Player level up event
		public static int LevelUpS2CEvt { get { return CSSFNetMessageID_GameLevelUpS2CEvt(); } }

		// Cmd: Change NickName
		public static int SetNickNameCmd { get { return CSSFNetMessageID_GameSetNickNameCmd(); } }

		public static int SetNickNameRes { get { return CSSFNetMessageID_GameSetNickNameRes(); } }


		// Cmd: Create Party
		public static int CreatePartyCmd { get { return CSSFNetMessageID_GameCreatePartyCmd(); } }

		public static int CreatePartyRes { get { return CSSFNetMessageID_GameCreatePartyRes(); } }


		// Cmd: Join party
		public static int JoinPartyCmd { get { return CSSFNetMessageID_GameJoinPartyCmd(); } }

		public static int JoinPartyRes { get { return CSSFNetMessageID_GameJoinPartyRes(); } }


		// S2C: Player Joined event
		public static int PartyPlayerJoinedS2CEvt { get { return CSSFNetMessageID_GamePartyPlayerJoinedS2CEvt(); } }

		// S2C: Party leader changed event
		public static int PartyLeaderChangedS2CEvt { get { return CSSFNetMessageID_GamePartyLeaderChangedS2CEvt(); } }

		// Cmd: Leave party command
		public static int LeavePartyCmd { get { return CSSFNetMessageID_GameLeavePartyCmd(); } }

		public static int LeavePartyRes { get { return CSSFNetMessageID_GameLeavePartyRes(); } }


		// S2C: Party Player left event
		public static int PartyPlayerLeftS2CEvt { get { return CSSFNetMessageID_GamePartyPlayerLeftS2CEvt(); } }

		// Cmd: Kick player from the party
		public static int PartyKickPlayerCmd { get { return CSSFNetMessageID_GamePartyKickPlayerCmd(); } }

		public static int PartyKickPlayerRes { get { return CSSFNetMessageID_GamePartyKickPlayerRes(); } }


		// S2C: Party Player kicked message
		public static int PartyPlayerKickedS2CEvt { get { return CSSFNetMessageID_GamePartyPlayerKickedS2CEvt(); } }

		// Cmd: Invite a player to the party
		public static int PartyInviteCmd { get { return CSSFNetMessageID_GamePartyInviteCmd(); } }

		public static int PartyInviteRes { get { return CSSFNetMessageID_GamePartyInviteRes(); } }


		// S2C: Party invite requested
		public static int PartyInviteRequestedS2CEvt { get { return CSSFNetMessageID_GamePartyInviteRequestedS2CEvt(); } }

		// Cmd: Send Party quick chat message
		public static int PartyQuickChatMessageCmd { get { return CSSFNetMessageID_GamePartyQuickChatMessageCmd(); } }

		public static int PartyQuickChatMessageRes { get { return CSSFNetMessageID_GamePartyQuickChatMessageRes(); } }


		// S2C: Party Chatting message event
		public static int PartyQuickChatMessageS2CEvt { get { return CSSFNetMessageID_GamePartyQuickChatMessageS2CEvt(); } }

		// Cmd: Party chatting
		public static int PartyChatMessageCmd { get { return CSSFNetMessageID_GamePartyChatMessageCmd(); } }

		public static int PartyChatMessageRes { get { return CSSFNetMessageID_GamePartyChatMessageRes(); } }


		// S2C: Party Chatting message event
		public static int PartyChatMessageS2CEvt { get { return CSSFNetMessageID_GamePartyChatMessageS2CEvt(); } }

		// Cmd: Join to a game
		public static int JoinGameCmd { get { return CSSFNetMessageID_GameJoinGameCmd(); } }

		public static int JoinGameRes { get { return CSSFNetMessageID_GameJoinGameRes(); } }


		// S2C: Player Joined in the game
		public static int PlayerJoinedS2CEvt { get { return CSSFNetMessageID_GamePlayerJoinedS2CEvt(); } }

		// Cmd: Leave Game
		public static int LeaveGameCmd { get { return CSSFNetMessageID_GameLeaveGameCmd(); } }

		public static int LeaveGameRes { get { return CSSFNetMessageID_GameLeaveGameRes(); } }


		// S2C: Player left event
		public static int PlayerLeftS2CEvt { get { return CSSFNetMessageID_GamePlayerLeftS2CEvt(); } }

		// Cmd: Kick player
		public static int KickPlayerCmd { get { return CSSFNetMessageID_GameKickPlayerCmd(); } }

		public static int KickPlayerRes { get { return CSSFNetMessageID_GameKickPlayerRes(); } }


		// S2C: Player kicked
		public static int PlayerKickedS2CEvt { get { return CSSFNetMessageID_GamePlayerKickedS2CEvt(); } }

		// Cmd: Assign role + Game state reset
		public static int AssignRoleCmd { get { return CSSFNetMessageID_GameAssignRoleCmd(); } }

		public static int AssignRoleRes { get { return CSSFNetMessageID_GameAssignRoleRes(); } }


		// S2C: Role assigned event
		public static int RoleAssignedS2CEvt { get { return CSSFNetMessageID_GameRoleAssignedS2CEvt(); } }

		// Cmd: Send chatting message to the game
		public static int ChatMessageCmd { get { return CSSFNetMessageID_GameChatMessageCmd(); } }

		public static int ChatMessageRes { get { return CSSFNetMessageID_GameChatMessageRes(); } }


		// S2C: Chatting message event 
		public static int ChatMessageS2CEvt { get { return CSSFNetMessageID_GameChatMessageS2CEvt(); } }

		// Cmd: Advance game
		public static int AdvanceGameCmd { get { return CSSFNetMessageID_GameAdvanceGameCmd(); } }

		public static int AdvanceGameRes { get { return CSSFNetMessageID_GameAdvanceGameRes(); } }


		// S2C: The game state is advanced
		public static int GameAdvancedS2CEvt { get { return CSSFNetMessageID_GameGameAdvancedS2CEvt(); } }

		// S2C: Game is ended
		public static int GameEndedS2CEvt { get { return CSSFNetMessageID_GameGameEndedS2CEvt(); } }

		// Cmd: Vote game advance
		public static int VoteGameAdvanceCmd { get { return CSSFNetMessageID_GameVoteGameAdvanceCmd(); } }

		public static int VoteGameAdvanceRes { get { return CSSFNetMessageID_GameVoteGameAdvanceRes(); } }


		// S2C: GameAdvance is Voted
		public static int GameAdvanceVotedS2CEvt { get { return CSSFNetMessageID_GameGameAdvanceVotedS2CEvt(); } }

		// Cmd: Vote
		public static int VoteCmd { get { return CSSFNetMessageID_GameVoteCmd(); } }

		public static int VoteRes { get { return CSSFNetMessageID_GameVoteRes(); } }


		// S2C: Player Voted
		public static int VotedS2CEvt { get { return CSSFNetMessageID_GameVotedS2CEvt(); } }

		// S2C: Vote is ended
		public static int VoteEndS2CEvt { get { return CSSFNetMessageID_GameVoteEndS2CEvt(); } }

		// S2C: Player Killed
		public static int PlayerKilledS2CEvt { get { return CSSFNetMessageID_GamePlayerKilledS2CEvt(); } }

		// S2C: Player Voted
		public static int PlayerRevealedS2CEvt { get { return CSSFNetMessageID_GamePlayerRevealedS2CEvt(); } }

		// Cmd: Play again with the current players
		public static int GamePlayAgainCmd { get { return CSSFNetMessageID_GameGamePlayAgainCmd(); } }

		public static int GamePlayAgainRes { get { return CSSFNetMessageID_GameGamePlayAgainRes(); } }


		// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
		public static int GamePlayAgainS2CEvt { get { return CSSFNetMessageID_GameGamePlayAgainS2CEvt(); } }

		// Cmd: Player. reveal a player
		public static int GameRevealPlayerCmd { get { return CSSFNetMessageID_GameGameRevealPlayerCmd(); } }

		public static int GameRevealPlayerRes { get { return CSSFNetMessageID_GameGameRevealPlayerRes(); } }


		// Cmd: Player. revive himself
		public static int GamePlayerReviveCmd { get { return CSSFNetMessageID_GameGamePlayerReviveCmd(); } }

		public static int GamePlayerReviveRes { get { return CSSFNetMessageID_GameGamePlayerReviveRes(); } }


		// S2C: Player is revived
		public static int GamePlayerRevivedS2CEvt { get { return CSSFNetMessageID_GameGamePlayerRevivedS2CEvt(); } }

		// Cmd: Player. reset ranking
		public static int GamePlayerResetRankCmd { get { return CSSFNetMessageID_GameGamePlayerResetRankCmd(); } }

		public static int GamePlayerResetRankRes { get { return CSSFNetMessageID_GameGamePlayerResetRankRes(); } }


		// Cmd: Request Game match
		public static int RequestGameMatchCmd { get { return CSSFNetMessageID_GameRequestGameMatchCmd(); } }

		public static int RequestGameMatchRes { get { return CSSFNetMessageID_GameRequestGameMatchRes(); } }


		// S2C: Game matched
		public static int GameMatchedS2CEvt { get { return CSSFNetMessageID_GameGameMatchedS2CEvt(); } }

		// S2C: Game match failed
		public static int GameMatchFailedS2CEvt { get { return CSSFNetMessageID_GameGameMatchFailedS2CEvt(); } }

		// S2C: Game matching started
		public static int GameMatchingStartedS2CEvt { get { return CSSFNetMessageID_GameGameMatchingStartedS2CEvt(); } }

		// Cmd: Cancel Game match
		public static int CancelGameMatchCmd { get { return CSSFNetMessageID_GameCancelGameMatchCmd(); } }

		public static int CancelGameMatchRes { get { return CSSFNetMessageID_GameCancelGameMatchRes(); } }


		// S2C: game matching canceled
		public static int GameMatchingCanceledS2CEvt { get { return CSSFNetMessageID_GameGameMatchingCanceledS2CEvt(); } }

		// Cmd: Buy shop item prepare
		public static int BuyShopItemPrepareCmd { get { return CSSFNetMessageID_GameBuyShopItemPrepareCmd(); } }

		public static int BuyShopItemPrepareRes { get { return CSSFNetMessageID_GameBuyShopItemPrepareRes(); } }


		// Cmd: Buy shop item
		public static int BuyShopItemCmd { get { return CSSFNetMessageID_GameBuyShopItemCmd(); } }

		public static int BuyShopItemRes { get { return CSSFNetMessageID_GameBuyShopItemRes(); } }


		// Cmd: Create or Join Chat channel
		public static int CreateOrJoinChatChannelCmd { get { return CSSFNetMessageID_GameCreateOrJoinChatChannelCmd(); } }

		public static int CreateOrJoinChatChannelRes { get { return CSSFNetMessageID_GameCreateOrJoinChatChannelRes(); } }


		// Cmd: Join
		public static int JoinChatChannelCmd { get { return CSSFNetMessageID_GameJoinChatChannelCmd(); } }

		public static int JoinChatChannelRes { get { return CSSFNetMessageID_GameJoinChatChannelRes(); } }


		// S2C: Player Joined event
		public static int ChatChannelPlayerJoinedS2CEvt { get { return CSSFNetMessageID_GameChatChannelPlayerJoinedS2CEvt(); } }

		// S2C: ChatChannel leader changed event
		public static int ChatChannelLeaderChangedS2CEvt { get { return CSSFNetMessageID_GameChatChannelLeaderChangedS2CEvt(); } }

		// Cmd: Leave ChatChannel command
		public static int LeaveChatChannelCmd { get { return CSSFNetMessageID_GameLeaveChatChannelCmd(); } }

		public static int LeaveChatChannelRes { get { return CSSFNetMessageID_GameLeaveChatChannelRes(); } }


		// S2C: ChatChannel Player left event
		public static int ChatChannelPlayerLeftS2CEvt { get { return CSSFNetMessageID_GameChatChannelPlayerLeftS2CEvt(); } }

		// Cmd: Kick player from the ChatChannel
		public static int ChatChannelKickPlayerCmd { get { return CSSFNetMessageID_GameChatChannelKickPlayerCmd(); } }

		public static int ChatChannelKickPlayerRes { get { return CSSFNetMessageID_GameChatChannelKickPlayerRes(); } }


		// S2C: ChatChannel Player kicked message
		public static int ChatChannelPlayerKickedS2CEvt { get { return CSSFNetMessageID_GameChatChannelPlayerKickedS2CEvt(); } }

		// Cmd: Party chatting
		public static int ChatChannelChatMessageCmd { get { return CSSFNetMessageID_GameChatChannelChatMessageCmd(); } }

		public static int ChatChannelChatMessageRes { get { return CSSFNetMessageID_GameChatChannelChatMessageRes(); } }


		// S2C: ChatChannel Chatting message event
		public static int ChatChannelChatMessageS2CEvt { get { return CSSFNetMessageID_GameChatChannelChatMessageS2CEvt(); } }

		// Cmd: Create or Join Chat channel
		public static int GetCharacterListCmd { get { return CSSFNetMessageID_GameGetCharacterListCmd(); } }

		public static int GetCharacterListRes { get { return CSSFNetMessageID_GameGetCharacterListRes(); } }


		// Cmd: Create or Join Chat channel
		public static int CreateCharacterCmd { get { return CSSFNetMessageID_GameCreateCharacterCmd(); } }

		public static int CreateCharacterRes { get { return CSSFNetMessageID_GameCreateCharacterRes(); } }


		// Cmd: Give my stamina to other player
		public static int GiveStaminaCmd { get { return CSSFNetMessageID_GameGiveStaminaCmd(); } }

		public static int GiveStaminaRes { get { return CSSFNetMessageID_GameGiveStaminaRes(); } }


		// Cmd: For debug, Change configue preset
		public static int SetPresetGameConfigIDCmd { get { return CSSFNetMessageID_GameSetPresetGameConfigIDCmd(); } }

		public static int SetPresetGameConfigIDRes { get { return CSSFNetMessageID_GameSetPresetGameConfigIDRes(); } }


		// Cmd: For Debug
		public static int GainGameResourceCmd { get { return CSSFNetMessageID_GameGainGameResourceCmd(); } }

		public static int GainGameResourceRes { get { return CSSFNetMessageID_GameGainGameResourceRes(); } }


		#region Native Interfaces 
		// C2S: Client heart bit
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameHeartBitC2SEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameHeartBitC2SEvt();


		// Cmd: Player connected from a login server and moved to game server
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinGameServerCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinGameServerCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinGameServerRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinGameServerRes();



		// Cmd: player complition statues
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetComplitionStateCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetComplitionStateCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetComplitionStateRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetComplitionStateRes();



		// Cmd: Player complition state
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetComplitionStateCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetComplitionStateCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetComplitionStateRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetComplitionStateRes();



		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRegisterGCMCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRegisterGCMCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRegisterGCMRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRegisterGCMRes();



		// Cmd: Unregister Google notification service ID
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameUnregisterGCMCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameUnregisterGCMCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameUnregisterGCMRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameUnregisterGCMRes();



		// Cmd: Invite friend
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameInviteFriendCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameInviteFriendCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameInviteFriendRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameInviteFriendRes();



		// Cmd: Accept friend request
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAcceptFriendRequestCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAcceptFriendRequestCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAcceptFriendRequestRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAcceptFriendRequestRes();



		// S2C: Notification for friend request is accepted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameFriendRequestAcceptedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameFriendRequestAcceptedS2CEvt();


		// Cmd: Remove friden form the friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRemoveFriendCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRemoveFriendCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRemoveFriendRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRemoveFriendRes();



		// S2C: Friend removed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameFriendRemovedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameFriendRemovedS2CEvt();


		// Cmd: Get friend list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetFriendListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetFriendListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetFriendListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetFriendListRes();



		// Cmd: Query notification list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetNotificationListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetNotificationListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetNotificationListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetNotificationListRes();



		// Cmd: Delete notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameDeleteNotificationCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameDeleteNotificationCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameDeleteNotificationRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameDeleteNotificationRes();



		// Cmd: Set notification is read
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetNotificationReadCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetNotificationReadCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetNotificationReadRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetNotificationReadRes();



		// Cmd: Accept notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAcceptNotificationCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAcceptNotificationCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAcceptNotificationRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAcceptNotificationRes();



		// S2C: Notify new notification
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameNotifyS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameNotifyS2CEvt();


		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameFindPlayerByEMailCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameFindPlayerByEMailCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameFindPlayerByEMailRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameFindPlayerByEMailRes();



		// Cmd: Query playerID list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameFindPlayerByPlayerIDCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameFindPlayerByPlayerIDCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameFindPlayerByPlayerIDRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameFindPlayerByPlayerIDRes();



		// Cmd: *Request Player Status Update
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRequestPlayerStatusUpdateCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRequestPlayerStatusUpdateCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRequestPlayerStatusUpdateRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRequestPlayerStatusUpdateRes();



		// S2C: *Notify Player Status Updated
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameNotifyPlayerStatusUpdatedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameNotifyPlayerStatusUpdatedS2CEvt();


		// Cmd: Get Ranking lise
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetRankingListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetRankingListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetRankingListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetRankingListRes();



		// Cmd: Game user game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetUserGamePlayerInfoCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetUserGamePlayerInfoCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetUserGamePlayerInfoRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetUserGamePlayerInfoRes();



		// Cmd: Game game play information
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetGamePlayerInfoCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetGamePlayerInfoCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetGamePlayerInfoRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetGamePlayerInfoRes();



		// S2C: Player level up event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLevelUpS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLevelUpS2CEvt();


		// Cmd: Change NickName
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetNickNameCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetNickNameCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetNickNameRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetNickNameRes();



		// Cmd: Create Party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCreatePartyCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCreatePartyCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCreatePartyRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCreatePartyRes();



		// Cmd: Join party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinPartyCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinPartyCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinPartyRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinPartyRes();



		// S2C: Player Joined event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyPlayerJoinedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyPlayerJoinedS2CEvt();


		// S2C: Party leader changed event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyLeaderChangedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyLeaderChangedS2CEvt();


		// Cmd: Leave party command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLeavePartyCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLeavePartyCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLeavePartyRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLeavePartyRes();



		// S2C: Party Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyPlayerLeftS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyPlayerLeftS2CEvt();


		// Cmd: Kick player from the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyKickPlayerCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyKickPlayerCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyKickPlayerRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyKickPlayerRes();



		// S2C: Party Player kicked message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyPlayerKickedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyPlayerKickedS2CEvt();


		// Cmd: Invite a player to the party
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyInviteCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyInviteCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyInviteRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyInviteRes();



		// S2C: Party invite requested
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyInviteRequestedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyInviteRequestedS2CEvt();


		// Cmd: Send Party quick chat message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyQuickChatMessageCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyQuickChatMessageCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyQuickChatMessageRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyQuickChatMessageRes();



		// S2C: Party Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyQuickChatMessageS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyQuickChatMessageS2CEvt();


		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyChatMessageCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyChatMessageCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyChatMessageRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyChatMessageRes();



		// S2C: Party Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePartyChatMessageS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePartyChatMessageS2CEvt();


		// Cmd: Join to a game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinGameCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinGameCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinGameRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinGameRes();



		// S2C: Player Joined in the game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePlayerJoinedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePlayerJoinedS2CEvt();


		// Cmd: Leave Game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLeaveGameCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLeaveGameCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLeaveGameRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLeaveGameRes();



		// S2C: Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePlayerLeftS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePlayerLeftS2CEvt();


		// Cmd: Kick player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameKickPlayerCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameKickPlayerCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameKickPlayerRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameKickPlayerRes();



		// S2C: Player kicked
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePlayerKickedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePlayerKickedS2CEvt();


		// Cmd: Assign role + Game state reset
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAssignRoleCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAssignRoleCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAssignRoleRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAssignRoleRes();



		// S2C: Role assigned event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRoleAssignedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRoleAssignedS2CEvt();


		// Cmd: Send chatting message to the game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatMessageCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatMessageCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatMessageRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatMessageRes();



		// S2C: Chatting message event 
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatMessageS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatMessageS2CEvt();


		// Cmd: Advance game
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAdvanceGameCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAdvanceGameCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameAdvanceGameRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameAdvanceGameRes();



		// S2C: The game state is advanced
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameAdvancedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameAdvancedS2CEvt();


		// S2C: Game is ended
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameEndedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameEndedS2CEvt();


		// Cmd: Vote game advance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameVoteGameAdvanceCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameVoteGameAdvanceCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameVoteGameAdvanceRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameVoteGameAdvanceRes();



		// S2C: GameAdvance is Voted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameAdvanceVotedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameAdvanceVotedS2CEvt();


		// Cmd: Vote
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameVoteCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameVoteCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameVoteRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameVoteRes();



		// S2C: Player Voted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameVotedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameVotedS2CEvt();


		// S2C: Vote is ended
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameVoteEndS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameVoteEndS2CEvt();


		// S2C: Player Killed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePlayerKilledS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePlayerKilledS2CEvt();


		// S2C: Player Voted
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GamePlayerRevealedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GamePlayerRevealedS2CEvt();


		// Cmd: Play again with the current players
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayAgainCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayAgainCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayAgainRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayAgainRes();



		// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayAgainS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayAgainS2CEvt();


		// Cmd: Player. reveal a player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameRevealPlayerCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameRevealPlayerCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameRevealPlayerRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameRevealPlayerRes();



		// Cmd: Player. revive himself
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayerReviveCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayerReviveCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayerReviveRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayerReviveRes();



		// S2C: Player is revived
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayerRevivedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayerRevivedS2CEvt();


		// Cmd: Player. reset ranking
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayerResetRankCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayerResetRankCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGamePlayerResetRankRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGamePlayerResetRankRes();



		// Cmd: Request Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRequestGameMatchCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRequestGameMatchCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameRequestGameMatchRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameRequestGameMatchRes();



		// S2C: Game matched
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameMatchedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameMatchedS2CEvt();


		// S2C: Game match failed
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameMatchFailedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameMatchFailedS2CEvt();


		// S2C: Game matching started
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameMatchingStartedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameMatchingStartedS2CEvt();


		// Cmd: Cancel Game match
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCancelGameMatchCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCancelGameMatchCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCancelGameMatchRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCancelGameMatchRes();



		// S2C: game matching canceled
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGameMatchingCanceledS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGameMatchingCanceledS2CEvt();


		// Cmd: Buy shop item prepare
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameBuyShopItemPrepareCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameBuyShopItemPrepareCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameBuyShopItemPrepareRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameBuyShopItemPrepareRes();



		// Cmd: Buy shop item
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameBuyShopItemCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameBuyShopItemCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameBuyShopItemRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameBuyShopItemRes();



		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCreateOrJoinChatChannelCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCreateOrJoinChatChannelCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCreateOrJoinChatChannelRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCreateOrJoinChatChannelRes();



		// Cmd: Join
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinChatChannelCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinChatChannelCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameJoinChatChannelRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameJoinChatChannelRes();



		// S2C: Player Joined event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelPlayerJoinedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelPlayerJoinedS2CEvt();


		// S2C: ChatChannel leader changed event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelLeaderChangedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelLeaderChangedS2CEvt();


		// Cmd: Leave ChatChannel command
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLeaveChatChannelCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLeaveChatChannelCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameLeaveChatChannelRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameLeaveChatChannelRes();



		// S2C: ChatChannel Player left event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelPlayerLeftS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelPlayerLeftS2CEvt();


		// Cmd: Kick player from the ChatChannel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelKickPlayerCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelKickPlayerCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelKickPlayerRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelKickPlayerRes();



		// S2C: ChatChannel Player kicked message
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelPlayerKickedS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelPlayerKickedS2CEvt();


		// Cmd: Party chatting
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelChatMessageCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelChatMessageCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelChatMessageRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelChatMessageRes();



		// S2C: ChatChannel Chatting message event
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameChatChannelChatMessageS2CEvt", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameChatChannelChatMessageS2CEvt();


		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetCharacterListCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetCharacterListCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGetCharacterListRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGetCharacterListRes();



		// Cmd: Create or Join Chat channel
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCreateCharacterCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCreateCharacterCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameCreateCharacterRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameCreateCharacterRes();



		// Cmd: Give my stamina to other player
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGiveStaminaCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGiveStaminaCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGiveStaminaRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGiveStaminaRes();



		// Cmd: For debug, Change configue preset
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetPresetGameConfigIDCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetPresetGameConfigIDCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameSetPresetGameConfigIDRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameSetPresetGameConfigIDRes();



		// Cmd: For Debug
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGainGameResourceCmd", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGainGameResourceCmd();


		[DllImport(NativeDLLName, EntryPoint = "CSSFNetMessageID_GameGainGameResourceRes", CharSet = CharSet.Auto)]
		static extern int CSSFNetMessageID_GameGainGameResourceRes();



		#endregion //Native Interfaces 
	}; // public partial class MessageIDGame




} // namespace SF.Net


