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


#ifdef X64
#define SF_ALIGN				16
#define SF_ALIGN_SHIFT			4
#define SF_ALIGN_DOUBLE			16
#define SF_ALIGN_DOUBLE_SHIFT	4
#else
#define SF_ALIGN				16
#define SF_ALIGN_SHIFT			4
#define SF_ALIGN_DOUBLE			16
#define SF_ALIGN_DOUBLE_SHIFT	4
#endif

#if __GNUC__
#define SF_DECLARE_ALIGN		__attribute__((aligned(SF_ALIGN)))
#define SF_DECLARE_ALIGN_DOUBLE __attribute__((aligned(SF_ALIGN_DOUBLE)))
#else
#define SF_DECLARE_ALIGN		__declspec(align(SF_ALIGN))
#define SF_DECLARE_ALIGN_DOUBLE __declspec(align(SF_ALIGN_DOUBLE))
#endif

//#define AlignUp(x,allign)	( (((uintptr_t)(x) + allign-1) & (~((uintptr_t)allign-1))) )


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


#pragma pack(push, 4)
	struct MemBlockFooter;

	struct MemBlockHdr
	{
		static constexpr uint32_t MEM_MAGIC = 0xAE92AE;// 0xAE9218AE;
		static constexpr uint32_t MEM_MAGIC_FREE = 0xCDCDCD;
		static constexpr uint32_t MaxHeaderAlignment = SF_ALIGN_DOUBLE;

		IHeap* pHeap = nullptr;
		uint32_t Size = 0;				// Allocated memory size. We don't support bigger than 4GB allocation
		uint32_t Magic : 24;
		uint32_t HeaderSize : 8;

		void InitHeader(IHeap* heap, uint32_t size, uint32_t headerSize);
		void Deinit();

		// +1 for reserved offset for reverse search
		static size_t GetHeaderSize();
		static size_t GetFooterSize();

		static size_t CalculateAllocationSize(size_t requestedSize, size_t alignment = SF_ALIGN_DOUBLE) { return GetHeaderSize() + AlignUp(requestedSize, alignment) + GetFooterSize(); }

		void* GetDataPtr() { return reinterpret_cast<uint8_t*>(this) + HeaderSize; }
		MemBlockFooter* GetFooter() { return (MemBlockFooter*)(reinterpret_cast<uint8_t*>(GetDataPtr()) + AlignUp(Size, MaxHeaderAlignment)); }
	};
#pragma pack(pop)

	struct MemBlockFooter
	{
		static constexpr uint32_t MEM_MAGIC = 0xB2AE3EB2;
		static constexpr uint32_t MEM_MAGIC_FREE = 0xCDEEEECD;

		uint32_t Magic = MEM_MAGIC_FREE;

#if ENABLE_MEMORY_TRACE
		DoubleLinkedListNode ListNode;
		CallStackTraceT<5> StackTrace; // Keep it tight, on linux bigger extra allocation was causing memory corruption.
		ThreadID LatestThreadID;
#endif

		void InitFooter();
		void Deinit();
	};

} // namespace SF


void* operator new(size_t size, SF::IHeap& heap);
void operator delete(void* pBuff, SF::IHeap& heap) noexcept;

void* operator new[] (size_t size, SF::IHeap& heap);
void operator delete[](void* pBuff, SF::IHeap& heap) noexcept;
