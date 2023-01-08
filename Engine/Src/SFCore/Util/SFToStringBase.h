////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author: Kyungkun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Util/SFStrUtil.h"
#include "Container/SFArray.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {

	class StringCrc32;
	class StringCrc64;

	///////////////////////////////////////////////////////////////////////////////////
	//
	// ToString Context
	//



    template<class CharType>
    struct TToStringOutputStream
    {
        TToStringOutputStream()
            : OrgBuffLen(0)
            , BuffLen(0)
            , pBuffer(nullptr)
        {
        }

        TToStringOutputStream(int InBuffLen, CharType* InBuffer)
            : OrgBuffLen(InBuffLen)
            , BuffLen(InBuffLen)
            , pBuffer(InBuffer)
        {
        }

        TToStringOutputStream(const TToStringOutputStream& src)
            : OrgBuffLen(src.OrgBuffLen)
            , BuffLen(src.BuffLen)
            , pBuffer(src.pBuffer)
        {
        }

        TToStringOutputStream& operator =(const TToStringOutputStream& src)
        {
            OrgBuffLen = src.OrgBuffLen;
            BuffLen = src.BuffLen;
            pBuffer = src.pBuffer;
            return *this;
        }

        SF_FORCEINLINE void Append(CharType newChar)
        {
            if (BuffLen > 0)
            {
                if (pBuffer)
                {
                    *pBuffer = newChar;
                    pBuffer++;
                }
                BuffLen--;
            }
        }

        SF_FORCEINLINE void Append(const CharType* newString)
        {
            if (BuffLen > 0)
            {
                if (pBuffer != nullptr)
                    StrUtil::StringCopyEx(pBuffer, BuffLen, TDefinedString<CharType>::Null);
                else
                    BuffLen -= (int)StrUtil::StringLen(TDefinedString<CharType>::Null);
            }
        }

        template<class OtherCharType>
        SF_FORCEINLINE void Append(const TToStringOutputStream<OtherCharType>& otherStream)
        {
            int usedByte = otherStream.UsedSize();
            assert(usedByte >= 0);

            if (BuffLen >= usedByte && otherStream.pBuffer != nullptr)
            {
                if (pBuffer != nullptr)
                    StrUtil::StringConvert(pBuffer, BuffLen, otherStream.pBuffer);
                else
                    BuffLen -= usedByte;
            }
        }

        SF_FORCEINLINE int UsedSize() const
        {
            return OrgBuffLen - BuffLen;
        }

        // Make sure it is null terminated string
        SF_FORCEINLINE void NullTerminate()
        {
            if (pBuffer != nullptr)
            {
                // Force Null terminate
                if (BuffLen == 0)
                    (pBuffer - 1)[0] = TCharCode<CharType>::NullTerminate;
                else if (BuffLen > 0)
                {
                    pBuffer[0] = TCharCode<CharType>::NullTerminate;
                    BuffLen--;
                }
            }
        }

        SF_FORCEINLINE bool IsValid()
        {
            return BuffLen > 0;
        }

        SF_FORCEINLINE bool IsFinished()
        {
            return !IsValid();
        }

        int OrgBuffLen{};
        int BuffLen{};
        CharType* pBuffer{};
    };


	struct ToStringContext
	{
        TToStringOutputStream<char> OutStream;

		unsigned	Radix			= 10;
		int			MaxDigit		= 100;
		int			MaxCharacters	= std::numeric_limits<int>::max();
		int			MaxArraySize	= 20;
	};


	///////////////////////////////////////////////////////////////////////////////////
	//
	// ToString helper implementations
	//


	// 
	Result _IToA(ToStringContext& context, int8_t val);
	Result _IToA(ToStringContext& context, uint8_t val);
	Result _IToA(ToStringContext& context, int16_t val);
	Result _IToA(ToStringContext& context, uint16_t val);
	Result _IToA(ToStringContext& context, int32_t val);
	Result _IToA(ToStringContext& context, uint32_t val);
	Result _IToA(ToStringContext& context, int64_t val);
	Result _IToA(ToStringContext& context, uint64_t val);


	Result _FToA(ToStringContext& context, double val);


}; // namespace SF



