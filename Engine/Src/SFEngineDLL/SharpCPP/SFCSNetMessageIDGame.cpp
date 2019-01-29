////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Game Message IDs
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/GameMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// C2S: Client heart bit
SFDLL_EXPORT int  CSSFNetMessageID_GameHeartBitC2SEvt()
{
 	return SF::Message::Game::HeartBitC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameHeartBitC2SEvt()


// Cmd: Player connected from a login server and moved to game server
SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameServerCmd()
{
 	return SF::Message::Game::JoinGameServerCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameServerCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameServerRes()
{
 	return SF::Message::Game::JoinGameServerRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameServerRes()


// Cmd: player complition statues
SFDLL_EXPORT int  CSSFNetMessageID_GameGetComplitionStateCmd()
{
 	return SF::Message::Game::GetComplitionStateCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetComplitionStateCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetComplitionStateRes()
{
 	return SF::Message::Game::GetComplitionStateRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetComplitionStateRes()


// Cmd: Player complition state
SFDLL_EXPORT int  CSSFNetMessageID_GameSetComplitionStateCmd()
{
 	return SF::Message::Game::SetComplitionStateCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetComplitionStateCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameSetComplitionStateRes()
{
 	return SF::Message::Game::SetComplitionStateRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetComplitionStateRes()


// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
SFDLL_EXPORT int  CSSFNetMessageID_GameRegisterGCMCmd()
{
 	return SF::Message::Game::RegisterGCMCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRegisterGCMCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameRegisterGCMRes()
{
 	return SF::Message::Game::RegisterGCMRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRegisterGCMRes()


// Cmd: Unregister Google notification service ID
SFDLL_EXPORT int  CSSFNetMessageID_GameUnregisterGCMCmd()
{
 	return SF::Message::Game::UnregisterGCMCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameUnregisterGCMCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameUnregisterGCMRes()
{
 	return SF::Message::Game::UnregisterGCMRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameUnregisterGCMRes()


// Cmd: Invite friend
SFDLL_EXPORT int  CSSFNetMessageID_GameInviteFriendCmd()
{
 	return SF::Message::Game::InviteFriendCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameInviteFriendCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameInviteFriendRes()
{
 	return SF::Message::Game::InviteFriendRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameInviteFriendRes()


// Cmd: Accept friend request
SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptFriendRequestCmd()
{
 	return SF::Message::Game::AcceptFriendRequestCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptFriendRequestCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptFriendRequestRes()
{
 	return SF::Message::Game::AcceptFriendRequestRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptFriendRequestRes()


// S2C: Notification for friend request is accepted
SFDLL_EXPORT int  CSSFNetMessageID_GameFriendRequestAcceptedS2CEvt()
{
 	return SF::Message::Game::FriendRequestAcceptedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameFriendRequestAcceptedS2CEvt()


// Cmd: Remove friden form the friend list
SFDLL_EXPORT int  CSSFNetMessageID_GameRemoveFriendCmd()
{
 	return SF::Message::Game::RemoveFriendCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRemoveFriendCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameRemoveFriendRes()
{
 	return SF::Message::Game::RemoveFriendRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRemoveFriendRes()


// S2C: Friend removed
SFDLL_EXPORT int  CSSFNetMessageID_GameFriendRemovedS2CEvt()
{
 	return SF::Message::Game::FriendRemovedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameFriendRemovedS2CEvt()


// Cmd: Get friend list
SFDLL_EXPORT int  CSSFNetMessageID_GameGetFriendListCmd()
{
 	return SF::Message::Game::GetFriendListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetFriendListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetFriendListRes()
{
 	return SF::Message::Game::GetFriendListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetFriendListRes()


// Cmd: Query notification list
SFDLL_EXPORT int  CSSFNetMessageID_GameGetNotificationListCmd()
{
 	return SF::Message::Game::GetNotificationListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetNotificationListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetNotificationListRes()
{
 	return SF::Message::Game::GetNotificationListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetNotificationListRes()


// Cmd: Delete notification
SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteNotificationCmd()
{
 	return SF::Message::Game::DeleteNotificationCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteNotificationCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteNotificationRes()
{
 	return SF::Message::Game::DeleteNotificationRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteNotificationRes()


// Cmd: Set notification is read
SFDLL_EXPORT int  CSSFNetMessageID_GameSetNotificationReadCmd()
{
 	return SF::Message::Game::SetNotificationReadCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetNotificationReadCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameSetNotificationReadRes()
{
 	return SF::Message::Game::SetNotificationReadRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetNotificationReadRes()


// Cmd: Accept notification
SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptNotificationCmd()
{
 	return SF::Message::Game::AcceptNotificationCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptNotificationCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptNotificationRes()
{
 	return SF::Message::Game::AcceptNotificationRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAcceptNotificationRes()


// S2C: Notify new notification
SFDLL_EXPORT int  CSSFNetMessageID_GameNotifyS2CEvt()
{
 	return SF::Message::Game::NotifyS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameNotifyS2CEvt()


// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByEMailCmd()
{
 	return SF::Message::Game::FindPlayerByEMailCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByEMailCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByEMailRes()
{
 	return SF::Message::Game::FindPlayerByEMailRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByEMailRes()


// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByPlayerIDCmd()
{
 	return SF::Message::Game::FindPlayerByPlayerIDCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByPlayerIDCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByPlayerIDRes()
{
 	return SF::Message::Game::FindPlayerByPlayerIDRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameFindPlayerByPlayerIDRes()


// Cmd: *Request Player Status Update
SFDLL_EXPORT int  CSSFNetMessageID_GameRequestPlayerStatusUpdateCmd()
{
 	return SF::Message::Game::RequestPlayerStatusUpdateCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRequestPlayerStatusUpdateCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameRequestPlayerStatusUpdateRes()
{
 	return SF::Message::Game::RequestPlayerStatusUpdateRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRequestPlayerStatusUpdateRes()


// S2C: *Notify Player Status Updated
SFDLL_EXPORT int  CSSFNetMessageID_GameNotifyPlayerStatusUpdatedS2CEvt()
{
 	return SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameNotifyPlayerStatusUpdatedS2CEvt()


// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetMessageID_GameGetRankingListCmd()
{
 	return SF::Message::Game::GetRankingListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetRankingListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetRankingListRes()
{
 	return SF::Message::Game::GetRankingListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetRankingListRes()


// Cmd: Game user game play information
SFDLL_EXPORT int  CSSFNetMessageID_GameGetUserGamePlayerInfoCmd()
{
 	return SF::Message::Game::GetUserGamePlayerInfoCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetUserGamePlayerInfoCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetUserGamePlayerInfoRes()
{
 	return SF::Message::Game::GetUserGamePlayerInfoRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetUserGamePlayerInfoRes()


// Cmd: Game game play information
SFDLL_EXPORT int  CSSFNetMessageID_GameGetGamePlayerInfoCmd()
{
 	return SF::Message::Game::GetGamePlayerInfoCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetGamePlayerInfoCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetGamePlayerInfoRes()
{
 	return SF::Message::Game::GetGamePlayerInfoRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetGamePlayerInfoRes()


// S2C: Player level up event
SFDLL_EXPORT int  CSSFNetMessageID_GameLevelUpS2CEvt()
{
 	return SF::Message::Game::LevelUpS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLevelUpS2CEvt()


// Cmd: Change NickName
SFDLL_EXPORT int  CSSFNetMessageID_GameSetNickNameCmd()
{
 	return SF::Message::Game::SetNickNameCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetNickNameCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameSetNickNameRes()
{
 	return SF::Message::Game::SetNickNameRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetNickNameRes()


// Cmd: Create Party
SFDLL_EXPORT int  CSSFNetMessageID_GameCreatePartyCmd()
{
 	return SF::Message::Game::CreatePartyCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCreatePartyCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameCreatePartyRes()
{
 	return SF::Message::Game::CreatePartyRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCreatePartyRes()


// Cmd: Join party
SFDLL_EXPORT int  CSSFNetMessageID_GameJoinPartyCmd()
{
 	return SF::Message::Game::JoinPartyCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinPartyCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameJoinPartyRes()
{
 	return SF::Message::Game::JoinPartyRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinPartyRes()


// S2C: Player Joined event
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyPlayerJoinedS2CEvt()
{
 	return SF::Message::Game::PartyPlayerJoinedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyPlayerJoinedS2CEvt()


// S2C: Party leader changed event
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyLeaderChangedS2CEvt()
{
 	return SF::Message::Game::PartyLeaderChangedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyLeaderChangedS2CEvt()


// Cmd: Leave party command
SFDLL_EXPORT int  CSSFNetMessageID_GameLeavePartyCmd()
{
 	return SF::Message::Game::LeavePartyCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeavePartyCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameLeavePartyRes()
{
 	return SF::Message::Game::LeavePartyRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeavePartyRes()


// S2C: Party Player left event
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyPlayerLeftS2CEvt()
{
 	return SF::Message::Game::PartyPlayerLeftS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyPlayerLeftS2CEvt()


// Cmd: Kick player from the party
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyKickPlayerCmd()
{
 	return SF::Message::Game::PartyKickPlayerCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyKickPlayerCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GamePartyKickPlayerRes()
{
 	return SF::Message::Game::PartyKickPlayerRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyKickPlayerRes()


// S2C: Party Player kicked message
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyPlayerKickedS2CEvt()
{
 	return SF::Message::Game::PartyPlayerKickedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyPlayerKickedS2CEvt()


// Cmd: Invite a player to the party
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyInviteCmd()
{
 	return SF::Message::Game::PartyInviteCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyInviteCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GamePartyInviteRes()
{
 	return SF::Message::Game::PartyInviteRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyInviteRes()


// S2C: Party invite requested
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyInviteRequestedS2CEvt()
{
 	return SF::Message::Game::PartyInviteRequestedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyInviteRequestedS2CEvt()


// Cmd: Send Party quick chat message
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyQuickChatMessageCmd()
{
 	return SF::Message::Game::PartyQuickChatMessageCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyQuickChatMessageCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GamePartyQuickChatMessageRes()
{
 	return SF::Message::Game::PartyQuickChatMessageRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyQuickChatMessageRes()


// S2C: Party Chatting message event
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyQuickChatMessageS2CEvt()
{
 	return SF::Message::Game::PartyQuickChatMessageS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyQuickChatMessageS2CEvt()


// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyChatMessageCmd()
{
 	return SF::Message::Game::PartyChatMessageCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyChatMessageCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GamePartyChatMessageRes()
{
 	return SF::Message::Game::PartyChatMessageRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyChatMessageRes()


// S2C: Party Chatting message event
SFDLL_EXPORT int  CSSFNetMessageID_GamePartyChatMessageS2CEvt()
{
 	return SF::Message::Game::PartyChatMessageS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePartyChatMessageS2CEvt()


// Cmd: Join to a game
SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameCmd()
{
 	return SF::Message::Game::JoinGameCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameRes()
{
 	return SF::Message::Game::JoinGameRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameRes()


// S2C: Player Joined in the game
SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerJoinedS2CEvt()
{
 	return SF::Message::Game::PlayerJoinedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerJoinedS2CEvt()


// Cmd: Leave Game
SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameCmd()
{
 	return SF::Message::Game::LeaveGameCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameRes()
{
 	return SF::Message::Game::LeaveGameRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameRes()


// S2C: Player left event
SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerLeftS2CEvt()
{
 	return SF::Message::Game::PlayerLeftS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerLeftS2CEvt()


// Cmd: Kick player
SFDLL_EXPORT int  CSSFNetMessageID_GameKickPlayerCmd()
{
 	return SF::Message::Game::KickPlayerCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameKickPlayerCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameKickPlayerRes()
{
 	return SF::Message::Game::KickPlayerRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameKickPlayerRes()


// S2C: Player kicked
SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerKickedS2CEvt()
{
 	return SF::Message::Game::PlayerKickedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerKickedS2CEvt()


// Cmd: Assign role + Game state reset
SFDLL_EXPORT int  CSSFNetMessageID_GameAssignRoleCmd()
{
 	return SF::Message::Game::AssignRoleCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAssignRoleCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameAssignRoleRes()
{
 	return SF::Message::Game::AssignRoleRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAssignRoleRes()


// S2C: Role assigned event
SFDLL_EXPORT int  CSSFNetMessageID_GameRoleAssignedS2CEvt()
{
 	return SF::Message::Game::RoleAssignedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRoleAssignedS2CEvt()


// Cmd: Send chatting message to the game
SFDLL_EXPORT int  CSSFNetMessageID_GameChatMessageCmd()
{
 	return SF::Message::Game::ChatMessageCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatMessageCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameChatMessageRes()
{
 	return SF::Message::Game::ChatMessageRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatMessageRes()


// S2C: Chatting message event 
SFDLL_EXPORT int  CSSFNetMessageID_GameChatMessageS2CEvt()
{
 	return SF::Message::Game::ChatMessageS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatMessageS2CEvt()


// Cmd: Advance game
SFDLL_EXPORT int  CSSFNetMessageID_GameAdvanceGameCmd()
{
 	return SF::Message::Game::AdvanceGameCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAdvanceGameCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameAdvanceGameRes()
{
 	return SF::Message::Game::AdvanceGameRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameAdvanceGameRes()


// S2C: The game state is advanced
SFDLL_EXPORT int  CSSFNetMessageID_GameGameAdvancedS2CEvt()
{
 	return SF::Message::Game::GameAdvancedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameAdvancedS2CEvt()


// S2C: Game is ended
SFDLL_EXPORT int  CSSFNetMessageID_GameGameEndedS2CEvt()
{
 	return SF::Message::Game::GameEndedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameEndedS2CEvt()


// Cmd: Vote game advance
SFDLL_EXPORT int  CSSFNetMessageID_GameVoteGameAdvanceCmd()
{
 	return SF::Message::Game::VoteGameAdvanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameVoteGameAdvanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameVoteGameAdvanceRes()
{
 	return SF::Message::Game::VoteGameAdvanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameVoteGameAdvanceRes()


// S2C: GameAdvance is Voted
SFDLL_EXPORT int  CSSFNetMessageID_GameGameAdvanceVotedS2CEvt()
{
 	return SF::Message::Game::GameAdvanceVotedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameAdvanceVotedS2CEvt()


// Cmd: Vote
SFDLL_EXPORT int  CSSFNetMessageID_GameVoteCmd()
{
 	return SF::Message::Game::VoteCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameVoteCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameVoteRes()
{
 	return SF::Message::Game::VoteRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameVoteRes()


// S2C: Player Voted
SFDLL_EXPORT int  CSSFNetMessageID_GameVotedS2CEvt()
{
 	return SF::Message::Game::VotedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameVotedS2CEvt()


// S2C: Vote is ended
SFDLL_EXPORT int  CSSFNetMessageID_GameVoteEndS2CEvt()
{
 	return SF::Message::Game::VoteEndS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameVoteEndS2CEvt()


// S2C: Player Killed
SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerKilledS2CEvt()
{
 	return SF::Message::Game::PlayerKilledS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerKilledS2CEvt()


// S2C: Player Voted
SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerRevealedS2CEvt()
{
 	return SF::Message::Game::PlayerRevealedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GamePlayerRevealedS2CEvt()


// Cmd: Play again with the current players
SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayAgainCmd()
{
 	return SF::Message::Game::GamePlayAgainCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayAgainCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayAgainRes()
{
 	return SF::Message::Game::GamePlayAgainRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayAgainRes()


// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayAgainS2CEvt()
{
 	return SF::Message::Game::GamePlayAgainS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayAgainS2CEvt()


// Cmd: Player. reveal a player
SFDLL_EXPORT int  CSSFNetMessageID_GameGameRevealPlayerCmd()
{
 	return SF::Message::Game::GameRevealPlayerCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameRevealPlayerCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGameRevealPlayerRes()
{
 	return SF::Message::Game::GameRevealPlayerRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameRevealPlayerRes()


// Cmd: Player. revive himself
SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerReviveCmd()
{
 	return SF::Message::Game::GamePlayerReviveCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerReviveCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerReviveRes()
{
 	return SF::Message::Game::GamePlayerReviveRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerReviveRes()


// S2C: Player is revived
SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerRevivedS2CEvt()
{
 	return SF::Message::Game::GamePlayerRevivedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerRevivedS2CEvt()


// Cmd: Player. reset ranking
SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerResetRankCmd()
{
 	return SF::Message::Game::GamePlayerResetRankCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerResetRankCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerResetRankRes()
{
 	return SF::Message::Game::GamePlayerResetRankRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGamePlayerResetRankRes()


// Cmd: Request Game match
SFDLL_EXPORT int  CSSFNetMessageID_GameRequestGameMatchCmd()
{
 	return SF::Message::Game::RequestGameMatchCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRequestGameMatchCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameRequestGameMatchRes()
{
 	return SF::Message::Game::RequestGameMatchRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameRequestGameMatchRes()


// S2C: Game matched
SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchedS2CEvt()
{
 	return SF::Message::Game::GameMatchedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchedS2CEvt()


// S2C: Game match failed
SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchFailedS2CEvt()
{
 	return SF::Message::Game::GameMatchFailedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchFailedS2CEvt()


// S2C: Game matching started
SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchingStartedS2CEvt()
{
 	return SF::Message::Game::GameMatchingStartedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchingStartedS2CEvt()


// Cmd: Cancel Game match
SFDLL_EXPORT int  CSSFNetMessageID_GameCancelGameMatchCmd()
{
 	return SF::Message::Game::CancelGameMatchCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCancelGameMatchCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameCancelGameMatchRes()
{
 	return SF::Message::Game::CancelGameMatchRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCancelGameMatchRes()


// S2C: game matching canceled
SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchingCanceledS2CEvt()
{
 	return SF::Message::Game::GameMatchingCanceledS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGameMatchingCanceledS2CEvt()


// Cmd: Buy shop item prepare
SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemPrepareCmd()
{
 	return SF::Message::Game::BuyShopItemPrepareCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemPrepareCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemPrepareRes()
{
 	return SF::Message::Game::BuyShopItemPrepareRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemPrepareRes()


// Cmd: Buy shop item
SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemCmd()
{
 	return SF::Message::Game::BuyShopItemCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemRes()
{
 	return SF::Message::Game::BuyShopItemRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameBuyShopItemRes()


// Cmd: Create or Join Chat channel
SFDLL_EXPORT int  CSSFNetMessageID_GameCreateOrJoinChatChannelCmd()
{
 	return SF::Message::Game::CreateOrJoinChatChannelCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCreateOrJoinChatChannelCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameCreateOrJoinChatChannelRes()
{
 	return SF::Message::Game::CreateOrJoinChatChannelRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCreateOrJoinChatChannelRes()


// Cmd: Join
SFDLL_EXPORT int  CSSFNetMessageID_GameJoinChatChannelCmd()
{
 	return SF::Message::Game::JoinChatChannelCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinChatChannelCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameJoinChatChannelRes()
{
 	return SF::Message::Game::JoinChatChannelRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinChatChannelRes()


// S2C: Player Joined event
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelPlayerJoinedS2CEvt()
{
 	return SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelPlayerJoinedS2CEvt()


// S2C: ChatChannel leader changed event
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelLeaderChangedS2CEvt()
{
 	return SF::Message::Game::ChatChannelLeaderChangedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelLeaderChangedS2CEvt()


// Cmd: Leave ChatChannel command
SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveChatChannelCmd()
{
 	return SF::Message::Game::LeaveChatChannelCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveChatChannelCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveChatChannelRes()
{
 	return SF::Message::Game::LeaveChatChannelRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveChatChannelRes()


// S2C: ChatChannel Player left event
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelPlayerLeftS2CEvt()
{
 	return SF::Message::Game::ChatChannelPlayerLeftS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelPlayerLeftS2CEvt()


// Cmd: Kick player from the ChatChannel
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelKickPlayerCmd()
{
 	return SF::Message::Game::ChatChannelKickPlayerCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelKickPlayerCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelKickPlayerRes()
{
 	return SF::Message::Game::ChatChannelKickPlayerRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelKickPlayerRes()


// S2C: ChatChannel Player kicked message
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelPlayerKickedS2CEvt()
{
 	return SF::Message::Game::ChatChannelPlayerKickedS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelPlayerKickedS2CEvt()


// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelChatMessageCmd()
{
 	return SF::Message::Game::ChatChannelChatMessageCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelChatMessageCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelChatMessageRes()
{
 	return SF::Message::Game::ChatChannelChatMessageRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelChatMessageRes()


// S2C: ChatChannel Chatting message event
SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelChatMessageS2CEvt()
{
 	return SF::Message::Game::ChatChannelChatMessageS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameChatChannelChatMessageS2CEvt()


// Cmd: Give my stamina to other player
SFDLL_EXPORT int  CSSFNetMessageID_GameGiveStaminaCmd()
{
 	return SF::Message::Game::GiveStaminaCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGiveStaminaCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGiveStaminaRes()
{
 	return SF::Message::Game::GiveStaminaRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGiveStaminaRes()


// Cmd: For debug, Change configue preset
SFDLL_EXPORT int  CSSFNetMessageID_GameSetPresetGameConfigIDCmd()
{
 	return SF::Message::Game::SetPresetGameConfigIDCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetPresetGameConfigIDCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameSetPresetGameConfigIDRes()
{
 	return SF::Message::Game::SetPresetGameConfigIDRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSetPresetGameConfigIDRes()


// Cmd: For Debug
SFDLL_EXPORT int  CSSFNetMessageID_GameGainGameResourceCmd()
{
 	return SF::Message::Game::GainGameResourceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGainGameResourceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGainGameResourceRes()
{
 	return SF::Message::Game::GainGameResourceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGainGameResourceRes()










