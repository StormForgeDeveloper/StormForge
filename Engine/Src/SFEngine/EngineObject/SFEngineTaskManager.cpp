////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine task manager
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Util/SFLog.h"
#include "Memory/SFMemory.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Thread/SFThread.h"
#include "Task/SFTask.h"
#include "Task/SFAsyncTaskManager.h"
#include "Util/SFTimeUtil.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "EngineObject/SFEngineTask.h"
#include "Service/SFEngineService.h"



namespace SF {


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Engine Task Manager base class -  interface for task manager
	//

	constexpr StringCrc64 EngineTaskManager::TypeName;


	// Constructor/Destructor
	EngineTaskManager::EngineTaskManager()
		: LibraryComponent("EngineTaskManager")
		, m_EngineNewTask(GetEngineHeap())
		, m_RenderingNewTask(GetEngineHeap())
		, m_EngineTickAction(GetEngineHeap())

	{
		m_AsyncTaskHandler = TaskFinishedEventDelegate{ 
			uintptr_t(this), 
			[this](Task* pTask)
			{
				unused(pTask);
				m_EngineAsyncTaskCount.fetch_sub(1, MemoryOrder::memory_order_release);
			}
		};

		m_RenderAsyncTaskHandler = TaskFinishedEventDelegate{
			uintptr_t(this),
			[this](Task* pTask)
			{
				unused(pTask);
				m_RenderAsyncTaskCount.fetch_sub(1, MemoryOrder::memory_order_release);
			}
		};

		m_EngineAsyncTaskCount = 0;

		m_FrameNumber = 0;
	}

	EngineTaskManager::~EngineTaskManager()
	{
	}


	// Initialize EngineTaskManager
	Result EngineTaskManager::InitializeComponent()
	{
		LibraryComponent::InitializeComponent();
		Service::EngineTaskManager = this;

		for (int iTick = 0; iTick < (int)EngineTaskTick::Max; iTick++)
		{
			m_Objects[iTick].Clear();
			m_Tasks[iTick].Clear();
		}

		return ResultCode::SUCCESS;
	}

	// Terminate EngineTaskManager
	void EngineTaskManager::DeinitializeComponent()
	{
		Service::EngineTaskManager = nullptr;

		for (int iTick = 0; iTick < (int)EngineTaskTick::Max; iTick++)
		{
			m_Objects[iTick].Clear();
			m_Tasks[iTick].Clear();
		}

		LibraryComponent::DeinitializeComponent();
	}

	void EngineTaskManager::UpdateObjectTickList(EngineTaskTick tick, uint32_t newTickFlag, EngineObject* pObj)
	{
		assert((int)tick >= 0 && (int)tick < countof(m_Objects));

		auto& tickList = m_Objects[(int)tick];
		auto& objNode = pObj->GetListNode(tick);

		auto mask = 1 << (int)tick;
		bool oldValue = (pObj->m_TickFlags & mask) != 0;
		bool newValue = (newTickFlag & mask) != 0;

		if (oldValue == newValue) return;

		if (oldValue)
		{
			if(tickList.IsInTheList(&objNode))
				tickList.Remove(&objNode);
		}
		else
			tickList.Add(&objNode);
	}

	void EngineTaskManager::SetTickFlags(EngineObject* pObj, uint32_t tickFlag)
	{
		if (ThisThread::GetThreadID() == GetEngineThreadID())
		{
			SetTickFlagsInternal(pObj, tickFlag);
		}
		else
		{
			assert(pObj->IsDisposed() || pObj->GetReferenceCount() > 0);

			SharedPointerT<EngineObject> pObjectPtr(pObj);
			RunOnEngineTick([this, tickFlag = tickFlag, pObjectPtr]()
				{
					if (pObjectPtr != nullptr)
					{
						SetTickFlagsInternal(pObjectPtr.get(), tickFlag);
					}
				});
		}
	}

	void EngineTaskManager::SetTickFlagsInternal(EngineObject* pObj, uint32_t tickFlag)
	{
		assert(ThisThread::GetThreadID() == GetEngineThreadID());

		auto curTickFlag = pObj->m_TickFlags.load(std::memory_order_acquire);
		if (curTickFlag == tickFlag)
			return;

		UpdateObjectTickList(EngineTaskTick::SyncSystemTick, tickFlag, pObj);
		UpdateObjectTickList(EngineTaskTick::SyncPreTick, tickFlag, pObj);
		UpdateObjectTickList(EngineTaskTick::SyncTick, tickFlag, pObj);
		UpdateObjectTickList(EngineTaskTick::AsyncTick, tickFlag, pObj);
		UpdateObjectTickList(EngineTaskTick::SyncPostTick, tickFlag, pObj);

		// 
		pObj->m_TickFlags.store(tickFlag, std::memory_order_release);
	}


	Result EngineTaskManager::RunOnEngineTick(DelegateEngineTickAction&& action)
	{
		auto result = m_EngineTickAction.Enqueue(Forward<DelegateEngineTickAction>(action));
		assert(result);
		return result;
	}

	// Add object event task
	Result EngineTaskManager::AddTask(EngineTask* pTask)
	{
		auto result = m_EngineNewTask.Enqueue(pTask);
		if (result) TaskOperator().Requested(pTask);
		assert(result);

		return result;
	}

	void EngineTaskManager::TickSyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList)
	{
		objectList.ForeachWithRemove([tick](DoubleLinkedListNodeDataT<EngineObject*>& node)
		{
			EngineObject* objectPtr;
			objectPtr = node.Data;

			if (objectPtr == nullptr)
			{
				// remove
				return false;
			}

			objectPtr->OnTick(tick);
			
			return true;
		});
	}

	void EngineTaskManager::TickAsyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList, Atomic<int32_t>& counter, const TaskFinishedEventDelegate& eventFunc)
	{
		objectList.ForeachWithRemove([&](DoubleLinkedListNodeDataT<EngineObject*>& node)
		{

			EngineObject* objectPtr;
			objectPtr = node.Data;
			if (objectPtr == nullptr)
			{
				// remove
				return false;
			}


#if SF_ENABLE_TASK_TRACKING
			m_TaskTrackingNames[m_TaskTrackingIndex++] = typeid(*objectPtr).name();
#endif

			auto task = objectPtr->GetEngineAsyncTickTask();

			ScheduleAsyncTaskForThisTick(*task, counter, eventFunc);

			return true;
		});
	}



	void EngineTaskManager::TickSyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList)
	{
		taskList.ForeachWithRemove([&taskList](DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>>& node) -> bool
		{
			SharedPointerT<EngineTask>& task = node.Data;

			if (task == nullptr)
			{
				// remove
				// when nullptr assignment is happened the task with node is released so return false will cause segment fault
				if (taskList.IsInTheList(&node))
					taskList.RemoveNoLock(&node);
				node.Data = nullptr;
				return true;
			}

			TaskOperator().StartWorking(*task);
			task->Run();
			if (task->GetState() == TaskState::Idle) // if you want the task keep going, don't finish it
			{
				// when nullptr assignment is happened the task with node is released so return false will cause segment fault
				if(taskList.IsInTheList(&node))
					taskList.RemoveNoLock(&node);
				node.Data = nullptr;
				return true;
			}

			return true;
		});
	}

	void EngineTaskManager::TickAsyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList, Atomic<int32_t>& counter, const TaskFinishedEventDelegate& eventFunc)
	{
		taskList.ForeachWithRemove([&](DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>>& node)
		{
			SharedPointerT<EngineTask>& task = node.Data;
			if (task == nullptr)
			{
				// remove
				// when nullptr assignment is happened the task with node is released so return false will cause segment fault
				if (taskList.IsInTheList(&node))
					taskList.RemoveNoLock(&node);
				node.Data = nullptr;
				return true;
			}

#if SF_ENABLE_TASK_TRACKING
			m_TaskTrackingNames[m_TaskTrackingIndex++] = typeid(*task.get()).name();
#endif

			counter.fetch_add(1, std::memory_order_relaxed);
			task->RemoveTaskTickHandler(intptr_t(this));
			task->AddTaskTickHandler(eventFunc);
			Service::AsyncTaskManager->PendingTask(task.get());

			//ScheduleAsyncTaskForThisTick(*task, counter, eventFunc);

			return true;
		});
	}

	void EngineTaskManager::WaitAsyncTasks()
	{
		while (m_EngineAsyncTaskCount.load(std::memory_order_acquire) > 0)
		{
			ThisThread::SleepFor(DurationMS(3));
		}
	}

	void EngineTaskManager::WaitAsyncRenderTasks()
	{
		while (m_RenderAsyncTaskCount.load(std::memory_order_acquire) > 0)
		{
			ThisThread::SleepFor(DurationMS(3));
		}
	}

	// Schedule task for this tick
	void EngineTaskManager::ScheduleAsyncTaskForThisTick(Task* pTask, Atomic<int32_t>& counter, const TaskFinishedEventDelegate& eventFunc)
	{
		counter.fetch_add(1, std::memory_order_relaxed);
		pTask->RemoveTaskTickHandler(intptr_t(this));
		pTask->AddTaskTickHandler(eventFunc);
		Service::AsyncTaskManager->PendingTask(pTask);
	}

	void EngineTaskManager::UpdatePendingTickAction()
	{
		DelegateEngineTickAction action;
		while (m_EngineTickAction.Dequeue(action))
		{
			action();
		}
	}

	void EngineTaskManager::UpdateEngineNewTasks()
	{
		SharedPointerT<EngineTask> task;
		while (m_EngineNewTask.Dequeue(task))
		{
			if (task == nullptr)
			{
				assert(false);
				continue;
			}

			auto index = (int)task->GetTickGroup();
			if (index < 0 || index >(int)countof(m_Tasks))
			{
				task = nullptr;
				Assert(false); // invalid index
				continue;
			}

			// canceled or nullified task
			if (task->GetState() == Task::State::Idle)
			{
				task = nullptr;
				continue;
			}

			task->GetManagerListNode().Data = task;
			auto result = m_Tasks[index].Add(&task->GetManagerListNode());
			TaskOperator().Scheduled(*task);
			unused(result);
			assert(result == Result(ResultCode::SUCCESS));
			task = nullptr;
		}
	}

	void EngineTaskManager::EngineTickUpdate()
	{
		m_FrameNumber.fetch_add(1, MemoryOrder::memory_order_release);

		UpdatePendingTickAction();
		UpdateEngineNewTasks();

		// We expect async task count is zero at the beginning
		Assert(m_EngineAsyncTaskCount == 0);
		m_EngineAsyncTaskCount = 0;
#if SF_ENABLE_TASK_TRACKING
		m_TaskTrackingIndex = 0;
#endif


		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncSystemTick]);
		TickSyncObjectList(EngineTaskTick::SyncSystemTick, m_Objects[(int)EngineTaskTick::SyncSystemTick]);

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncPreTick]);
		TickSyncObjectList(EngineTaskTick::SyncPreTick, m_Objects[(int)EngineTaskTick::SyncPreTick]);

		TickAsyncTaskList(m_Tasks[(int)EngineTaskTick::AsyncTick], m_EngineAsyncTaskCount, m_AsyncTaskHandler);
		TickAsyncObjectList(EngineTaskTick::AsyncTick, m_Objects[(int)EngineTaskTick::AsyncTick], m_EngineAsyncTaskCount, m_AsyncTaskHandler );

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncTick]);
		TickSyncObjectList(EngineTaskTick::SyncTick, m_Objects[(int)EngineTaskTick::SyncTick]);

		// Wait Async tasks
		WaitAsyncTasks();

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncPostTick]);
		TickSyncObjectList(EngineTaskTick::SyncPostTick, m_Objects[(int)EngineTaskTick::SyncPostTick]);
	}

	void EngineTaskManager::RenderingTickUpdate()
	{
		SharedPointerT<EngineTask> task;
		while (m_RenderingNewTask.Dequeue(task))
		{
			if (task == nullptr) continue;

			auto index = (int)task->GetTickGroup();
			if (index < 0 || index >(int)countof(m_Tasks))
			{
				Assert(false); // invalid index
				continue;
			}

			m_Tasks[index].Add(&task->GetManagerListNode());
			task = nullptr;
		}

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncPreRender]);
		TickSyncObjectList(EngineTaskTick::SyncPreRender, m_Objects[(int)EngineTaskTick::SyncPreRender]);

		// Reset async task count
		m_RenderAsyncTaskCount = 0;

		TickAsyncTaskList(m_Tasks[(int)EngineTaskTick::AsyncRender], m_RenderAsyncTaskCount, m_RenderAsyncTaskHandler);
		TickAsyncObjectList(EngineTaskTick::AsyncRender, m_Objects[(int)EngineTaskTick::AsyncRender], m_RenderAsyncTaskCount, m_RenderAsyncTaskHandler);

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncRender]);
		TickSyncObjectList(EngineTaskTick::SyncRender, m_Objects[(int)EngineTaskTick::SyncRender]);

		// Wait Async tasks
		WaitAsyncRenderTasks();

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncPostRender]);
		TickSyncObjectList(EngineTaskTick::SyncPostRender, m_Objects[(int)EngineTaskTick::SyncPostRender]);
	}


} // namespace SF

