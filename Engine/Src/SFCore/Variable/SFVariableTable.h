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
#include "String/SFStringCrc64.h"
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
	public:

		using Iterator = SortedArray<StringCrc64, Variable*, true, false>::Iterator;

	private:

		// TODO: memory optimization, use heap

		// heap for variables
		IHeap& m_Heap;

		// Variable 
		SortedArray<StringCrc64, Variable*, true, false> m_VairableTable;

	public:

		VariableTable(IHeap& heap);
		virtual ~VariableTable();

		IHeap& GetHeap() { return m_Heap; }

		size_t size() const { return m_VairableTable.size(); }
		Iterator begin() { return m_VairableTable.begin(); }
		const Iterator begin() const { return m_VairableTable.begin(); }
		Iterator end() { return m_VairableTable.end(); }
		const Iterator end() const { return m_VairableTable.end(); }

		// Set variable, contents will be copied
		virtual Result SetVariable(StringCrc64 name, const Variable& variable);

		// Set variable, it will take over the pointer owner ship
		virtual Result SetVariable(StringCrc64 name, std::unique_ptr<Variable>& variable);
		virtual Result SetVariable(StringCrc64 name, Variable*& variable);

		// Get variable
		Variable* GetVariable(StringCrc64 name);

		// Get/Set values
		template<class ValueType>
		Result SetValue(StringCrc64 name, ValueType value)
		{
			auto boxedValue = Boxing(value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(*boxedValue.GetVariable());
		}

		template<class ValueType>
		ValueType GetValue(StringCrc64 name)
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
		DualSortedMap<StringCrc64, Variable*> m_VairableTable;

	public:

		VariableTableMT(IHeap& heap);

		virtual ~VariableTableMT();

		IHeap& GetHeap() { return m_Heap; }

		virtual Result SetVariable(StringCrc64 name, const Variable& variable);


		template<class ValueType>
		Result SetValue(StringCrc64 name, ValueType value)
		{
			auto boxedValue = Boxing(value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(*boxedValue.GetVariable());
		}


		Variable* GetVariable(StringCrc64 name);

		template<class ValueType>
		ValueType GetValue(StringCrc64 name)
		{
			Variable* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}

	};



} // namespace SF




