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
#include "Multithread/SFSynchronization.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Util/SFString.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFUtility.h"


namespace SF {



    void atexit_handler()
    {
        // exit has request, give all go
        IHeap::SetMemoryLeakDetection(false);
    }

	///////////////////////////////////////////////////////////////
	//
	//	Memory manager interfaces
	//

    SharedPointerT<IHeap> Heap::Create(const char* name, IHeap& parent)
    {
        return new IHeap(name, &parent);
    }

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
	//	: m_pHeap(new IHeap(name, &parent))
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

        std::atexit(atexit_handler);

		if (stm_Instance == nullptr) // Need to check again after lock
		{
			// Using malloc to avoid recursive memory allocation
			void* pBuffer = STDMemoryManager::SystemAllignedAlloc(sizeof(STDMemoryManager), sizeof(int));
			stm_Instance = new(pBuffer) STDMemoryManager;
            stm_Instance->AddReference(); // We are not going to release this
            stm_Instance->SetIgnoreMemmoryLeak(true);
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
			alignment = SF_ALIGN_DOUBLE;

		// Adjust allocation size for header
		// +1 for reverse offset
		auto allocSize = MemBlockHdr::CalculateAllocationSize(size, alignment);

		m_AllocatedDRAM.fetch_add(size, std::memory_order_relaxed);

		MemBlockHdr* pMemBlock;
		pMemBlock = (MemBlockHdr*)SystemAllignedAlloc(allocSize, alignment);
		assert((intptr_t(pMemBlock) % alignment) == 0);
		AddAllocSize(size);

		pMemBlock->InitHeader(this, (uint32_t)size, (uint32_t)MemBlockHdr::GetDefaultHeaderSize());
		auto pFooter = pMemBlock->GetFooter();
		pFooter->InitFooter();

		return pMemBlock;
	}

	void STDMemoryManager::FreeInternal(MemBlockHdr* ptr)
	{
		SubAllocSize(ptr->Size);

		ptr->GetFooter()->Deinit();
		ptr->Deinit();

		SystemAlignedFree(ptr);

	}

	MemBlockHdr* STDMemoryManager::ReallocInternal(MemBlockHdr* ptr, size_t InOrgSize, size_t newSize, size_t alignment)
	{
		if (alignment == 0)
			alignment = sizeof(int);

		MemBlockHdr* pMemBlock = nullptr;
		auto orgSize = ptr->Size;

		auto allocSize = MemBlockHdr::CalculateAllocationSize(newSize, alignment);
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		void *newPtr = (MemBlockHdr*)_aligned_realloc(ptr, allocSize, alignment);
#else
		assert(alignment <= MemBlockHdr::MaxHeaderAlignment); // We assumed there will be no bigger alignment requirement
		void* newPtr = realloc(ptr, allocSize);
#endif
		if (newPtr == nullptr)
		{
			// We don't know whether the object need to be able to moved in memory. Let the caller handle new&copy
			return nullptr;
		}

		pMemBlock = reinterpret_cast<MemBlockHdr*>(newPtr);
		pMemBlock->InitHeader(this, (uint32_t)newSize, (uint32_t)MemBlockHdr::GetDefaultHeaderSize());
		pMemBlock->GetFooter()->InitFooter();

		if (orgSize != pMemBlock->Size)
		{
			SubAllocSize(orgSize);
			AddAllocSize(newSize);
		}


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
			stm_Instance = new EngineMemoryManager;
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

