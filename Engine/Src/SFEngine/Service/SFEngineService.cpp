////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Service
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Util/SFLog.h"
#include "Service/SFService.h"

#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLogComponent.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"

#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
//#include "Resource/SFResourceManager.h"
//#include "Graphics/SFGraphicDeviceGLES.h"
#include "Graphics/SFRenderCommand.h"


namespace SF {

	namespace Service
	{
		ServiceInstance<ConnectionManagerService> ConnectionManager;
		ServiceInstance<EngineTaskService> EngineTaskManager;
		ServiceInstance<EngineObjectManagerService> EngineObjectManager;
		ServiceInstance<IGraphicDevice> GraphicDevice;
		ServiceInstance<NetSystemService> NetSystem;
		ServiceInstance<IAssetImporterFactory> AssetImporterFactory;
		ServiceInstance<IAssetSerializerFactory> AssetSerializerFactory;
		//ServiceInstance<IResourceManagerService> ResourceManager;

		ServiceInstance<VariableFactoryService> VariableFactory;
	}


}; // namespace SF

