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
#include "Service/SFEngineService.h"
#include "SFEngine.h"

#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include "AndroidApp.h"
#include "AndroidAppTasks.h"


#include "Graphics/SFGraphicDeviceGLES.h"

#include <android/configuration.h>

//#include "Cube.h"

namespace SF
{

	AndroidAppTask::AndroidAppTask(ApplicationBase* app)
		: m_pApp((AndroidApp*)app)
	{

	}

	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask - tick
	//


	AndroidAppTask_UpdateLooper::AndroidAppTask_UpdateLooper(AndroidApp* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_UpdateLooper::Run()
	{
		int looperID;
		int events;
		AndroidApp* pApp = nullptr;


		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((looperID = ALooper_pollAll(pApp->IsPaused() ? -1 : 0, NULL, &events, (void**)&pApp)) >= 0)
		{
			Assert(GetApp() == pApp);

			if (looperID == AndroidApp::LOOPER_ID_INPUT)
			{
				GetApp()->ProcessInput();
			}
			// If a sensor has data, process it now.
			else if (looperID == AndroidApp::LOOPER_ID_SENSOR && GetApp()->GetSensorEventQueue() != nullptr)
			{
				ASensorEvent event;
				while (ASensorEventQueue_getEvents(GetApp()->GetSensorEventQueue(), &event, 1) > 0)
				{
					SFLog(System, Debug1, "accelerometer: x={0} y={1} z={2}",
						event.acceleration.x, event.acceleration.y,
						event.acceleration.z);
				}
			}

		}

	}



	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//


	AndroidAppTask_InputChanged::AndroidAppTask_InputChanged(ApplicationBase* app, AInputQueue* inputQueue)
		: AndroidAppTask(app)
		, m_InputQueue(inputQueue)
	{

	}

	void AndroidAppTask_InputChanged::Run()
	{
		if (GetApp()->GetInputQueue() != nullptr)
		{
			AInputQueue_detachLooper(GetApp()->GetInputQueue());
		}
		GetApp()->SetInputQueue(m_InputQueue);
		if (m_InputQueue != nullptr)
		{
			SFLog(System, Info, "Attaching input queue to looper");
			AInputQueue_attachLooper(m_InputQueue, GetApp()->GetLooper(), AndroidApp::LOOPER_ID_INPUT, NULL, GetApp());
		}
		else
		{
			SFLog(System, Info, "Input queue detached");
		}
	}


	AndroidAppTask_InitWindow::AndroidAppTask_InitWindow(ApplicationBase* app, ANativeWindow* pWindow)
		: AndroidAppTask(app)
		, m_Window(pWindow)
	{
	}

	AndroidAppTask_InitWindow::~AndroidAppTask_InitWindow()
	{
		if (m_Window != nullptr)
			ANativeWindow_release(m_Window);
	}

	void AndroidAppTask_InitWindow::Run()
	{
		if (m_Window != nullptr)
		{
			Service::GraphicDevice->InitDisplay(m_Window);
			m_Window = nullptr;
		}
	}


	AndroidAppTask_DestroyWindow::AndroidAppTask_DestroyWindow(ApplicationBase* app)
		: AndroidAppTask(app)
	{
	}

	void AndroidAppTask_DestroyWindow::Run()
	{
		Service::GraphicDevice->DeinitDisplay();
	}


	AndroidAppTask_WindowResized::AndroidAppTask_WindowResized(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_WindowResized::Run()
	{

	}


	AndroidAppTask_GainFocus::AndroidAppTask_GainFocus(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_GainFocus::Run()
	{
		GetApp()->SetPaused(false);

		if (GetApp()->GetAccelerometerSensor() == nullptr) return;

		ASensorEventQueue_enableSensor(GetApp()->GetSensorEventQueue(), GetApp()->GetAccelerometerSensor());
		// We'd like to get 60 events per second (in us).
		ASensorEventQueue_setEventRate(GetApp()->GetSensorEventQueue(), GetApp()->GetAccelerometerSensor(), (1000L / 60) * 1000);
	}


	AndroidAppTask_LostFocus::AndroidAppTask_LostFocus(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_LostFocus::Run()
	{
		GetApp()->SetPaused(true);

		if (GetApp()->GetAccelerometerSensor() == nullptr) return;
		
		ASensorEventQueue_disableSensor(GetApp()->GetSensorEventQueue(), GetApp()->GetAccelerometerSensor());
	}


	AndroidAppTask_LowMemory::AndroidAppTask_LowMemory(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_LowMemory::Run()
	{

	}


	AndroidAppTask_AppStart::AndroidAppTask_AppStart(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_AppStart::Run()
	{

	}


	AndroidAppTask_AppStop::AndroidAppTask_AppStop(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_AppStop::Run()
	{

	}


	AndroidAppTask_Pause::AndroidAppTask_Pause(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_Pause::Run()
	{
		GetApp()->SetPaused(true);
	}


	AndroidAppTask_Resume::AndroidAppTask_Resume(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_Resume::Run()
	{
		GetApp()->SetPaused(false);
	}


	AndroidAppTask_ConfigChanged::AndroidAppTask_ConfigChanged(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_ConfigChanged::Run()
	{
		AConfiguration_fromAssetManager(GetApp()->GetConfig(), GetApp()->GetAssetManager());
	}


	AndroidAppTask_SaveState::AndroidAppTask_SaveState(ApplicationBase* app)
		: AndroidAppTask(app)
	{

	}

	void AndroidAppTask_SaveState::Run()
	{
		// TODO::
	}


}

#else
void AndroidAppTask_Dummy() {}
#endif