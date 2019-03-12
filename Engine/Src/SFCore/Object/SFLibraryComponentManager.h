////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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
#include "String/SFFixedString.h"
#include "Container/SFSortedArray.h"
#include "Object/SFLibraryComponent.h"




namespace SF {



	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Component career base class
	//

	class LibraryComponentManager
	{
	public:

	private:


		SortedArray<FixedString, LibraryComponent*> m_ComponentByName;
		SortedArray<FixedString, LibraryComponent*> m_ComponentByTypeName;

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
		LibraryComponent* RemoveComponent(const FixedString& name);

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
			auto newComponent = new(GetHeap()) ComponentType();
			AddComponent(newComponent);
			return newComponent;
		}

		template<class ComponentType, class ...ArgTypes>
		ComponentType* AddComponent(ArgTypes... args)
		{
			auto newComponent = new(GetHeap()) ComponentType(args...);
			AddComponent(newComponent);
			return newComponent;
		}


		// Get component with name
		LibraryComponent* GetComponentByName(const FixedString& name);

		// Get component with typename
		LibraryComponent* GetComponentByType(const FixedString& typeName);

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
	};







} // namespace SF




