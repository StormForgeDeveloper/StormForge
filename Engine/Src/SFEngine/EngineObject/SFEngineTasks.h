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
	public:
		EngineTask_Terminate();

		virtual void Run() override;
	};

}; // namespace SF

