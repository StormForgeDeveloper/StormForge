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
 	bool GenericMessageLog::stm_IsInitialized = false;
	flatbuffers::Parser GenericMessageLog::stm_Parser;
	Result GenericMessageLog::Initialize()
	{
 		Result hr;

		if (stm_IsInitialized) return hr;
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericFailureCmd,&GenericFailureCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericFailureRes,&GenericFailureRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericTransactionCmd,&GenericTransactionCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericTransactionRes,&GenericTransactionRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_PostLogDataCmd,&PostLogDataCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_PostLogDataRes,&PostLogDataRes));


		Protocol::LoadFlatSchema(stm_Parser, "Generic.fbs");
		stm_Parser.opts.indent_step = -1; // no new line
		stm_IsInitialized = true;

		return hr;
	}; // Result GenericMessageLog::Initialize()
	Result GenericMessageLog::GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Generic.GenericFailureCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Generic:GenericFailureCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericFailureRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Generic.GenericFailureRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Generic:GenericFailureRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericFailureRes(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Generic.GenericTransactionCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Generic:GenericTransactionCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Generic.GenericTransactionRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Generic:GenericTransactionRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::PostLogDataCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Generic.PostLogDataCmd";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Generic:PostLogDataCmd: tid:{1}, sz:{2}: {3}", prefix, messageHeader->TransactionId, messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::PostLogDataCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::PostLogDataRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		std::string packetString;
		static const std::string tableName = "SF.Flat.Generic.PostLogDataRes";
		if (stm_Parser.LookupStruct(tableName)) {
		    flatbuffers::GenTextFromTable(stm_Parser, flatbuffers::GetRoot<flatbuffers::Table>(messageHeader->GetPayloadPtr()), tableName, &packetString);
		}
		SFLog(Net, Debug1, "{0} Generic:PostLogDataRes: tid:{1}, res:{2} sz:{3}: {4}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize, packetString.length() > 0 ? packetString.c_str() : "");

		return hr;
	}; // Result GenericMessageLog::PostLogDataRes(const char* prefix, const MessageHeader* messageHeader)


}; // namespace SF


