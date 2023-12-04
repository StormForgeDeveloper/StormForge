////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Crash reporter for windows
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "Util/SFPath.h"
#include "Component/SFUnhandledExceptionHandlerComponent.h"


namespace SF {

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//  System Exception handler
	//


	constexpr StringCrc64 UnhandledExceptionHandlerComponent::TypeName;


	UnhandledExceptionHandlerComponent::UnhandledExceptionHandlerComponent(bool bEnableFullDump)
		: LibraryComponent(TypeName)
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        m_bEnableFullDump = bEnableFullDump;
#endif
    }

    void UnhandledExceptionHandlerComponent::SetCrashShellCommand(const char* command)
    {
        m_CrashShellCommand[0] = {};

        if (!StrUtil::IsNullOrEmpty(command))
        {
            // make the command bg
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
            if (!StrUtil::StringCompairIgnoreCase("start ", 6, command, 6))
            {
                StrUtil::StringCopy(m_CrashShellCommand, "start ");
            }
#endif
            StrUtil::StringCat(m_CrashShellCommand, command);
        }
    }

    void UnhandledExceptionHandlerComponent::SetCrashDumpFilePrefix(const char* crashDumpPrefix)
    {
        if (!StrUtil:: IsNullOrEmpty(crashDumpPrefix))
        {
            StrUtil::StringCopy(m_CrashDumpFilePrefix, crashDumpPrefix);
        }
        else
        {
            StrUtil::StringCopy(m_CrashDumpFilePrefix, Util::Path::WithoutExt(Service::LogModule->GetLogFileName()));
        }
    }

	// Initialize component
	Result UnhandledExceptionHandlerComponent::InitializeComponent()
	{
		auto result = LibraryComponent::InitializeComponent();
		if (!result)
			return result;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		::SetUnhandledExceptionFilter(&CrashHandler);
#endif

		return result;
	}

	// Terminate component
	void UnhandledExceptionHandlerComponent::DeinitializeComponent()
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        ::SetUnhandledExceptionFilter(nullptr);
#endif
        LibraryComponent::DeinitializeComponent();
	}

    char UnhandledExceptionHandlerComponent::m_CrashShellCommand[8 * 1024]{};
    char UnhandledExceptionHandlerComponent::m_CrashDumpFilePrefix[1024]{};

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
    bool UnhandledExceptionHandlerComponent::m_bEnableFullDump = false;
    char UnhandledExceptionHandlerComponent::m_DumpFilePathBuffer[1024];
	void UnhandledExceptionHandlerComponent::WriteCrashDump(EXCEPTION_POINTERS* ipExPtrs, MINIDUMP_TYPE dumpType, const char* strMode)
	{
		const char szDumpFileExt[] = ".dmp";
		SYSTEMTIME kSysTime;
		GetLocalTime(&kSysTime);

		sprintf_s(m_DumpFilePathBuffer, "%s_%04d%02d%02d_%2d%02d%02d_%s_%s%s",
            m_CrashDumpFilePrefix,
			kSysTime.wYear, kSysTime.wMonth, kSysTime.wDay,
			kSysTime.wHour, kSysTime.wMinute, kSysTime.wSecond, strMode, Util::GetServiceName(), szDumpFileExt);

		HANDLE hFile = CreateFileA(
			m_DumpFilePathBuffer,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFile)
		{
			MINIDUMP_EXCEPTION_INFORMATION eInfo;
			eInfo.ThreadId = GetCurrentThreadId();
			eInfo.ExceptionPointers = ipExPtrs;
			eInfo.ClientPointers = FALSE;


			MiniDumpWriteDump(
				GetCurrentProcess(),
				GetCurrentProcessId(),
				hFile,
				dumpType,
				ipExPtrs ? &eInfo : NULL,
				NULL,
				NULL);

            if (!StrUtil::IsNullOrEmpty(m_CrashShellCommand))
            {
                StrUtil::StringCat(m_CrashShellCommand, " -dumpfile=");
                StrUtil::StringCat(m_CrashShellCommand, m_DumpFilePathBuffer);
            }
		}
		CloseHandle(hFile);
	}

	long __stdcall UnhandledExceptionHandlerComponent::CrashHandler( EXCEPTION_POINTERS* ipExPtrs )
	{
		uint uiRetCode = EXCEPTION_CONTINUE_SEARCH; // enable whatever system handler
		MINIDUMP_TYPE dumpType = MiniDumpWithFullMemory;

		WriteCrashDump(ipExPtrs, MiniDumpNormal, "mini");
		if (m_bEnableFullDump && dumpType != MiniDumpNormal)
		{
#ifdef _DEBUG
            const char* strMode = "DebugFull";
#else
            const char* strMode = "ReleaseFull";
#endif
			WriteCrashDump(ipExPtrs, dumpType, strMode);
		}

		Service::LogModule->Flush();

        const char* logFileName = Service::LogModule->GetLogFileName();
        if (!StrUtil::IsNullOrEmpty(m_CrashShellCommand) && !StrUtil::IsNullOrEmpty(logFileName))
        {
            StrUtil::StringCat(m_CrashShellCommand, " -logfile=");
            StrUtil::StringCat(m_CrashShellCommand, logFileName);


#if SF_PLATFORM != SF_PLATFORM_WINDOWS
            // Linux bg command
            StrUtil::StringCat(m_CrashShellCommand, " &");
#endif

            std::system(m_CrashShellCommand);
        }

		return uiRetCode;
	}
#endif

} // namespace SF

