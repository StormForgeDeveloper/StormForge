////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine main IOS
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"

#if SF_PLATFORM == SF_PLATFORM_IOS

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/IOS/IOSApp.h"
#include "Application/IOS/IOSAppTasks.h"

#include "Task/SFAsyncTaskManager.h"
#include "Object/SFObjectManager.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"

#include "Graphics/SFGraphicDeviceVulkan.h"
#include "Graphics/SFRenderCommand.h"
#include "Resource/SFResourceManager.h"

#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "EngineObject/SFEngineTasks.h"

#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"

#include "Asset/Importer/SFAssetImporterFactory.h"
#include "Asset/Serializer/SFAssetSerializerFactory.h"





namespace SF
{

	Engine* Engine::Start(const EngineInitParam& initParam)
	{
		// Prevent multiple initialization
		if (Engine::GetInstance() != nullptr)
			return Engine::GetInstance();

		auto pEngine = new(GetSystemHeap()) SF::Engine;
		pEngine->m_InitParameter = initParam;
		pEngine->RegisterBasicComponents();

		if (initParam.GraphicSystem != 0)
		{
			pEngine->AddComponent<SF::ResourceManagerComponent>();
			pEngine->AddComponent<SF::GraphicDeviceGLES>();
		}

		pEngine->AddComponent<SF::IOSApp>();

		pEngine->InitializeComponents();

		return pEngine;
	}

	void Engine::Stop()
	{
		// Skip if stop is called twice
		if (Engine::GetInstance() == nullptr)
			return;

		auto pApp = Engine::GetEngineComponent<IOSApp>();
		if (pApp == nullptr)
			return;

		EngineTaskPtr pTerminateTask = new(GetSystemHeap()) EngineTask_Terminate;
		pTerminateTask->Request();
		pTerminateTask->Wait();

		Engine::GetInstance()->DeinitializeComponents();
		Engine::GetInstance()->ClearComponents();
		GetSystemHeap().Delete(Engine::GetInstance());
	}


}

#else
void SFEngine_IOS_Dummy() {}
#endif
