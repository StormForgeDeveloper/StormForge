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
#include "Variable/SFVariableToString.h"



namespace SF {
	

	Result _ToString(ToStringContext& context, const NamedVariableBox& value)
	{
		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, static_cast<const char*>(value.GetName().ToString()))))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		auto Variable = value.GetVariable();
		if (Variable == nullptr)
		{
			if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(null)")))
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
		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "Tbl:(")))
			return ResultCode::FAIL;

		if (!(_IToA(context, (uint32_t)value.size())))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ")")))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

}


