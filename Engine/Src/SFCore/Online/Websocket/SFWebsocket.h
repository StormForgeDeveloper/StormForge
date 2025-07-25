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
#include "Util/SFString.h"
#include "Task/SFTask.h"
#include "Container/SFCircularBufferQueue.h"
#include "Object/SFSharedPointer.h"
#include "Delegate/SFEventDelegate.h"
#include "Util/SFGuid.h"
#include "libwebsockets.h"
#include <uv/version.h>
#include <uv.h>
#include <event2/event.h>


namespace SF
{
	namespace Log
	{
		extern LogChannel Websocket;
	};

#define RING_DEPTH 1024

	struct WSMessagePacket {
		void* payload;
		size_t len;

		char binary;
		char first;
		char final;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class Websocket
	//

	class Websocket
	{
	public:

		static constexpr size_t MessageBufferPadding = LWS_PRE; // Message buffer padding for libWebsocket
#if 0 // SF_PLATFORM == SF_PLATFORM_WINDOWS 
        static constexpr uint64_t AsyncLib = LWS_SERVER_OPTION_LIBUV;
#else
        static constexpr uint64_t AsyncLib = LWS_SERVER_OPTION_LIBEVENT;
#endif
		struct WSSessionData
		{
            CriticalSection* SendBufferLock{};
			CircularBufferQueue* SendBuffer{};
			Array<uint8_t>* ReceiveBuffer{};

			uint8_t flow_controlled : 1;
			uint8_t write_consume_pending : 1;

            uint64_t AppId{};
			char AuthKey[256];
			char MachineId[256];
			Guid SessionId;
            StringCrc32 ContentType;
			SharedPointer UserObjectPtr;

			void Initialize(size_t RecvBufferSize, size_t SendBufferSize);
			void Clear();
		};

		using EventFunction = std::function<int(struct lws*, void*, void*, size_t)>; // Return non-zero to disallow the connection.


	public:

		Websocket(const char* name);
		Websocket(const Websocket&) = delete;
		virtual ~Websocket() = default;

		SF_FORCEINLINE uint GetNumThread() const { return m_NumThread; }
		SF_FORCEINLINE void SetNumThread(uint numThread) { m_NumThread = numThread; }

		SF_FORCEINLINE size_t GetNumEventLoopObject() const { return m_EventLoops.size(); }

		SF_FORCEINLINE bool GetUseSSL() const { return m_UseSSL; }
		SF_FORCEINLINE void SetUseSSL(bool useSSL) { m_UseSSL = useSSL; }

        // server path
        void SetServerPath(const String& path) { m_ServerPath = path; }
        const String& GetServerPath() const { return m_ServerPath; }

        // Initialize
		virtual Result Initialize(const String& serverAddress, int port, const String& protocol);

        // Is valid connection?
		SF_FORCEINLINE bool IsValid() const { return m_WSIContext != nullptr && m_WSI != nullptr; }
        SF_FORCEINLINE bool IsInitialized() const { return !m_ServerAddress.IsNullOrEmpty(); }

        // terminate
		virtual void Terminate();

		virtual Result Send(struct WSSessionData* pss, const Array<uint8_t>& messageData);
        virtual void OnRecv(struct WSSessionData* pss, const Array<uint8_t>& messageData) {}

		virtual int OnProtocolInit(struct lws* wsi, void* user, void* in, size_t len) { return 0; }
		virtual int OnProtocolDestroy(struct lws* wsi, void* user, void* in, size_t len) { return 0; }
		virtual int OnProtocolFiltering(struct lws* wsi, void* user, void* in, size_t len)
		{
			if (m_ProtocolFilteringDeletates)
				return m_ProtocolFilteringDeletates(wsi, user, in, len);
			return 0;
		}

		virtual int OnClientAppendHeader(struct lws* wsi, void* user, void* in, size_t len) { return 0; }
		virtual int OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionClosed(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionError(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionWritable(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionReadable(struct lws* wsi, void* user, void* in, size_t len);

        // Try send flush manually. Use it when m_UseWriteEvent is off
        void TrySendFlush(void* user);

		static int WSCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len);
		virtual int OnWSCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len);


		SF_FORCEINLINE const String& GetName() const { return m_Name; }
		SF_FORCEINLINE bool UseWriteEvent() const { return m_UseWriteEvent; }

		// session data size
		virtual size_t GetSessionDataSize() const { return sizeof(struct WSSessionData); }


		SF_FORCEINLINE void SetProtocolFilteringFunction(const EventFunction& filteringFunc) { m_ProtocolFilteringDeletates = filteringFunc; }
		SF_FORCEINLINE void SetProtocolFilteringFunction(EventFunction&& filteringFunc) { m_ProtocolFilteringDeletates = Forward<EventFunction>(filteringFunc); }

        virtual void TickUpdate(int iThread) {}

		// Call this function if you want to use manual ticking 
		virtual void TickEventLoop(int iEvent);

	protected:

		void StartThread();

	protected:

		String m_Name;

		uint m_NumThread = 1;

		bool m_UseSSL = false;

        Atomic<int> m_RunningThreadCount;

		// thread
		DynamicArray<Thread*> m_Threads;

		// Protocol settings
		DynamicArray<lws_protocols> m_Protocols;

		// Mount settings
		DynamicArray<lws_http_mount> m_Mounts;

		// vhost protocol settings
		DynamicArray<lws_protocol_vhost_options> m_PVOOptions;

		// extension settings
		DynamicArray<lws_extension> m_Extensions;

		// WSI context
		struct lws_context* m_WSIContext = nullptr;

		// WSI instance
		lws* m_WSI{};

		// EventLoop
		DynamicArray<event_base*> m_EventLoops;
		//struct event_base* m_EventLoop{};
		struct event* m_EventTimerOuter{};
		struct event* m_EventSighandler{};


		// 
		Result m_Result;

		int m_Options{};

		// server path
		String m_ServerPath;

		String m_ServerAddress;

		String m_UseProtocol;

		// port setting
		int m_Port = 1212;

        // TODO: Need to find better place to put. EventLoop has issue with variable update
		bool m_UseRecvFlowControl = false;
		bool m_UseWriteEvent{};

		size_t m_RecvBufferSize = 32 * 1024;
		size_t m_SendBufferSize = 32 * 1024;

		size_t m_FlowControlMin{};
		size_t m_FlowControlMax{};

		EventFunction m_ProtocolFilteringDeletates;
	};



}

