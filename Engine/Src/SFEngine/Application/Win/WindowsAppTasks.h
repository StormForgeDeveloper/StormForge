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


#pragma once

#include "Application/SFApplicationBase.h"


struct ANativeActivity;
struct AConfiguration;

namespace SF
{
	class WindowsApp;


	class WindowsAppTask : public AppTask
	{
	private:
		WindowsApp* m_pApp;

	public:
		WindowsAppTask(ApplicationBase* app);

		WindowsApp* GetApp() { return m_pApp; }
	};


	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask - tick
	//


	class WindowsAppTask_UpdateLooper : public WindowsAppTask
	{
	public:
		WindowsAppTask_UpdateLooper(WindowsApp* app);
		virtual void Run() override;
	};


	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//



	class WindowsAppTask_InitWindow : public WindowsAppTask
	{
	private:
		NativeWindow m_Window;

	public:
		WindowsAppTask_InitWindow(ApplicationBase* app, NativeWindow pWindow);
		~WindowsAppTask_InitWindow();
		virtual void Run() override;
	};


	class WindowsAppTask_DestroyWindow : public WindowsAppTask
	{
	public:
		WindowsAppTask_DestroyWindow(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_WindowResized : public WindowsAppTask
	{
	public:
		WindowsAppTask_WindowResized(ApplicationBase* app);
		virtual void Run() override;
	};


	class WindowsAppTask_GainFocus : public WindowsAppTask
	{
	public:
		WindowsAppTask_GainFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_LostFocus : public WindowsAppTask
	{
	public:
		WindowsAppTask_LostFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_LowMemory : public WindowsAppTask
	{
	public:
		WindowsAppTask_LowMemory(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_AppStart : public WindowsAppTask
	{
	public:
		WindowsAppTask_AppStart(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_AppStop : public WindowsAppTask
	{
	public:
		WindowsAppTask_AppStop(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_Pause : public WindowsAppTask
	{
	public:
		WindowsAppTask_Pause(ApplicationBase* app);
		virtual void Run() override;
	};

	class WindowsAppTask_Resume : public WindowsAppTask
	{
	public:
		WindowsAppTask_Resume(ApplicationBase* app);
		virtual void Run() override;
	};

}

