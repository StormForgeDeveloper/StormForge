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
	private:

		// Free item queue
		CircularPageQueueAtomic<SharedObject*> m_FreeQueue;

		// Linked Object counter 
		SyncCounter m_ObjectCount;

#ifdef REFERENCE_DEBUG_TRACKING
		long DeletedObjects;
#endif

	private:

		bool FreeObject(SharedObject* pObj);
		void FreeObjectInternal(SharedObject* pObj);

	public:
#ifdef REFERENCE_DEBUG_TRACKING
		Concurrency::concurrent_unordered_map<uint, SharedObject*> m_PendingFreeObjects;
#endif

	public:

		SharedObjectManager(IHeap& heap);
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

		// Force clear freed objects
		void ClearFreedObjects();

		// Garbagte Collect free Pointers
		virtual void Update();
	};


}

