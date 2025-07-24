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

#if SF_PLATFORM == SF_PLATFORM_LINUX


#include "LinuxApp.h"
#include "LinuxAppTasks.h"


#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLog.h"
#include "Util/SFLogComponent.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
//#include "Resource/SFResourceManager.h"
//#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFEngineService.h"




namespace SF
{
	constexpr StringCrc64 LinuxApp::TypeName;

	LinuxApp::LinuxApp()
	{
	}

	LinuxApp::~LinuxApp()
	{

	}

	Result LinuxApp::InitializeComponent()
	{
		ApplicationBase::InitializeComponent();


		return true;
	}

	void LinuxApp::DeinitializeComponent()
	{
		ApplicationBase::DeinitializeComponent();

	}


	void LinuxApp::ProcessInput()
	{
	}




}

#else
void LinuxApp_Dummy() {}
#endif
