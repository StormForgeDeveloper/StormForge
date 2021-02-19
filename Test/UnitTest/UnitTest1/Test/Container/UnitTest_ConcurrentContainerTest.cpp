// TestApp.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"


#if SF_PLATOFRM == SF_PLATOFRM_WINDOWS

#include <gtest/gtest.h>
#include "Util/SFStrUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFStrFormat.h"
#include "Container/SFSpinBufferMT.h"
#include "Util/SFTimeUtil.h"
#include "Container/SFCircularQueue.h"
#include "Multithread/SFThread.h"
#include "UnitTest_ConcurrentContainerTest.h"



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



namespace BRTest
{

TEST_F(ConcurrentContainerTest, SpinBufferMT_Simple)
{
	const int64_t TEST_LENGTH = 10;
	SpinBufferMT<int64_t, 10> spinBuffer;

	for (int64_t ID = 1; ID < TEST_LENGTH; ID++)
	{
		auto lockedBlock = spinBuffer.Write_Lock();

		lockedBlock->Data = ID;

		spinBuffer.Write_Unlock(lockedBlock);
	};

	int64_t testID = 1;
	for (int64_t ID = 1; ID < TEST_LENGTH; ID++)
	{
		auto block = spinBuffer.Read_Lock([]() { return true; });
		EXPECT_FALSE(block == nullptr);
		if (block == nullptr)
			return;

		EXPECT_EQ(block->Data, testID);
		AssertRel(block->Data == testID);
		spinBuffer.Read_Unlock(block);
		testID++;
	}

}


TEST_F(ConcurrentContainerTest, SpinBufferMT_IN)
{
	const uint64_t TEST_LENGTH = TestScale * 9999;
	const int NUM_THREAD = 10;

	struct TestDataType
	{
		ThreadID TID;
		int WorkerID;
		int Value;
	};

	SpinBufferMT<TestDataType, NUM_THREAD*2> spinBuffer;
	SyncCounter writeWorkerCounter(0);
	SyncCounter readWorkerCounter(0);
	int PreviousData[NUM_THREAD];
	memset(PreviousData, 0, sizeof(PreviousData));

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&writeWorkerCounter, &spinBuffer, worker, TEST_LENGTH](Thread* pThread)
		{
			writeWorkerCounter.fetch_add(1, std::memory_order_relaxed);
			for (int iTest = 0; iTest < TEST_LENGTH; iTest++)
			{
				TestDataType data;
				data.TID = pThread->GetThreadID();
				data.WorkerID = worker;
				data.Value = iTest;
				auto lockedBlock = spinBuffer.Write_Lock();
				lockedBlock->Data = data;
				spinBuffer.Write_Unlock(lockedBlock);
			}

			writeWorkerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}




	for (uint worker = 0; worker < 1; worker++)
	{
		auto pWorker = new FunctorThread([&readWorkerCounter, &spinBuffer, &PreviousData, worker, NUM_THREAD, TEST_LENGTH](Thread* pThread)
		{
			readWorkerCounter.fetch_add(1, std::memory_order_relaxed);
			for (int iTest = 0; iTest < TEST_LENGTH*NUM_THREAD; iTest++)
			{
				auto lockedBlock = spinBuffer.Read_Lock([]() { return true; });
				auto workerID = lockedBlock->Data.WorkerID;
				auto previousValue = PreviousData[workerID];
				EXPECT_EQ(previousValue, lockedBlock->Data.Value);
				AssertRel(lockedBlock->Data.Value == previousValue);
				PreviousData[workerID]++;
				spinBuffer.Read_Unlock(lockedBlock);

			}

			readWorkerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	// wait writer threads
	while (writeWorkerCounter.load(std::memory_order_relaxed) > 0
		|| readWorkerCounter.load(std::memory_order_relaxed) > 0)
	{
		ThisThread::SleepFor(DurationMS(1000));
	}

	for (int item = 0; item < NUM_THREAD; item++)
	{
		EXPECT_EQ(TEST_LENGTH, PreviousData[item]);
		AssertRel(TEST_LENGTH == PreviousData[item]);
	}
}


TEST_F(ConcurrentContainerTest, SpinBufferMT_INOUT)
{
	const uint64_t TEST_LENGTH = TestScale * 9999;
	const int64_t NUM_THREAD = 10;
	const int64_t NUM_READ_THREAD = 5;

	struct TestDataType
	{
		ThreadID TID;
		int WorkerID;
		int Value;
	};

	SpinBufferMT<TestDataType, NUM_THREAD * 2> spinBuffer;
	SyncCounter writeWorkerCounter(0);
	SyncCounter readWorkerCounter(0);
	std::atomic<int> PreviousData[NUM_THREAD];
	for (int iData = 0; iData < NUM_THREAD; iData++)
		PreviousData[iData] = 0;

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&writeWorkerCounter, &spinBuffer, worker, TEST_LENGTH](Thread* pThread)
		{
			writeWorkerCounter.fetch_add(1, std::memory_order_relaxed);
			for (int iTest = 0; iTest < TEST_LENGTH; iTest++)
			{
				TestDataType data;
				data.TID = pThread->GetThreadID();
				data.WorkerID = worker;
				data.Value = iTest;
				auto lockedBlock = spinBuffer.Write_Lock();
				lockedBlock->Data = data;
				spinBuffer.Write_Unlock(lockedBlock);
			}

			writeWorkerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}


	for (uint worker = 0; worker < NUM_READ_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&readWorkerCounter, &spinBuffer, &PreviousData, worker, NUM_THREAD, NUM_READ_THREAD, TEST_LENGTH](Thread* pThread)
		{
			readWorkerCounter.fetch_add(1, std::memory_order_relaxed);
			for (int iTest = 0; iTest < ((TEST_LENGTH*NUM_THREAD) / NUM_READ_THREAD); iTest++)
			{
				auto lockedBlock = spinBuffer.Read_Lock([]() { return true; });
				auto workerID = lockedBlock->Data.WorkerID;
				PreviousData[workerID]++;
				spinBuffer.Read_Unlock(lockedBlock);

			}

			readWorkerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	// wait writer threads
	while (writeWorkerCounter.load(std::memory_order_relaxed) > 0
		|| readWorkerCounter.load(std::memory_order_relaxed) > 0)
	{
		ThisThread::SleepFor(DurationMS(1000));
	}

	for (int item = 0; item < NUM_THREAD; item++)
	{
		EXPECT_EQ(TEST_LENGTH, PreviousData[item]);
		AssertRel(TEST_LENGTH == PreviousData[item]);
	}
}



}  // namespace BRTest


#else
void ConcurrentContaqinerTest_Dummy()
{}
#endif
