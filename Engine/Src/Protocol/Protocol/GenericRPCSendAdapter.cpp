////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Generic Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/GenericRPCSendAdapter.h"
#include "Protocol/GenericMessageID.h"
#include "Generic_generated.h"



namespace SF
{
 	// Cmd: Generic failure message
	Result GenericRPCSendAdapter::GenericFailureCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Generic::GenericFailureCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Generic::GenericFailureCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::Generic::MID_GenericFailureCmd, fbb));


		return hr;
	}; // Result GenericRPCSendAdapter::GenericFailureCmd( const TransactionID &InTransactionID )
	// Cmd: Generic transaction result
	Result GenericRPCSendAdapter::GenericTransactionCmd( const TransactionID &InTransactionID )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Generic::GenericTransactionCmdBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Generic::GenericTransactionCmd> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::Generic::MID_GenericTransactionCmd, fbb));


		return hr;
	}; // Result GenericRPCSendAdapter::GenericTransactionCmd( const TransactionID &InTransactionID )


	// Cmd: Generic failure message
	Result GenericSvrRPCSendAdapter::GenericFailureRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Generic::GenericFailureResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Generic::GenericFailureRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, InResult, Message::Generic::MID_GenericFailureRes, fbb));


		return hr;
	}; // Result GenericSvrRPCSendAdapter::GenericFailureRes( const TransactionID &InTransactionID, const Result &InResult )
	// Cmd: Generic transaction result
	Result GenericSvrRPCSendAdapter::GenericTransactionRes( const TransactionID &InTransactionID, const Result &InResult, const TransactionID &InFinishedTransaction, const char* InSignature )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto FinishedTransactionOffset = SF::Flat::Helper::CreateTransactionID(fbb, InFinishedTransaction);
		auto SignatureOffset = SF::Flat::Helper::CreateString(fbb, InSignature);
		SF::Flat::Generic::GenericTransactionResBuilder _builder(fbb);
		_builder.add_finished_transaction(FinishedTransactionOffset);
		_builder.add_signature(SignatureOffset);
		flatbuffers::Offset<SF::Flat::Generic::GenericTransactionRes> packetOffset = _builder.Finish();

		protocolCheck(Send(InTransactionID, InResult, Message::Generic::MID_GenericTransactionRes, fbb));


		return hr;
	}; // Result GenericSvrRPCSendAdapter::GenericTransactionRes( const TransactionID &InTransactionID, const Result &InResult, const TransactionID &InFinishedTransaction, const char* InSignature )


}; // namespace SF


