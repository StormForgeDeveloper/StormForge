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
#include "Online/SFHTTPClient.h"
#include "Util/SFTrace.h"
#include "ResultCode/SFResultCodeLibrary.h"

namespace SF
{
    namespace Log
    {
        LogChannel HTTP("HTTP", LogOutputType::Info);
    }

    namespace HTTPClientImpl
    {

        Result CurlCodeToResult(CURLcode code)
        {
            switch (code)
            {
            case CURLE_OK:							return ResultCode::SUCCESS;
            case CURLE_UNSUPPORTED_PROTOCOL:		return ResultCode::HTTP_UNSUPPORTED_PROTOCOL;
            case CURLE_FAILED_INIT:					return ResultCode::HTTP_FAILED_INIT;
            case CURLE_URL_MALFORMAT:				return ResultCode::HTTP_URL_MALFORMAT;
            case CURLE_NOT_BUILT_IN:				return ResultCode::HTTP_NOT_BUILT_IN;
            case CURLE_COULDNT_RESOLVE_PROXY:		return ResultCode::HTTP_COULDNT_RESOLVE_PROXY;
            case CURLE_COULDNT_RESOLVE_HOST:		return ResultCode::HTTP_COULDNT_RESOLVE_HOST;
            case CURLE_COULDNT_CONNECT:				return ResultCode::HTTP_COULDNT_CONNECT;
            case CURLE_HTTP_POST_ERROR:				return ResultCode::HTTP_HTTP_POST_ERROR;
            case CURLE_SSL_ENGINE_NOTFOUND:			return ResultCode::HTTP_SSL_ENGINE_NOTFOUND;
            case CURLE_SSL_ENGINE_SETFAILED:		return ResultCode::HTTP_SSL_ENGINE_SETFAILED;
            case CURLE_SEND_ERROR:					return ResultCode::HTTP_SEND_ERROR;
            case CURLE_RECV_ERROR:					return ResultCode::HTTP_RECV_ERROR;
            case CURLE_USE_SSL_FAILED:				return ResultCode::HTTP_USE_SSL_FAILED;
            case CURLE_NO_CONNECTION_AVAILABLE:		return ResultCode::HTTP_NO_CONNECTION_AVAILABLE;
            case CURLE_SSL_CONNECT_ERROR:           return ResultCode::HTTP_SSL_CONNECT_ERROR;
            default:
                SFLog(System, Error, "Unknown CURL error:{0}", int(code));
                return ResultCode::UNEXPECTED;
            };
        }

    }

    HTTPClient::HTTPClient()
    {
    }

    HTTPClient::~HTTPClient()
    {
    }

    void HTTPClient::SetURL(const String& url)
    {
        m_URL = url;
    }




    HTTPClientCurl::HTTPClientCurl()
    {
    }

    HTTPClientCurl::~HTTPClientCurl()
    {
        if (m_Curl)
        {
            curl_easy_cleanup(m_Curl);
            m_Curl = nullptr;
        }

        if (m_Headers)
        {
            curl_slist_free_all(m_Headers);
        }

    }

    int HTTPClientCurl::ResultWriter(char* data, size_t size, size_t nmemb, void* param)
    {
        if (param == nullptr) return 0;

        auto* stream = (ResultBuffer*)param;

        stream->push_back(size * nmemb, (uint8_t*)data);

        return (int)(size * nmemb);
    }

    int HTTPClientCurl::CurlLogCB(CURL* handle,
        curl_infotype type,
        char* data,
        size_t size,
        void* clientp)
    {
        static const char* TypeNames[] = {
            "LINFO_TEXT",
            "CURLINFO_HEADER_IN",    /* 1 */
            "CURLINFO_HEADER_OUT",   /* 2 */
            "CURLINFO_DATA_IN",      /* 3 */
            "CURLINFO_DATA_OUT",     /* 4 */
            "CURLINFO_SSL_DATA_IN",  /* 5 */
            "CURLINFO_SSL_DATA_OUT", /* 6 */
        };
        const char* typeName = "Unknown";
        if (int(type) >= 0 && int(type) < CURLINFO_END)
        {
            typeName = TypeNames[int(type)];
        }

        SFLog(HTTP, Custom1, "CURL: {0}:{1}", typeName, data);

        return 0;
    }

    Result HTTPClientCurl::SetPostFieldData(const Array<const char>& postFieldData)
    {
        Result hr;

        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_POSTFIELDSIZE, postFieldData.size());
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_POSTFIELDS, (const char*)postFieldData.data());
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        return hr;
    }

    Result HTTPClientCurl::AddHeader(const char* headerEntry)
    {
        Result hr;

        defCheckMem(m_Headers = curl_slist_append(m_Headers, headerEntry));
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_HTTPHEADER, m_Headers);
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        return hr;
    }

    Result HTTPClientCurl::ProcessRequest()
    {
        ScopeContext hr([&](Result hr)
            {
                m_bIsCompleted = true;
                m_Result = hr;
            });

        if (m_bRequested)
        {
            return hr;
        }

        m_bRequested = true;

        m_HTTPResult.Clear();

        SFLog(System, Debug, "HTTP request. url:{0}, method:{1}", m_URL, IsGetMethod());

        m_Curl = curl_easy_init();
        if (m_Curl != nullptr)
        {
            m_CurlResult = curl_easy_setopt(GetCURL(), CURLOPT_WRITEDATA, &m_HTTPResult);
            defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));
            m_CurlResult = curl_easy_setopt(GetCURL(), CURLOPT_WRITEFUNCTION, &HTTPClientCurl::ResultWriter);
            defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));
        }
        else
        {
            m_CurlResult = CURLE_FAILED_INIT;
            defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));
        }

        // Debug logging
        curl_easy_setopt(GetCURL(), CURLOPT_VERBOSE, 1);
        curl_easy_setopt(GetCURL(), CURLOPT_DEBUGFUNCTION, &HTTPClientCurl::CurlLogCB);


        m_CurlResult = curl_easy_setopt(GetCURL(), CURLOPT_HTTPGET, IsGetMethod() ? 1 : 0);
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_URL, (const char*)m_URL);
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        // TODO: need to have root certificate list
        // for release build peer also need to be turned off
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYPEER, false);
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYHOST, 0L);
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        m_CurlResult = curl_easy_perform(GetCURL());
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        char* resultString = nullptr;
        m_CurlResult = curl_easy_getinfo(GetCURL(), CURLINFO_CONTENT_TYPE, &resultString);
        defCheck(HTTPClientImpl::CurlCodeToResult(m_CurlResult));

        Service::LogModule->Flush();
        m_ResultContentType = resultString;

        return hr;
    }
}
