////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SF object
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Util/SFStringCrc64.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "MemoryManager/SFMemoryManager.h"



namespace SF {

	class IHeap;


	////////////////////////////////////////////////////////////////
	//
	// base object
	//

	class Object : public SharedObject
	{

	private:
		StringCrc64 m_Name;

		// Object heap
		// As we are using hierarchical memory management, this should be safe, if it has crash because of this, it means you have non-hierarchical memory usage.
		// However, there are a couple of cases we need to have heap reference count per object, such as sharing a heap for particular group of objects, in this case the heap should have reference count so that the heap is valid while this object is alive even though it doesn't have any allocated memory from the heap.
		IHeapPtr m_Heap;

	public:

		Object(IHeap* heap, const StringCrc64& name = "");

		virtual ~Object();

		const StringCrc64& GetName() { return m_Name; }
		void SetName(const StringCrc64& name) { m_Name = name; }

		IHeap& GetHeap() const { return **m_Heap; }
	};

	extern template class SharedPointerT<Object>;
	typedef SharedPointerT<Object> ObjectPtr;


} // namespace SF

