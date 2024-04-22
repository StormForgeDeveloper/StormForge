////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : task
//
////////////////////////////////////////////////////////////////////////////////



#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDoubleLinkedListBase.h"
#include "Multithread/SFSystemSynchronization.h"
#include "Container/SFCircularPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "Delegate/SFEventDelegate.h"


namespace SF {


	// Task state
	enum class TaskState : uint32_t
	{
		Idle,
		Pending,
		Scheduled,
		Working
	};

	using TaskFinishedEventDelegate = EventDelegateList<Task*>::EventDelegate;


	//////////////////////////////////////////////////////////////////
	//
	//	Task class
	//

	class Task : public SharedObject
	{
	public:

		typedef TaskState State;

	private:

		// Task state
		Atomic<State> m_TaskState;

	protected:
		// Task notification queue, If assigned
		Atomic<bool> m_FinishedEventFired;
		EventDelegateList<Task*> m_TaskFinishedHandlers;

		// event invoked when it is ticked
		EventDelegateList<Task*> m_TaskTickedHandlers;

	protected:


		virtual void NotifyFinished();
		virtual void NotifyTicked();

		virtual void Requested();
		virtual void Scheduled();
		virtual void StartWorking();
		virtual void Finished();
		virtual void Canceled();

		friend class TaskOperator;
		friend class AsyncTaskManager;
		friend class AsyncTaskWorker;

	public:

		Task();
		Task(TaskFinishedEventDelegate&& pEventHandler);
		virtual ~Task();

		// Get task state
		State GetState(std::memory_order memoryOrder = std::memory_order_relaxed) { return m_TaskState.load(memoryOrder); }

		// Event handler
		void AddTaskEventHandler(TaskFinishedEventDelegate&& pEventHandler);
		void AddTaskEventHandler(const TaskFinishedEventDelegate& pEventHandler);
		void RemoveTaskEventHandler(uintptr_t context);

		void AddTaskTickHandler(TaskFinishedEventDelegate&& pEventHandler);
		void AddTaskTickHandler(const TaskFinishedEventDelegate& pEventHandler);
		void RemoveTaskTickHandler(uintptr_t context);

		// This call will queue this task to the global task manager
		virtual Result Request();

		virtual void Cancel();

		virtual void Run() {}

		virtual void Wait();
        virtual bool Wait(DurationMS waitTime);


		//////////////////////////////////////////////////////////////////////
		//
		//	Event notification
		//

		// Finish notification
		virtual void OnStarted() {}
		virtual void OnFinished() {}
		virtual void OnCanceled() {}

	};


	//////////////////////////////////////////////////////////////////////////
	//
	//	Task operator
	//		- Helper class to operate private interface of task.
	//		This class will help not to touch important internal operations 
	//
	class TaskOperator
	{
	public:
		void Requested(Task* pTask) { if (pTask != nullptr) pTask->Requested(); }
		void Scheduled(Task* pTask) { if (pTask != nullptr) pTask->Scheduled(); }
		void StartWorking(Task* pTask) { if (pTask != nullptr) pTask->StartWorking(); }
		void Finished(Task* pTask) { if (pTask != nullptr) pTask->Finished(); }
		void Canceled(Task* pTask) { if (pTask != nullptr) pTask->Canceled(); }
	};

	extern template class SharedPointerT < Task >;
	extern template class WeakPointerT < Task >;

	typedef SharedPointerT < Task > TaskPtr;

} // namespace SF

