////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine task manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Thread/SFThread.h"
#include "Thread/SFSynchronization.h"
#include "Container/SFSortedMap.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFCircularPageQueue.h"
#include "EngineObject/SFEngineObject.h"
#include "Util/SFLog.h"
#include "Container/SFIndexing.h"
#include "Container/SFHashTable.h"
#include "EngineObject/SFEngineTask.h"
#include "Service/SFEngineServices.h"


namespace SF {


	class EngineTaskManager;
	class EngineTask;



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineObject Manager base class -  interface for task manager
	//

	class EngineTaskManager : public LibraryComponent, public EngineTaskService
	{
	public:
		static constexpr StringCrc64 TypeName = "EngineTaskManager";

	private:

		// Object List per each tick group
		DoubleLinkedListStaticT<EngineObject*> m_Objects[(int)EngineTaskTick::Max];

		// tasks
		CircularPageQueue<SharedPointerT<EngineTask>> m_EngineNewTask;
		CircularPageQueue<SharedPointerT<EngineTask>> m_RenderingNewTask;

		DoubleLinkedListStaticT<SharedPointerT<EngineTask>> m_Tasks[(int)EngineTaskTick::Max];

		// Pending/Active task count
		std::atomic<int32_t> m_EngineAsyncTaskCount;
		TaskEventHandlerFinishCounter m_AsyncTaskHandler;
		//int m_AsyncTaskSync;
		std::atomic<int32_t> m_RenderAsyncTaskCount;
		TaskEventHandlerFinishCounter m_RenderAsyncTaskHandler;
        

	private:

		void UpdateObjectTickList(EngineTaskTick tick, uint32_t newTickFlag, EngineObject* pObj);
		virtual void SetTickFlagsInternal(EngineObject* pObj, uint32_t tickFlag) override;


		void TickSyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList);
		void TickAsyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList, TaskEventHandlerFinishCounter& counter);

		void TickSyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList);
		void TickAsyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList, TaskEventHandlerFinishCounter& counter);
		void WaitAsyncTasks();
		void WaitAsyncRenderTasks();

		// Schedule task for this tick
		void ScheduleAsyncTaskForThisTick(Task* pTask, TaskEventHandlerFinishCounter& counter);

		virtual void OnTaskFinished(EngineTask* pTask) override;
		virtual void OnTaskCanceled(EngineTask* pTask) override;

		friend class EngineTask;
		friend class Engine;
		friend class EngineThread;
		friend class RenderThread;

	public:
		// Constructor/Destructor
		EngineTaskManager();
		virtual ~EngineTaskManager();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize EngineTaskManager
		virtual Result InitializeComponent() override;

		// Terminate EngineTaskManager
		virtual void DeinitializeComponent() override;

		// Update tick flags, internal use
		virtual EngineTaskPtr SetTickFlags(EngineObject* pObj, uint32_t tickFlag) override;

		// Schedule Async task for this tick
		virtual Result ScheduleTaskForThisTick(Task* pTask) override;

		// Add object event task
		virtual Result AddTask(EngineTask* pTask) override;

		// Engine tick update
		virtual void EngineTickUpdate() override;

		// Rendering tick update
		virtual void RenderingTickUpdate() override;
	};




}; // namespace SF

