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

	// Our engine system has easy approach task arrangement system.
	// 
	enum class EngineTaskTick : int
	{
		None, // Don't tick

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
	//		- Engine tasks will be running as far as they have tick group assigned

	class EngineTask : public Task
	{
	public:

		using super = Task;

	private:

		// Task tick group
		EngineTaskTick m_TaskTick;

		// Task manager node
		DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>> m_TaskManagerNode;

	private:

		DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>>& GetManagerListNode();
		friend class EngineTaskManager;

	public:
		EngineTask(EngineTaskTick taskTick = EngineTaskTick::SyncPreTick);
		virtual ~EngineTask();

		// Get tick task flags
		EngineTaskTick GetTickGroup() { return m_TaskTick; }

		// TODO: probably we need to support changing tick group?
		void SetTickGroup(EngineTaskTick newTickGroup) { assert(newTickGroup == EngineTaskTick::None); m_TaskTick = newTickGroup; }

		// Dispose
		virtual void Dispose() override;

		virtual void Finished() override;

		// Request task. register itself to the task manager
		virtual Result Request() override;

		// Task run function. if repeat is bigger than 0 it will be called until repeat is 0 or below zero.
		virtual void Run() override;

        virtual void Wait() override;
        virtual bool Wait(DurationMS waitTime) override;
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

			// Only one time execution
			Finished();
		}
	};



}; // namespace SF

