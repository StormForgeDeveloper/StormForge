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
#include "Util/SFStringCrcDB.h"
#include "EngineObject/SFEngineTask.h"
#include "Service/SFConnectionManagerService.h"
#include "Service/SFNetSystemService.h"
#include "Service/SFIAssetImporterFactory.h"
#include "Service/SFIAssetSerializerFactory.h"
//#include "Service/SFResourceManagerService.h"
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
	public:

		using DelegateEngineTickAction = std::function<void()>;

	private:

		static ThreadID m_EngineThreadID;
        static ThreadID m_RenderThreadID;

	protected:
		// Engine frame number
		Atomic<uint32_t> m_FrameNumber = 0;


	private:
		virtual void SetTickFlagsInternal(EngineObject* pObj, uint32_t tickFlag) { unused(pObj); }

		friend class SetObjectTickFlagTask;


        static void SetEngineThreadID(ThreadID threadID) { m_EngineThreadID = threadID; }
        static void SetRenderThreadID(ThreadID threadID) { m_RenderThreadID = threadID; }

	protected:

		friend class EngineTask;
		friend class Engine;
		friend class EngineThread;
		friend class RenderThread;

	public:

		static ThreadID GetEngineThreadID() { return m_EngineThreadID; }
        static ThreadID GetRenderThreadID() { return m_RenderThreadID; }

		uint32_t GetFrameNumber() const { return m_FrameNumber.load(MemoryOrder::relaxed); }


		virtual void SetTickFlags(EngineObject* pObj, uint32_t tickFlag) { unused(pObj); unused(tickFlag); }


		// Schedule Async task for this tick, for one time running
		virtual Result RunOnEngineTick(DelegateEngineTickAction&& action) { return ResultCode::SUCCESS_FALSE; }

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
				EngineTaskPtr pNewTask = new SF::EngineTaskT<Func>(tickGroup, func);
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

		// Detained release. They will be kept for few frames and released
		virtual void AddToDetainedRelease(const SharedPointer& obj) { unused(obj); }
		virtual void AddToDetainedRelease(SharedPointer&& obj) { unused(obj); }

		virtual void Update() {}
	};


} // namespace SF

