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

#include "openssl/sha.h"
#include "openssl/evp.h"

namespace SF {
namespace Util {
	

	// SHA 256 hashing
	Result SHA256Hash(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer)
	{
		destBuffer.resize(SHA256_DIGEST_LENGTH);

        const EVP_MD* md = EVP_get_digestbyname("SHA256");
        if (md == nullptr)
        {
            return ResultCode::NOT_SUPPORTED;
        }

        EVP_MD_CTX* context = EVP_MD_CTX_create();
        if (context == nullptr)
        {
            return ResultCode::OUT_OF_MEMORY;
        }

        int iRet = EVP_DigestInit_ex(context, md, nullptr);
        if (iRet == 0)
        {
            return ResultCode::FAIL;
        }

        iRet = EVP_DigestUpdate(context, bytes_to_encode, srcSize);
        if (iRet == 0)
        {
            return ResultCode::FAIL;
        }

        uint md_len{};
        iRet = EVP_DigestFinal_ex(context, destBuffer.data(), &md_len);
        if (iRet == 0)
        {
            return ResultCode::FAIL;
        }


		//SHA256_CTX sha256;
		//if (SHA256_Init(&sha256) == 0)
		//	return ResultCode::FAIL;

		//if (SHA256_Update(&sha256, bytes_to_encode, srcSize) == 0)
		//	return ResultCode::FAIL;

		//if (SHA256_Final(destBuffer.data(), &sha256) == 0)
		//	return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

}
} // namespace SF

