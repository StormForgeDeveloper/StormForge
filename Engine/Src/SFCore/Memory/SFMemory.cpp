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

#include "Thread/SFThread.h"
#include "Memory/SFMemory.h"
#include "Memory/SFMemoryManager.h"



namespace SF {



	constexpr uint32_t MemBlockHdr::MEM_MAGIC;
	constexpr uint32_t MemBlockHdr::MEM_MAGIC_FREE;
	constexpr uint32_t MemBlockHdr::MaxHeaderAlignment;

	size_t MemBlockHdr::GetHeaderSize()
	{
		return AlignUp(sizeof(MemBlockHdr) + 1, MaxHeaderAlignment);
	}

	size_t MemBlockHdr::GetFooterSize()
	{
		return AlignUp(sizeof(MemBlockFooter), MaxHeaderAlignment);
	}


	void MemBlockHdr::Init(IHeap* heap, uint32_t size)
	{
		memset(this, 0, sizeof(MemBlockHdr));
		Magic = MEM_MAGIC;
		Size = (uint32_t)size;
		pHeap = heap;

		// This works because we added +1 before
		uint32_t dataOffset = GetHeaderSize();
		auto pReverseOffset = ((uint8_t*)this + dataOffset - 1);
		*pReverseOffset = static_cast<uint8_t>(dataOffset);
	}

	void MemBlockHdr::Deinit()
	{
		GetFooter()->Deinit();
		Magic = MEM_MAGIC_FREE;
	}


	void MemBlockFooter::Init()
	{
		Magic = MEM_MAGIC;
	#if ENABLE_MEMORY_TRACE
		memset(&ListNode, 0, sizeof(ListNode));
		StackTrace.CaptureCallStack(1);
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
#endif

void operator delete(void* pBuff) noexcept
{
	SF::IHeap::Free(pBuff);
}

void operator delete[](void* pBuff) noexcept
{
	SF::IHeap::Free(pBuff);
}
