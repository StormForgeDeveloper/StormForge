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
#include "Thread/SFThread.h"
#include "Thread/SFSynchronization.h"
#include "Object/SFSharedObjectManager.h"
#include "Object/SFObjectManager.h"
#include "Container/SFSortedMap.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFCircularPageQueue.h"
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

	private:

		SharedObjectManager m_ObjectReferenceManager;

		// Engine object list
		DoubleLinkedListBase<DoubleLinkedListNodeDataT<EngineObject*>>		m_EngineObjectList;

		SharedPointerT<EngineTask> m_TickTask;

	public:


		// Constructor/Destructor
		EngineObjectManager();
		virtual ~EngineObjectManager();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		// Initialize EngineObjectManager
		virtual Result InitializeComponent() override;

		// Terminate EngineObjectManager
		virtual void DeinitializeComponent() override;


		// TODO: Create/Destroy would be better?

		// Add Object
		virtual void AddObject(EngineObject* pObject) override;

		// Remove Object
		virtual void RemoveObject(EngineObject* pObject) override;


		virtual void Update() override;

	};







}; // namespace SF

