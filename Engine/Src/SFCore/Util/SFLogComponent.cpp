////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFLogComponent.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "IO/SFFileUtil.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFStringFormat.h"
#include "Service/SFService.h"
#include "Variable/SFVariableBoxing.h"


namespace SF {


	constexpr StringCrc64 LogOutputConsoleComponent::TypeName;




	LogOutputConsoleComponent::LogOutputConsoleComponent(const LogOutputMask& logMask)
		: LibraryComponent(StringCrc64("LogConsole"))
		, m_Handler(logMask)
	{
	}

	LogOutputConsoleComponent::~LogOutputConsoleComponent()
	{

	}

	void LogOutputConsoleComponent::MyOutputHandler::InitConsole()
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (m_hConsole == 0
			|| m_hConsole == INVALID_NATIVE_HANDLE_VALUE)
		{
			AllocConsole();

			m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTitleA(Util::GetServiceName());
		}
		SetConsoleCP(CP_UTF8);
#endif
	}

	void LogOutputConsoleComponent::MyOutputHandler::PrintOutput(const Log::LogItem* logMessage)
	{
		if (logMessage == nullptr) return;

#if SF_PLATFORM == SF_PLATFORM_ANDROID
		android_LogPriority logPriority = ANDROID_LOG_INFO;
		switch (logMessage->SubChannel)
		{
		case LogSubChannels::Error:
			logPriority = ANDROID_LOG_ERROR;
			break;
		case LogSubChannels::Warning:
			logPriority = ANDROID_LOG_WARN;
			break;
		case LogSubChannels::Assert:
			logPriority = ANDROID_LOG_FATAL;
			break;
		default:
			break;
		};

		__android_log_print(logPriority, "StormForge", "%s", logMessage->LogBuff);
#elif SF_PLATFORM == SF_PLATFORM_WINDOWS
		if (m_hConsole == INVALID_NATIVE_HANDLE_VALUE)
			return;

		DWORD dwWriten = 0;
		WriteConsoleA(m_hConsole, logMessage->LogBuff, (DWORD)logMessage->LogStringSize, &dwWriten, nullptr);
#else
		std::cout << logMessage->LogBuff;
#endif
	}

	// Initialize server component
	Result LogOutputConsoleComponent::InitializeComponent()
	{
		Service::LogModule->RegisterOutputHandler(&m_Handler);

		m_Handler.InitConsole();

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LogOutputConsoleComponent::DeinitializeComponent()
	{
		Service::LogModule->UnregisterOutputHandler(&m_Handler);
	}





	constexpr StringCrc64 LogOutputDebuggerComponent::TypeName;

	LogOutputDebuggerComponent::LogOutputDebuggerComponent(const LogOutputMask& logMask)
		: LibraryComponent(StringCrc64("LogDebugger"))
		, m_Handler(logMask)
	{

	}

	LogOutputDebuggerComponent::~LogOutputDebuggerComponent()
	{

	}

	void LogOutputDebuggerComponent::MyOutputHandler::PrintOutput(const Log::LogItem* logMessage)
	{
		if (logMessage == nullptr) return;
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		OutputDebugStringA(logMessage->LogBuff);
#endif
	}

	// Initialize server component
	Result LogOutputDebuggerComponent::InitializeComponent()
	{
		Service::LogModule->RegisterOutputHandler(&m_Handler);

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LogOutputDebuggerComponent::DeinitializeComponent()
	{
		Service::LogModule->UnregisterOutputHandler(&m_Handler);
	}



	constexpr StringCrc64 LogOutputFileComponent::TypeName;

	LogOutputFileComponent::LogOutputFileComponent(const LogOutputMask& logMask, const String& filePrefix, bool bOpenNewHourly)
		: LibraryComponent(StringCrc64("LogFile"))
		, m_Handler(logMask, filePrefix, bOpenNewHourly)
	{

	}


	LogOutputFileComponent::~LogOutputFileComponent()
	{

	}

	LogOutputFileComponent::MyOutputHandler::MyOutputHandler(const LogOutputMask& logMask, const String& filePrefix, bool bOpenNewHourly)
		: LogOutputHandler(logMask)
		, m_FilePrefix(filePrefix)
		, m_OpenNewFileHourly(bOpenNewHourly)
	{
		FileUtil::CreatePath(m_FilePrefix, 1);
		OpenLogFile();
	}

	void LogOutputFileComponent::MyOutputHandler::OpenLogFile()
	{
		String filePath;

		auto logFileCreated = std::chrono::system_clock::now();
		auto createdTimet = std::chrono::system_clock::to_time_t(logFileCreated);
		auto timeStruct = std::localtime(&createdTimet);
		m_LogFileCreatedHour = timeStruct->tm_hour;

		filePath.Format("{0}_{1}{2}{3}_{4}.log", m_FilePrefix.ToString(), timeStruct->tm_year + 1900, timeStruct->tm_mon + 1, timeStruct->tm_mday, timeStruct->tm_hour);
		m_File.Open(filePath, File::OpenMode::Create);
		if (m_File.IsOpened())
		{
			size_t szWritten;
			// UTF8 BOM
			static const uint8_t bytBOM[3] = { 0xEF, 0xBB, 0xBF };
			m_File.Write(bytBOM, 3, szWritten);
		}
	}




	void LogOutputFileComponent::MyOutputHandler::PrintOutput(const Log::LogItem* logMessage)
	{
		if (logMessage == nullptr) return;
		if (!m_File.IsOpened()) return;

		auto logTime = std::chrono::system_clock::to_time_t(logMessage->TimeStamp);
		auto timeStruct = std::localtime(&logTime);
		if (m_OpenNewFileHourly && m_LogFileCreatedHour != timeStruct->tm_hour)
		{
			// open new file
			m_File.Close();
			OpenLogFile();
			if (!m_File.IsOpened()) return;
		}

		size_t writen;
		m_File.Write((uint8_t*)logMessage->LogBuff, logMessage->LogStringSize, writen);
	}

	void LogOutputFileComponent::MyOutputHandler::Flush()
	{
		if (m_File.IsOpened())
			m_File.Flush();
	}

	// Initialize server component
	Result LogOutputFileComponent::InitializeComponent()
	{
		Service::LogModule->RegisterOutputHandler(&m_Handler);
		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LogOutputFileComponent::DeinitializeComponent()
	{
		Service::LogModule->UnregisterOutputHandler(&m_Handler);
	}





}	// namespace SF


