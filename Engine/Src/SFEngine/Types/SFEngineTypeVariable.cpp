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





namespace SF
{
    //IMPLEMENT_BOXING_TEMPLETE_BYVALUE(AccountID);

    //Result _ToString(ToStringContext& context, const AccountID& value)
    //{
    //    context.OutStream.BuffLen -= (int)value.ToString(context.OutStream.pBuffer, context.OutStream.BuffLen);

    //    return ResultCode::SUCCESS;
    //}


    Result _ToString(ToStringContext& context, const ClusterID& value)
    {
        if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ToString(value)))
            return ResultCode::FAIL;

        return ResultCode::SUCCESS;
    }

    IMPLEMENT_BOXING_TEMPLETE_BYVALUE(ClusterID);


    // Note that this format is parsed by PlayerPlatformID(const char* strId)
    Result _ToString(ToStringContext& context, const PlayerPlatformID& value)
    {
        if (!_IToA(context, (int)value.Platform))
            return ResultCode::FAIL;

        if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":"))
            return ResultCode::FAIL;

        context.OutStream.BuffLen -= (int)value.PlayerId.ToString(context.OutStream.pBuffer, context.OutStream.BuffLen);

        return ResultCode::SUCCESS;
    }

    IMPLEMENT_BOXING_TEMPLETE_BYREFERENCE(PlayerPlatformID);


    Result _ToString(ToStringContext& context, const AchievementStat& value)
    {
        if (!_IToA(context, (int)value.AchievementStatId))
            return ResultCode::FAIL;

        if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ":"))
            return ResultCode::FAIL;

        if (!_IToA(context, value.StatValue))
            return ResultCode::FAIL;


        return ResultCode::SUCCESS;
    }

    IMPLEMENT_BOXING_TEMPLETE_BYVALUE(AchievementStat);



} // namespace SF


