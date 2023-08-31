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

        TelemetryFlatComponent(const String& address, uint64_t clientId, const String& authTicket, bool bUseEventCacheFile);
        virtual ~TelemetryFlatComponent();


        virtual const StringCrc64& GetTypeName() const override { return TypeName; }


        virtual Result InitializeComponent() override;
        virtual void DeinitializeComponent() override;

    private:

        String m_Address;
        uint64_t m_ClientId{};
        String m_AuthTicket;
        bool m_bUseEventCacheFile = true;

        SFUniquePtr<TelemetryClientFlat> m_TelemetryPtr;
    };



}
