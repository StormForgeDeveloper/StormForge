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


#pragma once

#include "Application/SFApplicationBase.h"

#if SF_PLATFORM == SF_PLATFORM_LINUX




namespace SF
{
	class LinuxApp;


	class LinuxAppTask : public AppTask
	{
	private:
		LinuxApp* m_pApp;

	public:
		LinuxAppTask(ApplicationBase* app);

		LinuxApp* GetApp() { return m_pApp; }
	};



	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//



	class LinuxAppTask_InitWindow : public LinuxAppTask
	{
	private:
		NativeWindow m_Window;

	public:
		LinuxAppTask_InitWindow(ApplicationBase* app, NativeWindow pWindow);
		~LinuxAppTask_InitWindow();
		virtual void Run() override;
	};


	class LinuxAppTask_DestroyWindow : public LinuxAppTask
	{
	public:
		LinuxAppTask_DestroyWindow(ApplicationBase* app);
		virtual void Run() override;
	};

	class LinuxAppTask_WindowResized : public LinuxAppTask
	{
	public:
		LinuxAppTask_WindowResized(ApplicationBase* app);
		virtual void Run() override;
	};


	class LinuxAppTask_GainFocus : public LinuxAppTask
	{
	public:
		LinuxAppTask_GainFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class LinuxAppTask_LostFocus : public LinuxAppTask
	{
	public:
		LinuxAppTask_LostFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class LinuxAppTask_AppStart : public LinuxAppTask
	{
	public:
		LinuxAppTask_AppStart(ApplicationBase* app);
		virtual void Run() override;
	};

	class LinuxAppTask_AppStop : public LinuxAppTask
	{
	public:
		LinuxAppTask_AppStop(ApplicationBase* app);
		virtual void Run() override;
	};

	class LinuxAppTask_Pause : public LinuxAppTask
	{
	public:
		LinuxAppTask_Pause(ApplicationBase* app);
		virtual void Run() override;
	};

	class LinuxAppTask_Resume : public LinuxAppTask
	{
	public:
		LinuxAppTask_Resume(ApplicationBase* app);
		virtual void Run() override;
	};



}


#endif
