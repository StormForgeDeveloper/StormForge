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
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemory.h"

#include "SFEngine.h"

#include "String/SFFixedString32.h"
#include "String/SFString.h"
#include "Util/SFRandom.h"
#include "Util/SFLog.h"

#include "Container/SFCircularBuffer.h"



using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;






GTEST_TEST(Container, CircularBufferSimple)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	CircularBuffer<TestBufferSize> circularBuffer;
	size_t allocSize = 99;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	auto pBuffer = circularBuffer.Reserve(10 * 1024);
	GTEST_ASSERT_EQ(nullptr, pBuffer);

	for (int iTry = 0; iTry < 10; iTry++)
	{
		uint8_t fillPattern = 0xC7;
		pBuffer = circularBuffer.Reserve(allocSize);
		GTEST_ASSERT_NE(nullptr, pBuffer);

		memset(pBuffer, fillPattern, allocSize);

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.SetReadyForRead(pBuffer));

		auto pReadItem = circularBuffer.TakeBufferForRead();
		GTEST_ASSERT_NE(nullptr, pReadItem);

		EXPECT_EQ(CircularBuffer<TestBufferSize>::ItemState::Reading, pReadItem->State);
		GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
		GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

		auto pData = (uint8_t*)pReadItem->GetDataPtr();

		EXPECT_GE(circularBuffer.GetBufferSize(pReadItem), allocSize);

		EXPECT_EQ(pBuffer, pData);
		for (int iData = 0; iData < allocSize; iData++)
		{
			EXPECT_EQ(fillPattern, pData[iData]);
		}

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.FreeReadBuffer(pReadItem));
	}


	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(Container, CircularBufferSimple2)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	CircularBuffer<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());

	size_t allocSize = 10;
	int enqueuedCount = 0;
	for (int iTry = 0; ; iTry++, enqueuedCount++)
	{
		uint8_t fillPattern = iTry + 1;
		auto pBuffer = circularBuffer.Reserve(allocSize);
		if (pBuffer == nullptr)
			break;

		memset(pBuffer, fillPattern, allocSize);

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.SetReadyForRead(pBuffer));
	}


	for (int iTry = 0; iTry < enqueuedCount; iTry++)
	{
		uint8_t fillPattern = iTry + 1;

		auto pReadItem = circularBuffer.TakeBufferForRead();
		GTEST_ASSERT_NE(nullptr, pReadItem);

		EXPECT_EQ(CircularBuffer<TestBufferSize>::ItemState::Reading, pReadItem->State);
		GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
		GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

		EXPECT_GE(circularBuffer.GetBufferSize(pReadItem), allocSize);

		auto pData = (uint8_t*)pReadItem->GetDataPtr();
		for (int iData = 0; iData < allocSize; iData++)
		{
			EXPECT_EQ(fillPattern, pData[iData]);
		}

		EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.FreeReadBuffer(pReadItem));
	}


	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(Container, CircularBufferFull)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	CircularBuffer<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		auto opRan = Util::Random.Rand();

		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Reserve(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferSize((CircularBuffer<TestBufferSize>::BufferItem*)((intptr_t)pBuffer - sizeof(CircularBuffer<TestBufferSize>::BufferItem)));
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer, fillPattern, allocSize);

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.SetReadyForRead(pBuffer));
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount && ((opRan % 100) > 40))
		{
			auto pReadItem = circularBuffer.TakeBufferForRead();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer<TestBufferSize>::ItemState::Reading, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.FreeReadBuffer(pReadItem));
			processedCount++;
		}
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



GTEST_TEST(Container, CircularBufferEmpty)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	CircularBuffer<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		size_t allocSize = 120;// Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Reserve(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferSize((CircularBuffer<TestBufferSize>::BufferItem*)((intptr_t)pBuffer - sizeof(CircularBuffer<TestBufferSize>::BufferItem)));
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer, fillPattern, allocSize);

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.SetReadyForRead(pBuffer));
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount)
		{
			auto pReadItem = circularBuffer.TakeBufferForRead();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer<TestBufferSize>::ItemState::Reading, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.FreeReadBuffer(pReadItem));
			processedCount++;
		}
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(Container, CircularBufferEmptyRand)
{
	Heap testHeap("test", GetSystemHeap());
	constexpr size_t TestBufferSize = 256;
	constexpr size_t TestDataCount = 1000000;
	CircularBuffer<TestBufferSize> circularBuffer;

	EXPECT_TRUE(circularBuffer.IsEmpty());


	int enqueuedCount = 0, processedCount = 0;
	for (int iTest = 0; iTest < TestDataCount; iTest++)
	{
		size_t allocSize = Util::Random.Rand(20, 128);
		auto pBuffer = circularBuffer.Reserve(allocSize);
		if (pBuffer != nullptr)
		{
			allocSize = AlignUp(allocSize, 8);
			auto newAllocSize = circularBuffer.GetBufferSize((CircularBuffer<TestBufferSize>::BufferItem*)((intptr_t)pBuffer - sizeof(CircularBuffer<TestBufferSize>::BufferItem)));
			EXPECT_EQ(allocSize, newAllocSize);
			uint8_t fillPattern = (uint8_t)allocSize;
			memset(pBuffer, fillPattern, allocSize);

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.SetReadyForRead(pBuffer));
			enqueuedCount++;
		}

		if (enqueuedCount > processedCount)
		{
			auto pReadItem = circularBuffer.TakeBufferForRead();
			GTEST_ASSERT_NE(nullptr, pReadItem);

			EXPECT_EQ(CircularBuffer<TestBufferSize>::ItemState::Reading, pReadItem->State);
			GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
			GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

			size_t allocSize = circularBuffer.GetBufferSize(pReadItem);
			uint8_t fillPattern = (uint8_t)allocSize;

			auto pData = (uint8_t*)pReadItem->GetDataPtr();
			for (int iData = 0; iData < allocSize; iData++)
			{
				EXPECT_EQ(fillPattern, pData[iData]);
			}

			EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.FreeReadBuffer(pReadItem));
			processedCount++;
		}
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


template<size_t TestBufferSize>
void Container_CircularBuffer_ThreadTest(size_t testDataCount, int allocSizeStart, int allocSizeEnd, int ReadThreadCount, int WriteThreadCount)
{
	typedef CircularBuffer<TestBufferSize> CircularBufferTestT;

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
				auto pBuffer = circularBuffer.Reserve(allocSize);
				if (pBuffer == nullptr)
				{
					// wait a bit and try again
					Sleep(0);
					continue;
				}

				auto newAllocSize = circularBuffer.GetBufferSize((CircularBufferTestT::BufferItem*)((intptr_t)pBuffer - sizeof(CircularBufferTestT::BufferItem)));
				allocSize = newAllocSize;
				uint8_t fillPattern = (uint8_t)allocSize;
				memset(pBuffer, fillPattern, allocSize);

				EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.SetReadyForRead(pBuffer));

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
				auto pReadItem = circularBuffer.TakeBufferForRead();
				if (pReadItem == nullptr)
				{
					Sleep(0);
					continue;
				}

				EXPECT_EQ(CircularBufferTestT::ItemState::Reading, pReadItem->State);
				GTEST_ASSERT_GE(pReadItem->NextPos, (uint32_t)0);
				GTEST_ASSERT_LT(pReadItem->NextPos, TestBufferSize);

				size_t allocSize = circularBuffer.GetBufferSize(pReadItem);
				uint8_t fillPattern = (uint8_t)allocSize;

				auto pData = (uint8_t*)pReadItem->GetDataPtr();
				for (int iData = 0; iData < allocSize; iData++)
				{
					EXPECT_EQ(fillPattern, pData[iData]);
				}

				EXPECT_EQ(ResultCode::SUCCESS, circularBuffer.FreeReadBuffer(pReadItem));

				processedCount.fetch_add(1, std::memory_order_relaxed);
			}

			SFLog(System, Info, "Pull done");
		});
		pNewThread->Start();
		readThreads.push_back(pNewThread);
	}

	while (enqueuedCount.load(std::memory_order_relaxed) < TestDataCount)
	{
		Sleep(100);
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



GTEST_TEST(Container, CircularBufferThreadR1W1Small)
{
	Container_CircularBuffer_ThreadTest<256>(999999, 30, 128, 1, 1);
	
	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(Container, CircularBufferThreadR1W1Large)
{
	Container_CircularBuffer_ThreadTest<1024>(999999, 30, 128, 1, 1);

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



GTEST_TEST(Container, CircularBufferThreadMultipleR1W2)
{
	Container_CircularBuffer_ThreadTest<1024>(999999, 30, 128, 1, 2);

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



GTEST_TEST(Container, CircularBufferThreadMultipleR1W4)
{
	Container_CircularBuffer_ThreadTest<1024>(999999, 30, 128, 1, 4);

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}




