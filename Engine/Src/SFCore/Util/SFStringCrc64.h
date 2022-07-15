////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StringCrc64
//
////////////////////////////////////////////////////////////////////////////////


#pragma  once

#include <stdint.h>
#include "SFHasher64.h"

// MSVC compiler generates warning 4307 with constexpr functions which can't be avoided
#ifdef _MSC_VER
#pragma warning(disable : 4307)
#endif

namespace SF {



	class StringCrc64
	{
	private:

		uint64_t m_Hash;

	public:
		constexpr StringCrc64()
			: m_Hash(0)
		{

		}

		constexpr StringCrc64(uint64_t hash)
			: m_Hash(hash)
		{

		}

		constexpr StringCrc64(const char* text)
			: m_Hash(Hasher_Murmur64().Hash(text))
		{

		}

		constexpr uint64_t GetHash() const
		{
			return m_Hash;
		}

		constexpr operator uint64_t() const
		{
			return m_Hash;
		}

		explicit operator const char*() const
		{
			return ToString();
		}

		constexpr bool operator == (const StringCrc64& op) const { return m_Hash == op.m_Hash; }
		constexpr bool operator != (const StringCrc64& op) const { return m_Hash != op.m_Hash; }

		constexpr bool operator == (const uint64_t op) const { return m_Hash == op; }
		constexpr bool operator != (const uint64_t op) const { return m_Hash != op; }

		const char* ToString() const;
	};



    constexpr StringCrc64 operator "" _crc64(const char* s, size_t sz) {
        return Hasher_Murmur64().Hash(0, s, sz);
    }

}

