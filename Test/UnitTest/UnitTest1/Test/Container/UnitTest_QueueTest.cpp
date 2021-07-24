// QueueTest
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemory.h"
#include "UnitTest_QueueTest.h"
#include "SFEngine.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Container/SFPageQueue.h"
#include "Container/SFCircularPageQueue.h"




using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



TEST_F(QueueTest, PageQueueSimple)
{
	{
		PageQueue<int> testQueue(GetHeap(), 4);

		for (int iValue = 0; iValue < 513; iValue++)
		{
			EXPECT_TRUE(testQueue.Enqueue(iValue));
		}

		for (int iValue = 0; iValue < 513; iValue++)
		{
			int DequeueValue = -1;
			EXPECT_TRUE(testQueue.Dequeue(DequeueValue));

			EXPECT_EQ(DequeueValue, iValue);
		}
	}

	{
		PageQueue<int> testQueue(GetHeap(), 16);

		for (int iValue = 0; iValue < 513; iValue++)
		{
			EXPECT_TRUE(testQueue.Enqueue(iValue));
		}

		for (int iValue = 0; iValue < 513; iValue++)
		{
			int DequeueValue = -1;
			EXPECT_TRUE(testQueue.Dequeue(DequeueValue));

			EXPECT_EQ(DequeueValue, iValue);
		}
	}

	{
		PageQueue<int> testQueue(GetHeap(), 32);

		for (int iValue = 0; iValue < 513; iValue++)
		{
			EXPECT_TRUE(testQueue.Enqueue(iValue));
		}

		for (int iValue = 0; iValue < 513; iValue++)
		{
			int DequeueValue = -1;
			EXPECT_TRUE(testQueue.Dequeue(DequeueValue));

			EXPECT_EQ(DequeueValue, iValue);
		}
	}

	{
		PageQueue<int> testQueue(GetHeap(), 60);

		for (int iValue = 0; iValue < 513; iValue++)
		{
			EXPECT_TRUE(testQueue.Enqueue(iValue));
		}

		for (int iValue = 0; iValue < 513; iValue++)
		{
			int DequeueValue = -1;
			EXPECT_TRUE(testQueue.Dequeue(DequeueValue));

			EXPECT_EQ(DequeueValue, iValue);
		}
	}

	{
		PageQueue<int> testQueue(GetHeap());

		for (int iValue = 0; iValue < 513; iValue++)
		{
			EXPECT_TRUE(testQueue.Enqueue(iValue));
		}

		for (int iValue = 0; iValue < 513; iValue++)
		{
			int DequeueValue = -1;
			EXPECT_TRUE(testQueue.Dequeue(DequeueValue));

			EXPECT_EQ(DequeueValue, iValue);
		}
	}
}

TEST_F(QueueTest, PageQueueRandom)
{
	PageQueue<int> testQueue(GetHeap(), 40);

	int PrevDequeueValue{};
	for (int iValue = 1; iValue < 9999; iValue++)
	{
		auto RandValue = Util::Random.Rand(10);
		if (RandValue > 5 || testQueue.size() == 0)
		{
			EXPECT_TRUE(testQueue.Enqueue(iValue));
		}
		else
		{
			int DequeueValue{};
			EXPECT_TRUE(testQueue.Dequeue(DequeueValue));
			EXPECT_TRUE(PrevDequeueValue < DequeueValue);
		}
	}

	while (testQueue.size() > 0)
	{
		int DequeueValue{};
		EXPECT_TRUE(testQueue.Dequeue(DequeueValue));
		EXPECT_TRUE(PrevDequeueValue < DequeueValue);
	}
}

TEST_F(QueueTest, QueueSimple)
{
	Heap testHeap("test", GetSystemHeap());
}


