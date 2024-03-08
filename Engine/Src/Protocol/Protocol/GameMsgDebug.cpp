////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Game Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/GameMsgDebug.h"
#include "Protocol/GameMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Game Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceGame()
		{
 			// C2S: Client heartbeat
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::HeartbeatC2SEvt::MID.ID,&Message::Game::HeartbeatC2SEvt::TraceOut));
			// Cmd: Player connected from a login server and moved to game server
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameServerCmd::MID.ID,&Message::Game::JoinGameServerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameServerRes::MID.ID,&Message::Game::JoinGameServerRes::TraceOut));
			// Cmd: player complition statues
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetAchievementStatsCmd::MID.ID,&Message::Game::GetAchievementStatsCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetAchievementStatsRes::MID.ID,&Message::Game::GetAchievementStatsRes::TraceOut));
			// Cmd: Player complition state
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::Dummy1Cmd::MID.ID,&Message::Game::Dummy1Cmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::Dummy1Res::MID.ID,&Message::Game::Dummy1Res::TraceOut));
			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RegisterGCMCmd::MID.ID,&Message::Game::RegisterGCMCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RegisterGCMRes::MID.ID,&Message::Game::RegisterGCMRes::TraceOut));
			// Cmd: Unregister Google notification service ID
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::UnregisterGCMCmd::MID.ID,&Message::Game::UnregisterGCMCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::UnregisterGCMRes::MID.ID,&Message::Game::UnregisterGCMRes::TraceOut));
			// Cmd: Invite friend
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::InviteFriendCmd::MID.ID,&Message::Game::InviteFriendCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::InviteFriendRes::MID.ID,&Message::Game::InviteFriendRes::TraceOut));
			// Cmd: Accept friend request
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptFriendRequestCmd::MID.ID,&Message::Game::AcceptFriendRequestCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptFriendRequestRes::MID.ID,&Message::Game::AcceptFriendRequestRes::TraceOut));
			// S2C: Notification for friend request is accepted
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FriendRequestAcceptedS2CEvt::MID.ID,&Message::Game::FriendRequestAcceptedS2CEvt::TraceOut));
			// Cmd: Remove friden form the friend list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RemoveFriendCmd::MID.ID,&Message::Game::RemoveFriendCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RemoveFriendRes::MID.ID,&Message::Game::RemoveFriendRes::TraceOut));
			// S2C: Friend removed
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FriendRemovedS2CEvt::MID.ID,&Message::Game::FriendRemovedS2CEvt::TraceOut));
			// Cmd: Get friend list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetFriendListCmd::MID.ID,&Message::Game::GetFriendListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetFriendListRes::MID.ID,&Message::Game::GetFriendListRes::TraceOut));
			// Cmd: Query notification list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetNotificationListCmd::MID.ID,&Message::Game::GetNotificationListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetNotificationListRes::MID.ID,&Message::Game::GetNotificationListRes::TraceOut));
			// Cmd: Delete notification
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DeleteNotificationCmd::MID.ID,&Message::Game::DeleteNotificationCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DeleteNotificationRes::MID.ID,&Message::Game::DeleteNotificationRes::TraceOut));
			// Cmd: Set notification is read
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNotificationReadCmd::MID.ID,&Message::Game::SetNotificationReadCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNotificationReadRes::MID.ID,&Message::Game::SetNotificationReadRes::TraceOut));
			// Cmd: Accept notification
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptNotificationCmd::MID.ID,&Message::Game::AcceptNotificationCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptNotificationRes::MID.ID,&Message::Game::AcceptNotificationRes::TraceOut));
			// S2C: Notify new notification
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::NotifyS2CEvt::MID.ID,&Message::Game::NotifyS2CEvt::TraceOut));
			// Cmd: PlayerId Conversion
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformIdCmd::MID.ID,&Message::Game::FindPlayerByPlatformIdCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformIdRes::MID.ID,&Message::Game::FindPlayerByPlatformIdRes::TraceOut));
			// Cmd: PlayerId conversion
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByCharacterNameCmd::MID.ID,&Message::Game::FindPlayerByCharacterNameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByCharacterNameRes::MID.ID,&Message::Game::FindPlayerByCharacterNameRes::TraceOut));
			// Cmd: PlayerId Conversion
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformUserNameCmd::MID.ID,&Message::Game::FindPlayerByPlatformUserNameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformUserNameRes::MID.ID,&Message::Game::FindPlayerByPlatformUserNameRes::TraceOut));
			// Cmd: Query playerID list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByEMailCmd::MID.ID,&Message::Game::FindPlayerByEMailCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByEMailRes::MID.ID,&Message::Game::FindPlayerByEMailRes::TraceOut));
			// Cmd: Query playerID list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDCmd::MID.ID,&Message::Game::FindPlayerByPlayerIDCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDRes::MID.ID,&Message::Game::FindPlayerByPlayerIDRes::TraceOut));
			// Cmd: *Request Player Status Update
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateCmd::MID.ID,&Message::Game::RequestPlayerStatusUpdateCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateRes::MID.ID,&Message::Game::RequestPlayerStatusUpdateRes::TraceOut));
			// S2C: *Notify Player Status Updated
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.ID,&Message::Game::NotifyPlayerStatusUpdatedS2CEvt::TraceOut));
			// Cmd: Get Ranking list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetRankingListCmd::MID.ID,&Message::Game::GetRankingListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetRankingListRes::MID.ID,&Message::Game::GetRankingListRes::TraceOut));
			// Cmd: Game user game play information
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoCmd::MID.ID,&Message::Game::GetUserGamePlayerInfoCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoRes::MID.ID,&Message::Game::GetUserGamePlayerInfoRes::TraceOut));
			// Cmd: Game game play information
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoCmd::MID.ID,&Message::Game::GetGamePlayerInfoCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoRes::MID.ID,&Message::Game::GetGamePlayerInfoRes::TraceOut));
			// S2C: Player level up event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LevelUpS2CEvt::MID.ID,&Message::Game::LevelUpS2CEvt::TraceOut));
			// Cmd: Change NickName
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNickNameCmd::MID.ID,&Message::Game::SetNickNameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNickNameRes::MID.ID,&Message::Game::SetNickNameRes::TraceOut));
			// Cmd: Create Party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreatePartyCmd::MID.ID,&Message::Game::CreatePartyCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreatePartyRes::MID.ID,&Message::Game::CreatePartyRes::TraceOut));
			// Cmd: Join party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinPartyCmd::MID.ID,&Message::Game::JoinPartyCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinPartyRes::MID.ID,&Message::Game::JoinPartyRes::TraceOut));
			// S2C: Player Joined event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyPlayerJoinedS2CEvt::MID.ID,&Message::Game::PartyPlayerJoinedS2CEvt::TraceOut));
			// S2C: Party leader changed event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyLeaderChangedS2CEvt::MID.ID,&Message::Game::PartyLeaderChangedS2CEvt::TraceOut));
			// Cmd: Leave party command
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeavePartyCmd::MID.ID,&Message::Game::LeavePartyCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeavePartyRes::MID.ID,&Message::Game::LeavePartyRes::TraceOut));
			// S2C: Party Player left event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyPlayerLeftS2CEvt::MID.ID,&Message::Game::PartyPlayerLeftS2CEvt::TraceOut));
			// Cmd: Kick player from the party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyKickPlayerCmd::MID.ID,&Message::Game::PartyKickPlayerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyKickPlayerRes::MID.ID,&Message::Game::PartyKickPlayerRes::TraceOut));
			// S2C: Party Player kicked message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyPlayerKickedS2CEvt::MID.ID,&Message::Game::PartyPlayerKickedS2CEvt::TraceOut));
			// Cmd: Invite a player to the party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyInviteCmd::MID.ID,&Message::Game::PartyInviteCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyInviteRes::MID.ID,&Message::Game::PartyInviteRes::TraceOut));
			// S2C: Party invite requested
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyInviteRequestedS2CEvt::MID.ID,&Message::Game::PartyInviteRequestedS2CEvt::TraceOut));
			// Cmd: Send Party quick chat message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageCmd::MID.ID,&Message::Game::PartyQuickChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageRes::MID.ID,&Message::Game::PartyQuickChatMessageRes::TraceOut));
			// S2C: Party Chatting message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageS2CEvt::MID.ID,&Message::Game::PartyQuickChatMessageS2CEvt::TraceOut));
			// Cmd: Party chatting
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyChatMessageCmd::MID.ID,&Message::Game::PartyChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyChatMessageRes::MID.ID,&Message::Game::PartyChatMessageRes::TraceOut));
			// S2C: Party Chatting message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyChatMessageS2CEvt::MID.ID,&Message::Game::PartyChatMessageS2CEvt::TraceOut));
			// Cmd: Join to a game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameInstanceCmd::MID.ID,&Message::Game::JoinGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameInstanceRes::MID.ID,&Message::Game::JoinGameInstanceRes::TraceOut));
			// Cmd: Leave game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveGameInstanceCmd::MID.ID,&Message::Game::LeaveGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveGameInstanceRes::MID.ID,&Message::Game::LeaveGameInstanceRes::TraceOut));
			// Cmd: Search game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SearchGameInstanceCmd::MID.ID,&Message::Game::SearchGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SearchGameInstanceRes::MID.ID,&Message::Game::SearchGameInstanceRes::TraceOut));
			// Cmd: Search game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceCmd::MID.ID,&Message::Game::GetCharacterDataInGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceRes::MID.ID,&Message::Game::GetCharacterDataInGameInstanceRes::TraceOut));
			// Cmd: Request Game match
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestGameMatchCmd::MID.ID,&Message::Game::RequestGameMatchCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestGameMatchRes::MID.ID,&Message::Game::RequestGameMatchRes::TraceOut));
			// S2C: Game matched
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchedS2CEvt::MID.ID,&Message::Game::GameMatchedS2CEvt::TraceOut));
			// S2C: Game match failed
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchFailedS2CEvt::MID.ID,&Message::Game::GameMatchFailedS2CEvt::TraceOut));
			// S2C: Game matching started
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchingStartedS2CEvt::MID.ID,&Message::Game::GameMatchingStartedS2CEvt::TraceOut));
			// Cmd: Cancel Game match
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CancelGameMatchCmd::MID.ID,&Message::Game::CancelGameMatchCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CancelGameMatchRes::MID.ID,&Message::Game::CancelGameMatchRes::TraceOut));
			// S2C: game matching canceled
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchingCanceledS2CEvt::MID.ID,&Message::Game::GameMatchingCanceledS2CEvt::TraceOut));
			// Cmd: Request UGC template list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUGCTemplatesCmd::MID.ID,&Message::Game::GetUGCTemplatesCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUGCTemplatesRes::MID.ID,&Message::Game::GetUGCTemplatesRes::TraceOut));
			// Cmd: Save UGC content data
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SaveUGCCmd::MID.ID,&Message::Game::SaveUGCCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SaveUGCRes::MID.ID,&Message::Game::SaveUGCRes::TraceOut));
			// Cmd: Request WhiteboardSharing
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SearchUGCCmd::MID.ID,&Message::Game::SearchUGCCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SearchUGCRes::MID.ID,&Message::Game::SearchUGCRes::TraceOut));
			// Cmd: Get UGC content info, name, thumb image and so on
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUGCContentInfoCmd::MID.ID,&Message::Game::GetUGCContentInfoCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUGCContentInfoRes::MID.ID,&Message::Game::GetUGCContentInfoRes::TraceOut));
			// Cmd: Request WhiteboardSharing
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DownloadUGCContentCmd::MID.ID,&Message::Game::DownloadUGCContentCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DownloadUGCContentRes::MID.ID,&Message::Game::DownloadUGCContentRes::TraceOut));
			// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestUGCZoneInstanceCmd::MID.ID,&Message::Game::RequestUGCZoneInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestUGCZoneInstanceRes::MID.ID,&Message::Game::RequestUGCZoneInstanceRes::TraceOut));
			// Cmd: Buy shop item prepare
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareCmd::MID.ID,&Message::Game::BuyShopItemPrepareCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareRes::MID.ID,&Message::Game::BuyShopItemPrepareRes::TraceOut));
			// Cmd: Buy shop item
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemCmd::MID.ID,&Message::Game::BuyShopItemCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemRes::MID.ID,&Message::Game::BuyShopItemRes::TraceOut));
			// Cmd: Create or Join Chat channel
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelCmd::MID.ID,&Message::Game::CreateOrJoinChatChannelCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelRes::MID.ID,&Message::Game::CreateOrJoinChatChannelRes::TraceOut));
			// Cmd: Join
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinChatChannelCmd::MID.ID,&Message::Game::JoinChatChannelCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinChatChannelRes::MID.ID,&Message::Game::JoinChatChannelRes::TraceOut));
			// S2C: Player Joined event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerJoinedS2CEvt::TraceOut));
			// S2C: ChatChannel leader changed event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelLeaderChangedS2CEvt::MID.ID,&Message::Game::ChatChannelLeaderChangedS2CEvt::TraceOut));
			// Cmd: Leave ChatChannel command
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveChatChannelCmd::MID.ID,&Message::Game::LeaveChatChannelCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveChatChannelRes::MID.ID,&Message::Game::LeaveChatChannelRes::TraceOut));
			// S2C: ChatChannel Player left event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelPlayerLeftS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerLeftS2CEvt::TraceOut));
			// Cmd: Kick player from the ChatChannel
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerCmd::MID.ID,&Message::Game::ChatChannelKickPlayerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerRes::MID.ID,&Message::Game::ChatChannelKickPlayerRes::TraceOut));
			// S2C: ChatChannel Player kicked message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelPlayerKickedS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerKickedS2CEvt::TraceOut));
			// Cmd: Chat channel sending chatting message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageCmd::MID.ID,&Message::Game::ChatChannelChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageRes::MID.ID,&Message::Game::ChatChannelChatMessageRes::TraceOut));
			// S2C: ChatChannel Chatting message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageS2CEvt::MID.ID,&Message::Game::ChatChannelChatMessageS2CEvt::TraceOut));
			// Cmd: Whisper(tell) other player chatting
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::WhisperMessageCmd::MID.ID,&Message::Game::WhisperMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::WhisperMessageRes::MID.ID,&Message::Game::WhisperMessageRes::TraceOut));
			// S2C: Other player whispered(tell) to me message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::WhisperMessageS2CEvt::MID.ID,&Message::Game::WhisperMessageS2CEvt::TraceOut));
			// Cmd: Create character
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateCharacterCmd::MID.ID,&Message::Game::CreateCharacterCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateCharacterRes::MID.ID,&Message::Game::CreateCharacterRes::TraceOut));
			// Cmd: Delete character
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DeleteCharacterCmd::MID.ID,&Message::Game::DeleteCharacterCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DeleteCharacterRes::MID.ID,&Message::Game::DeleteCharacterRes::TraceOut));
			// Cmd: Get character list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterListCmd::MID.ID,&Message::Game::GetCharacterListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterListRes::MID.ID,&Message::Game::GetCharacterListRes::TraceOut));
			// Cmd: 
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataCmd::MID.ID,&Message::Game::GetCharacterDataCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataRes::MID.ID,&Message::Game::GetCharacterDataRes::TraceOut));
			// Cmd: Select character
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SelectCharacterCmd::MID.ID,&Message::Game::SelectCharacterCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SelectCharacterRes::MID.ID,&Message::Game::SelectCharacterRes::TraceOut));
			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestServerNoticeUpdateCmd::MID.ID,&Message::Game::RequestServerNoticeUpdateCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestServerNoticeUpdateRes::MID.ID,&Message::Game::RequestServerNoticeUpdateRes::TraceOut));
			// S2C: Server Notice updated event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ServerNoticeS2CEvt::MID.ID,&Message::Game::ServerNoticeS2CEvt::TraceOut));
			// Cmd: To call general functionality
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CallFunctionCmd::MID.ID,&Message::Game::CallFunctionCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CallFunctionRes::MID.ID,&Message::Game::CallFunctionRes::TraceOut));
		}; // void RegisterDebugTraceGame()


	}; // namespace Protocol
}; // namespace SF


