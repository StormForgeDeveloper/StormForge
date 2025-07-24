// AVLTreeTest.cpp : Defines the entry point for the console application.
//


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFSortedMap.h"
#include "Util/SFTimeUtil.h"
#include <unordered_map>

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





TEST_F(AVLTreeTest, SortedMapSimple)
//void TestSortedMap_Simple(unsigned numberOfTest, const int *TestValues)
{

	for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
	{
		TestValues[iTest] = MAX_TEST_VALUE - iTest;
	}

	SortedMap<uint,uint> sortedMap;

	int64_t order = -1;
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest], &order)));
		EXPECT_TRUE(order == 0);
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest], &order)));
		EXPECT_TRUE(order == iTest);
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);
}



TEST_F(AVLTreeTest, SortedMapOrderSequential)
{
	SortedMap<uint,uint> sortedMap;

	for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
	{
		TestValues[iTest] = MAX_TEST_VALUE - iTest;
	}

	// test foreach
	int64_t order = -1;
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest], &order));
		EXPECT_TRUE(order == iTest);
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest += offset)
	{
		decltype(iTest) innerTest = 0;

		sortedMap.ForeachOrder(iTest, numberOfTest, [&](const uint& key, const uint& value) -> bool
		{
			EXPECT_TRUE(TestValues[iTest + innerTest] == (INT)value);
			innerTest++;
			return true;
		});

		innerTest = numberOfTest - iTest;
		sortedMap.ForeachReverseOrder(iTest, numberOfTest, [&](const uint& key, const uint& value) -> bool
		{
			innerTest--;
			EXPECT_TRUE(TestValues[innerTest] == (INT)value);
			return true;
		});
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest += offset)
	{
		decltype(iTest) innerTest = 0;

		sortedMap.ForeachOrder(0, numberOfTest - iTest, [&](const uint& key, const uint& value)
		{
			EXPECT_TRUE(TestValues[innerTest] == (INT)value);
			innerTest++;
			return true;
		});

		innerTest = numberOfTest;
		sortedMap.ForeachReverseOrder(0, numberOfTest - iTest, [&](const uint& key, const uint& value)
		{
			innerTest--;
			EXPECT_TRUE(TestValues[innerTest] == (INT)value);
			return true;
		});
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = (uint)-1;
		EXPECT_TRUE(sortedMap.Remove(TestValues[iTest], value));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);


	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest]));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest += offset)
	{
		decltype(iTest) innerTest = 0;

		sortedMap.ForeachOrder(iTest, numberOfTest, [&](const uint& key, const uint& value)
		{
			EXPECT_TRUE(TestValues[iTest + innerTest] == (INT)value);
			innerTest++;
			return true;
		});
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE(sortedMap.Remove(TestValues[iTest], value));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);
}

TEST_F(AVLTreeTest, SortedMapOrderRandom)
{
	SortedMap<uint,uint> sortedMap;

	// test foreach
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest]));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
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

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
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
		EXPECT_TRUE(sortedMap.Remove(TestValues[iTest], value));
		EXPECT_TRUE((INT)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);


	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		EXPECT_TRUE(sortedMap.Insert(TestValues[iTest], TestValues[iTest]));
	}

	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
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
	}

	for (int iTest = numberOfTest - 1; iTest >= 0; iTest--)
	{
		uint value = (uint)-1;
		EXPECT_TRUE(sortedMap.Remove(TestValues[iTest], value));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}

	EXPECT_TRUE(sortedMap.size() == 0);
}

