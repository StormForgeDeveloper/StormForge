***
 
 CopyRight (c) 2022 StormForge
 
 Description : PlayInstance Message Protocol API Document

***



PlayInstance Protocol

namespace SF::Message::PlayInstance


# Protocol interface class NetPolicyPlayInstance
## JoinPlayInstance Request
Player Join request.

1. Command interface

        Result JoinPlayInstanceCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier)

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

        Result NewActorInViewS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes, const ActorMovement &InMovement, const StringCrc32 &InState, const Array<uint8_t>& InStateValues)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Joined Player Id

		- OutInAttributes: VariableTable type. Character visual data

		- OutInMovement: ActorMovement type. Actor movement of the character

		- OutInState: StringCrc32 type. StateId actor state.

		- OutInStateValues: VariableTable type. State values


## RemoveActorFromViewS2CEvt
Remove actor from view

        Result RemoveActorFromViewS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InActorID)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Removed Player Id(deprecated)

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


## OccupyMapObject Request
Occupy map object

1. Command interface

        Result OccupyMapObjectCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId)

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

        Result UnoccupyMapObjectCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId)

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

        Result UseMapObjectCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters)

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


## HarvestArea Request
Havest area

1. Command interface

        Result HarvestAreaCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id

		- OutAreaId: StringCrc32 type. Area Id

2. Result interface

C++: Cast message to HarvestAreaRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutPlayInstanceUID: EntityUID type. Play instance ID
		- OutPlayerID: PlayerID type. player id for validation
		- OutAreaId: StringCrc32 type. Area Id
		- OutResultAttributes: VariableTable type. Use result attributes


## ZoneChat Request
Send zone chatting

1. Command interface

        Result ZoneChatCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InChatMessageType, const char* InChatMessage)

		- OutTransactionID: TransactionID type. 

		- OutPlayInstanceUID: GameInsUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id

		- OutChatMessageType: int8 type. 0: local chatting, 1:zone global chatting

		- OutChatMessage: String type. Message to send

2. Result interface

C++: Cast message to ZoneChatRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 


## ZoneChatS2CEvt
Player state change

        Result ZoneChatS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InChatMessageType, const char* InMessage)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInChatMessageType: int8 type. 0: local chatting, 1:zone global chatting

		- OutInMessage: String type. Message to send


## CreateStream Request
Create stream instance

1. Command interface

        Result CreateStreamCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

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

        Result FindStreamCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

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

        Result DeleteStreamCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

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

        Result GetStreamListCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket)

		- OutTransactionID: TransactionID type. 

		- OutTicket: AuthTicket type. Login session Ticket

2. Result interface

C++: Cast message to GetStreamListRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutStreamNames: String type. Stream names


## CallFunction Request
To call general functionality

1. Command interface

        Result CallFunctionCmd(const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const Array<uint8_t>& InParameters)

		- OutTransactionID: TransactionID type. 

		- OutFunctionName: StringCrc32 type. function name

		- OutPlayerID: PlayerID type. Caller player Id

		- OutParameters: VariableTable type. function parameter

2. Result interface

C++: Cast message to CallFunctionRes to access values


		- OutTransactionID: TransactionID type. 
		- OutResult: Result type. 
		- OutResults: VariableTable type. function result








