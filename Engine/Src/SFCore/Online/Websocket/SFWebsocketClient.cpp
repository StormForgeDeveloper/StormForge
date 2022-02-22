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


	WebsocketClient::WebsocketClient(IHeap& heap, const char* serverAddress, const char* serverPath)
		: super(heap, "WSClient")
	{
		m_ServerAddress = serverAddress;
		m_ServerPath = serverPath;
	}

	WebsocketClient::~WebsocketClient()
	{}

	Result WebsocketClient::Initialize(int port)
	{
		if (m_WSIContext) // probably initializing again
			return ResultCode::SUCCESS_FALSE;

		super::Initialize(port);

		SFLog(Game, Info, "BR websocket server test | visit http://localhost:{0}", m_Port);

		m_PVOOptions.resize(5);
		m_PVOOptions[0] = {
			NULL,		/* "next" pvo linked-list */
			&m_PVOOptions[1],	/* "child" pvo linked-list */
			"TestWS",	/* protocol name we belong to on this vhost */
			""		/* ignored */
		};

		m_PVOOptions[1] = {
			&m_PVOOptions[2],		// "next" pvo linked-list 
			nullptr,				// "child" pvo linked-list 
			"ads",		/* pvo name */
			(const char*)m_ServerAddress.data()	/* pvo value */
		};

		m_PVOOptions[2] = {
			&m_PVOOptions[3],		// "next" pvo linked-list 
			nullptr,				// "child" pvo linked-list 
			"url",		/* pvo name */
			(const char*)m_ServerPath.data()	/* pvo value */
		};

		m_PVOOptions[3] = {
			&m_PVOOptions[4],		// "next" pvo linked-list 
			nullptr,				// "child" pvo linked-list 
			"options",		/* pvo name */
			(const char*)&m_Options	/* pvo value */
		};

		m_PVOOptions[4] = {
			nullptr,		// "next" pvo linked-list 
			nullptr,				// "child" pvo linked-list 
			"port",		/* pvo name */
			(const char*)&m_Port	/* pvo value */
		};



		m_Protocols.reserve(2);
		m_Protocols.push_back({
				"TestWS",
				&WSCallback,
				sizeof(struct ClientSessionData),
				1024,
				0, this, 0
			});
		m_Protocols.push_back(LWS_PROTOCOL_LIST_TERM);


		struct lws_context_creation_info info;
		memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
		info.port = CONTEXT_PORT_NO_LISTEN;
		info.protocols = m_Protocols.data();
		info.pvo = m_PVOOptions.data();
		info.extensions = m_Extensions.data();
		info.pt_serv_buf_size = 32 * 1024;
		info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT | LWS_SERVER_OPTION_VALIDATE_UTF8;
		if (UseWriteEvent())
			info.options |= LWS_SERVER_OPTION_LIBEVENT;

		//info.fd_limit_per_thread = 1 + 1 + 1;
		info.user = this;

		//info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

		m_WSIContext = lws_create_context(&info);
		if (!m_WSIContext) {
			SFLog(Game, Error, "lws init failed");
			return ResultCode::FAIL;
		}


		m_ConnectionState = ConnectionState::Connecting;

		TryConnect();

		m_Thread.reset(new(GetHeap()) FunctorTickThread([this](Thread* pThread)
			{
				return !lws_service(m_WSIContext, 0);
			}));

		m_Thread->Start();

		return ResultCode::SUCCESS;
	}

	void WebsocketClient::Terminate()
	{
		if (m_Thread)
		{
			m_Thread->SetKillEvent();
		}

		super::Terminate();

		m_ConnectionState = ConnectionState::Disconnected;
		m_Session = nullptr;

		if (m_Thread)
		{
			m_Thread->Stop(false);
			m_Thread.reset();
		}
	}

	void WebsocketClient::CallbackTryConnect(struct lws_sorted_usec_list* pSortedUsecList)
	{
		auto* vhd = lws_container_of(pSortedUsecList, VirtualHostData, SortedUsecList);
		vhd->pInstance->TryConnect();
	}

	void WebsocketClient::TryConnect()
	{
		lws_client_connect_info info{};
		//char host[128];

		//lws_snprintf(host, sizeof(host), "%s:%u", m_ServerAddress.data(), m_Port);

		memset(&info, 0, sizeof(info));
		info.context = m_WSIContext;
		info.port = m_Port;
		info.address = m_ServerAddress;
		info.path = m_ServerPath;
		info.host = info.address;
		info.origin = info.address;
		//info.ssl_connection = LCCSCF_USE_SSL;
		//info.vhost = m_VHost ? m_VHost->VHost : nullptr;
		info.protocol = "TestWS";
		info.local_protocol_name = "TestWS";
		//info.iface = m_NetInterfaceId; // don't specify to bind all
		//info.userdata = this; // This will skip session data allocation and use this instance as user data for session
		info.pwsi = &m_WSI;

		SFLog(Websocket, Info, "Connecting to {0}:{1}/{2}", info.address, info.port, info.path);

		if (!lws_client_connect_via_info(&info))
		{
			lws_sul_schedule(m_WSIContext, 0, &m_VHost->SortedUsecList, CallbackTryConnect, 10 * LWS_US_PER_SEC);
		}
	}

	void WebsocketClient::Send(const Array<uint8_t>& messageData)
	{
		if (m_Session == nullptr)
			return;

		super::Send(m_Session, messageData);
	}

	int WebsocketClient::OnProtocolInit(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Debug3, "WSCallback_ProtocolInit");

		super::OnProtocolInit(wsi, user, in, len);

		auto* vhd = reinterpret_cast<VirtualHostData*>(lws_protocol_vh_priv_zalloc(lws_get_vhost(wsi), lws_get_protocol(wsi), sizeof(struct VirtualHostData)));
		if (!vhd)
			return -1;

		vhd->Context = lws_get_context(wsi);
		vhd->VHost = lws_get_vhost(wsi);
		vhd->pInstance = reinterpret_cast<WebsocketClient*>(user);
		vhd->pInstance->m_WSI = wsi;

		TryConnect();

		return 0;
	}

	int WebsocketClient::OnProtocolDestroy(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Debug3, "WSCallback_ProtocolDestroy");

		auto* vhd = reinterpret_cast<VirtualHostData*>(lws_protocol_vh_priv_get(lws_get_vhost(wsi), lws_get_protocol(wsi)));

		if (vhd)
		{
			lws_sul_cancel(&vhd->SortedUsecList);
		}

		return 0;
	}

	int WebsocketClient::OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len)
	{
		int iRet = super::OnConnectionEstablished(wsi, user, in, len);

		if (iRet == 0)
		{
			m_Session = (struct WSSessionData*)user;

			m_ConnectionState = ConnectionState::Connected;
		}

		return iRet;
	}

	int WebsocketClient::OnConnectionClosed(struct lws* wsi, void* user, void* in, size_t len)
	{
		SFLog(Websocket, Debug3, "WSClient WSCallback_Closed");

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
		SFLog(Websocket, Debug3, "WSClient WSCallback_ConnectionError: {0}", (const char*)in);

		super::OnConnectionError(wsi, user, in, len);

		m_WSI = nullptr;
		m_Session = nullptr;
		m_Result = ResultCode::IO_DISCONNECTED;

		lws_cancel_service(lws_get_context(wsi));

		return 0;
	}


}

