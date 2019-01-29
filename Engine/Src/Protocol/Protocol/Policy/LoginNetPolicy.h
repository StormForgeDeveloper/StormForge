////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 The Braves
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
 	namespace Policy
	{
 		class NetPolicyLogin 
		{
 			private:
				SharedPointerT<Net::Connection> m_pConnection;
			public:
			// Constructor
			NetPolicyLogin ( const SharedPointerT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}
			NetPolicyLogin ( const SharedPointerAtomicT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}

			// Cmd: Login request
			Result LoginCmd( const uint32_t &InGameID, const char* InID, const char* InPassword );
			// Cmd: Login request with Facebook UID
			Result LoginByFacebookCmd( const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken );
			// Cmd: Login request
			Result CreateRandomUserCmd( const uint32_t &InGameID, const char* InCellPhone );
			// Cmd: Update my score and Get Ranking list
			Result UpdateMyScoreCmd( const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount );
			// Cmd: Get Ranking lise
			Result GetRankingListCmd( const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );
			// Cmd: For network test
			Result DataTestCmd( const Array<uint8_t>& InTestData );
			// C2S: Heartbit
			Result HeartBitC2SEvt(  );
			// Cmd: Write All!! User Score and Ranking list
			Result DebugPrintALLRankingCmd( const char* InFileName );

		}; // class NetPolicyLogin 


		class NetSvrPolicyLogin
		{
 			private:
				SharedPointerT<Net::Connection> m_pConnection;
			public:
			// Constructor
			NetSvrPolicyLogin ( const SharedPointerT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}
			NetSvrPolicyLogin ( const SharedPointerAtomicT<Net::Connection>& pConn ) : m_pConnection(pConn)
			{}

			// Cmd: Login request
			Result LoginRes( const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
			// Cmd: Login request with Facebook UID
			Result LoginByFacebookRes( const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
			// Cmd: Login request
			Result CreateRandomUserRes( const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
			// Cmd: Update my score and Get Ranking list
			Result UpdateMyScoreRes( const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
			// Cmd: Get Ranking lise
			Result GetRankingListRes( const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
			// Cmd: For network test
			Result DataTestRes( const Result &InResult, const Array<uint8_t>& InTestData );
			// Cmd: Write All!! User Score and Ranking list
			Result DebugPrintALLRankingRes( const Result &InResult );

		}; // class NetSvrPolicyLogin


	}; // namespace Policy
}; // namespace SF


