////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Log
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "String/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"
#include "Thread/SFThread.h"
#include "Object/SFSharedObject.h"
#include "Service/SFService.h"
#include "Memory/SFMemoryManager.h"

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
// For crash dump
#pragma comment(lib, "Dbghelp.lib")
#endif



namespace SF {
namespace Log {

	




	////////////////////////////////////////////////////////////////////////////////
	//
	// Trace Log Module
	//

	LogOutputHandler::LogOutputHandler(const LogChannelMask& outputMask)
		: m_OutputMask(outputMask)
	{
	}

	LogOutputHandler::~LogOutputHandler()
	{
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	// Trace Log Module
	//


	constexpr StringCrc64 LogModule::TypeName;


	LogModule::LogModule(const LogChannelParameter& printMask)
		: LibraryComponent("Log")
		, LogService(printMask)
		, m_Thread([&](Thread* pThread) { Run(pThread); })
		, m_OutputHandlers(GetSystemHeap())
	{
		Service::LogModule = this;

		m_Thread.SetThreadName("LogModule");
		m_Thread.Start();
		m_Thread.SetPriority(Thread::PRIORITY::HIGHEST);
	}


	LogModule::~LogModule()
	{
		m_Thread.SetKillEvent();
		// Print a message so that the thread can terminated
		SFLog(System, Info, "Logging system terminated");
		Service::LogModule = nullptr;
	}


	void LogModule::EnableChannel(LogMainChannelType mainChannel, LogSubChannelType subChannel, bool enable)
	{
		uint32_t mask = (uint32_t)(((uint64_t)1) << (32 + (int)mainChannel));

		if (enable)
		{
			m_PrintParameter.MainChannelMasks[(int)mainChannel].Composited |= mask;
		}
		else
		{
			m_PrintParameter.MainChannelMasks[(int)mainChannel].Composited &= ~mask;
		}
	}


	void LogModule::EnableChannel(LogSubChannelType subChannel, bool enable)
	{
		auto mask = (uint32_t)(((uint64_t)1) << (int)subChannel);

		if (enable)
		{
			m_PrintParameter.SubChannelMask.Composited |= mask;
		}
		else
		{
			m_PrintParameter.SubChannelMask.Composited &= ~mask;
		}
	}


	void LogModule::Run(Thread* pThread)
	{
		constexpr DurationMS flushWaitTime(3 * 1000);

		while (!pThread->CheckKillEvent(DurationMS(3)))
		{
			auto timeWaitStart = Util::Time.GetTimeMs();
			bool flushed = false;

			auto pLockBuffer = m_LogSpinBuffer.Read_Lock( [&]()
			{
				// Flush if there is no log over 1 sec
				if (!flushed && Util::TimeSince(timeWaitStart) > flushWaitTime)
				{
					flushed = true;
					timeWaitStart = Util::Time.GetTimeMs();
					for (auto itOutput : m_OutputHandlers)
					{
						itOutput->Flush();
					}
				}
				return true;
			});

			if (pLockBuffer != nullptr)
			{
				LogItem& logItem = pLockBuffer->Data;

				m_LogTimeMS = Util::Time.GetTimeMs();

				for (auto itOutput : m_OutputHandlers)
				{
					if ((itOutput->GetOutputMask().Composited & logItem.ChannelMask.Composited) != logItem.ChannelMask.Composited)
						continue;

					itOutput->PrintOutput(&logItem);
				}

				m_LogSpinBuffer.Read_Unlock(pLockBuffer);
			}
		}

	}

	Result LogModule::InitializeComponent()
	{
		return LibraryComponent::InitializeComponent();
	}

	void LogModule::DeinitializeComponent()
	{
		Flush();
		LibraryComponent::DeinitializeComponent();
	}


	// output handler
	void LogModule::RegisterOutputHandler(LogOutputHandler* output)
	{
		if (output == nullptr) return;
		m_OutputHandlers.push_back(output);
	}

	void LogModule::UnregisterOutputHandler(LogOutputHandler* output)
	{
		if (output == nullptr) return;
		m_OutputHandlers.RemoveItem(output);
	}

	void* LogModule::ReserveWriteBuffer()
	{
		auto pSpinBlock = m_LogSpinBuffer.Write_Lock();

		pSpinBlock->Data.TimeStamp = std::chrono::system_clock::now();

		return pSpinBlock;
	}

	void LogModule::ReleaseWriteBuffer(void* pBuffer, size_t messageSize)
	{
		LogSpinBuffer::BLOCK* pWriteBuffer = (LogSpinBuffer::BLOCK*)pBuffer;
		char *pOutBuff = pWriteBuffer->Data.LogBuff;
		int orgBuffLen = sizeof(pWriteBuffer->Data.LogBuff);

		pOutBuff += messageSize;
		int buffLen = orgBuffLen - (int)messageSize;

		// pending \r\n
		StrUtil::StringCopyEx(pOutBuff, buffLen, "\n");
		pWriteBuffer->Data.LogStringSize = messageSize + 1;

		m_LogSpinBuffer.Write_Unlock(pWriteBuffer);
	}

	size_t LogModule::WriteTimeTag(void* pLogItemBuff)
	{
		static const char* MainChannelNames[] =
		{
			"System",
			"Net",
			"IO",
			"ThirdParty",
			"Engine",
			"DB",
			"Protocol",
			"Svr",
			"Editor",
			"Game",

			"Custom",
		};

		auto pLogItem = (LogItem*)pLogItemBuff;

		std::time_t logTime = std::chrono::system_clock::to_time_t(pLogItem->TimeStamp);
		auto tm = std::localtime(&logTime);
		pLogItem->LogStringSize = StrUtil::Format(pLogItem->LogBuff, "{0}:{1}:{2} {3}: ", tm->tm_hour, tm->tm_min, tm->tm_sec, MainChannelNames[(int)pLogItem->MainChannel]);
		
		return pLogItem->LogStringSize;
	}

	// Flush log queue
	void LogModule::Flush()
	{
		auto writePosition = m_LogSpinBuffer.GetWritePosition();
		do
		{
			auto readPosition = m_LogSpinBuffer.GetReadPosition();
			if (writePosition - readPosition <= 0)
				break;
		} while (1);
	}





}	// namespace Log
} // namespace SF

