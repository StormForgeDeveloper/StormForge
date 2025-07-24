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

#if SF_USE_STD_STRING


    inline size_t Format(char* szBuffer, INT& BuffLen, const char* strFormat)
    {
        int prevBuffLen = BuffLen;

        StrUtil::StringCopyEx(szBuffer, BuffLen, strFormat);

        return prevBuffLen - BuffLen;
    }

    template<int BuffLen, class ...ArgTypes>
    inline size_t Format(char(&szBuffer)[BuffLen], const char* strFormat, const ArgTypes&... args)
    {
        std::string ss;

        std::vformat_to(std::back_inserter(ss), std::basic_string_view<char>(strFormat), std::make_format_args(args...));

        if (ss.length() > 0)
        {
            StrUtil::StringCopy(szBuffer, ss.c_str());
        }

        return ss.length();
    }

    template< class ...ArgTypes >
    inline size_t Format(char* szBuffer, INT& BuffLen, const char* strFormat, const ArgTypes&... args)
    {
        std::string ss;

        std::vformat_to(std::back_inserter(ss), std::basic_string_view<char>(strFormat), std::make_format_args(args...));

        if (ss.length() > 0)
        {
            StrUtil::StringCopyEx(szBuffer, BuffLen, ss.c_str());
        }

        return ss.length();
    }

#else // SF_USE_STD_STRING

	// 
	inline size_t Format( char* szBuffer, INT& BuffLen, const char* strFormat )
	{
		return Format_Internal(szBuffer, BuffLen, strFormat, 0, nullptr);
	}

	// 
	template< class ...ArgTypes >
	inline size_t Format(char* szBuffer, INT& BuffLen, const char* strFormat, const ArgTypes&... args)
	{
		StaticMemoryAllocatorT<2048> Allocator("TempStatic", GetSystemHeap());
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		return Format_Internal(szBuffer, BuffLen, strFormat, sizeof...(args), arguments);
	}

	// 
	template< int BuffLen >
	inline size_t Format(char(&szBuffer)[BuffLen], const char* strFormat)
	{
		char* pTempBuff = szBuffer;
		INT BuffReamin = BuffLen ;
		return Format_Internal(pTempBuff, BuffReamin, strFormat, 0, nullptr);
	}

	template< int BuffLen, class ...ArgTypes >
	inline size_t Format(char(&szBuffer)[BuffLen], const char* strFormat, const ArgTypes&... args)
	{
		StaticMemoryAllocatorT<2048> Allocator("TempStatic", GetSystemHeap());
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };

		char* pTempBuff = szBuffer;
		INT BuffReamin = BuffLen;
		return Format_Internal(pTempBuff, BuffReamin, strFormat, sizeof...(args), arguments);
	}

#endif // SF_USE_STD_STRING

} // namespace StrUtil
} // namespace SF


