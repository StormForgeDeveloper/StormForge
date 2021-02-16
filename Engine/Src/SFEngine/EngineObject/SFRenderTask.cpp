////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : RenderTask 
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "EngineObject/SFRenderTask.h"


namespace SF {

	
	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	RenderTask class -  interface for task operation
	//

	RenderTask::RenderTask(Object* pObject)
		: m_ObjectPtr(pObject)
	{

	}

	RenderTask::~RenderTask()
	{

	}

	void RenderTask::Run()
	{
		
	}


}; // namespace SF

