////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"

#if SF_PLATFORM == SF_PLATFORM_ANDROID


#include "AndroidApp.h"
#include "AndroidAppTasks.h"


#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLog.h"
#include "Util/SFLogComponent.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
#include "Resource/SFResourceManager.h"
#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFEngineService.h"




namespace SF
{
	constexpr StringCrc64 AndroidApp::TypeName;

	AndroidApp::AndroidApp(AAssetManager* assetManager)
		: m_Looper(nullptr)
		, m_InputQueue(nullptr)
		, m_Config(nullptr)
		, m_AssetManager(assetManager)
		, m_SensorManager(nullptr)
		, m_AccelerometerSensor(nullptr)
		, m_SensorEventQueue(nullptr)
	{
	}

	AndroidApp::~AndroidApp()
	{

	}

	Result AndroidApp::InitializeComponent()
	{
		ApplicationBase::InitializeComponent();

		m_Config = AConfiguration_new();
		//AConfiguration_fromAssetManager(m_Config, m_AssetManager);

		m_Looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
		//ALooper_addFd(m_Looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL, this);

		m_SensorManager = ASensorManager_getInstance();
		m_AccelerometerSensor = ASensorManager_getDefaultSensor(m_SensorManager, ASENSOR_TYPE_ACCELEROMETER);
		m_SensorEventQueue = ASensorManager_createEventQueue(m_SensorManager, m_Looper, LOOPER_ID_SENSOR, NULL, NULL);


		return true;
	}

	void AndroidApp::DeinitializeComponent()
	{
		ApplicationBase::DeinitializeComponent();

		if (m_InputQueue != nullptr) {
			AInputQueue_detachLooper(m_InputQueue);
		}
		AConfiguration_delete(m_Config);
	}


	void AndroidApp::ProcessInput()
	{
		AInputEvent* event = NULL;
		while (AInputQueue_getEvent(m_InputQueue, &event) >= 0) {

			if (AInputQueue_preDispatchEvent(m_InputQueue, event))
			{
				continue;
			}

			int32_t handled = 0;
			auto inputSource = AInputEvent_getSource(event);

			if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY)
			{
				auto keyAction = AKeyEvent_getAction(event);
				auto flags = AKeyEvent_getFlags(event);
				auto keyCode = AKeyEvent_getKeyCode(event);
				handled = HandleKeyInput(inputSource, keyAction, flags, keyCode);
			}
			else
			{
				auto motionAction = AMotionEvent_getAction(event);
				auto flags = AMotionEvent_getFlags(event);
				auto buttonState = AMotionEvent_getButtonState(event);
				float x = AMotionEvent_getXOffset(event);
				float y = AMotionEvent_getYOffset(event);
				// Motion event
				handled = HandleInput(inputSource, motionAction, flags, buttonState, x, y);
			}

			AInputQueue_finishEvent(m_InputQueue, event, handled);
		}
	}


	void AndroidApp::ProcessSensor()
	{
		if (m_AccelerometerSensor == nullptr) return;

		ASensorEvent event;
		while (ASensorEventQueue_getEvents(m_SensorEventQueue, &event, 1) > 0)
		{
			SFLog(System, Debug, "accelerometer: x={0} y={1} z={2}", event.acceleration.x, event.acceleration.y, event.acceleration.z);
		}
	}



}

#else
void AndroidApp_Dummy() {}
#endif
