////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Task class
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "Util/SFLog.h"
#include "String/SFToString.h"
#include "Task/SFTask.h"
#include "Task/SFAsyncTaskManager.h"



namespace SF {

	template class SharedPointerT < Task >;
	template class WeakPointerT < Task >;


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Task event handler
	//

	TaskEventHandlerQueue::TaskEventHandlerQueue(TaskNotificationQueue* pQueue)
		: m_pNotificationQueue(pQueue)
	{
	}

	void TaskEventHandlerQueue::OnTaskStateChanged(Task *pTask, TaskState state)
	{
		if (m_pNotificationQueue == nullptr)
			return;

		TaskNotification* notification = new(GetEngineHeap()) TaskNotification;
		notification->pTask = WeakPointerT<Task>(pTask);
		notification->State = state;

		m_pNotificationQueue->Enqueue(std::forward<TaskNotification*>(notification));
	}


	TaskEventHandlerFinishCounter::TaskEventHandlerFinishCounter(std::atomic<int32_t>& finishCounter)
		: m_FinishCounter(finishCounter)
	{
	}

	void TaskEventHandlerFinishCounter::OnTaskStateChanged(Task *pTask, TaskState state)
	{
		if (state == TaskState::Idle)
			m_FinishCounter.fetch_sub(1, std::memory_order_release);
	}

	
	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//


	Task::Task()
		: m_TaskState(State::Idle)
	{
	}


	Task::Task(TaskEventHandler* pEventHandler)
		: m_TaskState(State::Idle)
		, m_pNotificationHandler(pEventHandler)
	{
	}

	Task::~Task()
	{
	}

	void Task::NotifyStateChange()
	{
		if (m_pNotificationHandler == nullptr)
			return;

		m_pNotificationHandler->OnTaskStateChanged(this, GetState(std::memory_order_acquire));
		//TaskNotification* notification = new(GetEngineHeap()) TaskNotification;
		//notification->pTask = WeakPointerT<Task>(this);
		//notification->State = m_TaskState.load(std::memory_order_acquire);

		//m_pNotificationQueue->Enqueue(std::forward<TaskNotification*>(notification));
	}

	void Task::Requested()
	{
		State expected = State::Idle;
		while (!m_TaskState.compare_exchange_weak(expected, State::Pending, std::memory_order_seq_cst))
		{
			if (expected == State::Pending || expected == State::Scheduled || expected == State::Working) // already requested
				return;

			expected = State::Idle;
		}

		NotifyStateChange();
	}

	void Task::Scheduled()
	{
		State expected = State::Pending;
		while (!m_TaskState.compare_exchange_weak(expected, State::Scheduled, std::memory_order_seq_cst))
		{
			// Idle kind of fine, try again
			if (expected == State::Idle)
				continue;

			if (expected == State::Scheduled || expected == State::Working) // already requested
				return;

			expected = State::Pending;
		}

		NotifyStateChange();
	}

	void Task::StartWorking()
	{
		State expected = State::Scheduled;
		// relaxed not allowed for android
		while (!m_TaskState.compare_exchange_weak(expected, State::Working, std::memory_order_acq_rel))
		{
			if (expected == State::Working || expected == State::Idle) // already done or working
				return;

			if(expected != State::Pending) // Pending is fine, we just need to proceed, i guess
				expected = State::Scheduled;
		}

		NotifyStateChange();

		OnStarted();
	}

	void Task::Finished()
	{
		m_TaskState.store(State::Idle, std::memory_order_release);

		NotifyStateChange();

		OnFinished();
	}

	void Task::Canceled()
	{
		m_TaskState.store(State::Idle, std::memory_order_release);

		NotifyStateChange();

		OnCanceled();
	}

	// This call will queue this task to the global task manager
	void Task::Request()
	{
		if (m_TaskState.load(std::memory_order_relaxed) != State::Idle)
		{
			Assert(false);
			return;
		}

		Service::AsyncTaskManager->PendingTask(this);
	}

	void Task::Cancel()
	{
		m_TaskState.store(State::Idle, std::memory_order_relaxed);

		NotifyStateChange();
	}


	void Task::Wait()
	{
		while (m_TaskState.load(std::memory_order_relaxed) != State::Idle)
		{
			ThisThread::SleepFor(DurationMS(2));
			// If no one else referencing this task. we don't have to wait
			if (GetReferenceCount() == 1)
			{
				m_TaskState = State::Idle;
				break;
			}
		}
	}

	bool Task::Wait(DurationMS waitTime)
	{
		auto start = Util::Time.GetRawTimeMs();
		while (m_TaskState.load(std::memory_order_relaxed) != State::Idle)
		{
			ThisThread::SleepFor(DurationMS(2));

			// If no one else referencing this task. we don't have to wait
			if (GetReferenceCount() == 1)
			{
				m_TaskState = State::Idle;
				break;
			}

			// time check
			if (Util::TimeSinceRaw(start) > waitTime) break;
		}

		return true;
	}


}; // namespace SF

