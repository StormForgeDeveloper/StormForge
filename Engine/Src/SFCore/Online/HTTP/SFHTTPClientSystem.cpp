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
        LogChannel HTTP("HTTP", LogOutputType::Info);
    }

    namespace Service
    {
        ServiceInstance<HTTPClientSystem> HTTP;
    }


    HTTPClientSystem::HTTPClientSystem()
        : m_HTTPClientManager(GetSystemHeap())
        , m_PendingEvent(GetSystemHeap())
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
        Service::HTTP = new(GetSystemHeap()) HTTPClientSystemCurl;

        static const char* SelfSignedCert = 
"-----BEGIN CERTIFICATE-----\n\
MIIDlDCCAnygAwIBAgIUJAp0wrANOLgW3OuKCD1JY7Z0S3QwDQYJKoZIhvcNAQEL\
BQAwPzELMAkGA1UEBhMCS1IxDjAMBgNVBAgMBUtvcmVhMQ8wDQYDVQQHDAZCcmF2\
ZXMxDzANBgNVBAsMBkJyYXZlczAeFw0yNDA0MTMyMzM5NTBaFw0zNDA0MTEyMzM5\
NTBaMD8xCzAJBgNVBAYTAktSMQ4wDAYDVQQIDAVLb3JlYTEPMA0GA1UEBwwGQnJh\
dmVzMQ8wDQYDVQQLDAZCcmF2ZXMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\
AoIBAQCoBOd06OBePJUd0rkCPmdEbEiis7Jk/9kxHPq+0jihIiKkG3lYWv58wedG\
iQAigGYS24x0Fg/9GPlLpEqxHVn4vTVVZKKlmcnTbP5RIvTBYvY9jzwJdMsIRhoe\
BXeZ4/F8Rc8PCeyNbWwFSpab3aK1hpEYjOXJZIcE2xIaZMvJi+yKhg33DYjTfoqu\
S/+mZ/jWfUOnGt3PzsFe3Xu7oEdbkAYfKsWXgX8NdjPfjo9hvlFW/yKjpSLZD+yN\
IFh+HvvjVoAM5n/b1jHHi5CoPPeY43mvVf2oDUa+DD1x1x2K7K7Jjg4tQDvPe3kH\
XRu5c7v7lBEqLpVOLo33NIlTA+UVAgMBAAGjgYcwgYQwCQYDVR0TBAIwADALBgNV\
HQ8EBAMCBeAwSwYDVR0RBEQwQoIQKi5zdG9ybWZvcmdlLmFydIIQKi5maXNoaW5n\
LW9uLmNvbYIKKi5ra29sLmNvbYcEwKgAVIcEwKgAVYcEwKgAXDAdBgNVHQ4EFgQU\
I3QbVJSVGLlZVTCISozQWkInoBswDQYJKoZIhvcNAQELBQADggEBAGznlYUmxxxp\
7d8H6E2cO40t7yOOfY+f4XgkHymz6dilAaCS+gHQmX48zqZ7nUm18imc4wWCnIdW\
x4hVse6yYbzoGFfJiucqcC1HDyLBVSV9YUcmcytcA7m0I3vBUtAF5Klu7Aqaxeby\
00oFEbiMr16gYZcwM0Ac2hhloOSkweFKGUIoa4+p/0Bg5ct3OSFfCJw1pnSgHtwh\
S5rSPguuEgBTsacinIzkVE6Ttql/thKNz/vntQbw4wmMh3iLnor4iUAGS0hENgFj\
w7WQzWNIexoxAlvTwO6Ai+jHz/vJsSWhyCUfC4BEFruznlAM8CzZ1nOfKJGrsVjI\
om8DoC7cXOw=\n\
-----END CERTIFICATE-----";

        Service::HTTP->AddTrustedCert(SelfSignedCert);

		return super::InitializeComponent();
	}

    void HTTPClientComponent::DeinitializeComponent()
    {
        HTTPClientSystem* pSystem = *Service::HTTP;
        Service::HTTP = nullptr;

        if (pSystem != *Service::HTTP)
        {
            IHeap::Delete(pSystem);
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
