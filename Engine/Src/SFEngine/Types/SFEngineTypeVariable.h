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


    Result _ToString(ToStringContext& context, const PlayerPlatformID& value);

    DECLARE_BOXING_TEMPLETE_BYREFERENCE(PlayerPlatformID);


} // namespace SF



