////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : FixedString
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



	class FixedString
	{
	private:

		uint64_t m_Hash;

	public:
		constexpr FixedString()
			: m_Hash(0)
		{

		}

		constexpr FixedString(uint64_t hash)
			: m_Hash(hash)
		{

		}

		constexpr FixedString(const char* text)
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

		constexpr bool operator == (const FixedString& op) const { return m_Hash == op.m_Hash; }
		constexpr bool operator != (const FixedString& op) const { return m_Hash != op.m_Hash; }

		const char* ToString() const;
	};

}

