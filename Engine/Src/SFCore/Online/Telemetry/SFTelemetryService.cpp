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

#include "Online/Telemetry/SFTelemetryService.h"
#include "Online/Telemetry/SFTelemetryBR.h"
#include "Util/SFStringFormat.h"


#include <libwebsockets.h>


namespace SF
{

	namespace Log
	{
		LogChannel Telemetry("Telemetry", LogOutputType::Debug3);
	};

	namespace Service
	{
		ServiceInstance<TelemetryService> Telemetry;
	}



    ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //	class TelemetryEvent
    //

    TelemetryEvent::TelemetryEvent(IHeap& heap, TelemetryBR* pClient, uint32_t eventId, const char* eventName)
        : m_Heap(heap)
        , m_pClient(pClient)
        , m_EventId(eventId)
        , m_EventName(eventName)
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
    //	class TelemetryService
    //

	TelemetryService::TelemetryService()
	{

	}
	TelemetryService::~TelemetryService()
	{

	}


}

