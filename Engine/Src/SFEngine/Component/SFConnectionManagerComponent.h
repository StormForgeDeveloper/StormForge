////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server Config
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Object/SFLibraryComponent.h"

#include "Service/SFEngineService.h"

#include "Zookeeper/SFZookeeper.h"
#include "ServerConfig/SFServerConfig.h"




namespace SF
{

	class ConnectionManagerComponent : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = "ConnectionManagerComponent";

	private:

		uint m_BucketSize;

	public:

		// Constructor
		ConnectionManagerComponent(uint bucketSize);
		~ConnectionManagerComponent();


		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize component
		virtual Result InitializeComponent() override;

		// Terminate component
		virtual void DeinitializeComponent() override;
	};
}

