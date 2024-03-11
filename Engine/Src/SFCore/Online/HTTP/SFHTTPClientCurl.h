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
#include "Container/SFArray.h"
#include "Online/HTTP/SFHTTPClient.h"

#include "curl/curl.h"

namespace SF
{
    class HTTPClientSystemCurl;

    // Curl specialization
    class HTTPClientCurl : public HTTPClient
    {
    public:
        using super = HTTPClient;

        HTTPClientCurl(HTTPClientSystemCurl* curlSystem);
        virtual ~HTTPClientCurl();

        CURL* GetCURL() { return m_Curl; }
        CURLcode GetCURLResult() { return m_CurlResult; }

        // Set post field data
        virtual Result SetPostFieldData(const Array<const char>& postFieldData) override;

        // Add header entry
        virtual Result AddHeader(const char* headerEntry) override;

        // Send HTTP request
        virtual Result SendRequest() override;

        virtual void OnFinished() override;

        // Set result
        void SetFinished(Result hr);

    private:
        // Result writer
        static int ResultWriter(char* data, size_t size, size_t nmemb, void* param);

        // SSL context callback
        static CURLcode SSLCTXCallback(CURL* curl, void* sslctx, void* parm);

    protected:
        // Curl manager system
        HTTPClientSystemCurl* m_CurlSystem{};

        // curl
        CURL* m_Curl{};

        // curl header list
        curl_slist* m_Headers{};

        // curl result code
        CURLcode m_CurlResult = CURLE_OK;
    };

}

