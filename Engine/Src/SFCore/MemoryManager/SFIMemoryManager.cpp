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
#include "Util/SFLog.h"
#include "Object/SFSharedObjectManager.h"
#include "MemoryManager/SFHeapMemory.h"

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

	IHeap::IHeap(StringCrc64 nameCrc, IHeap* pParent)
		: m_Parent(pParent)
		, m_NameCrc(nameCrc)
		, m_IgnoreMemoryLeak(!IHeap::GetMemoryLeakDetection())
		, m_AllocatedDRAM(0)
		, m_AllocatedVRAM(0)
	{
		assert(pParent != this);
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
			SFLog(System, Warning, "MemoryLeak detected, {0}", m_AllocatedList.size());
#if ENABLE_MEMORY_TRACE
			int printcount = 0;
			m_AllocatedList.for_each([&printcount](DoubleLinkedListNode* pNode)
			{
				MemBlockFooter* pBlockFooter = ContainerPtrFromMember(MemBlockFooter, ListNode, pNode);
				pBlockFooter->StackTrace.PrintStackTrace(CurrentProcessID);
				printcount++;
				return printcount < 10; // print max 10
			});
#endif
			Assert(false);
		}
		//Assert(m_AllocatedDRAM.load(std::memory_order_acquire) == 0 && m_AllocatedVRAM.load(std::memory_order_acquire) == 0);
	}

	void IHeap::AddAllocSize(size_t size)
	{
		int64_t orgSize = m_AllocatedDRAM.fetch_add(size, std::memory_order_relaxed);
		if (orgSize == 0)
		{
			if (GetReferenceCount() > 0) // Ref count zero means it is not using shared pointer
			{
				// Keep extra reference count while this object has allocated memory block
				SharedReferenceInc(this);
			}
		}
	}

	void IHeap::SubAllocSize(size_t size)
	{
		auto remainAllocated = static_cast<intptr_t>(m_AllocatedDRAM.fetch_sub(size, std::memory_order_relaxed) - size);
		if (remainAllocated < 0)
		{
			assert(false);
			m_AllocatedDRAM = 0;
			if (GetReferenceCount() > 0)
			{
				// You can remove reference count
				SharedReferenceDec(this);
			}
		}
		else if (remainAllocated == 0)
		{
			if (GetReferenceCount() > 0)
			{
				// You can remove reference count
				SharedReferenceDec(this);
			}
		}
	}


	MemBlockHdr* IHeap::AllocInternal(size_t size, size_t alignment)
	{
		assert(GetParent() != nullptr);
		if (GetParent() == nullptr)
			return nullptr;

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
		auto pFooter = pMemBlock->GetFooter();
		pFooter->StackTrace.CaptureCallStack(4);
		m_AllocatedList.Add(&pFooter->ListNode);
#else
		unused(pMemBlock);
#endif
	}

	void IHeap::RemoveAllocatedList(MemBlockHdr* pMemBlock)
	{
#if ENABLE_MEMORY_TRACE
		auto pFooter = pMemBlock->GetFooter();
		assert(pFooter->Magic == MemBlockFooter::MEM_MAGIC);
		pFooter->StackTrace.CaptureCallStack(4);
		m_AllocatedList.Remove(&pFooter->ListNode);
#else
		unused(pMemBlock);
#endif
	}


	void* IHeap::Alloc(size_t size, size_t alignment)
	{

		MemBlockHdr* pMemBlock = AllocInternal(size, alignment);
		if (pMemBlock == nullptr)
			return nullptr;
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

		return (uint8_t*)pMemBlock->GetDataPtr();
	}

	void* IHeap::Realloc(void* ptr, size_t newSize, size_t alignment)
	{
		if (ptr == nullptr)
		{
			return Alloc(newSize, alignment);
		}

		MemBlockHdr* pMemBlock = GetMemoryBlockHdr(ptr);
		if (pMemBlock == nullptr)
		{
			// should be allocated from std
			return realloc(ptr, newSize);
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
		return pMemBlock->GetDataPtr();
	}

	bool IHeap::Free(void* ptr)
	{
		if (ptr == nullptr) return true;

		MemBlockHdr* pMemBlock = GetMemoryBlockHdr(ptr);
		if (pMemBlock == nullptr)
		{
			// should be allocated from other system
			free(ptr);
			return false;
		}

		auto pHeap = pMemBlock->pHeap;
#if ENABLE_MEMORY_TRACE
		if (pHeap != nullptr && !pHeap->GetIgnoreMemoryLeak())
			pHeap->RemoveAllocatedList(pMemBlock);
#endif

		pHeap->FreeInternal(pMemBlock);

		return true;
	}

	struct MemBlockHdr* IHeap::GetMemoryBlockHdr(void* ptr)
	{
		if (ptr == nullptr)
			return nullptr;

		// We have two size types 16bytes for normal header, 32bytes for extended heap
		constexpr auto DefaultHeaderSize = MemBlockHdr::GetDefaultHeaderSize();
		constexpr auto ExpectedHeaderSize2 = DefaultHeaderSize << 1;
		constexpr auto ExpectedHeaderSize3 = HeapMemory::MapNodeHeaderSize;
		MemBlockHdr* pMemBlock = nullptr;

		uint8_t* pCompilerSizePos = reinterpret_cast<uint8_t*>(ptr); // each compiler has different search length
		uint8_t headerOffset = 0;
		int iSearchMax = 6; // for linux

		// search up to for times, one already counted so 3 more
		for (int iSearch = 0; iSearch < iSearchMax; iSearch++, pCompilerSizePos-=sizeof(uint32_t))
		{
			headerOffset = *(pCompilerSizePos - 1); // The place I stored header offset
			pMemBlock = reinterpret_cast<MemBlockHdr*>(pCompilerSizePos - DefaultHeaderSize);
			if ((headerOffset == DefaultHeaderSize || headerOffset == ExpectedHeaderSize2 || headerOffset == ExpectedHeaderSize3)
				&& pMemBlock->Magic == MemBlockHdr::MEM_MAGIC)
				break;
		}

		// Our memory header hasn't found
		if (pMemBlock->Magic != MemBlockHdr::MEM_MAGIC)
		{
			// not a memory header allocated by this system
			return nullptr;
		}

		return pMemBlock;
	}

	IHeap* IHeap::GetAloocationHeap(void* ptr)
	{
		auto pHdr = GetMemoryBlockHdr(ptr);
		return pHdr ? pHdr->pHeap : nullptr;
	}

	bool IHeap::CheckMemoryHeader(void* ptr)
	{
		if (ptr == nullptr)
			return true;

		auto* pMemBlock = GetMemoryBlockHdr(ptr);
		if (pMemBlock == nullptr)
			return false;

		auto* pFooter = pMemBlock->GetFooter();
		if (pFooter == nullptr)
			return false;

		return pMemBlock->Magic == MemBlockHdr::MEM_MAGIC && pFooter->Magic == MemBlockFooter::MEM_MAGIC;
	}





}

