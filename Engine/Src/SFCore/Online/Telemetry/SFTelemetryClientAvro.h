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
#include "Online/Websocket/SFWebsocketClient.h"
#include "Online/Websocket/SFWebsocketClientCurl.h"
#include "Online/Telemetry/SFTelemetryEventQueue.h"
#include "Util/SFGuid.h"
#include "Util/SFGuidHelper.h"
#include "Avro/SFAvro.h"
#include "bson/bson.h"



namespace SF
{
	class TelemetryClientAvro;

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryEvent
	//

    //// Event creation wrapper for bson data
    //class TelemetryEventBson : public TelemetryEvent
    //{
    //protected:
    //    TelemetryEventBson(IHeap& heap, TelemetryClientAvro* pClient, uint32_t eventId, const char* eventName);
    //    friend class TelemetryClientAvro;

    //public:
    //    ~TelemetryEventBson();

    //    virtual ArrayView<const uint8_t> GetSerializedData() override;

    //    virtual TelemetryEvent& Set(const char* name, int value) override;
    //    virtual TelemetryEvent& Set(const char* name, int64_t value) override;
    //    virtual TelemetryEvent& Set(const char* name, float value) override;
    //    virtual TelemetryEvent& Set(const char* name, const char* value) override;
    //    virtual TelemetryEvent& Set(const String& name, int value) override;
    //    virtual TelemetryEvent& Set(const String& name, int64_t value) override;
    //    virtual TelemetryEvent& Set(const String& name, float value) override;
    //    virtual TelemetryEvent& Set(const String& name, const String& value) override;

    //private:
    //    bson_t m_Bson{};
    //    ArrayView<const uint8_t> m_BinData;
    //};



    // Event creation wrapper for Avro data
    class TelemetryEventAvro : public TelemetryEvent
    {
        using super = TelemetryEvent;

    protected:
        TelemetryEventAvro(IHeap& heap, TelemetryClientAvro* pClient, uint32_t eventId, const char* eventName, const AvroSchema& eventSchema);
        friend class TelemetryClientAvro;

        SF_FORCEINLINE AvroValue& GetAvroValue() { return m_AvroValue; }

    public:
        ~TelemetryEventAvro();

        SF_FORCEINLINE const AvroSchema& GetAvroSchema() const { return m_AvroSchema; }
        SF_FORCEINLINE const AvroValue& GetAvroValue() const { return m_AvroValue; }

        virtual void SetPlayEvent(bool bPlayEvent) override;

        virtual TelemetryEvent& Set(const char* name, bool value) override;
        virtual TelemetryEvent& Set(const char* name, int value) override;
        virtual TelemetryEvent& Set(const char* name, uint value) override;
        virtual TelemetryEvent& Set(const char* name, int64_t value) override;
        virtual TelemetryEvent& Set(const char* name, uint64_t value) override;
        virtual TelemetryEvent& Set(const char* name, float value) override;
        virtual TelemetryEvent& Set(const char* name, const char* value) override;
        virtual TelemetryEvent& Set(const char* name, const Guid& value) override;
        virtual TelemetryEvent& Set(const String& name, int value) override;
        virtual TelemetryEvent& Set(const String& name, int64_t value) override;
        virtual TelemetryEvent& Set(const String& name, float value) override;
        virtual TelemetryEvent& Set(const String& name, const String& value) override;

    private:
        AvroSchema m_AvroSchema;
        AvroValue m_AvroValue;
    };



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryClientAvro
	//

    class TelemetryClientAvro : public TelemetryService
    {
    public:

        static constexpr int64_t HeaderVersion = 4;
        static constexpr size_t MaxSerializationBufferSize = 6 * 1024;

		static constexpr char KeyName_AppId[] = "appid";
        static constexpr char KeyName_AuthKey[] = "authkey";
		static constexpr char KeyName_MachineId[] = "machineid";
		static constexpr char KeyName_SessionId[] = "sessionid";
		static constexpr char KeyName_EventId[] = "EventId";
		static constexpr char KeyName_Protocol[] = "SFTelemetry";
		static constexpr char KeyName_EventName[] = "EventName";

        static constexpr char FieldName_IsPlayEvent[] = "IsPlayEvent";
        static constexpr char FieldName_EventId[] = "EventId";
        static constexpr char FieldName_SessionId[] = "SessionId";
        static constexpr char FieldName_AppId[] = "AppId";
        static constexpr char FieldName_MachineId[] = "MachineId";
        static constexpr char FieldName_EventName[] = "EventName";
        static constexpr char FieldName_AccountId[] = "AccountId";

        using MyWebsocketClient = WebsocketClientCurl;

    public:

		TelemetryClientAvro();
        virtual ~TelemetryClientAvro();

		SF_FORCEINLINE IHeap& GetHeap() const { return GetSystemHeap(); }

        virtual Result Initialize(const String& url, const uint64_t& applicationId, const String& authKey, bool bUseEventFileCache);

		void Terminate();

        SF_FORCEINLINE bool IsInitialized() const { return m_Client.IsInitialized(); }
		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }

        SF_FORCEINLINE const uint64_t& GetApplicationId() const { return m_ApplicationId; }
        SF_FORCEINLINE const String& GetAuthKey() const { return m_AuthKey; }
        SF_FORCEINLINE const String& GetMachineId() const { return m_MachineId; }
        SF_FORCEINLINE const Guid& GetSessionId() const { return m_SessionId; }


        // register event schema
        // Need to be called before sending event with the name
        virtual Result RegisterEventSchema(const char* eventName, const char* eventSchema) override;

        virtual TelemetryEvent* CreateTelemetryEvent(const char* eventName) override;

	private:

		virtual void EnqueueEvent(TelemetryEvent* pEvent) override;
		friend class TelemetryEvent;

	private:

        uint64_t m_ApplicationId;
		String m_AuthKey;

		String m_MachineId;
        Guid m_SessionId;

		Atomic<uint32_t> m_EventId;
		Atomic<uint32_t> m_SentEventId;
		Atomic<uint32_t> m_AckedEventId;

        MyWebsocketClient m_Client;

		TelemetryEventQueue m_EventQueue;

		SFUniquePtr<Thread> m_Thread;

        std::unordered_map<std::string, UniquePtr<AvroSchema>> m_EventSchemas;

        GuidGenerator<std::mt19937_64> m_GuidGen;
    };


}

