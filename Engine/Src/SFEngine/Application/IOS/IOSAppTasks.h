////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic IOS application
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#if SF_PLATFORM == SF_PLATFORM_IOS

#include "Application/SFApplicationBase.h"




namespace SF
{
	class IOSApp;


	class IOSAppTask : public AppTask
	{
	private:
		IOSApp* m_pApp;

	public:
		IOSAppTask(ApplicationBase* app);

		IOSApp* GetApp() { return m_pApp; }
	};


	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//



	class IOSAppTask_InitWindow : public IOSAppTask
	{
	private:
		NativeWindow m_Window;

	public:
		IOSAppTask_InitWindow(ApplicationBase* app, NativeWindow pWindow);
		~IOSAppTask_InitWindow();
		virtual void Run() override;
	};


	class IOSAppTask_DestroyWindow : public IOSAppTask
	{
	public:
		IOSAppTask_DestroyWindow(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_WindowResized : public IOSAppTask
	{
	public:
		IOSAppTask_WindowResized(ApplicationBase* app);
		virtual void Run() override;
	};


	class IOSAppTask_GainFocus : public IOSAppTask
	{
	public:
		IOSAppTask_GainFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_LostFocus : public IOSAppTask
	{
	public:
		IOSAppTask_LostFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_LowMemory : public IOSAppTask
	{
	public:
		IOSAppTask_LowMemory(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_AppStart : public IOSAppTask
	{
	public:
		IOSAppTask_AppStart(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_AppStop : public IOSAppTask
	{
	public:
		IOSAppTask_AppStop(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_Pause : public IOSAppTask
	{
	public:
		IOSAppTask_Pause(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_Resume : public IOSAppTask
	{
	public:
		IOSAppTask_Resume(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_ConfigChanged : public IOSAppTask
	{
	public:
		IOSAppTask_ConfigChanged(ApplicationBase* app);
		virtual void Run() override;
	};

	class IOSAppTask_SaveState : public IOSAppTask
	{
	public:
		IOSAppTask_SaveState(ApplicationBase* app);
		virtual void Run() override;
	};


	class IOSAppTask_Terminate : public IOSAppTask
	{
	public:
		IOSAppTask_Terminate(ApplicationBase* app);
		~IOSAppTask_Terminate() {}
		virtual void Run() override;
	};


}

#endif
