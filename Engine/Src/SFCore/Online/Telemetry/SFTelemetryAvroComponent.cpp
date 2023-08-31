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

	TelemetryAvroComponent::TelemetryAvroComponent(const String& address, uint64_t clientId, const String& authTicket, bool bUseEventCacheFile)
        : LibraryComponent(TypeName)
        , m_Address(address)
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
        super::InitializeComponent();

        m_TelemetryPtr.reset(new(GetSystemHeap()) TelemetryClientAvro());

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
        m_TelemetryPtr->RegisterEventSchema("Login", LoginSchema);
        m_TelemetryPtr->RegisterEventSchema("SignUp", SignUpSchema);
        m_TelemetryPtr->RegisterEventSchema("UseItem", UseItemSchema);
        m_TelemetryPtr->RegisterEventSchema("FishingFinished", FishingFinishedSchema);

        Service::Telemetry = m_TelemetryPtr.get();

		return ResultCode::SUCCESS;
	}

    void TelemetryAvroComponent::DeinitializeComponent()
    {
        Service::Telemetry = nullptr;

        m_TelemetryPtr->Terminate();
        m_TelemetryPtr.reset();

        super::DeinitializeComponent();
    }
}

