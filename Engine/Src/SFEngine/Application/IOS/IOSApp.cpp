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


#include "SFEnginePCH.h"

#if SF_PLATFORM == SF_PLATFORM_IOS

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/IOS/IOSApp.h"
#include "Application/IOS/IOSAppTasks.h"


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
	constexpr StringCrc64 IOSApp::TypeName;

	IOSApp::IOSApp()
	{
	}

	IOSApp::~IOSApp()
	{

	}

	Result IOSApp::InitializeComponent()
	{
		ApplicationBase::InitializeComponent();

		return true;
	}

	void IOSApp::DeinitializeComponent()
	{
		ApplicationBase::DeinitializeComponent();
	}

	
}
#else
void IOSApp_Dummy() {}
#endif
