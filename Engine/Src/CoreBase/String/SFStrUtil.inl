////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String manipulation utility
//	
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {
	namespace StrUtil {

		template<int iBuffLen>
		Result StringCopy(char(&szDest)[iBuffLen], const char *szSrc)
		{
			if (szSrc)
			{
				int iLen = (int)strlen(szSrc) + 1;
				iLen = iBuffLen < iLen ? iBuffLen : iLen;

				if (szDest && iBuffLen > 0)
				{
					memcpy(szDest, szSrc, iLen*sizeof(char));
					if (iLen > 0)
						szDest[iLen - 1] = '\0';
				}
			}
			else
			{
				if (szDest && iBuffLen > 0)
					szDest[0] = '\0';
			}

			return ResultCode::SUCCESS;
		}

		template<int iBuffLen>
		Result StringCopy(wchar_t(&szDest)[iBuffLen], const wchar_t *szSrc)
		{
			if (szSrc)
			{
				int iLen = (int)wcslen(szSrc) + 1;
				iLen = iBuffLen < iLen ? iBuffLen : iLen;

				if (szDest && iBuffLen > 0)
				{
					memcpy(szDest, szSrc, iLen*sizeof(wchar_t));
					if (iLen > 0)
						szDest[iLen - 1] = L'\0';
				}
			}
			else
			{
				if (szDest && iBuffLen > 0)
					szDest[0] = L'\0';
			}

			return ResultCode::SUCCESS;
		}




		template<int iBuffLen>
		Result WCSToUTF8(const wchar_t* strWCS, char(&strUTF8)[iBuffLen])
		{
			return WCSToUTF8(strWCS, strUTF8, iBuffLen);
		}


		template<int iBuffLen>
		Result UTF8ToWCS(const char *strUTF8, wchar_t(&strWCS)[iBuffLen])
		{
			return UTF8ToWCS(strUTF8, strWCS, iBuffLen);
		}


		template<int iBuffLen>
		Result UTF8ToUTF8Bin(uint8_t(&UTF8BinBuff)[iBuffLen], const char* strSrc)
		{
			UTF8Bin *pUTF8 = (UTF8Bin*)UTF8BinBuff;
			pUTF8->IsNull = 0;
			pUTF8->Length = (uint32_t)strlen(strSrc);

			return StrUtil::StringCopy((char*)pUTF8->stringData, iBuffLen - sizeof(UTF8Bin), strSrc);
		}

		Result UTF8BinToUTF8(char* strDst, int dstLen, const uint8_t* strSrc)
		{
			Result hr = ResultCode::SUCCESS;

			UTF8Bin *pUTF8 = (UTF8Bin*)strSrc;

			if (pUTF8->IsNull)
				StringCopy(strDst, dstLen, "");
			else
			{
				StringCopy(strDst, dstLen, pUTF8->stringData);
			}

			return hr;
		}



		// String compare
		inline bool StringCompair(const char* szSrc, int iSrcBuffLen, const char* szDest, int iDestBuffLen)
		{
			if (szSrc == nullptr && szDest == nullptr)
				return true;

			if (szSrc == nullptr || szDest == nullptr)
				return false;

			if (iSrcBuffLen <= 0)	iSrcBuffLen = (int)strlen(szSrc) + 1;
			if (iDestBuffLen <= 0)	iDestBuffLen = (int)strlen(szDest) + 1;

			int MaxTry = std::min(iSrcBuffLen, iDestBuffLen);

			return StringCompair(szSrc, szDest, MaxTry);
		}

		// String compare
		inline bool StringCompair(const char* szSrc, const char* szDest, int maxCmpair)
		{
			if (szSrc == nullptr && szDest == nullptr)
				return true;

			if (szSrc == nullptr || szDest == nullptr)
				return false;


			for (int iComp = 0; iComp < maxCmpair; iComp++)
			{
				int iDiff = szSrc[0] - szDest[0];
				if (iDiff != 0)
					return false;

				if (*szSrc == '\0' || *szDest == '\0') break;

				szSrc++;
				szDest++;
			}

			return true;
		}

		inline bool StringCompair(const wchar_t* szSrc, const wchar_t* szDest, int maxCmpair)
		{
			if (szSrc == nullptr && szDest == nullptr)
				return true;

			if (szSrc == nullptr || szDest == nullptr)
				return false;


			for (int iComp = 0; iComp < maxCmpair; iComp++)
			{
				int iDiff = szSrc[0] - szDest[0];
				if (iDiff != 0)
					return false;

				if (*szSrc == L'\0' || *szDest == L'\0') break;

				szSrc++;
				szDest++;
			}

			return true;
		}

		inline bool StringCompair(const wchar_t* szSrc, int iSrcBuffLen, const wchar_t* szDest, int iDestBuffLen)
		{
			if (szSrc == nullptr && szDest == nullptr)
				return true;

			if (szSrc == nullptr || szDest == nullptr)
				return false;

			if (iSrcBuffLen <= 0)	iSrcBuffLen = (int)wcslen(szSrc) + 1;
			if (iDestBuffLen <= 0)	iDestBuffLen = (int)wcslen(szDest) + 1;

			int iCompLen = std::min(iSrcBuffLen, iDestBuffLen);
			for (int iComp = 0; iComp < iCompLen; iComp++, szSrc++, szDest++)
			{
				int iDiff = *szSrc - *szDest;
				if (iDiff != 0)
					return false;

				if (*szSrc == L'\0' || *szDest == L'\0') break;
			}

			return true;
		}

		template<int iSrcBuffLen, int iDestBuffLen>
		inline bool StringCompair(char(&szSrc)[iSrcBuffLen], char(&szDest)[iDestBuffLen])
		{
			return StringCompair(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iDestBuffLen>
		inline bool StringCompair(const char* szSrc, int iSrcBuffLen, char(&szDest)[iDestBuffLen])
		{
			return StringCompair(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iSrcBuffLen>
		inline bool StringCompair(char(&szSrc)[iSrcBuffLen], const char* szDest, int iDestBuffLen)
		{
			return StringCompair(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}


		template<int iSrcBuffLen, int iDestBuffLen>
		inline bool StringCompair(wchar_t(&szSrc)[iSrcBuffLen], wchar_t(&szDest)[iDestBuffLen])
		{
			return StringCompair(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iDestBuffLen>
		inline bool StringCompair(const wchar_t* szSrc, int iSrcBuffLen, wchar_t(&szDest)[iDestBuffLen])
		{
			return StringCompair(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iSrcBuffLen>
		inline bool StringCompair(wchar_t(&szSrc)[iSrcBuffLen], const wchar_t* szDest, int iDestBuffLen)
		{
			return StringCompair(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}




		// String compare with lower case
		inline bool StringCompairIgnoreCase(const char* szSrc, int iSrcBuffLen, const char* szDest, int iDestBuffLen)
		{
			if (szSrc == nullptr && szDest == nullptr)
				return true;

			if (szSrc == nullptr || szDest == nullptr)
				return false;

			if (iSrcBuffLen <= 0)	iSrcBuffLen = (int)strlen(szSrc) + 1;
			if (iDestBuffLen <= 0)	iDestBuffLen = (int)strlen(szDest) + 1;

			int iCompLen = std::min(iSrcBuffLen, iDestBuffLen);

			for (int iComp = 0; iComp < iCompLen; iComp++, szSrc++, szDest++)
			{
				char cSrc = szSrc[0];
				char cDest = szDest[0];
				char src = (cSrc >= 'A' && cSrc <= 'Z') ? (char)(cSrc - 'A' + 'a') : cSrc;
				char dst = (cDest >= 'A' && cDest <= 'Z') ? (char)(cDest - 'A' + 'a') : cDest;
				int iDiff = src - dst;
				if (iDiff != 0)
					return false;

				if (cSrc == L'\0' || cDest == L'\0') break;
			}

			return true;
		}

		inline bool StringCompairIgnoreCase(const wchar_t* szSrc, int iSrcBuffLen, const wchar_t* szDest, int iDestBuffLen)
		{
			if (szSrc == nullptr && szDest == nullptr)
				return true;

			if (szSrc == nullptr || szDest == nullptr)
				return false;

			if (iSrcBuffLen <= 0)	iSrcBuffLen = (int)wcslen(szSrc) + 1;
			if (iDestBuffLen <= 0)	iDestBuffLen = (int)wcslen(szDest) + 1;

			int iCompLen = std::min(iSrcBuffLen, iDestBuffLen);

			for (int iComp = 0; iComp < iCompLen && szSrc[0] != L'\0' && szDest[0] != L'\0'; iComp++, szSrc++, szDest++)
			{
				wchar_t cSrc = szSrc[0];
				wchar_t cDest = szDest[0];
				wchar_t src = (cSrc >= L'A' && cSrc <= L'Z') ? (cSrc - L'A' + L'a') : cSrc;
				wchar_t dst = (cDest >= L'A' && cDest <= L'Z') ? (cDest - L'A' + L'a') : cDest;
				int iDiff = src - dst;
				if (iDiff != 0)
					return false;

				if (cSrc == L'\0' || cDest == L'\0') break;
			}

			return true;
		}

		template<int iSrcBuffLen, int iDestBuffLen>
		inline bool StringCompairIgnoreCase(char(&szSrc)[iSrcBuffLen], char(&szDest)[iDestBuffLen])
		{
			return StringCompairIgnoreCase(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iDestBuffLen>
		inline bool StringCompairIgnoreCase(const char* szSrc, int iSrcBuffLen, char(&szDest)[iDestBuffLen])
		{
			return StringCompairIgnoreCase(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iSrcBuffLen>
		inline bool StringCompairIgnoreCase(char(&szSrc)[iSrcBuffLen], const char* szDest, int iDestBuffLen)
		{
			return StringCompairIgnoreCase(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}


		template<int iSrcBuffLen, int iDestBuffLen>
		inline bool StringCompairIgnoreCase(wchar_t(&szSrc)[iSrcBuffLen], wchar_t(&szDest)[iDestBuffLen])
		{
			return StringCompairIgnoreCase(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iDestBuffLen>
		inline bool StringCompairIgnoreCase(const wchar_t* szSrc, int iSrcBuffLen, wchar_t(&szDest)[iDestBuffLen])
		{
			return StringCompairIgnoreCase(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}

		template<int iSrcBuffLen>
		inline bool StringCompairIgnoreCase(wchar_t(&szSrc)[iSrcBuffLen], const wchar_t* szDest, int iDestBuffLen)
		{
			return StringCompairIgnoreCase(szSrc, iSrcBuffLen, szDest, iDestBuffLen);
		}





		// String convert to lower case 
		// szSrc(In/Out)		: Source string to convert
		Result StringLower(char* szSrc, int iBuffLen)
		{
			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;

			if (iBuffLen <= 0) iBuffLen = (int)strlen(szSrc);

			for (int iConv = 0; iConv < iBuffLen && szSrc[0] != '\0'; iConv++)
			{
				int cSrc = szSrc[0];
				if (cSrc >= 'A' && cSrc <= 'Z')
					szSrc[0] = (cSrc - 'A' + 'a');

				szSrc++;
			}

			return ResultCode::SUCCESS;
		}

		Result StringLower(wchar_t* szSrc, int iBuffLen)
		{
			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;

			if (iBuffLen <= 0) iBuffLen = (int)wcslen(szSrc);

			for (int iConv = 0; iConv < iBuffLen && szSrc[0] != L'\0'; iConv++)
			{
				wchar_t cSrc = szSrc[0];
				if (cSrc >= L'A' && cSrc <= L'Z')
					szSrc[0] = cSrc - L'A' + L'a';

				szSrc++;
			}

			return ResultCode::SUCCESS;
		}

		template<int iBuffLen>
		Result StringLower(char(&szSrc)[iBuffLen])
		{
			return StringLower(szSrc, iBuffLen);
		}

		template<int iBuffLen>
		Result StringLower(wchar_t(&szSrc)[iBuffLen])
		{
			return StringLower(szSrc, iBuffLen);
		}


		// String convert to lower case with reallocation, if source string longer then testination buffer
		// szSrc				: Source string to convert
		// szDest(In/Out)		: Buffer pointer reference
		// iBuffLen(In/Out)		: Destination buffer size. if buffer is small to take all source message, then reallocated
		Result StringLower(char* &szDest, int &iBuffLen, const char* szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)strlen(szSrc) + 1;

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(szDest, iBuffLen, szSrc);
				if (!(hr)) return hr;
			}
			else
			{
				return ResultCode::INVALID_ARG;
				//hr = StringDup(szDest, szSrc);
				//if (!(hr)) return hr;
				//iBuffLen = iSrcBuffLen;
			}

			return StringLower(szDest, iBuffLen);
		}

		Result StringLower(wchar_t* &szDest, int &iBuffLen, const wchar_t* szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)wcslen(szSrc) + 1;

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(szDest, iBuffLen, szSrc);
				if (!(hr)) return hr;
			}
			else
			{
				return ResultCode::INVALID_ARG;
				//hr = StringDup(szDest, szSrc);
				//if (!(hr)) return hr;
				//iBuffLen = iSrcBuffLen;
			}

			return StringLower(szDest, iBuffLen);
		}


		Result StringLwrEx(char* &szDest, int &iBuffLen, const char* szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			hr = StringCopyEx(szDest, iBuffLen, szSrc);
			if (!(hr)) return hr;

			return StringLower(szDest, iBuffLen);
		}

		Result StringLwrEx(wchar_t* &szDest, int &iBuffLen, const wchar_t* szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			hr = StringCopyEx(szDest, iBuffLen, szSrc);
			if (!(hr)) return hr;

			return StringLower(szDest, iBuffLen);
		}

		// String convert to lower case with truncate, if source string longer then testination buffer
		// szSrc				: Source string to convert
		// szDest(In)			: Buffer pointer to copy
		template<int iBuffLen>
		Result StringLower(char(&szDest)[iBuffLen], const char *szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)strlen(szSrc) + 1;
			int iConvLen = std::min(iBuffLen, iSrcBuffLen);

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(szDest, iConvLen, szSrc);
				if (!(hr)) return hr;
			}

			return StringLower(szDest, iConvLen);
		}

		template<int iBuffLen>
		Result StringLower(wchar_t(&wszDest)[iBuffLen], const wchar_t *wszSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (wszSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)wcslen(wszSrc) + 1;
			int iConvLen = std::min(iBuffLen, iSrcBuffLen);

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(wszDest, iConvLen, wszSrc);
				if (!(hr)) return hr;
			}

			return StringLower(wszDest, iConvLen);
		}





		// String convert to lower case 
		// szSrc(In/Out)		: Source string to convert
		Result StringUpper(char* szSrc, int iBuffLen)
		{
			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;

			if (iBuffLen <= 0) iBuffLen = (int)strlen(szSrc);

			for (int iConv = 0; iConv < iBuffLen && szSrc[0] != '\0'; iConv++)
			{
				int srcChar = szSrc[0];
				if (srcChar >= 'a' && srcChar <= 'z')
					srcChar = srcChar - 'a' + 'A';

				szSrc++;
			}

			return ResultCode::SUCCESS;
		}

		Result StringUpper(wchar_t* szSrc, int iBuffLen)
		{
			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;

			if (iBuffLen <= 0) iBuffLen = (int)wcslen(szSrc);

			for (int iConv = 0; iConv < iBuffLen && szSrc[0] != L'\0'; iConv++)
			{
				if (szSrc[0] >= 'a' && szSrc[0] <= 'z')
					szSrc[0] = szSrc[0] - 'a' + 'A';

				szSrc++;
			}

			return ResultCode::SUCCESS;
		}

		template<int iBuffLen>
		Result StringUpper(char(&szSrc)[iBuffLen])
		{
			return StringUpper(szSrc, iBuffLen);
		}

		template<int iBuffLen>
		Result StringUpper(wchar_t(&szSrc)[iBuffLen])
		{
			return StringUpper(szSrc, iBuffLen);
		}


		// String convert to lower case with reallocation, if source string longer then testination buffer
		// szSrc				: Source string to convert
		// szDest(In/Out)		: Buffer pointer reference
		// iBuffLen(In/Out)		: Destination buffer size. if buffer is small to take all source message, then reallocated
		Result StringUpper(char* &szDest, int &iBuffLen, const char* szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)strlen(szSrc) + 1;

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(szDest, iBuffLen, szSrc);
				if (!(hr)) return hr;
			}
			else
			{
				return ResultCode::INVALID_ARG;
				//hr = StringDup(szDest, szSrc);
				//if (!(hr)) return hr;
				//iBuffLen = iSrcBuffLen;
			}

			return StringUpper(szDest, iBuffLen);
		}

		Result StringUpper(wchar_t* &szDest, int &iBuffLen, const wchar_t* szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)wcslen(szSrc) + 1;

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(szDest, iBuffLen, szSrc);
				if (!(hr)) return hr;
			}
			else
			{
				return ResultCode::INVALID_ARG;
				//hr = StringDup(szDest, szSrc);
				//if (!(hr)) return hr;
				//iBuffLen = iSrcBuffLen;
			}

			return StringUpper(szDest, iBuffLen);
		}

		// String convert to lower case with truncate, if source string longer then testination buffer
		// szSrc				: Source string to convert
		// szDest(In)			: Buffer pointer to copy
		template<int iBuffLen>
		Result StringUpper(char(&szDest)[iBuffLen], const char *szSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (szSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)strlen(szSrc) + 1;
			int iConvLen = std::min(iBuffLen, iSrcBuffLen);

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(szDest, iConvLen, szSrc);
				if (!(hr)) return hr;
			}

			return StringUpper(szDest, iConvLen);
		}

		template<int iBuffLen>
		Result StringUpper(wchar_t(&wszDest)[iBuffLen], const wchar_t *wszSrc)
		{
			Result hr = ResultCode::SUCCESS;

			if (wszSrc == nullptr)
				return ResultCode::INVALID_ARG;


			int iSrcBuffLen = (int)wcslen(wszSrc) + 1;
			int iConvLen = std::min(iBuffLen, iSrcBuffLen);

			if (iBuffLen >= iSrcBuffLen)
			{
				hr = StringCopy(wszDest, iConvLen, wszSrc);
				if (!(hr)) return hr;
			}

			return StringUpper(wszDest, iConvLen);
		}



		template<int iBuffLen>
		inline Result StringCat(char(&szDest)[iBuffLen], const char *szSrc)
		{
			size_t orgLen = strlen(szDest);
			return StringCopy(szDest + orgLen, iBuffLen - (int)orgLen, szSrc);
		}



		inline bool IsWhiteSpace(char ch)
		{
			return ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t';
		}


		inline bool IsNullOrEmpty(const char* str)
		{
			if (str == nullptr || str[0] == '\0')
				return true;
			return false;
		}


	}
}


