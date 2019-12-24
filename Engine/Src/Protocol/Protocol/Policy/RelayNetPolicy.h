////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 The Braves
// 
// Author : Generated
// 
// Description : Relay Message debug definitions
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"



namespace SF
{
 	namespace Policy
	{
 		class NetPolicyRelay 
		{
 			private:
				SharedPointerT<Net::Connection> m_pConnection;
			public:
			// Constructor
			NetPolicyRelay ( const SharedPointerT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}
			NetPolicyRelay ( const SharedPointerAtomicT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}

			// C2S: Event for Player Join request.
			Result JoinRelayInstanceC2SEvt( const PlayerID &InPlayerID );
			// C2S: Event for Player Join request.
			Result LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID );
			// C2S: Relay packet
			Result RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint64_t &InSenderRelayID, const uint64_t &InTargetRelayMask );

		}; // class NetPolicyRelay 


		class NetSvrPolicyRelay
		{
 			private:
				SharedPointerT<Net::Connection> m_pConnection;
			public:
			// Constructor
			NetSvrPolicyRelay ( const SharedPointerT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}
			NetSvrPolicyRelay ( const SharedPointerAtomicT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}

			// S2C: Event for joined player
			Result JoinRelayInstanceResS2CEvt( const Result &InResult, const RelayPlayerInfo &InMyPlayerInfo, const uint32_t &InRelayInstanceID, const Array<RelayPlayerInfo>& InMemberInfos );
			// S2C: Event for Player joined.
			Result PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo );
			// S2C: Event for Player left.
			Result PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason );

		}; // class NetSvrPolicyRelay


	}; // namespace Policy
}; // namespace SF


