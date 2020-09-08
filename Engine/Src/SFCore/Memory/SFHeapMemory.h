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
#include "Memory/SFIMemoryManager.h"
#include "Memory/SFHeapTree.h"
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

		static constexpr size_t BASE_ALIGNMENT = 16;

		//////////////////////////////////////////////////////////////////////////////////
		//
		//	Heap memory block
		// 

		struct MemoryBlock : public StaticDoubleLinkedList::Node
		{
			size_t BlockSize = 0;		// size of the block
			bool IsOwner = false;
			HeapTree FreeChunkTree;

			// Allocate from this heap memory block
			HeapTree::MapNode* Allocate(IHeap* thisHeap, size_t size, size_t alignment);

			// Free heap memory block.
			Result Free(HeapTree::MapNode* pMemBlock);

			// Access neighbor chunk
			HeapTree::MapNode* GetNextChunk(HeapTree::MapNode* pMemChunk);
			HeapTree::MapNode* GetPrevChunk(HeapTree::MapNode* pMemChunk);

			// Merge two chunks, and returns new chunk
			HeapTree::MapNode* MergeChunks(HeapTree::MapNode* pMemChunk, HeapTree::MapNode* pNextChunk);
		};


		static constexpr size_t MapNodeHeaderSize = AlignUp(sizeof(HeapTree::MapNode), BASE_ALIGNMENT);
		static constexpr size_t MemBlockHeaderSize = AlignUp(sizeof(MemoryBlock), BASE_ALIGNMENT);


	private:

		// Currently allocated and used list
		StaticDoubleLinkedList m_MemoryBlockList;

	public:

		// Constructor
		// @nameCrc: name of the heap
		// @parentHeap: parent heap, it also used for fall back heap
		// @initialMemoryBlockSize: Initial memory block size. 
		HeapMemory(StringCrc64 nameCrc, IHeap& parentHeap, size_t initialMemoryBlockSize = 4096);
		virtual ~HeapMemory();


	protected:

		// Interface for raw allocation. If the implementation requires custom memory header, the memory header size should be included in the request size
		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

	public:

		// Add memory block to the 
		//	@blockSize: memory block size pointed by pMemoryBlock
		//	@pMemoryBlock: memory block pointer
		//	@takeOverOwnerShip: If true the memory block will re deleted by this class
		void AddMemoryBlock(size_t blockSize, void* pMemoryBlock, bool takeOverOwnerShip = false);


		virtual void* Alloc(size_t size, size_t alignment = SF_ALIGN_DOUBLE) override;
		virtual void* Realloc(void* ptr, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE) override;

	};
}



