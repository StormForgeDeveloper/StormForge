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


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDB
	//

    class TelemetryService
    {
    public:



    public:

        TelemetryService();
        virtual ~TelemetryService();


        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0);

    };


}

