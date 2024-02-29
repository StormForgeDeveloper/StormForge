***
 
 CopyRight (c) 2024 StormForge
 
 Description : Game Message Protocol API Document

***



Game Server Protocol. Interface the game client can call to the server.

namespace SF::Message::Game


# Protocol interface class NetPolicyGame
## HeartbeatC2SEvt
Client heartbeat

        Result HeartbeatC2SEvt()


## JoinGameServer Request
Player connected from a login server and moved to game server

1. Command interface

        Result JoinGameServerCmd(const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID)

		- OutTransactionID: TransactionID type. 

		- OutAccID: AccountID type. AccountID of the player

		- OutTicket: AuthTicket type. Login session Ticket

		- OutLoginEntityUID: uint64 type. Login entity ID which you would get from login server

2. Result interface

C++: Cast message to JoinGameServerRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutNickName: String type. Nickname of the player
		- OutGameUID: GameInsUID type. Game instance UID. If the player is in a game, this value will have player's game instance id
		- OutPartyUID: PartyUID type. PartyUID. If the player is in a party
		- OutPartyLeaderID: AccountID type. PlayerID, for now, PlayerID is same to AccountID
		- OutMatchingTicket: MatchingQueueTicket type. Matching queue ticket


## GetAchievementStats Request
player complition statues

1. Command interface

        Result GetAchievementStatsCmd(const TransactionID &InTransactionID, const uint32_t &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo)

		- OutTransactionID: TransactionID type. 

		- OutCharacterID: uint32 type. Character Id to request

		- OutAchievementStatIDFrom: uint32 type. Beginning of achievementStat Id range to query

		- OutAchievementStatIDTo: uint32 type. End of achievementStat Id range to query

2. Result interface

C++: Cast message to GetAchievementStatsRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutAchievementStats: AchievementStat type. Achievement stat array


## Dummy1 Request
Player complition state

1. Command interface

        Result Dummy1Cmd(const TransactionID &InTransactionID, const char* InComplitionState)

		- OutTransactionID: TransactionID type. 

		- OutComplitionState: String type. Complition state to set

2. Result interface

C++: Cast message to Dummy1Res to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## RegisterGCM Request
Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time

1. Command interface

        Result RegisterGCMCmd(const TransactionID &InTransactionID, const char* InGCMRegisteredID)

		- OutTransactionID: TransactionID type. 

		- OutGCMRegisteredID: String type. Google notification ID

2. Result interface

C++: Cast message to RegisterGCMRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## UnregisterGCM Request
Unregister Google notification service ID

1. Command interface

        Result UnregisterGCMCmd(const TransactionID &InTransactionID, const char* InGCMRegisteredID)

		- OutTransactionID: TransactionID type. 

		- OutGCMRegisteredID: String type. ID to unregister

2. Result interface

C++: Cast message to UnregisterGCMRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## InviteFriend Request
Invite friend

1. Command interface

        Result InviteFriendCmd(const TransactionID &InTransactionID, const AccountID &InFriendID)

		- OutTransactionID: TransactionID type. 

		- OutFriendID: AccountID type. PlayerID to invite

2. Result interface

C++: Cast message to InviteFriendRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## AcceptFriendRequest Request
Accept friend request

1. Command interface

        Result AcceptFriendRequestCmd(const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId)

		- OutTransactionID: TransactionID type. 

		- OutInviterID: AccountID type. Inviter PlayerID

		- OutInviterPlatformId: PlayerPlatformID type. Inviter player ID

2. Result interface

C++: Cast message to AcceptFriendRequestRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutNewFriend: FriendInformation type. FriendInformation of the player


## FriendRequestAcceptedS2CEvt
Notification for friend request is accepted

        Result FriendRequestAcceptedS2CEvt(const FriendInformation &InAccepter)

		- OutInAccepter: FriendInformation type. Accepted player's information


## RemoveFriend Request
Remove friden form the friend list

1. Command interface

        Result RemoveFriendCmd(const TransactionID &InTransactionID, const AccountID &InFriendID)

		- OutTransactionID: TransactionID type. 

		- OutFriendID: AccountID type. Friend player ID

2. Result interface

C++: Cast message to RemoveFriendRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutFriendID: AccountID type. Removed friend player ID


## FriendRemovedS2CEvt
Friend removed

        Result FriendRemovedS2CEvt(const AccountID &InFriendID)

		- OutInFriendID: AccountID type. friend player ID


## GetFriendList Request
Get friend list

1. Command interface

        Result GetFriendListCmd(const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount)

		- OutTransactionID: TransactionID type. 

		- OutStartIndex: uint16 type. Friend list start index

		- OutCount: uint16 type. Maximum friend list to query

2. Result interface

C++: Cast message to GetFriendListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutMaxFriendSlot: uint16 type. Maximum friend list
		- OutTotalNumberOfFriends: uint16 type. Maximum friend list
		- OutStartIndex: uint16 type. Friend list start index
		- OutFriendList: FriendInformation type. Friend list


## GetNotificationList Request
Query notification list

1. Command interface

        Result GetNotificationListCmd(const TransactionID &InTransactionID)

		- OutTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetNotificationListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## DeleteNotification Request
Delete notification

1. Command interface

        Result DeleteNotificationCmd(const TransactionID &InTransactionID, const uint32_t &InNotificationID)

		- OutTransactionID: TransactionID type. 

		- OutNotificationID: uint32 type. Notification ID to delete

2. Result interface

C++: Cast message to DeleteNotificationRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutNotificationID: uint32 type. Deleted Notification ID


## SetNotificationRead Request
Set notification is read

1. Command interface

        Result SetNotificationReadCmd(const TransactionID &InTransactionID, const uint32_t &InNotificationID)

		- OutTransactionID: TransactionID type. 

		- OutNotificationID: uint32 type. Notification ID to set read

2. Result interface

C++: Cast message to SetNotificationReadRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutNotificationID: uint32 type. Notification ID to set read


## AcceptNotification Request
Accept notification

1. Command interface

        Result AcceptNotificationCmd(const TransactionID &InTransactionID, const uint32_t &InNotificationID)

		- OutTransactionID: TransactionID type. 

		- OutNotificationID: uint32 type. Notification ID to accept

2. Result interface

C++: Cast message to AcceptNotificationRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutNotificationID: uint32 type. Accepted Notification ID


## NotifyS2CEvt
Notify new notification

        Result NotifyS2CEvt(const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const Array<uint8_t>& InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp)

		- OutInNotificationID: uint32 type. Notification ID. Zero if it is an instant notification(not saved to db).

		- OutInNotificationType: StringCrc32 type. Notification type

		- OutInParameters: VariableTable type. Message parameters

		- OutInIsRead: uint8 type. Notification is read?

		- OutInTimeStamp: uint64 type. Issued UTC sec


## FindPlayerByPlatformId Request
PlayerId Conversion

1. Command interface

        Result FindPlayerByPlatformIdCmd(const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId)

		- OutTransactionID: TransactionID type. 

		- OutPlatformPlayerId: PlayerPlatformID type. Platform playerId

2. Result interface

C++: Cast message to FindPlayerByPlatformIdRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayerId: PlayerID type. PlayerId
		- OutPlayerPlatformId: PlayerPlatformID type. Platform player Id. ex) Steam


## FindPlayerByCharacterName Request
PlayerId conversion

1. Command interface

        Result FindPlayerByCharacterNameCmd(const TransactionID &InTransactionID, const char* InCharacterName)

		- OutTransactionID: TransactionID type. 

		- OutCharacterName: String type. Character name to search

2. Result interface

C++: Cast message to FindPlayerByCharacterNameRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayerId: PlayerID type. PlayerId


## FindPlayerByPlatformUserName Request
PlayerId Conversion

1. Command interface

        Result FindPlayerByPlatformUserNameCmd(const TransactionID &InTransactionID, const uint8_t &InPlatformType, const char* InPlatformUserName)

		- OutTransactionID: TransactionID type. 

		- OutPlatformType: uint8 type. Platform type. See EPlatform

		- OutPlatformUserName: String type. Platform User name

2. Result interface

C++: Cast message to FindPlayerByPlatformUserNameRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayerId: PlayerID type. PlayerId
		- OutPlayerPlatformId: PlayerPlatformID type. Platform player Id. ex) Steam


## FindPlayerByEMail Request
Query playerID list

1. Command interface

        Result FindPlayerByEMailCmd(const TransactionID &InTransactionID, const char* InPlayerEMail)

		- OutTransactionID: TransactionID type. 

		- OutPlayerEMail: String type. Player email to find

2. Result interface

C++: Cast message to FindPlayerByEMailRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayer: PlayerInformation type. Player information if found


## FindPlayerByPlayerID Request
Query playerID list

1. Command interface

        Result FindPlayerByPlayerIDCmd(const TransactionID &InTransactionID, const AccountID &InPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutPlayerID: AccountID type. Player ID to find

2. Result interface

C++: Cast message to FindPlayerByPlayerIDRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayer: PlayerInformation type. Player information if found


## RequestPlayerStatusUpdate Request
*Request Player Status Update

1. Command interface

        Result RequestPlayerStatusUpdateCmd(const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutTargetPlayerID: AccountID type. PlayerIDs to request

2. Result interface

C++: Cast message to RequestPlayerStatusUpdateRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## NotifyPlayerStatusUpdatedS2CEvt
*Notify Player Status Updated

        Result NotifyPlayerStatusUpdatedS2CEvt(const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame)

		- OutInPlayerID: AccountID type. Player ID

		- OutInLatestActiveTime: uint32 type. Latest active time of the player(32bit UTC sec)

		- OutInIsInGame: uint8 type. TRUE if the player is in a game


## GetRankingList Request
Get Ranking list

1. Command interface

        Result GetRankingListCmd(const TransactionID &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount)

		- OutTransactionID: TransactionID type. 

		- OutRankingType: uint8 type. 

		- OutBaseRanking: uint8 type. Base ranking to query, 0 based ranking order

		- OutCount: uint8 type. Number of playerinformation to query

2. Result interface

C++: Cast message to GetRankingListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutRanking: TotalRankingPlayerInformation type. 


## GetUserGamePlayerInfo Request
Game user game play information

1. Command interface

        Result GetUserGamePlayerInfoCmd(const TransactionID &InTransactionID)

		- OutTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetUserGamePlayerInfoRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutAttributes: VariableTable type. 


## GetGamePlayerInfo Request
Game game play information

1. Command interface

        Result GetGamePlayerInfoCmd(const TransactionID &InTransactionID, const AccountID &InPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutPlayerID: AccountID type. Game playerID to get

2. Result interface

C++: Cast message to GetGamePlayerInfoRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayerID: AccountID type. Game player ID
		- OutAttributes: VariableTable type. 


## LevelUpS2CEvt
Player level up event

        Result LevelUpS2CEvt(const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel)

		- OutInCurrentTotalExp: uint64 type. Current total exp of the player

		- OutInCurrentLevel: uint32 type. Current level


## SetNickName Request
Change NickName

1. Command interface

        Result SetNickNameCmd(const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree)

		- OutTransactionID: TransactionID type. 

		- OutNickName: String type. Nickname to change

		- OutIsCostFree: uint8 type. CostFree

2. Result interface

C++: Cast message to SetNickNameRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutTotalGem: uint64 type. Total after cost is consumed
		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## CreateParty Request
Create Party

1. Command interface

        Result CreatePartyCmd(const TransactionID &InTransactionID)

		- OutTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to CreatePartyRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPartyUID: PartyUID type. Created Party UID


## JoinParty Request
Join party

1. Command interface

        Result JoinPartyCmd(const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID)

		- OutTransactionID: TransactionID type. 

		- OutPartyUID: PartyUID type. Party ID to join

		- OutInviterID: AccountID type. Party inviter ID

2. Result interface

C++: Cast message to JoinPartyRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPartyUID: PartyUID type. Party UID
		- OutPartyLeaderID: AccountID type. Party leader ID
		- OutChatHistoryData: uint8 type. Chatting history of the party


## PartyPlayerJoinedS2CEvt
Player Joined event

        Result PartyPlayerJoinedS2CEvt(const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer)

		- OutInPartyUID: PartyUID type. Party UID

		- OutInJoinedPlayer: PlayerInformation type. Joind player information


## PartyLeaderChangedS2CEvt
Party leader changed event

        Result PartyLeaderChangedS2CEvt(const uint64_t &InPartyUID, const AccountID &InNewLeaderID)

		- OutInPartyUID: PartyUID type. Party UID

		- OutInNewLeaderID: AccountID type. New leader ID


## LeaveParty Request
Leave party command

1. Command interface

        Result LeavePartyCmd(const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutPartyUID: PartyUID type. PartyID to leave

		- OutPlayerID: AccountID type. Player ID to leave

2. Result interface

C++: Cast message to LeavePartyRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## PartyPlayerLeftS2CEvt
Party Player left event

        Result PartyPlayerLeftS2CEvt(const uint64_t &InPartyUID, const AccountID &InLeftPlayerID)

		- OutInPartyUID: PartyUID type. Party ID

		- OutInLeftPlayerID: AccountID type. Left Player ID


## PartyKickPlayer Request
Kick player from the party

1. Command interface

        Result PartyKickPlayerCmd(const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- OutTransactionID: TransactionID type. 

		- OutPartyUID: PartyUID type. PartyUID

		- OutPlayerID: AccountID type. PlayerID of the player

		- OutPlayerToKick: AccountID type. Player To Kick

2. Result interface

C++: Cast message to PartyKickPlayerRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## PartyPlayerKickedS2CEvt
Party Player kicked message

        Result PartyPlayerKickedS2CEvt(const uint64_t &InPartyUID, const AccountID &InKickedPlayerID)

		- OutInPartyUID: PartyUID type. Party UID

		- OutInKickedPlayerID: AccountID type. Kicked player ID


## PartyInvite Request
Invite a player to the party

1. Command interface

        Result PartyInviteCmd(const TransactionID &InTransactionID, const AccountID &InInviteTargetID)

		- OutTransactionID: TransactionID type. 

		- OutInviteTargetID: AccountID type. Invite target player ID

2. Result interface

C++: Cast message to PartyInviteRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## PartyInviteRequestedS2CEvt
Party invite requested

        Result PartyInviteRequestedS2CEvt(const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID)

		- OutInInviterID: AccountID type. Party inviter

		- OutInInviterName: String type. Party inviter name

		- OutInPartyToJoinUID: PartyUID type. Party UID to join


## PartyQuickChatMessage Request
Send Party quick chat message

1. Command interface

        Result PartyQuickChatMessageCmd(const TransactionID &InTransactionID, const uint32_t &InQuickChatID)

		- OutTransactionID: TransactionID type. 

		- OutQuickChatID: uint32 type. My quick chat message ID

2. Result interface

C++: Cast message to PartyQuickChatMessageRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## PartyQuickChatMessageS2CEvt
Party Chatting message event

        Result PartyQuickChatMessageS2CEvt(const AccountID &InSenderID, const uint32_t &InQuickChatID)

		- OutInSenderID: AccountID type. Message sender

		- OutInQuickChatID: uint32 type. My quick chat message ID


## PartyChatMessage Request
Party chatting

1. Command interface

        Result PartyChatMessageCmd(const TransactionID &InTransactionID, const char* InChatMessage)

		- OutTransactionID: TransactionID type. 

		- OutChatMessage: String type. My message

2. Result interface

C++: Cast message to PartyChatMessageRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## PartyChatMessageS2CEvt
Party Chatting message event

        Result PartyChatMessageS2CEvt(const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage)

		- OutInSenderID: AccountID type. Message sender

		- OutInSenderName: String type. Message sender name

		- OutInChatMessage: String type. Message text


## JoinGameInstance Request
Join to a game instance

1. Command interface

        Result JoinGameInstanceCmd(const TransactionID &InTransactionID, const uint64_t &InInsUID)

		- OutTransactionID: TransactionID type. 

		- OutInsUID: GameInsUID type. Game instance ID to join

2. Result interface

C++: Cast message to JoinGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutInsUID: GameInsUID type. Game instance ID
		- OutServerPublicAddress: String type. Game instance address


## LeaveGameInstance Request
Leave game instance

1. Command interface

        Result LeaveGameInstanceCmd(const TransactionID &InTransactionID, const uint64_t &InInsUID)

		- OutTransactionID: TransactionID type. 

		- OutInsUID: GameInsUID type. Game instance ID to join

2. Result interface

C++: Cast message to LeaveGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## SearchGameInstance Request
Search game instance

1. Command interface

        Result SearchGameInstanceCmd(const TransactionID &InTransactionID, const char* InSearchKeyword, const uint32_t &InZoneTableID)

		- OutTransactionID: TransactionID type. 

		- OutSearchKeyword: String type. Search keyword

		- OutZoneTableID: uint32 type. Search keyword, zone table id, ignored if it is zero

2. Result interface

C++: Cast message to SearchGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutGameInstances: VariableTable type. Game instance informations


## GetCharacterDataInGameInstance Request
Search game instance

1. Command interface

        Result GetCharacterDataInGameInstanceCmd(const TransactionID &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutGameInsUID: GameInsUID type. Game instance UID

		- OutPlayerID: PlayerID type. Player Id to get

2. Result interface

C++: Cast message to GetCharacterDataInGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayerID: PlayerID type. Player Movement
		- OutGameInstances: VariableTable type. Game instance ID


## RequestGameMatch Request
Request Game match

1. Command interface

        Result RequestGameMatchCmd(const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole)

		- OutTransactionID: TransactionID type. 

		- OutNumPlayer: uint8 type. Request game match

		- OutRequestRole: uint8 type. Request special role

2. Result interface

C++: Cast message to RequestGameMatchRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutTotalGem: uint64 type. Total after cost is consumed
		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## GameMatchedS2CEvt
Game matched

        Result GameMatchedS2CEvt(const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney)

		- OutInInsUID: GameInsUID type. Matched game instance ID

		- OutInTimeStamp: uint32 type. Time stamp in UTC

		- OutInGameState: GameStateID type. Game state

		- OutInDay: uint8 type. Game Day

		- OutInMaxPlayer: uint8 type. Max player of the game

		- OutInPlayerIndex: uint8 type. Player index in the game

		- OutInPlayerCharacter: uint8 type. Player character in the game

		- OutInRole: uint8 type. Role of the player

		- OutInDead: uint8 type. TRUE if the player is dead

		- OutInChatHistoryData: uint8 type. Game chatting history

		- OutInGameLogData: uint8 type. Game history log

		- OutInStamina: uint32 type. 

		- OutInTotalGem: uint64 type. Game gem

		- OutInTotalGameMoney: uint64 type. Game money


## GameMatchFailedS2CEvt
Game match failed

        Result GameMatchFailedS2CEvt(const Result &InFailedReason)

		- OutInFailedReason: Result type. Match failed reason


## GameMatchingStartedS2CEvt
Game matching started

        Result GameMatchingStartedS2CEvt()


## CancelGameMatch Request
Cancel Game match

1. Command interface

        Result CancelGameMatchCmd(const TransactionID &InTransactionID)

		- OutTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to CancelGameMatchRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## GameMatchingCanceledS2CEvt
game matching canceled

        Result GameMatchingCanceledS2CEvt()


## GetUGCTemplates Request
Request UGC template list

1. Command interface

        Result GetUGCTemplatesCmd(const TransactionID &InTransactionID, const Array<const char*>& InTags)

		- OutTransactionID: TransactionID type. 

		- OutTags: String type. Tags, used for search

2. Result interface

C++: Cast message to GetUGCTemplatesRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutUGCIDs: uint64 type. search result UGC ids


## SaveUGC Request
Save UGC content data

1. Command interface

        Result SaveUGCCmd(const TransactionID &InTransactionID, const Array<uint8_t>& InUGCMetaData, const Array<uint8_t>& InUGCContents)

		- OutTransactionID: TransactionID type. 

		- OutUGCMetaData: VariableTable type. Metadata will be linked with. This is quick access data like name and thumb image

		- OutUGCContents: VariableTable type. UGCContents data. main content binary and so on

2. Result interface

C++: Cast message to SaveUGCRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutUGCID: uint64 type. Assigned UGC content id


## SearchUGC Request
Request WhiteboardSharing

1. Command interface

        Result SearchUGCCmd(const TransactionID &InTransactionID, const Array<const char*>& InTags)

		- OutTransactionID: TransactionID type. 

		- OutTags: String type. Search tags

2. Result interface

C++: Cast message to SearchUGCRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## GetUGCContentInfo Request
Get UGC content info, name, thumb image and so on

1. Command interface

        Result GetUGCContentInfoCmd(const TransactionID &InTransactionID, const uint64_t &InUGCID)

		- OutTransactionID: TransactionID type. 

		- OutUGCID: uint64 type. UGC content id

2. Result interface

C++: Cast message to GetUGCContentInfoRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutUGCMetaData: VariableTable type. UGCContents metadata


## DownloadUGCContent Request
Request WhiteboardSharing

1. Command interface

        Result DownloadUGCContentCmd(const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData)

		- OutTransactionID: TransactionID type. 

		- OutUGCID: uint64 type. UGC content id

		- OutIsIncludeMetaData: uint8 type. 

2. Result interface

C++: Cast message to DownloadUGCContentRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutUGCMetaData: VariableTable type. UGCContents metadata


## RequestUGCZoneInstance Request
Request ugc zone instance. It will provision new zone instance if there is none for the player. Issues: Limit(?), what happens if friend try to get into other player's Aquarium zone

1. Command interface

        Result RequestUGCZoneInstanceCmd(const TransactionID &InTransactionID, const uint64_t &InUGCID)

		- OutTransactionID: TransactionID type. 

		- OutUGCID: uint64 type. UGC content id

2. Result interface

C++: Cast message to RequestUGCZoneInstanceRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutGameInstance: VariableTable type. Privisoned UGC zone instance information


## BuyShopItemPrepare Request
Buy shop item prepare

1. Command interface

        Result BuyShopItemPrepareCmd(const TransactionID &InTransactionID, const uint32_t &InShopItemID)

		- OutTransactionID: TransactionID type. 

		- OutShopItemID: uint32 type. Shop table id

2. Result interface

C++: Cast message to BuyShopItemPrepareRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutShopItemID: uint32 type. Shop table id
		- OutPurchaseID: String type. Purchase ID


## BuyShopItem Request
Buy shop item

1. Command interface

        Result BuyShopItemCmd(const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken)

		- OutTransactionID: TransactionID type. 

		- OutShopItemID: uint32 type. Shop table id

		- OutPlatform: String type. 

		- OutPackageName: String type. 

		- OutPurchaseTransactionID: String type. IOS transaction ID

		- OutPurchaseToken: uint8 type. 

2. Result interface

C++: Cast message to BuyShopItemRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutShopItemID: uint32 type. Shop table id


## CreateOrJoinChatChannel Request
Create or Join Chat channel

1. Command interface

        Result CreateOrJoinChatChannelCmd(const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode)

		- OutTransactionID: TransactionID type. 

		- OutChannelName: String type. 

		- OutPasscode: String type. 

2. Result interface

C++: Cast message to CreateOrJoinChatChannelRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutChatUID: EntityUID type. Created/Joined Chat channel UID
		- OutChannelLeaderID: PlayerID type. ChatChannel leader ID


## JoinChatChannel Request
Join

1. Command interface

        Result JoinChatChannelCmd(const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID, const char* InPasscode)

		- OutTransactionID: TransactionID type. 

		- OutChatUID: EntityUID type. ChatChannel UID to join

		- OutInviterID: AccountID type. Chat channel inviter ID

		- OutPasscode: String type. 

2. Result interface

C++: Cast message to JoinChatChannelRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutChatUID: EntityUID type. ChatChannel UID
		- OutChannelLeaderID: PlayerID type. ChatChannel leader ID


## ChatChannelPlayerJoinedS2CEvt
Player Joined event

        Result ChatChannelPlayerJoinedS2CEvt(const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer)

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInJoinedPlayer: PlayerInformation type. Joind player information


## ChatChannelLeaderChangedS2CEvt
ChatChannel leader changed event

        Result ChatChannelLeaderChangedS2CEvt(const uint64_t &InChatUID, const AccountID &InNewLeaderID)

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInNewLeaderID: AccountID type. New leader ID


## LeaveChatChannel Request
Leave ChatChannel command

1. Command interface

        Result LeaveChatChannelCmd(const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutChatUID: EntityUID type. ChatChannel to leave

		- OutPlayerID: AccountID type. Player ID to leave

2. Result interface

C++: Cast message to LeaveChatChannelRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## ChatChannelPlayerLeftS2CEvt
ChatChannel Player left event

        Result ChatChannelPlayerLeftS2CEvt(const uint64_t &InChatUID, const AccountID &InLeftPlayerID)

		- OutInChatUID: EntityUID type. ChatChannel ID

		- OutInLeftPlayerID: AccountID type. Left Player ID


## ChatChannelKickPlayer Request
Kick player from the ChatChannel

1. Command interface

        Result ChatChannelKickPlayerCmd(const TransactionID &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- OutTransactionID: TransactionID type. 

		- OutChatUID: EntityUID type. PartyUID

		- OutPlayerID: AccountID type. PlayerID of the player

		- OutPlayerToKick: AccountID type. Player To Kick

2. Result interface

C++: Cast message to ChatChannelKickPlayerRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## ChatChannelPlayerKickedS2CEvt
ChatChannel Player kicked message

        Result ChatChannelPlayerKickedS2CEvt(const uint64_t &InChatUID, const AccountID &InKickedPlayerID)

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInKickedPlayerID: AccountID type. Kicked player ID


## ChatChannelChatMessage Request
Chat channel sending chatting message

1. Command interface

        Result ChatChannelChatMessageCmd(const TransactionID &InTransactionID, const uint64_t &InChatUID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutTransactionID: TransactionID type. 

		- OutChatUID: EntityUID type. ChatChannel UID

		- OutChatMetaData: VariableTable type. Chat MetaData, player id and so on

		- OutChatMessage: String type. My message

2. Result interface

C++: Cast message to ChatChannelChatMessageRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## ChatChannelChatMessageS2CEvt
ChatChannel Chatting message event

        Result ChatChannelChatMessageS2CEvt(const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutInSenderID: PlayerID type. Sender PlayerID

		- OutInChatMetaData: VariableTable type. Chat MetaData, player id and so on

		- OutInChatMessage: String type. Message text


## WhisperMessage Request
Whisper(tell) other player chatting

1. Command interface

        Result WhisperMessageCmd(const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutTransactionID: TransactionID type. 

		- OutReceiverID: PlayerID type. Receiver ID

		- OutReceiverName: String type. Receiver name. Supporting character only for now

		- OutChatMetaData: VariableTable type. Chat MetaData, player id and so on

		- OutChatMessage: String type. My message

2. Result interface

C++: Cast message to WhisperMessageRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## WhisperMessageS2CEvt
Other player whispered(tell) to me message event

        Result WhisperMessageS2CEvt(const PlayerID &InSenderID, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutInSenderID: PlayerID type. Sender PlayerID

		- OutInChatMetaData: VariableTable type. Chat MetaData, player id and so on

		- OutInChatMessage: String type. Message text


## CreateCharacter Request
Create character

1. Command interface

        Result CreateCharacterCmd(const TransactionID &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InPrivateData)

		- OutTransactionID: TransactionID type. 

		- OutCharacterName: String type. 

		- OutPublicData: VariableTable type. 

		- OutPrivateData: VariableTable type. 

2. Result interface

C++: Cast message to CreateCharacterRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutCharacterID: uint32 type. Created character ID


## DeleteCharacter Request
Delete character

1. Command interface

        Result DeleteCharacterCmd(const TransactionID &InTransactionID, const uint32_t &InCharacterID)

		- OutTransactionID: TransactionID type. 

		- OutCharacterID: uint32 type. Character ID to remove

2. Result interface

C++: Cast message to DeleteCharacterRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## GetCharacterList Request
Get character list

1. Command interface

        Result GetCharacterListCmd(const TransactionID &InTransactionID)

		- OutTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetCharacterListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutCharacters: VariableTable type. Characters


## GetCharacterData Request


1. Command interface

        Result GetCharacterDataCmd(const TransactionID &InTransactionID, const uint32_t &InCharacterID)

		- OutTransactionID: TransactionID type. 

		- OutCharacterID: uint32 type. Character ID to get

2. Result interface

C++: Cast message to GetCharacterDataRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPrivateData: VariableTable type. Character private data
		- OutEquipData: VariableTable type. Character equip data


## SelectCharacter Request
Select character

1. Command interface

        Result SelectCharacterCmd(const TransactionID &InTransactionID, const uint32_t &InCharacterID)

		- OutTransactionID: TransactionID type. 

		- OutCharacterID: uint32 type. Character ID to select

2. Result interface

C++: Cast message to SelectCharacterRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutCharacterID: uint32 type. Selected Character ID
		- OutAttributes: VariableTable type. Character attributes


## RequestServerNoticeUpdate Request
Request Server Notice. Sever will send ServerNoticeS2CEvt

1. Command interface

        Result RequestServerNoticeUpdateCmd(const TransactionID &InTransactionID)

		- OutTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to RequestServerNoticeUpdateRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## ServerNoticeS2CEvt
Server Notice updated event

        Result ServerNoticeS2CEvt(const int8_t &InNoticeCategory, const char* InServerNoticeMessage)

		- OutInNoticeCategory: int8 type. Notice category

		- OutInServerNoticeMessage: String type. ServerNotice message text


## CallFunction Request
To call general functionality

1. Command interface

        Result CallFunctionCmd(const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters)

		- OutTransactionID: TransactionID type. 

		- OutFunctionName: StringCrc32 type. function name

		- OutParameters: VariableTable type. function parameter

2. Result interface

C++: Cast message to CallFunctionRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutResults: VariableTable type. function result








