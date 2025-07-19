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

	public:

		Object(const StringCrc64& name = "");

		virtual ~Object();

		const StringCrc64& GetName() { return m_Name; }
		void SetName(const StringCrc64& name) { m_Name = name; }

		IHeap& GetHeap() const { return GetSystemHeap(); }
	};

	extern template class SharedPointerT<Object>;
	typedef SharedPointerT<Object> ObjectPtr;


} // namespace SF

