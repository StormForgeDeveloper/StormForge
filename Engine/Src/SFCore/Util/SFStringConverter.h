////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : string converter
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Util/SFString.h"


namespace SF {

    template<class ToCharType, class FromCharType>
    class StringConverter
    {
    public:
        TString<ToCharType> ConvertedString;

        StringConverter()
        {
        }

        StringConverter(const TString<FromCharType>& srcString)
        {
            Convert(srcString);
        }

        // return by default if it doesn't have specialized conversion logic
        const TString<ToCharType>& Convert(const TString<FromCharType>& srcString)
        {
            return srcString;
        }

        operator const TString<ToCharType>& ()
        {
            return ConvertedString;
        }
    };

    template<>
    const TString<char>& StringConverter<char, wchar_t>::Convert(const TString<wchar_t>& srcString)
    {
        size_t maxStringSize = (srcString.length() + 1) * 5;
        ConvertedString.Reserve(maxStringSize);

        size_t convertedSize = StrUtil::WCSToUTF8(srcString, ConvertedString.data(), (int)maxStringSize);
        ConvertedString.Resize(convertedSize); 

        return ConvertedString;
    }

    template<>
    const TString<wchar_t>& StringConverter<wchar_t, char>::Convert(const TString<char>& srcString)
    {
        size_t maxStringSize = (srcString.length() + 1);
        ConvertedString.Reserve(maxStringSize);

        size_t convertedSize = StrUtil::UTF8ToWCS(srcString, ConvertedString.data(), (int)maxStringSize);
        ConvertedString.Resize(convertedSize);

        return ConvertedString;
    }

} // namespace SF

