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

#include "SFProtocol.h"

#include "Protocol/GameMessageLog.h"
#include "Protocol/PlayInstanceMessageLog.h"
#include "Protocol/GenericMessageLog.h"


namespace SF {


	const uint32_t SF_PROTOCOL_VERSION = 21;

namespace Protocol {

	std::unordered_map<MessageID, MessageHandlingFunction> MessageDebugTraceMap;


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

            GameMessageLog::Initialize();
            PlayInstanceMessageLog::Initialize();
            GenericMessageLog::Initialize();

			return true;
		}

		static SFProtocolInitializer stm_Instance;
	};

	SFProtocolInitializer SFProtocolInitializer::stm_Instance;



	void PrintDebugMessage(const char* preFix, const MessageHeader* pHeader)
	{
		if(pHeader == nullptr )
			return;

		auto itFound = MessageDebugTraceMap.find(pHeader->GetMessageID());
		if (itFound != MessageDebugTraceMap.end())
		{
			((itFound->second))(preFix, pHeader);
		}
		else
		{
			SFLog(Net, Error, "PrintDebugMessage failed, can't find message handler prefix:{0} for msgId:{1}", preFix, pHeader->GetMessageID());
		}
	}
	
	
} // namespace Protocol
} // namespace SF
