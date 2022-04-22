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

	HeapMemory::MemoryBlock::MemoryBlock(HeapMemory* pHeap, size_t blockSize, bool isOwner)
		: BlockSize(blockSize)
		, IsOwner(isOwner)
	{
		assert((BlockSize % MemBlockHdr::MaxHeaderAlignment) == 0);

		auto pDataBlock = reinterpret_cast<uint8_t*>(this) + MemBlockHeaderSize;

		pHead = new(pDataBlock) HeapTree::MapNode(pHeap, MemBlockHdr::MEM_MAGIC_FREE, BlockSize - MapNodeHeaderSize - MapNodeFooterSize);
		pHead->GetFooter()->InitFooter();

		FreeChunkTree.Insert(pHead);
	}

	// Allocate from this heap memory block
	HeapTree::MapNode* HeapMemory::MemoryBlock::Allocate(IHeap* thisHeap, size_t size, size_t alignment)
	{
		auto dataSectionSize = (uint32_t)AlignUp(size, MemBlockHdr::MaxHeaderAlignment);

		HeapTree::MapNode *pFreeChunk = nullptr, *pNewChunk = nullptr;
		if (!FreeChunkTree.FindSameOrBigger(dataSectionSize, pFreeChunk))
			return nullptr;

		assert(pFreeChunk->MemChunkHeader.Size >= size);

		auto chunkAllocationSize = static_cast<HeapTree::KeyType>(HeapMemory::CalculateAllocationSize(size, alignment));
		Result result = FreeChunkTree.Remove(pFreeChunk);
		Assert(result);
		if (!result) return nullptr;

		size_t blockSize = pFreeChunk->MemChunkHeader.Size;
		if (blockSize <= (chunkAllocationSize + HeapMemory::MapNodeOverhead))
		{
			assert((blockSize % MemBlockHdr::MaxHeaderAlignment) == 0);
			assert(dataSectionSize <= (uint)blockSize);
			dataSectionSize = (uint)blockSize;
			// it's too small to divide let's use them all

			pFreeChunk->MemChunkHeader.Magic = MemBlockHdr::MEM_MAGIC;
		}
		else
		{
			pFreeChunk->MemChunkHeader.InitHeader(thisHeap, (uint32_t)dataSectionSize, MapNodeHeaderSize);
			// Split chunk
			auto pNextChunkData = (uint8_t*)pFreeChunk + chunkAllocationSize;

			if (pNextChunkData) // If next chunk doesn't over the boundary
			{
				// - (allocating chunk footer + dataSize) - (next chunk header)
				// Next chunk uses footer from original chunk(before split)
				pNewChunk = new((void*)pNextChunkData) HeapTree::MapNode(thisHeap, MemBlockHdr::MEM_MAGIC_FREE, blockSize - (dataSectionSize + MapNodeFooterSize + MapNodeHeaderSize));

				pNewChunk->PrevMemoryChunk = pFreeChunk;
				auto pNextOfNext = GetNextChunk(pNewChunk);
				if (pNextOfNext != nullptr)
					pNextOfNext->PrevMemoryChunk = pNewChunk;

				result = FreeChunkTree.Insert(pNewChunk);
				Assert(result);
			}
		}
		assert((dataSectionSize % MemBlockHdr::MaxHeaderAlignment) == 0);

		pFreeChunk->GetFooter()->InitFooter();

#ifdef DEBUG
		if (pNewChunk)
		{
			auto pTestNextChunk = GetNextChunk(pFreeChunk);
			assert(pTestNextChunk == pNewChunk);
		}
#endif

		//CheckIntegrity();

		return pFreeChunk;
	}

	HeapTree::MapNode* HeapMemory::MemoryBlock::ResizeChunk(IHeap* thisHeap, HeapTree::MapNode* pMemBlock, size_t newSize)
	{
		newSize = AlignUp(newSize, MemBlockHdr::MaxHeaderAlignment);

		size_t totalAfterMerge = pMemBlock->MemChunkHeader.Size;
		if (totalAfterMerge >= newSize) // we don't support shrink
			return pMemBlock;

		// check whether we can combine next blocks
		auto pCurChunk = GetNextChunk(pMemBlock);
		for (; pCurChunk && pCurChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE; pCurChunk = GetNextChunk(pCurChunk))
		{
			totalAfterMerge += CalculateAllocationSize(pCurChunk->MemChunkHeader.Size);
			if (totalAfterMerge >= newSize)
				break;
		}

		// we can't increase block size
		if (totalAfterMerge < newSize)
			return nullptr;

		//CheckIntegrity();

		// We know we have space. merge free blocks
		pCurChunk = GetNextChunk(pMemBlock);
		HeapTree::MapNode* pNextChunk{};
		for (; pCurChunk && pCurChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE && pMemBlock->MemChunkHeader.Size < newSize; pCurChunk = pNextChunk)
		{
			pNextChunk = GetNextChunk(pCurChunk);
			FreeChunkTree.Remove(pCurChunk);

			MergeChunks(pMemBlock, pCurChunk);
		}

		//CheckIntegrity();

		// If the chunk has bunch of remain space, we need to split that up
		if (pMemBlock->MemChunkHeader.Size > (newSize + 2 * (MapNodeHeaderSize + MapNodeFooterSize)))
		{
			HeapTree::MapNode* pNewChunk{};
			if (SplitChunk(thisHeap, pMemBlock, newSize, pNewChunk))
			{
				FreeChunkTree.Insert(pNewChunk);
			}
		}

		//CheckIntegrity();

		return pMemBlock;
	}

	// Free heap memory block.
	Result HeapMemory::MemoryBlock::Free(HeapTree::MapNode* pMemChunk)
	{
		if (pMemChunk == nullptr)
			return ResultCode::INVALID_POINTER;

		if (!IsInThisBlock(pMemChunk))
			return ResultCode::NOT_EXIST;

		// merge next chunk if possible
		auto pNextChunk = GetNextChunk(pMemChunk);
#if DEBUG
		HeapTree::MapNode tempNext{};
		if (pNextChunk) tempNext = *pNextChunk;
#endif
		if (pMemChunk != pNextChunk && pNextChunk != nullptr && pNextChunk->MemChunkHeader.IsFree())
		{
			assert(FreeChunkTree.size() > 0);
			// Remove next chunk from free list
			auto result = FreeChunkTree.Remove(pNextChunk);
			if (!result)
			{
				// broken memory
				AssertRel(false);
				return result;
			}

			pMemChunk->MemChunkHeader.Magic = MemBlockHdr::MEM_MAGIC_FREE;
			auto bRet = MergeChunks(pMemChunk, pNextChunk);
			assert(bRet); unused(bRet);
			pMemChunk->MemChunkHeader.Magic = MemBlockHdr::MEM_MAGIC;
		}


		// merge previous chunk if possible
		auto pPrevChunk = GetPrevChunk(pMemChunk);
		if (pMemChunk != pPrevChunk && pPrevChunk != nullptr && pPrevChunk->MemChunkHeader.IsFree())
		{
#if DEBUG
			HeapTree::MapNode temp = *pPrevChunk;
#endif
			assert(FreeChunkTree.size() > 0);
			// Remove next chunk from free list
			auto result = FreeChunkTree.Remove(pPrevChunk);
			if (!result)
			{
				// broken memory
				AssertRel(false);
				return result;
			}

			pMemChunk->MemChunkHeader.Magic = MemBlockHdr::MEM_MAGIC_FREE;
			bool bRet = MergeChunks(pPrevChunk, pMemChunk);
			assert(bRet); unused(bRet);
			pMemChunk = pPrevChunk;
		}


		pMemChunk->MemChunkHeader.Magic = MemBlockHdr::MEM_MAGIC_FREE;
		assert(IsInThisBlock(pMemChunk));
		Result hr = FreeChunkTree.Insert(pMemChunk);
		assert(hr);
		assert(FreeChunkTree.IsInTheTree(pMemChunk));
		pMemChunk->GetFooter()->InitFooter(); // update call stack

		//CheckIntegrity();

		return hr;
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
		return pMemChunk->PrevMemoryChunk;
	}

	// Merge two chunks, and returns new chunk
	bool HeapMemory::MemoryBlock::MergeChunks(HeapTree::MapNode* pMemChunk, HeapTree::MapNode* pNextChunk)
	{
		if (!pNextChunk->MemChunkHeader.IsFree())
		{
			assert(false);
			return false;
		}

		assert(pNextChunk->MemChunkHeader.Magic == MemBlockHdr::MEM_MAGIC_FREE);
		assert(pMemChunk != pNextChunk);

		assert(IsInThisBlock(pMemChunk));
		assert(IsInThisBlock(pNextChunk));
		assert(GetNextChunk(pMemChunk) == pNextChunk);
		assert(pNextChunk->PrevMemoryChunk == pMemChunk);

		auto pNextOfNextChunk = GetNextChunk(pNextChunk);

		if (pNextOfNextChunk)
		{
			assert(pNextOfNextChunk->PrevMemoryChunk == pNextChunk);
			pNextOfNextChunk->PrevMemoryChunk = pMemChunk;
		}
		pMemChunk->MemChunkHeader.Size += MapNodeFooterSize + MapNodeHeaderSize + pNextChunk->MemChunkHeader.Size;

		// erase contents of pNextChunk header
		memset(pNextChunk, 0xC2, sizeof(HeapTree::MapNode));
#if DEBUG
		memcpy(pNextChunk, &pMemChunk, sizeof(void*));
#endif

		assert(GetNextChunk(pMemChunk) == pNextOfNextChunk);

		return true;
	}

	bool HeapMemory::MemoryBlock::SplitChunk(IHeap* ThisHeap, HeapTree::MapNode* pMemChunk, size_t newSize, HeapTree::MapNode* &pOutNewChunk)
	{
		// Make sure content block has enough space
		if (pMemChunk->MemChunkHeader.Size < CalculateAllocationSize(newSize))
			return false;

		auto OrgSize = pMemChunk->MemChunkHeader.Size;
		pMemChunk->MemChunkHeader.Size = (uint32_t)newSize;
		pMemChunk->GetFooter()->InitFooter();

		//auto nextChunkPos = uintptr_t(pMemChunk) + MapNodeHeaderSize + newSize + MapNodeFooterSize;
		auto nextChunkPos = GetNextChunk(pMemChunk);

		auto newBlockDataSize = OrgSize - (newSize + MapNodeFooterSize + MapNodeHeaderSize);
		pOutNewChunk = new((void*)nextChunkPos) HeapTree::MapNode(ThisHeap, MemBlockHdr::MEM_MAGIC_FREE, newBlockDataSize);
		//pOutNewChunk->GetFooter()->InitFooter(); // should be initialized already

		pOutNewChunk->PrevMemoryChunk = pMemChunk;
		auto nextOfNewChunk = GetNextChunk(pOutNewChunk);
		if (nextOfNewChunk)
			nextOfNewChunk->PrevMemoryChunk = pOutNewChunk;

		return true;
	}

	void HeapMemory::MemoryBlock::CheckIntegrity(HeapTree::MapNode* pSkipTest)
	{
#if DEBUG
		bool bRet{};
		HeapTree::MapNode* pPrevNode{};
		for (auto* pCurTest = pHead; pCurTest; pCurTest = GetNextChunk(pCurTest))
		{
			assert(IsInThisBlock(pCurTest));

			if (pCurTest != pHead)
			{
				assert(pPrev);
				bRet = pCurTest->PrevMemoryChunk == pPrevNode;
				assert(bRet);
			}

			if (pCurTest->MemChunkHeader.IsFree())
			{
				bRet = pCurTest == pSkipTest || FreeChunkTree.IsInTheTree(pCurTest);
				assert(bRet);
			}
			else
			{
				assert(pCurTest->SameKeyNextNode.NotInAnyList());
			}

			pPrevNode = pCurTest;
		}

#endif
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
#ifdef DEBUG
				auto pDataPtr = pAllocated->MemChunkHeader.GetDataPtr();
				auto pDataPtr2 = pAllocated->GetDataPtr();
				assert(pDataPtr == pDataPtr2);// If this doesn't match it will cause broken memory on release
				MemBlockHdr* pFoundMemBlock = GetMemoryBlockHdr(pDataPtr);
				assert(pFoundMemBlock && pFoundMemBlock == &pAllocated->MemChunkHeader);

				assert(pAllocated->GetFooter()->Magic == MemBlockFooter::MEM_MAGIC);
				assert(pAllocated->MemChunkHeader.GetFooter()->Magic == MemBlockFooter::MEM_MAGIC);
#endif
				AddAllocSize(pAllocated->MemChunkHeader.Size);
				return &pAllocated->MemChunkHeader;
			}
		}

		if (m_AllowOverflowAllocation)
		{
			SFLog(System, Debug5, "Allocating from overflow heap {0} size:{1}", GetNameCrc(), size);

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
		auto oldSize = ptr->Size;

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			if (pMemBlock->IsInThisBlock(pMemChunk))
			{
				pMemBlock->ResizeChunk(this, pMemChunk, newSize);
				break;
			}
		}

		if (pMemChunk->MemChunkHeader.Size != oldSize)
		{
			SubAllocSize(oldSize);
			AddAllocSize(pMemChunk->MemChunkHeader.Size);
		}

		if (pMemChunk->MemChunkHeader.Size >= newSize)
		{
			return &pMemChunk->MemChunkHeader;
		}

		return nullptr;
	}

	void HeapMemory::FreeInternal(MemBlockHdr* ptr)
	{
		if (ptr == nullptr)
			return;

		SubAllocSize(ptr->Size);

		auto pMemChunk = ContainerPtrFromMember(HeapTree::MapNode, MemChunkHeader, ptr);

		for (auto itBlock : m_MemoryBlockList)
		{
			auto pMemBlock = static_cast<MemoryBlock*>(itBlock);
			if (!pMemBlock->IsInThisBlock(pMemChunk))
				continue;

			if (pMemBlock->Free(pMemChunk))
			{
				return;
			}
			else
			{
				assert(false);
			}
		}

		GetParent()->FreeInternal(ptr);

		return;
	}



	// Add memory block to the 
	//	@blockSize: memory block size pointed by pMemoryBlock
	//	@pMemoryBlock: memory block pointer
	//	@takeOverOwnerShip: If true the memory block will re deleted by this class
	HeapMemory::MemoryBlock* HeapMemory::AddMemoryBlock(size_t blockSize, void* pMemoryBlock, bool takeOverOwnerShip)
	{
		// drop bytes if the address isn't aligned
		if ((uintptr_t(pMemoryBlock) % MemBlockHdr::MaxHeaderAlignment) != 0)
		{
			blockSize -= MemBlockHdr::MaxHeaderAlignment;
			pMemoryBlock = (void*)AlignUp(uintptr_t(pMemoryBlock), MemBlockHdr::MaxHeaderAlignment);
		}

		blockSize &= ~(MemBlockHdr::MaxHeaderAlignment - 1); // chop down not aligned area

		// test block size requirement
		if (blockSize < MemBlockHdr::MaxHeaderAlignment)
			return nullptr;

		assert(blockSize > (sizeof(MemoryBlock) + MapNodeFooterSize + MapNodeHeaderSize)); // the memory size should be bigger than header informations
		auto pMemBlock = new(pMemoryBlock) MemoryBlock(this, blockSize - MemBlockHeaderSize, takeOverOwnerShip);

		m_MemoryBlockList.push_back(pMemBlock);
		return pMemBlock;
	}

	Result HeapMemoryHistory::ReplayHistory(IHeap& heap, const uint8_t* basePtr, size_t numHistory, const HeapMemoryHistory* pHistory)
	{
		SortedArray<MemBlockHdr* , MemBlockHdr*> allocated(GetEngineHeap());
		MemBlockHdr* pNewBlockHeader{};
		for (uint iHistory = 0; iHistory < numHistory; iHistory++, pHistory++)
		{
			auto pBlockHeaderIn = (MemBlockHdr*)(basePtr + pHistory->PosIn);
			auto pBlockHeaderOut = pHistory->PosOut > 0 ? (MemBlockHdr*)(basePtr + pHistory->PosOut) : nullptr;
			pNewBlockHeader = nullptr;
			switch (pHistory->Op)
			{
			case 'A':
				pNewBlockHeader = heap.AllocInternal(pHistory->Size, pHistory->Alignment);
				if (pNewBlockHeader)
				{
					if (pBlockHeaderOut != pNewBlockHeader)
						return ResultCode::FAIL;

					allocated.Insert(pNewBlockHeader, pNewBlockHeader);
				}
				break;
			case 'R':
				pNewBlockHeader = heap.ReallocInternal(pBlockHeaderIn, pBlockHeaderIn->Size, pHistory->Size, pHistory->Alignment);
				if (pNewBlockHeader)
				{
					if (pBlockHeaderOut != pNewBlockHeader)
						return ResultCode::FAIL;

					if (pBlockHeaderIn != pNewBlockHeader)
					{
						allocated.Remove(pBlockHeaderIn, pBlockHeaderIn);
						allocated.Insert(pNewBlockHeader, pNewBlockHeader);
					}
				}
				break;
			case 'F':
				if (!allocated.Find(pBlockHeaderIn, pNewBlockHeader))
					return ResultCode::FAIL;

				heap.FreeInternal(pBlockHeaderIn);
				break;
			default:
				assert(false);
				break;
			}

		}

		return ResultCode::SUCCESS;
	}


}	// namespace SF





