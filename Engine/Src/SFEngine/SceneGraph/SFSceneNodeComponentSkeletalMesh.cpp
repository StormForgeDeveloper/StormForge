////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SceneNodeComponent
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "String/SFStrUtil.h"
#include "SceneGraph/SFSceneNode.h"
#include "SceneGraph/SFSceneNodeComponentSkeletalMesh.h"
#include "EngineObject/SFEngineObject.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"



namespace SF {

	template class SharedPointerT<SceneNodeComponentSkeletalMesh>;



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNodeComponent class -  interface for task operation
	//


	// Constructor
	SceneNodeComponentSkeletalMesh::SceneNodeComponentSkeletalMesh(IHeap& heap, const StringCrc64& name)
		: SceneNodeComponentMesh(heap, name)
		, m_Joints(heap)
		, m_Skeletons(heap)
	{

	}

	SceneNodeComponentSkeletalMesh::~SceneNodeComponentSkeletalMesh()
	{
	}

	void SceneNodeComponentSkeletalMesh::Dispose()
	{
		SceneNodeComponentMesh::Dispose();
	}


	// Component tick update
	Result SceneNodeComponentSkeletalMesh::Update(DurationMS delta)
	{
		return ResultCode::SUCCESS;
	}

	// copy properties to new component
	Result SceneNodeComponentSkeletalMesh::CopyProperties(const SceneCloneContext& cloneFlags, SceneNodeComponent* pSrcComponent)
	{
		if (pSrcComponent == nullptr)
			return ResultCode::INVALID_POINTER;

		auto result = SceneNodeComponentMesh::CopyProperties(cloneFlags, pSrcComponent);
		if (!result)
			return result;


		return ResultCode::SUCCESS;
	}

	// child component should overrride this for clone
	SceneNodeComponent* SceneNodeComponentSkeletalMesh::Clone(const SceneCloneContext& cloneFlags, SceneNode* newOwner)
	{
		auto newComponent = new(cloneFlags.Heap) SceneNodeComponentSkeletalMesh(cloneFlags.Heap);
		if (newComponent == nullptr)
			return nullptr;

		newComponent->CopyProperties(cloneFlags, this);

		return newComponent;
	}


}; // namespace SF

