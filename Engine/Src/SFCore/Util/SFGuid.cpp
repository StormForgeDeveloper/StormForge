////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Guid
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "Util/SFGuid.h"
#include "Util/SFGuidHelper.h"
#include "Platform/SFCPUInfo.h"
#include "Util/SFLog.h"

namespace SF
{
    IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Guid);

    Result _ToString(ToStringContext& context, const Guid& value)
    {
        context.OutStream.BuffLen -= (int)value.ToString(context.OutStream.pBuffer, context.OutStream.BuffLen);

        return ResultCode::SUCCESS;
    }

    namespace GuidImpl
    {
        // This implementation is based on https ://github.com/crashoz/uuid_v4

        constexpr int UUID_NumDigits[] = {8, 4, 4, 4, 2, 2, 2, 2, 2, 2 };
        constexpr int UUID_NumBytes[] = {4, 2, 2, 2, 1, 1, 1, 1, 1, 1 };

        void SwapBytes(Array<uint8_t>& buffer, int basePos, int numBytes)
        {
            for (int left = basePos, right = basePos + numBytes - 1; left < right; right--, left++)
            {
                std::swap(buffer[left], buffer[right]);
            }
        }


        /*
          Converts a 128-bits unsigned int to an Guid string representation.
          Uses SIMD via Intel's AVX2 instruction set.
         */
        void m128itos(__m128i x, char* mem)
        {
            // Expand each byte in x to two bytes in res
            // i.e. 0x12345678 -> 0x0102030405060708
            // Then translate each byte to its hex ascii representation
            // i.e. 0x0102030405060708 -> 0x3132333435363738
            const __m256i mask = _mm256_set1_epi8(0x0F);
            const __m256i add = _mm256_set1_epi8(0x06);
            const __m256i alpha_mask = _mm256_set1_epi8(0x10);
            const __m256i alpha_offset = _mm256_set1_epi8(0x57);

            __m256i a = _mm256_castsi128_si256(x);
            __m256i as = _mm256_srli_epi64(a, 4);
            __m256i lo = _mm256_unpacklo_epi8(as, a);
            __m128i hi = _mm256_castsi256_si128(_mm256_unpackhi_epi8(as, a));
            __m256i c = _mm256_inserti128_si256(lo, hi, 1);
            __m256i d = _mm256_and_si256(c, mask);
            __m256i alpha = _mm256_slli_epi64(_mm256_and_si256(_mm256_add_epi8(d, add), alpha_mask), 3);
            __m256i offset = _mm256_blendv_epi8(_mm256_slli_epi64(add, 3), alpha_offset, alpha);
            __m256i res = _mm256_add_epi8(d, offset);

            // Add dashes between blocks as specified in RFC-4122
            // 8-4-4-4-12
            const __m256i dash_shuffle = _mm256_set_epi32(0x0b0a0908, 0x07060504, 0x80030201, 0x00808080, 0x0d0c800b, 0x0a090880, 0x07060504, 0x03020100);
            const __m256i dash = _mm256_set_epi64x(0x0000000000000000ull, 0x2d000000002d0000ull, 0x00002d000000002d, 0x0000000000000000ull);

            __m256i resd = _mm256_shuffle_epi8(res, dash_shuffle);
            resd = _mm256_or_si256(resd, dash);

            _mm256_storeu_si256((__m256i*)mem, resd);
            *(uint16_t*)(mem + 16) = uint16_t(_mm256_extract_epi16(res, 7));
            *(uint32_t*)(mem + 32) = _mm256_extract_epi32(res, 7);
        }

        // 32 characters are packed into x
        __m128i StrTom128i(__m256i x)
        {
            // Build a mask to apply a different offset to alphas and digits
            const __m256i sub = _mm256_set1_epi8(0x2F);
            const __m256i mask = _mm256_set1_epi8(0x20);
            const __m256i alpha_offset = _mm256_set1_epi8(0x28);
            const __m256i digits_offset = _mm256_set1_epi8(0x01);
            const __m256i unweave = _mm256_set_epi32(0x0f0d0b09, 0x0e0c0a08, 0x07050301, 0x06040200, 0x0f0d0b09, 0x0e0c0a08, 0x07050301, 0x06040200);
            const __m256i shift = _mm256_set_epi32(0x00000000, 0x00000004, 0x00000000, 0x00000004, 0x00000000, 0x00000004, 0x00000000, 0x00000004);

            // Translate ascii bytes to their value
            // i.e. 0x3132333435363738 -> 0x0102030405060708
            // Shift hi-digits
            // i.e. 0x0102030405060708 -> 0x1002300450067008
            // Horizontal add
            // i.e. 0x1002300450067008 -> 0x12345678
            __m256i a = _mm256_sub_epi8(x, sub);
            __m256i alpha = _mm256_slli_epi64(_mm256_and_si256(a, mask), 2);
            __m256i sub_mask = _mm256_blendv_epi8(digits_offset, alpha_offset, alpha);
            a = _mm256_sub_epi8(a, sub_mask);
            a = _mm256_shuffle_epi8(a, unweave);
            a = _mm256_sllv_epi32(a, shift);
            a = _mm256_hadd_epi32(a, _mm256_setzero_si256());
            a = _mm256_permute4x64_epi64(a, 0b00001000);

            return _mm256_castsi256_si128(a);
        }

        /*
          Converts an Guid string representation to a 128-bits unsigned int.
          Uses SIMD via Intel's AVX2 instruction set.
         */
        __m128i RFCStrTom128i(const char* mem)
        {
            // Remove dashes and pack hex ascii bytes in a 256-bits int
            const __m256i dash_shuffle = _mm256_set_epi32(0x80808080, 0x0f0e0d0c, 0x0b0a0908, 0x06050403, 0x80800f0e, 0x0c0b0a09, 0x07060504, 0x03020100);

            __m256i x = _mm256_loadu_si256((__m256i*)mem);
            x = _mm256_shuffle_epi8(x, dash_shuffle);
            x = _mm256_insert_epi16(x, (*(uint16_t*)(mem + 16)), 7);
            x = _mm256_insert_epi32(x, (*(uint32_t*)(mem + 32)), 7);

            return StrTom128i(x);
        }


        __m128i ShortFormStrTom128i(const char* mem)
        {
            // Remove dashes and pack hex ascii bytes in a 256-bits int
            const __m256i dash_shuffle = _mm256_set_epi32(0x80808080, 0x0f0e0d0c, 0x0b0a0908, 0x06050403, 0x80800f0e, 0x0c0b0a09, 0x07060504, 0x03020100);

            __m256i x = _mm256_loadu_si256((__m256i*)mem);

            return StrTom128i(x);
        }
    }

    const Guid Guid::Empty(0,0);

    Guid Guid::FromBytes(const uint8_t* bytes)
    {
        if (bytes == nullptr)
        {
            return Guid(0,0);
        }
        else
        {
            __m128i x = _mm_loadu_si128((__m128i*)bytes);
            return Guid(x);
        }
    }

    void Guid::ToString(char* strBuff) const
    {
        if (CPUInfo::GetFeatures().AVX2)
        {
            __m128i x = _mm_loadu_si128((__m128i*)data);
            GuidImpl::m128itos(x, strBuff);
        }
        else
        {
            uint8_t dataBuff[16];
            memcpy(dataBuff, data, sizeof(dataBuff));
            ArrayView<uint8_t> dataArray(16, dataBuff);

            ArrayView<uint8_t> outBuff(36, reinterpret_cast<uint8_t*>(strBuff));
            Result hr;
            int basePos = 0;
            const uint8_t* curPos = dataBuff;
            for (int numBytes : GuidImpl::UUID_NumBytes)
            {
                // Swap bytes, UUID uses big endian
                GuidImpl::SwapBytes(dataArray, basePos, numBytes);

                // Hex encode
                hr = Util::HEXEncode(numBytes, curPos, outBuff);
                if (hr.IsFailure())
                    return;

                curPos += numBytes;
                basePos += numBytes;

                // Append '-'
                outBuff.push_back('-');
            }
        }
    }

    bool Guid::TryParseRFC(const char* str, Guid& outGuid)
    {
        ArrayView<uint8_t> outBuff(16, 0, outGuid.data);
        Result hr;

        const uint8_t* curPos = reinterpret_cast<const uint8_t*>(str);
        int basePos = 0;
        for (int NumDigit : GuidImpl::UUID_NumDigits)
        {
            hr = Util::HEXDecode(NumDigit, curPos, outBuff);
            if (hr.IsFailure())
                return false;

            // Swap bytes, UUID uses big endian
            // for now we only support little endian
            int numBytes = NumDigit / 2;
            GuidImpl::SwapBytes(outBuff, basePos, numBytes);

            curPos += NumDigit;
            basePos += numBytes;

            // Skip '-'
            if ((*curPos) != '-')
                return false;

            curPos++;
            basePos++;
        }

        return hr.IsSuccess();
    }

    bool Guid::TryParse32(const char* str, Guid& outGuid)
    {
        ArrayView<uint8_t> outBuff(16, 0, outGuid.data);
        Result hr = Util::HEXDecode(32, reinterpret_cast<const uint8_t*>(str), outBuff);
        if (hr.IsFailure())
            return false;

        // Swap bytes, UUID uses big endian
        // for now we only support little endian
        int basePos = 0;
        for (int numBytes : GuidImpl::UUID_NumBytes)
        {
            GuidImpl::SwapBytes(outBuff, basePos, numBytes);

            basePos += numBytes;
        }

        return true;
    }

    bool Guid::TryParseUInt64(const char* str, Guid& outGuid)
    {
        if (str == nullptr)
        {
            outGuid.Reset();
            return false;
        }

        uint64_t intValue = std::atoll(str);

        outGuid = Guid::FromUInt64(intValue);

        return true;
    }

    bool Guid::TryParseHexUInt64(const char* str, Guid& outGuid)
    {
        if (str == nullptr)
        {
            outGuid.Reset();
            return false;
        }

        uint64_t intValue;
        ArrayView<uint8_t> outBuff(8, 0, reinterpret_cast<uint8_t*>(&intValue));
        Result hr = Util::HEXDecode(16, reinterpret_cast<const uint8_t*>(str), outBuff);
        if (hr.IsFailure())
            return false;

        outGuid = Guid::FromUInt64(intValue);

        return true;
    }

    bool Guid::TryParseGeneric(const char* str, Guid& outGuid)
    {
        size_t strLen = StrUtil::StringLen(str);
        if (strLen == 36 && StrUtil::Indexof(str, '-')) // assuming that it is RFC format
        {
            if (CPUInfo::GetFeatures().AVX2)
            {
                // RFCStrTom128i doesn't check validity. let's run simple and quick test
                if (str[8] != '-' || str[13] != '-' || str[18] != '-' || str[23] != '-')
                {
                    return false;
                }

                outGuid = Guid(GuidImpl::RFCStrTom128i(str));
               return true;
            }
            else
            {
                return TryParseRFC(str, outGuid);
            }
        }
        else if (strLen == 32) // compact format
        {
            if (CPUInfo::GetFeatures().AVX2)
            {
                outGuid = Guid(GuidImpl::RFCStrTom128i(str));
                return true;
            }
            else
            {
                return TryParse32(str, outGuid);
            }
        }
        else // abnormal format, assuming that it is UInt64 integer
        {
            return TryParseUInt64(str, outGuid);
        }
    }

    Guid Guid::ParseGeneric(const char* str)
    {
        Guid guid;
        if (!TryParseGeneric(str, guid))
        {
            memset(guid.data, 0, sizeof(data));
        }
        return guid;
    }

    Guid Guid::FromUInt64(uint64_t value)
    {
        Guid guid;

        memcpy(guid.data, &value, 8);
        memset(guid.data + 8, 0, 8);

        return guid;
    }


} // namespace SF


