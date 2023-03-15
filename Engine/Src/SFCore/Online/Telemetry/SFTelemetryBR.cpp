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


    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEventBson
    //

 //   TelemetryEventBson::TelemetryEventBson(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName)
	//	: TelemetryEvent(heap, pClient, eventId, eventName)
	//{
	//	bson_init(&m_Bson);
	//}

	//TelemetryEventBson::~TelemetryEventBson()
	//{
	//	bson_destroy(&m_Bson);
	//}

 //   ArrayView<const uint8_t> TelemetryEventBson::GetSerializedData()
	//{
 //       if (m_pClient == nullptr)
 //           return m_BinData;

 //       Set(TelemetryBR::KeyName_ClientId, m_pClient->GetClientId().data());
 //       Set(TelemetryBR::KeyName_MachineId, m_pClient->GetMachineId().data());
 //       Set(TelemetryBR::KeyName_SessionId, m_pClient->GetSessionId().data());
 //       Set(TelemetryBR::KeyName_EventId, (int32_t)m_EventId);
 //       Set(TelemetryBR::KeyName_EventName, GetEventName().data());

	//	m_BinData.SetLinkedBuffer(size_t(m_Bson.len), bson_get_data(&m_Bson));

	//	return m_BinData;
	//}

	//TelemetryEvent& TelemetryEventBson::Set(const char* name, int value)
	//{
	//	bson_append_int32(&m_Bson, name, (int)strlen(name), value);
	//	return *this;
	//}

 //   TelemetryEvent& TelemetryEventBson::Set(const char* name, int64_t value)
	//{
	//	bson_append_int64(&m_Bson, name, (int)strlen(name), value);
	//	return *this;
	//}

 //   TelemetryEvent& TelemetryEventBson::Set(const char* name, float value)
	//{
	//	bson_append_double(&m_Bson, name, (int)strlen(name), value);
	//	return *this;
	//}

 //   TelemetryEvent& TelemetryEventBson::Set(const char* name, const char* value)
	//{
	//	bson_append_utf8(&m_Bson, name, (int)strlen(name), value, (int)strlen(value));
	//	return *this;
	//}


 //   TelemetryEvent& TelemetryEventBson::Set(const String& name, int value)
	//{
	//	bson_append_int32(&m_Bson, name, (int)name.length(), value);
	//	return *this;
	//}

 //   TelemetryEvent& TelemetryEventBson::Set(const String& name, int64_t value)
	//{
	//	bson_append_int64(&m_Bson, name, (int)name.length(), value);
	//	return *this;
	//}

 //   TelemetryEvent& TelemetryEventBson::Set(const String& name, float value)
	//{
	//	bson_append_double(&m_Bson, name, (int)name.length(), value);
	//	return *this;
	//}

 //   TelemetryEvent& TelemetryEventBson::Set(const String& name, const String& value)
	//{
	//	bson_append_utf8(&m_Bson, name, (int)name.length(), value, (int)value.length());
	//	return *this;
	//}


    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEventAvro
    //

    TelemetryEventAvro::TelemetryEventAvro(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName, const AvroSchema& eventSchema)
        : TelemetryEvent(heap, pClient, eventId, eventName)
        , m_AvroSchema(eventSchema)
        , m_AvroValue(eventSchema)
    {
    }

    TelemetryEventAvro::~TelemetryEventAvro()
    {
    }

    //ArrayView<const uint8_t> TelemetryEventAvro::GetSerializedData()
    //{
    //    if (m_BinData.size() > 0)
    //        return m_BinData;

    //    m_BinData.resize(1024 * 10); // max event size
    //    AvroWriter writer(m_BinData);

    //    // avro streaming mode
    //    writer.WriteString(m_EventSchema);
    //    writer.WriteValue(m_AvroValue);

    //    m_BinData.resize(writer.WrittenSize());

    //    return m_BinData;
    //}

    void TelemetryEventAvro::SetPlayEvent(bool bPlayEvent)
    {
        super::SetPlayEvent(bPlayEvent);

        m_AvroValue.SetValue(TelemetryBR::FieldName_IsPlayEvent, bPlayEvent);
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

	Result TelemetryBR::Initialize(const String& serverAddress, int port, const uint64_t& clientId, const String& authKey)
	{
		Result hr;

		m_ClientId = clientId;
		m_AuthKey = authKey;

		m_MachineId = Util::GetMachineUniqueId();
        m_SessionId = m_GuidGen.NewGuid();
        char sessionIdString[128]{};
        m_SessionId.ToString(sessionIdString);

        SFLog(Telemetry, Info, "Telemetry session initialized, machine:{0}, sessionId:{1}", m_MachineId, sessionIdString);

		m_Client.SetUseTickThread(false); // We are using manual ticking
		m_Client.SetClientAppendHeaderFunction([&](struct lws* wsi, void* user, void* in, size_t len)
			{
                char sessionId[128]{};
                m_SessionId.ToString(sessionId);

				unsigned char** p = (unsigned char**)in, * end = (*p) + len;
				String HeaderString;
				HeaderString.Format("{0}={1};{2}={3};{4}={5};{6}={7};{8}={9}", 
					KeyName_ClientId, m_ClientId,
					KeyName_AuthKey, m_AuthKey,
					KeyName_MachineId, m_MachineId, 
					KeyName_SessionId, sessionId,
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
                    uint32_t eventId = *pEventId;
					m_EventQueue.FreePostedEvents(eventId);
					//SFLog(Telemetry, Debug3, "Client Recv Ack eventId:{0}", eventId);
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
						auto sendRes = m_Client.Send(ArrayView<uint8_t>(pEventItem->GetDataSize() - sizeof(curEventId), (uint8_t*)pEventItem->GetDataPtr() + sizeof(curEventId)));
						if (sendRes)
						{
							m_SentEventId.store(curEventId, MemoryOrder::memory_order_relaxed);
						}
						else
						{
							SFLog(Telemetry, Error, "Posting failed sendRes:{0}", sendRes);
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

    Result TelemetryBR::RegisterEventSchema(const char* eventName, const char* eventSchema)
    {
        Result hr;

        auto newSchema = new AvroSchema;
        hr = newSchema->Init(String(eventSchema));
        if (!hr)
        {
            SFLog(Telemetry, Error, "RegisterEventSchema failed, hr:{0}", hr);
            return hr;
        }

        newSchema->AppendFieldBool(FieldName_IsPlayEvent);
        newSchema->AppendFieldInt(FieldName_EventId);
        newSchema->AppendFieldBytes(FieldName_SessionId);
        newSchema->AppendFieldInt64(FieldName_ClientId);
        newSchema->AppendFieldString(FieldName_MachineId);

        m_EventSchemas.insert(std::make_pair(eventName, newSchema));

        return hr;
    }

	TelemetryEvent* TelemetryBR::CreateTelemetryEvent(const char* eventName)
	{
        Result hr;
		if (eventName == nullptr)
			return nullptr;

		if (!m_Client.IsValid())
			return nullptr;

        auto itSchema = m_EventSchemas.find(eventName);
        if (itSchema == m_EventSchemas.end())
        {
            SFLog(Telemetry, Debug3, "Event schema not found call RegisterEventSchema first. event:{0}", eventName);
            return nullptr;
        }

		uint32_t eventId = m_EventId.fetch_add(1, MemoryOrder::memory_order_release) + 1;
		if (eventId == 0)
			eventId = m_EventId.fetch_add(1, MemoryOrder::memory_order_release) + 1;

		auto newEvent = new(GetSystemHeap()) TelemetryEventAvro(GetSystemHeap(), this, eventId, eventName, *itSchema->second);

        if (newEvent)
        {
            AvroValue& avroValue = newEvent->GetAvroValue();

            Guid sessionId = GetSessionId();
            ArrayView<const uint8_t> sessionIdView(sizeof(Guid), (uint8_t*)sessionId.data);

            hr = avroValue.SetValue(FieldName_SessionId, sessionIdView);
            if (!hr)
                return nullptr;
            //hr = avroValue.SetValue(FieldName_EventId, (int)newEvent->GetEventId());
            hr = avroValue.SetValue(FieldName_ClientId, (int64_t)GetClientId());
            if (!hr)
                return nullptr;
            hr = avroValue.SetValue(FieldName_MachineId, GetMachineId());
            if (!hr)
                return nullptr;
        }

		return newEvent;
	}

	void TelemetryBR::EnqueueEvent(TelemetryEvent* pInEvent)
	{
        auto* pEvent = static_cast<TelemetryEventAvro*>(pInEvent);
        if (pEvent == nullptr)
            return;

        // Serialization buffer
        DynamicArray<char> serializationBuffer;

        if (serializationBuffer.size() == 0)
            serializationBuffer.resize(MaxSerializationBufferSize);

        AvroWriter writer(serializationBuffer);

        Guid sessionId = GetSessionId();
        ArrayView<const uint8_t> sessionIdView(sizeof(Guid), (uint8_t*)sessionId.data);

        // avro streaming mode
        writer.WriteInt64(HeaderVersion);
        writer.WriteInt64(pEvent->GetEventId());
        writer.WriteBytes(sessionIdView);

        writer.WriteString(pEvent->GetAvroSchema().GetSchemaString());
        writer.WriteValue(pEvent->GetAvroValue());

        serializationBuffer.resize(writer.WrittenSize());

#if 0 // Test deserialization
        {
            ArrayView<char> dataView(serializationBuffer);
            SF::AvroReader avroReader(dataView);

            auto headerVersion = avroReader.ReadInt64();
            if (headerVersion != TelemetryBR::HeaderVersion)
            {
                return;
            }

            auto testEventId = (uint32_t)avroReader.ReadInt64();

            Guid testSessionId;
            ArrayView<uint8_t> guidDataView(sizeof(testSessionId.data), testSessionId.data);
            avroReader.ReadBytes(guidDataView);
            if (testSessionId != sessionId)
            {
                return;
            }

            String schemaString = avroReader.ReadString();
            AvroSchema readSchema(schemaString);
            AvroValue readValue(readSchema);
            avroReader.ReadValue(readValue);
            ArrayView<const uint8_t> readSessionId = readValue.GetFieldValue<ArrayView<const uint8_t>>(FieldName_SessionId);
            Guid readSessionGuId = *(Guid*)readSessionId.data();
            bool readIsPlayEvent = readValue.GetFieldValue<bool>(FieldName_IsPlayEvent);
            String readMachineId = readValue.GetFieldValue<String>(FieldName_MachineId);
            int readClientId = readValue.GetFieldValue<int64_t>(FieldName_ClientId);
            int readClientId2 = readValue.GetFieldValue<int>(FieldName_ClientId);
        }
#endif

		m_EventQueue.EnqueueEvent(pEvent->GetEventId(), ArrayView<const uint8_t>(serializationBuffer));
	}

}

