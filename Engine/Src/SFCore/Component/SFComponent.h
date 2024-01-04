////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : Component class definition
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "ResultCode/SFResultCodeLibrary.h"


namespace SF
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	IComponent base class
	//

	class Component
	{
	private:

		unsigned int m_ComponentID = 0;
		bool m_IsInitialized = false;

	public:
		Component( unsigned int id ) : m_ComponentID(id), m_IsInitialized(false) {}
		virtual ~Component() {}

		uint GetComponentID() { return m_ComponentID; }
		bool GetIsInitialized() { return m_IsInitialized; }

		// Initialize server component
		virtual Result InitializeComponent()
        {
            m_IsInitialized = true;
            return ResultCode::SUCCESS;
        }

		// Terminate server component
        virtual Result TerminateComponent()
        {
            m_IsInitialized = false;
            return ResultCode::SUCCESS;
        }

		virtual void TickUpdate() {}
	};



	// Using hashed name to maintain components
	class ComponentManager
	{
	public:

	private:

		IHeap& m_Heap;

		bool m_IsInitialized = false;

		// component array
		SortedArray<StringCrc32,Component*> m_Components;

	public:
		ComponentManager(IHeap& heap)
			: m_Heap(heap)
			, m_Components(m_Heap)
		{
		}

		virtual ~ComponentManager()
		{
			for (auto itComponent : m_Components)
			{
				if (itComponent.GetValue())
					itComponent.GetValue()->TerminateComponent();
				IHeap::Delete(itComponent.GetValue());
			}
			m_Components.Clear();
		}

		IHeap& GetHeap() { return m_Heap; }

		// Clear components
		virtual void ClearComponents()
		{
			for (auto itComponent : m_Components)
			{
				if (itComponent.GetValue())
					itComponent.GetValue()->TerminateComponent();
				IHeap::Delete(itComponent.GetValue());
			}
			m_Components.Clear();
		}

		// Initialize components
		virtual Result InitializeComponents()
		{
			ScopeContext hr = ResultCode::SUCCESS;

			for (auto itComponent : m_Components)
			{
				auto pComponent = itComponent.GetValue();
				if (pComponent)
				{
					if (pComponent->GetIsInitialized())
						pComponent->TerminateComponent();

					hr = pComponent->InitializeComponent();
					if (!hr.IsSuccess()) return hr;
				}
			}

			m_IsInitialized = true;

			return hr;
		}

		Result TerminateComponents()
		{
			ScopeContext hr = ResultCode::SUCCESS;
			// Terminate in reverse order
			for (auto itComponent : m_Components)
			{
				auto pComponent = itComponent.GetValue();
				if (pComponent != nullptr && pComponent->GetIsInitialized())
				{
					pComponent->TerminateComponent();
				}
			}

			m_IsInitialized = false;

			return hr;
		}

		auto begin() { return m_Components.begin(); }
		auto end() { return m_Components.end(); }

		// Add component
		Component* RemoveComponent(StringCrc32 name)
		{
			Component* pComponent = nullptr;
			m_Components.Remove(name, pComponent);

			if (pComponent != nullptr)
			{
				pComponent->TerminateComponent();
			}

			
			return pComponent;
		}

		template< class ComponentType,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>> >
		ComponentType* RemoveComponent()
		{
			return static_cast<ComponentType*>(RemoveComponent(ComponentType::ComponentID));
		}

		// Add component
		template< class ComponentType,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		Result AddComponent()
		{
			if (GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType;
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (hr.IsFailure())
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, typename ...ArgTypes,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		Result AddComponent(ArgTypes&&... args)
		{
			if (GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(args...);
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (!hr.IsSuccess())
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		//template< class ComponentType, class ParamType0, class ParamType1,
		//	typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		//Result AddComponent(ParamType0&& p0, ParamType1&& p1)
		//{
		//	if (GetComponent<ComponentType>() != nullptr)
		//	{
		//		// already inserted
		//		return ResultCode::SUCCESS_FALSE;
		//	}

		//	ComponentType* newComponent = new(m_Heap) ComponentType(p0, p1);
		//	if (newComponent == nullptr)
		//		return ResultCode::OUT_OF_MEMORY;

		//	Result hr = AddComponent(newComponent);
		//	if (!hr.IsSuccess())
		//	{
		//		IHeap::Delete(newComponent);
		//	}

		//	return hr;
		//}

		//template< class ComponentType, class ParamType0, class ParamType1, class ParamType2,
		//	typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>> >
		//Result AddComponent(ParamType0 p0, ParamType1 p1, ParamType2 p2)
		//{
		//	if (GetComponent<ComponentType>() != nullptr)
		//	{
		//		// already inserted
		//		return ResultCode::SUCCESS_FALSE;
		//	}

		//	ComponentType* newComponent = new(m_Heap) ComponentType(p0, p1, p2);
		//	if (newComponent == nullptr)
		//		return ResultCode::OUT_OF_MEMORY;

		//	Result hr = AddComponent(newComponent);
		//	if (!hr.IsSuccess())
		//	{
		//		IHeap::Delete(newComponent);
		//	}

		//	return hr;
		//}


		template< class ComponentType,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		Result AddComponent(ComponentType*& newComponent)
		{
			if (m_Components.find(newComponent->GetComponentID()) != nullptr)
			{
				// already registered
				return ResultCode::DUPLICATED_COMPONENT;
			}

			m_Components.Insert(newComponent->GetComponentID(), newComponent);

			if (m_IsInitialized && !newComponent->GetIsInitialized())
				newComponent->InitializeComponent();

			OnAddComponent(newComponent);

			newComponent = nullptr;

			return ResultCode::SUCCESS;
		}

		virtual void OnAddComponent(Component* newComponent) {}

		// Get component with its ID
		Component* GetComponent(StringCrc32 ID) const
		{
			return m_Components.find(ID);
		}

		template< class ComponentType,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>> >
		ComponentType* GetComponent(StringCrc32 ID) const
		{
			return static_cast<ComponentType*>(m_Components.find(ID));
		}


		// Get component with its type
		template< class ComponentType,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>> >
		ComponentType* GetComponent() const
		{
			return static_cast<ComponentType*>(GetComponent(ComponentType::ComponentID));
		}

		// iterate all component
		void ForeachComponent(std::function<void(Component*)> functor)
		{
			for (auto itComponent : m_Components)
			{
				auto pComponent = itComponent.GetValue();
				if (pComponent != nullptr)
					functor(pComponent);
			}
		}


		virtual void TickUpdate()
		{
			for (auto itComponent : m_Components)
			{
				auto pComponent = itComponent.GetValue();
				if (pComponent != nullptr)
					pComponent->TickUpdate();
			}
		}
	};

} // namespace SF

