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
		virtual Result InitializeComponent() { m_IsInitialized = true; return ResultCode::SUCCESS; }
		// Terminate server component
		virtual void TerminateComponent() { m_IsInitialized = false;  }

		virtual void TickUpdate() {}
	};



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Component career base class
	//

	// deprecated
	template< size_t MaxComponentID >
	class [[deprecated("Use ComponentManager")]] ComponentCarrier
	{
	public:

	private:

		IHeap& m_Heap;

		// component array
		Component* m_Components[MaxComponentID+1];

	public:
		ComponentCarrier(IHeap& memoryManager)
			: m_Heap(memoryManager)
		{
			memset( m_Components, 0, sizeof(Component*)*(MaxComponentID+1) );
		}

		virtual ~ComponentCarrier()
		{
			for (size_t iComponent = 0; iComponent < (MaxComponentID + 1); iComponent++)
			{
				if (m_Components[iComponent] != nullptr)
					m_Components[iComponent]->TerminateComponent();
				IHeap::Delete( m_Components[iComponent] );
			}
		}

		IHeap& GetHeap() { return m_Heap; }

		// Clear components
		virtual void ClearComponents()
		{
			for(size_t iComponent = 0; iComponent < (MaxComponentID+1); iComponent++ )
			{
				if( m_Components[iComponent] != nullptr )
					m_Components[iComponent]->TerminateComponent();
			}
		}
		
		// Initialize components
		virtual Result InitializeComponents()
		{
			Result hr = ResultCode::SUCCESS;
			size_t iComponent = 0;
			for( ; iComponent < (MaxComponentID+1); iComponent++ )
			{
				if( m_Components[iComponent] != nullptr )
				{
					if( m_Components[iComponent]->GetIsInitialized() )
						m_Components[iComponent]->TerminateComponent();

					hr = m_Components[iComponent]->InitializeComponent();
					if (!hr) return hr;
				}
			}

			return hr;
		}

		Result TerminateComponents()
		{
			Result hr = ResultCode::SUCCESS;
			// Terminate in reverse order
			int iComponent = (int)MaxComponentID;
			for (; iComponent >= 0; iComponent--)
			{
				if (m_Components[iComponent] != nullptr)
				{
					m_Components[iComponent]->TerminateComponent();
				}
			}

			return hr;
		}

		// Add component
		Component* RemoveComponent(unsigned int iComponent)
		{
			if (m_Components[iComponent] != nullptr)
			{
				m_Components[iComponent]->TerminateComponent();
			}

			return m_Components[iComponent];
		}

		template< class ComponentType >
		ComponentType* RemoveComponent()
		{
			uint iComponent = ComponentType::ComponentID;
			if (iComponent >= (MaxComponentID + 1) || iComponent < 0)
				return nullptr;

			ComponentType *pComponent = m_Components[iComponent];
			m_Components[iComponent] = nullptr;

			if (pComponent != nullptr)
				pComponent->TerminateComponent();

			return pComponent;
		}

		// Add component
		template< class ComponentType >
		Result AddComponent( bool bAllowDuplicatedComponent = false )
		{
			if( !bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr )
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType;
			if( newComponent == nullptr )
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if( !(hr) )
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, class ParamType0 >
		Result AddComponent( ParamType0 p0, bool bAllowDuplicatedComponent = false )
		{
			if( !bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr )
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(p0);
			if( newComponent == nullptr )
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if( !(hr) )
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, class ParamType0, class ParamType1 >
		Result AddComponent( ParamType0 p0, ParamType1 p1, bool bAllowDuplicatedComponent = false )
		{
			if( !bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr )
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(p0,p1);
			if( newComponent == nullptr )
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if( !(hr) )
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, class ParamType0, class ParamType1, class ParamType2 >
		Result AddComponent(ParamType0 p0, ParamType1 p1, ParamType2 p2, bool bAllowDuplicatedComponent = false)
		{
			if (!bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(p0, p1, p2);
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (!(hr))
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}


		template< class ComponentType >
		Result AddComponent( ComponentType* &newComponent )
		{
			// invalid component id range
			if( newComponent->GetComponentID() >= (MaxComponentID+1) )
				return ResultCode::UNEXPECTED;

			if( m_Components[newComponent->GetComponentID()] != nullptr )
			{
				// already registered
				return ResultCode::DUPLICATED_COMPONENT;
			}

			m_Components[newComponent->GetComponentID()] = newComponent;

			OnAddComponent(newComponent);

			newComponent = nullptr;

			return ResultCode::SUCCESS;
		}

		virtual void OnAddComponent(Component* newComponent)
		{}

		// Get component with its ID
		Component* GetComponent( int ID )
		{
			if( (size_t)ID >= (MaxComponentID+1) || ID < 0 )
				return nullptr;

			return m_Components[ID];
		}

		template< class ComponentType >
		ComponentType* GetComponent(int ID)
		{
			if((size_t)ID >= (MaxComponentID+1) || ID < 0 )
				return nullptr;

			if( m_Components[ID] != nullptr )
				return dynamic_cast<ComponentType*>(m_Components[ID]);
			else
				return nullptr;
		}


		// Get component with its type
		template< class ComponentType >
		ComponentType* GetComponent()
		{
			uint ID = ComponentType::ComponentID;
			if( ID >= (MaxComponentID+1) || ID < 0 )
				return nullptr;

			if( m_Components[ID] != nullptr )
				return (ComponentType*)m_Components[ID];
			else
				return nullptr;
		}
		
		// Get component with its type
		template< class ComponentType >
		const ComponentType* GetComponent() const
		{
			uint ID = ComponentType::ComponentID;
			if( ID >= (MaxComponentID+1) || ID < 0 )
				return nullptr;

			if( m_Components[ID] != nullptr )
				return (ComponentType*)m_Components[ID];
			else
				return nullptr;
		}

		// iterate all component
		void ForeachComponent( std::function<void(Component*)> functor )
		{
			for(size_t iComponent = 0; iComponent < (MaxComponentID+1); iComponent++ )
			{
				if( m_Components[iComponent] != nullptr )
					functor(m_Components[iComponent]);
			}
		}

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
					if (!hr) return hr;
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
				if (pComponent != nullptr)
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
		Result AddComponent(bool bAllowDuplicatedComponent = false)
		{
			if (!bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType;
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (!(hr))
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, class ParamType0,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		Result AddComponent(const ParamType0& p0, bool bAllowDuplicatedComponent = false)
		{
			if (!bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(p0);
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (!hr)
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, class ParamType0, class ParamType1,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		Result AddComponent(ParamType0&& p0, ParamType1&& p1, bool bAllowDuplicatedComponent = false)
		{
			if (!bAllowDuplicatedComponent && GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(p0, p1);
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (!hr)
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}

		template< class ComponentType, class ParamType0, class ParamType1, class ParamType2,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>> >
		Result AddComponent(ParamType0 p0, ParamType1 p1, ParamType2 p2)
		{
			if (GetComponent<ComponentType>() != nullptr)
			{
				// already inserted
				return ResultCode::SUCCESS_FALSE;
			}

			ComponentType* newComponent = new(m_Heap) ComponentType(p0, p1, p2);
			if (newComponent == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			Result hr = AddComponent(newComponent);
			if (!hr)
			{
				IHeap::Delete(newComponent);
			}

			return hr;
		}


		template< class ComponentType,
			typename = std::enable_if_t<std::is_base_of_v<Component, ComponentType>>>
		Result AddComponent(ComponentType*& newComponent)
		{
			if (m_Components.find(newComponent->GetComponentID()) != nullptr)
			{
				// already registered
				return ResultCode::DUPLICATED_COMPONENT;
			}

			m_Components.Insert(ComponentType::ComponentID, newComponent);

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
			return m_Components.find(ID);
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
				if (itComponent.GetValue() != nullptr)
					functor(itComponent.GetValue());
			}
		}


		virtual void TickUpdate()
		{
			for (auto itComponent : m_Components)
			{
				if (itComponent.GetValue() != nullptr)
					itComponent.GetValue()->TickUpdate();
			}
		}
	};

} // namespace SF

