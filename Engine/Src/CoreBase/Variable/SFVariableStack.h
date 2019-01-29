////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable stack
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFFixedString.h"
#include "String/SFString.h"
#include "Variable/SFVariable.h"
#include "Memory/SFStackHeap.h"
#include "Container/SFSortedArray.h"


namespace SF {



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable stack container
	//

	class VariableStack
	{
	private:

		// TODO: memory optimization, use heap

		// heap for variables
		SharedPointerT<StackHeap<2048>> m_Heap;

		// Variable 
		StaticArray<Variable*,20> m_Vairables;

	public:

		VariableStack(IHeap& heap);
		virtual ~VariableStack();

		IHeap& GetHeap() { return **m_Heap; }

		// Push/Pop variable
		Result Push(const Variable& variable);
		Variable* GetFromFront(int offset = 0);
		Result Pop(size_t count = 1);

		size_t size() const { return m_Vairables.size(); }

		// Get/Set values
		template<class ValueType>
		Result PushValue(ValueType value)
		{
			auto boxedValue = Boxing(value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return Push(*boxedValue.GetVariable());
		}

		template<class ValueType>
		ValueType PopValue()
		{
			Variable* pVariable = GetFront();
			if (pVariable == nullptr)
				return DefaultValue<ValueType>();

			// After pop call, the variable already released
			auto result = pVariable->GetValue<ValueType>();

			Pop();

			return result;
		}

	};



} // namespace SF




