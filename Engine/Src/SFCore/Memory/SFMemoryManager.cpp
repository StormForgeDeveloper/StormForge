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



namespace SF {



	///////////////////////////////////////////////////////////////
	//
	//	Memory manager interfaces
	//

	// System memory manager
	IHeap& GetSystemHeap()
	{
		return *STDMemoryManager::GetInstance();
	}



	// Engine memory manager
	IHeap& GetEngineHeap()
	{
		return *EngineMemoryManager::GetInstance();
	}



	///////////////////////////////////////////////////////////
	// 
	//	Heap
	//    - Hierarchical memory heap
	//

	Heap::Heap(const char* name, IHeap& parent)
		: m_pHeap(new(GetSystemHeap()) IHeap(name, &parent))
	{
	}

	Heap::~Heap()
	{
		// All memory related to the heap should be reported
		if (m_pHeap != nullptr)
			m_pHeap->ReportLeak();
	}

	// Allocation/Reallocation interface
	void* Heap::Alloc(size_t size, size_t alignment)
	{
		if (m_pHeap == nullptr)
			return nullptr;

		return m_pHeap->Alloc(size, alignment);
	}

	void* Heap::Realloc(void* ptr, size_t newSize, size_t alignment)
	{
		if (m_pHeap == nullptr)
			return nullptr;

		return m_pHeap->Realloc(ptr, newSize, alignment);
	}





	///////////////////////////////////////////////////////////
	// 
	//	STDMemoryManager
	//

	STDMemoryManager* STDMemoryManager::stm_Instance = nullptr;

	STDMemoryManager* STDMemoryManager::GetInstance()
	{
		static CriticalSection g_StdHeapLock;
		// This condition will be true most of time, and early return will be faster if the compiler is not inteligent enough.
		if (stm_Instance != nullptr) 
			return stm_Instance;

		MutexScopeLock lock(g_StdHeapLock);
		if (stm_Instance == nullptr) // Need to check again after lock
		{
			void* pBuffer = malloc(sizeof(STDMemoryManager));
			stm_Instance = new(pBuffer) STDMemoryManager;
			SharedReferenceInc inc(stm_Instance); // we need to manage the reference count manually because it wasn't techinically not allocated in regualr way
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
		size_t spaceForHeader = AlignUp(sizeof(MemBlockHdr) + 1, alignment);
		auto allocSize = size + spaceForHeader;

		m_AllocatedDRAM.fetch_add(size, std::memory_order_relaxed);

		MemBlockHdr* pMemBlock;
		pMemBlock = (MemBlockHdr*)SystemAllignedAlloc(allocSize, alignment);

		pMemBlock->Init(this, (uint32_t)size, (uint32_t)spaceForHeader);

		return pMemBlock;
	}

	void STDMemoryManager::FreeInternal(MemBlockHdr* ptr)
	{
		m_AllocatedDRAM.fetch_add(ptr->Size, std::memory_order_relaxed);

		return SystemAlignedFree(ptr);
	}

	MemBlockHdr* STDMemoryManager::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		if (alignment == 0)
			alignment = sizeof(int);

		// Adjust allocation size for header
		// +1 for reverse offset
		size_t spaceForHeader = AlignUp(sizeof(MemBlockHdr) + 1, alignment);
		auto allocSize = newSize + spaceForHeader;

		MemBlockHdr* pMemBlock;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		void *newPtr = (MemBlockHdr*)_aligned_realloc(ptr, allocSize, alignment);
#else
		void* newPtr = realloc(ptr, newSize);
		auto remain = ((int64_t)newPtr) % alignment;
		if (newPtr == nullptr || remain != 0)
#endif
		if (newPtr == nullptr)
		{
			auto newPtr2 = SystemAllignedAlloc(allocSize, alignment);
			if (newPtr2 == nullptr)
				return nullptr;

			memcpy(newPtr2, newPtr, orgSize);
			SystemAlignedFree(newPtr);
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

	EngineMemoryManager EngineMemoryManager::stm_Instance;

	EngineMemoryManager* EngineMemoryManager::GetInstance()
	{
		return &stm_Instance;
	}

	EngineMemoryManager::EngineMemoryManager()
		: Heap("Engine", GetSystemHeap())
	{
	}

	EngineMemoryManager::~EngineMemoryManager()
	{
	}




}

