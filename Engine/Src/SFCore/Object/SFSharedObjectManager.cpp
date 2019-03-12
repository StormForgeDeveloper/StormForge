////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2014 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Object/SFSharedObject.h"
#include "Thread/SFSynchronization.h"
#include "Object/SFSharedObjectManager.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"


namespace SF {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Internal implementation
	//

	SharedObjectManager::SharedObjectManager(IHeap& heap)
		: m_FreeQueue(heap, 2048, 1024)
		, m_ObjectCount(0)
#ifdef REFERENCE_DEBUG_TRACKING
		, DeletedObjects(0);
#endif
	{
	}

	SharedObjectManager::~SharedObjectManager()
	{
		ClearFreedObjects();
	}

	bool SharedObjectManager::FreeObject(SharedObject* pObj)
	{
		auto managerRefCount = pObj->m_ManagerReferenceCount.fetch_sub(1, std::memory_order_relaxed) - 1;
		// it's queued more than once. leave this object for later operation
		if (managerRefCount > 0)
		{
			// If the object queued multiple times
#ifdef REFERENCE_DEBUG_TRACKING
			pObj->LatestQueueProcessResult = "In Queue again";
#endif
			return false;
		}

		if (!pObj->CanDelete())
		{
			pObj->m_ManagerReferenceCount.fetch_add(1, std::memory_order_relaxed);
			return false;
		}

		FreeObjectInternal(pObj);

		return true;
	}


	void SharedObjectManager::FreeObjectInternal(SharedObject* pObj)
	{
#ifdef REFERENCE_DEBUG_TRACKING

		AssertRel(pObj->GetReferenceCount() == 0);
		AssertRel(pObj->m_SharedObjectState == SharedObject::SharedObjectState::Disposed || pObj->m_SharedObjectState == SharedObject::SharedObjectState::Deleted);
		pObj->m_ReferenceManagerObject = nullptr;

		Interlocked::Increment(DeletedObjects);


		// no one is using this object pointer. We are good to release it
		AssertRel(pObj->GetReferenceCount() == 0 && pObj->GetWeakReferenceCount() == 0 && pObj->GetManagerReferenceCount() == 0);
		m_PendingFreeObjects.unsafe_erase(pObj->TestID);
		//_ReadWriteBarrier();
		std::atomic_thread_fence(std::memory_order_cst_seq);
#else
		pObj->m_ReferenceManagerObject = nullptr;
#endif
		m_ObjectCount.fetch_sub(1, std::memory_order_relaxed);

		IHeap::Delete(pObj);
	}

	void SharedObjectManager::RegisterSharedObject(SharedObject* pSharedObject)
	{
		assert(pSharedObject->m_ReferenceManagerObject == nullptr || pSharedObject->m_ReferenceManagerObject == this);

		if (pSharedObject->m_ReferenceManagerObject != this)
			m_ObjectCount.fetch_add(1, std::memory_order_relaxed);

		// This will just link manager to object
		pSharedObject->m_ReferenceManagerObject = this;

#ifdef REFERENCE_DEBUG_TRACKING
		Assert(pSharedObject->TestID >= 0 && pSharedObject->TestID < 10000);
		m_PendingFreeObjects.insert(std::make_pair((unsigned int)pSharedObject->TestID, pSharedObject));
#endif
	}

	// 
	void SharedObjectManager::FreeSharedReference(SharedObject* pObj
#ifdef REFERENCE_DEBUG_TRACKING
		, const char* fileName, int lineNumber
#endif
		)
	{
		if (pObj == nullptr)
			return;

#ifdef REFERENCE_DEBUG_TRACKING
		auto state = pObj->m_SharedObjectState.load(std::memory_order_relaxed);

		pObj->LatestReleaseFile = fileName;
		pObj->LatestReleaseLine = lineNumber;
		pObj->LatestReleaseState = state;
#endif
		assert(pObj->GetReferenceCount() == 0 && pObj->GetWeakReferenceCount() == 0);
		pObj->m_ManagerReferenceCount.fetch_add(1, std::memory_order_acquire);
		m_FreeQueue.Enqueue(pObj);
	}

	void SharedObjectManager::ClearFreedObjects()
	{
		SharedObject* pObj = nullptr;
		while (m_FreeQueue.Dequeue(pObj))
		{
			auto queueReferenceCount = pObj->m_ManagerReferenceCount.fetch_sub(1, std::memory_order_relaxed) - 1;
			if(queueReferenceCount == 0)
				FreeObjectInternal(pObj);
		}

	}

	// Garbage Collect free Pointers
	void SharedObjectManager::Update()
	{
		auto numItems = m_FreeQueue.size();
		for (decltype(numItems) item = 0; item < numItems; item++)
		{
			SharedObject* pObj = nullptr;
			if (!m_FreeQueue.Dequeue(pObj))
				break;

			if (!FreeObject(pObj))
			{
				m_FreeQueue.Enqueue(pObj);
			}
		}
	}

}

