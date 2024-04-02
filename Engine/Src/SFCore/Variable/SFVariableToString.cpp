////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"

#include "Util/SFToString.h"
#include "Variable/SFVariable.h"
#include "Variable/SFVariableBoxing.h"
#include "Variable/SFVariableToString.h"
#include "Util/SFGuidHelper.h"



namespace SF {
	
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(NamedVariableBox);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(VariableTable);



	Result _ToString(ToStringContext& context, const NamedVariableBox& value)
	{
		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, static_cast<const char*>(value.GetName().ToString()))))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":")))
			return ResultCode::FAIL;

		auto Variable = value.GetVariable();
		if (Variable == nullptr)
		{
			if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "(null)")))
				return ResultCode::FAIL;
		}
		else
		{
			if (!Variable->ToString(context))
				return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}


	Result _ToString(ToStringContext& context, const VariableTable& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "VT:("))
			return ResultCode::FAIL;

		if (!(_IToA(context, (uint32_t)value.size())))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":"))
			return ResultCode::FAIL;

		for (auto itValue : value)
		{
			_ToString(context, itValue.GetKey());
			if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "="))
				return ResultCode::FAIL;

			itValue.GetValue()->ToString(context);

			if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
				return ResultCode::FAIL;
		}

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

}


