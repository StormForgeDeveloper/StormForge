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
#include "Protocol/GameMsgClass.h"
#include "SharpCPP/SFCSUtil.h"



using namespace SF;


// C2S: Client heartbeat
SFDLL_EXPORT int  CSSFNetAdapter_GameHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::HeartbeatC2SEvt::Create(pConnection->GetHeap());
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )



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
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InInviterID, const PlayerPlatformID& InInviterPlatformId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::AcceptFriendRequestCmd::Create(pConnection->GetHeap(), InTransactionID, InInviterID,InInviterPlatformId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, AccountID InInviterID, const PlayerPlatformID& InInviterPlatformId )


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


// Cmd: PlayerId Conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInPlatformPlayerId,const PlayerPlatformID* InPlatformPlayerId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByPlatformIdCmd::Create(pConnection->GetHeap(), InTransactionID,SF::ArrayView<PlayerPlatformID>(_sizeOfInPlatformPlayerId, _sizeOfInPlatformPlayerId, const_cast<PlayerPlatformID*>(InPlatformPlayerId)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint16_t _sizeOfInPlatformPlayerId,const PlayerPlatformID* InPlatformPlayerId )


// Cmd: PlayerId conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InCharacterName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByCharacterNameCmd::Create(pConnection->GetHeap(), InTransactionID,InCharacterName);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InCharacterName )


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


// Cmd: Get Ranking list
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


// Cmd: Join to a game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InInsUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinGameInstanceCmd::Create(pConnection->GetHeap(), InTransactionID, InInsUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InInsUID )


// Cmd: Leave game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InInsUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeaveGameInstanceCmd::Create(pConnection->GetHeap(), InTransactionID, InInsUID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InInsUID )


// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InSearchKeyword, uint32_t InZoneTableID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SearchGameInstanceCmd::Create(pConnection->GetHeap(), InTransactionID,InSearchKeyword, InZoneTableID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InSearchKeyword, uint32_t InZoneTableID )


// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, PlayerID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterDataInGameInstanceCmd::Create(pConnection->GetHeap(), InTransactionID, InGameInsUID, InPlayerID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InGameInsUID, PlayerID InPlayerID )


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
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InInviterID, const char* InPasscode )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinChatChannelCmd::Create(pConnection->GetHeap(), InTransactionID, InChatUID, InInviterID,InPasscode);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, AccountID InInviterID, const char* InPasscode )


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


// Cmd: Chat channel sending chatting message
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelChatMessageCmd::Create(pConnection->GetHeap(), InTransactionID, InChatUID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint64_t InChatUID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )


// Cmd: Whisper(tell) other player chatting
SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, PlayerID InReceiverID, const char* InReceiverName, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::WhisperMessageCmd::Create(pConnection->GetHeap(), InTransactionID, InReceiverID,InReceiverName,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, PlayerID InReceiverID, const char* InReceiverName, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )


// Cmd: Create character
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InCharacterName, uint16_t _sizeOfInVisualData,uint8_t* InVisualData, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateCharacterCmd::Create(pConnection->GetHeap(), InTransactionID,InCharacterName,SF::ArrayView<uint8_t>(_sizeOfInVisualData, _sizeOfInVisualData, InVisualData),SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, const char* InCharacterName, uint16_t _sizeOfInVisualData,uint8_t* InVisualData, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )


// Cmd: Delete character
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::DeleteCharacterCmd::Create(pConnection->GetHeap(), InTransactionID, InCharacterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InCharacterID )


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
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterDataCmd::Create(pConnection->GetHeap(), InTransactionID, InCharacterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InCharacterID )


// Cmd: Select character
SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SelectCharacterCmd::Create(pConnection->GetHeap(), InTransactionID, InCharacterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, uint32_t InCharacterID )


// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, StringCrc32 InFunctionName, uint16_t _sizeOfInParameters,uint8_t* InParameters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CallFunctionCmd::Create(pConnection->GetHeap(), InTransactionID, InFunctionName,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionCmd( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, StringCrc32 InFunctionName, uint16_t _sizeOfInParameters,uint8_t* InParameters )




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



// Cmd: PlayerId Conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByPlatformIdRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayerId,InPlayerPlatformId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId )



// Cmd: PlayerId conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId, CharacterID InCharacterId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::FindPlayerByCharacterNameRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayerId,InPlayerPlatformId, InCharacterId);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId, CharacterID InCharacterId )



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



// Cmd: Get Ranking list
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



// Cmd: Join to a game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InInsUID, const NetAddress& InServerAddress4, const NetAddress& InServerAddress6 )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinGameInstanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InInsUID,InServerAddress4,InServerAddress6);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InInsUID, const NetAddress& InServerAddress4, const NetAddress& InServerAddress6 )



// Cmd: Leave game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::LeaveGameInstanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInGameInstances,const VariableTable* InGameInstances )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SearchGameInstanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<VariableTable>(_sizeOfInGameInstances, _sizeOfInGameInstances, const_cast<VariableTable*>(InGameInstances)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInGameInstances,const VariableTable* InGameInstances )



// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, PlayerID InPlayerID, uint16_t _sizeOfInGameInstances,uint8_t* InGameInstances )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterDataInGameInstanceRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInGameInstances, _sizeOfInGameInstances, InGameInstances));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, PlayerID InPlayerID, uint16_t _sizeOfInGameInstances,uint8_t* InGameInstances )



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
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateOrJoinChatChannelRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InChatUID, InChannelLeaderID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )



// Cmd: Join
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::JoinChatChannelRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InChatUID, InChannelLeaderID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )



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



// Cmd: Chat channel sending chatting message
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
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(pConnection->GetHeap(), InSenderID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )



// Cmd: Whisper(tell) other player chatting
SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::WhisperMessageRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// S2C: Other player whispered(tell) to me message event
SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::WhisperMessageS2CEvt::Create(pConnection->GetHeap(), InSenderID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )



// Cmd: Create character
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CreateCharacterRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InCharacterID);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InCharacterID )



// Cmd: Delete character
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::DeleteCharacterRes::Create(pConnection->GetHeap(), InTransactionID, InResult);
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult )



// Cmd: Get character list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInCharacters,const VariableTable* InCharacters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::GetCharacterListRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<VariableTable>(_sizeOfInCharacters, _sizeOfInCharacters, const_cast<VariableTable*>(InCharacters)));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInCharacters,const VariableTable* InCharacters )



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



// Cmd: Select character
SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InCharacterID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::SelectCharacterRes::Create(pConnection->GetHeap(), InTransactionID, InResult, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint32_t InCharacterID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return ResultCode::INVALID_POINTER;
	MessageDataPtr pMessage = SF::Message::Game::CallFunctionRes::Create(pConnection->GetHeap(), InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInResults, _sizeOfInResults, InResults));
	if(pMessage == nullptr) return ResultCode::OUT_OF_MEMORY;
	auto res = pConnection->Send(pMessage);
	return (uint32_t)res;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionRes( intptr_t InNativeConnectionHandle, uint64_t InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )









