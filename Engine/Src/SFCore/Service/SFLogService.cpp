////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Script service
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "Service/SFLogService.h"



namespace SF
{
	namespace Log
	{
        LogChannel Global("Global", LogOutputType::CustomMax);
		LogChannel System("System", LogOutputType::CustomMax);
		LogChannel Net("Net", LogOutputType::CustomMax);
		LogChannel IO("IO", LogOutputType::CustomMax);
		LogChannel ThirdParty("ThirdParty", LogOutputType::CustomMax);
		LogChannel Engine("Engine", LogOutputType::CustomMax);
		LogChannel Protocol("Protocol", LogOutputType::CustomMax);
		LogChannel Editor("Editor", LogOutputType::CustomMax);
		LogChannel Game("Game", LogOutputType::CustomMax);
	}

	static const char* g_LogOutputTypeNames[] = {
		// Generic trace
		"Error",
		"Warning",
		"Factal",
		"Info",

		// Module additional traces
		"Custom1",
		"Custom2",
		"Custom3",
		"Custom4",
		"Custom5",
		"Custom6",
		"Custom7",
		"Custom8",
		"Custom9",
		"Custom10",

		"Debug",
		"Debug1",
		"Debug2",
		"Debug3",
		"Debug4",
		"Debug5",
		"Debug6",
		"Debug7",
		"Debug8",

		"Max",
	};

	const char* ToString(LogOutputType logOutputType)
	{
		return g_LogOutputTypeNames[(int)logOutputType];
	}

} // namespace SF


