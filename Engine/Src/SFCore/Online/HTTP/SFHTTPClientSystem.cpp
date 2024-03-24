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
        Result hr;
        BIO* cbio = BIO_new_mem_buf((void*)certString.data(), (int)certString.GetLength());
        STACK_OF(X509_INFO)* inf {};

        if (!cbio) {
            return ResultCode::UNEXPECTED;
        }

        inf = PEM_X509_INFO_read_bio(cbio, NULL, NULL, NULL);

        if (!inf) {
            BIO_free(cbio);
            return ResultCode::INVALID_FORMAT;
        }

        m_AdditionalCert.push_back(inf);

        BIO_free(cbio);

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
