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
		fbb.Finish(packetOffset);

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
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::Generic::MID_GenericTransactionCmd, fbb));


		return hr;
	}; // Result GenericRPCSendAdapter::GenericTransactionCmd( const TransactionID &InTransactionID )
	// C2S: Client heartbeat
	Result GenericRPCSendAdapter::HeartbeatC2SEvt(  )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Generic::HeartbeatC2SEvtBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Generic::HeartbeatC2SEvt> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(TransactionID(), ResultCode::SUCCESS, Message::Generic::MID_HeartbeatC2SEvt, fbb));


		return hr;
	}; // Result GenericRPCSendAdapter::HeartbeatC2SEvt(  )
	// Cmd: Post log data through gateway
	Result GenericRPCSendAdapter::PostLogDataCmd( const TransactionID &InTransactionID, const char* InDestLogChannel, const Array<uint8_t>& InMessageData )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		auto DestLogChannelOffset = SF::Flat::Helper::CreateString(fbb, InDestLogChannel);
		auto MessageDataOffset = SF::Flat::Helper::Createuint8Vector(fbb, InMessageData);
		SF::Flat::Generic::PostLogDataCmdBuilder _builder(fbb);
		_builder.add_dest_log_channel(DestLogChannelOffset);
		_builder.add_message_data(MessageDataOffset);
		flatbuffers::Offset<SF::Flat::Generic::PostLogDataCmd> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, ResultCode::SUCCESS, Message::Generic::MID_PostLogDataCmd, fbb));


		return hr;
	}; // Result GenericRPCSendAdapter::PostLogDataCmd( const TransactionID &InTransactionID, const char* InDestLogChannel, const Array<uint8_t>& InMessageData )


	// Cmd: Generic failure message
	Result GenericSvrRPCSendAdapter::GenericFailureRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Generic::GenericFailureResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Generic::GenericFailureRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

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
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::Generic::MID_GenericTransactionRes, fbb));


		return hr;
	}; // Result GenericSvrRPCSendAdapter::GenericTransactionRes( const TransactionID &InTransactionID, const Result &InResult, const TransactionID &InFinishedTransaction, const char* InSignature )
	// Cmd: Post log data through gateway
	Result GenericSvrRPCSendAdapter::PostLogDataRes( const TransactionID &InTransactionID, const Result &InResult )
	{
 		Result hr;

		protocolCheckPtr(m_Endpoint);

		flatbuffers::FlatBufferBuilder& fbb = GetBuilderForNew();
		SF::Flat::Generic::PostLogDataResBuilder _builder(fbb);
		flatbuffers::Offset<SF::Flat::Generic::PostLogDataRes> packetOffset = _builder.Finish();
		fbb.Finish(packetOffset);

		protocolCheck(Send(InTransactionID, InResult, Message::Generic::MID_PostLogDataRes, fbb));


		return hr;
	}; // Result GenericSvrRPCSendAdapter::PostLogDataRes( const TransactionID &InTransactionID, const Result &InResult )


}; // namespace SF


