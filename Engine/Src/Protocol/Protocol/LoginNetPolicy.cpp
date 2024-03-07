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
 	// Cmd: Login with ID/PW request
	Result NetPolicyLogin::LoginCmd( const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginCmd::CalculateMessageSize(InTransactionID, Inuser_id, Inpassword, InGameID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginCmd::Create(messageBuffer, InTransactionID, Inuser_id, Inpassword, InGameID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::LoginCmd( const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID )
	// Cmd: Login with steam login info
	Result NetPolicyLogin::LoginWithSteamCmd( const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginWithSteamCmd::CalculateMessageSize(InTransactionID, InSteamAppID, InSteamPlayerID, InSteamPlayerName, InSteamPlayerToken, InGameID);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginWithSteamCmd::Create(messageBuffer, InTransactionID, InSteamAppID, InSteamPlayerID, InSteamPlayerName, InSteamPlayerToken, InGameID));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyLogin::LoginWithSteamCmd( const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID )


	// Cmd: Login with ID/PW request
	Result NetSvrPolicyLogin::LoginRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginRes::CalculateMessageSize(InTransactionID, InResult, InNickName, InAccountID, InAuthTicket, InBannedReason, InGameServerAddress);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginRes::Create(messageBuffer, InTransactionID, InResult, InNickName, InAccountID, InAuthTicket, InBannedReason, InGameServerAddress));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::LoginRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
	// Cmd: Login with steam login info
	Result NetSvrPolicyLogin::LoginWithSteamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )
	{
 		Result hr;

		size_t messageSize = SF::Message::Login::LoginWithSteamRes::CalculateMessageSize(InTransactionID, InResult, InNickName, InAccountID, InAuthTicket, InBannedReason, InGameServerAddress);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Login::LoginWithSteamRes::Create(messageBuffer, InTransactionID, InResult, InNickName, InAccountID, InAuthTicket, InBannedReason, InGameServerAddress));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyLogin::LoginWithSteamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress )


}; // namespace SF


