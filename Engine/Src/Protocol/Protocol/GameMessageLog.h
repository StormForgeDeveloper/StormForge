////////////////////////////////////////////////////////////////////////////////
// 
// StormForge
// 
// Author : Generated
// 
// Description : Game MessageLog
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "Protocol/GameMessageID.h"




namespace SF
{
 

	class GameMessageLog
	{
 		private:
		static bool stm_IsInitialized;
		static flatbuffers::Parser stm_Parser;

		public:
		static Result Initialize();

		static Result HeartbeatC2SEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinGameServerCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinGameServerRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetAchievementStatsCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetAchievementStatsRes(const char* prefix, const MessageHeader* messageHeader);
		static Result Dummy1Cmd(const char* prefix, const MessageHeader* messageHeader);
		static Result Dummy1Res(const char* prefix, const MessageHeader* messageHeader);
		static Result RegisterGCMCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RegisterGCMRes(const char* prefix, const MessageHeader* messageHeader);
		static Result UnregisterGCMCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result UnregisterGCMRes(const char* prefix, const MessageHeader* messageHeader);
		static Result InviteFriendCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result InviteFriendRes(const char* prefix, const MessageHeader* messageHeader);
		static Result AcceptFriendRequestCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result AcceptFriendRequestRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FriendRequestAcceptedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result RemoveFriendCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RemoveFriendRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FriendRemovedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result GetFriendListCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetFriendListRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetNotificationListCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetNotificationListRes(const char* prefix, const MessageHeader* messageHeader);
		static Result DeleteNotificationCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result DeleteNotificationRes(const char* prefix, const MessageHeader* messageHeader);
		static Result SetNotificationReadCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SetNotificationReadRes(const char* prefix, const MessageHeader* messageHeader);
		static Result AcceptNotificationCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result AcceptNotificationRes(const char* prefix, const MessageHeader* messageHeader);
		static Result NotifyS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByPlatformIdCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByPlatformIdRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByCharacterNameCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByCharacterNameRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByPlatformUserNameCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByPlatformUserNameRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByEMailCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByEMailRes(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByPlayerIDCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result FindPlayerByPlayerIDRes(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestPlayerStatusUpdateCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestPlayerStatusUpdateRes(const char* prefix, const MessageHeader* messageHeader);
		static Result NotifyPlayerStatusUpdatedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result GetRankingListCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetRankingListRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetUserGamePlayerInfoCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetUserGamePlayerInfoRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetGamePlayerInfoCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetGamePlayerInfoRes(const char* prefix, const MessageHeader* messageHeader);
		static Result LevelUpS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result SetNickNameCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SetNickNameRes(const char* prefix, const MessageHeader* messageHeader);
		static Result CreatePartyCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CreatePartyRes(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinPartyCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinPartyRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyPlayerJoinedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyLeaderChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result LeavePartyCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result LeavePartyRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyPlayerLeftS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyKickPlayerCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyKickPlayerRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyPlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyInviteCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyInviteRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyInviteRequestedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyQuickChatMessageCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyQuickChatMessageRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyQuickChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyChatMessageCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyChatMessageRes(const char* prefix, const MessageHeader* messageHeader);
		static Result PartyChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinGameInstanceRes(const char* prefix, const MessageHeader* messageHeader);
		static Result LeaveGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result LeaveGameInstanceRes(const char* prefix, const MessageHeader* messageHeader);
		static Result SearchGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SearchGameInstanceRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetCharacterDataInGameInstanceCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetCharacterDataInGameInstanceRes(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestGameMatchCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestGameMatchRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GameMatchedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result GameMatchFailedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result GameMatchingStartedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result CancelGameMatchCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CancelGameMatchRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GameMatchingCanceledS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result GetUGCTemplatesCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetUGCTemplatesRes(const char* prefix, const MessageHeader* messageHeader);
		static Result SaveUGCCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SaveUGCRes(const char* prefix, const MessageHeader* messageHeader);
		static Result SearchUGCCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SearchUGCRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetUGCContentInfoCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetUGCContentInfoRes(const char* prefix, const MessageHeader* messageHeader);
		static Result DownloadUGCContentCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result DownloadUGCContentRes(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestUGCZoneInstanceCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestUGCZoneInstanceRes(const char* prefix, const MessageHeader* messageHeader);
		static Result BuyShopItemPrepareCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result BuyShopItemPrepareRes(const char* prefix, const MessageHeader* messageHeader);
		static Result BuyShopItemCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result BuyShopItemRes(const char* prefix, const MessageHeader* messageHeader);
		static Result CreateOrJoinChatChannelCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CreateOrJoinChatChannelRes(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinChatChannelCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result JoinChatChannelRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelPlayerJoinedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelLeaderChangedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result LeaveChatChannelCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result LeaveChatChannelRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelPlayerLeftS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelKickPlayerCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelKickPlayerRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelPlayerKickedS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelChatMessageCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelChatMessageRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ChatChannelChatMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result WhisperMessageCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result WhisperMessageRes(const char* prefix, const MessageHeader* messageHeader);
		static Result WhisperMessageS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result CreateCharacterCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CreateCharacterRes(const char* prefix, const MessageHeader* messageHeader);
		static Result DeleteCharacterCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result DeleteCharacterRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetCharacterListCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetCharacterListRes(const char* prefix, const MessageHeader* messageHeader);
		static Result GetCharacterDataCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result GetCharacterDataRes(const char* prefix, const MessageHeader* messageHeader);
		static Result SelectCharacterCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result SelectCharacterRes(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestServerNoticeUpdateCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result RequestServerNoticeUpdateRes(const char* prefix, const MessageHeader* messageHeader);
		static Result ServerNoticeS2CEvt(const char* prefix, const MessageHeader* messageHeader);
		static Result CallFunctionCmd(const char* prefix, const MessageHeader* messageHeader);
		static Result CallFunctionRes(const char* prefix, const MessageHeader* messageHeader);

	}; // class GameMessageLog


}; // namespace SF


