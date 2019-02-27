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
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::HeartBitC2SEvt::Create(m_pConnection->GetIOHeap());
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::HeartBitC2SEvt(  )
		// Cmd: Player connected from a login server and moved to game server
		Result NetPolicyGame::JoinGameServerCmd( const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameServerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InAccID, InTicket, InLoginEntityUID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::JoinGameServerCmd( const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		// Cmd: player complition statues
		Result NetPolicyGame::GetComplitionStateCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetComplitionStateCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GetComplitionStateCmd( const TransactionID &InTransactionID )
		// Cmd: Player complition state
		Result NetPolicyGame::SetComplitionStateCmd( const TransactionID &InTransactionID, const char* InComplitionState )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetComplitionStateCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InComplitionState);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::SetComplitionStateCmd( const TransactionID &InTransactionID, const char* InComplitionState )
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result NetPolicyGame::RegisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RegisterGCMCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGCMRegisteredID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::RegisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
		// Cmd: Unregister Google notification service ID
		Result NetPolicyGame::UnregisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::UnregisterGCMCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGCMRegisteredID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::UnregisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
		// Cmd: Invite friend
		Result NetPolicyGame::InviteFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::InviteFriendCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InFriendID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::InviteFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
		// Cmd: Accept friend request
		Result NetPolicyGame::AcceptFriendRequestCmd( const TransactionID &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptFriendRequestCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InInviterID, InInviterFacebookUID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::AcceptFriendRequestCmd( const TransactionID &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID )
		// Cmd: Remove friden form the friend list
		Result NetPolicyGame::RemoveFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemoveFriendCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InFriendID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::RemoveFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
		// Cmd: Get friend list
		Result NetPolicyGame::GetFriendListCmd( const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetFriendListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InStartIndex, InCount);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GetFriendListCmd( const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
		// Cmd: Query notification list
		Result NetPolicyGame::GetNotificationListCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetNotificationListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GetNotificationListCmd( const TransactionID &InTransactionID )
		// Cmd: Delete notification
		Result NetPolicyGame::DeleteNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::DeleteNotificationCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNotificationID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::DeleteNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
		// Cmd: Set notification is read
		Result NetPolicyGame::SetNotificationReadCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNotificationReadCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNotificationID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::SetNotificationReadCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
		// Cmd: Accept notification
		Result NetPolicyGame::AcceptNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptNotificationCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNotificationID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::AcceptNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
		// Cmd: Query playerID list
		Result NetPolicyGame::FindPlayerByEMailCmd( const TransactionID &InTransactionID, const char* InPlayerEMail )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByEMailCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerEMail);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::FindPlayerByEMailCmd( const TransactionID &InTransactionID, const char* InPlayerEMail )
		// Cmd: Query playerID list
		Result NetPolicyGame::FindPlayerByPlayerIDCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByPlayerIDCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::FindPlayerByPlayerIDCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
		// Cmd: *Request Player Status Update
		Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestPlayerStatusUpdateCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTargetPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::RequestPlayerStatusUpdateCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		// Cmd: Get Ranking lise
		Result NetPolicyGame::GetRankingListCmd( const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetRankingListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InRankingType, InBaseRanking, InCount);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GetRankingListCmd( const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
		// Cmd: Game user game play information
		Result NetPolicyGame::GetUserGamePlayerInfoCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetUserGamePlayerInfoCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GetUserGamePlayerInfoCmd( const TransactionID &InTransactionID )
		// Cmd: Game game play information
		Result NetPolicyGame::GetGamePlayerInfoCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetGamePlayerInfoCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GetGamePlayerInfoCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
		// Cmd: Change NickName
		Result NetPolicyGame::SetNickNameCmd( const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNickNameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNickName, InIsCostFree);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::SetNickNameCmd( const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
		// Cmd: Create Party
		Result NetPolicyGame::CreatePartyCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreatePartyCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::CreatePartyCmd( const TransactionID &InTransactionID )
		// Cmd: Join party
		Result NetPolicyGame::JoinPartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinPartyCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPartyUID, InInviterID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::JoinPartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
		// Cmd: Leave party command
		Result NetPolicyGame::LeavePartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeavePartyCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPartyUID, InPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::LeavePartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
		// Cmd: Kick player from the party
		Result NetPolicyGame::PartyKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyKickPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPartyUID, InPlayerID, InPlayerToKick);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::PartyKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		// Cmd: Invite a player to the party
		Result NetPolicyGame::PartyInviteCmd( const TransactionID &InTransactionID, const AccountID &InInviteTargetID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyInviteCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InInviteTargetID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::PartyInviteCmd( const TransactionID &InTransactionID, const AccountID &InInviteTargetID )
		// Cmd: Send Party quick chat message
		Result NetPolicyGame::PartyQuickChatMessageCmd( const TransactionID &InTransactionID, const uint32_t &InQuickChatID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyQuickChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InQuickChatID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::PartyQuickChatMessageCmd( const TransactionID &InTransactionID, const uint32_t &InQuickChatID )
		// Cmd: Party chatting
		Result NetPolicyGame::PartyChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatMessage);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::PartyChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage )
		// Cmd: Join to a game
		Result NetPolicyGame::JoinGameCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPlayerID, InTicket, InInsUID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::JoinGameCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID )
		// Cmd: Leave Game
		Result NetPolicyGame::LeaveGameCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveGameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::LeaveGameCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Kick player
		Result NetPolicyGame::KickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::KickPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InPlayerToKick);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::KickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		// Cmd: Assign role + Game state reset
		Result NetPolicyGame::AssignRoleCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AssignRoleCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::AssignRoleCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Send chatting message to the game
		Result NetPolicyGame::ChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage, const uint8_t &InRole )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatMessage, InRole);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::ChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage, const uint8_t &InRole )
		// Cmd: Advance game
		Result NetPolicyGame::AdvanceGameCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AdvanceGameCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::AdvanceGameCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Vote game advance
		Result NetPolicyGame::VoteGameAdvanceCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteGameAdvanceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::VoteGameAdvanceCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket )
		// Cmd: Vote
		Result NetPolicyGame::VoteCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameInsUID, InPlayerID, InTicket, InVoteTarget, InActionSerial);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::VoteCmd( const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial )
		// Cmd: Play again with the current players
		Result NetPolicyGame::GamePlayAgainCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayAgainCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GamePlayAgainCmd( const TransactionID &InTransactionID )
		// Cmd: Player. reveal a player
		Result NetPolicyGame::GameRevealPlayerCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameRevealPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTargetPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GameRevealPlayerCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID )
		// Cmd: Player. revive himself
		Result NetPolicyGame::GamePlayerReviveCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerReviveCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GamePlayerReviveCmd( const TransactionID &InTransactionID )
		// Cmd: Player. reset ranking
		Result NetPolicyGame::GamePlayerResetRankCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerResetRankCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GamePlayerResetRankCmd( const TransactionID &InTransactionID )
		// Cmd: Request Game match
		Result NetPolicyGame::RequestGameMatchCmd( const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestGameMatchCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InNumPlayer, InRequestRole);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::RequestGameMatchCmd( const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
		// Cmd: Cancel Game match
		Result NetPolicyGame::CancelGameMatchCmd( const TransactionID &InTransactionID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::CancelGameMatchCmd::Create(m_pConnection->GetIOHeap(), InTransactionID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::CancelGameMatchCmd( const TransactionID &InTransactionID )
		// Cmd: Buy shop item prepare
		Result NetPolicyGame::BuyShopItemPrepareCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemPrepareCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InShopItemID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::BuyShopItemPrepareCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID )
		// Cmd: Buy shop item
		Result NetPolicyGame::BuyShopItemCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InShopItemID, InPlatform, InPackageName, InPurchaseTransactionID, InPurchaseToken);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::BuyShopItemCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
		// Cmd: Create or Join Chat channel
		Result NetPolicyGame::CreateOrJoinChatChannelCmd( const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreateOrJoinChatChannelCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChannelName, InPasscode);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::CreateOrJoinChatChannelCmd( const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode )
		// Cmd: Join
		Result NetPolicyGame::JoinChatChannelCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinChatChannelCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InInviterID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::JoinChatChannelCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID )
		// Cmd: Leave ChatChannel command
		Result NetPolicyGame::LeaveChatChannelCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveChatChannelCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::LeaveChatChannelCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID )
		// Cmd: Kick player from the ChatChannel
		Result NetPolicyGame::ChatChannelKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelKickPlayerCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InPlayerID, InPlayerToKick);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::ChatChannelKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
		// Cmd: Party chatting
		Result NetPolicyGame::ChatChannelChatMessageCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelChatMessageCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InChatUID, InChatMessage);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::ChatChannelChatMessageCmd( const TransactionID &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage )
		// Cmd: Give my stamina to other player
		Result NetPolicyGame::GiveStaminaCmd( const TransactionID &InTransactionID, const AccountID &InTargetPlayer )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GiveStaminaCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTargetPlayer);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GiveStaminaCmd( const TransactionID &InTransactionID, const AccountID &InTargetPlayer )
		// Cmd: For debug, Change configue preset
		Result NetPolicyGame::SetPresetGameConfigIDCmd( const TransactionID &InTransactionID, const uint32_t &InPresetID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetPresetGameConfigIDCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InPresetID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::SetPresetGameConfigIDCmd( const TransactionID &InTransactionID, const uint32_t &InPresetID )
		// Cmd: For Debug
		Result NetPolicyGame::GainGameResourceCmd( const TransactionID &InTransactionID, const int32_t &InResource, const int32_t &InValue )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GainGameResourceCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InResource, InValue);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetPolicyGame::GainGameResourceCmd( const TransactionID &InTransactionID, const int32_t &InResource, const int32_t &InValue )


		// Cmd: Player connected from a login server and moved to game server
		Result NetSvrPolicyGame::JoinGameServerRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameServerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNickName, InGameUID, InPartyUID, InPartyLeaderID, InMatchingTicket);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::JoinGameServerRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
		// Cmd: player complition statues
		Result NetSvrPolicyGame::GetComplitionStateRes( const TransactionID &InTransactionID, const Result &InResult, const char* InComplitionState )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetComplitionStateRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InComplitionState);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GetComplitionStateRes( const TransactionID &InTransactionID, const Result &InResult, const char* InComplitionState )
		// Cmd: Player complition state
		Result NetSvrPolicyGame::SetComplitionStateRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetComplitionStateRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::SetComplitionStateRes( const TransactionID &InTransactionID, const Result &InResult )
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result NetSvrPolicyGame::RegisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RegisterGCMRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::RegisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
		// Cmd: Unregister Google notification service ID
		Result NetSvrPolicyGame::UnregisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::UnregisterGCMRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::UnregisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
		// Cmd: Invite friend
		Result NetSvrPolicyGame::InviteFriendRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::InviteFriendRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::InviteFriendRes( const TransactionID &InTransactionID, const Result &InResult )
		// Cmd: Accept friend request
		Result NetSvrPolicyGame::AcceptFriendRequestRes( const TransactionID &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptFriendRequestRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNewFriend);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::AcceptFriendRequestRes( const TransactionID &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend )
		// S2C: Notification for friend request is accepted
		Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::FriendRequestAcceptedS2CEvt::Create(m_pConnection->GetIOHeap(), InAccepter);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter )
		// Cmd: Remove friden form the friend list
		Result NetSvrPolicyGame::RemoveFriendRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RemoveFriendRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InFriendID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::RemoveFriendRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID )
		// S2C: Friend removed
		Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::FriendRemovedS2CEvt::Create(m_pConnection->GetIOHeap(), InFriendID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::FriendRemovedS2CEvt( const AccountID &InFriendID )
		// Cmd: Get friend list
		Result NetSvrPolicyGame::GetFriendListRes( const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetFriendListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InMaxFriendSlot, InTotalNumberOfFriends, InStartIndex, InFriendList);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GetFriendListRes( const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList )
		// Cmd: Query notification list
		Result NetSvrPolicyGame::GetNotificationListRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetNotificationListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GetNotificationListRes( const TransactionID &InTransactionID, const Result &InResult )
		// Cmd: Delete notification
		Result NetSvrPolicyGame::DeleteNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::DeleteNotificationRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNotificationID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::DeleteNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		// Cmd: Set notification is read
		Result NetSvrPolicyGame::SetNotificationReadRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNotificationReadRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNotificationID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::SetNotificationReadRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		// Cmd: Accept notification
		Result NetSvrPolicyGame::AcceptNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AcceptNotificationRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InNotificationID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::AcceptNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
		// S2C: Notify new notification
		Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::NotifyS2CEvt::Create(m_pConnection->GetIOHeap(), InNotificationID, InNotificationType, InMessageParam0, InMessageParam1, InMessageText, InIsRead, InTimeStamp);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
		// Cmd: Query playerID list
		Result NetSvrPolicyGame::FindPlayerByEMailRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByEMailRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayer);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::FindPlayerByEMailRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		// Cmd: Query playerID list
		Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::FindPlayerByPlayerIDRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayer);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::FindPlayerByPlayerIDRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
		// Cmd: *Request Player Status Update
		Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestPlayerStatusUpdateRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::RequestPlayerStatusUpdateRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: *Notify Player Status Updated
		Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::NotifyPlayerStatusUpdatedS2CEvt::Create(m_pConnection->GetIOHeap(), InPlayerID, InLatestActiveTime, InIsInGame);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
		// Cmd: Get Ranking lise
		Result NetSvrPolicyGame::GetRankingListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetRankingListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InRanking);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GetRankingListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		// Cmd: Game user game play information
		Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const int16_t &InLevel, const int64_t &InExp, const int64_t &InGameMoney, const int64_t &InGem, const int16_t &InStamina, const uint32_t &InLastUpdateTime, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetUserGamePlayerInfoRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InLevel, InExp, InGameMoney, InGem, InStamina, InLastUpdateTime, InTotalPlayed, InWinPlaySC, InWinPlaySM, InWinPlaySS, InLosePlaySC, InLosePlaySM, InLosePlaySS, InWinPlayNC, InWinPlayNM, InWinPlayNS, InLosePlayNC, InLosePlayNM, InLosePlayNS, InWeeklyWin, InWeeklyLose);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GetUserGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const int16_t &InLevel, const int64_t &InExp, const int64_t &InGameMoney, const int64_t &InGem, const int16_t &InStamina, const uint32_t &InLastUpdateTime, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )
		// Cmd: Game game play information
		Result NetSvrPolicyGame::GetGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const int16_t &InLevel, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GetGamePlayerInfoRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPlayerID, InLevel, InTotalPlayed, InWinPlaySC, InWinPlaySM, InWinPlaySS, InLosePlaySC, InLosePlaySM, InLosePlaySS, InWinPlayNC, InWinPlayNM, InWinPlayNS, InLosePlayNC, InLosePlayNM, InLosePlayNS, InWeeklyWin, InWeeklyLose);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GetGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const int16_t &InLevel, const int32_t &InTotalPlayed, const int32_t &InWinPlaySC, const int32_t &InWinPlaySM, const int32_t &InWinPlaySS, const int32_t &InLosePlaySC, const int32_t &InLosePlaySM, const int32_t &InLosePlaySS, const int32_t &InWinPlayNC, const int32_t &InWinPlayNM, const int32_t &InWinPlayNS, const int32_t &InLosePlayNC, const int32_t &InLosePlayNM, const int32_t &InLosePlayNS, const int32_t &InWeeklyWin, const int32_t &InWeeklyLose )
		// S2C: Player level up event
		Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LevelUpS2CEvt::Create(m_pConnection->GetIOHeap(), InCurrentTotalExp, InCurrentLevel);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
		// Cmd: Change NickName
		Result NetSvrPolicyGame::SetNickNameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetNickNameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::SetNickNameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// Cmd: Create Party
		Result NetSvrPolicyGame::CreatePartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreatePartyRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPartyUID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::CreatePartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
		// Cmd: Join party
		Result NetSvrPolicyGame::JoinPartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinPartyRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID, InChatHistoryData);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::JoinPartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
		// S2C: Player Joined event
		Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyPlayerJoinedS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InJoinedPlayer);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
		// S2C: Party leader changed event
		Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyLeaderChangedS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InNewLeaderID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
		// Cmd: Leave party command
		Result NetSvrPolicyGame::LeavePartyRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeavePartyRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::LeavePartyRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Party Player left event
		Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyPlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InLeftPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
		// Cmd: Kick player from the party
		Result NetSvrPolicyGame::PartyKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyKickPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Party Player kicked message
		Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyPlayerKickedS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InKickedPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
		// Cmd: Invite a player to the party
		Result NetSvrPolicyGame::PartyInviteRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyInviteRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyInviteRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Party invite requested
		Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyInviteRequestedS2CEvt::Create(m_pConnection->GetIOHeap(), InInviterID, InInviterName, InPartyToJoinUID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
		// Cmd: Send Party quick chat message
		Result NetSvrPolicyGame::PartyQuickChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyQuickChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyQuickChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Party Chatting message event
		Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyQuickChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InQuickChatID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
		// Cmd: Party chatting
		Result NetSvrPolicyGame::PartyChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Party Chatting message event
		Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PartyChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InSenderName, InChatMessage);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		// Cmd: Join to a game
		Result NetSvrPolicyGame::JoinGameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinGameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::JoinGameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData )
		// S2C: Player Joined in the game
		Result NetSvrPolicyGame::PlayerJoinedS2CEvt( const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer, const uint8_t &InJoinedPlayerRole, const uint8_t &InJoinedPlayerDead, const uint8_t &InJoinedPlayerIndex, const uint8_t &InJoinedPlayerCharacter )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerJoinedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InJoinedPlayer, InJoinedPlayerRole, InJoinedPlayerDead, InJoinedPlayerIndex, InJoinedPlayerCharacter);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PlayerJoinedS2CEvt( const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer, const uint8_t &InJoinedPlayerRole, const uint8_t &InJoinedPlayerDead, const uint8_t &InJoinedPlayerIndex, const uint8_t &InJoinedPlayerCharacter )
		// Cmd: Leave Game
		Result NetSvrPolicyGame::LeaveGameRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveGameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::LeaveGameRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Player left event
		Result NetSvrPolicyGame::PlayerLeftS2CEvt( const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InLeftPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PlayerLeftS2CEvt( const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID )
		// Cmd: Kick player
		Result NetSvrPolicyGame::KickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::KickPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::KickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Player kicked
		Result NetSvrPolicyGame::PlayerKickedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerKickedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InKickedPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PlayerKickedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID )
		// Cmd: Assign role + Game state reset
		Result NetSvrPolicyGame::AssignRoleRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AssignRoleRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::AssignRoleRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Role assigned event
		Result NetSvrPolicyGame::RoleAssignedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RoleAssignedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InPlayerID, InRole);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::RoleAssignedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole )
		// Cmd: Send chatting message to the game
		Result NetSvrPolicyGame::ChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Chatting message event 
		Result NetSvrPolicyGame::ChatMessageS2CEvt( const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InRole, InSenderName, InChatMessage);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatMessageS2CEvt( const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage )
		// Cmd: Advance game
		Result NetSvrPolicyGame::AdvanceGameRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::AdvanceGameRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::AdvanceGameRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: The game state is advanced
		Result NetSvrPolicyGame::GameAdvancedS2CEvt( const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameAdvancedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InTimeStamp, InGameState, InDay);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameAdvancedS2CEvt( const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay )
		// S2C: Game is ended
		Result NetSvrPolicyGame::GameEndedS2CEvt( const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameEndedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InWinner, InGainedExp, InGainedGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameEndedS2CEvt( const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney )
		// Cmd: Vote game advance
		Result NetSvrPolicyGame::VoteGameAdvanceRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteGameAdvanceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::VoteGameAdvanceRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: GameAdvance is Voted
		Result NetSvrPolicyGame::GameAdvanceVotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameAdvanceVotedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InVoter);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameAdvanceVotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter )
		// Cmd: Vote
		Result NetSvrPolicyGame::VoteRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::VoteRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: Player Voted
		Result NetSvrPolicyGame::VotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::VotedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InVoter, InVotedTarget);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::VotedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget )
		// S2C: Vote is ended
		Result NetSvrPolicyGame::VoteEndS2CEvt( const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::VoteEndS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InVoted);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::VoteEndS2CEvt( const uint64_t &InGameInsUID, const Array<AccountID>& InVoted )
		// S2C: Player Killed
		Result NetSvrPolicyGame::PlayerKilledS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerKilledS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InKilledPlayer, InReason);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PlayerKilledS2CEvt( const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason )
		// S2C: Player Voted
		Result NetSvrPolicyGame::PlayerRevealedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::PlayerRevealedS2CEvt::Create(m_pConnection->GetIOHeap(), InGameInsUID, InRevealedPlayerID, InRole, InReason);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::PlayerRevealedS2CEvt( const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason )
		// Cmd: Play again with the current players
		Result NetSvrPolicyGame::GamePlayAgainRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayAgainRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayAgainRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value
		Result NetSvrPolicyGame::GamePlayAgainS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeadPlayer )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayAgainS2CEvt::Create(m_pConnection->GetIOHeap(), InPartyUID, InLeadPlayer);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayAgainS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeadPlayer )
		// Cmd: Player. reveal a player
		Result NetSvrPolicyGame::GameRevealPlayerRes( const TransactionID &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameRevealPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InRevealedPlayerID, InRevealedRole, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameRevealPlayerRes( const TransactionID &InTransactionID, const Result &InResult, const Array<AccountID>& InRevealedPlayerID, const Array<uint8_t>& InRevealedRole, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// Cmd: Player. revive himself
		Result NetSvrPolicyGame::GamePlayerReviveRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerReviveRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayerReviveRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Player is revived
		Result NetSvrPolicyGame::GamePlayerRevivedS2CEvt( const AccountID &InRevivedPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerRevivedS2CEvt::Create(m_pConnection->GetIOHeap(), InRevivedPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayerRevivedS2CEvt( const AccountID &InRevivedPlayerID )
		// Cmd: Player. reset ranking
		Result NetSvrPolicyGame::GamePlayerResetRankRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GamePlayerResetRankRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GamePlayerResetRankRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// Cmd: Request Game match
		Result NetSvrPolicyGame::RequestGameMatchRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::RequestGameMatchRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::RequestGameMatchRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Game matched
		Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchedS2CEvt::Create(m_pConnection->GetIOHeap(), InInsUID, InTimeStamp, InGameState, InDay, InMaxPlayer, InPlayerIndex, InPlayerCharacter, InRole, InDead, InChatHistoryData, InGameLogData, InStamina, InTotalGem, InTotalGameMoney);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
		// S2C: Game match failed
		Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchFailedS2CEvt::Create(m_pConnection->GetIOHeap(), InFailedReason);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchFailedS2CEvt( const Result &InFailedReason )
		// S2C: Game matching started
		Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchingStartedS2CEvt::Create(m_pConnection->GetIOHeap());
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchingStartedS2CEvt(  )
		// Cmd: Cancel Game match
		Result NetSvrPolicyGame::CancelGameMatchRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::CancelGameMatchRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::CancelGameMatchRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: game matching canceled
		Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GameMatchingCanceledS2CEvt::Create(m_pConnection->GetIOHeap());
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GameMatchingCanceledS2CEvt(  )
		// Cmd: Buy shop item prepare
		Result NetSvrPolicyGame::BuyShopItemPrepareRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemPrepareRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InShopItemID, InPurchaseID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::BuyShopItemPrepareRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
		// Cmd: Buy shop item
		Result NetSvrPolicyGame::BuyShopItemRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::BuyShopItemRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InShopItemID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::BuyShopItemRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
		// Cmd: Create or Join Chat channel
		Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InChatUID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::CreateOrJoinChatChannelRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InChatUID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::CreateOrJoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InChatUID )
		// Cmd: Join
		Result NetSvrPolicyGame::JoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::JoinChatChannelRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InPartyUID, InPartyLeaderID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::JoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID )
		// S2C: Player Joined event
		Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelPlayerJoinedS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InJoinedPlayer);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer )
		// S2C: ChatChannel leader changed event
		Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelLeaderChangedS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InNewLeaderID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID )
		// Cmd: Leave ChatChannel command
		Result NetSvrPolicyGame::LeaveChatChannelRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::LeaveChatChannelRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::LeaveChatChannelRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: ChatChannel Player left event
		Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelPlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InLeftPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID )
		// Cmd: Kick player from the ChatChannel
		Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelKickPlayerRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: ChatChannel Player kicked message
		Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelPlayerKickedS2CEvt::Create(m_pConnection->GetIOHeap(), InChatUID, InKickedPlayerID);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID )
		// Cmd: Party chatting
		Result NetSvrPolicyGame::ChatChannelChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelChatMessageRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
		// S2C: ChatChannel Chatting message event
		Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::ChatChannelChatMessageS2CEvt::Create(m_pConnection->GetIOHeap(), InSenderID, InSenderName, InChatMessage);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::ChatChannelChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
		// Cmd: Give my stamina to other player
		Result NetSvrPolicyGame::GiveStaminaRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GiveStaminaRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTargetPlayer, InTimeStamp);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GiveStaminaRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InTargetPlayer, const uint64_t &InTimeStamp )
		// Cmd: For debug, Change configue preset
		Result NetSvrPolicyGame::SetPresetGameConfigIDRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::SetPresetGameConfigIDRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::SetPresetGameConfigIDRes( const TransactionID &InTransactionID, const Result &InResult )
		// Cmd: For Debug
		Result NetSvrPolicyGame::GainGameResourceRes( const TransactionID &InTransactionID, const Result &InResult )
		{
 			Result hr;

			 MessageDataPtr pMessage;
			 protocolChkPtr(m_pConnection);

			 pMessage = SF::Message::Game::GainGameResourceRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolChkPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

		Proc_End:

			return hr;

		}; // Result NetSvrPolicyGame::GainGameResourceRes( const TransactionID &InTransactionID, const Result &InResult )


	}; // namespace Policy
}; // namespace SF


