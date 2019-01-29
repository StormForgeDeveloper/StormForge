////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : FixedString
//
////////////////////////////////////////////////////////////////////////////////

#include "CoreBasePCH.h"
#include <stdint.h>
#include <assert.h>
#include <fstream>
#include <algorithm>

#include "String/SFFixedString32.h"
#include "String/SFFixedString.h"
#include "String/SFFixedStringDB.h"
#include "Service/SFService.h"


namespace SF
{
	constexpr uint32_t Hasher_Crc32::stm_CRC32Table[8][256];

	const char* FixedString32::ToString() const
	{
		return Service::StringDB->GetString(m_Crc);
	}


	const char* FixedString::ToString() const
	{
		return Service::StringDB->GetString(m_Hash);
	}
}