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
#include "String/SFFixedString.h"
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
		FixedString m_Name;

		// flags
		bool m_IsInitialized;

		SortedSet<FixedString> m_Dependencies;

	public:
		LibraryComponent(const FixedString& name) : m_Name(name), m_IsInitialized(false), m_Dependencies(GetSystemHeap()){}
		virtual ~LibraryComponent() {}

		const FixedString& GetName() { return m_Name; }
		virtual const FixedString& GetTypeName() = 0;

		// Check wheather this component is initialized or not
		bool GetIsInitialized() const { return m_IsInitialized; }

		// Add component depency
		template<class ComponentType>
		void AddDependency()
		{
			m_Dependencies.Set(ComponentType::TypeName);
		}

		// Add dependency with name
		void AddDependency(FixedString dependencyName)
		{
			m_Dependencies.Set(dependencyName);
		}


		// Get component dependencies
		const SortedSet<FixedString>& GetDependencies() const { return m_Dependencies; }

		// Initialize component
		virtual Result InitializeComponent() { m_IsInitialized = true; return ResultCode::SUCCESS; }
		// Terminate component
		virtual void DeinitializeComponent() { m_IsInitialized = false;  }
	};





} // namespace SF




