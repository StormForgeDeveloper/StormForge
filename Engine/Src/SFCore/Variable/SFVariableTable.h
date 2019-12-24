////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable table
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFFixedString.h"
#include "String/SFString.h"
#include "Variable/SFVariable.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFSortedArray.h"

namespace SF {



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	class VariableTable
	{
	private:

		// TODO: memory optimization, use heap

		// heap for variables
		IHeap& m_Heap;

		// Variable 
		SortedArray<FixedString, Variable*, true, false> m_VairableTable;

	public:

		VariableTable(IHeap& heap);
		virtual ~VariableTable();

		IHeap& GetHeap() { return m_Heap; }

		// Get/Set variable
		virtual Result SetVariable(FixedString name, const Variable& variable);
		Variable* GetVariable(FixedString name);

		// Get/Set values
		template<class ValueType>
		Result SetValue(FixedString name, ValueType value)
		{
			auto boxedValue = Boxing(value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(*boxedValue.GetVariable());
		}

		template<class ValueType>
		ValueType GetValue(FixedString name)
		{
			Variable* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}

	};


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container, thread safe version
	//

	class VariableTableMT
	{
	private:

		// TODO: memory optimize

		// heap for variables
		IHeap& m_Heap;

		// Variable 
		DualSortedMap<FixedString, Variable*> m_VairableTable;

	public:

		VariableTableMT(IHeap& heap);

		virtual ~VariableTableMT();

		IHeap& GetHeap() { return m_Heap; }

		virtual Result SetVariable(FixedString name, const Variable& variable);


		template<class ValueType>
		Result SetValue(FixedString name, ValueType value)
		{
			auto boxedValue = Boxing(value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(*boxedValue.GetVariable());
		}


		Variable* GetVariable(FixedString name);

		template<class ValueType>
		ValueType GetValue(FixedString name)
		{
			Variable* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}

	};



} // namespace SF




