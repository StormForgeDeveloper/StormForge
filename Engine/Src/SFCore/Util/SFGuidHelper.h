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


    Result _ToString(ToStringContext& context, const Guid& value);


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // GuidVariable
    /////////////////////////////////////////////////////////////////////////////////////////////////
    class VariableGuid : public Variable
    {
    public:

        static constexpr StringCrc32 TYPE_NAME = "Guid"_crc32c;

    private:
        Guid m_Value;

    public:
        VariableGuid()
        {
        }

        VariableGuid(const Guid& value)
            : m_Value(value)
        {
        }

        virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

        virtual void SetValue(bool value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(int8_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(uint8_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(int16_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(uint16_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(int32_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(uint32_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(int64_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(uint64_t value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(float value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(double value) override { m_Value = Guid::FromUInt64((uint64_t)value); }
        virtual void SetValue(const char* value) override { Guid::TryParseRFC(value, m_Value); }
        virtual void SetValue(const String& value) override { Guid::TryParseRFC(value, m_Value); }
        virtual void SetValue(StringCrc64 value) override { Guid::FromUInt64(value); }
        virtual void SetValue(const Guid& value) override { m_Value = value; }

        virtual void* GetDataPtr() const override { return (void*)m_Value.data; }
        virtual bool GetValueBool() const override { return m_Value.IsValid(); }
        virtual int8_t GetValueInt8() const override { return (int8_t)m_Value.ToUInt64(); }
        virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value.ToUInt64(); }
        virtual int16_t GetValueInt16() const override { return (int16_t)m_Value.ToUInt64(); }
        virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value.ToUInt64(); }
        virtual int32_t GetValueInt32() const override { return (int32_t)m_Value.ToUInt64(); }
        virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value.ToUInt64(); }
        virtual int64_t GetValueInt64() const override { return (int64_t)m_Value.ToUInt64(); }
        virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value.ToUInt64(); }
        virtual float GetValueFloat() const override { return (float)m_Value.ToUInt64(); }
        virtual double GetValueDouble() const override { return (double)m_Value.ToUInt64(); }
        virtual const char* GetValueCharString() const override { assert(false); return nullptr; }
        virtual StringCrc32 GetValueStringCrc32() const override { return (uint32_t)m_Value.ToUInt64(); }
        virtual StringCrc64 GetValueStringCrc64() const override { return (uint64_t)m_Value.ToUInt64(); }
        virtual String GetValueString() const override { return m_Value.ToString().c_str(); }
        virtual Guid GetValueGuid() const { return m_Value; }

        virtual Result ToString(ToStringContext& context) const override;

        virtual Variable* Clone(Array<uint8_t>& buffer) const override;
        virtual Variable* Clone(IHeap& heap) const override;

        virtual size_t GetSerializedSize() const  override;
        virtual Result Serialize(IOutputStream& output) const override;
        virtual Result Deserialize(IInputStream& input) override;

        virtual bool operator == (const Variable& op) const override
        {
            if (op.GetTypeName() != GetTypeName())
                return false;

            return op.GetValueGuid() == m_Value;
        }
    };


    DEFINE_BOXING_TEMPLETE(Guid, VariableGuid);
    //VariableBox BoxingByValue(IHeap& heap, Guid src);
    //VariableBox BoxingByReference(IHeap& heap, Guid src);
    //VariableBox Boxing(IHeap& heap, Guid src);
    //VariableBox Boxing(IHeap& heap, Array<Guid>& src);
    //VariableBox Boxing(IHeap& heap, const Array<Guid>& src);
    //IMPLEMENT_BOXING_TEMPLATE_INTERNAL(Guid, VariableGuid);


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // GuidGenerator
    //  Generates Guid from a provided random generator(c++11 < random > module)
    //  std::mt19937_64 is highly recommended as it has a SIMD implementation that
    //  makes it very fast and it produces high quality randomness.
    /////////////////////////////////////////////////////////////////////////////////////////////////
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


    /////////////////////////////////////////////////////////////////////////////////////////////////
    // GuidHelper
    /////////////////////////////////////////////////////////////////////////////////////////////////
    class GuidHelper
    {
    private:
        static GuidGenerator<std::mt19937_64> stm_Generator;
    public:

        static Guid New();
    };

} // SF
