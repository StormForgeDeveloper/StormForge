////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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
#include "String/SFStringCrc64.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"





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

	template<class ValueType>
	constexpr ValueType AlignUp(ValueType x, size_t align)
	{
		return (ValueType)((((uintptr_t)(x) +align - 1) & (~((uintptr_t)align - 1))));
	}

	class MemoryPool;
	class MemoryPoolManager;
	struct MemBlockHdr;
	class IHeap;
	class IHeapImpl;

	///////////////////////////////////////////////////////////////
	//
	//	Memory manager interfaces
	//

	// System memory manager
	IHeap& GetSystemHeap();

	// Engine memory manager
	IHeap& GetEngineHeap();





	/////////////////////////////////////////////////////////////////////////////////
	//
	//	IHeap, - used to be a base interface for heap, now basic implementation of heap
	//
	class IHeap : public SharedObject
	{
	private:
		// parent memory heap, used for overflow allocation or propagate allocation size calculation
		IHeap* m_Parent;

		// Heap name
		StringCrc64 m_NameCrc;

		// You can disable memory leak detection per heap
		bool m_IgnoreMemoryLeak;

		// Allocated memory list
		DoubleLinkedListBase<DoubleLinkedListNode, SF::ThreadSyncTraitReadWrite> m_AllocatedList;


	protected:

		// Allocated size include sub manager
		std::atomic<int64_t> m_AllocatedDRAM;
		std::atomic<int64_t> m_AllocatedVRAM;


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
		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment);
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
		IHeap* GetParent() { return m_Parent; }

		// get heap name
		StringCrc64 GetNameCrc() { return m_NameCrc; }

		// Allocation/Reallocation interface
		virtual void* Alloc(size_t size, size_t alignment = SF_ALIGN_DOUBLE);
		virtual void* Realloc(void* ptr, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE);
		static void Free(void* ptr);


		static struct MemBlockHdr* GetMemoryBlockHdr(void* ptr);
		static bool CheckMemoryHeader(void* ptr);

		// Deprecated
		template<class ClassType>
		static void Delete(ClassType* pPtr)
		{
			if (pPtr == nullptr) return;
			delete pPtr;
		}

	};

	typedef SharedPointerT<IHeap> IHeapPtr;
	typedef SharedPointerAtomicT<IHeap> IHeapAtomicPtr;



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

