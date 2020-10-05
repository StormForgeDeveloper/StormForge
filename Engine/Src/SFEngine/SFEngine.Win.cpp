////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine main Windows
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Win/WindowsApp.h"
#include "Application/Win/WindowsAppTasks.h"

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


		if (initParam.GraphicSystem != nullptr)
		{
			pEngine->AddComponent<SF::ResourceManagerComponent>();
			pEngine->AddComponent<SF::AssetImporterFactoryComponent>();
			pEngine->AddComponent<SF::AssetSerializerFactoryComponent>();

#if HAVE_VULKAN
			pEngine->AddComponent<SF::VulkanSystem>();
			pEngine->AddComponent<SF::GraphicDeviceComponent<SF::GraphicDeviceVulkan>>();
#endif
		}

		pEngine->AddComponent<SF::WindowsApp>();

		pEngine->InitializeComponents();

		return pEngine;
	}

	void Engine::Stop()
	{
		// Skip if stop is called twice
		if (Engine::GetInstance() == nullptr)
			return;

		auto pApp = Engine::GetEngineComponent<WindowsApp>();
		if (pApp == nullptr)
			return;

		EngineTaskPtr pTask = new(GetSystemHeap()) EngineTask_Terminate;
		pTask->Request();
		pTask->Wait();


		Engine::GetInstance()->DeinitializeComponents();
		Engine::GetInstance()->ClearComponents();
		GetSystemHeap().Delete(Engine::GetInstance());
	}


}

#else
void SFEngine_Win_Dummy() {}
#endif
