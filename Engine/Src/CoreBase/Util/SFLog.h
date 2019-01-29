////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Log
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Service/SFService.h"
#include "String/SFStrUtil.h"
#include "Container/SFArray.h"
#include "Container/SFSpinBufferMT.h"
#include "String/SFStrFormat.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Object/SFLibraryComponent.h"





namespace SF {
namespace Log {


	class LogOutputHandler;



	/////////////////////////////////////////////////////////////////////////
	//
	//	Log module
	//


	class LogModule : public LibraryComponent, public LogService
	{
	public:
		static constexpr FixedString TypeName = "LogModule";

		//Struct for Spin Buffer
		struct LogItem
		{
			LogMainChannelType		MainChannel;
			LogSubChannelType		SubChannel;
			LogChannelMask		ChannelMask;
			SystemTimeStampMS	TimeStamp;
			size_t LogStringSize = 0;
			char	LogBuff[3 * 1024];

			LogItem()
			{
				LogBuff[0] = 0;
			}
		};

		typedef SpinBufferMT<LogItem, 256> LogSpinBuffer;

	private:

		FunctorThread m_Thread;

		LogSpinBuffer m_LogSpinBuffer;

		// output handler array
		DynamicArray<LogOutputHandler*> m_OutputHandlers;

		TimeStampMS m_LogTimeMS;

	protected:

		void Run(Thread* pThread);

	public:

		LogModule(const LogChannelParameter& printMask = LogChannelParameter());
		~LogModule();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;

		// enable channel
		virtual void EnableChannel(LogMainChannelType mainChannel, LogSubChannelType subChannel, bool enable) override;
		virtual void EnableChannel(LogSubChannelType subChannel, bool enable) override;


		// output handler
		virtual void RegisterOutputHandler(LogOutputHandler* output) override;
		virtual void UnregisterOutputHandler(LogOutputHandler* output) override;

		// Reserve write buffer
		virtual void* ReserveWriteBuffer() override;
		virtual void ReleaseWriteBuffer(void* block, size_t messageSize) override;


		// Flush log queue
		virtual void Flush() override;

	};




	/////////////////////////////////////////////////////////////////////////
	//
	//	Log output handler
	//

	class LogOutputHandler
	{
	private:

		LogChannelMask m_OutputMask;

	public:

		LogOutputHandler(const LogChannelMask& outputMask);
		virtual ~LogOutputHandler();

		const LogChannelMask& GetOutputMask() { return m_OutputMask; }
		void SetOutputMask(const LogChannelMask& value) { m_OutputMask = value; }

		virtual void PrintOutput(const LogModule::LogItem* logMessage) = 0;

		// flush output if it uses buffering
		virtual void Flush() {}
	};





} // namespace Log
} // namespace SF




//////////////////////////////////////////////////////////////////////////////////////
//
//  Declare trace module
//

#define SFLog(mainChannel,subChannel, ...) \
		do{\
			auto pLogService = ::SF::Service::LogModule;\
			if( (pLogService != nullptr) )\
			{\
				auto mainChannelMask = pLogService->ToChannelMask(::SF::LogMainChannels::mainChannel);\
				auto subChannelMask = pLogService->ToChannelMask(::SF::LogSubChannels::subChannel);\
				if (pLogService->ShouldPrint(mainChannelMask, subChannelMask))\
				{\
					auto block = (::SF::Log::LogModule::LogSpinBuffer::BLOCK*)pLogService->ReserveWriteBuffer(); \
					if (block == nullptr) break; \
					block->Data.MainChannel = ::SF::LogMainChannels::mainChannel;\
					block->Data.SubChannel = ::SF::LogSubChannels::subChannel;\
					block->Data.ChannelMask = subChannelMask; \
					auto messageSize = SF::StrUtil::Format(block->Data.LogBuff, __VA_ARGS__) - 1; \
					pLogService->ReleaseWriteBuffer(block, messageSize); \
				}\
			}\
		}while(0);\
		\


#ifdef DEBUG
#define SFLogDebug(mainChannel,subChannel, ...) SFLog(mainChannel,Debug,__VA_ARGS__)
#else
#define SFLogDebug(mainChannel,subChannel, ...)
#endif


#define SFErrJmp(mainChannel, errval) \
	do {\
		hr = errval;\
		SFLog(mainChannel, Error, "{0}({1}): {2}", (const char*)__FILE__, __LINE__, hr ); \
		goto Proc_End;\
	} while(0);




