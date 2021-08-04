////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Stack walker
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "Multithread/SFThread.h"



namespace SF {


#if SF_PLATFORM == SF_PLATFORM_WINDOWS
#define CurrentProcessID GetCurrentProcess()
#else
#define CurrentProcessID 0
#endif


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Stack trace
	//

	struct CallStackTrace
	{
		enum {
			MIN_EXEOFFSET			= 0x100,
		};

		ThreadID m_CapturedThreadID;
		size_t m_StackTraceCount = 0;

		// constructor
		CallStackTrace();

		void CaptureCallStack(void** stackBuffer, uint bufferCount, uint skipDepth, uint maxDepth);

		// print stack trace
		Result PrintStackTrace(void** stackTrace, HANDLE hProcess );
	};


	template<uint MaxCallStackDepth = 12>
	struct CallStackTraceT : public CallStackTrace
	{
		void* m_StackTrace[MaxCallStackDepth]{};

		void CaptureCallStack(uint skipDepth = 0, uint maxDepth = MaxCallStackDepth)
		{
			CallStackTrace::CaptureCallStack(m_StackTrace, MaxCallStackDepth, skipDepth, std::min(MaxCallStackDepth, maxDepth));
		}

		Result PrintStackTrace(HANDLE hProcess)
		{
			return CallStackTrace::PrintStackTrace(m_StackTrace, hProcess);
		}
	};

} // namespace SF



