////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine result code initializer
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"


namespace SF {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module
	//

	class LibraryComponentEngineResultCode : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "LibraryComponentEngineResultCode";

	public:

		LibraryComponentEngineResultCode();
		~LibraryComponentEngineResultCode();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;

	};

}//namespace SF 





