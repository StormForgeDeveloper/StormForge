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
#include "Types/SFEngineTypedefs.h"


namespace SF
{

	Result _ToString(ToStringContext& context, const PlayerInformation& value);
	Result _ToString(ToStringContext& context, const RankingPlayerInformation& value);
	Result _ToString(ToStringContext& context, const FriendInformation& value);
	Result _ToString(ToStringContext& context, const TotalRankingPlayerInformation& value);
	Result _ToString(ToStringContext& context, const MatchingQueueTicket& value);
	Result _ToString(ToStringContext& context, const NotificationType& value);
	Result _ToString(ToStringContext& context, const RelayPlayerInfo& value);


	DEFINE_BOXING_TEMPLETE_BYREFERENCE(PlayerInformation);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(RankingPlayerInformation);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(FriendInformation);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(TotalRankingPlayerInformation);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(MatchingQueueTicket);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(NotificationType);
	DEFINE_BOXING_TEMPLETE_BYREFERENCE(RelayPlayerInfo);

}; // namespace SF



