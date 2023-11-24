////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c)  Kyungkun Ko
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


	const uint32_t SF_PROTOCOL_VERSION = 13;

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



	void PrintDebugMessage(const char* preFix, const MessageHeader* pHeader)
	{
		if(pHeader == nullptr )
			return;

		auto itFound = MessageDebugTraceMap.find(pHeader->msgID.IDSeq.MsgID);
		if (itFound != MessageDebugTraceMap.end())
		{
			((itFound->second))(preFix, pHeader);
		}
		else
		{
			SFLog(Net, Error, "PrintDebugMessage failed, can't find message handler prefix:{0} for msgId:{1}", preFix, pHeader->msgID);
		}
	}
	
	Result ParseMessage(const MessageHeader* pHeader, IVariableMapBuilder& variableMap)
	{
		if (pHeader == nullptr)
			return ResultCode::INVALID_POINTER;

		auto itFound = MessageParseToVariableMap.find(pHeader->msgID.IDSeq.MsgID);
		if (itFound != MessageParseToVariableMap.end())
		{
			return (itFound->second)(pHeader, variableMap);
		}
		else
		{
			SFLog(Net, Error, "ParseMessage(GenVariableTable) failed, can't find message handler for 0x{0:X8}", pHeader->msgID.GetMsgIDOnly());
		}

		return ResultCode::IO_BADPACKET;
	}
	
	Result ParseMessage(IHeap& memoryManager, const MessageHeader* pHeader, MessageBase * &pMsgBase)
	{
		pMsgBase = nullptr;

		if (pHeader == nullptr)
			return ResultCode::INVALID_POINTER;

		auto itFound = MessageParseToMessageBaseMap.find(pHeader->msgID.IDSeq.MsgID);
		if (itFound != MessageParseToMessageBaseMap.end())
		{
			return (itFound->second)(memoryManager, pHeader, pMsgBase);
		}
		else
		{
			SFLog(Net, Error, "ParseMessage failed, can't find message handler for 0x{0:X8}", pHeader->msgID.GetMsgIDOnly());
		}

		return ResultCode::IO_BADPACKET;
	}
	
} // namespace Protocol
} // namespace SF
