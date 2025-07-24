////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Variable/SFNamedVariableArray.h"
#include "Variable/SFVariableSerialization.h"
#include "Stream/SFMemoryStream.h"


namespace SF {


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	NamedVariableArray::NamedVariableArray()
	{
	}

	NamedVariableArray::NamedVariableArray(const NamedVariableArray& src)
	{
		for (auto& itVariable : src)
		{
			SetVariable(itVariable.Key, *itVariable.Value);
		}
	}

	NamedVariableArray::~NamedVariableArray()
	{
		Clear();
	}

	void  NamedVariableArray::Clear()
	{
		for (auto& itItem : m_VariableArray)
		{
			delete (itItem.Value);
		}

		m_VariableArray.Clear();
	}

	int NamedVariableArray::FindIndex(KeyType name) const
	{
		for (int iVar = 0; iVar < m_VariableArray.size(); iVar++)
		{
			if (m_VariableArray[iVar].Key == name)
				return iVar;
		}

		return -1;
	}

	Result NamedVariableArray::AddVariable(KeyType name, const Variable& variable)
	{
		auto newVariable = variable.Clone();

		return m_VariableArray.push_back({ name, newVariable });
	}

	Result NamedVariableArray::SetVariable(KeyType name, const Variable& variable)
	{
		auto newVariable = variable.Clone();

		int iVar = FindIndex(name);
		if (iVar >= 0)
		{
			delete (m_VariableArray[iVar].Value);
			m_VariableArray[iVar].Value = newVariable;
		}
		else
		{
			return m_VariableArray.push_back({ name, newVariable });
		}

		return ResultCode::SUCCESS;
	}

	Result NamedVariableArray::AddVariable(KeyType name, SFUniquePtr<Variable>& variable)
	{
		auto Ret = m_VariableArray.push_back({ name, variable.get() });
		if (Ret)
		{
			variable.release();
		}
		return Ret;
	}

	Result NamedVariableArray::SetVariable(KeyType name, SFUniquePtr<Variable>& variable)
	{
		Result hr;

		int iVar = FindIndex(name);
		if (iVar >= 0)
		{
			delete (m_VariableArray[iVar].Value);
			m_VariableArray[iVar].Value = variable.release();
		}
		else
		{
			hr = m_VariableArray.push_back({ name, variable.get() });
			if (hr)
				variable.release();
		}


		return hr;
	}



	NamedVariableArray& NamedVariableArray::operator = (const NamedVariableArray& src)
	{
		Reset();

		for (auto& itVariable : src)
		{
			SetVariable(itVariable.Key, *itVariable.Value);
		}

		return *this;
	}

	NamedVariableArray& NamedVariableArray::operator = (NamedVariableArray&& src)
	{
		Reset();

		m_VariableArray.resize(src.m_VariableArray.size());

		for (int iVar = 0; iVar < m_VariableArray.size(); iVar++)
		{
			m_VariableArray[iVar] = src.m_VariableArray[iVar];
			src.m_VariableArray[iVar].Value = nullptr;
		}

		src.Reset();

		return *this;
	}




} // namespace SF

