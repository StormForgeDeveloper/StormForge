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
#include "Variable/SFVariableSerialization.h"
#include "Variable/SFVariableBoxing.h"
#include "Stream/SFMemoryStream.h"
#include <json/json.h>


namespace SF {




	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	VariableTable::VariableTable(IHeap& heap)
		: m_Heap(heap)
		, m_VariableTable(heap)
	{
	}

	VariableTable::VariableTable(IHeap& heap, const VariableTable& src)
		: m_Heap(heap)
		, m_VariableTable(m_Heap)
	{
		for (auto& itVariable : src)
		{
			SetVariable(itVariable.GetKey(), *itVariable.GetValue());
		}
	}

	VariableTable::VariableTable(const VariableTable& src)
		: m_Heap(GetSystemHeap())
		, m_VariableTable(m_Heap)
	{
		for (auto& itVariable : src)
		{
			SetVariable(itVariable.GetKey(), *itVariable.GetValue());
		}
	}

	VariableTable::~VariableTable()
	{
		Clear();
	}

	void  VariableTable::Clear()
	{
		m_VariableTable.CommitChanges();
		m_VariableTable.ForeachOrder(0, (uint)m_VariableTable.size(), [](KeyType name, Variable* pValue)
		{
			unused(name);
			IHeap::Delete(pValue);
			return true;
		});

		m_VariableTable.Clear();
	}

	Result VariableTable::SetVariable(KeyType name, const Variable& variable)
	{
		Variable* pVariable = nullptr;
		m_VariableTable.Remove(name, pVariable);
		if (pVariable != nullptr)
		{
			IHeap::Delete(pVariable);
		}

		auto newVariable = variable.Clone(GetHeap());

		return m_VariableTable.Set(name, newVariable);
	}

	Result VariableTable::SetVariable(KeyType name, SFUniquePtr<Variable>& variable)
	{
		Variable* pVariable = nullptr;
		m_VariableTable.Remove(name, pVariable);
		if (pVariable != nullptr)
		{
			IHeap::Delete(pVariable);
		}

		auto Ret = m_VariableTable.Set(name, variable.get());
		if (Ret)
		{
			variable.release();
		}
		return Ret;
	}

	Result VariableTable::SetVariable(KeyType name, Variable*& variable)
	{
		Variable* pVariable = nullptr;
		m_VariableTable.Remove(name, pVariable);
		if (pVariable != nullptr)
		{
			IHeap::Delete(pVariable);
		}

		if (variable == nullptr)
			return ResultCode::INVALID_ARG;

		auto Ret = m_VariableTable.Set(name, variable);
		if (Ret)
		{
			variable = nullptr;
		}
		return Ret;
	}

	Variable* VariableTable::GetVariable(KeyType name)
	{
		Variable* pVariable = nullptr;

		m_VariableTable.Find(name, pVariable);

		return pVariable;
	}

	const Variable* VariableTable::GetVariable(KeyType name) const
	{
		Variable* pVariable = nullptr;

		m_VariableTable.Find(name, pVariable);

		return pVariable;
	}

	Result VariableTable::Remove(KeyType name)
	{
		SF::Variable* pVar{};
		auto res = m_VariableTable.Remove(name, pVar);
		if (res)
		{
			IHeap::Delete(pVar);
		}

		return res;
	}

	Result VariableTable::FromBinData(const Array<uint8_t>& binData)
	{
		InputMemoryStream stream(ArrayView<const uint8_t>(binData.size(), binData.data()));
		return stream >> *this;
	}

	VariableTable& VariableTable::operator = (const VariableTable& src)
	{
        if (&src == this)
            return *this;

		Reset();

		for (auto& itVariable : src)
		{
			SetVariable(itVariable.GetKey(), *itVariable.GetValue());
		}

		return *this;
	}

	VariableTable& VariableTable::operator = (VariableTable&& src)
	{
        if (&src == this)
            return *this;

        Reset();

		for (auto& itVariable : src)
		{
			SetVariable(itVariable.GetKey(), itVariable.GetValue());
		}

		src.Reset();

		return *this;
	}

	VariableTable& VariableTable::operator = (const NamedVariableArray& src)
	{
		Reset();

		for (auto& itVariable : src)
		{
			SetVariable(itVariable.Key, *itVariable.Value);
		}

		return *this;
	}

	VariableTable& VariableTable::operator = (NamedVariableArray&& src)
	{
		Reset();

		for (auto& itVariable : src)
		{
			SetVariable(itVariable.Key, itVariable.Value);
		}

		src.Reset();

		return *this;
	}

    Result operator >> (const Json::Value& src, VariableTable& dest)
    {
        if (src.type() != Json::objectValue)
        {
            return ResultCode::INVALID_ARG;
        }

        auto memberNames = src.getMemberNames();
        for (uint iValue = 0; iValue < src.size(); iValue++)
        {
            auto& curValue = src[iValue];
            auto& curName = memberNames[iValue];

            switch (curValue.type())
            {
            case Json::booleanValue:
                dest.SetValue(curName.c_str(), curValue.asBool());
                break;
            case Json::intValue:
                dest.SetValue(curName.c_str(), curValue.asInt64());
                break;
            case Json::realValue:
                dest.SetValue(curName.c_str(), curValue.asInt64());
                break;
            case Json::stringValue:
                dest.SetValue(curName.c_str(), curValue.asCString());
                break;
            default:
                SFLog(System, Error, "Loading from Json failed. We don't support automatic conversion from json valueName:{0} type:{1}", curName, int(curValue.type()));
                return ResultCode::NOT_SUPPORTED_FORMAT;
            }
        }

        return ResultCode::SUCCESS;
    }

    Result operator << (Json::Value& dest, const VariableTable& src)
    {
        if (src.size() == 0)
            return ResultCode::SUCCESS;

        for (auto& itVariable : src)
        {
            switch (itVariable.GetValue()->GetTypeName())
            {
            case VariableBool::TYPE_NAME:
                dest[itVariable.GetKey().ToString()] = Json::Value(itVariable.GetValue()->GetValueBool());
                break;
            case VariableResult::TYPE_NAME:
            case VariableInt::TYPE_NAME:
            case VariableInt64::TYPE_NAME:
                dest[itVariable.GetKey().ToString()] = Json::Value(itVariable.GetValue()->GetValueInt32());
                break;
            case VariableVoidP::TYPE_NAME:
            case VariableUInt64::TYPE_NAME:
            case VariableUInt::TYPE_NAME:
                dest[itVariable.GetKey().ToString()] = Json::Value(itVariable.GetValue()->GetValueUInt32());
                break;
            case VariableFloat::TYPE_NAME:
            case VariableDouble::TYPE_NAME:
                dest[itVariable.GetKey().ToString()] = Json::Value(itVariable.GetValue()->GetValueDouble());
                break;
            default:
                dest[itVariable.GetKey().ToString()] = Json::Value(itVariable.GetValue()->GetValueString());
                break;
            }
        }

        return ResultCode::SUCCESS;
    }


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable table container
	//

	VariableTableMT::VariableTableMT(IHeap& heap)
		: m_Heap(heap)
		, m_VariableTable(heap)
	{
	}

	VariableTableMT::~VariableTableMT()
	{
		m_VariableTable.CommitChanges();
		m_VariableTable.ForeachOrder(0, (uint)m_VariableTable.size(), [](KeyType name, Variable* pValue)
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
		m_VariableTable.Remove(name, pVariable);

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
		return m_VariableTable.Insert(name, pVariable);
	}


	Variable* VariableTableMT::GetVariable(KeyType name)
	{
		Variable* pVariable = nullptr;

		m_VariableTable.Find(name, pVariable);

		return pVariable;
	}






} // namespace SF

