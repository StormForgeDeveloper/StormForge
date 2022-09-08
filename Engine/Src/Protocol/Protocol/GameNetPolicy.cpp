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
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::HeartbeatC2SEvt::Create(GetSystemHeap());
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::HeartbeatC2SEvt(  )
	// Cmd: Player connected from a login server and moved to game server
	Result NetPolicyGame::JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinGameServerCmd::Create(GetSystemHeap(), InTransactionID, InAccID, InTicket, InLoginEntityUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	// Cmd: player complition statues
	Result NetPolicyGame::GetComplitionStateCmd( const uint64_t &InTransactionID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetComplitionStateCmd::Create(GetSystemHeap(), InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetComplitionStateCmd( const uint64_t &InTransactionID )
	// Cmd: Player complition state
	Result NetPolicyGame::SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SetComplitionStateCmd::Create(GetSystemHeap(), InTransactionID, InComplitionState);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState )
	// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
	Result NetPolicyGame::RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RegisterGCMCmd::Create(GetSystemHeap(), InTransactionID, InGCMRegisteredID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	// Cmd: Unregister Google notification service ID
	Result NetPolicyGame::UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::UnregisterGCMCmd::Create(GetSystemHeap(), InTransactionID, InGCMRegisteredID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
	// Cmd: Invite friend
	Result NetPolicyGame::InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::InviteFriendCmd::Create(GetSystemHeap(), InTransactionID, InFriendID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	// Cmd: Accept friend request
	Result NetPolicyGame::AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::AcceptFriendRequestCmd::Create(GetSystemHeap(), InTransactionID, InInviterID, InInviterPlatformId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
	// Cmd: Remove friden form the friend list
	Result NetPolicyGame::RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RemoveFriendCmd::Create(GetSystemHeap(), InTransactionID, InFriendID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
	// Cmd: Get friend list
	Result NetPolicyGame::GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetFriendListCmd::Create(GetSystemHeap(), InTransactionID, InStartIndex, InCount);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
	// Cmd: Query notification list
	Result NetPolicyGame::GetNotificationListCmd( const uint64_t &InTransactionID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetNotificationListCmd::Create(GetSystemHeap(), InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetNotificationListCmd( const uint64_t &InTransactionID )
	// Cmd: Delete notification
	Result NetPolicyGame::DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::DeleteNotificationCmd::Create(GetSystemHeap(), InTransactionID, InNotificationID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: Set notification is read
	Result NetPolicyGame::SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SetNotificationReadCmd::Create(GetSystemHeap(), InTransactionID, InNotificationID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: Accept notification
	Result NetPolicyGame::AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::AcceptNotificationCmd::Create(GetSystemHeap(), InTransactionID, InNotificationID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: PlayerId Conversion
	Result NetPolicyGame::FindPlayerByPlatformIdCmd( const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByPlatformIdCmd::Create(GetSystemHeap(), InTransactionID, InPlatformPlayerId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::FindPlayerByPlatformIdCmd( const uint64_t &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
	// Cmd: PlayerId conversion
	Result NetPolicyGame::FindPlayerByCharacterNameCmd( const uint64_t &InTransactionID, const char* InCharacterName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByCharacterNameCmd::Create(GetSystemHeap(), InTransactionID, InCharacterName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::FindPlayerByCharacterNameCmd( const uint64_t &InTransactionID, const char* InCharacterName )
	// Cmd: Query playerID list
	Result NetPolicyGame::FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByEMailCmd::Create(GetSystemHeap(), InTransactionID, InPlayerEMail);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail )
	// Cmd: Query playerID list
	Result NetPolicyGame::FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByPlayerIDCmd::Create(GetSystemHeap(), InTransactionID, InPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	// Cmd: *Request Player Status Update
	Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RequestPlayerStatusUpdateCmd::Create(GetSystemHeap(), InTransactionID, InTargetPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
	// Cmd: Get Ranking list
	Result NetPolicyGame::GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetRankingListCmd::Create(GetSystemHeap(), InTransactionID, InRankingType, InBaseRanking, InCount);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	// Cmd: Game user game play information
	Result NetPolicyGame::GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetUserGamePlayerInfoCmd::Create(GetSystemHeap(), InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID )
	// Cmd: Game game play information
	Result NetPolicyGame::GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetGamePlayerInfoCmd::Create(GetSystemHeap(), InTransactionID, InPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
	// Cmd: Change NickName
	Result NetPolicyGame::SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SetNickNameCmd::Create(GetSystemHeap(), InTransactionID, InNickName, InIsCostFree);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
	// Cmd: Create Party
	Result NetPolicyGame::CreatePartyCmd( const uint64_t &InTransactionID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CreatePartyCmd::Create(GetSystemHeap(), InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::CreatePartyCmd( const uint64_t &InTransactionID )
	// Cmd: Join party
	Result NetPolicyGame::JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinPartyCmd::Create(GetSystemHeap(), InTransactionID, InPartyUID, InInviterID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
	// Cmd: Leave party command
	Result NetPolicyGame::LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LeavePartyCmd::Create(GetSystemHeap(), InTransactionID, InPartyUID, InPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
	// Cmd: Kick player from the party
	Result NetPolicyGame::PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyKickPlayerCmd::Create(GetSystemHeap(), InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	// Cmd: Invite a player to the party
	Result NetPolicyGame::PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyInviteCmd::Create(GetSystemHeap(), InTransactionID, InInviteTargetID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
	// Cmd: Send Party quick chat message
	Result NetPolicyGame::PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyQuickChatMessageCmd::Create(GetSystemHeap(), InTransactionID, InQuickChatID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
	// Cmd: Party chatting
	Result NetPolicyGame::PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyChatMessageCmd::Create(GetSystemHeap(), InTransactionID, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage )
	// Cmd: Join to a game instance
	Result NetPolicyGame::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinGameInstanceCmd::Create(GetSystemHeap(), InTransactionID, InInsUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	// Cmd: Leave game instance
	Result NetPolicyGame::LeaveGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LeaveGameInstanceCmd::Create(GetSystemHeap(), InTransactionID, InInsUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::LeaveGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID )
	// Cmd: Search game instance
	Result NetPolicyGame::SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SearchGameInstanceCmd::Create(GetSystemHeap(), InTransactionID, InSearchKeyword, InZoneTableID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
	// Cmd: Search game instance
	Result NetPolicyGame::GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetCharacterDataInGameInstanceCmd::Create(GetSystemHeap(), InTransactionID, InGameInsUID, InPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
	// Cmd: Request Game match
	Result NetPolicyGame::RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RequestGameMatchCmd::Create(GetSystemHeap(), InTransactionID, InNumPlayer, InRequestRole);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
	// Cmd: Cancel Game match
	Result NetPolicyGame::CancelGameMatchCmd( const uint64_t &InTransactionID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CancelGameMatchCmd::Create(GetSystemHeap(), InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::CancelGameMatchCmd( const uint64_t &InTransactionID )
	// Cmd: Buy shop item prepare
	Result NetPolicyGame::BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::BuyShopItemPrepareCmd::Create(GetSystemHeap(), InTransactionID, InShopItemID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
	// Cmd: Buy shop item
	Result NetPolicyGame::BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::BuyShopItemCmd::Create(GetSystemHeap(), InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
	// Cmd: Create or Join Chat channel
	Result NetPolicyGame::CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CreateOrJoinChatChannelCmd::Create(GetSystemHeap(), InTransactionID, InChannelName, InPasscode);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
	// Cmd: Join
	Result NetPolicyGame::JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinChatChannelCmd::Create(GetSystemHeap(), InTransactionID, InChatUID, InInviterID, InPasscode);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode )
	// Cmd: Leave ChatChannel command
	Result NetPolicyGame::LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LeaveChatChannelCmd::Create(GetSystemHeap(), InTransactionID, InChatUID, InPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
	// Cmd: Kick player from the ChatChannel
	Result NetPolicyGame::ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelKickPlayerCmd::Create(GetSystemHeap(), InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	// Cmd: Chat channel sending chatting message
	Result NetPolicyGame::ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelChatMessageCmd::Create(GetSystemHeap(), InTransactionID, InChatUID, InChatMetaData, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Whisper(tell) other player chatting
	Result NetPolicyGame::WhisperMessageCmd( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::WhisperMessageCmd::Create(GetSystemHeap(), InTransactionID, InReceiverID, InReceiverName, InChatMetaData, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::WhisperMessageCmd( const uint64_t &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create character
	Result NetPolicyGame::CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InVisualData, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CreateCharacterCmd::Create(GetSystemHeap(), InTransactionID, InCharacterName, InVisualData, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InVisualData, const VariableTable &InAttributes )
	// Cmd: Delete character
	Result NetPolicyGame::DeleteCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::DeleteCharacterCmd::Create(GetSystemHeap(), InTransactionID, InCharacterID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::DeleteCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	// Cmd: Get character list
	Result NetPolicyGame::GetCharacterListCmd( const uint64_t &InTransactionID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetCharacterListCmd::Create(GetSystemHeap(), InTransactionID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetCharacterListCmd( const uint64_t &InTransactionID )
	// Cmd: 
	Result NetPolicyGame::GetCharacterDataCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetCharacterDataCmd::Create(GetSystemHeap(), InTransactionID, InCharacterID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::GetCharacterDataCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	// Cmd: Select character
	Result NetPolicyGame::SelectCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SelectCharacterCmd::Create(GetSystemHeap(), InTransactionID, InCharacterID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::SelectCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID )
	// Cmd: To call general functionality
	Result NetPolicyGame::CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CallFunctionCmd::Create(GetSystemHeap(), InTransactionID, InFunctionName, InParameters);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyGame::CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )


	// Cmd: Player connected from a login server and moved to game server
	Result NetSvrPolicyGame::JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinGameServerRes::Create(GetSystemHeap(), InTransactionID, InResult, InNickName, InGameUID, InPartyUID, InPartyLeaderID, InMatchingTicket);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
	// Cmd: player complition statues
	Result NetSvrPolicyGame::GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetComplitionStateRes::Create(GetSystemHeap(), InTransactionID, InResult, InComplitionState);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
	// Cmd: Player complition state
	Result NetSvrPolicyGame::SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SetComplitionStateRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
	Result NetSvrPolicyGame::RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RegisterGCMRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Unregister Google notification service ID
	Result NetSvrPolicyGame::UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::UnregisterGCMRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Invite friend
	Result NetSvrPolicyGame::InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::InviteFriendRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Accept friend request
	Result NetSvrPolicyGame::AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::AcceptFriendRequestRes::Create(GetSystemHeap(), InTransactionID, InResult, InNewFriend);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
	// S2C: Notification for friend request is accepted
	Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FriendRequestAcceptedS2CEvt::Create(GetSystemHeap(), InAccepter);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
	// Cmd: Remove friden form the friend list
	Result NetSvrPolicyGame::RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RemoveFriendRes::Create(GetSystemHeap(), InTransactionID, InResult, InFriendID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
	// S2C: Friend removed
	Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FriendRemovedS2CEvt::Create(GetSystemHeap(), InFriendID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
	// Cmd: Get friend list
	Result NetSvrPolicyGame::GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetFriendListRes::Create(GetSystemHeap(), InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex, InFriendList);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
	// Cmd: Query notification list
	Result NetSvrPolicyGame::GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetNotificationListRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Delete notification
	Result NetSvrPolicyGame::DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::DeleteNotificationRes::Create(GetSystemHeap(), InTransactionID, InResult, InNotificationID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// Cmd: Set notification is read
	Result NetSvrPolicyGame::SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SetNotificationReadRes::Create(GetSystemHeap(), InTransactionID, InResult, InNotificationID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// Cmd: Accept notification
	Result NetSvrPolicyGame::AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::AcceptNotificationRes::Create(GetSystemHeap(), InTransactionID, InResult, InNotificationID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// S2C: Notify new notification
	Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::NotifyS2CEvt::Create(GetSystemHeap(), InNotificationID, InNotificationType, InMessageParam0, InMessageParam1, InMessageText, InIsRead, InTimeStamp);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
	// Cmd: PlayerId Conversion
	Result NetSvrPolicyGame::FindPlayerByPlatformIdRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByPlatformIdRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayerId, InPlayerPlatformId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::FindPlayerByPlatformIdRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	// Cmd: PlayerId conversion
	Result NetSvrPolicyGame::FindPlayerByCharacterNameRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId, const CharacterID &InCharacterId )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByCharacterNameRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayerId, InPlayerPlatformId, InCharacterId);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::FindPlayerByCharacterNameRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId, const CharacterID &InCharacterId )
	// Cmd: Query playerID list
	Result NetSvrPolicyGame::FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByEMailRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayer);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	// Cmd: Query playerID list
	Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::FindPlayerByPlayerIDRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayer);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	// Cmd: *Request Player Status Update
	Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RequestPlayerStatusUpdateRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: *Notify Player Status Updated
	Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::Create(GetSystemHeap(), InPlayerID, InLatestActiveTime, InIsInGame);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
	// Cmd: Get Ranking list
	Result NetSvrPolicyGame::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetRankingListRes::Create(GetSystemHeap(), InTransactionID, InResult, InRanking);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: Game user game play information
	Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetUserGamePlayerInfoRes::Create(GetSystemHeap(), InTransactionID, InResult, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	// Cmd: Game game play information
	Result NetSvrPolicyGame::GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetGamePlayerInfoRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayerID, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
	// S2C: Player level up event
	Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LevelUpS2CEvt::Create(GetSystemHeap(), InCurrentTotalExp, InCurrentLevel);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
	// Cmd: Change NickName
	Result NetSvrPolicyGame::SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SetNickNameRes::Create(GetSystemHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// Cmd: Create Party
	Result NetSvrPolicyGame::CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CreatePartyRes::Create(GetSystemHeap(), InTransactionID, InResult, InPartyUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
	// Cmd: Join party
	Result NetSvrPolicyGame::JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinPartyRes::Create(GetSystemHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID, InChatHistoryData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
	// S2C: Player Joined event
	Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyPlayerJoinedS2CEvt::Create(GetSystemHeap(), InPartyUID, InJoinedPlayer);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
	// S2C: Party leader changed event
	Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyLeaderChangedS2CEvt::Create(GetSystemHeap(), InPartyUID, InNewLeaderID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
	// Cmd: Leave party command
	Result NetSvrPolicyGame::LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LeavePartyRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Player left event
	Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyPlayerLeftS2CEvt::Create(GetSystemHeap(), InPartyUID, InLeftPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
	// Cmd: Kick player from the party
	Result NetSvrPolicyGame::PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyKickPlayerRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Player kicked message
	Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyPlayerKickedS2CEvt::Create(GetSystemHeap(), InPartyUID, InKickedPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
	// Cmd: Invite a player to the party
	Result NetSvrPolicyGame::PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyInviteRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party invite requested
	Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyInviteRequestedS2CEvt::Create(GetSystemHeap(), InInviterID, InInviterName, InPartyToJoinUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
	// Cmd: Send Party quick chat message
	Result NetSvrPolicyGame::PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyQuickChatMessageRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Chatting message event
	Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyQuickChatMessageS2CEvt::Create(GetSystemHeap(), InSenderID, InQuickChatID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
	// Cmd: Party chatting
	Result NetSvrPolicyGame::PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyChatMessageRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Party Chatting message event
	Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::PartyChatMessageS2CEvt::Create(GetSystemHeap(), InSenderID, InSenderName, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
	// Cmd: Join to a game instance
	Result NetSvrPolicyGame::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress4, const NetAddress &InServerAddress6 )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinGameInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult, InInsUID, InServerAddress4, InServerAddress6);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress4, const NetAddress &InServerAddress6 )
	// Cmd: Leave game instance
	Result NetSvrPolicyGame::LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LeaveGameInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Search game instance
	Result NetSvrPolicyGame::SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SearchGameInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult, InGameInstances);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
	// Cmd: Search game instance
	Result NetSvrPolicyGame::GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetCharacterDataInGameInstanceRes::Create(GetSystemHeap(), InTransactionID, InResult, InPlayerID, InGameInstances);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
	// Cmd: Request Game match
	Result NetSvrPolicyGame::RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::RequestGameMatchRes::Create(GetSystemHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// S2C: Game matched
	Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GameMatchedS2CEvt::Create(GetSystemHeap(), InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// S2C: Game match failed
	Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GameMatchFailedS2CEvt::Create(GetSystemHeap(), InFailedReason);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
	// S2C: Game matching started
	Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GameMatchingStartedS2CEvt::Create(GetSystemHeap());
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
	// Cmd: Cancel Game match
	Result NetSvrPolicyGame::CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CancelGameMatchRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: game matching canceled
	Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GameMatchingCanceledS2CEvt::Create(GetSystemHeap());
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
	// Cmd: Buy shop item prepare
	Result NetSvrPolicyGame::BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::BuyShopItemPrepareRes::Create(GetSystemHeap(), InTransactionID, InResult, InShopItemID, InPurchaseID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
	// Cmd: Buy shop item
	Result NetSvrPolicyGame::BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::BuyShopItemRes::Create(GetSystemHeap(), InTransactionID, InResult, InShopItemID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
	// Cmd: Create or Join Chat channel
	Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CreateOrJoinChatChannelRes::Create(GetSystemHeap(), InTransactionID, InResult, InChatUID, InChannelLeaderID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	// Cmd: Join
	Result NetSvrPolicyGame::JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::JoinChatChannelRes::Create(GetSystemHeap(), InTransactionID, InResult, InChatUID, InChannelLeaderID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID, const PlayerID &InChannelLeaderID )
	// S2C: Player Joined event
	Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::Create(GetSystemHeap(), InChatUID, InJoinedPlayer);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
	// S2C: ChatChannel leader changed event
	Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::Create(GetSystemHeap(), InChatUID, InNewLeaderID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
	// Cmd: Leave ChatChannel command
	Result NetSvrPolicyGame::LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::LeaveChatChannelRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Player left event
	Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::Create(GetSystemHeap(), InChatUID, InLeftPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
	// Cmd: Kick player from the ChatChannel
	Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelKickPlayerRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Player kicked message
	Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::Create(GetSystemHeap(), InChatUID, InKickedPlayerID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
	// Cmd: Chat channel sending chatting message
	Result NetSvrPolicyGame::ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelChatMessageRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Chatting message event
	Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(GetSystemHeap(), InSenderID, InChatMetaData, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Whisper(tell) other player chatting
	Result NetSvrPolicyGame::WhisperMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::WhisperMessageRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::WhisperMessageRes( const uint64_t &InTransactionID, const Result &InResult )
	// S2C: Other player whispered(tell) to me message event
	Result NetSvrPolicyGame::WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::WhisperMessageS2CEvt::Create(GetSystemHeap(), InSenderID, InChatMetaData, InChatMessage);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create character
	Result NetSvrPolicyGame::CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CreateCharacterRes::Create(GetSystemHeap(), InTransactionID, InResult, InCharacterID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID )
	// Cmd: Delete character
	Result NetSvrPolicyGame::DeleteCharacterRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::DeleteCharacterRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::DeleteCharacterRes( const uint64_t &InTransactionID, const Result &InResult )
	// Cmd: Get character list
	Result NetSvrPolicyGame::GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetCharacterListRes::Create(GetSystemHeap(), InTransactionID, InResult, InCharacters);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
	// Cmd: 
	Result NetSvrPolicyGame::GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::GetCharacterDataRes::Create(GetSystemHeap(), InTransactionID, InResult, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	// Cmd: Select character
	Result NetSvrPolicyGame::SelectCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::SelectCharacterRes::Create(GetSystemHeap(), InTransactionID, InResult, InCharacterID, InAttributes);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::SelectCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes )
	// Cmd: To call general functionality
	Result NetSvrPolicyGame::CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Game::CallFunctionRes::Create(GetSystemHeap(), InTransactionID, InResult, InResults);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyGame::CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults )


}; // namespace SF


