////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Debug definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Platform/SFStackWalker.h"


#if SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID || SF_PLATFORM == SF_PLATFORM_IOS
#define __debugbreak() raise(SIGTRAP)
#else
#endif

#define ForceAssert(condi) \
				do{ \
					if( !(condi) ) {\
						ReportAssert();\
						__debugbreak(); \
					}else{}\
				}while(0); \


inline void ReportAssert() { SF::CallStackTraceT<15> trace; trace.PrintStackTrace(0); }


#if defined(_DEBUG) || defined(DEBUG)

// Base Assert
#define Assert(expr) ForceAssert(expr)

// Assert even release mode
#define AssertRel(expr) ForceAssert(expr)


#else // #ifdef _DEBUG

#define Assert(condi)

// Assert in release mode
#define AssertRel(condi) ForceAssert(condi);


#endif

namespace SF {


	struct CallTrack
	{
		const char* FileName;
		int LineNumber;

		CallTrack(const char* fileName = __FILE__, int lineNumber = __LINE__)
			: FileName(fileName), LineNumber(lineNumber)
		{
		}
	};


}


