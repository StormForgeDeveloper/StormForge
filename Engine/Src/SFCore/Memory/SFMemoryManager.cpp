////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory manager
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Thread/SFSynchronization.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemoryPool.h"
#include "String/SFString.h"
#include "String/SFStringCrc64.h"
#include "Util/SFUtility.h"


namespace SF {



	///////////////////////////////////////////////////////////////
	//
	//	Memory manager interfaces
	//

	// System memory manager
	IHeap& GetSystemHeap()
	{
		return *GetSystemHeapPtr().get();
	}

	const IHeapPtr& GetSystemHeapPtr()
	{
		return STDMemoryManager::GetInstance();
	}



	// Engine memory manager
	IHeap& GetEngineHeap()
	{
		return *GetEngineHeapPtr().get();
	}

	const IHeapPtr& GetEngineHeapPtr()
	{
		return EngineMemoryManager::GetInstance();
	}



	///////////////////////////////////////////////////////////
	// 
	//	Heap
	//    - Hierarchical memory heap
	//

	//Heap::Heap(const char* name, IHeap& parent)
	//	: m_pHeap(new(GetSystemHeap()) IHeap(name, &parent))
	//{
	//}

	//Heap::~Heap()
	//{
	//	// All memory related to the heap should be reported
	//	if (m_pHeap != nullptr)
	//		m_pHeap->ReportLeak();
	//}

	//// Allocation/Reallocation interface
	//void* Heap::Alloc(size_t size, size_t alignment)
	//{
	//	if (m_pHeap == nullptr)
	//		return nullptr;

	//	return m_pHeap->Alloc(size, alignment);
	//}

	//void* Heap::Realloc(void* ptr, size_t newSize, size_t alignment)
	//{
	//	if (m_pHeap == nullptr)
	//		return nullptr;

	//	return m_pHeap->Realloc(ptr, newSize, alignment);
	//}





	///////////////////////////////////////////////////////////
	// 
	//	STDMemoryManager
	//

	SharedPointerT<IHeap> STDMemoryManager::stm_Instance;

	const SharedPointerT<IHeap>& STDMemoryManager::GetInstance()
	{
		static CriticalSection g_StdHeapLock;
		// This condition will be true most of time, and early return will be faster if the compiler is not intelligent enough.
		if (stm_Instance != nullptr) 
			return stm_Instance;

		MutexScopeLock lock(g_StdHeapLock);
		if (stm_Instance == nullptr) // Need to check again after lock
		{
			// Using malloc to avoid recursive memory allocation
			void* pBuffer = STDMemoryManager::SystemAllignedAlloc(sizeof(STDMemoryManager), sizeof(int));
			stm_Instance = new(pBuffer) STDMemoryManager;
		}

		return stm_Instance;
	}


	STDMemoryManager::STDMemoryManager()
		: IHeap("STD")
	{
	}

	STDMemoryManager::~STDMemoryManager()
	{
	}

	void* STDMemoryManager::SystemAllignedAlloc(size_t size, size_t alignment)
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		return _aligned_malloc(size, alignment);
#elif SF_PLATFORM == SF_PLATFORM_ANDROID
		return memalign(alignment, size);
#elif SF_PLATFORM == SF_PLATFORM_IOS
		void* pPtr = nullptr;
		if (posix_memalign(&pPtr, alignment, size) != 0)
			return nullptr;
		return pPtr;
#else
		return aligned_alloc(alignment, size);
#endif
	}

	void STDMemoryManager::SystemAlignedFree(void* pPtr)
	{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		return _aligned_free(pPtr);
#else
		return free(pPtr);
#endif
	}

	MemBlockHdr* STDMemoryManager::AllocInternal(size_t size, size_t alignment)
	{
		if (alignment == 0)
			alignment = sizeof(int);

		// Adjust allocation size for header
		// +1 for reverse offset
		size_t spaceForHeader = MemBlockHdr::GetHeaderSize();
		auto allocSize = size + spaceForHeader;

		m_AllocatedDRAM.fetch_add(size, std::memory_order_relaxed);

		MemBlockHdr* pMemBlock;
		pMemBlock = (MemBlockHdr*)SystemAllignedAlloc(allocSize, alignment);

		AddAllocSize(size);

		pMemBlock->Init(this, (uint32_t)size, (uint32_t)spaceForHeader);

		return pMemBlock;
	}

	void STDMemoryManager::FreeInternal(MemBlockHdr* ptr)
	{
		SubAllocSize(ptr->Size);

		ptr->Magic = MemBlockHdr::MEM_MAGIC_FREE;

		SystemAlignedFree(ptr);

	}

	MemBlockHdr* STDMemoryManager::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		if (alignment == 0)
			alignment = sizeof(int);

		// Adjust allocation size for header
		// +1 for reverse offset
		size_t spaceForHeader = MemBlockHdr::GetHeaderSize();

		MemBlockHdr* pMemBlock = nullptr;
		MemBlockHdr* oldPtr = ptr;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		auto allocSize = newSize + spaceForHeader;
		void *newPtr = (MemBlockHdr*)_aligned_realloc(ptr, allocSize, alignment);
#else
		assert(alignment <= MemBlockHdr::MaxHeaderAlignment); // We assumed there will be no bigger alignment requirement
		auto allocSize = AlignUp(newSize + spaceForHeader, alignment);
		void* newPtr = realloc(ptr, allocSize);
		auto remain = ((int64_t)newPtr) % alignment;
#endif
		if (newPtr == nullptr)
		{
			auto newPtr2 = SystemAllignedAlloc(allocSize, alignment);
			if (newPtr2 == nullptr)
				return nullptr;

			if (oldPtr != nullptr)
				memcpy(newPtr2, oldPtr + 1, Util::Min(orgSize, newSize));

			SystemAlignedFree(oldPtr);
			newPtr = newPtr2;
		}

		pMemBlock = reinterpret_cast<MemBlockHdr*>(newPtr);
		pMemBlock->Init(this, (uint32_t)newSize, (uint32_t)spaceForHeader);

		return pMemBlock;
	}



	///////////////////////////////////////////////////////////
	// 
	//	EngineMemoryManager
	//

	SharedPointerT<IHeap> EngineMemoryManager::stm_Instance;

	const SharedPointerT<IHeap>& EngineMemoryManager::GetInstance()
	{
		static CriticalSection g_StdHeapLock;
		// This condition will be true most of time, and early return will be faster if the compiler is not intelligent enough.
		if (stm_Instance != nullptr)
			return stm_Instance;

		MutexScopeLock lock(g_StdHeapLock);
		if (stm_Instance == nullptr) // Need to check again after lock
		{
			// Using malloc to avoid recursive memory allocation
			stm_Instance = new(GetSystemHeap()) EngineMemoryManager;
		}

		return stm_Instance;
	}

	EngineMemoryManager::EngineMemoryManager()
		: IHeap("Engine", GetSystemHeapPtr().get())
	{
	}

	EngineMemoryManager::~EngineMemoryManager()
	{
	}




}

