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
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/LoginNetPolicy.h"
#include "Protocol/LoginMsgClass.h"



namespace SF
{
 	// Cmd: Login request
	Result NetPolicyLogin::LoginCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::LoginCmd::Create(GetSystemHeap(), InTransactionID, InGameID, InID, InPassword);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::LoginCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
	// Cmd: Login request with Facebook UID
	Result NetPolicyLogin::LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::LoginByFacebookCmd::Create(GetSystemHeap(), InTransactionID, InGameID, InUID, InFaceBookName, InEMail, InFacebookToken);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
	// Cmd: Login request with Facebook UID
	Result NetPolicyLogin::LoginBySteamCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::LoginBySteamCmd::Create(GetSystemHeap(), InTransactionID, InGameID, InSteamUserID, InSteamUserName, InSteamUserToken);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::LoginBySteamCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )
	// Cmd: Login request
	Result NetPolicyLogin::CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::CreateRandomUserCmd::Create(GetSystemHeap(), InTransactionID, InGameID, InCellPhone);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
	// Cmd: Update my score and Get Ranking list
	Result NetPolicyLogin::UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::UpdateMyScoreCmd::Create(GetSystemHeap(), InTransactionID, InRankingScore, InRankingType, InCount);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
	// Cmd: Get Ranking lise
	Result NetPolicyLogin::GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::GetRankingListCmd::Create(GetSystemHeap(), InTransactionID, InRankingType, InBaseRanking, InCount);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	// Cmd: For network test
	Result NetPolicyLogin::DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::DataTestCmd::Create(GetSystemHeap(), InTransactionID, InTestData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
	// C2S: Heartbeat
	Result NetPolicyLogin::HeartbeatC2SEvt(  )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::HeartbeatC2SEvt::Create(GetSystemHeap());
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::HeartbeatC2SEvt(  )
	// Cmd: Write All!! User Score and Ranking list
	Result NetPolicyLogin::DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::DebugPrintALLRankingCmd::Create(GetSystemHeap(), InTransactionID, InFileName);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetPolicyLogin::DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName )


	// Cmd: Login request
	Result NetSvrPolicyLogin::LoginRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::LoginRes::Create(GetSystemHeap(), InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::LoginRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	// Cmd: Login request with Facebook UID
	Result NetSvrPolicyLogin::LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::LoginByFacebookRes::Create(GetSystemHeap(), InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	// Cmd: Login request with Facebook UID
	Result NetSvrPolicyLogin::LoginBySteamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::LoginBySteamRes::Create(GetSystemHeap(), InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::LoginBySteamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	// Cmd: Login request
	Result NetSvrPolicyLogin::CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::CreateRandomUserRes::Create(GetSystemHeap(), InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	// Cmd: Update my score and Get Ranking list
	Result NetSvrPolicyLogin::UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::UpdateMyScoreRes::Create(GetSystemHeap(), InTransactionID, InResult, InRanking);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: Get Ranking lise
	Result NetSvrPolicyLogin::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::GetRankingListRes::Create(GetSystemHeap(), InTransactionID, InResult, InRanking);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: For network test
	Result NetSvrPolicyLogin::DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::DataTestRes::Create(GetSystemHeap(), InTransactionID, InResult, InTestData);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
	// Cmd: Write All!! User Score and Ranking list
	Result NetSvrPolicyLogin::DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		ScopeContext hr;

		 MessageDataPtr pMessage;
		 protocolCheckPtr(m_Endpoint);

		 pMessage = SF::Message::Login::DebugPrintALLRankingRes::Create(GetSystemHeap(), InTransactionID, InResult);
		 protocolCheckPtr(*pMessage);

		 return m_Endpoint->Send( pMessage );

	}; // Result NetSvrPolicyLogin::DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult )


}; // namespace SF


