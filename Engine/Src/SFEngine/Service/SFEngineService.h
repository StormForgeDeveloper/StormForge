////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine service
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Service/SFService.h"
#include "Service/SFEngineServices.h"





namespace SF {


	//////////////////////////////////////////////////////////////////////
	//
	//	Service base class
	//

	namespace Service
	{
		// Sample service
		//static ServiceInstance<SampleService> SampleService;

		extern ServiceInstance<ConnectionManagerService> ConnectionManager;
		extern ServiceInstance<EngineTaskService> EngineTaskManager;
		extern ServiceInstance<EngineObjectManagerService> EngineObjectManager;
		extern ServiceInstance<IGraphicDevice> GraphicDevice;
		extern ServiceInstance<NetSystemService> NetSystem;
		extern ServiceInstance<IAssetImporterFactory> AssetImporterFactory;
		extern ServiceInstance<IAssetSerializerFactory> AssetSerializerFactory;
		//extern ServiceInstance<IResourceManagerService> ResourceManager;

	};



}; // namespace SF

