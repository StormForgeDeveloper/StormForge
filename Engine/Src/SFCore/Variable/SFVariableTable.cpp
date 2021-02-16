////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable table
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Variable/SFVariableTable.h"



namespace SF {




	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	VariableTable::VariableTable(IHeap& heap)
		: m_Heap(heap)
		, m_VairableTable(heap)
	{
	}

	VariableTable::~VariableTable()
	{
		Clear();
	}

	void  VariableTable::Clear()
	{
		m_VairableTable.CommitChanges();
		m_VairableTable.ForeachOrder(0, (uint)m_VairableTable.size(), [](KeyType name, Variable* pValue)
		{
			unused(name);
			IHeap::Delete(pValue);
			return true;
		});

		m_VairableTable.Clear();
	}

	Result VariableTable::SetVariable(KeyType name, const Variable& variable)
	{
		Variable* pVariable = nullptr;
		m_VairableTable.Remove(name, pVariable);
		if (pVariable != nullptr)
		{
			IHeap::Delete(pVariable);
		}

		auto newVariable = variable.Clone(GetHeap());

		return m_VairableTable.Set(name, newVariable);
	}

	Result VariableTable::SetVariable(KeyType name, SFUniquePtr<Variable>& variable)
	{
		Variable* pVariable = nullptr;
		m_VairableTable.Remove(name, pVariable);
		if (pVariable != nullptr)
		{
			IHeap::Delete(pVariable);
		}

		auto Ret = m_VairableTable.Set(name, variable.get());
		if (Ret)
		{
			variable.release();
		}
		return Ret;
	}

	Result VariableTable::SetVariable(KeyType name, Variable*& variable)
	{
		Variable* pVariable = nullptr;
		m_VairableTable.Remove(name, pVariable);
		if (pVariable != nullptr)
		{
			IHeap::Delete(pVariable);
		}

		if (variable == nullptr)
			return ResultCode::INVALID_ARG;

		auto Ret = m_VairableTable.Set(name, variable);
		if (Ret)
		{
			variable = nullptr;
		}
		return Ret;
	}


	Variable* VariableTable::GetVariable(KeyType name)
	{
		Variable* pVariable = nullptr;

		m_VairableTable.Find(name, pVariable);

		return pVariable;
	}

	const Variable* VariableTable::GetVariable(KeyType name) const
	{
		Variable* pVariable = nullptr;

		m_VairableTable.Find(name, pVariable);

		return pVariable;
	}



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	VariableTableMT::VariableTableMT(IHeap& heap)
		: m_Heap(heap)
		, m_VairableTable(heap)
	{
	}

	VariableTableMT::~VariableTableMT()
	{
		m_VairableTable.CommitChanges();
		m_VairableTable.ForeachOrder(0, (uint)m_VairableTable.size(), [](KeyType name, Variable* pValue)
		{
			unused(name);
			IHeap::Delete(pValue);
			return true;
		});
	}

	Result VariableTableMT::SetVariable(KeyType name, const Variable& variable)
	{
		// TODO: need to be thread safe
		Variable* pVariable = nullptr;
		m_VairableTable.Remove(name, pVariable);

		auto varSize = (uint32_t)variable.GetVariableSize();
		uint8_t* pBuffer = nullptr;
		if (pVariable != nullptr)
		{
			auto orgVarSize = pVariable->GetVariableSize();
			pVariable->~Variable();

			if (orgVarSize == varSize)
			{
				pBuffer = reinterpret_cast<uint8_t*>(pVariable);
			}
			else
			{
				IHeap::Delete(reinterpret_cast<uint8_t*>(pVariable));
				pBuffer = new(GetHeap()) uint8_t[varSize];
			}
		}
		else
		{
			pBuffer = new(GetHeap()) uint8_t[varSize];
		}

		Array<uint8_t> tempBuff(varSize, reinterpret_cast<uint8_t*>(pBuffer));
		pVariable = variable.Clone(tempBuff);
		return m_VairableTable.Insert(name, pVariable);
	}


	Variable* VariableTableMT::GetVariable(KeyType name)
	{
		Variable* pVariable = nullptr;

		m_VairableTable.Find(name, pVariable);

		return pVariable;
	}






} // namespace SF

