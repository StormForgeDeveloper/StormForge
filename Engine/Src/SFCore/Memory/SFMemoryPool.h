////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory Pool 
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "Thread/SFSynchronization.h"
#include "Container/SFStackPool.h"
#include "Platform/StackWalker.h"
#include "Thread/SFSynchronization.h"
#include "Thread/SFSystemSynchronization.h"
#include "Container/SFSortedArray.h"






namespace SF {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory Pool
	//


	class MemoryPool : public IHeap
	{
	public:

		static constexpr int32_t  POOL_ITEM_MIN = 8;
		static constexpr int32_t  POOL_ITEM_MAX = 512;

		static constexpr int  FREE_LIST_SHIFT = 2;
		static constexpr int  FREE_LIST_NUM = 1 << FREE_LIST_SHIFT;
		static constexpr int  FREE_LIST_MASK = FREE_LIST_NUM - 1;


		// free stack item
		struct MemoryPoolItem
		{
			StackPool::Item StackItem;

			MemoryPoolItem()
			{
				memset(this, 0, sizeof(MemoryPoolItem));
			}
		};




	private:

		// allocation unit size
		size_t	m_AllocSize;

		// Allocated item count
		SyncCounter	m_AllocatedCount;

		// Free item stack
		std::atomic<uint32_t> m_FreeIndex;
		StackPool	m_FreeList[FREE_LIST_NUM];


	private:

		// Get memory pool item pointer from data pointer
		MemoryPoolItem* DataPtrToMemoryPoolItem(void* pPtr) { return (MemoryPoolItem*)((uint8_t*)pPtr + m_AllocSize); }
		void* MemoryPoolItemToDataPtr(MemoryPoolItem* pPtr) { return ((uint8_t*)pPtr - m_AllocSize); }

		//virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override;
		//virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

		StackPool& PickFreeList()
		{
			auto index = m_FreeIndex.fetch_add(1, std::memory_order_relaxed) & FREE_LIST_MASK;
			return m_FreeList[index];
		}

	public:
		// Constructor for singleton
		MemoryPool(IHeap& heap, size_t allocSize);
		virtual ~MemoryPool();


		// Get allocation data size
		size_t GetAllocSize() const { return m_AllocSize; }

		// Flush free items
		void Flush();

		// Allocate/Free
		virtual void* Alloc(size_t size, size_t alignment = SF_ALIGN_DOUBLE) override;
		virtual void* Realloc(void* ptr, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE) override;
	};




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory Pool manager
	//

	class MemoryPoolManager
	{
	private:

		// Max memory size for pool
		static constexpr size_t MAX_MEMORYSIZE_SHIFT = 8;
		static constexpr size_t MAX_MEMORYSIZE_POWEROF2 = 1 << MAX_MEMORYSIZE_SHIFT;
		// memory alignment size
		static constexpr size_t MAX_MEMORYPOOL_ALIGNMENT_SHIFT = 8;
		static constexpr size_t MAX_MEMORYPOOL_ALIGNMENT = 1 << MAX_MEMORYPOOL_ALIGNMENT_SHIFT;
		static constexpr size_t MAX_MEMORYPOOL_COUNT = MAX_MEMORYSIZE_SHIFT + 1;


		struct MemoryPoolItem
		{
			size_t MaxAllocationSize = 0;
			MemoryPool* pMemoryPool = nullptr;
		};

		// static instance
		static MemoryPoolManager* stm_pMemoryPoolManager;

		// memory pool by size
		MemoryPoolItem	m_MemoryPoolbySize[MAX_MEMORYPOOL_COUNT];


	private:

		// Quantize memory size
		bool QuantizeAndFind(size_t memorySize, uint32_t& minBitShift, size_t &newSize);


	public:

		MemoryPoolManager(IHeap& heap);
		~MemoryPoolManager();

		MemoryPool* GetMemoryPool(size_t allocationSize);

		// Get memory pool by size
		static MemoryPool* GetMemoryPoolBySize(size_t allocationSize);
	};







} // namespace SF






