////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Andrond engine main
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"

#if SF_PLATFORM == SF_PLATFORM_LINUX

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Linux/LinuxApp.h"
#include "Application/Linux/LinuxAppTasks.h"

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
		if (Engine::GetInstance() != nullptr)
			return Engine::GetInstance();


		auto pEngine = new(GetSystemHeap()) SF::Engine;
		pEngine->m_InitParameter = initParam;
		pEngine->RegisterBasicComponents();

		if (initParam.GraphicSystem != nullptr)
		{
			pEngine->AddComponent<SF::ResourceManagerComponent>();
#if HAVE_VULKAN
			pEngine->AddComponent<SF::VulkanSystem>();
			pEngine->AddComponent<SF::GraphicDeviceComponent<SF::GraphicDeviceVulkan>>();
#endif
		}

		pEngine->AddComponent<SF::LinuxApp>();


		// Initialize base system first
		pEngine->InitializeComponents();

		return pEngine;
	}

	void Engine::Stop()
	{
		if (Engine::GetInstance() == nullptr)
			return;

		auto pApp = Engine::GetEngineComponent<LinuxApp>();

		EngineTaskPtr pTerminateTask = new(GetSystemHeap()) EngineTask_Terminate;
		pTerminateTask->Request();

		pTerminateTask->Wait();

		Engine::GetInstance()->DeinitializeComponents();
		Engine::GetInstance()->ClearComponents();
		GetSystemHeap().Delete(Engine::GetInstance());
	}

}

#else
void SFEngine_Linux_Dummy() {}
#endif
