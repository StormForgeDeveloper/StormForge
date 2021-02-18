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

#pragma once

#include "SFTypedefs.h"
#include "Util/SFToString.h"
#include "Variable/SFVariableBoxing.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"


namespace SF
{

	Result _ToString(ToStringContext& context, Net::ConnectionState value);
	Result _ToString(ToStringContext& context, const Net::PeerInfo& value);
	Result _ToString(ToStringContext& context, NetClass value);
	Result _ToString(ToStringContext& context, const Message::MessageID& value);



	DECLARE_BOXING_TEMPLETE_BYVALUE(Net::ConnectionState);
	DECLARE_BOXING_TEMPLETE_BYVALUE(NetClass);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(Net::PeerInfo);
	DECLARE_BOXING_TEMPLETE_BYVALUE(Message::MessageID);


} // namespace SF


