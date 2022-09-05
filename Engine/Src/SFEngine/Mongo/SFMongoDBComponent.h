////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : MongoDB component
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Component/SFLibraryComponent.h"

namespace SF
{

	class MongoDBComponent : public LibraryComponent
	{
	public:

		static constexpr StringCrc64 TypeName = "MongoDBComponent";

	private:

		IHeap& m_Heap;

	public:

		// Constructor
		MongoDBComponent();
		~MongoDBComponent();

		// Heap
		IHeap& GetHeap() { return m_Heap; }

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;
		// Terminate component
		virtual void DeinitializeComponent() override;
	};
}

