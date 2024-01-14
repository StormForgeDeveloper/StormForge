////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "Util/SFLog.h"
#include "Service/SFService.h"

#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLogComponent.h"



namespace SF
{

	namespace Service
	{
		ServiceSingleton<StringCrcDB> StringDB;
		ServiceInstance<AsyncTaskService> AsyncTaskManager;
		ServiceInstance<LogService> LogModule;
		ServiceInstance<AsyncIOPortService> AsyncIOPort;
		ServiceInstance <ScriptEngineService> ScriptEngine;
	}

} // namespace SF

