////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Trace helper
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Util/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"
#include "Util/SFStrFormat.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Platform/SFStackWalker.h"

#ifndef SHIPPING
#define TRACE_DBG
#endif


namespace SF {
	namespace Trace {


		class TraceOutModule;
		class TraceModule;

		//////////////////////////////////////////////////////////////////////////////////////
		//
		//  Trace module
		//

		enum TraceChannels {

			// Generic trace
			TRC_ERROR		= 0x00000001,
			TRC_WARN		= 0x00000002,
			TRC_ASSERT		= 0x00000004,
			TRC_INFO		= 0x00000008,
		
			// Moudule additional traces
			TRC_USER1		= 0x00000020,
			TRC_USER2		= 0x00000040,
			TRC_USER3		= 0x00000080,
			TRC_USER4		= 0x00000100,
			TRC_USER5		= 0x00000200,
			TRC_USER6		= 0x00000400,
			TRC_USER7		= 0x00000800,
			TRC_USER8		= 0x00001000,
			TRC_USER9		= 0x00002000,
			TRC_USER10		= 0x00004000,
			TRC_USER11		= 0x00008000,
			TRC_USER12		= 0x00010000,
			TRC_USER13		= 0x00020000,
			TRC_USER14		= 0x00040000,
			TRC_USER15		= 0x00080000,
			TRC_USERMASK	= (TRC_USER1 | TRC_USER2 | TRC_USER3 | TRC_USER4 | TRC_USER5 | TRC_USER6 | TRC_USER7 | TRC_USER8 
								| TRC_USER9 | TRC_USER10 | TRC_USER11 | TRC_USER12 | TRC_USER13 | TRC_USER14 | TRC_USER15),

			// Debugging traces
			TRC_DBG1		= 0x00100000,
			TRC_DBG2		= 0x00200000,
			TRC_DBG3		= 0x00400000,
			TRC_DBG4		= 0x00800000,
			TRC_DBG5		= 0x01000000,
			TRC_DBG6		= 0x02000000,
			TRC_DBG7		= 0x04000000,
			TRC_DBG8		= 0x08000000,
			TRC_DBG9		= 0x10000000,
			TRC_DBG10		= 0x20000000,
			TRC_DBG11		= 0x40000000,
			TRC_DBG12		= 0x80000000,
			TRC_DBGMASK		= (TRC_DBG1 | TRC_DBG2 | TRC_DBG3 | TRC_DBG4 | TRC_DBG5 | TRC_DBG6 | TRC_DBG7 | TRC_DBG8 | TRC_DBG9 | TRC_DBG10 | TRC_DBG11 | TRC_DBG12),

			// Trace level default value
			TRC_DEFAULT		= (TRC_ERROR | TRC_WARN | TRC_ASSERT | TRC_INFO | TRC_USERMASK),

			TRC_GENERIC_ALL	= (TRC_ERROR | TRC_WARN | TRC_ASSERT | TRC_INFO | TRC_USERMASK ),
		};


		// Trace output option
		enum TraceOutput {

			// Generic trace
			TRCOUT_DEBUG	= 0x00000001,	// VS debug console
			TRCOUT_CONSOLE	= 0x00000002,	// Console write
			TRCOUT_EVENT	= 0x00000004,	// Event log
			TRCOUT_FILE1	= 0x00000100,	// Release Log file
			TRCOUT_FILE2	= 0x00000200,	// Debug log file( maybe include all )

			TRCOUT_FILE_ALL	= TRCOUT_FILE1|TRCOUT_FILE2,

			// Trace level default value
			TRCOUT_DEFAULT			= (TRCOUT_FILE1 | TRCOUT_CONSOLE),
			TRCOUT_DEFAULT_DEBUG	= (TRCOUT_FILE2 | TRCOUT_CONSOLE),
			TRCOUT_NONE		= 0,

			TRCOUT_FILE_LOG			= 0,	// Release Log file
			TRCOUT_FILE_DBGLOG		= 1,	// Debug log file( maybe include all )
			TRCOUT_NUMFILE = 2,
		};


	
	} // namespace Trace



} // namespace SF








/////////////////////////////////////////////////
//
// Error Jump Macros (Legacy gradually deprecated).
//
/////////////////////////////////////////////////


#ifdef TRACE_DBG

	#define TrcErrJmp(trcMod, errval, __var) \
	do {\
		__var = errval;\
		SFLog(trcMod, Error, "{0}({1}): {2}",     \
			__FILE__, __LINE__, hr ); \
		goto Proc_End;\
	} while(0);

	#define TrcErrReturn(trcMod, errval) \
	do {\
		SFLog(trcMod, Error, "{0}({1}): {2}",     \
			__FILE__, __LINE__, (SF::Result)errval ); \
		return errval;\
	} while(0);

// Basic check&branch routine
#define trcChk(checkState) \
	do{\
		hr = checkState;\
		if( !(hr) )\
		{\
			defTrace( Error, "{0}({1}): {2}", __FILE__, __LINE__, hr ); \
			goto Proc_End;\
		}\
	}while(0)\

#define trcErr(errVal) \
	do{\
		defTrace( Error, "{0}({1}): {2}", __FILE__, __LINE__, hr ); \
		hr = errVal;\
		goto Proc_End;\
	}while(0)\


#define trcMem(checkPointer) \
	do {\
		if( (checkPointer) == NULL )\
		{\
			defTrace( Error, "{0}({1}): Null Exception",     \
				__FILE__, __LINE__ ); \
			hr = ResultCode::OUT_OF_MEMORY;\
			goto Proc_End;\
		}\
	} while(0);\


#define trcChkPtr(checkPointer) \
	do{\
		if( (checkPointer) == NULL )\
		{\
			defTrace( Error, "{0}({1}): Invalid Pointer", __FILE__, __LINE__ ); \
			hr = ResultCode::INVALID_POINTER;\
			goto Proc_End;\
		}\
	}while(0);\


#define trcCheck(checkState) \
	do{\
		hr = checkState;\
		if( !(hr) )\
		{\
			defTrace( Error, "{0}({1}): {2}", __FILE__, __LINE__, hr ); \
			return hr;\
		}\
	}while(0)\

#define trcError(errVal) \
	do{\
		defTrace( Error, "{0}({1}): {2}", __FILE__, __LINE__, hr ); \
		hr = errVal;\
		return hr;\
	}while(0)\


#define trcCheckPtr(checkPointer) \
	do{\
		if( (checkPointer) == nullptr )\
		{\
			defTrace( Error, "{0}({1}): Invalid Pointer", __FILE__, __LINE__ ); \
			hr = ResultCode::INVALID_POINTER;\
			return hr;\
		}\
	}while(0);\

#define trcCheckMem(checkPointer) \
	do{\
		auto pResult = checkPointer;\
		if( pResult == nullptr )\
		{\
			defTrace( Error, "{0}({1}): Invalid Pointer", __FILE__, __LINE__ ); \
			hr = ResultCode::INVALID_POINTER;\
			return hr;\
		}\
	}while(0);\

#define trcCheckCondition(condi) \
				do{ \
					if( !(condi) ) {\
					defTrace( Factal, "{0}({1}): Assert occure : {2}", __FILE__, __LINE__, #condi );  SF::Service::LogModule->Flush();\
						return hr = ResultCode::UNEXPECTED;\
					}\
				}while(0) \


// Assert with expression
#define trcCheckConditionExp(condi,expr) \
				do{ \
					if( !(condi) ) {\
						defTrace( Factal, "{0}({1}): Assert occure : {2} : {3}", __FILE__, __LINE__, #condi, expr ); SF::Service::LogModule->Flush();\
						return hr = ResultCode::UNEXPECTED;\
					}\
				}while(0) \



#else
	#define TrcErrJmp(trcMod, errval, var) \
	do {\
		var = errval;\
		goto Proc_End;\
	} while(0);

	#define TrcErrReturn(trcMod, errval) \
	do {\
		return errval;\
	} while(0);

// Basic check&branch routine
#define trcChk(checkState) \
	do{\
		hr = checkState;\
		if( !(hr) )\
		{\
			goto Proc_End;\
		}\
	}while(0)\

#define trcErr(errVal) \
	do {\
		hr = errVal;\
		goto Proc_End;\
	} while(0);\


#define trcMem(checkPointer) \
	do{\
		if( (checkPointer) == NULL )\
		{\
			hr = ResultCode::OUT_OF_MEMORY;\
			goto Proc_End;\
		}\
	}while(0)\


#define trcChkPtr(checkPointer) \
	do{\
		if( (checkPointer) == NULL )\
		{\
			hr = ResultCode::INVALID_POINTER;\
			goto Proc_End;\
		}\
	}while(0)\




#endif // TRACE_DBG


// Assert
#define trcAssert(condi) \
				do{ \
					if( !(condi) ) {\
						CallStackTraceT<15> stackTrace; stackTrace.CaptureCallStack(); stackTrace.PrintStackTrace(CurrentProcessID);\
					defTrace( Factal, "{0}({1}): Assert occure : {2}", __FILE__, __LINE__, #condi );  SF::Service::LogModule->Flush();\
						trcCheck(ResultCode::UNEXPECTED);\
					}\
				}while(0) \


// Assert with expression
#define trcAssertExp(condi,expr) \
				do{ \
					if( !(condi) ) {\
						CallStackTraceT<15> stackTrace; stackTrace.CaptureCallStack(); stackTrace.PrintStackTrace(CurrentProcessID);\
						defTrace(Factal, "{0}({1}): Assert occure : {2} : {3}", __FILE__, __LINE__, #condi, expr ); SF::Service::LogModule->Flush();\
						trcCheck(ResultCode::UNEXPECTED);\
					}\
				}while(0) \


// Assert
#define TrcAssertReturn(condi) \
				do{ \
					if( !(condi) ) {\
						CallStackTraceT<15> stackTrace; stackTrace.CaptureCallStack(); stackTrace.PrintStackTrace(CurrentProcessID);\
					defTrace( Factal, "{0}({1}): Assert occure : {2}", __FILE__, __LINE__, #condi );  SF::Service::LogModule->Flush();\
						return ResultCode::UNEXPECTED;\
					}\
				}while(0) \


// Assert with expression
#define TrcAssertReturnExp(condi,expr) \
				do{ \
					if( !(condi) ) {\
						CallStackTraceT<15> stackTrace; stackTrace.CaptureCallStack(); stackTrace.PrintStackTrace(CurrentProcessID);\
						defTrace( Factal, "{0}({1}): Assert occure : {2} : {3}", __FILE__, __LINE__, #condi, expr ); SF::Service::LogModule->Flush();\
						return ResultCode::UNEXPECTED;\
					}\
				}while(0) \



// Basic check&branch routine
#define trcChkSilent(checkState) \
	do{\
	hr = checkState;\
	if( !(hr) )\
		{\
		goto Proc_End;\
		}\
	}while(0)\


#define trcErrSilent(errval)		\
	do {\
	hr = errval;\
	goto Proc_End;\
	} while(0);



// Assert even release mode
#define TrcAssertRel(condi) \
				do{ \
					if( !(condi) ) {\
						AssertRel(condi);\
						trcErr(ResultCode::UNEXPECTED);\
					}\
				} while(0)\






///////////////////////////////////////////////////////////////////////////////////
//
// Default trace module
//


#define defError(e)			trcError(e)
#define defCheck(e)			trcCheck(e)
#define defCheckError(ErrCode,exp)			{ do{ Result hRes = exp; if( !(hRes) ) TrcErrJmp(Svr,ErrCode,hr); } while(0); }
#define defCheckMem(a)			trcCheckMem(a)
#define defCheckPtr(a)			trcCheckMem(a)
#define defChkPtr(a)		trcChkPtr(a)


#define defErr(e)			trcErr(e)
#define defChk(e)			trcChk(e)
#define defChkErr(ErrCode,exp)			{ do{ Result hRes = exp; if( !(hRes) ) TrcErrJmp(Svr,ErrCode,hr); } while(0); }
#define defMem(a)			trcMem(a)
#define defChkPtr(a)		trcChkPtr(a)

#define defAssert(e)			trcAssert(e)
#define defAssertExp(e,expr)	trcAssertExp(e,expr)
#define defTrace(lModeMask, ...)				SFLog(System,lModeMask,__VA_ARGS__)

#define defChkSilent(e)		trcChkSilent(e)
#define defErrSilent(e)		trcErrSilent(e)




