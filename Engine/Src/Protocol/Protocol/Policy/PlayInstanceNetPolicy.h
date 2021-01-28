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



class VariableTable;



namespace SF
{
 	namespace Policy
	{
 		class NetPolicyPlayInstance 
		{
 			private:
				SharedPointerT<Net::Connection> m_pConnection;
			public:
			// Constructor
			NetPolicyPlayInstance ( const SharedPointerT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}
			NetPolicyPlayInstance ( const SharedPointerAtomicT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}

			// C2S: Play packet
			Result PlayPacketC2SEvt( const uint32_t &InPlayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );
			// C2S: Player Movement
			Result PlayerMovementC2SEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes );
			// Cmd: Create stream instance
			Result CreateStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
			// Cmd: Open stream instance
			Result FindStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
			// Cmd: Delete stream instance
			Result DeleteStreamCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName );
			// Cmd: Get stream list
			Result GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket );

		}; // class NetPolicyPlayInstance 


		class NetSvrPolicyPlayInstance
		{
 			private:
				SharedPointerT<Net::Connection> m_pConnection;
			public:
			// Constructor
			NetSvrPolicyPlayInstance ( const SharedPointerT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}
			NetSvrPolicyPlayInstance ( const SharedPointerAtomicT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}

			// S2C: Event for Player joined.
			Result PlayerJoinS2CEvt( const uint32_t &InPlayInstanceID, const PlayerInformation &InJoinedPlayerInfo );
			// S2C: Event for Player left.
			Result PlayerLeftS2CEvt( const uint32_t &InPlayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason );
			// S2C: New Player in get view
			Result NewPlayerInViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes );
			// S2C: Remove player from view
			Result RemovePlayerFromViewS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes );
			// S2C: Player Movement
			Result PlayerMovementS2CEvt( const uint64_t &InGameInsUID, const PlayerID &InPlayerID, const VariableTable &InAttributes );
			// Cmd: Create stream instance
			Result CreateStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID );
			// Cmd: Open stream instance
			Result FindStreamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID );
			// Cmd: Delete stream instance
			Result DeleteStreamRes( const uint64_t &InTransactionID, const Result &InResult );
			// Cmd: Get stream list
			Result GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<const char*>& InStreamNames );

		}; // class NetSvrPolicyPlayInstance


	}; // namespace Policy
}; // namespace SF


