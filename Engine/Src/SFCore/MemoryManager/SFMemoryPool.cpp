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
#include "Util/SFStrUtil.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "Multithread/SFSynchronization.h"
#include "ResultCode/SFResultCodeSystem.h"

#include "Container/SFHashTable2.h"
#include "Platform/SFStackWalker.h"
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
		, m_AllocSize(std::max(sizeof(MemoryPoolItem), allocSize))
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
			StackPool::Item* pPoolItem = itFreeList.Pop();
			while (pPoolItem != nullptr)
			{
				// Unmark used for memory pool
                MemoryPoolItem* pMemPoolItem = ContainerPtrFromMember(MemoryPoolItem, StackItem, pPoolItem);
				MemBlockHdr* pMemBlock = reinterpret_cast<MemBlockHdr*>(pMemPoolItem) - 1;
				assert(pMemBlock->Magic == MemBlockHdr::MEM_MAGIC);

				super::FreeInternal(pMemBlock);

				pPoolItem = itFreeList.Pop();
			}
		}
	}

	// Allocate/Free
    MemBlockHdr* MemoryPool::AllocInternal(size_t size, size_t alignment)
	{
        if (size > GetAllocSize())
        {
            Assert(false);
            return nullptr;
        }

        MemBlockHdr* pMemBlock{};
		StackPool& freeList = PickFreeList();
		MemoryPoolItem *pItem = reinterpret_cast<MemoryPoolItem*>(freeList.Pop());
		if (pItem == nullptr)
		{
			// Allocate page if no free item
            pMemBlock = GetParent()->AllocInternal(m_AllocSize, alignment);
			if (pMemBlock == nullptr)
				return nullptr;

			pItem = reinterpret_cast<MemoryPoolItem*>(pMemBlock->GetDataPtr());
		}
        else
        {
            pMemBlock = reinterpret_cast<MemBlockHdr*>(pItem) - 1;
        }
        memset(pItem, 0, sizeof(MemoryPoolItem));

		return pMemBlock;
	}

	MemBlockHdr* MemoryPool::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		// Not support realloc
		return nullptr;
	}

	void MemoryPool::FreeInternal(MemBlockHdr* pMemBlock)
	{
		StackPool& freeList = PickFreeList();
		size_t freeItemCount = freeList.size();
		if (freeItemCount > POOL_ITEM_MAX)
		{
			super::FreeInternal(pMemBlock);
		}
		else
		{
			MemoryPoolItem *pMemPoolItem = reinterpret_cast<MemoryPoolItem*>(pMemBlock->GetDataPtr());
			if (pMemPoolItem == nullptr)
			{
				return;
			}

            memset(pMemPoolItem, 0, sizeof(MemoryPoolItem));

            Assert(pMemBlock->Magic == MemBlockHdr::MEM_MAGIC);

            freeList.Push(&pMemPoolItem->StackItem);
		}

		m_AllocatedCount.fetch_sub(1, std::memory_order_relaxed);
	}

	// Allocate/Free
	void* MemoryPool::Alloc(size_t size, size_t alignment)
	{
		MemBlockHdr* pMemBlock = AllocInternal(GetAllocSize(), alignment);
		if (pMemBlock == nullptr)
			return nullptr;

        // redirect heap to me
        pMemBlock->pHeap = this;

		MemoryPoolItem *pMemItem = reinterpret_cast<MemoryPoolItem*>(pMemBlock->GetDataPtr());
		if (pMemItem == nullptr)
		{
			return nullptr;
		}

		m_AllocatedCount.fetch_add(1, std::memory_order_relaxed);

		return pMemItem + 1;
	}

	void* MemoryPool::Realloc(void* ptr, size_t newSize, size_t alignment)
	{
		unused(ptr, newSize, alignment);
		return nullptr;
	}



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


