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
	//	class TelemetryService
	//

    class TelemetryService
    {
    public:

		static constexpr char KeyName_AuthHeader[] = "sfclientid:";
		static constexpr char KeyName_AuthHeaderLen = sizeof(KeyName_AuthHeader) - 1; // without null terminator
		static constexpr char KeyName_ClientId[] = "clientid";
        static constexpr char KeyName_AuthKey[] = "authkey";



    public:

        TelemetryService();
        virtual ~TelemetryService();


        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0);

    };


}

