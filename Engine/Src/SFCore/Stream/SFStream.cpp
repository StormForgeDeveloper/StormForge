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
#include "String/SFString.h"
#include "String/SFStringCrc32.h"
#include "String/SFStringCrc64.h"
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

	Result IInputStream::Read(StringW& data)
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
			delete[] data;
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
			delete[] data;
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


	//Result IInputStream::Read(Result& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(StringCrc32& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(StringCrc64& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(NetAddress& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(NetClass& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(DurationMS& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(DurationSec& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(sockaddr_in6& data) { return Read(&data, sizeof(data)); }
	//Result IInputStream::Read(sockaddr_storage& data) { return Read(&data, sizeof(data)); }




	/////////////////////////////////////////////////////////////////////////////
	//
	//	IOutputStream
	//


	Result IOutputStream::Write(const CharPtr& data)
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

	Result IOutputStream::Write(const WCharPtr& data)
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

	Result IOutputStream::Write(const StringW& data)
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


	//Result IOutputStream::Write(const DurationMS& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const DurationSec& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const sockaddr_in6& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const sockaddr_storage& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const Result& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const StringCrc32& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const StringCrc64& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const NetClass& data) { return Write(&data, sizeof(data)); }
	//Result IOutputStream::Write(const NetAddress& data) { return Write(&data, sizeof(data)); }



}

