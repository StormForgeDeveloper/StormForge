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


#include "libwebsockets.h"


namespace SF
{
	namespace Log
	{
		extern LogChannel Websocket;
	};

#define RING_DEPTH 1024

	struct WSMessagePacket {
		void* payload; /* is malloc'd */
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


		static void DeleteMessageData(void* _msg);

		struct WSSessionData
		{
			struct lws_ring* SendQueue{};
			uint32_t SendQueueTail{};

			Array<uint8_t>* MessageData{};

			uint8_t flow_controlled : 1;
			uint8_t write_consume_pending : 1;

			void Initialize();
			void Clear();
		};


		Websocket(IHeap& heap, const char* name);
		Websocket(const Websocket&) = delete;
		virtual ~Websocket() = default;

		IHeap& GetHeap() const { return m_Heap; }

		virtual Result Initialize(int port);

		bool IsValid() const { return m_WSI != nullptr; }

		virtual void Terminate();

		virtual void Send(struct WSSessionData* pss, const Array<uint8_t>& messageData);
		virtual void OnRecv(struct WSSessionData* pss, const Array<uint8_t>& messageData) {}

		virtual int OnProtocolInit(struct lws* wsi, void* user, void* in, size_t len) { return 0; }
		virtual int OnProtocolDestroy(struct lws* wsi, void* user, void* in, size_t len) { return 0; }
		virtual int OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionClosed(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionError(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionWritable(struct lws* wsi, void* user, void* in, size_t len);
		virtual int OnConnectionReadable(struct lws* wsi, void* user, void* in, size_t len);

		static int WSCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len);
		virtual int OnWSCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len);


		const String& GetName() const { return m_Name; }

	protected:

		IHeap& m_Heap;

		String m_Name;

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

		// 
		Result m_Result;

		int m_Options{};

		// server path
		String m_ServerPath;

		String m_ServerAddress;

		// port setting
		int m_Port = 1212;
	};



}

