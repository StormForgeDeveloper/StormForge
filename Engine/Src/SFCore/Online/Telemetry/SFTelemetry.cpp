////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Telemetry warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/Telemetry/SFTelemetry.h"
#include "Util/SFStringFormat.h"





namespace SF
{



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class Telemetry
	//





	Telemetry::Telemetry()
	{
		
	}

	Telemetry::~Telemetry()
	{
	}

	Result Telemetry::Initialize(const String& brokers, const String& topic, int32_t partition)
	{
		return ResultCode::SUCCESS;
	}

}

