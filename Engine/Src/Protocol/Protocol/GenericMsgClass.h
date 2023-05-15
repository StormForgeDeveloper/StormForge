////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Generic Message parser definitions
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
 		namespace Generic
		{
 			// Cmd: Generic failure message
			class GenericFailureCmd : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 1,
				}; // enum ParameterTypeInfo
			public:
			private:
				RouteContext m_RouteContext{};
				uint64_t m_TransactionID{};
			public:
				GenericFailureCmd()
					{}

				GenericFailureCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GenericFailureCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const RouteContext& GetRouteContext() const	{ return m_RouteContext; };
				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const RouteContext &InRouteContext, const uint64_t &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const uint64_t &InTransactionID );

			}; // class GenericFailureCmd : public MessageBase

			class GenericFailureRes : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 1,
				}; // enum ParameterTypeInfo
			public:
			private:
				RouteContext m_RouteContext{};
				uint64_t m_TransactionID{};
				Result m_Result{};
			public:
				GenericFailureRes()
					{}

				GenericFailureRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				GenericFailureRes( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const RouteContext& GetRouteContext() const	{ return m_RouteContext; };
				const uint64_t& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult );

			}; // class GenericFailureRes : public MessageBase





		}; // namespace Generic
	}; // namespace Message
}; // namespace SF


