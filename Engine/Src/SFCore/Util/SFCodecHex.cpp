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
	

	static const char* g_Hex_Encode_Table = "0123456789ABCDEF";

	Result HEXEncode(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t>& destBuffer, uint8_t dummyChar)
	{
		Result hr;

		destBuffer.reserve(srcSize * 2);

		auto srcEnd = bytes_to_encode + srcSize;
		for (; srcEnd != bytes_to_encode;)
		{
			auto byteValue = *bytes_to_encode++;
			SFCheckResult(System, destBuffer.push_back(g_Hex_Encode_Table[((byteValue>>4) & 0xF)]));
			SFCheckResult(System, destBuffer.push_back(g_Hex_Encode_Table[(byteValue & 0xF)]));

			if (dummyChar)
			{
				SFCheckResult(System, destBuffer.push_back(dummyChar));
			}
		}

		return hr;
	}

	Result HEXDecode(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t>& destBuffer, uint8_t dummyChar)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}


}
} // namespace SF

