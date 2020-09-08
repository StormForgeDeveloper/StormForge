////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2014 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Stack walker
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "String/SFStrUtil.h"
#include "Util/SFLog.h"
#include "Thread/SFSynchronization.h"
#include "Container/SFStackPool.h"
#include "Platform/StackWalker.h"
#include "Platform/StackWalkerComponent.h"
#include "Service/SFService.h"


#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#pragma comment(lib,"DbgHelp.lib")
#endif

#define STACKWALKER_MIN_EXE_OFFSET ((int64_t)0)


namespace SF {
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Stack walker
	//

	class StackWalkerImpl
	{
	public:

		// stack frame for x86
		struct stack_frame 
		{
			struct stack_frame* pNext;
			void* pReturn;
		};


	private:

		uint m_ModuleStackSkipDepth;
		HANDLE m_hProcess = INVALID_NATIVE_HANDLE_VALUE;
		wchar_t m_SymbolPath[1024];

	private:

		void UpdateSkipDepth();

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		Result BuildSymbolPath();
		Result LoadModuleSymbols();

		SF_FORCEINLINE void GetStackFrame( CONTEXT& context, STACKFRAME64& stackFrame, DWORD& imageType );

		void SF_STDCALL CaptureCallStackFast( CallStackTrace& stackTrace, DWORD imageType, CONTEXT &context, STACKFRAME64 &stackFrame, uint skipDepth, uint maxDepth );
		void SF_STDCALL CaptureCallStackReliable( CallStackTrace& stackTrace, DWORD imageType, CONTEXT &context, STACKFRAME64 &stackFrame, uint skipDepth, uint maxDepth );
#else
#endif

	public:
		// Constructor
		StackWalkerImpl();
		virtual ~StackWalkerImpl();

		// initialize stace walker
		bool SF_STDCALL Initialize();

		// get current stack trace
		void SF_STDCALL CaptureCallStack( CallStackTrace& stackTrace, uint skipDepth, uint maxDepth );

		// print stack trace
		void PrintStackTrace();
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory Page allocator
	//

	CallStackTrace::CallStackTrace()
	{
		m_StackTraceCount = 0;
		memset( m_StackTrace, 0, sizeof(m_StackTrace) );
	}

	void CallStackTrace::CaptureCallStack(uint skipDepth, uint maxDepth)
	{
		m_CapturedThreadID = ThisThread::GetThreadID();
		if(StackWalker::GetImpl() != nullptr)
			StackWalker::GetImpl()->CaptureCallStack(*this, skipDepth, maxDepth);
	}

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	Result CallStackTrace::PrintStackTrace(HANDLE hProcess )
	{
		uint8_t Buffer[1024];
		memset( Buffer, 0, sizeof(Buffer) );

		_SYMBOL_INFO &symbolInfo = *(_SYMBOL_INFO*)Buffer;
		symbolInfo.SizeOfStruct = sizeof(_SYMBOL_INFO);
		symbolInfo.MaxNameLen = sizeof(Buffer) - sizeof(_SYMBOL_INFO);

		IMAGEHLP_LINE64 lineInfo;
		memset( &lineInfo, 0, sizeof(lineInfo) );
		lineInfo.SizeOfStruct = sizeof(lineInfo);
		SFLog(System, Debug, "m_StackTrace:" );

		for( uint stackDepth = 0; stackDepth < m_StackTraceCount && m_StackTrace[stackDepth] != 0; stackDepth++ )
		{
			DWORD64 offsetFromSymbol;
			BOOL symbol = SymFromAddr( hProcess, (DWORD64)m_StackTrace[stackDepth], &offsetFromSymbol, &symbolInfo );

			DWORD offsetFromLine;
			if( SymGetLineFromAddr64( hProcess, (DWORD64)m_StackTrace[stackDepth], &offsetFromLine, &lineInfo ) )
			{
				if( symbol )
				{
					SFLog(System, Debug, "{0}:{1}", (const wchar_t*)symbolInfo.Name, (uint32_t)lineInfo.LineNumber );
				}
				else
				{
					SFLog(System, Debug, "{0}:{1}", lineInfo.FileName, (uint32_t)lineInfo.LineNumber );
				}
			}
			else
			{
				if( !symbol )
				{
					DWORD64 relativeAddress = (DWORD64)m_StackTrace[stackDepth] - ((DWORD64)STACKWALKER_MIN_EXE_OFFSET + MIN_EXEOFFSET);
					sprintf_s( symbolInfo.Name, symbolInfo.MaxNameLen, "0x%p", (void*)relativeAddress );
				}
				SFLog(System, Debug, "{0}", (const wchar_t*)symbolInfo.Name );
			}
		}

		if(Service::LogModule != nullptr) Service::LogModule->Flush();


		return ResultCode::FAIL;
	}
#elif SF_PLATFORM == SF_PLATFORM_ANDROID


	struct BacktraceState
	{
		void** current;
		void** end;
	};

	static _Unwind_Reason_Code __UnwindCallback(struct _Unwind_Context* context, void* arg)
	{
		BacktraceState* state = static_cast<BacktraceState*>(arg);
		uintptr_t pc = _Unwind_GetIP(context);
		if (pc) {
			if (state->current == state->end) {
				return _URC_END_OF_STACK;
			}
			else {
				*state->current++ = reinterpret_cast<void*>(pc);
			}
		}
		return _URC_NO_REASON;
	}

	Result CallStackTrace::PrintStackTrace(NativeHandle hProcess)
	{
		BacktraceState state = { m_StackTrace, m_StackTrace + MAX_CALLSTACK_DEPTH };
		_Unwind_Backtrace(__UnwindCallback, &state);

		m_StackTraceCount = state.current - m_StackTrace;

		for (size_t idx = 0; idx < m_StackTraceCount; ++idx)
		{
			const void* addr = m_StackTrace[idx];
			const char* symbol = "";

			Dl_info info;
			if (dladdr(addr, &info) && info.dli_sname) {
				symbol = info.dli_sname;
			}

			SFLog(System, Debug, "{0}", symbol);
		}

		Service::LogModule->Flush();

		return ResultCode::SUCCESS;
	}


#elif SF_PLATFORM == SF_PLATFORM_IOS
	Result CallStackTrace::PrintStackTrace(NativeHandle hProcess)
	{
		SFLog(System, Debug, "StackTrace: NotImpl");

		return ResultCode::SUCCESS;
	}
#else
	Result CallStackTrace::PrintStackTrace(NativeHandle hProcess)
	{
		char **strings;

		strings = backtrace_symbols(m_StackTrace, (int)m_StackTraceCount);

		SFLog(System, Debug, "m_StackTrace:" );

		for (uint stackDepth = 0; stackDepth < m_StackTraceCount && strings != nullptr && strings[stackDepth] != 0; stackDepth++)
		{
			SFLog(System, Debug, "{0}", strings[stackDepth]);
		}

		free(strings);

		return ResultCode::SUCCESS;
	}

#endif

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory Page allocator
	//

	StackWalkerImpl::StackWalkerImpl()
		: m_ModuleStackSkipDepth(0)
		, m_hProcess(INVALID_NATIVE_HANDLE_VALUE)
	{
	}

	StackWalkerImpl::~StackWalkerImpl()
	{
	}

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	Result StackWalkerImpl::BuildSymbolPath()
	{
		wchar_t curDir[1024], tempBuffer[1024];

		memset( m_SymbolPath, 0, sizeof(m_SymbolPath) );

		if( GetCurrentDirectoryW( (DWORD)countof(curDir), curDir ) > 0 )
		{
			curDir[countof(curDir)-1] = L'\0';
			wcscat_s(m_SymbolPath, curDir);
			wcscat_s(m_SymbolPath, L";");
		}
		else
		{
			curDir[0] = L'\0';
		}

		// Adding module directories
		if( GetModuleFileNameW(NULL, tempBuffer, (DWORD)countof(tempBuffer)) > 0 )
		{
			tempBuffer[countof(tempBuffer)-1] = L'\0';
			if( wcsncmp( curDir, tempBuffer, wcslen(curDir) ) != 0 )
			{
				wchar_t *found = tempBuffer + wcslen(tempBuffer) - 1;
				while( *found != L'\\' && found > tempBuffer ) found--;

				if( found >= tempBuffer ) *found = L'\0';

				wcscat_s(m_SymbolPath, tempBuffer);
				wcscat_s(m_SymbolPath, L";");
			}
		}

		return ResultCode::SUCCESS;
	}

	Result StackWalkerImpl::LoadModuleSymbols()
	{
		HMODULE hModules[512];
		wchar_t imageFileName[1024];
		DWORD cbNeeded = 0;
		Result result = 0;

		if( m_hProcess == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::UNEXPECTED;

		memset(hModules, 0, sizeof(hModules));
		if( !EnumProcessModulesEx( m_hProcess, hModules, sizeof(hModules), &cbNeeded, LIST_MODULES_ALL ) )
		{
			AssertRel( cbNeeded <= sizeof(hModules) );
			return ResultCode::FAIL;
		}

		for( uint iModule = 0; iModule < countof(hModules) && hModules[iModule] != 0; iModule++ )
		{
			MODULEINFO moduleInfo;
			memset( &moduleInfo, 0, sizeof(moduleInfo) );
			if( !GetModuleInformation( m_hProcess, hModules[iModule], &moduleInfo, sizeof(moduleInfo) ) )
				continue;

			if( GetModuleFileNameExW( m_hProcess, hModules[iModule], imageFileName, (DWORD)countof(imageFileName) ) == 0 )
			{
				//result = GetLatestResultCode();
				continue;
			}

			if( SymLoadModuleExW( m_hProcess, NULL, imageFileName, NULL, (DWORD64)moduleInfo.lpBaseOfDll, moduleInfo.SizeOfImage, NULL, 0 ) == 0 )
			{
				//result = GetLatestResultCode();
				continue;
			}
		}
		

		return ResultCode::SUCCESS;
	}
	
	void StackWalkerImpl::GetStackFrame( CONTEXT& context, STACKFRAME64& stackFrame, DWORD& imageType )
	{
		memset(&stackFrame, 0, sizeof(stackFrame));
#ifdef _M_IX86
		imageType = IMAGE_FILE_MACHINE_I386;
		stackFrame.AddrPC.Offset = context.Eip;
		stackFrame.AddrPC.Mode = AddrModeFlat;
		stackFrame.AddrFrame.Offset = context.Ebp;
		stackFrame.AddrFrame.Mode = AddrModeFlat;
		stackFrame.AddrStack.Offset = context.Esp;
		stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
		imageType = IMAGE_FILE_MACHINE_AMD64;
		stackFrame.AddrPC.Offset = context.Rip;
		stackFrame.AddrPC.Mode = AddrModeFlat;
		stackFrame.AddrFrame.Offset = context.Rdi;
		stackFrame.AddrFrame.Mode = AddrModeFlat;
		stackFrame.AddrStack.Offset = context.Rsp;
		stackFrame.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
		imageType = IMAGE_FILE_MACHINE_IA64;
		stackFrame.AddrPC.Offset = context.StIIP;
		stackFrame.AddrPC.Mode = AddrModeFlat;
		stackFrame.AddrFrame.Offset = context.IntSp;
		stackFrame.AddrFrame.Mode = AddrModeFlat;
		stackFrame.AddrStack.Offset = context.IntRsp;
		stackFrame.AddrStack.Mode = AddrModeFlat;
#else
#error "Not supported CPU architecture"
#endif
	}

	// Find maximum skip depth
	void StackWalkerImpl::UpdateSkipDepth()
	{
		CallStackTrace stackTrace;
		uint MaxSearchDepth = 7;
		HANDLE hThread = GetCurrentThread();
		STACKFRAME64 stackFrame;
		DWORD imageType = 0;
		CONTEXT context;

		context.ContextFlags = CONTEXT_CONTROL;
		RtlCaptureContext(&context);

		GetStackFrame( context, stackFrame, imageType );

		m_ModuleStackSkipDepth = 1;

#if defined(_M_IX86) || defined(_M_X64)
		// Use fast version stack trace
		stackTrace.m_StackTraceCount = CaptureStackBackTrace( 1, MaxSearchDepth, stackTrace.m_StackTrace, nullptr );
		//CaptureCallStackFast( stackTrace, imageType, context, stackFrame, 1, MaxSearchDepth );
#else
		CaptureCallStackReliable( stackTrace, imageType, context, stackFrame, 1, MaxSearchDepth );
#endif

		IMAGEHLP_LINE64 lineInfo;
		memset( &lineInfo, 0, sizeof(lineInfo) );
		lineInfo.SizeOfStruct = sizeof(lineInfo);
		for( uint stackDepth = 0; stackDepth < MaxSearchDepth && stackTrace.m_StackTrace[stackDepth] != 0; stackDepth++ )
		{
			DWORD offsetFromLine = 0;
			if( !SymGetLineFromAddr64( m_hProcess, (DWORD64)stackTrace.m_StackTrace[stackDepth], &offsetFromLine, &lineInfo ) )
				continue;

			if( strstr( lineInfo.FileName, "stackwalker." ) != NULL )
			{
				// Update skippable depth
				m_ModuleStackSkipDepth = stackDepth + 1;
			}
		}

		// If we couldn't find any depth then set to 2 
		if( m_ModuleStackSkipDepth <= 1 )
		{
			m_ModuleStackSkipDepth = 2;
		}
		else
		{
			// remove one for initialize
			m_ModuleStackSkipDepth--;
		}
	}

	// This implementation tested on x86 and x64
	void SF_STDCALL StackWalkerImpl::CaptureCallStackFast( CallStackTrace& stackTrace, DWORD imageType, CONTEXT &context, STACKFRAME64 &stackFrame, uint skipDepth, uint maxDepth )
	{
		ULONG_PTR lowLimit, highLimit;
		HANDLE hThread = GetCurrentThread();

		//GetCurrentThreadStackLimits( &lowLimit, &highLimit );
		PNT_TIB pTib = reinterpret_cast<PNT_TIB>(NtCurrentTeb());
		highLimit = (ULONG_PTR)pTib->StackBase;
		lowLimit = (ULONG_PTR)pTib->StackLimit;
		
		Assert(skipDepth >= 1);
		skipDepth--;
		maxDepth--;

		stack_frame *currentStackFrame = (stack_frame*)stackFrame.AddrFrame.Offset;
		stack_frame *latestStackFrame = currentStackFrame;
		uint stackIndex = 0;
		for( uint frameNumber = 1; 
			currentStackFrame != nullptr 
				&& ((frameNumber < m_ModuleStackSkipDepth) || (frameNumber - m_ModuleStackSkipDepth) < maxDepth)
				&& stackIndex < CallStackTrace::MAX_CALLSTACK_DEPTH;
			++frameNumber )
		{
			ULONG_PTR stackFramePtr = (ULONG_PTR)currentStackFrame;
			if( stackFramePtr == NULL || stackFramePtr < lowLimit || stackFramePtr > highLimit
				|| (int64_t)currentStackFrame->pReturn < STACKWALKER_MIN_EXE_OFFSET)
			{
				stackTrace.m_StackTraceCount = stackIndex;

				//if( currentStackFrame->pReturn != nullptr && (stackFramePtr < lowLimit || stackFramePtr > highLimit) )
				//{
				//	// We steped into wrong place, get back previous stack and retrive again
				//	frameNumber--;
				//	currentStackFrame = latestStackFrame;
				//	stackFrame.AddrPC.Offset = (DWORD64)latestStackFrame->pReturn;
				//	stackFrame.AddrFrame.Offset = (DWORD64)latestStackFrame;
				//	stackFrame.AddrStack.Offset = (DWORD64)latestStackFrame;

				//	// Fast trace is failed, try reliable trace
				//	if( !StackWalk64( imageType, m_hProcess, hThread, &stackFrame, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL ) )
				//		return;

				//	currentStackFrame = (stack_frame*)stackFrame.AddrFrame.Offset;
				//	
				//	if( frameNumber < skipDepth )
				//		continue;

				//	stackTrace.m_StackTrace[ stackIndex++ ] = (void*)stackFrame.AddrPC.Offset;
				//	continue;
				//}
				//else
				{
					return;
				}
			}

			latestStackFrame = currentStackFrame;

			if( frameNumber < skipDepth )
			{
				currentStackFrame = currentStackFrame->pNext;
				continue;
			}

			stackTrace.m_StackTrace[stackIndex++] = currentStackFrame->pReturn;
			currentStackFrame = currentStackFrame->pNext;
		}

		stackTrace.m_StackTraceCount = stackIndex;
	}

	void SF_STDCALL StackWalkerImpl::CaptureCallStackReliable( CallStackTrace& stackTrace, DWORD imageType, CONTEXT &context, STACKFRAME64 &stackFrame, uint skipDepth, uint maxDepth )
	{
		HANDLE hThread = GetCurrentThread();

		uint stackIndex = 0;
		for( uint frameNumber = 1; (frameNumber - m_ModuleStackSkipDepth) < maxDepth && stackIndex < CallStackTrace::MAX_CALLSTACK_DEPTH; ++frameNumber )
		{
			if( !StackWalk64( imageType, m_hProcess, hThread, &stackFrame, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL ) )
				break;

			// frame skipping
			if( frameNumber < skipDepth )
				continue;

			stackTrace.m_StackTrace[ stackIndex++ ] = (void*)stackFrame.AddrPC.Offset;

			// prevent infinite call
			if( stackFrame.AddrPC.Offset == stackFrame.AddrReturn.Offset )
				break;

			// 
			if( stackFrame.AddrReturn.Offset == 0 )
				break;
		}

		stackTrace.m_StackTraceCount = stackIndex;
	}

	// get current stack trace
	// #pragma optimize("y",off)
	void SF_STDCALL StackWalkerImpl::CaptureCallStack( CallStackTrace& stackTrace, uint skipDepth, uint maxDepth )
	{
		STACKFRAME64 stackFrame;
		DWORD imageType = 0;
		CONTEXT context;

		context.ContextFlags = CONTEXT_CONTROL;
		RtlCaptureContext(&context);

		GetStackFrame( context, stackFrame, imageType );

#if defined(_M_IX86) || defined(_M_X64)
		// Use fast version stack trace
		maxDepth = std::min( maxDepth - skipDepth + m_ModuleStackSkipDepth, (uint)CallStackTrace::MAX_CALLSTACK_DEPTH );
		stackTrace.m_StackTraceCount = CaptureStackBackTrace( skipDepth + m_ModuleStackSkipDepth, maxDepth, stackTrace.m_StackTrace, nullptr );
		//CaptureCallStackFast( stackTrace, imageType, context, stackFrame, skipDepth + m_ModuleStackSkipDepth, maxDepth );
#else
		CaptureCallStackReliable( stackTrace, imageType, context, stackFrame, skipDepth + m_ModuleStackSkipDepth, maxDepth );
#endif
	}


	// initialize stace walker
	// #pragma optimize("y",off)
	bool StackWalkerImpl::Initialize()
	{
		m_hProcess = GetCurrentProcess();

		if (!(BuildSymbolPath()))
			return false;

		if (!SymInitializeW(m_hProcess, (PWSTR)m_SymbolPath, false))
			return false;

		// symbol load option
		DWORD symbolLoadOptions = SymGetOptions();
		symbolLoadOptions |= SYMOPT_LOAD_LINES | SYMOPT_FAIL_CRITICAL_ERRORS;
		symbolLoadOptions = SymSetOptions(symbolLoadOptions);

		if (!(LoadModuleSymbols()))
			return false;

		UpdateSkipDepth();

		return true;
	}


#elif SF_PLATFORM == SF_PLATFORM_ANDROID


// initialize stace walker
bool StackWalkerImpl::Initialize()
{
	m_ModuleStackSkipDepth = 2;

	return true;
}

// get current stack trace
void StackWalkerImpl::CaptureCallStack(CallStackTrace& stackTrace, uint skipDepth, uint maxDepth)
{
	BacktraceState state = { stackTrace.m_StackTrace, stackTrace.m_StackTrace + CallStackTrace::MAX_CALLSTACK_DEPTH };
	_Unwind_Backtrace(__UnwindCallback, &state);

	stackTrace.m_StackTraceCount = state.current - stackTrace.m_StackTrace;
}


#elif SF_PLATFORM == SF_PLATFORM_IOS

// initialize stace walker
bool StackWalkerImpl::Initialize()
{
	m_ModuleStackSkipDepth = 2;

	return true;
}

// get current stack trace
void StackWalkerImpl::CaptureCallStack(CallStackTrace& stackTrace, uint skipDepth, uint maxDepth)
{
	// TODO: not impl
	stackTrace.m_StackTraceCount = 0;
}


#else

	// initialize stace walker
	bool StackWalkerImpl::Initialize()
	{
		m_ModuleStackSkipDepth = 2;

		return true;
	}

	// get current stack trace
	void StackWalkerImpl::CaptureCallStack(CallStackTrace& stackTrace, uint skipDepth, uint maxDepth)
	{
		stackTrace.m_StackTraceCount = backtrace(stackTrace.m_StackTrace, countof(stackTrace.m_StackTrace));
	}


#endif


	// print stack trace
	void StackWalkerImpl::PrintStackTrace()
	{
		CallStackTrace stackTrace;
		CaptureCallStack( stackTrace, 0, CallStackTrace::MAX_CALLSTACK_DEPTH );

		stackTrace.PrintStackTrace(m_hProcess);
	}



	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Stack walker
	//

	constexpr StringCrc64 StackWalker::TypeName;

	StackWalkerImpl* StackWalker::stm_pInstance = nullptr;


	StackWalker::StackWalker()
		: LibraryComponent("StackWalker")
	{
		if (stm_pInstance == nullptr)
		{
			stm_pInstance = new(GetSystemHeap()) StackWalkerImpl;
			stm_pInstance->Initialize();
		}
	}

	StackWalker::~StackWalker()
	{
		GetSystemHeap().Delete(stm_pInstance);
		stm_pInstance = nullptr;
	}

	// Initialize component
	Result StackWalker::InitializeComponent()
	{

		return ResultCode::SUCCESS;
	}

		// Terminate component
	void StackWalker::DeinitializeComponent()
	{
		if (stm_pInstance == nullptr)
			return;

		delete stm_pInstance;
		stm_pInstance = nullptr;
	}


	// print stack trace
	void StackWalker::PrintStackTrace()
	{
		if(stm_pInstance == nullptr )
			return;

		stm_pInstance->PrintStackTrace();
	}


};	// namespace SF


