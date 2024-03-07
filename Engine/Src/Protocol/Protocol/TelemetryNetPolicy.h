////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Telemetry Message debug definitions
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


	class NetPolicyTelemetry 
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetPolicyTelemetry (const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Post telemetry event
		Result PostEventCmd( const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes );

	}; // class NetPolicyTelemetry 


	class NetSvrPolicyTelemetry
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetSvrPolicyTelemetry ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Post telemetry event
		Result PostEventRes( const TransactionID &InTransactionID, const Result &InResult );

	}; // class NetSvrPolicyTelemetry


}; // namespace SF


