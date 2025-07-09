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

#pragma once

#include "SFTypedefs.h"

#include "Util/SFStringCrc32.h"
#include "Online/Websocket/SFWebsocket.h"

#include "curl/curl.h"


namespace SF
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class Websocket
	//


	class WebsocketClientCurl
	{
	public:

		enum class ConnectionState
		{
			Disconnected,
			Connecting,
			Connected,
		};

        using EventOnConnected = std::function<void()>;
        using RecvDeletates = EventDelegateList<const Array<uint8_t>&>;
        using TickDeletates = EventDelegateList<int>;


	public:

		WebsocketClientCurl(const String& name);
		~WebsocketClientCurl();

        const String& GetName() const { return m_Name; }

		SF_FORCEINLINE bool IsInitialized() const { return !m_Url.IsNullOrEmpty(); }
        SF_FORCEINLINE bool IsConnected() const { return m_ConnectionState == ConnectionState::Connected; }

		SF_FORCEINLINE void SetUseTickThread(bool useTickThread) { m_UseTickThread = useTickThread; }
		SF_FORCEINLINE bool IsUseTickThread() const { return m_UseTickThread; }

        SF_FORCEINLINE void SetReconnectOnDisconnected(bool value) { m_ReconnectOnDisconnected = value; }
        SF_FORCEINLINE bool IsReconnectOnDisconnected() const { return m_ReconnectOnDisconnected; }

        void AddHeader(const char* headerKey, const char* headerString);
        void AddParameter(const char* headerKey, const char* headerString);

		virtual Result Initialize(const String& url, const String& protocol = "");
		virtual void Terminate();

		//static void CallbackTryConnect(struct lws_sorted_usec_list* pSortedUsecList);
		Result TryConnect();

        void CloseConnection();

		Result Send(const Array<uint8_t>& messageData);

        virtual void OnRecv(const Array<uint8_t>& messageData) { m_RecvDeletates.Invoke(messageData); }
        SF_FORCEINLINE RecvDeletates& OnRecvEvent() { return m_RecvDeletates; }

        SF_FORCEINLINE TickDeletates& OnTickEvent() { return m_TickDeletates; }

        SF_FORCEINLINE void SetOnConnectedCallback(const EventOnConnected& func) { m_OnConnectedHandler = func; }


        virtual void TickUpdate();
        virtual void TickEventLoop(int iEvent) { TickUpdate(); }

    private:

        Result SetPostFieldData(const Array<const char>& postFieldData);

        void StartThread();

        void OnConnectionError(Result result);
        void OnConnected();

	private:

        friend class WebsocketClientCurlImpl;

        CriticalSection m_ContextLock;

        String m_Name;
        String m_Url;
        String m_Protocol;
        bool m_UseSSL = false;

        CURL* m_Curl{};
        curl_slist* m_Headers{};
        DynamicArray<String> m_Parameters;

        DynamicArray<uint8_t> m_ReceiveBuffer;

        struct _Status
        {
            bool Accepted{};
            bool WebsocketUpgrade{};
            bool ConnectionUpgrade{};
            bool Redirection{};
            char ProtocolRequested[256];
            char ProtocolReceived[256];

            void Clear()
            {
                *this = {};
            }
        } m_CurlStatus{};

        SFUniquePtr<Thread> m_TickThread;

        // Use tick thread
		bool m_UseTickThread = true;
        bool m_ReconnectOnDisconnected = false;
        bool m_ConnectedThisFrame = false;

        Util::Timer m_ReconnectTimer;

        // Connection state
		ConnectionState m_ConnectionState = ConnectionState::Disconnected;

        // Connected event handler
        EventOnConnected m_OnConnectedHandler;

        // Recv Message delegate
        RecvDeletates m_RecvDeletates;

        // Tick delegate
        TickDeletates m_TickDeletates;
    };

}

