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

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#include "WindowsApp.h"
#include "WindowsAppTasks.h"
#include "Util/SFLog.h"




namespace SF
{
	constexpr StringCrc64 WindowsApp::TypeName;

	WindowsApp::WindowsApp()
	{
	}

	WindowsApp::~WindowsApp()
	{

	}

	Result WindowsApp::InitializeComponent()
	{
		ApplicationBase::InitializeComponent();

		return true;
	}

	void WindowsApp::DeinitializeComponent()
	{
		ApplicationBase::DeinitializeComponent();
	}


	void WindowsApp::ProcessInput()
	{
	}


	void WindowsApp::ProcessSensor()
	{
	}

	
}

#else
void WindowsApp_Dummy() {}
#endif
