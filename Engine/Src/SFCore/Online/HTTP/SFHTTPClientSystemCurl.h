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
#include "Online/HTTP/SFHTTPClientSystem.h"

#include "curl/curl.h"

namespace SF
{
    class HTTPClientCurl;

    namespace Log
    {
        extern LogChannel Curl;
    }

    namespace HTTPCurlImpl
    {
        // Convert Curl code to Result
        Result CurlCodeToResult(CURLcode code);

        // Curl log callback
        int CurlLogCB(CURL* handle,
            curl_infotype type,
            char* data,
            size_t size,
            void* clientp);
    }


    class HTTPClientSystemCurl : public HTTPClientSystem
    {
    private:

        using super = HTTPClientSystem;

        // Curl multi handle
        CURLM* m_hMulti{};

        // Managed instances
        std::unordered_map<CURL*, SharedPointerT<HTTPClientCurl>> m_Managed;

        // new pending handles
        CircularPageQueue<SharedPointerAtomicT<HTTPClientCurl>> m_PendingAdd;


    public:
        HTTPClientSystemCurl();
        virtual ~HTTPClientSystemCurl();

        // Create Http client
        virtual HTTPClient* CreateHTTPClientInternal() override;

        // add request
        void AddRequest(HTTPClientCurl* httpClient);

        // Tick update
        virtual void TickUpdate() override;

        // Tick update on game thread
        //virtual void TickGameUpdate() override;

    private:

        // Update curl event
        void UpdateCurlEvent();

        // set finished for the client
        void SetFinished(HTTPClientCurl* httpClientPtr, Result hr);

        // called when HTTPClient is released and going to destroyed
        void OnHTTPClientDestroy(HTTPClientCurl* pHTTPClient);
    };


}

