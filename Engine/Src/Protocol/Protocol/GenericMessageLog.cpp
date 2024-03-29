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
#include "Net/SFMessageEndpoint.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Protocol/GenericMessageLog.h"
#include "Generic_generated.h"



namespace SF
{
 	Result GenericMessageLog::Initialize()
	{
 		Result hr;

		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericFailureCmd,&GenericFailureCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericFailureRes,&GenericFailureRes));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericTransactionCmd,&GenericTransactionCmd));
		Protocol::MessageDebugTraceMap.insert(std::make_pair(Message::Generic::MID_GenericTransactionRes,&GenericTransactionRes));
		return hr;
	}; // Result GenericMessageLog::Initialize()
	Result GenericMessageLog::GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		SFLog(Net, Debug, "{0} Generic:GenericFailureCmd: tid:{1}, size:{2}", prefix, messageHeader->TransactionId, messageHeader->MessageSize);

		return hr;
	}; // Result GenericMessageLog::GenericFailureCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericFailureRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		SFLog(Net, Debug, "{0} Generic:GenericFailureRes: tid:{1}, Result:{2} size:{3}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize);

		return hr;
	}; // Result GenericMessageLog::GenericFailureRes(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		SFLog(Net, Debug, "{0} Generic:GenericTransactionCmd: tid:{1}, size:{2}", prefix, messageHeader->TransactionId, messageHeader->MessageSize);

		return hr;
	}; // Result GenericMessageLog::GenericTransactionCmd(const char* prefix, const MessageHeader* messageHeader)
	Result GenericMessageLog::GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader)
	{
 		Result hr;

		protocolCheckPtr(messageHeader);

		SFLog(Net, Debug, "{0} Generic:GenericTransactionRes: tid:{1}, Result:{2} size:{3}", prefix, messageHeader->TransactionId, messageHeader->GetTransactionResult(), messageHeader->MessageSize);

		return hr;
	}; // Result GenericMessageLog::GenericTransactionRes(const char* prefix, const MessageHeader* messageHeader)


}; // namespace SF


