////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Crc32 calculation based
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "String/SFHasher32C.h"



namespace SF {


	constexpr uint32_t Hasher_Crc32C::stm_CrcTable[];



	uint32_t Crc32C(const char* s)
	{
		if (s == nullptr)
			return 0;

		uint32_t crc = 0xffffffff;
		while ((*s) != '\0')
		{
			crc = (crc >> 8) ^ Hasher_Crc32C::stm_CrcTable[(crc ^ (*s++)) & 0xFF];
		}
		return crc ^ 0xffffffff;
	}

	uint32_t Crc32C(const uint8_t *buf, size_t len)
	{
		if (len == 0)
			return 0;

		uint32_t crc = 0xffffffff;
		while (len-- > 0) 
		{
			crc = (crc >> 8) ^ Hasher_Crc32C::stm_CrcTable[(crc ^ (*buf++)) & 0xFF];
		}
		return crc ^ 0xffffffff;
	}


namespace Util {
	


	// TODO: intrinsic version and Crypto

}
} // namespace SF

