// AVLTreeTest.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "UnitTest_AVLTreeTest.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



TEST_F(AVLTreeTest, DualSortedMapPerfTestSimple)
{
	DualSortedMap<uint,uint> sortedMap(GetHeap());
	TimeStampMS start, end;

	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Insert {0} items, {1}ms", numberOfTest, (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Remove  {0} items, {1}ms", numberOfTest, (end - start).count());


	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
		EXPECT_TRUE((sortedMap.CommitChanges()));
	}
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Insert with commit {0} items, {1}ms", numberOfTest, (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
		EXPECT_TRUE((sortedMap.CommitChanges()));
	}
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Remove with commit  {0} items, {1}ms", numberOfTest, (end - start).count());
}


TEST_F(AVLTreeTest, DualSortedMapPerfTestRead)
{
	DualSortedMap<uint,uint> sortedMap(GetHeap());
	TimeStampMS start, end;

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));

	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Find(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Find {0} items, {1}ms", numberOfTest, (end - start).count());


	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		//uint value = -1;
		long latestValue = -1;

		sortedMap.ForeachOrder(0, 100, [&](const uint& key, const uint& value)
		{
			if (latestValue != -1)
			{
				EXPECT_TRUE(value <= (uint)latestValue);
			}
			latestValue = value;
			return true;
		});
	}
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Query 100 items in {0} items {1} times, {2}ms", numberOfTest, numberOfTest, (end - start).count());
}

TEST_F(AVLTreeTest, DualSortedMapPerfTest1000)
{
	DualSortedMap<uint,uint> sortedMap(GetHeap());
	TimeStampMS start, end;

	int iTest = 0;
	SFLog(Game, Info, "Insert {0} items for test", numberOfTest - 1000);
	start = Util::Time.GetRawTimeMs();
	for (; iTest < std::max(0, (int)numberOfTest - 1000); iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Insertion took {0}ms", (end - start).count());
	EXPECT_TRUE((sortedMap.CommitChanges()));

	start = Util::Time.GetRawTimeMs();
	for (; iTest < (int)numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Insert last 1000 items, {0}ms", (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (iTest = 0; iTest < std::min(1000, (int)numberOfTest); iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Remove first 1000 items, {0}ms", (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (; iTest < (int)numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Remove remain items, {0}ms", (end - start).count());
}


TEST_F(AVLTreeTest, DualSortedMapPerfWithReadThreads)
{
	const int numReadThread = 10;
	const int testItemCount = 10000;
	DualSortedMap<uint, uint> sortedMap(GetHeap());
	TimeStampMS start, end;

	int iTest = 0;
	SFLog(Game, Info, "Insert {0} items for test", numberOfTest - testItemCount);
	start = Util::Time.GetRawTimeMs();
	for (; iTest < std::max(0, (int)numberOfTest - testItemCount); iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Insertion took {0}ms", (end - start).count());
	EXPECT_TRUE((sortedMap.CommitChanges()));

	// Start read threads
	for (int iThread = 0; iThread < numReadThread; iThread++)
	{
		auto newThread = new(GetHeap()) FunctorThread([this, &sortedMap](Thread* pThread)
		{
			while (!pThread->CheckKillEvent(DurationMS(1)))
			{
				uint value;
				auto selcted = Util::Random.Rand(numberOfTest);
				sortedMap.Find(selcted, value);
			}
		});

		newThread->Start();
		m_Threads.push_back(newThread);
	}


	// start test
	start = Util::Time.GetRawTimeMs();
	for (; iTest < (int)numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Insert last {0} items, {1}ms", testItemCount, (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (iTest = 0; iTest < std::min(1000, (int)numberOfTest); iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Remove first {0} items, {1}ms", testItemCount, (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (; iTest < (int)numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));
	end = Util::Time.GetRawTimeMs();
	SFLog(Game, Info, "Remove remain items, {0}ms", (end - start).count());

	// Stop all read threads
	StopAllThread();
}

