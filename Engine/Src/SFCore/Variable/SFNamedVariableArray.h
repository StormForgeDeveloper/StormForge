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

namespace SF {



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	class NamedVariableArray
	{
	public:

		using KeyType = StringCrc32;
		struct Item
		{
			KeyType Key{};
			Variable* Value{};

			SF_FORCEINLINE KeyType GetKey() const { return Key; }
			SF_FORCEINLINE Variable* GetValue() const { return Value; }
		};
		using Iterator = Array<Item>::iterator;

	private:

		// Variable 
		DynamicArray<Item> m_VariableArray;

	public:

		NamedVariableArray();
		NamedVariableArray(const NamedVariableArray& src);
		virtual ~NamedVariableArray();

		void Clear();
		void Reset() { Clear(); }

		size_t size() const { return m_VariableArray.size(); }
		Iterator begin() { return m_VariableArray.begin(); }
		const Iterator begin() const { return m_VariableArray.begin(); }
		Iterator end() { return m_VariableArray.end(); }
		const Iterator end() const { return m_VariableArray.end(); }

		// Contents will be copied
		Result AddVariable(KeyType name, const Variable& variable);
		Result SetVariable(KeyType name, const Variable& variable);

		// It will take over the pointer owner ship
		Result AddVariable(KeyType name, SFUniquePtr<Variable>& variable);
		Result SetVariable(KeyType name, SFUniquePtr<Variable>& variable);

		// Find index of the variable
		int FindIndex(KeyType name) const;

		// delete variable
		SF_FORCEINLINE void Remove(KeyType name)
		{
			Remove(FindIndex(name));
		}

		void Remove(int iVar)
		{
			if (iVar >= 0)
			{
				delete (m_VariableArray[iVar].Value);
				m_VariableArray.RemoveAt(iVar);
			}
		}

		void Remove(int iVar, SFUniquePtr<Variable>& removed)
		{
			if (iVar >= 0)
			{
				removed.reset(m_VariableArray[iVar].Value);
				m_VariableArray.RemoveAt(iVar);
			}
		}

		SF_FORCEINLINE void Remove(KeyType name, SFUniquePtr<Variable>& removed)
		{
			Remove(FindIndex(name), removed);
		}

		// Get variable
		SF_FORCEINLINE Variable* GetVariable(KeyType name)
		{
			int iVar = FindIndex(name);
			if (iVar >= 0)
				return m_VariableArray[iVar].Value;

			return nullptr;
		}

		SF_FORCEINLINE const Variable* GetVariable(KeyType name) const
		{
			int iVar = FindIndex(name);
			if (iVar >= 0)
				return m_VariableArray[iVar].Value;

			return nullptr;
		}
		SF_FORCEINLINE Variable* GetVariable(int iVar)
		{
			if (iVar >= 0)
				return m_VariableArray[iVar].Value;

			return nullptr;
		}
		SF_FORCEINLINE const Variable* GetVariable(int iVar) const
		{
			if (iVar >= 0)
				return m_VariableArray[iVar].Value;

			return nullptr;
		}

		// TODO: need to make it safer with string
		// Get/Set values
		template<class ValueType>
		SF_FORCEINLINE Result SetValue(KeyType name, const ValueType& value)
		{
			auto boxedValue = BoxingByValue(value);
			if (boxedValue.GetVariable() == nullptr)
				return ResultCode::NOT_SUPPORTED;

			return SetVariable(name , *boxedValue.GetVariable());
		}

		template<class ValueType>
		SF_FORCEINLINE ValueType GetValue(KeyType name) const
		{
			auto* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}

		SF_FORCEINLINE const Array<uint8_t>& GetValueBLOB(KeyType name) const
		{
			static StaticArray<uint8_t, 1> dummy;
			auto* pVariable = GetVariable(name);
			if (pVariable == nullptr)
				return dummy;

			return pVariable->GetValueBLOB();
		}


		bool operator == (const NamedVariableArray& src) const
		{
			if (size() != src.size())
				return false;

			for (auto& itItem : m_VariableArray)
			{
				auto pSrcVar = src.GetVariable(itItem.Key);
				if (*pSrcVar != *itItem.Value)
					return false;
			}

			return true;
		}


		NamedVariableArray& operator = (const NamedVariableArray& src);
		NamedVariableArray& operator = (NamedVariableArray&& src);
	};

} // namespace SF

