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
	

	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(SocketType);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Net::ConnectionState);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(NetClass);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(Net::PeerInfo);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(MessageID);
    IMPLEMENT_BOXING_TEMPLETE_BYVALUE(SockFamily);



	Result _ToString(ToStringContext& context, SocketType value)
	{
        static const char* Strings[] =
        {
            "Stream",
            "DataGram"
        };

        auto intValue = (int)value;
        if (intValue < 0 || intValue >= countof(Strings))
            return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "Invalid");
        else
            return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, Strings[intValue]);
	}

	Result _ToString(ToStringContext& context, Net::ConnectionState value)
	{
		return _IToA(context, (uint32_t)value);
	}


	Result _ToString(ToStringContext& context, const Net::PeerInfo& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "Local:"))
			return ResultCode::FAIL;

		if (!_IToA(context, value.PeerID))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "Remote:")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.PeerID)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}



	Result _ToString(ToStringContext& context, NetClass value)
	{
		return _IToA(context, (uint32_t)value);
	}


	Result _ToString(ToStringContext& context, const MessageID& value)
	{
		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "(")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.IDs.Policy)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.IDs.MsgCode)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ")")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.ID)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


    Result _ToString(ToStringContext& context, SockFamily value)
    {
        static const char* Strings[] = 
        {
            "None",
            "IPV4",// = AF_INET,
            "IPV6"// = AF_INET6
        };

        auto intValue = (int)value;
        if (intValue < 0 || intValue >= countof(Strings))
            return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "Invalid");
        else
            return StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, Strings[intValue]);

    }


} // namespace SF


