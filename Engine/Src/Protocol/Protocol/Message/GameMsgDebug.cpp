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
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/Message/GameMsgDebug.h"
#include "Protocol/Message/GameMsgClass.h"



namespace SF
{
 	namespace Protocol
	{
 		///////////////////////////////////////////////////////////////
		// Game Debug trace mapping
		extern std::unordered_map<uint32_t,MessageHandlingFunction> MessageDebugTraceMap;

		void RegisterDebugTraceGame()
		{
 			// C2S: Client heart bit
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::HeartBitC2SEvt::MID.IDSeq.MsgID,&Message::Game::HeartBitC2SEvt::TraceOut));
			// Cmd: Player connected from a login server and moved to game server
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameServerCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameServerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameServerRes::MID.IDSeq.MsgID,&Message::Game::JoinGameServerRes::TraceOut));
			// Cmd: player complition statues
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetComplitionStateCmd::MID.IDSeq.MsgID,&Message::Game::GetComplitionStateCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetComplitionStateRes::MID.IDSeq.MsgID,&Message::Game::GetComplitionStateRes::TraceOut));
			// Cmd: Player complition state
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetComplitionStateCmd::MID.IDSeq.MsgID,&Message::Game::SetComplitionStateCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetComplitionStateRes::MID.IDSeq.MsgID,&Message::Game::SetComplitionStateRes::TraceOut));
			// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RegisterGCMCmd::MID.IDSeq.MsgID,&Message::Game::RegisterGCMCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RegisterGCMRes::MID.IDSeq.MsgID,&Message::Game::RegisterGCMRes::TraceOut));
			// Cmd: Unregister Google notification service ID
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::UnregisterGCMCmd::MID.IDSeq.MsgID,&Message::Game::UnregisterGCMCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::UnregisterGCMRes::MID.IDSeq.MsgID,&Message::Game::UnregisterGCMRes::TraceOut));
			// Cmd: Invite friend
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::InviteFriendCmd::MID.IDSeq.MsgID,&Message::Game::InviteFriendCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::InviteFriendRes::MID.IDSeq.MsgID,&Message::Game::InviteFriendRes::TraceOut));
			// Cmd: Accept friend request
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptFriendRequestCmd::MID.IDSeq.MsgID,&Message::Game::AcceptFriendRequestCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptFriendRequestRes::MID.IDSeq.MsgID,&Message::Game::AcceptFriendRequestRes::TraceOut));
			// S2C: Notification for friend request is accepted
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FriendRequestAcceptedS2CEvt::MID.IDSeq.MsgID,&Message::Game::FriendRequestAcceptedS2CEvt::TraceOut));
			// Cmd: Remove friden form the friend list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RemoveFriendCmd::MID.IDSeq.MsgID,&Message::Game::RemoveFriendCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RemoveFriendRes::MID.IDSeq.MsgID,&Message::Game::RemoveFriendRes::TraceOut));
			// S2C: Friend removed
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FriendRemovedS2CEvt::MID.IDSeq.MsgID,&Message::Game::FriendRemovedS2CEvt::TraceOut));
			// Cmd: Get friend list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetFriendListCmd::MID.IDSeq.MsgID,&Message::Game::GetFriendListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetFriendListRes::MID.IDSeq.MsgID,&Message::Game::GetFriendListRes::TraceOut));
			// Cmd: Query notification list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetNotificationListCmd::MID.IDSeq.MsgID,&Message::Game::GetNotificationListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetNotificationListRes::MID.IDSeq.MsgID,&Message::Game::GetNotificationListRes::TraceOut));
			// Cmd: Delete notification
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DeleteNotificationCmd::MID.IDSeq.MsgID,&Message::Game::DeleteNotificationCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::DeleteNotificationRes::MID.IDSeq.MsgID,&Message::Game::DeleteNotificationRes::TraceOut));
			// Cmd: Set notification is read
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNotificationReadCmd::MID.IDSeq.MsgID,&Message::Game::SetNotificationReadCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNotificationReadRes::MID.IDSeq.MsgID,&Message::Game::SetNotificationReadRes::TraceOut));
			// Cmd: Accept notification
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptNotificationCmd::MID.IDSeq.MsgID,&Message::Game::AcceptNotificationCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AcceptNotificationRes::MID.IDSeq.MsgID,&Message::Game::AcceptNotificationRes::TraceOut));
			// S2C: Notify new notification
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::NotifyS2CEvt::MID.IDSeq.MsgID,&Message::Game::NotifyS2CEvt::TraceOut));
			// Cmd: Query playerID list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByEMailCmd::MID.IDSeq.MsgID,&Message::Game::FindPlayerByEMailCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByEMailRes::MID.IDSeq.MsgID,&Message::Game::FindPlayerByEMailRes::TraceOut));
			// Cmd: Query playerID list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDCmd::MID.IDSeq.MsgID,&Message::Game::FindPlayerByPlayerIDCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::FindPlayerByPlayerIDRes::MID.IDSeq.MsgID,&Message::Game::FindPlayerByPlayerIDRes::TraceOut));
			// Cmd: *Request Player Status Update
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateCmd::MID.IDSeq.MsgID,&Message::Game::RequestPlayerStatusUpdateCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestPlayerStatusUpdateRes::MID.IDSeq.MsgID,&Message::Game::RequestPlayerStatusUpdateRes::TraceOut));
			// S2C: *Notify Player Status Updated
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.IDSeq.MsgID,&Message::Game::NotifyPlayerStatusUpdatedS2CEvt::TraceOut));
			// Cmd: Get Ranking lise
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetRankingListCmd::MID.IDSeq.MsgID,&Message::Game::GetRankingListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetRankingListRes::MID.IDSeq.MsgID,&Message::Game::GetRankingListRes::TraceOut));
			// Cmd: Game user game play information
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoCmd::MID.IDSeq.MsgID,&Message::Game::GetUserGamePlayerInfoCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetUserGamePlayerInfoRes::MID.IDSeq.MsgID,&Message::Game::GetUserGamePlayerInfoRes::TraceOut));
			// Cmd: Game game play information
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoCmd::MID.IDSeq.MsgID,&Message::Game::GetGamePlayerInfoCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetGamePlayerInfoRes::MID.IDSeq.MsgID,&Message::Game::GetGamePlayerInfoRes::TraceOut));
			// S2C: Player level up event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LevelUpS2CEvt::MID.IDSeq.MsgID,&Message::Game::LevelUpS2CEvt::TraceOut));
			// Cmd: Change NickName
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNickNameCmd::MID.IDSeq.MsgID,&Message::Game::SetNickNameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetNickNameRes::MID.IDSeq.MsgID,&Message::Game::SetNickNameRes::TraceOut));
			// Cmd: Create Party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreatePartyCmd::MID.IDSeq.MsgID,&Message::Game::CreatePartyCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreatePartyRes::MID.IDSeq.MsgID,&Message::Game::CreatePartyRes::TraceOut));
			// Cmd: Join party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinPartyCmd::MID.IDSeq.MsgID,&Message::Game::JoinPartyCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinPartyRes::MID.IDSeq.MsgID,&Message::Game::JoinPartyRes::TraceOut));
			// S2C: Player Joined event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyPlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerJoinedS2CEvt::TraceOut));
			// S2C: Party leader changed event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyLeaderChangedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyLeaderChangedS2CEvt::TraceOut));
			// Cmd: Leave party command
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeavePartyCmd::MID.IDSeq.MsgID,&Message::Game::LeavePartyCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeavePartyRes::MID.IDSeq.MsgID,&Message::Game::LeavePartyRes::TraceOut));
			// S2C: Party Player left event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyPlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerLeftS2CEvt::TraceOut));
			// Cmd: Kick player from the party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyKickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::PartyKickPlayerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyKickPlayerRes::MID.IDSeq.MsgID,&Message::Game::PartyKickPlayerRes::TraceOut));
			// S2C: Party Player kicked message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyPlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyPlayerKickedS2CEvt::TraceOut));
			// Cmd: Invite a player to the party
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyInviteCmd::MID.IDSeq.MsgID,&Message::Game::PartyInviteCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyInviteRes::MID.IDSeq.MsgID,&Message::Game::PartyInviteRes::TraceOut));
			// S2C: Party invite requested
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyInviteRequestedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyInviteRequestedS2CEvt::TraceOut));
			// Cmd: Send Party quick chat message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageRes::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageRes::TraceOut));
			// S2C: Party Chatting message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyQuickChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyQuickChatMessageS2CEvt::TraceOut));
			// Cmd: Party chatting
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyChatMessageRes::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageRes::TraceOut));
			// S2C: Party Chatting message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PartyChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::PartyChatMessageS2CEvt::TraceOut));
			// Cmd: Join to a game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameInstanceCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameInstanceRes::MID.IDSeq.MsgID,&Message::Game::JoinGameInstanceRes::TraceOut));
			// Cmd: Leave game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveGameInstanceCmd::MID.IDSeq.MsgID,&Message::Game::LeaveGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveGameInstanceRes::MID.IDSeq.MsgID,&Message::Game::LeaveGameInstanceRes::TraceOut));
			// Cmd: Search game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SearchGameInstanceCmd::MID.IDSeq.MsgID,&Message::Game::SearchGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SearchGameInstanceRes::MID.IDSeq.MsgID,&Message::Game::SearchGameInstanceRes::TraceOut));
			// Cmd: Search game instance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataInGameInstanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataInGameInstanceRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataInGameInstanceRes::TraceOut));
			// Cmd: Join to a game
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameCmd::MID.IDSeq.MsgID,&Message::Game::JoinGameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinGameRes::MID.IDSeq.MsgID,&Message::Game::JoinGameRes::TraceOut));
			// S2C: Player Joined in the game
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerJoinedS2CEvt::TraceOut));
			// Cmd: Leave Game
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveGameCmd::MID.IDSeq.MsgID,&Message::Game::LeaveGameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveGameRes::MID.IDSeq.MsgID,&Message::Game::LeaveGameRes::TraceOut));
			// S2C: Player left event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerLeftS2CEvt::TraceOut));
			// Cmd: Kick player
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::KickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::KickPlayerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::KickPlayerRes::MID.IDSeq.MsgID,&Message::Game::KickPlayerRes::TraceOut));
			// S2C: Player kicked
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerKickedS2CEvt::TraceOut));
			// Cmd: Assign role + Game state reset
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AssignRoleCmd::MID.IDSeq.MsgID,&Message::Game::AssignRoleCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AssignRoleRes::MID.IDSeq.MsgID,&Message::Game::AssignRoleRes::TraceOut));
			// S2C: Role assigned event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RoleAssignedS2CEvt::MID.IDSeq.MsgID,&Message::Game::RoleAssignedS2CEvt::TraceOut));
			// Cmd: Send chatting message to the game
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::ChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatMessageRes::MID.IDSeq.MsgID,&Message::Game::ChatMessageRes::TraceOut));
			// S2C: Chatting message event 
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatMessageS2CEvt::TraceOut));
			// Cmd: Advance game
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AdvanceGameCmd::MID.IDSeq.MsgID,&Message::Game::AdvanceGameCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::AdvanceGameRes::MID.IDSeq.MsgID,&Message::Game::AdvanceGameRes::TraceOut));
			// S2C: The game state is advanced
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameAdvancedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameAdvancedS2CEvt::TraceOut));
			// S2C: Game is ended
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameEndedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameEndedS2CEvt::TraceOut));
			// Cmd: Vote game advance
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::VoteGameAdvanceCmd::MID.IDSeq.MsgID,&Message::Game::VoteGameAdvanceCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::VoteGameAdvanceRes::MID.IDSeq.MsgID,&Message::Game::VoteGameAdvanceRes::TraceOut));
			// S2C: GameAdvance is Voted
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameAdvanceVotedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameAdvanceVotedS2CEvt::TraceOut));
			// Cmd: Vote
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::VoteCmd::MID.IDSeq.MsgID,&Message::Game::VoteCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::VoteRes::MID.IDSeq.MsgID,&Message::Game::VoteRes::TraceOut));
			// S2C: Player Voted
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::VotedS2CEvt::MID.IDSeq.MsgID,&Message::Game::VotedS2CEvt::TraceOut));
			// S2C: Vote is ended
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::VoteEndS2CEvt::MID.IDSeq.MsgID,&Message::Game::VoteEndS2CEvt::TraceOut));
			// S2C: Player Killed
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PlayerKilledS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerKilledS2CEvt::TraceOut));
			// S2C: Player Voted
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::PlayerRevealedS2CEvt::MID.IDSeq.MsgID,&Message::Game::PlayerRevealedS2CEvt::TraceOut));
			// Cmd: Play again with the current players
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayAgainCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayAgainRes::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainRes::TraceOut));
			// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayAgainS2CEvt::MID.IDSeq.MsgID,&Message::Game::GamePlayAgainS2CEvt::TraceOut));
			// Cmd: Player. reveal a player
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameRevealPlayerCmd::MID.IDSeq.MsgID,&Message::Game::GameRevealPlayerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameRevealPlayerRes::MID.IDSeq.MsgID,&Message::Game::GameRevealPlayerRes::TraceOut));
			// Cmd: Player. revive himself
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayerReviveCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayerReviveCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayerReviveRes::MID.IDSeq.MsgID,&Message::Game::GamePlayerReviveRes::TraceOut));
			// S2C: Player is revived
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayerRevivedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GamePlayerRevivedS2CEvt::TraceOut));
			// Cmd: Player. reset ranking
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayerResetRankCmd::MID.IDSeq.MsgID,&Message::Game::GamePlayerResetRankCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GamePlayerResetRankRes::MID.IDSeq.MsgID,&Message::Game::GamePlayerResetRankRes::TraceOut));
			// Cmd: Request Game match
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestGameMatchCmd::MID.IDSeq.MsgID,&Message::Game::RequestGameMatchCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RequestGameMatchRes::MID.IDSeq.MsgID,&Message::Game::RequestGameMatchRes::TraceOut));
			// S2C: Game matched
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchedS2CEvt::TraceOut));
			// S2C: Game match failed
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchFailedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchFailedS2CEvt::TraceOut));
			// S2C: Game matching started
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchingStartedS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchingStartedS2CEvt::TraceOut));
			// Cmd: Cancel Game match
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CancelGameMatchCmd::MID.IDSeq.MsgID,&Message::Game::CancelGameMatchCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CancelGameMatchRes::MID.IDSeq.MsgID,&Message::Game::CancelGameMatchRes::TraceOut));
			// S2C: game matching canceled
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GameMatchingCanceledS2CEvt::MID.IDSeq.MsgID,&Message::Game::GameMatchingCanceledS2CEvt::TraceOut));
			// Cmd: Buy shop item prepare
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareCmd::MID.IDSeq.MsgID,&Message::Game::BuyShopItemPrepareCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemPrepareRes::MID.IDSeq.MsgID,&Message::Game::BuyShopItemPrepareRes::TraceOut));
			// Cmd: Buy shop item
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemCmd::MID.IDSeq.MsgID,&Message::Game::BuyShopItemCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::BuyShopItemRes::MID.IDSeq.MsgID,&Message::Game::BuyShopItemRes::TraceOut));
			// Cmd: Create or Join Chat channel
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::CreateOrJoinChatChannelCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateOrJoinChatChannelRes::MID.IDSeq.MsgID,&Message::Game::CreateOrJoinChatChannelRes::TraceOut));
			// Cmd: Join
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::JoinChatChannelCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::JoinChatChannelRes::MID.IDSeq.MsgID,&Message::Game::JoinChatChannelRes::TraceOut));
			// S2C: Player Joined event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerJoinedS2CEvt::TraceOut));
			// S2C: ChatChannel leader changed event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelLeaderChangedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelLeaderChangedS2CEvt::TraceOut));
			// Cmd: Leave ChatChannel command
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveChatChannelCmd::MID.IDSeq.MsgID,&Message::Game::LeaveChatChannelCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::LeaveChatChannelRes::MID.IDSeq.MsgID,&Message::Game::LeaveChatChannelRes::TraceOut));
			// S2C: ChatChannel Player left event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelPlayerLeftS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerLeftS2CEvt::TraceOut));
			// Cmd: Kick player from the ChatChannel
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerCmd::MID.IDSeq.MsgID,&Message::Game::ChatChannelKickPlayerCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelKickPlayerRes::MID.IDSeq.MsgID,&Message::Game::ChatChannelKickPlayerRes::TraceOut));
			// S2C: ChatChannel Player kicked message
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelPlayerKickedS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelPlayerKickedS2CEvt::TraceOut));
			// Cmd: Party chatting
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageCmd::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageRes::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageRes::TraceOut));
			// S2C: ChatChannel Chatting message event
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::ChatChannelChatMessageS2CEvt::MID.IDSeq.MsgID,&Message::Game::ChatChannelChatMessageS2CEvt::TraceOut));
			// Cmd: Create character
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateCharacterCmd::MID.IDSeq.MsgID,&Message::Game::CreateCharacterCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::CreateCharacterRes::MID.IDSeq.MsgID,&Message::Game::CreateCharacterRes::TraceOut));
			// Cmd: Remove character
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RemoveCharacterCmd::MID.IDSeq.MsgID,&Message::Game::RemoveCharacterCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::RemoveCharacterRes::MID.IDSeq.MsgID,&Message::Game::RemoveCharacterRes::TraceOut));
			// Cmd: Get character list
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterListCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterListCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterListRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterListRes::TraceOut));
			// Cmd: 
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataCmd::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GetCharacterDataRes::MID.IDSeq.MsgID,&Message::Game::GetCharacterDataRes::TraceOut));
			// Cmd: Give my stamina to other player
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GiveStaminaCmd::MID.IDSeq.MsgID,&Message::Game::GiveStaminaCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::GiveStaminaRes::MID.IDSeq.MsgID,&Message::Game::GiveStaminaRes::TraceOut));
			// Cmd: For debug, Change configue preset
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetPresetGameConfigIDCmd::MID.IDSeq.MsgID,&Message::Game::SetPresetGameConfigIDCmd::TraceOut));
			MessageDebugTraceMap.insert(std::make_pair(Message::Game::SetPresetGameConfigIDRes::MID.IDSeq.MsgID,&Message::Game::SetPresetGameConfigIDRes::TraceOut));
		}; // void RegisterDebugTraceGame()


	}; // namespace Protocol
}; // namespace SF


