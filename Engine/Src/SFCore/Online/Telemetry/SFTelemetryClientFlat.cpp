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

#include "Online/Telemetry/SFTelemetryClientFlat.h"
#include "Util/SFStringFormat.h"
#include "Util/SFLog.h"



namespace SF
{


    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEventBson
    //


    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEventFlat
    //

    TelemetryEventFlat::TelemetryEventFlat(IHeap& heap, TelemetryClientFlat* pClient, uint32_t eventId, const char* eventName)
        : TelemetryEvent(heap, pClient, eventId, eventName)
    {
    }

    TelemetryEventFlat::~TelemetryEventFlat()
    {
    }

    void TelemetryEventFlat::SetPlayEvent(bool bPlayEvent)
    {
        super::SetPlayEvent(bPlayEvent);
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, bool value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            Flat::Telemetry::EventAttributeValue_EventAttributeBool,
            SF::Flat::Telemetry::CreateEventAttributeBool(m_FlatBufferBuilder, value).Union());

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, int value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            Flat::Telemetry::EventAttributeValue_EventAttributeInt,
            SF::Flat::Telemetry::CreateEventAttributeInt(m_FlatBufferBuilder, value).Union());

        m_Attributes.push_back(attributeOffset);
        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, uint value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            Flat::Telemetry::EventAttributeValue_EventAttributeUInt,
            SF::Flat::Telemetry::CreateEventAttributeUInt(m_FlatBufferBuilder, value).Union());

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, int64_t value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            Flat::Telemetry::EventAttributeValue_EventAttributeInt64,
            SF::Flat::Telemetry::CreateEventAttributeInt64(m_FlatBufferBuilder, value).Union());

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, uint64_t value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            Flat::Telemetry::EventAttributeValue_EventAttributeUInt64,
            SF::Flat::Telemetry::CreateEventAttributeUInt64(m_FlatBufferBuilder, value).Union());

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, float value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            Flat::Telemetry::EventAttributeValue_EventAttributeFloat,
            SF::Flat::Telemetry::CreateEventAttributeFloat(m_FlatBufferBuilder, value).Union());

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const char* name, const char* value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            SF::Flat::Telemetry::EventAttributeValue_EventAttributeString,
            SF::Flat::Telemetry::CreateEventAttributeString(m_FlatBufferBuilder, m_FlatBufferBuilder.CreateString(value)).Union()
        );

        m_Attributes.push_back(attributeOffset);

        return *this;
    }


    TelemetryEvent& TelemetryEventFlat::Set(const String& name, int value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            SF::Flat::Telemetry::EventAttributeValue_EventAttributeInt,
            SF::Flat::Telemetry::CreateEventAttributeInt(m_FlatBufferBuilder, value).Union()
        );

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const String& name, int64_t value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            SF::Flat::Telemetry::EventAttributeValue_EventAttributeInt64,
            SF::Flat::Telemetry::CreateEventAttributeInt64(m_FlatBufferBuilder, value).Union()
        );

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const String& name, float value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            SF::Flat::Telemetry::EventAttributeValue_EventAttributeFloat,
            SF::Flat::Telemetry::CreateEventAttributeFloat(m_FlatBufferBuilder, value).Union()
        );

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

    TelemetryEvent& TelemetryEventFlat::Set(const String& name, const String& value)
    {
        auto nameOffset = m_FlatBufferBuilder.CreateString(name);

        auto attributeOffset = SF::Flat::Telemetry::CreateEventAttribute(m_FlatBufferBuilder, nameOffset,
            SF::Flat::Telemetry::EventAttributeValue_EventAttributeString,
            SF::Flat::Telemetry::CreateEventAttributeString(m_FlatBufferBuilder, m_FlatBufferBuilder.CreateString(value)).Union()
        );

        m_Attributes.push_back(attributeOffset);

        return *this;
    }

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryClientFlat
	//

	TelemetryClientFlat::TelemetryClientFlat()
		: m_Client(GetSystemHeap())
		, m_EventQueue(GetSystemHeap())
	{
	}

	TelemetryClientFlat::~TelemetryClientFlat()
	{
		Terminate();
	}

	Result TelemetryClientFlat::Initialize(const String& url, const uint64_t& applicationId, const String& authKey, bool bUseEventFileCache)
	{
		Result hr;

        m_ApplicationId.Format("{0}", applicationId);
		m_AuthKey = authKey;

		m_MachineId = Util::GetMachineUniqueId();
        m_SessionId = m_GuidGen.NewGuid();
        char sessionIdString[128]{};
        m_SessionId.ToString(sessionIdString);

        SFLog(Telemetry, Info, "Telemetry session initialized, machine:{0}, sessionId:{1}", m_MachineId, sessionIdString);

		m_Client.SetUseTickThread(false); // We are using manual ticking
        m_Client.SetReconnectOnDisconnected(true);

        char sessionId[128]{}, appId[128];
        m_SessionId.ToString(sessionId);

        StrUtil::Format(appId, "{0}", m_ApplicationId);

        m_Client.AddParameter(KeyName_AppId, appId);
        m_Client.AddParameter(KeyName_AccessKey, m_AuthKey);

		m_Client.OnRecvEvent().AddDelegate(uintptr_t(this), [&](const Array<uint8_t>& data)
			{
                OnRecv(data);
			});

		hr = m_Client.Initialize(url, KeyName_Protocol);
		if (!hr)
			return hr;

		m_EventQueue.Initialize(bUseEventFileCache);

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
				if (!m_Client.IsInitialized())
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

	void TelemetryClientFlat::Terminate()
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

	TelemetryEvent* TelemetryClientFlat::CreateTelemetryEvent(const char* eventName)
	{
        Result hr;
		if (eventName == nullptr)
			return nullptr;

		if (!m_Client.IsInitialized())
			return nullptr;

		uint32_t eventId = m_EventId.fetch_add(1, MemoryOrder::memory_order_release) + 1;
		if (eventId == 0)
			eventId = m_EventId.fetch_add(1, MemoryOrder::memory_order_release) + 1;

		auto newEvent = new(GetSystemHeap()) TelemetryEventFlat(GetSystemHeap(), this, eventId, eventName);

		return newEvent;
	}

	void TelemetryClientFlat::EnqueueEvent(TelemetryEvent* pInEvent)
	{
        auto* pEvent = static_cast<TelemetryEventFlat*>(pInEvent);
        if (pEvent == nullptr)
            return;

        uint32_t eventId = pEvent->GetEventId();

        ::flatbuffers::FlatBufferBuilder& packetBuilder = pEvent->GetPacketBuilder();

        Guid sessionId = GetSessionId();
        ArrayView<const uint8_t> sessionIdView(sizeof(Guid), (uint8_t*)sessionId.data);
        ::flatbuffers::Offset<::flatbuffers::Vector<uint8_t>> sessionIdOffset = packetBuilder.CreateVector(sessionIdView.data(), sessionIdView.size());

        ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<SF::Flat::Telemetry::EventAttribute>>> attributesOffset = packetBuilder.CreateVector(pEvent->GetAttributeOffesets());

        ::flatbuffers::Offset<FlatPostEventRequest> payloadOffset = SF::Flat::Telemetry::CreatePostEventRequest(packetBuilder,
            packetBuilder.CreateString(pEvent->GetEventName().data()), Util::Time.GetRawUTCMs().time_since_epoch().count(),
            packetBuilder.CreateString(GetApplicationId().data()),
            packetBuilder.CreateString(GetMachineId().data()),
            eventId, GetAccountId(), pEvent->IsPlayEvent(),
            sessionIdOffset, attributesOffset
            );

        
        ::flatbuffers::Offset<FlatTelemetryPacket> packetOffset = SF::Flat::Telemetry::CreateTelemetryPacket(packetBuilder, eventId,
            SF::Flat::Telemetry::PayloadData_PostEventRequest,
            payloadOffset.Union());


        packetBuilder.FinishSizePrefixed(packetOffset);

        ArrayView<uint8_t> packetBufferView(packetBuilder.GetSize(), (uint8_t*)packetBuilder.GetBufferPointer());

		m_EventQueue.EnqueueEvent(pEvent->GetEventId(), ArrayView<const uint8_t>(packetBufferView));
	}

    Result TelemetryClientFlat::OnRecv(const Array<uint8_t>& recvData)
    {
        Result hr;

        // Probably heartbeat packet?
        if (recvData.size() == 0)
            return hr;

        uint expectedSize = flatbuffers::GetSizePrefixedBufferLength(recvData.data());
        if (recvData.size() != expectedSize)
        {
            SFLog(System, Warning, "Telemetry received unexpected data size: expected:{0}, received:{1}", expectedSize, recvData.size());
            return ResultCode::INVALID_FORMAT;
        }

        const Flat::Telemetry::TelemetryPacket* requestPacket = Flat::Telemetry::GetSizePrefixedTelemetryPacket((const void*)recvData.data());
        if (requestPacket == nullptr)
        {
            return ResultCode::INVALID_FORMAT;
        }

        uint32_t eventId = requestPacket->request_id();

        m_EventQueue.FreePostedEvents(eventId);

        if (!hr)
        {
            SFLog(System, Error, "ObjectDirectory: failed with hr:{0}", hr);
        }

        return hr;
    }

}

