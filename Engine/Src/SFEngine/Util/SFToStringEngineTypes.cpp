////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type _ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "Util/SFStrFormat.h"
#include "Util/SFToStringEngineTypes.h"
#include "Types/SFEngineTypeVariable.h"



namespace SF {
	
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(PlayerInformation);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(RankingPlayerInformation);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(FriendInformation);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(TotalRankingPlayerInformation);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(MatchingQueueTicket);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(NotificationType);
	IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(RelayPlayerInfo);
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(RouteContext);




	Result _ToString(ToStringContext& context, const PlayerInformation& value)
	{
		if (!(_IToA(context, value.PlayerID)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_ToString(context, value.PlayerPlatformId)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, (const char*)value.NickName)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	Result _ToString(ToStringContext& context, const RankingPlayerInformation& value)
	{
		if (!(_ToString(context, (PlayerInformation&)value)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.WeeklyWin)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.WeeklyLose)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	Result _ToString(ToStringContext& context, const FriendInformation& value)
	{
		if (!(_ToString(context, (RankingPlayerInformation&)value)))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.WeeklyLose)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	Result _ToString(ToStringContext& context, const TotalRankingPlayerInformation& value)
	{
		if (!(_IToA(context, value.RankingID)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.PlayerID)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_ToString(context, value.PlayerPlatformId)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, (const char*)value.NickName)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	Result _ToString(ToStringContext& context, const MatchingQueueTicket& value)
	{
		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "("))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.QueueUID)))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":"))
			return ResultCode::FAIL;

		if (!_IToA(context, value.QueueItemID))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ")"))
			return ResultCode::FAIL;


		return ResultCode::SUCCESS;
	}


	Result _ToString(ToStringContext& context, const NotificationType& value)
	{
		if (!(_IToA(context, (uint16_t)value)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	Result _ToString(ToStringContext& context, const RelayPlayerInfo& value)
	{
		if (!(_IToA(context, value.EndpointID)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.RelayPlayerID)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	Result _ToString(ToStringContext& context, const RouteContext& Data)
	{
		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(")))
			return ResultCode::FAIL;

		if (!(_ToString(context, Data.Components.From)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_ToString(context, Data.Components.To)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ")")))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


}


