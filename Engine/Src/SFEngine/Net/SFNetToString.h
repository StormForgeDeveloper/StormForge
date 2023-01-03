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
#include "Types/SFEngineTypeSerialization.h"

namespace SF
{
	inline size_t SerializedSizeOf(const SocketType& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, SocketType& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const SocketType& data) { return output.Write(&data, sizeof(data)); }

	Result _ToString(ToStringContext& context, SocketType value);

	DECLARE_BOXING_TEMPLETE_BYVALUE(SocketType);


    inline size_t SerializedSizeOf(const SockFamily& Value) { return sizeof(Value); }
    inline Result operator >> (IInputStream& input, SockFamily& data) { return input.Read(&data, sizeof(data)); }
    inline Result operator << (IOutputStream& output, const SockFamily& data) { return output.Write(&data, sizeof(data)); }
    Result _ToString(ToStringContext& context, SockFamily value);
    DECLARE_BOXING_TEMPLETE_BYVALUE(SockFamily);

	Result _ToString(ToStringContext& context, Net::ConnectionState value);
	Result _ToString(ToStringContext& context, const Net::PeerInfo& value);
	Result _ToString(ToStringContext& context, NetClass value);
	Result _ToString(ToStringContext& context, const Message::MessageID& value);



	DECLARE_BOXING_TEMPLETE_BYVALUE(Net::ConnectionState);
	DECLARE_BOXING_TEMPLETE_BYVALUE(NetClass);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(Net::PeerInfo);
	DECLARE_BOXING_TEMPLETE_BYVALUE(Message::MessageID);


} // namespace SF


