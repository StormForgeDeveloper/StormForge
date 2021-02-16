////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular heap
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "MemoryManager/SFCircularHeap.h"




namespace SF {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	static allocator interface
	//   // allocate from the buffer first
	//

	CircularHeap::CircularHeap(IHeap& overflowHeap, size_t allocationBufferSize, uint8_t* allocationBuffer)
		: IHeap("CircularHeap", &overflowHeap)
		, m_FreeSize(allocationBufferSize)
		, m_AllocatePosition(0)
		, m_FreePosition(0)
		, m_AllocationBufferSize(allocationBufferSize)
		, m_AllocationBuffer(allocationBuffer)
		, m_RedundencySize(MemoryChunkHeader::GetHeaderSize() + MemoryChunkHeader::GetFooterSize())
	{
		// Because of the chunk header uses 32bit integer, the limit will be maximum of int32. Actually it's uint32_t, but it's not a big deal
		assert(m_AllocationBufferSize < INT_MAX);// , "CircularHeap: too big buffer size");
	}

	CircularHeap::~CircularHeap()
	{
	}


	// Allocate 
	MemBlockHdr* CircularHeap::AllocInternal(size_t size, size_t align)
	{
		// support zero size allocation
		if (size == 0)
			size = SF_ALIGN;

		MemoryChunkHeader *pChunk = nullptr;
		intptr_t allocationSize = MemoryChunkHeader::CalculateAllocationSize(size);

		if (m_FreeSize < allocationSize)
		{
			auto pMemBlk = GetParent()->AllocInternal(size, align);
			AddAllocSize(pMemBlk->Size);
			return pMemBlk;
		}

		if ((m_AllocatePosition + allocationSize) < (decltype(m_AllocatePosition))m_AllocationBufferSize)
		{
			pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);

			// If the remain size on the edge isn't enough for next allocation, increase allocation size so that it include dummy area
			if ((m_AllocatePosition + allocationSize + m_RedundencySize) >= m_AllocationBufferSize)
			{
				allocationSize += m_AllocationBufferSize - (m_AllocatePosition + allocationSize);
			}
		}
		else // remain size is too small. add dummy area and try to allocate from beginning of the buffer
		{
			intptr_t remainSize = m_AllocationBufferSize - m_AllocatePosition;

			if (m_FreeSize < (allocationSize + remainSize))
			{
				auto pMemBlk = GetParent()->AllocInternal(size, align);
				AddAllocSize(pMemBlk->Size);
				return pMemBlk;
			}

			// Add dummy area
			pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);
			pChunk->InitHeader(this, (uint32_t)(remainSize - m_RedundencySize), MemoryChunkHeader::GetHeaderSize());
			pChunk->pHeap = nullptr; // let's put null here so that we can use it as free block mark
			m_FreeSize -= remainSize;

			// move to beginning of the circular buffer
			pChunk = (MemoryChunkHeader*)(m_AllocationBuffer);
			m_AllocatePosition = 0;
			AssertRel(this->m_AllocatePosition < this->m_FreePosition);

			// If we don't have enough space after dummy, just allocate from parent heap
			if (m_FreeSize < allocationSize)
			{
				auto pMemBlk = GetParent()->AllocInternal(size, align);
				AddAllocSize(pMemBlk->Size);
				return pMemBlk;
			}
#ifdef DEBUG
			Assert((ValidateAllocatedChunks()));
#endif
		}

		m_FreeSize -= allocationSize;

		AssertRel(this->m_FreeSize <= (decltype(m_FreeSize))m_AllocationBufferSize && this->m_FreeSize >= 0);

		pChunk->InitHeader(this, (uint32_t)(allocationSize - m_RedundencySize), MemoryChunkHeader::GetHeaderSize());
		pChunk->GetFooter()->InitFooter();
		m_AllocatePosition += allocationSize;

		AddAllocSize(pChunk->Size);

		// we reached at the end of buffer, rounding up for next allocation
		if (m_AllocatePosition == m_AllocationBufferSize)
		{
			m_AllocatePosition = 0;
		}

#ifdef DEBUG
		Assert((ValidateAllocatedChunks()));
#endif
		return pChunk;
	}

	// Reallocate
	MemBlockHdr* CircularHeap::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t align)
	{
		return nullptr;
	}

	// Free
	void CircularHeap::FreeInternal(MemBlockHdr* pPtr)
	{
		if (pPtr == nullptr) // null free
			return ;

		auto freeSize = pPtr->Size;

		bool bIsInStaticBuffer = GetIsInStaticBuffer(pPtr);
		if (bIsInStaticBuffer)
		{
			MemoryChunkHeader *pChunk = pPtr;
			assert(m_FreePosition != m_AllocatePosition || m_FreeSize == 0);

			// I can't recall reason for this, moreover, calling free with raw pointer is wrong
			//intptr_t freePointer = (intptr_t)m_AllocationBuffer + m_FreePosition;
			//if (freePointer > (intptr_t)pChunk)
			//{
			//	Free((void*)(freePointer + MemoryChunkHeader::GetHeaderSize()));
			//}

			assert(m_FreePosition != m_AllocatePosition || m_FreeSize == 0);
			pChunk->pHeap = nullptr; // we uses pHeap as free block flag
			if (m_FreePosition != ((intptr_t)pChunk - (intptr_t)m_AllocationBuffer))
			{
				// If this memory isn't exist in the free position, we should leave it for later
				SubAllocSize(freeSize);
				return;
			}

			while ((pChunk->pHeap == nullptr) && m_FreeSize <= (decltype(m_FreeSize))m_AllocationBufferSize)
			{
				AssertRel((m_FreePosition == ((intptr_t)pChunk - (intptr_t)m_AllocationBuffer)) || m_FreeSize == 0);
				m_FreeSize += pChunk->Size + m_RedundencySize;
				m_FreePosition += pChunk->Size + m_RedundencySize;
				AssertRel(m_FreePosition <= (decltype(m_FreePosition))m_AllocationBufferSize);
				if ((decltype(m_AllocationBufferSize))m_FreePosition == m_AllocationBufferSize) m_FreePosition = 0;

				if ((decltype(m_AllocationBufferSize))m_FreeSize < m_AllocationBufferSize) // Any chunk must be exist
				{
					pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_FreePosition);
#ifdef DEBUG
					Assert((ValidateAllocatedChunks()));
#endif
					Assert(m_FreePosition != m_AllocatePosition);
				}
				else
				{
					break;
				}
			}

			AssertRel(m_FreeSize <= (decltype(m_FreeSize))m_AllocationBufferSize);
		}
		else
		{
			GetParent()->FreeInternal(pPtr);
		}

		SubAllocSize(freeSize);
	}

	// Validate allocated chunks for debug
	Result CircularHeap::ValidateAllocatedChunks()
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





