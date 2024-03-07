////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Telemetry Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/TelemetryNetPolicy.h"
#include "Protocol/TelemetryMsgClass.h"



namespace SF
{
 	// Cmd: Post telemetry event
	Result NetPolicyTelemetry::PostEventCmd( const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes )
	{
 		Result hr;

		size_t messageSize = SF::Message::Telemetry::PostEventCmd::CalculateMessageSize(InTransactionID, InEventName, InTimeStamp, InAppID, InMachineID, InEventID, InAccountID, InIsPlayEvent, InSessionID, InAttributes);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Telemetry::PostEventCmd::Create(messageBuffer, InTransactionID, InEventName, InTimeStamp, InAppID, InMachineID, InEventID, InAccountID, InIsPlayEvent, InSessionID, InAttributes));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetPolicyTelemetry::PostEventCmd( const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes )


	// Cmd: Post telemetry event
	Result NetSvrPolicyTelemetry::PostEventRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		size_t messageSize = SF::Message::Telemetry::PostEventRes::CalculateMessageSize(InTransactionID, InResult);
		SFNET_ALLOC_MESSAGE_FROM_STACK(messageBuffer,messageSize);
		protocolCheckPtr(m_Endpoint);

		protocolCheck(SF::Message::Telemetry::PostEventRes::Create(messageBuffer, InTransactionID, InResult));
		return m_Endpoint->SendMsg(messageBuffer);

	}; // Result NetSvrPolicyTelemetry::PostEventRes( const TransactionID &InTransactionID, const Result &InResult )


}; // namespace SF


