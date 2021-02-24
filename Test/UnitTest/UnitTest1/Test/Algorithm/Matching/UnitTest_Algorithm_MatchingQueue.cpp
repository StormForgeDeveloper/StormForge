// Matching queue test
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFSortedMap.h"
#include "Container/SFCircularPageQueue.h"
#include "Container/SFCircularQueue.h"
#include "Object/SFObjectPool.h"
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






// queue player
class QueuePlayer
{
public:

private:


	uint m_PlayerID = 0;

public:

	QueuePlayer()
	{
	}

	// Initialize player
	void Initialize(uint playerID)
	{
		m_PlayerID = playerID;
	}

	uint GetPlayerID() const { return m_PlayerID; }
};




struct QueueItem : public StackPool::Item
{
	StaticArray< QueuePlayer*, 4> Players;

	QueueItem(IHeap& heap)
		: Players(heap)
	{

	}
};





// queue based match maker
class QueueMatchMaker
{
public:
	static constexpr int MAX_MATCHING_PLAYER = 4;

private:

	// Heap
	IHeap& m_Heap;

	// Queue list
	CircularPageQueueAtomic<QueueItem*>* m_QueueByPlayerCount[3] = {0};

	// round robin pattern picking
	std::atomic<uint> m_ReservationStartFrom = 0;

	// matching time out
	// As far as we are going to test speed we don't need to do this.
	DurationMS m_MatchingTimeout = DurationMS(1);

	// match maker patterns
	static const uint stm_MatchingPattern4[][3];
	

public:
	QueueMatchMaker(IHeap& heap)
		: m_Heap(heap)
		//, m_QueueByPlayerCount(heap)
	{
	}

	~QueueMatchMaker()
	{
		Clear();
	}

	// Heap for match making
	IHeap& GetHeap() { return m_Heap;}

	// initialize
	void Initialize()
	{
		//m_QueueByPlayerCount.reserve(MAX_MATCHING_PLAYER - 1);
		for (int iQueue = 0; iQueue < (MAX_MATCHING_PLAYER - 1); iQueue++)
		{
			m_QueueByPlayerCount[iQueue] = new(GetHeap()) CircularPageQueueAtomic<QueueItem*>(GetHeap(), 2048, 1024);
		}
	}

	// clear memory
	void Clear()
	{
		for (auto& itQueue : m_QueueByPlayerCount)
		{
			if (itQueue == nullptr)
				continue;

			QueueItem* pItem = nullptr;
			while (itQueue->Dequeue(pItem))
			{
				IHeap::Delete(pItem);
			}

			IHeap::Delete(itQueue);
		}
		memset(m_QueueByPlayerCount, 0, sizeof(m_QueueByPlayerCount));
		//m_QueueByPlayerCount.Clear();

		ClearFreeQueueItem();
	}


	StackPool m_FreeQueueItem;
	// 
	QueueItem* NewQueueItem()
	{
		//auto pItem = m_FreeQueueItem.Pop();
		//if (pItem != nullptr)
		//{
		//	auto pQueueItem = static_cast<QueueItem*>(pItem);
		//	pQueueItem->Players.Clear();
		//	return pQueueItem;
		//}
		//else
		{
			return new(GetHeap()) QueueItem(GetHeap());
		}
	}

	void FreeQueueItem(QueueItem* pItem)
	{
		//m_FreeQueueItem.Push(pItem);
		IHeap::Delete(pItem);
	}

	void ClearFreeQueueItem()
	{
		auto pItem = m_FreeQueueItem.Pop();
		while (pItem != nullptr)
		{
			IHeap::Delete(pItem);
			pItem = m_FreeQueueItem.Pop();
		}
	}

	size_t GetItemCountInQueue(int iQueue)
	{
		if (iQueue < 0 || iQueue >= countof(m_QueueByPlayerCount))
			return 0;

		if (m_QueueByPlayerCount[iQueue] == nullptr)
			return 0;

		return m_QueueByPlayerCount[iQueue]->size();
	}

	Result EnqueuePlayers(QueueItem* pQueueItem)
	{
		if (pQueueItem == nullptr)
			return ResultCode::INVALID_POINTER;

		if (pQueueItem->Players.size() == 0)
		{
			FreeQueueItem(pQueueItem);
			return ResultCode::INVALID_ARG;
		}

		auto iQueue = pQueueItem->Players.size() - 1;
		AssertRel(iQueue >= 0 && iQueue < countof(m_QueueByPlayerCount));
		//Assert((uint32_t)pQueueItem != 0xCDCDCDCD);
		return m_QueueByPlayerCount[iQueue]->Enqueue(pQueueItem);
	}

	// Match make
	Result MatchMake(Array<QueuePlayer*>& players);
};

const uint QueueMatchMaker::stm_MatchingPattern4[][3] =
{
	//1  2  3
	{ 4, 0, 0 },
	{ 2, 1, 0 },
	{ 1, 0, 1 },
	// repeated pattern for matching balance
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },

	// repeated pattern for circulation
	{ 4, 0, 0 },
	{ 2, 1, 0 },
	{ 1, 0, 1 },
	// repeated pattern for matching balance
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
};





Result QueueMatchMaker::MatchMake(Array<QueuePlayer*>& players)
{
	Result hr = ResultCode::SUCCESS;
	uint targetMatchingMemberCount = 4;
	uint queueCount = targetMatchingMemberCount - 1;
	size_t numPatterns = 0;
	StaticArray<QueuePlayer*, 10> grabbedItems(GetHeap());


	auto pMatchingPatternTable = stm_MatchingPattern4;
	numPatterns = countof(stm_MatchingPattern4);

	// increase pattern offset after getting pattern table
	auto curPatternIndex = m_ReservationStartFrom.fetch_add(1, std::memory_order_relaxed) % numPatterns;

	// Search matching pattern based on queue item count
	auto pCurMatchingPattern = pMatchingPatternTable + curPatternIndex;
	for (uint iPattern = 0; iPattern < numPatterns; iPattern++, curPatternIndex++)
	{
		pCurMatchingPattern = pMatchingPatternTable + (curPatternIndex % numPatterns);
		bool bPatternMat = true;
		for (uint iQueue = 0; iQueue < queueCount; iQueue++)
		{
			if (m_QueueByPlayerCount[iQueue]->size() < (*pCurMatchingPattern)[iQueue])
			{
				bPatternMat = false;
				break;
			}
		}
		if (!bPatternMat)
			continue;

		// we've found best suit matching pattern
		break;
	}

	// failed to find patching pattern with current queue item count
	if (pCurMatchingPattern == nullptr)
	{
		return hr;
	}

	Result result;
	// pull player from the queue
	for (uint iQueue = 0; iQueue < queueCount; iQueue++)
	{
		uint numItemsToDequeue = (*pCurMatchingPattern)[iQueue];
		for (uint iItem = 0; iItem < numItemsToDequeue; iItem++)
		{
			QueueItem *pItem = nullptr;
			result = m_QueueByPlayerCount[iQueue]->Dequeue(pItem);
			if (result)
			{
				//Assert((uint32_t)pItem != 0xCDCDCDCD);
				for (auto& itPlayer : pItem->Players)
				{
					players.push_back(itPlayer);
				}
				FreeQueueItem(pItem);
				pItem = nullptr;
			}
			else
			{
				// we have missing items. maybe alread taken
				//Assert(false);
			}
		}
	}


	if (players.size() == 0)
		return ResultCode::FAIL;


	// pull missing players
	auto startTime = Util::Time.GetTimeMs();
	while(Util::TimeSince(startTime) < m_MatchingTimeout)
	{
		int iQueue = (int)targetMatchingMemberCount - (int)players.size() - 1;
		if (iQueue < 0) // if we found all
			break;

		for(; iQueue >= 0; iQueue--)
		{
			QueueItem *pItem = nullptr;
			result = m_QueueByPlayerCount[iQueue]->Dequeue(pItem);
			if (result)
			{
				//Assert((uint32_t)pItem != 0xCDCDCDCD);
				for (auto& itPlayer : pItem->Players)
				{
					players.push_back(itPlayer);
				}
				FreeQueueItem(pItem);
				//IHeap::Delete(pItem);
				// we need to update queue
				break;
			}
		}

		if (Util::TimeSince(startTime) > DurationMS(m_MatchingTimeout))
			return ResultCode::FAIL;
	}


	return hr;
}



TEST_F(AlgorithmTest, MatchingQueue)
{
	constexpr int NUM_MATCH_THREAD = 1;
	constexpr int NUM_UPDATE_THREAD = 9;
#ifdef DEBUG
	constexpr int NUM_PLAYER = 200;
	constexpr int NUM_SHELL = 50;
	constexpr int MATCHING_VARIATION = 10;
#else
	constexpr int NUM_PLAYER = 2000000;
	constexpr int NUM_SHELL = 5000;
	constexpr int MATCHING_VARIATION = 100;
#endif


	const DurationMS testTime(5 * 60 * 1000);
	std::atomic<uint32_t> playerUpdated(0);
	std::atomic< uint32_t> successfulMatchCount(0);
	std::atomic< uint32_t> failedMatchCount(0);

	auto players = new(GetHeap()) QueuePlayer[NUM_PLAYER];

	CircularQueue<QueuePlayer*, NUM_PLAYER*2> freePlayers;
	CriticalSection m_UpdateLock;
	//StackPool freeQueueItemPool(GetHeap());

	TimeStampMS start, end;

	QueueMatchMaker matchMaker(GetHeap());

	int iTest = 0;
	SFLog(Game, Info, "Initializing {0} items for test\n", NUM_PLAYER);
	start = Util::Time.GetRawTimeMs();
	for (int iPlayer = 0; iPlayer < NUM_PLAYER; iPlayer++)
	{
		players[iPlayer].Initialize(iPlayer + 1);
		EXPECT_TRUE(freePlayers.Enqueue(&players[iPlayer]));
		//EXPECT_TRUE((shuffleMap.Insert(Util::Random.Rand(), &players[iPlayer])));
	}

	//shuffleMap.ForeachOrder(0, (uint)shuffleMap.size(), [&freePlayers](uint32_t key, QueuePlayer* pPlayer)
	//{
	//	freePlayers.Enqueue(pPlayer);
	//	return true;
	//});

	//shuffleMap.ClearMap();

	matchMaker.Initialize();

	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Initialization took {0}ms\n", (end - start).count());


	// Start update threads
	for (int iThread = 0; iThread < NUM_UPDATE_THREAD; iThread++)
	{
		int threadID = iThread;
		auto newThread = new(GetHeap()) FunctorTickThread([&, threadID](Thread* pThread)
		{
			QueueItem* pQueueItem = nullptr;
			auto numPlayers = threadID % (QueueMatchMaker::MAX_MATCHING_PLAYER - 1) + 1;// (Util::Random.Rand() % (QueueMatchMaker::MAX_MATCHING_PLAYER - 1)) + 1;

			if (matchMaker.GetItemCountInQueue(numPlayers - 1) > 10000)
				return true;

			{
				MutexScopeLock lock(m_UpdateLock); // free player dequeue has to be locked

				// If there is not much free players, just do it later
				if (freePlayers.size() < QueueMatchMaker::MAX_MATCHING_PLAYER)
					return true;

				pQueueItem = matchMaker.NewQueueItem();
				for (int iPlayer = 0; iPlayer < numPlayers; iPlayer++)
				{
					QueuePlayer *pPlayer = nullptr;
					if (freePlayers.Dequeue(pPlayer))
						pQueueItem->Players.push_back(pPlayer);
				}
			}

			playerUpdated.fetch_add(1, std::memory_order_relaxed);
			EXPECT_TRUE(matchMaker.EnqueuePlayers(pQueueItem));

			return true;
		});

		newThread->Start();
		newThread->SetThreadName("UpdateThread");
		m_Threads.push_back(newThread);
	}

	// give some time to update thread so that they can queue enough items for match
	ThisThread::SleepFor(DurationMS(10000));

	auto startTime = Util::Time.GetRawTimeMs();

	// Start match threads
	for (int iThread = 0; iThread < NUM_MATCH_THREAD; iThread++)
	{
		auto newThread = new(GetHeap()) FunctorTickThread([&](Thread* pThread)
		{
			auto iPlayer = Util::Random.Rand() % NUM_PLAYER;
			QueuePlayer *pRankingPlayer = nullptr;
			int64_t ranking = 0;
			StaticArray<QueuePlayer*, 4> matchedPlayers(GetHeap());

			if (matchMaker.MatchMake(matchedPlayers))
			{
				successfulMatchCount.fetch_add(1, std::memory_order_relaxed);
			}
			else
			{
				if (matchedPlayers.size() > 0)
					failedMatchCount.fetch_add(1, std::memory_order_relaxed);

				{
					MutexScopeLock lock(m_UpdateLock); // free player dequeue has to be locked

					for (auto itPlayer : matchedPlayers)
					{
						QueuePlayer* pPlayer = itPlayer;
						EXPECT_TRUE(freePlayers.Enqueue(pPlayer));
					}
				}
			}

			return true;
		});

		newThread->Start();
		newThread->SetThreadName("MatchmakingThread");
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
	SFLog(Game, Info, "Matched {0} / sec", ((float)(successfulMatchCount.load() + failedMatchCount.load()) / testDurationSec));

	// Stop all read threads
	StopAllThread();

	matchMaker.Clear();
	freePlayers.ClearQueue();
	IHeap::Delete(players);
}

