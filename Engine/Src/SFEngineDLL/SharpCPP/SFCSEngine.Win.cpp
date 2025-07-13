////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Win/WindowsApp.h"
#include "Application/Win/WindowsAppTasks.h"

#include "Service/SFLogService.h"
#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLog.h"
#include "Util/SFLogComponent.h"
#include "Util/SFStrUtil.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFStrUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
#include "Resource/SFResourceManager.h"
#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFServices.h"
#include "Service/SFEngineService.h"
#include "SFEngine.h"



//////////////////////////////////////////////////////////////////////////////////////
//
//	Engine interface
//

static std::unique_ptr<SF::Mutex> g_InstanceMutex;
static int g_InstanceId = 0;

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngineWithLog(const char* processName, const char* logServerAddress, const char* logFilePrefix, uint32_t globalLogMask)
{
	SF::LogOutputMask logOutputMask(globalLogMask);

	SF::EngineInitParam initParam;

    SF::Log::Net.SetChannelLogLevel(SF::ELogLevel::Log);

	initParam.EnableMemoryLeakDetection = false;
    // Unity need to enable manually
    initParam.EnableCrashDump = false;

	char instanceNameBuffer[128];
	if (g_InstanceMutex == nullptr)
	{
		for (int instanceId = 0; instanceId < 10; instanceId++)
		{
			SF::StrUtil::Format(instanceNameBuffer, "{0}_{1}", processName, instanceId);
			auto instanceMutex = new SF::Mutex(instanceNameBuffer);
			if (GetLastError() != ERROR_ALREADY_EXISTS)
			{
				processName = instanceNameBuffer;
				g_InstanceMutex.reset(instanceMutex);
				g_InstanceId = instanceId;
				break;
			}
			else
			{
				delete instanceMutex;
			}
		}
	}
	else
	{
		SF::StrUtil::Format(instanceNameBuffer, "{0}_{1}", processName, g_InstanceId);
		processName = instanceNameBuffer;
	}

	srand(clock());
	initParam.GlobalLogOutputMask = logOutputMask;
	initParam.LogOutputConsole = SF::LogOutputMask(0);

    if (SF::StrUtil::IsNullOrEmpty(logFilePrefix))
    {
        initParam.LogOutputFile = SF::LogOutputMask(0);
    }
    else
    {
        initParam.LogOutputFile = SF::LogOutputMask();
        initParam.LogFilePrefix = logFilePrefix;
    }

	if (!SF::StrUtil::IsNullOrEmpty(logServerAddress))
	{
		initParam.LogServerAddress = logServerAddress;
		initParam.LogOutputLogServer = SF::LogOutputMask(uint32_t(-1));
	}

	if (!SF::StrUtil::IsNullOrEmpty(processName))
		SF::Util::SetServiceName(processName);

	// For stress test
	initParam.AsyncTaskThreadCount = 6;
	initParam.NetworkThreadCount = 4;

    SF::Engine* pEngine = SF::Engine::Start(initParam);
	return pEngine;
}

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngineWithGraphic(void* context)
{
	SF::EngineInitParam initParam;
#ifdef _DEBUG
	initParam.EnableMemoryLeakDetection = true;
#else
	initParam.EnableMemoryLeakDetection = false;
#endif

	initParam.LogOutputConsole = false;
	initParam.GraphicSystem = "Vulkan";
	auto pEngine = SF::Engine::Start(initParam);
	return pEngine;
}

SFDLL_EXPORT void SFEngine_NativeStopEngine()
{
	SF::Engine::Stop();
}

SFDLL_EXPORT void SFEngine_NativeFocused(bool focused)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	if (focused)
		pApp->SendCommand<SF::WindowsAppTask_GainFocus>();
	else
		pApp->SendCommand<SF::WindowsAppTask_LostFocus>();
}


SFDLL_EXPORT void SFEngine_NativeWindowCreated(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	pApp->SendCommand<SF::WindowsAppTask_InitWindow>((NativeWindow)nativeHandle);
}


SFDLL_EXPORT void SFEngine_NativeWindowClosed(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	pApp->SendCommand<SF::WindowsAppTask_DestroyWindow>();
}


SFDLL_EXPORT void SFEngine_NativeWindowResized()
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	pApp->SendCommand<SF::WindowsAppTask_WindowResized>();
}

#endif
