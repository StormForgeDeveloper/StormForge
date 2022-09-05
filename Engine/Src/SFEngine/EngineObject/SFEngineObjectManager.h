////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Multithread/SFThread.h"
#include "Multithread/SFSynchronization.h"
#include "Object/SFSharedObjectManager.h"
#include "Object/SFObjectManager.h"
#include "Container/SFSortedMap.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFCircularPageQueue.h"
#include "Container/SFPageQueue.h"
#include "EngineObject/SFEngineObject.h"
#include "Util/SFLog.h"
#include "Container/SFIndexing.h"
#include "Container/SFHashTable.h"
#include "Service/SFEngineServices.h"


namespace SF {


	class EngineObjectManager;
	class EngineTask;


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineObject Manager base class -  interface for task manager
	//

	class EngineObjectManager : public LibraryComponent, public EngineObjectManagerService
	{
	public:
		static constexpr StringCrc64 TypeName = "EngineObjectManager";
		static constexpr uint32_t DetainedRelease_QueueCount = 3;
		static constexpr uint32_t DetainedRelease_SwapTicks = 5;

	private:

		SharedObjectManager m_ObjectReferenceManager;

		// Engine object list
		DoubleLinkedListBase<DoubleLinkedListNodeDataT<EngineObject*>>		m_EngineObjectList;

		SharedPointerT<EngineTask> m_TickTask;


		// For Detained release
		Atomic<uint32_t> m_FlushBufferSerial = 0;
		PageQueue<SharedPointer> m_DetainedReleaseQueue0;
		PageQueue<SharedPointer> m_DetainedReleaseQueue1;
		PageQueue<SharedPointer> m_DetainedReleaseQueue2;
		PageQueue<SharedPointer>* m_DetainedReleaseQueues[DetainedRelease_QueueCount]{ &m_DetainedReleaseQueue0, &m_DetainedReleaseQueue1, &m_DetainedReleaseQueue2 };


	public:


		// Constructor/Destructor
		EngineObjectManager();
		virtual ~EngineObjectManager();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		// Initialize EngineObjectManager
		virtual Result InitializeComponent() override;

		// Terminate EngineObjectManager
		virtual void DeinitializeComponent() override;


		// TODO: Create/Destroy would be better?

		// Add Object
		virtual void AddObject(EngineObject* pObject) override;

		// Remove Object
		virtual void RemoveObject(EngineObject* pObject) override;


		virtual void AddToDetainedRelease(const SharedPointer& obj) override;
		virtual void AddToDetainedRelease(SharedPointer&& obj) override;


		virtual void Update() override;

	};







}; // namespace SF

