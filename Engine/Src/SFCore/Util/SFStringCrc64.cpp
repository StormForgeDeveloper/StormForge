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
		: m_Crc(Service::StringDB->AddNGetString32(text))
	{
	}

	const char* StringCrc32::ToString() const
	{
		return Service::StringDB->GetString(m_Crc);
	}


	const char* StringCrc64::ToString() const
	{
		return Service::StringDB->GetString(m_Hash);
	}
}