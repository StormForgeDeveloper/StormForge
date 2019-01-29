////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server Config
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "String/SFFixedString32.h"
#include "Component/SFConnectionManagerComponent.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"
#include "Service/SFEngineService.h"



namespace SF
{
	ConnectionManagerComponent::ConnectionManagerComponent(uint bucketSize)
		: LibraryComponent("ConnectionManagerComponent")
		, m_BucketSize(bucketSize)
	{
		AddDependency<Net::NetSystem>();
	}

	ConnectionManagerComponent::~ConnectionManagerComponent()
	{
	}


	// Initialize component
	Result ConnectionManagerComponent::InitializeComponent()
	{
		auto result = LibraryComponent::InitializeComponent();
		if (!result)
			return result;

		auto& memMgr = GetSystemHeap();
		auto pConnectionmanager = new(memMgr) Net::ConnectionManager(m_BucketSize);
		Service::ConnectionManager = pConnectionmanager;

		return result;
	}

	// Terminate component
	void ConnectionManagerComponent::DeinitializeComponent()
	{
		Service::ConnectionManager = nullptr;
		LibraryComponent::DeinitializeComponent();
	}

}


