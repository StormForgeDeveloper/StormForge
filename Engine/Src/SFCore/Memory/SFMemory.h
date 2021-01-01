////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory allocation library
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Memory/SFIMemoryManager.h"
#include "Container/SFDoubleLinkedListBase.h"


// Enable memory allocation trace
#define ENABLE_MEMORY_TRACE true



namespace SF {

	class IHeap;
	class IHeap;
	class MemoryPool;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory block descriptor
	//

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	// Check CRT heap memory status
	inline void CheckCtrMemory()
	{
		//Assert( _CrtCheckMemory( ) );
	}

#else
	inline void CheckCtrMemory()
	{
		//Assert(_CrtCheckMemory());
	}
#endif




#pragma pack(push, 1)
	struct MemBlockHdr
	{
		static constexpr uint32_t MEM_MAGIC = 0x3E9218AE;
		static constexpr uint32_t MEM_MAGIC_FREE = 0xCDCDCDCD;
		static constexpr uint32_t MaxHeaderAlignment = SF_ALIGN_DOUBLE;

		uint32_t Magic			= MEM_MAGIC_FREE;
		uint32_t Size			= 0;				// Allocated memory size. We don't support bigger than 4GB allocation
		IHeap* pHeap			= nullptr;


#if ENABLE_MEMORY_TRACE
		DoubleLinkedListNode ListNode;
		CallStackTraceT<5> StackTrace;
		ThreadID LatestThreadID;
#endif

		void Init(IHeap* heap, uint32_t size, uint32_t dataOffset);

		// +1 for reserved offset for reverse search
		static size_t GetHeaderSize() { return AlignUp(sizeof(MemBlockHdr) + 1, MaxHeaderAlignment); }

		void* GetDataPtr() { return reinterpret_cast<uint8_t*>(this) + GetHeaderSize(); }
	};
#pragma pack(pop)

	
} // namespace SF


void* operator new(size_t size, SF::IHeap& heap);
void operator delete(void* pBuff, SF::IHeap& heap) noexcept;

void* operator new[] (size_t size, SF::IHeap& heap);
void operator delete[](void* pBuff, SF::IHeap& heap) noexcept;



