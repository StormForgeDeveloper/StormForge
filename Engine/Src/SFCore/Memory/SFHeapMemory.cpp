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


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Thread/SFThread.h"
#include "Memory/SFMemory.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFHeapMemory.h"




namespace SF
{


	constexpr size_t HeapMemory::BASE_ALIGNMENT;


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Heap memory block
	// 


	// Allocate from this heap memory block
	HeapTree::MapNode* HeapMemory::MemoryBlock::Allocate(IHeap* thisHeap, size_t size, size_t alignment)
	{
		HeapTree::MapNode *pFreeChunk = nullptr;
		if (!FreeChunkTree.FindSameOrBigger(static_cast<HeapTree::KeyType>(MapNodeHeaderSize + size), pFreeChunk))
			return nullptr;

		Result result = FreeChunkTree.Remove(pFreeChunk);
		Assert(result);
		if (!result) return nullptr;

		auto pData = (uint8_t*)pFreeChunk + MapNodeHeaderSize;
		size_t blockSize = pFreeChunk->Size;
		if (blockSize < (size + MapNodeHeaderSize + SF_ALIGN_DOUBLE))
		{
			// it's too small to divide let's use them all
		}
		else
		{
			// Cut remain part and add back to free tree
			pFreeChunk->Size = static_cast<HeapTree::KeyType>(size);

			auto pNextChunk = GetNextChunk(pFreeChunk);
			auto pNewChunk = new((void*)(pData + size)) HeapTree::MapNode(blockSize - MapNodeHeaderSize - size);

			pNewChunk->PrevChunk = pFreeChunk;
			if (pNextChunk != nullptr) pNextChunk->PrevChunk = pNewChunk;
			result = FreeChunkTree.Insert(pNewChunk);
			Assert(result);
			if (!result) return nullptr;
		}

		pFreeChunk->InitHeader(thisHeap, pFreeChunk->Size, pFreeChunk->GetHeaderSize());
		pFreeChunk->State = 1;

		return pFreeChunk;
	}

	// Free heap memory block.
	Result HeapMemory::MemoryBlock::Free(HeapTree::MapNode* pMemChunk)
	{
		if (pMemChunk == nullptr)
			return ResultCode::INVALID_POINTER;

		auto ptrPos = reinterpret_cast<uintptr_t>(pMemChunk);
		auto begin = reinterpret_cast<uintptr_t>(this) + MemBlockHeaderSize;
		auto end = begin + BlockSize;
		if (ptrPos < begin || ptrPos >= end)
			return ResultCode::NOT_EXIST;

		pMemChunk->State = 0;

		// merge next chunk if possible
		auto pNextChunk = GetNextChunk(pMemChunk);
		if (pNextChunk != nullptr && pNextChunk->State == 0)
		{
			// Remove next chunk from free list
			auto result = FreeChunkTree.Remove(pNextChunk);
			if (!result && result != ResultCode::NOT_EXIST)
			{
				// broken memory
				AssertRel(false);
				return result;
			}

			pMemChunk = MergeChunks(pMemChunk, pNextChunk);
		}

		// merge previous chunk if possible
		auto pPrevChunk = GetPrevChunk(pMemChunk);
		if (pPrevChunk != nullptr && pPrevChunk->State == 0)
		{
			// Remove next chunk from free list
			auto result = FreeChunkTree.Remove(pPrevChunk);
			if (!result && result != ResultCode::NOT_EXIST)
			{
				// broken memory
				AssertRel(false);
				return result;
			}

			pMemChunk = MergeChunks(pPrevChunk, pMemChunk);
		}

		return FreeChunkTree.Insert(pMemChunk);
	}

	// Access neighbor chunk
	HeapTree::MapNode* HeapMemory::MemoryBlock::GetNextChunk(HeapTree::MapNode* pMemChunk)
	{
		auto begin = reinterpret_cast<uintptr_t>(this) + MemBlockHeaderSize;
		auto end = begin + BlockSize;

		auto nextPos = reinterpret_cast<uintptr_t>(pMemChunk) + pMemChunk->GetHeaderSize() + pMemChunk->Size;
		if (nextPos < end)
		{
			return reinterpret_cast<HeapTree::MapNode*>(nextPos);
		}

		return nullptr;
	}

	HeapTree::MapNode* HeapMemory::MemoryBlock::GetPrevChunk(HeapTree::MapNode* pMemChunk)
	{
		return pMemChunk->PrevChunk;
	}

	// Merge two chunks, and returns new chunk
	HeapTree::MapNode* HeapMemory::MemoryBlock::MergeChunks(HeapTree::MapNode* pMemChunk, HeapTree::MapNode* pNextChunk)
	{
		if (pNextChunk->State != 0)
			return pNextChunk;

		auto pNextOfNextChunk = GetNextChunk(pNextChunk);

		pNextOfNextChunk->PrevChunk = pMemChunk;
		pMemChunk->Size += pNextChunk->Size + MapNodeHeaderSize;

		// erase contents of pNextChunk
		memset(pNextChunk, 0xCD, sizeof(HeapTree::MapNode));

		return pMemChunk;
	}


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Heap memory manager
	//

	HeapMemory::HeapMemory(StringCrc64 name, IHeap& parentHeap, size_t initialMemoryBlockSize)
		: IHeap(name, &parentHeap)
	{
		if (initialMemoryBlockSize > 0)
		{
			auto allocSize = MemBlockHeaderSize + initialMemoryBlockSize;
			auto pBlock = parentHeap.Alloc(allocSize);

			AddMemoryBlock(allocSize, pBlock, true);
		}
	}

	HeapMemory::~HeapMemory()
	{
		auto itBlock = m_MemoryBlockList.pop_front();
		while(itBlock != nullptr)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			if (pMemBlock->IsOwner)
				delete[] (uint8_t*)itBlock;

			itBlock = m_MemoryBlockList.pop_front();
		}
	}


	// Interface for raw allocation. If the implementation requires custom memory header, the memory header size should be included in the request size
	MemBlockHdr* HeapMemory::AllocInternal(size_t size, size_t alignment)
	{
		Result result;

		Assert(alignment <= BASE_ALIGNMENT);

		// always use aligned size
		size = AlignUp(size, BASE_ALIGNMENT);

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			HeapTree::MapNode * pAllocated = pMemBlock->Allocate(this, size, alignment);
			if (pAllocated != nullptr)
				return pAllocated;
		}

		SFLog(System, Warning, "Allocating from overflow heap size:{0}", size);

		return IHeap::AllocInternal(size, alignment);
	}

	MemBlockHdr* HeapMemory::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		// TODO: Optimize
		FreeInternal(ptr);
		return AllocInternal(newSize, alignment);
	}

	void HeapMemory::FreeInternal(MemBlockHdr* ptr)
	{
		if (ptr == nullptr)
			return;

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			if (pMemBlock->Free(static_cast<HeapTree::MapNode*>(ptr)))
			{
				return;
			}
		}

		GetParent()->FreeInternal(ptr);

		return;
	}



	// Add memory block to the 
	//	@blockSize: memory block size pointed by pMemoryBlock
	//	@pMemoryBlock: memory block pointer
	//	@takeOverOwnerShip: If true the memory block will re deleted by this class
	void HeapMemory::AddMemoryBlock(size_t blockSize, void* pMemoryBlock, bool takeOverOwnerShip)
	{
		auto pMemBlock = new(pMemoryBlock) MemoryBlock;
		pMemBlock->BlockSize = blockSize - MemBlockHeaderSize;
		pMemBlock->IsOwner = takeOverOwnerShip;

		auto pDataBlock = (uint8_t*)pMemoryBlock + MemBlockHeaderSize;
		auto pDataBlockNode = new(pDataBlock) HeapTree::MapNode(pMemBlock->BlockSize - MapNodeHeaderSize);
		pMemBlock->FreeChunkTree.Insert(pDataBlockNode);

		m_MemoryBlockList.push_back(pMemBlock);
	}



	
};	// namespace SF





