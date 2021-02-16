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

		SortedSet<StringCrc64> m_Dependencies;

	public:
		LibraryComponent(const StringCrc64& name);
		virtual ~LibraryComponent() {}

		const StringCrc64& GetName() { return m_Name; }
		virtual const StringCrc64& GetTypeName() = 0;

		// Check whether this component is initialized or not
		bool GetIsInitialized() const { return m_IsInitialized; }

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
	};





} // namespace SF




