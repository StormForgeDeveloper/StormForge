////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Guid - RFC4122
//              Based on https://github.com/crashoz/uuid_v4
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

namespace SF {


    // Guid RFC-4122
    class SF_DECLARE_ALIGN_DOUBLE Guid
    {
    public:
        Guid()
        {}

        Guid(const Guid& other)
        {
            __m128i x = _mm_loadu_si128 ((__m128i*)other.data);
            _mm_store_si128((__m128i*)data, x);
        }

        /* Builds a 128-bits Guid */
        Guid(__m128i uuid)
        {
            _mm_store_si128((__m128i*)data, uuid);
        }

        Guid(uint64_t x, uint64_t y)
        {
            __m128i z = _mm_set_epi64x(x, y);
            _mm_store_si128((__m128i*)data, z);
        }

        Guid(const uint8_t* bytes)
        {
            __m128i x = _mm_loadu_si128((__m128i*)bytes);
            _mm_store_si128((__m128i*)data, x);
        }

        bool IsValid() const
        {
            auto* dwordData = reinterpret_cast<const uint32_t*>(data);
            return (dwordData[0] | dwordData[1] | dwordData[2] | dwordData[3]) != 0;
        }

        uint64_t Low() const { return *((uint64_t*)data); }
        uint64_t High() const { return *((uint64_t*)data + 8); }

        /* Static factory to parse an Guid from its string representation */
        static Guid Parse(const char* str)
        {
            return Guid(stom128i(str));
        }

        Guid& operator=(const Guid& other)
        {
            if (&other == this)
            {
                return *this;
            }
            __m128i x = _mm_loadu_si128 ((__m128i*)other.data);
            _mm_store_si128((__m128i*)data, x);
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


        void ToString(char* strBuff) const
        {
            __m128i x = _mm_loadu_si128((__m128i*)data);
            m128itos(x, strBuff);
        }

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

        static void m128itos(__m128i x, char* mem);
        static __m128i stom128i(const char* mem);

        uint8_t data[16]{};
    };


} // SF
