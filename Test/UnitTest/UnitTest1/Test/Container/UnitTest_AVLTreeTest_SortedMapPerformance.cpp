// AVLTreeTest.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
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





static void TestSortedMap_PerfTest(IHeap& heap, unsigned numberOfTest, const int *TestValues)
{
	SortedMap<uint,uint> sortedMap(heap);
	TimeStampMS start, end;

	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	end = Util::Time.GetRawTimeMs();
	printf("Insert %d items, %dms\n", numberOfTest, (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (unsigned iTest = 0; iTest < numberOfTest; iTest++)
	{
		uint value = -1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}
	end = Util::Time.GetRawTimeMs();
	printf("Remove  %d items, %dms\n", numberOfTest, (end - start).count());


	unsigned iTest = 0;
	for (; iTest < numberOfTest - 1000; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	start = Util::Time.GetRawTimeMs();
	for (; iTest < numberOfTest; iTest++)
	{
		EXPECT_TRUE((sortedMap.Insert(TestValues[iTest], TestValues[iTest])));
	}
	end = Util::Time.GetRawTimeMs();
	printf("Insert last 1000 items, %dms\n", (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (iTest = 0; iTest < std::min((unsigned)1000, numberOfTest); iTest++)
	{
		uint value = -1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}
	end = Util::Time.GetRawTimeMs();
	printf("Remove first 1000 items, %dms\n", (end - start).count());

	start = Util::Time.GetRawTimeMs();
	for (; iTest < numberOfTest; iTest++)
	{
		uint value = -1;
		EXPECT_TRUE((sortedMap.Remove(TestValues[iTest], value)));
		EXPECT_TRUE((int)value == TestValues[iTest]);
	}
	end = Util::Time.GetRawTimeMs();
	printf("Remove remain items, %dms\n", (end - start).count());
}



TEST_F(AVLTreeTest, SortedMapPerformance)
{
	TestSortedMap_PerfTest(GetHeap(), MAX_TEST_VALUE, TestValues);
}



