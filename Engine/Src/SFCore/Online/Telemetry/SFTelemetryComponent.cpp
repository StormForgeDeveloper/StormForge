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
#include "Util/SFStringFormat.h"




namespace SF
{



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryComponent
	//

	TelemetryComponent::TelemetryComponent()
	{

	}

	TelemetryComponent::~TelemetryComponent()
	{

	}

	Result TelemetryComponent::Initialize(const String& brokers, const String& topic, int32_t partition)
	{



		return ResultCode::SUCCESS;
	}


}

