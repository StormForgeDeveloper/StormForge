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
#include "Util/SFToStringBase.h"
#include "Net/SFNetToString.h"

namespace SF {
	

	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(SockType);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Net::ConnectionState);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(NetClass);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(Net::PeerInfo);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Message::MessageID);



	Result _ToString(ToStringContext& context, SockType value)
	{
		switch (value)
		{
		case SockType::Stream:
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "Stream");
		case SockType::DataGram:
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "DataGram");
		default:
			return StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(Invalid)");
		}
	}

	Result _ToString(ToStringContext& context, Net::ConnectionState value)
	{
		return _IToA(context, (uint32_t)value);
	}


	Result _ToString(ToStringContext& context, const Net::PeerInfo& value)
	{
		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "Local:"))
			return ResultCode::FAIL;

		if (!_IToA(context, value.PeerID))
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


