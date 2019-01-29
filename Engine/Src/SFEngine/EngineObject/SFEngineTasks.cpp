////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Task
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "EngineObject/SFEngineTasks.h"
#include "SFEngine.h"


namespace SF {


	EngineTask_Terminate::EngineTask_Terminate()
		: EngineTask(EngineTaskTick::SyncPostTick)
	{

	}

	void EngineTask_Terminate::Run()
	{
		auto pEngine = Engine::GetInstance();
		if (pEngine != nullptr)
			pEngine->SetExitCode(0);
	}


}; // namespace SF

