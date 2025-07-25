////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "MemoryManager/SFHeapMemory.h"

namespace SF {

	class StringCrc64;
	class VariableBox;

#if !SF_USE_STD_STRING

	// Format string
	template<typename CharType, typename SharedStringBufferType>
	template< class ...ArgTypes >
	inline typename TString<CharType, SharedStringBufferType>::StringType& TString<CharType, SharedStringBufferType>::Format(const CharType* strFormat, ArgTypes... args)
	{
		StaticMemoryAllocatorT<2048> Allocator("TempStatic", GetSystemHeap());
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		Format_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}

	// Format string
	template<typename CharType, typename SharedStringBufferType>
	template< class ...ArgTypes >
	inline typename TString<CharType, SharedStringBufferType>::StringType& TString<CharType, SharedStringBufferType>::AppendFormat(const CharType* strFormat, ArgTypes... args)
	{
		StaticMemoryAllocatorT<2048> Allocator("TempStatic", GetSystemHeap());
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}


	template< class ...ArgTypes >
	inline StringBuilder& StringBuilder::AppendFormat(const CharType* strFormat, ArgTypes... args)
	{
		StaticMemoryAllocatorT<2048> Allocator("TempStatic", GetSystemHeap());
		VariableBox arguments[sizeof...(args)] = { Boxing(args)... };
		AppendFormat_Internal(strFormat, sizeof...(args), arguments);
		return *this;
	}
#endif // !SF_USE_STD_STRING

}; // namespace SF


