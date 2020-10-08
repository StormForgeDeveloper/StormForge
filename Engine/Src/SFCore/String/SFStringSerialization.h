////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String Serialization
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "String/SFString.h"
#include "Stream/SFStream.h"

namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	String serialization size calculations
	//


	template<>
	inline size_t SerializedSizeOf(const CharPtr& Value) { return sizeof(uint16_t) + (StrUtil::StringLen(Value) + 1) * sizeof(char); }

	template<>
	inline size_t SerializedSizeOf(const WCharPtr& Value) { return sizeof(uint16_t) + (StrUtil::StringLen(Value) + 1) * sizeof(wchar_t); }

	template<>
	inline size_t SerializedSizeOf(const String& Value) { return sizeof(uint16_t) + (Value.GetLength() + 1) * sizeof(char); }

	template<>
	inline size_t SerializedSizeOf(const StringW& Value) { return sizeof(uint16_t) + (Value.GetLength() + 1) * sizeof(wchar_t); }



	////////////////////////////////////////////////////////////////////////////////
	//
	//	String stream io util
	//




} // namespace SF


