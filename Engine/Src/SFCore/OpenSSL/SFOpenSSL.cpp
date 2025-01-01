////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : OpenSSL helper
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFResult.h"
#include "OpenSSL/SFOpenSSL.h"
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

namespace SF
{



    SFOpenSSL_BIO::SFOpenSSL_BIO(const BIO_METHOD* method)
    {
        m_BIO = BIO_new(method);
    }


    SFOpenSSL_BIO::~SFOpenSSL_BIO()
    {
        if (m_BIO)
        {
            BIO_free_all(m_BIO);
        }
    }


    const BUF_MEM* SFOpenSSL_BIO::GetMemBuffer() const
    {
        BUF_MEM* bufptr{};
        if (m_BIO)
        {
            BIO_get_mem_ptr(m_BIO, &bufptr);
        }
        return bufptr;
    }


    void SFOpenSSL_BIO::Flush()
    {
        if (m_BIO)
        {
            BIO_flush(m_BIO);
        }
    }

    void SFOpenSSL_BIO::AppendOutputChain(const BIO_METHOD* method)
    {
        BIO* BioChain = BIO_new(method);
        m_BIO = BIO_push(m_BIO, BioChain);
    }

    void SFOpenSSL_BIO::Write(const Array<uint8_t>& data)
    {
        if (m_BIO)
        {
            BIO_write(m_BIO, data.data(), static_cast<int>(data.size()));
        }
    }



    static_assert(SFOpenSSL_EVP_MD_CTX::MAX_MD_SIZE == EVP_MAX_MD_SIZE);

    SFOpenSSL_EVP_MD_CTX::SFOpenSSL_EVP_MD_CTX(const EVP_MD* md, ENGINE* impl)
    {
        m_Ctx = EVP_MD_CTX_create();
        EVP_DigestInit_ex(m_Ctx, md, impl);
    }


    SFOpenSSL_EVP_MD_CTX::~SFOpenSSL_EVP_MD_CTX()
    {
        if (m_Ctx)
        {
            EVP_MD_CTX_destroy(m_Ctx);
        }
    }


    void SFOpenSSL_EVP_MD_CTX::Flush(Array<uint8_t>& outDigest)
    {
        if (m_Ctx)
        {
            unsigned int digest_len = 0;
            outDigest.resize(EVP_MAX_MD_SIZE);
            EVP_DigestFinal_ex(m_Ctx, outDigest.data(), &digest_len);
            outDigest.resize(digest_len);
        }
    }

    void SFOpenSSL_EVP_MD_CTX::Write(const Array<const uint8_t>& data)
    {
        if (m_Ctx)
        {
            EVP_DigestUpdate(m_Ctx, data.data(), data.size());
        }
    }

}
