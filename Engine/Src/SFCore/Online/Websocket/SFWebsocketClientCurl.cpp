////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Websocket client with Curl
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "Util/SFString.h"
#include "Util/SFStringFormat.h"
#include "Online/Websocket/SFWebsocketClientCurl.h"



namespace SF
{
    namespace Log
    {
        LogChannel LogCurl("LogCurl", LogOutputType::Debug);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class WebsocketClientCurl
    //


    WebsocketClientCurl::WebsocketClientCurl(IHeap& heap)
        : m_ReceiveBuffer(heap)
        , m_RecvDeletates(heap)
    {
    }

    WebsocketClientCurl::~WebsocketClientCurl()
    {
        if (m_Headers)
        {
            curl_slist_free_all(m_Headers);
            m_Headers = nullptr;
        }
    }


    class WebsocketClientCurlImpl
    {
    public:

        static int WebsocketCurl_DebugFunc(CURL* handle,
            curl_infotype type,
            char* data,
            size_t size,
            void* userdata)
        {
            switch(type)
            {
            case CURLINFO_TEXT:
                SFLog(LogCurl, Log, "CURLINFO_TEXT:{0}", data);
                break;
            case CURLINFO_HEADER_IN:
                SFLog(LogCurl, Log, "CURLINFO_HEADER_IN");
                break;
            case CURLINFO_HEADER_OUT:
                SFLog(LogCurl, Log, "CURLINFO_HEADER_OUT");
                break;
            case CURLINFO_DATA_IN:
                SFLog(LogCurl, Log, "CURLINFO_DATA_IN");
                break;
            case CURLINFO_DATA_OUT:
                SFLog(LogCurl, Log, "CURLINFO_DATA_OUT");
                break;
            case CURLINFO_SSL_DATA_IN:
                SFLog(LogCurl, Log, "CURLINFO_SSL_DATA_IN");
                break;
            case CURLINFO_SSL_DATA_OUT:
                SFLog(LogCurl, Log, "CURLINFO_SSL_DATA_OUT");
                break;
            default:
                break;
            }

            return 0;
        }

        static inline bool HeaderHasPrefix(const char* buffer, const size_t buflen, const char* prefix)
        {
            const size_t prefixlen = strlen(prefix);
            if (buflen < prefixlen)
                return false;

            return StrUtil::StringCompairIgnoreCase(prefix, int(prefixlen), buffer, int(buflen));
        }

        static inline void SkipSpaceStart(const char** p_buffer, size_t* p_len)
        {
            const char* buffer = *p_buffer;
            size_t len = *p_len;

            while (len > 0 && isspace(buffer[0])) {
                buffer++;
                len--;
            }

            while (len > 0 && isspace(buffer[len - 1]))
                len--;

            *p_buffer = buffer;
            *p_len = len;
        }


        static void CheckAccept(WebsocketClientCurl* priv, const char* buffer, size_t len)
        {
            auto& wsStatus = priv->m_CurlStatus;
            wsStatus.Accepted = false;

            //if (len != sizeof(priv->accept_key) - 1) {
            //    SFLog(Websocket, Error, "expected %zd bytes, got %zd '%.*s'",
            //        sizeof(priv->accept_key) - 1, len, (int)len, buffer);
            //    return;
            //}

            //if (memcmp(priv->accept_key, buffer, len) != 0) {
            //    SFLog(Websocket, Error, "invalid accept key '%.*s', expected '%.*s'",
            //        (int)len, buffer, (int)len, priv->accept_key);
            //    return;
            //}

            wsStatus.Accepted = true;
        }

        static void CheckProtocol(WebsocketClientCurl* priv, const char* buffer, size_t len)
        {
            auto& wsStatus = priv->m_CurlStatus;

            len = std::min(len, countof(wsStatus.ProtocolReceived) - 1);
            memcpy(wsStatus.ProtocolReceived, buffer, len);
            wsStatus.ProtocolReceived[len] = '\0';
        }

        static void CheckUpgrade(WebsocketClientCurl* priv, const char* buffer, size_t len)
        {
            auto& wsStatus = priv->m_CurlStatus;

            wsStatus.WebsocketUpgrade = false;

            if (len == strlen("websocket") &&
                !StrUtil::StringCompairIgnoreCase("websocket", -1, buffer, int(len)))
            {
                char localBuffer[128];
                len = std::min(len, countof(localBuffer) - 1);
                memcpy(localBuffer, buffer, len);
                localBuffer[len] = '\0';

                SFLog(Websocket, Error, "WebsocketClient Invalid Upgrade '{0}'. Expected 'websocket'", localBuffer);
                return;
            }

            wsStatus.WebsocketUpgrade = true;
        }

        static void CheckConnection(WebsocketClientCurl* priv, const char* buffer, size_t len)
        {
            auto& wsStatus = priv->m_CurlStatus;

            wsStatus.ConnectionUpgrade = false;

            if (len == strlen("upgrade") &&
                !StrUtil::StringCompairIgnoreCase("upgrade", -1, buffer, int(len)))
            {
                char localBuffer[128];
                len = std::min(len, countof(localBuffer) - 1);
                memcpy(localBuffer, buffer, len);
                localBuffer[len] = '\0';

                SFLog(Websocket, Error, "Unexpected Connection: {0}'. Expected 'upgrade'", localBuffer);
                return;
            }

            wsStatus.ConnectionUpgrade = true;
        }

        static size_t ReceiveHeader(const char* buffer, size_t count, size_t nitems, void* data)
        {
            long http_status = -1;
            WebsocketClientCurl* wsClient = reinterpret_cast<WebsocketClientCurl*>(data);
            CURL* curl = wsClient->m_Curl;
            auto& wsStatus = wsClient->m_CurlStatus;

            size_t len = count * nitems;
            const struct header_checker {
                const char* prefix;
                void (*check)(WebsocketClientCurl* priv, const char* suffix, size_t suffixlen);
            } *itr, header_checkers[] = {
                {"Sec-WebSocket-Accept:", CheckAccept},
                {"Sec-WebSocket-Protocol:", CheckProtocol},
                {"Connection:", CheckConnection},
                {"Upgrade:", CheckUpgrade},
                {NULL, NULL}
            };

            // If we are being redirected, let curl do that for us.
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
            if (300 <= http_status && http_status <= 399)
            {
                wsStatus.Redirection = true;
                return len;
            }
            else
            {
                wsStatus.Redirection = false;
            }

            if (len == 2 && memcmp(buffer, "\r\n", 2) == 0)
            {
                long status;

                curl_easy_getinfo(curl, CURLINFO_HTTP_CONNECTCODE, &status);
                if (!wsStatus.Accepted)
                {
                    SFLog(Websocket, Error, "Connection failed httpCode:{0} connectCode:{1}", http_status, status);
                    wsClient->OnConnectionError(ResultCode::IO_DISCONNECTED);
                    return 0;
                }
                else
                {
                    wsClient->OnConnected();
                    return len;
                }
            }

            if (HeaderHasPrefix(buffer, len, "HTTP/"))
            {
                wsStatus.Accepted = false;
                wsStatus.WebsocketUpgrade = false;
                wsStatus.ConnectionUpgrade = false;
                wsStatus.ProtocolReceived[0] = '\0';
                return len;
            }

            for (itr = header_checkers; itr->prefix != NULL; itr++)
            {
                if (HeaderHasPrefix(buffer, len, itr->prefix))
                {
                    size_t prefixlen = strlen(itr->prefix);
                    size_t valuelen = len - prefixlen;
                    const char* value = buffer + prefixlen;
                    SkipSpaceStart(&value, &valuelen);
                    itr->check(wsClient, value, valuelen);
                }
            }

            return len;
        }

        static size_t ReceiveData(const char* buffer, size_t count, size_t nitems, void* data)
        {
            WebsocketClientCurl* wsClient = reinterpret_cast<WebsocketClientCurl*>(data);
            CURL* curl = wsClient->m_Curl;
            auto& recvBuffer = wsClient->m_ReceiveBuffer;
            auto& wsStatus = wsClient->m_CurlStatus;

            size_t len = count * nitems;


            // ignore redirection data
            if (wsStatus.Redirection)
            {
                return len;
            }

            struct curl_ws_frame* frameMeta = curl_ws_meta(curl);
            if (frameMeta == nullptr)
            {
                SFLog(Websocket, Error, "Recv failed, invalid meta data");
                return len;
            }

            if (ReadData(frameMeta, buffer, recvBuffer))
            {
                wsClient->OnRecv(recvBuffer);
                recvBuffer.resize(0);
            }

            return len;
        }

        static bool ReadData(struct curl_ws_frame* frameMeta, const void* buffer, Array<uint8_t>& recvBuffer)
        {
            if (frameMeta == nullptr)
            {
                SFLog(Websocket, Error, "Recv failed, invalid meta data");
                return false;
            }

            // if start of frame
            if ((int)recvBuffer.size() != frameMeta->offset)
            {
                SFLog(Websocket, Error, "Recv failed, invalid data offset");
                return false;
            }

            recvBuffer.Append(ArrayView<const uint8_t>(frameMeta->len, reinterpret_cast<const uint8_t*>(buffer)));

            if (frameMeta->bytesleft == 0 || (frameMeta->flags & CURLWS_CLOSE) == CURLWS_CLOSE)
            {
                return true;
            }

            return false;
        }


    };

    void WebsocketClientCurl::AddHeader(const char* headerKey, const char* headerString)
    {
        String headerValue;
        headerValue.Format("{0}: {1}", headerKey, headerString);
        m_Headers = curl_slist_append(m_Headers, (const char*)headerValue);
    }

    void WebsocketClientCurl::AddParameter(const char* headerKey, const char* headerString)
    {
        String headerValue;
        headerValue.Format("{0}={1}", headerKey, headerString);
        m_Parameters.push_back(headerValue);
    }

	Result WebsocketClientCurl::Initialize(const String& url, const String& protocol)
	{
		if (m_Curl) // probably initializing again
			return ResultCode::SUCCESS_FALSE;

        m_Url = url;
        m_Protocol = protocol;

        m_ReceiveBuffer.reserve(8 * 1024);

        // set up parameters
        bool bSSLAddr = m_Url.StartsWith("wss://");
        if (bSSLAddr || m_Url.StartsWith("ws://"))
        {
            m_UseSSL = bSSLAddr;
        }

        const char* strPrefix = "?";
        for (auto& parameter : m_Parameters)
        {
            m_Url.Append(strPrefix);
            m_Url.Append(parameter);
            strPrefix = "&";
        }

        TryConnect();

		if (IsUseTickThread())
			StartThread();

		return ResultCode::SUCCESS;
	}

	void WebsocketClientCurl::Terminate()
	{
        SFLog(Websocket, Info, "WebsocketClientCurl Teminated");

        CloseConnection();

        if (m_TickThread)
        {
            m_TickThread->Stop();
            m_TickThread.reset();
        }
	}

    void WebsocketClientCurl::StartThread()
    {
        auto pThread = new(GetSystemHeap()) FunctorTickThread(
            [this](Thread* pThread)
            {
                SFLog(Websocket, Info, "WebsocketClientCurl thread started, {0}");
            },
            [this](Thread* pThread)
            {
                SFLog(Websocket, Info, "WebsocketClientCurl thread stopped, {0}");
            },
                [this](Thread* pThread)
            {
                if (!m_Curl)
                    return false;

                TickUpdate();

                return true;
            });

        pThread->Start();
        m_TickThread.reset(pThread);
    }

    void WebsocketClientCurl::TryConnect()
    {
        MutexScopeLock scopeLock(m_ContextLock);
        CURLcode result;

        SFLog(Websocket, Info, "Connecting websocket server: {0}", m_Url);

        // clean up first
        if (m_Curl)
            CloseConnection();

        m_Curl = curl_easy_init();

        curl_easy_setopt(m_Curl, CURLOPT_DEBUGFUNCTION, WebsocketClientCurlImpl::WebsocketCurl_DebugFunc);
        curl_easy_setopt(m_Curl, CURLOPT_DEBUGDATA, this);

        if (!m_Protocol.IsNullOrEmpty())
        {
            String m_ProtocolHeader;
            m_ProtocolHeader.Format("Sec-WebSocket-Protocol: {0}", m_Protocol);
            m_Headers = curl_slist_append(m_Headers, m_ProtocolHeader.data());
        }

        // TODO: Still working on this
        //m_Headers = curl_slist_append(NULL, "HTTP/1.1 101 WebSocket Protocol Handshake");
        //m_Headers = curl_slist_append(m_Headers, "Upgrade: WebSocket");
        //m_Headers = curl_slist_append(m_Headers, "Connection: Upgrade");
        //m_Headers = curl_slist_append(m_Headers, "Sec-WebSocket-Version: 13");
        //m_Headers = curl_slist_append(m_Headers, "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw=="); // ?
        //result = curl_easy_setopt(m_Curl, CURLOPT_PRIVATE, this);
        result = curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYPEER, false);
        result = curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYHOST, 0L);
        result = curl_easy_setopt(m_Curl, CURLOPT_URL, (const char*)m_Url);

        // https://curl.se/docs/websocket.html
        // Method 2
        result = curl_easy_setopt(m_Curl, CURLOPT_CONNECT_ONLY, 2L);

        result = curl_easy_setopt(m_Curl, CURLOPT_HTTPHEADER, m_Headers);
        //curl_easy_setopt(m_Curl, CURLOPT_OPENSOCKETFUNCTION, my_opensocketfunc);
        result = curl_easy_setopt(m_Curl, CURLOPT_HEADERFUNCTION, WebsocketClientCurlImpl::ReceiveHeader);
        result = curl_easy_setopt(m_Curl, CURLOPT_HEADERDATA, this);
        //result = curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, WebsocketClientCurlImpl::ReceiveData);
        //result = curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA, this);
        //curl_easy_setopt(m_Curl, CURLOPT_READFUNCTION, WebsocketClientCurlImpl::send_data);
        //curl_easy_setopt(m_Curl, CURLOPT_READDATA, this);

        m_ConnectedThisFrame = false;

        // Method 2 will finish handshake in curl_easy_perform
        result = curl_easy_perform(m_Curl);
        if (result != CURLE_OK)
        {
            SFLog(Websocket, Info, "Websocket client initialization error : {0}, {1}:{2}", m_Url, int(result), curl_easy_strerror(result));
        }
    }

    void WebsocketClientCurl::CloseConnection()
    {
        MutexScopeLock scopeLock(m_ContextLock);

        m_ConnectionState = ConnectionState::Disconnected;

        m_ConnectedThisFrame = false;

        if (m_Curl)
        {
            curl_easy_cleanup(m_Curl);
            m_Curl = nullptr;
        }

        if (m_Headers)
        {
            curl_slist_free_all(m_Headers);
            m_Headers = nullptr;
        }

        m_CurlStatus.Clear();
    }

    void WebsocketClientCurl::TickUpdate()
    {
        if (m_ConnectionState == ConnectionState::Disconnected)
        {
            CloseConnection();
            if (IsReconnectOnDisconnected())
            {
                if (!m_ReconnectTimer.IsTimerActive())
                {
                    m_ReconnectTimer.SetTimer(DurationMS(5000));
                }
                else if (m_ReconnectTimer.CheckTimer())
                {
                    TryConnect();
                    m_ReconnectTimer.SetTimer(DurationMS(5000));
                }
            }
        }
        else if (m_ConnectionState == ConnectionState::Connected)
        {
            if (m_ConnectedThisFrame)
            {
                if (m_OnConnectedHandler)
                    m_OnConnectedHandler();

                m_ConnectedThisFrame = false;
            }


            size_t rlen{};
            struct curl_ws_frame* frameMeta{};
            uint8_t readBuffer[4*1024];

            CURLcode result = curl_ws_recv(m_Curl, readBuffer, sizeof(readBuffer), &rlen, &frameMeta);
            if (result == CURLE_OK)
            {
                if (frameMeta)
                {
                    assert(frameMeta->len == rlen);
                    if (WebsocketClientCurlImpl::ReadData(frameMeta, readBuffer, m_ReceiveBuffer))
                    {
                        OnRecv(m_ReceiveBuffer);
                        m_ReceiveBuffer.resize(0);
                    }
                }
            }
            else if (result == CURLE_GOT_NOTHING)
            {
                // Closed?
                SFLog(Websocket, Warning, "Nothing? result:{0}, error:{1}", int(result), curl_easy_strerror(result));
                // the connection might be disconnected
                m_ConnectionState = ConnectionState::Disconnected;
            }
            else if (result == CURLE_AGAIN)
            {
                // try again later
            }
            else
            {
                SFLog(Websocket, Error, "Failed to recv curl error:{0}, {1}", int(result), curl_easy_strerror(result));
                CloseConnection();
            }
        }
    }

    void WebsocketClientCurl::OnConnectionError(Result result)
    {
        m_ConnectionState = ConnectionState::Disconnected;
        // Clear connection on tick
    }

    void WebsocketClientCurl::OnConnected()
    {
        m_ConnectionState = ConnectionState::Connected;
        SFLog(Websocket, Info, "Websocket connected {0}", m_Url);
        m_ConnectedThisFrame = true;
    }

    Result WebsocketClientCurl::Send(const Array<uint8_t>& messageData)
    {
        Result hr;

        size_t sentSize{};
        curl_off_t fragmentOffset = 0; // no fragmentation
        uint flags = CURLWS_BINARY;

        MutexScopeLock scopeLock(m_ContextLock);
        if (m_Curl == nullptr)
            return ResultCode::IO_DISCONNECTED;

        CURLcode result = curl_ws_send(m_Curl, messageData.data(), messageData.size(), &sentSize, fragmentOffset, flags);
        if (result == CURLE_OK)
        {

        }
        else if (result == CURLE_GOT_NOTHING)
        {
            // Closed?
            SFLog(Websocket, Warning, "Nothing? result:{0}, error:{1}", int(result), curl_easy_strerror(result));
            // the connection might be disconnected
            m_ConnectionState = ConnectionState::Disconnected;
        }
        else if (result == CURLE_AGAIN)
        {
            // recv later
        }
        else
        {
            SFLog(Websocket, Error, "Failed to send curl error:{0}, {1}", int(result), curl_easy_strerror(result));
            CloseConnection();
        }

        return hr;
    }

}

