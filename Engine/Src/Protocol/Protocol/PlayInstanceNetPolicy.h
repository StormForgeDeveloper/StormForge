////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : PlayInstance Message debug definitions
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"



namespace SF
{
    class MessageEndpoint;
   class VariableTable;
   struct ActorMovement;


	class NetPolicyPlayInstance 
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetPolicyPlayInstance (const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Player Join request.
		Result JoinPlayInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );
		// C2S: Play packet
		Result PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );
		// C2S: Player Movement
		Result PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		Result ClientSyncReliableC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );
		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		Result ClientSyncC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InSyncData );
		// Cmd: Occupy map object
		Result OccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId, const uint32_t &InUsageId );
		// Cmd: Unoccupy map object
		Result UnoccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
		// Cmd: Use map object
		Result UseMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters );
		// Cmd: Send zone chatting
		Result ZoneChatCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InChatMessageType, const char* InChatMessage );
		// Cmd: Create stream instance
		Result CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Open stream instance
		Result FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Delete stream instance
		Result DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Get stream list
		Result GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket );
		// Cmd: To call general functionality
		Result CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const PlayerID &InPlayerID, const VariableTable &InParameters );

	}; // class NetPolicyPlayInstance 


	class NetSvrPolicyPlayInstance
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetSvrPolicyPlayInstance ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Player Join request.
		Result JoinPlayInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		Result PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID );
		// S2C: New actor in get view
		Result NewActorInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes, const ActorMovement &InMovement, const StringCrc32 &InState, const VariableTable &InStateValues );
		// S2C: Remove actor from view
		Result RemoveActorFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InActorID );
		// S2C: Player Movement
		Result ActorMovementS2CEvt( const uint64_t &InPlayInstanceUID, const ActorMovement &InMovement );
		// S2C: Player Movement
		Result ActorMovementsS2CEvt( const uint64_t &InPlayInstanceUID, const Array<ActorMovement>& InMovement );
		// S2C: Player state change
		Result PlayerStateChangedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InState, const uint32_t &InMoveFrame, const Vector4 &InPosition, const VariableTable &InStateValues );
		// Cmd: Occupy map object
		Result OccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
		// Cmd: Unoccupy map object
		Result UnoccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const uint32_t &InMapObjectId );
		// Cmd: Use map object
		Result UseMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes );
		// Cmd: Send zone chatting
		Result ZoneChatRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: Player state change
		Result ZoneChatS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const int8_t &InChatMessageType, const char* InChatMessage );
		// Cmd: Create stream instance
		Result CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName );
		// Cmd: Open stream instance
		Result FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName );
		// Cmd: Delete stream instance
		Result DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamName );
		// Cmd: Get stream list
		Result GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );
		// Cmd: To call general functionality
		Result CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults );

	}; // class NetSvrPolicyPlayInstance


}; // namespace SF


