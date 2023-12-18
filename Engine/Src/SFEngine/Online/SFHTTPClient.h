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
#include "Object/SFSharedObject.h"

#include "curl/curl.h"

namespace SF
{

    // HTTP request wrapper
    class HTTPClient : public SharedObject
    {
    public:

        typedef StaticArray<char, 20 * 1024> ResultBuffer;

    public:
        HTTPClient();
        virtual ~HTTPClient();

        const String& GetResultContentType() const { return m_ResultContentType; }
        const Array<char>& GetResultContent() const { return m_HTTPResult; }

        void SetMethod(bool bIsGet) { m_bIsGetMethod = bIsGet; }
        bool IsGetMethod() const { return m_bIsGetMethod; }

        void SetVerifyPeer(bool bVerify) { m_bIsVerifyPeer = bVerify; }
        bool IsVerifyPeer() const { return m_bIsVerifyPeer; }

        void SetURL(const String& url);
        const String& GetURL() const { return m_URL; }

        // Set post field data
        virtual Result SetPostFieldData(const Array<const char>& postFieldData) { return ResultCode::NOT_IMPLEMENTED; }

        // Add header entry
        virtual Result AddHeader(const char* headerEntry) { return ResultCode::NOT_IMPLEMENTED; }

        // Send HTTP request
        virtual Result ProcessRequest() { return ResultCode::NOT_IMPLEMENTED; }

    protected:
        // Result content type
        String m_ResultContentType;

        // HTTP query result
        ResultBuffer m_HTTPResult;

        // Request URL
        String m_URL;

        // Is get method
        bool m_bIsGetMethod = true;

        // Is verify peer cert?
        bool m_bIsVerifyPeer = true;

        // Is completed?
        bool m_bIsCompleted = false;

        // Operation result
        Result m_Result;
    };

    using HTTPClientPtr = SharedPointerT<HTTPClient>;

    class HTTPClientCurl : public HTTPClient
    {
    public:
        HTTPClientCurl();
        virtual ~HTTPClientCurl();

        CURL* GetCURL() { return m_Curl; }
        CURLcode GetCURLResult() { return m_CurlResult; }

        // Set post field data
        virtual Result SetPostFieldData(const Array<const char>& postFieldData) override;

        // Add header entry
        virtual Result AddHeader(const char* headerEntry);

        // Send HTTP request
        virtual Result ProcessRequest();

    private:
        static int ResultWriter(char* data, size_t size, size_t nmemb, void* param);

    protected:
        // curl
        CURL* m_Curl{};

        // curl header list
        curl_slist* m_Headers{};

        // curl result code
        CURLcode m_CurlResult = CURLE_OK;
    };

}

