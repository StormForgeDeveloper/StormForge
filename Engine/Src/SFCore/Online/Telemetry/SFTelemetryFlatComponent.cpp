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

	TelemetryFlatComponent::TelemetryFlatComponent(const String& address, uint64_t clientId, const String& authTicket, bool bUseEventCacheFile)
        : LibraryComponent(TypeName)
        , m_Address(address)
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
        super::InitializeComponent();

        m_TelemetryPtr.reset(new(GetSystemHeap()) TelemetryClientFlat());

        int iSplitter = m_Address.IndexOfAnyFromEnd(",:");
        if (iSplitter < 0)
            return ResultCode::INVALID_ARG;

        String address = m_Address.SubString(0, iSplitter);
        int port = std::atol(m_Address.data() + iSplitter + 1);

        SFLog(Telemetry, Info, "Telemetry initialize: {0}, clientId:{1}", m_Address, m_ClientId);

        Result hr = m_TelemetryPtr->Initialize(address, port, m_ClientId, m_AuthTicket, m_bUseEventCacheFile);
        if (!hr)
            return hr;

        // Registering default schema
        //m_TelemetryPtr->RegisterEventSchema("Login", LoginSchema);
        //m_TelemetryPtr->RegisterEventSchema("SignUp", SignUpSchema);
        //m_TelemetryPtr->RegisterEventSchema("UseItem", UseItemSchema);
        //m_TelemetryPtr->RegisterEventSchema("FishingFinished", FishingFinishedSchema);

        Service::Telemetry = m_TelemetryPtr.get();

		return ResultCode::SUCCESS;
	}

    void TelemetryFlatComponent::DeinitializeComponent()
    {
        Service::Telemetry = nullptr;

        m_TelemetryPtr->Terminate();
        m_TelemetryPtr.reset();

        super::DeinitializeComponent();
    }
}

