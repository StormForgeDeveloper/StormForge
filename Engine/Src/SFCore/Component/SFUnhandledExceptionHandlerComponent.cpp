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
#include <ucontext.h>
#include <dlfcn.h>
#endif

namespace SF {

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//  System Exception handler
	//


	constexpr StringCrc64 UnhandledExceptionHandlerComponent::TypeName;


#if SF_PLATFORM == SF_PLATFORM_LINUX
    void CrashHandlerLinux(int signal, siginfo_t* info, void* context)
    {
	    static bool bHandled = false;
	    if (bHandled)
		    return;

	    bHandled = true;
        void* caller_address{};
        ucontext_t* uc = reinterpret_cast<ucontext_t*>(context);

        /* Get the address at the time the signal was raised */
        caller_address = (void*)uc->uc_mcontext.gregs[REG_RIP];

	    fprintf(stderr, "signal %d (%s), address is %p from %p\n",
                signal, strsignal(signal), info->si_addr,
                (void*)caller_address);

        constexpr size_t maxStack = 50;
        void* callStackArray[maxStack];
        int capturedSize = backtrace(callStackArray, countof(callStackArray));

        /* overwrite sigaction with caller's address */
        //callStackArray[1] = caller_address;

        char** messages = backtrace_symbols(callStackArray, capturedSize);

        Dl_info dlInfos[maxStack];
        memset(dlInfos, 0, sizeof(dlInfos));

        /* skip first stack frame (points here) */
        for (int i = 1; i < capturedSize && messages != NULL; ++i)
        {
            const char* message = messages[i] ? messages[i] : "";
            Dl_info& dlInfo = dlInfos[i];
            if (dladdr(callStackArray[i], &dlInfo) && dlInfo.dli_fname && dlInfo.dli_fbase)
            {
                void* pOffset = reinterpret_cast<void*>(uintptr_t(callStackArray[i]) - uintptr_t(dlInfo.dli_fbase));
                fprintf(stderr, "[bt]: (%d) %s, %s, %p\n", i, message, dlInfo.dli_fname, pOffset);
            }
            else
            {
                fprintf(stderr, "[bt]: (%d) %s\n", i, message);
            }
        }

        // send to log as well
        SFLog(System, Error, "signal {0} ({1}), address is {2} from {3}",
            signal, strsignal(signal), info->si_addr, (void*)caller_address);

        for (int i = 1; i < capturedSize && messages != NULL; ++i)
        {
            const char* message = messages[i] ? messages[i] : "";
            Dl_info& dlInfo = dlInfos[i];
            if (dlInfo.dli_fname && dlInfo.dli_fbase)
            {
                void* pOffset = reinterpret_cast<void*>(uintptr_t(callStackArray[i]) - uintptr_t(dlInfo.dli_fbase));
                SFLog(System, Error, "[bt]: ({0}) {1}, {2}, offset:{3}\n", i, message, dlInfo.dli_fname, pOffset);
            }
            else
            {
                SFLog(System, Error, "[bt]: ({0}) {1}", i, message);
            }
        }

        free(messages);

        Service::LogModule->Flush();

	    std::this_thread::sleep_for(std::chrono::seconds(5));
	    exit(0);
    }

    void CustomTerminate()
    {
        std::cerr << "Terminate called after throwing an uncaught exception\n";

        // Print stack trace
        void* array[20];
        int size = backtrace(array, 20);
        char** strings = backtrace_symbols(array, size);

        std::cerr << "Stack trace:\n";
        for (int i = 0; i < size; ++i) {
            std::cerr << strings[i] << "\n";
        }
        free(strings);

        std::abort(); // Force abnormal termination
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

                std::cerr << "OnTerminate" << std::endl;

                // Only on windows at the moment
#if 1 || SF_PLATFORM == SF_PLATFORM_WINDOWS
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
#elif SF_PLATFORM == SF_PLATFORM_LINUX
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
        sigaction(SIGTRAP, &action, nullptr);
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

