////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Blue3K
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemory.h"

#include "SFEngine.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Util/SFRandom.h"
#include "Util/SFLog.h"

#include "Container/SFCircularBuffer.h"
#include "Container/SFCircularBufferQueue.h"

#include "UnitTest_CircularBuffer.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;






TEST_F(CircularBufferTest, CircularBufferQueueSimple)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	StaticCircularBufferQueue<TestBufferSize> circularBuffer;
	size_t allocSize = 99;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	auto pBuffer = circularBuffer.AllocateWrite(10 * 1024);
	GTEST_ASSERT_EQ(nullptr, pBuffer);
	EXPECT_NE(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));

	for (int iTry = 0; iTry < 10; iTry++)
	{
		uint8_t fillPattern = 0xC7;
		pBuffer = circularBuffer.AllocateWrite(allocSize);
		GTEST_ASSERT_NE(nullptr, pBuffer);

		memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));

		auto pReadItem = circularBuffer.DequeueRead();
		GTEST_ASSERT_NE(nullptr, pReadItem);

		EXPECT_EQ(StaticCircularBufferQueue<TestBufferSize>::ItemState::Reading, pReadItem->State);
		GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
		GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

		auto pData = (uint8_t*)pReadItem->GetDataPtr();

		EXPECT_GE(circularBuffer.GetBufferItemSize(pReadItem), allocSize);

		EXPECT_EQ(pBuffer->GetDataPtr(), pData);
		for (int iData = 0; iData < allocSize; iData++)
		{
			EXPECT_EQ(fillPattern, pData[iData]);
		}

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseRead(pReadItem));
	}


	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


TEST_F(CircularBufferTest, CircularBufferQueueSimple2)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	StaticCircularBufferQueue<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	size_t allocSize = 10;
	int enqueuedCount = 0;
	for (int iTry = 0; ; iTry++, enqueuedCount++)
	{
		uint8_t fillPattern = iTry + 1;
		auto pBuffer = circularBuffer.AllocateWrite(allocSize);
		if (pBuffer == nullptr)
			break;

		memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));
	}


	for (int iTry = 0; iTry < enqueuedCount; iTry++)
	{
		uint8_t fillPattern = iTry + 1;

		auto pReadItem = circularBuffer.DequeueRead();
		GTEST_ASSERT_NE(nullptr, pReadItem);

		EXPECT_EQ(StaticCircularBufferQueue<TestBufferSize>::ItemState::Reading, pReadItem->State);
		GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
		GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

		EXPECT_GE(circularBuffer.GetBufferItemSize(pReadItem), allocSize);

		auto pData = (uint8_t*)pReadItem->GetDataPtr();
		for (int iData = 0; iData < allocSize; iData++)
		{
			EXPECT_EQ(fillPattern, pData[iData]);
		}

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseRead(pReadItem));
	}

}


TEST_F(CircularBufferTest, CircularBufferQueueFull)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBufferQueue<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		auto opRan = Util::Random.Rand();

		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.AllocateWrite(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount && ((opRan % 100) > 40))
		{
			auto pReadItem = circularBuffer.DequeueRead();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(StaticCircularBufferQueue<TestBufferSize>::ItemState::Reading, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseRead(pReadItem));
			processedCount++;
		}
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



TEST_F(CircularBufferTest, CircularBufferQueueEmpty)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBufferQueue<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		size_t allocSize = 120;// Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.AllocateWrite(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount)
		{
			auto pReadItem = circularBuffer.DequeueRead();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(StaticCircularBufferQueue<TestBufferSize>::ItemState::Reading, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseRead(pReadItem));
			processedCount++;
		}
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


TEST_F(CircularBufferTest, CircularBufferQueueEmptyRand)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBufferQueue<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.AllocateWrite(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount)
		{
			auto pReadItem = circularBuffer.DequeueRead();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(StaticCircularBufferQueue<TestBufferSize>::ItemState::Reading, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseRead(pReadItem));
			processedCount++;
		}
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


template<size_t TestBufferSize>
void Container_CircularBufferQueue_ThreadTest(size_t testDataCount, int allocSizeStart, int allocSizeEnd, int ReadThreadCount, int WriteThreadCount)
{
	using CircularBufferTestT = StaticCircularBufferQueue<TestBufferSize> ;

	Heap testHeap("test", GetSystemHeap());
	CircularBufferTestT circularBuffer;
	size_t TestDataCount = testDataCount;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	std::vector<Thread*> readThreads;
	std::vector<Thread*> writeThreads;


	std::atomic<uint64_t> enqueuedCount = 0;
	std::atomic<uint64_t> processedCount = 0;

	for (int iThread = 0; iThread < WriteThreadCount; iThread++)
	{
		auto pNewThread = new(testHeap) FunctorThread([&circularBuffer, allocSizeStart, allocSizeEnd, &enqueuedCount, TestDataCount](Thread* pThread)
		{
			unused(pThread);
			while (enqueuedCount.load(std::memory_order_relaxed) < TestDataCount)
			{
				size_t allocSize = Util::Random.Rand(allocSizeStart, allocSizeEnd);
				auto pBuffer = circularBuffer.AllocateWrite(allocSize);
				if (pBuffer == nullptr)
				{
					// wait a bit and try again
					ThisThread::SleepFor(DurationMS(0));
					continue;
				}

				auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
				allocSize = newAllocSize;
				uint8_t fillPattern = (uint8_t)allocSize;
				memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

				EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseWrite(pBuffer));

				enqueuedCount.fetch_add(1, std::memory_order_relaxed);
			}
		});

		pNewThread->Start();
		writeThreads.push_back(pNewThread);
	}



	for (int iThread = 0; iThread < ReadThreadCount; iThread++)
	{
		auto pNewThread = new(testHeap) FunctorThread([&circularBuffer, &enqueuedCount, &processedCount, TestDataCount](Thread* pThread)
		{

			while (processedCount.load(std::memory_order_relaxed) < TestDataCount)
			{
				auto pReadItem = circularBuffer.DequeueRead();
				if (pReadItem == nullptr)
				{
					ThisThread::SleepFor(DurationMS(0));
					continue;
				}

				EXPECT_EQ(CircularBufferTestT::ItemState::Reading, pReadItem->State);
				GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
				GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

				size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
				uint8_t fillPattern = (uint8_t)allocSize;

				auto pData = (uint8_t*)pReadItem->GetDataPtr();
				for (int iData = 0; iData < allocSize; iData++)
				{
					EXPECT_EQ(fillPattern, pData[iData]);
				}

				EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.ReleaseRead(pReadItem));

				processedCount.fetch_add(1, std::memory_order_relaxed);
			}

			SFLog(System, Info, "Pull done");
		});
		pNewThread->Start();
		readThreads.push_back(pNewThread);
	}

	while (enqueuedCount.load(std::memory_order_relaxed) < TestDataCount)
	{
		ThisThread::SleepFor(DurationMS(100));
	}

	for (auto itThread : writeThreads)
	{
		itThread->Stop();
		IHeap::Delete(itThread);
	}

	for (auto itThread : readThreads)
	{
		itThread->Stop();
		IHeap::Delete(itThread);
	}

}



TEST_F(CircularBufferTest, CircularBufferQueueThreadR1W1Small)
{
	Container_CircularBufferQueue_ThreadTest<256>(999999, 30, 128, 1, 1);
	
	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


TEST_F(CircularBufferTest, CircularBufferQueueThreadR1W1Large)
{
	Container_CircularBufferQueue_ThreadTest<1024>(999999, 30, 128, 1, 1);

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



TEST_F(CircularBufferTest, CircularBufferQueueThreadMultipleR1W2)
{
	Container_CircularBufferQueue_ThreadTest<1024>(999999, 30, 128, 1, 2);

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



TEST_F(CircularBufferTest, CircularBufferQueueThreadMultipleR1W4)
{
	Container_CircularBufferQueue_ThreadTest<1024>(999999, 30, 128, 1, 4);

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}




















TEST_F(CircularBufferTest, CircularBuffer_Simple)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	StaticCircularBuffer<TestBufferSize> circularBuffer;
	size_t allocSize = 99;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	auto pBuffer = circularBuffer.Allocate(10 * 1024);
	GTEST_ASSERT_EQ(nullptr, pBuffer);
	EXPECT_NE(ResultCode::SUCCESS, circularBuffer.Free(pBuffer));

	for (int iTry = 0; iTry < 10; iTry++)
	{
		uint8_t fillPattern = 0xC7;
		pBuffer = circularBuffer.Allocate(allocSize);
		GTEST_ASSERT_NE(nullptr, pBuffer);

		memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

		EXPECT_GE(circularBuffer.GetBufferItemSize(pBuffer), allocSize);

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pBuffer));
	}
}


TEST_F(CircularBufferTest, CircularBuffer_Simple2)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	StaticCircularBuffer<TestBufferSize> circularBuffer;
	std::vector<CircularBuffer::Item*> testAllocated;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	size_t allocSize = 10;
	int enqueuedCount = 0;
	for (int iTry = 0; ; iTry++, enqueuedCount++)
	{
		uint8_t fillPattern = iTry + 1;
		auto pBuffer = circularBuffer.Allocate(allocSize);
		if (pBuffer == nullptr)
			break;

		memset(pBuffer->GetDataPtr(), fillPattern, allocSize);
		testAllocated.push_back(pBuffer);
	}


	for (int iTry = 0; iTry < enqueuedCount; iTry++)
	{
		uint8_t fillPattern = iTry + 1;
		auto pReadItem = testAllocated[iTry];
		GTEST_ASSERT_NE(nullptr, pReadItem);

		EXPECT_EQ(CircularBuffer::ItemState::Reserved, pReadItem->State);
		GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
		GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

		EXPECT_GE(circularBuffer.GetBufferItemSize(pReadItem), allocSize);

		auto pData = (uint8_t*)pReadItem->GetDataPtr();
		for (int iData = 0; iData < allocSize; iData++)
		{
			EXPECT_EQ(fillPattern, pData[iData]);
		}

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pReadItem));
	}

}


TEST_F(CircularBufferTest, CircularBuffer_Full)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBuffer<TestBufferSize> circularBuffer;
	std::vector< CircularBuffer::Item*> allocated;
	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		auto opRan = Util::Random.Rand();

		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Allocate(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			allocated.push_back(pBuffer);
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount && ((opRan % 100) > 40))
		{
			auto pReadItem = allocated.back();
			allocated.pop_back();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer::ItemState::Reserved, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pReadItem));
			processedCount++;
		}
	}
}



TEST_F(CircularBufferTest, CircularBuffer_RandomFree)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBuffer<TestBufferSize> circularBuffer;
	std::vector< CircularBuffer::Item*> allocated;
	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		auto opRan = Util::Random.Rand();

		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Allocate(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			allocated.push_back(pBuffer);
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount && ((opRan % 100) > 40))
		{
			auto idxRemove = opRan % allocated.size();
			auto pReadItem = allocated[idxRemove];
			allocated.erase(allocated.begin() + idxRemove);
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer::ItemState::Reserved, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pReadItem));
			processedCount++;
		}
	}
}


TEST_F(CircularBufferTest, CircularBuffer_Empty)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBuffer<TestBufferSize> circularBuffer;
	std::vector<CircularBuffer::Item*> allocated;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		size_t allocSize = 120;// Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Allocate(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			allocated.push_back(pBuffer);
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount)
		{
			auto pReadItem = allocated.back();
			allocated.pop_back();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer::ItemState::Reserved, pReadItem->State.load());
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pReadItem));
			processedCount++;
		}
	}

}


TEST_F(CircularBufferTest, CircularBuffer_EmptyRand)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	StaticCircularBuffer<TestBufferSize> circularBuffer;
	std::vector<CircularBuffer::Item*> allocated;
	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Allocate(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

			allocated.push_back(pBuffer);
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount)
		{
			auto pReadItem = allocated.back();
			allocated.pop_back();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer::ItemState::Reserved, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferItemSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pReadItem));
			processedCount++;
		}
	}
}




template<size_t TestBufferSize>
void Container_CircularBuffer_ThreadTest(std::vector<SF::Thread*>& threadArray, size_t testDataCount, int allocSizeStart, int allocSizeEnd, int ThreadCount)
{
	using CircularBufferTestT = StaticCircularBuffer<TestBufferSize>;

	Heap testHeap("test", GetSystemHeap());
	CircularBufferTestT circularBuffer;
	size_t TestDataCount = testDataCount;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	std::atomic<size_t> testedCount = 0;
	std::atomic<size_t> finishedCount = 0;

	for (int iThread = 0; iThread < ThreadCount; iThread++)
	{
		auto pNewThread = new(testHeap) FunctorThread([&circularBuffer, allocSizeStart, allocSizeEnd, &testedCount, &finishedCount, TestDataCount]([[maybe_unused]] Thread* pThread)
		{
			while (testedCount.load(std::memory_order_relaxed) < TestDataCount)
			{
				size_t allocSize = Util::Random.Rand(allocSizeStart, allocSizeEnd);
				auto pBuffer = circularBuffer.Allocate(allocSize);
				if (pBuffer == nullptr)
				{
					// wait a bit and try again
					ThisThread::SleepFor(DurationMS(0));
					continue;
				}

				auto newAllocSize = circularBuffer.GetBufferItemSize(pBuffer);
				allocSize = newAllocSize;

				// Fill pattern
				uint8_t fillPattern = (uint8_t)allocSize;
				memset(pBuffer->GetDataPtr(), fillPattern, allocSize);

				ThisThread::SleepFor(DurationMS(50));

				// check whether it changed during sleep
				auto pData = (uint8_t*)pBuffer->GetDataPtr();
				for (int iData = 0; iData < allocSize; iData++)
				{
					EXPECT_EQ(fillPattern, pData[iData]);
				}

				EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.Free(pBuffer));

				testedCount.fetch_add(1, std::memory_order_relaxed);
			}

			finishedCount.fetch_add(1, std::memory_order_relaxed);
		});

		pNewThread->Start();
		threadArray.push_back(pNewThread);
	}


	while (finishedCount < ThreadCount)
	{
		ThisThread::SleepFor(DurationMS(500));
	}

}



TEST_F(CircularBufferTest, CircularBufferThreadR1W1Small)
{
	Container_CircularBuffer_ThreadTest<256>(m_Threads, m_TestCount, 30, 128, 1);
}


TEST_F(CircularBufferTest, CircularBufferThreadR1W1Large)
{
	Container_CircularBuffer_ThreadTest<1024>(m_Threads, m_TestCount, 30, 128, 1);
}


TEST_F(CircularBufferTest, CircularBufferThreadMultipleR1W2)
{
	Container_CircularBuffer_ThreadTest<1024>(m_Threads, m_TestCount, 30, 128, 1);
}



TEST_F(CircularBufferTest, CircularBufferThreadMultipleR1W4)
{
	Container_CircularBuffer_ThreadTest<1024>(m_Threads, m_TestCount, 30, 128, 1);
}



