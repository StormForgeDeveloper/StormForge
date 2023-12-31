////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Telemetry component FLatbuffer version
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "Online/Telemetry/SFTelemetryFlatComponent.h"
#include "Online/Websocket/SFWebsocketComponent.h"
#include "Online/Telemetry/SFTelemetryService.h"
#include "Util/SFStringFormat.h"
#include "Online/Telemetry/SFTelemetryClientFlat.h"


namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryFlatComponent
	//

	TelemetryFlatComponent::TelemetryFlatComponent(const String& url, uint64_t clientId, const String& authTicket, bool bUseEventCacheFile)
        : LibraryComponent(TypeName)
        , m_Url(url)
        , m_ClientId(clientId)
        , m_AuthTicket(authTicket)
        , m_bUseEventCacheFile(bUseEventCacheFile)
    {
        AddDependency<WebsocketComponent>();

	}

	TelemetryFlatComponent::~TelemetryFlatComponent()
	{

	}

	Result TelemetryFlatComponent::InitializeComponent()
	{
        Result hr;
        super::InitializeComponent();

        if (m_Url.IsNullOrEmpty())
        {
            SFLog(Telemetry, Info, "Telemetry is not configured");
            return hr;
        }

        m_TelemetryPtr.reset(new(GetSystemHeap()) TelemetryClientFlat());

        SFLog(Telemetry, Info, "Telemetry initialize: {0}, clientId:{1}", m_Url, m_ClientId);

        hr = m_TelemetryPtr->Initialize(m_Url, m_ClientId, m_AuthTicket, m_bUseEventCacheFile);
        if (!hr.IsSuccess())
            return hr;

        Service::Telemetry = m_TelemetryPtr.get();

		return hr;
	}

    void TelemetryFlatComponent::DeinitializeComponent()
    {
        Service::Telemetry = nullptr;

        m_TelemetryPtr->Terminate();
        m_TelemetryPtr.reset();

        super::DeinitializeComponent();
    }
}

