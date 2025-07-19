////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SF Object manager
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Object/SFObjectManager.h"


namespace SF {


	////////////////////////////////////////////////////////////////
	//
	// base object
	//

	constexpr StringCrc64 ObjectManager::TypeName;

	ObjectManager::ObjectManager(IHeap& memoryManager, const StringCrc64& name)
		: LibraryComponent(name)
	{
	}

	ObjectManager::~ObjectManager()
	{
	}


	// Initialize component
	Result ObjectManager::InitializeComponent()
	{
		return LibraryComponent::InitializeComponent();
	}

	// Terminate component
	void ObjectManager::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();
	}

}

