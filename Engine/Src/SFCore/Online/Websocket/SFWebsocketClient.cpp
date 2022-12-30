////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : WebsocketClient
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/Websocket/SFWebsocketClient.h"



namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class WebsocketClient
	//


	WebsocketClient::WebsocketClient(IHeap& heap)
		: super(heap, "WSClient")
	{
		m_ServerPath = "/";
		m_NumThread = 1;
		SortedUsecList.pInstance = this;
	}

	WebsocketClient::~WebsocketClient()
	{}

	Result WebsocketClient::Initialize(const String& serverAddress, int port, const String& protocol)
	{
		if (m_WSIContext) // probably initializing again
			return ResultCode::SUCCESS_FALSE;

		super::Initialize(serverAddress, port, protocol);

		SFLog(Websocket, Info, "Connecting websocket server: {0}:{1}", m_ServerAddress, m_Port);


		struct lws_context_creation_info info;
		memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
		info.port = CONTEXT_PORT_NO_LISTEN;
		info.protocols = m_Protocols.data();
		info.pvo = m_PVOOptions.data();
		info.extensions = m_Extensions.data();
		info.pt_serv_buf_size = 32 * 1024;
		info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT | LWS_SERVER_OPTION_VALIDATE_UTF8;
		if constexpr (AsyncLib != 0) // Even though it doesn't work well on windows we need to enable it because libwebsocket crashes without libevent enabled
		{
			info.options |= AsyncLib;
		}

		if (m_EventLoops.size() > 0)
		{
			info.count_threads = (uint)m_EventLoops.size();
			info.foreign_loops = reinterpret_cast<void**>(m_EventLoops.data());
		}

		//info.fd_limit_per_thread = 1 + 1 + 1;
		info.user = this;

		m_WSIContext = lws_create_context(&info);
		if (!m_WSIContext) {
			SFLog(Websocket, Error, "lws init failed");
			return ResultCode::FAIL;
		}

		m_ConnectionState = ConnectionState::Connecting;

		TryConnect();

		if (IsUseTickThread())
			StartThread();

		return ResultCode::SUCCESS;
	}

	void WebsocketClient::Terminate()
	{
		super::Terminate();

        SFLog(Websocket, Info, "BR websocket Disconnected");

		m_ConnectionState = ConnectionState::Disconnected;
		m_Session = nullptr;
	}

    void WebsocketClient::TickUpdate(int iThread)
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

        super::TickUpdate(iThread);
    }

	void WebsocketClient::TickEventLoop(int iEvent)
	{
		super::TickEventLoop(iEvent);

		// empty write queue if possible
		if (!m_UseWriteEvent && m_WSI && m_Session)
		{
            TrySendFlush(m_Session);
		}
	}

	void WebsocketClient::CallbackTryConnect(struct lws_sorted_usec_list* pSortedUsecList)
	{
		auto* pInstance = static_cast<DelayedEventContext*>(pSortedUsecList)->pInstance;
		pInstance->TryConnect();
	}

	void WebsocketClient::TryConnect()
	{
		if (m_WSIContext == nullptr || m_ConnectionState == ConnectionState::Connected) // skip for connected
			return;

		lws_client_connect_info info{};

		memset(&info, 0, sizeof(info));
		info.context = m_WSIContext;
		info.port = m_Port;
		info.address = m_ServerAddress;
		info.path = m_ServerPath;
		info.host = "HostHeader";// info.address;
		info.origin = "OriginHeader";// info.address;
		//info.ssl_connection = LCCSCF_USE_SSL;
		//info.vhost = m_VHost ? m_VHost->VHost : nullptr;
		info.protocol = m_UseProtocol;
		info.local_protocol_name = m_UseProtocol;
		//info.iface = m_NetInterfaceId; // don't specify to bind all
		//info.userdata = this; // This will skip session data allocation and use this instance as user data for session
		info.pwsi = &m_WSI;

		SFLog(Websocket, Debug1, "Connecting to {0}:{1}/{2}", info.address, info.port, info.path);

		if (!lws_client_connect_via_info(&info))
		{
			lws_sul_schedule(m_WSIContext, 0, &SortedUsecList, CallbackTryConnect, 10 * LWS_US_PER_SEC);
		}
	}

	Result WebsocketClient::Send(const Array<uint8_t>& messageData)
	{
		if (m_Session == nullptr)
			return ResultCode::IO_NOT_CONNECTED;

		return super::Send(m_Session, messageData);
	}

	int WebsocketClient::OnProtocolInit(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Debug3, "WSCallback_ProtocolInit");

		super::OnProtocolInit(wsi, user, in, len);

		//TryConnect();

		return 0;
	}

	int WebsocketClient::OnProtocolDestroy(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Debug3, "WSCallback_ProtocolDestroy");

		lws_sul_cancel(&SortedUsecList);

		return 0;
	}

	int WebsocketClient::OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len)
	{
		int iRet = super::OnConnectionEstablished(wsi, user, in, len);

		if (iRet == 0)
		{
			m_Session = (struct WSSessionData*)user;

			m_ConnectionState = ConnectionState::Connected;

            SFLog(Websocket, Debug2, "Connected");

            if (m_OnConnectedHandler)
                m_OnConnectedHandler();
		}

		return iRet;
	}

	int WebsocketClient::OnConnectionClosed(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Debug2, "WSClient WSCallback_Closed");

		super::OnConnectionClosed(wsi, user, in, len);

		m_ConnectionState = ConnectionState::Disconnected;
		m_Session = nullptr;
		m_Result = ResultCode::IO_CONNECTION_CLOSED;

		lws_cancel_service(lws_get_context(wsi));
		m_WSI = nullptr;

		return 0;
	}

	int WebsocketClient::OnConnectionError(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Error, "WSClient WSCallback_ConnectionError: {0}", (const char*)in);

		super::OnConnectionError(wsi, user, in, len);

		m_WSI = nullptr;
		m_Session = nullptr;
		m_Result = ResultCode::IO_DISCONNECTED;

		lws_cancel_service(lws_get_context(wsi));

		return 0;
	}


}

