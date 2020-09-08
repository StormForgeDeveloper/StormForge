////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Scene Graph node
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Memory/SFMemoryPool.h"
#include "Object/SFObject.h"
#include "SceneGraph/SFSceneNodeComponentMesh.h"
#include "Task/SFTimerScheduler.h"
#include "Container/SFDoubleLinkedList.h"

namespace SF {



	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNodeComponent class -  interface for task operation
	//

	class SceneNodeComponentSkeletalMesh : public SceneNodeComponentMesh
	{
	public:

		SCENENODECOMPONENT_DEFINE_SIGNATURE(SceneNodeComponentSkeletalMesh);


		// Joint information
		struct JointInfo
		{
			Matrix4 BindPose;
			SceneNode* Joint = nullptr;
			String JointPath;
			bool ManualUpdate; // if true bone matrix will not be updated from the joint
		};

	private:

		// joint information
		DynamicArray<JointInfo> m_Joints;

		// skeleton matrices for update
		DynamicArray<Matrix4> m_Skeletons;


	public:
		// Constructor
		SceneNodeComponentSkeletalMesh(IHeap& heap, const StringCrc64& name = "");
		virtual ~SceneNodeComponentSkeletalMesh();


		virtual void Dispose() override;


		Array<JointInfo>& GetJoints() { return m_Joints; }
		Array<Matrix4>& GetSkeletons() { return m_Skeletons; }


		// Compoentn tick update
		virtual Result Update(DurationMS delta) override;


		// copy properties to new component
		virtual Result CopyProperties(const SceneCloneContext& cloneFlags, SceneNodeComponent* pSrcComponent) override;

		// child component should overrride this for clone
		virtual SceneNodeComponent* Clone(const SceneCloneContext& cloneFlags, SceneNode* newOwner) override;

	};



	extern template class SharedPointerT<SceneNodeComponentMesh>;

}; // namespace SF

