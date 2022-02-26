////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Websocket warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

#include "Util/SFStringCrc32.h"
#include "Online/Websocket/SFWebsocket.h"




namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class Websocket
	//


	class WebsocketClient : public Websocket
	{
	public:

		using super = Websocket;

		enum class ConnectionState
		{
			Disconnected,
			Connecting,
			Connected,
		};

		struct VirtualHostData
		{
			WebsocketClient* pInstance;
			struct lws_context* Context;
			struct lws_vhost* VHost;
			lws_sorted_usec_list SortedUsecList;
		};

		struct ClientSessionData : public WSSessionData
		{
		};

		struct DelayedEventContext : public lws_sorted_usec_list
		{
			WebsocketClient* pInstance{};
		};


	public:

		WebsocketClient(IHeap& heap);
		~WebsocketClient();

		bool IsConnected() const { return m_ConnectionState == ConnectionState::Connected; }

		virtual Result Initialize(const String& serverAddress, int port, const String& protocol) override;
		virtual void Terminate() override;

		static void CallbackTryConnect(struct lws_sorted_usec_list* pSortedUsecList);
		void TryConnect();

		void Send(const Array<uint8_t>& messageData);

		virtual int OnProtocolInit(struct lws* wsi, void* user, void* in, size_t len) override;
		virtual int OnProtocolDestroy(struct lws* wsi, void* user, void* in, size_t len) override;
		virtual int OnClientAppendHeader(struct lws* wsi, void* user, void* in, size_t len) override
		{
			if (m_ClientAppendHandler)
				return m_ClientAppendHandler(wsi, user, in, len);
			return 0;
		}
		virtual int OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len) override;
		virtual int OnConnectionClosed(struct lws* wsi, void* user, void* in, size_t len) override;
		virtual int OnConnectionError(struct lws* wsi, void* user, void* in, size_t len) override;

		SF_FORCEINLINE void SetClientAppendHeaderFunction(const EventFunction& func) { m_ClientAppendHandler = func; }
		SF_FORCEINLINE void SetClientAppendHeaderFunction(EventFunction&& func) { m_ClientAppendHandler = Forward<EventFunction>(func); }

	private:


		VirtualHostData* m_VHost{};
		struct WSSessionData* m_Session{};

		// scheduler list
		DelayedEventContext SortedUsecList{};

		ConnectionState m_ConnectionState = ConnectionState::Disconnected;

		EventFunction m_ClientAppendHandler;
	};

}

