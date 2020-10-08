////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko 
// 
// Author : KyungKun Ko
//
// Description : Network type tostring 
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "String/SFToStringBase.h"
#include "Net/SFNetToString.h"

namespace SF {
	

	Result _ToString(ToStringContext& context, Net::ConnectionState value)
	{
		return _IToA(context, (uint32_t)value);
	}


	Result _ToString(ToStringContext& context, const Net::PeerInfo& value)
	{
		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "Local:")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.PeerID)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "Remote:")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.PeerID)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}



	Result _ToString(ToStringContext& context, NetClass value)
	{
		return _IToA(context, (uint32_t)value);
	}


	Result _ToString(ToStringContext& context, const Message::MessageID& value)
	{
		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.IDs.Policy)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.IDs.MsgCode)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ")")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.ID)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}



} // namespace SF


