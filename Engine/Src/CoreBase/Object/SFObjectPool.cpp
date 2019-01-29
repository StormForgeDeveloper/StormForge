////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "String/SFStrUtil.h"
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Thread/SFSynchronization.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Object/SFObjectPool.h"
#include "Container/SFHashTable.h"
#include "Memory/SFMemoryPool.h"


//#define SF_OBJECT_POOL_USE_DIRECTALLOCATION 1


namespace SF {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Object Pool(Multi-thread)
	//

	// Constructor for singleton
	ObjectPool::ObjectPool(IHeap& heap, size_t objectSize)
		: m_AllocSize(AlignUp(objectSize, SF_ALIGN_DOUBLE) + MEMITEM_SIZE)
		, m_CallDestructor(false)
		, m_FreeList(nullptr)
		, m_Heap(heap)
	{
	}

	ObjectPool::~ObjectPool()
	{
		ForceClear();
	}



	// force clear memory heap
	void ObjectPool::ForceClear()
	{
		auto curObject = m_FreeList;
		while (curObject != nullptr)
		{
			if (m_CallDestructor)
			{
				curObject->pObject->~ObjectPoolObject();
			}
			auto next = curObject->pNext;
			IHeap::Free(curObject);
			curObject = next;
		}
		m_FreeList = nullptr;
	}

	// Allocate/Free
	Result ObjectPool::Alloc(ObjectPoolObject* &pPtr)
	{
		ObjectItem *pMemItem = nullptr;
#if SF_OBJECT_POOL_USE_DIRECTALLOCATION
	pMemItem = new((void*)new(GetHeap()) uint8_t[m_AllocSize]) ObjectItem();
#else
	pMemItem = m_FreeList;
	if (pMemItem == nullptr)
	{
		pMemItem = (ObjectItem*)GetHeap().Alloc(m_AllocSize);
		pMemItem->pNext = nullptr;
		pMemItem->Using = 0;
		pMemItem->pObject = OnNewObject((uint8_t*)pMemItem + MEMITEM_SIZE);
	}
	else
	{
		m_FreeList = m_FreeList->pNext;

		Assert(pMemItem->Using == 0);
		if (pMemItem->Using != 0)
		{
			// Drop this memory and try another alloc
			return Alloc(pPtr);
		}
	}
#endif

		pMemItem->pNext = nullptr;
		if (pMemItem->pObject == nullptr)
		{
			pMemItem->pObject = OnNewObject((uint8_t*)pMemItem + MEMITEM_SIZE);
		}
		pPtr = pMemItem->pObject;
		pMemItem->Using++;
		Assert(pMemItem->Using == 1);

		pPtr->Reuse();

		m_AllocatedCount.fetch_add(1, std::memory_order_relaxed);

		return ResultCode::SUCCESS;
	}

	Result ObjectPool::Free(ObjectPoolObject* pPtr)
	{
		ObjectItem *pMemItem = nullptr;

		if (pPtr == nullptr)
			return ResultCode::SUCCESS;

		pPtr->Dispose();

		pMemItem = (ObjectItem*)((uint8_t*)pPtr - MEMITEM_SIZE);

		Assert(pMemItem->Using == 1);
		if (pMemItem->Using != 1)
		{
			// Drop memory that cause problem
			Assert(false);
		}
		else
		{
			pMemItem->Using--;
			Assert(pMemItem->Using == 0);
			AssertRel(pMemItem->pNext == nullptr && pMemItem != m_FreeList);

#if SF_OBJECT_POOL_USE_DIRECTALLOCATION
			GetHeap().Free(pMemItem);
#else
			pMemItem->pNext = m_FreeList;
			m_FreeList = pMemItem;
#endif
		}

		m_AllocatedCount.fetch_sub(1, std::memory_order_relaxed);

		return ResultCode::SUCCESS;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Object Pool(Multi-thread)
	//

	// Constructor for singleton
	ObjectPoolMT::ObjectPoolMT(IHeap& heap, size_t AllocSize)
		: m_AllocSize(AlignUp(AllocSize,SF_ALIGN_DOUBLE) + MEMITEM_SIZE)
		, m_Heap(heap)
	{
	}

	ObjectPoolMT::~ObjectPoolMT()
	{
	}

	// force clear memory heap
	void ObjectPoolMT::ForceClear()
	{
		m_FreeList.for_each( [this]( StackPool::Item *pItem )
		{
			MemItem *pMemItem = (MemItem*)pItem;
			pMemItem->pObject->~ObjectPoolObject();
			GetHeap().Free(pMemItem);
		});
		m_FreeList.Clear();
	}

	// Allocate/Free
	Result ObjectPoolMT::Alloc( ObjectPoolObject* &pPtr )
	{
		MemItem *pMemItem = nullptr;
		StackPool::Item *pItem = m_FreeList.Pop();
		if( pItem == nullptr )
		{
			// Allocate page if no free item
			pMemItem = (MemItem*)GetHeap().Alloc(m_AllocSize);
			pMemItem->pNext = nullptr;
			pMemItem->MemMagic = POOL_MEMMAGIC;
			pMemItem->Using = 0;
			pMemItem->pObject = OnNewObject( (uint8_t*)pMemItem+MEMITEM_SIZE );
		}
		else
		{
			pMemItem = (MemItem*)pItem;
			Assert( pMemItem->Using == 0 );
			Assert( pMemItem->MemMagic == POOL_MEMMAGIC );
			if( pMemItem->Using != 0 
				|| pMemItem->MemMagic != POOL_MEMMAGIC )
			{
				// Drop this memory and try another alloc
				return Alloc( pPtr );
			}
		}

		pPtr = pMemItem->pObject;
		CounterType Using = pMemItem->Using.fetch_add(1,std::memory_order_relaxed) + 1;
		AssertRel( Using == 1 );
		//Assert( Using == pMemItem->Using );

		pPtr->Reuse();

		//_WriteBarrier();
		std::atomic_thread_fence(std::memory_order_seq_cst);

		m_AllocatedCount.fetch_add(1,std::memory_order_relaxed);

		return ResultCode::SUCCESS;
	}

	Result ObjectPoolMT::Free( ObjectPoolObject* pPtr )
	{
		MemItem *pMemItem = nullptr;

		if( pPtr == nullptr )
			return ResultCode::SUCCESS;

		pPtr->Dispose();

		pMemItem = (MemItem*)((uint8_t*)pPtr - MEMITEM_SIZE);

		Assert( pMemItem->MemMagic == POOL_MEMMAGIC );
		Assert( pMemItem->Using == 1 );
		if( pMemItem->Using != 1
			|| pMemItem->MemMagic != POOL_MEMMAGIC )
		{
			// Drop memory that cause problem
		}
		else
		{
			CounterType Using = pMemItem->Using.fetch_sub(1,std::memory_order_relaxed) - 1;
			AssertRel( Using == 0 );
			//Assert( Using == pMemItem->Using );

			m_FreeList.Push( pMemItem );
		}

		
		m_AllocatedCount.fetch_sub(1, std::memory_order_relaxed);

		return ResultCode::SUCCESS;
	}


		

}	// namespace SF


