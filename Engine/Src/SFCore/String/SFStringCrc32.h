////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StringCrc32
//
////////////////////////////////////////////////////////////////////////////////

#pragma  once

#include <stdint.h>
#include "SFHasher32C.h"


namespace SF
{

	class StringCrc32
	{
	private:

		uint32_t m_Crc;

	public:
		constexpr StringCrc32()
			: m_Crc(0)
		{

		}

		constexpr StringCrc32(uint32_t stringCrc)
			: m_Crc(stringCrc)
		{

		}

		StringCrc32(const char* text)
			: m_Crc(Hasher_Crc32C().Hash(text))
		{

		}

		constexpr uint32_t GetHash() const
		{
			return m_Crc;
		}

		constexpr operator uint32_t() const
		{
			return m_Crc;
		}

		explicit operator const char*() const
		{
			return ToString();
		}

		constexpr bool operator == (const StringCrc32& op) const { return m_Crc == op.m_Crc; }
		constexpr bool operator != (const StringCrc32& op) const { return m_Crc != op.m_Crc; }

		constexpr bool operator == (const uint32_t op) const { return m_Crc == op; }
		constexpr bool operator != (const uint32_t op) const { return m_Crc != op; }

		const char* ToString() const;
	};

}
