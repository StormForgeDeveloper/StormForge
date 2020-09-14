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
	//	String stream IO util
	//

	template<>
	inline Result IInputStream::Read(VariableBox& data)
	{
		StringCrc32 TypeName;
		if (!Read(TypeName))
			return ResultCode::END_OF_STREAM;

		if (!data.SetVariableType(TypeName))
			return ResultCode::INVALID_FORMAT;

		if (!data.GetVariable()->Deserialize(*this))
			return ResultCode::INVALID_FORMAT;

		return ResultCode::SUCCESS;
	}

	template<>
	inline Result IInputStream::Read(NamedVariableBox& data)
	{
		StringCrc32 Name;
		if (!Read(Name))
			return ResultCode::END_OF_STREAM;

		data.SetName(Name);

		return Read(*static_cast<VariableBox*>(&data));
	}


	template<>
	inline Result IInputStream::Read(VariableTable& data)
	{
		uint16_t NumItems = 0;

		if (!Read(NumItems))
			return ResultCode::END_OF_STREAM;

		for (uint32_t iItem = 0; iItem < NumItems; iItem++)
		{
			StringCrc64 VariableName;
			if (!Read(VariableName))
				return ResultCode::END_OF_STREAM;

			StringCrc32 TypeName;
			if (!Read(TypeName))
				return ResultCode::END_OF_STREAM;

			std::unique_ptr<Variable> pVariable;
			pVariable.reset(Service::VariableFactory->CreateVariable(data.GetHeap(), TypeName));
			pVariable->Deserialize(*this);

			data.SetVariable(VariableName, pVariable);
		}

		return ResultCode::SUCCESS;
	}



	template<>
	inline Result IOutputStream::Write(const VariableBox& data)
	{
		auto pVariable = data.GetVariable();
		StringCrc32 TypeName = nullptr;
		if (pVariable == nullptr)
		{
			return Write(TypeName);
		}

		TypeName = pVariable->GetTypeName();

		if (!Write(TypeName))
			return ResultCode::END_OF_STREAM;

		return pVariable->Serialize(*this);
	}

	template<>
	inline Result IOutputStream::Write(const NamedVariableBox& data)
	{
		StringCrc32 Name = data.GetName();
		if (!Write(Name))
			return ResultCode::END_OF_STREAM;

		return Write(*static_cast<const VariableBox*>(&data));
	}

	template<>
	inline Result IOutputStream::Write(const VariableTable& data)
	{
		uint16_t NumItems = static_cast<uint16_t>(data.size());
		if (!Write(NumItems))
			return ResultCode::END_OF_STREAM;

		for (auto itItem : data)
		{
			StringCrc64 VariableName = itItem.GetKey();
			if (!Write(VariableName))
				return ResultCode::END_OF_STREAM;

			auto* pVariable = itItem.GetValue();
			StringCrc32 TypeName = pVariable == nullptr ? nullptr : pVariable->GetTypeName();
			if (!Write(TypeName))
				return ResultCode::END_OF_STREAM;

			if (pVariable == nullptr)
				continue;

			auto Ret = pVariable->Serialize(*this);
			if (!Ret)
				return Ret;
		}

		return ResultCode::SUCCESS;
	}


} // namespace SF


