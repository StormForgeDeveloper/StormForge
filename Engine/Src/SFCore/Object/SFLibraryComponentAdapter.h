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
#include "String/SFStringCrc64.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Object/SFLibraryComponent.h"


namespace SF {


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	LibraryComponent Adapter class
	//		Our memory model has problem with multiple inheritance. This adapter will help to add regular SharedObject as a component
	//

	template<class ClassType, class ... ParamTypes>
	class LibraryComponentAdapter : public LibraryComponent
	{
	public:
		static constexpr StringCrc64 TypeName = ClassType::TypeName;

	private:

		IHeap& m_Heap;

		SharedPointerT<ClassType> m_Object;

	public:

		// Constructor
		LibraryComponentAdapter(IHeap& heap, ParamTypes...args)
			: LibraryComponent(TypeName)
			, m_Heap(heap)
		{
			m_Object = new(heap) ClassType(args...);
		}
		~LibraryComponentAdapter()
		{
			m_Object = nullptr;
		}

		// Heap
		IHeap& GetHeap() { return m_Heap; }

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		ClassType* operator ->() { return *m_Object; }
		ClassType* operator *() { return *m_Object; }

		// Initialize component
		virtual Result InitializeComponent() override
		{
			if (GetIsInitialized())
				return ResultCode::SUCCESS;
			LibraryComponent::InitializeComponent();
			return m_Object->InitializeComponent();
		}

		// Terminate component
		virtual void DeinitializeComponent() override
		{
			if (!GetIsInitialized())
				return;

			m_Object->DeinitializeComponent();
			LibraryComponent::DeinitializeComponent();
		}
	};



} // namespace SF




