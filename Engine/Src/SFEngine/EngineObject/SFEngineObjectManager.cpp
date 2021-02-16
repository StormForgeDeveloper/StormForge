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
#include "Multithread/SFThread.h"
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
	constexpr uint32_t EngineObjectManager::DetainedRelease_QueueCount;
	constexpr uint32_t EngineObjectManager::DetainedRelease_SwapTicks;


	// Constructor/Destructor
	EngineObjectManager::EngineObjectManager()
		: LibraryComponent("EngineObjectManager")
		, m_ObjectReferenceManager(GetEngineHeap())
		, m_DetainedReleaseQueue0(GetEngineHeap())
		, m_DetainedReleaseQueue1(GetEngineHeap())
		, m_DetainedReleaseQueue2(GetEngineHeap())
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
			assert(pObject->GetReferenceCount() > 0);
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

	void EngineObjectManager::AddToDetainedRelease(const SharedPointer& obj)
	{
		// Engine tick can update m_FlushBufferSerial after we acquire buffer serial before end of this operation, but we still thread safety because the queue provide thread safety between read and write thread
		auto bufferSerial = m_FlushBufferSerial.load(MemoryOrder::memory_order_acquire);
		auto pQueue = m_DetainedReleaseQueues[bufferSerial % countof(m_DetainedReleaseQueues)];
		if (pQueue == nullptr)
		{
			assert(false);
			return;
		}

		pQueue->Enqueue(obj);
	}

	void EngineObjectManager::AddToDetainedRelease(SharedPointer&& obj)
	{
		auto bufferSerial = m_FlushBufferSerial.load(MemoryOrder::memory_order_acquire);
		auto pQueue = m_DetainedReleaseQueues[bufferSerial % countof(m_DetainedReleaseQueues)];
		if (pQueue == nullptr)
		{
			assert(false);
			return;
		}

		pQueue->Enqueue(Forward<SharedPointer>(obj));
	}


	void EngineObjectManager::Update()
	{
		m_ObjectReferenceManager.Update();

		// Every 5 frame we flip detained queue and empty new one
		if ((Service::EngineTaskManager->GetFrameNumber() % DetainedRelease_SwapTicks) == 0)
		{
			auto newBufferSerial = m_FlushBufferSerial.fetch_add(1, MemoryOrder::memory_order_release) + 1;
			auto pQueue = m_DetainedReleaseQueues[newBufferSerial % countof(m_DetainedReleaseQueues)];

			// empty items in the queue
			SharedPointer sharedPtr;
			while (pQueue->Dequeue(sharedPtr))
			{
				sharedPtr.ReleaseReference();
			}
		}
	}


} // namespace SF

