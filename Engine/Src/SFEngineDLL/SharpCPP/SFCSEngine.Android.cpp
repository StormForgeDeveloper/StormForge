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

#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Android/AndroidApp.h"
#include "Application/Android/AndroidAppTasks.h"


#include "Task/SFAsyncTaskManager.h"
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





//////////////////////////////////////////////////////////////////////////////////////
//
//	Engine interface
//

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngineEmpty()
{
	SF::LogChannelParameter logChannelParameter;
	logChannelParameter.SubChannelMask.Debug = 0;
	logChannelParameter.SubChannelMask.Debug1 = 0;
	logChannelParameter.SubChannelMask.Debug2 = 0;
	logChannelParameter.SubChannelMask.Debug3 = 0;

	SF::EngineInitParam initParam;
	initParam.LogOutputDebugger = false;
	initParam.LogChannel = logChannelParameter;
	return SF::Engine::Start(initParam);
}

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngine(AAssetManager* assetManager)
{
	SF::EngineInitParam initParam;
	initParam.Context = assetManager;
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
	auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
	if (focused)
		pApp->SendCommand<SF::AndroidAppTask_GainFocus>();
	else
		pApp->SendCommand<SF::AndroidAppTask_LostFocus>();
}


SFDLL_EXPORT void SFEngine_NativeWindowCreated(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
	pApp->SendCommand<SF::AndroidAppTask_InitWindow>((NativeWindow)nativeHandle);
}


SFDLL_EXPORT void SFEngine_NativeWindowClosed(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
	pApp->SendCommand<SF::AndroidAppTask_DestroyWindow>();
}


SFDLL_EXPORT void SFEngine_NativeWindowResized()
{
	auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
	pApp->SendCommand<SF::AndroidAppTask_WindowResized>();
}


#endif

