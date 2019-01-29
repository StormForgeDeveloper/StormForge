////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineTask manager
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "EngineObject/SFEngineTask.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Service/SFEngineService.h"


namespace SF {

	template class SharedPointerT<EngineTask>;
	template class WeakPointerT<EngineTask>;

	
	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineTask class -  interface for task operation
	//

	EngineTask::EngineTask(EngineTaskTick taskTick)
		: m_TaskTick(taskTick)
		, m_Repeat(0)
	{
	}

	EngineTask::~EngineTask()
	{
		AssertRel(m_TaskManagerNode.pNext == nullptr && m_TaskManagerNode.pPrev == nullptr);
	}

	DoubleLinkedListNodeDataT<SharedPointerT<EngineTask>>& EngineTask::GetManagerListNode()
	{
		return m_TaskManagerNode;
	}

	void EngineTask::Dispose()
	{
		//m_ObjectPtr = WeakPointerT<EngineObject>();
		AssertRel(m_TaskManagerNode.pNext == nullptr && m_TaskManagerNode.pPrev == nullptr);
		AssertRel(m_TaskManagerNode.pNext != (DoubleLinkedListNode*)0xdddddddddddddddd && m_TaskManagerNode.pPrev != (DoubleLinkedListNode*)0xdddddddddddddddd);
		m_TaskManagerNode.Data = nullptr;
	}

	void EngineTask::Request()
	{
		Service::EngineTaskManager->AddTask(this);
	}

	void EngineTask::Run()
	{
	}


	void EngineTask::OnStarted()
	{
		//Service::EngineTaskManager->OnTaskStarted(this);
	}

	void EngineTask::OnFinished()
	{
		Service::EngineTaskManager->OnTaskFinished(this);
	}

	void EngineTask::OnCanceled()
	{
		Service::EngineTaskManager->OnTaskFinished(this);
	}


}; // namespace SF

