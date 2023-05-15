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
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginCmd::CalculateMessageSize(InTransactionID, InGameID, InID, InPassword);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginCmd::Create(messageBuffer, InTransactionID, InGameID, InID, InPassword));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::LoginCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword )
	// Cmd: Login request with Facebook UID
	Result NetPolicyLogin::LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginByFacebookCmd::CalculateMessageSize(InTransactionID, InGameID, InUID, InFaceBookName, InEMail, InFacebookToken);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginByFacebookCmd::Create(messageBuffer, InTransactionID, InGameID, InUID, InFaceBookName, InEMail, InFacebookToken));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::LoginByFacebookCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken )
	// Cmd: Login request with Facebook UID
	Result NetPolicyLogin::LoginBySteamCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginBySteamCmd::CalculateMessageSize(InTransactionID, InGameID, InSteamUserID, InSteamUserName, InSteamUserToken);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginBySteamCmd::Create(messageBuffer, InTransactionID, InGameID, InSteamUserID, InSteamUserName, InSteamUserToken));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::LoginBySteamCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken )
	// Cmd: Login request
	Result NetPolicyLogin::CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::CreateRandomUserCmd::CalculateMessageSize(InTransactionID, InGameID, InCellPhone);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::CreateRandomUserCmd::Create(messageBuffer, InTransactionID, InGameID, InCellPhone));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::CreateRandomUserCmd( const uint64_t &InTransactionID, const uint32_t &InGameID, const char* InCellPhone )
	// Cmd: Update my score and Get Ranking list
	Result NetPolicyLogin::UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::UpdateMyScoreCmd::CalculateMessageSize(InTransactionID, InRankingScore, InRankingType, InCount);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::UpdateMyScoreCmd::Create(messageBuffer, InTransactionID, InRankingScore, InRankingType, InCount));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::UpdateMyScoreCmd( const uint64_t &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount )
	// Cmd: Get Ranking lise
	Result NetPolicyLogin::GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::GetRankingListCmd::CalculateMessageSize(InTransactionID, InRankingType, InBaseRanking, InCount);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::GetRankingListCmd::Create(messageBuffer, InTransactionID, InRankingType, InBaseRanking, InCount));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::GetRankingListCmd( const uint64_t &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount )
	// Cmd: For network test
	Result NetPolicyLogin::DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::DataTestCmd::CalculateMessageSize(InTransactionID, InTestData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::DataTestCmd::Create(messageBuffer, InTransactionID, InTestData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::DataTestCmd( const uint64_t &InTransactionID, const Array<uint8_t>& InTestData )
	// C2S: Heartbeat
	Result NetPolicyLogin::HeartbeatC2SEvt(  )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::HeartbeatC2SEvt::CalculateMessageSize();
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::HeartbeatC2SEvt::Create(messageBuffer));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::HeartbeatC2SEvt(  )
	// Cmd: Write All!! User Score and Ranking list
	Result NetPolicyLogin::DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::DebugPrintALLRankingCmd::CalculateMessageSize(InTransactionID, InFileName);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::DebugPrintALLRankingCmd::Create(messageBuffer, InTransactionID, InFileName));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::DebugPrintALLRankingCmd( const uint64_t &InTransactionID, const char* InFileName )


	// Cmd: Login request
	Result NetSvrPolicyLogin::LoginRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginRes::CalculateMessageSize(InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginRes::Create(messageBuffer, InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::LoginRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	// Cmd: Login request with Facebook UID
	Result NetSvrPolicyLogin::LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginByFacebookRes::CalculateMessageSize(InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginByFacebookRes::Create(messageBuffer, InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::LoginByFacebookRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	// Cmd: Login request with Facebook UID
	Result NetSvrPolicyLogin::LoginBySteamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginBySteamRes::CalculateMessageSize(InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginBySteamRes::Create(messageBuffer, InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID, InErrorReason));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::LoginBySteamRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason )
	// Cmd: Login request
	Result NetSvrPolicyLogin::CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::CreateRandomUserRes::CalculateMessageSize(InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::CreateRandomUserRes::Create(messageBuffer, InTransactionID, InResult, InGameServerPublicAddress, InAccID, InTicket, InLoginEntityUID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::CreateRandomUserRes( const uint64_t &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID )
	// Cmd: Update my score and Get Ranking list
	Result NetSvrPolicyLogin::UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::UpdateMyScoreRes::CalculateMessageSize(InTransactionID, InResult, InRanking);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::UpdateMyScoreRes::Create(messageBuffer, InTransactionID, InResult, InRanking));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::UpdateMyScoreRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: Get Ranking lise
	Result NetSvrPolicyLogin::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::GetRankingListRes::CalculateMessageSize(InTransactionID, InResult, InRanking);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::GetRankingListRes::Create(messageBuffer, InTransactionID, InResult, InRanking));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking )
	// Cmd: For network test
	Result NetSvrPolicyLogin::DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::DataTestRes::CalculateMessageSize(InTransactionID, InResult, InTestData);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::DataTestRes::Create(messageBuffer, InTransactionID, InResult, InTestData));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::DataTestRes( const uint64_t &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData )
	// Cmd: Write All!! User Score and Ranking list
	Result NetSvrPolicyLogin::DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::DebugPrintALLRankingRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::DebugPrintALLRankingRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::DebugPrintALLRankingRes( const uint64_t &InTransactionID, const Result &InResult )


}; // namespace SF


