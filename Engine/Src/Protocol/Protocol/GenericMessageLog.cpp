////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Generic Message log implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Protocol/GenericMessageLog.h"
#include "Protocol/Generic_generated.h"
#ifdef ERROR
#undef ERROR
#endif
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"



namespace SF
{
 	Result GenericMessageLog::Initialize()
	{
 		Result hr;

		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericFailureCmd,&GenericFailureCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericFailureRes,&GenericFailureRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericTransactionCmd,&GenericTransactionCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericTransactionRes,&GenericTransactionRes));


		Protocol::LoadFlatSchema("Generic.fbs");

		return hr;
	}; // Result GenericMessageLog::Initialize()
	Result GenericMessageLog::GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.Generic.GenericFailureCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} Generic:GenericFailureCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericFailureRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.Generic.GenericFailureRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} Generic:GenericFailureRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericFailureRes(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.Generic.GenericTransactionCmd")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} Generic:GenericTransactionCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		if (Protocol::MessageDebugParser.LookupStruct("SF.Flat.Generic.GenericTransactionRes")) {
		    flatbuffers::GenText(Protocol::MessageDebugParser, messageHeader->GetPayloadPtr(), &packetString);
		}
		SFLog(Net, Debug, "{0} Generic:GenericTransactionRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader)


}; // namespace SF


