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

#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Android/AndroidApp.h"
#include "Application/Android/AndroidAppTasks.h"

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



	static void AppOnStart(ANativeActivity* activity) {
		SFLog(System, Debug, "Start: {0}", activity);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_AppStart>();
		pTask->Wait();
	}

	static void AppOnResume(ANativeActivity* activity) {
		SFLog(System, Debug, "Resume: {0}", activity);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_Resume>();
		pTask->Wait();
	}

	static void AppOnPause(ANativeActivity* activity) {
		SFLog(System, Debug, "Pause: {0}", activity);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_Pause>();
		pTask->Wait();
	}

	static void AppOnStop(ANativeActivity* activity) {
		SFLog(System, Debug, "Stop: {0}", activity);
		auto pApp = Engine::GetEngineComponent<AndroidApp >();
		auto pTask = pApp->SendCommand<AndroidAppTask_AppStop>();
		pTask->Wait();
	}

	static void* AppOnSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
		//struct android_app* android_app = (struct android_app*)activity->instance;
		void* savedState = NULL;

		SFLog(System, Debug, "SaveInstanceState: {0}", activity);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_SaveState>();
		pTask->Wait();
		//pthread_mutex_lock(&android_app->mutex);
		//android_app->stateSaved = 0;
		//android_app_write_cmd(android_app, APP_CMD_SAVE_STATE);
		//while (!android_app->stateSaved) {
		//	pthread_cond_wait(&android_app->cond, &android_app->mutex);
		//}

		//if (android_app->savedState != NULL) {
		//	savedState = android_app->savedState;
		//	*outLen = android_app->savedStateSize;
		//	android_app->savedState = NULL;
		//	android_app->savedStateSize = 0;
		//}

		//pthread_mutex_unlock(&android_app->mutex);

		return savedState;
	}

	static void AppOnConfigurationChanged(ANativeActivity* activity) {
		SFLog(System, Debug, "ConfigurationChanged: {0}", activity);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		pApp->SendCommand<AndroidAppTask_ConfigChanged>();
	}

	static void AppOnLowMemory(ANativeActivity* activity) {
		SFLog(System, Debug, "LowMemory: {0}", activity);
		auto pEngine = (Engine*)activity->instance;
		auto pApp = pEngine->GetComponent<AndroidApp>();
		pApp->SendCommand<AndroidAppTask_LowMemory>();
	}

	static void AppOnWindowFocusChanged(ANativeActivity* activity, int focused) {
		SFLog(System, Debug, "WindowFocusChanged: {0} -- {1}", activity, focused);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		if (focused)
			pApp->SendCommand<AndroidAppTask_GainFocus>();
		else
			pApp->SendCommand<AndroidAppTask_LostFocus>();
	}

	static void AppOnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
		SFLog(System, Debug, "NativeWindowCreated: {0} -- {1}\n", activity, window);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		ANativeWindow_acquire(window);
		auto pTask = pApp->SendCommand<AndroidAppTask_InitWindow>(window);
		pTask->Wait();
	}

	static void AppOnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
		SFLog(System, Debug, "NativeWindowDestroyed: {0} -- {1}", activity, window);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_DestroyWindow>();
		pTask->Wait();
	}

	static void AppOnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
		SFLog(System, Debug, "InputQueueCreated: {0} -- {1}", activity, queue);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_InputChanged>(queue);
		pTask->Wait();
	}

	static void AppOnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
		SFLog(System, Debug, "InputQueueDestroyed: {0} -- {1}", activity, queue);
		auto pApp = Engine::GetEngineComponent<AndroidApp>();
		auto pTask = pApp->SendCommand<AndroidAppTask_InputChanged>(nullptr);
		pTask->Wait();
	}

	static void AppOnDestroy(ANativeActivity* activity) {
		SFLog(System, Debug, "Destroy: {0}", activity);
		SF::Engine::Stop();
		activity->instance = nullptr;
	}
}



extern "C"
{
	// For native activity support
	void ANativeActivity_onCreate(ANativeActivity* activity,
		void* savedState, size_t savedStateSize) {
		//SFLog(System, Debug, "Creating: {0}", activity);
		activity->callbacks->onDestroy = SF::AppOnDestroy;
		activity->callbacks->onStart = SF::AppOnStart;
		activity->callbacks->onResume = SF::AppOnResume;
		activity->callbacks->onSaveInstanceState = SF::AppOnSaveInstanceState;
		activity->callbacks->onPause = SF::AppOnPause;
		activity->callbacks->onStop = SF::AppOnStop;
		activity->callbacks->onConfigurationChanged = SF::AppOnConfigurationChanged;
		activity->callbacks->onLowMemory = SF::AppOnLowMemory;
		activity->callbacks->onWindowFocusChanged = SF::AppOnWindowFocusChanged;
		activity->callbacks->onNativeWindowCreated = SF::AppOnNativeWindowCreated;
		activity->callbacks->onNativeWindowDestroyed = SF::AppOnNativeWindowDestroyed;
		activity->callbacks->onInputQueueCreated = SF::AppOnInputQueueCreated;
		activity->callbacks->onInputQueueDestroyed = SF::AppOnInputQueueDestroyed;

		SF::EngineInitParam initParam;
		initParam.Context = activity->assetManager;
		initParam.GraphicSystem = "Vulkan";
		activity->instance = SF::Engine::Start(initParam);
	}
}


namespace SF
{

	Engine* Engine::Start(const EngineInitParam& initParam)
	{
		AAssetManager* assetManager = (AAssetManager*)initParam.Context;

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

		pEngine->AddComponent<SF::AndroidApp>(assetManager);


		// Initialize base system first
		pEngine->InitializeComponents();

		return pEngine;
	}

	void Engine::Stop()
	{
		if (Engine::GetInstance() == nullptr)
			return;

		auto pApp = Engine::GetEngineComponent<AndroidApp>();

		EngineTaskPtr pInputTask = pApp->SendCommand<AndroidAppTask_InputChanged>(nullptr);
		EngineTaskPtr pTerminateTask = new(GetSystemHeap()) EngineTask_Terminate;
		pTerminateTask->Request();

		pInputTask->Wait();
		pTerminateTask->Wait();

		Engine::GetInstance()->DeinitializeComponents();
		Engine::GetInstance()->ClearComponents();
		GetSystemHeap().Delete(Engine::GetInstance());
	}

}

#else
void SFEngine_Android_Dummy() {}
#endif
