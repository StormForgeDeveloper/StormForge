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
#include "Util/SFStringFormat.h"


#include <libwebsockets.h>


namespace SF
{


	TelemetryService::TelemetryService()
	{

	}
	TelemetryService::~TelemetryService()
	{

	}


	Result TelemetryService::Initialize(const String& brokers, const String& topic, int32_t partition)
	{
		return ResultCode::SUCCESS;
	}


}

