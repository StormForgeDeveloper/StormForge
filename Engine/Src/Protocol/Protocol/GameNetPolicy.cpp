////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Game Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/GameNetPolicy.h"
#include "Protocol/GameMsgClass.h"



namespace SF
{
 	// C2S: Client heartbeat
	Result NetPolicyGame::HeartbeatC2SEvt(  )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::HeartbeatC2SEvt::CalculateMessageSize();
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::HeartbeatC2SEvt::Create(messageBuffer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::HeartbeatC2SEvt(  )
	// Cmd: Player connected from a login server and moved to game server
	Result NetPolicyGame::JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinGameServerCmd::CalculateMessageSize(InTransactionID, InAccID, InTicket, InLoginEntityUID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinGameServerCmd::Create(messageBuffer, InTransactionID, InAccID, InTicket, InLoginEntityUID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	// Cmd: player complition statues
	Result NetPolicyGame::GetComplitionStateCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetComplitionStateCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetComplitionStateCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetComplitionStateCmd( const uint64_t &InTransactionID )
	// Cmd: Player complition state
	Result NetPolicyGame::SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SetComplitionStateCmd::CalculateMessageSize(InTransactionID, InComplitionState);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SetComplitionStateCmd::Create(messageBuffer, InTransactionID, InComplitionState));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState )
	// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
	Result NetPolicyGame::RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RegisterGCMCmd::CalculateMessageSize(InTransactionID, InGCMRegisteredID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RegisterGCMCmd::Create(messageBuffer, InTransactionID, InGCMRegisteredID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	// Cmd: Unregister Google notification service ID
	Result NetPolicyGame::UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::UnregisterGCMCmd::CalculateMessageSize(InTransactionID, InGCMRegisteredID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::UnregisterGCMCmd::Create(messageBuffer, InTransactionID, InGCMRegisteredID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	// Cmd: Invite friend
	Result NetPolicyGame::InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::InviteFriendCmd::CalculateMessageSize(InTransactionID, InFriendID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::InviteFriendCmd::Create(messageBuffer, InTransactionID, InFriendID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	// Cmd: Accept friend request
	Result NetPolicyGame::AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::AcceptFriendRequestCmd::CalculateMessageSize(InTransactionID, InInviterID, InInviterPlatformId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::AcceptFriendRequestCmd::Create(messageBuffer, InTransactionID, InInviterID, InInviterPlatformId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
	// Cmd: Remove friden form the friend list
	Result NetPolicyGame::RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RemoveFriendCmd::CalculateMessageSize(InTransactionID, InFriendID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RemoveFriendCmd::Create(messageBuffer, InTransactionID, InFriendID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	// Cmd: Get friend list
	Result NetPolicyGame::GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetFriendListCmd::CalculateMessageSize(InTransactionID, InStartIndex, InCount);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetFriendListCmd::Create(messageBuffer, InTransactionID, InStartIndex, InCount));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
	// Cmd: Query notification list
	Result NetPolicyGame::GetNotificationListCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetNotificationListCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetNotificationListCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetNotificationListCmd( const uint64_t &InTransactionID )
	// Cmd: Delete notification
	Result NetPolicyGame::DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::DeleteNotificationCmd::CalculateMessageSize(InTransactionID, InNotificationID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::DeleteNotificationCmd::Create(messageBuffer, InTransactionID, InNotificationID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: Set notification is read
	Result NetPolicyGame::SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SetNotificationReadCmd::CalculateMessageSize(InTransactionID, InNotificationID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SetNotificationReadCmd::Create(messageBuffer, InTransactionID, InNotificationID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: Accept notification
	Result NetPolicyGame::AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::AcceptNotificationCmd::CalculateMessageSize(InTransactionID, InNotificationID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::AcceptNotificationCmd::Create(messageBuffer, InTransactionID, InNotificationID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: PlayerId Conversion
	Result NetPolicyGame::FindPlayerByPlatformIdCmd( const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByPlatformIdCmd::CalculateMessageSize(InTransactionID, InPlatformPlayerId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByPlatformIdCmd::Create(messageBuffer, InTransactionID, InPlatformPlayerId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::FindPlayerByPlatformIdCmd( const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
	// Cmd: PlayerId conversion
	Result NetPolicyGame::FindPlayerByCharacterNameCmd( const uint64_t &InTransactionID, const char* InCharacterName )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByCharacterNameCmd::CalculateMessageSize(InTransactionID, InCharacterName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByCharacterNameCmd::Create(messageBuffer, InTransactionID, InCharacterName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::FindPlayerByCharacterNameCmd( const uint64_t &InTransactionID, const char* InCharacterName )
	// Cmd: PlayerId Conversion
	Result NetPolicyGame::FindPlayerByPlatformUserNameCmd( const uint64_t &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByPlatformUserNameCmd::CalculateMessageSize(InTransactionID, InPlatformType, InPlatformUserName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByPlatformUserNameCmd::Create(messageBuffer, InTransactionID, InPlatformType, InPlatformUserName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::FindPlayerByPlatformUserNameCmd( const uint64_t &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )
	// Cmd: Query playerID list
	Result NetPolicyGame::FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByEMailCmd::CalculateMessageSize(InTransactionID, InPlayerEMail);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByEMailCmd::Create(messageBuffer, InTransactionID, InPlayerEMail));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail )
	// Cmd: Query playerID list
	Result NetPolicyGame::FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByPlayerIDCmd::CalculateMessageSize(InTransactionID, InPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByPlayerIDCmd::Create(messageBuffer, InTransactionID, InPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	// Cmd: *Request Player Status Update
	Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RequestPlayerStatusUpdateCmd::CalculateMessageSize(InTransactionID, InTargetPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RequestPlayerStatusUpdateCmd::Create(messageBuffer, InTransactionID, InTargetPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
	// Cmd: Get Ranking list
	Result NetPolicyGame::GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetRankingListCmd::CalculateMessageSize(InTransactionID, InRankingType, InBaseRanking, InCount);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetRankingListCmd::Create(messageBuffer, InTransactionID, InRankingType, InBaseRanking, InCount));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	// Cmd: Game user game play information
	Result NetPolicyGame::GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetUserGamePlayerInfoCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetUserGamePlayerInfoCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID )
	// Cmd: Game game play information
	Result NetPolicyGame::GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetGamePlayerInfoCmd::CalculateMessageSize(InTransactionID, InPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetGamePlayerInfoCmd::Create(messageBuffer, InTransactionID, InPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	// Cmd: Change NickName
	Result NetPolicyGame::SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SetNickNameCmd::CalculateMessageSize(InTransactionID, InNickName, InIsCostFree);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SetNickNameCmd::Create(messageBuffer, InTransactionID, InNickName, InIsCostFree));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
	// Cmd: Create Party
	Result NetPolicyGame::CreatePartyCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CreatePartyCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CreatePartyCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::CreatePartyCmd( const uint64_t &InTransactionID )
	// Cmd: Join party
	Result NetPolicyGame::JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinPartyCmd::CalculateMessageSize(InTransactionID, InPartyUID, InInviterID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinPartyCmd::Create(messageBuffer, InTransactionID, InPartyUID, InInviterID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
	// Cmd: Leave party command
	Result NetPolicyGame::LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LeavePartyCmd::CalculateMessageSize(InTransactionID, InPartyUID, InPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LeavePartyCmd::Create(messageBuffer, InTransactionID, InPartyUID, InPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
	// Cmd: Kick player from the party
	Result NetPolicyGame::PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyKickPlayerCmd::CalculateMessageSize(InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyKickPlayerCmd::Create(messageBuffer, InTransactionID, InPartyUID, InPlayerID, InPlayerToKick));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	// Cmd: Invite a player to the party
	Result NetPolicyGame::PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyInviteCmd::CalculateMessageSize(InTransactionID, InInviteTargetID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyInviteCmd::Create(messageBuffer, InTransactionID, InInviteTargetID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
	// Cmd: Send Party quick chat message
	Result NetPolicyGame::PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyQuickChatMessageCmd::CalculateMessageSize(InTransactionID, InQuickChatID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyQuickChatMessageCmd::Create(messageBuffer, InTransactionID, InQuickChatID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
	// Cmd: Party chatting
	Result NetPolicyGame::PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyChatMessageCmd::CalculateMessageSize(InTransactionID, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyChatMessageCmd::Create(messageBuffer, InTransactionID, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage )
	// Cmd: Join to a game instance
	Result NetPolicyGame::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinGameInstanceCmd::CalculateMessageSize(InTransactionID, InInsUID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinGameInstanceCmd::Create(messageBuffer, InTransactionID, InInsUID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	// Cmd: Leave game instance
	Result NetPolicyGame::LeaveGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LeaveGameInstanceCmd::CalculateMessageSize(InTransactionID, InInsUID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LeaveGameInstanceCmd::Create(messageBuffer, InTransactionID, InInsUID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::LeaveGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	// Cmd: Search game instance
	Result NetPolicyGame::SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SearchGameInstanceCmd::CalculateMessageSize(InTransactionID, InSearchKeyword, InZoneTableID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SearchGameInstanceCmd::Create(messageBuffer, InTransactionID, InSearchKeyword, InZoneTableID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
	// Cmd: Search game instance
	Result NetPolicyGame::GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetCharacterDataInGameInstanceCmd::CalculateMessageSize(InTransactionID, InGameInsUID, InPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetCharacterDataInGameInstanceCmd::Create(messageBuffer, InTransactionID, InGameInsUID, InPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
	// Cmd: Request Game match
	Result NetPolicyGame::RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RequestGameMatchCmd::CalculateMessageSize(InTransactionID, InNumPlayer, InRequestRole);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RequestGameMatchCmd::Create(messageBuffer, InTransactionID, InNumPlayer, InRequestRole));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
	// Cmd: Cancel Game match
	Result NetPolicyGame::CancelGameMatchCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CancelGameMatchCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CancelGameMatchCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::CancelGameMatchCmd( const uint64_t &InTransactionID )
	// Cmd: Buy shop item prepare
	Result NetPolicyGame::BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::BuyShopItemPrepareCmd::CalculateMessageSize(InTransactionID, InShopItemID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::BuyShopItemPrepareCmd::Create(messageBuffer, InTransactionID, InShopItemID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
	// Cmd: Buy shop item
	Result NetPolicyGame::BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::BuyShopItemCmd::CalculateMessageSize(InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::BuyShopItemCmd::Create(messageBuffer, InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
	// Cmd: Create or Join Chat channel
	Result NetPolicyGame::CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CreateOrJoinChatChannelCmd::CalculateMessageSize(InTransactionID, InChannelName, InPasscode);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CreateOrJoinChatChannelCmd::Create(messageBuffer, InTransactionID, InChannelName, InPasscode));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
	// Cmd: Join
	Result NetPolicyGame::JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinChatChannelCmd::CalculateMessageSize(InTransactionID, InChatUID, InInviterID, InPasscode);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinChatChannelCmd::Create(messageBuffer, InTransactionID, InChatUID, InInviterID, InPasscode));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )
	// Cmd: Leave ChatChannel command
	Result NetPolicyGame::LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LeaveChatChannelCmd::CalculateMessageSize(InTransactionID, InChatUID, InPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LeaveChatChannelCmd::Create(messageBuffer, InTransactionID, InChatUID, InPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
	// Cmd: Kick player from the ChatChannel
	Result NetPolicyGame::ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelKickPlayerCmd::CalculateMessageSize(InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelKickPlayerCmd::Create(messageBuffer, InTransactionID, InChatUID, InPlayerID, InPlayerToKick));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	// Cmd: Chat channel sending chatting message
	Result NetPolicyGame::ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelChatMessageCmd::CalculateMessageSize(InTransactionID, InChatUID, InChatMetaData, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelChatMessageCmd::Create(messageBuffer, InTransactionID, InChatUID, InChatMetaData, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Whisper(tell) other player chatting
	Result NetPolicyGame::WhisperMessageCmd( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::WhisperMessageCmd::CalculateMessageSize(InTransactionID, InReceiverID, InReceiverName, InChatMetaData, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::WhisperMessageCmd::Create(messageBuffer, InTransactionID, InReceiverID, InReceiverName, InChatMetaData, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::WhisperMessageCmd( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create character
	Result NetPolicyGame::CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CreateCharacterCmd::CalculateMessageSize(InTransactionID, InCharacterName, InPublicData, InPrivateData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CreateCharacterCmd::Create(messageBuffer, InTransactionID, InCharacterName, InPublicData, InPrivateData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )
	// Cmd: Delete character
	Result NetPolicyGame::DeleteCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::DeleteCharacterCmd::CalculateMessageSize(InTransactionID, InCharacterID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::DeleteCharacterCmd::Create(messageBuffer, InTransactionID, InCharacterID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::DeleteCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	// Cmd: Get character list
	Result NetPolicyGame::GetCharacterListCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetCharacterListCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetCharacterListCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetCharacterListCmd( const uint64_t &InTransactionID )
	// Cmd: 
	Result NetPolicyGame::GetCharacterDataCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetCharacterDataCmd::CalculateMessageSize(InTransactionID, InCharacterID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetCharacterDataCmd::Create(messageBuffer, InTransactionID, InCharacterID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::GetCharacterDataCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	// Cmd: Select character
	Result NetPolicyGame::SelectCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SelectCharacterCmd::CalculateMessageSize(InTransactionID, InCharacterID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SelectCharacterCmd::Create(messageBuffer, InTransactionID, InCharacterID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::SelectCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
	Result NetPolicyGame::RequestServerNoticeUpdateCmd( const uint64_t &InTransactionID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RequestServerNoticeUpdateCmd::CalculateMessageSize(InTransactionID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RequestServerNoticeUpdateCmd::Create(messageBuffer, InTransactionID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::RequestServerNoticeUpdateCmd( const uint64_t &InTransactionID )
	// Cmd: To call general functionality
	Result NetPolicyGame::CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CallFunctionCmd::CalculateMessageSize(InTransactionID, InFunctionName, InParameters);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CallFunctionCmd::Create(messageBuffer, InTransactionID, InFunctionName, InParameters));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyGame::CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )


	// Cmd: Player connected from a login server and moved to game server
	Result NetSvrPolicyGame::JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinGameServerRes::CalculateMessageSize(InTransactionID, InResult, InNickName, InGameUID, InPartyUID, InPartyLeaderID, InMatchingTicket);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinGameServerRes::Create(messageBuffer, InTransactionID, InResult, InNickName, InGameUID, InPartyUID, InPartyLeaderID, InMatchingTicket));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
	// Cmd: player complition statues
	Result NetSvrPolicyGame::GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetComplitionStateRes::CalculateMessageSize(InTransactionID, InResult, InComplitionState);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetComplitionStateRes::Create(messageBuffer, InTransactionID, InResult, InComplitionState));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
	// Cmd: Player complition state
	Result NetSvrPolicyGame::SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SetComplitionStateRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SetComplitionStateRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
	Result NetSvrPolicyGame::RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RegisterGCMRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RegisterGCMRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Unregister Google notification service ID
	Result NetSvrPolicyGame::UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::UnregisterGCMRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::UnregisterGCMRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Invite friend
	Result NetSvrPolicyGame::InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::InviteFriendRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::InviteFriendRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Accept friend request
	Result NetSvrPolicyGame::AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::AcceptFriendRequestRes::CalculateMessageSize(InTransactionID, InResult, InNewFriend);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::AcceptFriendRequestRes::Create(messageBuffer, InTransactionID, InResult, InNewFriend));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
	// S2C: Notification for friend request is accepted
	Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FriendRequestAcceptedS2CEvt::CalculateMessageSize(InAccepter);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FriendRequestAcceptedS2CEvt::Create(messageBuffer, InAccepter));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
	// Cmd: Remove friden form the friend list
	Result NetSvrPolicyGame::RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RemoveFriendRes::CalculateMessageSize(InTransactionID, InResult, InFriendID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RemoveFriendRes::Create(messageBuffer, InTransactionID, InResult, InFriendID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
	// S2C: Friend removed
	Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FriendRemovedS2CEvt::CalculateMessageSize(InFriendID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FriendRemovedS2CEvt::Create(messageBuffer, InFriendID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
	// Cmd: Get friend list
	Result NetSvrPolicyGame::GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetFriendListRes::CalculateMessageSize(InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex, InFriendList);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetFriendListRes::Create(messageBuffer, InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex, InFriendList));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
	// Cmd: Query notification list
	Result NetSvrPolicyGame::GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetNotificationListRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetNotificationListRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Delete notification
	Result NetSvrPolicyGame::DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::DeleteNotificationRes::CalculateMessageSize(InTransactionID, InResult, InNotificationID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::DeleteNotificationRes::Create(messageBuffer, InTransactionID, InResult, InNotificationID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// Cmd: Set notification is read
	Result NetSvrPolicyGame::SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SetNotificationReadRes::CalculateMessageSize(InTransactionID, InResult, InNotificationID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SetNotificationReadRes::Create(messageBuffer, InTransactionID, InResult, InNotificationID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// Cmd: Accept notification
	Result NetSvrPolicyGame::AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::AcceptNotificationRes::CalculateMessageSize(InTransactionID, InResult, InNotificationID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::AcceptNotificationRes::Create(messageBuffer, InTransactionID, InResult, InNotificationID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// S2C: Notify new notification
	Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::NotifyS2CEvt::CalculateMessageSize(InNotificationID, InNotificationType, InParameters, InIsRead, InTimeStamp);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::NotifyS2CEvt::Create(messageBuffer, InNotificationID, InNotificationType, InParameters, InIsRead, InTimeStamp));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
	// Cmd: PlayerId Conversion
	Result NetSvrPolicyGame::FindPlayerByPlatformIdRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByPlatformIdRes::CalculateMessageSize(InTransactionID, InResult, InPlayerId, InPlayerPlatformId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByPlatformIdRes::Create(messageBuffer, InTransactionID, InResult, InPlayerId, InPlayerPlatformId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FindPlayerByPlatformIdRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	// Cmd: PlayerId conversion
	Result NetSvrPolicyGame::FindPlayerByCharacterNameRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByCharacterNameRes::CalculateMessageSize(InTransactionID, InResult, InPlayerId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByCharacterNameRes::Create(messageBuffer, InTransactionID, InResult, InPlayerId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FindPlayerByCharacterNameRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )
	// Cmd: PlayerId Conversion
	Result NetSvrPolicyGame::FindPlayerByPlatformUserNameRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByPlatformUserNameRes::CalculateMessageSize(InTransactionID, InResult, InPlayerId, InPlayerPlatformId);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByPlatformUserNameRes::Create(messageBuffer, InTransactionID, InResult, InPlayerId, InPlayerPlatformId));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FindPlayerByPlatformUserNameRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	// Cmd: Query playerID list
	Result NetSvrPolicyGame::FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByEMailRes::CalculateMessageSize(InTransactionID, InResult, InPlayer);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByEMailRes::Create(messageBuffer, InTransactionID, InResult, InPlayer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	// Cmd: Query playerID list
	Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::FindPlayerByPlayerIDRes::CalculateMessageSize(InTransactionID, InResult, InPlayer);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::FindPlayerByPlayerIDRes::Create(messageBuffer, InTransactionID, InResult, InPlayer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	// Cmd: *Request Player Status Update
	Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RequestPlayerStatusUpdateRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RequestPlayerStatusUpdateRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: *Notify Player Status Updated
	Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::CalculateMessageSize(InPlayerID, InLatestActiveTime, InIsInGame);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::Create(messageBuffer, InPlayerID, InLatestActiveTime, InIsInGame));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
	// Cmd: Get Ranking list
	Result NetSvrPolicyGame::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetRankingListRes::CalculateMessageSize(InTransactionID, InResult, InRanking);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetRankingListRes::Create(messageBuffer, InTransactionID, InResult, InRanking));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: Game user game play information
	Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetUserGamePlayerInfoRes::CalculateMessageSize(InTransactionID, InResult, InAttributes);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetUserGamePlayerInfoRes::Create(messageBuffer, InTransactionID, InResult, InAttributes));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	// Cmd: Game game play information
	Result NetSvrPolicyGame::GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetGamePlayerInfoRes::CalculateMessageSize(InTransactionID, InResult, InPlayerID, InAttributes);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetGamePlayerInfoRes::Create(messageBuffer, InTransactionID, InResult, InPlayerID, InAttributes));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
	// S2C: Player level up event
	Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LevelUpS2CEvt::CalculateMessageSize(InCurrentTotalExp, InCurrentLevel);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LevelUpS2CEvt::Create(messageBuffer, InCurrentTotalExp, InCurrentLevel));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
	// Cmd: Change NickName
	Result NetSvrPolicyGame::SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SetNickNameRes::CalculateMessageSize(InTransactionID, InResult, InTotalGem, InTotalGameMoney);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SetNickNameRes::Create(messageBuffer, InTransactionID, InResult, InTotalGem, InTotalGameMoney));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// Cmd: Create Party
	Result NetSvrPolicyGame::CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CreatePartyRes::CalculateMessageSize(InTransactionID, InResult, InPartyUID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CreatePartyRes::Create(messageBuffer, InTransactionID, InResult, InPartyUID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
	// Cmd: Join party
	Result NetSvrPolicyGame::JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinPartyRes::CalculateMessageSize(InTransactionID, InResult, InPartyUID, InPartyLeaderID, InChatHistoryData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinPartyRes::Create(messageBuffer, InTransactionID, InResult, InPartyUID, InPartyLeaderID, InChatHistoryData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
	// S2C: Player Joined event
	Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyPlayerJoinedS2CEvt::CalculateMessageSize(InPartyUID, InJoinedPlayer);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyPlayerJoinedS2CEvt::Create(messageBuffer, InPartyUID, InJoinedPlayer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
	// S2C: Party leader changed event
	Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyLeaderChangedS2CEvt::CalculateMessageSize(InPartyUID, InNewLeaderID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyLeaderChangedS2CEvt::Create(messageBuffer, InPartyUID, InNewLeaderID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
	// Cmd: Leave party command
	Result NetSvrPolicyGame::LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LeavePartyRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LeavePartyRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Player left event
	Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyPlayerLeftS2CEvt::CalculateMessageSize(InPartyUID, InLeftPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyPlayerLeftS2CEvt::Create(messageBuffer, InPartyUID, InLeftPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
	// Cmd: Kick player from the party
	Result NetSvrPolicyGame::PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyKickPlayerRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyKickPlayerRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Player kicked message
	Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyPlayerKickedS2CEvt::CalculateMessageSize(InPartyUID, InKickedPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyPlayerKickedS2CEvt::Create(messageBuffer, InPartyUID, InKickedPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
	// Cmd: Invite a player to the party
	Result NetSvrPolicyGame::PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyInviteRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyInviteRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party invite requested
	Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyInviteRequestedS2CEvt::CalculateMessageSize(InInviterID, InInviterName, InPartyToJoinUID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyInviteRequestedS2CEvt::Create(messageBuffer, InInviterID, InInviterName, InPartyToJoinUID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
	// Cmd: Send Party quick chat message
	Result NetSvrPolicyGame::PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyQuickChatMessageRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyQuickChatMessageRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Chatting message event
	Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyQuickChatMessageS2CEvt::CalculateMessageSize(InSenderID, InQuickChatID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyQuickChatMessageS2CEvt::Create(messageBuffer, InSenderID, InQuickChatID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
	// Cmd: Party chatting
	Result NetSvrPolicyGame::PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyChatMessageRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyChatMessageRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Chatting message event
	Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::PartyChatMessageS2CEvt::CalculateMessageSize(InSenderID, InSenderName, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::PartyChatMessageS2CEvt::Create(messageBuffer, InSenderID, InSenderName, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
	// Cmd: Join to a game instance
	Result NetSvrPolicyGame::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinGameInstanceRes::CalculateMessageSize(InTransactionID, InResult, InInsUID, InServerPublicAddress);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinGameInstanceRes::Create(messageBuffer, InTransactionID, InResult, InInsUID, InServerPublicAddress));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const char* InServerPublicAddress )
	// Cmd: Leave game instance
	Result NetSvrPolicyGame::LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LeaveGameInstanceRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LeaveGameInstanceRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Search game instance
	Result NetSvrPolicyGame::SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SearchGameInstanceRes::CalculateMessageSize(InTransactionID, InResult, InGameInstances);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SearchGameInstanceRes::Create(messageBuffer, InTransactionID, InResult, InGameInstances));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
	// Cmd: Search game instance
	Result NetSvrPolicyGame::GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetCharacterDataInGameInstanceRes::CalculateMessageSize(InTransactionID, InResult, InPlayerID, InGameInstances);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetCharacterDataInGameInstanceRes::Create(messageBuffer, InTransactionID, InResult, InPlayerID, InGameInstances));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
	// Cmd: Request Game match
	Result NetSvrPolicyGame::RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RequestGameMatchRes::CalculateMessageSize(InTransactionID, InResult, InTotalGem, InTotalGameMoney);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RequestGameMatchRes::Create(messageBuffer, InTransactionID, InResult, InTotalGem, InTotalGameMoney));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// S2C: Game matched
	Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GameMatchedS2CEvt::CalculateMessageSize(InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GameMatchedS2CEvt::Create(messageBuffer, InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData, InStamina, InTotalGem, InTotalGameMoney));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// S2C: Game match failed
	Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GameMatchFailedS2CEvt::CalculateMessageSize(InFailedReason);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GameMatchFailedS2CEvt::Create(messageBuffer, InFailedReason));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
	// S2C: Game matching started
	Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GameMatchingStartedS2CEvt::CalculateMessageSize();
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GameMatchingStartedS2CEvt::Create(messageBuffer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
	// Cmd: Cancel Game match
	Result NetSvrPolicyGame::CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CancelGameMatchRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CancelGameMatchRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: game matching canceled
	Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GameMatchingCanceledS2CEvt::CalculateMessageSize();
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GameMatchingCanceledS2CEvt::Create(messageBuffer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
	// Cmd: Buy shop item prepare
	Result NetSvrPolicyGame::BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::BuyShopItemPrepareRes::CalculateMessageSize(InTransactionID, InResult, InShopItemID, InPurchaseID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::BuyShopItemPrepareRes::Create(messageBuffer, InTransactionID, InResult, InShopItemID, InPurchaseID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
	// Cmd: Buy shop item
	Result NetSvrPolicyGame::BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::BuyShopItemRes::CalculateMessageSize(InTransactionID, InResult, InShopItemID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::BuyShopItemRes::Create(messageBuffer, InTransactionID, InResult, InShopItemID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
	// Cmd: Create or Join Chat channel
	Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CreateOrJoinChatChannelRes::CalculateMessageSize(InTransactionID, InResult, InChatUID, InChannelLeaderID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CreateOrJoinChatChannelRes::Create(messageBuffer, InTransactionID, InResult, InChatUID, InChannelLeaderID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	// Cmd: Join
	Result NetSvrPolicyGame::JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::JoinChatChannelRes::CalculateMessageSize(InTransactionID, InResult, InChatUID, InChannelLeaderID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::JoinChatChannelRes::Create(messageBuffer, InTransactionID, InResult, InChatUID, InChannelLeaderID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	// S2C: Player Joined event
	Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::CalculateMessageSize(InChatUID, InJoinedPlayer);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::Create(messageBuffer, InChatUID, InJoinedPlayer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
	// S2C: ChatChannel leader changed event
	Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::CalculateMessageSize(InChatUID, InNewLeaderID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelLeaderChangedS2CEvt::Create(messageBuffer, InChatUID, InNewLeaderID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
	// Cmd: Leave ChatChannel command
	Result NetSvrPolicyGame::LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::LeaveChatChannelRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::LeaveChatChannelRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Player left event
	Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::CalculateMessageSize(InChatUID, InLeftPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelPlayerLeftS2CEvt::Create(messageBuffer, InChatUID, InLeftPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
	// Cmd: Kick player from the ChatChannel
	Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelKickPlayerRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelKickPlayerRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Player kicked message
	Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::CalculateMessageSize(InChatUID, InKickedPlayerID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelPlayerKickedS2CEvt::Create(messageBuffer, InChatUID, InKickedPlayerID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
	// Cmd: Chat channel sending chatting message
	Result NetSvrPolicyGame::ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelChatMessageRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelChatMessageRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Chatting message event
	Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ChatChannelChatMessageS2CEvt::CalculateMessageSize(InSenderID, InChatMetaData, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(messageBuffer, InSenderID, InChatMetaData, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Whisper(tell) other player chatting
	Result NetSvrPolicyGame::WhisperMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::WhisperMessageRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::WhisperMessageRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::WhisperMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Other player whispered(tell) to me message event
	Result NetSvrPolicyGame::WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::WhisperMessageS2CEvt::CalculateMessageSize(InSenderID, InChatMetaData, InChatMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::WhisperMessageS2CEvt::Create(messageBuffer, InSenderID, InChatMetaData, InChatMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create character
	Result NetSvrPolicyGame::CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CreateCharacterRes::CalculateMessageSize(InTransactionID, InResult, InCharacterID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CreateCharacterRes::Create(messageBuffer, InTransactionID, InResult, InCharacterID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
	// Cmd: Delete character
	Result NetSvrPolicyGame::DeleteCharacterRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::DeleteCharacterRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::DeleteCharacterRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::DeleteCharacterRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Get character list
	Result NetSvrPolicyGame::GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetCharacterListRes::CalculateMessageSize(InTransactionID, InResult, InCharacters);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetCharacterListRes::Create(messageBuffer, InTransactionID, InResult, InCharacters));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
	// Cmd: 
	Result NetSvrPolicyGame::GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::GetCharacterDataRes::CalculateMessageSize(InTransactionID, InResult, InPrivateData, InEquipData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::GetCharacterDataRes::Create(messageBuffer, InTransactionID, InResult, InPrivateData, InEquipData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )
	// Cmd: Select character
	Result NetSvrPolicyGame::SelectCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::SelectCharacterRes::CalculateMessageSize(InTransactionID, InResult, InCharacterID, InAttributes);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::SelectCharacterRes::Create(messageBuffer, InTransactionID, InResult, InCharacterID, InAttributes));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::SelectCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )
	// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
	Result NetSvrPolicyGame::RequestServerNoticeUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::RequestServerNoticeUpdateRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::RequestServerNoticeUpdateRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::RequestServerNoticeUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Server Notice updated event
	Result NetSvrPolicyGame::ServerNoticeS2CEvt( const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::ServerNoticeS2CEvt::CalculateMessageSize(InNoticeCategory, InServerNoticeMessage);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::ServerNoticeS2CEvt::Create(messageBuffer, InNoticeCategory, InServerNoticeMessage));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::ServerNoticeS2CEvt( const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
	// Cmd: To call general functionality
	Result NetSvrPolicyGame::CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )
	{
 		Result hr;

		size_t messageSize = SF::Message::Game::CallFunctionRes::CalculateMessageSize(InTransactionID, InResult, InResults);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Game::CallFunctionRes::Create(messageBuffer, InTransactionID, InResult, InResults));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyGame::CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )


}; // namespace SF


