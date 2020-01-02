////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String manipulation utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "Util/SFLog.h"
#include "String/SFToString.h"
#include "Variable/SFVariableBoxing.h"
#include "String/SFStrFormat.h"
#include "Memory/SFMemory.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeSystem.h"

#include "iconv.h"

#if SF_PLATFORM == SF_PLATFORM_IOS
#define libiconv_open iconv_open
#endif

namespace SF {
namespace StrUtil {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	String formating helper
	//

	static inline int ChToInt( char ch )
	{
		int iChar = ch;
		iChar -= '0';
		if( iChar >= 0 && iChar < 10 )
			return iChar;

		return -1;
	}

	static inline void SkipSpace(const char*& szFormating)
	{
		for (char curChar = *szFormating; curChar && (curChar == ' ' && curChar != '	'); curChar = *szFormating++);
	}

	static inline double ReadNumber(char& curChar, const char*& szFormating)
	{
		double fNumber = 0;
		for (curChar = *szFormating++; curChar && (curChar != '%' && curChar != '}' && curChar != '{' && curChar != ':' && curChar != ','); curChar = *szFormating++)
		{
			if (curChar == '.')
				break;

			if (curChar == '\0')
				return fNumber;

			if (curChar < '0' || curChar > '9')
				continue;

			int iArgTem = ChToInt(curChar);
			if (iArgTem >= 0)
				fNumber = fNumber * 10 + iArgTem;
		}

		if (curChar != '.') return fNumber;

		double fExponent = 0.1;
		for (curChar = *szFormating++; curChar && (curChar != '%' && curChar != '}' && curChar != ':' && curChar != ','); curChar = *szFormating++)
		{
			if (curChar < '0' || curChar > '9')
				continue;

			if (curChar == '\0')
				return fNumber;

			int iArgTem = ChToInt(curChar);
			if (iArgTem >= 0)
				fNumber += (double)iArgTem * fExponent;
		}

		return fNumber;
	}

	// Internal format routine
	size_t Format_Internal( char*& pBuffer, int& iBuffLen, const char* szFormating, int iNumArg, VariableBox* Args )
	{
		char tempBuffer[512];

		if(pBuffer != nullptr && iBuffLen <= 0)
			return 0;

		// we are going to calculate size only
		if(pBuffer == nullptr)
			iBuffLen = std::numeric_limits<int>::max();

		auto orgBuffLen = iBuffLen;

		char curChar;

		for( curChar = *szFormating++; curChar && iBuffLen > 0; curChar = *szFormating++ )
		{
			if( curChar == '%' || curChar == '{')
			{
				int iArg = 0;

				SkipSpace(szFormating);

				// read argument index
				iArg = (int)(ReadNumber(curChar, szFormating) + 0.1);
				if (curChar == '{')
				{
					if(pBuffer!= nullptr) *pBuffer++ = curChar;
					iBuffLen--;
					continue;
				}

				// read option
				char option = '\0';
				double digits = -1;
				if (curChar == ':')
				{
					if (curChar == '\0')
					{
						assert(false);
						return 0;
					}

					SkipSpace(szFormating);

					if (curChar == '\0')
						return 0;

					curChar = *szFormating++;

					if (curChar == '\0')
						return 0;

					option = curChar;

					digits = ReadNumber(curChar, szFormating);
				}

				// Read max length
				if (curChar == ',')
				{
					if (curChar == '\0')
					{
						assert(false);
						return 0;
					}

					SkipSpace(szFormating);

					if (curChar == '\0')
						return 0;

					option = (char)ReadNumber(curChar, szFormating);
				}

				if( curChar == '\0' )
					return 0;

				if (iArg < iNumArg && Args[iArg].GetVariable() != nullptr)
				{
					ToStringContext context;
					context.MaxDigit = (int)digits;
					if (option == 'x' || option == 'X')
						context.Radix = 16;

					auto pArg = Args[iArg].GetVariable();

					if (pBuffer != nullptr)
					{
						context.StringBuffer = pBuffer;
						context.StringBufferLength = iBuffLen;

						pArg->ToString(context);

						pBuffer = context.StringBuffer;
						iBuffLen = context.StringBufferLength;
					}
					else
					{
						context.StringBuffer = tempBuffer;
						context.StringBufferLength = (int)sizeof(tempBuffer);

						pArg->ToString(context);

						int usedSize = ((int)sizeof(tempBuffer) - context.StringBufferLength);
						assert(usedSize >= 0);
						iBuffLen -= usedSize;
					}
				}
				else
				{
					if (pBuffer != nullptr)
						StrUtil::StringCopyEx( pBuffer, iBuffLen, "(Null)" );
					else
						iBuffLen -= (int)(strlen("(Null)"));
				}
			}
			else if (curChar == '}')
			{
				// Skip the first closing bracket
				curChar = *szFormating++;
				if (curChar == '}')
				{
					if (pBuffer != nullptr) *pBuffer++ = curChar;
					iBuffLen--;
				}
				else
				{
					// ignore other case
				}
			}
			else
			{
				if (pBuffer != nullptr) *pBuffer++ = curChar;
				iBuffLen--;
			}
		}

		if (pBuffer != nullptr)
		{
			// Force Null terminate
			if (iBuffLen == 0)
				(pBuffer - 1)[0] = 0;
			else if(iBuffLen > 0)
			{
				pBuffer[0] = 0;
				iBuffLen--;
			}
		}

		return orgBuffLen - iBuffLen;
	}






	// String duplication, szDest will destroyded if exist, and new memory will be allocated
	Result StringDup(IHeap& memoryManager, char* &szDest, const char* szSrc)
	{
		if (szDest != NULL)
		{
			memoryManager.Free(szDest);
			szDest = NULL;
		}

		if (szSrc)
		{
			INT iLen = (INT)strlen(szSrc) + 1;
			szDest = new(memoryManager) char[iLen];
			if (szDest == NULL)
				return ResultCode::OUT_OF_MEMORY;

			memcpy(szDest, szSrc, iLen*sizeof(char));
		}

		return ResultCode::SUCCESS;
	}

	Result StringDup(IHeap& memoryManager, wchar_t* &szDest, const wchar_t* szSrc)
	{
		if (szDest != NULL)
		{
			memoryManager.Free(szDest);
			szDest = NULL;
		}

		if (szSrc)
		{
			INT iLen = (INT)wcslen(szSrc) + 1;
			szDest = new(memoryManager) wchar_t[iLen];
			if (szDest == NULL)
				return ResultCode::OUT_OF_MEMORY;

			memcpy(szDest, szSrc, iLen*sizeof(wchar_t));
		}

		return ResultCode::SUCCESS;
	}

	// String copy to szDest. if szDest is NULL, operation failed
	Result StringCopyEx(char* &szDest, INT& iBuffLen, const char* szSrc)
	{
		if (szSrc && szDest)
		{
			char curChar;
			while (iBuffLen > 0 && (curChar = *szSrc++) != 0)
			{
				*szDest++ = curChar;
				iBuffLen--;
			}

			if (iBuffLen == 0)// force null terminate
				*(szDest - 1) = '\0';
			else
				*(szDest) = '\0';
		}
		else
		{
			if (szDest && iBuffLen > 0)
				szDest[0] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	// String copy to szDest. if szDest is NULL, operation failed
	Result StringCopyEx(wchar_t* &szDest, INT& iBuffLen, const wchar_t* szSrc)
	{
		if (szSrc && szDest)
		{
			wchar_t curChar;
			while (iBuffLen > 0 && (curChar = *szSrc++) != 0)
			{
				*szDest++ = curChar;
				iBuffLen--;
			}

			if (iBuffLen == 0)// force null terminate
				*(szDest - 1) = '\0';
			else
				*(szDest) = '\0';
		}
		else
		{
			if (szDest && iBuffLen > 0)
				szDest[0] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	Result StringCopy(char* szDest, INT iBuffLen, const char* szSrc)
	{
		if (szSrc && szDest)
		{
			char curChar;
			while (iBuffLen > 0 && (curChar = *szSrc++) != 0)
			{
				*szDest++ = curChar;
				iBuffLen--;
			}

			if (iBuffLen == 0)// force null terminate
				*(szDest - 1) = '\0';
			else
				szDest[0] = '\0';
		}
		else
		{
			if (szDest && iBuffLen > 0)
				szDest[0] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	Result StringCopy(wchar_t* szDest, INT iBuffLen, const wchar_t* szSrc)
	{
		if (szSrc)
		{
			wchar_t curChar;
			while (iBuffLen > 0 && (curChar = *szSrc++) != 0)
			{
				*szDest++ = curChar;
				iBuffLen--;
			}

			if (iBuffLen == 0)// force null terminate
				*(szDest - 1) = '\0';
			else
				szDest[0] = '\0';
		}
		else
		{
			if (szDest && iBuffLen > 0)
				szDest[0] = L'\0';
		}

		return ResultCode::SUCCESS;
	}

	
	/////////////////////////////////////////////////////////////////////////////
	//
	//	Helper data
	//

	const char* EmptyString = "";



	/////////////////////////////////////////////////////////////////////////////
	//
	//	iconv system
	//

	class ModuleIconv_impl
	{
	private:


	public:
		ModuleIconv_impl()
		{
			// Make iconv detect system locale correctly
			setlocale(LC_ALL, "");
		}

		~ModuleIconv_impl()
		{
		}


		// remain buffer size will be in destSize
		Result Convert(const char* destCode, char* dest, size_t destSize, const char* srcCode, const char* src, size_t srcSize, size_t& convertedSize)
		{
			Result hr = ResultCode::SUCCESS;
			auto orgDestSize = destSize;

			convertedSize = 0;

			iconv_t context = libiconv_open(destCode, srcCode);
			if (context == (iconv_t)-1)
			{
				hr = ResultCode::FAIL;
				goto Proc_End;
			}

#if SF_PLATFORM == SF_PLATFORM_LINUX | SF_PLATFORM == SF_PLATFORM_IOS
			{
				// On linux, source buffer can be changed.
				StaticArray<char, 2048> srcTemp(GetSystemHeap());
				srcTemp.reserve(srcSize);
				if(!StrUtil::StringCopy(srcTemp.data(), (int)srcSize, src))
                {
                    hr = ResultCode::FAIL;
                    goto Proc_End;
                }
                char* strCopied = srcTemp.data();
				convertedSize = libiconv(context, (const char**)&strCopied, &srcSize, &dest, &destSize);
			}
#else
			convertedSize = libiconv(context, (const char**)&src, &srcSize, &dest, &destSize);
#endif
			if (convertedSize == (size_t)-1)
			{
				switch (errno)
				{
				case E2BIG:
					hr = ResultCode::OUT_OF_MEMORY;
					break;
				case EILSEQ:
					hr = ResultCode::INVALID_BYTE_SEQUENCE;
					break;
				case EINVAL:
					hr = ResultCode::OUT_OF_MEMORY;
					break;
				default:
					hr = ResultCode::UNEXPECTED;
					break;
				}

				convertedSize = 0;
			}
			else
			{
				convertedSize = orgDestSize - destSize;
			}

		Proc_End:

			if (context != (iconv_t)-1)
			{
				libiconv_close(context);
			}

			return hr;
		}
	};

	ModuleIconv_impl ModuleIconv;

	/////////////////////////////////////////////////////////////////////////////
	//
	//	String convert
	//

	//// Unicode to MBCS string conversion
	//Result WCSToMBCS(const WCHAR* strWCS, char *strMBCS, INT iBuffLen)
	//{
	//	size_t convertedSize;

	//	if (strWCS == nullptr || strMBCS == nullptr)
	//		return ResultCode::INVALID_ARG;

	//	Result hr = ModuleIconv.Convert("", (char*)strMBCS, iBuffLen, "UTF-16", (const char*)strWCS, wcslen(strWCS)*sizeof(wchar_t), convertedSize);
	//	if (!(hr)) return hr;

	//	if (iBuffLen >= 1)
	//	{
	//		iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
	//		strMBCS[iBuffLen] = '\0';
	//	}

	//	return ResultCode::SUCCESS;
	//}

	//Result WCSToMBCS(const std::wstring &strWCS, std::string &strMBCS)
	//{
	//	size_t convertedSize;
	//	char stringBuffer[4*1024];

	//	if (strWCS.c_str() == nullptr)
	//	{
	//		strMBCS = "";
	//		return ResultCode::SUCCESS;
	//	}

	//	Result hr = ModuleIconv.Convert("", (char*)stringBuffer, countof(stringBuffer), "UTF-16", (const char*)strWCS.c_str(), strWCS.length(), convertedSize);
	//	if (!(hr)) return hr;

	//	auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
	//	stringBuffer[lastPos] = '\0';

	//	strMBCS = stringBuffer;

	//	return ResultCode::SUCCESS;
	//}

	// 
	Result ANSIToUTF8(const char* strAnsi, char *strUTF8, INT iBuffLen)
	{
		size_t convertedSize;

		if (strAnsi == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("UTF-8", (char*)strUTF8, iBuffLen, "CP1252", (const char*)strAnsi, strlen(strAnsi), convertedSize);
		if (!(hr)) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
			strUTF8[iBuffLen] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	// 
	Result UTF8ToANSI(const char* strUTF8, char *strAnsi, INT iBuffLen)
	{
		size_t convertedSize;

		if (strAnsi == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("CP1252", (char*)strAnsi, iBuffLen, "UTF-8", (const char*)strUTF8, strlen(strUTF8), convertedSize);
		if (!(hr)) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
			strAnsi[iBuffLen] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	// Unicode to UTF8 string conversion
	Result WCSToUTF8(const WCHAR* strWCS, char *strUTF8, INT iBuffLen)
	{
		size_t convertedSize;

		if (strWCS == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("UTF-8", (char*)strUTF8, iBuffLen, "UTF-16LE", (const char*)strWCS, wcslen(strWCS)*sizeof(wchar_t), convertedSize);
		if (!(hr)) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
			strUTF8[iBuffLen] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	Result WCSToUTF8(const std::wstring &strWCS, std::string &strUTF8)
	{
		size_t convertedSize;
		char stringBuffer[4 * 1024];

		if (strWCS.c_str() == nullptr)
		{
			strUTF8 = "";
			return ResultCode::SUCCESS;
		}

		Result hr = ModuleIconv.Convert("UTF-8", (char*)stringBuffer, countof(stringBuffer), "UTF-16LE", (const char*)strWCS.c_str(), strWCS.length(), convertedSize);
		if (!(hr)) return hr;

		auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
		stringBuffer[lastPos] = '\0';

		strUTF8 = stringBuffer;

		return ResultCode::SUCCESS;
	}

	//// MBCS to Unicode string conversion
	//Result MBCSToWCS(const char *strMBCS, WCHAR* strWCS, INT iBuffLen)
	//{
	//	size_t convertedSize;

	//	if (strWCS == nullptr || strMBCS == nullptr)
	//		return ResultCode::INVALID_ARG;

	//	Result hr = ModuleIconv.Convert("UTF-16", (char*)strWCS, iBuffLen, "", (const char*)strMBCS, strlen(strMBCS), convertedSize);
	//	if (!(hr)) return hr;

	//	if (iBuffLen >= 1)
	//	{
	//		iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
	//		strWCS[iBuffLen] = '\0';
	//	}

	//	return ResultCode::SUCCESS;
	//}

	//Result MBCSToWCS(const std::string &strMBCS, std::wstring &strWCS)
	//{
	//	size_t convertedSize;
	//	wchar_t stringBuffer[4 * 1024];

	//	if (strWCS.c_str() == nullptr)
	//	{
	//		strWCS = L"";
	//		return ResultCode::SUCCESS;
	//	}

	//	Result hr = ModuleIconv.Convert("UTF-16", (char*)stringBuffer, countof(stringBuffer), "", (const char*)strMBCS.c_str(), strMBCS.length(), convertedSize);
	//	if (!(hr)) return hr;

	//	auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
	//	stringBuffer[lastPos] = '\0';

	//	strWCS = stringBuffer;

	//	return ResultCode::SUCCESS;
	//}


	// UTF8 to Unicode string conversion
	Result UTF8ToWCS(const char *strUTF8, wchar_t* strWCS, INT iBuffLen)
	{
		size_t convertedSize;

		if (strWCS == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("UTF-16LE", (char*)strWCS, iBuffLen * sizeof(wchar_t), "UTF-8", (const char*)strUTF8, strlen(strUTF8)+1, convertedSize);
		if (!(hr)) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
			strWCS[iBuffLen] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	Result UTF8ToWCS(const std::string& strUTF8, std::wstring& strWCS)
	{
		size_t convertedSize;
		wchar_t stringBuffer[4 * 1024];

		if (strWCS.c_str() == nullptr)
		{
			strWCS = L"";
			return ResultCode::SUCCESS;
		}

		Result hr = ModuleIconv.Convert("UTF-16LE", (char*)stringBuffer, countof(stringBuffer) * sizeof(wchar_t), "UTF-8", (const char*)strUTF8.c_str(), strUTF8.length(), convertedSize);
		if (!(hr)) return hr;

		auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
		stringBuffer[lastPos] = '\0';

		strWCS = stringBuffer;

		return ResultCode::SUCCESS;
	}


	//// MBCS to Unicode string conversion
	//Result MBCSToUTF8(const char *strMBCS, char* strUTF8, INT iBuffLen)
	//{
	//	size_t convertedSize;

	//	if (strUTF8 == nullptr || strMBCS == nullptr)
	//		return ResultCode::INVALID_ARG;

	//	Result hr = ModuleIconv.Convert("UTF-8", (char*)strUTF8, iBuffLen, "", (const char*)strMBCS, strlen(strMBCS), convertedSize);
	//	if (!(hr)) return hr;

	//	if (iBuffLen >= 1)
	//	{
	//		iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
	//		strUTF8[iBuffLen] = '\0';
	//	}

	//	return ResultCode::SUCCESS;
	//}

	//Result MBCSToUTF8(const std::string &strMBCS, std::string &strUTF8)
	//{
	//	size_t convertedSize;
	//	char stringBuffer[4 * 1024];

	//	if (strUTF8.c_str() == nullptr)
	//	{
	//		strUTF8 = "";
	//		return ResultCode::SUCCESS;
	//	}

	//	Result hr = ModuleIconv.Convert("UTF-16", (char*)stringBuffer, countof(stringBuffer), "", (const char*)strMBCS.c_str(), strMBCS.length(), convertedSize);
	//	if (!(hr)) return hr;

	//	auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
	//	stringBuffer[lastPos] = '\0';

	//	strUTF8 = stringBuffer;

	//	return ResultCode::SUCCESS;
	//}


	//// UTF8 to MBCS string conversion
	//Result UTF8ToMBCS(const char *strUTF8, char* strMBCS, INT iBuffLen)
	//{
	//	size_t convertedSize;

	//	if (strUTF8 == nullptr || strMBCS == nullptr)
	//		return ResultCode::INVALID_ARG;

	//	Result hr = ModuleIconv.Convert("UTF-8", (char*)strMBCS, iBuffLen, "", (const char*)strUTF8, strlen(strUTF8), convertedSize);
	//	if (!(hr)) return hr;

	//	if (iBuffLen >= 1)
	//	{
	//		iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
	//		strMBCS[iBuffLen] = '\0';
	//	}

	//	return ResultCode::SUCCESS;
	//}

	//Result UTF8ToMBCS(const std::string& strUTF8, std::string& strMBCS)
	//{
	//	size_t convertedSize;
	//	char stringBuffer[4 * 1024];

	//	if (strMBCS.c_str() == nullptr)
	//	{
	//		strMBCS = "";
	//		return ResultCode::SUCCESS;
	//	}

	//	Result hr = ModuleIconv.Convert("UTF-16", (char*)stringBuffer, countof(stringBuffer), "", (const char*)strUTF8.c_str(), strUTF8.length(), convertedSize);
	//	if (!(hr)) return hr;

	//	auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
	//	stringBuffer[lastPos] = '\0';

	//	strMBCS = stringBuffer;

	//	return ResultCode::SUCCESS;
	//}




	///////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Search
	//

	// Search string pointer of separator
	// str				: String input
	// sep				: separator
	const char* FindToken(const char* str, char sep)
	{
		auto idx = Indexof(str, sep);
		if (idx < 0) return nullptr;
		return &str[idx];
	}

	// Search string pointer of separators
	// str				: String input
	// sep				: separator
	const char* FindToken(const char* str, const char* seps)
	{
		auto idx = IndexofAny(str, seps);
		if (idx < 0) return nullptr;
		return &str[idx];
	}


	// Search index of separator
	// str				: String input
	// sep				: separator
	int Indexof(const char* str, char sep)
	{
		if (str == nullptr)
			return -1;
		for(int iChar = 0; ;iChar++)
		{
			char currentChar = *str++;
			if (currentChar == '\0')
				break;

			if (currentChar == sep)
				return iChar;
		}

		return -1;
	}

	// Search index of any separator
	// str				: String input
	// seps				: separators
	int IndexofAny(const char* str, const char* seps)
	{
		if (str == nullptr)
			return -1;

		auto numSeps = strlen(seps);
		for (int iChar = 0; ; iChar++)
		{
			char currentChar = *str++;
			if (currentChar == '\0')
				break;

			for (uint iSep = 0; iSep < numSeps; iSep++)
			{
				auto sep = seps[iSep];
				if (currentChar == sep)
					return iChar;
			}
		}

		return -1;
	}


	// Search index of separator
	// str				: String input
	// sep				: separator
	int IndexofFromBack(const char* pSrc, char sep)
	{
		if (pSrc == nullptr)
			return -1;

		auto strLen = strlen(pSrc);
		if (strLen == 0)
			return -1;

		auto str = pSrc + strLen - 1;

		for (int iChar = (int)strLen - 1; iChar >= 0; iChar--, str--)
		{
			char currentChar = *str;
			if (currentChar == sep)
				return iChar;
		}

		return -1;
	}


	// Search index of any separator
	// str				: String input
	// seps				: separators
	int IndexofAnyFromBack(const char* pSrc, const char* seps)
	{
		if (pSrc == nullptr)
			return -1;

		auto strLen = strlen(pSrc);
		if (strLen == 0)
			return -1;

		auto str = pSrc + strLen - 1;

		for (int iChar = (int)strLen - 1;  iChar >= 0; iChar--, str--)
		{
			char currentChar = *str;

			for (uint iSep = 0; seps[iSep] != '\0'; iSep++)
			{
				auto sep = seps[iSep];
				if (currentChar == sep)
					return iChar;
			}
		}

		return -1;
	}


} // namespace StrUtil
} // namespace SF

