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
		// Cmd: Message bus send message warpper through gateway. it conveys other message inside
		Result MessageBusSendCmd( const TransactionID &InTransactionID );
		// Cmd: Listen to the message
		Result MessageBusListenCmd( const TransactionID &InTransactionID );
		// Cmd: Post log data through gateway
		Result PostLogDataCmd( const TransactionID &InTransactionID );

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
		// Cmd: Message bus send message warpper through gateway. it conveys other message inside
		Result MessageBusSendRes( const TransactionID &InTransactionID, const Result &InResult, const char* InDestChannel, const Array<uint8_t>& InMessageData );
		// Cmd: Listen to the message
		Result MessageBusListenRes( const TransactionID &InTransactionID, const Result &InResult, const char* InChannelToListen );
		// Cmd: Post log data through gateway
		Result PostLogDataRes( const TransactionID &InTransactionID, const Result &InResult, const char* InDestLogChannel, const Array<uint8_t>& InMessageData );

	}; // class GenericSvrRPCSendAdapter : public RPCSendAdapter


}; // namespace SF


