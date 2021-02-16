////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : string
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFString.h"


namespace SF {

	class StringCrc64;
	class VariableBox;


	// Format string
	template<typename CharType, typename SharedStringBufferType>
	template< class ...ArgTypes >
	typename TString<CharType, SharedStringBufferType>::StringType& TString<CharType, SharedStringBufferType>::Format(const CharType* strFormat, ArgTypes... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		Format_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}

	// Format string
	template<typename CharType, typename SharedStringBufferType>
	template< class ...ArgTypes >
	typename TString<CharType, SharedStringBufferType>::StringType& TString<CharType, SharedStringBufferType>::AppendFormat(const CharType* strFormat, ArgTypes... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}


	template< class ...ArgTypes >
	inline StringBuilder& StringBuilder::AppendFormat(const CharType* strFormat, ArgTypes... args)
	{
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}

}; // namespace SF


