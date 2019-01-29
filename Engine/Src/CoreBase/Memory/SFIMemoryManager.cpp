////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory manager
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Thread/SFSynchronization.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemoryPool.h"
#include "String/SFString.h"
#include "String/SFFixedString.h"
#include "Util/SFLog.h"
#include "Object/SFSharedObjectManager.h"


namespace SF {



	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	Heap manager
	//

	class Heapmanager : public SharedObjectManager, public Thread
	{
	private:

		bool m_ReportedExcessiveFreeObjects = false;

	public:

		Heapmanager()
			: SharedObjectManager(GetSystemHeap())
		{
			// TODO: Still working on this idea
			//Start();
		}


		// Garbagte Collect free Pointers
		virtual void Update() override
		{
			SharedObjectManager::Update();
			if (GetPendingFreeItemCount() > 1000)
			{
				Assert(m_ReportedExcessiveFreeObjects);
				m_ReportedExcessiveFreeObjects = true;
			}
			else
			{
				m_ReportedExcessiveFreeObjects = false;
			}
		}


		// thread tick function
		virtual bool Tick() override
		{
			Update();
			return true;
		}
	};





	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	Static
	//

	bool IHeap::stm_EnableLeakDetection = true;

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	IHeap implementation
	//

	IHeap::IHeap(FixedString nameCrc, IHeap* pParent)
		: m_Parent(pParent)
		, m_NameCrc(nameCrc)
		, m_IgnoreMemoryLeak(!IHeap::GetMemoryLeakDetection())
		, m_AllocatedDRAM(0)
		, m_AllocatedVRAM(0)
	{
	}

	IHeap::~IHeap()
	{
	}


	// Shared object overrides
	bool IHeap::CanDelete()
	{
		return m_AllocatedDRAM.load(std::memory_order_relaxed) == 0 && m_AllocatedVRAM.load(std::memory_order_relaxed) == 0;
	}

	void IHeap::Dispose()
	{
		ReportLeak();
	}


	// report if there is any memory hasn't released
	void IHeap::ReportLeak()
	{
		if (GetIgnoreMemoryLeak())
			return;

		// Look into m_AllocatedList for detail
		if (m_AllocatedDRAM.load(std::memory_order_acquire) != 0 || m_AllocatedVRAM.load(std::memory_order_acquire) != 0)
		{
			Assert(false);
			SFLog(System, Warning, "MemoryLeak detected, {0}", m_AllocatedList.size());
#if ENABLE_MEMORY_TRACE
			int printcount = 0;
			m_AllocatedList.for_each([&printcount](DoubleLinkedListNode* pNode)
			{
				MemBlockHdr* pBlockHdr = ContainerPtrFromMember(MemBlockHdr, ListNode, pNode);
				pBlockHdr->StackTrace.PrintStackTrace(CurrentProcessID);
				printcount++;
				return printcount < 10; // print max 10
			});
#endif
		}
		//Assert(m_AllocatedDRAM.load(std::memory_order_acquire) == 0 && m_AllocatedVRAM.load(std::memory_order_acquire) == 0);
	}

	void IHeap::AddAllocSize(size_t size)
	{
		int64_t orgSize = m_AllocatedDRAM.fetch_add(size, std::memory_order_relaxed);
		if (orgSize == 0)
		{
			SharedReferenceInc(this);
		}
	}

	void IHeap::SubAllocSize(size_t size)
	{
		auto remainAllocated = static_cast<intptr_t>(m_AllocatedDRAM.fetch_sub(size, std::memory_order_relaxed) - size);
		if (remainAllocated < 0)
		{
			assert(false);
			m_AllocatedDRAM = 0;
			SharedReferenceDec(this);
		}
		else if (remainAllocated == 0)
		{
			SharedReferenceDec(this);
		}
	}


	MemBlockHdr* IHeap::AllocInternal(size_t size, size_t alignment)
	{
		assert(GetParent() != nullptr);
		if (GetParent() == nullptr) return nullptr;

		MemBlockHdr* pMemBlock = GetParent()->AllocInternal(size, alignment);
		if (pMemBlock != nullptr)
		{
			AddAllocSize(size);
		}

		return pMemBlock;
	}

	MemBlockHdr* IHeap::ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment)
	{
		assert(GetParent() != nullptr);
		if (GetParent() == nullptr) return nullptr;

		ptr = GetParent()->ReallocInternal(ptr, orgSize, newSize, alignment);
		if (ptr != nullptr)
		{
			SubAllocSize(orgSize);
			AddAllocSize(newSize);
		}

		return ptr;
	}

	void IHeap::FreeInternal(MemBlockHdr* ptr)
	{
		ptr->pHeap = nullptr;

		auto parent = GetParent();
		auto freeSize = ptr->Size;

		if (parent == nullptr)
		{
			assert(false);
			return;
		}
		parent->FreeInternal(ptr);

		SubAllocSize(freeSize);
	}


	// Add/Remove to/from allocated list
	void IHeap::AddAllocatedList(MemBlockHdr* pMemBlock)
	{
#if ENABLE_MEMORY_TRACE
		pMemBlock->StackTrace.CaptureCallStack(2);
		m_AllocatedList.Add(&pMemBlock->ListNode);
#else
		unused(pMemBlock);
#endif
	}

	void IHeap::RemoveAllocatedList(MemBlockHdr* pMemBlock)
	{
#if ENABLE_MEMORY_TRACE
		pMemBlock->StackTrace.CaptureCallStack(2);
		m_AllocatedList.Remove(&pMemBlock->ListNode);
#else
		unused(pMemBlock);
#endif
	}


	void* IHeap::Alloc(size_t size, size_t alignment)
	{

		MemBlockHdr* pMemBlock = AllocInternal(size, alignment);
		if (pMemBlock == nullptr) return nullptr;
#if ENABLE_MEMORY_TRACE
		if (!GetIgnoreMemoryLeak())
		{
			AddAllocatedList(pMemBlock);
		}
#endif
		// We only support specific alignment range
		Assert(alignment <= SF_ALIGN_DOUBLE);

		// change heap to this
		pMemBlock->pHeap = this;

		return (uint8_t*)pMemBlock + pMemBlock->DataOffset;
	}

	void* IHeap::Realloc(void* ptr, size_t newSize, size_t alignment)
	{
		if (ptr == nullptr)
		{
			return Alloc(newSize, alignment);
		}

		auto offsetToHeader = *((uint8_t*)ptr - 1);
		MemBlockHdr* pMemBlock = reinterpret_cast<MemBlockHdr*>((uint8_t*)(ptr)-offsetToHeader);
		if (pMemBlock == nullptr)
			return nullptr;

		AssertRel(pMemBlock->Magic == MemBlockHdr::MEM_MAGIC);
		if(pMemBlock->Magic != MemBlockHdr::MEM_MAGIC)
		{
			Free(ptr);
			return Alloc(newSize, alignment);
		}

		auto orgSize = pMemBlock->Size;
		auto pHeap = pMemBlock->pHeap;
		if (pHeap == nullptr)
			pHeap = &GetSystemHeap();

#if ENABLE_MEMORY_TRACE
		if (!GetIgnoreMemoryLeak())
		{
			pHeap->RemoveAllocatedList(pMemBlock);
		}
#endif
		pMemBlock = pHeap->ReallocInternal(pMemBlock, orgSize, newSize, alignment);
		if (pMemBlock == nullptr) return nullptr;

		// change heap to this
		pMemBlock->pHeap = this;

#if ENABLE_MEMORY_TRACE
		if (!GetIgnoreMemoryLeak())
		{
			pHeap->AddAllocatedList(pMemBlock);
		}
#endif
		// we might just don't care realloc
		return (uint8_t*)pMemBlock + pMemBlock->DataOffset;
	}

	void IHeap::Free(void* ptr)
	{
		if (ptr == nullptr) return;

		MemBlockHdr* pMemBlock = GetMemoryBlockHdr(ptr);
		if (pMemBlock == nullptr)
		{
			// should be allocated from other system
			free(ptr);
			return;
		}

		auto pHeap = pMemBlock->pHeap;
#if ENABLE_MEMORY_TRACE
		if (pHeap != nullptr && !pHeap->GetIgnoreMemoryLeak())
			pHeap->RemoveAllocatedList(pMemBlock);
#endif
		//pMemBlock->pHeap = nullptr;

		pHeap->FreeInternal(pMemBlock);
	}

	struct MemBlockHdr* IHeap::GetMemoryBlockHdr(void* ptr)
	{
		if (ptr == nullptr)
			return nullptr;

		auto headerOffset = *((uint8_t*)ptr - 1);

		MemBlockHdr* pMemBlock = (MemBlockHdr*)((uint8_t*)(ptr) - headerOffset);
		if (pMemBlock->Magic != MemBlockHdr::MEM_MAGIC) // it could be array header
		{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			// On windows there is only count
			size_t *pSizes = (size_t*)(intptr_t(ptr) - sizeof(size_t));
			size_t count = pSizes[0];
#else
			// On Android there is size of element and count
			size_t *pSizes = (size_t*)(intptr_t(ptr) - sizeof(size_t) * 2);
			size_t count = pSizes[1];
#endif
			unused(count);
			pMemBlock = (MemBlockHdr*)((uint8_t*)(pSizes)-headerOffset);
			if (pMemBlock->Magic != MemBlockHdr::MEM_MAGIC)
			{
				// not a memory header allocated by this system
				return nullptr;
			}
		}

		return pMemBlock;
	}

	bool IHeap::CheckMemoryHeader(void* ptr)
	{
		MemBlockHdr* pMemBlock = GetMemoryBlockHdr(ptr);
		if (pMemBlock == nullptr)
			return false;

		AssertRel(pMemBlock->Magic == MemBlockHdr::MEM_MAGIC);
		return pMemBlock->Magic == MemBlockHdr::MEM_MAGIC;
	}




	////////////////////////////////////////////////////////////////////////////////////////
	////
	////
	////

	//IHeap::IHeap(const char* name, IHeap* pParent)
	//	: IHeap(name, pParent)
	//	, m_Name(name)
	//	, m_MemoryPoolManager(nullptr)
	//{
	//}

	//IHeap::~IHeap()
	//{
	//	auto pMemoryPool = m_MemoryPoolManager.exchange(nullptr, std::memory_order_acq_rel);
	//	if(pMemoryPool != nullptr)
	//		Delete(pMemoryPool);
	//}


	//MemoryPool* IHeap::GetMemoryPoolBySize(size_t size)
	//{
	//	auto pCurManager = m_MemoryPoolManager.load(std::memory_order_relaxed);
	//	if (pCurManager == nullptr)
	//	{
	//		MemoryPoolManager *pNewManager = new(*this) MemoryPoolManager(*this);
	//		MemoryPoolManager* expected = nullptr;
	//		while (!m_MemoryPoolManager.compare_exchange_weak(expected, pNewManager, std::memory_order_relaxed))
	//		{
	//			if (expected != nullptr)
	//			{
	//				Delete(pNewManager);
	//				break;
	//			}
	//		}

	//		pCurManager = m_MemoryPoolManager.load(std::memory_order_acquire);
	//	}

	//	return pCurManager->GetMemoryPool(size);
	//}



}

