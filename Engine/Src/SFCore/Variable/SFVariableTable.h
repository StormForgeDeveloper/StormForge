////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable table
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Variable/SFVariable.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFSortedArray.h"

namespace Json
{
    class Value;
}

namespace SF {


	class NamedVariableArray;

	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	class VariableTable
	{
	public:

		using KeyType = StringCrc32;
		using Iterator = SortedArray<KeyType, Variable*, true, false>::Iterator;

	private:

		// TODO: memory optimization, use heap

		// heap for variables
		IHeap& m_Heap;

		// Variable 
		SortedArray<KeyType, Variable*, true, false> m_VariableTable;

	public:

		VariableTable(IHeap& heap = GetEngineHeap());
		VariableTable(IHeap& heap, const VariableTable& src);
		VariableTable(const VariableTable& src);
		virtual ~VariableTable();

		IHeap& GetHeap() { return m_Heap; }

		void Clear();
		void Reset() { Clear(); }

		size_t size() const { return m_VariableTable.size(); }
		Iterator begin() { return m_VariableTable.begin(); }
		const Iterator begin() const { return m_VariableTable.begin(); }
		Iterator end() { return m_VariableTable.end(); }
		const Iterator end() const { return m_VariableTable.end(); }

		// Set variable, contents will be copied
		virtual Result SetVariable(KeyType name, const Variable& variable);

		// Set variable, it will take over the pointer owner ship
		virtual Result SetVariable(KeyType name, SFUniquePtr<Variable>& variable);
		virtual Result SetVariable(KeyType name, Variable*& variable);

		virtual Result Remove(KeyType name);

		void Remove(KeyType name, SFUniquePtr<Variable>& removed)
		{
			Variable* pVariable{};
			m_VariableTable.Remove(name, pVariable);
			removed.reset(pVariable);
		}

		// Get variable
		Variable* GetVariable(KeyType name);
		const Variable* GetVariable(KeyType name) const;

		// TODO: need to make it safer with string
		// Get/Set values
		template<class ValueType>
		Result SetValue(KeyType name, const ValueType& value)
		{
			auto boxedValue = BoxingByValue(GetHeap(), value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(name , *boxedValue.GetVariable());
		}

		template<class ValueType>
		ValueType GetValue(KeyType name) const
		{
			auto* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}

		const Array<uint8_t>& GetValueBLOB(KeyType name) const
		{
			static StaticArray<uint8_t, 1> dummy;
			auto* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return dummy;

			return pVariable->GetValueBLOB();
		}


		bool operator == (const VariableTable& src) const
		{
			if (size() != src.size())
				return false;

			for (auto& itItem : m_VariableTable)
			{
				auto pSrcVar = src.GetVariable(itItem.GetKey());
				if (*pSrcVar != *itItem.GetValue())
					return false;
			}

			return true;
		}

		// parse from bin data
		Result FromBinData(const Array<uint8_t>&);

		VariableTable& operator = (const VariableTable& src);
		VariableTable& operator = (VariableTable&& src);

		VariableTable& operator = (const NamedVariableArray& src);
		VariableTable& operator = (NamedVariableArray&& src);

        friend Result operator >> (const Json::Value& src, VariableTable& dest);
        friend Result operator << (Json::Value& dest, const VariableTable& src);
	};


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container, thread safe version
	//

	class VariableTableMT
	{
	public:

		using KeyType = StringCrc32;

	private:

		// TODO: memory optimize

		// heap for variables
		IHeap& m_Heap;

		// Variable 
		DualSortedMap<KeyType, Variable*> m_VariableTable;

	public:

		VariableTableMT(IHeap& heap);

		virtual ~VariableTableMT();

		IHeap& GetHeap() { return m_Heap; }

		virtual Result SetVariable(KeyType name, const Variable& variable);


		template<class ValueType>
		Result SetValue(KeyType name, ValueType value)
		{
			auto boxedValue = Boxing(GetHeap(), value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(*boxedValue.GetVariable());
		}


		Variable* GetVariable(KeyType name);

		template<class ValueType>
		ValueType GetValue(KeyType name)
		{
			Variable* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}
	};

} // namespace SF

