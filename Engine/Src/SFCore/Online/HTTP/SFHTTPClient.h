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

namespace SF
{
    namespace Log
    {
        extern LogChannel HTTP;
    }



    // HTTP request wrapper
    class HTTPClient : public SharedObject
    {
    public:

        using ResultBuffer = StaticArray<uint8_t, 20 * 1024>;

        using ResultCallback = std::function<void(HTTPClient*)>;

    public:
        HTTPClient();
        virtual ~HTTPClient();

        const String& GetResultContentType() const { return m_ResultContentType; }
        const Array<uint8_t>& GetResultContent() const { return m_HTTPResult; }
        Result GetResultCode() const { return m_Result; }

        void SetMethod(bool bIsGet) { m_bIsGetMethod = bIsGet; }
        bool IsGetMethod() const { return m_bIsGetMethod; }

        void SetVerifyPeer(bool bVerify) { m_bIsVerifyPeer = bVerify; }
        bool IsVerifyPeer() const { return m_bIsVerifyPeer; }

        bool IsCompleted() const { return m_bIsCompleted; }
        bool HasBeenRequested() const { return m_bRequested; }

        void SetURL(const String& url);
        const String& GetURL() const { return m_URL; }

        // Set post field data
        virtual Result SetPostFieldData(const Array<const char>& postFieldData) { return ResultCode::NOT_IMPLEMENTED; }

        // Add header entry
        virtual Result AddHeader(const char* headerEntry) { return ResultCode::NOT_IMPLEMENTED; }

        // Send HTTP request
        virtual Result SendRequest() { return ResultCode::NOT_IMPLEMENTED; }

        // Set OnFinished callback
        void SetOnFinishedCallback(const ResultCallback& onFinished) { m_ResultCallback = onFinished; }

        // result callback
        virtual void OnFinished()
        {
            if (m_ResultCallback)
            {
                m_ResultCallback(this);
            }
        }

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

        // Request has been sent
        bool m_bRequested = false;

        // Operation result
        Result m_Result;

        // Result callback
        ResultCallback m_ResultCallback;
    };

    using HTTPClientPtr = SharedPointerT<HTTPClient>;


}

