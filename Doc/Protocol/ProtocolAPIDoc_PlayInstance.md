***
 
 CopyRight (c) 2021 StormForge
 
 Description : PlayInstance Message Protocol API Document

***



PlayInstance Protocol

namespace SF::Message::PlayInstance


# Protocol interface class NetPolicyPlayInstance
## JoinGameInstance Request
Event for Player Join request.

1. Command interface

        Result JoinGameInstanceCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayInstanceUID: EntityUID type. Play instance to join

		- OutInPlayerID: PlayerID type. Joining player id

		- OutInPlayerIdentifier: String type. Joining player identifier. string value

2. Result interface

C++: Cast message to JoinGameInstanceRes to access values


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


## NewPlayerInViewS2CEvt
New Player in get view

        Result NewPlayerInViewS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const Array<uint8_t>& InAttributes, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Joined Player Id

		- OutInAttributes: VariableTable type. Character visual data

		- OutInMovement: ActorMovement type. Actor movement of the character


## RemovePlayerFromViewS2CEvt
Remove player from view

        Result RemovePlayerFromViewS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Removed Player Id


## PlayerMovementC2SEvt
Player Movement

        Result PlayerMovementC2SEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInMovement: ActorMovement type. Movement attributes


## PlayerMovementS2CEvt
Player Movement

        Result PlayerMovementS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInMovement: ActorMovement type. Movement attributes


## PlayerStateChangedS2CEvt
Player state change

        Result PlayerStateChangedS2CEvt(const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InState, const uint32_t &InMoveFrame, const Array<uint8_t>& InStateValues, const Vector4 &InPosition)

		- OutInPlayInstanceUID: GameInsUID type. Game instance UID

		- OutInPlayerID: PlayerID type. Player Id

		- OutInState: uint32 type. StateId, ActorMovement has same MovementStateId.

		- OutInMoveFrame: uint32 type. Movement frame state change has happened

		- OutInStateValues: VariableTable type. State change values

		- OutInPosition: Vector4 type. Position of the player when state change happened


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

        Result OccupyMapObjectCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const uint32_t &InUsageId)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayInstanceUID: EntityUID type. Play instance ID

		- OutInPlayerID: PlayerID type. player id

		- OutInMapObjectId: StringCrc32 type. MapObjectId

		- OutInUsageId: uint32 type. MapObjectOccupyMode 

2. Result interface

C++: Cast message to OccupyMapObjectRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id for validation

		- OutMapObjectId: StringCrc32 type. MapObjectId


## UnoccupyMapObject Request
Unoccupy map object

1. Command interface

        Result UnoccupyMapObjectCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayInstanceUID: EntityUID type. Play instance ID

		- OutInPlayerID: PlayerID type. player id

		- OutInMapObjectId: StringCrc32 type. MapObjectId

2. Result interface

C++: Cast message to UnoccupyMapObjectRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id for validation

		- OutMapObjectId: StringCrc32 type. MapObjectId


## UseMapObject Request
Use map object

1. Command interface

        Result UseMapObjectCmd(const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const Array<uint8_t>& InUseParameters)

		- OutInTransactionID: TransactionID type. 

		- OutInPlayInstanceUID: EntityUID type. Play instance ID

		- OutInPlayerID: PlayerID type. player id

		- OutInMapObjectId: StringCrc32 type. MapObjectId

		- OutInUseParameters: VariableTable type. use parameters

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

		- OutInTransactionID: TransactionID type. 

		- OutInPlayInstanceUID: EntityUID type. Play instance ID

		- OutInPlayerID: PlayerID type. player id

		- OutInAreaId: StringCrc32 type. Area Id

2. Result interface

C++: Cast message to HarvestAreaRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutPlayInstanceUID: EntityUID type. Play instance ID

		- OutPlayerID: PlayerID type. player id for validation

		- OutAreaId: StringCrc32 type. Area Id

		- OutResultAttributes: VariableTable type. Use result attributes


## CreateStream Request
Create stream instance

1. Command interface

        Result CreateStreamCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- OutInTransactionID: TransactionID type. 

		- OutInTicket: AuthTicket type. Login session Ticket

		- OutInStreamName: String type. Stream name

2. Result interface

C++: Cast message to CreateStreamRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutStreamServerAddr: NetAddress type. Stream server address to connect

		- OutStreamServerAddrIPV4: NetAddress type. Stream server address to connect

		- OutStreamUID: String type. Unique stream Id generated by server. This wil be used when you operate streaming


## FindStream Request
Open stream instance

1. Command interface

        Result FindStreamCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- OutInTransactionID: TransactionID type. 

		- OutInTicket: AuthTicket type. Login session Ticket

		- OutInStreamName: String type. Stream name

2. Result interface

C++: Cast message to FindStreamRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutStreamServerAddr: NetAddress type. Stream server address to connect

		- OutStreamServerAddrIPV4: NetAddress type. Stream server address to connect

		- OutStreamUID: String type. Unique stream Id generated by server. This wil be used when you operate streaming


## DeleteStream Request
Delete stream instance

1. Command interface

        Result DeleteStreamCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName)

		- OutInTransactionID: TransactionID type. 

		- OutInTicket: AuthTicket type. Login session Ticket

		- OutInStreamName: String type. stream name to delete

2. Result interface

C++: Cast message to DeleteStreamRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 


## GetStreamList Request
Get stream list

1. Command interface

        Result GetStreamListCmd(const uint64_t &InTransactionID, const AuthTicket &InTicket)

		- OutInTransactionID: TransactionID type. 

		- OutInTicket: AuthTicket type. Login session Ticket

2. Result interface

C++: Cast message to GetStreamListRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutStreamNames: String type. Stream names


## CallFunction Request
To call general functionality

1. Command interface

        Result CallFunctionCmd(const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const Array<uint8_t>& InParameters)

		- OutInTransactionID: TransactionID type. 

		- OutInFunctionName: StringCrc32 type. function name

		- OutInParameters: VariableTable type. function parameter

2. Result interface

C++: Cast message to CallFunctionRes to access values


		- OutTransactionID: TransactionID type. 

		- OutResult: Result type. 

		- OutResults: VariableTable type. function result








