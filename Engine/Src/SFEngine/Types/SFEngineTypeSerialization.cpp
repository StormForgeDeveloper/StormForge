////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine type defines
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Stream/SFStream.h"
#include "Types/SFEngineTypeSerialization.h"



namespace SF {

	/////////////////////////////////////////////////////////////////////
	//
	//	Type utility
	//
    Result _ToString(ToStringContext& context, const ClusterID& value);
    DECLARE_BOXING_TEMPLETE_BYVALUE(ClusterID);



} // namespace SF


