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


	EngineTask_Terminate::EngineTask_Terminate(int exitCode)
		: EngineTask(EngineTaskTick::SyncPostTick)
        , m_ExitCode(exitCode)
	{
        assert(exitCode >= 0);
	}

	void EngineTask_Terminate::Run()
	{
		Engine* pEngine = Engine::GetInstance();
		if (pEngine != nullptr)
			pEngine->SetExitCode(m_ExitCode);

		Finished();
	}

} // namespace SF
