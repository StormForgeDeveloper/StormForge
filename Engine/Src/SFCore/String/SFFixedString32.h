////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : FixedString32
//
////////////////////////////////////////////////////////////////////////////////

#pragma  once

#include <stdint.h>
#include "SFHasher32C.h"


namespace SF
{

	class FixedString32
	{
	private:

		uint32_t m_Crc;

	public:
		constexpr FixedString32()
			: m_Crc(0)
		{

		}

		constexpr FixedString32(uint32_t stringCrc)
			: m_Crc(stringCrc)
		{

		}

		FixedString32(const char* text)
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

		constexpr bool operator == (const FixedString32& op) const { return m_Crc == op.m_Crc; }
		constexpr bool operator != (const FixedString32& op) const { return m_Crc != op.m_Crc; }

		const char* ToString() const;
	};

}
