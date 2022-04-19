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
#include "Protocol/GameMsgClass.h"
#include "SharpCPP/SFCSUtil.h"



using namespace SF;


// C2S: Client heartbeat
SFDLL_EXPORT int  CSSFNetMessageID_GameHeartbeatC2SEvt()
{
 	return SF::Message::Game::HeartbeatC2SEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameHeartbeatC2SEvt()


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


// Cmd: Get Ranking list
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


// Cmd: Join to a game instance
SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameInstanceCmd()
{
 	return SF::Message::Game::JoinGameInstanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameInstanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameInstanceRes()
{
 	return SF::Message::Game::JoinGameInstanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameJoinGameInstanceRes()


// Cmd: Leave game instance
SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameInstanceCmd()
{
 	return SF::Message::Game::LeaveGameInstanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameInstanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameInstanceRes()
{
 	return SF::Message::Game::LeaveGameInstanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameLeaveGameInstanceRes()


// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetMessageID_GameSearchGameInstanceCmd()
{
 	return SF::Message::Game::SearchGameInstanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSearchGameInstanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameSearchGameInstanceRes()
{
 	return SF::Message::Game::SearchGameInstanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSearchGameInstanceRes()


// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataInGameInstanceCmd()
{
 	return SF::Message::Game::GetCharacterDataInGameInstanceCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataInGameInstanceCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataInGameInstanceRes()
{
 	return SF::Message::Game::GetCharacterDataInGameInstanceRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataInGameInstanceRes()


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


// Cmd: Chat channel sending chatting message
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


// Cmd: Wisper(tell) other player chatting
SFDLL_EXPORT int  CSSFNetMessageID_GameWisperMessageCmd()
{
 	return SF::Message::Game::WisperMessageCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameWisperMessageCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameWisperMessageRes()
{
 	return SF::Message::Game::WisperMessageRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameWisperMessageRes()


// S2C: Other player wispered(tell) to me message event
SFDLL_EXPORT int  CSSFNetMessageID_GameWisperMessageS2CEvt()
{
 	return SF::Message::Game::WisperMessageS2CEvt::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameWisperMessageS2CEvt()


// Cmd: Create character
SFDLL_EXPORT int  CSSFNetMessageID_GameCreateCharacterCmd()
{
 	return SF::Message::Game::CreateCharacterCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCreateCharacterCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameCreateCharacterRes()
{
 	return SF::Message::Game::CreateCharacterRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCreateCharacterRes()


// Cmd: Delete character
SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteCharacterCmd()
{
 	return SF::Message::Game::DeleteCharacterCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteCharacterCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteCharacterRes()
{
 	return SF::Message::Game::DeleteCharacterRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameDeleteCharacterRes()


// Cmd: Get character list
SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterListCmd()
{
 	return SF::Message::Game::GetCharacterListCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterListCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterListRes()
{
 	return SF::Message::Game::GetCharacterListRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterListRes()


// Cmd: 
SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataCmd()
{
 	return SF::Message::Game::GetCharacterDataCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataRes()
{
 	return SF::Message::Game::GetCharacterDataRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameGetCharacterDataRes()


// Cmd: Select character
SFDLL_EXPORT int  CSSFNetMessageID_GameSelectCharacterCmd()
{
 	return SF::Message::Game::SelectCharacterCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSelectCharacterCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameSelectCharacterRes()
{
 	return SF::Message::Game::SelectCharacterRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameSelectCharacterRes()


// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetMessageID_GameCallFunctionCmd()
{
 	return SF::Message::Game::CallFunctionCmd::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCallFunctionCmd()


SFDLL_EXPORT int  CSSFNetMessageID_GameCallFunctionRes()
{
 	return SF::Message::Game::CallFunctionRes::MID.IDSeq.MsgID;
} // SFDLL_EXPORT int  CSSFNetMessageID_GameCallFunctionRes()










