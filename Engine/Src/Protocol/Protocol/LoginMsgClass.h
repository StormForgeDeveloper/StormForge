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

#include "Protocol/SFProtocol.h"
#include "Net/SFMessage.h"
#include "Types/SFEngineTypedefs.h"
#include "Variable/SFVariableTable.h"
#include "Container/SFArray.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Variable/SFVariableMapBuilder.h"



namespace SF
{
 	namespace Message
	{
 		namespace Login
		{
 			// Cmd: Login request
			class LoginCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				uint32_t m_GameID{};
				const char* m_ID{};
				const char* m_Password{};
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
				const uint32_t& GetGameID() const	{ return m_GameID; };
				const char* GetID() const	{ return m_ID; };
				const char* GetPassword() const	{ return m_Password; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InGameID, const char* InID, const char* InPassword );

			}; // class LoginCmd : public MessageBase

			class LoginRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				const char* m_GameServerPublicAddress{};
				AccountID m_AccID{};
				AuthTicket m_Ticket{};
				uint64_t m_LoginEntityUID{};
				const char* m_ErrorReason{};
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
				const char* GetGameServerPublicAddress() const	{ return m_GameServerPublicAddress; };
				const AccountID& GetAccID() const	{ return m_AccID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const uint64_t& GetLoginEntityUID() const	{ return m_LoginEntityUID; };
				const char* GetErrorReason() const	{ return m_ErrorReason; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason );

			}; // class LoginRes : public MessageBase

			// Cmd: Login request with Facebook UID
			class LoginByFacebookCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				uint32_t m_GameID{};
				uint64_t m_UID{};
				const char* m_FaceBookName{};
				const char* m_EMail{};
				const char* m_FacebookToken{};
			public:
				LoginByFacebookCmd()
					{}

				LoginByFacebookCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginByFacebookCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetGameID() const	{ return m_GameID; };
				const uint64_t& GetUID() const	{ return m_UID; };
				const char* GetFaceBookName() const	{ return m_FaceBookName; };
				const char* GetEMail() const	{ return m_EMail; };
				const char* GetFacebookToken() const	{ return m_FacebookToken; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InGameID, const uint64_t &InUID, const char* InFaceBookName, const char* InEMail, const char* InFacebookToken );

			}; // class LoginByFacebookCmd : public MessageBase

			class LoginByFacebookRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				const char* m_GameServerPublicAddress{};
				AccountID m_AccID{};
				AuthTicket m_Ticket{};
				uint64_t m_LoginEntityUID{};
				const char* m_ErrorReason{};
			public:
				LoginByFacebookRes()
					{}

				LoginByFacebookRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginByFacebookRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetGameServerPublicAddress() const	{ return m_GameServerPublicAddress; };
				const AccountID& GetAccID() const	{ return m_AccID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const uint64_t& GetLoginEntityUID() const	{ return m_LoginEntityUID; };
				const char* GetErrorReason() const	{ return m_ErrorReason; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason );

			}; // class LoginByFacebookRes : public MessageBase

			// Cmd: Login request with Facebook UID
			class LoginBySteamCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				uint32_t m_GameID{};
				uint64_t m_SteamUserID{};
				const char* m_SteamUserName{};
				const char* m_SteamUserToken{};
			public:
				LoginBySteamCmd()
					{}

				LoginBySteamCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginBySteamCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetGameID() const	{ return m_GameID; };
				const uint64_t& GetSteamUserID() const	{ return m_SteamUserID; };
				const char* GetSteamUserName() const	{ return m_SteamUserName; };
				const char* GetSteamUserToken() const	{ return m_SteamUserToken; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InGameID, const uint64_t &InSteamUserID, const char* InSteamUserName, const char* InSteamUserToken );

			}; // class LoginBySteamCmd : public MessageBase

			class LoginBySteamRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				const char* m_GameServerPublicAddress{};
				AccountID m_AccID{};
				AuthTicket m_Ticket{};
				uint64_t m_LoginEntityUID{};
				const char* m_ErrorReason{};
			public:
				LoginBySteamRes()
					{}

				LoginBySteamRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				LoginBySteamRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetGameServerPublicAddress() const	{ return m_GameServerPublicAddress; };
				const AccountID& GetAccID() const	{ return m_AccID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const uint64_t& GetLoginEntityUID() const	{ return m_LoginEntityUID; };
				const char* GetErrorReason() const	{ return m_ErrorReason; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID, const char* InErrorReason );

			}; // class LoginBySteamRes : public MessageBase

			// Cmd: Login request
			class CreateRandomUserCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				uint32_t m_GameID{};
				const char* m_CellPhone{};
			public:
				CreateRandomUserCmd()
					{}

				CreateRandomUserCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateRandomUserCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint32_t& GetGameID() const	{ return m_GameID; };
				const char* GetCellPhone() const	{ return m_CellPhone; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint32_t &InGameID, const char* InCellPhone );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint32_t &InGameID, const char* InCellPhone );

			}; // class CreateRandomUserCmd : public MessageBase

			class CreateRandomUserRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				const char* m_GameServerPublicAddress{};
				AccountID m_AccID{};
				AuthTicket m_Ticket{};
				uint64_t m_LoginEntityUID{};
			public:
				CreateRandomUserRes()
					{}

				CreateRandomUserRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				CreateRandomUserRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const char* GetGameServerPublicAddress() const	{ return m_GameServerPublicAddress; };
				const AccountID& GetAccID() const	{ return m_AccID; };
				const AuthTicket& GetTicket() const	{ return m_Ticket; };
				const uint64_t& GetLoginEntityUID() const	{ return m_LoginEntityUID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const char* InGameServerPublicAddress, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );

			}; // class CreateRandomUserRes : public MessageBase

			// Cmd: Update my score and Get Ranking list
			class UpdateMyScoreCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				uint64_t m_RankingScore{};
				RankingType m_RankingType{};
				uint16_t m_Count{};
			public:
				UpdateMyScoreCmd()
					{}

				UpdateMyScoreCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UpdateMyScoreCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const uint64_t& GetRankingScore() const	{ return m_RankingScore; };
				const RankingType& GetRankingType() const	{ return m_RankingType; };
				const uint16_t& GetCount() const	{ return m_Count; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const uint64_t &InRankingScore, const RankingType &InRankingType, const uint16_t &InCount );

			}; // class UpdateMyScoreCmd : public MessageBase

			class UpdateMyScoreRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				ArrayView<TotalRankingPlayerInformation> m_Ranking;
			public:
				UpdateMyScoreRes()
					{}

				UpdateMyScoreRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				UpdateMyScoreRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<TotalRankingPlayerInformation>& GetRanking() const	{ return m_Ranking; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );

			}; // class UpdateMyScoreRes : public MessageBase

			// Cmd: Get Ranking lise
			class GetRankingListCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				RankingType m_RankingType{};
				uint8_t m_BaseRanking{};
				uint8_t m_Count{};
			public:
				GetRankingListCmd()
					{}

				GetRankingListCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetRankingListCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const RankingType& GetRankingType() const	{ return m_RankingType; };
				const uint8_t& GetBaseRanking() const	{ return m_BaseRanking; };
				const uint8_t& GetCount() const	{ return m_Count; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const RankingType &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );

			}; // class GetRankingListCmd : public MessageBase

			class GetRankingListRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				ArrayView<TotalRankingPlayerInformation> m_Ranking;
			public:
				GetRankingListRes()
					{}

				GetRankingListRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GetRankingListRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<TotalRankingPlayerInformation>& GetRanking() const	{ return m_Ranking; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );

			}; // class GetRankingListRes : public MessageBase

			// Cmd: For network test
			class DataTestCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				ArrayView<uint8_t> m_TestData;
			public:
				DataTestCmd()
					{}

				DataTestCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DataTestCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Array<uint8_t>& GetTestData() const	{ return m_TestData; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Array<uint8_t>& InTestData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Array<uint8_t>& InTestData );

			}; // class DataTestCmd : public MessageBase

			class DataTestRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				ArrayView<uint8_t> m_TestData;
			public:
				DataTestRes()
					{}

				DataTestRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DataTestRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };
				const Array<uint8_t>& GetTestData() const	{ return m_TestData; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult, const Array<uint8_t>& InTestData );

			}; // class DataTestRes : public MessageBase

			// C2S: Heartbeat
			class HeartbeatC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 0,
					HasRouteContext = 0,
				}; // enum ParameterTypeInfo
			public:
				TransactionID GetTransactionID() { return TransactionID{}; }
				RouteContext GetRouteContext() { return RouteContext{}; }
			private:
			public:
				HeartbeatC2SEvt()
					{}

				HeartbeatC2SEvt( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				HeartbeatC2SEvt( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}


				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize(  );
				static Result Create( MessageHeader* messageBuffer );

			}; // class HeartbeatC2SEvt : public MessageBase

			// Cmd: Write All!! User Score and Ranking list
			class DebugPrintALLRankingCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
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
				const char* m_FileName{};
			public:
				DebugPrintALLRankingCmd()
					{}

				DebugPrintALLRankingCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DebugPrintALLRankingCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetFileName() const	{ return m_FileName; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InFileName );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InFileName );

			}; // class DebugPrintALLRankingCmd : public MessageBase

			class DebugPrintALLRankingRes : public MessageBase
			{
 			public:
				static const MessageID MID;
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
			public:
				DebugPrintALLRankingRes()
					{}

				DebugPrintALLRankingRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				DebugPrintALLRankingRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult );

			}; // class DebugPrintALLRankingRes : public MessageBase





		}; // namespace Login
	}; // namespace Message
}; // namespace SF


