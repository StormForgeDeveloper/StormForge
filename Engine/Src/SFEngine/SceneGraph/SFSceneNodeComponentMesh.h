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
#include "MemoryManager/SFMemoryPool.h"
#include "Object/SFObject.h"
#include "Resource/SFIndexBuffer.h"
#include "Resource/SFVertexBuffer.h"
#include "SceneGraph/SFSceneNodeComponent.h"
#include "Task/SFTimerScheduler.h"
#include "Container/SFDoubleLinkedList.h"

namespace SF {


	// TODO: move to render
	enum class DrawPrimitiveType
	{
		Triangles = 0,
		Quads = 2,
		Lines = 3,
		LineStrip = 4,
		Points = 5
	};


	// SubMesh
	struct SceneNodeComponentMesh_SubMesh
	{
		//Effect Material;
		uint32_t IndexOffset = 0;
		DrawPrimitiveType PrimitiveType = DrawPrimitiveType::Lines;
		uint PrimitiveCount = 0;
	};




	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNodeComponent class -  interface for task operation
	//

	class SceneNodeComponentMesh : public SceneNodeComponent
	{
	public:

		SCENENODECOMPONENT_DEFINE_SIGNATURE(SceneNodeComponentMesh);

		typedef SceneNodeComponentMesh_SubMesh SubMesh;

	private:

		// when we use skinned transform, we need to use identity transform
		bool m_DisableLocalTransform = false;

		// If the component is cloned, it holds clone flags
		SceneCloneFlags m_CloneFlags;

		//// Mesh bounding box(AABB) in local coordinate
		//BoundingBox LocalBound{ get; internal set; }

		// Index buffer
		IndexBufferPtr m_IndexBuffer;

		//VertexDeclaration VertexDeclaration { get; private set; }
		VertexBufferPtr m_VertexBuffer;


		// material list
		DynamicArray<StringCrc64> m_MergedMaterials;

		// sub-meshes
		DynamicArray<SubMesh> m_SubMeshes;


		// TODO: New texture animation
		//	public string TextureName
		//{
		//	get
		//	{
		//		foreach(var subMesh in SubMeshes)
		//		{
		//			if (subMesh.Material == null) continue;
		//			foreach(var param in subMesh.Material.Parameters)
		//			{
		//				if (param.ParameterType != EffectParameterType.Texture2D) continue;

		//				var tex2D = param.GetValueTexture2D();
		//				if (tex2D == null) continue;
		//				return tex2D.Name;
		//			}
		//		}
		//		return null;
		//	}
		//	set
		//	{
		//		if (string.IsNullOrEmpty(value)) return;

		//		foreach(var subMesh in SubMeshes)
		//		{
		//			if (subMesh.Material == null) continue;
		//			foreach(var param in subMesh.Material.Parameters)
		//			{
		//				if (param.ParameterType != EffectParameterType.Texture2D) continue;
		//				var orgTex = param.GetValueTexture2D();
		//				if (orgTex != null && orgTex.Name == value) continue;

		//				var contentManager = CCContentManager.SharedContentManager;
		//				var texture = contentManager.Load<Texture2D>(value);
		//				param.SetValue(texture);
		//				break;
		//			}
		//		}
		//	}
		//}


		//	public override void FindTargetProperty(string propertyName, out System.Reflection.PropertyInfo propertyInfo, out object target)
		//	{
		//		base.FindTargetProperty(propertyName, out propertyInfo, out target);
		//		if (propertyInfo != null) {
		//			return;
		//		}

		//		propertyInfo = GetType().GetProperty(propertyName);
		//		if (propertyInfo != null)
		//		{
		//			target = this;
		//			return;
		//		}

		//		foreach(var subMesh in SubMeshes)
		//		{
		//			if (subMesh.Material == null) continue;
		//			propertyInfo = subMesh.Material.GetType().GetProperty(propertyName);
		//			if (propertyInfo != null)
		//			{
		//				target = subMesh.Material;
		//				return;
		//			}
		//		}
		//	}





	public:
		// Constructor
		SceneNodeComponentMesh(const StringCrc64& name = "");
		virtual ~SceneNodeComponentMesh();

		// Dispose
		virtual void Dispose() override;

		// Get/Set local transform enable/disable flag 
		bool GetDisableLocalTransform() { return m_DisableLocalTransform; }
		void SetDisableLocalTransform(bool disable) { m_DisableLocalTransform = disable; }

		// Get sub mesh list
		Array<SubMesh>& GetSubMeshes() { return m_SubMeshes; }

		// Compoenent tick update
		virtual Result Update(DurationMS delta) override;

		// 
		//virtual Result Draw() override;

		// copy properties to new component
		virtual Result CopyProperties(const SceneCloneContext& cloneFlags, SceneNodeComponent* pSrcComponent) override;

		// child component should overrride this for clone
		virtual SceneNodeComponent* Clone(const SceneCloneContext& cloneFlags, SceneNode* newOwner) override;

	};



	extern template class SharedPointerT<SceneNodeComponentMesh>;

}; // namespace SF

