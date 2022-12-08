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
#include "Util/SFToStringBase.h"



namespace SF {
	

	Result _ToString(ToStringContext& context, const NetAddress& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, (const char*)value.Address))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":"))
			return ResultCode::FAIL;

		if (!(_IToA(context, (uint32_t)value.Port)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	Result _ToString(ToStringContext& context, const TimeStampMS& value)
	{
		return _IToA(context, value.time_since_epoch().count());
	}


	Result _ToString(ToStringContext& context, const TimeStampSec& value)
	{
		return _IToA(context, value.time_since_epoch().count());
	}


	Result _ToString(ToStringContext& context, const UTCTimeStampMS& value)
	{
		return _IToA(context, value.time_since_epoch().count());
	}


	Result _ToString(ToStringContext& context, const UTCTimeStampSec& value)
	{
		return _IToA(context, value.time_since_epoch().count());
	}


	Result _ToString(ToStringContext& context, const DurationMS& value)
	{
		return _IToA(context, value.count());
	}


	Result _ToString(ToStringContext& context, const DurationSec& value)
	{
		return _IToA(context, value.count());
	}


	Result _ToString(ToStringContext& context, const sockaddr_in6& value)
	{
		char ipstr[INET6_ADDRSTRLEN] = "";
		inet_ntop(value.sin6_family, (void*)&value.sin6_addr, ipstr, sizeof ipstr);

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ipstr)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, (uint32_t)ntohs(value.sin6_port))))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	Result _ToString(ToStringContext& context, const sockaddr_storage& value)
	{
		NetAddress addr;
		addr = value;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, addr.Address)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, (uint32_t)addr.Port)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	Result _ToString(ToStringContext& context, const void* value)
	{
		return _ToString(context, (uint64_t)value);
	}

}


