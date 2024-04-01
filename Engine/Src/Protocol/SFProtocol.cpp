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
#include "Util/SFPath.h"

#include "Protocol/GameMessageLog.h"
#include "Protocol/PlayInstanceMessageLog.h"
#include "Protocol/GenericMessageLog.h"

#ifdef ERROR
#undef ERROR
#endif
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"


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

            //MessageDebugParser.opts.json_nested_flatbuffers = true;
            //MessageDebugParser.opts.natural_utf8 = true;
            //MessageDebugParser.opts.strict_json = false;

            GameMessageLog::Initialize();
            PlayInstanceMessageLog::Initialize();
            GenericMessageLog::Initialize();

			return true;
		}

		static SFProtocolInitializer stm_Instance;
	};

	SFProtocolInitializer SFProtocolInitializer::stm_Instance;

    Result LoadFlatSchema(flatbuffers::Parser& parser, const char* filePath)
    {
        Result hr;
        if (filePath == nullptr)
            return hr;

        const char* DevSchemaPath = "Dev/ProtocolSchema";

        std::vector<const char*> includes;
        includes.push_back(DevSchemaPath); // default protocol schema path
        includes.push_back("Dev/ServerProtocolSchema"); // default protocol schema path
        includes.push_back(nullptr);

        String relativePath = Util::Path::Combine(DevSchemaPath, filePath);

        DynamicArray<uint8_t> buffer;
        hr = Util::LoadWholeFile(relativePath, buffer);
        if (!hr.IsSuccess())
            return hr;

        buffer.push_back(0);

        // flatbuffer searches included schema from include paths. so don't need to manually load them
        bool bSuccess = parser.Parse(reinterpret_cast<const char*>(buffer.data()), includes.data(), filePath);
        if (!bSuccess)
        {
            std::string errorMsg;
            parser.Error(errorMsg).Check();
            SFLog(Protocol, Error, "Failed to parse schema file:{0}, error:{1}", filePath, errorMsg);
        }

        return hr;
    }


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
