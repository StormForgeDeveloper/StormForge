////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SF Object manager
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Object/SFObjectManager.h"


namespace SF {


	////////////////////////////////////////////////////////////////
	//
	// base object
	//

	constexpr FixedString ObjectManager::TypeName;

	ObjectManager::ObjectManager(IHeap& memoryManager, const FixedString& name)
		: LibraryComponent(name)
		, m_SharedObjectManager(memoryManager)
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

