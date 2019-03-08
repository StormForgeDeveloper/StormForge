////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Stack heap
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	static allocator interface
	//   // allocate from the buffer first
	//

	template< size_t BufferSize, size_t DefaultAlignment >
	StackHeap<BufferSize, DefaultAlignment>::StackHeap(FixedString name, IHeap& overflowHeap)
		: IHeap(name, &overflowHeap)
	{
		// Because of the chunk header uses 32bit integer, the limit will be maximum of int32. Actually it's uint32_t, but it's not a big deal
		static_assert(BufferSize < INT_MAX, "StackHeap: too big buffer size");

		MemoryChunkHeader* pChunk = reinterpret_cast<MemoryChunkHeader*>(m_AllocationBuffer);
		memset(pChunk, 0, sizeof(MemoryChunkHeader));
	}

	template< size_t BufferSize, size_t DefaultAlignment >
	StackHeap<BufferSize, DefaultAlignment>::~StackHeap()
	{
	}

	template< size_t BufferSize, size_t DefaultAlignment >
	inline bool StackHeap<BufferSize, DefaultAlignment>::GetIsInStaticBuffer(void* pPtr)
	{
		intptr_t ptr = (intptr_t)pPtr;
		intptr_t staticBuffer = (intptr_t)m_AllocationBuffer;
		return (ptr >= staticBuffer) && (ptr <= (staticBuffer + (intptr_t)BufferSize));
	}

	// Get free memory size in static buffer
	template< size_t BufferSize, size_t DefaultAlignment >
	inline size_t StackHeap<BufferSize, DefaultAlignment>::GetFreeMemorySize()
	{
		return BufferSize - m_AllocatePosition;
	}


	// Allocate 
	template< size_t BufferSize, size_t DefaultAlignment >
	MemBlockHdr* StackHeap<BufferSize, DefaultAlignment>::AllocInternal(size_t size, size_t alignment)
	{
		alignment = std::max(alignment, DefaultAlignment);
		MemoryChunkHeader *pChunk = nullptr;
		intptr_t allocationSize = (intptr_t)AlignUp(size, alignment);
		intptr_t remainSize = BufferSize - m_AllocatePosition;

		if (allocationSize == 0)
		{
			allocationSize = alignment;
		}

		if (remainSize < ((intptr_t)HEADER_SIZE + allocationSize))
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

		pChunk->Init(this, (uint32_t)allocationSize, HEADER_SIZE);
		pChunk->pHeap = this; // null means free block

#ifdef DEBUG
		Assert((ValidateAllocatedChunks()));
#endif

		AddAllocSize(pChunk->Size);

		remainSize -= allocationSize + HEADER_SIZE;
		if (remainSize < sizeof(MemoryChunkHeader))
			return pChunk;

		// Remain chunk has enough size for another header + alpha
		m_AllocatePosition += allocationSize + HEADER_SIZE;
		auto pNewPos = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);
		memset(pNewPos, 0, sizeof(MemoryChunkHeader));
		pNewPos->Magic = MemBlockHdr::MEM_MAGIC_FREE;
		pNewPos->Prev = pChunk;

		return pChunk;
	}

	// Reallocate
	template< size_t BufferSize, size_t DefaultAlignment >
	MemBlockHdr* StackHeap<BufferSize, DefaultAlignment>::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		assert(0);
		return nullptr;
	}

	// Free
	template< size_t BufferSize, size_t DefaultAlignment >
	void StackHeap<BufferSize, DefaultAlignment>::FreeInternal(MemBlockHdr* pPtr)
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

			MemoryChunkHeader *allocPointer = (MemoryChunkHeader *)((uintptr_t)m_AllocationBuffer + m_AllocatePosition);
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

		Assert(m_AllocatePosition == 0 || m_AllocatedDRAM.load(std::memory_order_relaxed) > freeSize);

		SubAllocSize(freeSize);
	}

	// Validate allocated chunks for debug
	template< size_t BufferSize, size_t DefaultAlignment >
	Result StackHeap<BufferSize, DefaultAlignment>::ValidateAllocatedChunks()
	{
		MemoryChunkHeader* pChunk = nullptr;

		// TODO: fix it
		//if ((decltype(BufferSize))m_FreeSize < BufferSize)
		//{
		//	intptr_t curPosition = m_FreePosition;
		//	do {
		//		pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + curPosition);
		//		AssertRel(pChunk->ChunkType == ChunkTypes::Free || pChunk->ChunkType == ChunkTypes::Dummy || pChunk->ChunkType == ChunkTypes::Allocated);
		//		if (!(pChunk->ChunkType == ChunkTypes::Free || pChunk->ChunkType == ChunkTypes::Dummy || pChunk->ChunkType == ChunkTypes::Allocated))
		//			return ResultCode::UNEXPECTED;
		//		curPosition += pChunk->ChunkSize;
		//		AssertRel(curPosition <= (decltype(curPosition))BufferSize);
		//		if (curPosition == BufferSize)
		//			curPosition = 0;
		//		AssertRel(GetIsInStaticBuffer(m_AllocationBuffer + curPosition));
		//		if (!GetIsInStaticBuffer(m_AllocationBuffer + curPosition))
		//			return ResultCode::UNEXPECTED;
		//	} while (curPosition != m_AllocatePosition);
		//}

		return ResultCode::SUCCESS;
	}




} // namespace SF





