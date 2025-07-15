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
#include "Platform/SFStackWalker.h"
#include "Component/SFUnhandledExceptionHandlerComponent.h"

#include <filesystem>

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#include <stacktrace>
#else
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#endif

namespace SF {

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//  System Exception handler
	//


	constexpr StringCrc64 UnhandledExceptionHandlerComponent::TypeName;


#if SF_PLATFORM == SF_PLATFORM_LINUX
    void CrashHandlerLinux(int signal, siginfo_t* info, void* Context)
    {
        fprintf(stderr, "System Signal %d.\n", signal);

        fprintf(stderr, "System Signal %S.\n", STRSIGNAL(signal));
        if (signal == SIGSYS)
        {
            fprintf(stderr, "si_syscall:%d.\n", info->si_syscall);
        }

        void* caller_address{};
        sig_ucontext_t* uc = (sig_ucontext_t*)ucontext;

        /* Get the address at the time the signal was raised */
#if defined(__i386__) // gcc specific
        caller_address = (void*)uc->uc_mcontext.eip; // EIP: x86 specific
#elif defined(__x86_64__) // gcc specific
        caller_address = (void*)uc->uc_mcontext.rip; // RIP: x86_64 specific
#else
#error Unsupported architecture. // TODO: Add support for other arch.
#endif

        fprintf(stderr, "signal %d (%s), address is %p from %p\n",
            sig_num, strsignal(sig_num), info->si_addr,
            (void*)caller_address);

        void* callStackArray[50];
        int capturedSize = backtrace(array, countof(callStackArray));

        /* overwrite sigaction with caller's address */
        array[1] = caller_address;

        char** messages = backtrace_symbols(callStackArray, size);

        /* skip first stack frame (points here) */
        for (i = 1; i < size && messages != NULL; ++i)
        {
            fprintf(stderr, "[bt]: (%d) %s\n", i, messages[i]);
        }

        // send to log as well
        for (i = 1; i < size && messages != NULL; ++i)
        {
            SFLog(System, Error, "[bt]: (%d) %s\n", i, messages[i]);
        }

        free(messages);

        Service::LogModule->Flush();
    }
#endif // SF_PLATFORM != SF_PLATFORM_LINUX


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

            // Append module path
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

    void UnhandledExceptionHandlerComponent::OnTerminate()
    {
        try {
            auto unknown = std::current_exception();
            if (unknown) {

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
                std::stacktrace trace = std::stacktrace::current();

                std::cerr << trace;

                for (const std::stacktrace_entry& stackEntry : trace)
                {
                    SFLog(System, Factal, "Stack: {0}, {1}:{2}", stackEntry.description(), stackEntry.source_file(), stackEntry.source_line());
                }
#else
                CallStackTraceT<20> trace;
                trace.PrintStackTrace(CurrentProcessID);
#endif
                std::rethrow_exception(unknown);
            }
            else {
                std::cerr << "normal termination" << std::endl;
            }
        }
        catch (const std::exception& e) { // for proper `std::` exceptions
            std::cerr << "unexpected exception: " << e.what() << std::endl;
        }
        catch (...) { // last resort for things like `throw 1;`
            std::cerr << "unknown exception" << std::endl;
        }
    }
	// Initialize component
	Result UnhandledExceptionHandlerComponent::InitializeComponent()
	{
		auto result = LibraryComponent::InitializeComponent();
		if (!result)
			return result;

        std::cout << "Initializing unhandled exception handler" << std::endl;
        SFLog(System, Info, "Initializing unhandled exception handler");

        std::set_terminate(OnTerminate);

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		::SetUnhandledExceptionFilter(&CrashHandler);
#else SF_PLATFORM == SF_PLATFORM_LINUX
        struct sigaction action;
        memset(&action, 0, sizeof(action));
        action.sa_sigaction = CrashHandlerLinux;
        sigfillset(&action.sa_mask);
        action.sa_flags = SA_SIGINFO | SA_RESTART | SA_ONSTACK;
        sigaction(SIGQUIT, &action, nullptr);
        sigaction(SIGABRT, &action, nullptr);
        sigaction(SIGILL, &action, nullptr);
        sigaction(SIGFPE, &action, nullptr);
        sigaction(SIGBUS, &action, nullptr);
        sigaction(SIGSEGV, &action, nullptr);
        sigaction(SIGSYS, &action, nullptr);
        //sigaction(SIGTRAP, &action, nullptr);
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

