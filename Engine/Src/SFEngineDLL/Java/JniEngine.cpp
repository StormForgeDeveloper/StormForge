////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"

#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include <jni.h>
#include <android/configuration.h>
#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

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
//#include "Resource/SFResourceManager.h"
//#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFEngineService.h"


//#include "Cube.h"



extern "C"
{


	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	Engine interface
	//

	JNIEXPORT jlong JNICALL Java_com_SF_SFEngine_NativeStartEngine(JNIEnv* env, jobject thisActivity, AAssetManager* assetManager)
	{
		SF::EngineInitParam initParam;
		initParam.Context = assetManager;
		return (jlong)SF::Engine::Start(initParam);
	}

	JNIEXPORT jlong JNICALL Java_com_SF_SFEngine_NativeStartEngineEmpty(JNIEnv* env, jobject thisActivity)
	{
		SF::EngineInitParam initParam;

		return (jlong)SF::Engine::Start(initParam);
	}

	JNIEXPORT void JNICALL Java_com_SF_SFEngine_NativeStopEngine(JNIEnv* env, jobject thisActivity)
	{
		SF::Engine::Stop();
	}

	JNIEXPORT void JNICALL Java_com_SF_SFEngine_NativeConfigChanged(JNIEnv* env, jobject thisActivity, AConfiguration* newConfig)
	{
		auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
		pApp->SendCommand<SF::AndroidAppTask_ConfigChanged>();
	}

	JNIEXPORT void JNICALL Java_com_SF_SFEngine_NativeFocused(JNIEnv* env, jobject thisActivity, bool focused)
	{
		auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
		if (focused)
			pApp->SendCommand<SF::AndroidAppTask_GainFocus>();
		else
			pApp->SendCommand<SF::AndroidAppTask_LostFocus>();
	}

	JNIEXPORT void JNICALL Java_com_SF_SFEngine_NativeSurfaceCreated(JNIEnv* env, jobject thisActivity, jobject surface)
	{
		auto nativeWindow = ANativeWindow_fromSurface(env, surface);
		Assert(nativeWindow != nullptr);
		auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
		auto pTask = pApp->SendCommand<SF::AndroidAppTask_InitWindow>(nativeWindow);
		pTask->Wait();
	}
	
	JNIEXPORT void JNICALL Java_com_SF_SFEngine_NativeSurfaceDestroyed(JNIEnv* env, jobject thisActivity, jobject surface)
	{
		auto pApp = SF::Engine::GetEngineComponent<SF::AndroidApp>();
		auto pTask = pApp->SendCommand<SF::AndroidAppTask_DestroyWindow>();
		pTask->Wait();
	}



	
}

#endif

