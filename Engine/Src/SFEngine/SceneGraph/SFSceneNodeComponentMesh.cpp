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
#include "Util/SFStrUtil.h"
#include "SceneGraph/SFSceneNode.h"
#include "SceneGraph/SFSceneNodeComponentMesh.h"
#include "EngineObject/SFEngineObject.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"



namespace SF {

	template class SharedPointerT<SceneNodeComponentMesh>;



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNodeComponent class -  interface for task operation
	//


	// Constructor
	SceneNodeComponentMesh::SceneNodeComponentMesh(const StringCrc64& name)
		: SceneNodeComponent(name)
	{
		memset(&m_CloneFlags, 0, sizeof(m_CloneFlags));

		SetUpdateTickMode(UpdateTickMode::BeforeDraw);
	}

	SceneNodeComponentMesh::~SceneNodeComponentMesh()
	{
	}

	void SceneNodeComponentMesh::Dispose()
	{
		SceneNodeComponent::Dispose();

		//for (auto& subMesh : m_SubMeshes)
		//{
			//if(!m_CloneFlags.Material)
			//	subMesh.Material->Dispose();
		//}
		m_SubMeshes.Clear();

		if (m_IndexBuffer != nullptr && !m_CloneFlags.Index)
			m_IndexBuffer->Dispose();
		m_IndexBuffer = nullptr;

		if (m_VertexBuffer != nullptr && !m_CloneFlags.Vertex)
			m_VertexBuffer->Dispose();
		m_VertexBuffer = nullptr;

		SceneNodeComponent::Dispose();
	}


	// Compoentn tick update
	Result SceneNodeComponentMesh::Update(DurationMS delta)
	{
		return ResultCode::SUCCESS;
	}

	// copy properties to new component
	Result SceneNodeComponentMesh::CopyProperties(const SceneCloneContext& cloneFlags, SceneNodeComponent* pSrcComponent)
	{
		if (pSrcComponent == nullptr)
			return ResultCode::INVALID_POINTER;

		auto pSrcMesh = (SceneNodeComponentMesh*)pSrcComponent;

		auto result = SceneNodeComponent::CopyProperties(cloneFlags, pSrcComponent);
		if (!result)
			return result;

		m_CloneFlags = cloneFlags;

		//m_LocalBound = pSrcComponent->m_LocalBound;
		//m_VertexBuffer = pSrcComponent->m_VertexBuffer;

		m_SubMeshes.resize(pSrcMesh->GetSubMeshes().size());
		for (uint iSubMesh = 0; iSubMesh < pSrcMesh->GetSubMeshes().size(); iSubMesh++)
		{
			m_SubMeshes[iSubMesh] = pSrcMesh->GetSubMeshes()[iSubMesh];
			//m_SubMeshes[iSubMesh].Material = pSrcMesh->GetSubMeshes()[iSubMesh].Material.Clone(cloneFlags);
		}

		return ResultCode::SUCCESS;
	}

	// child component should overrride this for clone
	SceneNodeComponent* SceneNodeComponentMesh::Clone(const SceneCloneContext& cloneFlags, SceneNode* newOwner)
	{
		auto newComponent = new SceneNodeComponentMesh();
		if (newComponent == nullptr)
			return nullptr;

		newComponent->CopyProperties(cloneFlags, this);

		return newComponent;
	}


}; // namespace SF

