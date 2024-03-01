////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Log
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"
#include "Multithread/SFThread.h"
#include "Object/SFSharedObject.h"
#include "Service/SFService.h"
#include "MemoryManager/SFMemoryManager.h"

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

	LogOutputHandler::LogOutputHandler(const char* channelName)
	{
        m_OutputMaskChannel = Service::LogModule->FindLogChannelString(channelName);
        assert(m_OutputMaskChannel); // we need channel
	}

	LogOutputHandler::~LogOutputHandler()
	{
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	// Trace Log Module
	//


	constexpr StringCrc64 LogModule::TypeName;


	LogModule::LogModule(const LogOutputMask& logOutputGlobalMask)
		: LibraryComponent("Log")
		, LogService(logOutputGlobalMask)
		, m_Thread([&](Thread* pThread) { Run(pThread); })
		, m_OutputHandlers(GetSystemHeap())
	{
		Service::LogModule = this;

		m_Thread.SetThreadName("LogThread");
		m_Thread.Start();
		m_Thread.SetPriority(Thread::PRIORITY::HIGHEST);
	}


	LogModule::~LogModule()
	{
		SFLog(System, Info, "Logging system terminated");

		Flush();
		m_Thread.SetKillEvent();
		Service::LogModule = nullptr;
	}



	void LogModule::Run(Thread* pThread)
	{
		constexpr DurationMS flushWaitTime(1 * 1000);

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

				// stop waiting if kill event has set
				if (pThread->CheckKillEvent(DurationMS(0)))
					return false;

				return true;
			});

			if (pLockBuffer != nullptr)
			{
				LogItem& logItem = pLockBuffer->Data;

				m_LogTimeMS = Util::Time.GetTimeMs();

				for (auto itOutput : m_OutputHandlers)
				{
					if ((itOutput->GetOutputMask().Composited & logItem.OutputMask.Composited) != logItem.OutputMask.Composited)
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
		// prevent logging on log thread, it can cause deadlock
		if (ThisThread::GetThreadID() == m_Thread.GetThreadID())
		{
			return nullptr;
		}

		auto pSpinBlock = m_LogSpinBuffer.Write_Lock();

		pSpinBlock->Data.TimeStamp = Util::Time.GetRawUTCMs();

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

	size_t LogModule::WriteTimeTag(Log::LogItem* pLogItem)
	{
		std::time_t logTime = UTCClockType::to_time_t(pLogItem->TimeStamp);

        const std::chrono::duration<double> tse = pLogItem->TimeStamp.time_since_epoch();
        long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;

		auto tm = std::localtime(&logTime);
		pLogItem->LogStringSize = StrUtil::Format(pLogItem->LogBuff, "[{0}/{1},{2}:{3}:{4}:{5}][{6}:{7}] ",
            tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, milliseconds,
            pLogItem->Channel->GetChannelNameString(), ToString(pLogItem->OutputType));
		
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

