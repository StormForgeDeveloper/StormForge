////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Task
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "EngineObject/SFEngineTask.h"



namespace SF {

	// Engine terminate task
	class EngineTask_Terminate : public EngineTask
	{
		using super = EngineTask;
    private:
        int m_ExitCode = 0;

	public:
		EngineTask_Terminate(int exitCode);

		virtual void Run() override;
	};

}; // namespace SF

