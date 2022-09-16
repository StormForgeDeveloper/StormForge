////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Login Message debug definitions
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


	class NetPolicyLogin 
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetPolicyLogin (const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Login request
		Result LoginCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword );
		// Cmd: Login request with Facebook UID
		Result LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken );
		// Cmd: Login request with Facebook UID
		Result LoginBySteamCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken );
		// Cmd: Login request
		Result CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone );
		// Cmd: Update my score and Get Ranking list
		Result UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount );
		// Cmd: Get Ranking lise
		Result GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );
		// Cmd: For network test
		Result DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData );
		// C2S: Heartbeat
		Result HeartbeatC2SEvt(  );
		// Cmd: Write All!! User Score and Ranking list
		Result DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName );

	}; // class NetPolicyLogin 


	class NetSvrPolicyLogin
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetSvrPolicyLogin ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Login request
		Result LoginRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
		// Cmd: Login request with Facebook UID
		Result LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
		// Cmd: Login request with Facebook UID
		Result LoginBySteamRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
		// Cmd: Login request
		Result CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
		// Cmd: Update my score and Get Ranking list
		Result UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
		// Cmd: Get Ranking lise
		Result GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
		// Cmd: For network test
		Result DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData );
		// Cmd: Write All!! User Score and Ranking list
		Result DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult );

	}; // class NetSvrPolicyLogin


}; // namespace SF


