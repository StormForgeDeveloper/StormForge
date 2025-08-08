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

// root CA
"-----BEGIN CERTIFICATE-----\n\
MIIGmTCCBQGgAwIBAgIQWDnie1UiZJ1RTQ2id4/4cTANBgkqhkiG9w0BAQwFADBg\
MQswCQYDVQQGEwJHQjEYMBYGA1UEChMPU2VjdGlnbyBMaW1pdGVkMTcwNQYDVQQD\
Ey5TZWN0aWdvIFB1YmxpYyBTZXJ2ZXIgQXV0aGVudGljYXRpb24gQ0EgRFYgUjM2\
MB4XDTI1MDYxMDAwMDAwMFoXDTI2MDcxMTIzNTk1OVowIDEeMBwGA1UEAxMVYXBw\
aHViLnN0b3JtZm9yZ2UuYXJ0MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\
AQEAsWZW/FVzpqPffB4JYwytbv/pzWXz048at1X7FKQCiTmT0AI2HP6gcwTKkgzD\
7DLmFwzoM8rQ4BIyeLt8sFx/hjlN5uC6xs6eOhP4azNCAjLjJh1BGy8FeGUvFXnV\
QlSMl4dfkGrUYJcyxRsbht/fcCazr+Yd2EYWwmLfVpe3jlIbRJar3SqrTgJ7WF1n\
GJh7gAVGErQNThvCBrPP4VLQ5o85qw9GJhVaSLotygZD8Z2hXw7+lqXwDCQjKAvG\
d0Ac3Agm34/WNoNc+nRlHvuBe11Hu+XdLBaQPYtfr95FRlKT5DZpx6qjXxhPqNTT\
aABsX7aOGMgJIyqktAXqkk4JWQIDAQABo4IDDTCCAwkwHwYDVR0jBBgwFoAUaMAS\
FhgOr872h6YyV6NGUV3LBycwHQYDVR0OBBYEFNnZLxljhR82/B4h1I0bXgCRFTrT\
MA4GA1UdDwEB/wQEAwIFoDAMBgNVHRMBAf8EAjAAMB0GA1UdJQQWMBQGCCsGAQUF\
BwMBBggrBgEFBQcDAjBJBgNVHSAEQjBAMDQGCysGAQQBsjEBAgIHMCUwIwYIKwYB\
BQUHAgEWF2h0dHBzOi8vc2VjdGlnby5jb20vQ1BTMAgGBmeBDAECATCBhAYIKwYB\
BQUHAQEEeDB2ME8GCCsGAQUFBzAChkNodHRwOi8vY3J0LnNlY3RpZ28uY29tL1Nl\
Y3RpZ29QdWJsaWNTZXJ2ZXJBdXRoZW50aWNhdGlvbkNBRFZSMzYuY3J0MCMGCCsG\
AQUFBzABhhdodHRwOi8vb2NzcC5zZWN0aWdvLmNvbTCCAX4GCisGAQQB1nkCBAIE\
ggFuBIIBagFoAHYA2AlVO5RPev/IFhlvlE+Fq7D4/F6HVSYPFdEucrtFSxQAAAGX\
W2LTiQAABAMARzBFAiEAn6cWed4MPWhfo832c+I6FH57bk82aGEAQ9fZkPwIbgUC\
IBPuUgZEsIow3rd8Lb7a/qXrtaHHdLmoiDf7Qf+P/nifAHUArKswcGzr7IQx9BPS\
9JFfER5CJEOx8qaMTzwrO6ceAsMAAAGXW2LTUgAABAMARjBEAiA+oC8XoV1vWtLe\
1VXL3mk2EfNkAZWqTnxSfZq/4FHJmAIgVHKX9CVAeokwKnz3Wv/5+u+k01WchF+k\
qtOBAjipi/MAdwDXbX0Q0af1d8LH6V/XAL/5gskzWmXh0LMBcxfAyMVpdwAAAZdb\
YtNWAAAEAwBIMEYCIQD4fgpXMbllMC6xLiFQYCEpzeyV9VOAclhWIYXa+Ki0egIh\
AOfh3oWeneG5quYvXjybPfrUUxefjsNpNwL1Q+kM4fZxMDYGA1UdEQQvMC2CFWFw\
cGh1Yi5zdG9ybWZvcmdlLmFydIIUbG9jYWwuc3Rvcm1mb3JnZS5hcnQwDQYJKoZI\
hvcNAQEMBQADggGBAGzIRYkK7G7lNFjCiHZyvb++hkenRPvqjxwdjNI39/by2Aks\
6e38xvDkw3RVFc/G2ddPExqgZeqPSvgr4CVmwha5t0qTPOIlR8NPIb5j6hF14HyC\
lscIrKPGP79O50SbrkqYet6WJkkBcTcgJk88kACvMA2d/vCEPBX4RVUlBrSr0Vg1\
SoTIIYqjG5ETnjLig6onykh2coi+FszcOzAL6+2TW+CveLPNI++qkAVNHqY8PQd+\
bHXhJXLcdI7KS9xjL1iGGD2YgBdLLJqu1TnICrDPGHk31j2e8jcfX5kQ44vMdKse\
jONGWlM2V0uKxi9svP+iibSbgoiW1jyChMvS41bcvX5z03lRrkrMJthYhmljGi+x\
/pK5goKP5wM9G+sbyWsbe/j2wwJus5lmVfR0dNPRc8ki78ttwuvUe2WvLBcYe92l\
/ubF4CKQZ7VYYudHe4n4JTLIdC3/wGCIVtJ82Dl15a6oRPSf7iFXqyxJqtSs2K+o\
f4GDnDxe7GgAKXxxlw==\n\
-----END CERTIFICATE-----",

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
