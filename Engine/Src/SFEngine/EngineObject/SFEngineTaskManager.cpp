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



	class UpdateObjectTickFlagTask : public EngineTask
	{
	private:
		// object pointer 
		SharedPointerT<EngineObject>	m_ObjectPtr;

	public:
		UpdateObjectTickFlagTask(EngineObject* pObj)
			: EngineTask()
			, m_ObjectPtr(pObj)
		{

		}

		virtual void Run() override
		{
			if (m_ObjectPtr != nullptr)
			{
				Service::EngineTaskManager->UpdateTickFlagsInternal(*m_ObjectPtr);
			}
			m_ObjectPtr = nullptr;
		}
	};


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
		, m_AsyncTaskHandler(m_EngineAsyncTaskCount)
		, m_RenderAsyncTaskHandler(m_RenderAsyncTaskCount)
	{
		m_EngineAsyncTaskCount = 0;
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

	void EngineTaskManager::UpdateObjectList(EngineTaskTick tick, EngineObject* pObj)
	{
		auto& tickList = m_Objects[(int)tick];
		auto& objNode = pObj->GetListNode(tick);

		auto mask = 1 << (int)tick;
		bool oldValue = (pObj->m_ActiveTickFlags & mask) != 0;
		bool newValue = (pObj->GetTickFlags() & mask) != 0;

		if (oldValue == newValue) return;

		if (oldValue)
		{
			if(tickList.IsInTheList(&objNode))
				tickList.Remove(&objNode);
		}
		else
			tickList.Add(&objNode);
	}

	EngineTaskPtr EngineTaskManager::UpdateTickFlags(EngineObject* pObj)
	{
        if(ThisThread::GetThreadID() == GetEngineThreadID())
        {
            UpdateTickFlagsInternal(pObj);
            return EngineTaskPtr();
        }
        else
        {
			assert(pObj->IsDisposed() || pObj->GetReferenceCount()>0);

            // This function can be called in the object destructor, so we need to use some global memory manager
            EngineTaskPtr pNewTask = new(GetEngineHeap()) UpdateObjectTickFlagTask(pObj);
            pNewTask->Request();
            return std::forward<EngineTaskPtr>(pNewTask);
        }
	}



	void EngineTaskManager::UpdateTickFlagsInternal(EngineObject* pObj)
	{
		if (pObj->m_ActiveTickFlags.load(std::memory_order_consume) == pObj->GetTickFlags())
			return;

		UpdateObjectList(EngineTaskTick::SyncSystemTick, pObj);
		UpdateObjectList(EngineTaskTick::SyncPreTick, pObj);
		UpdateObjectList(EngineTaskTick::SyncTick, pObj);
		UpdateObjectList(EngineTaskTick::AsyncTick, pObj);
		UpdateObjectList(EngineTaskTick::SyncPostTick, pObj);

        pObj->m_ActiveTickFlags.store(pObj->GetTickFlags(), std::memory_order_release);
	}


	// Schedule Async task for this tick
	Result EngineTaskManager::ScheduleTaskForThisTick(Task* pTask)
	{
		if (pTask == nullptr)
			return ResultCode::INVALID_ARG;

		ScheduleAsyncTaskForThisTick(pTask, m_AsyncTaskHandler);

		return ResultCode::SUCCESS;
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

	void EngineTaskManager::TickAsyncObjectList(EngineTaskTick tick, DoubleLinkedListStaticT<EngineObject*>& objectList, TaskEventHandlerFinishCounter& counter)
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

			auto task = objectPtr->GetEngineAsyncTask();

			ScheduleAsyncTaskForThisTick(*task, counter);

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
			auto repeat = task->DecRepeat();
			if (repeat < 0)
			{
				TaskOperator().Finished(*task);
				// remove
				// when nullptr assignment is happened the task with node is released so return false will cause segment fault
				if(taskList.IsInTheList(&node))
					taskList.RemoveNoLock(&node);
				node.Data = nullptr;
				return true;
			}

			return true;
		});
	}

	void EngineTaskManager::TickAsyncTaskList(DoubleLinkedListStaticT<SharedPointerT<EngineTask>>& taskList, TaskEventHandlerFinishCounter& counter)
	{
		taskList.ForeachWithRemove([&](DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>>& node)
		{
			SharedPointerT<EngineTask>& task = node.Data;
			if (task == nullptr || task->GetRepeat() < 0)
			{
				// remove
				// when nullptr assignment is happened the task with node is released so return false will cause segment fault
				if (taskList.IsInTheList(&node))
					taskList.RemoveNoLock(&node);
				node.Data = nullptr;
				return true;
			}

			ScheduleAsyncTaskForThisTick(*task, counter);

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
	void EngineTaskManager::ScheduleAsyncTaskForThisTick(Task* pTask, TaskEventHandlerFinishCounter& counter)
	{
		counter.GetCounter().fetch_add(1, std::memory_order_relaxed);
		pTask->SetTaskEventHandler(&counter);
		Service::AsyncTaskManager->PendingTask(pTask);
	}


	void EngineTaskManager::OnTaskFinished(EngineTask* pTask)
	{
		pTask->DecRepeat();
		pTask->SetTaskEventHandler(nullptr);

		//if (pTask->GetTaskTick() == EngineTaskTick::AsyncTick)
		//{
		//	m_EngineAsyncTaskCount.fetch_sub(1, std::memory_order_relaxed);
		//}
		//else if (pTask->GetTaskTick() == EngineTaskTick::AsyncRender)
		//{
		//	m_RenderAsyncTaskCount.fetch_sub(1, std::memory_order_relaxed);
		//}
	}

	void EngineTaskManager::OnTaskCanceled(EngineTask* pTask)
	{
		// do the same thing
		OnTaskFinished(pTask);
	}

	void EngineTaskManager::EngineTickUpdate()
	{
      
		SharedPointerT<EngineTask> task;
		while (m_EngineNewTask.Dequeue(task))
		{
			if (task == nullptr)
			{
				assert(false);
				continue;
			}

			auto index = (int)task->GetTaskTick();
			if (index < 0 || index >(int)countof(m_Tasks))
			{
				task = nullptr;
				Assert(false); // invalid index
				continue;
			}

			// canceled or nulified task
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

		// We expect async task count is zero at the beginning
		Assert(m_EngineAsyncTaskCount == 0);
		//m_EngineAsyncTaskCount = 0;

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncSystemTick]);
		TickSyncObjectList(EngineTaskTick::SyncSystemTick, m_Objects[(int)EngineTaskTick::SyncSystemTick]);

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncPreTick]);
		TickSyncObjectList(EngineTaskTick::SyncPreTick, m_Objects[(int)EngineTaskTick::SyncPreTick]);


		TickAsyncTaskList(m_Tasks[(int)EngineTaskTick::AsyncTick], m_AsyncTaskHandler);
		TickAsyncObjectList(EngineTaskTick::AsyncTick, m_Objects[(int)EngineTaskTick::AsyncTick], m_AsyncTaskHandler);

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

			auto index = (int)task->GetTaskTick();
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

		TickAsyncTaskList(m_Tasks[(int)EngineTaskTick::AsyncRender], m_RenderAsyncTaskHandler);
		TickAsyncObjectList(EngineTaskTick::AsyncRender, m_Objects[(int)EngineTaskTick::AsyncRender], m_RenderAsyncTaskHandler);

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncRender]);
		TickSyncObjectList(EngineTaskTick::SyncRender, m_Objects[(int)EngineTaskTick::SyncRender]);

		// Wait Async tasks
		WaitAsyncRenderTasks();

		TickSyncTaskList(m_Tasks[(int)EngineTaskTick::SyncPostRender]);
		TickSyncObjectList(EngineTaskTick::SyncPostRender, m_Objects[(int)EngineTaskTick::SyncPostRender]);
	}


} // namespace SF

