// AVLTreeTest.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "../UnitTest_Algorithm.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




// ranking key type
union RankingKey
{
	struct {
		uint32_t PlayerID;
		uint32_t Score;
	};
	uint64_t RankingKeyValue;
};


// ranking player
class RankingPlayer
{
public:
	static constexpr int MAX_SCORE = 1000000;

private:


	RankingKey m_RankingKey;

public:

	RankingPlayer()
	{
	}

	// Initialize player
	void Initialize(uint playerID)
	{
		m_RankingKey.PlayerID = playerID;
		SetRandomScore();
	}


	void SetRandomScore()
	{
		m_RankingKey.Score = Util::Random.Rand() % MAX_SCORE;
	}


	uint GetPlayerID() const { return m_RankingKey.PlayerID; }

	uint GetScore() const { return m_RankingKey.Score; }
	void SetScore(uint newScore) { m_RankingKey.Score = newScore; }

	uint64_t GetRankingKey() const { return m_RankingKey.RankingKeyValue; }
};

constexpr int RankingPlayer::MAX_SCORE;



TEST_F(AlgorithmTest, MatchingRanking)
{
	constexpr int NUM_MATCH_THREAD = 4;
	constexpr int NUM_UPDATE_THREAD = 1;
#ifdef DEBUG
	constexpr int NUM_PLAYER = 2000;
	constexpr int NUM_SHELL = 50;
	constexpr int MATCHING_VARIATION = 20;
	const DurationMS testTime(40 * 1000);
#else
	constexpr int NUM_PLAYER = 2000000;
	constexpr int NUM_SHELL = 5000;
	constexpr int MATCHING_VARIATION = 100;
	const DurationMS testTime(5 * 60 * 1000);
#endif

	std::atomic<uint32_t> playerUpdated(0);
	std::atomic< uint32_t> successfulMatchCount(0);
	std::atomic< uint32_t> failedMatchCount(0);

	auto players = new(GetHeap()) RankingPlayer[NUM_PLAYER];

	DualSortedMap<uint64_t, RankingPlayer*> rankingMap(GetHeap());
	CriticalSection m_UpdateLock;
	TimeStampMS start, end;

	int iTest = 0;
	SFLog(Game, Info, "Insert {0} items for test\n", NUM_PLAYER);
	start = Util::Time.GetRawTimeMs();
	for (int iPlayer = 0; iPlayer < NUM_PLAYER; iPlayer++)
	{
		players[iPlayer].Initialize(iPlayer + 1);
		EXPECT_TRUE((rankingMap.Insert(players[iPlayer].GetRankingKey(), &players[iPlayer])));
	}
	end = Util::Time.GetRawTimeMs();
	printf("Insertion took %dms\n", (end - start).count());

	EXPECT_TRUE((rankingMap.CommitChanges()));

	auto startTime = Util::Time.GetRawTimeMs();

	// Start update threads
	for (int iThread = 0; iThread < NUM_UPDATE_THREAD; iThread++)
	{
		auto newThread = new(GetHeap()) FunctorTickThread([&](Thread* pThread)
		{
			MutexScopeLock lock(m_UpdateLock);
			auto iPlayer = Util::Random.Rand() % NUM_PLAYER;
			RankingPlayer *pPlayer = &players[iPlayer];
			RankingPlayer *pRemovedPlayer = nullptr;
			if (!rankingMap.Remove(pPlayer->GetRankingKey(), pRemovedPlayer))
				return true;

			pPlayer->SetRandomScore();
			
			EXPECT_TRUE((rankingMap.Insert(pPlayer->GetRankingKey(), pPlayer)));

			auto updated = playerUpdated.fetch_add(1, std::memory_order_relaxed);

			if ((updated%100) == 0)
				rankingMap.CommitChanges();

			return true;
		});

		newThread->Start();
		newThread->SetThreadName("UpdateThread");
		m_Threads.push_back(newThread);
	}

	// Start match threads
	for (int iThread = 0; iThread < NUM_MATCH_THREAD; iThread++)
	{
		auto newThread = new(GetHeap()) FunctorTickThread([&](Thread* pThread)
		{
			auto iPlayer = Util::Random.Rand() % NUM_PLAYER;
			RankingPlayer *pPlayer = &players[iPlayer];
			RankingPlayer *pRankingPlayer = nullptr;
			int64_t ranking = 0;
			auto rankingKey = pPlayer->GetRankingKey();
			StaticArray<RankingPlayer*, 8> selectedPlayers(GetHeap());
			auto matchingPlayerCount = selectedPlayers.GetAllocatedSize();

			if (!rankingMap.Find(rankingKey, pRankingPlayer, &ranking))
			{
				failedMatchCount.fetch_add(1, std::memory_order_relaxed);
				return true; // user not found
			}

			auto startRanking = ranking - (decltype(ranking))(Util::Random.Rand() % MATCHING_VARIATION);

			// TODO: add random picking function in range so that we can give more variation
			rankingMap.ForeachOrder((int)startRanking, (uint)matchingPlayerCount, [&selectedPlayers, pPlayer](uint64_t key, RankingPlayer* pMatchedPlayer)
			{
				if (pMatchedPlayer->GetPlayerID() == pPlayer->GetPlayerID())
					return true;

				selectedPlayers.push_back(pMatchedPlayer);
				return true;
			});

			if(selectedPlayers.size() == matchingPlayerCount)
				successfulMatchCount.fetch_add(1, std::memory_order_relaxed);
			else
				failedMatchCount.fetch_add(1, std::memory_order_relaxed);

			return true;
		});

		newThread->Start();
		newThread->SetThreadName("UpdateThread");
		newThread->SetTickInterval(DurationMS(0));
		m_Threads.push_back(newThread);
	}



	while (Util::TimeSinceRaw(startTime) < testTime)
	{
		ThisThread::SleepFor(DurationMS(500));
	}


	auto testDuration = Util::TimeSinceRaw(startTime);
	SFLog(Game, Info, "PlayerUpdated:{0}, Match success/fail:{1}/{2}, duration:{3} min", playerUpdated.load(), successfulMatchCount.load(), failedMatchCount.load(), (float)testDuration.count() / (60000.f));
	auto testDurationSec = testDuration.count() / 1000;
	SFLog(Game, Info, "Matched {0} / sec", (successfulMatchCount.load() / testDurationSec));

	// Stop all read threads
	StopAllThread();

	rankingMap.clear();

	IHeap::Delete(players);
}

