////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/Telemetry/SFTelemetryBR.h"
#include "Util/SFStringFormat.h"
#include "Util/SFLog.h"



namespace SF
{

	namespace TelemetryBRImpl
	{
		void GenerateSessionId(const String& machineId, String& outSessionId)
		{
			outSessionId.Format("{0}-{1}", machineId, Util::Time.GetRawUTCMs());
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryEvent
	//

    TelemetryEvent::TelemetryEvent(IHeap& heap, TelemetryBR* pClient, uint32_t eventId)
        : m_Heap(heap)
        , m_pClient(pClient)
        , m_EventId(eventId)
    {
    }

    TelemetryEvent::~TelemetryEvent()
    {
    }


    void TelemetryEvent::PostEvent()
    {
        if (m_bSent)
            return;

        if (m_pClient)
            m_pClient->EnqueueEvent(this);

        m_bSent = true;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEventBson
    //

    TelemetryEventBson::TelemetryEventBson(IHeap& heap, TelemetryBR* pClient, uint32_t eventId)
		: TelemetryEvent(heap, pClient, eventId)
	{
		bson_init(&m_Bson);
	}

	TelemetryEventBson::~TelemetryEventBson()
	{
		bson_destroy(&m_Bson);
	}

    ArrayView<const uint8_t> TelemetryEventBson::GetSerializedData()
	{
		m_BinData.SetLinkedBuffer(size_t(m_Bson.len), bson_get_data(&m_Bson));

		return m_BinData;
	}

	TelemetryEvent& TelemetryEventBson::Set(const char* name, int value)
	{
		bson_append_int32(&m_Bson, name, (int)strlen(name), value);
		return *this;
	}

    TelemetryEvent& TelemetryEventBson::Set(const char* name, int64_t value)
	{
		bson_append_int64(&m_Bson, name, (int)strlen(name), value);
		return *this;
	}

    TelemetryEvent& TelemetryEventBson::Set(const char* name, float value)
	{
		bson_append_double(&m_Bson, name, (int)strlen(name), value);
		return *this;
	}

    TelemetryEvent& TelemetryEventBson::Set(const char* name, const char* value)
	{
		bson_append_utf8(&m_Bson, name, (int)strlen(name), value, (int)strlen(value));
		return *this;
	}


    TelemetryEvent& TelemetryEventBson::Set(const String& name, int value)
	{
		bson_append_int32(&m_Bson, name, (int)name.length(), value);
		return *this;
	}

    TelemetryEvent& TelemetryEventBson::Set(const String& name, int64_t value)
	{
		bson_append_int64(&m_Bson, name, (int)name.length(), value);
		return *this;
	}

    TelemetryEvent& TelemetryEventBson::Set(const String& name, float value)
	{
		bson_append_double(&m_Bson, name, (int)name.length(), value);
		return *this;
	}

    TelemetryEvent& TelemetryEventBson::Set(const String& name, const String& value)
	{
		bson_append_utf8(&m_Bson, name, (int)name.length(), value, (int)value.length());
		return *this;
	}


    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEventAvro
    //

    TelemetryEventAvro::TelemetryEventAvro(IHeap& heap, TelemetryBR* pClient, uint32_t eventId)
        : TelemetryEvent(heap, pClient, eventId)
    {
    }

    TelemetryEventAvro::~TelemetryEventAvro()
    {
    }

    ArrayView<const uint8_t> TelemetryEventAvro::GetSerializedData()
    {
        ;

        return m_BinData;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const char* name, int value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const char* name, int64_t value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const char* name, float value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const char* name, const char* value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }


    TelemetryEvent& TelemetryEventAvro::Set(const String& name, int value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const String& name, int64_t value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const String& name, float value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }

    TelemetryEvent& TelemetryEventAvro::Set(const String& name, const String& value)
    {
        m_AvroValue.SetValue(name, value);
        return *this;
    }



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryBR
	//

	TelemetryBR::TelemetryBR()
		: m_Client(GetSystemHeap())
		, m_EventQueue(GetSystemHeap())
	{
	}

	TelemetryBR::~TelemetryBR()
	{
		Terminate();
	}

	Result TelemetryBR::Initialize(const String& serverAddress, int port, const String& clientId, const String& authKey)
	{
		Result hr;

		m_ClientId = clientId;
		m_AuthKey = authKey;

		m_MachineId = Util::GetMachineUniqueId();
		TelemetryBRImpl::GenerateSessionId(m_MachineId, m_SessionId);

		m_Client.SetUseTickThread(false); // We are using manual ticking
		m_Client.SetClientAppendHeaderFunction([&](struct lws* wsi, void* user, void* in, size_t len)
			{
				unsigned char** p = (unsigned char**)in, * end = (*p) + len;
				String HeaderString;
				HeaderString.Format("{0}={1};{2}={3};{4}={5};{6}={7};{8}={9}", 
					KeyName_ClientId, m_ClientId,
					KeyName_AuthKey, m_AuthKey,
					KeyName_MachineId, m_MachineId, 
					KeyName_SessionId, m_SessionId,
                    KeyName_DataType,"avro");
				auto res = lws_add_http_header_by_name(wsi, (unsigned char*)KeyName_AuthHeader, (unsigned char*)HeaderString.data(), (int)HeaderString.length(), p, end);
				if (res)
				{
					return -1;
				}

				return 0;
			});

		m_Client.OnRecvEvent().AddDelegate(uintptr_t(this), [&](Websocket::WSSessionData* pss, const Array<uint8_t>& data)
			{
				uint32_t* pEventId = (uint32_t*)data.data();
				if (pEventId == nullptr || data.size() < sizeof(uint32_t))
					return;

				for (uint Processed = 0; Processed < data.size(); Processed+=4, pEventId++)
				{
					m_EventQueue.FreePostedEvents(*pEventId);
					SFLog(Telemetry, Info, "Client Recv Ack eventId:{0}", *pEventId);
				}
			});

		hr = m_Client.Initialize(serverAddress, port, TelemetryBR::KeyName_Protocol);
		if (!hr)
			return hr;


		m_EventQueue.Initialize();

		auto pTail = m_EventQueue.GetTailEvent();
		if (pTail)
		{
			uint32_t eventId = *(uint32_t*)pTail->GetDataPtr();
			m_EventId = eventId;
			m_SentEventId = eventId - 1;
			m_AckedEventId = eventId - 1;
		}
		else
		{
			m_EventId = 0;
			m_SentEventId = uint32_t(-1);
			m_AckedEventId = uint32_t(-1);
		}

		// 
		m_Thread.reset(new(GetHeap()) FunctorTickThread([this](Thread* pThread)
			{
				if (!m_Client.IsValid())
				{
					m_Client.TryConnect();
					ThisThread::SleepFor(DurationMS(10000));
					return true;
				}

				m_Client.TickEventLoop(0);

				if (!m_Client.IsConnected())
				{
					ThisThread::SleepFor(DurationMS(500));
					return true;
				}

				constexpr int MaxSend = 5;
				{
					MutexScopeLock scopeLock(m_EventQueue.GetReadLock());
					TelemetryEventQueue::EventItem* pEventItem = m_EventQueue.GetTailEvent();
					for (; pEventItem; pEventItem = m_EventQueue.GetNextEvent(pEventItem))
					{
						auto curEventId = *(uint32_t*)pEventItem->GetDataPtr();
						auto idDiff = int32_t(curEventId - m_SentEventId);
						if (idDiff <= 0) // sent but not acked
							continue;

						if (idDiff > MaxSend)
							break;

						SFLog(Telemetry, Debug3, "Posting event eventId:{0}, sz:{1}", curEventId, pEventItem->GetDataSize());
						auto sendRes = m_Client.Send(ArrayView<uint8_t>(pEventItem->GetDataSize(), (uint8_t*)pEventItem->GetDataPtr()));
						if (sendRes)
						{
							m_SentEventId.store(curEventId, MemoryOrder::memory_order_relaxed);
						}
						else
						{
							SFLog(Telemetry, Debug3, "Posting failed sendRes:{0}", sendRes);
							break;
						}
					}

				}
				return true;
			}));

		m_Thread->Start();


		return ResultCode::SUCCESS;
	}

	void TelemetryBR::Terminate()
	{
		if (m_Thread != nullptr)
		{
			m_Thread->SetKillEvent();
		}

		m_Client.Terminate();

		if (m_Thread != nullptr)
		{
			m_Thread->Stop();
			m_Thread.reset();
		}

		m_EventQueue.SaveDelta();
	}

	TelemetryEvent* TelemetryBR::CreateTelemetryEvent(const char* eventName)
	{
		if (eventName == nullptr)
			return nullptr;

		if (!m_Client.IsValid())
			return nullptr;

		uint32_t eventId = m_EventId.fetch_add(1, MemoryOrder::memory_order_release) + 1;
		if (eventId == 0)
			eventId = m_EventId.fetch_add(1, MemoryOrder::memory_order_release) + 1;

		auto newEvent = new(GetSystemHeap()) TelemetryEventAvro(GetSystemHeap(), this, eventId);

		newEvent->Set(KeyName_ClientId, m_ClientId.data());
		newEvent->Set(KeyName_MachineId, m_MachineId.data());
		newEvent->Set(KeyName_SessionId, m_SessionId.data());
		newEvent->Set(KeyName_EventId, (int32_t)eventId);
		newEvent->Set(KeyName_EventName, eventName);

		return newEvent;
	}

	void TelemetryBR::EnqueueEvent(TelemetryEvent* pEvent)
	{
		m_EventQueue.EnqueueEvent(pEvent->GetEventId(), pEvent->GetSerializedData());
	}

}

