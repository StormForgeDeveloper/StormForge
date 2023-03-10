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
#include "Stream/SFStream.h"
#include "Container/SFIndexing.h"
#include <random>
//#include <string>
//#include <limits>
//#include <iostream>
//#include <sstream>
//#include <cstdint>
//#include <memory>
//
//#include <emmintrin.h>
//#include <smmintrin.h>
//#include <immintrin.h>

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

        size_t GetHash() const
        {
            return *((uint64_t*)data) ^ *((uint64_t*)data + 8);
        }

        static void m128itos(__m128i x, char* mem);
        static __m128i stom128i(const char* mem);

        uint8_t data[16]{};
    };


    // hash support
    template <> class hash<SF::Guid>
    {
        size_t operator()(const SF::Guid& guid) const
        {
            return guid.GetHash();
        }
    };

    inline size_t SerializedSizeOf(const Guid& Value) { return sizeof(Value); }
    inline Result operator >> (IInputStream& input, Guid& data) { return input.Read(&data, sizeof(data)); }
    inline Result operator << (IOutputStream& output, const Guid& data) { return output.Write(&data, sizeof(data)); }



    /*
      Generates Guid from a provided random generator (c++11 <random> module)
      std::mt19937_64 is highly recommended as it has a SIMD implementation that
      makes it very fast and it produces high quality randomness.
     */
    template <typename RNG = std::mt19937_64>
    class GuidGenerator {
    public:
        GuidGenerator()
            : m_RandGen(new RNG(std::random_device()()))
            , m_Distribution(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max())
        {}

        GuidGenerator(uint64_t seed)
            : m_RandGen(new RNG(seed))
            , m_Distribution(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max())
        {}

        GuidGenerator(RNG& gen)
            : m_RandGen(gen)
            , m_Distribution(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max())
        {}

        /* Generates a new Guid */
        Guid NewGuid()
        {
            // The two masks set the uuid version (4) and variant (1)
            const __m128i and_mask = _mm_set_epi64x(0xFFFFFFFFFFFFFF3Full, 0xFF0FFFFFFFFFFFFFull);
            const __m128i or_mask = _mm_set_epi64x(0x0000000000000080ull, 0x0040000000000000ull);
            __m128i n = _mm_set_epi64x(m_Distribution(*m_RandGen), m_Distribution(*m_RandGen));
            __m128i uuid = _mm_or_si128(_mm_and_si128(n, and_mask), or_mask);

            return Guid(uuid);
        }

    private:
        std::shared_ptr<RNG> m_RandGen;
        std::uniform_int_distribution<uint64_t> m_Distribution;
    };


} // SF
