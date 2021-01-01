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
#include "Thread/SFThread.h"



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
			MAX_CALLSTACK_DEPTH		= 12,
			MIN_EXEOFFSET			= 0x100,
		};

		ThreadID m_CapturedThreadID;
		size_t m_StackTraceCount;
		void* m_StackTrace[MAX_CALLSTACK_DEPTH];

		// constructor
		CallStackTrace();

		void CaptureCallStack(uint skipDepth = 0, uint maxDepth = CallStackTrace::MAX_CALLSTACK_DEPTH);

		// print stack trace
		Result PrintStackTrace(HANDLE hProcess );
	};


} // namespace SF



