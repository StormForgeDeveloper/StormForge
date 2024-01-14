////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StringCrc64
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include <stdint.h>
#include <assert.h>
#include <fstream>
#include <algorithm>

#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFStringCrcDB.h"
#include "Service/SFService.h"


namespace SF
{
	// todo: move to preprocessing
	StringCrc32::StringCrc32(const char* text)
		: m_Crc(StringCrcDB::Get().AddNGetString32(text))
	{}

	const char* StringCrc32::ToString() const
	{
		auto pStr = StringCrcDB::Get().GetString(m_Crc);
		if (pStr != nullptr)
			return pStr;
		else
		{
			static char strBuffer[16]{};
			ToStringContext context{};
			context.Radix = 16;
			context.MaxDigit = 0;
			context.OutStream.pBuffer = strBuffer;
			context.OutStream.BuffLen = (int)countof(strBuffer);
			_IToA(context, (uint32_t)m_Crc);
			return strBuffer;
		}
	}


	const char* StringCrc64::ToString() const
	{
		auto pStr = Service::StringDB->GetString(m_Hash);
		if (pStr != nullptr)
			return pStr;
		else
		{
			static char strBuffer[32]{};
			ToStringContext context{};
			context.Radix = 16;
			context.MaxDigit = 0;
			context.OutStream.pBuffer = strBuffer;
			context.OutStream.BuffLen = (int)countof(strBuffer);
			_IToA(context, (uint64_t)m_Hash);
			return strBuffer;
		}
	}
}
