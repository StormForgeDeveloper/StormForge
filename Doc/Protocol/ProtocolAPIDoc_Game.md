***
 
 CopyRight (c) 2021 StormForge
 
 Description : Game Message Protocol API Document

***



Game Server Protocol. Interface the game client can call to the server.

namespace SF::Message::Game


# Protocol interface class NetPolicyGame
## HeartbeatC2SEvt
Client heart bit

        Result HeartbeatC2SEvt()


## JoinGameServer Request
Player connected from a login server and moved to game server

1. Command interface

        Result JoinGameServerCmd(const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID)

		- OutInTransactionID: TransactionID type. 

		- OutInAccID: AccountID type. AccountID of the player

		- OutInTicket: AuthTicket type. Login session Ticket

		- OutInLoginEntityUID: uint64 type. Login entity ID which you would get from login server

2. Result interface

C++: Cast message to JoinGameServerRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutNickName: String type. Nickname of the player

		- OutGameUID: GameInsUID type. Game instance UID. If the player is in a game, this value will have player's game instance id

		- OutPartyUID: PartyUID type. PartyUID. If the player is in a party

		- OutPartyLeaderID: AccountID type. PlayerID, for now, PlayerID is same to AccountID

		- OutMatchingTicket: MatchingQueueTicket type. Matching queue ticket


## GetComplitionState Request
player complition statues

1. Command interface

        Result GetComplitionStateCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetComplitionStateRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutComplitionState: String type. Complition state string


## SetComplitionState Request
Player complition state

1. Command interface

        Result SetComplitionStateCmd(const uint64_t &InTransactionID, const char* InComplitionState)

		- OutInTransactionID: TransactionID type. 

		- OutInComplitionState: String type. Complition state to set

2. Result interface

C++: Cast message to SetComplitionStateRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## RegisterGCM Request
Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time

1. Command interface

        Result RegisterGCMCmd(const uint64_t &InTransactionID, const char* InGCMRegisteredID)

		- OutInTransactionID: TransactionID type. 

		- OutInGCMRegisteredID: String type. Google notification ID

2. Result interface

C++: Cast message to RegisterGCMRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## UnregisterGCM Request
Unregister Google notification service ID

1. Command interface

        Result UnregisterGCMCmd(const uint64_t &InTransactionID, const char* InGCMRegisteredID)

		- OutInTransactionID: TransactionID type. 

		- OutInGCMRegisteredID: String type. ID to unregister

2. Result interface

C++: Cast message to UnregisterGCMRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## InviteFriend Request
Invite friend

1. Command interface

        Result InviteFriendCmd(const uint64_t &InTransactionID, const AccountID &InFriendID)

		- OutInTransactionID: TransactionID type. 

		- OutInFriendID: AccountID type. PlayerID to invite

2. Result interface

C++: Cast message to InviteFriendRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## AcceptFriendRequest Request
Accept friend request

1. Command interface

        Result AcceptFriendRequestCmd(const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID)

		- OutInTransactionID: TransactionID type. 

		- OutInInviterID: AccountID type. Inviter PlayerID

		- OutInInviterFacebookUID: FacebookUID type. Inviter player ID

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

        Result RemoveFriendCmd(const uint64_t &InTransactionID, const AccountID &InFriendID)

		- OutInTransactionID: TransactionID type. 

		- OutInFriendID: AccountID type. Friend player ID

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

        Result GetFriendListCmd(const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount)

		- OutInTransactionID: TransactionID type. 

		- OutInStartIndex: uint16 type. Friend list start index

		- OutInCount: uint16 type. Maximum friend list to query

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

        Result GetNotificationListCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetNotificationListRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## DeleteNotification Request
Delete notification

1. Command interface

        Result DeleteNotificationCmd(const uint64_t &InTransactionID, const uint32_t &InNotificationID)

		- OutInTransactionID: TransactionID type. 

		- OutInNotificationID: uint32 type. Notification ID to delete

2. Result interface

C++: Cast message to DeleteNotificationRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutNotificationID: uint32 type. Deleted Notification ID


## SetNotificationRead Request
Set notification is read

1. Command interface

        Result SetNotificationReadCmd(const uint64_t &InTransactionID, const uint32_t &InNotificationID)

		- OutInTransactionID: TransactionID type. 

		- OutInNotificationID: uint32 type. Notification ID to set read

2. Result interface

C++: Cast message to SetNotificationReadRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutNotificationID: uint32 type. Notification ID to set read


## AcceptNotification Request
Accept notification

1. Command interface

        Result AcceptNotificationCmd(const uint64_t &InTransactionID, const uint32_t &InNotificationID)

		- OutInTransactionID: TransactionID type. 

		- OutInNotificationID: uint32 type. Notification ID to accept

2. Result interface

C++: Cast message to AcceptNotificationRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutNotificationID: uint32 type. Accepted Notification ID


## NotifyS2CEvt
Notify new notification

        Result NotifyS2CEvt(const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp)

		- OutInNotificationID: uint32 type. Notification ID

		- OutInNotificationType: uint32 type. Notification type

		- OutInMessageParam0: uint64 type. Message parameter 0

		- OutInMessageParam1: uint64 type. Message parameter 1

		- OutInMessageText: String type. Message text

		- OutInIsRead: uint8 type. Notification is read?

		- OutInTimeStamp: uint64 type. Issued UTC sec


## FindPlayerByEMail Request
Query playerID list

1. Command interface

        Result FindPlayerByEMailCmd(const uint64_t &InTransactionID, const char* InPlayerEMail)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayerEMail: String type. Player email to find

2. Result interface

C++: Cast message to FindPlayerByEMailRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPlayer: PlayerInformation type. Player information if found


## FindPlayerByPlayerID Request
Query playerID list

1. Command interface

        Result FindPlayerByPlayerIDCmd(const uint64_t &InTransactionID, const AccountID &InPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayerID: AccountID type. Player ID to find

2. Result interface

C++: Cast message to FindPlayerByPlayerIDRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPlayer: PlayerInformation type. Player information if found


## RequestPlayerStatusUpdate Request
*Request Player Status Update

1. Command interface

        Result RequestPlayerStatusUpdateCmd(const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInTargetPlayerID: AccountID type. PlayerIDs to request

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
Get Ranking lise

1. Command interface

        Result GetRankingListCmd(const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount)

		- OutInTransactionID: TransactionID type. 

		- OutInRankingType: uint8 type. 

		- OutInBaseRanking: uint8 type. Base ranking to query, 0 based ranking order

		- OutInCount: uint8 type. Number of playerinformation to query

2. Result interface

C++: Cast message to GetRankingListRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutRanking: TotalRankingPlayerInformation type. 


## GetUserGamePlayerInfo Request
Game user game play information

1. Command interface

        Result GetUserGamePlayerInfoCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetUserGamePlayerInfoRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutAttributes: VariableTable type. 


## GetGamePlayerInfo Request
Game game play information

1. Command interface

        Result GetGamePlayerInfoCmd(const uint64_t &InTransactionID, const AccountID &InPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayerID: AccountID type. Game playerID to get

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

        Result SetNickNameCmd(const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree)

		- OutInTransactionID: TransactionID type. 

		- OutInNickName: String type. Nickname to change

		- OutInIsCostFree: uint8 type. CostFree

2. Result interface

C++: Cast message to SetNickNameRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutTotalGem: uint64 type. Total after cost is consumed

		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## CreateParty Request
Create Party

1. Command interface

        Result CreatePartyCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to CreatePartyRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPartyUID: PartyUID type. Created Party UID


## JoinParty Request
Join party

1. Command interface

        Result JoinPartyCmd(const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID)

		- OutInTransactionID: TransactionID type. 

		- OutInPartyUID: PartyUID type. Party ID to join

		- OutInInviterID: AccountID type. Party inviter ID

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

        Result LeavePartyCmd(const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInPartyUID: PartyUID type. PartyID to leave

		- OutInPlayerID: AccountID type. Player ID to leave

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

        Result PartyKickPlayerCmd(const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- OutInTransactionID: TransactionID type. 

		- OutInPartyUID: PartyUID type. PartyUID

		- OutInPlayerID: AccountID type. PlayerID of the player

		- OutInPlayerToKick: AccountID type. Player To Kick

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

        Result PartyInviteCmd(const uint64_t &InTransactionID, const AccountID &InInviteTargetID)

		- OutInTransactionID: TransactionID type. 

		- OutInInviteTargetID: AccountID type. Invite target player ID

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

        Result PartyQuickChatMessageCmd(const uint64_t &InTransactionID, const uint32_t &InQuickChatID)

		- OutInTransactionID: TransactionID type. 

		- OutInQuickChatID: uint32 type. My quick chat message ID

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

        Result PartyChatMessageCmd(const uint64_t &InTransactionID, const char* InChatMessage)

		- OutInTransactionID: TransactionID type. 

		- OutInChatMessage: String type. My message

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

        Result JoinGameInstanceCmd(const uint64_t &InTransactionID, const uint64_t &InInsUID)

		- OutInTransactionID: TransactionID type. 

		- OutInInsUID: GameInsUID type. Game instance ID to join

2. Result interface

C++: Cast message to JoinGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutInsUID: GameInsUID type. Game instance ID

		- OutServerAddress: NetAddress type. Game instance address

		- OutServerAddress4: NetAddress type. Game instance address


## LeaveGameInstance Request
Leave game instance

1. Command interface

        Result LeaveGameInstanceCmd(const uint64_t &InTransactionID, const uint64_t &InInsUID)

		- OutInTransactionID: TransactionID type. 

		- OutInInsUID: GameInsUID type. Game instance ID to join

2. Result interface

C++: Cast message to LeaveGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## SearchGameInstance Request
Search game instance

1. Command interface

        Result SearchGameInstanceCmd(const uint64_t &InTransactionID, const char* InSearchKeyword)

		- OutInTransactionID: TransactionID type. 

		- OutInSearchKeyword: String type. Search keyword

2. Result interface

C++: Cast message to SearchGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutGameInstances: GameInstanceInfo type. Game instance informations


## GetCharacterDataInGameInstance Request
Search game instance

1. Command interface

        Result GetCharacterDataInGameInstanceCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id to get

2. Result interface

C++: Cast message to GetCharacterDataInGameInstanceRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPlayerID: PlayerID type. Player Movement

		- OutGameInstances: VariableTable type. Game instance ID


## JoinGame Request
Join to a game

1. Command interface

        Result JoinGameCmd(const uint64_t &InTransactionID, const AccountID &InPlayerID, const AuthTicket &InTicket, const uint64_t &InInsUID)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayerID: AccountID type. Player ID of the player

		- OutInTicket: AuthTicket type. Login session ID

		- OutInInsUID: GameInsUID type. Game instance ID to join

2. Result interface

C++: Cast message to JoinGameRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutInsUID: GameInsUID type. Game instance ID

		- OutTimeStamp: uint32 type. Time stamp in UTC

		- OutGameState: GameStateID type. Game state

		- OutDay: uint8 type. Game Day

		- OutMaxPlayer: uint8 type. Max player of the game

		- OutPlayerIndex: uint8 type. Player index in the game

		- OutPlayerCharacter: uint8 type. Player character in the game

		- OutRole: uint8 type. Role of the player

		- OutDead: uint8 type. TRUE if the player is dead

		- OutChatHistoryData: uint8 type. Game chatting history

		- OutGameLogData: uint8 type. Game history log


## PlayerJoinedS2CEvt
Player Joined in the game

        Result PlayerJoinedS2CEvt(const uint64_t &InGameInsUID, const PlayerInformation &InJoinedPlayer)

		- OutInGameInsUID: GameInsUID type. Game instance UID

		- OutInJoinedPlayer: PlayerInformation type. Joined player information


## LeaveGame Request
Leave Game

1. Command interface

        Result LeaveGameCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Game instance ID to leave

		- OutInPlayerID: AccountID type. Player id of the player

		- OutInTicket: AuthTicket type. Login session ID of the player

2. Result interface

C++: Cast message to LeaveGameRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## PlayerLeftS2CEvt
Player left event

        Result PlayerLeftS2CEvt(const uint64_t &InGameInsUID, const AccountID &InLeftPlayerID)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInLeftPlayerID: AccountID type. Left player ID


## KickPlayer Request
Kick player

1. Command interface

        Result KickPlayerCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInPlayerID: AccountID type. PlayerID of the player

		- OutInPlayerToKick: AccountID type. Player ID to kick from the game

2. Result interface

C++: Cast message to KickPlayerRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## PlayerKickedS2CEvt
Player kicked

        Result PlayerKickedS2CEvt(const uint64_t &InGameInsUID, const AccountID &InKickedPlayerID)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInKickedPlayerID: AccountID type. Kicked player ID


## AssignRole Request
Assign role + Game state reset

1. Command interface

        Result AssignRoleCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInPlayerID: AccountID type. PlayerID of the player

		- OutInTicket: AuthTicket type. Login sessionID of the player

2. Result interface

C++: Cast message to AssignRoleRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## RoleAssignedS2CEvt
Role assigned event

        Result RoleAssignedS2CEvt(const uint64_t &InGameInsUID, const AccountID &InPlayerID, const uint8_t &InRole)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInPlayerID: AccountID type. Player id of the player

		- OutInRole: uint8 type. Role of the player


## ChatMessage Request
Send chatting message to the game

1. Command interface

        Result ChatMessageCmd(const uint64_t &InTransactionID, const char* InChatMessage, const uint8_t &InRole)

		- OutInTransactionID: TransactionID type. 

		- OutInChatMessage: String type. chatting message

		- OutInRole: uint8 type. Role of the player

2. Result interface

C++: Cast message to ChatMessageRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## ChatMessageS2CEvt
Chatting message event 

        Result ChatMessageS2CEvt(const AccountID &InSenderID, const uint8_t &InRole, const char* InSenderName, const char* InChatMessage)

		- OutInSenderID: AccountID type. sender player ID

		- OutInRole: uint8 type. Role of the sender

		- OutInSenderName: String type. NickName of the player

		- OutInChatMessage: String type. Chatting message


## AdvanceGame Request
Advance game

1. Command interface

        Result AdvanceGameCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Advance game state

		- OutInPlayerID: AccountID type. Player id of the player

		- OutInTicket: AuthTicket type. Login session ID of the player

2. Result interface

C++: Cast message to AdvanceGameRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## GameAdvancedS2CEvt
The game state is advanced

        Result GameAdvancedS2CEvt(const uint64_t &InGameInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInTimeStamp: uint32 type. Time stamp in UTC

		- OutInGameState: GameStateID type. Game state ID

		- OutInDay: uint8 type. Day of the game


## GameEndedS2CEvt
Game is ended

        Result GameEndedS2CEvt(const uint64_t &InGameInsUID, const uint8_t &InWinner, const uint32_t &InGainedExp, const uint32_t &InGainedGameMoney)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInWinner: GameWinner type. Winner of the game

		- OutInGainedExp: uint32 type. Gained Experience of the game

		- OutInGainedGameMoney: uint32 type. Gained game money


## VoteGameAdvance Request
Vote game advance

1. Command interface

        Result VoteGameAdvanceCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInPlayerID: AccountID type. PlayerID of the player

		- OutInTicket: AuthTicket type. Login session ID of the player

2. Result interface

C++: Cast message to VoteGameAdvanceRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## GameAdvanceVotedS2CEvt
GameAdvance is Voted

        Result GameAdvanceVotedS2CEvt(const uint64_t &InGameInsUID, const AccountID &InVoter)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInVoter: AccountID type. Voter id


## Vote Request
Vote

1. Command interface

        Result VoteCmd(const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const AccountID &InPlayerID, const AuthTicket &InTicket, const AccountID &InVoteTarget, const uint32_t &InActionSerial)

		- OutInTransactionID: TransactionID type. 

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInPlayerID: AccountID type. PlayerID of the player

		- OutInTicket: AuthTicket type. Login session ID of the player

		- OutInVoteTarget: AccountID type. Vote Target

		- OutInActionSerial: uint32 type. Action serial, used for player voting order

2. Result interface

C++: Cast message to VoteRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## VotedS2CEvt
Player Voted

        Result VotedS2CEvt(const uint64_t &InGameInsUID, const AccountID &InVoter, const AccountID &InVotedTarget)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInVoter: AccountID type. Voter ID

		- OutInVotedTarget: AccountID type. Voted player ID


## VoteEndS2CEvt
Vote is ended

        Result VoteEndS2CEvt(const uint64_t &InGameInsUID, const Array<AccountID>& InVoted)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInVoted: AccountID type. Selected player list


## PlayerKilledS2CEvt
Player Killed

        Result PlayerKilledS2CEvt(const uint64_t &InGameInsUID, const AccountID &InKilledPlayer, const uint8_t &InReason)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInKilledPlayer: AccountID type. Killed Player ID

		- OutInReason: PlayerKilledReason type. Player killed reason


## PlayerRevealedS2CEvt
Player Voted

        Result PlayerRevealedS2CEvt(const uint64_t &InGameInsUID, const AccountID &InRevealedPlayerID, const uint8_t &InRole, const uint8_t &InReason)

		- OutInGameInsUID: GameInsUID type. Game instance ID

		- OutInRevealedPlayerID: AccountID type. Revealed player ID

		- OutInRole: uint8 type. Role player role

		- OutInReason: PlayerRevealedReason type. Rlayer revealed reason


## GamePlayAgain Request
Play again with the current players

1. Command interface

        Result GamePlayAgainCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GamePlayAgainRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutTotalGem: uint64 type. Total after cost is consumed

		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## GamePlayAgainS2CEvt
Somebody pressed play again. Only one of PartyUID and GameInsUID can have a value

        Result GamePlayAgainS2CEvt(const uint64_t &InPartyUID, const AccountID &InLeadPlayer)

		- OutInPartyUID: PartyUID type. Party ID

		- OutInLeadPlayer: AccountID type. Player who pressed replay


## GameRevealPlayer Request
Player. reveal a player

1. Command interface

        Result GameRevealPlayerCmd(const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInTargetPlayerID: AccountID type. 

2. Result interface

C++: Cast message to GameRevealPlayerRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutRevealedPlayerID: AccountID type. 

		- OutRevealedRole: uint8 type. 

		- OutTotalGem: uint64 type. Total after cost is consumed

		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## GamePlayerRevive Request
Player. revive himself

1. Command interface

        Result GamePlayerReviveCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GamePlayerReviveRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutTotalGem: uint64 type. Total after cost is consumed

		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## GamePlayerRevivedS2CEvt
Player is revived

        Result GamePlayerRevivedS2CEvt(const AccountID &InRevivedPlayerID)

		- OutInRevivedPlayerID: AccountID type. Player who is revived


## GamePlayerResetRank Request
Player. reset ranking

1. Command interface

        Result GamePlayerResetRankCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GamePlayerResetRankRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutTotalGem: uint64 type. Total after cost is consumed

		- OutTotalGameMoney: uint64 type. Total after cost is consumed


## RequestGameMatch Request
Request Game match

1. Command interface

        Result RequestGameMatchCmd(const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole)

		- OutInTransactionID: TransactionID type. 

		- OutInNumPlayer: uint8 type. Request game match

		- OutInRequestRole: uint8 type. Request special role

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

        Result CancelGameMatchCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to CancelGameMatchRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## GameMatchingCanceledS2CEvt
game matching canceled

        Result GameMatchingCanceledS2CEvt()


## BuyShopItemPrepare Request
Buy shop item prepare

1. Command interface

        Result BuyShopItemPrepareCmd(const uint64_t &InTransactionID, const uint32_t &InShopItemID)

		- OutInTransactionID: TransactionID type. 

		- OutInShopItemID: uint32 type. Shop table id

2. Result interface

C++: Cast message to BuyShopItemPrepareRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutShopItemID: uint32 type. Shop table id

		- OutPurchaseID: String type. Purchase ID


## BuyShopItem Request
Buy shop item

1. Command interface

        Result BuyShopItemCmd(const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken)

		- OutInTransactionID: TransactionID type. 

		- OutInShopItemID: uint32 type. Shop table id

		- OutInPlatform: String type. 

		- OutInPackageName: String type. 

		- OutInPurchaseTransactionID: String type. IOS transaction ID

		- OutInPurchaseToken: uint8 type. 

2. Result interface

C++: Cast message to BuyShopItemRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutShopItemID: uint32 type. Shop table id


## CreateOrJoinChatChannel Request
Create or Join Chat channel

1. Command interface

        Result CreateOrJoinChatChannelCmd(const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode)

		- OutInTransactionID: TransactionID type. 

		- OutInChannelName: String type. 

		- OutInPasscode: String type. 

2. Result interface

C++: Cast message to CreateOrJoinChatChannelRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutChatUID: EntityUID type. Created/Joined Chat channel UID


## JoinChatChannel Request
Join

1. Command interface

        Result JoinChatChannelCmd(const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID)

		- OutInTransactionID: TransactionID type. 

		- OutInChatUID: EntityUID type. ChatChannel UID to join

		- OutInInviterID: AccountID type. Party inviter ID

2. Result interface

C++: Cast message to JoinChatChannelRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPartyUID: EntityUID type. ChatChannel UID

		- OutPartyLeaderID: AccountID type. Party leader ID


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

        Result LeaveChatChannelCmd(const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID)

		- OutInTransactionID: TransactionID type. 

		- OutInChatUID: EntityUID type. ChatChannel to leave

		- OutInPlayerID: AccountID type. Player ID to leave

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

        Result ChatChannelKickPlayerCmd(const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick)

		- OutInTransactionID: TransactionID type. 

		- OutInChatUID: EntityUID type. PartyUID

		- OutInPlayerID: AccountID type. PlayerID of the player

		- OutInPlayerToKick: AccountID type. Player To Kick

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
Party chatting

1. Command interface

        Result ChatChannelChatMessageCmd(const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage)

		- OutInTransactionID: TransactionID type. 

		- OutInChatUID: EntityUID type. ChatChannel UID

		- OutInChatMessage: String type. My message

2. Result interface

C++: Cast message to ChatChannelChatMessageRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## ChatChannelChatMessageS2CEvt
ChatChannel Chatting message event

        Result ChatChannelChatMessageS2CEvt(const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage)

		- OutInSenderID: AccountID type. Message sender

		- OutInSenderName: String type. Message sender name

		- OutInChatMessage: String type. Message text


## CreateCharacter Request
Create character

1. Command interface

        Result CreateCharacterCmd(const uint64_t &InTransactionID, const char* InCharacterName, const Array<uint8_t>& InAttributes)

		- OutInTransactionID: TransactionID type. 

		- OutInCharacterName: String type. 

		- OutInAttributes: VariableTable type. 

2. Result interface

C++: Cast message to CreateCharacterRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutCharacterID: int32 type. Created character ID


## RemoveCharacter Request
Remove character

1. Command interface

        Result RemoveCharacterCmd(const uint64_t &InTransactionID, const int32_t &InCharacterID)

		- OutInTransactionID: TransactionID type. 

		- OutInCharacterID: int32 type. Character ID to remove

2. Result interface

C++: Cast message to RemoveCharacterRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## GetCharacterList Request
Get character list

1. Command interface

        Result GetCharacterListCmd(const uint64_t &InTransactionID)

		- OutInTransactionID: TransactionID type. 

2. Result interface

C++: Cast message to GetCharacterListRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutCharacterIDs: int32 type. Character id list


## GetCharacterData Request


1. Command interface

        Result GetCharacterDataCmd(const uint64_t &InTransactionID, const int32_t &InCharacterID, const Array<const char*>& InAttributeNames)

		- OutInTransactionID: TransactionID type. 

		- OutInCharacterID: int32 type. Character ID to get

		- OutInAttributeNames: String type. attribute names to query

2. Result interface

C++: Cast message to GetCharacterDataRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutAttributes: VariableTable type. Character attributes


## GiveStamina Request
Give my stamina to other player

1. Command interface

        Result GiveStaminaCmd(const uint64_t &InTransactionID, const AccountID &InTargetPlayer)

		- OutInTransactionID: TransactionID type. 

		- OutInTargetPlayer: AccountID type. Player ID to give

2. Result interface

C++: Cast message to GiveStaminaRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutTargetPlayer: AccountID type. Player ID to give

		- OutTimeStamp: uint64 type. Time since stamina sent


## SetPresetGameConfigID Request
For debug, Change configue preset

1. Command interface

        Result SetPresetGameConfigIDCmd(const uint64_t &InTransactionID, const uint32_t &InPresetID)

		- OutInTransactionID: TransactionID type. 

		- OutInPresetID: uint32 type. Configuation preset id

2. Result interface

C++: Cast message to SetPresetGameConfigIDRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 








