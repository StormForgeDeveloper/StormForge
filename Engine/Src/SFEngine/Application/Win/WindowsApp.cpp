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


#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLog.h"
#include "Util/SFLogComponent.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"
#include "Resource/SFResourceManager.h"
#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFEngineService.h"




namespace SF
{
	constexpr FixedString WindowsApp::TypeName;

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
