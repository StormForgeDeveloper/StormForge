////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Util/SFPath.h"
#include "Service/SFService.h"
#include "Variable/SFVariableBoxing.h"
#include "Util/SFStringConverter.h"

#include <filesystem>

namespace SF {


	constexpr StringCrc64 LogOutputConsoleComponent::TypeName;

    namespace Log
    {
        LogChannel OutputConsole("OutputConsole", ELogLevel::Debug3);
    }

	LogOutputConsoleComponent::LogOutputConsoleComponent()
		: LibraryComponent(StringCrc64("LogConsole"))
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
        // For some reason, docker doesn't like std::cout
        printf("%s", logMessage->LogBuff);
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




    namespace Log
    {
        LogChannel OutputDebugger("OutputDebugger", ELogLevel::Max);
    }

	constexpr StringCrc64 LogOutputDebuggerComponent::TypeName;

	LogOutputDebuggerComponent::LogOutputDebuggerComponent()
		: LibraryComponent(StringCrc64("LogDebugger"))
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



    namespace Log
    {
        LogChannel OutputFile("OutputFile", ELogLevel::Max);
    }

	constexpr StringCrc64 LogOutputFileComponent::TypeName;

	LogOutputFileComponent::LogOutputFileComponent(const String& filePrefix, bool bOpenNewHourly)
		: LibraryComponent(StringCrc64("LogFile"))
		, m_Handler(filePrefix, bOpenNewHourly)
	{

	}


	LogOutputFileComponent::~LogOutputFileComponent()
	{

	}

	LogOutputFileComponent::MyOutputHandler::MyOutputHandler(const String& filePrefix, bool bOpenNewHourly)
        : LogOutputHandler("OutputFile")
        , m_FilePrefix(filePrefix)
		, m_OpenNewFileHourly(bOpenNewHourly)
	{
		FileUtil::CreatePath(m_FilePrefix, 1);
		OpenLogFile();
	}

	void LogOutputFileComponent::MyOutputHandler::OpenLogFile()
	{
		auto logFileCreated = std::chrono::system_clock::now();
		auto createdTimet = std::chrono::system_clock::to_time_t(logFileCreated);
		auto timeStruct = std::localtime(&createdTimet);
		m_LogFileCreatedHour = timeStruct->tm_hour;

        m_LogFilePath.Format("{0}_{1}{2}{3}_{4:02}{5:02}{6:02}.log", m_FilePrefix.ToString(), timeStruct->tm_year + 1900, timeStruct->tm_mon + 1, timeStruct->tm_mday, timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
		m_File.Open(m_LogFilePath, File::OpenMode::Create);
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

        // make copy of log file name so that other module can access it
        Service::LogModule->SetLogFileName(m_Handler.GetLogFilePath());

        // Clear old log files
        //std::filesystem::
        String logDir = Util::Path::GetFileDirectory(m_Handler.GetLogFilePath());
        if (!logDir.EndsWith(Util::Path::DirectorySeparatorChars))
        {
            logDir.Append(Util::Path::DirectorySeparatorChar);
        }


        constexpr DurationMS fileLifeTime(2 * 24 * 60 * 60 * 1000);
        //constexpr DurationMS fileLifeTime(5 * 1000);
        auto systemNow = std::filesystem::file_time_type::clock::now();
        std::filesystem::path logDirPath(logDir.c_str());
        for (const auto& itFile : std::filesystem::directory_iterator(logDirPath, std::filesystem::directory_options::skip_permission_denied))
        {
            if (itFile.is_directory() || !itFile.is_regular_file())
                continue;

            std::filesystem::path filePath = itFile.path();
            std::filesystem::path::string_type ext = filePath.extension().c_str();

            StringConverter<char, std::filesystem::path::value_type> converter;

            String fileExt = converter.Convert(ext.c_str());
            if (!fileExt.EndsWith("log", true) && !fileExt.EndsWith("dmp", true))
                continue;

            std::filesystem::file_time_type fileTime = itFile.last_write_time();
            DurationMS timeSince = std::chrono::duration_cast<DurationMS>(systemNow - fileTime);
            if (timeSince > fileLifeTime)
            {
                std::error_code err;
                std::filesystem::remove(filePath, err);
            }
        }

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void LogOutputFileComponent::DeinitializeComponent()
	{
		Service::LogModule->UnregisterOutputHandler(&m_Handler);
	}

}	// namespace SF
