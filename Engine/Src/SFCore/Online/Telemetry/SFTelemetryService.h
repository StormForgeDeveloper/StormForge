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


namespace SF
{

    namespace Log
    {
        extern LogChannel Telemetry;
    };

    class TelemetryService;
    using TelemetryClient = TelemetryService;

    // Event creation wrapper
    class TelemetryEvent
    {
    protected:
        TelemetryEvent(IHeap& heap, TelemetryClient* pClient, uint32_t eventId, const char* eventName);

    public:
        virtual ~TelemetryEvent();

        SF_FORCEINLINE uint32_t GetEventId() const { return m_EventId; }
        SF_FORCEINLINE const String& GetEventName() const { return m_EventName; }

        virtual void SetPlayEvent(bool bPlayEvent) { m_bPlayEvent = bPlayEvent; }
        bool IsPlayEvent() const { return m_bPlayEvent; }

        virtual void SetAccountID(uint64_t accountId) { m_AccountId = accountId; }
        uint64_t GetAccountID() const { return m_AccountId; }

        virtual TelemetryEvent& Set(const char* name, bool value) = 0;
        virtual TelemetryEvent& Set(const char* name, int value) = 0;
        virtual TelemetryEvent& Set(const char* name, uint value) = 0;
        virtual TelemetryEvent& Set(const char* name, int64_t value) = 0;
        virtual TelemetryEvent& Set(const char* name, uint64_t value) = 0;
        virtual TelemetryEvent& Set(const char* name, float value) = 0;
        virtual TelemetryEvent& Set(const char* name, const char* value) = 0;
        virtual TelemetryEvent& Set(const String& name, int value) = 0;
        virtual TelemetryEvent& Set(const String& name, int64_t value) = 0;
        virtual TelemetryEvent& Set(const String& name, float value) = 0;
        virtual TelemetryEvent& Set(const String& name, const String& value) = 0;

        virtual void PostEvent();

    protected:
        IHeap& m_Heap;
        TelemetryClient* m_pClient{};
        bool m_bSent = false;
        uint32_t m_EventId{};
        uint64_t m_AccountId{};
        String m_EventName;
        bool m_bPlayEvent{};
    };

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryService
	//

    class TelemetryService
    {
    public:

        TelemetryService();
        virtual ~TelemetryService();

        void SetAccountID(uint64_t accountId) { m_AccountId = accountId; }
        uint64_t GetAccountID() const { return m_AccountId; }

        virtual Result RegisterEventSchema(const char* eventName, const char* eventSchema) { return ResultCode::NOT_IMPLEMENTED; }
        virtual TelemetryEvent* CreateTelemetryEvent(const char* eventName) { return nullptr; }

        virtual void EnqueueEvent(TelemetryEvent* pEvent) {}

    private:

        uint64_t m_AccountId{};
    };


	namespace Service
	{
		extern ServiceInstance<TelemetryService> Telemetry;
	}

}

