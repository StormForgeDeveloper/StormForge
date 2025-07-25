////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine Component class
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Util/SFStringCrc64.h"
#include "Container/SFSortedArray.h"
#include "Container/SFArray.h"
#include "Component/SFLibraryComponent.h"




namespace SF {

    class LibraryComponent;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Component career base class
	//

	class LibraryComponentManager
	{
	public:

	private:

        DynamicArray<LibraryComponent*> m_Components;
		SortedArray<StringCrc64, LibraryComponent*> m_ComponentByName;
		SortedArray<StringCrc64, LibraryComponent*> m_ComponentByTypeName;

        // tickable components
        DynamicArray<LibraryComponent*> m_TickableComponents;

		bool m_IsInitialized;

	private:

		// initialize component and its dependencies
		Result InitializeComponent(LibraryComponent* pComponent);

	public:


		// Constructor
		LibraryComponentManager();
		virtual ~LibraryComponentManager();

		virtual IHeap& GetHeap() { return GetSystemHeap(); }

		// Clear components
		virtual void ClearComponents();
		
		
		// Initialize components
		virtual Result InitializeComponents();
		virtual Result DeinitializeComponents();

		// Add component
		LibraryComponent* RemoveComponent(LibraryComponent* pComponent);
		LibraryComponent* RemoveComponent(const StringCrc64& name);

		template< class ComponentType >
		ComponentType* RemoveComponent()
		{
			return static_cast<ComponentType*>( RemoveComponent(ComponentType::TypeName) );
		}


		virtual void OnAddComponent(LibraryComponent* newComponent)	{}

		Result AddComponent(LibraryComponent* newComponent);

		template<class ComponentType>
		ComponentType* AddComponent()
		{
			auto newComponent = new ComponentType;
			AddComponent(newComponent);
			return newComponent;
		}

		template<class ComponentType, class ...ArgTypes>
		ComponentType* AddComponent(ArgTypes... args)
		{
			auto newComponent = new ComponentType(args...);
			AddComponent(newComponent);
			return newComponent;
		}


		// Get component with name
		LibraryComponent* GetComponentByName(const StringCrc64& name);

		// Get component with typename
		LibraryComponent* GetComponentByType(const StringCrc64& typeName);

		template< class ComponentType >
		ComponentType* GetComponent()
		{
			return static_cast<ComponentType*>(GetComponentByType(ComponentType::TypeName) );
		}

		// iterate all component
		template<class FuncType>
		void ForeachComponent(FuncType functor)
		{
			m_ComponentByName.ForeachOrder(0, m_ComponentByName.size(), functor);
		}


        // Tick update, called from engine tick update
        virtual void ComponentTickUpdate();
	};

} // namespace SF

