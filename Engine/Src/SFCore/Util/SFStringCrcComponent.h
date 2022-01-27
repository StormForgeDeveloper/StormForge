////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine string crc initializer
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

	class StringCrcLibraryComponent : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "StringCrcLibraryComponent";

		String m_StringCrcBinPath;

	public:

		StringCrcLibraryComponent(const char* stringCrcBinPath);
		~StringCrcLibraryComponent();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;

	};

}//namespace SF 

