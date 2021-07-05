// AVLTreeTest.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
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



TEST_F(AVLTreeTest, DualSortedMapSimple)
{

	for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
	{
		TestValues[iTest] = MAX_TEST_VALUE - iTest;
	}

	DualSortedMap<uint,uint> sortedMap(GetHeap());

	int64_t order = -1;
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest], &order));
		EXPECT_TRUE(order == 0);
		uint value = (uint)-1;
		EXPECT_TRUE(sortedMap.Remove(TestValues[iTest], value));
		EXPECT_TRUE((int)value == TestValues[iTest]);

		EXPECT_TRUE(!sortedMap.Find(TestValues[iTest], value));

		if ((rand()%10) > 5)
			EXPECT_TRUE(sortedMap.CommitChanges());
	}

	EXPECT_TRUE(sortedMap.CommitChanges());

	EXPECT_TRUE(sortedMap.size() == 0);

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest], &order));
		EXPECT_TRUE(order == iTest);
	}

	EXPECT_TRUE(sortedMap.CommitChanges());

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE(sortedMap.Remove(TestValues[iTest], value));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.CommitChanges());

	EXPECT_TRUE(sortedMap.size() == 0);

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest]));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE(!sortedMap.Find(TestValues[iTest], value));
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));

	EXPECT_TRUE(sortedMap.size() == 0);



	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Find(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));
	EXPECT_TRUE(sortedMap.size() == 0);


	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));
	EXPECT_TRUE(sortedMap.size() == 0);

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));
	EXPECT_TRUE(sortedMap.size() == 0);
}


TEST_F(AVLTreeTest, DualSortedMapOrderSequential)
{
	DualSortedMap<uint,uint> sortedMap(GetHeap());

	for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
	{
		TestValues[iTest] = MAX_TEST_VALUE - iTest;
	}


	// test foreach
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		decltype(iTest) innerTest = 0;
		
		sortedMap.ForeachOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			EXPECT_TRUE(TestValues[iTest + innerTest] == (int)value);
			innerTest++;
			return true;
		});
		
		sortedMap.ForeachReverseOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			innerTest++;
			EXPECT_TRUE(TestValues[iTest + innerTest] == (int)value);
			return true;
		});
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		decltype(iTest) innerTest = 0;

		sortedMap.ForeachOrder(0, numberOfTest - iTest, [&](const uint& key, const uint& value)
		{
			EXPECT_TRUE(TestValues[innerTest] == (int)value);
			innerTest++;
			return true;
		});

		sortedMap.ForeachReverseOrder(0, numberOfTest - iTest, [&](const uint& key, const uint& value)
		{
			innerTest--;
			EXPECT_TRUE(TestValues[innerTest] == (int)value);
			return true;
		});
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));
	EXPECT_TRUE(sortedMap.size() == 0);


	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		decltype(iTest) innerTest = 0;

		sortedMap.ForeachOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			EXPECT_TRUE(TestValues[iTest + innerTest] == (int)value);
			innerTest++;
			return true;
		});

		sortedMap.ForeachReverseOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			innerTest--;
			EXPECT_TRUE(TestValues[iTest + innerTest] == (int)value);
			return true;
		});
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE((sortedMap.CommitChanges()));
	EXPECT_TRUE(sortedMap.size() == 0);
}

TEST_F(AVLTreeTest, DualSortedMapRandom)
{
	DualSortedMap<uint,uint> sortedMap(GetHeap());

	// test foreach
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));

#ifdef DEBUG
	const unsigned testOffset = 1;
#else
	const unsigned testOffset = 601;
#endif

	for (unsigned iTest = 0; iTest < numberOfTest; iTest += testOffset)
	{
		long latestValue = -1;

		sortedMap.ForeachOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			if (latestValue != -1)
			{
				EXPECT_TRUE(value <= (uint)latestValue);
			}
			latestValue = value;
			return true;
		});

		latestValue = -1;
		sortedMap.ForeachReverseOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			if (latestValue != -1)
			{
				EXPECT_TRUE(value >= (uint)latestValue);
			}
			latestValue = value;
			return true;
		});
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest += testOffset)
	{
		long latestValue = -1;

		sortedMap.ForeachOrder(0, numberOfTest - iTest, [&](const uint& key, const uint& value)
		{
			if (latestValue != -1)
			{
				EXPECT_TRUE(value <= (uint)latestValue);
			}
			latestValue = value;
			return true;
		});

		latestValue = -1;
		sortedMap.ForeachReverseOrder(0, numberOfTest - iTest, [&](const uint& key, const uint& value)
		{
			if (latestValue != -1)
			{
				EXPECT_TRUE(value >= (uint)latestValue);
			}
			latestValue = value;
			return true;
		});
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));

	EXPECT_TRUE(sortedMap.size() == 0);
}

TEST_F(AVLTreeTest, DualSortedMapRandomForeach)
{
	DualSortedMap<uint,uint> sortedMap(GetHeap());

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));

#ifdef DEBUG
	const unsigned testOffset = 1;
	DurationMS runningTime = DurationMS(60 * 1000);
#else
	const unsigned testOffset = 611;
	DurationMS runningTime = DurationMS(2 * 60 * 1000);
#endif

	TimeStampMS start = Util::Time.GetRawTimeMs();
	TimeStampMS end = Util::Time.GetRawTimeMs();
	int *Status = new int[numberOfTest];
	memset(Status, 0, sizeof(int)*numberOfTest);
	for (unsigned iTest = 0; (end - start) < runningTime; iTest++)
	{
		uint value = (uint)-1;
		uint testIndex = ((uint)rand()) % numberOfTest;
		if (Status[testIndex] == 0)
		{
			Status[testIndex] = 1;
			EXPECT_TRUE((sortedMap.Remove(TestValues[testIndex], value)));
			EXPECT_TRUE((int)value == TestValues[testIndex]);
		}
		else
		{
			Status[testIndex] = 0;
			EXPECT_TRUE((sortedMap.Insert(TestValues[testIndex], TestValues[testIndex])));
		}

		if ((iTest + 1) % 10)
		{
			EXPECT_TRUE((sortedMap.CommitChanges()));
		}


		for (unsigned iLocalTest = 0; iLocalTest < numberOfTest; iLocalTest += testOffset)
		{
			long latestValue = -1;

			sortedMap.ForeachOrder(iLocalTest, numberOfTest, [&](const uint& key, const uint& value)
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
	}

	delete[] Status;
}



TEST_F(AVLTreeTest, DualSortedMapThread)
{
	DualSortedMap<uint,Atomic<uint>> sortedMap(GetHeap());
	int *Status = new int[numberOfTest];
	const int NUM_THREAD = 10;

	memset(Status, 0, sizeof(int)*numberOfTest);

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	EXPECT_TRUE((sortedMap.CommitChanges()));

	
	{
		long latestValue = -1;
		uint testIndex = ((uint)rand()) % numberOfTest;
		sortedMap.ForeachOrder(testIndex, 1000, [&](const uint& key, const Atomic<uint>& value)
		{
			if (latestValue != -1)
			{
				EXPECT_TRUE(value <= (uint)latestValue);
			}
			latestValue = value;
			return true;
		});
	}


	// TODO: broken on Windows, probably AMD CPU or VS lib on AMD CPU issue
#if SF_PLATFORM != SF_PLATFORM_WINDOWS
	for (int iThread = 0; iThread < NUM_THREAD; iThread++)
	{
		auto thread = new(GetHeap()) FunctorThread(
			[&](Thread* pThread)
			{
				while (true)
				{
					auto loopInterval = pThread->UpdateInterval(DurationMS(10));

					if (pThread->CheckKillEvent(loopInterval))
					{
						// Kill Event signaled
						break;
					}


					// NOTE: This will fails when there is multiple commit happened from other thread. it just matter of statistic
					long latestValue = -1;
					uint testIndex = ((uint)rand()) % numberOfTest;
					uint curIndex = testIndex;
					sortedMap.ForeachOrder(testIndex, 20, [&](const uint& key, const Atomic<uint>& value)
					{
						// -1: initial value
						if (latestValue != -1)
						{
							EXPECT_LE(value, (uint)latestValue);
						}
						latestValue = value;
						curIndex++;
						return true;
					});
				}
			});

		thread->Start();
		m_Threads.push_back(thread);
	}

#endif

	auto start = Util::Time.GetRawTimeMs();
	auto end = Util::Time.GetRawTimeMs();
#ifdef DEBUG
	auto runningTime = DurationMS(60 * 1000);
#else
	auto runningTime = DurationMS(30 * 60 * 1000);
#endif
	for (unsigned iTest = numberOfTest; (end - start) < runningTime; iTest++)
	{
		Atomic<uint> value = (uint)-1;
		uint testIndex = ((uint)rand()) % numberOfTest;
		if (Status[testIndex] == 0)
		{
			Status[testIndex] = 1;
			EXPECT_TRUE((sortedMap.Remove(TestValues[testIndex], value)));
			EXPECT_TRUE((INT)value == TestValues[testIndex]);
		}
		else
		{
			Status[testIndex] = 0;
			EXPECT_TRUE((sortedMap.Insert(TestValues[testIndex], TestValues[testIndex])));
		}

		if ((iTest + 1) % 10)
		{
			EXPECT_TRUE((sortedMap.CommitChanges()));
		}

		end = Util::Time.GetRawTimeMs();
	}

	StopAllThread();

	delete[] Status;
}

