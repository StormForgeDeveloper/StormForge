﻿***
 
 CopyRight (c) 2019 StormForge
 
 Description : Relay Message Protocol API Document

***



Relay Protocol

namespace SF::Message::Relay


# Protocol interface class NetPolicyRelay
## JoinRelayInstanceC2SEvt
Event for Player Join request.

        Result JoinRelayInstanceC2SEvt(const PlayerID &InPlayerID)

		- OutInPlayerID: PlayerID type. Joining player id


## JoinRelayInstanceResS2CEvt
Event for joined player

        Result JoinRelayInstanceResS2CEvt(const Result &InResult, const RelayPlayerInfo &InMyPlayerInfo, const uint32_t &InRelayInstanceID, const Array<RelayPlayerInfo>& InMemberInfos)

		- OutInResult: Result type. Join result

		- OutInMyPlayerInfo: RelayPlayerInfo type. Joined player info

		- OutInRelayInstanceID: uint32 type. joined relay instance ID

		- OutInMemberInfos: RelayPlayerInfo type. Member player IDs


## LeaveRelayInstanceC2SEvt
Event for Player Join request.

        Result LeaveRelayInstanceC2SEvt(const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID)

		- OutInRelayInstanceID: uint32 type. Relay Instance id

		- OutInPlayerID: PlayerID type. player id


## PlayerJoinS2CEvt
Event for Player joined.

        Result PlayerJoinS2CEvt(const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo)

		- OutInRelayInstanceID: uint32 type. Relay Instance id

		- OutInJoinedPlayerInfo: RelayPlayerInfo type. Joined player ID


## PlayerLeftS2CEvt
Event for Player left.

        Result PlayerLeftS2CEvt(const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason)

		- OutInRelayInstanceID: uint32 type. Relay Instance id

		- OutInLeftPlayerID: PlayerID type. Left player ID

		- OutInKickedReason: uint32 type. Reason


## RelayPacketC2SEvt
Relay packet

        Result RelayPacketC2SEvt(const uint32_t &InRelayInstanceID, const uint64_t &InSenderRelayID, const uint64_t &InTargetRelayMask)

		- OutInRelayInstanceID: uint32 type. Relay Instance id

		- OutInSenderRelayID: uint64 type. Sender player ID

		- OutInTargetRelayMask: uint64 type. Target relay mask.







