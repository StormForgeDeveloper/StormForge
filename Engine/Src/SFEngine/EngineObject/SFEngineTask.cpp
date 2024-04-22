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
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
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
		// NOTE: It is better to be cleared, but it is not a big deal
		//assert(m_TaskTick == EngineTaskTick::None);

		AssertRel(m_TaskManagerNode.pNext == nullptr && m_TaskManagerNode.pPrev == nullptr);
		//AssertRel(m_TaskManagerNode.pNext != (DoubleLinkedListNode*)0xdddddddddddddddd && m_TaskManagerNode.pPrev != (DoubleLinkedListNode*)0xdddddddddddddddd);
		m_TaskManagerNode.Data = nullptr;
	}

	Result EngineTask::Request()
	{
		return Service::EngineTaskManager->AddTask(this);
	}

	void EngineTask::Finished()
	{
		SetTickGroup(EngineTaskTick::None);
		super::Finished();
	}

	void EngineTask::Run()
	{
	}

    void EngineTask::Wait()
    {
        if (m_TaskManagerNode.IsInAnyList())
        {
            super::Wait();
        }
    }

    bool EngineTask::Wait(DurationMS waitTime)
    {
        if (m_TaskManagerNode.IsInAnyList())
        {
            return super::Wait(waitTime);
        }

        return true;
    }

	//void EngineTask::OnStarted()
	//{
	//	//Service::EngineTaskManager->OnTaskStarted(this);
	//}

	//void EngineTask::OnFinished()
	//{
	//	//Service::EngineTaskManager->OnTaskFinished(this);
	//}

	//void EngineTask::OnCanceled()
	//{
	//	//Service::EngineTaskManager->OnTaskFinished(this);
	//}


} // namespace SF

