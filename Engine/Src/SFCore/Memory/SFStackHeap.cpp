////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Stack heap
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Memory/SFStackHeap.h"



namespace SF {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	static allocator interface
	//   // allocate from the buffer first
	//

	StackHeap::StackHeap(StringCrc64 name, IHeap& overflowHeap, size_t bufferSize, uint8_t* allocationBuffer)
		: IHeap(name, &overflowHeap)
		, m_AllocationBufferSize(bufferSize)
		, m_AllocationBuffer(allocationBuffer)
	{
		// Because of the chunk header uses 32bit integer, the limit will be maximum of int32. Actually it's uint32_t, but it's not a big deal
		assert(m_AllocationBufferSize < INT_MAX);// , "StackHeap: too big buffer size");

		MemoryChunkHeader* pChunk = reinterpret_cast<MemoryChunkHeader*>(m_AllocationBuffer);
		memset(pChunk, 0, sizeof(MemoryChunkHeader));
		pChunk->Magic = MemoryChunkHeader::MEM_MAGIC_FREE;
	}

	StackHeap::~StackHeap()
	{
	}

	// Allocate 
	MemBlockHdr* StackHeap::AllocInternal(size_t size, size_t alignment)
	{
		// allow zero size allocation
		if (size == 0)
			size = alignment;

		MemoryChunkHeader *pChunk = nullptr;
		intptr_t allocationSize = MemoryChunkHeader::CalculateAllocationSize(size, alignment);
		intptr_t remainSize = m_AllocationBufferSize - m_AllocatePosition;

		if (remainSize < allocationSize)
		{
			auto pMemBlk = GetParent()->AllocInternal(size, alignment);
			AddAllocSize(size);
			return pMemBlk;
		}

		// set up head
		pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);
		// if the block isn't free, means it's last block and there is not enough free space to set up new free header
		if(pChunk->Magic == MemBlockHdr::MEM_MAGIC)
		{
			auto pMemBlk = GetParent()->AllocInternal(size, alignment);
			AddAllocSize(size);
			return pMemBlk;
		}

		pChunk->InitHeader(this, (uint32_t)size);
		pChunk->pHeap = this; // null means free block
		pChunk->GetFooter()->InitFooter();

#ifdef DEBUG
		Assert((ValidateAllocatedChunks()));
#endif

		AddAllocSize(pChunk->Size);

		remainSize -= allocationSize;
		if (remainSize < sizeof(MemoryChunkHeader))
			return pChunk;

		// Remain chunk has enough size for another header + alpha
		m_AllocatePosition += allocationSize;
		auto pNewPos = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);
		memset(pNewPos, 0, sizeof(MemoryChunkHeader));
		pNewPos->Magic = MemBlockHdr::MEM_MAGIC_FREE;
		pNewPos->Prev = pChunk;

		return pChunk;
	}

	// Reallocate
	MemBlockHdr* StackHeap::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		assert(0);
		return nullptr;
	}

	// Free
	void StackHeap::FreeInternal(MemBlockHdr* pPtr)
	{
		if (pPtr == nullptr) // null free
			return ;

		auto freeSize = pPtr->Size;

		bool bIsInStaticBuffer = GetIsInStaticBuffer(pPtr);
		if (bIsInStaticBuffer)
		{
			MemoryChunkHeader *pChunk = static_cast<MemoryChunkHeader*>(pPtr);
			if (pChunk->Magic != MemBlockHdr::MEM_MAGIC)
			{
				assert(false); // broken?
				return;
			}
			pChunk->Magic = MemBlockHdr::MEM_MAGIC_FREE;
			pChunk->pHeap = nullptr;

			// merge from last, all free blocks
			MemoryChunkHeader *allocPointer = reinterpret_cast<MemoryChunkHeader*>(reinterpret_cast<uintptr_t>(m_AllocationBuffer) + m_AllocatePosition);
			while (allocPointer != nullptr && allocPointer->Magic != MemBlockHdr::MEM_MAGIC)
			{
				assert(allocPointer->pHeap == nullptr);
				m_AllocatePosition = (uintptr_t)allocPointer - (uintptr_t)m_AllocationBuffer;
				allocPointer = allocPointer->Prev;
			}
		}
		else
		{
			GetParent()->FreeInternal(pPtr);
		}

		Assert(m_AllocatePosition == 0 || m_AllocatedDRAM.load(std::memory_order_relaxed) >= freeSize);

		SubAllocSize(freeSize);
	}

	// Validate allocated chunks for debug
	Result StackHeap::ValidateAllocatedChunks()
	{
		MemoryChunkHeader* pChunk = nullptr;

		// TODO: fix it
		//if ((decltype(m_AllocationBufferSize))m_FreeSize < m_AllocationBufferSize)
		//{
		//	intptr_t curPosition = m_FreePosition;
		//	do {
		//		pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + curPosition);
		//		AssertRel(pChunk->ChunkType == ChunkTypes::Free || pChunk->ChunkType == ChunkTypes::Dummy || pChunk->ChunkType == ChunkTypes::Allocated);
		//		if (!(pChunk->ChunkType == ChunkTypes::Free || pChunk->ChunkType == ChunkTypes::Dummy || pChunk->ChunkType == ChunkTypes::Allocated))
		//			return ResultCode::UNEXPECTED;
		//		curPosition += pChunk->ChunkSize;
		//		AssertRel(curPosition <= (decltype(curPosition))m_AllocationBufferSize);
		//		if (curPosition == m_AllocationBufferSize)
		//			curPosition = 0;
		//		AssertRel(GetIsInStaticBuffer(m_AllocationBuffer + curPosition));
		//		if (!GetIsInStaticBuffer(m_AllocationBuffer + curPosition))
		//			return ResultCode::UNEXPECTED;
		//	} while (curPosition != m_AllocatePosition);
		//}

		return ResultCode::SUCCESS;
	}

} // namespace SF





