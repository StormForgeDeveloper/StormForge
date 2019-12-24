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

#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Variable/SFVariableBoxing.h"



namespace SF {


	Result _ToString(ToStringContext& context, const NetAddress& value);
	Result _ToString(ToStringContext& context, const TimeStampMS& value);
	Result _ToString(ToStringContext& context, const DurationMS& value);
	Result _ToString(ToStringContext& context, const TimeStampSec& value);
	Result _ToString(ToStringContext& context, const DurationSec& value);
	Result _ToString(ToStringContext& context, const sockaddr_in6& value);
	Result _ToString(ToStringContext& context, const sockaddr_storage& value);


	DEFINE_BOXING_TEMPLETE_BYREFERENCE(NetAddress);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(TimeStampMS);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(DurationMS);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(TimeStampSec);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(DurationSec);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(sockaddr_in6);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(sockaddr_storage);

}; // namespace SF



