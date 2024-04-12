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
            const char* data{};
            int flags{};
            ERR_get_error_line_data(&file, &line, &data, &flags);

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
MIIDpzCCAo+gAwIBAgIUdDMmR7hUsJg4FYqdm5uGNs7qiMwwDQYJKoZIhvcNAQEL\n\
BQAwPzELMAkGA1UEBhMCS1IxDjAMBgNVBAgMBUtvcmVhMQ8wDQYDVQQHDAZCcmF2\n\
ZXMxDzANBgNVBAsMBkJyYXZlczAeFw0yNDA0MTEyMjA0MjBaFw0zNDA0MDkyMjA0\n\
MjBaMD8xCzAJBgNVBAYTAktSMQ4wDAYDVQQIDAVLb3JlYTEPMA0GA1UEBwwGQnJh\n\
dmVzMQ8wDQYDVQQLDAZCcmF2ZXMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n\
AoIBAQDFfBefHb2sn7o7819fjeRxj/UU4yFx0QdLyj9eMno3b4BhRNGwCQGQbIBv\n\
wq3hY0J5kJe3r4ea1qsNcrEWwxnf97CLEUxmjmGLEgUmN0/vv0t7h29SlumewuM7\n\
fiSRxVP/mvdHbgUOdzut4qITP61L7PE65EErSblFyp7+YVX2pKv8eX3laV5OkiSX\n\
fDf95ZmP8DQPTjD2MpH2Z2lYtDP552RXgZP8ienyj1Y8JhmXcHdAC07qk5WTKcSy\n\
OthVpRyXIjEZqEPBq54JSXFfDHFNjC9jQJY0ylc2FPWOTULEcQdzBgn+tSilvlKx\n\
K6u+qxGTUJX9O4qcvTrPtt7r2DWDAgMBAAGjgZowgZcwCQYDVR0TBAIwADALBgNV\n\
HQ8EBAMCBeAwXgYDVR0RBFcwVYIVYXBwaHViLnN0b3JtZm9yZ2UuYXJ0ghAqLnN0\n\
b3JtZm9yZ2UuYXJ0ghAqLmZpc2hpbmctb24uY29tggxkZXYua2tvbC5jb22HBMCo\n\
AFSHBMCoAFwwHQYDVR0OBBYEFLg+CbN6kg0qrMUSuH7GZMtRsMcQMA0GCSqGSIb3\n\
DQEBCwUAA4IBAQBQQBUOStUOklgdQKohqDABUTa8x1J3kQs8Mneqa7+SzeQ97nZp\n\
Fgo3G4xfAIVv8kUrweocc1G+ymPZgiFDDxcCmvcui6l8tRQtIFCGcS6kQ3TeVJCL\n\
5dmUD3XJz57J7aaIGg3GuuLrf9AUVLgjsPtIixPL1/Xe6dIAC4jNMon4FlfJx8ia\n\
2CJFP2/Dng2Zbyrhft7cYi6wd8oLRLfLKPQoqdRtzJfuskOPb6f9E/qcMaHvE2QG\n\
w20kfMhTJiGXfOc+0BCpx0rvoaP0njEcteVIXZ748U+1BcxJxwayfXbQTXRFf+pk\n\
/3+b26rPiW2HJJRLPl0MB9/+J5EktwpIHM6n\n\
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
