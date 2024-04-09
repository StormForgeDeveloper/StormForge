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

#pragma once

#include "SFTypedefs.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Task/SFTask.h"

namespace SF
{
    class TelemetryClientFlat;

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryFlatComponent
	//

    class TelemetryFlatComponent : public LibraryComponent
    {
    public:

        using super = LibraryComponent;
        static constexpr StringCrc64 TypeName = "TelemetryComponent";

    public:

        TelemetryFlatComponent(const String& url, const Guid& clientId, const String& authTicket, bool bUseEventCacheFile);
        virtual ~TelemetryFlatComponent();


        virtual const StringCrc64& GetTypeName() const override { return TypeName; }


        virtual Result InitializeComponent() override;
        virtual void DeinitializeComponent() override;

    private:

        // Server Url
        String m_Url;

        // client id
        Guid m_ClientId{};

        // auth key
        String m_AuthTicket;

        // enable event cache file writting
        bool m_bUseEventCacheFile = true;

        // Telemetry client ptr
        SFUniquePtr<TelemetryClientFlat> m_TelemetryPtr;
    };



}
