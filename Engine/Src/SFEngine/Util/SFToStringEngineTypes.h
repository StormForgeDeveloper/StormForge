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
#include "Util/SFGuid.h"
#include "Util/SFGuidHelper.h"

namespace SF
{

	Result _ToString(ToStringContext& context, const PlayerInformation& value);
	Result _ToString(ToStringContext& context, const RankingPlayerInformation& value);
	Result _ToString(ToStringContext& context, const FriendInformation& value);
	Result _ToString(ToStringContext& context, const TotalRankingPlayerInformation& value);
	Result _ToString(ToStringContext& context, const MatchingQueueTicket& value);
	Result _ToString(ToStringContext& context, const NotificationType& value);
	Result _ToString(ToStringContext& context, const RelayPlayerInfo& value);
	//Result _ToString(ToStringContext& context, const RouteContext& Data);
    //Result _ToString(ToStringContext& context, const Guid& Data);


	DECLARE_BOXING_TEMPLETE_BYREFERENCE(PlayerInformation);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(RankingPlayerInformation);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(FriendInformation);
	//DECLARE_BOXING_TEMPLETE_BYREFERENCE(TotalRankingPlayerInformation);
	//DECLARE_BOXING_TEMPLETE_BYREFERENCE(MatchingQueueTicket);
	//DECLARE_BOXING_TEMPLETE_BYREFERENCE(NotificationType);
	//DECLARE_BOXING_TEMPLETE_BYREFERENCE(RelayPlayerInfo);

} // namespace SF


