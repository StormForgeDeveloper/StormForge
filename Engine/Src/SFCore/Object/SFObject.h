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
#include "String/SFFixedString.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "Memory/SFMemoryManager.h"



namespace SF {

	class IHeap;


	////////////////////////////////////////////////////////////////
	//
	// base object
	//

	class Object : public SharedObject
	{

	private:
		FixedString m_Name;

		// Object heap
		// As we are using hierarchical memory management, this should be safe, if it has crash because of this, it means you have non-hierarchical memory usage.
		// However, there are a couple of cases we need to have heap reference count per object, such as sharing a heap for particular group of objects, in this case the heap should have reference count so that the heap is valid while this object is alive even though it doesn't have any allocated memory from the heap.
		IHeapPtr m_Heap;

	public:

		Object(IHeap* heap, const FixedString& name = "");

		virtual ~Object();

		const FixedString& GetName() { return m_Name; }
		void SetName(const FixedString& name) { m_Name = name; }

		IHeap& GetHeap() { return **m_Heap; }
	};

	extern template class SharedPointerT<Object>;
	typedef SharedPointerT<Object> ObjectPtr;


} // namespace SF

