// Algorithm test.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFToString.h"
#include "../UnitTest_Algorithm.h"
#include "SFSphericalShellManager.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


//
// This is implementation of spherical shell matching


TEST_F(AlgorithmTest, MatchingPreference)
{
	constexpr int NUM_UPDATE_THREAD = 4;
#ifdef DEBUG
	constexpr int NUM_MATCH_THREAD = 1;
	constexpr int NUM_PLAYER = 2000;
	constexpr int NUM_PLAYER_VARIATION = 200;
	constexpr int NUM_SHELL = 50;
#else
	constexpr int NUM_MATCH_THREAD = 2;
	constexpr int NUM_PLAYER = 2000000;
	constexpr int NUM_PLAYER_VARIATION = 2000;
	constexpr int NUM_SHELL = 5000;
#endif

	const DurationMS testTime(5 * 60 * 1000);
	SphericalShellManager matchManager(GetHeap());
	Atomic<uint32_t> playerUpdated(0);
	Atomic< uint32_t> successfulMatchCount(0);
	Atomic< uint32_t> failedMatchCount(0);


	auto players = new(GetHeap()) PreferencePlayer[NUM_PLAYER + NUM_PLAYER_VARIATION];

	SFLog(Game, Info, "Initializing matching system");
	Result initResult = matchManager.Initialize(NUM_SHELL);
	EXPECT_EQ(ResultCode::SUCCESS, initResult);

	// add all player first
	SFLog(Game, Info, "Adding initial players");
	for (int iPlayer = 0; iPlayer < (NUM_PLAYER + NUM_PLAYER_VARIATION); iPlayer++)
	{
		uint playerID = iPlayer+1;
		// add or update a random player to the system 
		UserPreference preference;
		preference.InitRandom();

		players[iPlayer].Initialize(playerID, preference);

		matchManager.AddPlayer(&players[iPlayer]);
	}

	SFLog(Game, Info, "PreferencePlayer added:{0}", (NUM_PLAYER + NUM_PLAYER_VARIATION));
	auto startTime = Util::Time.GetRawTimeMs();

	for (int iThread = 0; iThread < NUM_UPDATE_THREAD; iThread++)
	{
		auto pThread = new(GetHeap()) FunctorTickThread([&](Thread* pThread)
		{
			uint playerID = Util::Random.Rand() % (NUM_PLAYER + NUM_PLAYER_VARIATION);
			UserPreference preference;
			preference.InitRandom();

			players[playerID].SetPreference(preference);
			matchManager.UpdatePlayerShell(&players[playerID]);

			playerUpdated.fetch_add(1, std::memory_order_relaxed);
			return true;
		});

		pThread->Start();
		pThread->SetThreadName("PlayerUpdate");
		m_Threads.push_back(pThread);
	}


	for (int iThread = 0; iThread < NUM_MATCH_THREAD; iThread++)
	{
		auto pThread = new(GetHeap()) FunctorTickThread([&](Thread* pThread)
		{
			StaticArray<PreferencePlayer*, 5> matchedPlayer(GetHeap());
			// match make a player
			uint playerID = Util::Random.Rand() % (NUM_PLAYER);
			if (matchManager.MatchMake(&players[playerID], matchedPlayer))
				successfulMatchCount.fetch_add(1, std::memory_order_relaxed);
			else
				failedMatchCount.fetch_add(1, std::memory_order_relaxed);

			// add back the players
			for (auto& itPlayer : matchedPlayer)
			{
				MutexScopeLock lock(itPlayer->GetShellLock());
				matchManager.AddPlayer(itPlayer);
			}

			return true;
		});

		pThread->Start();
		pThread->SetTickInterval(DurationMS(0));
		pThread->SetThreadName("Matching");
		m_Threads.push_back(pThread);
	}


	while (Util::TimeSinceRaw(startTime) < testTime)
	{
		ThisThread::SleepFor(DurationMS(500));
	}


	auto testDuration = Util::TimeSinceRaw(startTime);
	SFLog(Game, Info, "PlayerUpdated:{0}, Match success/fail:{1}/{2}, duration:{3} min", playerUpdated.load(), successfulMatchCount.load(), failedMatchCount.load(), (float)testDuration.count()/(60000.f));
	auto testDurationSec = testDuration.count() / 1000;
	SFLog(Game, Info, "Matched {0} / sec", (successfulMatchCount.load() / testDurationSec));


	StopAllThread();

	IHeap::Delete(players);

	matchManager.Clear();

}

