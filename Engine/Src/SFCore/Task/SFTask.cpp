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



#include "SFCorePCH.h"
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


	
	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//


	Task::Task()
		: m_TaskState(State::Idle)
		, m_FinishedEventFired(true)
		, m_TaskFinishedHandlers(GetSystemHeap())
		, m_TaskTickedHandlers(GetSystemHeap())
	{
	}


	Task::Task(TaskFinishedEventDelegate&& pEventHandler)
		: m_TaskState(State::Idle)
		, m_FinishedEventFired(true)
		, m_TaskFinishedHandlers(GetSystemHeap())
		, m_TaskTickedHandlers(GetSystemHeap())
	{
		m_TaskFinishedHandlers.AddDelegate(Forward<TaskFinishedEventDelegate>(pEventHandler));
	}

	Task::~Task()
	{
		if (!m_FinishedEventFired.load(MemoryOrder::memory_order_acquire))
		{
			m_TaskFinishedHandlers.Invoke(this);
		}
	}

	void Task::NotifyFinished()
	{
		if (!m_FinishedEventFired.load(MemoryOrder::memory_order_acquire))
		{
			m_TaskFinishedHandlers.Invoke(this);
			m_FinishedEventFired.store(false, MemoryOrder::memory_order_release);
		}
	}

	void Task::NotifyTicked()
	{
		m_TaskTickedHandlers.Invoke(this);
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

		OnStarted();
	}

	void Task::Finished()
	{
		m_TaskState.store(State::Idle, std::memory_order_release);

		NotifyFinished();
		OnFinished();
	}

	void Task::Canceled()
	{
		m_TaskState.store(State::Idle, std::memory_order_release);

		NotifyFinished();
		OnCanceled();
	}

	void Task::AddTaskEventHandler(TaskFinishedEventDelegate&& pEventHandler)
	{
		m_TaskFinishedHandlers.AddDelegate(Forward<TaskFinishedEventDelegate>(pEventHandler));
	}

	void Task::AddTaskEventHandler(const TaskFinishedEventDelegate& pEventHandler)
	{
		m_TaskFinishedHandlers.AddDelegate(pEventHandler);
	}

	void Task::RemoveTaskEventHandler(uintptr_t context)
	{
		m_TaskFinishedHandlers.RemoveDelegateAll(context);
	}

	void Task::AddTaskTickHandler(TaskFinishedEventDelegate&& pEventHandler)
	{
		m_TaskTickedHandlers.AddDelegate(Forward<TaskFinishedEventDelegate>(pEventHandler));
	}

	void Task::AddTaskTickHandler(const TaskFinishedEventDelegate& pEventHandler)
	{
		m_TaskTickedHandlers.AddDelegate(pEventHandler);
	}

	void Task::RemoveTaskTickHandler(uintptr_t context)
	{
		m_TaskTickedHandlers.RemoveDelegateAll(context);
	}


	// This call will queue this task to the global task manager
	Result Task::Request()
	{
		m_FinishedEventFired = false;

		if (m_TaskState.load(std::memory_order_relaxed) != State::Idle)
		{
			Assert(false);
			return ResultCode::INVALID_STATE;
		}

		return Service::AsyncTaskManager->PendingTask(this);
	}

	void Task::Cancel()
	{
		m_TaskState.store(State::Idle, std::memory_order_relaxed);

		NotifyFinished();
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


} // namespace SF

