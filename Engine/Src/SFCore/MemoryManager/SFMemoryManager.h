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
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFIMemoryManager.h"
#include "Container/SFContainerTraitBase.h"
#include "Container/SFDoubleLinkedListBase.h"






namespace SF {

	class MemoryPool;



	///////////////////////////////////////////////////////////
	// 
	//	Heap
	//    - Deprecated. just a wrapper now
	//

	class Heap : public SharedPointerT<IHeap>
	{
	public:

		Heap(const char* name, IHeap& parent) 
			: SharedPointerT<IHeap>(new(parent) IHeap(name, &parent))
		{}

		operator IHeap& () { return *get(); }
	};






	///////////////////////////////////////////////////////////
	// 
	//	STDMemoryManager
	//
	class STDMemoryManager : public IHeap
	{
	private:

		static SharedPointerT<IHeap> stm_Instance;

	protected:

		virtual MemBlockHdr* AllocInternal(size_t size, size_t alignment = SF_ALIGN_DOUBLE) override;
		virtual MemBlockHdr* ReallocInternal(MemBlockHdr* ptr, size_t orgSize, size_t newSize, size_t alignment = SF_ALIGN_DOUBLE) override;
		virtual void FreeInternal(MemBlockHdr* ptr) override;
	public:

		STDMemoryManager();
		virtual ~STDMemoryManager();

		static void* SystemAllignedAlloc(size_t size, size_t alignment);
		static void SystemAlignedFree(void* pPtr);

		static const SharedPointerT<IHeap>& GetInstance();
	};



	///////////////////////////////////////////////////////////
	// 
	//	EngineMemoryManager
	//
	class EngineMemoryManager : public IHeap
	{
	private:

		static SharedPointerT<IHeap> stm_Instance;

	public:

		EngineMemoryManager();
		virtual ~EngineMemoryManager();

		static const SharedPointerT<IHeap>& GetInstance();
	};


} // namespace SF

