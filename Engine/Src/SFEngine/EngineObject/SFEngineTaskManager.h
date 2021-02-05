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


#if defined(DEBUG)
#define SF_ENABLE_TASK_TRACKING 1
#else
#define SF_ENABLE_TASK_TRACKING 0
#endif

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
		CircularPageQueue<DelegateEngineTickAction> m_EngineTickAction;

		DoubleLinkedListStaticT<SharedPointerT<EngineTask>> m_Tasks[(int)EngineTaskTick::Max];

		// Pending/Active task count
		Atomic<int32_t> m_EngineAsyncTaskCount;
		TaskFinishedEventDelegate m_AsyncTaskHandler;
		//int m_AsyncTaskSync;
		Atomic<int32_t> m_RenderAsyncTaskCount;
		TaskFinishedEventDelegate m_RenderAsyncTaskHandler;
        
#if SF_ENABLE_TASK_TRACKING
		uint32_t m_TaskTrackingIndex = 0;
		const char* m_TaskTrackingNames[1024]{};
#endif


	private:

		void UpdatePendingTickAction();
		void UpdateEngineNewTasks();

		void UpdateObjectTickList(EngineTaskTick tick, uint32_t newTickFlag, EngineObject* pObj);
		virtual void SetTickFlagsInternal(EngineObject* pObj, uint32_t tickFlag) override;

		void TickSyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList);
		void TickAsyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList, Atomic<int32_t>& counter, const TaskFinishedEventDelegate& eventFunc);
		void TickSyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList);
		void TickAsyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList, Atomic<int32_t>& counter, const TaskFinishedEventDelegate& eventFunc);
		void WaitAsyncTasks();
		void WaitAsyncRenderTasks();

		// Schedule task for this tick
		void ScheduleAsyncTaskForThisTick(Task* pTask, Atomic<int32_t>& counter, const TaskFinishedEventDelegate& eventFunc);


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
		virtual void SetTickFlags(EngineObject* pObj, uint32_t tickFlag) override;

		// 
		virtual Result RunOnEngineTick(DelegateEngineTickAction&& action) override;

		// Add object event task
		virtual Result AddTask(EngineTask* pTask) override;

		// Engine tick update
		virtual void EngineTickUpdate() override;

		// Rendering tick update
		virtual void RenderingTickUpdate() override;
	};

} // namespace SF

