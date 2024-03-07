////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : Game Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "Net/SFConnection.h"
#include "Protocol/GameMsgClass.h"
#include "Interfaces/Sharp/SFCSUtil.h"



using namespace SF;


// C2S: Client heartbeat
SFDLL_EXPORT int  CSSFNetAdapter_GameHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::HeartbeatC2SEvt::CalculateMessageSize();
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::HeartbeatC2SEvt::Create(pMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameHeartbeatC2SEvt( intptr_t InNativeConnectionHandle )



// Cmd: Player connected from a login server and moved to game server
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinGameServerCmd::CalculateMessageSize(InTransactionID, InAccID, InTicket, InLoginEntityUID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinGameServerCmd::Create(pMessage, InTransactionID, InAccID, InTicket, InLoginEntityUID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InAccID, AuthTicket InTicket, uint64_t InLoginEntityUID )


// Cmd: player complition statues
SFDLL_EXPORT int  CSSFNetAdapter_GameGetAchievementStatsCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID, uint32_t InAchievementStatIDFrom, uint32_t InAchievementStatIDTo )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetAchievementStatsCmd::CalculateMessageSize(InTransactionID, InCharacterID, InAchievementStatIDFrom, InAchievementStatIDTo);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetAchievementStatsCmd::Create(pMessage, InTransactionID, InCharacterID, InAchievementStatIDFrom, InAchievementStatIDTo);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetAchievementStatsCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID, uint32_t InAchievementStatIDFrom, uint32_t InAchievementStatIDTo )


// Cmd: Player complition state
SFDLL_EXPORT int  CSSFNetAdapter_GameDummy1Cmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InComplitionState )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::Dummy1Cmd::CalculateMessageSize(InTransactionID,InComplitionState);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::Dummy1Cmd::Create(pMessage, InTransactionID,InComplitionState);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDummy1Cmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InComplitionState )


// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InGCMRegisteredID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RegisterGCMCmd::CalculateMessageSize(InTransactionID,InGCMRegisteredID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RegisterGCMCmd::Create(pMessage, InTransactionID,InGCMRegisteredID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InGCMRegisteredID )


// Cmd: Unregister Google notification service ID
SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InGCMRegisteredID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::UnregisterGCMCmd::CalculateMessageSize(InTransactionID,InGCMRegisteredID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::UnregisterGCMCmd::Create(pMessage, InTransactionID,InGCMRegisteredID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InGCMRegisteredID )


// Cmd: Invite friend
SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::InviteFriendCmd::CalculateMessageSize(InTransactionID, InFriendID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::InviteFriendCmd::Create(pMessage, InTransactionID, InFriendID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InFriendID )


// Cmd: Accept friend request
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InInviterID, const PlayerPlatformID& InInviterPlatformId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::AcceptFriendRequestCmd::CalculateMessageSize(InTransactionID, InInviterID,InInviterPlatformId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::AcceptFriendRequestCmd::Create(pMessage, InTransactionID, InInviterID,InInviterPlatformId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InInviterID, const PlayerPlatformID& InInviterPlatformId )


// Cmd: Remove friden form the friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RemoveFriendCmd::CalculateMessageSize(InTransactionID, InFriendID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RemoveFriendCmd::Create(pMessage, InTransactionID, InFriendID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InFriendID )


// Cmd: Get friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint16_t InStartIndex, uint16_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetFriendListCmd::CalculateMessageSize(InTransactionID, InStartIndex, InCount);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetFriendListCmd::Create(pMessage, InTransactionID, InStartIndex, InCount);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint16_t InStartIndex, uint16_t InCount )


// Cmd: Query notification list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetNotificationListCmd::CalculateMessageSize(InTransactionID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetNotificationListCmd::Create(pMessage, InTransactionID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )


// Cmd: Delete notification
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::DeleteNotificationCmd::CalculateMessageSize(InTransactionID, InNotificationID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::DeleteNotificationCmd::Create(pMessage, InTransactionID, InNotificationID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InNotificationID )


// Cmd: Set notification is read
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SetNotificationReadCmd::CalculateMessageSize(InTransactionID, InNotificationID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SetNotificationReadCmd::Create(pMessage, InTransactionID, InNotificationID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InNotificationID )


// Cmd: Accept notification
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::AcceptNotificationCmd::CalculateMessageSize(InTransactionID, InNotificationID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::AcceptNotificationCmd::Create(pMessage, InTransactionID, InNotificationID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InNotificationID )


// Cmd: PlayerId Conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const PlayerPlatformID& InPlatformPlayerId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByPlatformIdCmd::CalculateMessageSize(InTransactionID,InPlatformPlayerId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByPlatformIdCmd::Create(pMessage, InTransactionID,InPlatformPlayerId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const PlayerPlatformID& InPlatformPlayerId )


// Cmd: PlayerId conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InCharacterName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByCharacterNameCmd::CalculateMessageSize(InTransactionID,InCharacterName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByCharacterNameCmd::Create(pMessage, InTransactionID,InCharacterName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InCharacterName )


// Cmd: PlayerId Conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformUserNameCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint8_t InPlatformType, const char* InPlatformUserName )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByPlatformUserNameCmd::CalculateMessageSize(InTransactionID, InPlatformType,InPlatformUserName);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByPlatformUserNameCmd::Create(pMessage, InTransactionID, InPlatformType,InPlatformUserName);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformUserNameCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint8_t InPlatformType, const char* InPlatformUserName )


// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InPlayerEMail )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByEMailCmd::CalculateMessageSize(InTransactionID,InPlayerEMail);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByEMailCmd::Create(pMessage, InTransactionID,InPlayerEMail);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InPlayerEMail )


// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByPlayerIDCmd::CalculateMessageSize(InTransactionID, InPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByPlayerIDCmd::Create(pMessage, InTransactionID, InPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InPlayerID )


// Cmd: *Request Player Status Update
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint16_t _sizeOfInTargetPlayerID,const AccountID* InTargetPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestPlayerStatusUpdateCmd::CalculateMessageSize(InTransactionID,SF::ArrayView<AccountID>(_sizeOfInTargetPlayerID, _sizeOfInTargetPlayerID, const_cast<AccountID*>(InTargetPlayerID)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestPlayerStatusUpdateCmd::Create(pMessage, InTransactionID,SF::ArrayView<AccountID>(_sizeOfInTargetPlayerID, _sizeOfInTargetPlayerID, const_cast<AccountID*>(InTargetPlayerID)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint16_t _sizeOfInTargetPlayerID,const AccountID* InTargetPlayerID )


// Cmd: Get Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint8_t InRankingType, uint8_t InBaseRanking, uint8_t InCount )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetRankingListCmd::CalculateMessageSize(InTransactionID, InRankingType, InBaseRanking, InCount);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetRankingListCmd::Create(pMessage, InTransactionID, InRankingType, InBaseRanking, InCount);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint8_t InRankingType, uint8_t InBaseRanking, uint8_t InCount )


// Cmd: Game user game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetUserGamePlayerInfoCmd::CalculateMessageSize(InTransactionID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetUserGamePlayerInfoCmd::Create(pMessage, InTransactionID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )


// Cmd: Game game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetGamePlayerInfoCmd::CalculateMessageSize(InTransactionID, InPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetGamePlayerInfoCmd::Create(pMessage, InTransactionID, InPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InPlayerID )


// Cmd: Change NickName
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InNickName, uint8_t InIsCostFree )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SetNickNameCmd::CalculateMessageSize(InTransactionID,InNickName, InIsCostFree);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SetNickNameCmd::Create(pMessage, InTransactionID,InNickName, InIsCostFree);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InNickName, uint8_t InIsCostFree )


// Cmd: Create Party
SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CreatePartyCmd::CalculateMessageSize(InTransactionID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CreatePartyCmd::Create(pMessage, InTransactionID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )


// Cmd: Join party
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPartyUID, AccountID InInviterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinPartyCmd::CalculateMessageSize(InTransactionID, InPartyUID, InInviterID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinPartyCmd::Create(pMessage, InTransactionID, InPartyUID, InInviterID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPartyUID, AccountID InInviterID )


// Cmd: Leave party command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPartyUID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LeavePartyCmd::CalculateMessageSize(InTransactionID, InPartyUID, InPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LeavePartyCmd::Create(pMessage, InTransactionID, InPartyUID, InPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPartyUID, AccountID InPlayerID )


// Cmd: Kick player from the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPartyUID, AccountID InPlayerID, AccountID InPlayerToKick )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyKickPlayerCmd::CalculateMessageSize(InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyKickPlayerCmd::Create(pMessage, InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InPartyUID, AccountID InPlayerID, AccountID InPlayerToKick )


// Cmd: Invite a player to the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InInviteTargetID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyInviteCmd::CalculateMessageSize(InTransactionID, InInviteTargetID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyInviteCmd::Create(pMessage, InTransactionID, InInviteTargetID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, AccountID InInviteTargetID )


// Cmd: Send Party quick chat message
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InQuickChatID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyQuickChatMessageCmd::CalculateMessageSize(InTransactionID, InQuickChatID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyQuickChatMessageCmd::Create(pMessage, InTransactionID, InQuickChatID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InQuickChatID )


// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyChatMessageCmd::CalculateMessageSize(InTransactionID,InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyChatMessageCmd::Create(pMessage, InTransactionID,InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InChatMessage )


// Cmd: Join to a game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InInsUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinGameInstanceCmd::CalculateMessageSize(InTransactionID, InInsUID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinGameInstanceCmd::Create(pMessage, InTransactionID, InInsUID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InInsUID )


// Cmd: Leave game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InInsUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LeaveGameInstanceCmd::CalculateMessageSize(InTransactionID, InInsUID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LeaveGameInstanceCmd::Create(pMessage, InTransactionID, InInsUID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InInsUID )


// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InSearchKeyword, uint32_t InZoneTableID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SearchGameInstanceCmd::CalculateMessageSize(InTransactionID,InSearchKeyword, InZoneTableID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SearchGameInstanceCmd::Create(pMessage, InTransactionID,InSearchKeyword, InZoneTableID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InSearchKeyword, uint32_t InZoneTableID )


// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InGameInsUID, PlayerID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetCharacterDataInGameInstanceCmd::CalculateMessageSize(InTransactionID, InGameInsUID, InPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetCharacterDataInGameInstanceCmd::Create(pMessage, InTransactionID, InGameInsUID, InPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InGameInsUID, PlayerID InPlayerID )


// Cmd: Request Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint8_t InNumPlayer, uint8_t InRequestRole )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestGameMatchCmd::CalculateMessageSize(InTransactionID, InNumPlayer, InRequestRole);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestGameMatchCmd::Create(pMessage, InTransactionID, InNumPlayer, InRequestRole);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint8_t InNumPlayer, uint8_t InRequestRole )


// Cmd: Cancel Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CancelGameMatchCmd::CalculateMessageSize(InTransactionID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CancelGameMatchCmd::Create(pMessage, InTransactionID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )


// Cmd: Request UGC template list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCTemplatesCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, intptr_t InTags )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	auto& InTagsArray_ = *NativeToObject<SF::ArrayObject<const char*>>(InTags);
	size_t messageSize = SF::Message::Game::GetUGCTemplatesCmd::CalculateMessageSize(InTransactionID,InTagsArray_);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetUGCTemplatesCmd::Create(pMessage, InTransactionID,InTagsArray_);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCTemplatesCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, intptr_t InTags )


// Cmd: Save UGC content data
SFDLL_EXPORT int  CSSFNetAdapter_GameSaveUGCCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint16_t _sizeOfInUGCMetaData,uint8_t* InUGCMetaData, uint16_t _sizeOfInUGCContents,uint8_t* InUGCContents )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SaveUGCCmd::CalculateMessageSize(InTransactionID,SF::ArrayView<uint8_t>(_sizeOfInUGCMetaData, _sizeOfInUGCMetaData, InUGCMetaData),SF::ArrayView<uint8_t>(_sizeOfInUGCContents, _sizeOfInUGCContents, InUGCContents));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SaveUGCCmd::Create(pMessage, InTransactionID,SF::ArrayView<uint8_t>(_sizeOfInUGCMetaData, _sizeOfInUGCMetaData, InUGCMetaData),SF::ArrayView<uint8_t>(_sizeOfInUGCContents, _sizeOfInUGCContents, InUGCContents));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSaveUGCCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint16_t _sizeOfInUGCMetaData,uint8_t* InUGCMetaData, uint16_t _sizeOfInUGCContents,uint8_t* InUGCContents )


// Cmd: Request WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_GameSearchUGCCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, intptr_t InTags )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	auto& InTagsArray_ = *NativeToObject<SF::ArrayObject<const char*>>(InTags);
	size_t messageSize = SF::Message::Game::SearchUGCCmd::CalculateMessageSize(InTransactionID,InTagsArray_);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SearchUGCCmd::Create(pMessage, InTransactionID,InTagsArray_);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSearchUGCCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, intptr_t InTags )


// Cmd: Get UGC content info, name, thumb image and so on
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCContentInfoCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InUGCID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetUGCContentInfoCmd::CalculateMessageSize(InTransactionID, InUGCID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetUGCContentInfoCmd::Create(pMessage, InTransactionID, InUGCID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCContentInfoCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InUGCID )


// Cmd: Request WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_GameDownloadUGCContentCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InUGCID, uint8_t InIsIncludeMetaData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::DownloadUGCContentCmd::CalculateMessageSize(InTransactionID, InUGCID, InIsIncludeMetaData);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::DownloadUGCContentCmd::Create(pMessage, InTransactionID, InUGCID, InIsIncludeMetaData);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDownloadUGCContentCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InUGCID, uint8_t InIsIncludeMetaData )


// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestUGCZoneInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InUGCID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestUGCZoneInstanceCmd::CalculateMessageSize(InTransactionID, InUGCID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestUGCZoneInstanceCmd::Create(pMessage, InTransactionID, InUGCID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestUGCZoneInstanceCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InUGCID )


// Cmd: Buy shop item prepare
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InShopItemID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::BuyShopItemPrepareCmd::CalculateMessageSize(InTransactionID, InShopItemID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::BuyShopItemPrepareCmd::Create(pMessage, InTransactionID, InShopItemID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InShopItemID )


// Cmd: Buy shop item
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, uint16_t _sizeOfInPurchaseToken,const uint8_t* InPurchaseToken )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::BuyShopItemCmd::CalculateMessageSize(InTransactionID, InShopItemID,InPlatform,InPackageName,InPurchaseTransactionID,SF::ArrayView<uint8_t>(_sizeOfInPurchaseToken, _sizeOfInPurchaseToken, const_cast<uint8_t*>(InPurchaseToken)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::BuyShopItemCmd::Create(pMessage, InTransactionID, InShopItemID,InPlatform,InPackageName,InPurchaseTransactionID,SF::ArrayView<uint8_t>(_sizeOfInPurchaseToken, _sizeOfInPurchaseToken, const_cast<uint8_t*>(InPurchaseToken)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, uint16_t _sizeOfInPurchaseToken,const uint8_t* InPurchaseToken )


// Cmd: Create or Join Chat channel
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InChannelName, const char* InPasscode )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CreateOrJoinChatChannelCmd::CalculateMessageSize(InTransactionID,InChannelName,InPasscode);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CreateOrJoinChatChannelCmd::Create(pMessage, InTransactionID,InChannelName,InPasscode);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InChannelName, const char* InPasscode )


// Cmd: Join
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, AccountID InInviterID, const char* InPasscode )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinChatChannelCmd::CalculateMessageSize(InTransactionID, InChatUID, InInviterID,InPasscode);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinChatChannelCmd::Create(pMessage, InTransactionID, InChatUID, InInviterID,InPasscode);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, AccountID InInviterID, const char* InPasscode )


// Cmd: Leave ChatChannel command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, AccountID InPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LeaveChatChannelCmd::CalculateMessageSize(InTransactionID, InChatUID, InPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LeaveChatChannelCmd::Create(pMessage, InTransactionID, InChatUID, InPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, AccountID InPlayerID )


// Cmd: Kick player from the ChatChannel
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, AccountID InPlayerID, AccountID InPlayerToKick )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelKickPlayerCmd::CalculateMessageSize(InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelKickPlayerCmd::Create(pMessage, InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, AccountID InPlayerID, AccountID InPlayerToKick )


// Cmd: Chat channel sending chatting message
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelChatMessageCmd::CalculateMessageSize(InTransactionID, InChatUID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelChatMessageCmd::Create(pMessage, InTransactionID, InChatUID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint64_t InChatUID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )


// Cmd: Whisper(tell) other player chatting
SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, PlayerID InReceiverID, const char* InReceiverName, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::WhisperMessageCmd::CalculateMessageSize(InTransactionID, InReceiverID,InReceiverName,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::WhisperMessageCmd::Create(pMessage, InTransactionID, InReceiverID,InReceiverName,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, PlayerID InReceiverID, const char* InReceiverName, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )


// Cmd: Create character
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InCharacterName, uint16_t _sizeOfInPublicData,uint8_t* InPublicData, uint16_t _sizeOfInPrivateData,uint8_t* InPrivateData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CreateCharacterCmd::CalculateMessageSize(InTransactionID,InCharacterName,SF::ArrayView<uint8_t>(_sizeOfInPublicData, _sizeOfInPublicData, InPublicData),SF::ArrayView<uint8_t>(_sizeOfInPrivateData, _sizeOfInPrivateData, InPrivateData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CreateCharacterCmd::Create(pMessage, InTransactionID,InCharacterName,SF::ArrayView<uint8_t>(_sizeOfInPublicData, _sizeOfInPublicData, InPublicData),SF::ArrayView<uint8_t>(_sizeOfInPrivateData, _sizeOfInPrivateData, InPrivateData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, const char* InCharacterName, uint16_t _sizeOfInPublicData,uint8_t* InPublicData, uint16_t _sizeOfInPrivateData,uint8_t* InPrivateData )


// Cmd: Delete character
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::DeleteCharacterCmd::CalculateMessageSize(InTransactionID, InCharacterID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::DeleteCharacterCmd::Create(pMessage, InTransactionID, InCharacterID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID )


// Cmd: Get character list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetCharacterListCmd::CalculateMessageSize(InTransactionID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetCharacterListCmd::Create(pMessage, InTransactionID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )


// Cmd: 
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetCharacterDataCmd::CalculateMessageSize(InTransactionID, InCharacterID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetCharacterDataCmd::Create(pMessage, InTransactionID, InCharacterID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID )


// Cmd: Select character
SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SelectCharacterCmd::CalculateMessageSize(InTransactionID, InCharacterID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SelectCharacterCmd::Create(pMessage, InTransactionID, InCharacterID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, uint32_t InCharacterID )


// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestServerNoticeUpdateCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestServerNoticeUpdateCmd::CalculateMessageSize(InTransactionID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestServerNoticeUpdateCmd::Create(pMessage, InTransactionID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestServerNoticeUpdateCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID )


// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, StringCrc32 InFunctionName, uint16_t _sizeOfInParameters,uint8_t* InParameters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CallFunctionCmd::CalculateMessageSize(InTransactionID, InFunctionName,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CallFunctionCmd::Create(pMessage, InTransactionID, InFunctionName,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionCmd( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, StringCrc32 InFunctionName, uint16_t _sizeOfInParameters,uint8_t* InParameters )




// Cmd: Player connected from a login server and moved to game server
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InNickName, uint64_t InGameUID, uint64_t InPartyUID, AccountID InPartyLeaderID, const MatchingQueueTicket& InMatchingTicket )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinGameServerRes::CalculateMessageSize(InTransactionID, InResult,InNickName, InGameUID, InPartyUID, InPartyLeaderID,InMatchingTicket);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinGameServerRes::Create(pMessage, InTransactionID, InResult,InNickName, InGameUID, InPartyUID, InPartyLeaderID,InMatchingTicket);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameServerRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const char* InNickName, uint64_t InGameUID, uint64_t InPartyUID, AccountID InPartyLeaderID, const MatchingQueueTicket& InMatchingTicket )



// Cmd: player complition statues
SFDLL_EXPORT int  CSSFNetAdapter_GameGetAchievementStatsRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInAchievementStats,const AchievementStat* InAchievementStats )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetAchievementStatsRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<AchievementStat>(_sizeOfInAchievementStats, _sizeOfInAchievementStats, const_cast<AchievementStat*>(InAchievementStats)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetAchievementStatsRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<AchievementStat>(_sizeOfInAchievementStats, _sizeOfInAchievementStats, const_cast<AchievementStat*>(InAchievementStats)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetAchievementStatsRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInAchievementStats,const AchievementStat* InAchievementStats )



// Cmd: Player complition state
SFDLL_EXPORT int  CSSFNetAdapter_GameDummy1Res( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::Dummy1Res::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::Dummy1Res::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDummy1Res( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RegisterGCMRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RegisterGCMRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRegisterGCMRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Unregister Google notification service ID
SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::UnregisterGCMRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::UnregisterGCMRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameUnregisterGCMRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Invite friend
SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::InviteFriendRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::InviteFriendRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameInviteFriendRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Accept friend request
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const PlayerInformation& InNewFriend )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::AcceptFriendRequestRes::CalculateMessageSize(InTransactionID, InResult,InNewFriend);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::AcceptFriendRequestRes::Create(pMessage, InTransactionID, InResult,InNewFriend);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptFriendRequestRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const PlayerInformation& InNewFriend )



// S2C: Notification for friend request is accepted
SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt( intptr_t InNativeConnectionHandle, const PlayerInformation& InAccepter )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FriendRequestAcceptedS2CEvt::CalculateMessageSize(InAccepter);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FriendRequestAcceptedS2CEvt::Create(pMessage, InAccepter);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRequestAcceptedS2CEvt( intptr_t InNativeConnectionHandle, const PlayerInformation& InAccepter )



// Cmd: Remove friden form the friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RemoveFriendRes::CalculateMessageSize(InTransactionID, InResult, InFriendID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RemoveFriendRes::Create(pMessage, InTransactionID, InResult, InFriendID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRemoveFriendRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, AccountID InFriendID )



// S2C: Friend removed
SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRemovedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InFriendID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FriendRemovedS2CEvt::CalculateMessageSize( InFriendID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FriendRemovedS2CEvt::Create(pMessage,  InFriendID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFriendRemovedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InFriendID )



// Cmd: Get friend list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t InMaxFriendSlot, uint16_t InTotalNumberOfFriends, uint16_t InStartIndex, uint16_t _sizeOfInFriendList,const PlayerInformation* InFriendList )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetFriendListRes::CalculateMessageSize(InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,SF::ArrayView<PlayerInformation>(_sizeOfInFriendList, _sizeOfInFriendList, const_cast<PlayerInformation*>(InFriendList)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetFriendListRes::Create(pMessage, InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex,SF::ArrayView<PlayerInformation>(_sizeOfInFriendList, _sizeOfInFriendList, const_cast<PlayerInformation*>(InFriendList)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetFriendListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t InMaxFriendSlot, uint16_t InTotalNumberOfFriends, uint16_t InStartIndex, uint16_t _sizeOfInFriendList,const PlayerInformation* InFriendList )



// Cmd: Query notification list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetNotificationListRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetNotificationListRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetNotificationListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Delete notification
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::DeleteNotificationRes::CalculateMessageSize(InTransactionID, InResult, InNotificationID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::DeleteNotificationRes::Create(pMessage, InTransactionID, InResult, InNotificationID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteNotificationRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InNotificationID )



// Cmd: Set notification is read
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SetNotificationReadRes::CalculateMessageSize(InTransactionID, InResult, InNotificationID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SetNotificationReadRes::Create(pMessage, InTransactionID, InResult, InNotificationID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNotificationReadRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InNotificationID )



// Cmd: Accept notification
SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InNotificationID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::AcceptNotificationRes::CalculateMessageSize(InTransactionID, InResult, InNotificationID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::AcceptNotificationRes::Create(pMessage, InTransactionID, InResult, InNotificationID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameAcceptNotificationRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InNotificationID )



// S2C: Notify new notification
SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InNotificationID, StringCrc32 InNotificationType, uint16_t _sizeOfInParameters,uint8_t* InParameters, uint8_t InIsRead, uint64_t InTimeStamp )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::NotifyS2CEvt::CalculateMessageSize( InNotificationID, InNotificationType,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters), InIsRead, InTimeStamp);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::NotifyS2CEvt::Create(pMessage,  InNotificationID, InNotificationType,SF::ArrayView<uint8_t>(_sizeOfInParameters, _sizeOfInParameters, InParameters), InIsRead, InTimeStamp);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyS2CEvt( intptr_t InNativeConnectionHandle, uint32_t InNotificationID, StringCrc32 InNotificationType, uint16_t _sizeOfInParameters,uint8_t* InParameters, uint8_t InIsRead, uint64_t InTimeStamp )



// Cmd: PlayerId Conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByPlatformIdRes::CalculateMessageSize(InTransactionID, InResult, InPlayerId,InPlayerPlatformId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByPlatformIdRes::Create(pMessage, InTransactionID, InResult, InPlayerId,InPlayerPlatformId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformIdRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId )



// Cmd: PlayerId conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByCharacterNameRes::CalculateMessageSize(InTransactionID, InResult, InPlayerId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByCharacterNameRes::Create(pMessage, InTransactionID, InResult, InPlayerId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByCharacterNameRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerId )



// Cmd: PlayerId Conversion
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByPlatformUserNameRes::CalculateMessageSize(InTransactionID, InResult, InPlayerId,InPlayerPlatformId);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByPlatformUserNameRes::Create(pMessage, InTransactionID, InResult, InPlayerId,InPlayerPlatformId);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlatformUserNameRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerId, const PlayerPlatformID& InPlayerPlatformId )



// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const PlayerInformation& InPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByEMailRes::CalculateMessageSize(InTransactionID, InResult,InPlayer);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByEMailRes::Create(pMessage, InTransactionID, InResult,InPlayer);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByEMailRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const PlayerInformation& InPlayer )



// Cmd: Query playerID list
SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const PlayerInformation& InPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::FindPlayerByPlayerIDRes::CalculateMessageSize(InTransactionID, InResult,InPlayer);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::FindPlayerByPlayerIDRes::Create(pMessage, InTransactionID, InResult,InPlayer);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameFindPlayerByPlayerIDRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, const PlayerInformation& InPlayer )



// Cmd: *Request Player Status Update
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestPlayerStatusUpdateRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestPlayerStatusUpdateRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestPlayerStatusUpdateRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: *Notify Player Status Updated
SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InPlayerID, uint32_t InLatestActiveTime, uint8_t InIsInGame )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::CalculateMessageSize( InPlayerID, InLatestActiveTime, InIsInGame);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::Create(pMessage,  InPlayerID, InLatestActiveTime, InIsInGame);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameNotifyPlayerStatusUpdatedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InPlayerID, uint32_t InLatestActiveTime, uint8_t InIsInGame )



// Cmd: Get Ranking list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetRankingListRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetRankingListRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<TotalRankingPlayerInformation>(_sizeOfInRanking, _sizeOfInRanking, const_cast<TotalRankingPlayerInformation*>(InRanking)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetRankingListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInRanking,const TotalRankingPlayerInformation* InRanking )



// Cmd: Game user game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetUserGamePlayerInfoRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetUserGamePlayerInfoRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUserGamePlayerInfoRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: Game game play information
SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, AccountID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetGamePlayerInfoRes::CalculateMessageSize(InTransactionID, InResult, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetGamePlayerInfoRes::Create(pMessage, InTransactionID, InResult, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetGamePlayerInfoRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, AccountID InPlayerID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// S2C: Player level up event
SFDLL_EXPORT int  CSSFNetAdapter_GameLevelUpS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InCurrentTotalExp, uint32_t InCurrentLevel )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LevelUpS2CEvt::CalculateMessageSize( InCurrentTotalExp, InCurrentLevel);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LevelUpS2CEvt::Create(pMessage,  InCurrentTotalExp, InCurrentLevel);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLevelUpS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InCurrentTotalExp, uint32_t InCurrentLevel )



// Cmd: Change NickName
SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SetNickNameRes::CalculateMessageSize(InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SetNickNameRes::Create(pMessage, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSetNickNameRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// Cmd: Create Party
SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPartyUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CreatePartyRes::CalculateMessageSize(InTransactionID, InResult, InPartyUID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CreatePartyRes::Create(pMessage, InTransactionID, InResult, InPartyUID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreatePartyRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPartyUID )



// Cmd: Join party
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPartyUID, AccountID InPartyLeaderID, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinPartyRes::CalculateMessageSize(InTransactionID, InResult, InPartyUID, InPartyLeaderID,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinPartyRes::Create(pMessage, InTransactionID, InResult, InPartyUID, InPartyLeaderID,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinPartyRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InPartyUID, AccountID InPartyLeaderID, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData )



// S2C: Player Joined event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, const PlayerInformation& InJoinedPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyPlayerJoinedS2CEvt::CalculateMessageSize( InPartyUID,InJoinedPlayer);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyPlayerJoinedS2CEvt::Create(pMessage,  InPartyUID,InJoinedPlayer);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, const PlayerInformation& InJoinedPlayer )



// S2C: Party leader changed event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InNewLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyLeaderChangedS2CEvt::CalculateMessageSize( InPartyUID, InNewLeaderID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyLeaderChangedS2CEvt::Create(pMessage,  InPartyUID, InNewLeaderID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InNewLeaderID )



// Cmd: Leave party command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LeavePartyRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LeavePartyRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeavePartyRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Party Player left event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InLeftPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyPlayerLeftS2CEvt::CalculateMessageSize( InPartyUID, InLeftPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyPlayerLeftS2CEvt::Create(pMessage,  InPartyUID, InLeftPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InLeftPlayerID )



// Cmd: Kick player from the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyKickPlayerRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyKickPlayerRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyKickPlayerRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Party Player kicked message
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyPlayerKickedS2CEvt::CalculateMessageSize( InPartyUID, InKickedPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyPlayerKickedS2CEvt::Create(pMessage,  InPartyUID, InKickedPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InPartyUID, AccountID InKickedPlayerID )



// Cmd: Invite a player to the party
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyInviteRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyInviteRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Party invite requested
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRequestedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InInviterID, const char* InInviterName, uint64_t InPartyToJoinUID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyInviteRequestedS2CEvt::CalculateMessageSize( InInviterID,InInviterName, InPartyToJoinUID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyInviteRequestedS2CEvt::Create(pMessage,  InInviterID,InInviterName, InPartyToJoinUID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyInviteRequestedS2CEvt( intptr_t InNativeConnectionHandle, AccountID InInviterID, const char* InInviterName, uint64_t InPartyToJoinUID )



// Cmd: Send Party quick chat message
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyQuickChatMessageRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyQuickChatMessageRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Party Chatting message event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, uint32_t InQuickChatID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyQuickChatMessageS2CEvt::CalculateMessageSize( InSenderID, InQuickChatID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyQuickChatMessageS2CEvt::Create(pMessage,  InSenderID, InQuickChatID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyQuickChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, uint32_t InQuickChatID )



// Cmd: Party chatting
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyChatMessageRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyChatMessageRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Party Chatting message event
SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, const char* InSenderName, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::PartyChatMessageS2CEvt::CalculateMessageSize( InSenderID,InSenderName,InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::PartyChatMessageS2CEvt::Create(pMessage,  InSenderID,InSenderName,InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GamePartyChatMessageS2CEvt( intptr_t InNativeConnectionHandle, AccountID InSenderID, const char* InSenderName, const char* InChatMessage )



// Cmd: Join to a game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InInsUID, const char* InServerPublicAddress )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinGameInstanceRes::CalculateMessageSize(InTransactionID, InResult, InInsUID,InServerPublicAddress);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinGameInstanceRes::Create(pMessage, InTransactionID, InResult, InInsUID,InServerPublicAddress);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InInsUID, const char* InServerPublicAddress )



// Cmd: Leave game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LeaveGameInstanceRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LeaveGameInstanceRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInGameInstances,uint8_t* InGameInstances )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	SF::DynamicArray<VariableTable> InGameInstancesArray_;
	SF::InputMemoryStream InGameInstancesStream_(SF::ArrayView<uint8_t>(_sizeOfInGameInstances, InGameInstances));
	InGameInstancesStream_ >> InGameInstancesArray_;
	size_t messageSize = SF::Message::Game::SearchGameInstanceRes::CalculateMessageSize(InTransactionID, InResult,InGameInstancesArray_);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SearchGameInstanceRes::Create(pMessage, InTransactionID, InResult,InGameInstancesArray_);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSearchGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInGameInstances,uint8_t* InGameInstances )



// Cmd: Search game instance
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerID, uint16_t _sizeOfInGameInstances,uint8_t* InGameInstances )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetCharacterDataInGameInstanceRes::CalculateMessageSize(InTransactionID, InResult, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInGameInstances, _sizeOfInGameInstances, InGameInstances));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetCharacterDataInGameInstanceRes::Create(pMessage, InTransactionID, InResult, InPlayerID,SF::ArrayView<uint8_t>(_sizeOfInGameInstances, _sizeOfInGameInstances, InGameInstances));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataInGameInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, PlayerID InPlayerID, uint16_t _sizeOfInGameInstances,uint8_t* InGameInstances )



// Cmd: Request Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestGameMatchRes::CalculateMessageSize(InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestGameMatchRes::Create(pMessage, InTransactionID, InResult, InTotalGem, InTotalGameMoney);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestGameMatchRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// S2C: Game matched
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay, uint8_t InMaxPlayer, uint8_t InPlayerIndex, uint8_t InPlayerCharacter, uint8_t InRole, uint8_t InDead, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData, uint16_t _sizeOfInGameLogData,const uint8_t* InGameLogData, uint32_t InStamina, uint64_t InTotalGem, uint64_t InTotalGameMoney )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GameMatchedS2CEvt::CalculateMessageSize( InInsUID, InTimeStamp,(uint8_t) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)),SF::ArrayView<uint8_t>(_sizeOfInGameLogData, _sizeOfInGameLogData, const_cast<uint8_t*>(InGameLogData)), InStamina, InTotalGem, InTotalGameMoney);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GameMatchedS2CEvt::Create(pMessage,  InInsUID, InTimeStamp,(uint8_t) InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead,SF::ArrayView<uint8_t>(_sizeOfInChatHistoryData, _sizeOfInChatHistoryData, const_cast<uint8_t*>(InChatHistoryData)),SF::ArrayView<uint8_t>(_sizeOfInGameLogData, _sizeOfInGameLogData, const_cast<uint8_t*>(InGameLogData)), InStamina, InTotalGem, InTotalGameMoney);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InInsUID, uint32_t InTimeStamp, int InGameState, uint8_t InDay, uint8_t InMaxPlayer, uint8_t InPlayerIndex, uint8_t InPlayerCharacter, uint8_t InRole, uint8_t InDead, uint16_t _sizeOfInChatHistoryData,const uint8_t* InChatHistoryData, uint16_t _sizeOfInGameLogData,const uint8_t* InGameLogData, uint32_t InStamina, uint64_t InTotalGem, uint64_t InTotalGameMoney )



// S2C: Game match failed
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchFailedS2CEvt( intptr_t InNativeConnectionHandle, Result InFailedReason )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GameMatchFailedS2CEvt::CalculateMessageSize( InFailedReason);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GameMatchFailedS2CEvt::Create(pMessage,  InFailedReason);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchFailedS2CEvt( intptr_t InNativeConnectionHandle, Result InFailedReason )



// S2C: Game matching started
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingStartedS2CEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GameMatchingStartedS2CEvt::CalculateMessageSize();
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GameMatchingStartedS2CEvt::Create(pMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingStartedS2CEvt( intptr_t InNativeConnectionHandle )



// Cmd: Cancel Game match
SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CancelGameMatchRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CancelGameMatchRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCancelGameMatchRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: game matching canceled
SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingCanceledS2CEvt( intptr_t InNativeConnectionHandle )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GameMatchingCanceledS2CEvt::CalculateMessageSize();
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GameMatchingCanceledS2CEvt::Create(pMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGameMatchingCanceledS2CEvt( intptr_t InNativeConnectionHandle )



// Cmd: Request UGC template list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCTemplatesRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InUGCIDs )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetUGCTemplatesRes::CalculateMessageSize(InTransactionID, InResult, InUGCIDs);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetUGCTemplatesRes::Create(pMessage, InTransactionID, InResult, InUGCIDs);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCTemplatesRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InUGCIDs )



// Cmd: Save UGC content data
SFDLL_EXPORT int  CSSFNetAdapter_GameSaveUGCRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InUGCID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SaveUGCRes::CalculateMessageSize(InTransactionID, InResult, InUGCID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SaveUGCRes::Create(pMessage, InTransactionID, InResult, InUGCID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSaveUGCRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InUGCID )



// Cmd: Request WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_GameSearchUGCRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SearchUGCRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SearchUGCRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSearchUGCRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Get UGC content info, name, thumb image and so on
SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCContentInfoRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInUGCMetaData,uint8_t* InUGCMetaData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetUGCContentInfoRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInUGCMetaData, _sizeOfInUGCMetaData, InUGCMetaData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetUGCContentInfoRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInUGCMetaData, _sizeOfInUGCMetaData, InUGCMetaData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetUGCContentInfoRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInUGCMetaData,uint8_t* InUGCMetaData )



// Cmd: Request WhiteboardSharing
SFDLL_EXPORT int  CSSFNetAdapter_GameDownloadUGCContentRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInUGCMetaData,uint8_t* InUGCMetaData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::DownloadUGCContentRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInUGCMetaData, _sizeOfInUGCMetaData, InUGCMetaData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::DownloadUGCContentRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInUGCMetaData, _sizeOfInUGCMetaData, InUGCMetaData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDownloadUGCContentRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInUGCMetaData,uint8_t* InUGCMetaData )



// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestUGCZoneInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInGameInstance,uint8_t* InGameInstance )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestUGCZoneInstanceRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInGameInstance, _sizeOfInGameInstance, InGameInstance));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestUGCZoneInstanceRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInGameInstance, _sizeOfInGameInstance, InGameInstance));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestUGCZoneInstanceRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInGameInstance,uint8_t* InGameInstance )



// Cmd: Buy shop item prepare
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InShopItemID, const char* InPurchaseID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::BuyShopItemPrepareRes::CalculateMessageSize(InTransactionID, InResult, InShopItemID,InPurchaseID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::BuyShopItemPrepareRes::Create(pMessage, InTransactionID, InResult, InShopItemID,InPurchaseID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemPrepareRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InShopItemID, const char* InPurchaseID )



// Cmd: Buy shop item
SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InShopItemID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::BuyShopItemRes::CalculateMessageSize(InTransactionID, InResult, InShopItemID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::BuyShopItemRes::Create(pMessage, InTransactionID, InResult, InShopItemID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameBuyShopItemRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InShopItemID )



// Cmd: Create or Join Chat channel
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CreateOrJoinChatChannelRes::CalculateMessageSize(InTransactionID, InResult, InChatUID, InChannelLeaderID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CreateOrJoinChatChannelRes::Create(pMessage, InTransactionID, InResult, InChatUID, InChannelLeaderID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateOrJoinChatChannelRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )



// Cmd: Join
SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::JoinChatChannelRes::CalculateMessageSize(InTransactionID, InResult, InChatUID, InChannelLeaderID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::JoinChatChannelRes::Create(pMessage, InTransactionID, InResult, InChatUID, InChannelLeaderID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameJoinChatChannelRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint64_t InChatUID, PlayerID InChannelLeaderID )



// S2C: Player Joined event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, const PlayerInformation& InJoinedPlayer )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::CalculateMessageSize( InChatUID,InJoinedPlayer);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::Create(pMessage,  InChatUID,InJoinedPlayer);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerJoinedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, const PlayerInformation& InJoinedPlayer )



// S2C: ChatChannel leader changed event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InNewLeaderID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::CalculateMessageSize( InChatUID, InNewLeaderID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::Create(pMessage,  InChatUID, InNewLeaderID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelLeaderChangedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InNewLeaderID )



// Cmd: Leave ChatChannel command
SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::LeaveChatChannelRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::LeaveChatChannelRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameLeaveChatChannelRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: ChatChannel Player left event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InLeftPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::CalculateMessageSize( InChatUID, InLeftPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::Create(pMessage,  InChatUID, InLeftPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerLeftS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InLeftPlayerID )



// Cmd: Kick player from the ChatChannel
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelKickPlayerRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelKickPlayerRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelKickPlayerRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: ChatChannel Player kicked message
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InKickedPlayerID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::CalculateMessageSize( InChatUID, InKickedPlayerID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::Create(pMessage,  InChatUID, InKickedPlayerID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelPlayerKickedS2CEvt( intptr_t InNativeConnectionHandle, uint64_t InChatUID, AccountID InKickedPlayerID )



// Cmd: Chat channel sending chatting message
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelChatMessageRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelChatMessageRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: ChatChannel Chatting message event
SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ChatChannelChatMessageS2CEvt::CalculateMessageSize( InSenderID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(pMessage,  InSenderID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameChatChannelChatMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )



// Cmd: Whisper(tell) other player chatting
SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::WhisperMessageRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::WhisperMessageRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Other player whispered(tell) to me message event
SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::WhisperMessageS2CEvt::CalculateMessageSize( InSenderID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::WhisperMessageS2CEvt::Create(pMessage,  InSenderID,SF::ArrayView<uint8_t>(_sizeOfInChatMetaData, _sizeOfInChatMetaData, InChatMetaData),InChatMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameWhisperMessageS2CEvt( intptr_t InNativeConnectionHandle, PlayerID InSenderID, uint16_t _sizeOfInChatMetaData,uint8_t* InChatMetaData, const char* InChatMessage )



// Cmd: Create character
SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InCharacterID )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CreateCharacterRes::CalculateMessageSize(InTransactionID, InResult, InCharacterID);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CreateCharacterRes::Create(pMessage, InTransactionID, InResult, InCharacterID);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCreateCharacterRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InCharacterID )



// Cmd: Delete character
SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::DeleteCharacterRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::DeleteCharacterRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameDeleteCharacterRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// Cmd: Get character list
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInCharacters,uint8_t* InCharacters )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	SF::DynamicArray<VariableTable> InCharactersArray_;
	SF::InputMemoryStream InCharactersStream_(SF::ArrayView<uint8_t>(_sizeOfInCharacters, InCharacters));
	InCharactersStream_ >> InCharactersArray_;
	size_t messageSize = SF::Message::Game::GetCharacterListRes::CalculateMessageSize(InTransactionID, InResult,InCharactersArray_);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetCharacterListRes::Create(pMessage, InTransactionID, InResult,InCharactersArray_);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterListRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInCharacters,uint8_t* InCharacters )



// Cmd: 
SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInPrivateData,uint8_t* InPrivateData, uint16_t _sizeOfInEquipData,uint8_t* InEquipData )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::GetCharacterDataRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInPrivateData, _sizeOfInPrivateData, InPrivateData),SF::ArrayView<uint8_t>(_sizeOfInEquipData, _sizeOfInEquipData, InEquipData));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::GetCharacterDataRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInPrivateData, _sizeOfInPrivateData, InPrivateData),SF::ArrayView<uint8_t>(_sizeOfInEquipData, _sizeOfInEquipData, InEquipData));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameGetCharacterDataRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInPrivateData,uint8_t* InPrivateData, uint16_t _sizeOfInEquipData,uint8_t* InEquipData )



// Cmd: Select character
SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InCharacterID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::SelectCharacterRes::CalculateMessageSize(InTransactionID, InResult, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::SelectCharacterRes::Create(pMessage, InTransactionID, InResult, InCharacterID,SF::ArrayView<uint8_t>(_sizeOfInAttributes, _sizeOfInAttributes, InAttributes));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameSelectCharacterRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint32_t InCharacterID, uint16_t _sizeOfInAttributes,uint8_t* InAttributes )



// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
SFDLL_EXPORT int  CSSFNetAdapter_GameRequestServerNoticeUpdateRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::RequestServerNoticeUpdateRes::CalculateMessageSize(InTransactionID, InResult);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::RequestServerNoticeUpdateRes::Create(pMessage, InTransactionID, InResult);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameRequestServerNoticeUpdateRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult )



// S2C: Server Notice updated event
SFDLL_EXPORT int  CSSFNetAdapter_GameServerNoticeS2CEvt( intptr_t InNativeConnectionHandle, int8_t InNoticeCategory, const char* InServerNoticeMessage )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::ServerNoticeS2CEvt::CalculateMessageSize( InNoticeCategory,InServerNoticeMessage);
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::ServerNoticeS2CEvt::Create(pMessage,  InNoticeCategory,InServerNoticeMessage);
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameServerNoticeS2CEvt( intptr_t InNativeConnectionHandle, int8_t InNoticeCategory, const char* InServerNoticeMessage )



// Cmd: To call general functionality
SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )
{
 	auto pConnection = NativeToObject<Net::Connection>(InNativeConnectionHandle);
	if(pConnection == nullptr) return (int)ResultCode::INVALID_POINTER;
	size_t messageSize = SF::Message::Game::CallFunctionRes::CalculateMessageSize(InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInResults, _sizeOfInResults, InResults));
	SFNET_ALLOC_MESSAGE_FROM_STACK(pMessage,messageSize);
	Result hr = SF::Message::Game::CallFunctionRes::Create(pMessage, InTransactionID, InResult,SF::ArrayView<uint8_t>(_sizeOfInResults, _sizeOfInResults, InResults));
	if (hr) hr = pConnection->SendMsg(pMessage);
	return (int32_t)hr;
} // SFDLL_EXPORT int  CSSFNetAdapter_GameCallFunctionRes( intptr_t InNativeConnectionHandle, const TransactionID& InTransactionID, Result InResult, uint16_t _sizeOfInResults,uint8_t* InResults )









