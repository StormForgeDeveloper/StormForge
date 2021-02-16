////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "String/SFStrUtil.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "Multithread/SFSynchronization.h"
#include "ResultCode/SFResultCodeSystem.h"

#include "Container/SFHashTable2.h"
#include "Platform/StackWalker.h"
#include "MemoryManager/SFMemoryPool.h"


namespace SF
{








	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory Pool by size
	//

	constexpr int32_t MemoryPool::POOL_ITEM_MIN;
	constexpr int32_t MemoryPool::POOL_ITEM_MAX;


	// Constructor for singleton
	MemoryPool::MemoryPool(IHeap& heap, size_t allocSize)
		: IHeap("MemoryPool", &heap)
		, m_AllocSize(allocSize)
	{
	}

	MemoryPool::~MemoryPool()
	{
		Flush();

		if (IHeap::GetMemoryLeakDetection())
		{
			assert(m_AllocatedCount == 0);
			for (auto& itFreeList : m_FreeList)
			{
				auto itemCount = itFreeList.size();
				unused(itemCount);
				assert(itemCount == 0);
			}
		}

	}




	void MemoryPool::Flush()
	{
		for (auto& itFreeList : m_FreeList)
		{
			auto pPoolItem = itFreeList.Pop();
			while (pPoolItem != nullptr)
			{
				// Unmark used for memory pool
				auto pMemPoolItem = ContainerPtrFromMember(MemoryPoolItem, StackItem, pPoolItem);
				auto pDataPtr = MemoryPoolItemToDataPtr(pMemPoolItem);
				auto pMemHdr = GetMemoryBlockHdr(pDataPtr);
				assert(pMemHdr->Magic == MemBlockHdr::MEM_MAGIC);

				FreeInternal(pMemHdr);

				pPoolItem = itFreeList.Pop();
			}
		}
	}

	//
	//	// Allocate/Free
	//	MemBlockHdr* MemoryPool::AllocInternal(size_t size, size_t alignment)
	//	{
	//		if (size != GetAllocSize())
	//		{
	//			Assert(false);
	//			if (size > GetAllocSize())
	//				return nullptr;
	//		}
	//		auto& freeList = PickFreeList();
	//		MemoryPoolItem *pItem = reinterpret_cast<MemoryPoolItem*>(freeList.Pop());
	//		if (pItem == nullptr)
	//		{
	//			// Allocate page if no free item
	//			void *pAllocItem = m_Heap.Alloc(m_AllocSize);
	//			if (pAllocItem == nullptr)
	//				return nullptr;
	//
	//			// Mark used for memory pool
	//			auto pMemHdr = m_Heap.GetMemoryBlockHdr(pAllocItem);
	//			pMemHdr->pMemoryPool = this;
	//
	//			memset(pAllocItem, 0, MEMITEM_SIZE);
	//			pItem = (MemoryPoolItem*)pAllocItem;
	//			pItem->MemMagic = POOL_MEMMAGIC;
	//		}
	//		else
	//		{
	//			//bool isUsing = pItem->Using.load(std::memory_order_relaxed);
	//			//AssertRel(isUsing == false);
	//
	//			if (pItem->MemMagic != POOL_MEMMAGIC)
	//			{
	//#if ENABLE_MEMORY_TRACE
	//				pItem->StackTrace.PrintStackTrace(CurrentProcessID);
	//#endif
	//				// Trash invalid memory and try another alloc
	//				return AllocInternal(typeName);
	//			}
	//		}
	//
	//		//pItem->Using.exchange(true, std::memory_order_release);
	//
	//		return pItem;
	//	}
	//
	//	MemBlockHdr* MemoryPool::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	//	{
	//		// Not support realloc
	//		return nullptr;
	//	}

	void MemoryPool::FreeInternal(MemBlockHdr* pMemBlock)
	{
		auto& freeList = PickFreeList();
		auto freeItemCount = freeList.size();
		if (freeItemCount > POOL_ITEM_MAX)
		{
			FreeInternal(pMemBlock);
		}
		else
		{
			MemoryPoolItem *pMemPoolItem = DataPtrToMemoryPoolItem(pMemBlock->GetDataPtr());
			if (pMemPoolItem == nullptr)
			{
				return;
			}

			Assert(pMemPoolItem->StackItem.pNext == nullptr);
			Assert(pMemBlock->Magic == MemBlockHdr::MEM_MAGIC);
			freeList.Push(&pMemPoolItem->StackItem);
		}

		m_AllocatedCount.fetch_sub(1, std::memory_order_relaxed);
	}

	// Allocate/Free
	void* MemoryPool::Alloc(size_t size, size_t alignment)
	{
		auto pMemBlock = AllocInternal(GetAllocSize() + sizeof(MemoryPoolItem), SF_ALIGN_DOUBLE);
		if (pMemBlock == nullptr)
			return nullptr;

		pMemBlock->pHeap = this;

		MemoryPoolItem *pMemItem = DataPtrToMemoryPoolItem(pMemBlock->GetDataPtr());
		memset(pMemItem, 0, sizeof(MemoryPoolItem));
		if (pMemItem == nullptr)
		{
			return nullptr;
		}

		void* pPtr = pMemBlock->GetDataPtr();
		AssertRel(((int64_t)pPtr & (SF_ALIGN_DOUBLE - 1)) == 0);
	//#if ENABLE_MEMORY_TRACE
		//Assert(pMemBlock->GetFooter()->ListNode.pPrev == nullptr);
	//#endif  // ENABLE_MEMORY_TRACE

		// TODO: capture callstack
		{
//#if ENABLE_MEMORY_TRACE
//			// Refresh call stack
//			pMemBlock->GetFooter()->StackTrace.CaptureCallStack(1);
//#endif
		}

		m_AllocatedCount.fetch_add(1, std::memory_order_relaxed);

		return pPtr;
	}

	void* MemoryPool::Realloc(void* ptr, size_t newSize, size_t alignment)
	{
		unused(ptr, newSize, alignment);
		return nullptr;
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory Pool manager
	//



	// Max memory size for pool
	constexpr size_t MemoryPoolManager::MAX_MEMORYSIZE_SHIFT;
	constexpr size_t MemoryPoolManager::MAX_MEMORYSIZE_POWEROF2;
	// memory alignment size
	constexpr size_t MemoryPoolManager::MAX_MEMORYPOOL_ALIGNMENT_SHIFT;
	constexpr size_t MemoryPoolManager::MAX_MEMORYPOOL_ALIGNMENT;
	constexpr size_t MemoryPoolManager::MAX_MEMORYPOOL_COUNT;



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	MemoryPoolManager
	//

	MemoryPoolManager *MemoryPoolManager::stm_pMemoryPoolManager = nullptr;

	MemoryPoolManager::MemoryPoolManager(IHeap& heap)
	{
		int sizeShift = 1;
		for (auto& itPoolItem : m_MemoryPoolbySize)
		{
			itPoolItem.MaxAllocationSize = (size_t)1 << sizeShift;
			itPoolItem.pMemoryPool = new MemoryPool(heap, itPoolItem.MaxAllocationSize);
			sizeShift++;
		}
	}

	MemoryPoolManager::~MemoryPoolManager()
	{
		// How can we delete them?
		for (auto& itPoolItem : m_MemoryPoolbySize)
		{
			IHeap::Delete(itPoolItem.pMemoryPool);
		}
	}

	bool MemoryPoolManager::QuantizeAndFind(size_t memorySize, uint32_t& minBitShift, size_t &newSize)
	{
		Assert(memorySize < (size_t)std::numeric_limits<uint32_t>::max());

		minBitShift = Util::FindMinBitShift((uint32_t)memorySize);

		newSize = (size_t)1 << minBitShift;
		if (newSize > MAX_MEMORYSIZE_POWEROF2)
		{
			// We don't use memory pool for this type
			newSize = AlignUp(memorySize, MAX_MEMORYPOOL_ALIGNMENT);
			return false;
		}
		else
		{
			return true;
		}
	}

	// Get memory pool
	MemoryPool* MemoryPoolManager::GetMemoryPool(size_t allocationSize)
	{

		uint32_t minBitShift;
		size_t newAllocationSize = allocationSize;
		if (!QuantizeAndFind(allocationSize, minBitShift, newAllocationSize))
			return nullptr;

		assert(minBitShift != 0 && minBitShift < countof(m_MemoryPoolbySize));
		auto poolIndex = minBitShift - 1;

		if (poolIndex >= countof(m_MemoryPoolbySize))
			return nullptr;

		assert(m_MemoryPoolbySize[poolIndex].MaxAllocationSize >= newAllocationSize);
		return m_MemoryPoolbySize[poolIndex].pMemoryPool;
	}

	// Get memory pool by size
	MemoryPool* MemoryPoolManager::GetMemoryPoolBySize(size_t allocationSize)
	{
		// TODO: release memory pool manager. use regular heap to allocated it on std heap
		if (stm_pMemoryPoolManager == nullptr)
			stm_pMemoryPoolManager = new MemoryPoolManager(GetSystemHeap());

		return stm_pMemoryPoolManager->GetMemoryPool(allocationSize);
	}




}	// namespace SF


