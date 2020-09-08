////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Util/SFLog.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Thread/SFThread.h"
#include "Task/SFTask.h"
#include "Task/SFAsyncTaskManager.h"
#include "Util/SFTimeUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTask.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Service/SFEngineService.h"



namespace SF {



	class EngineObjectManagerTask : public EngineTask
	{
	public:
		EngineObjectManagerTask()
			: EngineTask(EngineTaskTick::SyncPostTick)
		{

		}
		virtual void Run()
		{
			Service::EngineObjectManager->Update();
		}
	};



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineObject Manager base class -  interface for task manager
	//

	constexpr StringCrc64 EngineObjectManager::TypeName;

	// Constructor/Destructor
	EngineObjectManager::EngineObjectManager()
		: LibraryComponent("EngineObjectManager")
		, m_ObjectReferenceManager(GetEngineHeap())
	{
		Service::EngineObjectManager = this;
	}

	EngineObjectManager::~EngineObjectManager()
	{
		Service::EngineObjectManager = nullptr;
	}


	// Initialize EngineObjectManager
	Result EngineObjectManager::InitializeComponent()
	{
		LibraryComponent::InitializeComponent();

		m_TickTask = new(GetEngineHeap()) EngineObjectManagerTask();

		Service::EngineTaskManager->AddTask(*m_TickTask);

		return ResultCode::SUCCESS;
	}

	// Terminate EngineObjectManager
	void EngineObjectManager::DeinitializeComponent()
	{
		LibraryComponent::DeinitializeComponent();

		m_ObjectReferenceManager.ClearFreedObjects();

		m_TickTask = nullptr;
	}

	// Add Object
	void EngineObjectManager::AddObject(EngineObject* pObject)
	{
		m_ObjectReferenceManager.RegisterSharedObject(pObject);

		if (Service::EngineTaskManager->GetEngineThreadID() == ThisThread::GetThreadID())
		{
			if (!m_EngineObjectList.Add(&pObject->GetManagerListNode()))
			{
				Assert(false);
			}
			else
			{
				pObject->m_ActuallyRegistered.store(true, std::memory_order_release);
			}
		}
		else
		{
			assert(pObject->GetReferenceCount() > 0 || pObject->GetWeakReferenceCount() == 1);
			assert(pObject->GetWeakReferenceCount() > 0);
			SharedPointerT<EngineObject> pShared = pObject;
			Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPreTick, [this, pShared]()
			{
				if (!m_EngineObjectList.Add(&pShared->GetManagerListNode()))
				{
					Assert(false);
				}
				else
				{
					pShared->m_ActuallyRegistered.store(true, std::memory_order_release);
				}
			});
		}
	}

	// Remove Object
	void EngineObjectManager::RemoveObject(EngineObject* pObject)
	{
		if (Service::EngineTaskManager->GetEngineThreadID() == ThisThread::GetThreadID())
		{
			if (!m_EngineObjectList.Remove(&pObject->GetManagerListNode()))
			{
				Assert(false);
			}
			else
			{
				pObject->m_ActuallyRegistered.store(false, std::memory_order_release);
			}
		}
		else
		{
			assert(pObject->GetReferenceCount() > 0); // Engine object can't be removed on another thread if they already released
			assert(pObject->GetWeakReferenceCount() > 0);
			SharedPointerT<EngineObject> pShared = pObject;
			Service::EngineTaskManager->RunOnEngineThread(EngineTaskTick::SyncPreTick, [this, pShared]()
			{
				if (!m_EngineObjectList.Remove(&pShared->GetManagerListNode()))
				{
					Assert(false);
				}
				else
				{
					pShared->m_ActuallyRegistered.store(false, std::memory_order_release);
				}
			});
		}

	}


	void EngineObjectManager::Update()
	{
		m_ObjectReferenceManager.Update();
	}




}; // namespace SF

