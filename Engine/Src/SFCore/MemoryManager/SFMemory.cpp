////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
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

#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFMemoryManager.h"



namespace SF {



	constexpr uint32_t MemBlockHdr::MEM_MAGIC;
	constexpr uint32_t MemBlockHdr::MEM_MAGIC_FREE;
	constexpr uint32_t MemBlockHdr::MaxHeaderAlignment;


	void MemBlockHdr::InitHeader(IHeap* heap, uint32_t size, uint32_t headerSize)
	{
		memset(this, 0, headerSize);
		Magic = MEM_MAGIC;
		Size = (uint32_t)size;
		pHeap = heap;

		// This works because we added +1 before
		// storing at both location. extension could have different size, and we need header size at last byte.
		HeaderSize = headerSize;
		auto pReverseOffset = ((uint8_t*)this + headerSize - 1);
		*pReverseOffset = static_cast<uint8_t>(headerSize);
	}

	void MemBlockHdr::Deinit()
	{
		GetFooter()->Deinit();
		Magic = MEM_MAGIC_FREE;
	}


	void MemBlockFooter::InitFooter()
	{
		Magic = MEM_MAGIC;
	#if ENABLE_MEMORY_TRACE
		memset(&ListNode, 0, sizeof(ListNode));
        ListNode.Data = this;
        StackTrace.CaptureCallStack(2);
		LatestThreadID = ThisThread::GetThreadID();
	#endif
	}

	void MemBlockFooter::Deinit()
	{
		Magic = MEM_MAGIC_FREE;
	}

}	// namespace SF





////////////////////////////////////////////////////////////////////////////////
//
//	Overriding of std memory operators
//

void* operator new(size_t size, SF::IHeap& heap)
{
	return heap.Alloc(size);
}

void operator delete(void* pBuff, SF::IHeap& heap) noexcept
{
	heap.Free(pBuff);
}

void* operator new[](size_t size, SF::IHeap& heap)
{
	return heap.Alloc(size);
}

void operator delete[](void* pBuff, SF::IHeap& heap) noexcept
{
	heap.Free(pBuff);
}

//#define SF_OVERRIDE_NEW

#ifdef SF_OVERRIDE_NEW
void* operator new(size_t size, size_t align)
{
	return SF::GetSystemHeap().Alloc(size, align);
}

void* operator new( size_t size )
{
	return SF::GetSystemHeap().Alloc(size);
}

void* operator new[](size_t size)
{
	return SF::GetSystemHeap().Alloc(size);
}

void operator delete(void* pBuff) noexcept
{
	SF::IHeap::Free(pBuff);
}

void operator delete[](void* pBuff) noexcept
{
	SF::IHeap::Free(pBuff);
}
#endif
