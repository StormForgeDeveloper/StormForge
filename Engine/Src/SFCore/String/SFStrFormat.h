////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String Format utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Variable/SFVariableBoxing.h"


namespace SF {
namespace StrUtil {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	String formating helper
	//

	// Format string with argument list
	// Modified buffer pointer and remain buffer size returned to original parameter
	// return used or required string buffer length
	size_t Format_Internal( char*& szBuffer, int& BuffLen, const char* szFormating, int iNumArg, VariableBox* Args );


	// 
	inline size_t Format( char* szBuffer, INT& BuffLen, const char* strFormat )
	{
		return Format_Internal(szBuffer, BuffLen, strFormat, 0, nullptr);
	}

	// 
	template< class ...ArgTypes >
		inline size_t Format(char* szBuffer, INT& BuffLen, const char* strFormat, const ArgTypes&... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		return Format_Internal(szBuffer, BuffLen, strFormat, sizeof...(args), arguments);
	}

	// 
	template< int BuffLen >
	size_t Format(char(&szBuffer)[BuffLen], const char* strFormat)
	{
		char* pTempBuff = szBuffer;
		INT BuffReamin = BuffLen ;
		return Format_Internal(pTempBuff, BuffReamin, strFormat, 0, nullptr);
	}

	template< int BuffLen, class ...ArgTypes >
	size_t Format(char(&szBuffer)[BuffLen], const char* strFormat, const ArgTypes&... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };

		char* pTempBuff = szBuffer;
		INT BuffReamin = BuffLen;
		return Format_Internal(pTempBuff, BuffReamin, strFormat, sizeof...(args), arguments);
	}


}; // namespace StrUtil
} // namespace SF


