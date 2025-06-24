////////////////////////////////////////////////////////////////////////////////
// 
// StormForge
// 
// Author : Generated
// 
// Description : Generic RPC Send interface
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFProtocol.h"
#include "Net/SFNetDef.h"
#include "MessageBus/SFRPCSendAdapter.h"
#include "Protocol/GenericMessageID.h"




namespace SF
{
    class MessageEndpoint;
   class VariableTable;
   struct ActorMovement;


	class GenericRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		GenericRPCSendAdapter (MessageEndpoint* pEndpoint) : RPCSendAdapter(pEndpoint)
		{}
		GenericRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Generic failure message
		Result GenericFailureCmd( const TransactionID &InTransactionID );
		// Cmd: Generic transaction result
		Result GenericTransactionCmd( const TransactionID &InTransactionID );
		// C2S: Client heartbeat
		Result HeartbeatC2SEvt(  );
		// Cmd: Post log data through gateway
		Result PostLogDataCmd( const TransactionID &InTransactionID, const char* InDestLogChannel, const Array<uint8_t>& InMessageData );

	}; // class GenericRPCSendAdapter : public RPCSendAdapter


	class GenericSvrRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		GenericSvrRPCSendAdapter (MessageEndpoint* pEndpoint) : RPCSendAdapter(pEndpoint)
		{}
		GenericSvrRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Generic failure message
		Result GenericFailureRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Generic transaction result
		Result GenericTransactionRes( const TransactionID &InTransactionID, const Result &InResult, const TransactionID &InFinishedTransaction, const char* InSignature );
		// Cmd: Post log data through gateway
		Result PostLogDataRes( const TransactionID &InTransactionID, const Result &InResult );

	}; // class GenericSvrRPCSendAdapter : public RPCSendAdapter


}; // namespace SF


