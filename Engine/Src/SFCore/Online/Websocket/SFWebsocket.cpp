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

#include <signal.h>



namespace SF
{
	namespace Log
	{
		LogChannel Websocket("Websocket", LogOutputType::Info);
	};


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	struct Websocket::WSSessionData
	//

	void Websocket::WSSessionData::Initialize(size_t RecvBufferSize, size_t SendBufferSize)
	{
		SendBuffer = new(GetSystemHeap()) CircularBufferQueue(GetSystemHeap(), SendBufferSize);
		ReceiveBuffer = new(GetSystemHeap()) DynamicArray<uint8_t>(GetSystemHeap(), RecvBufferSize);
		UserObjectPtr.reset();
	}

	void Websocket::WSSessionData::Clear()
	{
		IHeap::Delete(SendBuffer);
		SendBuffer = nullptr;

		IHeap::Delete(ReceiveBuffer);
		ReceiveBuffer = nullptr;

		UserObjectPtr.reset();
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
		, m_RecvDeletates(m_Heap)
	{
//		// Websocket doesn't work well with libevent on Windows
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		m_UseWriteEvent = false;
#else
		m_UseWriteEvent = true;
#endif
	}


	Result Websocket::Initialize(const String& serverAddress, int port, const String& protocol)
	{
		m_ServerAddress = serverAddress;
		m_Port = port;
		m_UseProtocol = protocol;

		m_PVOOptions.push_back({
			nullptr,		/* "next" pvo linked-list */
			nullptr,	/* "child" pvo linked-list */
			m_UseProtocol,	/* protocol name we belong to on this vhost */
			""		/* ignored */
		});

		m_Protocols.reserve(2);
		m_Protocols.push_back({
				m_UseProtocol,
				&WSCallback,
				GetSessionDataSize(),
				1024,
				0, this, 0
			});
		m_Protocols.push_back(LWS_PROTOCOL_LIST_TERM);

		// don't use this extension for now
		//m_Extensions.push_back({
		//	"permessage-deflate",
		//	lws_extension_callback_pm_deflate,
		//	"permessage-deflate"
		//	 "; client_no_context_takeover"
		//	 "; client_max_window_bits"
		//	});
		m_Extensions.push_back({ nullptr, nullptr, nullptr /* terminator */ });

		m_FlowControlMin = size_t(m_SendBufferSize * 0.3);
		m_FlowControlMax = size_t(m_SendBufferSize * 0.7);


		// Event loop
		//event_enable_debug_mode();
		for (uint iThread = 0; iThread < m_NumThread; iThread++)
		{
			m_EventLoops.push_back(event_base_new());
		}
		//m_EventSighandler = evsignal_new(m_EventLoop, SIGINT, signal_cb_event, (void*)SIGINT);
		//m_EventTimerOuter = event_new(m_EventLoop, -1, EV_PERSIST, timer_cb_event, NULL);

		//struct timeval tv {};;
		//tv.tv_sec = 1;
		//tv.tv_usec = 0;
		//evtimer_add(m_EventTimerOuter, &tv);


		return ResultCode::SUCCESS;
	}

	void Websocket::StartThread()
	{
		for (uint iThread = 0; iThread < m_NumThread; iThread++)
		{
			auto pThread = new(GetHeap()) FunctorTickThread([this, iThread](Thread* pThread)
				{
					if (!m_WSIContext)
						return false;

					if (m_EventLoops.size() > 0)
					{
						event_base_loop(m_EventLoops[iThread], EVLOOP_ONCE | EVLOOP_NONBLOCK);
					}
					else
					{
						lws_service(m_WSIContext, 10);
					}

					return true;
				});

			pThread->Start();
			m_Threads.push_back(pThread);
		}
	}

	void Websocket::Terminate()
	{
		for (auto itThread : m_Threads)
		{
			itThread->SetKillEvent();
		}

		for (auto itLoop : m_EventLoops)
		{
			struct timeval tv {};;
			tv.tv_sec = 0;
			tv.tv_usec = 10;
			event_base_loopexit(itLoop, &tv);
		}

		for (auto itThread : m_Threads)
		{
			itThread->Stop(false);
			IHeap::Delete(itThread);
		}
		m_Threads.Reset();

		if (m_EventTimerOuter)
		{
			evtimer_del(m_EventTimerOuter);
			event_free(m_EventTimerOuter);
			m_EventTimerOuter = nullptr;
		}

		if (m_EventSighandler)
		{
			evsignal_del(m_EventSighandler);
			event_free(m_EventSighandler);
			m_EventSighandler = nullptr;
		}

		if (m_WSIContext)
		{
			lws_context_destroy(m_WSIContext);
			m_WSIContext = nullptr;
		}

		for (auto itLoop : m_EventLoops)
		{
			event_base_loop(itLoop, 0);
			event_base_free(itLoop);
		}

		m_WSI = nullptr;
	}

	void Websocket::Send(struct WSSessionData* pss, const Array<uint8_t>& messageData)
	{
		if (m_WSI == nullptr || pss == nullptr || pss->SendBuffer == nullptr
			|| messageData.size() == 0)
		{
			SFLog(Websocket, Debug3, "Websocket::Send, failed, not initialized?");
			return;
		}

		auto pSendItem = pss->SendBuffer->AllocateWrite(MessageBufferPadding + messageData.size());
		if (pSendItem == nullptr)
		{
			SFLog(Websocket, Debug3, "OOM: dropping!");
			return;
		}

		memcpy((char*)pSendItem->GetDataPtr() + MessageBufferPadding, messageData.data(), messageData.size());

		pss->SendBuffer->ReleaseWrite(pSendItem);

		if (m_UseWriteEvent)
		{
			lws_callback_on_writable(m_WSI);
		}
		else
		{
			OnConnectionWritable(m_WSI, pss, nullptr, 0);
		}

	}

	int Websocket::OnConnectionEstablished(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;
		pss->Initialize(m_RecvBufferSize, m_SendBufferSize);
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
		m_WSI = nullptr;

		m_Result = ResultCode::IO_DISCONNECTED;

		lws_cancel_service(lws_get_context(wsi));

		return 0;
	}


	int Websocket::OnConnectionWritable(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;

		if (pss == nullptr || pss->SendBuffer == nullptr)
			return 1;

		auto SendBuffer = pss->SendBuffer;
		auto pSendItem = SendBuffer->DequeueRead();
		if (pSendItem == nullptr)
			return 0; // nothing to send

		int flags = lws_write_ws_flags(LWS_WRITE_BINARY, 1, 1);
		auto dataLen = int(pSendItem->DataSize - MessageBufferPadding);

		// notice we allowed for LWS_PRE in the payload already
		int m = lws_write(wsi, ((unsigned char*)pSendItem->GetDataPtr()) + MessageBufferPadding, dataLen, (enum lws_write_protocol)flags);
		SendBuffer->ReleaseRead(pSendItem);
		if (m < dataLen)
		{
			SFLog(Websocket, Error, "ERROR {0} writing to ws socket", m);
			return -1;
		}

		SFLog(Websocket, Debug4, "{0}  wrote {0}: flags: 0x{1:x}", GetName(), m, flags);

		if (m_UseWriteEvent)
		{
			lws_callback_on_writable(wsi);
		}

		// If output buffer is saturated, slow down reading from the connection
		if (m_UseRecvFlowControl)
		{
			if (pss->flow_controlled)
			{
				if (SendBuffer->GetFreeSize() > m_FlowControlMax)
				{
					lws_rx_flow_control(wsi, 1); // enable reading
					pss->flow_controlled = 0;
				}
			}
			else if (pss->SendBuffer->GetFreeSize() < m_FlowControlMin)
			{
				lws_rx_flow_control(wsi, 0); // disable reading
				pss->flow_controlled = 1;
			}
		}

		return 0;
	}

	int Websocket::OnConnectionReadable(struct lws* wsi, void* user, void* in, size_t len)
	{
		struct WSSessionData* pss = (struct WSSessionData*)user;

		if (pss->ReceiveBuffer == nullptr)
			return 0;

		SFLog(Websocket, Debug4, "WSClient WSCallback_Readable: (rpp:{0}, first:{1}, last:{2}, bin:{3}, len:{4}, stored:{5})",
			(int)lws_remaining_packet_payload(wsi),
			lws_is_first_fragment(wsi),
			lws_is_final_fragment(wsi),
			lws_frame_is_binary(wsi), (int)len,
			(int)pss->ReceiveBuffer->size());

		if (len == 0)
			return 0;

		WSMessagePacket amsg{};

		amsg.first = (char)lws_is_first_fragment(wsi);
		amsg.final = (char)lws_is_final_fragment(wsi);
		amsg.binary = (char)lws_frame_is_binary(wsi);

		if (amsg.first)
			pss->ReceiveBuffer->Reset();

		pss->ReceiveBuffer->Append(ArrayView<uint8_t>(len, reinterpret_cast<uint8_t*>(in)));

		if (amsg.final)
		{
			OnRecv(pss, *pss->ReceiveBuffer);
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

			SFLog(Websocket, Debug4, "{0} WSCallback {1}, size:{2}", pInstance ? pInstance->GetName() : "", (int)reason, len);

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
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
			return OnProtocolFiltering(wsi, user, in, len);
		case LWS_CALLBACK_EVENT_WAIT_CANCELLED:
			return 0;
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
		case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
			return OnClientAppendHeader(wsi, user, in, len);
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

