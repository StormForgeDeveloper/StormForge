// TestApp.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Util/SFStrUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFStrFormat.h"
#include "Container/SFPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "Container/SFCircularQueue.h"
#include "Multithread/SFThread.h"
#include "Object/SFSharedPointer.h"
#include "Object/SFSharedObjectManager.h"
#include "SFSystemSynchronizeTest.h"

#include "Multithread/SFSystemSynchronization.h"


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







TEST_F(SystemSynchronizationTest, Mutex)
{
	const uint64_t TEST_LENGTH = TestScale * 999999;
	const int64_t NUM_THREAD = 10;

	SyncCounter workerCounter(0);
	std::atomic<int> testData(0);
	std::atomic<int> testIndex(0);
	Mutex dataLock;

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&dataLock, &testData, &testIndex, &workerCounter, worker, TEST_LENGTH](Thread* pThread)
		{
			workerCounter.fetch_add(1, std::memory_order_relaxed);
			for (uint64_t iTest = 0; iTest < TEST_LENGTH; iTest++)
			{
				MutexScopeLock scopeLock(dataLock);
				auto read = testData.load(std::memory_order_acquire);
				testData.store(read + 1, std::memory_order_release);
				auto indexData = testIndex.fetch_add(1, std::memory_order_relaxed);
				AssertRel(indexData == read);
			}

			workerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	ThisThread::SleepFor(DurationMS(10));

	// wait writer threads
	while (workerCounter.load(std::memory_order_relaxed) > 0)
	{
		ThisThread::SleepFor(DurationMS(1000));
	}
}



TEST_F(SystemSynchronizationTest, CriticalSection)
{
	const uint64_t TEST_LENGTH = TestScale * 999999;
	const int64_t NUM_THREAD = 10;

	SyncCounter workerCounter(0);
	std::atomic<int> testData(0);
	std::atomic<int> testIndex(0);
	CriticalSection dataLock;

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&dataLock, &testData, &testIndex, &workerCounter, worker, TEST_LENGTH](Thread* pThread)
		{
			workerCounter.fetch_add(1, std::memory_order_relaxed);
			for (uint64_t iTest = 0; iTest < TEST_LENGTH; iTest++)
			{
				MutexScopeLock scopeLock(dataLock);
				auto read = testData.load(std::memory_order_acquire);
				testData.store(read + 1, std::memory_order_release);
				auto indexData = testIndex.fetch_add(1, std::memory_order_relaxed);
				AssertRel(indexData == read);
			}

			workerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	ThisThread::SleepFor(DurationMS(10));

	// wait writer threads
	while (workerCounter.load(std::memory_order_relaxed) > 0)
	{
		ThisThread::SleepFor(DurationMS(1000));
	}
}

TEST_F(SystemSynchronizationTest, Event)
{
	const uint64_t TEST_LENGTH = TestScale * 999999;
	const int64_t NUM_THREAD = 10;

	SyncCounter workerCounter(0);
	std::atomic<int> testData(0);
	std::atomic<int> testIndex(0);
	Event dataEvent, workDoneEvent;

	dataEvent.Reset();
	workDoneEvent.Reset();

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&dataEvent, &workDoneEvent, &testData, &testIndex, &workerCounter, worker, TEST_LENGTH](Thread* pThread)
		{
			workerCounter.fetch_add(1, std::memory_order_relaxed);
			for (uint64_t iTest = 0; iTest < TEST_LENGTH; iTest++)
			{
				while (!dataEvent.WaitEvent(DurationMS::max()));

				auto read = testData.load(std::memory_order_acquire);
				testData.store(read + 1, std::memory_order_release);
				auto indexData = testIndex.load(std::memory_order_relaxed);
				AssertRel(indexData == read);

				workDoneEvent.Set();
			}

			workerCounter.fetch_sub(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	ThisThread::SleepFor(DurationMS(10));


	for (uint64_t iTest = 0; iTest < (TEST_LENGTH*NUM_THREAD); iTest++)
	{
		dataEvent.Set();
		while (!workDoneEvent.WaitEvent(DurationMS::max()));

		auto read = testData.load(std::memory_order_acquire);
		auto indexData = testIndex.fetch_add(1, std::memory_order_relaxed) + 1;
		AssertRel(indexData == read);
	}


	// wait writer threads
	while (workerCounter.load(std::memory_order_relaxed) > 0)
	{
		ThisThread::SleepFor(DurationMS(1000));
	}
}



