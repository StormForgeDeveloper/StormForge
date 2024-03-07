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
#include "SFProtocol.h"
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

		// Cmd: Login with ID/PW request
		Result LoginCmd( const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID );
		// Cmd: Login with steam login info
		Result LoginWithSteamCmd( const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID );

	}; // class NetPolicyLogin 


	class NetSvrPolicyLogin
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetSvrPolicyLogin ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Login with ID/PW request
		Result LoginRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress );
		// Cmd: Login with steam login info
		Result LoginWithSteamRes( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress );

	}; // class NetSvrPolicyLogin


}; // namespace SF


