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


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"

#ifdef SF_USE_MBEDTLS
#include "mbedtls/sha256.h"
#else // SF_USE_MBEDTLS
#include "openssl/sha.h"
#endif // SF_USE_MBEDTLS


namespace SF {
namespace Util {
	

	// SHA 256 hashing
	Result SHA256Hash(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer)
	{
#ifdef SF_USE_MBEDTLS
		mbedtls_sha256_context ctx2;

		destBuffer.resize(32);

		mbedtls_sha256_init(&ctx2);
		mbedtls_sha256_starts(&ctx2, 0); /* SHA-256, not 224 */

		mbedtls_sha256_update(&ctx2, bytes_to_encode, srcSize);

		mbedtls_sha256_finish(&ctx2, destBuffer.data());

		mbedtls_sha256_free(&ctx2);

		/* 0 here means use the full SHA-256, not the SHA-224 variant */
		//mbedtls_sha256(hello_buffer, hello_len, output1, 0);

#else // SF_USE_MBEDTLS
		destBuffer.resize(SHA256_DIGEST_LENGTH);

		SHA256_CTX sha256;
		if (SHA256_Init(&sha256) == 0)
			return ResultCode::FAIL;

		if (SHA256_Update(&sha256, bytes_to_encode, srcSize) == 0)
			return ResultCode::FAIL;

		if (SHA256_Final(destBuffer.data(), &sha256) == 0)
			return ResultCode::FAIL;

#endif // SF_USE_MBEDTLS
		return ResultCode::SUCCESS;
	}

}
} // namespace SF

