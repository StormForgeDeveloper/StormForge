////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SFStream
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Stream/SFStream.h"
#include "Util/SFString.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "SFResult.h"


namespace SF {


	/////////////////////////////////////////////////////////////////////////////
	//
	//	IInputStream
	//

	Result IInputStream::Read(String& data)
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

	Result IInputStream::Read(WString& data)
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

	Result IInputStream::Read(std::string& data)
	{
		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		if (NumChar == 0)
		{
			data.resize(0);
			return ResultCode::SUCCESS;
		}

		data.resize(NumChar - 1);

		return Read(data.data(), NumChar * sizeof(char));
	}

	Result IInputStream::Read(std::wstring& data)
	{
		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		if (NumChar == 0)
		{
			data.resize(0);
			return ResultCode::SUCCESS;
		}

		data.resize(NumChar - 1);

		return Read(data.data(), NumChar * sizeof(wchar_t));
	}

	Result IInputStream::Read(char*& data)
	{
		if (data != nullptr)
			IHeap::Delete(data);
		data = nullptr;

		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		if (NumChar == 0)
		{
			data = nullptr;
			return ResultCode::SUCCESS;
		}

		data = new char[NumChar - 1];

		return Read(data, NumChar * sizeof(char));
	}

	Result IInputStream::Read(wchar_t*& data)
	{
		if (data != nullptr)
			IHeap::Delete(data);
		data = nullptr;

		uint16_t NumChar = 0;
		if (!Read(&NumChar, sizeof(NumChar)))
			return ResultCode::END_OF_STREAM;

		if (NumChar == 0)
		{
			return ResultCode::SUCCESS;
		}

		data = new wchar_t[NumChar - 1];

		return Read(data, NumChar * sizeof(wchar_t));
	}




	/////////////////////////////////////////////////////////////////////////////
	//
	//	IOutputStream
	//


	Result IOutputStream::Write(const char* data)
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

	Result IOutputStream::Write(const wchar_t* data)
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

	Result IOutputStream::Write(const String& data)
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

	Result IOutputStream::Write(const WString& data)
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

	Result IOutputStream::Write(const std::string& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(data.length() + 1);
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		if (data.data())
			return Write(data.data(), NumChar * sizeof(char));
		else
		{
			return Write(char{});
		}
	}

	Result IOutputStream::Write(const std::wstring& data)
	{
		uint16_t NumChar = static_cast<uint16_t>(data.length() + 1);
		if (!Write(&NumChar, sizeof(NumChar)))
			return ResultCode::OUT_OF_RESERVED_MEMORY;

		if (data.data())
			return Write(data.data(), NumChar * sizeof(wchar_t));
		else
		{
			return Write(wchar_t{});
		}
	}



}

