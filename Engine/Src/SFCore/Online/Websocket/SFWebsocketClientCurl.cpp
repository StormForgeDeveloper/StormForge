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

#include "Online/Websocket/SFWebsocketClientCurl.h"



namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class WebsocketClientCurl
	//


	WebsocketClientCurl::WebsocketClientCurl(IHeap& heap)
	{
	}

	WebsocketClientCurl::~WebsocketClientCurl()
	{}

    //curl_socket_t my_opensocketfunc(void* clientp, curlsocktype purpose, struct curl_sockaddr* address)
    //{
    //    return sock = socket(address->family, address->socktype, address->protocol);
    //}

	Result WebsocketClientCurl::Initialize(const String& serverAddress, int port, const String& protocol)
	{
		if (m_Curl) // probably initializing again
			return ResultCode::SUCCESS_FALSE;

        m_ServerAddress = serverAddress;
        m_ServerPath = "/";
        m_Port = port;
        m_Protocol = protocol;

		SFLog(Websocket, Info, "Connecting websocket server: {0}:{1}", m_ServerAddress, m_Port);

        String url;
        url.Format("{0}://{1}:{2}{3}", m_UseSSL ? "wss":"ws", m_ServerAddress, m_Port, m_ServerPath);
        m_Curl = curl_easy_init();


        // TODO: Still working on this
        curl_slist* header_list_ptr = curl_slist_append(NULL, "HTTP/1.1 101 WebSocket Protocol Handshake");
        //header_list_ptr = curl_slist_append(header_list_ptr, "Upgrade: WebSocket");
        //header_list_ptr = curl_slist_append(header_list_ptr, "Connection: Upgrade");
        //header_list_ptr = curl_slist_append(header_list_ptr, "Sec-WebSocket-Version: 13");
        //header_list_ptr = curl_slist_append(header_list_ptr, "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw=="); // ?
        curl_easy_setopt(m_Curl, CURLOPT_PRIVATE, this);
        curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(m_Curl, CURLOPT_URL, (const char*)url);

        // https://curl.se/docs/websocket.html
        // Method 2
        curl_easy_setopt(m_Curl, CURLOPT_CONNECT_ONLY, 2L);

        curl_easy_setopt(m_Curl, CURLOPT_HTTPHEADER, header_list_ptr);
        //curl_easy_setopt(m_Curl, CURLOPT_OPENSOCKETFUNCTION, my_opensocketfunc);
        //curl_easy_setopt(m_Curl, CURLOPT_HEADERFUNCTION, my_func);
        //curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, my_writefunc);
        //curl_easy_setopt(m_Curl, CURLOPT_HEADERFUNCTION, _cws_receive_header);
        //curl_easy_setopt(m_Curl, CURLOPT_HEADERDATA, priv);
        //curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, _cws_receive_data);
        //curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA, priv);
        //curl_easy_setopt(m_Curl, CURLOPT_READFUNCTION, _cws_send_data);
        //curl_easy_setopt(m_Curl, CURLOPT_READDATA, priv);

        // Method 2 will finish handshake in curl_easy_perform
        curl_easy_perform(m_Curl);

		if (IsUseTickThread())
			StartThread();

		return ResultCode::SUCCESS;
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

	void WebsocketClientCurl::Terminate()
	{
        SFLog(Websocket, Info, "WebsocketClientCurl Teminated");

		m_ConnectionState = ConnectionState::Disconnected;

        if (m_Curl)
        {
            curl_easy_cleanup(m_Curl);
            m_Curl = nullptr;
        }
	}

    void WebsocketClientCurl::TickUpdate()
    {
        if (IsReconnectOnDisconnected() && m_ConnectionState == ConnectionState::Disconnected)
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


}

