////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Quic component
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"
#include "Util/SFString.h"


namespace SF {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Module
	//

    class QuicService;

	class EngineComponentQuic : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "EngineComponentQuic";

	public:

        EngineComponentQuic();
		~EngineComponentQuic();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize server component
		virtual Result InitializeComponent() override;
		// Terminate server component
		virtual void DeinitializeComponent() override;

    private:

        UniquePtr<QuicService> m_QuicService;
	};

}//namespace SF 





