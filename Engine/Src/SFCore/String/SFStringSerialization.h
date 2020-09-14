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

	template<>
	inline Result IInputStream::Read(String& data)
	{
		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		if (NumChar == 0)
		{
			data.Resize(0);
			return ResultCode::SUCCESS;
		}

		data.Resize(NumChar - 1);

		return Read(data.data(), NumChar * sizeof(char));
	}

	template<>
	inline Result IInputStream::Read(StringW& data)
	{
		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		if (NumChar == 0)
		{
			data.Resize(0);
			return ResultCode::SUCCESS;
		}

		data.Resize(NumChar - 1);

		return Read(data.data(), NumChar * sizeof(wchar_t));
	}




	template<>
	inline Result IOutputStream::Write(const CharPtr& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(StrUtil::StringLen(data) + 1);
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;


		if (data)
		{
			return Write(data, NumChar * sizeof(char));
		}
		else
		{
			return Write(char{});
		}

		return ResultCode::SUCCESS;
	}

	template<>
	inline Result IOutputStream::Write(const WCharPtr& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(StrUtil::StringLen(data) + 1);
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		if (data)
		{
			return Write(data, NumChar * sizeof(wchar_t));
		}
		else
		{
			return Write(wchar_t{});
		}

		return ResultCode::SUCCESS;
	}

	template<>
	inline Result IOutputStream::Write(const String& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(data.size() + 1);
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		if (data.data())
			return Write(data.data(), NumChar * sizeof(char));
		else
		{
			return Write(char{});
		}
	}

	template<>
	inline Result IOutputStream::Write(const StringW& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(data.size() + 1);
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		if (data.data())
			return Write(data.data(), NumChar * sizeof(wchar_t));
		else
		{
			return Write(wchar_t{});
		}
	}


} // namespace SF


