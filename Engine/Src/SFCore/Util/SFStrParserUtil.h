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
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {
namespace StrUtil {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	String parsing helper
	//

	// Pass all white spaces(space or tab) and return first non white space pointer of the input string
	const char* SkipWhiteSpace(const char* str, bool newLineIsWhiteSpace = true);
	char* SkipWhiteSpace(char* str, bool newLineIsWhiteSpace = true);

	// Pass all non - white spaces, and return first white space pointer of the input string
	const char* NextWhiteSpace(const char* str, bool newLineIsWhiteSpace = true);
	char* NextWhiteSpace(char* str, bool newLineIsWhiteSpace = true);


} // namespace StrUtil
} // namespace SF


