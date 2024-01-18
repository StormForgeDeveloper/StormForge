////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Script service
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "Service/SFLogService.h"


namespace SF
{
	namespace Log
	{
        LogChannel Global("Global", LogOutputType::CustomMax);
		LogChannel System("System", LogOutputType::CustomMax);
		LogChannel Net("Net", LogOutputType::CustomMax);
		LogChannel IO("IO", LogOutputType::CustomMax);
		LogChannel ThirdParty("ThirdParty", LogOutputType::CustomMax);
		LogChannel Engine("Engine", LogOutputType::CustomMax);
		LogChannel Protocol("Protocol", LogOutputType::CustomMax);
		LogChannel Editor("Editor", LogOutputType::CustomMax);
		LogChannel Game("Game", LogOutputType::CustomMax);
	}

	static const char* g_LogOutputTypeNames[] = {
		// Generic trace
		"Error",
		"Warning",
		"Factal",
		"Info",

		// Module additional traces
		"Custom1",
		"Custom2",
		"Custom3",
		"Custom4",
		"Custom5",
		"Custom6",
		"Custom7",
		"Custom8",
		"Custom9",
		"Custom10",

		"Debug",
		"Debug1",
		"Debug2",
		"Debug3",
		"Debug4",
		"Debug5",
		"Debug6",
		"Debug7",
		"Debug8",

		"Max",
	};

    Log::LogChannel* LogService::stm_ChannelList = nullptr;


    Log::LogChannel::LogChannel(const char* channelName, LogOutputType defaultLogLevel)
    {
        uint32_t channelMask = static_cast<uint32_t>((1 << (static_cast<uint32_t>(defaultLogLevel) + 1)) - 1);

        Init(channelName, channelMask);
        AddToChannelList();
    }

    Log::LogChannel::LogChannel(const char* channelName, uint32_t channelMask)
    {
        Init(channelName, channelMask);
        AddToChannelList();
    }

    void Log::LogChannel::SetChannelLogLevel(LogOutputType logLevel)
    {
        uint32_t channelMask = static_cast<uint32_t>((1 << (static_cast<uint32_t>(logLevel) + 1)) - 1);
        SetChannelLogMask(channelMask);
    }

    void Log::LogChannel::SetChannelLogMask(uint32_t logMask)
    {
        m_ChannelMask.Composited = logMask;
    }

    void Log::LogChannel::SetChannelLogMask(const LogOutputMask& logMask)
    {
        m_ChannelMask = logMask;
    }

    void Log::LogChannel::Init(const char* channelName, uint32_t channelMask)
    {
        StrUtil::StringCopy(m_ChannelNameString, channelName);
        m_ChannelNameString[countof(m_ChannelNameString) - 1] = '\0';

        char channelNameLwr[128];
        StrUtil::StringLower(channelNameLwr, m_ChannelNameString);

        m_ChannelName = channelNameLwr;

        SetChannelLogMask(channelMask);
    }

    void Log::LogChannel::AddToChannelList()
    {
        LogService::AddToChannelList(this);
    }

    void LogService::AddToChannelList(Log::LogChannel* pLogChannel)
    {
        if (pLogChannel == nullptr)
            return;

        assert(pLogChannel->m_pNextChannel == nullptr);

        pLogChannel->m_pNextChannel = stm_ChannelList;
        stm_ChannelList = pLogChannel;
    }

    void LogService::RemoveFromChannelList(Log::LogChannel* pLogChannel)
    {
        if (pLogChannel == nullptr)
            return;

        Log::LogChannel** ppCur = &stm_ChannelList;
        for ( ;ppCur && *ppCur; ppCur = &((*ppCur)->m_pNextChannel))
        {
            if ((*ppCur) == pLogChannel)
            {
                (*ppCur) = pLogChannel->m_pNextChannel;
                break;
            }
        }
    }

    Log::LogChannel* LogService::FindLogChannel(const StringCrc32 channelName)
    {
        Log::LogChannel* pCur = stm_ChannelList;
        for (; pCur; pCur = pCur->m_pNextChannel)
        {
            if (pCur->GetChannelName() == channelName)
            {
                break;
            }
        }

        return pCur;
    }

    Log::LogChannel* LogService::FindLogChannelString(const char* channelName)
    {
        char channelNameLwr[256]{};
        StrUtil::StringLower(channelNameLwr, channelName);
        return FindLogChannel(channelNameLwr);
    }

    void LogService::SetLogFileName(const char* logFileName)
    {
        StrUtil::StringCopy(m_LogFileName, logFileName);
    }

	const char* ToString(LogOutputType logOutputType)
	{
		return g_LogOutputTypeNames[(int)logOutputType];
	}

} // namespace SF


