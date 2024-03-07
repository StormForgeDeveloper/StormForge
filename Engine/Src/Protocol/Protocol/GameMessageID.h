////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Game Message IDs
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Net/SFMessage.h"
#include "SFProtocol.h"


namespace SF
{
 	namespace Message
	{
 		namespace Game
		{
 

			// C2S: Client heartbeat
			constexpr MessageID MID_HeartbeatC2SEvt(MessageType::Event,1,MessageProtocol::Game,0);
			// Cmd: Player connected from a login server and moved to game server
			constexpr MessageID MID_JoinGameServerCmd(MessageType::Command,1,MessageProtocol::Game,1);
			constexpr MessageID MID_JoinGameServerRes(MessageType::Result,1,MessageProtocol::Game,1);

			// Cmd: player complition statues
			constexpr MessageID MID_GetAchievementStatsCmd(MessageType::Command,1,MessageProtocol::Game,2);
			constexpr MessageID MID_GetAchievementStatsRes(MessageType::Result,1,MessageProtocol::Game,2);

			// Cmd: Player complition state
			constexpr MessageID MID_Dummy1Cmd(MessageType::Command,1,MessageProtocol::Game,3);
			constexpr MessageID MID_Dummy1Res(MessageType::Result,1,MessageProtocol::Game,3);

			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			constexpr MessageID MID_RegisterGCMCmd(MessageType::Command,1,MessageProtocol::Game,4);
			constexpr MessageID MID_RegisterGCMRes(MessageType::Result,1,MessageProtocol::Game,4);

			// Cmd: Unregister Google notification service ID
			constexpr MessageID MID_UnregisterGCMCmd(MessageType::Command,1,MessageProtocol::Game,5);
			constexpr MessageID MID_UnregisterGCMRes(MessageType::Result,1,MessageProtocol::Game,5);

			// Cmd: Invite friend
			constexpr MessageID MID_InviteFriendCmd(MessageType::Command,1,MessageProtocol::Game,6);
			constexpr MessageID MID_InviteFriendRes(MessageType::Result,1,MessageProtocol::Game,6);

			// Cmd: Accept friend request
			constexpr MessageID MID_AcceptFriendRequestCmd(MessageType::Command,1,MessageProtocol::Game,7);
			constexpr MessageID MID_AcceptFriendRequestRes(MessageType::Result,1,MessageProtocol::Game,7);

			// S2C: Notification for friend request is accepted
			constexpr MessageID MID_FriendRequestAcceptedS2CEvt(MessageType::Event,1,MessageProtocol::Game,8);
			// Cmd: Remove friden form the friend list
			constexpr MessageID MID_RemoveFriendCmd(MessageType::Command,1,MessageProtocol::Game,9);
			constexpr MessageID MID_RemoveFriendRes(MessageType::Result,1,MessageProtocol::Game,9);

			// S2C: Friend removed
			constexpr MessageID MID_FriendRemovedS2CEvt(MessageType::Event,1,MessageProtocol::Game,10);
			// Cmd: Get friend list
			constexpr MessageID MID_GetFriendListCmd(MessageType::Command,1,MessageProtocol::Game,11);
			constexpr MessageID MID_GetFriendListRes(MessageType::Result,1,MessageProtocol::Game,11);

			// Cmd: Query notification list
			constexpr MessageID MID_GetNotificationListCmd(MessageType::Command,1,MessageProtocol::Game,12);
			constexpr MessageID MID_GetNotificationListRes(MessageType::Result,1,MessageProtocol::Game,12);

			// Cmd: Delete notification
			constexpr MessageID MID_DeleteNotificationCmd(MessageType::Command,1,MessageProtocol::Game,13);
			constexpr MessageID MID_DeleteNotificationRes(MessageType::Result,1,MessageProtocol::Game,13);

			// Cmd: Set notification is read
			constexpr MessageID MID_SetNotificationReadCmd(MessageType::Command,1,MessageProtocol::Game,14);
			constexpr MessageID MID_SetNotificationReadRes(MessageType::Result,1,MessageProtocol::Game,14);

			// Cmd: Accept notification
			constexpr MessageID MID_AcceptNotificationCmd(MessageType::Command,1,MessageProtocol::Game,15);
			constexpr MessageID MID_AcceptNotificationRes(MessageType::Result,1,MessageProtocol::Game,15);

			// S2C: Notify new notification
			constexpr MessageID MID_NotifyS2CEvt(MessageType::Event,1,MessageProtocol::Game,16);
			// Cmd: PlayerId Conversion
			constexpr MessageID MID_FindPlayerByPlatformIdCmd(MessageType::Command,1,MessageProtocol::Game,17);
			constexpr MessageID MID_FindPlayerByPlatformIdRes(MessageType::Result,1,MessageProtocol::Game,17);

			// Cmd: PlayerId conversion
			constexpr MessageID MID_FindPlayerByCharacterNameCmd(MessageType::Command,1,MessageProtocol::Game,18);
			constexpr MessageID MID_FindPlayerByCharacterNameRes(MessageType::Result,1,MessageProtocol::Game,18);

			// Cmd: PlayerId Conversion
			constexpr MessageID MID_FindPlayerByPlatformUserNameCmd(MessageType::Command,1,MessageProtocol::Game,19);
			constexpr MessageID MID_FindPlayerByPlatformUserNameRes(MessageType::Result,1,MessageProtocol::Game,19);

			// Cmd: Query playerID list
			constexpr MessageID MID_FindPlayerByEMailCmd(MessageType::Command,1,MessageProtocol::Game,20);
			constexpr MessageID MID_FindPlayerByEMailRes(MessageType::Result,1,MessageProtocol::Game,20);

			// Cmd: Query playerID list
			constexpr MessageID MID_FindPlayerByPlayerIDCmd(MessageType::Command,1,MessageProtocol::Game,21);
			constexpr MessageID MID_FindPlayerByPlayerIDRes(MessageType::Result,1,MessageProtocol::Game,21);

			// Cmd: *Request Player Status Update
			constexpr MessageID MID_RequestPlayerStatusUpdateCmd(MessageType::Command,1,MessageProtocol::Game,22);
			constexpr MessageID MID_RequestPlayerStatusUpdateRes(MessageType::Result,1,MessageProtocol::Game,22);

			// S2C: *Notify Player Status Updated
			constexpr MessageID MID_NotifyPlayerStatusUpdatedS2CEvt(MessageType::Event,1,MessageProtocol::Game,23);
			// Cmd: Get Ranking list
			constexpr MessageID MID_GetRankingListCmd(MessageType::Command,1,MessageProtocol::Game,24);
			constexpr MessageID MID_GetRankingListRes(MessageType::Result,1,MessageProtocol::Game,24);

			// Cmd: Game user game play information
			constexpr MessageID MID_GetUserGamePlayerInfoCmd(MessageType::Command,1,MessageProtocol::Game,25);
			constexpr MessageID MID_GetUserGamePlayerInfoRes(MessageType::Result,1,MessageProtocol::Game,25);

			// Cmd: Game game play information
			constexpr MessageID MID_GetGamePlayerInfoCmd(MessageType::Command,1,MessageProtocol::Game,26);
			constexpr MessageID MID_GetGamePlayerInfoRes(MessageType::Result,1,MessageProtocol::Game,26);

			// S2C: Player level up event
			constexpr MessageID MID_LevelUpS2CEvt(MessageType::Event,1,MessageProtocol::Game,27);
			// Cmd: Change NickName
			constexpr MessageID MID_SetNickNameCmd(MessageType::Command,1,MessageProtocol::Game,28);
			constexpr MessageID MID_SetNickNameRes(MessageType::Result,1,MessageProtocol::Game,28);

			// Cmd: Create Party
			constexpr MessageID MID_CreatePartyCmd(MessageType::Command,1,MessageProtocol::Game,29);
			constexpr MessageID MID_CreatePartyRes(MessageType::Result,1,MessageProtocol::Game,29);

			// Cmd: Join party
			constexpr MessageID MID_JoinPartyCmd(MessageType::Command,1,MessageProtocol::Game,30);
			constexpr MessageID MID_JoinPartyRes(MessageType::Result,1,MessageProtocol::Game,30);

			// S2C: Player Joined event
			constexpr MessageID MID_PartyPlayerJoinedS2CEvt(MessageType::Event,1,MessageProtocol::Game,31);
			// S2C: Party leader changed event
			constexpr MessageID MID_PartyLeaderChangedS2CEvt(MessageType::Event,1,MessageProtocol::Game,32);
			// Cmd: Leave party command
			constexpr MessageID MID_LeavePartyCmd(MessageType::Command,1,MessageProtocol::Game,33);
			constexpr MessageID MID_LeavePartyRes(MessageType::Result,1,MessageProtocol::Game,33);

			// S2C: Party Player left event
			constexpr MessageID MID_PartyPlayerLeftS2CEvt(MessageType::Event,1,MessageProtocol::Game,34);
			// Cmd: Kick player from the party
			constexpr MessageID MID_PartyKickPlayerCmd(MessageType::Command,1,MessageProtocol::Game,35);
			constexpr MessageID MID_PartyKickPlayerRes(MessageType::Result,1,MessageProtocol::Game,35);

			// S2C: Party Player kicked message
			constexpr MessageID MID_PartyPlayerKickedS2CEvt(MessageType::Event,1,MessageProtocol::Game,36);
			// Cmd: Invite a player to the party
			constexpr MessageID MID_PartyInviteCmd(MessageType::Command,1,MessageProtocol::Game,37);
			constexpr MessageID MID_PartyInviteRes(MessageType::Result,1,MessageProtocol::Game,37);

			// S2C: Party invite requested
			constexpr MessageID MID_PartyInviteRequestedS2CEvt(MessageType::Event,1,MessageProtocol::Game,38);
			// Cmd: Send Party quick chat message
			constexpr MessageID MID_PartyQuickChatMessageCmd(MessageType::Command,1,MessageProtocol::Game,39);
			constexpr MessageID MID_PartyQuickChatMessageRes(MessageType::Result,1,MessageProtocol::Game,39);

			// S2C: Party Chatting message event
			constexpr MessageID MID_PartyQuickChatMessageS2CEvt(MessageType::Event,1,MessageProtocol::Game,40);
			// Cmd: Party chatting
			constexpr MessageID MID_PartyChatMessageCmd(MessageType::Command,1,MessageProtocol::Game,41);
			constexpr MessageID MID_PartyChatMessageRes(MessageType::Result,1,MessageProtocol::Game,41);

			// S2C: Party Chatting message event
			constexpr MessageID MID_PartyChatMessageS2CEvt(MessageType::Event,1,MessageProtocol::Game,42);
			// Cmd: Join to a game instance
			constexpr MessageID MID_JoinGameInstanceCmd(MessageType::Command,1,MessageProtocol::Game,43);
			constexpr MessageID MID_JoinGameInstanceRes(MessageType::Result,1,MessageProtocol::Game,43);

			// Cmd: Leave game instance
			constexpr MessageID MID_LeaveGameInstanceCmd(MessageType::Command,1,MessageProtocol::Game,44);
			constexpr MessageID MID_LeaveGameInstanceRes(MessageType::Result,1,MessageProtocol::Game,44);

			// Cmd: Search game instance
			constexpr MessageID MID_SearchGameInstanceCmd(MessageType::Command,1,MessageProtocol::Game,45);
			constexpr MessageID MID_SearchGameInstanceRes(MessageType::Result,1,MessageProtocol::Game,45);

			// Cmd: Search game instance
			constexpr MessageID MID_GetCharacterDataInGameInstanceCmd(MessageType::Command,1,MessageProtocol::Game,46);
			constexpr MessageID MID_GetCharacterDataInGameInstanceRes(MessageType::Result,1,MessageProtocol::Game,46);

			// Cmd: Request Game match
			constexpr MessageID MID_RequestGameMatchCmd(MessageType::Command,1,MessageProtocol::Game,47);
			constexpr MessageID MID_RequestGameMatchRes(MessageType::Result,1,MessageProtocol::Game,47);

			// S2C: Game matched
			constexpr MessageID MID_GameMatchedS2CEvt(MessageType::Event,1,MessageProtocol::Game,48);
			// S2C: Game match failed
			constexpr MessageID MID_GameMatchFailedS2CEvt(MessageType::Event,1,MessageProtocol::Game,49);
			// S2C: Game matching started
			constexpr MessageID MID_GameMatchingStartedS2CEvt(MessageType::Event,1,MessageProtocol::Game,50);
			// Cmd: Cancel Game match
			constexpr MessageID MID_CancelGameMatchCmd(MessageType::Command,1,MessageProtocol::Game,51);
			constexpr MessageID MID_CancelGameMatchRes(MessageType::Result,1,MessageProtocol::Game,51);

			// S2C: game matching canceled
			constexpr MessageID MID_GameMatchingCanceledS2CEvt(MessageType::Event,1,MessageProtocol::Game,52);
			// Cmd: Request UGC template list
			constexpr MessageID MID_GetUGCTemplatesCmd(MessageType::Command,1,MessageProtocol::Game,53);
			constexpr MessageID MID_GetUGCTemplatesRes(MessageType::Result,1,MessageProtocol::Game,53);

			// Cmd: Save UGC content data
			constexpr MessageID MID_SaveUGCCmd(MessageType::Command,1,MessageProtocol::Game,54);
			constexpr MessageID MID_SaveUGCRes(MessageType::Result,1,MessageProtocol::Game,54);

			// Cmd: Request WhiteboardSharing
			constexpr MessageID MID_SearchUGCCmd(MessageType::Command,1,MessageProtocol::Game,55);
			constexpr MessageID MID_SearchUGCRes(MessageType::Result,1,MessageProtocol::Game,55);

			// Cmd: Get UGC content info, name, thumb image and so on
			constexpr MessageID MID_GetUGCContentInfoCmd(MessageType::Command,1,MessageProtocol::Game,56);
			constexpr MessageID MID_GetUGCContentInfoRes(MessageType::Result,1,MessageProtocol::Game,56);

			// Cmd: Request WhiteboardSharing
			constexpr MessageID MID_DownloadUGCContentCmd(MessageType::Command,1,MessageProtocol::Game,57);
			constexpr MessageID MID_DownloadUGCContentRes(MessageType::Result,1,MessageProtocol::Game,57);

			// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
			constexpr MessageID MID_RequestUGCZoneInstanceCmd(MessageType::Command,1,MessageProtocol::Game,58);
			constexpr MessageID MID_RequestUGCZoneInstanceRes(MessageType::Result,1,MessageProtocol::Game,58);

			// Cmd: Buy shop item prepare
			constexpr MessageID MID_BuyShopItemPrepareCmd(MessageType::Command,1,MessageProtocol::Game,59);
			constexpr MessageID MID_BuyShopItemPrepareRes(MessageType::Result,1,MessageProtocol::Game,59);

			// Cmd: Buy shop item
			constexpr MessageID MID_BuyShopItemCmd(MessageType::Command,1,MessageProtocol::Game,60);
			constexpr MessageID MID_BuyShopItemRes(MessageType::Result,1,MessageProtocol::Game,60);

			// Cmd: Create or Join Chat channel
			constexpr MessageID MID_CreateOrJoinChatChannelCmd(MessageType::Command,1,MessageProtocol::Game,61);
			constexpr MessageID MID_CreateOrJoinChatChannelRes(MessageType::Result,1,MessageProtocol::Game,61);

			// Cmd: Join
			constexpr MessageID MID_JoinChatChannelCmd(MessageType::Command,1,MessageProtocol::Game,62);
			constexpr MessageID MID_JoinChatChannelRes(MessageType::Result,1,MessageProtocol::Game,62);

			// S2C: Player Joined event
			constexpr MessageID MID_ChatChannelPlayerJoinedS2CEvt(MessageType::Event,1,MessageProtocol::Game,63);
			// S2C: ChatChannel leader changed event
			constexpr MessageID MID_ChatChannelLeaderChangedS2CEvt(MessageType::Event,1,MessageProtocol::Game,64);
			// Cmd: Leave ChatChannel command
			constexpr MessageID MID_LeaveChatChannelCmd(MessageType::Command,1,MessageProtocol::Game,65);
			constexpr MessageID MID_LeaveChatChannelRes(MessageType::Result,1,MessageProtocol::Game,65);

			// S2C: ChatChannel Player left event
			constexpr MessageID MID_ChatChannelPlayerLeftS2CEvt(MessageType::Event,1,MessageProtocol::Game,66);
			// Cmd: Kick player from the ChatChannel
			constexpr MessageID MID_ChatChannelKickPlayerCmd(MessageType::Command,1,MessageProtocol::Game,67);
			constexpr MessageID MID_ChatChannelKickPlayerRes(MessageType::Result,1,MessageProtocol::Game,67);

			// S2C: ChatChannel Player kicked message
			constexpr MessageID MID_ChatChannelPlayerKickedS2CEvt(MessageType::Event,1,MessageProtocol::Game,68);
			// Cmd: Chat channel sending chatting message
			constexpr MessageID MID_ChatChannelChatMessageCmd(MessageType::Command,1,MessageProtocol::Game,69);
			constexpr MessageID MID_ChatChannelChatMessageRes(MessageType::Result,1,MessageProtocol::Game,69);

			// S2C: ChatChannel Chatting message event
			constexpr MessageID MID_ChatChannelChatMessageS2CEvt(MessageType::Event,1,MessageProtocol::Game,70);
			// Cmd: Whisper(tell) other player chatting
			constexpr MessageID MID_WhisperMessageCmd(MessageType::Command,1,MessageProtocol::Game,71);
			constexpr MessageID MID_WhisperMessageRes(MessageType::Result,1,MessageProtocol::Game,71);

			// S2C: Other player whispered(tell) to me message event
			constexpr MessageID MID_WhisperMessageS2CEvt(MessageType::Event,1,MessageProtocol::Game,72);
			// Cmd: Create character
			constexpr MessageID MID_CreateCharacterCmd(MessageType::Command,1,MessageProtocol::Game,73);
			constexpr MessageID MID_CreateCharacterRes(MessageType::Result,1,MessageProtocol::Game,73);

			// Cmd: Delete character
			constexpr MessageID MID_DeleteCharacterCmd(MessageType::Command,1,MessageProtocol::Game,74);
			constexpr MessageID MID_DeleteCharacterRes(MessageType::Result,1,MessageProtocol::Game,74);

			// Cmd: Get character list
			constexpr MessageID MID_GetCharacterListCmd(MessageType::Command,1,MessageProtocol::Game,75);
			constexpr MessageID MID_GetCharacterListRes(MessageType::Result,1,MessageProtocol::Game,75);

			// Cmd: 
			constexpr MessageID MID_GetCharacterDataCmd(MessageType::Command,1,MessageProtocol::Game,76);
			constexpr MessageID MID_GetCharacterDataRes(MessageType::Result,1,MessageProtocol::Game,76);

			// Cmd: Select character
			constexpr MessageID MID_SelectCharacterCmd(MessageType::Command,1,MessageProtocol::Game,77);
			constexpr MessageID MID_SelectCharacterRes(MessageType::Result,1,MessageProtocol::Game,77);

			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			constexpr MessageID MID_RequestServerNoticeUpdateCmd(MessageType::Command,1,MessageProtocol::Game,78);
			constexpr MessageID MID_RequestServerNoticeUpdateRes(MessageType::Result,1,MessageProtocol::Game,78);

			// S2C: Server Notice updated event
			constexpr MessageID MID_ServerNoticeS2CEvt(MessageType::Event,1,MessageProtocol::Game,79);
			// Cmd: To call general functionality
			constexpr MessageID MID_CallFunctionCmd(MessageType::Command,1,MessageProtocol::Game,80);
			constexpr MessageID MID_CallFunctionRes(MessageType::Result,1,MessageProtocol::Game,80);



		} // namespace Game
	} // namespace Message
} // namespace SF



