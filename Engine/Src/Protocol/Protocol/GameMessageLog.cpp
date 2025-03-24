////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Game Message log implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Protocol/GameMessageLog.h"
#include "Protocol/Game_generated.h"
#ifdef ERROR
#undef ERROR
#endif
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"



namespace SF
{
 	bool GameMessageLog::stm_IsInitialized = false;
	flatbuffers::Parser GameMessageLog::stm_Parser;
	Result GameMessageLog::Initialize()
	{
 		Result hr;

		if (stm_IsInitialized) return hr;
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_HeartbeatC2SEvt,&HeartbeatC2SEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinGameServerCmd,&JoinGameServerCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinGameServerRes,&JoinGameServerRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetAchievementStatsCmd,&GetAchievementStatsCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetAchievementStatsRes,&GetAchievementStatsRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_Dummy1Cmd,&Dummy1Cmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_Dummy1Res,&Dummy1Res));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RegisterGCMCmd,&RegisterGCMCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RegisterGCMRes,&RegisterGCMRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_UnregisterGCMCmd,&UnregisterGCMCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_UnregisterGCMRes,&UnregisterGCMRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_InviteFriendCmd,&InviteFriendCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_InviteFriendRes,&InviteFriendRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_AcceptFriendRequestCmd,&AcceptFriendRequestCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_AcceptFriendRequestRes,&AcceptFriendRequestRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FriendRequestAcceptedS2CEvt,&FriendRequestAcceptedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RemoveFriendCmd,&RemoveFriendCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RemoveFriendRes,&RemoveFriendRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FriendRemovedS2CEvt,&FriendRemovedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetFriendListCmd,&GetFriendListCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetFriendListRes,&GetFriendListRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetNotificationListCmd,&GetNotificationListCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetNotificationListRes,&GetNotificationListRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_DeleteNotificationCmd,&DeleteNotificationCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_DeleteNotificationRes,&DeleteNotificationRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SetNotificationReadCmd,&SetNotificationReadCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SetNotificationReadRes,&SetNotificationReadRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_AcceptNotificationCmd,&AcceptNotificationCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_AcceptNotificationRes,&AcceptNotificationRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_NotifyS2CEvt,&NotifyS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByPlatformIdCmd,&FindPlayerByPlatformIdCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByPlatformIdRes,&FindPlayerByPlatformIdRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByCharacterNameCmd,&FindPlayerByCharacterNameCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByCharacterNameRes,&FindPlayerByCharacterNameRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByPlatformUserNameCmd,&FindPlayerByPlatformUserNameCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByPlatformUserNameRes,&FindPlayerByPlatformUserNameRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByEMailCmd,&FindPlayerByEMailCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByEMailRes,&FindPlayerByEMailRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByPlayerIDCmd,&FindPlayerByPlayerIDCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_FindPlayerByPlayerIDRes,&FindPlayerByPlayerIDRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestPlayerStatusUpdateCmd,&RequestPlayerStatusUpdateCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestPlayerStatusUpdateRes,&RequestPlayerStatusUpdateRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_NotifyPlayerStatusUpdatedS2CEvt,&NotifyPlayerStatusUpdatedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetRankingListCmd,&GetRankingListCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetRankingListRes,&GetRankingListRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetUserGamePlayerInfoCmd,&GetUserGamePlayerInfoCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetUserGamePlayerInfoRes,&GetUserGamePlayerInfoRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetGamePlayerInfoCmd,&GetGamePlayerInfoCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetGamePlayerInfoRes,&GetGamePlayerInfoRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LevelUpS2CEvt,&LevelUpS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SetNickNameCmd,&SetNickNameCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SetNickNameRes,&SetNickNameRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CreatePartyCmd,&CreatePartyCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CreatePartyRes,&CreatePartyRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinPartyCmd,&JoinPartyCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinPartyRes,&JoinPartyRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyPlayerJoinedS2CEvt,&PartyPlayerJoinedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyLeaderChangedS2CEvt,&PartyLeaderChangedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LeavePartyCmd,&LeavePartyCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LeavePartyRes,&LeavePartyRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyPlayerLeftS2CEvt,&PartyPlayerLeftS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyKickPlayerCmd,&PartyKickPlayerCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyKickPlayerRes,&PartyKickPlayerRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyPlayerKickedS2CEvt,&PartyPlayerKickedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyInviteCmd,&PartyInviteCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyInviteRes,&PartyInviteRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyInviteRequestedS2CEvt,&PartyInviteRequestedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyQuickChatMessageCmd,&PartyQuickChatMessageCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyQuickChatMessageRes,&PartyQuickChatMessageRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyQuickChatMessageS2CEvt,&PartyQuickChatMessageS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyChatMessageCmd,&PartyChatMessageCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyChatMessageRes,&PartyChatMessageRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_PartyChatMessageS2CEvt,&PartyChatMessageS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinGameInstanceCmd,&JoinGameInstanceCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinGameInstanceRes,&JoinGameInstanceRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LeaveGameInstanceCmd,&LeaveGameInstanceCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LeaveGameInstanceRes,&LeaveGameInstanceRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SearchGameInstanceCmd,&SearchGameInstanceCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SearchGameInstanceRes,&SearchGameInstanceRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestGameMatchCmd,&RequestGameMatchCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestGameMatchRes,&RequestGameMatchRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GameMatchedS2CEvt,&GameMatchedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GameMatchFailedS2CEvt,&GameMatchFailedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GameMatchingStartedS2CEvt,&GameMatchingStartedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CancelGameMatchCmd,&CancelGameMatchCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CancelGameMatchRes,&CancelGameMatchRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GameMatchingCanceledS2CEvt,&GameMatchingCanceledS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetUGCTemplatesCmd,&GetUGCTemplatesCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetUGCTemplatesRes,&GetUGCTemplatesRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SaveUGCCmd,&SaveUGCCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SaveUGCRes,&SaveUGCRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SearchUGCCmd,&SearchUGCCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SearchUGCRes,&SearchUGCRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetUGCContentInfoCmd,&GetUGCContentInfoCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetUGCContentInfoRes,&GetUGCContentInfoRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_DownloadUGCContentCmd,&DownloadUGCContentCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_DownloadUGCContentRes,&DownloadUGCContentRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestUGCZoneInstanceCmd,&RequestUGCZoneInstanceCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestUGCZoneInstanceRes,&RequestUGCZoneInstanceRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_BuyShopItemPrepareCmd,&BuyShopItemPrepareCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_BuyShopItemPrepareRes,&BuyShopItemPrepareRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_BuyShopItemCmd,&BuyShopItemCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_BuyShopItemRes,&BuyShopItemRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CreateOrJoinChatChannelCmd,&CreateOrJoinChatChannelCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CreateOrJoinChatChannelRes,&CreateOrJoinChatChannelRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinChatChannelCmd,&JoinChatChannelCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_JoinChatChannelRes,&JoinChatChannelRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelPlayerJoinedS2CEvt,&ChatChannelPlayerJoinedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelLeaderChangedS2CEvt,&ChatChannelLeaderChangedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LeaveChatChannelCmd,&LeaveChatChannelCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_LeaveChatChannelRes,&LeaveChatChannelRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelPlayerLeftS2CEvt,&ChatChannelPlayerLeftS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelKickPlayerCmd,&ChatChannelKickPlayerCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelKickPlayerRes,&ChatChannelKickPlayerRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelPlayerKickedS2CEvt,&ChatChannelPlayerKickedS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelChatMessageCmd,&ChatChannelChatMessageCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelChatMessageRes,&ChatChannelChatMessageRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ChatChannelChatMessageS2CEvt,&ChatChannelChatMessageS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_WhisperMessageCmd,&WhisperMessageCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_WhisperMessageRes,&WhisperMessageRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_WhisperMessageS2CEvt,&WhisperMessageS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CreateCharacterCmd,&CreateCharacterCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CreateCharacterRes,&CreateCharacterRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_DeleteCharacterCmd,&DeleteCharacterCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_DeleteCharacterRes,&DeleteCharacterRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetCharacterListCmd,&GetCharacterListCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetCharacterListRes,&GetCharacterListRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetCharacterDataCmd,&GetCharacterDataCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_GetCharacterDataRes,&GetCharacterDataRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SelectCharacterCmd,&SelectCharacterCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_SelectCharacterRes,&SelectCharacterRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestServerNoticeUpdateCmd,&RequestServerNoticeUpdateCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_RequestServerNoticeUpdateRes,&RequestServerNoticeUpdateRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_ServerNoticeS2CEvt,&ServerNoticeS2CEvt));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CallFunctionCmd,&CallFunctionCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Game::MID_CallFunctionRes,&CallFunctionRes));


		Protocol::LoadFlatSchema(stm_Parser, "Game.fbs");
		stm_Parser.opts.indent_step = -1; // no new line
		stm_IsInitialized = true;

		return hr;
	}; // Result GameMessageLog::Initialize()
	Result GameMessageLog::HeartbeatC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.HeartbeatC2SEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug7, "{0} Game:HeartbeatC2SEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::HeartbeatC2SEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinGameServerCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinGameServerCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinGameServerCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinGameServerCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinGameServerRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinGameServerRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinGameServerRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinGameServerRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetAchievementStatsCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetAchievementStatsCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetAchievementStatsCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetAchievementStatsCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetAchievementStatsRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetAchievementStatsRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetAchievementStatsRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetAchievementStatsRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::Dummy1Cmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.Dummy1Cmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:Dummy1Cmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::Dummy1Cmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::Dummy1Res(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.Dummy1Res";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:Dummy1Res: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::Dummy1Res(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RegisterGCMCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RegisterGCMCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RegisterGCMCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RegisterGCMCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RegisterGCMRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RegisterGCMRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RegisterGCMRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RegisterGCMRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::UnregisterGCMCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.UnregisterGCMCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:UnregisterGCMCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::UnregisterGCMCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::UnregisterGCMRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.UnregisterGCMRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:UnregisterGCMRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::UnregisterGCMRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::InviteFriendCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.InviteFriendCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:InviteFriendCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::InviteFriendCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::InviteFriendRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.InviteFriendRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:InviteFriendRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::InviteFriendRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::AcceptFriendRequestCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.AcceptFriendRequestCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:AcceptFriendRequestCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::AcceptFriendRequestCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::AcceptFriendRequestRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.AcceptFriendRequestRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:AcceptFriendRequestRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::AcceptFriendRequestRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FriendRequestAcceptedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FriendRequestAcceptedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FriendRequestAcceptedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FriendRequestAcceptedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RemoveFriendCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RemoveFriendCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RemoveFriendCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RemoveFriendCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RemoveFriendRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RemoveFriendRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RemoveFriendRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RemoveFriendRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FriendRemovedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FriendRemovedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FriendRemovedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FriendRemovedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetFriendListCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetFriendListCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetFriendListCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetFriendListCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetFriendListRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetFriendListRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetFriendListRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetFriendListRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetNotificationListCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetNotificationListCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetNotificationListCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetNotificationListCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetNotificationListRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetNotificationListRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetNotificationListRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetNotificationListRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::DeleteNotificationCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.DeleteNotificationCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:DeleteNotificationCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::DeleteNotificationCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::DeleteNotificationRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.DeleteNotificationRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:DeleteNotificationRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::DeleteNotificationRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SetNotificationReadCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SetNotificationReadCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SetNotificationReadCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SetNotificationReadCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SetNotificationReadRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SetNotificationReadRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SetNotificationReadRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SetNotificationReadRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::AcceptNotificationCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.AcceptNotificationCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:AcceptNotificationCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::AcceptNotificationCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::AcceptNotificationRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.AcceptNotificationRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:AcceptNotificationRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::AcceptNotificationRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::NotifyS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.NotifyS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:NotifyS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::NotifyS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByPlatformIdCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByPlatformIdCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByPlatformIdCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByPlatformIdCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByPlatformIdRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByPlatformIdRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByPlatformIdRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByPlatformIdRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByCharacterNameCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByCharacterNameCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByCharacterNameCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByCharacterNameCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByCharacterNameRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByCharacterNameRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByCharacterNameRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByCharacterNameRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByPlatformUserNameCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByPlatformUserNameCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByPlatformUserNameCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByPlatformUserNameCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByPlatformUserNameRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByPlatformUserNameRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByPlatformUserNameRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByPlatformUserNameRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByEMailCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByEMailCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByEMailCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByEMailCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByEMailRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByEMailRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByEMailRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByEMailRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByPlayerIDCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByPlayerIDCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByPlayerIDCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByPlayerIDCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::FindPlayerByPlayerIDRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.FindPlayerByPlayerIDRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:FindPlayerByPlayerIDRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::FindPlayerByPlayerIDRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestPlayerStatusUpdateCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestPlayerStatusUpdateCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestPlayerStatusUpdateCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestPlayerStatusUpdateCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestPlayerStatusUpdateRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestPlayerStatusUpdateRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestPlayerStatusUpdateRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestPlayerStatusUpdateRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::NotifyPlayerStatusUpdatedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.NotifyPlayerStatusUpdatedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:NotifyPlayerStatusUpdatedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::NotifyPlayerStatusUpdatedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetRankingListCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetRankingListCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetRankingListCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetRankingListCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetRankingListRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetRankingListRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetRankingListRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetRankingListRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetUserGamePlayerInfoCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetUserGamePlayerInfoCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetUserGamePlayerInfoCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetUserGamePlayerInfoCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetUserGamePlayerInfoRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetUserGamePlayerInfoRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetUserGamePlayerInfoRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetUserGamePlayerInfoRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetGamePlayerInfoCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetGamePlayerInfoCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetGamePlayerInfoCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetGamePlayerInfoCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetGamePlayerInfoRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetGamePlayerInfoRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetGamePlayerInfoRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetGamePlayerInfoRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LevelUpS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LevelUpS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LevelUpS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LevelUpS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SetNickNameCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SetNickNameCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SetNickNameCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SetNickNameCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SetNickNameRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SetNickNameRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SetNickNameRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SetNickNameRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CreatePartyCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CreatePartyCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CreatePartyCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CreatePartyCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CreatePartyRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CreatePartyRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CreatePartyRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CreatePartyRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinPartyCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinPartyCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinPartyCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinPartyCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinPartyRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinPartyRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinPartyRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinPartyRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyPlayerJoinedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyPlayerJoinedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyPlayerJoinedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyPlayerJoinedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyLeaderChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyLeaderChangedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyLeaderChangedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyLeaderChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LeavePartyCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LeavePartyCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LeavePartyCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LeavePartyCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LeavePartyRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LeavePartyRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LeavePartyRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LeavePartyRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyPlayerLeftS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyPlayerLeftS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyPlayerLeftS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyPlayerLeftS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyKickPlayerCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyKickPlayerCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyKickPlayerCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyKickPlayerCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyKickPlayerRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyKickPlayerRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyKickPlayerRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyKickPlayerRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyPlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyPlayerKickedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyPlayerKickedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyPlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyInviteCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyInviteCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyInviteCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyInviteCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyInviteRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyInviteRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyInviteRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyInviteRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyInviteRequestedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyInviteRequestedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyInviteRequestedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyInviteRequestedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyQuickChatMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyQuickChatMessageCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyQuickChatMessageCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyQuickChatMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyQuickChatMessageRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyQuickChatMessageRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyQuickChatMessageRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyQuickChatMessageRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyQuickChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyQuickChatMessageS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyQuickChatMessageS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyQuickChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyChatMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyChatMessageCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyChatMessageCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyChatMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyChatMessageRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyChatMessageRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyChatMessageRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyChatMessageRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::PartyChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.PartyChatMessageS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:PartyChatMessageS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::PartyChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinGameInstanceCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinGameInstanceCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinGameInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinGameInstanceRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinGameInstanceRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinGameInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LeaveGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LeaveGameInstanceCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LeaveGameInstanceCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LeaveGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LeaveGameInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LeaveGameInstanceRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LeaveGameInstanceRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LeaveGameInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SearchGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SearchGameInstanceCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SearchGameInstanceCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SearchGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SearchGameInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SearchGameInstanceRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SearchGameInstanceRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SearchGameInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestGameMatchCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestGameMatchCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestGameMatchCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestGameMatchCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestGameMatchRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestGameMatchRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestGameMatchRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestGameMatchRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GameMatchedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GameMatchedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GameMatchedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GameMatchedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GameMatchFailedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GameMatchFailedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GameMatchFailedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GameMatchFailedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GameMatchingStartedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GameMatchingStartedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GameMatchingStartedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GameMatchingStartedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CancelGameMatchCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CancelGameMatchCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CancelGameMatchCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CancelGameMatchCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CancelGameMatchRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CancelGameMatchRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CancelGameMatchRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CancelGameMatchRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GameMatchingCanceledS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GameMatchingCanceledS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GameMatchingCanceledS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GameMatchingCanceledS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetUGCTemplatesCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetUGCTemplatesCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetUGCTemplatesCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetUGCTemplatesCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetUGCTemplatesRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetUGCTemplatesRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetUGCTemplatesRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetUGCTemplatesRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SaveUGCCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SaveUGCCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SaveUGCCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SaveUGCCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SaveUGCRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SaveUGCRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SaveUGCRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SaveUGCRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SearchUGCCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SearchUGCCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SearchUGCCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SearchUGCCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SearchUGCRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SearchUGCRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SearchUGCRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SearchUGCRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetUGCContentInfoCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetUGCContentInfoCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetUGCContentInfoCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetUGCContentInfoCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetUGCContentInfoRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetUGCContentInfoRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetUGCContentInfoRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetUGCContentInfoRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::DownloadUGCContentCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.DownloadUGCContentCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:DownloadUGCContentCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::DownloadUGCContentCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::DownloadUGCContentRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.DownloadUGCContentRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:DownloadUGCContentRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::DownloadUGCContentRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestUGCZoneInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestUGCZoneInstanceCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestUGCZoneInstanceCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestUGCZoneInstanceCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestUGCZoneInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestUGCZoneInstanceRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestUGCZoneInstanceRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestUGCZoneInstanceRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::BuyShopItemPrepareCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.BuyShopItemPrepareCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:BuyShopItemPrepareCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::BuyShopItemPrepareCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::BuyShopItemPrepareRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.BuyShopItemPrepareRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:BuyShopItemPrepareRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::BuyShopItemPrepareRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::BuyShopItemCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.BuyShopItemCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:BuyShopItemCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::BuyShopItemCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::BuyShopItemRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.BuyShopItemRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:BuyShopItemRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::BuyShopItemRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CreateOrJoinChatChannelCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CreateOrJoinChatChannelCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CreateOrJoinChatChannelCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CreateOrJoinChatChannelCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CreateOrJoinChatChannelRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CreateOrJoinChatChannelRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CreateOrJoinChatChannelRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CreateOrJoinChatChannelRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinChatChannelCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinChatChannelCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinChatChannelCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinChatChannelCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::JoinChatChannelRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.JoinChatChannelRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:JoinChatChannelRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::JoinChatChannelRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelPlayerJoinedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelPlayerJoinedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelPlayerJoinedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelPlayerJoinedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelLeaderChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelLeaderChangedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelLeaderChangedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelLeaderChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LeaveChatChannelCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LeaveChatChannelCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LeaveChatChannelCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LeaveChatChannelCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::LeaveChatChannelRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.LeaveChatChannelRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:LeaveChatChannelRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::LeaveChatChannelRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelPlayerLeftS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelPlayerLeftS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelPlayerLeftS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelPlayerLeftS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelKickPlayerCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelKickPlayerCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelKickPlayerCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelKickPlayerCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelKickPlayerRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelKickPlayerRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelKickPlayerRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelKickPlayerRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelPlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelPlayerKickedS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelPlayerKickedS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelPlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelChatMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelChatMessageCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelChatMessageCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelChatMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelChatMessageRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelChatMessageRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelChatMessageRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelChatMessageRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ChatChannelChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ChatChannelChatMessageS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ChatChannelChatMessageS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ChatChannelChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::WhisperMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.WhisperMessageCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:WhisperMessageCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::WhisperMessageCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::WhisperMessageRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.WhisperMessageRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:WhisperMessageRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::WhisperMessageRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::WhisperMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.WhisperMessageS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:WhisperMessageS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::WhisperMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CreateCharacterCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CreateCharacterCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CreateCharacterCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CreateCharacterCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CreateCharacterRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CreateCharacterRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CreateCharacterRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CreateCharacterRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::DeleteCharacterCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.DeleteCharacterCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:DeleteCharacterCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::DeleteCharacterCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::DeleteCharacterRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.DeleteCharacterRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:DeleteCharacterRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::DeleteCharacterRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetCharacterListCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetCharacterListCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetCharacterListCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetCharacterListCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetCharacterListRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetCharacterListRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetCharacterListRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetCharacterListRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetCharacterDataCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetCharacterDataCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetCharacterDataCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetCharacterDataCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::GetCharacterDataRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.GetCharacterDataRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:GetCharacterDataRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::GetCharacterDataRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SelectCharacterCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SelectCharacterCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SelectCharacterCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SelectCharacterCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::SelectCharacterRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.SelectCharacterRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:SelectCharacterRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::SelectCharacterRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestServerNoticeUpdateCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestServerNoticeUpdateCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestServerNoticeUpdateCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestServerNoticeUpdateCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::RequestServerNoticeUpdateRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.RequestServerNoticeUpdateRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:RequestServerNoticeUpdateRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::RequestServerNoticeUpdateRes(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::ServerNoticeS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.ServerNoticeS2CEvt";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:ServerNoticeS2CEvt: sz:{1}: {2}", prefix, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::ServerNoticeS2CEvt(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CallFunctionCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CallFunctionCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CallFunctionCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CallFunctionCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GameMessageLog::CallFunctionRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Game.CallFunctionRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Game:CallFunctionRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GameMessageLog::CallFunctionRes(const char* prefix, const MessageHeader* messageHeader)


}; // namespace SF


