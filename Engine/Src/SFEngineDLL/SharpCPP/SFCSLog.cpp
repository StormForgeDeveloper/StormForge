////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Object
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Util/SFLog.h"
#include "Object/SFObject.h"


using namespace SF;


//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT void SFCSLog_LogMessage(int32_t logLevel, const char* message)
{
	if (message == nullptr)
		return;

	switch (logLevel)
	{
	case 0:
		SFLog(Game, Info, "{0}", message);
		break;
	case 1:
		SFLog(Game, Warning, "{0}", message);
		break;
	case 2:
		SFLog(Game, Error, "{0}", message);
		break;
	case 3:
		SFLog(Game, Debug1, "{0}", message);
		break;
	case 4:
		SFLog(Game, Debug2, "{0}", message);
		break;
	case 5:
	default:
		SFLog(Game, Debug3, "{0}", message);
		break;
	}
}
	

SFDLL_EXPORT void SFCSLog_Flush()
{
	Service::LogModule->Flush();
}


SFDLL_EXPORT uint32_t SFCSLog_NativeSetLogLevel(const char* channelName, uint32_t logLevel)
{
    char channelNameLwr[256];
    StrUtil::StringLower(channelNameLwr, channelName);
    Log::LogChannel* pChannel = Service::LogModule->FindLogChannel(channelNameLwr);
    if (pChannel == nullptr)
    {
        return (uint32_t)ResultCode::OBJECT_NOT_FOUND;
    }

    pChannel->SetChannelLogLevel((LogOutputType)logLevel);

    return (uint32_t)ResultCode::SUCCESS;
}


SFDLL_EXPORT uint32_t SFCSLog_NativeSetLogMask(const char* channelName, uint32_t logMask)
{
    char channelNameLwr[256];
    StrUtil::StringLower(channelNameLwr, channelName);
    Log::LogChannel* pChannel = Service::LogModule->FindLogChannel(channelNameLwr);
    if (pChannel == nullptr)
    {
        return (uint32_t)ResultCode::OBJECT_NOT_FOUND;
    }

    pChannel->SetChannelLogMask(logMask);

    return (uint32_t)ResultCode::SUCCESS;
}

