////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic windows application
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "WindowsApp.h"
#include "WindowsAppTasks.h"
#include "Service/SFEngineService.h"
#include "SFEngine.h"
#include "Graphics/SFGraphicDeviceGLES.h"


#if SF_PLATFORM == SF_PLATFORM_WINDOWS


namespace SF
{

	WindowsAppTask::WindowsAppTask(ApplicationBase* app)
		: m_pApp((WindowsApp*)app)
	{

	}

	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask - tick
	//


	WindowsAppTask_UpdateLooper::WindowsAppTask_UpdateLooper(WindowsApp* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_UpdateLooper::Run()
	{
		//int looperID;
		//int events;
		//WindowsApp* pApp = nullptr;


		//// If not animating, we will block forever waiting for events.
		//// If animating, we loop until all events are read, then continue
		//// to draw the next frame of animation.
		//while ((looperID = ALooper_pollAll(pApp->IsPaused() ? -1 : 0, NULL, &events, (void**)&pApp)) >= 0)
		//{
		//	Assert(GetApp() == pApp);

		//	if (looperID == AndroidApp::LOOPER_ID_INPUT)
		//	{
		//		GetApp()->ProcessInput();
		//	}
		//	// If a sensor has data, process it now.
		//	else if (looperID == AndroidApp::LOOPER_ID_SENSOR && GetApp()->GetSensorEventQueue() != nullptr)
		//	{
		//		ASensorEvent event;
		//		while (ASensorEventQueue_getEvents(GetApp()->GetSensorEventQueue(), &event, 1) > 0)
		//		{
		//			SFLog(System, Debug1, "accelerometer: x={0} y={1} z={2}",
		//				event.acceleration.x, event.acceleration.y,
		//				event.acceleration.z);
		//		}
		//	}

		//}

	}



	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//



	WindowsAppTask_InitWindow::WindowsAppTask_InitWindow(ApplicationBase* app, NativeWindow pWindow)
		: WindowsAppTask(app)
		, m_Window(pWindow)
	{
	}

	WindowsAppTask_InitWindow::~WindowsAppTask_InitWindow()
	{
		//if (m_Window != nullptr)
		//	ANativeWindow_release(m_Window);
	}

	void WindowsAppTask_InitWindow::Run()
	{
		if (m_Window != nullptr)
		{
			Service::GraphicDevice->InitDisplay(m_Window);
			m_Window = nullptr;
		}
	}


	WindowsAppTask_DestroyWindow::WindowsAppTask_DestroyWindow(ApplicationBase* app)
		: WindowsAppTask(app)
	{
	}

	void WindowsAppTask_DestroyWindow::Run()
	{
		Service::GraphicDevice->DeinitDisplay();
	}


	WindowsAppTask_WindowResized::WindowsAppTask_WindowResized(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_WindowResized::Run()
	{
		Service::GraphicDevice->OnResize();
	}


	WindowsAppTask_GainFocus::WindowsAppTask_GainFocus(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_GainFocus::Run()
	{
		GetApp()->SetPaused(false);

		//if (GetApp()->GetAccelerometerSensor() == nullptr) return;

		//ASensorEventQueue_enableSensor(GetApp()->GetSensorEventQueue(), GetApp()->GetAccelerometerSensor());
		//// We'd like to get 60 events per second (in us).
		//ASensorEventQueue_setEventRate(GetApp()->GetSensorEventQueue(), GetApp()->GetAccelerometerSensor(), (1000L / 60) * 1000);
	}


	WindowsAppTask_LostFocus::WindowsAppTask_LostFocus(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_LostFocus::Run()
	{
		GetApp()->SetPaused(true);

		//if (GetApp()->GetAccelerometerSensor() == nullptr) return;
		//
		//ASensorEventQueue_disableSensor(GetApp()->GetSensorEventQueue(), GetApp()->GetAccelerometerSensor());
	}


	WindowsAppTask_LowMemory::WindowsAppTask_LowMemory(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_LowMemory::Run()
	{

	}


	WindowsAppTask_AppStart::WindowsAppTask_AppStart(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_AppStart::Run()
	{

	}


	WindowsAppTask_AppStop::WindowsAppTask_AppStop(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_AppStop::Run()
	{

	}


	WindowsAppTask_Pause::WindowsAppTask_Pause(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_Pause::Run()
	{
		GetApp()->SetPaused(true);
	}


	WindowsAppTask_Resume::WindowsAppTask_Resume(ApplicationBase* app)
		: WindowsAppTask(app)
	{

	}

	void WindowsAppTask_Resume::Run()
	{
		GetApp()->SetPaused(false);
	}




}

#else
void WindowsAppTasks_Dummy() {}
#endif
