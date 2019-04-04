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



	constexpr uint16_t MemBlockHdr::MEM_MAGIC;
	constexpr uint16_t MemBlockHdr::MEM_MAGIC_FREE;


	void MemBlockHdr::Init(IHeap* heap, uint32_t size, uint32_t dataOffset)
	{
		memset(this, 0, sizeof(MemBlockHdr));
		Magic = MemBlockHdr::MEM_MAGIC;
		DataOffset = (decltype(DataOffset))dataOffset;
		Size = (uint32_t)size;
		pHeap = heap;

		// This works because we added +1 before
		auto pReverseOffset = ((uint8_t*)this + DataOffset - 1);
		*pReverseOffset = static_cast<uint8_t>(DataOffset);

#if ENABLE_MEMORY_TRACE
		StackTrace.CaptureCallStack(1);
		LatestThreadID = ThisThread::GetThreadID();
#endif
	}


	
	
};	// namespace SF





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

void* operator new(size_t size, size_t align)
{
	return SF::GetSystemHeap().Alloc(size, align);
}

void* operator new( size_t size )
{
	return SF::GetSystemHeap().Alloc(size);
}

void operator delete( void* pBuff ) noexcept
{
	return SF::GetSystemHeap().Free(pBuff);
}

void* operator new[]( size_t size )
{
	return SF::GetSystemHeap().Alloc(size);
}

void operator delete[]( void* pBuff ) noexcept
{
	return SF::GetSystemHeap().Free(pBuff);
}

