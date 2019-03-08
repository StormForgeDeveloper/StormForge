////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Object/SFObject.h"
#include "Object/SFObjectManager.h"
#include "Service/SFService.h"
#include "SFAssert.h"


namespace SF {



	template class SharedPointerT<Object>;


	////////////////////////////////////////////////////////////////
	//
	// base object
	//

	Object::Object(IHeap* heap, const FixedString& name)
		: m_Name(name)
		, m_Heap(heap)
	{
		AssertRel(heap != nullptr);
	}

	Object::~Object()
	{
	}


}

