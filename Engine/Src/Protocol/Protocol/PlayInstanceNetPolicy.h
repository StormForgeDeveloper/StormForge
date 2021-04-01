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

		// Cmd: Event for Player Join request.
		Result JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );
		// C2S: Play packet
		Result PlayPacketC2SEvt( const uint64_t &InPlayInstanceUID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );
		// C2S: Player Movement
		Result PlayerMovementC2SEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
		// Cmd: Occupy map object
		Result OccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const uint32_t &InUsageId );
		// Cmd: Unoccupy map object
		Result UnoccupyMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId );
		// Cmd: Use map object
		Result UseMapObjectCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InUseParameters );
		// Cmd: Havest area
		Result HarvestAreaCmd( const uint64_t &InTransactionID, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId );
		// Cmd: Create stream instance
		Result CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Open stream instance
		Result FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Delete stream instance
		Result DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
		// Cmd: Get stream list
		Result GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket );
		// Cmd: To call general functionality
		Result CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters );

	}; // class NetPolicyPlayInstance 


	class NetSvrPolicyPlayInstance
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetSvrPolicyPlayInstance ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Event for Player Join request.
		Result JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		Result PlayerKickedS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InKickedPlayerID );
		// S2C: New Player in get view
		Result NewPlayerInViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const VariableTable &InAttributes );
		// S2C: Remove player from view
		Result RemovePlayerFromViewS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID );
		// S2C: Player Movement
		Result PlayerMovementS2CEvt( const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const ActorMovement &InMovement );
		// Cmd: Occupy map object
		Result OccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId );
		// Cmd: Unoccupy map object
		Result UnoccupyMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId );
		// Cmd: Use map object
		Result UseMapObjectRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InMapObjectId, const VariableTable &InResultAttributes );
		// Cmd: Havest area
		Result HarvestAreaRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPlayInstanceUID, const PlayerID &InPlayerID, const StringCrc32 &InAreaId, const VariableTable &InResultAttributes );
		// Cmd: Create stream instance
		Result CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID );
		// Cmd: Open stream instance
		Result FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID );
		// Cmd: Delete stream instance
		Result DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Get stream list
		Result GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );
		// Cmd: To call general functionality
		Result CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults );

	}; // class NetSvrPolicyPlayInstance


}; // namespace SF


