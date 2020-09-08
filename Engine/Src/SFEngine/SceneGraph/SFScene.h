////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Scene Graph
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryPool.h"
#include "Object/SFObject.h"
#include "SceneGraph/SFSceneNode.h"
#include "Task/SFTimerScheduler.h"
#include "Container/SFDoubleLinkedList.h"
#include "Math/SF3DMath.h"

namespace SF {


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Scene class -  interface for task operation
	//

	class Scene : public SceneNode
	{
	public:
	private:


	public:
		// Constructor
		Scene(IHeap& heap, const StringCrc64& name = "");
		virtual ~Scene();

		virtual void Dispose() override;

	};



	extern template class SharedPointerT<Scene>;

}; // namespace SF

