// TestApp.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "String/SFStrUtil.h"
#include "String/SFStrFormat.h"
#include "Object/SFSharedPointer.h"
#include "UnitTest_HashTableTest.h"
#include "Container/SFHashTable2.h"
#include "Util/SFTimeUtil.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;

#ifdef DEBUG
#define TestScale 1
#else
#define TestScale 10
#endif





const int64_t TEST_COUNT = TestScale * 99999;
const int64_t MAX_NUMBER = TestScale * TestScale * TestScale * TestScale * TestScale * TestScale * 1000;

struct TestMapNode2
{
public:
	int64_t Value;
};


class TestMapNodeShared : public SharedObject
{
public:
	volatile int64_t Value;
};

TEST_F(HashTableTest, HashTable2_NonUnique)
{


	typedef HashTable2<	int64_t, TestMapNode2*,
		NonUniqueKeyTrait, ThreadSyncTraitNoneT<int64_t, TestMapNode2*>
	> TestTableType;

	TestTableType TestMap(GetHeap());
	std::unordered_map<int, int> checkSet;


	for (int64_t iTest = 0; iTest < TEST_COUNT; iTest++)
	{
		int value = rand() % MAX_NUMBER;
		auto itFound = checkSet.find(value);

		TestMapNode2 *pNewNode = new TestMapNode2;
		memset(pNewNode, 0, sizeof(TestMapNode2));
		pNewNode->Value = value;
		if (itFound == checkSet.end())
		{
			checkSet.insert(std::make_pair(value, 1));
		}
		else
		{
			int Count = checkSet[value];
			checkSet[value] = Count + 1;
		}
		Result hrRes = TestMap.Insert(pNewNode->Value, pNewNode);
		AssertRel(hrRes);
		AssertRel(hrRes);
	}


	for (int iTest = 0; iTest < TEST_COUNT; iTest++)
	{
		int value = rand() % MAX_NUMBER;
		auto itFound = checkSet.find(value);
		TestMapNode2 *pNode = nullptr;

		if (itFound == checkSet.end())
		{
			AssertRel(!(TestMap.Find(value, pNode)));
		}
		else
		{
			AssertRel((TestMap.Find(value, pNode)));
			AssertRel(value == pNode->Value);
			EXPECT_EQ(value, pNode->Value);
		}
	}

	auto itCheck = checkSet.begin();
	for (; itCheck != checkSet.end(); itCheck++)
	{
		Result hr;
		TestMapNode2* pNode = nullptr;
		hr = TestMap.Find(itCheck->first, pNode);
		AssertRel((hr));

		if (!(hr))
			continue;
		TestMapNode2* pErased = nullptr;
		hr = TestMap.Erase(pNode->Value, pErased);
		AssertRel(pNode == pErased);
		AssertRel((hr));
		if (!(hr))
			continue;
		delete pNode;
	}
}



TEST_F(HashTableTest, HashTable2_Unique)
{
	typedef HashTable2<	int64_t, TestMapNode2*,
		UniqueKeyTrait, ThreadSyncTraitNoneT<int64_t, TestMapNode2*>
	> TestTableType;

	TestTableType TestMap(GetHeap());
	std::unordered_set<int> checkSet;
	TestMapNode2* pNode = nullptr;

	for (int64_t iTest = 0; iTest < TEST_COUNT; iTest++)
	{
		int value = rand() % MAX_NUMBER;
		auto itFound = checkSet.find(value);

		if (itFound == checkSet.end())
		{
			TestMapNode2 *pNewNode = new TestMapNode2;
			memset(pNewNode, 0, sizeof(TestMapNode2));
			pNewNode->Value = value;
			checkSet.insert(value);
			AssertRel((TestMap.Insert(value, pNewNode)));
		}
	}

	for (int64_t iTest = 0; iTest < TEST_COUNT; iTest++)
	{
		int value = rand() % MAX_NUMBER;
		auto itFound = checkSet.find(value);

		if (itFound == checkSet.end())
		{
			AssertRel(!(TestMap.Find(value, pNode)));
		}
		else
		{
			AssertRel((TestMap.Find(value, pNode)));
		}
	}

	auto itCheck = checkSet.begin();
	for (; itCheck != checkSet.end(); itCheck++)
	{
		AssertRel((TestMap.Find(*itCheck, pNode)));
		TestMapNode2 *pErased;
		AssertRel((TestMap.Erase(pNode->Value, pErased)));
		AssertRel(pNode == pErased);
		delete pNode;
	}

}

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
TEST_F(HashTableTest, HashTable2_UniqueMT)
{
	const int READ_THREAD_COUNT = 10;


	SyncCounter numberOfItems;

	typedef HashTable2<	int64_t, SharedPointerT<TestMapNodeShared>,
		UniqueKeyTrait, ThreadSyncTraitReadWriteT<int64_t, SharedPointerT<TestMapNodeShared>>
	> TestTableType;

	Concurrency::concurrent_unordered_map<int64_t, SharedPointerT<TestMapNodeShared>> m_TestMap;
	TestTableType TestMap(GetHeap());
	TestMapNodeShared* pNode = nullptr;


	for (int64_t ID = 0; ID < READ_THREAD_COUNT; ID++)
	{
		FunctorThread *pTask = new FunctorThread([&, ID](Thread *pThread)
		{
			while (!pThread->CheckKillEvent(DurationMS(5)))
			{
				int value = rand() % MAX_NUMBER;
				SharedPointerT<TestMapNodeShared> pFound = nullptr;

				if ((TestMap.Find(value, pFound)))
				{
					ThisThread::SleepFor(DurationMS(10));
					AssertRel(value == pFound->Value);
					EXPECT_EQ(value, pFound->Value);
				}
				else
				{
				}
			}

		});
		pTask->Start();
		m_Threads.push_back(pTask);
	};


	for (int64_t i = 0; i < (TEST_COUNT); i++)
	{
		int64_t value = (rand() % MAX_NUMBER) + 1;
		TestMapNodeShared *pNewNode = new TestMapNodeShared;
		pNewNode->Value = value;
		if ((TestMap.Insert(value, pNewNode)))
		{
			m_TestMap.insert(std::make_pair(value, pNewNode));
			numberOfItems.fetch_add(1, std::memory_order_relaxed);
		}
		else
		{
			//delete pNewNode;
		}
	}


	TimeStampMS start = Util::Time.GetRawTimeMs();
	TimeStampMS end = Util::Time.GetRawTimeMs();
#ifdef DEBUG
	DurationMS runningTime = DurationMS(1 * 60 * 1000);
#else
	DurationMS runningTime = DurationMS(5 * 60 * 1000);
#endif
	for (; (end - start) < runningTime;)
	{
		int64_t value = (rand() % MAX_NUMBER) + 1;
		//int64_t operation = rand() % MAX_NUMBER;

		SharedPointerT<TestMapNodeShared> pFound = nullptr;

		if ((TestMap.Find(value, pFound)))
		{
			EXPECT_EQ(value, pFound->Value);
			AssertRel(value == pFound->Value);
			SharedPointerT<TestMapNodeShared> pErased = nullptr;
			if ((TestMap.Erase((int64_t)pFound->Value, pErased)))
			{
				SharedPointerT<TestMapNodeShared> pErased2 = nullptr;
				AssertRel(!(TestMap.Erase((int64_t)pFound->Value, pErased2)));
				AssertRel(pErased == pFound);
				AssertRel(pErased->Value == pFound->Value);

				auto itFound = m_TestMap.find(value);
				AssertRel(itFound->second == pErased);
				m_TestMap.unsafe_erase(value);

				numberOfItems.fetch_sub(1, std::memory_order_relaxed);
			}
			else
			{
				//AssertRel(false);
				TestMap.Erase((int64_t)pFound->Value, pErased);
			}
		}
		else
		{
			TestMapNodeShared *pNewNode = new TestMapNodeShared;
			pNewNode->Value = value;
			if ((TestMap.Insert(value, pNewNode)))
			{
				m_TestMap.insert(std::make_pair(value, pNewNode));
				numberOfItems.fetch_add(1, std::memory_order_relaxed);
			}
			else
			{
				//delete pNewNode;
			}
		}

		end = Util::Time.GetRawTimeMs();
	}


	ThisThread::SleepFor(DurationMS(1000));

	StopAllThread();

	AssertRel(TestMap.size() == numberOfItems.load(std::memory_order_relaxed));

	TestMap.Clear();
	AssertRel(TestMap.size() == 0);
	EXPECT_EQ(0, TestMap.size());
}
#endif

TEST_F(HashTableTest, HashTable2_UniqueWriteMT)
{
	const int READ_THREAD_COUNT = 10;
	const int WRITE_THREAD_COUNT = 10;


	SyncCounter workCounterRead, workCounterWrite, numberOfItems;

	typedef HashTable2<	int64_t, SharedPointerT<TestMapNodeShared>,
		UniqueKeyTrait, ThreadSyncTraitReadWriteT<int64_t, SharedPointerT<TestMapNodeShared>>
	> TestTableType;


	TestTableType TestMap(GetHeap(), 1);
	//TestMapNodeShared* pNode = nullptr;


	for (int64_t ID = 0; ID < READ_THREAD_COUNT; ID++)
	{
		FunctorThread *pTask = new FunctorThread([&, ID](Thread *pThread)
		{
			workCounterRead.fetch_add(1, std::memory_order_relaxed);

			while (!pThread->CheckKillEvent(DurationMS(5)))
			{
				int value = rand() % MAX_NUMBER;
				SharedPointerT<TestMapNodeShared> pFound = nullptr;

				if ((TestMap.Find(value, pFound)))
				{
					ThisThread::SleepFor(DurationMS(10));
					AssertRel(value == pFound->Value);
					EXPECT_EQ(value, pFound->Value);
				}
				else
				{
				}
			}

			workCounterRead.fetch_sub(1, std::memory_order_relaxed);

		});
		pTask->Start();
		m_Threads.push_back(pTask);
	};


	for (int64_t i = 0; i < (TEST_COUNT); i++)
	{
		int64_t value = (rand() % MAX_NUMBER) + 1;
		TestMapNodeShared *pNewNode = new TestMapNodeShared;
		pNewNode->Value = value;
		if ((TestMap.Insert(value, pNewNode)))
		{
			numberOfItems.fetch_add(1, std::memory_order_relaxed);
		}
		else
		{
			//delete pNewNode;
		}
	}


	//auto start = BR::Util::Time.GetRawTimeMs();
	//auto end = BR::Util::Time.GetRawTimeMs();
#ifdef DEBUG
	auto runningTime = DurationMS(5 * 1000);
#else
	//ULONG runningTime = 30 * 60 * 1000;
	auto runningTime = DurationMS(60 * 1000);
#endif


	for (int iThread = 0; iThread < WRITE_THREAD_COUNT; iThread++)
	{
		FunctorThread *pTask = new FunctorThread([&](Thread *pThread)
		{
			workCounterWrite.fetch_add(1, std::memory_order_acquire);

			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				int64_t value = (rand() % MAX_NUMBER) + 1;
				//int64_t operation = rand() % MAX_NUMBER;

				SharedPointerT<TestMapNodeShared> pFound = nullptr;

				if ((TestMap.Find(value, pFound)))
				{
					AssertRel(pFound != nullptr);
					EXPECT_EQ(value, pFound->Value);
					AssertRel(value == pFound->Value);
					SharedPointerT<TestMapNodeShared> pErased = nullptr;
					if ((TestMap.Erase((int64_t)pFound->Value, pErased)))
					{
						AssertRel(pErased->Value == pFound->Value);
						numberOfItems.fetch_sub(1, std::memory_order_relaxed);
					}
					else
					{
						//AssertRel(false);
						//TestMap.Erase(pFound->Value, pErased);
					}
				}
				else
				{
					TestMapNodeShared *pNewNode = new TestMapNodeShared;
					pNewNode->Value = value;
					if ((TestMap.Insert(value, pNewNode)))
					{
						numberOfItems.fetch_add(1, std::memory_order_relaxed);
					}
				}

			}

			workCounterWrite.fetch_sub(1, std::memory_order_release);
		});
		pTask->Start();
		m_Threads.push_back(pTask);
	}


	ThisThread::SleepFor(DurationMS(runningTime));

	StopAllThread();

	AssertRel(TestMap.size() == numberOfItems.load(std::memory_order_relaxed));

	TestMap.Clear();
	AssertRel(TestMap.size() == 0);
	EXPECT_EQ(0, TestMap.size());
}

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
TEST_F(HashTableTest, HashTable2_PerfRead)
{
	const int READ_THREAD_COUNT = 10;

	SyncCounter numberOfItems;
	SyncCounter readCount(0), writeCount(0);

	typedef HashTable2<	int64_t, SharedPointerT<TestMapNodeShared>,
		UniqueKeyTrait, ThreadSyncTraitReadWriteT<int64_t, SharedPointerT<TestMapNodeShared>>
	> TestTableType;

	Concurrency::concurrent_unordered_map<int64_t, SharedPointerT<TestMapNodeShared>> m_TestMap;
	TestTableType TestMap(GetHeap(), 1024);
	//TestMapNodeShared* pNode = nullptr;


	for (int64_t ID = 0; ID < READ_THREAD_COUNT; ID++)
	{
		FunctorThread *pTask = new FunctorThread([&, ID](Thread *pThread)
		{
			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				int value = rand() % MAX_NUMBER;
				SharedPointerT<TestMapNodeShared> pFound = nullptr;

				if ((TestMap.Find(value, pFound)))
				{
					AssertRel(value == pFound->Value);
					EXPECT_EQ(value, pFound->Value);
				}
				else
				{
				}
				readCount.fetch_add(1, std::memory_order_relaxed);
			}

		});
		pTask->Start();
		m_Threads.push_back(pTask);
	};


	for (int64_t i = 0; i < (TEST_COUNT); i++)
	{
		int value = rand() % MAX_NUMBER;
		TestMapNodeShared *pNewNode = new TestMapNodeShared;
		pNewNode->Value = value;
		if ((TestMap.Insert(value, pNewNode)))
		{
			m_TestMap.insert(std::make_pair(value, pNewNode));
			numberOfItems.fetch_add(1, std::memory_order_relaxed);
		}
		else
		{
			//delete pNewNode;
		}
		writeCount.fetch_add(1, std::memory_order_relaxed);
	}


	auto start = Util::Time.GetRawTimeMs();
	auto end = Util::Time.GetRawTimeMs();
#ifdef DEBUG
	auto runningTime = DurationMS(1 * 60 * 1000);
#else
	auto runningTime = DurationMS(10 * 60 * 1000);
#endif
	for (; (end - start) < runningTime;)
	{
		int64_t value = rand() % MAX_NUMBER;
		//int64_t operation = rand() % MAX_NUMBER;

		SharedPointerT<TestMapNodeShared> pFound = nullptr;

		if ((TestMap.Find(value, pFound)))
		{
			AssertRel(pFound != nullptr);
			EXPECT_EQ(value, pFound->Value);
			AssertRel(value == pFound->Value);
			SharedPointerT<TestMapNodeShared> pErased = nullptr;
			if ((TestMap.Erase((int64_t)pFound->Value, pErased)))
			{
				SharedPointerT<TestMapNodeShared> pErased2 = nullptr;
				AssertRel(!(TestMap.Erase((int64_t)pFound->Value, pErased2)));
				AssertRel(pErased == pFound);
				AssertRel(pErased->Value == pFound->Value);

				auto itFound = m_TestMap.find(value);
				AssertRel(itFound->second == pErased);
				m_TestMap.unsafe_erase(value);

				numberOfItems.fetch_sub(1, std::memory_order_relaxed);
			}
			else
			{
				//AssertRel(false);
				TestMap.Erase((int64_t)pFound->Value, pErased);
			}
		}
		else
		{
			TestMapNodeShared *pNewNode = new TestMapNodeShared;
			pNewNode->Value = value;
			if ((TestMap.Insert(value, pNewNode)))
			{
				m_TestMap.insert(std::make_pair(value, pNewNode));
				numberOfItems.fetch_add(1, std::memory_order_relaxed);
			}
			else
			{
				//delete pNewNode;
			}
		}

		writeCount.fetch_add(1, std::memory_order_relaxed);
		end = Util::Time.GetRawTimeMs();
	}


	ThisThread::SleepFor(DurationMS(1000));

	StopAllThread();

	AssertRel(TestMap.size() == numberOfItems.load(std::memory_order_relaxed));

	TestMap.Clear();
	AssertRel(TestMap.size() == 0);
	EXPECT_EQ(0, TestMap.size());

	printf("Read: %llu, Write: %llu\n", readCount.load(std::memory_order_acquire), writeCount.load(std::memory_order_acquire));
}
#endif

TEST_F(HashTableTest, HashTable2_PerfReadWriteMT)
{
	const int READ_THREAD_COUNT = 8;
	const int WRITE_THREAD_COUNT = 8;


	std::atomic<uint64_t> numberOfItems;
	std::atomic<uint64_t> readCount(0), writeCount(0);

	typedef HashTable2<	int64_t, SharedPointerT<TestMapNodeShared>,
		UniqueKeyTrait
	> TestTableType;


	TestTableType TestMap(GetHeap(), 3);
	//TestMapNodeShared* pNode = nullptr;


	for (int64_t ID = 0; ID < READ_THREAD_COUNT; ID++)
	{
		FunctorThread *pTask = new FunctorThread([&, ID](Thread *pThread)
		{
			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				int value = rand() % MAX_NUMBER;
				SharedPointerT<TestMapNodeShared> pFound = nullptr;

				if ((TestMap.Find(value, pFound)))
				{
					AssertRel(value == pFound->Value);
				}
				else
				{
				}
				readCount.fetch_add(1, std::memory_order_relaxed);
			}

		});
		pTask->Start();
		m_Threads.push_back(pTask);
	};


	for (int64_t i = 0; i < (TEST_COUNT); i++)
	{
		int value = rand() % MAX_NUMBER;
		TestMapNodeShared *pNewNode = new TestMapNodeShared;
		pNewNode->Value = value;
		if ((TestMap.Insert(value, pNewNode)))
		{
			numberOfItems.fetch_add(1, std::memory_order_relaxed);
		}
		else
		{
			//delete pNewNode;
		}
		writeCount.fetch_add(1, std::memory_order_relaxed);
	}


	//auto start = BR::Util::Time.GetRawTimeMs();
	//auto end = BR::Util::Time.GetRawTimeMs();
#ifdef DEBUG
	auto runningTime = DurationMS(1 * 60 * 1000);
#else
	auto runningTime = DurationMS(10 * 60 * 1000);
#endif


	for (int iThread = 0; iThread < WRITE_THREAD_COUNT; iThread++)
	{
		FunctorThread *pTask = new FunctorThread([&](Thread *pThread)
		{
			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				int64_t value = rand() % MAX_NUMBER;
				//int64_t operation = rand() % MAX_NUMBER;

				SharedPointerT<TestMapNodeShared> pFound = nullptr;

				if ((TestMap.Find(value, pFound)))
				{
					EXPECT_EQ(value, pFound->Value);
					AssertRel(value == pFound->Value);
					SharedPointerT<TestMapNodeShared> pErased = nullptr;
					if ((TestMap.Erase((int64_t)pFound->Value, pErased)))
					{
						AssertRel(pErased->Value == pFound->Value);
						numberOfItems.fetch_sub(1, std::memory_order_relaxed);
					}
					else
					{
						//AssertRel(false);
						//TestMap.Erase(pFound->Value, pErased);
					}
				}
				else
				{
					TestMapNodeShared *pNewNode = new TestMapNodeShared;
					pNewNode->Value = value;
					if ((TestMap.Insert(value, pNewNode)))
					{
						numberOfItems.fetch_add(1, std::memory_order_relaxed);
					}
				}
				writeCount.fetch_add(1, std::memory_order_relaxed);
			}
		});
		pTask->Start();
		m_Threads.push_back(pTask);
	}



	ThisThread::SleepFor(DurationMS(runningTime));

	StopAllThread();

	AssertRel(TestMap.size() == numberOfItems.load(std::memory_order_relaxed));

	TestMap.Clear();
	AssertRel(TestMap.size() == 0);
	EXPECT_EQ(0, TestMap.size());

	printf("Read: %llu, Write: %llu\n", readCount.load(std::memory_order_acquire), writeCount.load(std::memory_order_acquire));
}




