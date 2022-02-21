////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Websocket
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/Websocket/SFWebsocket.h"





namespace SF
{
	namespace Log
	{
		LogChannel Websocket("Websocket", LogOutputType::Info);
	};


	void Websocket::DeleteMessageData(void* _msg)
	{
		auto pMsgData = (struct WSMessagePacket*)_msg;

		free(pMsgData->payload);
		pMsgData->payload = NULL;
		pMsgData->len = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	struct Websocket::WSSessionData
	//

	void Websocket::WSSessionData::Initialize()
	{
		SendQueue = lws_ring_create(sizeof(WSMessagePacket), RING_DEPTH, DeleteMessageData);
		if (!SendQueue)
			return;
		SendQueueTail = 0;

		MessageData = new(GetSystemHeap()) DynamicArray<uint8_t>(GetSystemHeap(), 128 * 1024);
	}

	void Websocket::WSSessionData::Clear()
	{
		lws_ring_destroy(SendQueue);
		SendQueue = nullptr;

		IHeap::Delete(MessageData);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class Websocket
	//


	Websocket::Websocket(IHeap& heap, const char* name)
		: m_Heap(heap)
		, m_Name(name)
		, m_Protocols(GetHeap())
		, m_Mounts(GetHeap())
		, m_PVOOptions(GetHeap())
		, m_Extensions(GetHeap())
	{
	}

	Result Websocket::Initialize(int port)
	{
		m_Port = port;
		return ResultCode::SUCCESS;
	}

	void Websocket::Terminate()
	{
		if (m_WSIContext)
		{
			lws_context_destroy(m_WSIContext);
			m_WSIContext = nullptr;
		}

		m_WSI = nullptr;
	}

	void Websocket::Send(struct WSSessionData* pss, const Array<uint8_t>&messageData)
	{
		if (m_WSI == nullptr || pss == nullptr
			|| messageData.size() == 0)
			return;

		int n = (int)lws_ring_get_count_free_elements(pss->SendQueue);
		if (!n)
		{
			SFLog(Websocket, Debug3, "Nothing to read: dropping!");
			return;
		}

		WSMessagePacket amsg{};

		// notice we over-allocate by LWS_PRE
		amsg.payload = malloc(LWS_PRE + messageData.size());
		if (!amsg.payload)
		{
			SFLog(Websocket, Debug3, "OOM: dropping!");
			return;
		}

		memcpy((char*)amsg.payload + LWS_PRE, messageData.data(), messageData.size());
		if (!lws_ring_insert(pss->SendQueue, &amsg, 1))
		{
			DeleteMessageData(&amsg);
			SFLog(Websocket, Debug3, "Send queue is full. dropping!");
			return;
		}

		lws_callback_on_writable(m_WSI);

	}

	int Websocket::OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;
		pss->Initialize();
		return 0;
	}

	int Websocket::OnConnectionClosed(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;
		pss->Clear();
		return 0;
	}

	int Websocket::OnConnectionError(struct lws* wsi, void* user, void* in, size_t len)
	{
		//SFLog(Websocket, Debug3, "WSClient WSCallback_ConnectionError: {0}", (const char*)in);

		m_WSI = nullptr;

		m_Result = ResultCode::IO_DISCONNECTED;

		lws_cancel_service(lws_get_context(wsi));

		return 0;
	}


	int Websocket::OnConnectionWritable(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;
		const WSMessagePacket* pmsg{};

		if (pss->write_consume_pending)
		{
			lws_ring_consume_single_tail(pss->SendQueue, &pss->SendQueueTail, 1);
			pss->write_consume_pending = 0;
		}

		pmsg = (const WSMessagePacket*)lws_ring_get_element(pss->SendQueue, &pss->SendQueueTail);
		if (!pmsg) {
			SFLog(Websocket, Debug3, "WSCallback_Writable nothing to write");
			return 0;
		}

		int flags = lws_write_ws_flags(
			pmsg->binary ? LWS_WRITE_BINARY : LWS_WRITE_TEXT,
			pmsg->first, pmsg->final);

		// notice we allowed for LWS_PRE in the payload already
		int m = lws_write(wsi, ((unsigned char*)pmsg->payload) + LWS_PRE, pmsg->len, (enum lws_write_protocol)flags);
		if (m < (int)pmsg->len)
		{
			SFLog(Websocket, Error, "ERROR {0} writing to ws socket", m);
			return -1;
		}

		SFLog(Websocket, Info, "WSServer  wrote {0}: flags: 0x{1:x} first:{2} final:{3}",
			m, flags, pmsg->first, pmsg->final);

		/*
		 * Workaround deferred deflate in pmd extension by only
		 * consuming the fifo entry when we are certain it has been
		 * fully deflated at the next WRITABLE callback.  You only need
		 * this if you're using pmd.
		 */
		pss->write_consume_pending = 1;
		lws_callback_on_writable(wsi);

		if (pss->flow_controlled && (int)lws_ring_get_count_free_elements(pss->SendQueue) > RING_DEPTH - 5)
		{
			lws_rx_flow_control(wsi, 1);
			pss->flow_controlled = 0;
		}

		return 0;
	}

	int Websocket::OnConnectionReadable(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;

		if (pss->MessageData == nullptr)
			return 0;

		SFLog(Websocket, Debug3, "WSClient WSCallback_Readable: (rpp:{0}, first:{1}, last:{2}, bin:{3}, len:{4}, stored:{5})",
			(int)lws_remaining_packet_payload(wsi),
			lws_is_first_fragment(wsi),
			lws_is_final_fragment(wsi),
			lws_frame_is_binary(wsi), (int)len,
			(int)pss->MessageData->size());

		if (len == 0)
			return 0;

		WSMessagePacket amsg{};

		amsg.first = (char)lws_is_first_fragment(wsi);
		amsg.final = (char)lws_is_final_fragment(wsi);
		amsg.binary = (char)lws_frame_is_binary(wsi);

		if (amsg.first)
			pss->MessageData->Reset();

		pss->MessageData->Append(ArrayView<uint8_t>(len, reinterpret_cast<uint8_t*>(in)));

		if (amsg.final)
		{
			OnRecv(pss, *pss->MessageData);
		}

		return 0;
	}



	int Websocket::WSCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len)
	{
		auto vho = lws_get_vhost(wsi);
		if (vho)
		{
			auto userData = lws_get_vhost_user(vho);
			auto pInstance = reinterpret_cast<Websocket*>(userData);
			if (pInstance)
			{
				auto org = pInstance->GetName().GetDebugStringPtr();

				pInstance->OnWSCallback(wsi, reason, user, in, len);

				auto after = pInstance->GetName().GetDebugStringPtr();
				assert(org == after);
			}

			SFLog(Websocket, Info, "{0} WSCallback {1}, size:{2}", pInstance ? pInstance->GetName() : "", (int)reason, len);

			return 0;
		}

		return 0;
	}

	int Websocket::OnWSCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len)
	{
		switch (reason)
		{
		case LWS_CALLBACK_PROTOCOL_INIT:
			return OnProtocolInit(wsi, user, in, len);
		case LWS_CALLBACK_PROTOCOL_DESTROY:
			return OnProtocolDestroy(wsi, user, in, len);
			// Server
		case LWS_CALLBACK_ESTABLISHED:
			return OnConnectionEstablished(wsi, user, in, len);
		case LWS_CALLBACK_CLOSED:
			return OnConnectionClosed(wsi, user, in, len);
		case LWS_CALLBACK_SERVER_WRITEABLE:
			return OnConnectionWritable(wsi, user, in, len);
		case LWS_CALLBACK_RECEIVE:
			return OnConnectionReadable(wsi, user, in, len);
			// Client
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			return OnConnectionEstablished(wsi, user, in, len);
		case LWS_CALLBACK_CLIENT_CLOSED:
			return OnConnectionClosed(wsi, user, in, len);
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			return OnConnectionWritable(wsi, user, in, len);
		case LWS_CALLBACK_CLIENT_RECEIVE:
			return OnConnectionReadable(wsi, user, in, len);
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
			return OnConnectionError(wsi, user, in, len);
		default:
			break;
		}

		return 0;
	}


}

