////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : 3rdParty initializer
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

	class LibraryComponent3rdParties : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "LibraryComponent3rdParties";

	public:

        LibraryComponent3rdParties();
		~LibraryComponent3rdParties();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;

	};

}//namespace SF 





