////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Game Message parsing implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/GameMsgParsing.h"
#include "Protocol/GameMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 
		///////////////////////////////////////////////////////////////
		// Game message parser mapping

		extern std::unordered_map<uint32_t,HandleParseMessageTo> MessageParseToVariableMap;
		extern std::unordered_map<uint32_t,HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

		void RegisterParserGame()
		{
 			// C2S: Client heartbeat
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::HeartbeatC2SEvt::MID.ID,&Message::Game::HeartbeatC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::HeartbeatC2SEvt::MID.ID,&Message::Game::HeartbeatC2SEvt::ParseMessageToMessageBase));
			// Cmd: Player connected from a login server and moved to game server
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameServerCmd::MID.ID,&Message::Game::JoinGameServerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameServerCmd::MID.ID,&Message::Game::JoinGameServerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameServerRes::MID.ID,&Message::Game::JoinGameServerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameServerRes::MID.ID,&Message::Game::JoinGameServerRes::ParseMessageToMessageBase));
			// Cmd: player complition statues
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetAchievementStatsCmd::MID.ID,&Message::Game::GetAchievementStatsCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetAchievementStatsCmd::MID.ID,&Message::Game::GetAchievementStatsCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetAchievementStatsRes::MID.ID,&Message::Game::GetAchievementStatsRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetAchievementStatsRes::MID.ID,&Message::Game::GetAchievementStatsRes::ParseMessageToMessageBase));
			// Cmd: Player complition state
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::Dummy1Cmd::MID.ID,&Message::Game::Dummy1Cmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::Dummy1Cmd::MID.ID,&Message::Game::Dummy1Cmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::Dummy1Res::MID.ID,&Message::Game::Dummy1Res::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::Dummy1Res::MID.ID,&Message::Game::Dummy1Res::ParseMessageToMessageBase));
			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RegisterGCMCmd::MID.ID,&Message::Game::RegisterGCMCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RegisterGCMCmd::MID.ID,&Message::Game::RegisterGCMCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RegisterGCMRes::MID.ID,&Message::Game::RegisterGCMRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RegisterGCMRes::MID.ID,&Message::Game::RegisterGCMRes::ParseMessageToMessageBase));
			// Cmd: Unregister Google notification service ID
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::UnregisterGCMCmd::MID.ID,&Message::Game::UnregisterGCMCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::UnregisterGCMCmd::MID.ID,&Message::Game::UnregisterGCMCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::UnregisterGCMRes::MID.ID,&Message::Game::UnregisterGCMRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::UnregisterGCMRes::MID.ID,&Message::Game::UnregisterGCMRes::ParseMessageToMessageBase));
			// Cmd: Invite friend
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::InviteFriendCmd::MID.ID,&Message::Game::InviteFriendCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::InviteFriendCmd::MID.ID,&Message::Game::InviteFriendCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::InviteFriendRes::MID.ID,&Message::Game::InviteFriendRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::InviteFriendRes::MID.ID,&Message::Game::InviteFriendRes::ParseMessageToMessageBase));
			// Cmd: Accept friend request
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptFriendRequestCmd::MID.ID,&Message::Game::AcceptFriendRequestCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptFriendRequestCmd::MID.ID,&Message::Game::AcceptFriendRequestCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptFriendRequestRes::MID.ID,&Message::Game::AcceptFriendRequestRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptFriendRequestRes::MID.ID,&Message::Game::AcceptFriendRequestRes::ParseMessageToMessageBase));
			// S2C: Notification for friend request is accepted
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FriendRequestAcceptedS2CEvt::MID.ID,&Message::Game::FriendRequestAcceptedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FriendRequestAcceptedS2CEvt::MID.ID,&Message::Game::FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Remove friden form the friend list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RemoveFriendCmd::MID.ID,&Message::Game::RemoveFriendCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RemoveFriendCmd::MID.ID,&Message::Game::RemoveFriendCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RemoveFriendRes::MID.ID,&Message::Game::RemoveFriendRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RemoveFriendRes::MID.ID,&Message::Game::RemoveFriendRes::ParseMessageToMessageBase));
			// S2C: Friend removed
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FriendRemovedS2CEvt::MID.ID,&Message::Game::FriendRemovedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FriendRemovedS2CEvt::MID.ID,&Message::Game::FriendRemovedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Get friend list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetFriendListCmd::MID.ID,&Message::Game::GetFriendListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetFriendListCmd::MID.ID,&Message::Game::GetFriendListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetFriendListRes::MID.ID,&Message::Game::GetFriendListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetFriendListRes::MID.ID,&Message::Game::GetFriendListRes::ParseMessageToMessageBase));
			// Cmd: Query notification list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetNotificationListCmd::MID.ID,&Message::Game::GetNotificationListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetNotificationListCmd::MID.ID,&Message::Game::GetNotificationListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetNotificationListRes::MID.ID,&Message::Game::GetNotificationListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetNotificationListRes::MID.ID,&Message::Game::GetNotificationListRes::ParseMessageToMessageBase));
			// Cmd: Delete notification
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DeleteNotificationCmd::MID.ID,&Message::Game::DeleteNotificationCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DeleteNotificationCmd::MID.ID,&Message::Game::DeleteNotificationCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DeleteNotificationRes::MID.ID,&Message::Game::DeleteNotificationRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DeleteNotificationRes::MID.ID,&Message::Game::DeleteNotificationRes::ParseMessageToMessageBase));
			// Cmd: Set notification is read
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNotificationReadCmd::MID.ID,&Message::Game::SetNotificationReadCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNotificationReadCmd::MID.ID,&Message::Game::SetNotificationReadCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNotificationReadRes::MID.ID,&Message::Game::SetNotificationReadRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNotificationReadRes::MID.ID,&Message::Game::SetNotificationReadRes::ParseMessageToMessageBase));
			// Cmd: Accept notification
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptNotificationCmd::MID.ID,&Message::Game::AcceptNotificationCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptNotificationCmd::MID.ID,&Message::Game::AcceptNotificationCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptNotificationRes::MID.ID,&Message::Game::AcceptNotificationRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptNotificationRes::MID.ID,&Message::Game::AcceptNotificationRes::ParseMessageToMessageBase));
			// S2C: Notify new notification
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::NotifyS2CEvt::MID.ID,&Message::Game::NotifyS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::NotifyS2CEvt::MID.ID,&Message::Game::NotifyS2CEvt::ParseMessageToMessageBase));
			// Cmd: PlayerId Conversion
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformIdCmd::MID.ID,&Message::Game::FindPlayerByPlatformIdCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformIdCmd::MID.ID,&Message::Game::FindPlayerByPlatformIdCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformIdRes::MID.ID,&Message::Game::FindPlayerByPlatformIdRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformIdRes::MID.ID,&Message::Game::FindPlayerByPlatformIdRes::ParseMessageToMessageBase));
			// Cmd: PlayerId conversion
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByCharacterNameCmd::MID.ID,&Message::Game::FindPlayerByCharacterNameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByCharacterNameCmd::MID.ID,&Message::Game::FindPlayerByCharacterNameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByCharacterNameRes::MID.ID,&Message::Game::FindPlayerByCharacterNameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByCharacterNameRes::MID.ID,&Message::Game::FindPlayerByCharacterNameRes::ParseMessageToMessageBase));
			// Cmd: PlayerId Conversion
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformUserNameCmd::MID.ID,&Message::Game::FindPlayerByPlatformUserNameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformUserNameCmd::MID.ID,&Message::Game::FindPlayerByPlatformUserNameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformUserNameRes::MID.ID,&Message::Game::FindPlayerByPlatformUserNameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlatformUserNameRes::MID.ID,&Message::Game::FindPlayerByPlatformUserNameRes::ParseMessageToMessageBase));
			// Cmd: Query playerID list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByEMailCmd::MID.ID,&Message::Game::FindPlayerByEMailCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByEMailCmd::MID.ID,&Message::Game::FindPlayerByEMailCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByEMailRes::MID.ID,&Message::Game::FindPlayerByEMailRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByEMailRes::MID.ID,&Message::Game::FindPlayerByEMailRes::ParseMessageToMessageBase));
			// Cmd: Query playerID list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDCmd::MID.ID,&Message::Game::FindPlayerByPlayerIDCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDCmd::MID.ID,&Message::Game::FindPlayerByPlayerIDCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDRes::MID.ID,&Message::Game::FindPlayerByPlayerIDRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDRes::MID.ID,&Message::Game::FindPlayerByPlayerIDRes::ParseMessageToMessageBase));
			// Cmd: *Request Player Status Update
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateCmd::MID.ID,&Message::Game::RequestPlayerStatusUpdateCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateCmd::MID.ID,&Message::Game::RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateRes::MID.ID,&Message::Game::RequestPlayerStatusUpdateRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateRes::MID.ID,&Message::Game::RequestPlayerStatusUpdateRes::ParseMessageToMessageBase));
			// S2C: *Notify Player Status Updated
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.ID,&Message::Game::NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.ID,&Message::Game::NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Get Ranking list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetRankingListCmd::MID.ID,&Message::Game::GetRankingListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetRankingListCmd::MID.ID,&Message::Game::GetRankingListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetRankingListRes::MID.ID,&Message::Game::GetRankingListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetRankingListRes::MID.ID,&Message::Game::GetRankingListRes::ParseMessageToMessageBase));
			// Cmd: Game user game play information
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoCmd::MID.ID,&Message::Game::GetUserGamePlayerInfoCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoCmd::MID.ID,&Message::Game::GetUserGamePlayerInfoCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoRes::MID.ID,&Message::Game::GetUserGamePlayerInfoRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoRes::MID.ID,&Message::Game::GetUserGamePlayerInfoRes::ParseMessageToMessageBase));
			// Cmd: Game game play information
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoCmd::MID.ID,&Message::Game::GetGamePlayerInfoCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoCmd::MID.ID,&Message::Game::GetGamePlayerInfoCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoRes::MID.ID,&Message::Game::GetGamePlayerInfoRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoRes::MID.ID,&Message::Game::GetGamePlayerInfoRes::ParseMessageToMessageBase));
			// S2C: Player level up event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LevelUpS2CEvt::MID.ID,&Message::Game::LevelUpS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LevelUpS2CEvt::MID.ID,&Message::Game::LevelUpS2CEvt::ParseMessageToMessageBase));
			// Cmd: Change NickName
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNickNameCmd::MID.ID,&Message::Game::SetNickNameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNickNameCmd::MID.ID,&Message::Game::SetNickNameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNickNameRes::MID.ID,&Message::Game::SetNickNameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNickNameRes::MID.ID,&Message::Game::SetNickNameRes::ParseMessageToMessageBase));
			// Cmd: Create Party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreatePartyCmd::MID.ID,&Message::Game::CreatePartyCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreatePartyCmd::MID.ID,&Message::Game::CreatePartyCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreatePartyRes::MID.ID,&Message::Game::CreatePartyRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreatePartyRes::MID.ID,&Message::Game::CreatePartyRes::ParseMessageToMessageBase));
			// Cmd: Join party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinPartyCmd::MID.ID,&Message::Game::JoinPartyCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinPartyCmd::MID.ID,&Message::Game::JoinPartyCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinPartyRes::MID.ID,&Message::Game::JoinPartyRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinPartyRes::MID.ID,&Message::Game::JoinPartyRes::ParseMessageToMessageBase));
			// S2C: Player Joined event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyPlayerJoinedS2CEvt::MID.ID,&Message::Game::PartyPlayerJoinedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyPlayerJoinedS2CEvt::MID.ID,&Message::Game::PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase));
			// S2C: Party leader changed event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyLeaderChangedS2CEvt::MID.ID,&Message::Game::PartyLeaderChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyLeaderChangedS2CEvt::MID.ID,&Message::Game::PartyLeaderChangedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Leave party command
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeavePartyCmd::MID.ID,&Message::Game::LeavePartyCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeavePartyCmd::MID.ID,&Message::Game::LeavePartyCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeavePartyRes::MID.ID,&Message::Game::LeavePartyRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeavePartyRes::MID.ID,&Message::Game::LeavePartyRes::ParseMessageToMessageBase));
			// S2C: Party Player left event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyPlayerLeftS2CEvt::MID.ID,&Message::Game::PartyPlayerLeftS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyPlayerLeftS2CEvt::MID.ID,&Message::Game::PartyPlayerLeftS2CEvt::ParseMessageToMessageBase));
			// Cmd: Kick player from the party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyKickPlayerCmd::MID.ID,&Message::Game::PartyKickPlayerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyKickPlayerCmd::MID.ID,&Message::Game::PartyKickPlayerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyKickPlayerRes::MID.ID,&Message::Game::PartyKickPlayerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyKickPlayerRes::MID.ID,&Message::Game::PartyKickPlayerRes::ParseMessageToMessageBase));
			// S2C: Party Player kicked message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyPlayerKickedS2CEvt::MID.ID,&Message::Game::PartyPlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyPlayerKickedS2CEvt::MID.ID,&Message::Game::PartyPlayerKickedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Invite a player to the party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyInviteCmd::MID.ID,&Message::Game::PartyInviteCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyInviteCmd::MID.ID,&Message::Game::PartyInviteCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyInviteRes::MID.ID,&Message::Game::PartyInviteRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyInviteRes::MID.ID,&Message::Game::PartyInviteRes::ParseMessageToMessageBase));
			// S2C: Party invite requested
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyInviteRequestedS2CEvt::MID.ID,&Message::Game::PartyInviteRequestedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyInviteRequestedS2CEvt::MID.ID,&Message::Game::PartyInviteRequestedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Send Party quick chat message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageCmd::MID.ID,&Message::Game::PartyQuickChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageCmd::MID.ID,&Message::Game::PartyQuickChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageRes::MID.ID,&Message::Game::PartyQuickChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageRes::MID.ID,&Message::Game::PartyQuickChatMessageRes::ParseMessageToMessageBase));
			// S2C: Party Chatting message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageS2CEvt::MID.ID,&Message::Game::PartyQuickChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageS2CEvt::MID.ID,&Message::Game::PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Party chatting
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyChatMessageCmd::MID.ID,&Message::Game::PartyChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyChatMessageCmd::MID.ID,&Message::Game::PartyChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyChatMessageRes::MID.ID,&Message::Game::PartyChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyChatMessageRes::MID.ID,&Message::Game::PartyChatMessageRes::ParseMessageToMessageBase));
			// S2C: Party Chatting message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyChatMessageS2CEvt::MID.ID,&Message::Game::PartyChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyChatMessageS2CEvt::MID.ID,&Message::Game::PartyChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Join to a game instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameInstanceCmd::MID.ID,&Message::Game::JoinGameInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameInstanceCmd::MID.ID,&Message::Game::JoinGameInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameInstanceRes::MID.ID,&Message::Game::JoinGameInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameInstanceRes::MID.ID,&Message::Game::JoinGameInstanceRes::ParseMessageToMessageBase));
			// Cmd: Leave game instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveGameInstanceCmd::MID.ID,&Message::Game::LeaveGameInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveGameInstanceCmd::MID.ID,&Message::Game::LeaveGameInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveGameInstanceRes::MID.ID,&Message::Game::LeaveGameInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveGameInstanceRes::MID.ID,&Message::Game::LeaveGameInstanceRes::ParseMessageToMessageBase));
			// Cmd: Search game instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SearchGameInstanceCmd::MID.ID,&Message::Game::SearchGameInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SearchGameInstanceCmd::MID.ID,&Message::Game::SearchGameInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SearchGameInstanceRes::MID.ID,&Message::Game::SearchGameInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SearchGameInstanceRes::MID.ID,&Message::Game::SearchGameInstanceRes::ParseMessageToMessageBase));
			// Cmd: Search game instance
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceCmd::MID.ID,&Message::Game::GetCharacterDataInGameInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceCmd::MID.ID,&Message::Game::GetCharacterDataInGameInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceRes::MID.ID,&Message::Game::GetCharacterDataInGameInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceRes::MID.ID,&Message::Game::GetCharacterDataInGameInstanceRes::ParseMessageToMessageBase));
			// Cmd: Request Game match
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestGameMatchCmd::MID.ID,&Message::Game::RequestGameMatchCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestGameMatchCmd::MID.ID,&Message::Game::RequestGameMatchCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestGameMatchRes::MID.ID,&Message::Game::RequestGameMatchRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestGameMatchRes::MID.ID,&Message::Game::RequestGameMatchRes::ParseMessageToMessageBase));
			// S2C: Game matched
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchedS2CEvt::MID.ID,&Message::Game::GameMatchedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchedS2CEvt::MID.ID,&Message::Game::GameMatchedS2CEvt::ParseMessageToMessageBase));
			// S2C: Game match failed
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchFailedS2CEvt::MID.ID,&Message::Game::GameMatchFailedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchFailedS2CEvt::MID.ID,&Message::Game::GameMatchFailedS2CEvt::ParseMessageToMessageBase));
			// S2C: Game matching started
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchingStartedS2CEvt::MID.ID,&Message::Game::GameMatchingStartedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchingStartedS2CEvt::MID.ID,&Message::Game::GameMatchingStartedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Cancel Game match
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CancelGameMatchCmd::MID.ID,&Message::Game::CancelGameMatchCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CancelGameMatchCmd::MID.ID,&Message::Game::CancelGameMatchCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CancelGameMatchRes::MID.ID,&Message::Game::CancelGameMatchRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CancelGameMatchRes::MID.ID,&Message::Game::CancelGameMatchRes::ParseMessageToMessageBase));
			// S2C: game matching canceled
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchingCanceledS2CEvt::MID.ID,&Message::Game::GameMatchingCanceledS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchingCanceledS2CEvt::MID.ID,&Message::Game::GameMatchingCanceledS2CEvt::ParseMessageToMessageBase));
			// Cmd: Request UGC template list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUGCTemplatesCmd::MID.ID,&Message::Game::GetUGCTemplatesCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUGCTemplatesCmd::MID.ID,&Message::Game::GetUGCTemplatesCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUGCTemplatesRes::MID.ID,&Message::Game::GetUGCTemplatesRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUGCTemplatesRes::MID.ID,&Message::Game::GetUGCTemplatesRes::ParseMessageToMessageBase));
			// Cmd: Save UGC content data
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SaveUGCCmd::MID.ID,&Message::Game::SaveUGCCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SaveUGCCmd::MID.ID,&Message::Game::SaveUGCCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SaveUGCRes::MID.ID,&Message::Game::SaveUGCRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SaveUGCRes::MID.ID,&Message::Game::SaveUGCRes::ParseMessageToMessageBase));
			// Cmd: Request WhiteboardSharing
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SearchUGCCmd::MID.ID,&Message::Game::SearchUGCCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SearchUGCCmd::MID.ID,&Message::Game::SearchUGCCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SearchUGCRes::MID.ID,&Message::Game::SearchUGCRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SearchUGCRes::MID.ID,&Message::Game::SearchUGCRes::ParseMessageToMessageBase));
			// Cmd: Get UGC content info, name, thumb image and so on
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUGCContentInfoCmd::MID.ID,&Message::Game::GetUGCContentInfoCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUGCContentInfoCmd::MID.ID,&Message::Game::GetUGCContentInfoCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUGCContentInfoRes::MID.ID,&Message::Game::GetUGCContentInfoRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUGCContentInfoRes::MID.ID,&Message::Game::GetUGCContentInfoRes::ParseMessageToMessageBase));
			// Cmd: Request WhiteboardSharing
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DownloadUGCContentCmd::MID.ID,&Message::Game::DownloadUGCContentCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DownloadUGCContentCmd::MID.ID,&Message::Game::DownloadUGCContentCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DownloadUGCContentRes::MID.ID,&Message::Game::DownloadUGCContentRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DownloadUGCContentRes::MID.ID,&Message::Game::DownloadUGCContentRes::ParseMessageToMessageBase));
			// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestUGCZoneInstanceCmd::MID.ID,&Message::Game::RequestUGCZoneInstanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestUGCZoneInstanceCmd::MID.ID,&Message::Game::RequestUGCZoneInstanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestUGCZoneInstanceRes::MID.ID,&Message::Game::RequestUGCZoneInstanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestUGCZoneInstanceRes::MID.ID,&Message::Game::RequestUGCZoneInstanceRes::ParseMessageToMessageBase));
			// Cmd: Buy shop item prepare
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareCmd::MID.ID,&Message::Game::BuyShopItemPrepareCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareCmd::MID.ID,&Message::Game::BuyShopItemPrepareCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareRes::MID.ID,&Message::Game::BuyShopItemPrepareRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareRes::MID.ID,&Message::Game::BuyShopItemPrepareRes::ParseMessageToMessageBase));
			// Cmd: Buy shop item
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemCmd::MID.ID,&Message::Game::BuyShopItemCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemCmd::MID.ID,&Message::Game::BuyShopItemCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemRes::MID.ID,&Message::Game::BuyShopItemRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemRes::MID.ID,&Message::Game::BuyShopItemRes::ParseMessageToMessageBase));
			// Cmd: Create or Join Chat channel
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelCmd::MID.ID,&Message::Game::CreateOrJoinChatChannelCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelCmd::MID.ID,&Message::Game::CreateOrJoinChatChannelCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelRes::MID.ID,&Message::Game::CreateOrJoinChatChannelRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelRes::MID.ID,&Message::Game::CreateOrJoinChatChannelRes::ParseMessageToMessageBase));
			// Cmd: Join
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinChatChannelCmd::MID.ID,&Message::Game::JoinChatChannelCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinChatChannelCmd::MID.ID,&Message::Game::JoinChatChannelCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinChatChannelRes::MID.ID,&Message::Game::JoinChatChannelRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinChatChannelRes::MID.ID,&Message::Game::JoinChatChannelRes::ParseMessageToMessageBase));
			// S2C: Player Joined event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerJoinedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase));
			// S2C: ChatChannel leader changed event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelLeaderChangedS2CEvt::MID.ID,&Message::Game::ChatChannelLeaderChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelLeaderChangedS2CEvt::MID.ID,&Message::Game::ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Leave ChatChannel command
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveChatChannelCmd::MID.ID,&Message::Game::LeaveChatChannelCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveChatChannelCmd::MID.ID,&Message::Game::LeaveChatChannelCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveChatChannelRes::MID.ID,&Message::Game::LeaveChatChannelRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveChatChannelRes::MID.ID,&Message::Game::LeaveChatChannelRes::ParseMessageToMessageBase));
			// S2C: ChatChannel Player left event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelPlayerLeftS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerLeftS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelPlayerLeftS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase));
			// Cmd: Kick player from the ChatChannel
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerCmd::MID.ID,&Message::Game::ChatChannelKickPlayerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerCmd::MID.ID,&Message::Game::ChatChannelKickPlayerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerRes::MID.ID,&Message::Game::ChatChannelKickPlayerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerRes::MID.ID,&Message::Game::ChatChannelKickPlayerRes::ParseMessageToMessageBase));
			// S2C: ChatChannel Player kicked message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelPlayerKickedS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelPlayerKickedS2CEvt::MID.ID,&Message::Game::ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Chat channel sending chatting message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageCmd::MID.ID,&Message::Game::ChatChannelChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageCmd::MID.ID,&Message::Game::ChatChannelChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageRes::MID.ID,&Message::Game::ChatChannelChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageRes::MID.ID,&Message::Game::ChatChannelChatMessageRes::ParseMessageToMessageBase));
			// S2C: ChatChannel Chatting message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageS2CEvt::MID.ID,&Message::Game::ChatChannelChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageS2CEvt::MID.ID,&Message::Game::ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Whisper(tell) other player chatting
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::WhisperMessageCmd::MID.ID,&Message::Game::WhisperMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::WhisperMessageCmd::MID.ID,&Message::Game::WhisperMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::WhisperMessageRes::MID.ID,&Message::Game::WhisperMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::WhisperMessageRes::MID.ID,&Message::Game::WhisperMessageRes::ParseMessageToMessageBase));
			// S2C: Other player whispered(tell) to me message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::WhisperMessageS2CEvt::MID.ID,&Message::Game::WhisperMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::WhisperMessageS2CEvt::MID.ID,&Message::Game::WhisperMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Create character
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateCharacterCmd::MID.ID,&Message::Game::CreateCharacterCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateCharacterCmd::MID.ID,&Message::Game::CreateCharacterCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateCharacterRes::MID.ID,&Message::Game::CreateCharacterRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateCharacterRes::MID.ID,&Message::Game::CreateCharacterRes::ParseMessageToMessageBase));
			// Cmd: Delete character
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DeleteCharacterCmd::MID.ID,&Message::Game::DeleteCharacterCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DeleteCharacterCmd::MID.ID,&Message::Game::DeleteCharacterCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DeleteCharacterRes::MID.ID,&Message::Game::DeleteCharacterRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DeleteCharacterRes::MID.ID,&Message::Game::DeleteCharacterRes::ParseMessageToMessageBase));
			// Cmd: Get character list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterListCmd::MID.ID,&Message::Game::GetCharacterListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterListCmd::MID.ID,&Message::Game::GetCharacterListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterListRes::MID.ID,&Message::Game::GetCharacterListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterListRes::MID.ID,&Message::Game::GetCharacterListRes::ParseMessageToMessageBase));
			// Cmd: 
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterDataCmd::MID.ID,&Message::Game::GetCharacterDataCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterDataCmd::MID.ID,&Message::Game::GetCharacterDataCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterDataRes::MID.ID,&Message::Game::GetCharacterDataRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterDataRes::MID.ID,&Message::Game::GetCharacterDataRes::ParseMessageToMessageBase));
			// Cmd: Select character
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SelectCharacterCmd::MID.ID,&Message::Game::SelectCharacterCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SelectCharacterCmd::MID.ID,&Message::Game::SelectCharacterCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SelectCharacterRes::MID.ID,&Message::Game::SelectCharacterRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SelectCharacterRes::MID.ID,&Message::Game::SelectCharacterRes::ParseMessageToMessageBase));
			// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestServerNoticeUpdateCmd::MID.ID,&Message::Game::RequestServerNoticeUpdateCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestServerNoticeUpdateCmd::MID.ID,&Message::Game::RequestServerNoticeUpdateCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestServerNoticeUpdateRes::MID.ID,&Message::Game::RequestServerNoticeUpdateRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestServerNoticeUpdateRes::MID.ID,&Message::Game::RequestServerNoticeUpdateRes::ParseMessageToMessageBase));
			// S2C: Server Notice updated event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ServerNoticeS2CEvt::MID.ID,&Message::Game::ServerNoticeS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ServerNoticeS2CEvt::MID.ID,&Message::Game::ServerNoticeS2CEvt::ParseMessageToMessageBase));
			// Cmd: To call general functionality
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CallFunctionCmd::MID.ID,&Message::Game::CallFunctionCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CallFunctionCmd::MID.ID,&Message::Game::CallFunctionCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CallFunctionRes::MID.ID,&Message::Game::CallFunctionRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CallFunctionRes::MID.ID,&Message::Game::CallFunctionRes::ParseMessageToMessageBase));
		}; // void RegisterParserGame()


	}; // namespace Protocol
}; // namespace SF


