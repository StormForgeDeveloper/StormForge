////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String Format utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {

	class IHeap;

namespace StrUtil
{
	// Maximum utf8 bytes per character
	// UTF-8 encoding supports longer byte sequences, up to 6 bytes, but the biggest code point of Unicode 6.0 (U+10FFFF) only takes 4 bytes.
	constexpr size_t MAX_UTF8_BYTES = 6;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	String functions
	//

	// string length in input data type, element count
	size_t StringLen(const char* StringValue);
	size_t StringLen(const wchar_t* StringValue);

	// string length in input data type for specified character count
	size_t StringLen(const char* StringValue, int CharacterCount); // We uses utf8
	inline size_t StringLen(const wchar_t* StringValue, int CharacterCount) { return std::min((size_t)CharacterCount, StringLen(StringValue)); }

	// Character count in the string
	size_t CharacterCount(const char* StringValue); // We uses utf8
	inline size_t CharacterCount(const wchar_t* StringValue) { return StringLen(StringValue); }


	////////////////////////////////////////////////////////////////////////////////
	//
	//	String manipulation helper
	//

	// String duplication, szDest will destroyed if exist, and new memory will be allocated
	Result StringDup(IHeap& heap, char* &szDest, const char* szSrc );
	Result StringDup(IHeap& heap, wchar_t* &szDest, const wchar_t* szSrc );

	// copy string and update dest pointer and length
	Result StringCopyEx(char* &szDest, int& iBuffLen, const char* szSrc); // copy with modified parameter
	Result StringCopyEx(wchar_t* &szDest, int& iBuffLen, const wchar_t* szSrc); // copy with modified parameter

	// String copy to szDest. if szDest is NULL, operation failed
	// Simple copy with boundary check
	Result StringCopy( char* szDest, int iBuffLen, const char* szSrc );
	Result StringCopy( wchar_t* szDest, int iBuffLen, const wchar_t* szSrc );
	template<int iBuffLen>
	inline Result StringCopy( char (&szDest)[iBuffLen], const char *szSrc );
	template<int iBuffLen>
	inline Result StringCopy( wchar_t (&wszDest)[iBuffLen], const wchar_t *wszSrc );


	//// Unicode to MBCS string conversion
	//Result WCSToMBCS( const wchar_t* strWCS, char *strMBCS, int iBuffLen );
	//template<int iBuffLen>
	//Result WCSToMBCS( const wchar_t* strWCS, char (&strMBCS)[iBuffLen] );
	//Result WCSToMBCS( const std::wstring &strWCS, std::string &strMBCS );

	// Ansi to UTF8
	Result ANSIToUTF8(const char* strAnsi, char *strUTF8, int iBuffLen);

	// UTF8 to Ansi
	Result UTF8ToANSI(const char* strUTF8, char *strAnsi, int iBuffLen);



	// Unicode to UTF8 string conversion
	size_t WCSToUTF8( const wchar_t* strWCS, char *strUTF8, int iBuffLen );
	template<int iBuffLen>
	size_t WCSToUTF8( const wchar_t* strWCS, char (&strUTF8)[iBuffLen] );
	size_t WCSToUTF8( const std::wstring &strWCS, std::string &strUTF8 );

	//// MBCS to Unicode string conversion
	//Result MBCSToWCS( const char *strMBCS, wchar_t* strWCS, int iBuffLen );
	//template<int iBuffLen>
	//Result MBCSToWCS( const char *strMBCS, wchar_t (&strWCS)[iBuffLen] );
	//Result MBCSToWCS( const std::string &strMBCS, std::wstring &strWCS );

	//// MBCS to UTF8 string conversion
	//Result MBCSToUTF8( const char *strMBCS, char* strUTF8, int iBuffLen );
	//template<int iBuffLen>
	//Result MBCSToUTF8( const char *strMBCS, char (&strUTF8)[iBuffLen] );
	//Result MBCSToUTF8( const std::string &strMBCS, std::string &strUTF8 );

	// UTF8 to Unicode string conversion
	size_t UTF8ToWCS( const char *strUTF8, wchar_t* strWCS, int iBuffLen );
	template<int iBuffLen>
	size_t UTF8ToWCS( const char *strUTF8, wchar_t (&strWCS)[iBuffLen] );
	size_t UTF8ToWCS( const std::string& strUTF8, std::wstring& strWCS );

	//// UTF8 to MBCS string conversion
	//Result UTF8ToMBCS( const char *strUTF8, char* strMBCS, int iBuffLen );
	//template<int iBuffLen>
	//Result UTF8ToMBCS( const char *strUTF8, char (&strMBCS)[iBuffLen] );
	//Result UTF8ToMBCS( const std::string& strUTF8, std::string& strMBCS );


	// String compare
	bool StringCompair( const char* szSrc, const char* szDest, int maxCmpair);
	bool StringCompair(const wchar_t* szSrc, const wchar_t* szDest, int maxCmpair);

	bool StringCompair( const char* szSrc, int iSrcBuffLen, const char* szDest, int iDestBuffLen );
	bool StringCompair( const wchar_t* szSrc, int iSrcBuffLen, const wchar_t* szDest, int iDestBuffLen );
	template<int iSrcBuffLen, int iDestBuffLen>
	bool StringCompair( char (&szSrc)[iSrcBuffLen], char (&szDest)[iDestBuffLen] );
	template<int iDestBuffLen>
	bool StringCompair( const char* szSrc, int iSrcBuffLen, char (&szDest)[iDestBuffLen] );
	template<int iSrcBuffLen>
	bool StringCompair( char (&szSrc)[iSrcBuffLen], const char* szDest, int iDestBuffLen );

	template<int iSrcBuffLen, int iDestBuffLen>
	bool StringCompair( wchar_t (&szSrc)[iSrcBuffLen], wchar_t (&szDest)[iDestBuffLen] );
	template<int iDestBuffLen>
	bool StringCompair( const wchar_t* szSrc, int iSrcBuffLen, wchar_t (&szDest)[iDestBuffLen] );
	template<int iSrcBuffLen>
	bool StringCompair( wchar_t (&szSrc)[iSrcBuffLen], const wchar_t* szDest, int iDestBuffLen );


	// String compare with lower case
	bool StringCompairIgnoreCase( const char* szSrc, int iSrcBuffLen, const char* szDest, int iDestBuffLen );
	bool StringCompairIgnoreCase( const wchar_t* szSrc, int iSrcBuffLen, const wchar_t* szDest, int iDestBuffLen );
	template<int iSrcBuffLen, int iDestBuffLen>
	bool StringCompairIgnoreCase( char (&szSrc)[iSrcBuffLen], char (&szDest)[iDestBuffLen] );
	template<int iDestBuffLen>
	bool StringCompairIgnoreCase( const char* szSrc, int iSrcBuffLen, char (&szDest)[iDestBuffLen] );
	template<int iSrcBuffLen>
	bool StringCompairIgnoreCase( char (&szSrc)[iSrcBuffLen], const char* szDest, int iDestBuffLen );

	template<int iSrcBuffLen, int iDestBuffLen>
	bool StringCompairIgnoreCase( wchar_t (&szSrc)[iSrcBuffLen], wchar_t (&szDest)[iDestBuffLen] );
	template<int iDestBuffLen>
	bool StringCompairIgnoreCase( const wchar_t* szSrc, int iSrcBuffLen, wchar_t (&szDest)[iDestBuffLen] );
	template<int iSrcBuffLen>
	bool StringCompairIgnoreCase( wchar_t (&szSrc)[iSrcBuffLen], const wchar_t* szDest, int iDestBuffLen );


	// String convert to lower case 
	// szSrc(In/Out)		: Source string to convert
	inline Result StringLower( char* szSrc, int iBuffLen );
	inline Result StringLower( wchar_t* szSrc, int iBuffLen );
	template<int iBuffLen>
	inline Result StringLower( char (&szSrc)[iBuffLen] );
	template<int iBuffLen>
	inline Result StringLower( wchar_t (&szSrc)[iBuffLen] );

	// String convert to lower case with reallocation with destination pointer and length update
	// szSrc				: Source string to convert
	// szDest(In/Out)		: Buffer pointer reference
	// iBuffLen(In/Out)		: Destination buffer size. if buffer is small to take all source message, then reallocated
	inline Result StringLower( char* &szDest, int &iBuffLen, const char* szSrc );
	inline Result StringLower( wchar_t* &szDest, int &iBuffLen, const wchar_t* szSrc );

	// Update desitnation pointer and size update
	inline Result StringLwrEx(char* &szDest, int &iBuffLen, const char* szSrc);
	inline Result StringLwrEx(wchar_t* &szDest, int &iBuffLen, const wchar_t* szSrc);

	// String convert to lower case with truncate, if source string longer then destination buffer
	// szSrc				: Source string to convert
	// szDest(In)			: Buffer pointer to copy
	template<int iBuffLen>
	inline Result StringLower( char (&szDest)[iBuffLen], const char *szSrc );
	template<int iBuffLen>
	inline Result StringLower( wchar_t (&wszDest)[iBuffLen], const wchar_t *wszSrc );


	// String convert to uppercase 
	// szSrc(In/Out)		: Source string to convert
	inline Result StringUpper( char* szSrc, int iBuffLen );
	inline Result StringUpper( wchar_t* szSrc, int iBuffLen );
	template<int iBuffLen>
	inline Result StringUpper( char (&szSrc)[iBuffLen] );
	template<int iBuffLen>
	inline Result StringUpper( wchar_t (&szSrc)[iBuffLen] );

	// String convert to uppercase with reallocation, if source string longer then destination buffer
	// szSrc				: Source string to convert
	// szDest(In/Out)		: Buffer pointer reference
	// iBuffLen(In/Out)		: Destination buffer size. if buffer is small to take all source message, then reallocated
	inline Result StringUpper( char* &szDest, int &iBuffLen, const char* szSrc );
	inline Result StringUpper( wchar_t* &szDest, int &iBuffLen, const wchar_t* szSrc );

	// String convert to uppercase with truncate, if source string longer then destination buffer
	// szSrc				: Source string to convert
	// szDest(In)			: Buffer pointer to copy
	template<int iBuffLen>
	inline Result StringUpper( char (&szDest)[iBuffLen], const char *szSrc );
	template<int iBuffLen>
	inline Result StringUpper( wchar_t (&wszDest)[iBuffLen], const wchar_t *wszSrc );


	template<int iBuffLen>
	Result StringCat(char(&szDest)[iBuffLen], const char *szSrc);

	// Check whether the character is white space character
	bool IsWhiteSpace(char ch);
	bool IsWhiteSpace(wchar_t ch);

	// Check whether the string is empty or null
	bool IsNullOrEmpty(const char* str);
	bool IsNullOrEmpty(const wchar_t* str);


	///////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Search
	//

	// Search string pointer of separator
	// str				: String input
	// sep				: separator
	const char* FindToken(const char* str, char sep);

	// Search string pointer of separators
	// str				: String input
	// sep				: separator
	const char* FindToken(const char* str, const char* seps);

	// Search index of separator
	// str				: String input
	// sep				: separator
	int Indexof(const char* str, char sep);

	// Search index of any separator
	// str				: String input
	// seps				: separators
	int IndexofAny(const char* str, const char* seps);

	// Search index of separator
	// str				: String input
	// sep				: separator
	int IndexofFromBack(const char* str, char sep);

	// Search index of any separator
	// str				: String input
	// seps				: separators
	int IndexofAnyFromBack(const char* str, const char* seps);


	///////////////////////////////////////////////////////////////////////////////////////////
	//
	//	UTF8 binary string
	//

#pragma pack (push)
#pragma pack (1)
	struct UTF8Bin
	{
		uint8_t IsNull;
		uint32_t Length;
		char stringData[1];
	};
#pragma pack(pop)

	// UTF8 to UTF8String(Database UTF8 Format) string conversion
	template<int iBuffLen>
	inline Result UTF8ToUTF8Bin( uint8_t (&UTF8BinBuff)[iBuffLen], const char* strSrc );

	inline Result UTF8BinToUTF8( char* strDst, int dstLen, const uint8_t* strSrc );


	/////////////////////////////////////////////////////////////////////////////
	//
	//	Helper data
	//

	extern const char* EmptyString;


} // namespace StrUtil
} // namespace SF

#include "SFStrUtil.inl"


