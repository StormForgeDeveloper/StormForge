////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Login Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFConnection.h"
#include "Protocol/Policy/LoginNetPolicy.h"
#include "Protocol/Message/LoginMsgClass.h"



namespace SF
{
 	namespace Policy
	{
 		// Cmd: Login request
		Result NetPolicyLogin::LoginCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::LoginCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameID, InID, InPassword);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::LoginCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
		// Cmd: Login request with Facebook UID
		Result NetPolicyLogin::LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::LoginByFacebookCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameID, InUID, InFaceBookName, InEMail, InFacebookToken);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
		// Cmd: Login request
		Result NetPolicyLogin::CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::CreateRandomUserCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InGameID, InCellPhone);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
		// Cmd: Update my score and Get Ranking list
		Result NetPolicyLogin::UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::UpdateMyScoreCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InRankingScore, InRankingType, InCount);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
		// Cmd: Get Ranking lise
		Result NetPolicyLogin::GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::GetRankingListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InRankingType, InBaseRanking, InCount);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
		// Cmd: For network test
		Result NetPolicyLogin::DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::DataTestCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTestData);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
		// C2S: Heartbit
		Result NetPolicyLogin::HeartBitC2SEvt(  )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::HeartBitC2SEvt::Create(m_pConnection->GetIOHeap());
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::HeartBitC2SEvt(  )
		// Cmd: Write All!! User Score and Ranking list
		Result NetPolicyLogin::DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::DebugPrintALLRankingCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InFileName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyLogin::DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName )


		// Cmd: Login request
		Result NetSvrPolicyLogin::LoginRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::LoginRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InGameServerAddr, InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::LoginRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		// Cmd: Login request with Facebook UID
		Result NetSvrPolicyLogin::LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::LoginByFacebookRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InGameServerAddr, InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		// Cmd: Login request
		Result NetSvrPolicyLogin::CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::CreateRandomUserRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InGameServerAddr, InGameServerAddrIPV4, InAccID, InTicket, InLoginEntityUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InGameServerAddr, const NetAddress &InGameServerAddrIPV4, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
		// Cmd: Update my score and Get Ranking list
		Result NetSvrPolicyLogin::UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::UpdateMyScoreRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InRanking);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		// Cmd: Get Ranking lise
		Result NetSvrPolicyLogin::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::GetRankingListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InRanking);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
		// Cmd: For network test
		Result NetSvrPolicyLogin::DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::DataTestRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InTestData);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
		// Cmd: Write All!! User Score and Ranking list
		Result NetSvrPolicyLogin::DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			ScopeContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Login::DebugPrintALLRankingRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyLogin::DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult )


	}; // namespace Policy
}; // namespace SF


