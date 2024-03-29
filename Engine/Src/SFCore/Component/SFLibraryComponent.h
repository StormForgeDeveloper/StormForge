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
#include "Util/SFStringCrc64.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Container/SFSortedSet.h"


namespace SF {

	class LibraryComponentManager;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	LibraryComponent base class
	//

	class LibraryComponent
	{
	public:

	private:

		// Component name
		StringCrc64 m_Name;

		// flags
		bool m_IsInitialized;
        bool m_IsTickable = false;

		SortedSet<StringCrc64> m_Dependencies;

		friend class LibraryComponentManager;

	public:
		LibraryComponent(const StringCrc64& name, bool bIsTickable = false);
		virtual ~LibraryComponent() {}

		const StringCrc64& GetName() const { return m_Name; }
		virtual const StringCrc64& GetTypeName() const = 0;

		// Check whether this component is initialized or not
		bool GetIsInitialized() const { return m_IsInitialized; }

        bool IsTickable() const { return m_IsTickable; }

		// Add component dependency
		template<class ComponentType>
		void AddDependency()
		{
			m_Dependencies.Set(ComponentType::TypeName);
		}

		// Add dependency with name
		void AddDependency(StringCrc64 dependencyName)
		{
			m_Dependencies.Set(dependencyName);
		}


		// Get component dependencies
		const SortedSet<StringCrc64>& GetDependencies() const { return m_Dependencies; }

		// Initialize component
		virtual Result InitializeComponent() { m_IsInitialized = true; return ResultCode::SUCCESS; }
		// Terminate component
		virtual void DeinitializeComponent() { m_IsInitialized = false;  }

        // Tick update, called from engine tick update
        virtual void TickUpdate() {}
	};





} // namespace SF




