////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
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
 

	public static class MessageIDGame
	{
 		// C2S: Client heartbeat
		public static readonly MessageID HeartbeatC2SEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 0);
		// Cmd: Player connected from a login server and moved to game server
		public static readonly MessageID JoinGameServerCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 1);
		public static readonly MessageID JoinGameServerRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 1);

		// Cmd: player completion statues
		public static readonly MessageID GetAchievementStatsCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 2);
		public static readonly MessageID GetAchievementStatsRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 2);

		// Cmd: Player complition state
		public static readonly MessageID Dummy1Cmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 3);
		public static readonly MessageID Dummy1Res = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 3);

		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		public static readonly MessageID RegisterGCMCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 4);
		public static readonly MessageID RegisterGCMRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 4);

		// Cmd: Unregister Google notification service ID
		public static readonly MessageID UnregisterGCMCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 5);
		public static readonly MessageID UnregisterGCMRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 5);

		// Cmd: Invite friend
		public static readonly MessageID InviteFriendCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 6);
		public static readonly MessageID InviteFriendRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 6);

		// Cmd: Accept friend request
		public static readonly MessageID AcceptFriendRequestCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 7);
		public static readonly MessageID AcceptFriendRequestRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 7);

		// S2C: Notification for friend request is accepted
		public static readonly MessageID FriendRequestAcceptedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 8);
		// Cmd: Remove friden form the friend list
		public static readonly MessageID RemoveFriendCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 9);
		public static readonly MessageID RemoveFriendRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 9);

		// S2C: Friend removed
		public static readonly MessageID FriendRemovedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 10);
		// Cmd: Get friend list
		public static readonly MessageID GetFriendListCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 11);
		public static readonly MessageID GetFriendListRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 11);

		// Cmd: Query notification list
		public static readonly MessageID GetNotificationListCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 12);
		public static readonly MessageID GetNotificationListRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 12);

		// Cmd: Delete notification
		public static readonly MessageID DeleteNotificationCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 13);
		public static readonly MessageID DeleteNotificationRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 13);

		// Cmd: Set notification is read
		public static readonly MessageID SetNotificationReadCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 14);
		public static readonly MessageID SetNotificationReadRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 14);

		// Cmd: Accept notification
		public static readonly MessageID AcceptNotificationCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 15);
		public static readonly MessageID AcceptNotificationRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 15);

		// S2C: Notify new notification
		public static readonly MessageID NotifyS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 16);
		// Cmd: PlayerId Conversion
		public static readonly MessageID FindPlayerByPlatformIdCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 17);
		public static readonly MessageID FindPlayerByPlatformIdRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 17);

		// Cmd: PlayerId conversion
		public static readonly MessageID FindPlayerByCharacterNameCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 18);
		public static readonly MessageID FindPlayerByCharacterNameRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 18);

		// Cmd: PlayerId Conversion
		public static readonly MessageID FindPlayerByPlatformUserNameCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 19);
		public static readonly MessageID FindPlayerByPlatformUserNameRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 19);

		// Cmd: Query playerID list
		public static readonly MessageID FindPlayerByEMailCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 20);
		public static readonly MessageID FindPlayerByEMailRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 20);

		// Cmd: Query playerID list
		public static readonly MessageID FindPlayerByPlayerIDCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 21);
		public static readonly MessageID FindPlayerByPlayerIDRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 21);

		// Cmd: *Request Player Status Update
		public static readonly MessageID RequestPlayerStatusUpdateCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 22);
		public static readonly MessageID RequestPlayerStatusUpdateRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 22);

		// S2C: *Notify Player Status Updated
		public static readonly MessageID NotifyPlayerStatusUpdatedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 23);
		// Cmd: Get Ranking list
		public static readonly MessageID GetRankingListCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 24);
		public static readonly MessageID GetRankingListRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 24);

		// Cmd: Game user game play information
		public static readonly MessageID GetUserGamePlayerInfoCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 25);
		public static readonly MessageID GetUserGamePlayerInfoRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 25);

		// Cmd: Game game play information
		public static readonly MessageID GetGamePlayerInfoCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 26);
		public static readonly MessageID GetGamePlayerInfoRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 26);

		// S2C: Player level up event
		public static readonly MessageID LevelUpS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 27);
		// Cmd: Change NickName
		public static readonly MessageID SetNickNameCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 28);
		public static readonly MessageID SetNickNameRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 28);

		// Cmd: Create Party
		public static readonly MessageID CreatePartyCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 29);
		public static readonly MessageID CreatePartyRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 29);

		// Cmd: Join party
		public static readonly MessageID JoinPartyCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 30);
		public static readonly MessageID JoinPartyRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 30);

		// S2C: Player Joined event
		public static readonly MessageID PartyPlayerJoinedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 31);
		// S2C: Party leader changed event
		public static readonly MessageID PartyLeaderChangedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 32);
		// Cmd: Leave party command
		public static readonly MessageID LeavePartyCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 33);
		public static readonly MessageID LeavePartyRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 33);

		// S2C: Party Player left event
		public static readonly MessageID PartyPlayerLeftS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 34);
		// Cmd: Kick player from the party
		public static readonly MessageID PartyKickPlayerCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 35);
		public static readonly MessageID PartyKickPlayerRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 35);

		// S2C: Party Player kicked message
		public static readonly MessageID PartyPlayerKickedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 36);
		// Cmd: Invite a player to the party
		public static readonly MessageID PartyInviteCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 37);
		public static readonly MessageID PartyInviteRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 37);

		// S2C: Party invite requested
		public static readonly MessageID PartyInviteRequestedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 38);
		// Cmd: Send Party quick chat message
		public static readonly MessageID PartyQuickChatMessageCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 39);
		public static readonly MessageID PartyQuickChatMessageRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 39);

		// S2C: Party Chatting message event
		public static readonly MessageID PartyQuickChatMessageS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 40);
		// Cmd: Party chatting
		public static readonly MessageID PartyChatMessageCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 41);
		public static readonly MessageID PartyChatMessageRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 41);

		// S2C: Party Chatting message event
		public static readonly MessageID PartyChatMessageS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 42);
		// Cmd: Join to a game instance
		public static readonly MessageID JoinGameInstanceCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 43);
		public static readonly MessageID JoinGameInstanceRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 43);

		// Cmd: Leave game instance
		public static readonly MessageID LeaveGameInstanceCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 44);
		public static readonly MessageID LeaveGameInstanceRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 44);

		// Cmd: Search game instance
		public static readonly MessageID SearchGameInstanceCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 45);
		public static readonly MessageID SearchGameInstanceRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 45);

		// Cmd: Search game instance
		public static readonly MessageID GetCharacterDataInGameInstanceCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 46);
		public static readonly MessageID GetCharacterDataInGameInstanceRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 46);

		// Cmd: Request Game match
		public static readonly MessageID RequestGameMatchCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 47);
		public static readonly MessageID RequestGameMatchRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 47);

		// S2C: Game matched
		public static readonly MessageID GameMatchedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 48);
		// S2C: Game match failed
		public static readonly MessageID GameMatchFailedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 49);
		// S2C: Game matching started
		public static readonly MessageID GameMatchingStartedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 50);
		// Cmd: Cancel Game match
		public static readonly MessageID CancelGameMatchCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 51);
		public static readonly MessageID CancelGameMatchRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 51);

		// S2C: game matching canceled
		public static readonly MessageID GameMatchingCanceledS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 52);
		// Cmd: Request UGC template list
		public static readonly MessageID GetUGCTemplatesCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 53);
		public static readonly MessageID GetUGCTemplatesRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 53);

		// Cmd: Save UGC content data
		public static readonly MessageID SaveUGCCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 54);
		public static readonly MessageID SaveUGCRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 54);

		// Cmd: Request WhiteboardSharing
		public static readonly MessageID SearchUGCCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 55);
		public static readonly MessageID SearchUGCRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 55);

		// Cmd: Get UGC content info, name, thumb image and so on
		public static readonly MessageID GetUGCContentInfoCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 56);
		public static readonly MessageID GetUGCContentInfoRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 56);

		// Cmd: Request WhiteboardSharing
		public static readonly MessageID DownloadUGCContentCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 57);
		public static readonly MessageID DownloadUGCContentRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 57);

		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
		public static readonly MessageID RequestUGCZoneInstanceCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 58);
		public static readonly MessageID RequestUGCZoneInstanceRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 58);

		// Cmd: Buy shop item prepare
		public static readonly MessageID BuyShopItemPrepareCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 59);
		public static readonly MessageID BuyShopItemPrepareRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 59);

		// Cmd: Buy shop item
		public static readonly MessageID BuyShopItemCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 60);
		public static readonly MessageID BuyShopItemRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 60);

		// Cmd: Create or Join Chat channel
		public static readonly MessageID CreateOrJoinChatChannelCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 61);
		public static readonly MessageID CreateOrJoinChatChannelRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 61);

		// Cmd: Join
		public static readonly MessageID JoinChatChannelCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 62);
		public static readonly MessageID JoinChatChannelRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 62);

		// S2C: Player Joined event
		public static readonly MessageID ChatChannelPlayerJoinedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 63);
		// S2C: ChatChannel leader changed event
		public static readonly MessageID ChatChannelLeaderChangedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 64);
		// Cmd: Leave ChatChannel command
		public static readonly MessageID LeaveChatChannelCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 65);
		public static readonly MessageID LeaveChatChannelRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 65);

		// S2C: ChatChannel Player left event
		public static readonly MessageID ChatChannelPlayerLeftS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 66);
		// Cmd: Kick player from the ChatChannel
		public static readonly MessageID ChatChannelKickPlayerCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 67);
		public static readonly MessageID ChatChannelKickPlayerRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 67);

		// S2C: ChatChannel Player kicked message
		public static readonly MessageID ChatChannelPlayerKickedS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 68);
		// Cmd: Chat channel sending chatting message
		public static readonly MessageID ChatChannelChatMessageCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 69);
		public static readonly MessageID ChatChannelChatMessageRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 69);

		// S2C: ChatChannel Chatting message event
		public static readonly MessageID ChatChannelChatMessageS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 70);
		// Cmd: Whisper(tell) other player chatting
		public static readonly MessageID WhisperMessageCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 71);
		public static readonly MessageID WhisperMessageRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 71);

		// S2C: Other player whispered(tell) to me message event
		public static readonly MessageID WhisperMessageS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 72);
		// Cmd: Create character
		public static readonly MessageID CreateCharacterCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 73);
		public static readonly MessageID CreateCharacterRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 73);

		// Cmd: Delete character
		public static readonly MessageID DeleteCharacterCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 74);
		public static readonly MessageID DeleteCharacterRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 74);

		// Cmd: Get character list
		public static readonly MessageID GetCharacterListCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 75);
		public static readonly MessageID GetCharacterListRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 75);

		// Cmd: 
		public static readonly MessageID GetCharacterDataCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 76);
		public static readonly MessageID GetCharacterDataRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 76);

		// Cmd: Select character
		public static readonly MessageID SelectCharacterCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 77);
		public static readonly MessageID SelectCharacterRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 77);

		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		public static readonly MessageID RequestServerNoticeUpdateCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 78);
		public static readonly MessageID RequestServerNoticeUpdateRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 78);

		// S2C: Server Notice updated event
		public static readonly MessageID ServerNoticeS2CEvt = MessageID.MakeMessageID(EMessageType.Event, 1, SF.MessageProtocol.Game, 79);
		// Cmd: To call general functionality
		public static readonly MessageID CallFunctionCmd = MessageID.MakeMessageID(EMessageType.Command, 1, SF.MessageProtocol.Game, 80);
		public static readonly MessageID CallFunctionRes = MessageID.MakeMessageID(EMessageType.Result, 1, SF.MessageProtocol.Game, 80);

	}; // public static class MessageIDGame




} // namespace SF.Net


