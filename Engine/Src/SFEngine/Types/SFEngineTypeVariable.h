////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : VariableBox - Implementation of box/unboxing without micro allocation
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFEngineTypedefs.h"
#include "Variable/SFVariableBoxing.h"


namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	// VariableBox 
	//

    Result _ToString(ToStringContext& context, const ClusterID& value);
    DECLARE_BOXING_TEMPLETE_BYVALUE(ClusterID);


    Result _ToString(ToStringContext& context, const PlayerPlatformID& value);
    DECLARE_BOXING_TEMPLETE_BYREFERENCE(PlayerPlatformID);


    Result _ToString(ToStringContext& context, const AchievementStat& value);
    DECLARE_BOXING_TEMPLETE_BYVALUE(AchievementStat);

} // namespace SF



