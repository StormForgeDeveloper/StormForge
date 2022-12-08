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
    class TCharCode
    {
    };

    template<>
    struct TCharCode<char>
    {
        static constexpr char NullTerminate = '\0';
        static constexpr char Space = ' ';
        static constexpr char Tab = '\t';
        static constexpr char CR = '\r';
        static constexpr char LF = '\n';
        static constexpr char Colon = ':';
        static constexpr char Semicolon = ':';
        static constexpr char LeftCurlyBrace = '{';
        static constexpr char RightCurlyBrace = '}';
        static constexpr char Comma = ',';
        static constexpr char Dot = '.';
        static constexpr char NUM_0 = '0';
        static constexpr char NUM_9 = '9';
        static constexpr char A = 'A';
        static constexpr char a = 'a';
        static constexpr char X = 'X';
        static constexpr char x = 'x';
        static constexpr char Z = 'Z';
        static constexpr char z = 'z';
    };

    template<>
    struct TCharCode<wchar_t>
    {
        static constexpr wchar_t NullTerminate = L'\0';
        static constexpr wchar_t Space = L' ';
        static constexpr wchar_t Tab = L'\t';
        static constexpr wchar_t CR = L'\r';
        static constexpr wchar_t LF = L'\n';
        static constexpr wchar_t Colon = L':';
        static constexpr wchar_t Semicolon = L':';
        static constexpr wchar_t LeftCurlyBrace = L'{';
        static constexpr wchar_t RightCurlyBrace = L'}';
        static constexpr wchar_t Comma = L',';
        static constexpr wchar_t Dot = L'.';
        static constexpr wchar_t NUM_0 = L'0';
        static constexpr wchar_t NUM_9 = L'9';
        static constexpr wchar_t A = L'A';
        static constexpr wchar_t a = L'a';
        static constexpr wchar_t X = L'X';
        static constexpr wchar_t x = L'x';
        static constexpr wchar_t Z = L'Z';
        static constexpr wchar_t z = L'z';
    };

    template<class CharType>
    class TDefinedString
    {
    };

    template<>
    struct TDefinedString<char>
    {
        static constexpr const char* Null = "Null";
    };

    template<>
    struct TDefinedString<wchar_t>
    {
        static constexpr const wchar_t* Null = L"Null";
    };


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



