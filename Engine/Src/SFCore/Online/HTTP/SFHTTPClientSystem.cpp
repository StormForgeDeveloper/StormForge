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
    }

    HTTPClientPtr HTTPClientSystem::CreateHTTPClient()
    {
        HTTPClient* pClient = CreateHTTPClientInternal();
        m_HTTPClientManager.RegisterSharedObject(pClient);
        return pClient;
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
