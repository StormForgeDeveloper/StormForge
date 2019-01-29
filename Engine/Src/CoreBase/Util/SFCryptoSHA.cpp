////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SHA256 hash
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "openssl/sha.h"



namespace SF {
namespace Util {
	

	// SHA 256 hashing
	Result SHA256Hash(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer)
	{
		destBuffer.resize(SHA256_DIGEST_LENGTH);

		SHA256_CTX sha256;
		if (SHA256_Init(&sha256) == 0)
			return ResultCode::FAIL;

		if (SHA256_Update(&sha256, bytes_to_encode, srcSize) == 0)
			return ResultCode::FAIL;

		if (SHA256_Final(destBuffer.data(), &sha256) == 0)
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


}
} // namespace SF

