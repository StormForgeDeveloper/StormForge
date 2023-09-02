////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TelemetryService 
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Task/SFTask.h"
#include "Util/SFLog.h"
#include "Online/Telemetry/SFTelemetryService.h"
#include "Online/Websocket/SFWebsocketClientCurl.h"
#include "Online/Telemetry/SFTelemetryEventQueue.h"
#include "Util/SFGuid.h"
#include "SFFLat/Telemetry_generated.h"


namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryEvent
	//

    class TelemetryClientFlat;

    using FlatTelemetryPacketBuilder = SF::Flat::Telemetry::TelemetryPacketBuilder;
    using FlatTelemetryPacket = SF::Flat::Telemetry::TelemetryPacket;
    using FlatPostEventRequest = SF::Flat::Telemetry::PostEventRequest;
    using FlatPostEventResult = SF::Flat::Telemetry::PostEventResult;


    // Event creation wrapper for Avro data
    class TelemetryEventFlat : public TelemetryEvent
    {
        using super = TelemetryEvent;

    protected:
        TelemetryEventFlat(IHeap& heap, TelemetryClientFlat* pClient, uint32_t eventId, const char* eventName);
        friend class TelemetryClientFlat;

        SF_FORCEINLINE ::flatbuffers::FlatBufferBuilder& GetPacketBuilder() { return m_FlatBufferBuilder; }
        SF_FORCEINLINE std::vector<::flatbuffers::Offset<SF::Flat::Telemetry::EventAttribute>>& GetAttributeOffesets() { return m_Attributes; }

    public:
        ~TelemetryEventFlat();

        virtual void SetPlayEvent(bool bPlayEvent) override;

        virtual TelemetryEvent& Set(const char* name, bool value) override;
        virtual TelemetryEvent& Set(const char* name, int value) override;
        virtual TelemetryEvent& Set(const char* name, uint value) override;
        virtual TelemetryEvent& Set(const char* name, int64_t value) override;
        virtual TelemetryEvent& Set(const char* name, uint64_t value) override;
        virtual TelemetryEvent& Set(const char* name, float value) override;
        virtual TelemetryEvent& Set(const char* name, const char* value) override;
        virtual TelemetryEvent& Set(const String& name, int value) override;
        virtual TelemetryEvent& Set(const String& name, int64_t value) override;
        virtual TelemetryEvent& Set(const String& name, float value) override;
        virtual TelemetryEvent& Set(const String& name, const String& value) override;

    private:

        // Flat buffer builder
        ::flatbuffers::FlatBufferBuilder m_FlatBufferBuilder;

        std::vector<::flatbuffers::Offset<SF::Flat::Telemetry::EventAttribute>> m_Attributes;
    };



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryClientFlat
	//

    class TelemetryClientFlat : public TelemetryService
    {
    public:

        static constexpr int64_t HeaderVersion = 4;
        static constexpr size_t MaxSerializationBufferSize = 6 * 1024;

		static constexpr char KeyName_AppId[] = "appid";
        static constexpr char KeyName_AccessKey[] = "AccessKey";
        static constexpr char KeyName_Protocol[] = "SFTelemetry";

        static constexpr char FieldName_IsPlayEvent[] = "IsPlayEvent";
        static constexpr char FieldName_EventId[] = "EventId";
        static constexpr char FieldName_SessionId[] = "SessionId";
        static constexpr char FieldName_AppId[] = "AppId";
        static constexpr char FieldName_MachineId[] = "MachineId";
        static constexpr char FieldName_EventName[] = "EventName";
        static constexpr char FieldName_AccountId[] = "AccountId";

        using MyWebsocketClient = WebsocketClientCurl;

    public:

		TelemetryClientFlat();
        virtual ~TelemetryClientFlat();

		SF_FORCEINLINE IHeap& GetHeap() const { return GetSystemHeap(); }

        virtual Result Initialize(const String& url, const uint64_t& applicationId, const String& authKey, bool bUseEventFileCache);
		void Terminate();

        virtual Result RegisterEventSchema(const char* eventName, const char* eventSchema) override
        {
            // Nothing to do
            return ResultCode::SUCCESS;
        }

        SF_FORCEINLINE bool IsInitialized() const { return m_Client.IsInitialized(); }
		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }

        SF_FORCEINLINE const String& GetApplicationId() const { return m_ApplicationId; }
        SF_FORCEINLINE const String& GetAuthKey() const { return m_AuthKey; }
        SF_FORCEINLINE const String& GetMachineId() const { return m_MachineId; }
        SF_FORCEINLINE const Guid& GetSessionId() const { return m_SessionId; }
        SF_FORCEINLINE const uint64_t& GetAccountId() const { return m_AccountId; }

        virtual void SetAccountId(uint64_t accountId) override { m_AccountId = accountId; }


        // register event schema
        // Need to be called before sending event with the name
        //virtual Result RegisterEventSchema(const char* eventName, const char* eventSchema) override;

        virtual TelemetryEvent* CreateTelemetryEvent(const char* eventName) override;

	private:

		virtual void EnqueueEvent(TelemetryEvent* pEvent) override;

        Result OnRecv(const Array<uint8_t>& recvData);

		friend class TelemetryEvent;

	private:

        String m_ApplicationId;
		String m_AuthKey;

		String m_MachineId;
        Guid m_SessionId;
        uint64_t m_AccountId{};

		Atomic<uint32_t> m_EventId;
		Atomic<uint32_t> m_SentEventId;
		Atomic<uint32_t> m_AckedEventId;

        MyWebsocketClient m_Client;

		TelemetryEventQueue m_EventQueue;

		SFUniquePtr<Thread> m_Thread;

        GuidGenerator<std::mt19937_64> m_GuidGen;
    };


}

