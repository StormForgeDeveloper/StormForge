***
 
 CopyRight (c) 2025 StormForge
 
 Description : PlayInstance Message Protocol API Document

***



PlayInstance Protocol

namespace SF::Message::PlayInstance


# Protocol interface class PlayInstanceRPCSendAdapter
## JoinPlayInstance Request
Player Join request.

1. Command interface

        Result JoinPlayInstanceCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier, const uint32_t &InCustomZoneDataVersion)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance to join

		- PlayerID: type:PlayerID, Joining player id

		- PlayerIdentifier: type:String, Joining player identifier. string value

		- CustomZoneDataVersion: type:uint32, Custom zone data version the client has

2. Result interface

C++: Cast message to JoinPlayInstanceRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayInstanceUID: type:EntityUID, joined Play instance ID
		- PlayerID: type:PlayerID, Joined player id for validation
		- CharacterID: type:CharacterID, Joined player's character id for validation
		- CharacterPrivateData: type:VariableTable,  character private data
		- Movement: type:ActorMovement, Start movement


## PlayerKickedS2CEvt
Player kicked event. this event will be broadcasted when a player kicked.

        Result PlayerKickedS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InKickedPlayerID)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInKickedPlayerID: PlayerID type. Kicked player ID


## PlayPacketC2SEvt
Play packet

        Result PlayPacketC2SEvt(const GameInstanceUID &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInSenderEndpointID: uint32 type. Sender player ID

		- OutInTargetEndpointMask: uint32 type. Target Play mask.

		- OutInPayload: uint8 type. Payload data


## NewActorInViewS2CEvt
New actor in get view

        Result NewActorInViewS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const Array<uint8_t>& InPublicData, const Array<uint8_t>& InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Joined Player Id

		- OutInPlayerPlatformId: PlayerPlatformID type. Joined Player platform id

		- OutInPublicData: VariableTable type. Character public data

		- OutInEquipData: VariableTable type. Character Equip data

		- OutInMovement: ActorMovement type. Actor movement of the character. This one has actor id inside

		- OutInState: StringCrc32 type. StateId actor state.

		- OutInStateValues: VariableTable type. State values


## RemoveActorFromViewS2CEvt
Remove actor from view

        Result RemoveActorFromViewS2CEvt(const GameInstanceUID &InPlayInstanceUID, const uint32_t &InActorID)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInActorID: uint32 type. Removed actor Id


## PlayerMovementC2SEvt
Player Movement

        Result PlayerMovementC2SEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInMovement: ActorMovement type. Movement attributes


## ActorMovementS2CEvt
Player Movement

        Result ActorMovementS2CEvt(const GameInstanceUID &InPlayInstanceUID, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInMovement: ActorMovement type. Movement attributes


## ActorMovementsS2CEvt
Player Movement

        Result ActorMovementsS2CEvt(const GameInstanceUID &InPlayInstanceUID, const Array<ActorMovement>& InMovement)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInMovement: ActorMovement type. Movement attributes


## PlayerStateChangedS2CEvt
Player state change

        Result PlayerStateChangedS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const Array<uint8_t>& InStateValues)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInState: StringCrc32 type. StateId actor state.

		- OutInMoveFrame: uint32 type. Movement frame state change has happened

		- OutInPosition: Vector4 type. Position of the player when state change happened

		- OutInStateValues: VariableTable type. State change values


## ClientSyncReliableC2SEvt
Reliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet

        Result ClientSyncReliableC2SEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInSyncData: VariableTable type. sync data


## ClientSyncC2SEvt
Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet

        Result ClientSyncC2SEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InSyncData)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInSyncData: VariableTable type. sync data


## SetCharacterPublicMessage Request
Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well

1. Command interface

        Result SetCharacterPublicMessageCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance ID

		- PlayerID: type:PlayerID, player id

		- PublicMessage: type:String, Public message to set.

2. Result interface

C++: Cast message to SetCharacterPublicMessageRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## CharacterPrivateDataChangedS2CEvt
Character's private data has changed

        Result CharacterPrivateDataChangedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const Array<uint8_t>& InPrivateData)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInCharacterID: CharacterID type. Character Id

		- OutInPrivateData: VariableTable type. Character private data


## CharacterPublicDataChangedS2CEvt
Player public data has been changed

        Result CharacterPublicDataChangedS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InPublicData)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInPublicData: VariableTable type. Character public data


## RequestWhiteboardSharing Request
Request WhiteboardSharing

1. Command interface

        Result RequestWhiteboardSharingCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const Array<uint8_t>& InWhiteboardInfo)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance

		- PlayerID: type:PlayerID, My Player id

		- TargetPlayerID: type:PlayerID, Target Player id

		- WhiteboardInfo: type:VariableTable, Whiteboard information

2. Result interface

C++: Cast message to RequestWhiteboardSharingRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## AcceptWhiteboardSharing Request
Accept WhiteboardSharing

1. Command interface

        Result AcceptWhiteboardSharingCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance

		- PlayerID: type:PlayerID, Player id

		- RequestedPlayerID: type:PlayerID, Requested Player id

		- Answer: type:uint8, true: accept, false: reject

2. Result interface

C++: Cast message to AcceptWhiteboardSharingRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## CloseWhiteboardSharing Request
Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed

1. Command interface

        Result CloseWhiteboardSharingCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance

		- PlayerID: type:PlayerID, Player id

2. Result interface

C++: Cast message to CloseWhiteboardSharingRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## AddWhiteboardSharingLogEntry Request
Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded

1. Command interface

        Result AddWhiteboardSharingLogEntryCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance

		- PlayerID: type:PlayerID, Player id

		- LogEntry: type:VariableTable, Log entry

2. Result interface

C++: Cast message to AddWhiteboardSharingLogEntryRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- LogEntryID: type:LogEntryID, Log entry Id, you also receive it by event. LogEntryID


## UpdateWhiteboardSharingLogEntry Request
Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded

1. Command interface

        Result UpdateWhiteboardSharingLogEntryCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance

		- PlayerID: type:PlayerID, Player id

		- LogEntry: type:VariableTable, Log entry, LogEntryID should be included

2. Result interface

C++: Cast message to UpdateWhiteboardSharingLogEntryRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## RemoveWhiteboardSharingLogEntry Request
Update whiteboard log entry

1. Command interface

        Result RemoveWhiteboardSharingLogEntryCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance

		- PlayerID: type:PlayerID, Player id

		- LogEntryID: type:LogEntryID, Log entry Id, you received it by event. Removed log entry id

2. Result interface

C++: Cast message to RemoveWhiteboardSharingLogEntryRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## WhiteboardSharingRequestedS2CEvt
WhiteboardSharing has been requested

        Result WhiteboardSharingRequestedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInRequestedPlayerID: PlayerID type. Player id who requested


## WhiteboardSharingRejectedS2CEvt
WhiteboardSharing has been requested

        Result WhiteboardSharingRejectedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id to receive

		- OutInRejectedPlayerID: PlayerID type. Player id who rejected


## WhiteboardSharingStartedS2CEvt
WhiteboardSharing has been started

        Result WhiteboardSharingStartedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const Array<uint8_t>& InWhiteboardInfo)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInOtherPlayerID: PlayerID type. the other player id

		- OutInWhiteboardInfo: VariableTable type. Whiteboard information


## WhiteboardSharingHasClosedS2CEvt
WhiteboardSharing has been closed

        Result WhiteboardSharingHasClosedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInClosedPlayerID: PlayerID type. Player id who requested close


## WhiteboardSharingNewLogEntryAddedS2CEvt
WhiteboardSharing new log entry has been added

        Result WhiteboardSharingNewLogEntryAddedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. target player id

		- OutInLogEntry: VariableTable type. Log entry data. It should have new 'LogEntryID'


## WhiteboardSharingNewLogEntryRemovedS2CEvt
WhiteboardSharing new log entry has been removed

        Result WhiteboardSharingNewLogEntryRemovedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. target player id

		- OutInLogEntryID: LogEntryID type. Log entry id


## WhiteboardSharingNewLogEntryUpdatedS2CEvt
WhiteboardSharing new log entry has been updated

        Result WhiteboardSharingNewLogEntryUpdatedS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InLogEntry)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. target player id

		- OutInLogEntry: VariableTable type. Log entry


## OccupyMapObject Request
Occupy map object

1. Command interface

        Result OccupyMapObjectCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance ID

		- PlayerID: type:PlayerID, player id

		- MapObjectId: type:uint32, MapObjectId

		- UsageId: type:uint32, MapObjectOccupyMode 

2. Result interface

C++: Cast message to OccupyMapObjectRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayInstanceUID: type:EntityUID, Play instance ID
		- PlayerID: type:PlayerID, player id for validation
		- MapObjectId: type:uint32, MapObjectId


## UnoccupyMapObject Request
Unoccupy map object

1. Command interface

        Result UnoccupyMapObjectCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance ID

		- PlayerID: type:PlayerID, player id

		- MapObjectId: type:uint32, MapObjectId

2. Result interface

C++: Cast message to UnoccupyMapObjectRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayInstanceUID: type:EntityUID, Play instance ID
		- PlayerID: type:PlayerID, player id for validation
		- MapObjectId: type:uint32, MapObjectId


## UseMapObject Request
Use map object

1. Command interface

        Result UseMapObjectCmd(const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:EntityUID, Play instance ID

		- PlayerID: type:PlayerID, player id

		- MapObjectId: type:StringCrc32, MapObjectId

		- UseParameters: type:VariableTable, use parameters

2. Result interface

C++: Cast message to UseMapObjectRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- PlayInstanceUID: type:EntityUID, Play instance ID
		- PlayerID: type:PlayerID, player id for validation
		- MapObjectId: type:StringCrc32, MapObjectId
		- ResultAttributes: type:VariableTable, Use result attributes


## ZoneChat Request
Send zone chatting

1. Command interface

        Result ZoneChatCmd(const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:GameInstanceUID, Play instance ID

		- PlayerID: type:PlayerID, Sender PlayerID

		- MessageType: type:int8, chatting message type

		- ChatMetaData: type:VariableTable, Chat meta data, player id and so on

		- ChatMessage: type:String, Message to send

2. Result interface

C++: Cast message to ZoneChatRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## ZoneChatS2CEvt
Player state change

        Result ZoneChatS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const Array<uint8_t>& InChatMetaData, const char* InChatMessage)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInSenderID: PlayerID type. Sender PlayerID

		- OutInMessageType: int8 type. chatting message type

		- OutInChatMetaData: VariableTable type. Chat meta data, player id

		- OutInChatMessage: String type. Message to send


## LevelUpS2CEvt
Effect modifier initial sync

        Result LevelUpS2CEvt(const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel)

		- OutInPlayInstanceUID: EntityUID type. Play instance

		- OutInPlayerID: PlayerID type. player id

		- OutInCurrentExp: int64 type. Current experience

		- OutInCurrentLevel: int type. Current level


## CallFunction Request
To call general functionality

1. Command interface

        Result CallFunctionCmd(const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters)

		- TransactionID: type:TransactionID, 

		- FunctionName: type:StringCrc32, function name

		- PlayerID: type:PlayerID, Caller player Id

		- Parameters: type:VariableTable, function parameter

2. Result interface

C++: Cast message to CallFunctionRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- Results: type:VariableTable, function result


## SendVoiceDataC2SEvt
Send coded voice data to server

        Result SendVoiceDataC2SEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInPlayerID: PlayerID type. player id

		- OutInFrameIndex: uint16 type. voice frame index

		- OutInVoiceData: uint8 type. Voice data


## VoiceDataS2CEvt
Voice data

        Result VoiceDataS2CEvt(const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData)

		- OutInActorID: uint32 type. actor id

		- OutInFrameIndex: uint16 type. voice frame index

		- OutInVoiceData: uint8 type. Voice data


## UGCEditAdd Request
UGC zone edit command

1. Command interface

        Result UGCEditAddCmd(const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InInvenItemUID, const uint32_t &InGroupInstanceID, const Vector4 &InPosition, const Quaternion &InRotation, const Vector4 &InScale)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:GameInstanceUID, Play instance ID

		- PlayerID: type:PlayerID, Operator PlayerID

		- InvenItemUID: type:uint32, Inventory Item UID to place in the zone

		- GroupInstanceID: type:uint32, Group instance Id such as Aquarium instance Id

		- Position: type:Vector4, Position to place

		- Rotation: type:Quaternion, Rotation of the placement, quaternion value

		- Scale: type:Vector4, Scale

2. Result interface

C++: Cast message to UGCEditAddRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- EntityInstanceId: type:uint32, Added entity's Instance Id
		- TimeOffset: type:uint32, TimeOffset for animation sync
		- InvenChanges: type:VariableTable, Inventory changes


## UGCEditMove Request
UGC zone edit command

1. Command interface

        Result UGCEditMoveCmd(const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InEntityInstanceId, const Vector4 &InPosition, const Quaternion &InRotation, const Vector4 &InScale)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:GameInstanceUID, Play instance ID

		- PlayerID: type:PlayerID, Operator PlayerID

		- EntityInstanceId: type:uint32, Entity's Instance Id to move

		- Position: type:Vector4, Position

		- Rotation: type:Quaternion, Rotation quaternion value

		- Scale: type:Vector4, Scale

2. Result interface

C++: Cast message to UGCEditMoveRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## UGCEditDelete Request
UGC zone edit command

1. Command interface

        Result UGCEditDeleteCmd(const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InEntityInstanceId)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:GameInstanceUID, Play instance ID

		- PlayerID: type:PlayerID, Operator PlayerID

		- EntityInstanceId: type:uint32, Entity's Instance Id to delete

2. Result interface

C++: Cast message to UGCEditDeleteRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 


## UGCEditClaimBack Request
UGC zone edit command

1. Command interface

        Result UGCEditClaimBackCmd(const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InEntityInstanceId)

		- TransactionID: type:TransactionID, 

		- PlayInstanceUID: type:GameInstanceUID, Play instance ID

		- PlayerID: type:PlayerID, Operator PlayerID

		- EntityInstanceId: type:uint32, Entity's Instance Id to claim back

2. Result interface

C++: Cast message to UGCEditClaimBackRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- EntityInstanceId: type:uint32, Entity's Instance Id to claim back
		- InvenChanges: type:VariableTable, Inventory changes


## UGCEditAddedS2CEvt
UGC zone edited event

        Result UGCEditAddedS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const uint32_t &InEntityInstanceId, const StringCrc32 &InEntityType, const uint32_t &InTableId, const uint32_t &InTimeOffset, const Vector4 &InPosition, const Quaternion &InRotation, const Vector4 &InScale)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInOperatorPlayerID: PlayerID type. Player who operated

		- OutInEntityInstanceId: uint32 type. Entity's Instance Id to delete

		- OutInEntityType: StringCrc32 type. EntityType

		- OutInTableId: uint32 type. Data table Id

		- OutInTimeOffset: uint32 type. TimeOffset for animation sync

		- OutInPosition: Vector4 type. Position

		- OutInRotation: Quaternion type. Rotation quaternion value

		- OutInScale: Vector4 type. Scale


## UGCEditRemovedS2CEvt
UGC zone edited event

        Result UGCEditRemovedS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const uint32_t &InEntityInstanceId)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInOperatorPlayerID: PlayerID type. Player who operated

		- OutInEntityInstanceId: uint32 type. Entity's Instance Id to delete


## UGCEditMovedS2CEvt
UGC zone edited event

        Result UGCEditMovedS2CEvt(const GameInstanceUID &InPlayInstanceUID, const PlayerID &InOperatorPlayerID, const uint32_t &InEntityInstanceId, const Vector4 &InPosition, const Quaternion &InRotation, const Vector4 &InScale)

		- OutInPlayInstanceUID: GameInstanceUID type. Game instance UID

		- OutInOperatorPlayerID: PlayerID type. Player who operated

		- OutInEntityInstanceId: uint32 type. Moved Entity's Instance Id

		- OutInPosition: Vector4 type. Position

		- OutInRotation: Quaternion type. Rotation

		- OutInScale: Vector4 type. Scale


## CreateStream Request
Create stream instance

1. Command interface

        Result CreateStreamCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- TransactionID: type:TransactionID, 

		- Ticket: type:AuthTicket, Login session Ticket

		- StreamName: type:String, Stream name

2. Result interface

C++: Cast message to CreateStreamRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- StreamName: type:String, Stream name


## FindStream Request
Open stream instance

1. Command interface

        Result FindStreamCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- TransactionID: type:TransactionID, 

		- Ticket: type:AuthTicket, Login session Ticket

		- StreamName: type:String, Stream name

2. Result interface

C++: Cast message to FindStreamRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- StreamName: type:String, Stream name


## DeleteStream Request
Delete stream instance

1. Command interface

        Result DeleteStreamCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- TransactionID: type:TransactionID, 

		- Ticket: type:AuthTicket, Login session Ticket

		- StreamName: type:String, stream name to delete

2. Result interface

C++: Cast message to DeleteStreamRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- StreamName: type:String, Stream name


## GetStreamList Request
Get stream list

1. Command interface

        Result GetStreamListCmd(const TransactionID &InTransactionID, const AuthTicket &InTicket)

		- TransactionID: type:TransactionID, 

		- Ticket: type:AuthTicket, Login session Ticket

2. Result interface

C++: Cast message to GetStreamListRes to access values


		- TransactionID: type:TransactionID, 
		- Result: type:Result, 
		- StreamNames: type:String, Stream names








