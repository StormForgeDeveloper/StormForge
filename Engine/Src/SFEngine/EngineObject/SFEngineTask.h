////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Task/SFTask.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDoubleLinkedList.h"

namespace SF {

	class EngineObject;
	class EngineObjectManager;


	//////////////////////////////////////////////////////////////////
	//
	//	EngineTaskTick
	//

	// Our engine system has easy approach task arrange ment system.
	// 
	enum class EngineTaskTick : int
	{
		SyncSystemTick,
		SyncPreTick,
		SyncTick,
		AsyncTick,
		SyncPostTick,

		SyncPreRender,
		SyncRender,
		AsyncRender,
		SyncPostRender,

		Max,
	};


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineTask -  interface for task operation
	//

	class EngineTask : public Task
	{
	public:

	private:

		// Task tick group
		EngineTaskTick m_TaskTick;

		// Repeat count, -1 means tick forever
		std::atomic<int> m_Repeat;

		// Task manager node
		DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>> m_TaskManagerNode;

	private:

		DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>>& GetManagerListNode();
		friend class EngineTaskManager;

		virtual void OnStarted() override;
		virtual void OnFinished() override;
		virtual void OnCanceled() override;

	public:
		EngineTask(EngineTaskTick taskTick = EngineTaskTick::SyncPreTick);
		virtual ~EngineTask();

		// Get tick task flags
		EngineTaskTick GetTaskTick() { return m_TaskTick; }

		// Get repeat setting
		int GetRepeat() { return m_Repeat.load(std::memory_order_relaxed); }

		// Set repeat setting. std::numeric_limits<int>::max() means infinite
		void SetRepeat(int repeat) { m_Repeat = repeat; }

		// Inc/Dec repeat. 
		void IncRepeat() { m_Repeat.fetch_add(1, std::memory_order_relaxed); }
		int DecRepeat() { auto orgCount = m_Repeat.load(std::memory_order_relaxed); if (orgCount != std::numeric_limits<int>::max()) return m_Repeat.fetch_sub(1, std::memory_order_release) - 1; return orgCount; }

		// Dispose
		virtual void Dispose() override;

		// Request task. register itself to the task manager
		virtual void Request() override;

		// Task run function. if repeat is bigger than 0 it will be called until repeat is 0 or below zero.
		virtual void Run() override;

	};

	extern template class SharedPointerT<EngineTask>;
	extern template class WeakPointerT<EngineTask>;

	typedef SharedPointerT<EngineTask> EngineTaskPtr;



	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Generic functor task
	//

	template<class Func>
	class EngineTaskT : public EngineTask
	{
	private:
		Func m_Func;

	public:

		EngineTaskT(EngineTaskTick taskTick, Func func)
			: EngineTask(taskTick)
			, m_Func(func)
		{
		}

		virtual void Run()
		{
			m_Func();
		}
	};



}; // namespace SF

