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

	class ModuleTestLimits_impl
	{
	public:
		ModuleTestLimits_impl()
		{
			SFLog(System, Info, "Testing system limits");

			rlimit limit;
			memset(&limit, 0, sizeof limit);
			if (getrlimit(RLIMIT_RTPRIO, &limit) != 0)
			{
				SFLog(System, Info, "Failed to get rtpio limits:{0}", std::strerror(errno));
			}

			unsigned int rrMax = (unsigned)sched_get_priority_max(SCHED_RR);
			if (rrMax > limit.rlim_cur || rrMax > limit.rlim_max)
			{
				SFLog(System, Info, "rtpio RR Required limit: min:{0}, max:{1}", (int)sched_get_priority_min(SCHED_RR), (int)rrMax);
			}

			unsigned int fifoMax = (unsigned)sched_get_priority_max(SCHED_FIFO);
			if (fifoMax > limit.rlim_cur || fifoMax > limit.rlim_max)
			{
				SFLog(System, Info, "rtpio FIFO Required limit: min:{0}, max:{1}", (int)sched_get_priority_min(SCHED_FIFO), (int)fifoMax);
			}

			if (getrlimit(RLIMIT_CORE, &limit) != 0)
			{
				SFLog(System, Info, "Failed to get RLIMIT_CORE limits:{0}", std::strerror(errno));
			}
			else
			{
				SFLog(System, Info, "RLIMIT_CORE limits: cur:{0}, max{1}", limit.rlim_cur, limit.rlim_max);
			}

			if (getrlimit(RLIMIT_FSIZE, &limit) != 0)
			{
				SFLog(System, Info, "Failed to get RLIMIT_FSIZE limits:{0}", std::strerror(errno));
			}
			else
			{
				SFLog(System, Info, "RLIMIT_FSIZE limits: cur:{0}, max{1}", limit.rlim_cur, limit.rlim_max);
			}
		}
	};


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
#if SF_USE_VULKAN
			pEngine->AddComponent<SF::VulkanSystem>();
			pEngine->AddComponent<SF::GraphicDeviceComponent<SF::GraphicDeviceVulkan>>();
#endif
		}

		pEngine->AddComponent<SF::LinuxApp>();


		// Initialize base system first
		pEngine->InitializeComponents();

		ModuleTestLimits_impl CheckLimits;

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
