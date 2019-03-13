////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Time util interface
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Util/SFTimeUtil.h"

#include "SFCSUtil.h"




namespace SF
{

	SFDLL_EXPORT uint64_t SFTime_NativeGetTimeOffset()
	{
		return Util::Time.GetRawUTCMs().time_since_epoch().count();
	}



}
