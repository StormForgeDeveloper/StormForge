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
#include "Component/SFLibraryComponentInitializer.h"
#include "Net/SFNetToString.h"

#include "Protocol/SFProtocol.h"

#include "Protocol/LoginMsgDebug.h"
#include "Protocol/GameMsgDebug.h"

#include "Protocol/LoginMsgParsing.h"
#include "Protocol/GameMsgParsing.h"

#include "Protocol/PlayInstanceMsgDebug.h"
#include "Protocol/PlayInstanceMsgParsing.h"

#include "Protocol/GenericMsgDebug.h"
#include "Protocol/GenericMsgParsing.h"


namespace SF {

	const uint32_t SF_PROTOCOL_VERSION = 12;

namespace Protocol {

	std::unordered_map<uint32_t, MessageHandlingFunction> MessageDebugTraceMap;
	std::unordered_map<uint32_t, HandleParseMessageTo> MessageParseToVariableMap;
	std::unordered_map<uint32_t, HandleParseMessageToMessageBase> MessageParseToMessageBaseMap;


	class SFProtocolInitializer : public LibraryComponentInitializer
	{
	public:

		SFProtocolInitializer()
		{}
		~SFProtocolInitializer()
		{}

		virtual bool Initialize(ComponentInitializeMode InitMode) override
		{
			if (InitMode != ComponentInitializeMode::AfterRegisterComponent)
				return false;

			RegisterDebugTraceLogin();
			RegisterDebugTraceGame();
			RegisterDebugTracePlayInstance();
            RegisterDebugTraceGeneric();

			RegisterParserLogin();
			RegisterParserGame();
			RegisterParserPlayInstance();
            RegisterParserGeneric();

			return true;
		}

		static SFProtocolInitializer stm_Instance;
	};

	SFProtocolInitializer SFProtocolInitializer::stm_Instance;



	void PrintDebugMessage(const char* preFix, const SharedPointerT<MessageData>& pMsg )
	{
		if( pMsg == nullptr )
			return;

		auto itFound = MessageDebugTraceMap.find(pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);
		if (itFound != MessageDebugTraceMap.end())
		{
			((itFound->second))(preFix, pMsg);
		}
		else
		{
			SFLog(Net, Error, "PrintDebugMessage failed, can't find message handler prefix:{0} for msgId:{1}", preFix, pMsg->GetMessageHeader()->msgID);
		}
	}
	
	Result ParseMessage(const SharedPointerT<MessageData>& pMsg, IVariableMapBuilder& variableMap)
	{
		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		auto itFound = MessageParseToVariableMap.find(pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);
		if (itFound != MessageParseToVariableMap.end())
		{
			return (itFound->second)(pMsg, variableMap);
		}
		else
		{
			SFLog(Net, Error, "ParseMessage(GenVariableTable) failed, can't find message handler for 0x{0:X8}", pMsg->GetMessageHeader()->msgID.GetMsgIDOnly());
		}

		return ResultCode::IO_BADPACKET;
	}
	
	Result ParseMessage(IHeap& memoryManager, const SharedPointerT<MessageData>& pMsg, MessageBase * &pMsgBase)
	{
		pMsgBase = nullptr;

		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		auto itFound = MessageParseToMessageBaseMap.find(pMsg->GetMessageHeader()->msgID.IDSeq.MsgID);
		if (itFound != MessageParseToMessageBaseMap.end())
		{
			return (itFound->second)(memoryManager, pMsg, pMsgBase);
		}
		else
		{
			SFLog(Net, Error, "ParseMessage failed, can't find message handler for 0x{0:X8}", pMsg->GetMessageHeader()->msgID.GetMsgIDOnly());
		}

		return ResultCode::IO_BADPACKET;
	}
	

} // namespace Protocol
} // namespace SF


