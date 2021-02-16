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





namespace SF {

	/////////////////////////////////////////////////////////////////////
	//
	//	Type utility
	//

	GameInstanceInfo::GameInstanceInfo(const GameInstanceInfo& src)
		: GameInstanceUID(src.GameInstanceUID)
		, TypeName(src.TypeName)
		, DataID(src.DataID)
	{
	}

	GameInstanceInfo::GameInstanceInfo(GameInsUID InGameInstanceUID, StringCrc32 InTypeName, StringCrc32 InDataID)
		: GameInstanceUID(InGameInstanceUID)
		, TypeName(InTypeName)
		, DataID(InDataID)
	{
	}

	GameInstanceInfo& GameInstanceInfo::operator = (const GameInstanceInfo& src)
	{
		GameInstanceUID = src.GameInstanceUID;
		TypeName = src.TypeName;
		DataID = src.DataID;

		return *this;
	}

	bool GameInstanceInfo::operator == (const GameInstanceInfo& src) const
	{
		return GameInstanceUID == src.GameInstanceUID
			&& TypeName == src.TypeName
			&& DataID == src.DataID;
	}



	////////////////////////////////////////////////////////////////////////////////////
	//
	//	Player informations
	//

	PlayerInformation::PlayerInformation(const PlayerInformation& src)
	{
		(*this) = src;
	}

	PlayerInformation& PlayerInformation::operator = (const PlayerInformation& src)
	{
		this->PlayerID = src.PlayerID;
		this->FBUID = src.FBUID;
		Level = src.Level;
		IsPlayingGame = src.IsPlayingGame;
		LastActiveTime = src.LastActiveTime;

		StrUtil::StringCopy(NickName, src.NickName);

		return *this;
	}

	PlayerInformation::PlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime)
	{
		InitPlayerInformation(playerID, fbUID, nickName, level, isPlayingGame, lastActiveTime);
	}

	Result PlayerInformation::InitPlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime)
	{
		if (nickName == nullptr)
			return ResultCode::INVALID_ARG;

		this->PlayerID = playerID;
		this->FBUID = fbUID;
		Level = level;
		IsPlayingGame = isPlayingGame;
		LastActiveTime = lastActiveTime;

		return StrUtil::StringCopy(NickName, nickName);
	}


	bool PlayerInformation::operator == (const PlayerInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}




	RankingPlayerInformation::RankingPlayerInformation()
		:WeeklyWin(0)
		, WeeklyLose(0)
	{
	}

	RankingPlayerInformation::RankingPlayerInformation(const RankingPlayerInformation& src)
		: PlayerInformation(src)
	{
		WeeklyWin = src.WeeklyWin;
		WeeklyLose = src.WeeklyLose;
	}

	RankingPlayerInformation::RankingPlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime)
		:PlayerInformation(playerID, fbUID, nickName, level, isPlayingGame, lastActiveTime)
	{
		WeeklyWin = weeklyWin;
		WeeklyLose = weeklyLose;
	}

	RankingPlayerInformation& RankingPlayerInformation::operator = (const RankingPlayerInformation& src)
	{
		*(PlayerInformation*)this = src;
		//InitPlayerInformation(src.PlayerID, src.FBUID, src.NickName, src.Level, src.IsPlayingGame, src.LastActiveTime);
		WeeklyWin = src.WeeklyWin;
		WeeklyLose = src.WeeklyLose;
		return *this;
	}

	bool RankingPlayerInformation::operator == (const RankingPlayerInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}




	FriendInformation::FriendInformation()
		:LastStaminaSent(0)
	{
	}

	FriendInformation::FriendInformation(const FriendInformation& src)
		: RankingPlayerInformation(src)
	{
		LastStaminaSent = src.LastStaminaSent;
	}

	FriendInformation::FriendInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime, uint64_t lastStaminaSent)
		: RankingPlayerInformation(playerID, fbUID, nickName, level, weeklyWin, weeklyLose, isPlayingGame, lastActiveTime)
	{
		LastStaminaSent = lastStaminaSent;
	}

	FriendInformation& FriendInformation::operator = (const FriendInformation& src)
	{
		//InitPlayerInformation(src.PlayerID, src.FBUID, src.NickName, src.Level, src.weeklyWin, src.weeklyLose, src.IsPlayingGame, src.LastActiveTime);
		*(RankingPlayerInformation*)this = src;
		LastStaminaSent = src.LastStaminaSent;
		return *this;
	}

	bool FriendInformation::operator == (const FriendInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}





	TotalRankingPlayerInformation::TotalRankingPlayerInformation()
	{
		memset(this, 0, sizeof(TotalRankingPlayerInformation));
	}

	TotalRankingPlayerInformation::TotalRankingPlayerInformation(const TotalRankingPlayerInformation& src)
	{
		(*this) = src;
	}

	TotalRankingPlayerInformation& TotalRankingPlayerInformation::operator = (const TotalRankingPlayerInformation& src)
	{
		RankingID = src.RankingID;
		Ranking = src.Ranking;
		this->PlayerID = src.PlayerID;
		this->FBUID = src.FBUID;
		Level = src.Level;
		ScoreLow = src.ScoreLow;
		ScoreHigh = src.ScoreHigh;

		StrUtil::StringCopy(NickName, src.NickName);

		return *this;
	}

	TotalRankingPlayerInformation::TotalRankingPlayerInformation(uint32_t rankingID, uint32_t ranking, AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint scoreLow, uint scoreHigh)
	{
		//if( nickName == nullptr ) 
		//	return ResultCode::INVALID_ARG;

		RankingID = rankingID;
		Ranking = ranking;
		this->PlayerID = playerID;
		this->FBUID = fbUID;
		Level = level;
		ScoreLow = scoreLow;
		ScoreHigh = scoreHigh;

		StrUtil::StringCopy(NickName, nickName);
	}

	bool TotalRankingPlayerInformation::operator == (const TotalRankingPlayerInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}





} // namespace SF


