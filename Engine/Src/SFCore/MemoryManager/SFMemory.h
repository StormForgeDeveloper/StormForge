////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Container/SFDoubleLinkedListBase.h"

// Enable memory allocation trace
#define ENABLE_MEMORY_TRACE true



namespace SF {

	class IHeap;
	class MemoryPool;



	template<class ValueType>
	constexpr ValueType AlignUp(ValueType x, size_t align)
	{
		return (ValueType)((((uintptr_t)(x)+align - 1) & (~((uintptr_t)align - 1))));
	}



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


	struct MemBlockFooter
	{
		static constexpr uint32_t MEM_MAGIC = 0xB2AE3EB2;
		static constexpr uint32_t MEM_MAGIC_FREE = 0xCDEEEECD;

		uint32_t Magic = MEM_MAGIC_FREE;

#if ENABLE_MEMORY_TRACE
        DoubleLinkedListNodeDataT<MemBlockFooter*> ListNode;
		CallStackTraceT<10> StackTrace; // Keep it tight.
		ThreadID LatestThreadID;
#endif
		void InitFooter();
		void Deinit();
	};

#pragma pack(push, 4)
	struct MemBlockFooter;

	struct SF_DECLARE_ALIGN_DOUBLE MemBlockHdr
	{
		static constexpr uint32_t MEM_MAGIC = 0xAE92AE;// 0xAE9218AE;
		static constexpr uint32_t MEM_MAGIC_FREE = 0xCDCDCD;
		static constexpr uint32_t MaxHeaderAlignment = SF_ALIGN_DOUBLE;

		IHeap* pHeap = nullptr;
		uint32_t Size = 0;				// Allocated memory size. We don't support bigger than 4GB allocation
		uint32_t Magic : 24;
		uint32_t HeaderSize : 8;

		SF_FORCEINLINE bool IsFree() const { return Magic == MEM_MAGIC_FREE; }
		SF_FORCEINLINE bool IsValid() const { return Magic == MEM_MAGIC || Magic == MEM_MAGIC_FREE; }

		void InitHeader(IHeap* heap, uint32_t size, uint32_t headerSize);
		void Deinit();

		// +1 for reserved offset for reverse search
		static constexpr size_t GetDefaultHeaderSize()
		{
			return AlignUp(sizeof(MemBlockHdr), MaxHeaderAlignment);
		}

		static constexpr size_t GetFooterSize()
		{
			return AlignUp(sizeof(MemBlockFooter), MaxHeaderAlignment);
		}

		static size_t CalculateAllocationSize(size_t requestedSize, size_t alignment = SF_ALIGN_DOUBLE) { return GetDefaultHeaderSize() + AlignUp(requestedSize, alignment) + GetFooterSize(); }

		SF_FORCEINLINE void* GetDataPtr() { return (void*)(AlignUp(uintptr_t(this) + GetDefaultHeaderSize(), MaxHeaderAlignment)); }
		SF_FORCEINLINE MemBlockFooter* GetFooter() { return (MemBlockFooter*)(reinterpret_cast<uint8_t*>(GetDataPtr()) + AlignUp(Size, MaxHeaderAlignment)); }
	};
#pragma pack(pop)

} // namespace SF

#ifndef SF_USE_IHEAP_NEW
#define SF_USE_IHEAP_NEW 0
#endif

#if SF_USE_IHEAP_NEW

void* operator new(size_t size, SF::IHeap& heap);
void operator delete(void* pBuff, SF::IHeap& heap) noexcept;

void* operator new[] (size_t size, SF::IHeap& heap);
void operator delete[](void* pBuff, SF::IHeap& heap) noexcept;

#endif // SF_USE_IHEAP_NEW
