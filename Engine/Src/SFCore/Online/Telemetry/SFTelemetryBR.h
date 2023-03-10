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
#include "Online/Telemetry/SFTelemetryEventQueue.h"
#include "Util/SFGuid.h"
#include "Avro/SFAvro.h"
#include "bson/bson.h"



namespace SF
{
	class TelemetryBR;

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryEvent
	//

	// Event creation wrapper
	class TelemetryEvent
	{
	protected:
		TelemetryEvent(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName);

	public:
		~TelemetryEvent();

		SF_FORCEINLINE uint32_t GetEventId() const { return m_EventId; }
        SF_FORCEINLINE const String& GetEventName() const { return m_EventName; }
        virtual const AvroSchema& GetAvroSchema() const = 0;
        virtual const AvroValue& GetAvroValue() const = 0;

		virtual TelemetryEvent& Set(const char* name, int value) = 0;
		virtual TelemetryEvent& Set(const char* name, int64_t value) = 0;
		virtual TelemetryEvent& Set(const char* name, float value) = 0;
		virtual TelemetryEvent& Set(const char* name, const char* value) = 0;
		virtual TelemetryEvent& Set(const String& name, int value) = 0;
		virtual TelemetryEvent& Set(const String& name, int64_t value) = 0;
		virtual TelemetryEvent& Set(const String& name, float value) = 0;
		virtual TelemetryEvent& Set(const String& name, const String& value) = 0;

		virtual void PostEvent();

	protected:
		IHeap& m_Heap;
		TelemetryBR* m_pClient{};
		bool m_bSent = false;
		uint32_t m_EventId{};
        String m_EventName;
	};


    //// Event creation wrapper for bson data
    //class TelemetryEventBson : public TelemetryEvent
    //{
    //protected:
    //    TelemetryEventBson(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName);
    //    friend class TelemetryBR;

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
    protected:
        TelemetryEventAvro(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName, const AvroSchema& eventSchema);
        friend class TelemetryBR;

    public:
        ~TelemetryEventAvro();

        virtual const AvroSchema& GetAvroSchema() const override { return m_AvroSchema; }
        virtual const AvroValue& GetAvroValue() const override { return m_AvroValue; }

        virtual TelemetryEvent& Set(const char* name, int value) override;
        virtual TelemetryEvent& Set(const char* name, int64_t value) override;
        virtual TelemetryEvent& Set(const char* name, float value) override;
        virtual TelemetryEvent& Set(const char* name, const char* value) override;
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
	//	class TelemetryBR
	//

    class TelemetryBR : public TelemetryService
    {
    public:

        static constexpr int64_t HeaderVersion = 1;

        static constexpr size_t MaxSerializationBufferSize = 6 * 1024;

		static constexpr char KeyName_AuthHeader[] = "sftelemetry:";
		static constexpr int KeyName_AuthHeaderLen = sizeof(KeyName_AuthHeader) - 1; // without null terminator
		static constexpr char KeyName_ClientId[] = "clientid";
        static constexpr char KeyName_AuthKey[] = "authkey";
		static constexpr char KeyName_MachineId[] = "machineid";
		static constexpr char KeyName_SessionId[] = "sessionid";
        static constexpr char KeyName_DataType[] = "datatype";
		static constexpr char KeyName_EventId[] = "EventId";
		static constexpr char KeyName_Protocol[] = "SFTelemetry";
		static constexpr char KeyName_EventName[] = "EventName";


    public:

		TelemetryBR();
        virtual ~TelemetryBR();

		SF_FORCEINLINE IHeap& GetHeap() const { return GetSystemHeap(); }

        virtual Result Initialize(const String& serverAddress, int port, const uint64_t& clientId, const String& authKey);

		void Terminate();


		SF_FORCEINLINE bool IsValid() const { return m_Client.IsValid(); }

		SF_FORCEINLINE bool IsConnected() const { return m_Client.IsConnected(); }

        SF_FORCEINLINE const uint64_t& GetClientId() const { return m_ClientId; }
        SF_FORCEINLINE const String& GetAuthKey() const { return m_AuthKey; }
        SF_FORCEINLINE const String& GetMachineId() const { return m_MachineId; }
        SF_FORCEINLINE const Guid& GetSessionId() const { return m_SessionId; }


        // register event schema
        // Need to be called before sending event with the name
        Result RegisterEventSchema(const char* eventName, const char* eventSchema);

		TelemetryEvent* CreateTelemetryEvent(const char* eventName);

	private:

		void EnqueueEvent(TelemetryEvent* pEvent);
		friend class TelemetryEvent;

	private:

        uint64_t m_ClientId;
		String m_AuthKey;

		String m_MachineId;
        Guid m_SessionId;

		Atomic<uint32_t> m_EventId;
		Atomic<uint32_t> m_SentEventId;
		Atomic<uint32_t> m_AckedEventId;

		WebsocketClient m_Client;

		TelemetryEventQueue m_EventQueue;

		SFUniquePtr<Thread> m_Thread;

        std::unordered_map<std::string, UniquePtr<AvroSchema>> m_EventSchemas;

        GuidGenerator<std::mt19937_64> m_GuidGen;
    };


}

