////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Login Message parser definitions
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFProtocol.h"
#include "Net/SFMessage.h"
#include "Types/SFEngineTypedefs.h"
#include "Variable/SFVariableTable.h"
#include "Container/SFArray.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Variable/SFVariableMapBuilder.h"
#include "Protocol/LoginMessageID.h"



namespace SF
{
 	namespace Message
	{
 		namespace Login
		{
 			// Cmd: Login with ID/PW request
			class LoginCmd : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_LoginCmd;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				const char* m_user_id{};
				const char* m_password{};
				const char* m_GameID{};
			public:
				LoginCmd()
					{}

				LoginCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* Getuser_id() const	{ return m_user_id; };
				const char* Getpassword() const	{ return m_password; };
				const char* GetGameID() const	{ return m_GameID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* Inuser_id, const char* Inpassword, const char* InGameID );

			}; // class LoginCmd : public MessageBase

			class LoginRes : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_LoginRes;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				const char* m_NickName{};
				AccountID m_AccountID{};
				AuthTicket m_AuthTicket{};
				const char* m_BannedReason{};
				const char* m_GameServerAddress{};
			public:
				LoginRes()
					{}

				LoginRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetNickName() const	{ return m_NickName; };
				const AccountID& GetAccountID() const	{ return m_AccountID; };
				const AuthTicket& GetAuthTicket() const	{ return m_AuthTicket; };
				const char* GetBannedReason() const	{ return m_BannedReason; };
				const char* GetGameServerAddress() const	{ return m_GameServerAddress; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress );

			}; // class LoginRes : public MessageBase

			// Cmd: Login with steam login info
			class LoginWithSteamCmd : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_LoginWithSteamCmd;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				uint64_t m_SteamAppID{};
				uint64_t m_SteamPlayerID{};
				const char* m_SteamPlayerName{};
				const char* m_SteamPlayerToken{};
				const char* m_GameID{};
			public:
				LoginWithSteamCmd()
					{}

				LoginWithSteamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginWithSteamCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetSteamAppID() const	{ return m_SteamAppID; };
				const uint64_t& GetSteamPlayerID() const	{ return m_SteamPlayerID; };
				const char* GetSteamPlayerName() const	{ return m_SteamPlayerName; };
				const char* GetSteamPlayerToken() const	{ return m_SteamPlayerToken; };
				const char* GetGameID() const	{ return m_GameID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InSteamAppID, const uint64_t &InSteamPlayerID, const char* InSteamPlayerName, const char* InSteamPlayerToken, const char* InGameID );

			}; // class LoginWithSteamCmd : public MessageBase

			class LoginWithSteamRes : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_LoginWithSteamRes;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
				TransactionID m_TransactionID{};
				Result m_Result{};
				const char* m_NickName{};
				AccountID m_AccountID{};
				AuthTicket m_AuthTicket{};
				const char* m_BannedReason{};
				const char* m_GameServerAddress{};
			public:
				LoginWithSteamRes()
					{}

				LoginWithSteamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginWithSteamRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetNickName() const	{ return m_NickName; };
				const AccountID& GetAccountID() const	{ return m_AccountID; };
				const AuthTicket& GetAuthTicket() const	{ return m_AuthTicket; };
				const char* GetBannedReason() const	{ return m_BannedReason; };
				const char* GetGameServerAddress() const	{ return m_GameServerAddress; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InNickName, const AccountID &InAccountID, const AuthTicket &InAuthTicket, const char* InBannedReason, const char* InGameServerAddress );

			}; // class LoginWithSteamRes : public MessageBase





		}; // namespace Login
	}; // namespace Message
}; // namespace SF


