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

#if SF_PLATFORM == SF_PLATFORM_ANDROID


struct ANativeActivity;
struct AConfiguration;

namespace SF
{
	class AndroidApp;


	class AndroidAppTask : public AppTask
	{
	private:
		AndroidApp* m_pApp;

	public:
		AndroidAppTask(ApplicationBase* app);

		AndroidApp* GetApp() { return m_pApp; }
	};


	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask - tick
	//


	class AndroidAppTask_UpdateLooper : public AndroidAppTask
	{
	public:
		AndroidAppTask_UpdateLooper(AndroidApp* app);
		virtual void Run() override;
	};


	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//


	class AndroidAppTask_InputChanged : public AndroidAppTask
	{
	private:
		AInputQueue* m_InputQueue;

	public:
		AndroidAppTask_InputChanged(ApplicationBase* app, AInputQueue* inputQueue);
		virtual void Run() override;
	};


	class AndroidAppTask_InitWindow : public AndroidAppTask
	{
	private:
		ANativeWindow* m_Window;

	public:
		AndroidAppTask_InitWindow(ApplicationBase* app, ANativeWindow* pWindow);
		~AndroidAppTask_InitWindow();
		virtual void Run() override;
	};


	class AndroidAppTask_DestroyWindow : public AndroidAppTask
	{
	public:
		AndroidAppTask_DestroyWindow(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_WindowResized : public AndroidAppTask
	{
	public:
		AndroidAppTask_WindowResized(ApplicationBase* app);
		virtual void Run() override;
	};


	class AndroidAppTask_GainFocus : public AndroidAppTask
	{
	public:
		AndroidAppTask_GainFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_LostFocus : public AndroidAppTask
	{
	public:
		AndroidAppTask_LostFocus(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_LowMemory : public AndroidAppTask
	{
	public:
		AndroidAppTask_LowMemory(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_AppStart : public AndroidAppTask
	{
	public:
		AndroidAppTask_AppStart(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_AppStop : public AndroidAppTask
	{
	public:
		AndroidAppTask_AppStop(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_Pause : public AndroidAppTask
	{
	public:
		AndroidAppTask_Pause(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_Resume : public AndroidAppTask
	{
	public:
		AndroidAppTask_Resume(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_ConfigChanged : public AndroidAppTask
	{
	public:
		AndroidAppTask_ConfigChanged(ApplicationBase* app);
		virtual void Run() override;
	};

	class AndroidAppTask_SaveState : public AndroidAppTask
	{
	public:
		AndroidAppTask_SaveState(ApplicationBase* app);
		virtual void Run() override;
	};




}


#endif
