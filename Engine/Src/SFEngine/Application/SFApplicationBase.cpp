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

#include "Application/SFApplicationBase.h"


namespace SF
{
	ApplicationBase::ApplicationBase()
		: LibraryComponent("Application")
		, m_Heap("AppHeap", GetSystemHeap())
		, m_CommandQueue(GetHeap())
	{
	}

	ApplicationBase::~ApplicationBase()
	{

	}

	
	Result ApplicationBase::InitializeComponent()
	{
		LibraryComponent::InitializeComponent();

		m_IsPaused = false;

		return ResultCode::SUCCESS;
	}

	void ApplicationBase::DeinitializeComponent()
	{

		LibraryComponent::DeinitializeComponent();
	}




	AppTask::AppTask()
		: EngineTask(EngineTaskTick::SyncSystemTick)
	{

	}
}
