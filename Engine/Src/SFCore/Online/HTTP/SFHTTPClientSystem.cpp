////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : HTTP client
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Online/HTTP/SFHTTPClient.h"
#include "Online/HTTP/SFHTTPClientSystem.h"
#include "Online/HTTP/SFHTTPClientSystemCurl.h"
#include "Util/SFTrace.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "openssl/types.h"
#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/pem.h"
#include "openssl/pem2.h"
#include "openssl/err.h"


namespace SF
{
    namespace Log
    {
        LogChannel HTTP("HTTP", ELogLevel::Info);
    }

    namespace Service
    {
        ServiceInstance<HTTPClientSystem> HTTP;
    }


    HTTPClientSystem::HTTPClientSystem()
    {
    }

    HTTPClientSystem::~HTTPClientSystem()
    {
        for (STACK_OF(X509_INFO)* x509Stack : m_AdditionalCert)
        {
            sk_X509_INFO_pop_free(x509Stack, X509_INFO_free);
        }
        m_AdditionalCert.Reset();
    }

    HTTPClientPtr HTTPClientSystem::CreateHTTPClient()
    {
        HTTPClient* pClient = CreateHTTPClientInternal();
        m_HTTPClientManager.RegisterSharedObject(pClient);
        return pClient;
    }

    Result HTTPClientSystem::AddTrustedCert(const String& certString)
    {
        BIO* cbio{};
        ScopeContext hr([this, &cbio](Result hr)
            {
                if (cbio)
                {
                    BIO_free(cbio);
                }

            });

        ERR_clear_error();

        cbio = BIO_new_mem_buf((void*)certString.data(), (int)certString.GetLength());
        STACK_OF(X509_INFO)* x509Stack {};

        if (!cbio) {
            return ResultCode::UNEXPECTED;
        }

        x509Stack = PEM_X509_INFO_read_bio(cbio, NULL, NULL, NULL);

        if (ERR_get_error() != 0)
        {
            const char* file{};
            int line{};
            ERR_peek_error_line(&file, &line);

            SFLog(HTTP, Error, "Failed to import cert string, file:{0}:{1}", file, line);

            return ResultCode::INVALID_FORMAT;
        }

        if (!x509Stack) {
            return ResultCode::INVALID_FORMAT;
        }

        if (sk_X509_INFO_num(x509Stack) == 0)
        {
            SFLog(HTTP, Error, "Failed to import cert string, empty cert data. possible format error");

            return ResultCode::INVALID_FORMAT;
        }

        m_AdditionalCert.push_back(x509Stack);

        return hr;
    }

    void HTTPClientSystem::TickUpdate()
    {
        m_HTTPClientManager.Update();
    }

    void HTTPClientSystem::TickGameUpdate()
    {
        SharedPointerAtomicT<HTTPClient> httpClient;
        while (m_PendingEvent.Dequeue(httpClient))
        {
            httpClient->OnFinished();
            httpClient.reset();
        }
    }
	
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class HTTPClientComponent
	//

	HTTPClientComponent::HTTPClientComponent()
		: LibraryComponent(TypeName, true)
	{
	}

	HTTPClientComponent::~HTTPClientComponent()
	{
	}

	Result HTTPClientComponent::InitializeComponent()
	{
        Result hr;

        Service::HTTP = new HTTPClientSystemCurl;

        static const char* SelfSignedCerts[] = {

// Selfsigned
"-----BEGIN CERTIFICATE-----\n\
MIIDlDCCAnygAwIBAgIUJrpHHMJyOMi3u1fP6Bi/9sbXu5swDQYJKoZIhvcNAQEL\
BQAwPzELMAkGA1UEBhMCS1IxDjAMBgNVBAgMBUtvcmVhMQ8wDQYDVQQHDAZCcmF2\
ZXMxDzANBgNVBAsMBkJyYXZlczAeFw0yNTAxMTUwNzU4MTVaFw0zNTAxMTMwNzU4\
MTVaMD8xCzAJBgNVBAYTAktSMQ4wDAYDVQQIDAVLb3JlYTEPMA0GA1UEBwwGQnJh\
dmVzMQ8wDQYDVQQLDAZCcmF2ZXMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\
AoIBAQCoBOd06OBePJUd0rkCPmdEbEiis7Jk/9kxHPq+0jihIiKkG3lYWv58wedG\
iQAigGYS24x0Fg/9GPlLpEqxHVn4vTVVZKKlmcnTbP5RIvTBYvY9jzwJdMsIRhoe\
BXeZ4/F8Rc8PCeyNbWwFSpab3aK1hpEYjOXJZIcE2xIaZMvJi+yKhg33DYjTfoqu\
S/+mZ/jWfUOnGt3PzsFe3Xu7oEdbkAYfKsWXgX8NdjPfjo9hvlFW/yKjpSLZD+yN\
IFh+HvvjVoAM5n/b1jHHi5CoPPeY43mvVf2oDUa+DD1x1x2K7K7Jjg4tQDvPe3kH\
XRu5c7v7lBEqLpVOLo33NIlTA+UVAgMBAAGjgYcwgYQwCQYDVR0TBAIwADALBgNV\
HQ8EBAMCBeAwSwYDVR0RBEQwQoIQKi5zdG9ybWZvcmdlLmFydIIQKi5maXNoaW5n\
LW9uLmNvbYIKKi5ra29sLmNvbYcEwKgAVIcEwKgAVYcEwKgAXDAdBgNVHQ4EFgQU\
I3QbVJSVGLlZVTCISozQWkInoBswDQYJKoZIhvcNAQELBQADggEBAGm39e6fMxUr\
YTVGfeW3C7gUmcczP+SJ4XdYOkGNBRrwmZpG25DZfbdjZvZHaPIy5+C3vqNlWlfw\
03OGORZULMqbEoSR3KFdl7+mT0GSH+qoSFRr11FL6oxDS2qb5DVo3G9Kla7kf9J/\
SDW4+0WuG91CHGarCFFuSxni0Afqc8iRZqFr6fFneF1y4LCyVPkei6zQClt3zBfw\
53puTsQukfMtG7ZN8Q+b5bYBX3uxOMBJzXErHHQp8k8Onl9CoVWnCM2oHDe+gyoo\
wTnDpv4r3wuSH/KdArkkWBMmXo1gFRwO7yp9NzV2CW9zYa3AptJafGh8c4hbGfK1\
OyGU210KPqc=\n\
-----END CERTIFICATE-----"

        };

        for (const char* SelfSignedCert : SelfSignedCerts)
        {
            defCheck(Service::HTTP->AddTrustedCert(SelfSignedCert));
        }

		defCheck(super::InitializeComponent());

        return hr;
	}

    void HTTPClientComponent::DeinitializeComponent()
    {
        HTTPClientSystem* pSystem = *Service::HTTP;
        Service::HTTP = nullptr;

        if (pSystem != *Service::HTTP)
        {
            delete (pSystem);
        }

        super::DeinitializeComponent();
    }

    void HTTPClientComponent::TickUpdate()
    {
        super::TickUpdate();

        Service::HTTP->TickUpdate();
        Service::HTTP->TickGameUpdate();
    }
}
