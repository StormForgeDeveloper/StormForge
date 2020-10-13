////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromFOrge
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
#include "Net/SFConnection.h"
#include "Protocol/Policy/GameNetPolicy.h"
#include "Protocol/Message/GameMsgClass.h"



namespace SF
{
 	namespace Policy
	{
 		// C2S: Client heart bit
		Result NetPolicyGame::HeartBitC2SEvt(  )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::HeartBitC2SEvt::Create(m_pConnection->GetIOHeap());
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::HeartBitC2SEvt(  )
		// Cmd: Player connected from a login server and moved to game server
		Result NetPolicyGame::JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameServerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InAccID, InTicket, InLoginEntityUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		// Cmd: player complition statues
		Result NetPolicyGame::GetComplitionStateCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetComplitionStateCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetComplitionStateCmd( const uint64_t &InTransactionID )
		// Cmd: Player complition state
		Result NetPolicyGame::SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetComplitionStateCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InComplitionState);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState )
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result NetPolicyGame::RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RegisterGCMCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGCMRegisteredID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
		// Cmd: Unregister Google notification service ID
		Result NetPolicyGame::UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::UnregisterGCMCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGCMRegisteredID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID )
		// Cmd: Invite friend
		Result NetPolicyGame::InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::InviteFriendCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InFriendID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
		// Cmd: Accept friend request
		Result NetPolicyGame::AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptFriendRequestCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InInviterID, InInviterFacebookUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )
		// Cmd: Remove friden form the friend list
		Result NetPolicyGame::RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemoveFriendCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InFriendID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID )
		// Cmd: Get friend list
		Result NetPolicyGame::GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetFriendListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InStartIndex, InCount);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
		// Cmd: Query notification list
		Result NetPolicyGame::GetNotificationListCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetNotificationListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetNotificationListCmd( const uint64_t &InTransactionID )
		// Cmd: Delete notification
		Result NetPolicyGame::DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::DeleteNotificationCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNotificationID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
		// Cmd: Set notification is read
		Result NetPolicyGame::SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNotificationReadCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNotificationID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
		// Cmd: Accept notification
		Result NetPolicyGame::AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptNotificationCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNotificationID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID )
		// Cmd: Query playerID list
		Result NetPolicyGame::FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByEMailCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerEMail);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail )
		// Cmd: Query playerID list
		Result NetPolicyGame::FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByPlayerIDCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
		// Cmd: *Request Player Status Update
		Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestPlayerStatusUpdateCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTargetPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		// Cmd: Get Ranking lise
		Result NetPolicyGame::GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetRankingListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InRankingType, InBaseRanking, InCount);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
		// Cmd: Game user game play information
		Result NetPolicyGame::GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetUserGamePlayerInfoCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID )
		// Cmd: Game game play information
		Result NetPolicyGame::GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetGamePlayerInfoCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID )
		// Cmd: Change NickName
		Result NetPolicyGame::SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNickNameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNickName, InIsCostFree);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
		// Cmd: Create Party
		Result NetPolicyGame::CreatePartyCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreatePartyCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::CreatePartyCmd( const uint64_t &InTransactionID )
		// Cmd: Join party
		Result NetPolicyGame::JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinPartyCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPartyUID, InInviterID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
		// Cmd: Leave party command
		Result NetPolicyGame::LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeavePartyCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPartyUID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
		// Cmd: Kick player from the party
		Result NetPolicyGame::PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyKickPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		// Cmd: Invite a player to the party
		Result NetPolicyGame::PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyInviteCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InInviteTargetID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID )
		// Cmd: Send Party quick chat message
		Result NetPolicyGame::PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyQuickChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InQuickChatID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID )
		// Cmd: Party chatting
		Result NetPolicyGame::PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatMessage);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage )
		// Cmd: Join to a game instance
		Result NetPolicyGame::JoinGameInstanceCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameInstanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID, InTicket, InInsUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::JoinGameInstanceCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		// Cmd: Leave game instance
		Result NetPolicyGame::LeaveGameInstanceCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveGameInstanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID, InTicket, InInsUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::LeaveGameInstanceCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		// Cmd: Search game instance
		Result NetPolicyGame::SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SearchGameInstanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InSearchKeyword);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword )
		// Cmd: Search game instance
		Result NetPolicyGame::GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetCharacterDataInGameInstanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID )
		// C2S: Player Movement
		Result NetPolicyGame::PlayerMovementC2SEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerMovementC2SEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::PlayerMovementC2SEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// Cmd: Join to a game
		Result NetPolicyGame::JoinGameCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID, InTicket, InInsUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::JoinGameCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		// Cmd: Leave Game
		Result NetPolicyGame::LeaveGameCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveGameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::LeaveGameCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Kick player
		Result NetPolicyGame::KickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::KickPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InPlayerToKick);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::KickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		// Cmd: Assign role + Game state reset
		Result NetPolicyGame::AssignRoleCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AssignRoleCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::AssignRoleCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Send chatting message to the game
		Result NetPolicyGame::ChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatMessage, InRole);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::ChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole )
		// Cmd: Advance game
		Result NetPolicyGame::AdvanceGameCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AdvanceGameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::AdvanceGameCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Vote game advance
		Result NetPolicyGame::VoteGameAdvanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteGameAdvanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::VoteGameAdvanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Vote
		Result NetPolicyGame::VoteCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket, InVoteTarget, InActionSerial);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::VoteCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )
		// Cmd: Play again with the current players
		Result NetPolicyGame::GamePlayAgainCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayAgainCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GamePlayAgainCmd( const uint64_t &InTransactionID )
		// Cmd: Player. reveal a player
		Result NetPolicyGame::GameRevealPlayerCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameRevealPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTargetPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GameRevealPlayerCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		// Cmd: Player. revive himself
		Result NetPolicyGame::GamePlayerReviveCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerReviveCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GamePlayerReviveCmd( const uint64_t &InTransactionID )
		// Cmd: Player. reset ranking
		Result NetPolicyGame::GamePlayerResetRankCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerResetRankCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GamePlayerResetRankCmd( const uint64_t &InTransactionID )
		// Cmd: Request Game match
		Result NetPolicyGame::RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestGameMatchCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNumPlayer, InRequestRole);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
		// Cmd: Cancel Game match
		Result NetPolicyGame::CancelGameMatchCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CancelGameMatchCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::CancelGameMatchCmd( const uint64_t &InTransactionID )
		// Cmd: Buy shop item prepare
		Result NetPolicyGame::BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemPrepareCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InShopItemID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID )
		// Cmd: Buy shop item
		Result NetPolicyGame::BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
		// Cmd: Create or Join Chat channel
		Result NetPolicyGame::CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreateOrJoinChatChannelCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChannelName, InPasscode);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode )
		// Cmd: Join
		Result NetPolicyGame::JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinChatChannelCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InInviterID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )
		// Cmd: Leave ChatChannel command
		Result NetPolicyGame::LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveChatChannelCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
		// Cmd: Kick player from the ChatChannel
		Result NetPolicyGame::ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelKickPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		// Cmd: Party chatting
		Result NetPolicyGame::ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InChatMessage);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )
		// Cmd: Create character
		Result NetPolicyGame::CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreateCharacterCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InCharacterName, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InAttributes )
		// Cmd: Remove character
		Result NetPolicyGame::RemoveCharacterCmd( const uint64_t &InTransactionID, const int32_t &InCharacterID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemoveCharacterCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InCharacterID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::RemoveCharacterCmd( const uint64_t &InTransactionID, const int32_t &InCharacterID )
		// Cmd: Get character list
		Result NetPolicyGame::GetCharacterListCmd( const uint64_t &InTransactionID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetCharacterListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetCharacterListCmd( const uint64_t &InTransactionID )
		// Cmd: 
		Result NetPolicyGame::GetCharacterDataCmd( const uint64_t &InTransactionID, const int32_t &InCharacterID, const char* InAttributeNames )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetCharacterDataCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InCharacterID, InAttributeNames);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GetCharacterDataCmd( const uint64_t &InTransactionID, const int32_t &InCharacterID, const char* InAttributeNames )
		// Cmd: Give my stamina to other player
		Result NetPolicyGame::GiveStaminaCmd( const uint64_t &InTransactionID, const AccountID &InTargetPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GiveStaminaCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTargetPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::GiveStaminaCmd( const uint64_t &InTransactionID, const AccountID &InTargetPlayer )
		// Cmd: For debug, Change configue preset
		Result NetPolicyGame::SetPresetGameConfigIDCmd( const uint64_t &InTransactionID, const uint32_t &InPresetID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetPresetGameConfigIDCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPresetID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyGame::SetPresetGameConfigIDCmd( const uint64_t &InTransactionID, const uint32_t &InPresetID )


		// Cmd: Player connected from a login server and moved to game server
		Result NetSvrPolicyGame::JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameServerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNickName, InGameUID, InPartyUID, InPartyLeaderID, InMatchingTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
		// Cmd: player complition statues
		Result NetSvrPolicyGame::GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetComplitionStateRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InComplitionState);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState )
		// Cmd: Player complition state
		Result NetSvrPolicyGame::SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetComplitionStateRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result NetSvrPolicyGame::RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RegisterGCMRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Unregister Google notification service ID
		Result NetSvrPolicyGame::UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::UnregisterGCMRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Invite friend
		Result NetSvrPolicyGame::InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::InviteFriendRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Accept friend request
		Result NetSvrPolicyGame::AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptFriendRequestRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNewFriend);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
		// S2C: Notification for friend request is accepted
		Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::FriendRequestAcceptedS2CEvt::Create(m_pConnection->GetIOHeap(), InAccepter);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
		// Cmd: Remove friden form the friend list
		Result NetSvrPolicyGame::RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemoveFriendRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InFriendID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID )
		// S2C: Friend removed
		Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::FriendRemovedS2CEvt::Create(m_pConnection->GetIOHeap(), InFriendID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
		// Cmd: Get friend list
		Result NetSvrPolicyGame::GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetFriendListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex, InFriendList);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
		// Cmd: Query notification list
		Result NetSvrPolicyGame::GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetNotificationListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Delete notification
		Result NetSvrPolicyGame::DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::DeleteNotificationRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNotificationID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		// Cmd: Set notification is read
		Result NetSvrPolicyGame::SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNotificationReadRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNotificationID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		// Cmd: Accept notification
		Result NetSvrPolicyGame::AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptNotificationRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNotificationID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		// S2C: Notify new notification
		Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::NotifyS2CEvt::Create(m_pConnection->GetIOHeap(), InNotificationID, InNotificationType, InMessageParam0, InMessageParam1, InMessageText, InIsRead, InTimeStamp);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
		// Cmd: Query playerID list
		Result NetSvrPolicyGame::FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByEMailRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		// Cmd: Query playerID list
		Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByPlayerIDRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		// Cmd: *Request Player Status Update
		Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestPlayerStatusUpdateRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: *Notify Player Status Updated
		Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::Create(m_pConnection->GetIOHeap(), InPlayerID, InLatestActiveTime, InIsInGame);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
		// Cmd: Get Ranking lise
		Result NetSvrPolicyGame::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetRankingListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InRanking);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		// Cmd: Game user game play information
		Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetUserGamePlayerInfoRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
		// Cmd: Game game play information
		Result NetSvrPolicyGame::GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetGamePlayerInfoRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
		// S2C: Player level up event
		Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LevelUpS2CEvt::Create(m_pConnection->GetIOHeap(), InCurrentTotalExp, InCurrentLevel);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
		// Cmd: Change NickName
		Result NetSvrPolicyGame::SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNickNameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// Cmd: Create Party
		Result NetSvrPolicyGame::CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreatePartyRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPartyUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
		// Cmd: Join party
		Result NetSvrPolicyGame::JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinPartyRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID, InChatHistoryData);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
		// S2C: Player Joined event
		Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyPlayerJoinedS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InJoinedPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
		// S2C: Party leader changed event
		Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyLeaderChangedS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InNewLeaderID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
		// Cmd: Leave party command
		Result NetSvrPolicyGame::LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeavePartyRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Party Player left event
		Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyPlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InLeftPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
		// Cmd: Kick player from the party
		Result NetSvrPolicyGame::PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyKickPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Party Player kicked message
		Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyPlayerKickedS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InKickedPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
		// Cmd: Invite a player to the party
		Result NetSvrPolicyGame::PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyInviteRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Party invite requested
		Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyInviteRequestedS2CEvt::Create(m_pConnection->GetIOHeap(), InInviterID, InInviterName, InPartyToJoinUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
		// Cmd: Send Party quick chat message
		Result NetSvrPolicyGame::PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyQuickChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Party Chatting message event
		Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyQuickChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InQuickChatID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
		// Cmd: Party chatting
		Result NetSvrPolicyGame::PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Party Chatting message event
		Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InSenderName, InChatMessage);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		// Cmd: Join to a game instance
		Result NetSvrPolicyGame::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameInstanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InInsUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID )
		// Cmd: Leave game instance
		Result NetSvrPolicyGame::LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveGameInstanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InInsUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID )
		// Cmd: Search game instance
		Result NetSvrPolicyGame::SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<GameInstanceInfo>& InGameInstances )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SearchGameInstanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InGameInstances);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<GameInstanceInfo>& InGameInstances )
		// Cmd: Search game instance
		Result NetSvrPolicyGame::GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetCharacterDataInGameInstanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayerID, InGameInstances);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
		// S2C: New Player in get view
		Result NetSvrPolicyGame::NewPlayerInViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::NewPlayerInViewS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::NewPlayerInViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// S2C: Remove player from view
		Result NetSvrPolicyGame::RemovePlayerFromViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemovePlayerFromViewS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RemovePlayerFromViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// S2C: Player Movement
		Result NetSvrPolicyGame::PlayerMovementS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerMovementS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PlayerMovementS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes )
		// Cmd: Join to a game
		Result NetSvrPolicyGame::JoinGameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::JoinGameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )
		// S2C: Player Joined in the game
		Result NetSvrPolicyGame::PlayerJoinedS2CEvt( const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerJoinedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InJoinedPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PlayerJoinedS2CEvt( const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer )
		// Cmd: Leave Game
		Result NetSvrPolicyGame::LeaveGameRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveGameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::LeaveGameRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Player left event
		Result NetSvrPolicyGame::PlayerLeftS2CEvt( const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InLeftPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PlayerLeftS2CEvt( const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )
		// Cmd: Kick player
		Result NetSvrPolicyGame::KickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::KickPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::KickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Player kicked
		Result NetSvrPolicyGame::PlayerKickedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerKickedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InKickedPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PlayerKickedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )
		// Cmd: Assign role + Game state reset
		Result NetSvrPolicyGame::AssignRoleRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AssignRoleRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::AssignRoleRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Role assigned event
		Result NetSvrPolicyGame::RoleAssignedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RoleAssignedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InRole);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RoleAssignedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )
		// Cmd: Send chatting message to the game
		Result NetSvrPolicyGame::ChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Chatting message event 
		Result NetSvrPolicyGame::ChatMessageS2CEvt( const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InRole, InSenderName, InChatMessage);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatMessageS2CEvt( const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )
		// Cmd: Advance game
		Result NetSvrPolicyGame::AdvanceGameRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::AdvanceGameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::AdvanceGameRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: The game state is advanced
		Result NetSvrPolicyGame::GameAdvancedS2CEvt( const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameAdvancedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InTimeStamp, InGameState, InDay);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameAdvancedS2CEvt( const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )
		// S2C: Game is ended
		Result NetSvrPolicyGame::GameEndedS2CEvt( const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameEndedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InWinner, InGainedExp, InGainedGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameEndedS2CEvt( const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )
		// Cmd: Vote game advance
		Result NetSvrPolicyGame::VoteGameAdvanceRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteGameAdvanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::VoteGameAdvanceRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: GameAdvance is Voted
		Result NetSvrPolicyGame::GameAdvanceVotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameAdvanceVotedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InVoter);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameAdvanceVotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter )
		// Cmd: Vote
		Result NetSvrPolicyGame::VoteRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::VoteRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: Player Voted
		Result NetSvrPolicyGame::VotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::VotedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InVoter, InVotedTarget);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::VotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )
		// S2C: Vote is ended
		Result NetSvrPolicyGame::VoteEndS2CEvt( const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteEndS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InVoted);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::VoteEndS2CEvt( const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )
		// S2C: Player Killed
		Result NetSvrPolicyGame::PlayerKilledS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerKilledS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InKilledPlayer, InReason);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PlayerKilledS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )
		// S2C: Player Voted
		Result NetSvrPolicyGame::PlayerRevealedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerRevealedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InRevealedPlayerID, InRole, InReason);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::PlayerRevealedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )
		// Cmd: Play again with the current players
		Result NetSvrPolicyGame::GamePlayAgainRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayAgainRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayAgainRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
		Result NetSvrPolicyGame::GamePlayAgainS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeadPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayAgainS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InLeadPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayAgainS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeadPlayer )
		// Cmd: Player. reveal a player
		Result NetSvrPolicyGame::GameRevealPlayerRes( const uint64_t &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameRevealPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InRevealedPlayerID, InRevealedRole, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameRevealPlayerRes( const uint64_t &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// Cmd: Player. revive himself
		Result NetSvrPolicyGame::GamePlayerReviveRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerReviveRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayerReviveRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Player is revived
		Result NetSvrPolicyGame::GamePlayerRevivedS2CEvt( const AccountID &InRevivedPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerRevivedS2CEvt::Create(m_pConnection->GetIOHeap(), InRevivedPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayerRevivedS2CEvt( const AccountID &InRevivedPlayerID )
		// Cmd: Player. reset ranking
		Result NetSvrPolicyGame::GamePlayerResetRankRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerResetRankRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayerResetRankRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// Cmd: Request Game match
		Result NetSvrPolicyGame::RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestGameMatchRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Game matched
		Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchedS2CEvt::Create(m_pConnection->GetIOHeap(), InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Game match failed
		Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchFailedS2CEvt::Create(m_pConnection->GetIOHeap(), InFailedReason);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
		// S2C: Game matching started
		Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchingStartedS2CEvt::Create(m_pConnection->GetIOHeap());
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
		// Cmd: Cancel Game match
		Result NetSvrPolicyGame::CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CancelGameMatchRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: game matching canceled
		Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchingCanceledS2CEvt::Create(m_pConnection->GetIOHeap());
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
		// Cmd: Buy shop item prepare
		Result NetSvrPolicyGame::BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemPrepareRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InShopItemID, InPurchaseID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
		// Cmd: Buy shop item
		Result NetSvrPolicyGame::BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InShopItemID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
		// Cmd: Create or Join Chat channel
		Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreateOrJoinChatChannelRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InChatUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID )
		// Cmd: Join
		Result NetSvrPolicyGame::JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinChatChannelRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )
		// S2C: Player Joined event
		Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InJoinedPlayer);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
		// S2C: ChatChannel leader changed event
		Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InNewLeaderID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
		// Cmd: Leave ChatChannel command
		Result NetSvrPolicyGame::LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveChatChannelRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: ChatChannel Player left event
		Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InLeftPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
		// Cmd: Kick player from the ChatChannel
		Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelKickPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: ChatChannel Player kicked message
		Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InKickedPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
		// Cmd: Party chatting
		Result NetSvrPolicyGame::ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult )
		// S2C: ChatChannel Chatting message event
		Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InSenderName, InChatMessage);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		// Cmd: Create character
		Result NetSvrPolicyGame::CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const int32_t &InCharacterID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreateCharacterRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InCharacterID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const int32_t &InCharacterID )
		// Cmd: Remove character
		Result NetSvrPolicyGame::RemoveCharacterRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemoveCharacterRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::RemoveCharacterRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Get character list
		Result NetSvrPolicyGame::GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<int32_t>& InCharacterIDs )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetCharacterListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InCharacterIDs);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<int32_t>& InCharacterIDs )
		// Cmd: 
		Result NetSvrPolicyGame::GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetCharacterDataRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InAttributes);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
		// Cmd: Give my stamina to other player
		Result NetSvrPolicyGame::GiveStaminaRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::GiveStaminaRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTargetPlayer, InTimeStamp);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::GiveStaminaRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )
		// Cmd: For debug, Change configue preset
		Result NetSvrPolicyGame::SetPresetGameConfigIDRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetPresetGameConfigIDRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyGame::SetPresetGameConfigIDRes( const uint64_t &InTransactionID, const Result &InResult )


	}; // namespace Policy
}; // namespace SF


