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
#include "String/SFStrUtil.h"
#include "String/SFStrFormat.h"
#include "String/SFToStringEngineTypes.h"



namespace SF {
	

	Result _ToString(ToStringContext& context, const PlayerInformation& value)
	{
		if (!(_IToA(context, value.PlayerID)))
			return ResultCode::FAIL;

		if (!(StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ":")))
			return ResultCode::FAIL;

		if (!(_IToA(context, value.FBUID)))
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

		if (!(_IToA(context, value.FBUID)))
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

	Result _ToString(ToStringContext& context, const GameInstanceInfo& value)
	{
		if (!(_IToA(context, value.GameInstanceUID)))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	void TestEngineTypes()
	{
		DynamicArray<FriendInformation> testFriendList(GetSystemHeap());
		FriendInformation test;
		test.FBUID = 1;
		testFriendList.push_back(test);
		test.FBUID = 2;
		testFriendList.push_back(test);

		const Array< FriendInformation>& testFriendListC = testFriendList;
		char testString[512];
		StrUtil::Format(testString, "{0}", testFriendList);
		StrUtil::Format(testString, "{0}", testFriendListC);
		

		auto boxedFriendList = Boxing(testFriendList);
		auto pFriendList = UnboxingReference<Array<FriendInformation>>(boxedFriendList);
		for (auto& fr : *pFriendList)
		{
			StrUtil::Format(testString, "{0}", fr);
		}


	}

}


