////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Telemetry Message parser definitions
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
#include "Protocol/TelemetryMessageID.h"



namespace SF
{
 	namespace Message
	{
 		namespace Telemetry
		{
 			// Cmd: Post telemetry event
			class PostEventCmd : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_PostEventCmd;
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
				const char* m_EventName{};
				uint64_t m_TimeStamp{};
				const char* m_AppID{};
				const char* m_MachineID{};
				uint32_t m_EventID{};
				AccountID m_AccountID{};
				uint8 m_IsPlayEvent{};
				ArrayView<uint8_t> m_SessionID;
				ArrayView<NamedVariable> m_Attributes;
			public:
				PostEventCmd()
					{}

				PostEventCmd( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PostEventCmd( const MessageHeader* pHeader )
					: MessageBase(pHeader)
					{}

				const TransactionID& GetTransactionID() const	{ return m_TransactionID; };
				const char* GetEventName() const	{ return m_EventName; };
				const uint64_t& GetTimeStamp() const	{ return m_TimeStamp; };
				const char* GetAppID() const	{ return m_AppID; };
				const char* GetMachineID() const	{ return m_MachineID; };
				const uint32_t& GetEventID() const	{ return m_EventID; };
				const AccountID& GetAccountID() const	{ return m_AccountID; };
				const uint8& GetIsPlayEvent() const	{ return m_IsPlayEvent; };
				const Array<uint8_t>& GetSessionID() const	{ return m_SessionID; };
				const Array<NamedVariable>& GetAttributes() const	{ return m_Attributes; };

				static Result TraceOut(const char* prefix, const MessageHeader* pHeader);

				virtual Result ParseMessage(const MessageHeader* pHeader);
				static Result ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase(IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMsgBase);

				static size_t CalculateMessageSize( const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes );
				static Result Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes );

			}; // class PostEventCmd : public MessageBase

			class PostEventRes : public MessageBase
			{
 			public:
				static constexpr MessageID MID = MID_PostEventRes;
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
				PostEventRes()
					{}

				PostEventRes( const MessageDataPtr &pMsg )
					: MessageBase(pMsg)
					{}

				PostEventRes( const MessageHeader* pHeader )
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

			}; // class PostEventRes : public MessageBase





		}; // namespace Telemetry
	}; // namespace Message
}; // namespace SF


