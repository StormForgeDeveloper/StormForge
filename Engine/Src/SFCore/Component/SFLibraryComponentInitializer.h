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

	// Initialization enum
	enum class ComponentInitializeMode : uint8_t
	{
		PreInit,
		RegisterComponent,
		AfterRegisterComponent,
		Max,
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

		// Initializer, return true if you don't need to receive any initializer messsage
		virtual bool Initialize(ComponentInitializeMode InitMode) { return true; }

		// initialized done and released from system
		virtual void Release() {}

		// call component initializers in the list
		static void CallInitializers(ComponentInitializeMode InitMode);

	private:

		LibraryComponentInitializer* m_pNext{};

		static uint32_t stm_CalledMode;
		static LibraryComponentInitializer* stm_pHead;
	};





} // namespace SF




