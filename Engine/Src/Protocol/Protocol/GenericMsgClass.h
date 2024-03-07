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

#include "SFProtocol.h"
#include "Net/SFMessage.h"
#include "Types/SFEngineTypedefs.h"
#include "Variable/SFVariableTable.h"
#include "Container/SFArray.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Variable/SFVariableMapBuilder.h"
#include "Protocol/GenericMessageID.h"



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
				static constexpr MessageID MID = MID_GenericFailureCmd;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 1,
				}; // enum ParameterTypeInfo
			public:
			private:
				RouteContext m_RouteContext{};
				TransactionID m_TransactionID{};
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
				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const RouteContext &InRouteContext, const TransactionID &InTransactionID );
				static Result Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const TransactionID &InTransactionID );

			}; // class GenericFailureCmd : public MessageBase

			class GenericFailureRes : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_GenericFailureRes;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasTransactionID = 1,
					HasRouteContext = 1,
				}; // enum ParameterTypeInfo
			public:
			private:
				RouteContext m_RouteContext{};
				TransactionID m_TransactionID{};
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
				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const Result& GetResult() const	{ return m_Result; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const RouteContext &InRouteContext, const TransactionID &InTransactionID, const Result &InResult );
				static Result Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const TransactionID &InTransactionID, const Result &InResult );

			}; // class GenericFailureRes : public MessageBase





		}; // namespace Generic
	}; // namespace Message
}; // namespace SF


