////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory allocation library
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "MemoryManager/SFIMemoryManager.h"
#include "MemoryManager/SFHeapTree.h"
#include "Container/SFStaticDoubleLinkedList.h"

// Enable memory allocation trace
#define ENABLE_MEMORY_TRACE true



namespace SF
{
	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Heap memory manager
	//	 - It reserves memory and manage allocation inside
	//	 - If overflow happens it allocates from parent heap
	//

	class HeapMemory : public IHeap
	{
	public:

		//////////////////////////////////////////////////////////////////////////////////
		//
		//	Heap memory block
		// 

		struct MemoryBlock : public StaticDoubleLinkedList::Node
		{
			size_t BlockSize = 0;		// size of the block
			bool IsOwner = false;

			HeapTree::MapNode* pHead{};

			HeapTree FreeChunkTree;

			MemoryBlock(HeapMemory* pHeap, size_t blockSize, bool isOwner);

			// Allocate from this heap memory block
			HeapTree::MapNode* Allocate(IHeap* thisHeap, size_t size, size_t alignment);

			HeapTree::MapNode* ResizeChunk(IHeap* thisHeap, HeapTree::MapNode* pMemBlock, size_t newSize);

			// Free heap memory block.
			Result Free(HeapTree::MapNode* pMemBlock);

			SF_FORCEINLINE bool IsInThisBlock(HeapTree::MapNode* pMemChunk)
			{
				if (pMemChunk == nullptr)
					return false;

				auto ptrPos = reinterpret_cast<uintptr_t>(pMemChunk);
				auto begin = reinterpret_cast<uintptr_t>(this) + MemBlockHeaderSize;
				auto end = begin + BlockSize;
				if (ptrPos < begin || (ptrPos + MapNodeHeaderSize + MapNodeFooterSize) >= end)
					return false;

				assert((ptrPos + pMemChunk->MemChunkHeader.Size + MapNodeHeaderSize + MapNodeFooterSize) <= end);

				return true;
			}

			// Access neighbor chunk
			HeapTree::MapNode* GetNextChunk(HeapTree::MapNode* pMemChunk);
			HeapTree::MapNode* GetPrevChunk(HeapTree::MapNode* pMemChunk);

			// Merge two chunks, and returns new chunk
			bool MergeChunks(HeapTree::MapNode* pMemChunk, HeapTree::MapNode* pNextChunk);
			bool SplitChunk(IHeap* ThisHeap, HeapTree::MapNode* pMemChunk, size_t newSize, HeapTree::MapNode* &pOutNewChunk);

			void CheckIntegrity(HeapTree::MapNode* pSkipTest = nullptr);
		};

		static constexpr size_t MapNodeHeaderSize = AlignUp(sizeof(HeapTree::MapNode), MemBlockHdr::MaxHeaderAlignment);
		static constexpr size_t MemBlockHeaderSize = AlignUp(sizeof(MemoryBlock), MemBlockHdr::MaxHeaderAlignment);
		static constexpr size_t MapNodeFooterSize = AlignUp(sizeof(MemBlockFooter), MemBlockHdr::MaxHeaderAlignment);
		static constexpr size_t MinumumMemoryBlockOverhead = MapNodeHeaderSize + MemBlockHeaderSize + MapNodeFooterSize;


	private:

		// Currently allocated and used list
		StaticDoubleLinkedList m_MemoryBlockList;

		bool m_AllowOverflowAllocation = true;

	public:

		// Constructor
		// @nameCrc: name of the heap
		// @parentHeap: parent heap, it also used for fall back heap
		// @initialMemoryBlockSize: Initial memory block size. 
		HeapMemory(StringCrc64 nameCrc, IHeap& parentHeap, size_t initialMemoryBlockSize = 4096);
		virtual ~HeapMemory();

		SF_FORCEINLINE void SetAllowOverflowAllocation(bool bEnable) { m_AllowOverflowAllocation = bEnable; }
		SF_FORCEINLINE bool GetAllowOverflowAllocation() { return m_AllowOverflowAllocation; }

		static SF_FORCEINLINE size_t CalculateAllocationSize(size_t requestedSize, size_t alignment = SF_ALIGN_DOUBLE)
		{
			return MapNodeHeaderSize + AlignUp(requestedSize, MemBlockHdr::MaxHeaderAlignment) + MapNodeFooterSize;
		}


	protected:

		// Interface for raw allocation. If the implementation requires custom memory header, the memory header size should be included in the request size
		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

	public:

		// Add memory block to the 
		//	@blockSize: memory block size pointed by pMemoryBlock
		//	@pMemoryBlock: memory block pointer
		//	@takeOverOwnerShip: If true the memory block will be managed and deleted by this class
		void AddMemoryBlock(size_t blockSize, void* pMemoryBlock, bool takeOverOwnerShip = false);


		//virtual void* Alloc(size_t size, size_t alignment = SF_ALIGN_DOUBLE) override;
		//virtual void* Realloc(void* ptr, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE) override;

	};



	///////////////////////////////////////////////////////////////////////////
	// Thread safe version
	class HeapMemoryMT : public HeapMemory
	{
		using super = HeapMemory;

	public:
		HeapMemoryMT(StringCrc64 nameCrc, IHeap& parentHeap, size_t initialMemoryBlockSize = 4096)
			: HeapMemory(nameCrc, parentHeap, initialMemoryBlockSize)
		{
		}

	protected:
		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override
		{
			MutexScopeLock scopeLock(m_Lock);
			return super::AllocInternal(size, alignment);
		}

		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override
		{
			MutexScopeLock scopeLock(m_Lock);
			return super::ReallocInternal(ptr, orgSize, newSize, alignment);
		}

		virtual void FreeInternal(MemBlockHdr* ptr) override
		{
			MutexScopeLock scopeLock(m_Lock);
			return super::FreeInternal(ptr);
		}

	private:

		CriticalSection m_Lock;
	};


	// memory allocator from static block
	template<size_t StaticSize, class HeapMemoryType = HeapMemory>
	class StaticMemoryAllocatorT : public HeapMemoryType
	{
	public:

		using super = HeapMemoryType;

		StaticMemoryAllocatorT(StringCrc64 nameCrc, IHeap& parentHeap)
			: HeapMemoryType(nameCrc, parentHeap, 0)
		{
			super::AddMemoryBlock(sizeof(m_StaticMemoryBlock), m_StaticMemoryBlock, false);
		}

	private:

		uint8_t m_StaticMemoryBlock[StaticSize + HeapMemory::MinumumMemoryBlockOverhead];
	};

}



