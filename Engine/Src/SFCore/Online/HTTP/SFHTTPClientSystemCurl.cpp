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
    namespace Log
    {
        // Enable debug channel to print out curl internal logs
        LogChannel Curl("Curl", LogOutputType::Info);
    }

    namespace HTTPCurlImpl
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
            case CURLE_BAD_FUNCTION_ARGUMENT:       return ResultCode::HTTP_BAD_FUNCTION_ARGUMENT;
            default:
                SFLog(System, Error, "Unknown CURL error:{0}", int(code));
                return ResultCode::UNEXPECTED;
            };
        }

        Result CurlCodeToResult(CURLMcode code)
        {
            switch (code)
            {
            case CURLM_OK: return ResultCode::SUCCESS;
            case CURLM_CALL_MULTI_PERFORM: return ResultCode::HTTP_CALL_MULTI_PERFORM;// please call curl_multi_perform() or curl_multi_socket*() soon
            case CURLM_BAD_HANDLE: return ResultCode::HTTP_BAD_HANDLE; // the passed-in handle is not a valid CURLM handle
            case CURLM_BAD_EASY_HANDLE: return ResultCode::HTTP_BAD_EASY_HANDLE; // an easy handle was not good/valid
            case CURLM_OUT_OF_MEMORY: return ResultCode::OUT_OF_MEMORY;
            case CURLM_INTERNAL_ERROR: return ResultCode::HTTP_INTERNAL_ERROR; // this is a libcurl bug
            case CURLM_BAD_SOCKET: return ResultCode::HTTP_BAD_SOCKET; // the passed in socket argument did not match
            case CURLM_UNKNOWN_OPTION: return ResultCode::HTTP_UNKNOWN_OPTION; // curl_multi_setopt() with unsupported option
            case CURLM_ADDED_ALREADY: return ResultCode::HTTP_ADDED_ALREADY; // an easy handle already added to a multi handle was attempted to get added - again
            case CURLM_RECURSIVE_API_CALL: return ResultCode::HTTP_RECURSIVE_API_CALL; // an api function was called from inside a callback
            case CURLM_WAKEUP_FAILURE: return ResultCode::HTTP_WAKEUP_FAILURE; // wakeup is unavailable or failed
            case CURLM_BAD_FUNCTION_ARGUMENT: return ResultCode::HTTP_BAD_FUNCTION_ARGUMENT; // function called with a bad parameter
            case CURLM_ABORTED_BY_CALLBACK: return ResultCode::HTTP_ABORTED_BY_CALLBACK; // 
            case CURLM_UNRECOVERABLE_POLL: return ResultCode::HTTP_UNRECOVERABLE_POLL; //
            default:
                SFLog(HTTP, Error, "UnknownErrorCode: {0}", int(code));
                return ResultCode::UNEXPECTED;
            }
        }


        int CurlLogCB(CURL* handle,
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

            std::string strData(data, data + size);
            switch (type)
            {
            case CURLINFO_TEXT:
                SFLog(Curl, Debug, "{0}:{1}", typeName, strData);
                break;
            case CURLINFO_HEADER_IN:
                SFLog(Curl, Debug, "{0}:{1}", typeName, strData);
                break;
            case CURLINFO_HEADER_OUT:
                SFLog(Curl, Debug, "{0}:{1}", typeName, strData);
                break;
            case CURLINFO_DATA_IN:
                SFLog(Curl, Debug1, "{0}:{1}", typeName, strData);
                break;
            case CURLINFO_DATA_OUT:
                SFLog(Curl, Debug1, "{0}:{1}", typeName, strData);
                break;
            case CURLINFO_SSL_DATA_IN:
                SFLog(Curl, Debug4, "{0}:{1}", typeName, strData);
                break;
            case CURLINFO_SSL_DATA_OUT:
                SFLog(Curl, Debug4, "{0}:{1}", typeName, strData);
                break;
            default:
                SFLog(Curl, Debug5, "{0}:{1}", typeName, strData);
                break;
            }

            return 0;
        }

    }


    HTTPClientSystemCurl::HTTPClientSystemCurl()
        : m_PendingAdd(GetSystemHeap())
    {
        m_hMulti = curl_multi_init();
        curl_multi_setopt(m_hMulti, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);

        m_HTTPClientManager.SetOnDestroyObjectEventHandler([this](SharedObject* pObj)
            {
                OnHTTPClientDestroy(static_cast<HTTPClientCurl*>(pObj));
            });


    }

    HTTPClientSystemCurl::~HTTPClientSystemCurl()
    {
        if (m_hMulti)
        {
            curl_multi_cleanup(m_hMulti);
        }
    }

    HTTPClient* HTTPClientSystemCurl::CreateHTTPClientInternal()
    {
        return new(GetSystemHeap()) HTTPClientCurl(this);
    }

    void HTTPClientSystemCurl::AddRequest(HTTPClientCurl* httpClient)
    {
        m_PendingAdd.Enqueue(httpClient);
    }

    void HTTPClientSystemCurl::TickUpdate()
    {
        if (m_hMulti == nullptr)
            return;

        // process pending add
        SharedPointerAtomicT<HTTPClientCurl> httpClient;
        while (m_PendingAdd.Dequeue(httpClient))
        {
            SharedPointerT<HTTPClientCurl> httpClientPtr = Forward<SharedPointerT<HTTPClientCurl>>(httpClient);
            auto itFound = m_Managed.find(httpClientPtr->GetCURL());
            if (itFound == m_Managed.end())
            {
                auto insertRes = m_Managed.insert(std::make_pair(httpClientPtr->GetCURL(), httpClientPtr));
                if (insertRes.second)
                {
                    CURLMcode curlResult = curl_multi_add_handle(m_hMulti, httpClientPtr->GetCURL());
                    Result multiResult = HTTPCurlImpl::CurlCodeToResult(curlResult);
                    if (multiResult.IsFailure())
                    {
                        SFLog(HTTP, Error, "curl_multi_add_handle failure, hr:{0}", multiResult);
                        m_Managed.erase(insertRes.first);

                        SetFinished(httpClientPtr.get(), multiResult);
                    }
                }
                else
                {
                    SetFinished(httpClientPtr.get(), ResultCode::UNEXPECTED);
                }
            }
        }

        int runningCount = 0;
        Result multiResult;
        // update multi
        if (m_Managed.size() > 0)
        {

            CURLMcode curlResult = curl_multi_perform(m_hMulti, &runningCount);
            multiResult = HTTPCurlImpl::CurlCodeToResult(curlResult);
            if (multiResult.IsFailure())
            {
                SFLog(HTTP, Error, "curl_multi_perform failure, hr:{0}", multiResult);
            }
            else if (runningCount)
            {
                // wait for activity, timeout or "nothing"
                curlResult = curl_multi_poll(m_hMulti, NULL, 0, 1000, NULL);
                multiResult = HTTPCurlImpl::CurlCodeToResult(curlResult);
            }

        }

        UpdateCurlEvent();

        if (multiResult.IsSuccess()
            && runningCount == 0
            && m_Managed.size() > 0)
        {
            // This shouldn't happen, but if it does, clean up whatever left
            SFLog(HTTP, Error, "curl finished all job, but there are {0} managed requestes. force cleaning up", m_Managed.size());

            for (auto& itManaged : m_Managed)
            {
                SetFinished(itManaged.second.get(), ResultCode::IO_CANCELED);
            }
            m_Managed.clear();
        }

        super::TickUpdate();
    }

    void HTTPClientSystemCurl::UpdateCurlEvent()
    {
        if (m_hMulti == nullptr)
            return;

        CURLMsg* msg{};
        int queued{};
        while (true)
        {
            msg = curl_multi_info_read(m_hMulti, &queued);
            if (msg == nullptr)
                break;

            if (msg->msg == CURLMSG_DONE)
            {
                // a transfer ended
                auto itFound = m_Managed.find(msg->easy_handle);
                if (itFound != m_Managed.end())
                {
                    SharedPointerT<HTTPClientCurl> httpClient = itFound->second;
                    curl_multi_remove_handle(m_hMulti, msg->easy_handle);
                    m_Managed.erase(itFound);

                    SetFinished(httpClient.get(), msg->data.result);
                }
            }
        }
    }

    void HTTPClientSystemCurl::SetFinished(HTTPClientCurl* httpClient, Result hr)
    {
        if (!httpClient->IsCompleted())
        {
            httpClient->SetFinished(hr);
            m_PendingEvent.Enqueue(httpClient);
        }
    }

    void HTTPClientSystemCurl::OnHTTPClientDestroy(HTTPClientCurl* pHTTPClient)
    {
        if (m_hMulti)
        {
            // make sure it won't be in manage
            if (m_Managed.erase(pHTTPClient->GetCURL()))
            {
                curl_multi_remove_handle(m_hMulti, pHTTPClient->GetCURL());
            }
        }
    }
}
