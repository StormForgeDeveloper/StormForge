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

#include "Util/SFGuid.h"

#include "Stream/SFStream.h"
#include "Container/SFIndexing.h"
#include "Variable/SFVariableBoxing.h"

    // hash support
template <> class std::hash<SF::Guid>
{
public:
    size_t operator()(const SF::Guid& guid) const
    {
        return guid.GetHash();
    }
};

namespace SF {



    // serialization support
    inline size_t SerializedSizeOf(const Guid& Value) { return sizeof(Value); }
    inline Result operator >> (IInputStream& input, Guid& data) { return input.Read(&data, sizeof(data)); }
    inline Result operator << (IOutputStream& output, const Guid& data) { return output.Write(&data, sizeof(data)); }

    DECLARE_BOXING_TEMPLETE_BYVALUE(Guid);

    Result _ToString(ToStringContext& context, const Guid& value);


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
