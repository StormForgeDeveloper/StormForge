***
 
 CopyRight (c) 2025 StormForge
 
 Description : Game Message Protocol API Document

***



Game Server Protocol. Interface the game client can call to the server.

namespace SF::Message::Game


# Protocol interface class GameRPCSendAdapter
## HeartbeatC2SEvt
Client heartbeat

        Result HeartbeatC2SEvt()


## JoinGameServer Request
Player connected from a login server and moved to game server

1. Command interface

        Result JoinGameServerCmd(const TransactionID &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID)

		- TransactionID: type:TransactionID, 

		- AccID: type:AccountID, AccountID of the player

		- Ticket: type:AuthTicket, Login session Ticket

		- LoginEntityUID: type:uint64, Login entity ID which you would get from login server

2. Result interface

C++: Cast message to JoinGameServerRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NickName: type:String, Nickname of the player
		- GameUID: type:GameInstanceUID, Game instance UID. If the player is in a game, this value will have player's game instance id
		- PartyUID: type:PartyUID, PartyUID. If the player is in a party
		- PartyLeaderID: type:AccountID, PlayerID, for now, PlayerID is same to AccountID
		- MatchingTicket: type:MatchingQueueTicket, Matching queue ticket


## GetAchievementStats Request
player completion statues

1. Command interface

        Result GetAchievementStatsCmd(const TransactionID &InTransactionID, const CharacterID &InCharacterID, const uint32_t &InAchievementStatIDFrom, const uint32_t &InAchievementStatIDTo)

		- TransactionID: type:TransactionID, 

		- CharacterID: type:CharacterID, Character Id to request

		- AchievementStatIDFrom: type:uint32, Beginning of achievementStat Id range to query

		- AchievementStatIDTo: type:uint32, End of achievementStat Id range to query

2. Result interface

C++: Cast message to GetAchievementStatsRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- AchievementStats: type:AchievementStat, Achievement stat array


## Dummy1 Request
Player complition state

1. Command interface

        Result Dummy1Cmd(const TransactionID &InTransactionID, const char* InComplitionState)

		- TransactionID: type:TransactionID, 

		- ComplitionState: type:String, Complition state to set

2. Result interface

C++: Cast message to Dummy1Res to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## RegisterGCM Request
Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time

1. Command interface

        Result RegisterGCMCmd(const TransactionID &InTransactionID, const char* InGCMRegisteredID)

		- TransactionID: type:TransactionID, 

		- GCMRegisteredID: type:String, Google notification ID

2. Result interface

C++: Cast message to RegisterGCMRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## UnregisterGCM Request
Unregister Google notification service ID

1. Command interface

        Result UnregisterGCMCmd(const TransactionID &InTransactionID, const char* InGCMRegisteredID)

		- TransactionID: type:TransactionID, 

		- GCMRegisteredID: type:String, ID to unregister

2. Result interface

C++: Cast message to UnregisterGCMRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## InviteFriend Request
Invite friend

1. Command interface

        Result InviteFriendCmd(const TransactionID &InTransactionID, const AccountID &InFriendID)

		- TransactionID: type:TransactionID, 

		- FriendID: type:AccountID, PlayerID to invite

2. Result interface

C++: Cast message to InviteFriendRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## AcceptFriendRequest Request
Accept friend request

1. Command interface

        Result AcceptFriendRequestCmd(const TransactionID &InTransactionID, const AccountID &InInviterID, const PlayerPlatformID &InInviterPlatformId)

		- TransactionID: type:TransactionID, 

		- InviterID: type:AccountID, Inviter PlayerID

		- InviterPlatformId: type:PlayerPlatformID, Inviter player ID

2. Result interface

C++: Cast message to AcceptFriendRequestRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NewFriend: type:PlayerInformation, PlayerInformation of the player


## FriendRequestAcceptedS2CEvt
Notification for friend request is accepted

        Result FriendRequestAcceptedS2CEvt(const PlayerInformation &InAccepter)

		- OutInAccepter: PlayerInformation type. Accepted player's information


## RemoveFriend Request
Remove friden form the friend list

1. Command interface

        Result RemoveFriendCmd(const TransactionID &InTransactionID, const AccountID &InFriendID)

		- TransactionID: type:TransactionID, 

		- FriendID: type:AccountID, Friend player ID

2. Result interface

C++: Cast message to RemoveFriendRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- FriendID: type:AccountID, Removed friend player ID


## FriendRemovedS2CEvt
Friend removed

        Result FriendRemovedS2CEvt(const AccountID &InFriendID)

		- OutInFriendID: AccountID type. friend player ID


## GetFriendList Request
Get friend list

1. Command interface

        Result GetFriendListCmd(const TransactionID &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount)

		- TransactionID: type:TransactionID, 

		- StartIndex: type:uint16, Friend list start index

		- Count: type:uint16, Maximum friend list to query

2. Result interface

C++: Cast message to GetFriendListRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- MaxFriendSlot: type:uint16, Maximum friend list
		- TotalNumberOfFriends: type:uint16, Maximum friend list
		- StartIndex: type:uint16, Friend list start index
		- FriendList: type:PlayerInformation, Friend list


## GetNotificationList Request
Query notification list

1. Command interface

        Result GetNotificationListCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GetNotificationListRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## DeleteNotification Request
Delete notification

1. Command interface

        Result DeleteNotificationCmd(const TransactionID &InTransactionID, const uint32_t &InNotificationID)

		- TransactionID: type:TransactionID, 

		- NotificationID: type:uint32, Notification ID to delete

2. Result interface

C++: Cast message to DeleteNotificationRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NotificationID: type:uint32, Deleted Notification ID


## SetNotificationRead Request
Set notification is read

1. Command interface

        Result SetNotificationReadCmd(const TransactionID &InTransactionID, const uint32_t &InNotificationID)

		- TransactionID: type:TransactionID, 

		- NotificationID: type:uint32, Notification ID to set read

2. Result interface

C++: Cast message to SetNotificationReadRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NotificationID: type:uint32, Notification ID to set read


## AcceptNotification Request
Accept notification

1. Command interface

        Result AcceptNotificationCmd(const TransactionID &InTransactionID, const uint32_t &InNotificationID)

		- TransactionID: type:TransactionID, 

		- NotificationID: type:uint32, Notification ID to accept

2. Result interface

C++: Cast message to AcceptNotificationRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- NotificationID: type:uint32, Accepted Notification ID


## NotifyS2CEvt
Notify new notification

        Result NotifyS2CEvt(const uint32_t &InNotificationID, const StringCrc32 &InNotificationType, const VariableTable &InParameters, const uint8_t &InIsRead, const uint64_t &InTimeStamp)

		- OutInNotificationID: uint32 type. Notification ID. Zero if it is an instant notification(not saved to db).

		- OutInNotificationType: StringCrc32 type. Notification type

		- OutInParameters: VariableTable type. Message parameters

		- OutInIsRead: uint8 type. Notification is read?

		- OutInTimeStamp: uint64 type. Issued UTC sec


## FindPlayerByPlatformId Request
PlayerId Conversion

1. Command interface

        Result FindPlayerByPlatformIdCmd(const TransactionID &InTransactionID, const PlayerPlatformID &InPlatformPlayerId)

		- TransactionID: type:TransactionID, 

		- PlatformPlayerId: type:PlayerPlatformID, Platform playerId

2. Result interface

C++: Cast message to FindPlayerByPlatformIdRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayerId: type:PlayerID, PlayerId
		- PlayerPlatformId: type:PlayerPlatformID, Platform player Id. ex) Steam


## FindPlayerByCharacterName Request
PlayerId conversion

1. Command interface

        Result FindPlayerByCharacterNameCmd(const TransactionID &InTransactionID, const char* InCharacterName)

		- TransactionID: type:TransactionID, 

		- CharacterName: type:String, Character name to search

2. Result interface

C++: Cast message to FindPlayerByCharacterNameRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayerId: type:PlayerID, PlayerId


## FindPlayerByPlatformUserName Request
PlayerId Conversion

1. Command interface

        Result FindPlayerByPlatformUserNameCmd(const TransactionID &InTransactionID, const EPlatform &InPlatformType, const char* InPlatformUserName)

		- TransactionID: type:TransactionID, 

		- PlatformType: type:Platform, Platform type. See EPlatform

		- PlatformUserName: type:String, Platform User name

2. Result interface

C++: Cast message to FindPlayerByPlatformUserNameRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayerId: type:PlayerID, PlayerId
		- PlayerPlatformId: type:PlayerPlatformID, Platform player Id. ex) Steam


## FindPlayerByEMail Request
Query playerID list

1. Command interface

        Result FindPlayerByEMailCmd(const TransactionID &InTransactionID, const char* InPlayerEMail)

		- TransactionID: type:TransactionID, 

		- PlayerEMail: type:String, Player email to find

2. Result interface

C++: Cast message to FindPlayerByEMailRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Player: type:PlayerInformation, Player information if found


## FindPlayerByPlayerID Request
Query playerID list

1. Command interface

        Result FindPlayerByPlayerIDCmd(const TransactionID &InTransactionID, const AccountID &InPlayerID)

		- TransactionID: type:TransactionID, 

		- PlayerID: type:AccountID, Player ID to find

2. Result interface

C++: Cast message to FindPlayerByPlayerIDRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Player: type:PlayerInformation, Player information if found


## RequestPlayerStatusUpdate Request
*Request Player Status Update

1. Command interface

        Result RequestPlayerStatusUpdateCmd(const TransactionID &InTransactionID, const Array<AccountID>& InTargetPlayerID)

		- TransactionID: type:TransactionID, 

		- TargetPlayerID: type:AccountID, PlayerIDs to request

2. Result interface

C++: Cast message to RequestPlayerStatusUpdateRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


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

		- TransactionID: type:TransactionID, 

		- RankingType: type:uint8, 

		- BaseRanking: type:uint8, Base ranking to query, 0 based ranking order

		- Count: type:uint8, Number of playerinformation to query

2. Result interface

C++: Cast message to GetRankingListRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Ranking: type:TotalRankingPlayerInformation, 


## GetUserGamePlayerInfo Request
Game user game play information

1. Command interface

        Result GetUserGamePlayerInfoCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GetUserGamePlayerInfoRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Attributes: type:VariableTable, 


## GetGamePlayerInfo Request
Game game play information

1. Command interface

        Result GetGamePlayerInfoCmd(const TransactionID &InTransactionID, const AccountID &InPlayerID)

		- TransactionID: type:TransactionID, 

		- PlayerID: type:AccountID, Game playerID to get

2. Result interface

C++: Cast message to GetGamePlayerInfoRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayerID: type:AccountID, Game player ID
		- Attributes: type:VariableTable, 


## LevelUpS2CEvt
Player level up event

        Result LevelUpS2CEvt(const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel)

		- OutInCurrentTotalExp: uint64 type. Current total exp of the player

		- OutInCurrentLevel: uint32 type. Current level


## SetNickName Request
Change NickName

1. Command interface

        Result SetNickNameCmd(const TransactionID &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree)

		- TransactionID: type:TransactionID, 

		- NickName: type:String, Nickname to change

		- IsCostFree: type:uint8, CostFree

2. Result interface

C++: Cast message to SetNickNameRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- TotalGem: type:uint64, Total after cost is consumed
		- TotalGameMoney: type:uint64, Total after cost is consumed


## CreateParty Request
Create Party

1. Command interface

        Result CreatePartyCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to CreatePartyRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PartyUID: type:PartyUID, Created Party UID


## JoinParty Request
Join party

1. Command interface

        Result JoinPartyCmd(const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID)

		- TransactionID: type:TransactionID, 

		- PartyUID: type:PartyUID, Party ID to join

		- InviterID: type:AccountID, Party inviter ID

2. Result interface

C++: Cast message to JoinPartyRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PartyUID: type:PartyUID, Party UID
		- PartyLeaderID: type:AccountID, Party leader ID
		- ChatHistoryData: type:uint8, Chatting history of the party


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

		- TransactionID: type:TransactionID, 

		- PartyUID: type:PartyUID, PartyID to leave

		- PlayerID: type:AccountID, Player ID to leave

2. Result interface

C++: Cast message to LeavePartyRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## PartyPlayerLeftS2CEvt
Party Player left event

        Result PartyPlayerLeftS2CEvt(const uint64_t &InPartyUID, const AccountID &InLeftPlayerID)

		- OutInPartyUID: PartyUID type. Party ID

		- OutInLeftPlayerID: AccountID type. Left Player ID


## PartyKickPlayer Request
Kick player from the party

1. Command interface

        Result PartyKickPlayerCmd(const TransactionID &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- TransactionID: type:TransactionID, 

		- PartyUID: type:PartyUID, PartyUID

		- PlayerID: type:AccountID, PlayerID of the player

		- PlayerToKick: type:AccountID, Player To Kick

2. Result interface

C++: Cast message to PartyKickPlayerRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## PartyPlayerKickedS2CEvt
Party Player kicked message

        Result PartyPlayerKickedS2CEvt(const uint64_t &InPartyUID, const AccountID &InKickedPlayerID)

		- OutInPartyUID: PartyUID type. Party UID

		- OutInKickedPlayerID: AccountID type. Kicked player ID


## PartyInvite Request
Invite a player to the party

1. Command interface

        Result PartyInviteCmd(const TransactionID &InTransactionID, const AccountID &InInviteTargetID)

		- TransactionID: type:TransactionID, 

		- InviteTargetID: type:AccountID, Invite target player ID

2. Result interface

C++: Cast message to PartyInviteRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


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

		- TransactionID: type:TransactionID, 

		- QuickChatID: type:uint32, My quick chat message ID

2. Result interface

C++: Cast message to PartyQuickChatMessageRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## PartyQuickChatMessageS2CEvt
Party Chatting message event

        Result PartyQuickChatMessageS2CEvt(const AccountID &InSenderID, const uint32_t &InQuickChatID)

		- OutInSenderID: AccountID type. Message sender

		- OutInQuickChatID: uint32 type. My quick chat message ID


## PartyChatMessage Request
Party chatting

1. Command interface

        Result PartyChatMessageCmd(const TransactionID &InTransactionID, const char* InChatMessage)

		- TransactionID: type:TransactionID, 

		- ChatMessage: type:String, My message

2. Result interface

C++: Cast message to PartyChatMessageRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## PartyChatMessageS2CEvt
Party Chatting message event

        Result PartyChatMessageS2CEvt(const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage)

		- OutInSenderID: AccountID type. Message sender

		- OutInSenderName: String type. Message sender name

		- OutInChatMessage: String type. Message text


## RequestJoinGameInstance Request
Join to a game instance

1. Command interface

        Result RequestJoinGameInstanceCmd(const TransactionID &InTransactionID, const GameInstanceUID &InInsUID)

		- TransactionID: type:TransactionID, 

		- InsUID: type:GameInstanceUID, Game instance ID to join

2. Result interface

C++: Cast message to RequestJoinGameInstanceRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- InsUID: type:GameInstanceUID, Game instance ID
		- ZoneCustomData: type:byte, Game zone custom data like UGC modification
		- ServerPublicAddress: type:String, Game instance address


## RequestLeaveGameInstance Request
Leave game instance

1. Command interface

        Result RequestLeaveGameInstanceCmd(const TransactionID &InTransactionID, const GameInstanceUID &InInsUID)

		- TransactionID: type:TransactionID, 

		- InsUID: type:GameInstanceUID, Game instance ID to join

2. Result interface

C++: Cast message to RequestLeaveGameInstanceRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## SearchGameInstance Request
Search game instance. directory based search schema.    @SearchKeyword    - Static zone search with zone id: /ZoneInstance/Static/{ZoneTableID}/*    - Public UGC zone search for a player: /ZoneInstance/UGC/{PlayerID}/*   

1. Command interface

        Result SearchGameInstanceCmd(const TransactionID &InTransactionID, const char* InSearchKeyword)

		- TransactionID: type:TransactionID, 

		- SearchKeyword: type:String, Search keyword

2. Result interface

C++: Cast message to SearchGameInstanceRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- GameInstances: type:VariableTable, Game instance informations


## RequestGameMatch Request
Request Game match

1. Command interface

        Result RequestGameMatchCmd(const TransactionID &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole)

		- TransactionID: type:TransactionID, 

		- NumPlayer: type:uint8, Request game match

		- RequestRole: type:uint8, Request special role

2. Result interface

C++: Cast message to RequestGameMatchRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- TotalGem: type:uint64, Total after cost is consumed
		- TotalGameMoney: type:uint64, Total after cost is consumed


## GameMatchedS2CEvt
Game matched

        Result GameMatchedS2CEvt(const GameInstanceUID &InInsUID, const uint32_t &InTimeStamp, const GameStateID &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney)

		- OutInInsUID: GameInstanceUID type. Matched game instance ID

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

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to CancelGameMatchRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## GameMatchingCanceledS2CEvt
game matching canceled

        Result GameMatchingCanceledS2CEvt()


## GetMyUGCGames Request
Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.

1. Command interface

        Result GetMyUGCGamesCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GetMyUGCGamesRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- UGCContents: type:UGCGameInfo, UGC Game infos


## RequestUGCGameInstance Request
Request ugc zone instance. It will provision new zone instance if there is none for the player. Use SearchGameInstance to find friend's zone instance.

1. Command interface

        Result RequestUGCGameInstanceCmd(const TransactionID &InTransactionID, const Guid &InUGCContentId)

		- TransactionID: type:TransactionID, 

		- UGCContentId: type:Guid, UGC ContentId

2. Result interface

C++: Cast message to RequestUGCGameInstanceRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- GameInstanceID: type:GameInstanceUID, Privisoned UGC zone instance id
		- GameInstanceAddress: type:String, Privisoned UGC zone instance address


## GetUGCTemplates Request
Request UGC template list

1. Command interface

        Result GetUGCTemplatesCmd(const TransactionID &InTransactionID, const Array<const char*>& InTags)

		- TransactionID: type:TransactionID, 

		- Tags: type:String, Tags, used for search

2. Result interface

C++: Cast message to GetUGCTemplatesRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- UGCIDs: type:UGCID, search result UGC ids


## UploadUGC Request
Upload UGC content data

1. Command interface

        Result UploadUGCCmd(const TransactionID &InTransactionID, const VariableTable &InUGCMetaData, const VariableTable &InUGCContents)

		- TransactionID: type:TransactionID, 

		- UGCMetaData: type:VariableTable, Metadata will be linked with. This is quick access data like name and thumb image

		- UGCContents: type:VariableTable, UGCContents data. main content binary and so on

2. Result interface

C++: Cast message to UploadUGCRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- UGCID: type:UGCID, Assigned UGC content id


## SearchUGC Request
Request WhiteboardSharing

1. Command interface

        Result SearchUGCCmd(const TransactionID &InTransactionID, const Array<const char*>& InTags)

		- TransactionID: type:TransactionID, 

		- Tags: type:String, Search tags

2. Result interface

C++: Cast message to SearchUGCRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## GetUGCContentInfo Request
Get UGC content info, name, thumb image and so on

1. Command interface

        Result GetUGCContentInfoCmd(const TransactionID &InTransactionID, const uint64_t &InUGCID)

		- TransactionID: type:TransactionID, 

		- UGCID: type:UGCID, UGC content id

2. Result interface

C++: Cast message to GetUGCContentInfoRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- UGCMetaData: type:VariableTable, UGCContents metadata


## DownloadUGCContent Request
Request WhiteboardSharing

1. Command interface

        Result DownloadUGCContentCmd(const TransactionID &InTransactionID, const uint64_t &InUGCID, const uint8_t &InIsIncludeMetaData)

		- TransactionID: type:TransactionID, 

		- UGCID: type:UGCID, UGC content id

		- IsIncludeMetaData: type:uint8, 

2. Result interface

C++: Cast message to DownloadUGCContentRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- UGCMetaData: type:VariableTable, UGCContents metadata


## BuyShopItemPrepare Request
Buy shop item prepare

1. Command interface

        Result BuyShopItemPrepareCmd(const TransactionID &InTransactionID, const uint32_t &InShopItemID)

		- TransactionID: type:TransactionID, 

		- ShopItemID: type:uint32, Shop table id

2. Result interface

C++: Cast message to BuyShopItemPrepareRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- ShopItemID: type:uint32, Shop table id
		- PurchaseID: type:String, Purchase ID


## BuyShopItem Request
Buy shop item

1. Command interface

        Result BuyShopItemCmd(const TransactionID &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken)

		- TransactionID: type:TransactionID, 

		- ShopItemID: type:uint32, Shop table id

		- Platform: type:String, 

		- PackageName: type:String, 

		- PurchaseTransactionID: type:String, IOS transaction ID

		- PurchaseToken: type:uint8, 

2. Result interface

C++: Cast message to BuyShopItemRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- ShopItemID: type:uint32, Shop table id


## CreateOrJoinChatChannel Request
Create or Join Chat channel

1. Command interface

        Result CreateOrJoinChatChannelCmd(const TransactionID &InTransactionID, const char* InChannelName, const char* InPasscode)

		- TransactionID: type:TransactionID, 

		- ChannelName: type:String, 

		- Passcode: type:String, 

2. Result interface

C++: Cast message to CreateOrJoinChatChannelRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- ChatUID: type:EntityUID, Created/Joined Chat channel UID
		- ChannelLeaderID: type:PlayerID, ChatChannel leader ID


## JoinChatChannel Request
Join

1. Command interface

        Result JoinChatChannelCmd(const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InInviterID, const char* InPasscode)

		- TransactionID: type:TransactionID, 

		- ChatUID: type:EntityUID, ChatChannel UID to join

		- InviterID: type:AccountID, Chat channel inviter ID

		- Passcode: type:String, 

2. Result interface

C++: Cast message to JoinChatChannelRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- ChatUID: type:EntityUID, ChatChannel UID
		- ChannelLeaderID: type:PlayerID, ChatChannel leader ID


## ChatChannelPlayerJoinedS2CEvt
Player Joined event

        Result ChatChannelPlayerJoinedS2CEvt(const EntityUID &InChatUID, const PlayerInformation &InJoinedPlayer)

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInJoinedPlayer: PlayerInformation type. Joind player information


## ChatChannelLeaderChangedS2CEvt
ChatChannel leader changed event

        Result ChatChannelLeaderChangedS2CEvt(const EntityUID &InChatUID, const AccountID &InNewLeaderID)

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInNewLeaderID: AccountID type. New leader ID


## LeaveChatChannel Request
Leave ChatChannel command

1. Command interface

        Result LeaveChatChannelCmd(const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID)

		- TransactionID: type:TransactionID, 

		- ChatUID: type:EntityUID, ChatChannel to leave

		- PlayerID: type:AccountID, Player ID to leave

2. Result interface

C++: Cast message to LeaveChatChannelRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## ChatChannelPlayerLeftS2CEvt
ChatChannel Player left event

        Result ChatChannelPlayerLeftS2CEvt(const EntityUID &InChatUID, const AccountID &InLeftPlayerID)

		- OutInChatUID: EntityUID type. ChatChannel ID

		- OutInLeftPlayerID: AccountID type. Left Player ID


## ChatChannelKickPlayer Request
Kick player from the ChatChannel

1. Command interface

        Result ChatChannelKickPlayerCmd(const TransactionID &InTransactionID, const EntityUID &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- TransactionID: type:TransactionID, 

		- ChatUID: type:EntityUID, PartyUID

		- PlayerID: type:AccountID, PlayerID of the player

		- PlayerToKick: type:AccountID, Player To Kick

2. Result interface

C++: Cast message to ChatChannelKickPlayerRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## ChatChannelPlayerKickedS2CEvt
ChatChannel Player kicked message

        Result ChatChannelPlayerKickedS2CEvt(const EntityUID &InChatUID, const AccountID &InKickedPlayerID)

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInKickedPlayerID: AccountID type. Kicked player ID


## ChatChannelChatMessage Request
Chat channel sending chatting message

1. Command interface

        Result ChatChannelChatMessageCmd(const TransactionID &InTransactionID, const EntityUID &InChatUID, const VariableTable &InChatMetaData, const char* InChatMessage)

		- TransactionID: type:TransactionID, 

		- ChatUID: type:EntityUID, ChatChannel UID

		- ChatMetaData: type:VariableTable, Chat MetaData, player id and so on

		- ChatMessage: type:String, My message

2. Result interface

C++: Cast message to ChatChannelChatMessageRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## ChatChannelChatMessageS2CEvt
ChatChannel Chatting message event

        Result ChatChannelChatMessageS2CEvt(const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage)

		- OutInSenderID: PlayerID type. Sender PlayerID

		- OutInChatMetaData: VariableTable type. Chat MetaData, player id and so on

		- OutInChatMessage: String type. Message text


## WhisperMessage Request
Whisper(tell) other player chatting

1. Command interface

        Result WhisperMessageCmd(const TransactionID &InTransactionID, const PlayerID &InReceiverID, const char* InReceiverName, const VariableTable &InChatMetaData, const char* InChatMessage)

		- TransactionID: type:TransactionID, 

		- ReceiverID: type:PlayerID, Receiver ID

		- ReceiverName: type:String, Receiver name. Supporting character only for now

		- ChatMetaData: type:VariableTable, Chat MetaData, player id and so on

		- ChatMessage: type:String, My message

2. Result interface

C++: Cast message to WhisperMessageRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## WhisperMessageS2CEvt
Other player whispered(tell) to me message event

        Result WhisperMessageS2CEvt(const PlayerID &InSenderID, const VariableTable &InChatMetaData, const char* InChatMessage)

		- OutInSenderID: PlayerID type. Sender PlayerID

		- OutInChatMetaData: VariableTable type. Chat MetaData, player id and so on

		- OutInChatMessage: String type. Message text


## CreateCharacter Request
Create character

1. Command interface

        Result CreateCharacterCmd(const TransactionID &InTransactionID, const char* InCharacterName, const VariableTable &InPublicData, const VariableTable &InPrivateData)

		- TransactionID: type:TransactionID, 

		- CharacterName: type:String, 

		- PublicData: type:VariableTable, 

		- PrivateData: type:VariableTable, 

2. Result interface

C++: Cast message to CreateCharacterRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- CharacterID: type:CharacterID, Created character ID


## DeleteCharacter Request
Delete character

1. Command interface

        Result DeleteCharacterCmd(const TransactionID &InTransactionID, const CharacterID &InCharacterID)

		- TransactionID: type:TransactionID, 

		- CharacterID: type:CharacterID, Character ID to remove

2. Result interface

C++: Cast message to DeleteCharacterRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## GetCharacterList Request
Get character list

1. Command interface

        Result GetCharacterListCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to GetCharacterListRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Characters: type:VariableTable, Characters


## GetCharacterData Request


1. Command interface

        Result GetCharacterDataCmd(const TransactionID &InTransactionID, const CharacterID &InCharacterID)

		- TransactionID: type:TransactionID, 

		- CharacterID: type:CharacterID, Character ID to get

2. Result interface

C++: Cast message to GetCharacterDataRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PrivateData: type:VariableTable, Character private data
		- EquipData: type:VariableTable, Character equip data


## SelectCharacter Request
Select character

1. Command interface

        Result SelectCharacterCmd(const TransactionID &InTransactionID, const CharacterID &InCharacterID)

		- TransactionID: type:TransactionID, 

		- CharacterID: type:CharacterID, Character ID to select

2. Result interface

C++: Cast message to SelectCharacterRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- CharacterID: type:CharacterID, Selected Character ID
		- Attributes: type:VariableTable, Character attributes


## RequestServerNoticeUpdate Request
Request Server Notice. Sever will send ServerNoticeS2CEvt

1. Command interface

        Result RequestServerNoticeUpdateCmd(const TransactionID &InTransactionID)

		- TransactionID: type:TransactionID, 

2. Result interface

C++: Cast message to RequestServerNoticeUpdateRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## ServerNoticeS2CEvt
Server Notice updated event

        Result ServerNoticeS2CEvt(const int8_t &InNoticeCategory, const char* InServerNoticeMessage)

		- OutInNoticeCategory: int8 type. Notice category

		- OutInServerNoticeMessage: String type. ServerNotice message text


## CallFunction Request
To call general functionality

1. Command interface

        Result CallFunctionCmd(const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters)

		- TransactionID: type:TransactionID, 

		- FunctionName: type:StringCrc32, function name

		- Parameters: type:VariableTable, function parameter

2. Result interface

C++: Cast message to CallFunctionRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Results: type:VariableTable, function result








