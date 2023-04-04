////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TelemetryComponent warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "Online/Telemetry/SFTelemetryComponent.h"
#include "Online/Websocket/SFWebsocketComponent.h"
#include "Online/Telemetry/SFTelemetryService.h"
#include "Util/SFStringFormat.h"
#include "Online/Telemetry/SFTelemetryBR.h"



namespace SF
{

    static const char loginSchema[] =
        "{\n\
            \"type\" : \"record\",\n\
            \"namespace\" : \"BR\",\n\
            \"name\" : \"Login\",\n\
            \"fields\" : [\n\
                { \"name\" : \"UserId\", \"type\" : \"long\" },\n\
                { \"name\" : \"Platform\", \"type\" : \"int\" },\n\
                { \"name\" : \"PlatformPlayerId\", \"type\" : \"long\" }\n\
            ]\n\
        }\n";
    static const char signUpSchema[] =
        "{\n\
            \"type\" : \"record\",\n\
            \"namespace\" : \"BR\",\n\
            \"name\" : \"SignUp\",\n\
            \"fields\" : [\n\
                { \"name\" : \"UserId\", \"type\" : \"long\" },\n\
                { \"name\" : \"Platform\", \"type\" : \"int\" },\n\
                { \"name\" : \"PlatformPlayerId\", \"type\" : \"long\" }\n\
            ]\n\
        }\n";
    static const char useItemSchema[] =
        "{\n\
            \"type\" : \"record\",\n\
            \"namespace\" : \"BR\",\n\
            \"name\" : \"UseItem\",\n\
            \"fields\" : [\n\
                { \"name\" : \"ItemId\", \"type\" : \"long\" }\n\
            ]\n\
        }\n";

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryComponent
	//

	TelemetryComponent::TelemetryComponent(const String& address, uint64_t clientId, const String& authTicket)
        : LibraryComponent(TypeName)
        , m_Address(address)
        , m_ClientId(clientId)
        , m_AuthTicket(authTicket)
    {
        AddDependency<WebsocketComponent>();

	}

	TelemetryComponent::~TelemetryComponent()
	{

	}

	Result TelemetryComponent::InitializeComponent()
	{
        super::InitializeComponent();

        m_TelemetryPtr.reset(new(GetSystemHeap()) TelemetryBR());

        int iSplitter = m_Address.IndexOfAnyFromEnd(",:");
        if (iSplitter < 0)
            return ResultCode::INVALID_ARG;

        String address = m_Address.SubString(0, iSplitter);
        int port = std::atol(m_Address.data() + iSplitter + 1);

        SFLog(Telemetry, Info, "Telemetry initialize: {0}, clientId:{1}", m_Address, m_ClientId);

        Result hr = m_TelemetryPtr->Initialize(address, port, m_ClientId, m_AuthTicket);
        if (!hr)
            return hr;

        // Registering default shcema
        m_TelemetryPtr->RegisterEventSchema("Login", loginSchema);
        m_TelemetryPtr->RegisterEventSchema("SignUp", signUpSchema);
        m_TelemetryPtr->RegisterEventSchema("UseItem", useItemSchema);

        Service::Telemetry = m_TelemetryPtr.get();

		return ResultCode::SUCCESS;
	}

    void TelemetryComponent::DeinitializeComponent()
    {
        Service::Telemetry = nullptr;

        m_TelemetryPtr->Terminate();
        m_TelemetryPtr.reset();

        super::DeinitializeComponent();
    }
}

