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
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "EngineObject/SFEngineObject.h"
#include "SceneGraph/SFSceneNodeComponent.h"
#include "SceneGraph/SFSceneNode.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"



namespace SF {

	template class SharedPointerT<SceneNodeComponent>;



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNodeComponent class -  interface for task operation
	//


	// Constructor
	SceneNodeComponent::SceneNodeComponent(IHeap& heap, const StringCrc64& name)
		: Object(&heap, name)
	{

	}

	SceneNodeComponent::~SceneNodeComponent()
	{
	}

	void SceneNodeComponent::Dispose()
	{
		Object::Dispose();
	}

	// Change owner
	void SceneNodeComponent::ChangeOwner(SceneNode* newOwner)
	{
		if (m_Owner != nullptr)
			m_Owner->RemoveComponent(this);

		m_Owner = newOwner;

		if (m_Owner != nullptr)
			m_Owner->AddComponent(this);
	}


	Result SceneNodeComponent::CopyProperties(const SceneCloneContext& cloneFlags, SceneNodeComponent* pSrcComponent)
	{
		if (pSrcComponent == nullptr)
			return ResultCode::INVALID_POINTER;

		SetName(pSrcComponent->GetName());
		m_UpdateTickMode = pSrcComponent->m_UpdateTickMode;

		return ResultCode::SUCCESS;
	}



}; // namespace SF

