////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : Game Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/Message/GameMsgClass.h"
#include "SFCSUtil.h"



using namespace SF;


// C2S: Client heart bit
SFDLL_EXPORT int  CSSFNetAdapter_GameHeartBitC2SEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::HeartBitC2SEvt::Create(pConnection->GetHeap());
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameHeartBitC2SEvt( intptr_t InNativeConnectionHandle )



// Cmd: Player connected from a login server and moved to game server
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinGameServerCmd::Create(pConnection->GetHeap(), InTransactionID, InAccID, InTicket, InLoginEntityUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )


// Cmd: player complition statues
SFDLL_EXPORT int  CSSFNetAdapter_GameGetComplitionStateCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetComplitionStateCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetComplitionStateCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Player complition state
SFDLL_EXPORT int  CSSFNetAdapter_GameSetComplitionStateCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InComplitionState )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetComplitionStateCmd::Create(pConnection->GetHeap(), InTransactionID,InComplitionState);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetComplitionStateCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InComplitionState )


// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InGCMRegisteredID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RegisterGCMCmd::Create(pConnection->GetHeap(), InTransactionID,InGCMRegisteredID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InGCMRegisteredID )


// Cmd: Unregister Google notification service ID
SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InGCMRegisteredID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::UnregisterGCMCmd::Create(pConnection->GetHeap(), InTransactionID,InGCMRegisteredID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InGCMRegisteredID )


// Cmd: Invite friend
SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::InviteFriendCmd::Create(pConnection->GetHeap(), InTransactionID, InFriendID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InFriendID )


// Cmd: Accept friend request
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InInviterID, FacebookUID InInviterFacebookUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AcceptFriendRequestCmd::Create(pConnection->GetHeap(), InTransactionID, InInviterID, InInviterFacebookUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InInviterID, FacebookUID InInviterFacebookUID )


// Cmd: Remove friden form the friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RemoveFriendCmd::Create(pConnection->GetHeap(), InTransactionID, InFriendID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InFriendID )


// Cmd: Get friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t InStartIndex, uint16_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetFriendListCmd::Create(pConnection->GetHeap(), InTransactionID, InStartIndex, InCount);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t InStartIndex, uint16_t InCount )


// Cmd: Query notification list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetNotificationListCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Delete notification
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::DeleteNotificationCmd::Create(pConnection->GetHeap(), InTransactionID, InNotificationID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InNotificationID )


// Cmd: Set notification is read
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetNotificationReadCmd::Create(pConnection->GetHeap(), InTransactionID, InNotificationID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InNotificationID )


// Cmd: Accept notification
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AcceptNotificationCmd::Create(pConnection->GetHeap(), InTransactionID, InNotificationID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InNotificationID )


// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InPlayerEMail )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByEMailCmd::Create(pConnection->GetHeap(), InTransactionID,InPlayerEMail);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InPlayerEMail )


// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByPlayerIDCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InPlayerID )


// Cmd: *Request Player Status Update
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTargetPlayerID,const AccountID* InTargetPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RequestPlayerStatusUpdateCmd::Create(pConnection->GetHeap(), InTransactionID,SF::ArrayView<AccountID>(_sizeOfInTargetPlayerID, _sizeOfInTargetPlayerID, const_cast<AccountID*>(InTargetPlayerID)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTargetPlayerID,const AccountID* InTargetPlayerID )


// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint8_t InRankingType, uint8_t InBaseRanking, uint8_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetRankingListCmd::Create(pConnection->GetHeap(), InTransactionID, InRankingType, InBaseRanking, InCount);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint8_t InRankingType, uint8_t InBaseRanking, uint8_t InCount )


// Cmd: Game user game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetUserGamePlayerInfoCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Game game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetGamePlayerInfoCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InPlayerID )


// Cmd: Change NickName
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InNickName, uint8_t InIsCostFree )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetNickNameCmd::Create(pConnection->GetHeap(), InTransactionID,InNickName, InIsCostFree);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InNickName, uint8_t InIsCostFree )


// Cmd: Create Party
SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreatePartyCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Join party
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPartyUID, AccountID InInviterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinPartyCmd::Create(pConnection->GetHeap(), InTransactionID, InPartyUID, InInviterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPartyUID, AccountID InInviterID )


// Cmd: Leave party command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPartyUID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeavePartyCmd::Create(pConnection->GetHeap(), InTransactionID, InPartyUID, InPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPartyUID, AccountID InPlayerID )


// Cmd: Kick player from the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPartyUID, AccountID InPlayerID, AccountID InPlayerToKick )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyKickPlayerCmd::Create(pConnection->GetHeap(), InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InPartyUID, AccountID InPlayerID, AccountID InPlayerToKick )


// Cmd: Invite a player to the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InInviteTargetID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyInviteCmd::Create(pConnection->GetHeap(), InTransactionID, InInviteTargetID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InInviteTargetID )


// Cmd: Send Party quick chat message
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InQuickChatID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyQuickChatMessageCmd::Create(pConnection->GetHeap(), InTransactionID, InQuickChatID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InQuickChatID )


// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyChatMessageCmd::Create(pConnection->GetHeap(), InTransactionID,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InChatMessage )


// Cmd: Join to a game
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InPlayerID, AuthTicket InTicket, uint64_t InInsUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinGameCmd::Create(pConnection->GetHeap(), InTransactionID, InPlayerID, InTicket, InInsUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InPlayerID, AuthTicket InTicket, uint64_t InInsUID )


// Cmd: Leave Game
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeaveGameCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )


// Cmd: Kick player
SFDLL_EXPORT int  CSSFNetAdapter_GameKickPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AccountID InPlayerToKick )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::KickPlayerCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID, InPlayerToKick);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameKickPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AccountID InPlayerToKick )


// Cmd: Assign role + Game state reset
SFDLL_EXPORT int  CSSFNetAdapter_GameAssignRoleCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AssignRoleCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAssignRoleCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )


// Cmd: Send chatting message to the game
SFDLL_EXPORT int  CSSFNetAdapter_GameChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InChatMessage, uint8_t InRole )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatMessageCmd::Create(pConnection->GetHeap(), InTransactionID,InChatMessage, InRole);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InChatMessage, uint8_t InRole )


// Cmd: Advance game
SFDLL_EXPORT int  CSSFNetAdapter_GameAdvanceGameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AdvanceGameCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAdvanceGameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )


// Cmd: Vote game advance
SFDLL_EXPORT int  CSSFNetAdapter_GameVoteGameAdvanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::VoteGameAdvanceCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameVoteGameAdvanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket )


// Cmd: Vote
SFDLL_EXPORT int  CSSFNetAdapter_GameVoteCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket, AccountID InVoteTarget, uint32_t InActionSerial )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::VoteCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket, InVoteTarget, InActionSerial);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameVoteCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, AccountID InPlayerID, AuthTicket InTicket, AccountID InVoteTarget, uint32_t InActionSerial )


// Cmd: Play again with the current players
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayAgainCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayAgainCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayAgainCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Player. reveal a player
SFDLL_EXPORT int  CSSFNetAdapter_GameGameRevealPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTargetPlayerID,const AccountID* InTargetPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameRevealPlayerCmd::Create(pConnection->GetHeap(), InTransactionID,SF::ArrayView<AccountID>(_sizeOfInTargetPlayerID, _sizeOfInTargetPlayerID, const_cast<AccountID*>(InTargetPlayerID)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameRevealPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInTargetPlayerID,const AccountID* InTargetPlayerID )


// Cmd: Player. revive himself
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerReviveCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayerReviveCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerReviveCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Player. reset ranking
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerResetRankCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayerResetRankCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerResetRankCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Request Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint8_t InNumPlayer, uint8_t InRequestRole )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RequestGameMatchCmd::Create(pConnection->GetHeap(), InTransactionID, InNumPlayer, InRequestRole);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint8_t InNumPlayer, uint8_t InRequestRole )


// Cmd: Cancel Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CancelGameMatchCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: Buy shop item prepare
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InShopItemID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::BuyShopItemPrepareCmd::Create(pConnection->GetHeap(), InTransactionID, InShopItemID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InShopItemID )


// Cmd: Buy shop item
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, uint16_t _sizeOfInPurchaseToken,const uint8_t* InPurchaseToken )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::BuyShopItemCmd::Create(pConnection->GetHeap(), InTransactionID, InShopItemID,InPlatform,InPackageName,InPurchaseTransactionID,SF::ArrayView<uint8_t>(_sizeOfInPurchaseToken, _sizeOfInPurchaseToken, const_cast<uint8_t*>(InPurchaseToken)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, uint16_t _sizeOfInPurchaseToken,const uint8_t* InPurchaseToken )


// Cmd: Create or Join Chat channel
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InChannelName, const char* InPasscode )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateOrJoinChatChannelCmd::Create(pConnection->GetHeap(), InTransactionID,InChannelName,InPasscode);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InChannelName, const char* InPasscode )


// Cmd: Join
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InInviterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinChatChannelCmd::Create(pConnection->GetHeap(), InTransactionID, InChatUID, InInviterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InInviterID )


// Cmd: Leave ChatChannel command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeaveChatChannelCmd::Create(pConnection->GetHeap(), InTransactionID, InChatUID, InPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InPlayerID )


// Cmd: Kick player from the ChatChannel
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InPlayerID, AccountID InPlayerToKick )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelKickPlayerCmd::Create(pConnection->GetHeap(), InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InPlayerID, AccountID InPlayerToKick )


// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelChatMessageCmd::Create(pConnection->GetHeap(), InTransactionID, InChatUID,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, const char* InChatMessage )


// Cmd: Create character
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InCharacterName, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateCharacterCmd::Create(pConnection->GetHeap(), InTransactionID,InCharacterName,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InCharacterName, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )


// Cmd: Remove character
SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RemoveCharacterCmd::Create(pConnection->GetHeap(), InTransactionID, InCharacterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int32_t InCharacterID )


// Cmd: Get character list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterListCmd::Create(pConnection->GetHeap(), InTransactionID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID )


// Cmd: 
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int32_t InCharacterID, const char* InAttributeNames )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterDataCmd::Create(pConnection->GetHeap(), InTransactionID, InCharacterID,InAttributeNames);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, int32_t InCharacterID, const char* InAttributeNames )


// Cmd: Give my stamina to other player
SFDLL_EXPORT int  CSSFNetAdapter_GameGiveStaminaCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InTargetPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GiveStaminaCmd::Create(pConnection->GetHeap(), InTransactionID, InTargetPlayer);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGiveStaminaCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InTargetPlayer )


// Cmd: For debug, Change configue preset
SFDLL_EXPORT int  CSSFNetAdapter_GameSetPresetGameConfigIDCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InPresetID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetPresetGameConfigIDCmd::Create(pConnection->GetHeap(), InTransactionID, InPresetID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetPresetGameConfigIDCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InPresetID )




// Cmd: Player connected from a login server and moved to game server
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InNickName, uint64_t InGameUID, uint64_t InPartyUID, AccountID InPartyLeaderID, const MatchingQueueTicket& InMatchingTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinGameServerRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InNickName, InGameUID, InPartyUID, InPartyLeaderID,InMatchingTicket);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InNickName, uint64_t InGameUID, uint64_t InPartyUID, AccountID InPartyLeaderID, const MatchingQueueTicket& InMatchingTicket )



// Cmd: player complition statues
SFDLL_EXPORT int  CSSFNetAdapter_GameGetComplitionStateRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InComplitionState )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetComplitionStateRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InComplitionState);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetComplitionStateRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const char* InComplitionState )



// Cmd: Player complition state
SFDLL_EXPORT int  CSSFNetAdapter_GameSetComplitionStateRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetComplitionStateRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetComplitionStateRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RegisterGCMRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Unregister Google notification service ID
SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::UnregisterGCMRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Invite friend
SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::InviteFriendRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Accept friend request
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const FriendInformation& InNewFriend )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AcceptFriendRequestRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InNewFriend);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const FriendInformation& InNewFriend )



// S2C: Notification for friend request is accepted
SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt( intptr_t InNativeConnectionHandle, const FriendInformation& InAccepter )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FriendRequestAcceptedS2CEvt::Create(pConnection->GetHeap(),InAccepter);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt( intptr_t InNativeConnectionHandle, const FriendInformation& InAccepter )



// Cmd: Remove friden form the friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RemoveFriendRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InFriendID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, AccountID InFriendID )



// S2C: Friend removed
SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRemovedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FriendRemovedS2CEvt::Create(pConnection->GetHeap(), InFriendID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRemovedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InFriendID )



// Cmd: Get friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t InMaxFriendSlot, uint16_t InTotalNumberOfFriends, uint16_t InStartIndex, uint16_t _sizeOfInFriendList,const FriendInformation* InFriendList )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetFriendListRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,SF::ArrayView<FriendInformation>(_sizeOfInFriendList, _sizeOfInFriendList, const_cast<FriendInformation*>(InFriendList)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t InMaxFriendSlot, uint16_t InTotalNumberOfFriends, uint16_t InStartIndex, uint16_t _sizeOfInFriendList,const FriendInformation* InFriendList )



// Cmd: Query notification list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetNotificationListRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Delete notification
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::DeleteNotificationRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InNotificationID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InNotificationID )



// Cmd: Set notification is read
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetNotificationReadRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InNotificationID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InNotificationID )



// Cmd: Accept notification
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AcceptNotificationRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InNotificationID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InNotificationID )



// S2C: Notify new notification
SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InNotificationID, uint32_t InNotificationType, uint64_t InMessageParam0, uint64_t InMessageParam1, const char* InMessageText, uint8_t InIsRead, uint64_t InTimeStamp )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::NotifyS2CEvt::Create(pConnection->GetHeap(), InNotificationID, InNotificationType, InMessageParam0, InMessageParam1,InMessageText, InIsRead, InTimeStamp);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InNotificationID, uint32_t InNotificationType, uint64_t InMessageParam0, uint64_t InMessageParam1, const char* InMessageText, uint8_t InIsRead, uint64_t InTimeStamp )



// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const PlayerInformation& InPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByEMailRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InPlayer);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const PlayerInformation& InPlayer )



// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const PlayerInformation& InPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByPlayerIDRes::Create(pConnection->GetHeap(), InTransactionID, InResult,InPlayer);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, const PlayerInformation& InPlayer )



// Cmd: *Request Player Status Update
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RequestPlayerStatusUpdateRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: *Notify Player Status Updated
SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InPlayerID, uint32_t InLatestActiveTime, uint8_t InIsInGame )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::Create(pConnection->GetHeap(), InPlayerID, InLatestActiveTime, InIsInGame);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InPlayerID, uint32_t InLatestActiveTime, uint8_t InIsInGame )



// Cmd: Get Ranking lise
SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetRankingListRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )



// Cmd: Game user game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetUserGamePlayerInfoRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: Game game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, AccountID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetGamePlayerInfoRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, AccountID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// S2C: Player level up event
SFDLL_EXPORT int  CSSFNetAdapter_GameLevelUpS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InCurrentTotalExp, uint32_t InCurrentLevel )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LevelUpS2CEvt::Create(pConnection->GetHeap(), InCurrentTotalExp, InCurrentLevel);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLevelUpS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InCurrentTotalExp, uint32_t InCurrentLevel )



// Cmd: Change NickName
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetNickNameRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// Cmd: Create Party
SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPartyUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreatePartyRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPartyUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPartyUID )



// Cmd: Join party
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPartyUID, AccountID InPartyLeaderID, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinPartyRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPartyUID, AccountID InPartyLeaderID, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData )



// S2C: Player Joined event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, const PlayerInformation& InJoinedPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyPlayerJoinedS2CEvt::Create(pConnection->GetHeap(), InPartyUID,InJoinedPlayer);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, const PlayerInformation& InJoinedPlayer )



// S2C: Party leader changed event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InNewLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyLeaderChangedS2CEvt::Create(pConnection->GetHeap(), InPartyUID, InNewLeaderID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InNewLeaderID )



// Cmd: Leave party command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeavePartyRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Party Player left event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InLeftPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyPlayerLeftS2CEvt::Create(pConnection->GetHeap(), InPartyUID, InLeftPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InLeftPlayerID )



// Cmd: Kick player from the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyKickPlayerRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Party Player kicked message
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyPlayerKickedS2CEvt::Create(pConnection->GetHeap(), InPartyUID, InKickedPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InKickedPlayerID )



// Cmd: Invite a player to the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyInviteRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Party invite requested
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRequestedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InInviterID, const char* InInviterName, uint64_t InPartyToJoinUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyInviteRequestedS2CEvt::Create(pConnection->GetHeap(), InInviterID,InInviterName, InPartyToJoinUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRequestedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InInviterID, const char* InInviterName, uint64_t InPartyToJoinUID )



// Cmd: Send Party quick chat message
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyQuickChatMessageRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Party Chatting message event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, uint32_t InQuickChatID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyQuickChatMessageS2CEvt::Create(pConnection->GetHeap(), InSenderID, InQuickChatID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, uint32_t InQuickChatID )



// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyChatMessageRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Party Chatting message event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, const char* InSenderName, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PartyChatMessageS2CEvt::Create(pConnection->GetHeap(), InSenderID,InSenderName,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, const char* InSenderName, const char* InChatMessage )



// Cmd: Join to a game
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay, uint8_t InMaxPlayer, uint8_t InPlayerIndex, uint8_t InPlayerCharacter, uint8_t InRole, uint8_t InDead, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData, uint16_t _sizeOfInGameLogData,const uint8_t* InGameLogData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinGameRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InInsUID, InTimeStamp,(uint8_t) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)),SF::ArrayView<uint8_t>(_sizeOfInGameLogData, _sizeOfInGameLogData, const_cast<uint8_t*>(InGameLogData)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay, uint8_t InMaxPlayer, uint8_t InPlayerIndex, uint8_t InPlayerCharacter, uint8_t InRole, uint8_t InDead, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData, uint16_t _sizeOfInGameLogData,const uint8_t* InGameLogData )



// S2C: Player Joined in the game
SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, const PlayerInformation& InJoinedPlayer, uint8_t InJoinedPlayerRole, uint8_t InJoinedPlayerDead, uint8_t InJoinedPlayerIndex, uint8_t InJoinedPlayerCharacter )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PlayerJoinedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID,InJoinedPlayer, InJoinedPlayerRole, InJoinedPlayerDead, InJoinedPlayerIndex, InJoinedPlayerCharacter);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, const PlayerInformation& InJoinedPlayer, uint8_t InJoinedPlayerRole, uint8_t InJoinedPlayerDead, uint8_t InJoinedPlayerIndex, uint8_t InJoinedPlayerCharacter )



// Cmd: Leave Game
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeaveGameRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Player left event
SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InLeftPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PlayerLeftS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InLeftPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InLeftPlayerID )



// Cmd: Kick player
SFDLL_EXPORT int  CSSFNetAdapter_GameKickPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::KickPlayerRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameKickPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Player kicked
SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PlayerKickedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InKickedPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InKickedPlayerID )



// Cmd: Assign role + Game state reset
SFDLL_EXPORT int  CSSFNetAdapter_GameAssignRoleRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AssignRoleRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAssignRoleRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Role assigned event
SFDLL_EXPORT int  CSSFNetAdapter_GameRoleAssignedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InPlayerID, uint8_t InRole )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RoleAssignedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InPlayerID, InRole);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRoleAssignedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InPlayerID, uint8_t InRole )



// Cmd: Send chatting message to the game
SFDLL_EXPORT int  CSSFNetAdapter_GameChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatMessageRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Chatting message event 
SFDLL_EXPORT int  CSSFNetAdapter_GameChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, uint8_t InRole, const char* InSenderName, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatMessageS2CEvt::Create(pConnection->GetHeap(), InSenderID, InRole,InSenderName,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, uint8_t InRole, const char* InSenderName, const char* InChatMessage )



// Cmd: Advance game
SFDLL_EXPORT int  CSSFNetAdapter_GameAdvanceGameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AdvanceGameRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAdvanceGameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: The game state is advanced
SFDLL_EXPORT int  CSSFNetAdapter_GameGameAdvancedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameAdvancedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InTimeStamp,(uint8_t) InGameState, InDay);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameAdvancedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay )



// S2C: Game is ended
SFDLL_EXPORT int  CSSFNetAdapter_GameGameEndedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, int InWinner, uint32_t InGainedExp, uint32_t InGainedGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameEndedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID,(uint8_t) InWinner, InGainedExp, InGainedGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameEndedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, int InWinner, uint32_t InGainedExp, uint32_t InGainedGameMoney )



// Cmd: Vote game advance
SFDLL_EXPORT int  CSSFNetAdapter_GameVoteGameAdvanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::VoteGameAdvanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameVoteGameAdvanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: GameAdvance is Voted
SFDLL_EXPORT int  CSSFNetAdapter_GameGameAdvanceVotedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InVoter )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameAdvanceVotedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InVoter);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameAdvanceVotedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InVoter )



// Cmd: Vote
SFDLL_EXPORT int  CSSFNetAdapter_GameVoteRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::VoteRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameVoteRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Player Voted
SFDLL_EXPORT int  CSSFNetAdapter_GameVotedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InVoter, AccountID InVotedTarget )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::VotedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InVoter, InVotedTarget);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameVotedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InVoter, AccountID InVotedTarget )



// S2C: Vote is ended
SFDLL_EXPORT int  CSSFNetAdapter_GameVoteEndS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, uint16_t _sizeOfInVoted,const AccountID* InVoted )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::VoteEndS2CEvt::Create(pConnection->GetHeap(), InGameInsUID,SF::ArrayView<AccountID>(_sizeOfInVoted, _sizeOfInVoted, const_cast<AccountID*>(InVoted)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameVoteEndS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, uint16_t _sizeOfInVoted,const AccountID* InVoted )



// S2C: Player Killed
SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerKilledS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InKilledPlayer, int InReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PlayerKilledS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InKilledPlayer,(uint8_t) InReason);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerKilledS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InKilledPlayer, int InReason )



// S2C: Player Voted
SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerRevealedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InRevealedPlayerID, uint8_t InRole, int InReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::PlayerRevealedS2CEvt::Create(pConnection->GetHeap(), InGameInsUID, InRevealedPlayerID, InRole,(uint8_t) InReason);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePlayerRevealedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InGameInsUID, AccountID InRevealedPlayerID, uint8_t InRole, int InReason )



// Cmd: Play again with the current players
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayAgainRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayAgainRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayAgainRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayAgainS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InLeadPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayAgainS2CEvt::Create(pConnection->GetHeap(), InPartyUID, InLeadPlayer);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayAgainS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InLeadPlayer )



// Cmd: Player. reveal a player
SFDLL_EXPORT int  CSSFNetAdapter_GameGameRevealPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRevealedPlayerID,const AccountID* InRevealedPlayerID, uint16_t _sizeOfInRevealedRole,const uint8_t* InRevealedRole, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameRevealPlayerRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<AccountID>(_sizeOfInRevealedPlayerID, _sizeOfInRevealedPlayerID, const_cast<AccountID*>(InRevealedPlayerID)),SF::ArrayView<uint8_t>(_sizeOfInRevealedRole, _sizeOfInRevealedRole, const_cast<uint8_t*>(InRevealedRole)), InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameRevealPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInRevealedPlayerID,const AccountID* InRevealedPlayerID, uint16_t _sizeOfInRevealedRole,const uint8_t* InRevealedRole, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// Cmd: Player. revive himself
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerReviveRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayerReviveRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerReviveRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// S2C: Player is revived
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerRevivedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InRevivedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayerRevivedS2CEvt::Create(pConnection->GetHeap(), InRevivedPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerRevivedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InRevivedPlayerID )



// Cmd: Player. reset ranking
SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerResetRankRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GamePlayerResetRankRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGamePlayerResetRankRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// Cmd: Request Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RequestGameMatchRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// S2C: Game matched
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay, uint8_t InMaxPlayer, uint8_t InPlayerIndex, uint8_t InPlayerCharacter, uint8_t InRole, uint8_t InDead, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData, uint16_t _sizeOfInGameLogData,const uint8_t* InGameLogData, uint32_t InStamina, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameMatchedS2CEvt::Create(pConnection->GetHeap(), InInsUID, InTimeStamp,(uint8_t) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)),SF::ArrayView<uint8_t>(_sizeOfInGameLogData, _sizeOfInGameLogData, const_cast<uint8_t*>(InGameLogData)), InStamina, InTotalGem, InTotalGameMoney);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay, uint8_t InMaxPlayer, uint8_t InPlayerIndex, uint8_t InPlayerCharacter, uint8_t InRole, uint8_t InDead, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData, uint16_t _sizeOfInGameLogData,const uint8_t* InGameLogData, uint32_t InStamina, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// S2C: Game match failed
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchFailedS2CEvt( intptr_t InNativeConnectionHandle, Result InFailedReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameMatchFailedS2CEvt::Create(pConnection->GetHeap(), InFailedReason);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchFailedS2CEvt( intptr_t InNativeConnectionHandle, Result InFailedReason )



// S2C: Game matching started
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingStartedS2CEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameMatchingStartedS2CEvt::Create(pConnection->GetHeap());
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingStartedS2CEvt( intptr_t InNativeConnectionHandle )



// Cmd: Cancel Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CancelGameMatchRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: game matching canceled
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingCanceledS2CEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GameMatchingCanceledS2CEvt::Create(pConnection->GetHeap());
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingCanceledS2CEvt( intptr_t InNativeConnectionHandle )



// Cmd: Buy shop item prepare
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InShopItemID, const char* InPurchaseID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::BuyShopItemPrepareRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InShopItemID,InPurchaseID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InShopItemID, const char* InPurchaseID )



// Cmd: Buy shop item
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InShopItemID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::BuyShopItemRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InShopItemID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InShopItemID )



// Cmd: Create or Join Chat channel
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InChatUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateOrJoinChatChannelRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InChatUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InChatUID )



// Cmd: Join
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPartyUID, AccountID InPartyLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinChatChannelRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InPartyUID, AccountID InPartyLeaderID )



// S2C: Player Joined event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, const PlayerInformation& InJoinedPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::Create(pConnection->GetHeap(), InChatUID,InJoinedPlayer);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, const PlayerInformation& InJoinedPlayer )



// S2C: ChatChannel leader changed event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InNewLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::Create(pConnection->GetHeap(), InChatUID, InNewLeaderID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InNewLeaderID )



// Cmd: Leave ChatChannel command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeaveChatChannelRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: ChatChannel Player left event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InLeftPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::Create(pConnection->GetHeap(), InChatUID, InLeftPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InLeftPlayerID )



// Cmd: Kick player from the ChatChannel
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelKickPlayerRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: ChatChannel Player kicked message
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::Create(pConnection->GetHeap(), InChatUID, InKickedPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InKickedPlayerID )



// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelChatMessageRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: ChatChannel Chatting message event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, const char* InSenderName, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(pConnection->GetHeap(), InSenderID,InSenderName,InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, const char* InSenderName, const char* InChatMessage )



// Cmd: Create character
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, int32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateCharacterRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InCharacterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, int32_t InCharacterID )



// Cmd: Remove character
SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::RemoveCharacterRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Get character list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInCharacterIDs,const int32_t* InCharacterIDs )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterListRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<int32_t>(_sizeOfInCharacterIDs, _sizeOfInCharacterIDs, const_cast<int32_t*>(InCharacterIDs)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInCharacterIDs,const int32_t* InCharacterIDs )



// Cmd: 
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterDataRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: Give my stamina to other player
SFDLL_EXPORT int  CSSFNetAdapter_GameGiveStaminaRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, AccountID InTargetPlayer, uint64_t InTimeStamp )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GiveStaminaRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InTargetPlayer, InTimeStamp);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGiveStaminaRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, AccountID InTargetPlayer, uint64_t InTimeStamp )



// Cmd: For debug, Change configue preset
SFDLL_EXPORT int  CSSFNetAdapter_GameSetPresetGameConfigIDRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SetPresetGameConfigIDRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetPresetGameConfigIDRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )









