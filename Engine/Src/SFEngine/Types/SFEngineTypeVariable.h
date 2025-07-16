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
#include "Variable/SFVariable.h"
#include "Variable/SFVariableBoxing.h"


namespace SF {

    template<> inline AccountID Variable::GetValue<AccountID>() const { return AccountID(GetValueGuid()); }


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


    Result _ToString(ToStringContext& context, const EntityUID& Data);
    DECLARE_BOXING_TEMPLETE_BYVALUE(EntityUID);

    Result _ToString(ToStringContext& context, const TransactionID& Data);
    DEFINE_BOXING_TEMPLETE(TransactionID, VariableUInt64);

    Result _ToString(ToStringContext& context, const AccountID& Data);
    DEFINE_BOXING_TEMPLETE(AccountID, VariableGuid);

} // namespace SF



