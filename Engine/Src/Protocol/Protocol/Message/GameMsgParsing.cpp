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
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/GameMsgParsing.h"
#include "Protocol/Message/GameMsgClass.h"



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
 			// C2S: Client heart bit
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::HeartBitC2SEvt::MID.IDSeq.MsgID,&Message::Game::HeartBitC2SEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::HeartBitC2SEvt::MID.IDSeq.MsgID,&Message::Game::HeartBitC2SEvt::ParseMessageToMessageBase));
			// Cmd: Player connected from a login server and moved to game server
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameServerCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameServerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameServerCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameServerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameServerRes::MID.IDSeq.MsgID,&Message::Game::JoinGameServerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameServerRes::MID.IDSeq.MsgID,&Message::Game::JoinGameServerRes::ParseMessageToMessageBase));
			// Cmd: player complition statues
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetComplitionStateCmd::MID.IDSeq.MsgID,&Message::Game::GetComplitionStateCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetComplitionStateCmd::MID.IDSeq.MsgID,&Message::Game::GetComplitionStateCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetComplitionStateRes::MID.IDSeq.MsgID,&Message::Game::GetComplitionStateRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetComplitionStateRes::MID.IDSeq.MsgID,&Message::Game::GetComplitionStateRes::ParseMessageToMessageBase));
			// Cmd: Player complition state
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetComplitionStateCmd::MID.IDSeq.MsgID,&Message::Game::SetComplitionStateCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetComplitionStateCmd::MID.IDSeq.MsgID,&Message::Game::SetComplitionStateCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetComplitionStateRes::MID.IDSeq.MsgID,&Message::Game::SetComplitionStateRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetComplitionStateRes::MID.IDSeq.MsgID,&Message::Game::SetComplitionStateRes::ParseMessageToMessageBase));
			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RegisterGCMCmd::MID.IDSeq.MsgID,&Message::Game::RegisterGCMCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RegisterGCMCmd::MID.IDSeq.MsgID,&Message::Game::RegisterGCMCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RegisterGCMRes::MID.IDSeq.MsgID,&Message::Game::RegisterGCMRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RegisterGCMRes::MID.IDSeq.MsgID,&Message::Game::RegisterGCMRes::ParseMessageToMessageBase));
			// Cmd: Unregister Google notification service ID
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::UnregisterGCMCmd::MID.IDSeq.MsgID,&Message::Game::UnregisterGCMCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::UnregisterGCMCmd::MID.IDSeq.MsgID,&Message::Game::UnregisterGCMCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::UnregisterGCMRes::MID.IDSeq.MsgID,&Message::Game::UnregisterGCMRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::UnregisterGCMRes::MID.IDSeq.MsgID,&Message::Game::UnregisterGCMRes::ParseMessageToMessageBase));
			// Cmd: Invite friend
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::InviteFriendCmd::MID.IDSeq.MsgID,&Message::Game::InviteFriendCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::InviteFriendCmd::MID.IDSeq.MsgID,&Message::Game::InviteFriendCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::InviteFriendRes::MID.IDSeq.MsgID,&Message::Game::InviteFriendRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::InviteFriendRes::MID.IDSeq.MsgID,&Message::Game::InviteFriendRes::ParseMessageToMessageBase));
			// Cmd: Accept friend request
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptFriendRequestCmd::MID.IDSeq.MsgID,&Message::Game::AcceptFriendRequestCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptFriendRequestCmd::MID.IDSeq.MsgID,&Message::Game::AcceptFriendRequestCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptFriendRequestRes::MID.IDSeq.MsgID,&Message::Game::AcceptFriendRequestRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptFriendRequestRes::MID.IDSeq.MsgID,&Message::Game::AcceptFriendRequestRes::ParseMessageToMessageBase));
			// S2C: Notification for friend request is accepted
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FriendRequestAcceptedS2CEvt::MID.IDSeq.MsgID,&Message::Game::FriendRequestAcceptedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FriendRequestAcceptedS2CEvt::MID.IDSeq.MsgID,&Message::Game::FriendRequestAcceptedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Remove friden form the friend list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RemoveFriendCmd::MID.IDSeq.MsgID,&Message::Game::RemoveFriendCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RemoveFriendCmd::MID.IDSeq.MsgID,&Message::Game::RemoveFriendCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RemoveFriendRes::MID.IDSeq.MsgID,&Message::Game::RemoveFriendRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RemoveFriendRes::MID.IDSeq.MsgID,&Message::Game::RemoveFriendRes::ParseMessageToMessageBase));
			// S2C: Friend removed
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FriendRemovedS2CEvt::MID.IDSeq.MsgID,&Message::Game::FriendRemovedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FriendRemovedS2CEvt::MID.IDSeq.MsgID,&Message::Game::FriendRemovedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Get friend list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetFriendListCmd::MID.IDSeq.MsgID,&Message::Game::GetFriendListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetFriendListCmd::MID.IDSeq.MsgID,&Message::Game::GetFriendListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetFriendListRes::MID.IDSeq.MsgID,&Message::Game::GetFriendListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetFriendListRes::MID.IDSeq.MsgID,&Message::Game::GetFriendListRes::ParseMessageToMessageBase));
			// Cmd: Query notification list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetNotificationListCmd::MID.IDSeq.MsgID,&Message::Game::GetNotificationListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetNotificationListCmd::MID.IDSeq.MsgID,&Message::Game::GetNotificationListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetNotificationListRes::MID.IDSeq.MsgID,&Message::Game::GetNotificationListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetNotificationListRes::MID.IDSeq.MsgID,&Message::Game::GetNotificationListRes::ParseMessageToMessageBase));
			// Cmd: Delete notification
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DeleteNotificationCmd::MID.IDSeq.MsgID,&Message::Game::DeleteNotificationCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DeleteNotificationCmd::MID.IDSeq.MsgID,&Message::Game::DeleteNotificationCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::DeleteNotificationRes::MID.IDSeq.MsgID,&Message::Game::DeleteNotificationRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::DeleteNotificationRes::MID.IDSeq.MsgID,&Message::Game::DeleteNotificationRes::ParseMessageToMessageBase));
			// Cmd: Set notification is read
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNotificationReadCmd::MID.IDSeq.MsgID,&Message::Game::SetNotificationReadCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNotificationReadCmd::MID.IDSeq.MsgID,&Message::Game::SetNotificationReadCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNotificationReadRes::MID.IDSeq.MsgID,&Message::Game::SetNotificationReadRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNotificationReadRes::MID.IDSeq.MsgID,&Message::Game::SetNotificationReadRes::ParseMessageToMessageBase));
			// Cmd: Accept notification
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptNotificationCmd::MID.IDSeq.MsgID,&Message::Game::AcceptNotificationCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptNotificationCmd::MID.IDSeq.MsgID,&Message::Game::AcceptNotificationCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AcceptNotificationRes::MID.IDSeq.MsgID,&Message::Game::AcceptNotificationRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AcceptNotificationRes::MID.IDSeq.MsgID,&Message::Game::AcceptNotificationRes::ParseMessageToMessageBase));
			// S2C: Notify new notification
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::NotifyS2CEvt::MID.IDSeq.MsgID,&Message::Game::NotifyS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::NotifyS2CEvt::MID.IDSeq.MsgID,&Message::Game::NotifyS2CEvt::ParseMessageToMessageBase));
			// Cmd: Query playerID list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByEMailCmd::MID.IDSeq.MsgID,&Message::Game::FindPlayerByEMailCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByEMailCmd::MID.IDSeq.MsgID,&Message::Game::FindPlayerByEMailCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByEMailRes::MID.IDSeq.MsgID,&Message::Game::FindPlayerByEMailRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByEMailRes::MID.IDSeq.MsgID,&Message::Game::FindPlayerByEMailRes::ParseMessageToMessageBase));
			// Cmd: Query playerID list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDCmd::MID.IDSeq.MsgID,&Message::Game::FindPlayerByPlayerIDCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDCmd::MID.IDSeq.MsgID,&Message::Game::FindPlayerByPlayerIDCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDRes::MID.IDSeq.MsgID,&Message::Game::FindPlayerByPlayerIDRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDRes::MID.IDSeq.MsgID,&Message::Game::FindPlayerByPlayerIDRes::ParseMessageToMessageBase));
			// Cmd: *Request Player Status Update
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateCmd::MID.IDSeq.MsgID,&Message::Game::RequestPlayerStatusUpdateCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateCmd::MID.IDSeq.MsgID,&Message::Game::RequestPlayerStatusUpdateCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateRes::MID.IDSeq.MsgID,&Message::Game::RequestPlayerStatusUpdateRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateRes::MID.IDSeq.MsgID,&Message::Game::RequestPlayerStatusUpdateRes::ParseMessageToMessageBase));
			// S2C: *Notify Player Status Updated
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.IDSeq.MsgID,&Message::Game::NotifyPlayerStatusUpdatedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.IDSeq.MsgID,&Message::Game::NotifyPlayerStatusUpdatedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Get Ranking lise
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetRankingListCmd::MID.IDSeq.MsgID,&Message::Game::GetRankingListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetRankingListCmd::MID.IDSeq.MsgID,&Message::Game::GetRankingListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetRankingListRes::MID.IDSeq.MsgID,&Message::Game::GetRankingListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetRankingListRes::MID.IDSeq.MsgID,&Message::Game::GetRankingListRes::ParseMessageToMessageBase));
			// Cmd: Game user game play information
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoCmd::MID.IDSeq.MsgID,&Message::Game::GetUserGamePlayerInfoCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoCmd::MID.IDSeq.MsgID,&Message::Game::GetUserGamePlayerInfoCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoRes::MID.IDSeq.MsgID,&Message::Game::GetUserGamePlayerInfoRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoRes::MID.IDSeq.MsgID,&Message::Game::GetUserGamePlayerInfoRes::ParseMessageToMessageBase));
			// Cmd: Game game play information
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoCmd::MID.IDSeq.MsgID,&Message::Game::GetGamePlayerInfoCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoCmd::MID.IDSeq.MsgID,&Message::Game::GetGamePlayerInfoCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoRes::MID.IDSeq.MsgID,&Message::Game::GetGamePlayerInfoRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoRes::MID.IDSeq.MsgID,&Message::Game::GetGamePlayerInfoRes::ParseMessageToMessageBase));
			// S2C: Player level up event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LevelUpS2CEvt::MID.IDSeq.MsgID,&Message::Game::LevelUpS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LevelUpS2CEvt::MID.IDSeq.MsgID,&Message::Game::LevelUpS2CEvt::ParseMessageToMessageBase));
			// Cmd: Change NickName
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNickNameCmd::MID.IDSeq.MsgID,&Message::Game::SetNickNameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNickNameCmd::MID.IDSeq.MsgID,&Message::Game::SetNickNameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetNickNameRes::MID.IDSeq.MsgID,&Message::Game::SetNickNameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetNickNameRes::MID.IDSeq.MsgID,&Message::Game::SetNickNameRes::ParseMessageToMessageBase));
			// Cmd: Create Party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreatePartyCmd::MID.IDSeq.MsgID,&Message::Game::CreatePartyCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreatePartyCmd::MID.IDSeq.MsgID,&Message::Game::CreatePartyCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreatePartyRes::MID.IDSeq.MsgID,&Message::Game::CreatePartyRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreatePartyRes::MID.IDSeq.MsgID,&Message::Game::CreatePartyRes::ParseMessageToMessageBase));
			// Cmd: Join party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinPartyCmd::MID.IDSeq.MsgID,&Message::Game::JoinPartyCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinPartyCmd::MID.IDSeq.MsgID,&Message::Game::JoinPartyCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinPartyRes::MID.IDSeq.MsgID,&Message::Game::JoinPartyRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinPartyRes::MID.IDSeq.MsgID,&Message::Game::JoinPartyRes::ParseMessageToMessageBase));
			// S2C: Player Joined event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyPlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerJoinedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyPlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerJoinedS2CEvt::ParseMessageToMessageBase));
			// S2C: Party leader changed event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyLeaderChangedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyLeaderChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyLeaderChangedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyLeaderChangedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Leave party command
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeavePartyCmd::MID.IDSeq.MsgID,&Message::Game::LeavePartyCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeavePartyCmd::MID.IDSeq.MsgID,&Message::Game::LeavePartyCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeavePartyRes::MID.IDSeq.MsgID,&Message::Game::LeavePartyRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeavePartyRes::MID.IDSeq.MsgID,&Message::Game::LeavePartyRes::ParseMessageToMessageBase));
			// S2C: Party Player left event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyPlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerLeftS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyPlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerLeftS2CEvt::ParseMessageToMessageBase));
			// Cmd: Kick player from the party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyKickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::PartyKickPlayerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyKickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::PartyKickPlayerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyKickPlayerRes::MID.IDSeq.MsgID,&Message::Game::PartyKickPlayerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyKickPlayerRes::MID.IDSeq.MsgID,&Message::Game::PartyKickPlayerRes::ParseMessageToMessageBase));
			// S2C: Party Player kicked message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyPlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyPlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerKickedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Invite a player to the party
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyInviteCmd::MID.IDSeq.MsgID,&Message::Game::PartyInviteCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyInviteCmd::MID.IDSeq.MsgID,&Message::Game::PartyInviteCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyInviteRes::MID.IDSeq.MsgID,&Message::Game::PartyInviteRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyInviteRes::MID.IDSeq.MsgID,&Message::Game::PartyInviteRes::ParseMessageToMessageBase));
			// S2C: Party invite requested
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyInviteRequestedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyInviteRequestedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyInviteRequestedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyInviteRequestedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Send Party quick chat message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageRes::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageRes::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageRes::ParseMessageToMessageBase));
			// S2C: Party Chatting message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Party chatting
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyChatMessageRes::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyChatMessageRes::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageRes::ParseMessageToMessageBase));
			// S2C: Party Chatting message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PartyChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PartyChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Join to a game
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinGameRes::MID.IDSeq.MsgID,&Message::Game::JoinGameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinGameRes::MID.IDSeq.MsgID,&Message::Game::JoinGameRes::ParseMessageToMessageBase));
			// S2C: Player Joined in the game
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerJoinedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerJoinedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Leave Game
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveGameCmd::MID.IDSeq.MsgID,&Message::Game::LeaveGameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveGameCmd::MID.IDSeq.MsgID,&Message::Game::LeaveGameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveGameRes::MID.IDSeq.MsgID,&Message::Game::LeaveGameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveGameRes::MID.IDSeq.MsgID,&Message::Game::LeaveGameRes::ParseMessageToMessageBase));
			// S2C: Player left event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerLeftS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerLeftS2CEvt::ParseMessageToMessageBase));
			// Cmd: Kick player
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::KickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::KickPlayerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::KickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::KickPlayerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::KickPlayerRes::MID.IDSeq.MsgID,&Message::Game::KickPlayerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::KickPlayerRes::MID.IDSeq.MsgID,&Message::Game::KickPlayerRes::ParseMessageToMessageBase));
			// S2C: Player kicked
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerKickedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Assign role + Game state reset
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AssignRoleCmd::MID.IDSeq.MsgID,&Message::Game::AssignRoleCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AssignRoleCmd::MID.IDSeq.MsgID,&Message::Game::AssignRoleCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AssignRoleRes::MID.IDSeq.MsgID,&Message::Game::AssignRoleRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AssignRoleRes::MID.IDSeq.MsgID,&Message::Game::AssignRoleRes::ParseMessageToMessageBase));
			// S2C: Role assigned event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RoleAssignedS2CEvt::MID.IDSeq.MsgID,&Message::Game::RoleAssignedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RoleAssignedS2CEvt::MID.IDSeq.MsgID,&Message::Game::RoleAssignedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Send chatting message to the game
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::ChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::ChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatMessageRes::MID.IDSeq.MsgID,&Message::Game::ChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatMessageRes::MID.IDSeq.MsgID,&Message::Game::ChatMessageRes::ParseMessageToMessageBase));
			// S2C: Chatting message event 
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Advance game
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AdvanceGameCmd::MID.IDSeq.MsgID,&Message::Game::AdvanceGameCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AdvanceGameCmd::MID.IDSeq.MsgID,&Message::Game::AdvanceGameCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::AdvanceGameRes::MID.IDSeq.MsgID,&Message::Game::AdvanceGameRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::AdvanceGameRes::MID.IDSeq.MsgID,&Message::Game::AdvanceGameRes::ParseMessageToMessageBase));
			// S2C: The game state is advanced
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameAdvancedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameAdvancedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameAdvancedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameAdvancedS2CEvt::ParseMessageToMessageBase));
			// S2C: Game is ended
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameEndedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameEndedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameEndedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameEndedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Vote game advance
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::VoteGameAdvanceCmd::MID.IDSeq.MsgID,&Message::Game::VoteGameAdvanceCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::VoteGameAdvanceCmd::MID.IDSeq.MsgID,&Message::Game::VoteGameAdvanceCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::VoteGameAdvanceRes::MID.IDSeq.MsgID,&Message::Game::VoteGameAdvanceRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::VoteGameAdvanceRes::MID.IDSeq.MsgID,&Message::Game::VoteGameAdvanceRes::ParseMessageToMessageBase));
			// S2C: GameAdvance is Voted
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameAdvanceVotedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameAdvanceVotedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameAdvanceVotedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameAdvanceVotedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Vote
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::VoteCmd::MID.IDSeq.MsgID,&Message::Game::VoteCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::VoteCmd::MID.IDSeq.MsgID,&Message::Game::VoteCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::VoteRes::MID.IDSeq.MsgID,&Message::Game::VoteRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::VoteRes::MID.IDSeq.MsgID,&Message::Game::VoteRes::ParseMessageToMessageBase));
			// S2C: Player Voted
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::VotedS2CEvt::MID.IDSeq.MsgID,&Message::Game::VotedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::VotedS2CEvt::MID.IDSeq.MsgID,&Message::Game::VotedS2CEvt::ParseMessageToMessageBase));
			// S2C: Vote is ended
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::VoteEndS2CEvt::MID.IDSeq.MsgID,&Message::Game::VoteEndS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::VoteEndS2CEvt::MID.IDSeq.MsgID,&Message::Game::VoteEndS2CEvt::ParseMessageToMessageBase));
			// S2C: Player Killed
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PlayerKilledS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerKilledS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PlayerKilledS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerKilledS2CEvt::ParseMessageToMessageBase));
			// S2C: Player Voted
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::PlayerRevealedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerRevealedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::PlayerRevealedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerRevealedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Play again with the current players
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayAgainCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayAgainCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayAgainRes::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayAgainRes::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainRes::ParseMessageToMessageBase));
			// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayAgainS2CEvt::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayAgainS2CEvt::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainS2CEvt::ParseMessageToMessageBase));
			// Cmd: Player. reveal a player
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameRevealPlayerCmd::MID.IDSeq.MsgID,&Message::Game::GameRevealPlayerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameRevealPlayerCmd::MID.IDSeq.MsgID,&Message::Game::GameRevealPlayerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameRevealPlayerRes::MID.IDSeq.MsgID,&Message::Game::GameRevealPlayerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameRevealPlayerRes::MID.IDSeq.MsgID,&Message::Game::GameRevealPlayerRes::ParseMessageToMessageBase));
			// Cmd: Player. revive himself
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayerReviveCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayerReviveCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayerReviveCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayerReviveCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayerReviveRes::MID.IDSeq.MsgID,&Message::Game::GamePlayerReviveRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayerReviveRes::MID.IDSeq.MsgID,&Message::Game::GamePlayerReviveRes::ParseMessageToMessageBase));
			// S2C: Player is revived
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayerRevivedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GamePlayerRevivedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayerRevivedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GamePlayerRevivedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Player. reset ranking
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayerResetRankCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayerResetRankCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayerResetRankCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayerResetRankCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GamePlayerResetRankRes::MID.IDSeq.MsgID,&Message::Game::GamePlayerResetRankRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GamePlayerResetRankRes::MID.IDSeq.MsgID,&Message::Game::GamePlayerResetRankRes::ParseMessageToMessageBase));
			// Cmd: Request Game match
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestGameMatchCmd::MID.IDSeq.MsgID,&Message::Game::RequestGameMatchCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestGameMatchCmd::MID.IDSeq.MsgID,&Message::Game::RequestGameMatchCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RequestGameMatchRes::MID.IDSeq.MsgID,&Message::Game::RequestGameMatchRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RequestGameMatchRes::MID.IDSeq.MsgID,&Message::Game::RequestGameMatchRes::ParseMessageToMessageBase));
			// S2C: Game matched
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchedS2CEvt::ParseMessageToMessageBase));
			// S2C: Game match failed
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchFailedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchFailedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchFailedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchFailedS2CEvt::ParseMessageToMessageBase));
			// S2C: Game matching started
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchingStartedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchingStartedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchingStartedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchingStartedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Cancel Game match
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CancelGameMatchCmd::MID.IDSeq.MsgID,&Message::Game::CancelGameMatchCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CancelGameMatchCmd::MID.IDSeq.MsgID,&Message::Game::CancelGameMatchCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CancelGameMatchRes::MID.IDSeq.MsgID,&Message::Game::CancelGameMatchRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CancelGameMatchRes::MID.IDSeq.MsgID,&Message::Game::CancelGameMatchRes::ParseMessageToMessageBase));
			// S2C: game matching canceled
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GameMatchingCanceledS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchingCanceledS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GameMatchingCanceledS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchingCanceledS2CEvt::ParseMessageToMessageBase));
			// Cmd: Buy shop item prepare
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareCmd::MID.IDSeq.MsgID,&Message::Game::BuyShopItemPrepareCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareCmd::MID.IDSeq.MsgID,&Message::Game::BuyShopItemPrepareCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareRes::MID.IDSeq.MsgID,&Message::Game::BuyShopItemPrepareRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareRes::MID.IDSeq.MsgID,&Message::Game::BuyShopItemPrepareRes::ParseMessageToMessageBase));
			// Cmd: Buy shop item
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemCmd::MID.IDSeq.MsgID,&Message::Game::BuyShopItemCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemCmd::MID.IDSeq.MsgID,&Message::Game::BuyShopItemCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::BuyShopItemRes::MID.IDSeq.MsgID,&Message::Game::BuyShopItemRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::BuyShopItemRes::MID.IDSeq.MsgID,&Message::Game::BuyShopItemRes::ParseMessageToMessageBase));
			// Cmd: Create or Join Chat channel
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::CreateOrJoinChatChannelCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::CreateOrJoinChatChannelCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelRes::MID.IDSeq.MsgID,&Message::Game::CreateOrJoinChatChannelRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelRes::MID.IDSeq.MsgID,&Message::Game::CreateOrJoinChatChannelRes::ParseMessageToMessageBase));
			// Cmd: Join
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::JoinChatChannelCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::JoinChatChannelCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::JoinChatChannelRes::MID.IDSeq.MsgID,&Message::Game::JoinChatChannelRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::JoinChatChannelRes::MID.IDSeq.MsgID,&Message::Game::JoinChatChannelRes::ParseMessageToMessageBase));
			// S2C: Player Joined event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerJoinedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerJoinedS2CEvt::ParseMessageToMessageBase));
			// S2C: ChatChannel leader changed event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelLeaderChangedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelLeaderChangedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelLeaderChangedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelLeaderChangedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Leave ChatChannel command
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::LeaveChatChannelCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::LeaveChatChannelCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::LeaveChatChannelRes::MID.IDSeq.MsgID,&Message::Game::LeaveChatChannelRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::LeaveChatChannelRes::MID.IDSeq.MsgID,&Message::Game::LeaveChatChannelRes::ParseMessageToMessageBase));
			// S2C: ChatChannel Player left event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelPlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerLeftS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelPlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerLeftS2CEvt::ParseMessageToMessageBase));
			// Cmd: Kick player from the ChatChannel
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::ChatChannelKickPlayerCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::ChatChannelKickPlayerCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerRes::MID.IDSeq.MsgID,&Message::Game::ChatChannelKickPlayerRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerRes::MID.IDSeq.MsgID,&Message::Game::ChatChannelKickPlayerRes::ParseMessageToMessageBase));
			// S2C: ChatChannel Player kicked message
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelPlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerKickedS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelPlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerKickedS2CEvt::ParseMessageToMessageBase));
			// Cmd: Party chatting
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageRes::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageRes::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageRes::ParseMessageToMessageBase));
			// S2C: ChatChannel Chatting message event
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageS2CEvt::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageS2CEvt::ParseMessageToMessageBase));
			// Cmd: Create character
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateCharacterCmd::MID.IDSeq.MsgID,&Message::Game::CreateCharacterCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateCharacterCmd::MID.IDSeq.MsgID,&Message::Game::CreateCharacterCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::CreateCharacterRes::MID.IDSeq.MsgID,&Message::Game::CreateCharacterRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::CreateCharacterRes::MID.IDSeq.MsgID,&Message::Game::CreateCharacterRes::ParseMessageToMessageBase));
			// Cmd: Remove character
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RemoveCharacterCmd::MID.IDSeq.MsgID,&Message::Game::RemoveCharacterCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RemoveCharacterCmd::MID.IDSeq.MsgID,&Message::Game::RemoveCharacterCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::RemoveCharacterRes::MID.IDSeq.MsgID,&Message::Game::RemoveCharacterRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::RemoveCharacterRes::MID.IDSeq.MsgID,&Message::Game::RemoveCharacterRes::ParseMessageToMessageBase));
			// Cmd: Get character list
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterListCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterListCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterListCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterListCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterListRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterListRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterListRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterListRes::ParseMessageToMessageBase));
			// Cmd: 
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterDataCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterDataCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GetCharacterDataRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GetCharacterDataRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataRes::ParseMessageToMessageBase));
			// Cmd: Give my stamina to other player
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GiveStaminaCmd::MID.IDSeq.MsgID,&Message::Game::GiveStaminaCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GiveStaminaCmd::MID.IDSeq.MsgID,&Message::Game::GiveStaminaCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::GiveStaminaRes::MID.IDSeq.MsgID,&Message::Game::GiveStaminaRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::GiveStaminaRes::MID.IDSeq.MsgID,&Message::Game::GiveStaminaRes::ParseMessageToMessageBase));
			// Cmd: For debug, Change configue preset
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetPresetGameConfigIDCmd::MID.IDSeq.MsgID,&Message::Game::SetPresetGameConfigIDCmd::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetPresetGameConfigIDCmd::MID.IDSeq.MsgID,&Message::Game::SetPresetGameConfigIDCmd::ParseMessageToMessageBase));
			MessageParseToVariableMap.insert(std::make_pair(Message::Game::SetPresetGameConfigIDRes::MID.IDSeq.MsgID,&Message::Game::SetPresetGameConfigIDRes::ParseMessageTo));
			MessageParseToMessageBaseMap.insert(std::make_pair(Message::Game::SetPresetGameConfigIDRes::MID.IDSeq.MsgID,&Message::Game::SetPresetGameConfigIDRes::ParseMessageToMessageBase));
		}; // void RegisterParserGame()


	}; // namespace Protocol
}; // namespace SF


