////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryPool.h"
#include "Object/SFObject.h"
#include "EngineObject/SFEngineTask.h"
#include "Task/SFTimerScheduler.h"
#include "Container/SFDoubleLinkedList.h"
#include "Container/SFCircularQueue.h"


namespace SF {


	class EngineObjectManager;
	class AsyncTaskWorker;
	class EngineTask;
	class EngineObjectTimerAction;
	class EngineObjectAsyncEngineTask;

	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineObject class -  interface for task operation
	//

	class EngineObject : public Object
	{
	public:


	private:

		SharedPointerT<TimerAction> m_TimerAction;

		// Queued Actions to run on object tick on game thread
		CircularQueue<std::function<void()>, 64> m_PendingObjectTickActions;

        // TODO: Actually tick flag should be queue style as tick flags change task will be queued to task manager.
		std::atomic<uint32_t> m_TickFlags;
        
		bool m_Registered = false;
        bool m_Disposed = false;

		std::atomic<bool> m_ActuallyRegistered;

		SharedPointerT<EngineObjectAsyncEngineTask> m_EngineAsyncTask, m_RenderAsyncTask;

		DoubleLinkedListNodeDataT<EngineObject*> m_ManagerListNodes;
		DoubleLinkedListNodeDataT<EngineObject*> m_ListNodes[(int)EngineTaskTick::Max];

    private:

		SharedPointerT<EngineObjectAsyncEngineTask>& GetEngineAsyncTask();
		SharedPointerT<EngineObjectAsyncEngineTask>& GetRenderAsyncTask();

		DoubleLinkedListNodeDataT<EngineObject*>& GetManagerListNode() { return m_ManagerListNodes; }
		DoubleLinkedListNodeDataT<EngineObject*>& GetListNode(EngineTaskTick taskTick) { return m_ListNodes[(int)taskTick]; }

		friend class EngineObjectManager;
		friend class EngineTaskManager;



	public:
		// Constructor
		EngineObject(IHeap* heap, const StringCrc64& name);
		virtual ~EngineObject();

		void RegisterToEngineObjectManager();

		virtual bool CanDelete() override;
		virtual void Dispose() override;

		bool IsDisposed() { return m_Disposed; }

		// Change tick flag
		// Any combination of EngineTaskTick are acceptable
		uint32_t GetTickFlags() { return m_TickFlags.load(std::memory_order_relaxed); }
		EngineTaskPtr SetTickFlags(uint32_t tickFlag);
		EngineTaskPtr SetTickGroup(EngineTaskTick tickGroup);

		// Set timer
		//	@startDelay: timer will start after startDelay
		//	@interval: 0 means no repeat
		void SetTimer(DurationMS startDelay, DurationMS interval = DurationMS(0));


		/////////////////////////////////////////////////////////
		// Event functions

		// OnTimer
		// @return : ResultCode::SUCCESS_FALSE will stop timer
		virtual Result OnTimerTick(TimerAction *pAction) { unused(pAction); return ResultCode::NOT_IMPLEMENTED; }

		// Object task
		virtual Result OnTick(EngineTaskTick tick) { return ResultCode::NOT_IMPLEMENTED; }
	};


	////////////////////////////////////////////////////////////////////////
	//
	//  EngineObjectTimerAction
	//

	class EngineObjectTimerAction : public TimerAction
	{
	private:

		EngineObject* m_pObject;

	public:
		EngineObjectTimerAction(EngineObject* pTickTask);
		~EngineObjectTimerAction();

		void DisposeWeakPointer();

		virtual bool OnTimerTick() override;

		virtual const char* GetDebugString() override;
	};



	class EngineObjectAsyncEngineTask : public EngineTask
	{
	private:
		EngineObject* m_ObjectPtr;

	public:
		EngineObjectAsyncEngineTask(EngineObject* pObj, EngineTaskTick taskTick);

		void ClearObject();

		virtual void Run() override;
	};



	extern template class SharedPointerT<EngineObject>;

}; // namespace SF

