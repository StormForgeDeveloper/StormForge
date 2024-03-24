////////////////////////////////////////////////////////////////////////////////
// 
// StormForge
// 
// Author : Generated
// 
// Description : PlayInstance RPC Send interface
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "MessageBus/SFRPCSendAdapter.h"
#include "Protocol/PlayInstanceMessageID.h"




namespace SF
{
    class MessageEndpoint;
   class VariableTable;
   struct ActorMovement;


	class PlayInstanceRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		PlayInstanceRPCSendAdapter (MessageEndpoint* pEndpoint, flatbuffers::FlatBufferBuilder* pBuilder = nullptr) : RPCSendAdapter(pEndpoint, pBuilder)
		{}
		PlayInstanceRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Player Join request.
		Result JoinPlayInstanceCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );
		// C2S: Play packet
		Result PlayPacketC2SEvt( const GameInstanceUID &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );
		// C2S: Player Movement
		Result PlayerMovementC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
		// C2S: Reliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		Result ClientSyncReliableC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );
		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		Result ClientSyncC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );
		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		Result SetCharacterPublicMessageCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPublicMessage );
		// Cmd: Request WhiteboardSharing
		Result RequestWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InTargetPlayerID, const VariableTable &InWhiteboardInfo );
		// Cmd: Accept WhiteboardSharing
		Result AcceptWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID, const uint8_t &InAnswer );
		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		Result CloseWhiteboardSharingCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID );
		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		Result AddWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		Result UpdateWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
		// Cmd: Update whiteboard log entry
		Result RemoveWhiteboardSharingLogEntryCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID );
		// Cmd: Occupy map object
		Result OccupyMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId );
		// Cmd: Unoccupy map object
		Result UnoccupyMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
		// Cmd: Use map object
		Result UseMapObjectCmd( const TransactionID &InTransactionID, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters );
		// Cmd: Send zone chatting
		Result ZoneChatCmd( const TransactionID &InTransactionID, const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );
		// Cmd: To call general functionality
		Result CallFunctionCmd( const TransactionID &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters );
		// C2S: Send coded voice data to server
		Result SendVoiceDataC2SEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData );
		// Cmd: Create stream instance
		Result CreateStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Open stream instance
		Result FindStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Delete stream instance
		Result DeleteStreamCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Get stream list
		Result GetStreamListCmd( const TransactionID &InTransactionID, const AuthTicket &InTicket );

	}; // class PlayInstanceRPCSendAdapter : public RPCSendAdapter


	class PlayInstanceSvrRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		PlayInstanceSvrRPCSendAdapter (MessageEndpoint* pEndpoint, flatbuffers::FlatBufferBuilder* pBuilder = nullptr) : RPCSendAdapter(pEndpoint, pBuilder)
		{}
		PlayInstanceSvrRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Player Join request.
		Result JoinPlayInstanceRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InCharacterPrivateData, const ActorMovement &InMovement );
		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		Result PlayerKickedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InKickedPlayerID );
		// S2C: New actor in get view
		Result NewActorInViewS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerPlatformID &InPlayerPlatformId, const VariableTable &InPublicData, const VariableTable &InEquipData, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues );
		// S2C: Remove actor from view
		Result RemoveActorFromViewS2CEvt( const GameInstanceUID &InPlayInstanceUID, const uint32_t &InActorID );
		// S2C: Player Movement
		Result ActorMovementS2CEvt( const GameInstanceUID &InPlayInstanceUID, const ActorMovement &InMovement );
		// S2C: Player Movement
		Result ActorMovementsS2CEvt( const GameInstanceUID &InPlayInstanceUID, const Array<ActorMovement>& InMovement );
		// S2C: Player state change
		Result PlayerStateChangedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues );
		// Cmd: Set character public message. Server will broadcast CharacterPublicDataChanged, NewActorInView should have updated value as well
		Result SetCharacterPublicMessageRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Character's private data has changed
		Result CharacterPrivateDataChangedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const CharacterID &InCharacterID, const VariableTable &InPrivateData );
		// S2C: Player public data has been changed
		Result CharacterPublicDataChangedS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InPublicData );
		// Cmd: Request WhiteboardSharing
		Result RequestWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Accept WhiteboardSharing
		Result AcceptWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Close WhiteboardSharing. Both clients will receive WhiteboardSharingHasClosed
		Result CloseWhiteboardSharingRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		Result AddWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult, const uint32_t &InLogEntryID );
		// Cmd: Add new log entry to WhiteboardSharing. The other client will receive WhiteboardSharingNewLogEntryAdded
		Result UpdateWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Update whiteboard log entry
		Result RemoveWhiteboardSharingLogEntryRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: WhiteboardSharing has been requested
		Result WhiteboardSharingRequestedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRequestedPlayerID );
		// S2C: WhiteboardSharing has been requested
		Result WhiteboardSharingRejectedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InRejectedPlayerID );
		// S2C: WhiteboardSharing has been started
		Result WhiteboardSharingStartedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InOtherPlayerID, const VariableTable &InWhiteboardInfo );
		// S2C: WhiteboardSharing has been closed
		Result WhiteboardSharingHasClosedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const PlayerID &InClosedPlayerID );
		// S2C: WhiteboardSharing new log entry has been added
		Result WhiteboardSharingNewLogEntryAddedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
		// S2C: WhiteboardSharing new log entry has been removed
		Result WhiteboardSharingNewLogEntryRemovedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InLogEntryID );
		// S2C: WhiteboardSharing new log entry has been updated
		Result WhiteboardSharingNewLogEntryUpdatedS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InLogEntry );
		// Cmd: Occupy map object
		Result OccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
		// Cmd: Unoccupy map object
		Result UnoccupyMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
		// Cmd: Use map object
		Result UseMapObjectRes( const TransactionID &InTransactionID, const Result &InResult, const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes );
		// Cmd: Send zone chatting
		Result ZoneChatRes( const TransactionID &InTransactionID, const Result &InResult );
		// S2C: Player state change
		Result ZoneChatS2CEvt( const GameInstanceUID &InPlayInstanceUID, const PlayerID &InSenderID, const int8_t &InMessageType, const VariableTable &InChatMetaData, const char* InChatMessage );
		// S2C: Effect modifier initial sync
		Result LevelUpS2CEvt( const EntityUID &InPlayInstanceUID, const PlayerID &InPlayerID, const int64_t &InCurrentExp, const int32_t &InCurrentLevel );
		// Cmd: To call general functionality
		Result CallFunctionRes( const TransactionID &InTransactionID, const Result &InResult, const VariableTable &InResults );
		// S2C: Voice data
		Result VoiceDataS2CEvt( const uint32_t &InActorID, const uint16_t &InFrameIndex, const Array<uint8_t>& InVoiceData );
		// Cmd: Create stream instance
		Result CreateStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );
		// Cmd: Open stream instance
		Result FindStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );
		// Cmd: Delete stream instance
		Result DeleteStreamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InStreamName );
		// Cmd: Get stream list
		Result GetStreamListRes( const TransactionID &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );

	}; // class PlayInstanceSvrRPCSendAdapter : public RPCSendAdapter


}; // namespace SF


