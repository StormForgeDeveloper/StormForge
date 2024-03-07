////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : Generated
// 
// Description : Telemetry Message parser implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFProtocol.h"
#include "Util/SFToString.h"
#include "Net/SFNetToString.h"
#include "Container/SFArray.h"
#include "SFProtocolHelper.h"
#include "Protocol/TelemetryMsgClass.h"



namespace SF
{
 	namespace Message
	{
 		namespace Telemetry
		{
 			// Cmd: Post telemetry event
			Result PostEventCmd::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_EventName, ArrayLen));
				protocolCheck(*input >> m_TimeStamp);
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_AppID, ArrayLen));
				protocolCheck(input->Read(ArrayLen));
				protocolCheck(input->ReadLink(m_MachineID, ArrayLen));
				protocolCheck(*input >> m_EventID);
				protocolCheck(*input >> m_AccountID);
				protocolCheck(*input >> m_IsPlayEvent);
				protocolCheck(input->Read(ArrayLen));
				uint8_t* SessionIDPtr = nullptr;
				protocolCheck(input->ReadLink(SessionIDPtr, ArrayLen));
				m_SessionID.SetLinkedBuffer(ArrayLen, SessionIDPtr);
				protocolCheck(input->Read(ArrayLen));
				NamedVariable* AttributesPtr = nullptr;
				protocolCheck(input->ReadLink(AttributesPtr, ArrayLen));
				m_Attributes.SetLinkedBuffer(ArrayLen, AttributesPtr);

				return hr;

			}; // Result PostEventCmd::ParseMessage(const MessageHeader* pHeader)

			Result PostEventCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PostEventCmd parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("EventName", parser.GetEventName());
				variableBuilder.SetVariable("TimeStamp", parser.GetTimeStamp());
				variableBuilder.SetVariable("AppID", parser.GetAppID());
				variableBuilder.SetVariable("MachineID", parser.GetMachineID());
				variableBuilder.SetVariable("EventID", parser.GetEventID());
				variableBuilder.SetVariable("AccountID", parser.GetAccountID());
				variableBuilder.SetVariable("IsPlayEvent", "bool", parser.GetIsPlayEvent());
				variableBuilder.SetVariable("SessionID", parser.GetSessionID());
				variableBuilder.SetVariableArray("Attributes", "NamedVariable", parser.GetAttributes());

				return hr;

			}; // Result PostEventCmd::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PostEventCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) PostEventCmd(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PostEventCmd::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PostEventCmd::CalculateMessageSize( const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InEventName)
					+ SerializedSizeOf(InTimeStamp)
					+ SerializedSizeOf(InAppID)
					+ SerializedSizeOf(InMachineID)
					+ SerializedSizeOf(InEventID)
					+ SerializedSizeOf(InAccountID)
					+ SerializedSizeOf(InIsPlayEvent)
					+ SerializedSizeOf(InSessionID)
					+ SerializedSizeOf(InAttributes)
				);

				return __uiMessageSize;
			}; // size_t PostEventCmd::CalculateMessageSize( const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes )


			Result PostEventCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InEventName)
					+ SerializedSizeOf(InTimeStamp)
					+ SerializedSizeOf(InAppID)
					+ SerializedSizeOf(InMachineID)
					+ SerializedSizeOf(InEventID)
					+ SerializedSizeOf(InAccountID)
					+ SerializedSizeOf(InIsPlayEvent)
					+ SerializedSizeOf(InSessionID)
					+ SerializedSizeOf(InAttributes)
				);

				messageBuffer->msgID = PostEventCmd::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InEventName);
				protocolCheck(*output << InTimeStamp);
				protocolCheck(*output << InAppID);
				protocolCheck(*output << InMachineID);
				protocolCheck(*output << InEventID);
				protocolCheck(*output << InAccountID);
				protocolCheck(*output << InIsPlayEvent);
				protocolCheck(*output << InSessionID);
				protocolCheck(*output << InAttributes);

				return hr;
			}; // Result PostEventCmd::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const char* InEventName, const uint64_t &InTimeStamp, const char* InAppID, const char* InMachineID, const uint32_t &InEventID, const AccountID &InAccountID, const uint8 &InIsPlayEvent, const Array<uint8_t>& InSessionID, const Array<NamedVariable>& InAttributes )

			Result PostEventCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PostEventCmd parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Telemetry::PostEvent, {0}:{1} , TransactionID:{2}, EventName:{3,60}, TimeStamp:{4}, AppID:{5,60}, MachineID:{6,60}, EventID:{7}, AccountID:{8}, IsPlayEvent:{9}, SessionID:{10,30}, Attributes:{11,30}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetEventName(), parser.GetTimeStamp(), parser.GetAppID(), parser.GetMachineID(), parser.GetEventID(), parser.GetAccountID(), parser.GetIsPlayEvent(), parser.GetSessionID(), parser.GetAttributes()); 
				return ResultCode::SUCCESS;
			}; // Result PostEventCmd::TraceOut(const char* prefix, const MessageHeader* pHeader)

			Result PostEventRes::ParseMessage(const MessageHeader* pHeader)
			{
 				Result hr;


				protocolCheckPtr(pHeader);

				ArrayView<const uint8_t> bufferView(pHeader->GetPayload());
				InputMemoryStream inputStream(bufferView);
				auto* input = inputStream.ToInputStream();
				uint16_t ArrayLen = 0;(void)(ArrayLen);

				protocolCheck(*input >> m_TransactionID);
				protocolCheck(*input >> m_Result);

				return hr;

			}; // Result PostEventRes::ParseMessage(const MessageHeader* pHeader)

			Result PostEventRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )
			{
 				Result hr;


				PostEventRes parser;
				protocolCheck(parser.ParseMessage(pHeader));

				variableBuilder.SetVariable("TransactionID", "TransactionID", parser.GetTransactionID());
				variableBuilder.SetVariable("Result", parser.GetResult());

				return hr;

			}; // Result PostEventRes::ParseMessageTo(const MessageHeader* pHeader, IVariableMapBuilder& variableBuilder )

			Result PostEventRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )
			{
 				Result hr;

				protocolCheckMem(pMessageBase = new(memHeap) PostEventRes(pHeader));
				protocolCheck(pMessageBase->ParseMsg());

				return hr;

			}; // Result PostEventRes::ParseMessageToMessageBase( IHeap& memHeap, const MessageHeader* pHeader, MessageBase* &pMessageBase )


			size_t PostEventRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )
			{
 				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				return __uiMessageSize;
			}; // size_t PostEventRes::CalculateMessageSize( const TransactionID &InTransactionID, const Result &InResult )


			Result PostEventRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )
			{
 				Result hr;

				unsigned __uiMessageSize = (unsigned)(Message::HeaderSize 
					+ SerializedSizeOf(InTransactionID)
					+ SerializedSizeOf(InResult)
				);

				messageBuffer->msgID = PostEventRes::MID;
				if (messageBuffer->Length < __uiMessageSize)
					return ResultCode::UNEXPECTED;
				else
					messageBuffer->Length = __uiMessageSize;

				ArrayView<uint8_t> payloadView(size_t(messageBuffer->Length - sizeof(MessageHeader)), 0, reinterpret_cast<uint8_t*>(messageBuffer->GetDataPtr()));
				OutputMemoryStream outputStream(payloadView);
				IOutputStream* output = outputStream.ToOutputStream();

				protocolCheck(*output << InTransactionID);
				protocolCheck(*output << InResult);

				return hr;
			}; // Result PostEventRes::Create( MessageHeader* messageBuffer, const TransactionID &InTransactionID, const Result &InResult )

			Result PostEventRes::TraceOut(const char* prefix, const MessageHeader* pHeader)
			{
 				PostEventRes parser;
				parser.ParseMessage(pHeader);
				SFLog(Net, Debug1, "Telemetry::PostEvent, {0}:{1} , TransactionID:{2}, Result:{3:X8}",
						prefix, pHeader->Length, parser.GetTransactionID(), parser.GetResult()); 
				return ResultCode::SUCCESS;
			}; // Result PostEventRes::TraceOut(const char* prefix, const MessageHeader* pHeader)



		}; // namespace Telemetry
	}; // namespace Message
}; // namespace SF


