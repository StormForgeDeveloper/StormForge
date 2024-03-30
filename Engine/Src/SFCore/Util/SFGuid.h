////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Guid - RFC4122
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

namespace SF {

    // UUID binary form is defined with big endian system, and this also affects string representation.
    // 4 bytes + 2 bytes + 2 bytes + 2 bytes + 8 X 1 bytes
    // https://www.rfc-editor.org/rfc/rfc4122
    // Guid RFC-4122
    class SF_DECLARE_ALIGN_DOUBLE Guid
    {
    public:

        static const Guid Empty;

        Guid()
        {
            __m128i x = _mm_setzero_si128 ();
            _mm_storeu_si128((__m128i*)data, x);
        }

        Guid(const Guid& other)
        {
            __m128i x = _mm_loadu_si128((__m128i*)other.data);
            _mm_storeu_si128((__m128i*)data, x);
        }

        /* Builds a 128-bits Guid */
        Guid(__m128i uuid)
        {
            // No boundary limit unlike _mm_store_si128
            _mm_storeu_si128((__m128i*)data, uuid);
        }

        Guid(uint64_t x, uint64_t y)
        {
            memcpy(data, &x, sizeof(x));
            memcpy(data + 8, &y, sizeof(x));
        }

        bool IsValid() const
        {
            auto* dwordData = reinterpret_cast<const uint32_t*>(data);
            return (dwordData[0] | dwordData[1] | dwordData[2] | dwordData[3]) != 0;
        }

        void Reset()
        {
            memset(data, 0, sizeof(data));
        }

        //uint64_t Low() const { return *((uint64_t*)data); }
        //uint64_t High() const { return *((uint64_t*)data + 8); }
        uint64_t ToUInt64() const
        {
            return *((uint64_t*)data);
        }

        // Parse string with some format detection logic.
        // The implementation has some faulty cases. use particular implementation if you knows the input string format
        static bool TryParseGeneric(const char* str, Guid& outGuid);
        // Parse RFC string ex)"12345678-90ab-cdef-1234-1234567890ab"
        static bool TryParseRFC(const char* str, Guid& outGuid);
        // Parse short form string ex)"1234567890abcdef12341234567890ab"
        static bool TryParse32(const char* str, Guid& outGuid);
        // Parse 64bit unsigned integer string and fills from high portion
        //  ex) "1311768467294899695" => 0x1234567890abcdef => "00000000-0000-0000-1234-567890abcdef"
        static bool TryParseUInt64(const char* str, Guid& outGuid);
        static bool TryParseHexUInt64(const char* str, Guid& outGuid);

        static Guid ParseGeneric(const char* str);

        // From bytes array
        static Guid FromBytes(const uint8_t* bytes);

        // Make a Guid from uint64_t
        static Guid FromUInt64(uint64_t value);

        Guid& operator=(const Guid& other)
        {
            if (&other == this)
            {
                return *this;
            }

            __m128i x = _mm_loadu_si128 ((__m128i*)other.data);
            _mm_storeu_si128((__m128i*)data, x);

            return *this;
        }

        friend bool operator==(const Guid& lhs, const Guid& rhs)
        {
            __m128i x = _mm_loadu_si128 ((__m128i*)lhs.data);
            __m128i y = _mm_loadu_si128 ((__m128i*)rhs.data);

            __m128i neq = _mm_xor_si128(x, y);
            return _mm_test_all_zeros(neq, neq);
        }

        friend bool operator<(const Guid& lhs, const Guid& rhs)
        {
            // There are no trivial 128-bits comparisons in SSE/AVX
            // It's faster to compare two uint64_t
            uint64_t* x = (uint64_t*)lhs.data;
            uint64_t* y = (uint64_t*)rhs.data;
            return *x < *y || (*x == *y && *(x + 1) < *(y + 1));
        }

        friend bool operator!=(const Guid& lhs, const Guid& rhs) { return !(lhs == rhs); }
        friend bool operator> (const Guid& lhs, const Guid& rhs) { return rhs < lhs; }
        friend bool operator<=(const Guid& lhs, const Guid& rhs) { return !(lhs > rhs); }
        friend bool operator>=(const Guid& lhs, const Guid& rhs) { return !(lhs < rhs); }

        std::string ToString() const
        {
            std::string mem;
            mem.resize(36);
            ToString(mem.data());
            return mem;
        }


        void ToString(char* strBuff) const;

        size_t ToString(char* strBuff, size_t bufferSize) const
        {
            if (bufferSize <= 32)
                return 0;

            ToString(strBuff);

            return 32;
        }

        size_t GetHash() const
        {
            return *((uint64_t*)data) ^ *((uint64_t*)data + 8);
        }

        uint8_t data[16];
    };


} // SF
