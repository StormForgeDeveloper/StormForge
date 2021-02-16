////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Variable/SFVariable.h"
#include "Variable/SFNamedVariableBox.h"
#include "Variable/SFVariableTable.h"
#include "String/SFToString.h"
#include "String/SFStringFormat.h"
#include "String/SFHasher32C.h"

namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Serialized sizeof implementation
	//


	size_t SerializedSizeOf(const Variable& Value)
	{
		return Value.GetSerializedSize();
	}

	size_t SerializedSizeOf(const VariableBox& Value)
	{
		auto pVariable = Value.GetVariable();
		return sizeof(Variable::TypeNameType) + (pVariable ? pVariable->GetSerializedSize() : 0);
	}


	size_t SerializedSizeOf(const NamedVariableBox& Value)
	{
		auto pVariable = Value.GetVariable();
		return sizeof(NamedVariableBox::NameType) + sizeof(Variable::TypeNameType) + (pVariable ? pVariable->GetSerializedSize() : 0);
	}


	size_t SerializedSizeOf(const VariableTable& Value)
	{
		size_t Size = sizeof(uint16_t);
		for (auto& itVar : Value)
		{
			Size += SerializedSizeOf(itVar.GetKey());
			auto* pVariable = itVar.GetValue();
			if (pVariable != nullptr)
			{
				Size += sizeof(Variable::TypeNameType);
				Size += SerializedSizeOf(*pVariable);
			}
		}

		return Size;
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	//	operator
	//


	Result operator >> (IInputStream& input, VariableBox& data)
	{
		StringCrc32 TypeName;
		if (!(input >> TypeName))
			return ResultCode::END_OF_STREAM;

		if (!data.SetVariableType(TypeName))
			return ResultCode::INVALID_FORMAT;

		if (!data.GetVariable()->Deserialize(input))
			return ResultCode::INVALID_FORMAT;

		return ResultCode::SUCCESS;
	}

	Result operator >> (IInputStream& input, NamedVariableBox& data)
	{
		StringCrc32 Name;
		if (!(input >> Name))
			return ResultCode::END_OF_STREAM;

		data.SetName(Name);

		return (input >> *static_cast<VariableBox*>(&data));
	}


	Result operator >> (IInputStream& input, VariableTable& data)
	{
		uint16_t NumItems = 0;

		if (!input.Read(NumItems))
			return ResultCode::END_OF_STREAM;

		for (uint32_t iItem = 0; iItem < NumItems; iItem++)
		{
			VariableTable::KeyType VariableName;
			if (!(input >> VariableName))
				return ResultCode::END_OF_STREAM;

			StringCrc32 TypeName;
			if (!(input >> TypeName))
				return ResultCode::END_OF_STREAM;

			SFUniquePtr<Variable> pVariable;
			if (TypeName != nullptr)
			{
				pVariable.reset(Service::VariableFactory->CreateVariable(data.GetHeap(), TypeName));
				pVariable->Deserialize(input);
			}

			data.SetVariable(VariableName, pVariable);
		}

		return ResultCode::SUCCESS;
	}



	Result operator << (IOutputStream& output, const VariableBox& data)
	{
		auto pVariable = data.GetVariable();
		StringCrc32 TypeName = nullptr;
		if (pVariable == nullptr)
		{
			return (output << TypeName);
		}

		TypeName = pVariable->GetTypeName();

		if (!(output << TypeName))
			return ResultCode::END_OF_STREAM;

		return pVariable->Serialize(output);
	}


	Result operator << (IOutputStream& output, const NamedVariableBox& data)
	{
		StringCrc32 Name = data.GetName();
		if (!(output << Name))
			return ResultCode::END_OF_STREAM;

		return output << (*static_cast<const VariableBox*>(&data));
	}

	Result operator << (IOutputStream& output, const VariableTable& data)
	{
		uint16_t NumItems = static_cast<uint16_t>(data.size());
		if (!(output << NumItems))
			return ResultCode::END_OF_STREAM;

		for (auto itItem : data)
		{
			VariableTable::KeyType VariableName = itItem.GetKey();
			if (!(output << VariableName))
				return ResultCode::END_OF_STREAM;

			auto* pVariable = itItem.GetValue();
			StringCrc32 TypeName = pVariable == nullptr ? nullptr : pVariable->GetTypeName();
			if (!(output << TypeName))
				return ResultCode::END_OF_STREAM;

			if (pVariable == nullptr)
				continue;

			auto Ret = pVariable->Serialize(output);
			if (!Ret)
				return Ret;
		}

		return ResultCode::SUCCESS;
	}



} // namespace SF

