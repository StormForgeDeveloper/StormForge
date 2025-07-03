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
#include "Container/SFIndexing.h"

namespace SF
{

	class StringCrc32
	{
	private:

		uint32_t m_Crc;

	public:
		constexpr StringCrc32()
			: m_Crc(0)
		{}

		constexpr StringCrc32(uint32_t stringCrc)
			: m_Crc(stringCrc)
		{}

		StringCrc32(const char* text);

		constexpr uint32_t GetHash() const { return m_Crc; }

		constexpr operator uint32_t() const { return m_Crc; }

		explicit operator const char*() const { return ToString(); }

		constexpr bool operator == (const StringCrc32& op) const { return m_Crc == op.m_Crc; }
		constexpr bool operator != (const StringCrc32& op) const { return m_Crc != op.m_Crc; }

		constexpr bool operator == (const uint32_t op) const { return m_Crc == op; }
		constexpr bool operator != (const uint32_t op) const { return m_Crc != op; }

		const char* ToString() const;
	};


    constexpr StringCrc32 operator "" _crc(const char* s, size_t sz) {
        return Hasher_Crc32C::Hash(s);
    }

    constexpr StringCrc32 operator "" _crc32c(const char* s, size_t sz) {
        return Hasher_Crc32C::Hash(s);
    }


    template<>
    class hash<StringCrc32>
    {
    public:
        typedef StringCrc32 KeyType;

        size_t operator()(const KeyType& _Keyval) const
        {
            return _Keyval.GetHash();
        }
    };

}

namespace std
{
    template<>
    class hash<SF::StringCrc32>
    {
    public:
        typedef SF::StringCrc32 KeyType;

        size_t operator()(const KeyType& _Keyval) const
        {
            return _Keyval.GetHash();
        }
    };

}
