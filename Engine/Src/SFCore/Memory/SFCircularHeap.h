////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular heap
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "Thread/SFSynchronization.h"
#include "Container/SFStackPool.h"
#include "Memory/SFIMemoryManager.h"






namespace SF {
	




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Circular buffer memory allocator
	//

	class CircularHeap : public IHeap
	{
	public:

		enum class ChunkTypes : uint32_t
		{
			Free = 0xc7c7c7c7,
			Dummy,
			Allocated,
		};

#pragma pack(push, 4)
		using MemoryChunkHeader = MemBlockHdr;
#pragma pack(pop)

		// header size
		//static const size_t HEADER_SIZE = AlignUp(sizeof(MemoryChunkHeader), SF_ALIGN_DOUBLE);


		intptr_t			m_FreeSize;

		intptr_t			m_AllocatePosition;
		intptr_t			m_FreePosition;

		// Static buffer
		size_t m_AllocationBufferSize = 0;

		uint8_t				*m_AllocationBuffer = nullptr;

		intptr_t m_RedundencySize = 0;

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t align) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t align) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

	public:

		CircularHeap(IHeap& overflowHeap, size_t allocationBufferSize, uint8_t* allocationBuffer);
		~CircularHeap();


		bool GetIsInStaticBuffer(void* pPtr)
		{
			intptr_t ptr = (intptr_t)pPtr;
			intptr_t staticBuffer = (intptr_t)m_AllocationBuffer;
			return (ptr >= staticBuffer) && (ptr <= (staticBuffer + (intptr_t)m_AllocationBufferSize));
		}

		// Get free memory size in static buffer
		size_t GetFreeMemorySize()
		{
			return m_FreeSize;
		}

		// Validate allocated chunks for debug
		Result ValidateAllocatedChunks();

	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Circular buffer memory allocator
	//

	template< size_t BufferSize >
	class CircularHeapT : public CircularHeap
	{
	public:

		// Static buffer
		uint8_t				m_Buffer[BufferSize];

	public:

		CircularHeapT(IHeap& overflowHeap)
			: CircularHeap(overflowHeap, BufferSize, m_Buffer)
		{
		}

	};


} // namespace SF


