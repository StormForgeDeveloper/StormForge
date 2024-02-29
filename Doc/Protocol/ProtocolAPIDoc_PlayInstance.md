***
 
 CopyRight (c) 2024 StormForge
 
 Description : PlayInstance Message Protocol API Document

***



PlayInstance Protocol

namespace SF::Message::PlayInstance


# Protocol interface class NetPolicyPlayInstance
## JoinPlayInstance Request
Player Join request.

1. Command interface

        Result JoinPlayInstanceCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance to join

		- OutPlayerID: PlayerID type. Joining player id

		- OutPlayerIdentifier: String type. Joining player identifier. string value

2. Result interface

C++: Cast message to JoinPlayInstanceRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayInstanceUID: EntityUID type. joined Play instance ID
		- OutPlayerID: PlayerID type. Joined player id for validation
		- OutCharacterID: CharacterID type. Joined player's character id for validation
		- OutCharacterPrivateData: VariableTable type.  character private data
		- OutMovement: ActorMovement type. Start movement


## PlayerKickedS2CEvt
Player kicked event. this event will be broadcasted when a player kicked.

        Result PlayerKickedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInKickedPlayerID: PlayerID type. Kicked player ID


## PlayPacketC2SEvt
Play packet

        Result PlayPacketC2SEvt(const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInSenderEndpointID: uint32 type. Sender player ID

		- OutInTargetEndpointMask: uint32 type. Target Play mask.

		- OutInPayload: uint8 type. Payload data


## NewActorInViewS2CEvt
New actor in get view

        Result NewActorInViewS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Joined Player Id

		- OutInPlayerPlatformId: PlayerPlatformID type. Joined Player platform id

		- OutInPublicData: VariableTable type. Character public data

		- OutInEquipData: VariableTable type. Character Equip data

		- OutInMovement: ActorMovement type. Actor movement of the character. This one has actor id inside

		- OutInState: StringCrc32 type. StateId actor state.

		- OutInStateValues: VariableTable type. State values


## RemoveActorFromViewS2CEvt
Remove actor from view

        Result RemoveActorFromViewS2CEvt(const uint64_t &InPlayInstanceUID, const uint32_t &InActorID)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInActorID: uint32 type. Removed actor Id


## PlayerMovementC2SEvt
Player Movement

        Result PlayerMovementC2SEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInMovement: ActorMovement type. Movement attributes


## ActorMovementS2CEvt
Player Movement

        Result ActorMovementS2CEvt(const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInMovement: ActorMovement type. Movement attributes


## ActorMovementsS2CEvt
Player Movement

        Result ActorMovementsS2CEvt(const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInMovement: ActorMovement type. Movement attributes


## PlayerStateChangedS2CEvt
Player state change

        Result PlayerStateChangedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInState: StringCrc32 type. StateId actor state.

		- OutInMoveFrame: uint32 type. Movement frame state change has happened

		- OutInPosition: Vector4 type. Position of the player when state change happened

		- OutInStateValues: VariableTable type. State change values


## ClientSyncReliableC2SEvt
Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet

        Result ClientSyncReliableC2SEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInSyncData: VariableTable type. sync data


## ClientSyncC2SEvt
Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet

        Result ClientSyncC2SEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInSyncData: VariableTable type. sync data


## SetCharacterPublicMessage Request
Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well

1. Command interface

        Result SetCharacterPublicMessageCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id

		- OutPublicMessage: String type. Public message to set.

2. Result interface

C++: Cast message to SetCharacterPublicMessageRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## CharacterPrivateDataChangedS2CEvt
Character's private data has changed

        Result CharacterPrivateDataChangedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InCharacterID, const Array<uint8_t>& InPrivateData)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInCharacterID: uint32 type. Character Id

		- OutInPrivateData: VariableTable type. Character private data


## CharacterPublicDataChangedS2CEvt
Player public data has been changed

        Result CharacterPublicDataChangedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInPublicData: VariableTable type. Character public data


## RequestWhiteboardSharing Request
Request WhiteboardSharing

1. Command interface

        Result RequestWhiteboardSharingCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance

		- OutPlayerID: PlayerID type. My Player id

		- OutTargetPlayerID: PlayerID type. Target Player id

		- OutWhiteboardInfo: VariableTable type. Whiteboard information

2. Result interface

C++: Cast message to RequestWhiteboardSharingRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## AcceptWhiteboardSharing Request
Accept WhiteboardSharing

1. Command interface

        Result AcceptWhiteboardSharingCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance

		- OutPlayerID: PlayerID type. Player id

		- OutRequestedPlayerID: PlayerID type. Requested Player id

		- OutAnswer: uint8 type. true: accept, false: reject

2. Result interface

C++: Cast message to AcceptWhiteboardSharingRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## CloseWhiteboardSharing Request
Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed

1. Command interface

        Result CloseWhiteboardSharingCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance

		- OutPlayerID: PlayerID type. Player id

2. Result interface

C++: Cast message to CloseWhiteboardSharingRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## AddWhiteboardSharingLogEntry Request
Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded

1. Command interface

        Result AddWhiteboardSharingLogEntryCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance

		- OutPlayerID: PlayerID type. Player id

		- OutLogEntry: VariableTable type. Log entry

2. Result interface

C++: Cast message to AddWhiteboardSharingLogEntryRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutLogEntryID: LogEntryID type. Log entry Id, you also receive it by event. LogEntryID


## UpdateWhiteboardSharingLogEntry Request
Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded

1. Command interface

        Result UpdateWhiteboardSharingLogEntryCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance

		- OutPlayerID: PlayerID type. Player id

		- OutLogEntry: VariableTable type. Log entry, LogEntryID should be included

2. Result interface

C++: Cast message to UpdateWhiteboardSharingLogEntryRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## RemoveWhiteboardSharingLogEntry Request
Update whiteboard log entry

1. Command interface

        Result RemoveWhiteboardSharingLogEntryCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance

		- OutPlayerID: PlayerID type. Player id

		- OutLogEntryID: LogEntryID type. Log entry Id, you received it by event. Removed log entry id

2. Result interface

C++: Cast message to RemoveWhiteboardSharingLogEntryRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## WhiteboardSharingRequestedS2CEvt
WhiteboardSharing has been requested

        Result WhiteboardSharingRequestedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInRequestedPlayerID: PlayerID type. Player id who requested


## WhiteboardSharingRejectedS2CEvt
WhiteboardSharing has been requested

        Result WhiteboardSharingRejectedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id to receive

		- OutInRejectedPlayerID: PlayerID type. Player id who rejected


## WhiteboardSharingStartedS2CEvt
WhiteboardSharing has been started

        Result WhiteboardSharingStartedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInOtherPlayerID: PlayerID type. the other player id

		- OutInWhiteboardInfo: VariableTable type. Whiteboard information


## WhiteboardSharingHasClosedS2CEvt
WhiteboardSharing has been closed

        Result WhiteboardSharingHasClosedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInClosedPlayerID: PlayerID type. Player id who requested close


## WhiteboardSharingNewLogEntryAddedS2CEvt
WhiteboardSharing new log entry has been added

        Result WhiteboardSharingNewLogEntryAddedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. target player id

		- OutInLogEntry: VariableTable type. Log entry data. It should have new 'LogEntryID'


## WhiteboardSharingNewLogEntryRemovedS2CEvt
WhiteboardSharing new log entry has been removed

        Result WhiteboardSharingNewLogEntryRemovedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. target player id

		- OutInLogEntryID: LogEntryID type. Log entry id


## WhiteboardSharingNewLogEntryUpdatedS2CEvt
WhiteboardSharing new log entry has been updated

        Result WhiteboardSharingNewLogEntryUpdatedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. target player id

		- OutInLogEntry: VariableTable type. Log entry


## OccupyMapObject Request
Occupy map object

1. Command interface

        Result OccupyMapObjectCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id

		- OutMapObjectId: uint32 type. MapObjectId

		- OutUsageId: uint32 type. MapObjectOccupyMode 

2. Result interface

C++: Cast message to OccupyMapObjectRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayInstanceUID: EntityUID type. Play instance ID
		- OutPlayerID: PlayerID type. player id for validation
		- OutMapObjectId: uint32 type. MapObjectId


## UnoccupyMapObject Request
Unoccupy map object

1. Command interface

        Result UnoccupyMapObjectCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id

		- OutMapObjectId: uint32 type. MapObjectId

2. Result interface

C++: Cast message to UnoccupyMapObjectRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayInstanceUID: EntityUID type. Play instance ID
		- OutPlayerID: PlayerID type. player id for validation
		- OutMapObjectId: uint32 type. MapObjectId


## UseMapObject Request
Use map object

1. Command interface

        Result UseMapObjectCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id

		- OutMapObjectId: StringCrc32 type. MapObjectId

		- OutUseParameters: VariableTable type. use parameters

2. Result interface

C++: Cast message to UseMapObjectRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayInstanceUID: EntityUID type. Play instance ID
		- OutPlayerID: PlayerID type. player id for validation
		- OutMapObjectId: StringCrc32 type. MapObjectId
		- OutResultAttributes: VariableTable type. Use result attributes


## ZoneChat Request
Send zone chatting

1. Command interface

        Result ZoneChatCmd(const TransactionID &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: GameInsUID type. Play instance ID

		- OutPlayerID: PlayerID type. Sender PlayerID

		- OutMessageType: int8 type. chatting message type

		- OutChatMetaData: VariableTable type. Chat meta data, player id and so on

		- OutChatMessage: String type. Message to send

2. Result interface

C++: Cast message to ZoneChatRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## ZoneChatS2CEvt
Player state change

        Result ZoneChatS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInSenderID: PlayerID type. Sender PlayerID

		- OutInMessageType: int8 type. chatting message type

		- OutInChatMetaData: VariableTable type. Chat meta data, player id

		- OutInChatMessage: String type. Message to send


## LevelUpS2CEvt
Effect modifier initial sync

        Result LevelUpS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInCurrentExp: int64 type. Current experience

		- OutInCurrentLevel: int type. Current level


## CallFunction Request
To call general functionality

1. Command interface

        Result CallFunctionCmd(const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters)

		- OutTransactionID: TransactionID type. 

		- OutFunctionName: StringCrc32 type. function name

		- OutPlayerID: PlayerID type. Caller player Id

		- OutParameters: VariableTable type. function parameter

2. Result interface

C++: Cast message to CallFunctionRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutResults: VariableTable type. function result


## SendVoiceDataC2SEvt
Send coded voice data to server

        Result SendVoiceDataC2SEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. player id

		- OutInFrameIndex: uint16 type. voice frame index

		- OutInVoiceData: uint8 type. Voice data


## VoiceDataS2CEvt
Voice data

        Result VoiceDataS2CEvt(const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData)

		- OutInActorID: uint32 type. actor id

		- OutInFrameIndex: uint16 type. voice frame index

		- OutInVoiceData: uint8 type. Voice data


## CreateStream Request
Create stream instance

1. Command interface

        Result CreateStreamCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- OutTransactionID: TransactionID type. 

		- OutTicket: AuthTicket type. Login session Ticket

		- OutStreamName: String type. Stream name

2. Result interface

C++: Cast message to CreateStreamRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutStreamName: String type. Stream name


## FindStream Request
Open stream instance

1. Command interface

        Result FindStreamCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- OutTransactionID: TransactionID type. 

		- OutTicket: AuthTicket type. Login session Ticket

		- OutStreamName: String type. Stream name

2. Result interface

C++: Cast message to FindStreamRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutStreamName: String type. Stream name


## DeleteStream Request
Delete stream instance

1. Command interface

        Result DeleteStreamCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- OutTransactionID: TransactionID type. 

		- OutTicket: AuthTicket type. Login session Ticket

		- OutStreamName: String type. stream name to delete

2. Result interface

C++: Cast message to DeleteStreamRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutStreamName: String type. Stream name


## GetStreamList Request
Get stream list

1. Command interface

        Result GetStreamListCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket)

		- OutTransactionID: TransactionID type. 

		- OutTicket: AuthTicket type. Login session Ticket

2. Result interface

C++: Cast message to GetStreamListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutStreamNames: String type. Stream names








