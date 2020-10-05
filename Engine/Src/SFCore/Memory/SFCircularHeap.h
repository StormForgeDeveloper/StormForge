////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
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

	template< size_t BufferSize, size_t alignment >
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
		typedef MemBlockHdr MemoryChunkHeader;
		//struct MemoryChunkHeader : public MemBlockHdr
		//{
		//	ChunkTypes	ChunkType;
		//};
#pragma pack(pop)

		// header size
		static const size_t HEADER_SIZE = AlignUp(sizeof(MemoryChunkHeader), alignment);


		intptr_t			m_FreeSize;

		intptr_t			m_AllocatePosition;
		intptr_t			m_FreePosition;

		// Static buffer
		uint8_t				m_AllocationBuffer[BufferSize];

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t align) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t align) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;

	public:

		CircularHeap(IHeap& overflowHeap);
		~CircularHeap();

		bool GetIsInStaticBuffer(void* pPtr);

		// Get free memory size in static buffer
		size_t GetFreeMemorySize();

		// Validate allocated chunks for debug
		Result ValidateAllocatedChunks();

	};



} // namespace SF


#include "SFCircularHeap.inl"




