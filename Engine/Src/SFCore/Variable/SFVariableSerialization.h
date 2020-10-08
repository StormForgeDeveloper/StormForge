////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable serialization
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Variable/SFVariableBoxing.h"
#include "Service/SFService.h"
#include "Stream/SFStream.h"
#include "Variable/SFVariableTable.h"
#include "Variable/SFNamedVariableBox.h"

namespace SF {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable serialization size calculations
	//



	template<>
	inline size_t SerializedSizeOf(const Variable& Value) { return Value.GetSerializedSize(); }



	template<>
	inline size_t SerializedSizeOf(const VariableBox& Value)
	{
		auto pVariable = Value.GetVariable();
		return pVariable ? pVariable->GetSerializedSize() : sizeof(Variable::TypeNameType);
	}


	template<>
	inline size_t SerializedSizeOf(const NamedVariableBox& Value) { auto pVariable = Value.GetVariable(); return sizeof(NamedVariableBox::NameType) + pVariable ? pVariable->GetSerializedSize() : sizeof(Variable::TypeNameType); }


	template<>
	inline size_t SerializedSizeOf(const VariableTable& Value)
	{
		size_t Size = sizeof(uint16_t);
		for (auto& itVar : Value)
		{
			Size += SerializedSizeOf(itVar.GetKey());
			auto* pVariable = itVar.GetValue();
			if (pVariable != nullptr)
				Size += SerializedSizeOf(*pVariable);
			else
				Size += sizeof(Variable::TypeNameType);
		}

		return Size;
	}



	Result operator >> (IInputStream& input, VariableBox& data);
	Result operator << (IOutputStream& output, const VariableBox& data);

	Result operator >> (IInputStream& input, NamedVariableBox& data);
	Result operator << (IOutputStream& output, const NamedVariableBox& data);

	Result operator >> (IInputStream& input, VariableTable& data);
	Result operator << (IOutputStream& output, const VariableTable& data);



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	VariableTableWriter
	//		Helper class to help send message
	//

	//template<typename DataType, typename ArrayType = DynamicArray<uint8_t>>
	//class BinarySerializer : public ArrayType
	//{
	//public:

	//	BinarySerializer(const DataType& src)
	//	{
	//		OutputMemoryStream outputStream(*this);
	//		auto* output = outputStream.ToOutputStream();
	//		output->Write(src);
	//	}


	//};

} // namespace SF


