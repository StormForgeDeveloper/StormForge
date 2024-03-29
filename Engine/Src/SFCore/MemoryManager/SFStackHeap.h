////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Stack heap
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "Multithread/SFSynchronization.h"
#include "Container/SFStackPool.h"
#include "MemoryManager/SFIMemoryManager.h"






namespace SF
{
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Stack memory allocator
	//


	class StackHeap : public IHeap
	{
	public:

		// memory header

		struct MemoryChunkHeader
		{
			MemoryChunkHeader* Prev = nullptr;

			MemBlockHdr MemHeader;

			static size_t GetHeaderSize() { return AlignUp(sizeof(MemoryChunkHeader), MemBlockHdr::MaxHeaderAlignment); }
			static size_t CalculateAllocationSize(size_t requestedSize, size_t alignment = SF_ALIGN_DOUBLE) { return MemoryChunkHeader::GetHeaderSize() + AlignUp(requestedSize, MemBlockHdr::MaxHeaderAlignment) + MemBlockHdr::GetFooterSize(); }
		};


		// stack position
		intptr_t			m_AllocatePosition = 0;

		size_t m_AllocationBufferSize = 0;

		// buffer
		uint8_t				*m_AllocationBuffer = nullptr;

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

	public:

		StackHeap(StringCrc64 name, IHeap& overflowHeap, size_t bufferSize, uint8_t* allocationBuffer);
		~StackHeap();

		bool GetIsInStaticBuffer(void* pPtr)
		{
			intptr_t ptr = (intptr_t)pPtr;
			intptr_t staticBuffer = (intptr_t)m_AllocationBuffer;
			return (ptr >= staticBuffer) && (ptr <= (staticBuffer + (intptr_t)m_AllocationBufferSize));
		}

		// Get free memory size in static buffer
		size_t GetFreeMemorySize()
		{
			return m_AllocationBufferSize - m_AllocatePosition;
		}

		// Validate allocated chunks for debug
		Result ValidateAllocatedChunks();

	};


	template< size_t BufferSize >
	class StackHeapT : public StackHeap
	{
	public:

		// Static buffer
		uint8_t				m_Buffer[BufferSize];

	public:

		StackHeapT(StringCrc64 name, IHeap& overflowHeap)
			: StackHeap(name, overflowHeap, BufferSize, m_Buffer)
		{
		}
	};

} // namespace SF



