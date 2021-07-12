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
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFHeapMemory.h"




namespace SF
{



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Heap memory block
	// 



	// Allocate from this heap memory block
	HeapTree::MapNode* HeapMemory::MemoryBlock::Allocate(IHeap* thisHeap, size_t size, size_t alignment)
	{
		auto dataSectionSize = (uint32_t)AlignUp(size, MemBlockHdr::MaxHeaderAlignment);

		HeapTree::MapNode *pFreeChunk = nullptr, *pNewChunk = nullptr;
		if (!FreeChunkTree.FindSameOrBigger(dataSectionSize, pFreeChunk))
			return nullptr;

		auto chunkAllocationSize = static_cast<HeapTree::KeyType>(HeapMemory::CalculateAllocationSize(size, alignment));
		Result result = FreeChunkTree.Remove(pFreeChunk);
		Assert(result);
		if (!result) return nullptr;

		size_t blockSize = pFreeChunk->MemChunkHeader.Size;
		if (blockSize < chunkAllocationSize)
		{
			// it's too small to divide let's use them all
		}
		else
		{
			// Split chunk
			auto pNextChunkData = (uint8_t*)pFreeChunk + chunkAllocationSize;
			auto pNextChunk = GetNextChunk(pFreeChunk);
			// - (allocating chunk footer + dataSize) - (next chunk header)
			// Next chunk uses footer from original chunk(before split)
			pNewChunk = new((void*)pNextChunkData) HeapTree::MapNode(thisHeap, MemBlockHdr::MEM_MAGIC_FREE, blockSize - (dataSectionSize + MapNodeFooterSize + MapNodeHeaderSize));

			pNewChunk->PrevChunk = pFreeChunk;
			if (pNextChunk != nullptr) pNextChunk->PrevChunk = pNewChunk;
			result = FreeChunkTree.Insert(pNewChunk);
			Assert(result);
			if (!result) return nullptr;
		}

		pFreeChunk->MemChunkHeader.InitHeader(thisHeap, (uint32_t)dataSectionSize, MapNodeHeaderSize);
		pFreeChunk->GetFooter()->InitFooter();
		pFreeChunk->State = 1;

		if (pNewChunk)
		{
			auto pTestNextChunk = GetNextChunk(pFreeChunk);
			assert(pTestNextChunk == pNewChunk);
		}

		return pFreeChunk;
	}

	HeapTree::MapNode* HeapMemory::MemoryBlock::ResizeChunk(IHeap* thisHeap, HeapTree::MapNode* pMemBlock, size_t newSize)
	{
		size_t totalAfterMerge = pMemBlock->MemChunkHeader.Size;
		if (totalAfterMerge >= newSize) // we don't support shrink
			return pMemBlock;

		// check whether we can combine next blocks
		auto pCurChunk = GetNextChunk(pMemBlock);
		for (; pCurChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE; pCurChunk = GetNextChunk(pCurChunk))
		{
			totalAfterMerge += CalculateAllocationSize(pCurChunk->MemChunkHeader.Size);
			if (totalAfterMerge >= newSize)
				break;
		}

		// we can't increase block size
		if (totalAfterMerge < newSize)
			return nullptr;

		// We know we have space. merge free blocks
		pCurChunk = GetNextChunk(pMemBlock);
		auto pNextChunk = GetNextChunk(pCurChunk);
		for (; pCurChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE; pCurChunk = pNextChunk)
		{
			pNextChunk = GetNextChunk(pCurChunk);
			FreeChunkTree.Remove(pCurChunk);

			MergeChunks(pMemBlock, pCurChunk);
		}

		return pMemBlock;
	}

	// Free heap memory block.
	Result HeapMemory::MemoryBlock::Free(HeapTree::MapNode* pMemChunk)
	{
		if (pMemChunk == nullptr)
			return ResultCode::INVALID_POINTER;

		if (!IsInThisBlock(pMemChunk))
			return ResultCode::NOT_EXIST;

		pMemChunk->MemChunkHeader.Magic = MemBlockHdr::MEM_MAGIC_FREE;
		pMemChunk->State = 0;

		// merge next chunk if possible
		auto pNextChunk = GetNextChunk(pMemChunk);
		if (pMemChunk != pNextChunk && pNextChunk != nullptr && pNextChunk->State == 0)
		{
			assert(FreeChunkTree.size() > 0);
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
		if (pMemChunk != pPrevChunk && pPrevChunk != nullptr && pPrevChunk->State == 0)
		{
			assert(FreeChunkTree.size() > 0);
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

		assert(pMemChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE);
		assert(IsInThisBlock(pMemChunk));
		return FreeChunkTree.Insert(pMemChunk);
	}

	// Access neighbor chunk
	HeapTree::MapNode* HeapMemory::MemoryBlock::GetNextChunk(HeapTree::MapNode* pMemChunk)
	{
		assert(pMemChunk->MemChunkHeader.HeaderSize == HeapMemory::MapNodeHeaderSize);
		assert(pMemChunk->MemChunkHeader.GetFooterSize() == HeapMemory::MapNodeFooterSize);
		assert(IsInThisBlock(pMemChunk));

		auto nextPos = reinterpret_cast<uintptr_t>(pMemChunk) + HeapMemory::MapNodeHeaderSize + pMemChunk->MemChunkHeader.Size + HeapMemory::MapNodeFooterSize;
		if (IsInThisBlock(reinterpret_cast<HeapTree::MapNode*>(nextPos)))
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

		assert(pNextChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE);
		assert(pMemChunk != pNextChunk);

		assert(IsInThisBlock(pMemChunk));
		assert(IsInThisBlock(pNextChunk));

		auto pNextOfNextChunk = GetNextChunk(pNextChunk);

		if (pNextOfNextChunk) pNextOfNextChunk->PrevChunk = pMemChunk;
		pMemChunk->MemChunkHeader.Size += MapNodeFooterSize + MapNodeHeaderSize + pNextChunk->MemChunkHeader.Size;

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
				IHeap::Delete((uint8_t*)itBlock);

			itBlock = m_MemoryBlockList.pop_front();
		}
	}


	// Interface for raw allocation. If the implementation requires custom memory header, the memory header size should be included in the request size
	MemBlockHdr* HeapMemory::AllocInternal(size_t size, size_t alignment)
	{
		Result result;

		// always use aligned size
		size = AlignUp(size, MemBlockHdr::MaxHeaderAlignment);

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			HeapTree::MapNode * pAllocated = pMemBlock->Allocate(this, size, alignment);

			if (pAllocated != nullptr)
			{
				auto pDataPtr = pAllocated->MemChunkHeader.GetDataPtr();
				auto pDataPtr2 = pAllocated->GetDataPtr();
				assert(pDataPtr == pDataPtr2);
				MemBlockHdr* pFoundMemBlock = GetMemoryBlockHdr(pDataPtr);
				assert(pFoundMemBlock && pFoundMemBlock == &pAllocated->MemChunkHeader);

				return &pAllocated->MemChunkHeader;
			}
		}

		if (m_AllowOverflowAllocation)
		{
			SFLog(System, Debug, "Allocating from overflow heap size:{0}", size);

			return IHeap::AllocInternal(size, alignment);
		}
		else
		{
			return nullptr;
		}
	}

	MemBlockHdr* HeapMemory::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		auto pMemChunk = ContainerPtrFromMember(HeapTree::MapNode, MemChunkHeader, ptr);

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			if (pMemBlock->IsInThisBlock(pMemChunk))
			{
				auto pResized = pMemBlock->ResizeChunk(this, pMemChunk, newSize);
				if (pResized)
				{
					pMemChunk = pResized;
					break;
				}
			}
		}

		if (pMemChunk->MemChunkHeader.Size >= newSize)
			return &pMemChunk->MemChunkHeader;

		// fall back, reallocate
		FreeInternal(&pMemChunk->MemChunkHeader);
		return AllocInternal(newSize, alignment);
	}

	void HeapMemory::FreeInternal(MemBlockHdr* ptr)
	{
		if (ptr == nullptr)
			return;

		auto pMemChunk = ContainerPtrFromMember(HeapTree::MapNode, MemChunkHeader, ptr);

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			if (pMemBlock->Free(pMemChunk))
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
		assert(blockSize > (sizeof(MemoryBlock) + MapNodeFooterSize + MapNodeHeaderSize)); // the memory size should be bigger than header informations
		auto pMemBlock = new(pMemoryBlock) MemoryBlock;
		pMemBlock->BlockSize = blockSize - MemBlockHeaderSize;
		pMemBlock->IsOwner = takeOverOwnerShip;

		auto pDataBlock = (uint8_t*)pMemoryBlock + MemBlockHeaderSize;

		auto pDataBlockNode = new(pDataBlock) HeapTree::MapNode(this, MemBlockHdr::MEM_MAGIC_FREE, pMemBlock->BlockSize - MapNodeHeaderSize - MapNodeFooterSize);
		pDataBlockNode->GetFooter()->InitFooter();
		pMemBlock->FreeChunkTree.Insert(pDataBlockNode);

		m_MemoryBlockList.push_back(pMemBlock);
	}

}	// namespace SF





