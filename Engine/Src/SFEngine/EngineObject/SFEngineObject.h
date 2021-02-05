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

		SharedPointerT<EngineObjectAsyncEngineTask> m_EngineAsyncTickTask, m_RenderAsyncTickTask;

		DoubleLinkedListNodeDataT<EngineObject*> m_ManagerListNodes;
		DoubleLinkedListNodeDataT<EngineObject*> m_ListNodes[(int)EngineTaskTick::Max];

    private:

		SharedPointerT<EngineObjectAsyncEngineTask>& GetEngineAsyncTickTask();
		SharedPointerT<EngineObjectAsyncEngineTask>& GetRenderAsyncTickTask();

		DoubleLinkedListNodeDataT<EngineObject*>& GetManagerListNode() { return m_ManagerListNodes; }
		DoubleLinkedListNodeDataT<EngineObject*>& GetListNode(EngineTaskTick taskTick) { return m_ListNodes[(int)taskTick]; }

		friend class EngineObjectManager;
		friend class EngineTaskManager;

		void RegisterToEngineObjectManager();

		void SetTickFlags(uint32_t tickFlag);


	public:
		// Constructor
		EngineObject(IHeap* heap, const StringCrc64& name);
		virtual ~EngineObject();

		// Initialize engine object
		virtual Result InitializeObject();


		virtual bool CanDelete() override;
		virtual void Dispose() override;

		bool IsDisposed() { return m_Disposed; }

		// Change tick flag
		// Any combination of EngineTaskTick are acceptable
		uint32_t GetTickFlags() { return m_TickFlags.load(std::memory_order_relaxed); }
		void SetTickGroup(EngineTaskTick tickGroup);

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
	public:

		using super = EngineTask;

	private:
		EngineObject* m_ObjectPtr;

	public:
		EngineObjectAsyncEngineTask(EngineObject* pObj, EngineTaskTick taskTick);

		void ClearObject();

		virtual void Run() override;

		virtual void NotifyTicked() override;

	};



	extern template class SharedPointerT<EngineObject>;

	using EngineObjectPtr = SharedPointerT<EngineObject>;


	// for engine object
	template<class ObjectType, class ...ArgTypes,
		typename = std::enable_if_t<std::is_base_of<EngineObject, ObjectType>::value>
	>
	inline SharedPointerT<ObjectType> NewObject(IHeap& heap, ArgTypes... args)
	{
		SharedPointerT<ObjectType> ObjectPtr = new(heap) ObjectType(heap, args...);
		ObjectPtr->InitializeObject();
		return std::forward<SharedPointerT<ObjectType>>(ObjectPtr);
	}


	//// for regular object type
	//template<class ObjectType, class ...ArgTypes,
	//	typename = std::enable_if_t<!std::is_base_of<EngineObject, ObjectType>::value && std::is_base_of<Object, ObjectType>::value>
	//>
	//	inline SharedPointerT<ObjectType> NewObject(IHeap& heap, const ArgTypes&... args)
	//{
	//	SharedPointerT<ObjectType> ObjectPtr = new(heap) ObjectType(&heap, args...);
	//	return std::forward<SharedPointerT<ObjectType>>(ObjectPtr);
	//}


} // namespace SF

