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

#if SF_PLATFORM == SF_PLATFORM_LINUX

#include "LinuxApp.h"
#include "LinuxAppTasks.h"


#include "Graphics/SFGraphicDeviceGLES.h"



//#include "Cube.h"

namespace SF
{

	LinuxAppTask::LinuxAppTask(ApplicationBase* app)
		: m_pApp((LinuxApp*)app)
	{

	}



	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//



	LinuxAppTask_InitWindow::LinuxAppTask_InitWindow(ApplicationBase* app, NativeWindow pWindow)
		: LinuxAppTask(app)
		, m_Window(pWindow)
	{
	}

	LinuxAppTask_InitWindow::~LinuxAppTask_InitWindow()
	{
		//if (m_Window != nullptr)
		//	ANativeWindow_release(m_Window);
	}

	void LinuxAppTask_InitWindow::Run()
	{
		if (m_Window != 0)
		{
			Service::GraphicDevice->InitDisplay(m_Window);
			m_Window = 0;
		}
	}


	LinuxAppTask_DestroyWindow::LinuxAppTask_DestroyWindow(ApplicationBase* app)
		: LinuxAppTask(app)
	{
	}

	void LinuxAppTask_DestroyWindow::Run()
	{
		Service::GraphicDevice->DeinitDisplay();
	}


	LinuxAppTask_WindowResized::LinuxAppTask_WindowResized(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_WindowResized::Run()
	{

	}


	LinuxAppTask_GainFocus::LinuxAppTask_GainFocus(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_GainFocus::Run()
	{
		GetApp()->SetPaused(false);

	}


	LinuxAppTask_LostFocus::LinuxAppTask_LostFocus(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_LostFocus::Run()
	{
		GetApp()->SetPaused(true);

	}


	LinuxAppTask_AppStart::LinuxAppTask_AppStart(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_AppStart::Run()
	{

	}


	LinuxAppTask_AppStop::LinuxAppTask_AppStop(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_AppStop::Run()
	{

	}


	LinuxAppTask_Pause::LinuxAppTask_Pause(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_Pause::Run()
	{
		GetApp()->SetPaused(true);
	}


	LinuxAppTask_Resume::LinuxAppTask_Resume(ApplicationBase* app)
		: LinuxAppTask(app)
	{

	}

	void LinuxAppTask_Resume::Run()
	{
		GetApp()->SetPaused(false);
	}



}

#else
void LinuxAppTask_Dummy() {}
#endif