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
#include "Protocol/GameRPCSendAdapter.h"
#include "Protocol/GameMessageID.h"
#include "Game_generated.h"



namespace SF
{
 	// C2S: Client heartbeat
	Result GameRPCSendAdapter::HeartbeatC2SEvt(  )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::HeartbeatC2SEvtBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::HeartbeatC2SEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_HeartbeatC2SEvt, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::HeartbeatC2SEvt(  )
	// Cmd: Player connected from a login server and moved to game server
	Result GameRPCSendAdapter::JoinGameServerCmd( const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto AccIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InAccID);
		SF::Flat::Game::JoinGameServerCmdBuilder _builder(fbb);
		_builder.add_acc_id(AccIDOffset);
		_builder.add_ticket(InTicket);
		_builder.add_login_entity_uid(InLoginEntityUID);
		flatbuffers::Offset<SF::Flat::Game::JoinGameServerCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinGameServerCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::JoinGameServerCmd( const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	// Cmd: player completion statues
	Result GameRPCSendAdapter::GetAchievementStatsCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		SF::Flat::Game::GetAchievementStatsCmdBuilder _builder(fbb);
		_builder.add_character_id(CharacterIDOffset);
		_builder.add_achievement_stat_idfrom(InAchievementStatIDFrom);
		_builder.add_achievement_stat_idto(InAchievementStatIDTo);
		flatbuffers::Offset<SF::Flat::Game::GetAchievementStatsCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetAchievementStatsCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetAchievementStatsCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo )
	// Cmd: Player complition state
	Result GameRPCSendAdapter::Dummy1Cmd( const TransactionID &InTransactionID, const char* InComplitionState )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ComplitionStateOffset = SF::Flat::Helper::CreateString(fbb, InComplitionState);
		SF::Flat::Game::Dummy1CmdBuilder _builder(fbb);
		_builder.add_complition_state(ComplitionStateOffset);
		flatbuffers::Offset<SF::Flat::Game::Dummy1Cmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_Dummy1Cmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::Dummy1Cmd( const TransactionID &InTransactionID, const char* InComplitionState )
	// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
	Result GameRPCSendAdapter::RegisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto GCMRegisteredIDOffset = SF::Flat::Helper::CreateString(fbb, InGCMRegisteredID);
		SF::Flat::Game::RegisterGCMCmdBuilder _builder(fbb);
		_builder.add_gcmregistered_id(GCMRegisteredIDOffset);
		flatbuffers::Offset<SF::Flat::Game::RegisterGCMCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RegisterGCMCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::RegisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
	// Cmd: Unregister Google notification service ID
	Result GameRPCSendAdapter::UnregisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto GCMRegisteredIDOffset = SF::Flat::Helper::CreateString(fbb, InGCMRegisteredID);
		SF::Flat::Game::UnregisterGCMCmdBuilder _builder(fbb);
		_builder.add_gcmregistered_id(GCMRegisteredIDOffset);
		flatbuffers::Offset<SF::Flat::Game::UnregisterGCMCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_UnregisterGCMCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::UnregisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID )
	// Cmd: Invite friend
	Result GameRPCSendAdapter::InviteFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto FriendIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InFriendID);
		SF::Flat::Game::InviteFriendCmdBuilder _builder(fbb);
		_builder.add_friend_id(FriendIDOffset);
		flatbuffers::Offset<SF::Flat::Game::InviteFriendCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_InviteFriendCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::InviteFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
	// Cmd: Accept friend request
	Result GameRPCSendAdapter::AcceptFriendRequestCmd( const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InviterIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InInviterID);
		auto InviterPlatformIdOffset = SF::Flat::Helper::CreatePlayerPlatformID(fbb, InInviterPlatformId);
		SF::Flat::Game::AcceptFriendRequestCmdBuilder _builder(fbb);
		_builder.add_inviter_id(InviterIDOffset);
		_builder.add_inviter_platform_id(InviterPlatformIdOffset);
		flatbuffers::Offset<SF::Flat::Game::AcceptFriendRequestCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_AcceptFriendRequestCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::AcceptFriendRequestCmd( const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId )
	// Cmd: Remove friden form the friend list
	Result GameRPCSendAdapter::RemoveFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto FriendIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InFriendID);
		SF::Flat::Game::RemoveFriendCmdBuilder _builder(fbb);
		_builder.add_friend_id(FriendIDOffset);
		flatbuffers::Offset<SF::Flat::Game::RemoveFriendCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RemoveFriendCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::RemoveFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID )
	// Cmd: Get friend list
	Result GameRPCSendAdapter::GetFriendListCmd( const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetFriendListCmdBuilder _builder(fbb);
		_builder.add_start_index(InStartIndex);
		_builder.add_count(InCount);
		flatbuffers::Offset<SF::Flat::Game::GetFriendListCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetFriendListCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetFriendListCmd( const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount )
	// Cmd: Query notification list
	Result GameRPCSendAdapter::GetNotificationListCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetNotificationListCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::GetNotificationListCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetNotificationListCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetNotificationListCmd( const TransactionID &InTransactionID )
	// Cmd: Delete notification
	Result GameRPCSendAdapter::DeleteNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::DeleteNotificationCmdBuilder _builder(fbb);
		_builder.add_notification_id(InNotificationID);
		flatbuffers::Offset<SF::Flat::Game::DeleteNotificationCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_DeleteNotificationCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::DeleteNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: Set notification is read
	Result GameRPCSendAdapter::SetNotificationReadCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::SetNotificationReadCmdBuilder _builder(fbb);
		_builder.add_notification_id(InNotificationID);
		flatbuffers::Offset<SF::Flat::Game::SetNotificationReadCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SetNotificationReadCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::SetNotificationReadCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: Accept notification
	Result GameRPCSendAdapter::AcceptNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::AcceptNotificationCmdBuilder _builder(fbb);
		_builder.add_notification_id(InNotificationID);
		flatbuffers::Offset<SF::Flat::Game::AcceptNotificationCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_AcceptNotificationCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::AcceptNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID )
	// Cmd: PlayerId Conversion
	Result GameRPCSendAdapter::FindPlayerByPlatformIdCmd( const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlatformPlayerIdOffset = SF::Flat::Helper::CreatePlayerPlatformID(fbb, InPlatformPlayerId);
		SF::Flat::Game::FindPlayerByPlatformIdCmdBuilder _builder(fbb);
		_builder.add_platform_player_id(PlatformPlayerIdOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByPlatformIdCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByPlatformIdCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::FindPlayerByPlatformIdCmd( const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId )
	// Cmd: PlayerId conversion
	Result GameRPCSendAdapter::FindPlayerByCharacterNameCmd( const TransactionID &InTransactionID, const char* InCharacterName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterNameOffset = SF::Flat::Helper::CreateString(fbb, InCharacterName);
		SF::Flat::Game::FindPlayerByCharacterNameCmdBuilder _builder(fbb);
		_builder.add_character_name(CharacterNameOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByCharacterNameCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByCharacterNameCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::FindPlayerByCharacterNameCmd( const TransactionID &InTransactionID, const char* InCharacterName )
	// Cmd: PlayerId Conversion
	Result GameRPCSendAdapter::FindPlayerByPlatformUserNameCmd( const TransactionID &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlatformUserNameOffset = SF::Flat::Helper::CreateString(fbb, InPlatformUserName);
		SF::Flat::Game::FindPlayerByPlatformUserNameCmdBuilder _builder(fbb);
		_builder.add_platform_type(InPlatformType);
		_builder.add_platform_user_name(PlatformUserNameOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByPlatformUserNameCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByPlatformUserNameCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::FindPlayerByPlatformUserNameCmd( const TransactionID &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName )
	// Cmd: Query playerID list
	Result GameRPCSendAdapter::FindPlayerByEMailCmd( const TransactionID &InTransactionID, const char* InPlayerEMail )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerEMailOffset = SF::Flat::Helper::CreateString(fbb, InPlayerEMail);
		SF::Flat::Game::FindPlayerByEMailCmdBuilder _builder(fbb);
		_builder.add_player_email(PlayerEMailOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByEMailCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByEMailCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::FindPlayerByEMailCmd( const TransactionID &InTransactionID, const char* InPlayerEMail )
	// Cmd: Query playerID list
	Result GameRPCSendAdapter::FindPlayerByPlayerIDCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		SF::Flat::Game::FindPlayerByPlayerIDCmdBuilder _builder(fbb);
		_builder.add_player_id(PlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByPlayerIDCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByPlayerIDCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::FindPlayerByPlayerIDCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
	// Cmd: *Request Player Status Update
	Result GameRPCSendAdapter::RequestPlayerStatusUpdateCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto TargetPlayerIDOffset = SF::Flat::Helper::CreateAccountIDVector(fbb, InTargetPlayerID);
		SF::Flat::Game::RequestPlayerStatusUpdateCmdBuilder _builder(fbb);
		_builder.add_target_player_id(TargetPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::RequestPlayerStatusUpdateCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestPlayerStatusUpdateCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::RequestPlayerStatusUpdateCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID )
	// Cmd: Get Ranking list
	Result GameRPCSendAdapter::GetRankingListCmd( const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetRankingListCmdBuilder _builder(fbb);
		_builder.add_ranking_type(InRankingType);
		_builder.add_base_ranking(InBaseRanking);
		_builder.add_count(InCount);
		flatbuffers::Offset<SF::Flat::Game::GetRankingListCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetRankingListCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetRankingListCmd( const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	// Cmd: Game user game play information
	Result GameRPCSendAdapter::GetUserGamePlayerInfoCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetUserGamePlayerInfoCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::GetUserGamePlayerInfoCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetUserGamePlayerInfoCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetUserGamePlayerInfoCmd( const TransactionID &InTransactionID )
	// Cmd: Game game play information
	Result GameRPCSendAdapter::GetGamePlayerInfoCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		SF::Flat::Game::GetGamePlayerInfoCmdBuilder _builder(fbb);
		_builder.add_player_id(PlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::GetGamePlayerInfoCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetGamePlayerInfoCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetGamePlayerInfoCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID )
	// Cmd: Change NickName
	Result GameRPCSendAdapter::SetNickNameCmd( const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto NickNameOffset = SF::Flat::Helper::CreateString(fbb, InNickName);
		SF::Flat::Game::SetNickNameCmdBuilder _builder(fbb);
		_builder.add_nick_name(NickNameOffset);
		_builder.add_is_cost_free(InIsCostFree);
		flatbuffers::Offset<SF::Flat::Game::SetNickNameCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SetNickNameCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::SetNickNameCmd( const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree )
	// Cmd: Create Party
	Result GameRPCSendAdapter::CreatePartyCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::CreatePartyCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::CreatePartyCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CreatePartyCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::CreatePartyCmd( const TransactionID &InTransactionID )
	// Cmd: Join party
	Result GameRPCSendAdapter::JoinPartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InviterIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InInviterID);
		SF::Flat::Game::JoinPartyCmdBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_inviter_id(InviterIDOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinPartyCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinPartyCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::JoinPartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID )
	// Cmd: Leave party command
	Result GameRPCSendAdapter::LeavePartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		SF::Flat::Game::LeavePartyCmdBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_player_id(PlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::LeavePartyCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_LeavePartyCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::LeavePartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID )
	// Cmd: Kick player from the party
	Result GameRPCSendAdapter::PartyKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		auto PlayerToKickOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerToKick);
		SF::Flat::Game::PartyKickPlayerCmdBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_player_to_kick(PlayerToKickOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyKickPlayerCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyKickPlayerCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::PartyKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	// Cmd: Invite a player to the party
	Result GameRPCSendAdapter::PartyInviteCmd( const TransactionID &InTransactionID, const AccountID &InInviteTargetID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InviteTargetIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InInviteTargetID);
		SF::Flat::Game::PartyInviteCmdBuilder _builder(fbb);
		_builder.add_invite_target_id(InviteTargetIDOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyInviteCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyInviteCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::PartyInviteCmd( const TransactionID &InTransactionID, const AccountID &InInviteTargetID )
	// Cmd: Send Party quick chat message
	Result GameRPCSendAdapter::PartyQuickChatMessageCmd( const TransactionID &InTransactionID, const uint32_t &InQuickChatID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::PartyQuickChatMessageCmdBuilder _builder(fbb);
		_builder.add_quick_chat_id(InQuickChatID);
		flatbuffers::Offset<SF::Flat::Game::PartyQuickChatMessageCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyQuickChatMessageCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::PartyQuickChatMessageCmd( const TransactionID &InTransactionID, const uint32_t &InQuickChatID )
	// Cmd: Party chatting
	Result GameRPCSendAdapter::PartyChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::Game::PartyChatMessageCmdBuilder _builder(fbb);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyChatMessageCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyChatMessageCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::PartyChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage )
	// Cmd: Join to a game instance
	Result GameRPCSendAdapter::JoinGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InInsUID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InsUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InInsUID);
		SF::Flat::Game::JoinGameInstanceCmdBuilder _builder(fbb);
		_builder.add_ins_uid(InsUIDOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinGameInstanceCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinGameInstanceCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::JoinGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InInsUID )
	// Cmd: Leave game instance
	Result GameRPCSendAdapter::LeaveGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InInsUID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InsUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InInsUID);
		SF::Flat::Game::LeaveGameInstanceCmdBuilder _builder(fbb);
		_builder.add_ins_uid(InsUIDOffset);
		flatbuffers::Offset<SF::Flat::Game::LeaveGameInstanceCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_LeaveGameInstanceCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::LeaveGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InInsUID )
	// Cmd: Search game instance
	Result GameRPCSendAdapter::SearchGameInstanceCmd( const TransactionID &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto SearchKeywordOffset = SF::Flat::Helper::CreateString(fbb, InSearchKeyword);
		SF::Flat::Game::SearchGameInstanceCmdBuilder _builder(fbb);
		_builder.add_search_keyword(SearchKeywordOffset);
		_builder.add_zone_table_id(InZoneTableID);
		flatbuffers::Offset<SF::Flat::Game::SearchGameInstanceCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SearchGameInstanceCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::SearchGameInstanceCmd( const TransactionID &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID )
	// Cmd: Search game instance
	Result GameRPCSendAdapter::GetCharacterDataInGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InGameInstanceUID, const PlayerID &InPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto GameInstanceUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InGameInstanceUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		SF::Flat::Game::GetCharacterDataInGameInstanceCmdBuilder _builder(fbb);
		_builder.add_game_instance_uid(GameInstanceUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::GetCharacterDataInGameInstanceCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetCharacterDataInGameInstanceCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetCharacterDataInGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InGameInstanceUID, const PlayerID &InPlayerID )
	// Cmd: Request Game match
	Result GameRPCSendAdapter::RequestGameMatchCmd( const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RequestGameMatchCmdBuilder _builder(fbb);
		_builder.add_num_player(InNumPlayer);
		_builder.add_request_role(InRequestRole);
		flatbuffers::Offset<SF::Flat::Game::RequestGameMatchCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestGameMatchCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::RequestGameMatchCmd( const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole )
	// Cmd: Cancel Game match
	Result GameRPCSendAdapter::CancelGameMatchCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::CancelGameMatchCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::CancelGameMatchCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CancelGameMatchCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::CancelGameMatchCmd( const TransactionID &InTransactionID )
	// Cmd: Request UGC template list
	Result GameRPCSendAdapter::GetUGCTemplatesCmd( const TransactionID &InTransactionID, const Array<const char*>& InTags )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto TagsOffset = SF::Flat::Helper::CreateStringVector(fbb, InTags);
		SF::Flat::Game::GetUGCTemplatesCmdBuilder _builder(fbb);
		_builder.add_tags(TagsOffset);
		flatbuffers::Offset<SF::Flat::Game::GetUGCTemplatesCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetUGCTemplatesCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetUGCTemplatesCmd( const TransactionID &InTransactionID, const Array<const char*>& InTags )
	// Cmd: Save UGC content data
	Result GameRPCSendAdapter::SaveUGCCmd( const TransactionID &InTransactionID, const VariableTable &InUGCMetaData, const VariableTable &InUGCContents )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto UGCMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InUGCMetaData);
		auto UGCContentsOffset = SF::Flat::Helper::CreateVariableTable(fbb, InUGCContents);
		SF::Flat::Game::SaveUGCCmdBuilder _builder(fbb);
		_builder.add_ugcmeta_data(UGCMetaDataOffset);
		_builder.add_ugccontents(UGCContentsOffset);
		flatbuffers::Offset<SF::Flat::Game::SaveUGCCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SaveUGCCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::SaveUGCCmd( const TransactionID &InTransactionID, const VariableTable &InUGCMetaData, const VariableTable &InUGCContents )
	// Cmd: Request WhiteboardSharing
	Result GameRPCSendAdapter::SearchUGCCmd( const TransactionID &InTransactionID, const Array<const char*>& InTags )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto TagsOffset = SF::Flat::Helper::CreateStringVector(fbb, InTags);
		SF::Flat::Game::SearchUGCCmdBuilder _builder(fbb);
		_builder.add_tags(TagsOffset);
		flatbuffers::Offset<SF::Flat::Game::SearchUGCCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SearchUGCCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::SearchUGCCmd( const TransactionID &InTransactionID, const Array<const char*>& InTags )
	// Cmd: Get UGC content info, name, thumb image and so on
	Result GameRPCSendAdapter::GetUGCContentInfoCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetUGCContentInfoCmdBuilder _builder(fbb);
		_builder.add_ugcid(InUGCID);
		flatbuffers::Offset<SF::Flat::Game::GetUGCContentInfoCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetUGCContentInfoCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetUGCContentInfoCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID )
	// Cmd: Request WhiteboardSharing
	Result GameRPCSendAdapter::DownloadUGCContentCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::DownloadUGCContentCmdBuilder _builder(fbb);
		_builder.add_ugcid(InUGCID);
		_builder.add_is_include_meta_data(InIsIncludeMetaData);
		flatbuffers::Offset<SF::Flat::Game::DownloadUGCContentCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_DownloadUGCContentCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::DownloadUGCContentCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData )
	// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
	Result GameRPCSendAdapter::RequestUGCZoneInstanceCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RequestUGCZoneInstanceCmdBuilder _builder(fbb);
		_builder.add_ugcid(InUGCID);
		flatbuffers::Offset<SF::Flat::Game::RequestUGCZoneInstanceCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestUGCZoneInstanceCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::RequestUGCZoneInstanceCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID )
	// Cmd: Buy shop item prepare
	Result GameRPCSendAdapter::BuyShopItemPrepareCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::BuyShopItemPrepareCmdBuilder _builder(fbb);
		_builder.add_shop_item_id(InShopItemID);
		flatbuffers::Offset<SF::Flat::Game::BuyShopItemPrepareCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_BuyShopItemPrepareCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::BuyShopItemPrepareCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID )
	// Cmd: Buy shop item
	Result GameRPCSendAdapter::BuyShopItemCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlatformOffset = SF::Flat::Helper::CreateString(fbb, InPlatform);
		auto PackageNameOffset = SF::Flat::Helper::CreateString(fbb, InPackageName);
		auto PurchaseTransactionIDOffset = SF::Flat::Helper::CreateString(fbb, InPurchaseTransactionID);
		auto PurchaseTokenOffset = SF::Flat::Helper::Createuint8Vector(fbb, InPurchaseToken);
		SF::Flat::Game::BuyShopItemCmdBuilder _builder(fbb);
		_builder.add_shop_item_id(InShopItemID);
		_builder.add_platform(PlatformOffset);
		_builder.add_package_name(PackageNameOffset);
		_builder.add_purchase_transaction_id(PurchaseTransactionIDOffset);
		_builder.add_purchase_token(PurchaseTokenOffset);
		flatbuffers::Offset<SF::Flat::Game::BuyShopItemCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_BuyShopItemCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::BuyShopItemCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken )
	// Cmd: Create or Join Chat channel
	Result GameRPCSendAdapter::CreateOrJoinChatChannelCmd( const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChannelNameOffset = SF::Flat::Helper::CreateString(fbb, InChannelName);
		auto PasscodeOffset = SF::Flat::Helper::CreateString(fbb, InPasscode);
		SF::Flat::Game::CreateOrJoinChatChannelCmdBuilder _builder(fbb);
		_builder.add_channel_name(ChannelNameOffset);
		_builder.add_passcode(PasscodeOffset);
		flatbuffers::Offset<SF::Flat::Game::CreateOrJoinChatChannelCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CreateOrJoinChatChannelCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::CreateOrJoinChatChannelCmd( const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode )
	// Cmd: Join
	Result GameRPCSendAdapter::JoinChatChannelCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InInviterID, const char* InPasscode )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto InviterIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InInviterID);
		auto PasscodeOffset = SF::Flat::Helper::CreateString(fbb, InPasscode);
		SF::Flat::Game::JoinChatChannelCmdBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_inviter_id(InviterIDOffset);
		_builder.add_passcode(PasscodeOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinChatChannelCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinChatChannelCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::JoinChatChannelCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InInviterID, const char* InPasscode )
	// Cmd: Leave ChatChannel command
	Result GameRPCSendAdapter::LeaveChatChannelCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		SF::Flat::Game::LeaveChatChannelCmdBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::LeaveChatChannelCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_LeaveChatChannelCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::LeaveChatChannelCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID )
	// Cmd: Kick player from the ChatChannel
	Result GameRPCSendAdapter::ChatChannelKickPlayerCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		auto PlayerToKickOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerToKick);
		SF::Flat::Game::ChatChannelKickPlayerCmdBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_player_to_kick(PlayerToKickOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelKickPlayerCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_ChatChannelKickPlayerCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::ChatChannelKickPlayerCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick )
	// Cmd: Chat channel sending chatting message
	Result GameRPCSendAdapter::ChatChannelChatMessageCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto ChatMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InChatMetaData);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::Game::ChatChannelChatMessageCmdBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_chat_meta_data(ChatMetaDataOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelChatMessageCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_ChatChannelChatMessageCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::ChatChannelChatMessageCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Whisper(tell) other player chatting
	Result GameRPCSendAdapter::WhisperMessageCmd( const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ReceiverIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InReceiverID);
		auto ReceiverNameOffset = SF::Flat::Helper::CreateString(fbb, InReceiverName);
		auto ChatMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InChatMetaData);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::Game::WhisperMessageCmdBuilder _builder(fbb);
		_builder.add_receiver_id(ReceiverIDOffset);
		_builder.add_receiver_name(ReceiverNameOffset);
		_builder.add_chat_meta_data(ChatMetaDataOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::WhisperMessageCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_WhisperMessageCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::WhisperMessageCmd( const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create character
	Result GameRPCSendAdapter::CreateCharacterCmd( const TransactionID &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterNameOffset = SF::Flat::Helper::CreateString(fbb, InCharacterName);
		auto PublicDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InPublicData);
		auto PrivateDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InPrivateData);
		SF::Flat::Game::CreateCharacterCmdBuilder _builder(fbb);
		_builder.add_character_name(CharacterNameOffset);
		_builder.add_public_data(PublicDataOffset);
		_builder.add_private_data(PrivateDataOffset);
		flatbuffers::Offset<SF::Flat::Game::CreateCharacterCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CreateCharacterCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::CreateCharacterCmd( const TransactionID &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData )
	// Cmd: Delete character
	Result GameRPCSendAdapter::DeleteCharacterCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		SF::Flat::Game::DeleteCharacterCmdBuilder _builder(fbb);
		_builder.add_character_id(CharacterIDOffset);
		flatbuffers::Offset<SF::Flat::Game::DeleteCharacterCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_DeleteCharacterCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::DeleteCharacterCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID )
	// Cmd: Get character list
	Result GameRPCSendAdapter::GetCharacterListCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetCharacterListCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::GetCharacterListCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetCharacterListCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetCharacterListCmd( const TransactionID &InTransactionID )
	// Cmd: 
	Result GameRPCSendAdapter::GetCharacterDataCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		SF::Flat::Game::GetCharacterDataCmdBuilder _builder(fbb);
		_builder.add_character_id(CharacterIDOffset);
		flatbuffers::Offset<SF::Flat::Game::GetCharacterDataCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetCharacterDataCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::GetCharacterDataCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID )
	// Cmd: Select character
	Result GameRPCSendAdapter::SelectCharacterCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		SF::Flat::Game::SelectCharacterCmdBuilder _builder(fbb);
		_builder.add_character_id(CharacterIDOffset);
		flatbuffers::Offset<SF::Flat::Game::SelectCharacterCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SelectCharacterCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::SelectCharacterCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID )
	// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
	Result GameRPCSendAdapter::RequestServerNoticeUpdateCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RequestServerNoticeUpdateCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::RequestServerNoticeUpdateCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestServerNoticeUpdateCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::RequestServerNoticeUpdateCmd( const TransactionID &InTransactionID )
	// Cmd: To call general functionality
	Result GameRPCSendAdapter::CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ParametersOffset = SF::Flat::Helper::CreateVariableTable(fbb, InParameters);
		SF::Flat::Game::CallFunctionCmdBuilder _builder(fbb);
		_builder.add_function_name(InFunctionName);
		_builder.add_parameters(ParametersOffset);
		flatbuffers::Offset<SF::Flat::Game::CallFunctionCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CallFunctionCmd, fbb));


		return hr;
	}; // Result GameRPCSendAdapter::CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters )


	// Cmd: Player connected from a login server and moved to game server
	Result GameSvrRPCSendAdapter::JoinGameServerRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const GameInstanceUID &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto NickNameOffset = SF::Flat::Helper::CreateString(fbb, InNickName);
		auto GameUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InGameUID);
		auto PartyLeaderIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPartyLeaderID);
		auto MatchingTicketOffset = SF::Flat::Helper::CreateMatchingQueueTicket(fbb, InMatchingTicket);
		SF::Flat::Game::JoinGameServerResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_nick_name(NickNameOffset);
		_builder.add_game_uid(GameUIDOffset);
		_builder.add_party_uid(InPartyUID);
		_builder.add_party_leader_id(PartyLeaderIDOffset);
		_builder.add_matching_ticket(MatchingTicketOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinGameServerRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinGameServerRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::JoinGameServerRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const GameInstanceUID &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket )
	// Cmd: player completion statues
	Result GameSvrRPCSendAdapter::GetAchievementStatsRes( const TransactionID &InTransactionID, const Result &InResult, const Array<AchievementStat>& InAchievementStats )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto AchievementStatsOffset = SF::Flat::Helper::CreateAchievementStatVector(fbb, InAchievementStats);
		SF::Flat::Game::GetAchievementStatsResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_achievement_stats(AchievementStatsOffset);
		flatbuffers::Offset<SF::Flat::Game::GetAchievementStatsRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetAchievementStatsRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetAchievementStatsRes( const TransactionID &InTransactionID, const Result &InResult, const Array<AchievementStat>& InAchievementStats )
	// Cmd: Player complition state
	Result GameSvrRPCSendAdapter::Dummy1Res( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::Dummy1ResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::Dummy1Res> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_Dummy1Res, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::Dummy1Res( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
	Result GameSvrRPCSendAdapter::RegisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RegisterGCMResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::RegisterGCMRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RegisterGCMRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::RegisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Unregister Google notification service ID
	Result GameSvrRPCSendAdapter::UnregisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::UnregisterGCMResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::UnregisterGCMRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_UnregisterGCMRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::UnregisterGCMRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Invite friend
	Result GameSvrRPCSendAdapter::InviteFriendRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::InviteFriendResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::InviteFriendRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_InviteFriendRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::InviteFriendRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Accept friend request
	Result GameSvrRPCSendAdapter::AcceptFriendRequestRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InNewFriend )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto NewFriendOffset = SF::Flat::Helper::CreatePlayerInformation(fbb, InNewFriend);
		SF::Flat::Game::AcceptFriendRequestResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_new_friend(NewFriendOffset);
		flatbuffers::Offset<SF::Flat::Game::AcceptFriendRequestRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_AcceptFriendRequestRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::AcceptFriendRequestRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InNewFriend )
	// S2C: Notification for friend request is accepted
	Result GameSvrRPCSendAdapter::FriendRequestAcceptedS2CEvt( const PlayerInformation &InAccepter )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto AccepterOffset = SF::Flat::Helper::CreatePlayerInformation(fbb, InAccepter);
		SF::Flat::Game::FriendRequestAcceptedS2CEvtBuilder _builder(fbb);
		_builder.add_accepter(AccepterOffset);
		flatbuffers::Offset<SF::Flat::Game::FriendRequestAcceptedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_FriendRequestAcceptedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FriendRequestAcceptedS2CEvt( const PlayerInformation &InAccepter )
	// Cmd: Remove friden form the friend list
	Result GameSvrRPCSendAdapter::RemoveFriendRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto FriendIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InFriendID);
		SF::Flat::Game::RemoveFriendResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_friend_id(FriendIDOffset);
		flatbuffers::Offset<SF::Flat::Game::RemoveFriendRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RemoveFriendRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::RemoveFriendRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID )
	// S2C: Friend removed
	Result GameSvrRPCSendAdapter::FriendRemovedS2CEvt( const AccountID &InFriendID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto FriendIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InFriendID);
		SF::Flat::Game::FriendRemovedS2CEvtBuilder _builder(fbb);
		_builder.add_friend_id(FriendIDOffset);
		flatbuffers::Offset<SF::Flat::Game::FriendRemovedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_FriendRemovedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FriendRemovedS2CEvt( const AccountID &InFriendID )
	// Cmd: Get friend list
	Result GameSvrRPCSendAdapter::GetFriendListRes( const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<PlayerInformation>& InFriendList )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto FriendListOffset = SF::Flat::Helper::CreatePlayerInformationVector(fbb, InFriendList);
		SF::Flat::Game::GetFriendListResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_max_friend_slot(InMaxFriendSlot);
		_builder.add_total_number_of_friends(InTotalNumberOfFriends);
		_builder.add_start_index(InStartIndex);
		_builder.add_friend_list(FriendListOffset);
		flatbuffers::Offset<SF::Flat::Game::GetFriendListRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetFriendListRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetFriendListRes( const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<PlayerInformation>& InFriendList )
	// Cmd: Query notification list
	Result GameSvrRPCSendAdapter::GetNotificationListRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetNotificationListResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::GetNotificationListRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetNotificationListRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetNotificationListRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Delete notification
	Result GameSvrRPCSendAdapter::DeleteNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::DeleteNotificationResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_notification_id(InNotificationID);
		flatbuffers::Offset<SF::Flat::Game::DeleteNotificationRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_DeleteNotificationRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::DeleteNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// Cmd: Set notification is read
	Result GameSvrRPCSendAdapter::SetNotificationReadRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::SetNotificationReadResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_notification_id(InNotificationID);
		flatbuffers::Offset<SF::Flat::Game::SetNotificationReadRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SetNotificationReadRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::SetNotificationReadRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// Cmd: Accept notification
	Result GameSvrRPCSendAdapter::AcceptNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::AcceptNotificationResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_notification_id(InNotificationID);
		flatbuffers::Offset<SF::Flat::Game::AcceptNotificationRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_AcceptNotificationRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::AcceptNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID )
	// S2C: Notify new notification
	Result GameSvrRPCSendAdapter::NotifyS2CEvt( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ParametersOffset = SF::Flat::Helper::CreateVariableTable(fbb, InParameters);
		SF::Flat::Game::NotifyS2CEvtBuilder _builder(fbb);
		_builder.add_notification_id(InNotificationID);
		_builder.add_notification_type(InNotificationType);
		_builder.add_parameters(ParametersOffset);
		_builder.add_is_read(InIsRead);
		_builder.add_time_stamp(InTimeStamp);
		flatbuffers::Offset<SF::Flat::Game::NotifyS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_NotifyS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::NotifyS2CEvt( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp )
	// Cmd: PlayerId Conversion
	Result GameSvrRPCSendAdapter::FindPlayerByPlatformIdRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIdOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerId);
		auto PlayerPlatformIdOffset = SF::Flat::Helper::CreatePlayerPlatformID(fbb, InPlayerPlatformId);
		SF::Flat::Game::FindPlayerByPlatformIdResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player_id(PlayerIdOffset);
		_builder.add_player_platform_id(PlayerPlatformIdOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByPlatformIdRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByPlatformIdRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FindPlayerByPlatformIdRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	// Cmd: PlayerId conversion
	Result GameSvrRPCSendAdapter::FindPlayerByCharacterNameRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIdOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerId);
		SF::Flat::Game::FindPlayerByCharacterNameResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player_id(PlayerIdOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByCharacterNameRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByCharacterNameRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FindPlayerByCharacterNameRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId )
	// Cmd: PlayerId Conversion
	Result GameSvrRPCSendAdapter::FindPlayerByPlatformUserNameRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIdOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerId);
		auto PlayerPlatformIdOffset = SF::Flat::Helper::CreatePlayerPlatformID(fbb, InPlayerPlatformId);
		SF::Flat::Game::FindPlayerByPlatformUserNameResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player_id(PlayerIdOffset);
		_builder.add_player_platform_id(PlayerPlatformIdOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByPlatformUserNameRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByPlatformUserNameRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FindPlayerByPlatformUserNameRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId )
	// Cmd: Query playerID list
	Result GameSvrRPCSendAdapter::FindPlayerByEMailRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerOffset = SF::Flat::Helper::CreatePlayerInformation(fbb, InPlayer);
		SF::Flat::Game::FindPlayerByEMailResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player(PlayerOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByEMailRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByEMailRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FindPlayerByEMailRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	// Cmd: Query playerID list
	Result GameSvrRPCSendAdapter::FindPlayerByPlayerIDRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerOffset = SF::Flat::Helper::CreatePlayerInformation(fbb, InPlayer);
		SF::Flat::Game::FindPlayerByPlayerIDResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player(PlayerOffset);
		flatbuffers::Offset<SF::Flat::Game::FindPlayerByPlayerIDRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_FindPlayerByPlayerIDRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::FindPlayerByPlayerIDRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer )
	// Cmd: *Request Player Status Update
	Result GameSvrRPCSendAdapter::RequestPlayerStatusUpdateRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RequestPlayerStatusUpdateResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::RequestPlayerStatusUpdateRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestPlayerStatusUpdateRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::RequestPlayerStatusUpdateRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: *Notify Player Status Updated
	Result GameSvrRPCSendAdapter::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		SF::Flat::Game::NotifyPlayerStatusUpdatedS2CEvtBuilder _builder(fbb);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_latest_active_time(InLatestActiveTime);
		_builder.add_is_in_game(InIsInGame);
		flatbuffers::Offset<SF::Flat::Game::NotifyPlayerStatusUpdatedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_NotifyPlayerStatusUpdatedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame )
	// Cmd: Get Ranking list
	Result GameSvrRPCSendAdapter::GetRankingListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto RankingOffset = SF::Flat::Helper::CreateTotalRankingPlayerInformationVector(fbb, InRanking);
		SF::Flat::Game::GetRankingListResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_ranking(RankingOffset);
		flatbuffers::Offset<SF::Flat::Game::GetRankingListRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetRankingListRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetRankingListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: Game user game play information
	Result GameSvrRPCSendAdapter::GetUserGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto AttributesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InAttributes);
		SF::Flat::Game::GetUserGamePlayerInfoResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_attributes(AttributesOffset);
		flatbuffers::Offset<SF::Flat::Game::GetUserGamePlayerInfoRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetUserGamePlayerInfoRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetUserGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InAttributes )
	// Cmd: Game game play information
	Result GameSvrRPCSendAdapter::GetGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPlayerID);
		auto AttributesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InAttributes);
		SF::Flat::Game::GetGamePlayerInfoResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_attributes(AttributesOffset);
		flatbuffers::Offset<SF::Flat::Game::GetGamePlayerInfoRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetGamePlayerInfoRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes )
	// S2C: Player level up event
	Result GameSvrRPCSendAdapter::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::LevelUpS2CEvtBuilder _builder(fbb);
		_builder.add_current_total_exp(InCurrentTotalExp);
		_builder.add_current_level(InCurrentLevel);
		flatbuffers::Offset<SF::Flat::Game::LevelUpS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_LevelUpS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel )
	// Cmd: Change NickName
	Result GameSvrRPCSendAdapter::SetNickNameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::SetNickNameResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_total_gem(InTotalGem);
		_builder.add_total_game_money(InTotalGameMoney);
		flatbuffers::Offset<SF::Flat::Game::SetNickNameRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SetNickNameRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::SetNickNameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// Cmd: Create Party
	Result GameSvrRPCSendAdapter::CreatePartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::CreatePartyResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_party_uid(InPartyUID);
		flatbuffers::Offset<SF::Flat::Game::CreatePartyRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CreatePartyRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::CreatePartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID )
	// Cmd: Join party
	Result GameSvrRPCSendAdapter::JoinPartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PartyLeaderIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InPartyLeaderID);
		auto ChatHistoryDataOffset = SF::Flat::Helper::Createuint8Vector(fbb, InChatHistoryData);
		SF::Flat::Game::JoinPartyResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_party_uid(InPartyUID);
		_builder.add_party_leader_id(PartyLeaderIDOffset);
		_builder.add_chat_history_data(ChatHistoryDataOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinPartyRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinPartyRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::JoinPartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData )
	// S2C: Player Joined event
	Result GameSvrRPCSendAdapter::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto JoinedPlayerOffset = SF::Flat::Helper::CreatePlayerInformation(fbb, InJoinedPlayer);
		SF::Flat::Game::PartyPlayerJoinedS2CEvtBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_joined_player(JoinedPlayerOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyPlayerJoinedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyPlayerJoinedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer )
	// S2C: Party leader changed event
	Result GameSvrRPCSendAdapter::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto NewLeaderIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InNewLeaderID);
		SF::Flat::Game::PartyLeaderChangedS2CEvtBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_new_leader_id(NewLeaderIDOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyLeaderChangedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyLeaderChangedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID )
	// Cmd: Leave party command
	Result GameSvrRPCSendAdapter::LeavePartyRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::LeavePartyResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::LeavePartyRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_LeavePartyRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::LeavePartyRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Party Player left event
	Result GameSvrRPCSendAdapter::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto LeftPlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InLeftPlayerID);
		SF::Flat::Game::PartyPlayerLeftS2CEvtBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_left_player_id(LeftPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyPlayerLeftS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyPlayerLeftS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID )
	// Cmd: Kick player from the party
	Result GameSvrRPCSendAdapter::PartyKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::PartyKickPlayerResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::PartyKickPlayerRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyKickPlayerRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Party Player kicked message
	Result GameSvrRPCSendAdapter::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto KickedPlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InKickedPlayerID);
		SF::Flat::Game::PartyPlayerKickedS2CEvtBuilder _builder(fbb);
		_builder.add_party_uid(InPartyUID);
		_builder.add_kicked_player_id(KickedPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyPlayerKickedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyPlayerKickedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID )
	// Cmd: Invite a player to the party
	Result GameSvrRPCSendAdapter::PartyInviteRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::PartyInviteResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::PartyInviteRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyInviteRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyInviteRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Party invite requested
	Result GameSvrRPCSendAdapter::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InviterIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InInviterID);
		auto InviterNameOffset = SF::Flat::Helper::CreateString(fbb, InInviterName);
		SF::Flat::Game::PartyInviteRequestedS2CEvtBuilder _builder(fbb);
		_builder.add_inviter_id(InviterIDOffset);
		_builder.add_inviter_name(InviterNameOffset);
		_builder.add_party_to_join_uid(InPartyToJoinUID);
		flatbuffers::Offset<SF::Flat::Game::PartyInviteRequestedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyInviteRequestedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID )
	// Cmd: Send Party quick chat message
	Result GameSvrRPCSendAdapter::PartyQuickChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::PartyQuickChatMessageResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::PartyQuickChatMessageRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyQuickChatMessageRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyQuickChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Party Chatting message event
	Result GameSvrRPCSendAdapter::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto SenderIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InSenderID);
		SF::Flat::Game::PartyQuickChatMessageS2CEvtBuilder _builder(fbb);
		_builder.add_sender_id(SenderIDOffset);
		_builder.add_quick_chat_id(InQuickChatID);
		flatbuffers::Offset<SF::Flat::Game::PartyQuickChatMessageS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyQuickChatMessageS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID )
	// Cmd: Party chatting
	Result GameSvrRPCSendAdapter::PartyChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::PartyChatMessageResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::PartyChatMessageRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_PartyChatMessageRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Party Chatting message event
	Result GameSvrRPCSendAdapter::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto SenderIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InSenderID);
		auto SenderNameOffset = SF::Flat::Helper::CreateString(fbb, InSenderName);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::Game::PartyChatMessageS2CEvtBuilder _builder(fbb);
		_builder.add_sender_id(SenderIDOffset);
		_builder.add_sender_name(SenderNameOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::PartyChatMessageS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_PartyChatMessageS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage )
	// Cmd: Join to a game instance
	Result GameSvrRPCSendAdapter::JoinGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const GameInstanceUID &InInsUID, const char* InServerPublicAddress )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InsUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InInsUID);
		auto ServerPublicAddressOffset = SF::Flat::Helper::CreateString(fbb, InServerPublicAddress);
		SF::Flat::Game::JoinGameInstanceResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_ins_uid(InsUIDOffset);
		_builder.add_server_public_address(ServerPublicAddressOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinGameInstanceRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinGameInstanceRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::JoinGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const GameInstanceUID &InInsUID, const char* InServerPublicAddress )
	// Cmd: Leave game instance
	Result GameSvrRPCSendAdapter::LeaveGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::LeaveGameInstanceResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::LeaveGameInstanceRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_LeaveGameInstanceRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::LeaveGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Search game instance
	Result GameSvrRPCSendAdapter::SearchGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto GameInstancesOffset = SF::Flat::Helper::CreateVariableTableVector(fbb, InGameInstances);
		SF::Flat::Game::SearchGameInstanceResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_game_instances(GameInstancesOffset);
		flatbuffers::Offset<SF::Flat::Game::SearchGameInstanceRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SearchGameInstanceRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::SearchGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances )
	// Cmd: Search game instance
	Result GameSvrRPCSendAdapter::GetCharacterDataInGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PlayerIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InPlayerID);
		auto GameInstancesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InGameInstances);
		SF::Flat::Game::GetCharacterDataInGameInstanceResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_player_id(PlayerIDOffset);
		_builder.add_game_instances(GameInstancesOffset);
		flatbuffers::Offset<SF::Flat::Game::GetCharacterDataInGameInstanceRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetCharacterDataInGameInstanceRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetCharacterDataInGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances )
	// Cmd: Request Game match
	Result GameSvrRPCSendAdapter::RequestGameMatchRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RequestGameMatchResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_total_gem(InTotalGem);
		_builder.add_total_game_money(InTotalGameMoney);
		flatbuffers::Offset<SF::Flat::Game::RequestGameMatchRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestGameMatchRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::RequestGameMatchRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// S2C: Game matched
	Result GameSvrRPCSendAdapter::GameMatchedS2CEvt( const GameInstanceUID &InInsUID, const uint32_t &InTimeStamp, const GameStateID &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto InsUIDOffset = SF::Flat::Helper::CreateGameInstanceUID(fbb, InInsUID);
		auto GameStateOffset = SF::Flat::Helper::CreateGameStateID(fbb, InGameState);
		auto ChatHistoryDataOffset = SF::Flat::Helper::Createuint8Vector(fbb, InChatHistoryData);
		auto GameLogDataOffset = SF::Flat::Helper::Createuint8Vector(fbb, InGameLogData);
		SF::Flat::Game::GameMatchedS2CEvtBuilder _builder(fbb);
		_builder.add_ins_uid(InsUIDOffset);
		_builder.add_time_stamp(InTimeStamp);
		_builder.add_game_state(GameStateOffset);
		_builder.add_day(InDay);
		_builder.add_max_player(InMaxPlayer);
		_builder.add_player_index(InPlayerIndex);
		_builder.add_player_character(InPlayerCharacter);
		_builder.add_role(InRole);
		_builder.add_dead(InDead);
		_builder.add_chat_history_data(ChatHistoryDataOffset);
		_builder.add_game_log_data(GameLogDataOffset);
		_builder.add_stamina(InStamina);
		_builder.add_total_gem(InTotalGem);
		_builder.add_total_game_money(InTotalGameMoney);
		flatbuffers::Offset<SF::Flat::Game::GameMatchedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_GameMatchedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GameMatchedS2CEvt( const GameInstanceUID &InInsUID, const uint32_t &InTimeStamp, const GameStateID &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney )
	// S2C: Game match failed
	Result GameSvrRPCSendAdapter::GameMatchFailedS2CEvt( const Result &InFailedReason )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GameMatchFailedS2CEvtBuilder _builder(fbb);
		_builder.add_failed_reason((int)InFailedReason);
		flatbuffers::Offset<SF::Flat::Game::GameMatchFailedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_GameMatchFailedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GameMatchFailedS2CEvt( const Result &InFailedReason )
	// S2C: Game matching started
	Result GameSvrRPCSendAdapter::GameMatchingStartedS2CEvt(  )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GameMatchingStartedS2CEvtBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::GameMatchingStartedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_GameMatchingStartedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GameMatchingStartedS2CEvt(  )
	// Cmd: Cancel Game match
	Result GameSvrRPCSendAdapter::CancelGameMatchRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::CancelGameMatchResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::CancelGameMatchRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CancelGameMatchRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::CancelGameMatchRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: game matching canceled
	Result GameSvrRPCSendAdapter::GameMatchingCanceledS2CEvt(  )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GameMatchingCanceledS2CEvtBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Game::GameMatchingCanceledS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_GameMatchingCanceledS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GameMatchingCanceledS2CEvt(  )
	// Cmd: Request UGC template list
	Result GameSvrRPCSendAdapter::GetUGCTemplatesRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCIDs )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::GetUGCTemplatesResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_ugcids(InUGCIDs);
		flatbuffers::Offset<SF::Flat::Game::GetUGCTemplatesRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetUGCTemplatesRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetUGCTemplatesRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCIDs )
	// Cmd: Save UGC content data
	Result GameSvrRPCSendAdapter::SaveUGCRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::SaveUGCResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_ugcid(InUGCID);
		flatbuffers::Offset<SF::Flat::Game::SaveUGCRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SaveUGCRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::SaveUGCRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCID )
	// Cmd: Request WhiteboardSharing
	Result GameSvrRPCSendAdapter::SearchUGCRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::SearchUGCResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::SearchUGCRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SearchUGCRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::SearchUGCRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Get UGC content info, name, thumb image and so on
	Result GameSvrRPCSendAdapter::GetUGCContentInfoRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto UGCMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InUGCMetaData);
		SF::Flat::Game::GetUGCContentInfoResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_ugcmeta_data(UGCMetaDataOffset);
		flatbuffers::Offset<SF::Flat::Game::GetUGCContentInfoRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetUGCContentInfoRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetUGCContentInfoRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData )
	// Cmd: Request WhiteboardSharing
	Result GameSvrRPCSendAdapter::DownloadUGCContentRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto UGCMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InUGCMetaData);
		SF::Flat::Game::DownloadUGCContentResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_ugcmeta_data(UGCMetaDataOffset);
		flatbuffers::Offset<SF::Flat::Game::DownloadUGCContentRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_DownloadUGCContentRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::DownloadUGCContentRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData )
	// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone
	Result GameSvrRPCSendAdapter::RequestUGCZoneInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InGameInstance )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto GameInstanceOffset = SF::Flat::Helper::CreateVariableTable(fbb, InGameInstance);
		SF::Flat::Game::RequestUGCZoneInstanceResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_game_instance(GameInstanceOffset);
		flatbuffers::Offset<SF::Flat::Game::RequestUGCZoneInstanceRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestUGCZoneInstanceRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::RequestUGCZoneInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InGameInstance )
	// Cmd: Buy shop item prepare
	Result GameSvrRPCSendAdapter::BuyShopItemPrepareRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PurchaseIDOffset = SF::Flat::Helper::CreateString(fbb, InPurchaseID);
		SF::Flat::Game::BuyShopItemPrepareResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_shop_item_id(InShopItemID);
		_builder.add_purchase_id(PurchaseIDOffset);
		flatbuffers::Offset<SF::Flat::Game::BuyShopItemPrepareRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_BuyShopItemPrepareRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::BuyShopItemPrepareRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID )
	// Cmd: Buy shop item
	Result GameSvrRPCSendAdapter::BuyShopItemRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::BuyShopItemResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_shop_item_id(InShopItemID);
		flatbuffers::Offset<SF::Flat::Game::BuyShopItemRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_BuyShopItemRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::BuyShopItemRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID )
	// Cmd: Create or Join Chat channel
	Result GameSvrRPCSendAdapter::CreateOrJoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InChatUID, const PlayerID &InChannelLeaderID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto ChannelLeaderIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InChannelLeaderID);
		SF::Flat::Game::CreateOrJoinChatChannelResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_channel_leader_id(ChannelLeaderIDOffset);
		flatbuffers::Offset<SF::Flat::Game::CreateOrJoinChatChannelRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CreateOrJoinChatChannelRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::CreateOrJoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InChatUID, const PlayerID &InChannelLeaderID )
	// Cmd: Join
	Result GameSvrRPCSendAdapter::JoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InChatUID, const PlayerID &InChannelLeaderID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto ChannelLeaderIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InChannelLeaderID);
		SF::Flat::Game::JoinChatChannelResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_channel_leader_id(ChannelLeaderIDOffset);
		flatbuffers::Offset<SF::Flat::Game::JoinChatChannelRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_JoinChatChannelRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::JoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InChatUID, const PlayerID &InChannelLeaderID )
	// S2C: Player Joined event
	Result GameSvrRPCSendAdapter::ChatChannelPlayerJoinedS2CEvt( const EntityUID &InChatUID, const PlayerInformation &InJoinedPlayer )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto JoinedPlayerOffset = SF::Flat::Helper::CreatePlayerInformation(fbb, InJoinedPlayer);
		SF::Flat::Game::ChatChannelPlayerJoinedS2CEvtBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_joined_player(JoinedPlayerOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelPlayerJoinedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_ChatChannelPlayerJoinedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelPlayerJoinedS2CEvt( const EntityUID &InChatUID, const PlayerInformation &InJoinedPlayer )
	// S2C: ChatChannel leader changed event
	Result GameSvrRPCSendAdapter::ChatChannelLeaderChangedS2CEvt( const EntityUID &InChatUID, const AccountID &InNewLeaderID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto NewLeaderIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InNewLeaderID);
		SF::Flat::Game::ChatChannelLeaderChangedS2CEvtBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_new_leader_id(NewLeaderIDOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelLeaderChangedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_ChatChannelLeaderChangedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelLeaderChangedS2CEvt( const EntityUID &InChatUID, const AccountID &InNewLeaderID )
	// Cmd: Leave ChatChannel command
	Result GameSvrRPCSendAdapter::LeaveChatChannelRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::LeaveChatChannelResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::LeaveChatChannelRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_LeaveChatChannelRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::LeaveChatChannelRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Player left event
	Result GameSvrRPCSendAdapter::ChatChannelPlayerLeftS2CEvt( const EntityUID &InChatUID, const AccountID &InLeftPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto LeftPlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InLeftPlayerID);
		SF::Flat::Game::ChatChannelPlayerLeftS2CEvtBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_left_player_id(LeftPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelPlayerLeftS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_ChatChannelPlayerLeftS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelPlayerLeftS2CEvt( const EntityUID &InChatUID, const AccountID &InLeftPlayerID )
	// Cmd: Kick player from the ChatChannel
	Result GameSvrRPCSendAdapter::ChatChannelKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::ChatChannelKickPlayerResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelKickPlayerRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_ChatChannelKickPlayerRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Player kicked message
	Result GameSvrRPCSendAdapter::ChatChannelPlayerKickedS2CEvt( const EntityUID &InChatUID, const AccountID &InKickedPlayerID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ChatUIDOffset = SF::Flat::Helper::CreateEntityUID(fbb, InChatUID);
		auto KickedPlayerIDOffset = SF::Flat::Helper::CreateAccountID(fbb, InKickedPlayerID);
		SF::Flat::Game::ChatChannelPlayerKickedS2CEvtBuilder _builder(fbb);
		_builder.add_chat_uid(ChatUIDOffset);
		_builder.add_kicked_player_id(KickedPlayerIDOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelPlayerKickedS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_ChatChannelPlayerKickedS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelPlayerKickedS2CEvt( const EntityUID &InChatUID, const AccountID &InKickedPlayerID )
	// Cmd: Chat channel sending chatting message
	Result GameSvrRPCSendAdapter::ChatChannelChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::ChatChannelChatMessageResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelChatMessageRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_ChatChannelChatMessageRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelChatMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: ChatChannel Chatting message event
	Result GameSvrRPCSendAdapter::ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto SenderIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InSenderID);
		auto ChatMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InChatMetaData);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::Game::ChatChannelChatMessageS2CEvtBuilder _builder(fbb);
		_builder.add_sender_id(SenderIDOffset);
		_builder.add_chat_meta_data(ChatMetaDataOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::ChatChannelChatMessageS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_ChatChannelChatMessageS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Whisper(tell) other player chatting
	Result GameSvrRPCSendAdapter::WhisperMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::WhisperMessageResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::WhisperMessageRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_WhisperMessageRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::WhisperMessageRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Other player whispered(tell) to me message event
	Result GameSvrRPCSendAdapter::WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto SenderIDOffset = SF::Flat::Helper::CreatePlayerID(fbb, InSenderID);
		auto ChatMetaDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InChatMetaData);
		auto ChatMessageOffset = SF::Flat::Helper::CreateString(fbb, InChatMessage);
		SF::Flat::Game::WhisperMessageS2CEvtBuilder _builder(fbb);
		_builder.add_sender_id(SenderIDOffset);
		_builder.add_chat_meta_data(ChatMetaDataOffset);
		_builder.add_chat_message(ChatMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::WhisperMessageS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_WhisperMessageS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage )
	// Cmd: Create character
	Result GameSvrRPCSendAdapter::CreateCharacterRes( const TransactionID &InTransactionID, const Result &InResult, const CharacterID &InCharacterID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		SF::Flat::Game::CreateCharacterResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_character_id(CharacterIDOffset);
		flatbuffers::Offset<SF::Flat::Game::CreateCharacterRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CreateCharacterRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::CreateCharacterRes( const TransactionID &InTransactionID, const Result &InResult, const CharacterID &InCharacterID )
	// Cmd: Delete character
	Result GameSvrRPCSendAdapter::DeleteCharacterRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::DeleteCharacterResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::DeleteCharacterRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_DeleteCharacterRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::DeleteCharacterRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Get character list
	Result GameSvrRPCSendAdapter::GetCharacterListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharactersOffset = SF::Flat::Helper::CreateVariableTableVector(fbb, InCharacters);
		SF::Flat::Game::GetCharacterListResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_characters(CharactersOffset);
		flatbuffers::Offset<SF::Flat::Game::GetCharacterListRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetCharacterListRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetCharacterListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters )
	// Cmd: 
	Result GameSvrRPCSendAdapter::GetCharacterDataRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto PrivateDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InPrivateData);
		auto EquipDataOffset = SF::Flat::Helper::CreateVariableTable(fbb, InEquipData);
		SF::Flat::Game::GetCharacterDataResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_private_data(PrivateDataOffset);
		_builder.add_equip_data(EquipDataOffset);
		flatbuffers::Offset<SF::Flat::Game::GetCharacterDataRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_GetCharacterDataRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::GetCharacterDataRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData )
	// Cmd: Select character
	Result GameSvrRPCSendAdapter::SelectCharacterRes( const TransactionID &InTransactionID, const Result &InResult, const CharacterID &InCharacterID, const VariableTable &InAttributes )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto CharacterIDOffset = SF::Flat::Helper::CreateCharacterID(fbb, InCharacterID);
		auto AttributesOffset = SF::Flat::Helper::CreateVariableTable(fbb, InAttributes);
		SF::Flat::Game::SelectCharacterResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_character_id(CharacterIDOffset);
		_builder.add_attributes(AttributesOffset);
		flatbuffers::Offset<SF::Flat::Game::SelectCharacterRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_SelectCharacterRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::SelectCharacterRes( const TransactionID &InTransactionID, const Result &InResult, const CharacterID &InCharacterID, const VariableTable &InAttributes )
	// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
	Result GameSvrRPCSendAdapter::RequestServerNoticeUpdateRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Game::RequestServerNoticeUpdateResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		flatbuffers::Offset<SF::Flat::Game::RequestServerNoticeUpdateRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_RequestServerNoticeUpdateRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::RequestServerNoticeUpdateRes( const TransactionID &InTransactionID, const Result &InResult )
	// S2C: Server Notice updated event
	Result GameSvrRPCSendAdapter::ServerNoticeS2CEvt( const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ServerNoticeMessageOffset = SF::Flat::Helper::CreateString(fbb, InServerNoticeMessage);
		SF::Flat::Game::ServerNoticeS2CEvtBuilder _builder(fbb);
		_builder.add_notice_category(InNoticeCategory);
		_builder.add_server_notice_message(ServerNoticeMessageOffset);
		flatbuffers::Offset<SF::Flat::Game::ServerNoticeS2CEvt> packetOffset = _builder.Finish();

		protocolCheck(Send(TransactionID(), Message::Game::MID_ServerNoticeS2CEvt, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::ServerNoticeS2CEvt( const int8_t &InNoticeCategory, const char* InServerNoticeMessage )
	// Cmd: To call general functionality
	Result GameSvrRPCSendAdapter::CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto ResultsOffset = SF::Flat::Helper::CreateVariableTable(fbb, InResults);
		SF::Flat::Game::CallFunctionResBuilder _builder(fbb);
		_builder.add_result((int)InResult);
		_builder.add_results(ResultsOffset);
		flatbuffers::Offset<SF::Flat::Game::CallFunctionRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, Message::Game::MID_CallFunctionRes, fbb));


		return hr;
	}; // Result GameSvrRPCSendAdapter::CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults )


}; // namespace SF


