////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Async Task manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFCircularPageQueue.h"
#include "Container/SFPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "Multithread/SFSystemSynchronization.h"
#include "Task/SFTask.h"
#include "Service/SFService.h"




namespace SF {

	class Task;
	class AsyncTaskManager;

	class AsyncTaskWorker : public Thread
	{
	private:

		class AsyncTaskManager* m_pTaskManager;


	public:

		// Constructor/Destructor
		AsyncTaskWorker(AsyncTaskManager* pTaskManager);
		virtual ~AsyncTaskWorker();

		// run function
		virtual bool Tick() override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class AsyncTaskManager
	//

	class AsyncTaskManager : public AsyncTaskService
	{
	public:
#ifdef _DEBUG
		static const bool UseConditionVariable;
#else
		static constexpr bool UseConditionVariable = false;
#endif

		typedef CircularPageQueue<SharedPointerAtomicT<Task>> TaskQueue;

	private:

		Mutex m_Mutex;
		std::mutex m_TaskAssignMutex;
		std::condition_variable m_TaskAssignCondition;

		TaskQueue m_PendingTasks;

		DynamicArray<AsyncTaskWorker*>	m_TaskWorkers;

		int m_NumThread;

	private:


		friend class TaskManagerComponent;
		friend class AsyncTaskWorker;

		std::mutex& GetTaskAssignMutex() { return m_TaskAssignMutex; }
		std::condition_variable& GetTaskAssignVariable() { return m_TaskAssignCondition; }
		TaskQueue& GetTaskQueue() { return m_PendingTasks; }
		

	public:

		AsyncTaskManager(int numThread);
		~AsyncTaskManager();


		// Wait task sync group
		// Async task manager support sync group. waiting flush all scheduled tasks are done
		virtual bool WaitTaskSyncGroup(DurationMS waitDuration) override;

		// Pending an async task 
		virtual Result PendingTask(Task* pTask) override;


		// Initialize component
		Result Initialize();
		// Terminate component
		void Deinitialize();
	};


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	AsyncTaskManager component
	//

	class AsyncTaskManagerComponent : public LibraryComponent
	{
	public:

		static constexpr StringCrc64 TypeName = "AsyncTaskManager";

	private:

		AsyncTaskManager m_TaskManager;

	public:

		AsyncTaskManagerComponent(int numThread);
		~AsyncTaskManagerComponent();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;
		// Terminate component
		virtual void DeinitializeComponent() override;

	};



}; // namespace SF

