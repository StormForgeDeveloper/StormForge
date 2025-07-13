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
			constexpr MessageID MID_HeartbeatC2SEvt(EMessageType::Event,1,MessageProtocol::Game,0);
			// Cmd: Player connected from a login server and moved to game server
			constexpr MessageID MID_JoinGameServerCmd(EMessageType::Command,1,MessageProtocol::Game,1);
			constexpr MessageID MID_JoinGameServerRes(EMessageType::Result,1,MessageProtocol::Game,1);

			// Cmd: player completion statues
			constexpr MessageID MID_GetAchievementStatsCmd(EMessageType::Command,1,MessageProtocol::Game,2);
			constexpr MessageID MID_GetAchievementStatsRes(EMessageType::Result,1,MessageProtocol::Game,2);

			// Cmd: Player complition state
			constexpr MessageID MID_Dummy1Cmd(EMessageType::Command,1,MessageProtocol::Game,3);
			constexpr MessageID MID_Dummy1Res(EMessageType::Result,1,MessageProtocol::Game,3);

			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			constexpr MessageID MID_RegisterGCMCmd(EMessageType::Command,1,MessageProtocol::Game,4);
			constexpr MessageID MID_RegisterGCMRes(EMessageType::Result,1,MessageProtocol::Game,4);

			// Cmd: Unregister Google notification service ID
			constexpr MessageID MID_UnregisterGCMCmd(EMessageType::Command,1,MessageProtocol::Game,5);
			constexpr MessageID MID_UnregisterGCMRes(EMessageType::Result,1,MessageProtocol::Game,5);

			// Cmd: Invite friend
			constexpr MessageID MID_InviteFriendCmd(EMessageType::Command,1,MessageProtocol::Game,6);
			constexpr MessageID MID_InviteFriendRes(EMessageType::Result,1,MessageProtocol::Game,6);

			// Cmd: Accept friend request
			constexpr MessageID MID_AcceptFriendRequestCmd(EMessageType::Command,1,MessageProtocol::Game,7);
			constexpr MessageID MID_AcceptFriendRequestRes(EMessageType::Result,1,MessageProtocol::Game,7);

			// S2C: Notification for friend request is accepted
			constexpr MessageID MID_FriendRequestAcceptedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,8);
			// Cmd: Remove friden form the friend list
			constexpr MessageID MID_RemoveFriendCmd(EMessageType::Command,1,MessageProtocol::Game,9);
			constexpr MessageID MID_RemoveFriendRes(EMessageType::Result,1,MessageProtocol::Game,9);

			// S2C: Friend removed
			constexpr MessageID MID_FriendRemovedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,10);
			// Cmd: Get friend list
			constexpr MessageID MID_GetFriendListCmd(EMessageType::Command,1,MessageProtocol::Game,11);
			constexpr MessageID MID_GetFriendListRes(EMessageType::Result,1,MessageProtocol::Game,11);

			// Cmd: Query notification list
			constexpr MessageID MID_GetNotificationListCmd(EMessageType::Command,1,MessageProtocol::Game,12);
			constexpr MessageID MID_GetNotificationListRes(EMessageType::Result,1,MessageProtocol::Game,12);

			// Cmd: Delete notification
			constexpr MessageID MID_DeleteNotificationCmd(EMessageType::Command,1,MessageProtocol::Game,13);
			constexpr MessageID MID_DeleteNotificationRes(EMessageType::Result,1,MessageProtocol::Game,13);

			// Cmd: Set notification is read
			constexpr MessageID MID_SetNotificationReadCmd(EMessageType::Command,1,MessageProtocol::Game,14);
			constexpr MessageID MID_SetNotificationReadRes(EMessageType::Result,1,MessageProtocol::Game,14);

			// Cmd: Accept notification
			constexpr MessageID MID_AcceptNotificationCmd(EMessageType::Command,1,MessageProtocol::Game,15);
			constexpr MessageID MID_AcceptNotificationRes(EMessageType::Result,1,MessageProtocol::Game,15);

			// S2C: Notify new notification
			constexpr MessageID MID_NotifyS2CEvt(EMessageType::Event,1,MessageProtocol::Game,16);
			// Cmd: PlayerId Conversion
			constexpr MessageID MID_FindPlayerByPlatformIdCmd(EMessageType::Command,1,MessageProtocol::Game,17);
			constexpr MessageID MID_FindPlayerByPlatformIdRes(EMessageType::Result,1,MessageProtocol::Game,17);

			// Cmd: PlayerId conversion
			constexpr MessageID MID_FindPlayerByCharacterNameCmd(EMessageType::Command,1,MessageProtocol::Game,18);
			constexpr MessageID MID_FindPlayerByCharacterNameRes(EMessageType::Result,1,MessageProtocol::Game,18);

			// Cmd: PlayerId Conversion
			constexpr MessageID MID_FindPlayerByPlatformUserNameCmd(EMessageType::Command,1,MessageProtocol::Game,19);
			constexpr MessageID MID_FindPlayerByPlatformUserNameRes(EMessageType::Result,1,MessageProtocol::Game,19);

			// Cmd: Query playerID list
			constexpr MessageID MID_FindPlayerByEMailCmd(EMessageType::Command,1,MessageProtocol::Game,20);
			constexpr MessageID MID_FindPlayerByEMailRes(EMessageType::Result,1,MessageProtocol::Game,20);

			// Cmd: Query playerID list
			constexpr MessageID MID_FindPlayerByPlayerIDCmd(EMessageType::Command,1,MessageProtocol::Game,21);
			constexpr MessageID MID_FindPlayerByPlayerIDRes(EMessageType::Result,1,MessageProtocol::Game,21);

			// Cmd: *Request Player Status Update
			constexpr MessageID MID_RequestPlayerStatusUpdateCmd(EMessageType::Command,1,MessageProtocol::Game,22);
			constexpr MessageID MID_RequestPlayerStatusUpdateRes(EMessageType::Result,1,MessageProtocol::Game,22);

			// S2C: *Notify Player Status Updated
			constexpr MessageID MID_NotifyPlayerStatusUpdatedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,23);
			// Cmd: Get Ranking list
			constexpr MessageID MID_GetRankingListCmd(EMessageType::Command,1,MessageProtocol::Game,24);
			constexpr MessageID MID_GetRankingListRes(EMessageType::Result,1,MessageProtocol::Game,24);

			// Cmd: Game user game play information
			constexpr MessageID MID_GetUserGamePlayerInfoCmd(EMessageType::Command,1,MessageProtocol::Game,25);
			constexpr MessageID MID_GetUserGamePlayerInfoRes(EMessageType::Result,1,MessageProtocol::Game,25);

			// Cmd: Game game play information
			constexpr MessageID MID_GetGamePlayerInfoCmd(EMessageType::Command,1,MessageProtocol::Game,26);
			constexpr MessageID MID_GetGamePlayerInfoRes(EMessageType::Result,1,MessageProtocol::Game,26);

			// S2C: Player level up event
			constexpr MessageID MID_LevelUpS2CEvt(EMessageType::Event,1,MessageProtocol::Game,27);
			// Cmd: Change NickName
			constexpr MessageID MID_SetNickNameCmd(EMessageType::Command,1,MessageProtocol::Game,28);
			constexpr MessageID MID_SetNickNameRes(EMessageType::Result,1,MessageProtocol::Game,28);

			// Cmd: Create Party
			constexpr MessageID MID_CreatePartyCmd(EMessageType::Command,1,MessageProtocol::Game,29);
			constexpr MessageID MID_CreatePartyRes(EMessageType::Result,1,MessageProtocol::Game,29);

			// Cmd: Join party
			constexpr MessageID MID_JoinPartyCmd(EMessageType::Command,1,MessageProtocol::Game,30);
			constexpr MessageID MID_JoinPartyRes(EMessageType::Result,1,MessageProtocol::Game,30);

			// S2C: Player Joined event
			constexpr MessageID MID_PartyPlayerJoinedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,31);
			// S2C: Party leader changed event
			constexpr MessageID MID_PartyLeaderChangedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,32);
			// Cmd: Leave party command
			constexpr MessageID MID_LeavePartyCmd(EMessageType::Command,1,MessageProtocol::Game,33);
			constexpr MessageID MID_LeavePartyRes(EMessageType::Result,1,MessageProtocol::Game,33);

			// S2C: Party Player left event
			constexpr MessageID MID_PartyPlayerLeftS2CEvt(EMessageType::Event,1,MessageProtocol::Game,34);
			// Cmd: Kick player from the party
			constexpr MessageID MID_PartyKickPlayerCmd(EMessageType::Command,1,MessageProtocol::Game,35);
			constexpr MessageID MID_PartyKickPlayerRes(EMessageType::Result,1,MessageProtocol::Game,35);

			// S2C: Party Player kicked message
			constexpr MessageID MID_PartyPlayerKickedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,36);
			// Cmd: Invite a player to the party
			constexpr MessageID MID_PartyInviteCmd(EMessageType::Command,1,MessageProtocol::Game,37);
			constexpr MessageID MID_PartyInviteRes(EMessageType::Result,1,MessageProtocol::Game,37);

			// S2C: Party invite requested
			constexpr MessageID MID_PartyInviteRequestedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,38);
			// Cmd: Send Party quick chat message
			constexpr MessageID MID_PartyQuickChatMessageCmd(EMessageType::Command,1,MessageProtocol::Game,39);
			constexpr MessageID MID_PartyQuickChatMessageRes(EMessageType::Result,1,MessageProtocol::Game,39);

			// S2C: Party Chatting message event
			constexpr MessageID MID_PartyQuickChatMessageS2CEvt(EMessageType::Event,1,MessageProtocol::Game,40);
			// Cmd: Party chatting
			constexpr MessageID MID_PartyChatMessageCmd(EMessageType::Command,1,MessageProtocol::Game,41);
			constexpr MessageID MID_PartyChatMessageRes(EMessageType::Result,1,MessageProtocol::Game,41);

			// S2C: Party Chatting message event
			constexpr MessageID MID_PartyChatMessageS2CEvt(EMessageType::Event,1,MessageProtocol::Game,42);
			// Cmd: Join to a game instance
			constexpr MessageID MID_RequestJoinGameInstanceCmd(EMessageType::Command,1,MessageProtocol::Game,43);
			constexpr MessageID MID_RequestJoinGameInstanceRes(EMessageType::Result,1,MessageProtocol::Game,43);

			// Cmd: Leave game instance
			constexpr MessageID MID_RequestLeaveGameInstanceCmd(EMessageType::Command,1,MessageProtocol::Game,44);
			constexpr MessageID MID_RequestLeaveGameInstanceRes(EMessageType::Result,1,MessageProtocol::Game,44);

			// Cmd: Search game instance. directory based search schema.    @SearchKeyword    - Static zone search with zone id: /ZoneInstance/Static/{ZoneTableID}/*    - Public UGC zone search for a player: /ZoneInstance/UGC/{PlayerID}/*   
			constexpr MessageID MID_SearchGameInstanceCmd(EMessageType::Command,1,MessageProtocol::Game,45);
			constexpr MessageID MID_SearchGameInstanceRes(EMessageType::Result,1,MessageProtocol::Game,45);

			// Cmd: Request Game match
			constexpr MessageID MID_RequestGameMatchCmd(EMessageType::Command,1,MessageProtocol::Game,46);
			constexpr MessageID MID_RequestGameMatchRes(EMessageType::Result,1,MessageProtocol::Game,46);

			// S2C: Game matched
			constexpr MessageID MID_GameMatchedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,47);
			// S2C: Game match failed
			constexpr MessageID MID_GameMatchFailedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,48);
			// S2C: Game matching started
			constexpr MessageID MID_GameMatchingStartedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,49);
			// Cmd: Cancel Game match
			constexpr MessageID MID_CancelGameMatchCmd(EMessageType::Command,1,MessageProtocol::Game,50);
			constexpr MessageID MID_CancelGameMatchRes(EMessageType::Result,1,MessageProtocol::Game,50);

			// S2C: game matching canceled
			constexpr MessageID MID_GameMatchingCanceledS2CEvt(EMessageType::Event,1,MessageProtocol::Game,51);
			// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
			constexpr MessageID MID_GetMyUGCGamesCmd(EMessageType::Command,1,MessageProtocol::Game,52);
			constexpr MessageID MID_GetMyUGCGamesRes(EMessageType::Result,1,MessageProtocol::Game,52);

			// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
			constexpr MessageID MID_RequestUGCGameInstanceCmd(EMessageType::Command,1,MessageProtocol::Game,53);
			constexpr MessageID MID_RequestUGCGameInstanceRes(EMessageType::Result,1,MessageProtocol::Game,53);

			// S2C: Requested instance is ready and can join
			constexpr MessageID MID_InstanceIsReadyS2CEvt(EMessageType::Event,1,MessageProtocol::Game,54);
			// Cmd: Request UGC template list
			constexpr MessageID MID_GetUGCTemplatesCmd(EMessageType::Command,1,MessageProtocol::Game,55);
			constexpr MessageID MID_GetUGCTemplatesRes(EMessageType::Result,1,MessageProtocol::Game,55);

			// Cmd: Upload UGC content data
			constexpr MessageID MID_UploadUGCCmd(EMessageType::Command,1,MessageProtocol::Game,56);
			constexpr MessageID MID_UploadUGCRes(EMessageType::Result,1,MessageProtocol::Game,56);

			// Cmd: Request WhiteboardSharing
			constexpr MessageID MID_SearchUGCCmd(EMessageType::Command,1,MessageProtocol::Game,57);
			constexpr MessageID MID_SearchUGCRes(EMessageType::Result,1,MessageProtocol::Game,57);

			// Cmd: Get UGC content info, name, thumb image and so on
			constexpr MessageID MID_GetUGCContentInfoCmd(EMessageType::Command,1,MessageProtocol::Game,58);
			constexpr MessageID MID_GetUGCContentInfoRes(EMessageType::Result,1,MessageProtocol::Game,58);

			// Cmd: Request WhiteboardSharing
			constexpr MessageID MID_DownloadUGCContentCmd(EMessageType::Command,1,MessageProtocol::Game,59);
			constexpr MessageID MID_DownloadUGCContentRes(EMessageType::Result,1,MessageProtocol::Game,59);

			// Cmd: Buy shop item prepare
			constexpr MessageID MID_BuyShopItemPrepareCmd(EMessageType::Command,1,MessageProtocol::Game,60);
			constexpr MessageID MID_BuyShopItemPrepareRes(EMessageType::Result,1,MessageProtocol::Game,60);

			// Cmd: Buy shop item
			constexpr MessageID MID_BuyShopItemCmd(EMessageType::Command,1,MessageProtocol::Game,61);
			constexpr MessageID MID_BuyShopItemRes(EMessageType::Result,1,MessageProtocol::Game,61);

			// Cmd: Create or Join Chat channel
			constexpr MessageID MID_CreateOrJoinChatChannelCmd(EMessageType::Command,1,MessageProtocol::Game,62);
			constexpr MessageID MID_CreateOrJoinChatChannelRes(EMessageType::Result,1,MessageProtocol::Game,62);

			// Cmd: Join
			constexpr MessageID MID_JoinChatChannelCmd(EMessageType::Command,1,MessageProtocol::Game,63);
			constexpr MessageID MID_JoinChatChannelRes(EMessageType::Result,1,MessageProtocol::Game,63);

			// S2C: Player Joined event
			constexpr MessageID MID_ChatChannelPlayerJoinedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,64);
			// S2C: ChatChannel leader changed event
			constexpr MessageID MID_ChatChannelLeaderChangedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,65);
			// Cmd: Leave ChatChannel command
			constexpr MessageID MID_LeaveChatChannelCmd(EMessageType::Command,1,MessageProtocol::Game,66);
			constexpr MessageID MID_LeaveChatChannelRes(EMessageType::Result,1,MessageProtocol::Game,66);

			// S2C: ChatChannel Player left event
			constexpr MessageID MID_ChatChannelPlayerLeftS2CEvt(EMessageType::Event,1,MessageProtocol::Game,67);
			// Cmd: Kick player from the ChatChannel
			constexpr MessageID MID_ChatChannelKickPlayerCmd(EMessageType::Command,1,MessageProtocol::Game,68);
			constexpr MessageID MID_ChatChannelKickPlayerRes(EMessageType::Result,1,MessageProtocol::Game,68);

			// S2C: ChatChannel Player kicked message
			constexpr MessageID MID_ChatChannelPlayerKickedS2CEvt(EMessageType::Event,1,MessageProtocol::Game,69);
			// Cmd: Chat channel sending chatting message
			constexpr MessageID MID_ChatChannelChatMessageCmd(EMessageType::Command,1,MessageProtocol::Game,70);
			constexpr MessageID MID_ChatChannelChatMessageRes(EMessageType::Result,1,MessageProtocol::Game,70);

			// S2C: ChatChannel Chatting message event
			constexpr MessageID MID_ChatChannelChatMessageS2CEvt(EMessageType::Event,1,MessageProtocol::Game,71);
			// Cmd: Whisper(tell) other player chatting
			constexpr MessageID MID_WhisperMessageCmd(EMessageType::Command,1,MessageProtocol::Game,72);
			constexpr MessageID MID_WhisperMessageRes(EMessageType::Result,1,MessageProtocol::Game,72);

			// S2C: Other player whispered(tell) to me message event
			constexpr MessageID MID_WhisperMessageS2CEvt(EMessageType::Event,1,MessageProtocol::Game,73);
			// Cmd: Create character
			constexpr MessageID MID_CreateCharacterCmd(EMessageType::Command,1,MessageProtocol::Game,74);
			constexpr MessageID MID_CreateCharacterRes(EMessageType::Result,1,MessageProtocol::Game,74);

			// Cmd: Delete character
			constexpr MessageID MID_DeleteCharacterCmd(EMessageType::Command,1,MessageProtocol::Game,75);
			constexpr MessageID MID_DeleteCharacterRes(EMessageType::Result,1,MessageProtocol::Game,75);

			// Cmd: Get character list
			constexpr MessageID MID_GetCharacterListCmd(EMessageType::Command,1,MessageProtocol::Game,76);
			constexpr MessageID MID_GetCharacterListRes(EMessageType::Result,1,MessageProtocol::Game,76);

			// Cmd: 
			constexpr MessageID MID_GetCharacterDataCmd(EMessageType::Command,1,MessageProtocol::Game,77);
			constexpr MessageID MID_GetCharacterDataRes(EMessageType::Result,1,MessageProtocol::Game,77);

			// Cmd: Select character
			constexpr MessageID MID_SelectCharacterCmd(EMessageType::Command,1,MessageProtocol::Game,78);
			constexpr MessageID MID_SelectCharacterRes(EMessageType::Result,1,MessageProtocol::Game,78);

			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			constexpr MessageID MID_RequestServerNoticeUpdateCmd(EMessageType::Command,1,MessageProtocol::Game,79);
			constexpr MessageID MID_RequestServerNoticeUpdateRes(EMessageType::Result,1,MessageProtocol::Game,79);

			// S2C: Server Notice updated event
			constexpr MessageID MID_ServerNoticeS2CEvt(EMessageType::Event,1,MessageProtocol::Game,80);
			// Cmd: To call general functionality
			constexpr MessageID MID_CallFunctionCmd(EMessageType::Command,1,MessageProtocol::Game,81);
			constexpr MessageID MID_CallFunctionRes(EMessageType::Result,1,MessageProtocol::Game,81);



		} // namespace Game
	} // namespace Message
} // namespace SF



