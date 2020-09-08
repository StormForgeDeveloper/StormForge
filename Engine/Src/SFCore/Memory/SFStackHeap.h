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
#include "Thread/SFSynchronization.h"
#include "Container/SFStackPool.h"
#include "Memory/SFIMemoryManager.h"






namespace SF
{
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Stack memory allocator
	//

	template< size_t BufferSize, size_t DefaultAlignment = SF_ALIGN_DOUBLE >
	class StackHeap : public IHeap
	{
	public:

		// memory header
#pragma pack(push,1)
		struct MemoryChunkHeader : public MemBlockHdr
		{
			MemoryChunkHeader* Prev = nullptr;
		};
#pragma pack(pop)

		// header size
		static const size_t HEADER_SIZE = AlignUp(sizeof(MemoryChunkHeader), DefaultAlignment);


		// stack position
		intptr_t			m_AllocatePosition = 0;

		// Static buffer
		uint8_t				m_AllocationBuffer[BufferSize];

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

	public:

		StackHeap(StringCrc64 name, IHeap& overflowHeap);
		~StackHeap();

		bool GetIsInStaticBuffer(void* pPtr);

		// Get free memory size in static buffer
		size_t GetFreeMemorySize();

		// Validate allocated chunks for debug
		Result ValidateAllocatedChunks();

	};



} // namespace SF


#include "SFStackHeap.inl"




