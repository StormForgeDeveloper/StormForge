////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SF object manager
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedObjectManager.h"
#include "Object/SFLibraryComponent.h"




namespace SF {

	////////////////////////////////////////////////////////////////
	//
	// object manager
	//

	class ObjectManager : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "ObjectManager";

	protected:

		SharedObjectManager m_SharedObjectManager;

	public:

		ObjectManager(IHeap& memoryManager, const StringCrc64& name = StringCrc64("ObjectManager"));
		virtual ~ObjectManager();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;
		// Terminate component
		virtual void DeinitializeComponent() override;

	};



} // namespace SF

