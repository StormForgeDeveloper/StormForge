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

#include "String/SFStringCrc32.h"
#include "String/SFStringCrc64.h"
#include "String/SFStringCrcDB.h"
#include "Service/SFService.h"


namespace SF
{

	const char* StringCrc32::ToString() const
	{
		return Service::StringDB->GetString(m_Crc);
	}


	const char* StringCrc64::ToString() const
	{
		return Service::StringDB->GetString(m_Hash);
	}
}