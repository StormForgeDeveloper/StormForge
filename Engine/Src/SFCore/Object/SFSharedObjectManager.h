////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2014 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Multithread/SFSynchronization.h"
#include "Container/SFCircularPageQueue.h"


//#define REFERENCE_DEBUG_TRACKING

namespace SF {

	class SharedObjectManager;
	class SharedPointer;
	class SharedObject;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Shared object pointer manager
	//

	class SharedObjectManager
	{
    public:

        using DestroyObjectEvent = std::function<void(SharedObject*)>;

	private:

		// Free item queue
		CircularPageQueueAtomic<SharedObject*> m_FreeQueue;

		// Linked Object counter 
		Atomic<int> m_ObjectCount;

#ifdef REFERENCE_DEBUG_TRACKING
		long DeletedObjects;
#endif

        // event handler
        DestroyObjectEvent m_OnDestroy;

	private:

		bool FreeObject(SharedObject* pObj);
		void FreeObjectInternal(SharedObject* pObj);

	public:
#ifdef REFERENCE_DEBUG_TRACKING
		Concurrency::concurrent_unordered_map<uint, SharedObject*> m_PendingFreeObjects;
#endif

	public:

		SharedObjectManager();
		virtual ~SharedObjectManager();

		// GetPending free item count
		size_t GetPendingFreeItemCount() { return m_FreeQueue.size(); }

		// Register shared object
		virtual void RegisterSharedObject(SharedObject* pSharedObject);

		// Free shared object
		virtual void FreeSharedReference(SharedObject* pObj
#ifdef REFERENCE_DEBUG_TRACKING
			, const char* fileName = __BASE_FILE__, int lineNumber
#endif
			);

        // set OnDestroyObject event handler
        void SetOnDestroyObjectEventHandler(const DestroyObjectEvent& eventHandler) { m_OnDestroy = eventHandler; }
        void SetOnDestroyObjectEventHandler(DestroyObjectEvent&& eventHandler) { m_OnDestroy = Forward<DestroyObjectEvent>(eventHandler); }

		// Force clear freed objects
		void ClearFreedObjects();

		// Garbage Collect free Pointers
		virtual void Update();
	};


}

