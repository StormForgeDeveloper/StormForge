////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net Connection implementation
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFProtocolPCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Util/SFLog.h"
#include "Net/SFConnection.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Util/SFTimeUtil.h"


#include "Protocol/SFProtocol.h"

#include "Protocol/Message/LoginMsgDebug.h"
#include "Protocol/Message/GameMsgDebug.h"

#include "Protocol/Message/LoginMsgParsing.h"
#include "Protocol/Message/GameMsgParsing.h"

#include "Protocol/Message/PlayInstanceMsgDebug.h"
#include "Protocol/Message/PlayInstanceMsgParsing.h"


namespace SF {

	const int SF_PROTOCOL_VERSION = 11;

namespace Protocol {

	std::unordered_map<uint32_t, MessageHandlingFunction> MessageDebugTraceMap;
	
	void RegisterConnectionDebugMessage()
	{
		if (MessageDebugTraceMap.size() > 0) return;
		
		RegisterDebugTraceLogin( );
		RegisterDebugTraceGame( );
		RegisterDebugTracePlayInstance();
	}

	
	std::unordered_map<uint32_t, HandleParseMessageTo> MessageParseToVariableMap;
	std::unordered_map<uint32_t, HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;

	void RegisterMessageParser()
	{
		if (MessageParseToVariableMap.size() > 0) return;
		
		RegisterParserLogin();
		RegisterParserGame();
		RegisterParserPlayInstance();
	}
	
	void PrintDebugMessage(const char* preFix, const SharedPointerT<Message::MessageData>& pMsg )
	{
		if( pMsg == nullptr )
			return;

		auto itFound = MessageDebugTraceMap.find(pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);
		if (itFound != MessageDebugTraceMap.end())
		{
			((itFound->second))(preFix, pMsg);
		}
	}
	
	Result ParseMessage(SharedPointerT<Message::MessageData>& pMsg, IVariableMapBuilder& variableMap)
	{
		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		auto itFound = MessageParseToVariableMap.find(pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);
		if (itFound != MessageParseToVariableMap.end())
		{
			return (itFound->second)(pMsg, variableMap);
		}
		
		return ResultCode::IO_BADPACKET;
	}
	
	Result ParseMessage(IHeap& memoryManager, SharedPointerT<Message::MessageData>&& pMsg, Message::MessageBase * &pMsgBase)
	{
		pMsgBase = nullptr;

		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		auto itFound = MessageParseToMessageBaseMap.find(pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);
		if (itFound != MessageParseToMessageBaseMap.end())
		{
			return (itFound->second)(memoryManager, std::forward<MessageDataPtr>(pMsg), pMsgBase);
		}
		
		return ResultCode::IO_BADPACKET;
	}
	

} // namespace Protocol
} // namespace SF


