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
#include "String/SFStrUtil.h"
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


} // namespace SF


