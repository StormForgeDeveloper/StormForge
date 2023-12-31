////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base64 codec
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"



namespace SF {
namespace Util {
	
	static const char* g_Crypto_Base64_chars =	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
												"abcdefghijklmnopqrstuvwxyz"
												"0123456789+/";

	static const char* g_Crypto_Base64URL_chars =	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
													"abcdefghijklmnopqrstuvwxyz"
													"0123456789-_";

	static inline Result Base64_DecodeChar(uint8_t in, uint8_t& out, const char* encoding_chars)
	{
		if ('A' <= in && in <= 'Z')
		{
			out = uint8_t(in - 'A');
		}
		else if ('a' <= in && in <= 'z')
		{
			out = uint8_t(in - 'a' + 26);
		}
		else if ('0' <= in && in <= '9')
		{
			out = uint8_t(in - '0' + 26 * 2);
		}
		else
		{
			if (encoding_chars[26 * 2 + 10 + 0] == in)
				out = 26 * 2 + 10 + 0;
			else if (encoding_chars[26 * 2 + 10 + 1] == in)
				out = 26 * 2 + 10 + 1;
			else
				return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}


	// Base 64 encode/decode
	static Result Base64Encode_(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer, uint8_t dummyChar, const char* encodeChars)
	{
		Result hr;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		for (; srcSize > 0; srcSize--)
		{
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3)
			{
				char_array_4[0] = (unsigned char)((char_array_3[0] & 0xfc) >> 2);
				char_array_4[1] = (unsigned char)(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
				char_array_4[2] = (unsigned char)(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));
				char_array_4[3] = (unsigned char)(char_array_3[2] & 0x3f);

				for (i = 0; (i < 4); i++)
				{
					hr = destBuffer.push_back((uint8_t)encodeChars[char_array_4[i]]);
					if (!hr.IsSuccess()) return hr;
				}
				i = 0;
			}

		}

		if (i)
		{
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (unsigned char)((char_array_3[0] & 0xfc) >> 2);
			char_array_4[1] = (unsigned char)(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
			char_array_4[2] = (unsigned char)(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));
			char_array_4[3] = (unsigned char)(char_array_3[2] & 0x3f);

			for (j = 0; (j < i + 1); j++)
			{
				hr = destBuffer.push_back((uint8_t)encodeChars[char_array_4[j]]);
				if (!hr.IsSuccess()) return hr;
			}

			if (dummyChar != '\0')
			{
				while ((i++ < 3))
				{
					hr = destBuffer.push_back((uint8_t)'=');
					if (!hr.IsSuccess()) return hr;
				}
			}
		}


		return hr;
	}


	static Result Base64Decode_(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t> &destBuffer, uint8_t dummyChar, const char* encodeChars)
	{
		Result hr;
		int in_len = (int)srcSize;
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];

		while (in_len-- && (bytes_to_decode[in_] != dummyChar))
		{
			hr = Base64_DecodeChar(bytes_to_decode[in_], char_array_4[i++], encodeChars);
			if (!hr.IsSuccess()) return hr;

			in_++;
			if (i == 4)
			{
				char_array_3[0] = (unsigned char)((char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4));
				char_array_3[1] = (unsigned char)(((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2));
				char_array_3[2] = (unsigned char)(((char_array_4[2] & 0x3) << 6) + char_array_4[3]);

				for (i = 0; (i < 3); i++)
				{
					hr = destBuffer.push_back((uint8_t)char_array_3[i]);
					if (!hr.IsSuccess()) return hr;
				}
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			char_array_3[0] = (unsigned char)((char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4));
			char_array_3[1] = (unsigned char)(((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2));
			char_array_3[2] = (unsigned char)(((char_array_4[2] & 0x3) << 6) + char_array_4[3]);

			for (j = 0; (j < i - 1); j++)
			{
				hr = destBuffer.push_back((uint8_t)char_array_3[j]);
				if (!hr.IsSuccess()) return hr;
			}
		}

		return hr;
	}


	Result Base64Encode(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer, uint8_t dummyChar)
	{
		return Base64Encode_(srcSize, bytes_to_encode, destBuffer, dummyChar, g_Crypto_Base64_chars);
	}

	Result Base64Decode(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t> &destBuffer, uint8_t dummyChar)
	{
		return Base64Decode_(srcSize, bytes_to_decode, destBuffer, dummyChar, g_Crypto_Base64_chars);
	}


	Result Base64URLEncode(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer, uint8_t dummyChar)
	{
		return Base64Encode_(srcSize, bytes_to_encode, destBuffer, dummyChar, g_Crypto_Base64URL_chars);
	}

	Result Base64URLDecode(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t> &destBuffer, uint8_t dummyChar)
	{
		return Base64Decode_(srcSize, bytes_to_decode, destBuffer, dummyChar, g_Crypto_Base64URL_chars);
	}


}
} // namespace SF

