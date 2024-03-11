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
#include "Online/HTTP/SFHTTPClientCurl.h"
#include "Online/HTTP/SFHTTPClientSystemCurl.h"
#include "Util/SFTrace.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "openssl/ssl.h"

namespace SF
{

    HTTPClientCurl::HTTPClientCurl(HTTPClientSystemCurl* curlSystem)
        : m_CurlSystem(curlSystem)
    {
    }

    HTTPClientCurl::~HTTPClientCurl()
    {
        // Once m_Curl is allocated, the pointer should remain to the last
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

    CURLcode HTTPClientCurl::SSLCTXCallback(CURL* curl, void* sslctx, void* parm)
    {
        (void)curl;
        (void)parm;

        // Add additional trusted cert to the callback
        X509_STORE* cts = SSL_CTX_get_cert_store((SSL_CTX*)sslctx);

        for (STACK_OF(X509_INFO)* x509Stack : Service::HTTP->GetTrustedCerts())
        {
            for (int i = 0; i < sk_X509_INFO_num(x509Stack); i++)
            {
                X509_INFO* itmp = sk_X509_INFO_value(x509Stack, i);
                if (itmp->x509)
                {
                    X509_STORE_add_cert(cts, itmp->x509);
                }
                if (itmp->crl)
                {
                    X509_STORE_add_crl(cts, itmp->crl);
                }
            }
        }

        return CURLE_OK;
    }

    Result HTTPClientCurl::SetPostFieldData(const Array<const char>& postFieldData)
    {
        Result hr;

        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_POSTFIELDSIZE, postFieldData.size());
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_POSTFIELDS, (const char*)postFieldData.data());
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        return hr;
    }

    Result HTTPClientCurl::AddHeader(const char* headerEntry)
    {
        Result hr;

        defCheckMem(m_Headers = curl_slist_append(m_Headers, headerEntry));
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_HTTPHEADER, m_Headers);
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        return hr;
    }

    Result HTTPClientCurl::SendRequest()
    {
        ScopeContext hr([&](Result hr)
            {
                if (hr.IsFailure())
                {
                    SetFinished(hr);
                }
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
            defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));
            m_CurlResult = curl_easy_setopt(GetCURL(), CURLOPT_WRITEFUNCTION, &HTTPClientCurl::ResultWriter);
            defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));
        }
        else
        {
            m_CurlResult = CURLE_FAILED_INIT;
            defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));
        }

        // Debug logging
        curl_easy_setopt(GetCURL(), CURLOPT_VERBOSE, 1);
        curl_easy_setopt(GetCURL(), CURLOPT_DEBUGFUNCTION, &HTTPCurlImpl::CurlLogCB);

        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_HTTPGET, IsGetMethod() ? 1 : 0);
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_URL, (const char*)m_URL);
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        // for release build peer also need to be turned off
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYPEER, true);
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYHOST, 1L);
        defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        // Handle additional cert
        m_CurlResult = curl_easy_setopt(m_Curl, CURLOPT_SSL_CTX_FUNCTION, SSLCTXCallback);

        curl_easy_setopt(m_Curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);

        // client might want to have this setting, but not for server
        //curl_easy_setopt(m_Curl, CURLOPT_PIPEWAIT, 1L);

        if (m_CurlSystem)
        {
            m_CurlSystem->AddRequest(this);
        }
        else
        {
            m_CurlResult = curl_easy_perform(m_Curl);
            defCheck(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

            OnFinished();
        }

        return hr;
    }

    void HTTPClientCurl::OnFinished()
    {
        Result hr;

        char* resultString = nullptr;
        m_CurlResult = curl_easy_getinfo(m_Curl, CURLINFO_CONTENT_TYPE, &resultString);

        //Service::LogModule->Flush();
        m_ResultContentType = resultString;

        SetFinished(HTTPCurlImpl::CurlCodeToResult(m_CurlResult));

        super::OnFinished();
    }

    void HTTPClientCurl::SetFinished(Result hr)
    {
        if (!m_bIsCompleted)
        {
            m_bIsCompleted = true;
            m_Result = hr;
        }
    }

}
