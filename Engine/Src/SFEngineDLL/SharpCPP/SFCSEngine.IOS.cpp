////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#if SF_PLATFORM == SF_PLATFORM_IOS

#include "Application/IOS/IOSApp.h"
#include "Application/IOS/IOSAppTasks.h"


#include "Multithread/SFAsyncTaskManager.h"
#include "Util/SFLog.h"
#include "Util/SFLogComponent.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"
#include "Resource/SFResourceManager.h"
#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFEngineService.h"
#include "SFEngine.h"



//////////////////////////////////////////////////////////////////////////////////////
//
//	Engine interface
//

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngineWithLog(const char* processName, const char* logServerAddress, uint32_t globalLogMask)
{
	SF::LogMask logMask;
	logMask.Composited = std::numeric_limits<uint64_t>::max();
	logMask.SubChannelBits.Debug = 0;
	logMask.SubChannelBits.Debug1 = 0;
	logMask.SubChannelBits.Debug2 = 0;
	logMask.SubChannelBits.Debug3 = 0;

	SF::EngineInitParam initParam;
    initParam.GlobalLogOutputMask = SF::LogOutputMask(globalLogMask);
    initParam.LogOutputConsole = false;
	initParam.LogPrintMask = logMask.Composited;

    // Unity need to enable manually
    initParam.EnableCrashDump = true;

	if (!SF::StrUtil::IsNullOrEmpty(logServerAddress))
		initParam.LogServerAddress = logServerAddress;

	if (!SF::StrUtil::IsNullOrEmpty(processName))
		SF::Util::SetServiceName(processName);

	return SF::Engine::Start(initParam);
}

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngineWithGraphic(void* graphicContext)
{
	SF::EngineInitParam initParam;
	initParam.GraphicSystem = "Vulkan";
	initParam.LogOutputDebugger = false;
	return SF::Engine::Start(initParam);
}

SFDLL_EXPORT void SFEngine_NativeStopEngine()
{
	SF::Engine::Stop();
}

SFDLL_EXPORT void SFEngine_NativeFocused(bool focused)
{

}


SFDLL_EXPORT void SFEngine_NativeWindowCreated(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::IOSApp>();
	pApp->SendCommand<SF::IOSAppTask_InitWindow>((NativeWindow)nativeHandle);
}


SFDLL_EXPORT void SFEngine_NativeWindowClosed(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::IOSApp>();
	pApp->SendCommand<SF::IOSAppTask_DestroyWindow>();
}

SFDLL_EXPORT void SFEngine_NativeWindowResized()
{
	auto pApp = SF::Engine::GetEngineComponent<SF::IOSApp>();
	pApp->SendCommand<SF::IOSAppTask_WindowResized>();
}


#endif
