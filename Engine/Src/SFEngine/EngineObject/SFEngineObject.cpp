////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "Util/SFStrUtil.h"
#include "EngineObject/SFEngineObject.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"



namespace SF {

	template class SharedPointerT<EngineObject>;



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineObjectAsyncEngineTask class -  interface for task operation
	//


	EngineObjectAsyncEngineTask::EngineObjectAsyncEngineTask(EngineObject* pObj, EngineTaskTick taskTick)
		: EngineTask(taskTick)
		, m_ObjectPtr(pObj)
	{

	}

	void EngineObjectAsyncEngineTask::ClearObject()
	{
		m_ObjectPtr = nullptr;// = WeakPointerT<EngineObject>();
	}

	void EngineObjectAsyncEngineTask::Run()
	{
		EngineObject* objectPtr = m_ObjectPtr;
		if (objectPtr == nullptr)
		{
			m_ObjectPtr = nullptr;// WeakPointerT<EngineObject>();
			return;
		}

		objectPtr->OnTick(GetTickGroup());
	}

	void EngineObjectAsyncEngineTask::NotifyTicked()
	{
		assert(m_TaskTickedHandlers.size() > 0);
		super::NotifyTicked();
	}


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineObject class -  interface for task operation
	//


	// Constructor
	EngineObject::EngineObject(IHeap* heap, const StringCrc64& name)
		: Object(heap, name)
		, m_TickFlags(0)
		, m_ActuallyRegistered(false)
		, m_ManagerListNodes(this)
		, m_ComponentManager(GetHeap())
	{
		for (int iNode = 0; iNode < (int)EngineTaskTick::Max; iNode++)
		{
			m_ListNodes[iNode].Data = this;
		}
	}

	EngineObject::~EngineObject()
	{
		// The object need to be unregistered from the task manager
		Assert(m_TickFlags == 0);

		// Engine object is a shared object with shared object manager
		if(m_Registered)
			Service::EngineObjectManager->RemoveObject(this);
		m_Registered = false;

		AssertRel(m_ManagerListNodes.pNext == nullptr && m_ManagerListNodes.pPrev == nullptr);
		for (auto& itNode : m_ListNodes)
		{
			AssertRel(itNode.pNext == nullptr && itNode.pPrev == nullptr);
		}

	}

	Result EngineObject::InitializeObject()
	{
		RegisterToEngineObjectManager();

		return m_ComponentManager.InitializeComponents();
	}

	void EngineObject::RegisterToEngineObjectManager()
	{
		if (m_Registered)
			return;

		Service::EngineObjectManager->AddObject(this);
		m_Registered = true;
	}

	bool EngineObject::CanDelete()
	{
		if (!Object::CanDelete()) return false;

		if (m_TickFlags.load(std::memory_order_relaxed) != 0)
		{
			assert(!m_Disposed); // this shouldn't happen
			return false;
		}

		return true;
	}

	void EngineObject::Dispose()
	{
		if (m_Disposed)
			return;

		m_Disposed = true;

		SetTickFlags(0);

		if (m_EngineAsyncTickTask != nullptr)
			m_EngineAsyncTickTask->ClearObject();
		m_EngineAsyncTickTask = nullptr;

		if (m_RenderAsyncTickTask != nullptr)
			m_RenderAsyncTickTask->ClearObject();
		m_RenderAsyncTickTask = nullptr;

		m_ComponentManager.TerminateComponents();
	}


	void EngineObject::SetTickFlags(uint32_t tickFlag)
	{
		Service::EngineTaskManager->SetTickFlags(this, tickFlag);
	}

	void EngineObject::SetTickGroup(EngineTaskTick tickGroup)
	{
		auto tickFlag = tickGroup != EngineTaskTick::None ? (uint32_t)1 << (int)tickGroup : 0;
		SetTickFlags(tickFlag);
	}


	SharedPointerT<EngineObjectAsyncEngineTask>& EngineObject::GetEngineAsyncTickTask()
	{
		if (m_Disposed) return m_EngineAsyncTickTask;
		if (m_EngineAsyncTickTask == nullptr) m_EngineAsyncTickTask = new(GetHeap()) EngineObjectAsyncEngineTask(this, EngineTaskTick::AsyncTick);
		return m_EngineAsyncTickTask;
	}

	SharedPointerT<EngineObjectAsyncEngineTask>& EngineObject::GetRenderAsyncTickTask()
	{
		if (m_Disposed) return m_RenderAsyncTickTask;
		if (m_RenderAsyncTickTask == nullptr) m_RenderAsyncTickTask = new(GetHeap()) EngineObjectAsyncEngineTask(this, EngineTaskTick::AsyncRender);
		return m_RenderAsyncTickTask;
	}

	// Set timer
	//	@startDelay: timer will start after startDelay
	//	@interval: 0 means no repeat
	void EngineObject::SetTimer(DurationMS startDelay, DurationMS interval)
	{
		if (m_TimerAction == nullptr)
			m_TimerAction = new(GetHeap()) EngineObjectTimerAction(this);
	}

	Result EngineObject::OnTick(EngineTaskTick tick)
	{
		m_ComponentManager.TickUpdate();
		return ResultCode::SUCCESS;
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Default timer action
	//

	EngineObjectTimerAction::EngineObjectTimerAction(EngineObject* pTickTask)
		: m_pObject(pTickTask)
	{
	}

	EngineObjectTimerAction::~EngineObjectTimerAction()
	{
		Assert(m_pObject == nullptr);
	}

	void EngineObjectTimerAction::DisposeWeakPointer()
	{
		m_pObject = nullptr;
	}

	bool EngineObjectTimerAction::OnTimerTick()
	{
		EngineObject* pTickTask = m_pObject;

		if (pTickTask == nullptr)
			return false;

		int nextDiff = (INT)(GetNextTickTime() - Util::Time.GetTimeMs()).count();
		if (nextDiff <= 0)
		{
			// Do default rescheduling
			TimeStampMS nextTick = Util::Time.GetTimeMs() + GetTickInterval();
			SetNextTickTime(nextTick);
		}

		if (pTickTask->OnTimerTick(this) == Result(ResultCode::SUCCESS_FALSE))
			return false;

		return true;
	}

	const char* EngineObjectTimerAction::GetDebugString()
	{
		EngineObject* pTickTask = m_pObject;
		if (pTickTask != nullptr) return typeid(*pTickTask).name();

		return "EngineObjectTimerAction";
	}



}; // namespace SF

