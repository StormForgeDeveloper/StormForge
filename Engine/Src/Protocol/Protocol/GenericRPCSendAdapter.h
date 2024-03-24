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
		GenericRPCSendAdapter (MessageEndpoint* pEndpoint, flatbuffers::FlatBufferBuilder* pBuilder = nullptr) : RPCSendAdapter(pEndpoint, pBuilder)
		{}
		GenericRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Generic failure message
		Result GenericFailureCmd( const TransactionID &InTransactionID );
		// Cmd: Generic transaction result
		Result GenericTransactionCmd( const TransactionID &InTransactionID );

	}; // class GenericRPCSendAdapter : public RPCSendAdapter


	class GenericSvrRPCSendAdapter : public RPCSendAdapter
	{
 		public:
		// Constructor
		GenericSvrRPCSendAdapter (MessageEndpoint* pEndpoint, flatbuffers::FlatBufferBuilder* pBuilder = nullptr) : RPCSendAdapter(pEndpoint, pBuilder)
		{}
		GenericSvrRPCSendAdapter (const SharedPointerT<MessageEndpoint>& pEndpoint) : RPCSendAdapter(pEndpoint.get())
		{}

		// Cmd: Generic failure message
		Result GenericFailureRes( const TransactionID &InTransactionID, const Result &InResult );
		// Cmd: Generic transaction result
		Result GenericTransactionRes( const TransactionID &InTransactionID, const Result &InResult, const TransactionID &InFinishedTransaction, const char* InSignature );

	}; // class GenericSvrRPCSendAdapter : public RPCSendAdapter


}; // namespace SF


