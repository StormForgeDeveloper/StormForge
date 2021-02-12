////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Async Task manager
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "Util/SFLog.h"
#include "String/SFToString.h"
#include "Task/SFTask.h"
#include "Task/SFAsyncTaskManager.h"




namespace SF {


#ifdef _DEBUG
	const bool AsyncTaskManager::UseConditionVariable = false;
#else
	constexpr bool AsyncTaskManager::UseConditionVariable;
#endif

	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//


	// Constructor/Destructor
	AsyncTaskWorker::AsyncTaskWorker(AsyncTaskManager* pTaskManager)
		: Thread("AsyncTaskWorker")
		, m_pTaskManager(pTaskManager)
	{
	}

	AsyncTaskWorker::~AsyncTaskWorker()
	{
	}

	// run function
	bool AsyncTaskWorker::Tick()
	{
		if (m_pTaskManager == nullptr)
			return false;

		if (AsyncTaskManager::UseConditionVariable)
		{
			std::unique_lock<std::mutex> lockGuard(m_pTaskManager->GetTaskAssignMutex());
			auto waitResult = m_pTaskManager->GetTaskAssignVariable().wait_for(lockGuard, DurationMS(60 * 1000));
			if (waitResult == std::cv_status::timeout)
			{
				return true;
			}
		}

		SharedPointerAtomicT<Task> pTask;
		Result result = m_pTaskManager->GetTaskQueue().Dequeue(pTask, [&]() { return IsKillEventSignaled(); });
		if (pTask == nullptr)
		{
			unused(result);
			assert(!result);
			return true;
		}

		if (pTask->GetState() == Task::State::Scheduled || pTask->GetState() == Task::State::Pending)
		{
			pTask->StartWorking();

			pTask->Run();

			pTask->Finished();
		}
		else
		{
			pTask->Canceled();
		}
		pTask->NotifyTicked();

		return true;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	AsyncTaskManager
	//

	AsyncTaskManager::AsyncTaskManager(int numThread)
		: m_PendingTasks(GetEngineHeap())
		, m_TaskWorkers(GetEngineHeap())
		, m_NumThread(numThread)
	{
	}

	AsyncTaskManager::~AsyncTaskManager()
	{
		
	}
/*
	void AsyncTaskManager::AssignTask(SharedPointerT<Task>& pTask)
	{
		MutexScopeLock scopeLock(m_TaskLock);
		WeakPointerT<Task> task;

		if (m_PendingTasks.Dequeue(task))
		{
			pTask = task;
		}
	}
*/
	// Wait task sync group
	// Async task manager support sync group. waiting flush all scheduled tasks are done
	bool AsyncTaskManager::WaitTaskSyncGroup(DurationMS waitDuration)
	{
		unused(waitDuration);
		return true;
	}

	// Pending an async task 
	Result AsyncTaskManager::PendingTask(Task* pTask)
	{
		Result hr;
		if (UseConditionVariable)
		{
			std::scoped_lock<std::mutex> lockGuard(GetTaskAssignMutex());

			TaskOperator().Requested(pTask);
			hr = m_PendingTasks.Enqueue(SharedPointerAtomicT<Task>(pTask));
			if (hr)
			{
				m_TaskAssignCondition.notify_one();
			}
			else
			{
				TaskOperator().Canceled(pTask);
			}
		}
		else
		{
			TaskOperator().Requested(pTask);
			hr = m_PendingTasks.Enqueue(SharedPointerAtomicT<Task>(pTask));
			if (!hr)
			{
				TaskOperator().Canceled(pTask);
			}
		}

		return hr;
	}


	// Initialize server component
	Result AsyncTaskManager::Initialize()
	{
		// Start worker threads
		for (int iThread = 0; iThread < m_NumThread; iThread++)
		{
			auto pWorker = new(GetEngineHeap()) AsyncTaskWorker(this);
			m_TaskWorkers.push_back(pWorker);
			pWorker->Start();
		}

		Service::AsyncTaskManager = this;

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void AsyncTaskManager::Deinitialize()
	{

		for (auto itWorker = m_TaskWorkers.begin(); itWorker.IsValid(); ++itWorker)
		{
			(*itWorker)->SetKillEvent();
		}

		if (UseConditionVariable)
		{
			m_TaskAssignCondition.notify_all();
		}

		for (auto itWorker = m_TaskWorkers.begin(); itWorker.IsValid(); ++itWorker)
		{
			(*itWorker)->Stop(true);
			IHeap::Delete(*itWorker);
		}

		SharedPointerAtomicT<Task> task;
		while (m_PendingTasks.Dequeue(task))
		{
			if (task != nullptr)
			{
				task->OnFinished();
			}
		}

		Service::AsyncTaskManager = nullptr;
	}





	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	AsyncTaskManager component
	//

	constexpr StringCrc64 AsyncTaskManagerComponent::TypeName;


	AsyncTaskManagerComponent::AsyncTaskManagerComponent(int numThread)
		: LibraryComponent(StringCrc64(TypeName))
		, m_TaskManager(numThread)
	{

	}

	AsyncTaskManagerComponent::~AsyncTaskManagerComponent()
	{
	}


	// Initialize server component
	Result AsyncTaskManagerComponent::InitializeComponent()
	{
		Result hr = LibraryComponent::InitializeComponent();
		if (!(hr)) return hr;

		m_TaskManager.Initialize();

		return ResultCode::SUCCESS;
	}

	// Terminate server component
	void AsyncTaskManagerComponent::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();

		m_TaskManager.Deinitialize();
	}


} // namespace SF

