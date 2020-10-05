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
#include "Memory/SFIMemoryManager.h"
#include "Container/SFContainerTraitBase.h"
#include "Container/SFDoubleLinkedListBase.h"






namespace SF {

	class MemoryPool;
	//class MemoryPoolManager;
	//class IHeap;




	///////////////////////////////////////////////////////////
	// 
	//	Heap
	//    - Hierarchical memory heap
	//
	class Heap
	{
	public:

	private:

		// heap pointer
		SharedPointerT<IHeap> m_pHeap;


	protected:

	public:

		Heap(const char* name, IHeap& parent);
		virtual ~Heap();

		// Get parent heap
		IHeap* GetParent() { return m_pHeap != nullptr ? m_pHeap->GetParent() : nullptr; }

		// get heap name
		StringCrc64 GetNameCrc() { return m_pHeap != nullptr ? m_pHeap->GetNameCrc() : ""; }

		// Allocation/Reallocation interface
		void* Alloc(size_t size, size_t alignment = SF_ALIGN_DOUBLE);
		void* Realloc(void* ptr, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE);
		//static void Free(void* ptr);

		// Casting
		operator IHeap&() { return **m_pHeap; }
	};






	///////////////////////////////////////////////////////////
	// 
	//	STDMemoryManager
	//
	class STDMemoryManager : public IHeap
	{
	private:

		static STDMemoryManager* stm_Instance;

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment = SF_ALIGN_DOUBLE) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;
	public:

		STDMemoryManager();
		virtual ~STDMemoryManager();

		static void* SystemAllignedAlloc(size_t size, size_t alignment);
		static void SystemAlignedFree(void* pPtr);

		static STDMemoryManager* GetInstance();
	};



	///////////////////////////////////////////////////////////
	// 
	//	EngineMemoryManager
	//
	class EngineMemoryManager : public Heap
	{
	private:

		static EngineMemoryManager stm_Instance;

	public:

		EngineMemoryManager();
		virtual ~EngineMemoryManager();

		static EngineMemoryManager* GetInstance();
	};


} // namespace SF

