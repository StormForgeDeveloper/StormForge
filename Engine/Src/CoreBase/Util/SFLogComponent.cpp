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


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFLogComponent.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFUtility.h"
#include "String/SFFixedString.h"
#include "Service/SFService.h"



namespace SF {


	constexpr FixedString LogOutputConsoleComponent::TypeName;


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



	LogOutputConsoleComponent::LogOutputConsoleComponent(const LogChannelMask& logMask)
		: LibraryComponent(FixedString("LogConsole"))
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

	void LogOutputConsoleComponent::MyOutputHandler::PrintOutput(const Log::LogModule::LogItem* logMessage)
	{
		if (logMessage == nullptr) return;

		const char* channelName = MainChannelNames[std::min((uint)logMessage->MainChannel, (uint)LogMainChannelType::Max - 1)];

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

		__android_log_print(logPriority, "StormForge", "%s: %s", channelName, logMessage->LogBuff);
#elif SF_PLATFORM == SF_PLATFORM_WINDOWS
		if (m_hConsole == INVALID_NATIVE_HANDLE_VALUE)
			return;

		DWORD dwWriten = 0;
		char strTimeLine[256];

		std::time_t logTime = std::chrono::system_clock::to_time_t(logMessage->TimeStamp);
		auto tm = std::localtime(&logTime);
		auto sizeTimeLine = StrUtil::Format(strTimeLine, "{0}:{1}:{2} {3}", tm->tm_hour, tm->tm_min, tm->tm_sec, channelName);

		WriteConsoleA(m_hConsole, strTimeLine, (DWORD)sizeTimeLine, &dwWriten, nullptr);
		WriteConsoleA(m_hConsole, logMessage->LogBuff, (DWORD)logMessage->LogStringSize, &dwWriten, nullptr);
#else
		std::time_t logTime = std::chrono::system_clock::to_time_t(logMessage->TimeStamp);
		std::cout << std::put_time(std::localtime(&logTime), "%F %T") << ":(" << channelName << ":" << (int)logMessage->SubChannel << "): " << logMessage->LogBuff << "\r\n";
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





	constexpr FixedString LogOutputDebuggerComponent::TypeName;

	LogOutputDebuggerComponent::LogOutputDebuggerComponent(const LogChannelMask& logMask)
		: LibraryComponent(FixedString("LogDebugger"))
		, m_Handler(logMask)
	{

	}

	LogOutputDebuggerComponent::~LogOutputDebuggerComponent()
	{

	}

	void LogOutputDebuggerComponent::MyOutputHandler::PrintOutput(const Log::LogModule::LogItem* logMessage)
	{
		if (logMessage == nullptr) return;
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		OutputDebugStringA(logMessage->LogBuff);
		OutputDebugStringA("\n");
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



	constexpr FixedString LogOutputFileComponent::TypeName;

	LogOutputFileComponent::LogOutputFileComponent(const LogChannelMask& logMask, const String& filePrefix, bool bOpenNewHourly)
		: LibraryComponent(FixedString("LogFile"))
		, m_Handler(logMask, filePrefix, bOpenNewHourly)
	{

	}


	LogOutputFileComponent::~LogOutputFileComponent()
	{

	}

	LogOutputFileComponent::MyOutputHandler::MyOutputHandler(const LogChannelMask& logMask, const String& filePrefix, bool bOpenNewHourly)
		: LogOutputHandler(logMask)
		, m_FilePrefix(filePrefix)
		, m_OpenNewFileHourly(bOpenNewHourly)
	{

		OpenLogFile();
	}

	void LogOutputFileComponent::MyOutputHandler::OpenLogFile()
	{

		String filePath;

		auto logFileCreated = std::chrono::system_clock::now();
		auto createdTimet = std::chrono::system_clock::to_time_t(logFileCreated);
		auto timeStruct = std::localtime(&createdTimet);
		m_LogFileCreatedHour = timeStruct->tm_hour;

		filePath.Format("{0}_{1}{2}{3}_{4}.log", m_FilePrefix, timeStruct->tm_year + 1900, timeStruct->tm_mon + 1, timeStruct->tm_mday, timeStruct->tm_hour);
		m_File.Open(filePath, File::OpenMode::Create);
		if (m_File.IsOpened())
		{
			size_t szWritten;
			// UTF8 BOM
			static const uint8_t bytBOM[3] = { 0xEF, 0xBB, 0xBF };
			m_File.Write(bytBOM, 3, szWritten);
		}
	}




	void LogOutputFileComponent::MyOutputHandler::PrintOutput(const Log::LogModule::LogItem* logMessage)
	{
		if (logMessage == nullptr) return;
		if (!m_File.IsOpened()) return;

		const char* channelName = MainChannelNames[std::min((uint)logMessage->MainChannel, (uint)LogMainChannelType::Max - 1)];

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
		char timeStampString[256];
		size_t stringSize = StrUtil::Format(timeStampString, "{0}:{1}/{2}:{3:X8}>{4}: ", timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec, Util::Time.GetTimeMs().time_since_epoch().count(), channelName);
		m_File.Write((uint8_t*)timeStampString, stringSize - 1, writen);
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


