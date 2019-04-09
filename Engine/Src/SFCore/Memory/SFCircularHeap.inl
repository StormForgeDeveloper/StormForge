////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular heap
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	static allocator interface
	//   // allocate from the buffer first
	//

	template< size_t BufferSize, size_t alignment >
	CircularHeap<BufferSize, alignment>::CircularHeap(IHeap& overflowHeap)
		: IHeap("CircularHeap", &overflowHeap)
		, m_FreeSize(BufferSize)
		, m_AllocatePosition(0)
		, m_FreePosition(0)
	{
		// Because of the chunk header uses 32bit integer, the limit will be maximum of int32. Actually it's uint32_t, but it's not a big deal
		static_assert(BufferSize < INT_MAX, "CircularHeap: too big buffer size");
	}

	template< size_t BufferSize, size_t alignment >
	CircularHeap<BufferSize, alignment>::~CircularHeap()
	{
	}

	template< size_t BufferSize, size_t alignment >
	inline bool CircularHeap<BufferSize, alignment>::GetIsInStaticBuffer(void* pPtr)
	{
		intptr_t ptr = (intptr_t)pPtr;
		intptr_t staticBuffer = (intptr_t)m_AllocationBuffer;
		return (ptr >= staticBuffer) && (ptr <= (staticBuffer + (intptr_t)BufferSize));
	}

	// Get free memory size in static buffer
	template< size_t BufferSize, size_t alignment >
	inline size_t CircularHeap<BufferSize, alignment>::GetFreeMemorySize()
	{
		return m_FreeSize;
	}


	// Allocate 
	template< size_t BufferSize, size_t alignment >
	MemBlockHdr* CircularHeap<BufferSize, alignment>::AllocInternal(size_t size, size_t align)
	{
		align = Util::Max(alignment, align);
		MemoryChunkHeader *pChunk = nullptr;
		intptr_t allocationSize = (intptr_t)AlignUp(HEADER_SIZE + size, align);

		if (m_FreeSize < allocationSize)
			return GetParent()->AllocInternal(size, align);

		if ((m_AllocatePosition + allocationSize) < (decltype(m_AllocatePosition))BufferSize)
		{
			pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);

			// If the remain size on the edge isn't enough for next allocation, increase allocation size so that it include dummy area
			if ((m_AllocatePosition + HEADER_SIZE) >= BufferSize)
			{
				allocationSize += BufferSize - (m_AllocatePosition + allocationSize);
			}
		}
		else
		{
			intptr_t remainSize = BufferSize - m_AllocatePosition;

			if (m_FreeSize < (allocationSize + remainSize))
				return GetParent()->AllocInternal(size, align);

			// Add dummy area
			pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_AllocatePosition);
			pChunk->Init(this, (uint32_t)remainSize, HEADER_SIZE);
			pChunk->pHeap = nullptr; // let's put null here so that we can use it as free block mark
			m_FreeSize -= remainSize + HEADER_SIZE;

			// move to beginning of the circular buffer
			pChunk = (MemoryChunkHeader*)(m_AllocationBuffer);
			m_AllocatePosition = 0;
			AssertRel(this->m_AllocatePosition < this->m_FreePosition);

#ifdef DEBUG
			Assert((ValidateAllocatedChunks()));
#endif
		}

		m_FreeSize -= allocationSize;

		AssertRel(this->m_FreeSize <= (decltype(m_FreeSize))BufferSize && this->m_FreeSize >= 0);

		pChunk->Init(this, (uint32_t)allocationSize - HEADER_SIZE, HEADER_SIZE);
		m_AllocatePosition += allocationSize;

#ifdef DEBUG
		Assert((ValidateAllocatedChunks()));
#endif
		return pChunk;
	}

	// Reallocate
	template< size_t BufferSize, size_t alignment >
	MemBlockHdr* CircularHeap<BufferSize, alignment>::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t align)
	{
		return nullptr;
	}

	// Free
	template< size_t BufferSize, size_t alignment >
	void CircularHeap<BufferSize, alignment>::FreeInternal(MemBlockHdr* pPtr)
	{
		if (pPtr == nullptr) // null free
			return ;

		bool bIsInStaticBuffer = GetIsInStaticBuffer(pPtr);
		if (bIsInStaticBuffer)
		{
			MemoryChunkHeader *pChunk = pPtr;
			assert(m_FreePosition != m_AllocatePosition || m_FreeSize == 0);

			intptr_t freePointer = (intptr_t)m_AllocationBuffer + m_FreePosition;
			if (freePointer > (intptr_t)pChunk)
			{
				Free((void*)(freePointer + HEADER_SIZE));
			}

			//assert(pChunk->ChunkType != ChunkTypes::Free);
			//AssertRel(pChunk->ChunkType == ChunkTypes::Dummy || pChunk->ChunkType == ChunkTypes::Allocated);
			assert(m_FreePosition != m_AllocatePosition || m_FreeSize == 0);
			//if (pChunk->ChunkType != ChunkTypes::Dummy && pChunk->ChunkType != ChunkTypes::Allocated)
			//{
			//	// Duplicate free? or broken memory
			//	assert(false);
			//	return;
			//}
			//pChunk->ChunkType = ChunkTypes::Free;
			pChunk->pHeap = nullptr;
			if (m_FreePosition != ((intptr_t)pChunk - (intptr_t)m_AllocationBuffer))
			{
				// If this memory isn't exist in the free position, we should leave it for later
				return;
			}

			//while ((pChunk->ChunkType == ChunkTypes::Free || pChunk->ChunkType == ChunkTypes::Dummy) && m_FreeSize <= (decltype(m_FreeSize))BufferSize)
			while ((pChunk->pHeap == nullptr) && m_FreeSize <= (decltype(m_FreeSize))BufferSize)
			{
				AssertRel((m_FreePosition == ((intptr_t)pChunk - (intptr_t)m_AllocationBuffer)) || m_FreeSize == 0);
				m_FreeSize += pChunk->Size;
				m_FreePosition += pChunk->Size;
				AssertRel(m_FreePosition <= (decltype(m_FreePosition))BufferSize);
				if ((decltype(BufferSize))m_FreePosition == BufferSize) m_FreePosition = 0;

				if ((decltype(BufferSize))m_FreeSize < BufferSize) // Any chunk must be exist
				{
					pChunk = (MemoryChunkHeader*)(m_AllocationBuffer + m_FreePosition);
					//if (pChunk->ChunkType != ChunkTypes::Free && pChunk->ChunkType != ChunkTypes::Dummy && pChunk->ChunkType != ChunkTypes::Allocated)
					//{
					//	// Broken memory
					//	assert(false);
					//	return ;
					//}

					// Validate allocated chunks
#ifdef DEBUG
					Assert((ValidateAllocatedChunks()));
#endif
					Assert(m_FreePosition != m_AllocatePosition);
					//AssertRel(pChunk->ChunkType == ChunkTypes::Free || pChunk->ChunkType == ChunkTypes::Dummy || pChunk->ChunkType == ChunkTypes::Allocated);
				}
				else
				{
					break;
				}
			}

			AssertRel(m_FreeSize <= (decltype(m_FreeSize))BufferSize);
		}
		else
		{
			IHeap::Free(pPtr);
		}
	}

	// Validate allocated chunks for debug
	template< size_t BufferSize, size_t alignment >
	Result CircularHeap<BufferSize, alignment>::ValidateAllocatedChunks()
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





