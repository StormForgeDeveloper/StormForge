////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render task
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Task/SFTask.h"
#include "Object/SFSharedPointer.h"
#include "EngineObject/SFEngineObject.h"
#include "Container/SFDoubleLinkedList.h"

namespace SF {


	class EngineObjectManager;



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	RenderTask -  interface for task operation
	//

	class RenderTask : protected Task
	{
	public:

	private:
		// object pointer 
		WeakPointerT<Object>	m_ObjectPtr;

	private:

	public:
		RenderTask(Object* pObject); // poke ticking
		virtual ~RenderTask();

		virtual Result Request() override;

		virtual void Run() override;
	};

	

}; // namespace SF

