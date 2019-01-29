////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Service/SFLogService.h"
#include "String/SFFixedStringDB.h"


namespace SF {

	class Task;

	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class AsyncTaskManager
	//

	class AsyncTaskService
	{
	public:

		// Wait task sync group
		// Async task manager support sync group. waiting flush all scheduled tasks are done
		virtual bool WaitTaskSyncGroup(DurationMS waitDuration) { unused(waitDuration);  return true; }

		// Pending an async task 
		virtual void PendingTask(Task* pTask) { unused(pTask); }
	};



}; // namespace SF

