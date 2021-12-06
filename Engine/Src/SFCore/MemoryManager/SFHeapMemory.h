////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
		static constexpr size_t MapNodeOverhead = MapNodeHeaderSize + MemBlockHdr::MaxHeaderAlignment + MapNodeFooterSize;


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
		//  @return: added memory block pointer
		MemoryBlock* AddMemoryBlock(size_t blockSize, void* pMemoryBlock, bool takeOverOwnerShip = false);


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
			m_BaseMemoryBlock = super::AddMemoryBlock(sizeof(m_StaticMemoryBlock), m_StaticMemoryBlock, false);
		}

		SF_FORCEINLINE const uint8_t* GetStaticBuffer() const { return m_StaticMemoryBlock; }
		SF_FORCEINLINE const HeapMemory::MemoryBlock* GetBaseMemoryBlock() const { return m_BaseMemoryBlock; }

	private:

		uint8_t m_StaticMemoryBlock[StaticSize + HeapMemory::MinumumMemoryBlockOverhead];
		HeapMemory::MemoryBlock* m_BaseMemoryBlock{};

	};

	// Memory allocation history
	struct HeapMemoryHistory
	{
		char Op;
		intptr_t PosIn;
		intptr_t PosOut;
		size_t Size;
		size_t Alignment;

		static Result ReplayHistory(IHeap& heap, const uint8_t* basePtr, size_t numHistory, const HeapMemoryHistory* pHistory);
	};

	// memory allocator from static block
	template<size_t StaticSize, class HeapMemoryType = HeapMemory>
	class StaticMemoryAllocatorDebugT : public HeapMemoryType
	{
	public:

		using super = HeapMemoryType;

		StaticMemoryAllocatorDebugT(StringCrc64 nameCrc, IHeap& parentHeap)
			: HeapMemoryType(nameCrc, parentHeap, 0)
		{
			memset(m_History, 0, sizeof(m_History));
			m_BaseMemoryBlock = super::AddMemoryBlock(sizeof(m_StaticMemoryBlock), m_StaticMemoryBlock, false);
		}

		SF_FORCEINLINE const HeapMemory::MemoryBlock* GetBaseMemoryBlock() const { return m_BaseMemoryBlock; }

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override
		{
			auto ptr = super::AllocInternal(size, alignment);
			auto ptrPos = intptr_t(ptr) - intptr_t(m_BaseMemoryBlock);
			assert(ptrPos >= 0);
			auto buffLen = sizeof(m_History) - m_HistoryPos;
			static const char strFormat[] = "{ 'A', 0, 0x%" PRIxPTR ",%zu,%zu },\n";
			m_HistoryPos += snprintf(m_History + m_HistoryPos, buffLen, strFormat, ptrPos, size, alignment);
			if ((m_HistoryPos + 128) >= sizeof(m_History)) m_HistoryPos = 0; // reset pos
			return ptr;
		}

		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override
		{
			auto ptrPos = intptr_t(ptr) - intptr_t(m_BaseMemoryBlock);
			assert(ptrPos >= 0);

			auto newBlock = super::ReallocInternal(ptr, orgSize, newSize, alignment);
			if (newBlock == nullptr)
				return nullptr;

			auto ptrPos2 = intptr_t(newBlock) - intptr_t(m_BaseMemoryBlock);
			if (ptrPos >= 0 && ptrPos < sizeof(m_StaticMemoryBlock))
			{
				assert(ptrPos2 >= 0);
				auto buffLen = sizeof(m_History) - m_HistoryPos;
				static const char strFormat[] = "{ 'R',0x%" PRIxPTR ",0x%" PRIxPTR ",%zu,%zu },\n";
				m_HistoryPos += snprintf(m_History + m_HistoryPos, buffLen, strFormat, ptrPos, ptrPos2, newSize, alignment);
				if ((m_HistoryPos + 128) >= sizeof(m_History)) m_HistoryPos = 0; // reset pos
			}

			return newBlock;
		}

		virtual void FreeInternal(MemBlockHdr* ptr) override
		{
			auto ptrPos = intptr_t(ptr) - intptr_t(m_BaseMemoryBlock);
			assert(ptrPos >= 0);
			if (ptrPos >= 0 && ptrPos < sizeof(m_StaticMemoryBlock))
			{
				auto buffLen = sizeof(m_History) - m_HistoryPos;
				static const char strFormat[] = "{ 'F',0x%" PRIxPTR ", 0, 0, 0 },\n";
				m_HistoryPos += snprintf(m_History + m_HistoryPos, buffLen, strFormat, ptrPos);
				if ((m_HistoryPos + 128) >= sizeof(m_History)) m_HistoryPos = 0; // reset pos
			}

			return super::FreeInternal(ptr);
		}

	private:

		uint8_t m_StaticMemoryBlock[StaticSize + HeapMemory::MinumumMemoryBlockOverhead];
		HeapMemory::MemoryBlock* m_BaseMemoryBlock{};

		size_t m_HistoryPos = 0;
		char m_History[((StaticSize / HeapMemory::MapNodeOverhead) + 1) * 128];
	};

}



