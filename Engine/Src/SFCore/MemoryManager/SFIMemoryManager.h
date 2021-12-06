////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory manager
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Container/SFContainerTraitBase.h"
#include "Container/SFDoubleLinkedListBase.h"
#include "Util/SFStringCrc64.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "MemoryManager/SFMemory.h"




namespace SF {

	class MemoryPool;
	class MemoryPoolManager;
	struct MemBlockHdr;
	class IHeap;
	class IHeapImpl;


	typedef SharedPointerT<IHeap> IHeapPtr;
	typedef SharedPointerAtomicT<IHeap> IHeapAtomicPtr;


	///////////////////////////////////////////////////////////////
	//
	//	Memory manager interfaces
	//

	// System memory manager
	IHeap& GetSystemHeap();
	const IHeapPtr& GetSystemHeapPtr();

	// Engine memory manager
	IHeap& GetEngineHeap();
	const IHeapPtr& GetEngineHeapPtr();



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	IHeap, - used to be a base interface for heap, now basic implementation of heap
	//
	class IHeap : public SharedObject
	{
	private:
		// parent memory heap, used for overflow allocation or propagate allocation size calculation
		IHeapPtr m_Parent;

		// Heap name
		StringCrc64 m_NameCrc;

		// You can disable memory leak detection per heap
		bool m_IgnoreMemoryLeak;

		// Allocated memory list
		DoubleLinkedListBase<DoubleLinkedListNode, SF::ThreadSyncTraitReadWrite> m_AllocatedList;


	protected:

		// Allocated size include sub manager
		Atomic<int64_t> m_AllocatedDRAM;
		Atomic<int64_t> m_AllocatedVRAM;


	private:

		// Global memory leak detection flag
		static bool stm_EnableLeakDetection;

	public:

		// Static accessors
		static bool GetMemoryLeakDetection() { return stm_EnableLeakDetection; }
		static void SetMemoryLeakDetection(bool enable) { stm_EnableLeakDetection = enable; }

	protected:

		void AddAllocSize(size_t size);
		void SubAllocSize(size_t size);

	public:

		////////////////////////////////////////////////////////
		// Internal - Do not access

		// Interface for raw allocation. If the implementation requires custom memory header, the memory header size should be included in the request size
		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment = SF_ALIGN_DOUBLE);
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment);
		virtual void FreeInternal(MemBlockHdr* ptr);

		// Add/Remove to/from allocated list
		void AddAllocatedList(MemBlockHdr* pMemBlock);
		void RemoveAllocatedList(MemBlockHdr* pMemBlock);


	public:
		IHeap(StringCrc64 nameCrc, IHeap* pParent = nullptr);
		virtual ~IHeap();

		// Shared object overrides
		virtual bool CanDelete() override;
		virtual void Dispose() override;


		// flag for memory leak detection
		bool GetIgnoreMemoryLeak() { return m_IgnoreMemoryLeak; }
		void SetIgnoreMemmoryLeak(bool value) { m_IgnoreMemoryLeak = value; }

		// report if there is any memory hasn't released
		void ReportLeak();


		// Get parent heap
		IHeap* GetParent() { return m_Parent.get(); }

		// get heap name
		StringCrc64 GetNameCrc() { return m_NameCrc; }

		// Allocation/Reallocation interface
		virtual void* Alloc(size_t size, size_t alignment = SF_ALIGN_DOUBLE);
		virtual void* Realloc(void* ptr, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE);
		static bool Free(void* ptr);


		static struct MemBlockHdr* GetMemoryBlockHdr(void* ptr);
		static IHeap* GetAloocationHeap(void* ptr);
		static bool CheckMemoryHeader(void* ptr);
		static SF_FORCEINLINE void TestMemoryHeaderChecked(void* ptr)
		{
			Assert(CheckMemoryHeader(ptr));
		}

		template<class ClassType>
			//template<
		//	class ClassType,
		//	typename = std::enable_if_t<std::is_trivially_constructible_v<ClassType>>
		//>
		static void Delete(ClassType* pPtr)
		{
			if (pPtr == nullptr) return;
			auto pHeap = GetAloocationHeap((void*)(pPtr));
			assert(pHeap);
			pPtr->~ClassType();
			operator delete((void*)(pPtr), *pHeap);
		}

		//template<
		//	class ClassType,
		//	typename = std::enable_if_t<!std::is_trivially_constructible_v<ClassType>>
		//>
		//static void Delete(ClassType* pPtr)
		//{
		//	if (pPtr == nullptr) return;
		//	auto pHeap = GetAloocationHeap((void*)(pPtr));
		//	assert(pHeap);
		//	operator delete((void*)(pPtr), *pHeap);
		//}
	};


	// SF deleter
	template <class DataType>
	struct Deleter {
		constexpr Deleter() noexcept = default;

		void operator()(DataType* _Ptr) const noexcept {
			static_assert(0 < sizeof(DataType), "can't delete an incomplete type");
			IHeap::Delete(_Ptr);
		}
	};

	template<typename DataType, typename D = Deleter<DataType>>
	using SFUniquePtr = std::unique_ptr<DataType, D>;


	/////////////////////////////////////////////////////////////
	//// 
	////	IHeap
	////    - All allocation goes to here
	////
	//class IHeap : public IHeap
	//{
	//private:

	//	const char* m_Name;

	//	std::atomic<MemoryPoolManager*> m_MemoryPoolManager;


	//public:
	//	IHeap(const char* name, IHeap* pParent = nullptr);
	//	virtual ~IHeap();

	//	const char* GetName() { return m_Name; }

	//	virtual MemoryPool* GetMemoryPoolBySize(size_t size);

	//	// TODO: Add GPU allocation interfaces
	//};



} // namespace SF

