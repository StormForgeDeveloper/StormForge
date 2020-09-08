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
#include "EngineObject/SFEngineObject.h"
#include "Task/SFTimerScheduler.h"
#include "Container/SFArray.h"
#include "Math/SF3DMath.h"
#include "String/SFString.h"


namespace SF
{
	class SceneNodeComponent;

	struct SceneCloneFlags
	{
		bool Node : 1;	// Create new node, create a copy of whole node heierarchy
		bool AnimationData : 1;	// Animation data, mostly you don't want to make copy of this
		bool AnimationContext : 1;	// Animation Context, If yo didn't make a copy of animation context, they will share animtion status
		bool Material : 1;	// Material, mostly you don't want to make copy of this
		bool Vertex : 1;	// Vertex, mostly you don't want to make copy of this
		bool Index : 1;			// Index, mostly you don't want to make copy of this
		bool Texture : 1;	// Texture, mostly you don't want to make copy of this

		SceneCloneFlags()
		{
			Node = true;
			AnimationData = false;
			AnimationContext = true;
			Material = true;
			Texture = false;
		}
	};

	// Clone options
	struct SceneCloneContext : public SceneCloneFlags
	{
		IHeap& Heap;

		SceneCloneContext(IHeap& heap)
			: Heap(heap)
		{
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNode class -  interface for task operation
	//

	class SceneNode : public Object
	{
	public:


	private:

		/// <summary>
		/// Cached local transform matrix
		/// </summary>
		Matrix4 m_Transform = Matrix4::Identity();

		/// <summary>
		/// Cached absolute transform matrix
		/// </summary>
		Matrix4 m_AbsoluteTransform = Matrix4::Identity();

		/// <summary>
		/// Any translation applied to the bone
		/// </summary>
		Vector4 m_Translation = Vector4::Zero();

		/// <summary>
		/// Any rotation applied to the bone
		/// </summary>
		Quaternion m_Rotation = Quaternion::Identity();

		/// <summary>
		/// Any scaling applied to the bone
		/// </summary>
		Vector4 m_Scale = Vector4::One();

		// transformation update serial
		uint m_TransformUpdateSerial = 0;
		uint m_ParentTransformUpdateSerial = 0;
		uint m_TransformCacheSerial = 0;

		/// <summary>
		/// Parent for this node
		/// </summary>
		SceneNode* m_Parent = nullptr;

		/// <summary>
		/// The children of this bone
		/// </summary>
		DynamicArray<SharedPointerT<SceneNode>> m_Children;
		DynamicArray<SceneNode*> m_ChildrenToRemove;

		// Node component
		SortedArray<StringCrc64, SharedPointerT<SceneNodeComponent>, true, false> m_NodeComponents;

	protected:


		void SetParentInternal(SceneNode* parent);

		void UpdateRemoveChildren();

	public:

	public:
		// Constructor
		SceneNode(IHeap& heap, const StringCrc64& name = "");
		virtual ~SceneNode();

		// Dispose
		virtual void Dispose() override;



		//Get Transform update serial
		uint GetTransformUpdateSerial() { return m_TransformUpdateSerial; }


		/// <summary>
		/// The bone bind transform
		/// </summary>
		const Matrix4& GetLocalTransform()
		{
			UpdateTransform();
			return m_Transform;
		}
			//set
			//{
			//    m_Transform = value;
			//    m_Translation = m_Transform.Translation;
			//    m_Rotation.CreateF = m_Transform.;
			//    m_Scale = m_Transform.Translation;
			//}
		//}

		// Get absolute transform
		const Matrix4& GetAbsoluteTransform();

		/// <summary>
		/// Compute the absolute transformation for this bone.
		/// </summary>
		void UpdateTransform();


		/// <summary>
		/// rotation
		/// </summary>
		const Quaternion& GetRotation() { return m_Rotation; }
		void SetRotation(const Quaternion& value) { m_Rotation = value; m_TransformUpdateSerial++; }

		/// <summary>
		/// translations
		/// </summary>
		const Vector4& GetTranslation() { return m_Translation; }
		void SetTranslation(const Vector4& value) { m_Translation = value; m_TransformUpdateSerial++; }

		/// <summary>
		/// scaling
		/// </summary>
		const Vector4& GetScale() { return m_Scale; }
		void SetSacle(const Vector4& value) { m_Scale = value; m_TransformUpdateSerial++; }


		//	/// <summary>
		//	/// World space bounding box
		//	/// </summary>
		//BoundingBox m_WorldBound;
		//[Preserve]
		//public BoundingBox WorldBound
		//{
		//	get { return m_WorldBound; }
		//}

		/// <summary>
		/// Parent Node
		/// </summary>
		SceneNode* GetParent() { return m_Parent; }

		/// <summary>
		/// The children of this node
		/// </summary>
		DynamicArray<SharedPointerT<SceneNode>>& GetChildren() { return m_Children; }

		// Set parent
		void SetParent(SceneNode* parent);

		// Add child
		void AddChild(SceneNode* child);

		// Remove child
		void RemoveChild(SceneNode* child);

		// Find child
		SceneNode* FindChild(StringCrc64 nodeName);

		/// <summary>
		/// Find child recursively
		/// </summary>
		/// <param name="nodePath">node path to find</param>
		/// <returns></returns>
		SceneNode* FindChildRecursively(const String& nodePath);


		template<class ComponentType>
		ComponentType* GetComponent()
		{
			SceneNodeComponent* component = nullptr;
			if (m_NodeComponents.Find(ComponentType::TypeSignature, component))
				return static_cast<ComponentType*>(component);
			else
				return nullptr;
		}

		//
		template<class ComponentType>
		ComponentType* AddComponent()
		{
			SceneNodeComponent* component = nullptr;
			auto key = ComponentType::TypeSignature;

			if(m_NodeComponents.Find(key, component))
				return static_cast<ComponentType*>(component);

			component = new(GetHeap()) ComponentType;

			m_NodeComponents.Insert(key, component);

			return static_cast<ComponentType*>(component);
		}

		// Add a component
		Result AddComponent(SceneNodeComponent* newComponent);

		// Remove a component
		void RemoveComponent(SceneNodeComponent* componentToRemove);


		// Func: std::function<void(SceneNodeComponent*)>
		template<class Func>
		void ForeachComponent(Func action)
		{
			for(auto component : m_NodeComponents)
			{
				action(component);
			}
		}


		/// <summary>
		/// Initialize components of all hierarchy
		/// </summary>
		/// <param name="rootNode">root node of this hierarchy. This will be used for search nodes for animation component or other link search</param>
		void InitializeComponents(SceneNode* rootNode = nullptr);



//// Update world coordinate bounding box
//public void UpdateBoundingBox()
//{
//	if (m_NodeComponents == null)
//		return;
//
//	bool bIsFirst = true;
//	Matrix worldTransform = AbsoluteTransform;
//
//	m_WorldBound = new BoundingBox();
//
//	foreach(var component in m_NodeComponents)
//	{
//		var meshComponent = component.Value as MeshComponent;
//		if (meshComponent == null)
//			continue;
//
//		Vector3 min = meshComponent.LocalBound.Min, max = meshComponent.LocalBound.Max;
//		Vector3.Transform(ref max, ref worldTransform, out max);
//		Vector3.Transform(ref min, ref worldTransform, out min);
//
//		if (bIsFirst)
//		{
//			bIsFirst = false;
//			m_WorldBound.Min = min;
//			m_WorldBound.Max = max;
//		}
//		else
//		{
//			m_WorldBound.Min = Vector3.Min(m_WorldBound.Min, min);
//			m_WorldBound.Max = Vector3.Max(m_WorldBound.Max, max);
//		}
//	}
//
//
//	// Update children
//	foreach(var child in m_Children)
//	{
//		child.UpdateBoundingBox();
//
//		// Merge bounding box of children
//		if (bIsFirst)
//		{
//			bIsFirst = false;
//			m_WorldBound.Min = child.WorldBound.Min;
//			m_WorldBound.Max = child.WorldBound.Max;
//		}
//		else
//		{
//			m_WorldBound.Min = Vector3.Min(m_WorldBound.Min, child.WorldBound.Min);
//			m_WorldBound.Max = Vector3.Max(m_WorldBound.Max, child.WorldBound.Max);
//		}
//	}
//}
//
//public void Update(float deltaTime)
//{
//	if (m_NodeComponents == null || !m_IsActive)
//		return;
//
//	UpdateInternal(NodeComponent.TickMask.PreUpdate, deltaTime);
//	UpdateInternal(NodeComponent.TickMask.Update, deltaTime);
//	UpdateInternal(NodeComponent.TickMask.PostUpdate, deltaTime);
//}
//
		

//void UpdateInternal(NodeComponent.TickMask tickMask, float deltaTime)
//{
//	// if m_NodeComponents == null, it means this node is disposed
//	if (m_NodeComponents == null)
//		return;
//
//	foreach(var component in m_NodeComponents)
//	{
//		if ((component.Value.UpdateTickMask & (ulong)tickMask) != 0)
//			component.Value.UpdateComponent(tickMask, deltaTime);
//	}
//
//	// Transform is updated on Update tick
//	if (tickMask == NodeComponent.TickMask.Update)
//		UpdateTransform();
//
//	UpdateRemoveChildren();
//
//	foreach(var child in m_Children)
//	{
//		child.UpdateInternal(tickMask, deltaTime);
//	}
//}
//
//
//#endregion

		// Copy properties from another node
		virtual Result CopyProperties(const SceneCloneContext& cloneFlags, SceneNode* pScrNode);

		// Create cloned node
		virtual SceneNode* Clone(const SceneCloneContext& cloneFlags);



///// <summary>
///// Draw node recursively
///// </summary>
///// <param name="graphics">Graphic device instance</param>
///// <param name="camera">Camera for view information</param>
//public virtual void Draw(GraphicsDevice graphics, Camera camera)
//{
//	if (m_NodeComponents == null)
//		return;
//
//	// disable drawing for all children and itself
//	if (!m_Visible || !m_IsActive)
//		return;
//
//	//var perfUpdate = PerfMonitor.StartPerf(this, "BRNodeComponentDraw");
//
//	foreach(var component in m_NodeComponents)
//	{
//		component.Value.Draw(graphics, camera);
//	}
//
//	//perfUpdate.End();
//
//
//	//var perfChild = PerfMonitor.StartPerf(this, "BRNodeDraw");
//	foreach(var child in m_Children)
//	{
//		child.Draw(graphics, camera);
//	}
//	//perfChild.End();
//}


	};



	extern template class SharedPointerT<SceneNode>;

}; // namespace SF

