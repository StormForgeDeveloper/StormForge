////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Scene
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "SceneGraph/SFScene.h"
#include "EngineObject/SFEngineObject.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"



namespace SF {

	template class SharedPointerT<Scene>;




	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Scene class -  interface for task operation
	//


	// Constructor
	Scene::Scene(IHeap& heap, const FixedString& name)
		: SceneNode(heap, name)
	{

	}

	Scene::~Scene()
	{
	}

	void Scene::Dispose()
	{
		Object::Dispose();
	}



}; // namespace SF

