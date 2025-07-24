////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Telemetry component Avro version
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "Online/Telemetry/SFTelemetryAvroComponent.h"
#include "Online/Websocket/SFWebsocketComponent.h"
#include "Online/Telemetry/SFTelemetryService.h"
#include "Util/SFStringFormat.h"
#include "Online/Telemetry/SFTelemetryClientAvro.h"



namespace SF
{

    static const char LoginSchema[] =
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
    static const char SignUpSchema[] =
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
    static const char UseItemSchema[] =
        "{\n\
            \"type\" : \"record\",\n\
            \"namespace\" : \"BR\",\n\
            \"name\" : \"UseItem\",\n\
            \"fields\" : [\n\
                { \"name\" : \"ItemId\", \"type\" : \"long\" }\n\
            ]\n\
        }\n";
    static const char FishingFinishedSchema[] =
        "{\n\
            \"type\" : \"record\",\n\
            \"namespace\" : \"BR\",\n\
            \"name\" : \"FishingFinished\",\n\
            \"fields\" : [\n\
                { \"name\" : \"UserId\", \"type\" : \"long\" },\n\
                { \"name\" : \"CharacterId\", \"type\" : \"long\" },\n\
                { \"name\" : \"FishId\", \"type\" : \"int\" },\n\
                { \"name\" : \"ExpGain\", \"type\" : \"long\" },\n\
                { \"name\" : \"SelectedRewardGroupId0\", \"type\" : \"int\" },\n\
                { \"name\" : \"SelectedRewardGroupId1\", \"type\" : \"int\" },\n\
                { \"name\" : \"SelectedRewardGroupId2\", \"type\" : \"int\" }\n\
            ]\n\
        }\n";


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryAvroComponent
	//

	TelemetryAvroComponent::TelemetryAvroComponent(const String& url, uint64_t clientId, const String& authTicket, bool bUseEventCacheFile)
        : LibraryComponent(TypeName)
        , m_Url(url)
        , m_ClientId(clientId)
        , m_AuthTicket(authTicket)
        , m_bUseEventCacheFile(bUseEventCacheFile)
    {
        AddDependency<WebsocketComponent>();

	}

	TelemetryAvroComponent::~TelemetryAvroComponent()
	{

	}

	Result TelemetryAvroComponent::InitializeComponent()
	{
        Result hr;
        super::InitializeComponent();

        if (m_Url.IsNullOrEmpty())
        {
            SFLog(Telemetry, Info, "Telemetry is not configured");
            return hr;
        }

        m_TelemetryPtr.reset(new TelemetryClientAvro());

        SFLog(Telemetry, Info, "Telemetry initialize: {0}, clientId:{1}", m_Url, m_ClientId);

        hr = m_TelemetryPtr->Initialize(m_Url, m_ClientId, m_AuthTicket, m_bUseEventCacheFile);
        if (!hr.IsSuccess())
            return hr;

        // Registering default schema
        m_TelemetryPtr->RegisterEventSchema("Login", LoginSchema);
        m_TelemetryPtr->RegisterEventSchema("SignUp", SignUpSchema);
        m_TelemetryPtr->RegisterEventSchema("UseItem", UseItemSchema);
        m_TelemetryPtr->RegisterEventSchema("FishingFinished", FishingFinishedSchema);

        Service::Telemetry = m_TelemetryPtr.get();

		return hr;
	}

    void TelemetryAvroComponent::DeinitializeComponent()
    {
        Service::Telemetry = nullptr;

        m_TelemetryPtr->Terminate();
        m_TelemetryPtr.reset();

        super::DeinitializeComponent();
    }
}

