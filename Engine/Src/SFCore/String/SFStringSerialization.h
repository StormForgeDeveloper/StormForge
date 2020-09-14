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
	//	String stream io util
	//

	template<>
	inline Result IInputStream::Read(String& data)
	{
		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		data.Resize(NumChar);

		return Read(data.data(), NumChar * sizeof(char));
	}

	template<>
	inline Result IInputStream::Read(StringW& data)
	{
		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		data.Resize(NumChar);

		return Read(data.data(), NumChar * sizeof(wchar_t));
	}



	template<>
	inline Result IOutputStream::Write(const String& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(data.size());
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		return Write(data.data(), NumChar * sizeof(char));
	}

	template<>
	inline Result IOutputStream::Write(const StringW& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(data.size());
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		return Write(data.data(), NumChar * sizeof(wchar_t));
	}


} // namespace SF


