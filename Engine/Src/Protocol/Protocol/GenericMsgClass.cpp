////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Generic Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "Protocol/SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "Protocol/SFProtocolHelper.h"
#include "Protocol/GenericMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Generic
		{
 			// Cmd: Generic failure message
			const MessageID GenericFailureCmd::MID = MessageID(MSGTYPE_COMMAND, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GENERIC, 0);
			Result GenericFailureCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_RouteContext);
				protocolCheck(*input >> m_TransactionID);

				return hr;

			}; // Result GenericFailureCmd::ParseMessage(const MessageHeader* pHeader)

			Result GenericFailureCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GenericFailureCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("RouteContext", "RouteContext", parser.GetRouteContext());
				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());

				return hr;

			}; // Result GenericFailureCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GenericFailureCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) GenericFailureCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GenericFailureCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GenericFailureCmd::CalculateMessageSize( const RouteContext &InRouteContext, const uint64_t &InTransactionID )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InRouteContext)
					+ SerializedSizeOf(InTransactionID)
				);

				return __uiMessageSize;
			}; // size_t GenericFailureCmd::CalculateMessageSize( const RouteContext &InRouteContext, const uint64_t &InTransactionID )


			Result GenericFailureCmd::Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const uint64_t &InTransactionID )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InRouteContext)
					+ SerializedSizeOf(InTransactionID)
				);

				messageBuffer->msgID = GenericFailureCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InRouteContext);
				protocolCheck(*output << InTransactionID);

				return hr;
			}; // Result GenericFailureCmd::Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const uint64_t &InTransactionID )

			Result GenericFailureCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GenericFailureCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Generic::GenericFailure, {0}:{1} , RouteContext:{2}, TransactionID:{3}",
						prefix, pHeader->Length, parser.GetRouteContext(), parser.GetTransactionID()); 
				return ResultCode::SUCCESS;
			}; // Result GenericFailureCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			const MessageID GenericFailureRes::MID = MessageID(MSGTYPE_RESULT, MSGTYPE_RELIABLE, MSGTYPE_NONE, PROTOCOLID_GENERIC, 0);
			Result GenericFailureRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_RouteContext);
				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result GenericFailureRes::ParseMessage(const MessageHeader* pHeader)

			Result GenericFailureRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				GenericFailureRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("RouteContext", "RouteContext", parser.GetRouteContext());
				variableBuilder.SetVariable("TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result GenericFailureRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result GenericFailureRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) GenericFailureRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result GenericFailureRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t GenericFailureRes::CalculateMessageSize( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InRouteContext)
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t GenericFailureRes::CalculateMessageSize( const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )


			Result GenericFailureRes::Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InRouteContext)
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = GenericFailureRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InRouteContext);
				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result GenericFailureRes::Create( MessageHeader* messageBuffer, const RouteContext &InRouteContext, const uint64_t &InTransactionID, const Result &InResult )

			Result GenericFailureRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				GenericFailureRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Generic::GenericFailure, {0}:{1} , RouteContext:{2}, TransactionID:{3}, Result:{4:X8}",
						prefix, pHeader->Length, parser.GetRouteContext(), parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result GenericFailureRes::TraceOut(const char* prefix, const MessageHeader* pHeader)



		}; // namespace Generic
	}; // namespace Message
}; // namespace SF


