////////////////////////////////////////////////////////////////////////////////
// 
// StormForge
// 
// Author : Generated
// 
// Description : Game RPC Send interface
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "MessageBus/SFRPCSendAdapter.h"
#include "Protocol/GameMessageID.h"




namespace SF
{
    class MessageEndpoint;
   class VariableTable;
   struct ActorMovement;


	class GameRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		GameRPCSendAdapter (MessageEndpoint* pEndpoint) : RPCSendAdapter(pEndpoint)
		{}
		GameRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// C2S: Client heartbeat
		Result HeartbeatC2SEvt(  );
		// Cmd: Player connected from a login server and moved to game server
		Result JoinGameServerCmd( const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
		// Cmd: player completion statues
		Result GetAchievementStatsCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo );
		// Cmd: Player complition state
		Result Dummy1Cmd( const TransactionID &InTransactionID, const char* InComplitionState );
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result RegisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID );
		// Cmd: Unregister Google notification service ID
		Result UnregisterGCMCmd( const TransactionID &InTransactionID, const char* InGCMRegisteredID );
		// Cmd: Invite friend
		Result InviteFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID );
		// Cmd: Accept friend request
		Result AcceptFriendRequestCmd( const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId );
		// Cmd: Remove friden form the friend list
		Result RemoveFriendCmd( const TransactionID &InTransactionID, const AccountID &InFriendID );
		// Cmd: Get friend list
		Result GetFriendListCmd( const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount );
		// Cmd: Query notification list
		Result GetNotificationListCmd( const TransactionID &InTransactionID );
		// Cmd: Delete notification
		Result DeleteNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID );
		// Cmd: Set notification is read
		Result SetNotificationReadCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID );
		// Cmd: Accept notification
		Result AcceptNotificationCmd( const TransactionID &InTransactionID, const uint32_t &InNotificationID );
		// Cmd: PlayerId Conversion
		Result FindPlayerByPlatformIdCmd( const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId );
		// Cmd: PlayerId conversion
		Result FindPlayerByCharacterNameCmd( const TransactionID &InTransactionID, const char* InCharacterName );
		// Cmd: PlayerId Conversion
		Result FindPlayerByPlatformUserNameCmd( const TransactionID &InTransactionID, const EPlatform &InPlatformType, const char* InPlatformUserName );
		// Cmd: Query playerID list
		Result FindPlayerByEMailCmd( const TransactionID &InTransactionID, const char* InPlayerEMail );
		// Cmd: Query playerID list
		Result FindPlayerByPlayerIDCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID );
		// Cmd: *Request Player Status Update
		Result RequestPlayerStatusUpdateCmd( const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID );
		// Cmd: Get Ranking list
		Result GetRankingListCmd( const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );
		// Cmd: Game user game play information
		Result GetUserGamePlayerInfoCmd( const TransactionID &InTransactionID );
		// Cmd: Game game play information
		Result GetGamePlayerInfoCmd( const TransactionID &InTransactionID, const AccountID &InPlayerID );
		// Cmd: Change NickName
		Result SetNickNameCmd( const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree );
		// Cmd: Create Party
		Result CreatePartyCmd( const TransactionID &InTransactionID );
		// Cmd: Join party
		Result JoinPartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID );
		// Cmd: Leave party command
		Result LeavePartyCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID );
		// Cmd: Kick player from the party
		Result PartyKickPlayerCmd( const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );
		// Cmd: Invite a player to the party
		Result PartyInviteCmd( const TransactionID &InTransactionID, const AccountID &InInviteTargetID );
		// Cmd: Send Party quick chat message
		Result PartyQuickChatMessageCmd( const TransactionID &InTransactionID, const uint32_t &InQuickChatID );
		// Cmd: Party chatting
		Result PartyChatMessageCmd( const TransactionID &InTransactionID, const char* InChatMessage );
		// Cmd: Join to a game instance
		Result JoinGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InInsUID );
		// Cmd: Leave game instance
		Result LeaveGameInstanceCmd( const TransactionID &InTransactionID, const GameInstanceUID &InInsUID );
		// Cmd: Search game instance. directory based search schema.    @SearchKeyword    - Static zone search with zone id: /ZoneInstance/Static/{ZoneTableID}/*    - Public UGC zone search for a player: /ZoneInstance/UGC/{PlayerID}/*   
		Result SearchGameInstanceCmd( const TransactionID &InTransactionID, const char* InSearchKeyword );
		// Cmd: Request Game match
		Result RequestGameMatchCmd( const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole );
		// Cmd: Cancel Game match
		Result CancelGameMatchCmd( const TransactionID &InTransactionID );
		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		Result GetMyUGCGamesCmd( const TransactionID &InTransactionID );
		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		Result RequestUGCGameInstanceCmd( const TransactionID &InTransactionID, const Guid &InUGCContentId );
		// Cmd: Request UGC template list
		Result GetUGCTemplatesCmd( const TransactionID &InTransactionID, const Array<const char*>& InTags );
		// Cmd: Upload UGC content data
		Result UploadUGCCmd( const TransactionID &InTransactionID, const VariableTable &InUGCMetaData, const VariableTable &InUGCContents );
		// Cmd: Request WhiteboardSharing
		Result SearchUGCCmd( const TransactionID &InTransactionID, const Array<const char*>& InTags );
		// Cmd: Get UGC content info, name, thumb image and so on
		Result GetUGCContentInfoCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID );
		// Cmd: Request WhiteboardSharing
		Result DownloadUGCContentCmd( const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData );
		// Cmd: Buy shop item prepare
		Result BuyShopItemPrepareCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID );
		// Cmd: Buy shop item
		Result BuyShopItemCmd( const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken );
		// Cmd: Create or Join Chat channel
		Result CreateOrJoinChatChannelCmd( const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode );
		// Cmd: Join
		Result JoinChatChannelCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InInviterID, const char* InPasscode );
		// Cmd: Leave ChatChannel command
		Result LeaveChatChannelCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID );
		// Cmd: Kick player from the ChatChannel
		Result ChatChannelKickPlayerCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );
		// Cmd: Chat channel sending chatting message
		Result ChatChannelChatMessageCmd( const TransactionID &InTransactionID, const EntityUID &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage );
		// Cmd: Whisper(tell) other player chatting
		Result WhisperMessageCmd( const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage );
		// Cmd: Create character
		Result CreateCharacterCmd( const TransactionID &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData );
		// Cmd: Delete character
		Result DeleteCharacterCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID );
		// Cmd: Get character list
		Result GetCharacterListCmd( const TransactionID &InTransactionID );
		// Cmd: 
		Result GetCharacterDataCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID );
		// Cmd: Select character
		Result SelectCharacterCmd( const TransactionID &InTransactionID, const CharacterID &InCharacterID );
		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		Result RequestServerNoticeUpdateCmd( const TransactionID &InTransactionID );
		// Cmd: To call general functionality
		Result CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters );

	}; // class GameRPCSendAdapter : public RPCSendAdapter


	class GameSvrRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		GameSvrRPCSendAdapter (MessageEndpoint* pEndpoint) : RPCSendAdapter(pEndpoint)
		{}
		GameSvrRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Player connected from a login server and moved to game server
		Result JoinGameServerRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const GameInstanceUID &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket );
		// Cmd: player completion statues
		Result GetAchievementStatsRes( const TransactionID &InTransactionID, const Result &InResult, const Array<AchievementStat>& InAchievementStats );
		// Cmd: Player complition state
		Result Dummy1Res( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result RegisterGCMRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Unregister Google notification service ID
		Result UnregisterGCMRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Invite friend
		Result InviteFriendRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Accept friend request
		Result AcceptFriendRequestRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InNewFriend );
		// S2C: Notification for friend request is accepted
		Result FriendRequestAcceptedS2CEvt( const PlayerInformation &InAccepter );
		// Cmd: Remove friden form the friend list
		Result RemoveFriendRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InFriendID );
		// S2C: Friend removed
		Result FriendRemovedS2CEvt( const AccountID &InFriendID );
		// Cmd: Get friend list
		Result GetFriendListRes( const TransactionID &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<PlayerInformation>& InFriendList );
		// Cmd: Query notification list
		Result GetNotificationListRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Delete notification
		Result DeleteNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
		// Cmd: Set notification is read
		Result SetNotificationReadRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
		// Cmd: Accept notification
		Result AcceptNotificationRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
		// S2C: Notify new notification
		Result NotifyS2CEvt( const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp );
		// Cmd: PlayerId Conversion
		Result FindPlayerByPlatformIdRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId );
		// Cmd: PlayerId conversion
		Result FindPlayerByCharacterNameRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId );
		// Cmd: PlayerId Conversion
		Result FindPlayerByPlatformUserNameRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerID &InPlayerId, const PlayerPlatformID &InPlayerPlatformId );
		// Cmd: Query playerID list
		Result FindPlayerByEMailRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );
		// Cmd: Query playerID list
		Result FindPlayerByPlayerIDRes( const TransactionID &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );
		// Cmd: *Request Player Status Update
		Result RequestPlayerStatusUpdateRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: *Notify Player Status Updated
		Result NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame );
		// Cmd: Get Ranking list
		Result GetRankingListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
		// Cmd: Game user game play information
		Result GetUserGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InAttributes );
		// Cmd: Game game play information
		Result GetGamePlayerInfoRes( const TransactionID &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes );
		// S2C: Player level up event
		Result LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel );
		// Cmd: Change NickName
		Result SetNickNameRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
		// Cmd: Create Party
		Result CreatePartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID );
		// Cmd: Join party
		Result JoinPartyRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData );
		// S2C: Player Joined event
		Result PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer );
		// S2C: Party leader changed event
		Result PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID );
		// Cmd: Leave party command
		Result LeavePartyRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Party Player left event
		Result PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID );
		// Cmd: Kick player from the party
		Result PartyKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Party Player kicked message
		Result PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID );
		// Cmd: Invite a player to the party
		Result PartyInviteRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Party invite requested
		Result PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID );
		// Cmd: Send Party quick chat message
		Result PartyQuickChatMessageRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Party Chatting message event
		Result PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID );
		// Cmd: Party chatting
		Result PartyChatMessageRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Party Chatting message event
		Result PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage );
		// Cmd: Join to a game instance
		Result JoinGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const GameInstanceUID &InInsUID, const Array<uint8_t>& InZoneCustomData, const char* InServerPublicAddress );
		// Cmd: Leave game instance
		Result LeaveGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Search game instance. directory based search schema.    @SearchKeyword    - Static zone search with zone id: /ZoneInstance/Static/{ZoneTableID}/*    - Public UGC zone search for a player: /ZoneInstance/UGC/{PlayerID}/*   
		Result SearchGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances );
		// Cmd: Request Game match
		Result RequestGameMatchRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
		// S2C: Game matched
		Result GameMatchedS2CEvt( const GameInstanceUID &InInsUID, const uint32_t &InTimeStamp, const GameStateID &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
		// S2C: Game match failed
		Result GameMatchFailedS2CEvt( const Result &InFailedReason );
		// S2C: Game matching started
		Result GameMatchingStartedS2CEvt(  );
		// Cmd: Cancel Game match
		Result CancelGameMatchRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: game matching canceled
		Result GameMatchingCanceledS2CEvt(  );
		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		Result GetMyUGCGamesRes( const TransactionID &InTransactionID, const Result &InResult, const Array<UGCGameInfo>& InUGCContents );
		// Cmd: Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.
		Result RequestUGCGameInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const GameInstanceUID &InGameInstanceID, const char* InGameInstanceAddress );
		// Cmd: Request UGC template list
		Result GetUGCTemplatesRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCIDs );
		// Cmd: Upload UGC content data
		Result UploadUGCRes( const TransactionID &InTransactionID, const Result &InResult, const uint64_t &InUGCID );
		// Cmd: Request WhiteboardSharing
		Result SearchUGCRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Get UGC content info, name, thumb image and so on
		Result GetUGCContentInfoRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData );
		// Cmd: Request WhiteboardSharing
		Result DownloadUGCContentRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InUGCMetaData );
		// Cmd: Buy shop item prepare
		Result BuyShopItemPrepareRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID );
		// Cmd: Buy shop item
		Result BuyShopItemRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InShopItemID );
		// Cmd: Create or Join Chat channel
		Result CreateOrJoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InChatUID, const PlayerID &InChannelLeaderID );
		// Cmd: Join
		Result JoinChatChannelRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InChatUID, const PlayerID &InChannelLeaderID );
		// S2C: Player Joined event
		Result ChatChannelPlayerJoinedS2CEvt( const EntityUID &InChatUID, const PlayerInformation &InJoinedPlayer );
		// S2C: ChatChannel leader changed event
		Result ChatChannelLeaderChangedS2CEvt( const EntityUID &InChatUID, const AccountID &InNewLeaderID );
		// Cmd: Leave ChatChannel command
		Result LeaveChatChannelRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: ChatChannel Player left event
		Result ChatChannelPlayerLeftS2CEvt( const EntityUID &InChatUID, const AccountID &InLeftPlayerID );
		// Cmd: Kick player from the ChatChannel
		Result ChatChannelKickPlayerRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: ChatChannel Player kicked message
		Result ChatChannelPlayerKickedS2CEvt( const EntityUID &InChatUID, const AccountID &InKickedPlayerID );
		// Cmd: Chat channel sending chatting message
		Result ChatChannelChatMessageRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: ChatChannel Chatting message event
		Result ChatChannelChatMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage );
		// Cmd: Whisper(tell) other player chatting
		Result WhisperMessageRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Other player whispered(tell) to me message event
		Result WhisperMessageS2CEvt( const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage );
		// Cmd: Create character
		Result CreateCharacterRes( const TransactionID &InTransactionID, const Result &InResult, const CharacterID &InCharacterID );
		// Cmd: Delete character
		Result DeleteCharacterRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Get character list
		Result GetCharacterListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters );
		// Cmd: 
		Result GetCharacterDataRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InPrivateData, const VariableTable &InEquipData );
		// Cmd: Select character
		Result SelectCharacterRes( const TransactionID &InTransactionID, const Result &InResult, const CharacterID &InCharacterID, const VariableTable &InAttributes );
		// Cmd: Request Server Notice. Sever will send ServerNoticeS2CEvt
		Result RequestServerNoticeUpdateRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Server Notice updated event
		Result ServerNoticeS2CEvt( const int8_t &InNoticeCategory, const char* InServerNoticeMessage );
		// Cmd: To call general functionality
		Result CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults );

	}; // class GameSvrRPCSendAdapter : public RPCSendAdapter


}; // namespace SF


