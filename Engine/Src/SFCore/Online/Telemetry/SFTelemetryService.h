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

    class TelemetryBR;

    // Event creation wrapper
    class TelemetryEvent
    {
    protected:
        TelemetryEvent(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName);

    public:
        virtual ~TelemetryEvent();

        SF_FORCEINLINE uint32_t GetEventId() const { return m_EventId; }
        SF_FORCEINLINE const String& GetEventName() const { return m_EventName; }

        virtual void SetPlayEvent(bool bPlayEvent) { m_bPlayEvent = bPlayEvent; }
        bool IsPlayEvent() const { return m_bPlayEvent; }

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
        TelemetryBR* m_pClient{};
        bool m_bSent = false;
        uint32_t m_EventId{};
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

        virtual void SetAccountId(uint64_t accountId) {}

        virtual Result RegisterEventSchema(const char* eventName, const char* eventSchema) { return ResultCode::NOT_IMPLEMENTED; }
        virtual TelemetryEvent* CreateTelemetryEvent(const char* eventName) { return nullptr; }



    private:
    };



	namespace Service
	{
		extern ServiceInstance<TelemetryService> Telemetry;
	}

}

