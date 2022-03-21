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
		LogChannel System("System", LogOutputType::Info);
		LogChannel Net("Net", LogOutputType::Info);
		LogChannel IO("IO", LogOutputType::Info);
		LogChannel ThirdParty("ThirdParty", LogOutputType::Info);
		LogChannel Engine("Engine", LogOutputType::Info);
		LogChannel Protocol("Protocol", LogOutputType::Info);
		LogChannel Editor("Editor", LogOutputType::Info);
		LogChannel Game("Game", LogOutputType::Info);
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


