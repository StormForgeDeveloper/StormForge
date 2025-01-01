////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : OpenSSl helper
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <stdint.h>
#include <openssl/types.h>

typedef struct bio_method_st BIO_METHOD;


namespace SF
{


    class SFOpenSSL_BIO
    {
    public:

        SFOpenSSL_BIO(const BIO_METHOD* method);

        ~SFOpenSSL_BIO();

        bool IsValid() const { return m_BIO; }
        operator BIO* () const { return m_BIO; }

        const BUF_MEM* GetMemBuffer() const;

        void Flush();

        void AppendOutputChain(const BIO_METHOD* method);

        void Write(const Array<uint8_t>& data);

    private:

        BIO* m_BIO{};
    };


    class SFOpenSSL_EVP_MD_CTX
    {
    public:
        static constexpr int MAX_MD_SIZE = 64;

        SFOpenSSL_EVP_MD_CTX(const EVP_MD* md, ENGINE* impl = nullptr);

        ~SFOpenSSL_EVP_MD_CTX();

        bool IsValid() const { return m_Ctx; }
        operator EVP_MD_CTX* () const { return m_Ctx; }

        void Flush(Array<uint8_t>& outDigest);

        void Write(const Array<const uint8_t>& data);

    private:

        EVP_MD_CTX* m_Ctx{};
    };

}
