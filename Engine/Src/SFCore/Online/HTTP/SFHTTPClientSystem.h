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

#pragma once

#include "SFTypedefs.h"
#include "Online/HTTP/SFHTTPClient.h"
#include "Service/SFService.h"
#include "Object/SFSharedObjectManager.h"
#include "openssl/pem.h"

namespace SF
{
    namespace Log
    {
        extern LogChannel HTTP;
    }

    // HTTP request manager system
    class HTTPClientSystem
    {
    public:
        HTTPClientSystem();
        virtual ~HTTPClientSystem();

        // Create Http client
        HTTPClientPtr CreateHTTPClient();

        // Add X509 cert to OpenSSL CA list
        virtual Result AddTrustedCert(const String& certString);

        virtual const Array<STACK_OF(X509_INFO)*> GetTrustedCerts() const { return m_AdditionalCert; }

        // Tick update
        virtual void TickUpdate();

        // Tick update on game thread
        virtual void TickGameUpdate();

    protected:

        virtual HTTPClient* CreateHTTPClientInternal() { return nullptr; }

        // shared object manager, for released client management
        SharedObjectManager m_HTTPClientManager;

        // Finished HTTPCLients
        CircularPageQueue<SharedPointerAtomicT<HTTPClient>> m_PendingEvent;

        // 
        DynamicArray<STACK_OF(X509_INFO)*> m_AdditionalCert;
    };

    namespace Service
    {
        extern ServiceInstance<HTTPClientSystem> HTTP;
    }


		////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class HTTPClientComponent
	//

    class HTTPClientComponent : public LibraryComponent
    {
    public:

        using super = LibraryComponent;
        static constexpr StringCrc64 TypeName = "HTTPClientComponent";

    public:

        HTTPClientComponent();
        virtual ~HTTPClientComponent();

        virtual const StringCrc64& GetTypeName() const override { return TypeName; }

        virtual Result InitializeComponent() override;
        virtual void DeinitializeComponent() override;
        virtual void TickUpdate() override;

    };



}

