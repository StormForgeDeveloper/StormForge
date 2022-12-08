////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Types/SFEngineTypeVariable.h"





namespace SF {

    // Note that this format is parsed by PlayerPlatformID(const char* strId)
    Result _ToString(ToStringContext& context, const PlayerPlatformID& value)
    {
        if (!_IToA(context, (int)value.Platform))
            return ResultCode::FAIL;

        if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":"))
            return ResultCode::FAIL;

        if (!_IToA(context, value.PlayerID))
            return ResultCode::FAIL;

        return ResultCode::SUCCESS;
    }

    IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(PlayerPlatformID)




} // namespace SF


