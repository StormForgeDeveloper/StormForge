////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SceneNode
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "String/SFStrUtil.h"
#include "SceneGraph/SFSceneNode.h"
#include "SceneGraph/SFSceneNodeComponent.h"
#include "EngineObject/SFEngineObject.h"
#include "Util/SFTimeUtil.h"
#include "Service/SFEngineService.h"



namespace SF {

	template class SharedPointerT<SceneNode>;


	////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SceneNode class -  interface for task operation
	//


	// Constructor
	SceneNode::SceneNode(IHeap& heap, const FixedString& name)
		: Object(&heap, name)
		, m_Children(heap)
		, m_ChildrenToRemove(heap)
		, m_NodeComponents(heap)
	{

	}

	SceneNode::~SceneNode()
	{
	}

	void SceneNode::Dispose()
	{
		Object::Dispose();

		for(auto component : m_NodeComponents)
		{
			component->Dispose();
		}
		m_NodeComponents.Clear();

		for(auto child : m_Children)
		{
			child->Dispose();
		}
		m_Children.Clear();
		m_ChildrenToRemove.Clear();
	}

	// Add a component
	Result SceneNode::AddComponent(SceneNodeComponent* newComponent)
	{
		if (newComponent == nullptr)
			return ResultCode::INVALID_POINTER;

		return m_NodeComponents.Insert(newComponent->GetTypeSignature(), newComponent);
	}

	// Remove a component
	void SceneNode::RemoveComponent(SceneNodeComponent* componentToRemove)
	{
		if (componentToRemove == nullptr)
			return;

		SharedPointerT<SceneNodeComponent> removed;
		m_NodeComponents.Remove(componentToRemove->GetTypeSignature(), removed);
	}



	const Matrix4& SceneNode::GetAbsoluteTransform()
	{
		UpdateTransform();
		return m_AbsoluteTransform;
	}


	/// <summary>
	/// Compute the absolute transformation for this bone.
	/// </summary>
	void SceneNode::UpdateTransform()
	{
		if (m_TransformUpdateSerial != m_TransformCacheSerial)
		{
			Matrix4 rot, scaleMatrix, trans;
			scaleMatrix.InitScaleMatrix(GetScale());
			rot.InitRotationMatrix(GetRotation());
			trans.InitTranslationMatrix(GetTranslation());

			m_Transform = trans * rot * scaleMatrix;
		}

		if (GetParent() != nullptr)
		{
			if (m_TransformUpdateSerial != m_TransformCacheSerial || m_ParentTransformUpdateSerial != GetParent()->GetTransformUpdateSerial())
			{
				// This bone has a parent bone
				m_AbsoluteTransform = m_Transform * GetParent()->GetAbsoluteTransform();

				m_ParentTransformUpdateSerial = GetParent()->GetTransformUpdateSerial();
				// It means all children need to updated except my local transform
				m_TransformUpdateSerial++;
			}
		}
		else
		{
			if (m_TransformUpdateSerial != m_TransformCacheSerial)
			{
				// This is the root bone
				m_AbsoluteTransform = m_Transform;
			}
		}

		m_TransformCacheSerial = m_TransformUpdateSerial;
	}


	void SceneNode::SetParent(SceneNode* parent)
	{
		if (m_Parent != nullptr)
		{
			if (m_Parent == parent) return;
			m_Parent->RemoveChild(this);
		}

		if(parent != nullptr)
			parent->AddChild(this);
	}

	void SceneNode::SetParentInternal(SceneNode* parent)
	{
		if (m_Parent != nullptr && parent != nullptr)
		{
			Assert(m_Parent == parent);
		}

		m_Parent = parent;
	}

	void SceneNode::UpdateRemoveChildren()
	{
		for (auto childToRemove : m_ChildrenToRemove)
		{
			m_Children.RemoveItem(childToRemove);
		}
		m_ChildrenToRemove.Clear();
	}

	void SceneNode::AddChild(SceneNode* child)
	{
		Assert(child != this);

		for (auto itChild : m_Children)
		{
			if (itChild == child)
			{
				return; // already child of this
			}
		}

		m_Children.push_back(child);

		child->SetParentInternal(this);
	}

	void SceneNode::RemoveChild(SceneNode* child)
	{
		for (auto itChild : m_Children)
		{
			if (itChild == child)
			{
				m_ChildrenToRemove.push_back(child);
				child->SetParentInternal(nullptr);
				return;
			}
		}
	}

	SceneNode* SceneNode::FindChild(FixedString nodeName)
	{
		for(auto child : m_Children)
		{
			if (child->GetName() == nodeName)
			{
				return *child;
			}
		}

		return nullptr;
	}

	/// <summary>
		/// Initialize components of all hierarchy
		/// </summary>
		/// <param name="rootNode">root node of this hierarchy. This will be used for search nodes for animation component or other link search</param>
	void SceneNode::InitializeComponents(SceneNode* rootNode)
	{
		if (rootNode == nullptr)
			rootNode = this;

		for (auto component : m_NodeComponents)
		{
			component->InitializeComponent(rootNode);
		}

		for (auto child : m_Children)
		{
			child->InitializeComponents(rootNode);
		}
	}

	/// <summary>
	/// Find child recursively
	/// </summary>
	/// <param name="nodePath">node path to find</param>
	/// <returns></returns>
	SceneNode* SceneNode::FindChildRecursively(const String& nodePath)
	{
		StaticArray<String, 10> targetPaths(GetHeap());
		nodePath.Split("/", false, targetPaths);
		SceneNode* currentNode = this;

		// Fixup root path down to one level
		if (currentNode->GetName() != FixedString(targetPaths[0]))
		{
			auto found = currentNode->FindChild(FixedString(targetPaths[0]));
			if (found == nullptr)
			{
				SFLog(Game, Error, "Animation target assign failed: Can't find root node");
				return nullptr;
			}

			currentNode = found;
		}

		for (uint depth = 1; depth < targetPaths.size(); depth++)
		{
			currentNode = currentNode->FindChild(FixedString(targetPaths[depth]));
			if (currentNode == nullptr)
			{
				SFLog(Game, Error, "Animation target assign failed: Can't find node");
				return nullptr;
			}
		}

		return currentNode;
	}

	Result SceneNode::CopyProperties(const SceneCloneContext& cloneFlags, SceneNode* pScrNode)
	{
		m_Rotation = pScrNode->m_Rotation;
		m_Translation = pScrNode->m_Translation;
		m_Scale = pScrNode->m_Scale;

		return ResultCode::SUCCESS;
	}

	SceneNode* SceneNode::Clone(const SceneCloneContext& cloneFlags)
	{
		auto newNode = new(cloneFlags.Heap) SceneNode(cloneFlags.Heap);

		newNode->CopyProperties(cloneFlags, this);

		for (auto component : m_NodeComponents)
		{
			auto clonedComponent = component->Clone(cloneFlags, newNode);
			Assert(clonedComponent->GetOwner() == newNode);
			newNode->AddComponent(clonedComponent);
		}

		for(auto child : m_Children)
		{
			auto clonedChild = child->Clone(cloneFlags);
			newNode->AddChild(clonedChild);
		}

		return newNode;
	}



}; // namespace SF

