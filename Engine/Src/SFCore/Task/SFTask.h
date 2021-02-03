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
#include "Memory/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDoubleLinkedListBase.h"
#include "Thread/SFSystemSynchronization.h"
#include "Container/SFCircularPageQueue.h"
#include "Util/SFTimeUtil.h"



namespace SF {


	// Task state
	enum class TaskState : uint32_t
	{
		Idle,
		Pending,
		Scheduled,
		Working
	};


	struct TaskNotification
	{
		WeakPointerT<class Task> pTask;
		TaskState State;
	};


	typedef CircularPageQueueAtomic<TaskNotification*> TaskNotificationQueue;
	

	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Task event handler
	//

	// notification handler base 
	class TaskEventHandler
	{
	public:
		TaskEventHandler() {}
		virtual ~TaskEventHandler() {}

		// called when task state has changed
		virtual void OnTaskStateChanged(Task *pTask, TaskState state) { unused(pTask); unused(state); }
	};

	// Handle event queue
	class TaskEventHandlerQueue : public TaskEventHandler
	{
	private:
		TaskNotificationQueue* m_pNotificationQueue = nullptr;

	public:

		TaskEventHandlerQueue(TaskNotificationQueue* pQueue);

		virtual void OnTaskStateChanged(Task *pTask, TaskState state) override;
	};

	// Handle sync state
	class TaskEventHandlerFinishCounter : public TaskEventHandler
	{
	private:
		std::atomic<int32_t>& m_FinishCounter;

	public:

		TaskEventHandlerFinishCounter(std::atomic<int32_t>& finishCounter);

		std::atomic<int32_t>& GetCounter() { return m_FinishCounter; }

		virtual void OnTaskStateChanged(Task *pTask, TaskState state) override;
	};



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

		// Task notification queue, If assigned

		Atomic<TaskEventHandler*> m_pNotificationHandler;

	private:

		void Requested();
		void Scheduled();
		void StartWorking();
		void Finished();
		void Canceled();

		void NotifyStateChange();

		friend class TaskOperator;

	public:

		Task();
		Task(TaskEventHandler* pEventHandler);
		virtual ~Task();

		// Get task state
		State GetState(std::memory_order memoryOrder = std::memory_order_relaxed) { return m_TaskState.load(memoryOrder); }

		// Event handler
		TaskEventHandler* GetTaskEventHandler() { return m_pNotificationHandler.load(MemoryOrder::memory_order_acquire); }
		void SetTaskEventHandler(TaskEventHandler* pEventHandler) { m_pNotificationHandler.store(pEventHandler, MemoryOrder::memory_order_release); }

		// This call will queue this task to the global task manager
		virtual void Request();

		virtual void Cancel();

		virtual void Run() {}

		void Wait();
		bool Wait(DurationMS waitTime);

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

