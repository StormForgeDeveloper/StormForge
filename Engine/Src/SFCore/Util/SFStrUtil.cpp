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
#include "Util/SFStrUtil.h"
#include "Util/SFLog.h"
#include "Util/SFToString.h"
#include "Variable/SFVariableBoxing.h"
#include "Util/SFStrFormat.h"
#include "MemoryManager/SFMemory.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeSystem.h"

#include "iconv.h"

#if SF_PLATFORM == SF_PLATFORM_IOS
#define libiconv_open iconv_open
#endif

namespace SF {
namespace StrUtil {

    /*

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

	static inline int ChToInt(wchar_t ch)
	{
		int iChar = ch;
		iChar -= L'0';
		if (iChar >= 0 && iChar < 10)
			return iChar;

		return -1;
	}

	static inline void SkipSpace(const char*& szFormating)
	{
		for (char curChar = *szFormating; curChar && (curChar == ' ' && curChar != '	'); curChar = *szFormating++);
	}

	static inline void SkipSpace(const wchar_t*& szFormating)
	{
		for (wchar_t curChar = *szFormating; curChar && (curChar == L' ' && curChar != L'	'); curChar = *szFormating++);
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

	static inline double ReadNumber(wchar_t& curChar, const wchar_t*& szFormating)
	{
		double fNumber = 0;
		for (curChar = *szFormating++; curChar && (curChar != L'%' && curChar != L'}' && curChar != L'{' && curChar != L':' && curChar != L','); curChar = *szFormating++)
		{
			if (curChar == L'.')
				break;

			if (curChar == L'\0')
				return fNumber;

			if (curChar < L'0' || curChar > L'9')
				continue;

			int iArgTem = ChToInt(curChar);
			if (iArgTem >= 0)
				fNumber = fNumber * 10 + iArgTem;
		}

		if (curChar != L'.') return fNumber;

		double fExponent = 0.1;
		for (curChar = *szFormating++; curChar && (curChar != L'%' && curChar != L'}' && curChar != L':' && curChar != L','); curChar = *szFormating++)
		{
			if (curChar < L'0' || curChar > L'9')
				continue;

			if (curChar == L'\0')
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
		const size_t tempBufferSize = 512;
		char* tempBuffer = nullptr;

		if(pBuffer != nullptr && iBuffLen <= 0)
			return 0;

		// we are going to calculate size only
		if (pBuffer == nullptr)
		{
			tempBuffer = reinterpret_cast<char*>(alloca(tempBufferSize)); // don't need to allocate if we don't use size calculation
			iBuffLen = std::numeric_limits<int>::max();
		}

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
						context.OutStream.pBuffer = pBuffer;
						context.OutStream.BuffLen = iBuffLen;

						pArg->ToString(context);

						pBuffer = context.OutStream.pBuffer;
						iBuffLen = context.OutStream.BuffLen;
					}
					else
					{
						context.OutStream.pBuffer = tempBuffer;
						context.OutStream.BuffLen = (int)tempBufferSize;

						pArg->ToString(context);

						int usedSize = ((int)tempBufferSize - context.OutStream.BuffLen);
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

	size_t Format_Internal(wchar_t*& pBuffer, int& iBuffLen, const wchar_t* szFormating, int iNumArg, VariableBox* Args)
	{
		char tempBuffer[512];

		if (pBuffer != nullptr && iBuffLen <= 0)
			return 0;

		// we are going to calculate size only
		if (pBuffer == nullptr)
			iBuffLen = std::numeric_limits<int>::max();

		auto orgBuffLen = iBuffLen;

		wchar_t curChar;

		for (curChar = *szFormating++; curChar && iBuffLen > 0; curChar = *szFormating++)
		{
			if (curChar == L'%' || curChar == L'{')
			{
				int iArg = 0;

				SkipSpace(szFormating);

				// read argument index
				iArg = (int)(ReadNumber(curChar, szFormating) + 0.1);
				if (curChar == '{')
				{
					if (pBuffer != nullptr) *pBuffer++ = curChar;
					iBuffLen--;
					continue;
				}

				// read option
				wchar_t option = L'\0';
				double digits = -1;
				if (curChar == L':')
				{
					if (curChar == L'\0')
					{
						assert(false);
						return 0;
					}

					SkipSpace(szFormating);

					if (curChar == L'\0')
						return 0;

					curChar = *szFormating++;

					if (curChar == L'\0')
						return 0;

					option = curChar;

					digits = ReadNumber(curChar, szFormating);
				}

				// Read max length
				if (curChar == L',')
				{
					if (curChar == L'\0')
					{
						assert(false);
						return 0;
					}

					SkipSpace(szFormating);

					if (curChar == L'\0')
						return 0;

					option = (wchar_t)ReadNumber(curChar, szFormating);
				}

				if (curChar == L'\0')
					return 0;

				if (iArg < iNumArg && Args[iArg].GetVariable() != nullptr)
				{
					ToStringContext context;
					context.MaxDigit = (int)digits;
					if (option == L'x' || option == L'X')
						context.Radix = 16;

					auto pArg = Args[iArg].GetVariable();

					context.OutStream.pBuffer = tempBuffer;
					context.OutStream.BuffLen = (int)sizeof(tempBuffer);

					pArg->ToString(context);

					int usedSize = ((int)sizeof(tempBuffer) - context.OutStream.BuffLen);
					assert(usedSize >= 0);
					if (pBuffer == nullptr)
					{
						iBuffLen -= usedSize;
					}
					else
					{
						auto convertedSize = StrUtil::UTF8ToWCS(tempBuffer, pBuffer, iBuffLen);
						iBuffLen -= static_cast<int>(convertedSize);
					}
				}
				else
				{
					if (pBuffer != nullptr)
						StrUtil::StringCopyEx(pBuffer, iBuffLen, L"(Null)");
					else
						iBuffLen -= (int)(StrUtil::StringLen(L"(Null)"));
				}
			}
			else if (curChar == L'}')
			{
				// Skip the first closing bracket
				curChar = *szFormating++;
				if (curChar == L'}')
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
			else if (iBuffLen > 0)
			{
				pBuffer[0] = 0;
				iBuffLen--;
			}
		}

		return orgBuffLen - iBuffLen;
	}



	size_t StringLen(const char* StringValue)
	{
		if (StringValue == nullptr)
			return 0;

		size_t strLen = 0;
		for (; *StringValue != '\0'; StringValue++, strLen++)
		{
		}
		
		return strLen;
	}

	size_t StringLen(const wchar_t* StringValue)
	{
		if (StringValue == nullptr)
			return 0;

		size_t strLen = 0;
		for (; *StringValue != '\0'; StringValue++, strLen++)
		{
		}

		return strLen;
	}

	size_t CharacterCount(const char* StringValue)
	{
		static const uint8_t AdditionalCount[] = { 1, 1, 1, 1,  1, 1, 2, 3 };

		if (StringValue == nullptr)
			return 0;

		auto* CurPos = reinterpret_cast<const uint8_t*>(StringValue);
		size_t CharacterCount = 0;
		for(uint32_t CurChar = *CurPos++; CurChar != 0; CurChar = *CurPos++, CharacterCount++)
		{
			CurChar >>= 4;
			if ((CurChar & 0x8) == 0)
				continue;

			CurPos += AdditionalCount[CurChar & 0x7];
		}

		return CharacterCount;
	}

	// String duplication, szDest will destroyed if exist, and new memory will be allocated
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

	// 
	Result ANSIToUTF8(const char* strAnsi, char *strUTF8, INT iBuffLen)
	{
		size_t convertedSize;

		if (strAnsi == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("UTF-8", (char*)strUTF8, iBuffLen, "CP1252", (const char*)strAnsi, strlen(strAnsi), convertedSize);
		if (!hr) return hr;

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
		size_t convertedSize = 0;

		if (strAnsi == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("CP1252", (char*)strAnsi, iBuffLen, "UTF-8", (const char*)strUTF8, strlen(strUTF8), convertedSize);
		if (!hr) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((INT)convertedSize + 1, iBuffLen) - 1;
			strAnsi[iBuffLen] = '\0';
		}

		return ResultCode::SUCCESS;
	}

	// Unicode to UTF8 string conversion
	size_t WCSToUTF8(const wchar_t* strWCS, char *strUTF8, int iBuffLen)
	{
		size_t convertedSize;

		if (strWCS == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("UTF-8", (char*)strUTF8, iBuffLen, "UTF-16LE", (const char*)strWCS, wcslen(strWCS)*sizeof(wchar_t), convertedSize);
		if (!hr) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((int)convertedSize + 1, iBuffLen) - 1;
			strUTF8[iBuffLen] = '\0';
		}

		return convertedSize;
	}

	size_t WCSToUTF8(const std::wstring &strWCS, std::string &strUTF8)
	{
		size_t convertedSize;
		char stringBuffer[4 * 1024];

		if (strWCS.c_str() == nullptr)
		{
			strUTF8 = "";
			return ResultCode::SUCCESS;
		}

		assert(sizeof(stringBuffer) >= ((strWCS.length() + 1) * 5)); // Maximum buffer test

		Result hr = ModuleIconv.Convert("UTF-8", (char*)stringBuffer, countof(stringBuffer), "UTF-16LE", (const char*)strWCS.c_str(), strWCS.length() * sizeof(wchar_t), convertedSize);
		if (!hr) return hr;

		auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
		stringBuffer[lastPos] = '\0';

		strUTF8 = stringBuffer;

		return convertedSize;
	}

	// Unicode to UTF8 string conversion
	size_t WCSToUTF8(const char16_t* strWCS, char* strUTF8, int iBuffLen)
	{
		size_t convertedSize;

		if (strWCS == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		auto inputStrLen = std::char_traits<char16_t>::length(strWCS);

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		const char* char16Type = "UTF-16LE";
#else
		const char* char16Type = "UTF-16LE";
#endif

		Result hr = ModuleIconv.Convert("UTF-8", (char*)strUTF8, iBuffLen, char16Type, (const char*)strWCS, inputStrLen * sizeof(char16_t), convertedSize);
		if (!hr) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((int)convertedSize + 1, iBuffLen) - 1;
			strUTF8[iBuffLen] = '\0';
		}

		return convertedSize;
	}

	size_t WCSToUTF8(const std::u16string& strWCS, std::string& strUTF8)
	{
		size_t convertedSize;
		char stringBuffer[4 * 1024];

		if (strWCS.c_str() == nullptr)
		{
			strUTF8 = "";
			return ResultCode::SUCCESS;
		}

		assert(sizeof(stringBuffer) >= ((strWCS.length() + 1) * 5)); // Maximum buffer test
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		const char* char16Type = "UTF-16LE";
#else
		const char* char16Type = "UTF-16BE";
#endif

		Result hr = ModuleIconv.Convert("UTF-8", (char*)stringBuffer, countof(stringBuffer), char16Type, (const char*)strWCS.c_str(), strWCS.length() * sizeof(char16_t), convertedSize);
		if (!hr) return hr;

		auto lastPos = std::min(convertedSize + 1, countof(stringBuffer)) - 1;
		stringBuffer[lastPos] = '\0';

		strUTF8 = stringBuffer;

		return convertedSize;
	}


	// UTF8 to Unicode string conversion
	size_t UTF8ToWCS(const char *strUTF8, wchar_t* strWCS, int iBuffLen)
	{
		size_t convertedSize;

		if (strWCS == nullptr || strUTF8 == nullptr)
			return ResultCode::INVALID_ARG;

		Result hr = ModuleIconv.Convert("UTF-16LE", (char*)strWCS, iBuffLen * sizeof(wchar_t), "UTF-8", (const char*)strUTF8, strlen(strUTF8)+1, convertedSize);
		if (!(hr)) return hr;

		if (iBuffLen >= 1)
		{
			iBuffLen = std::min((int)convertedSize + 1, iBuffLen) - 1;
			strWCS[iBuffLen] = '\0';
		}

		return convertedSize;
	}

	size_t UTF8ToWCS(const std::string& strUTF8, std::wstring& strWCS)
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

		return strWCS.length();
	}




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

*/

} // namespace StrUtil
} // namespace SF

