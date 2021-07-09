////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Component class
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Util/SFStringCrc64.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Container/SFSortedSet.h"


namespace SF {

	enum class ComponentInitializeMode : uint8_t
	{
		PreInit,
		RegisterComponent,
		AfterRegisterComponent,
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	LibraryComponent initializer
	// 	   - Initializer for indirectly added components
	//

	class LibraryComponentInitializer
	{
	public:
		LibraryComponentInitializer();
		virtual ~LibraryComponentInitializer();

		virtual void Initialize(ComponentInitializeMode InitMode) = 0;

		// call component initializers in the list
		static void CallInitializers(ComponentInitializeMode InitMode);

	private:

		LibraryComponentInitializer* m_pNext{};

		static LibraryComponentInitializer* stm_pHead;
	};





} // namespace SF




