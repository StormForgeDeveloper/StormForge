////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine services
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Container/SFHashTable2.h"
#include "Object/SFSharedPointer.h"
#include "String/SFFixedStringDB.h"
#include "EngineObject/SFEngineTask.h"
#include "Service/SFConnectionManagerService.h"
#include "Service/SFNetSystemService.h"
#include "Service/SFIAssetImporterFactory.h"
#include "Service/SFIAssetSerializerFactory.h"
#include "Service/SFResourceManagerService.h"
#include "Service/SFIGraphicDevice.h"



namespace SF {


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	EngineTaskService
	//
	
	class EngineTaskManager;
	class EngineObject;

	typedef SharedPointerT<EngineTask> EngineTaskPtr;

	class EngineTaskService
	{
	private:

		ThreadID m_EngineThreadID;
		ThreadID m_RenderThreadID;


	private:
		virtual void UpdateTickFlagsInternal(EngineObject* pObj) { unused(pObj); }

		friend class UpdateObjectTickFlagTask;


		void SetEngineThreadID(ThreadID threadID) { m_EngineThreadID = threadID; }
		void SetRenderThreadID(ThreadID threadID) { m_RenderThreadID = threadID; }

	protected:

		virtual void OnTaskFinished(EngineTask* pTask) {}
		virtual void OnTaskCanceled(EngineTask* pTask) {}

		friend class EngineTask;
		friend class Engine;
		friend class EngineThread;
		friend class RenderThread;

	public:

		ThreadID GetEngineThreadID() { return m_EngineThreadID; }
		ThreadID GetRenderThreadID() { return m_RenderThreadID; }


		virtual EngineTaskPtr UpdateTickFlags(EngineObject* pObj) { unused(pObj); return EngineTaskPtr(); }


		// Schedule Async task for this tick, for one time running
		virtual Result ScheduleTaskForThisTick(Task* pTask) { unused(pTask); return ResultCode::SUCCESS_FALSE; }

		// Add object event task
		virtual Result AddTask(EngineTask* pTask) { unused(pTask); return ResultCode::SUCCESS_FALSE; }

		// Engine tick update
		virtual void EngineTickUpdate() {}

		// Rendering tick update
		virtual void RenderingTickUpdate() {}

		template<class Func>
		EngineTaskPtr RunOnEngineThread(EngineTaskTick tickGroup, Func func)
		{
			if (ThisThread::GetThreadID() == GetEngineThreadID())
			{
				func();
				return EngineTaskPtr();
			}
			else
			{
				// This function can be called in the object destructor, so we need to use some global memory manager
				EngineTaskPtr pNewTask = new(GetEngineHeap()) SF::EngineTaskT<Func>(tickGroup, func);
				pNewTask->Request();
				return std::forward<EngineTaskPtr>(pNewTask);
			}
		}

	};

	
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Engine object manager service
	//
	
	
	class EngineObjectManager;
	class EngineTask;


	
	class EngineObjectManagerService
	{
	public:
				// Add Object
		virtual void AddObject(EngineObject* pObject) {unused(pObject); }

		// Remove Object
		virtual void RemoveObject(EngineObject* pObject) { unused(pObject); }

		virtual void Update() {}
	};


	



}; // namespace SF

