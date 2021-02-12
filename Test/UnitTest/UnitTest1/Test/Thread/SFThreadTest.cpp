// TestApp.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "String/SFStrUtil.h"
#include "Util/SFRandom.h"
#include "String/SFStrFormat.h"
#include "Container/SFPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "Container/SFCircularQueue.h"
#include "Thread/SFThread.h"
#include "Object/SFSharedPointer.h"
#include "Object/SFSharedObjectManager.h"
#include "SFThreadTest.h"

#include "Task/SFTask.h"



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


class WorkingEntity : public SharedObject
{
private:
	uint m_WorkerThreadID;
	uint m_EntityID;


public:
	struct TestData {
		CounterType Item;
	};
	TestData *pItem;

	uint TestID;

	WorkingEntity(uint entityID)
		: m_WorkerThreadID(0)
		, m_EntityID(entityID)
	{
		pItem = new TestData;
		pItem->Item = 1;
	}

	inline uint GetWorkerThreadID()                   { return m_WorkerThreadID; }

	Result AssignWorkerThreadID(uint workerThreadID)
	{
		if (m_WorkerThreadID != 0)
			return ResultCode::UNEXPECTED;

		m_WorkerThreadID = workerThreadID;

		return ResultCode::SUCCESS;
	}

	virtual void Dispose() override
	{
		delete pItem;
		pItem = nullptr;
	}
};



class TaskWorkerThread : public Thread
{
private:

	// Task worker minimum interval
	DurationMS m_TaskWorkerInterval;

	// Task queue
	PageQueue<WeakPointerT<WorkingEntity>> m_WorkItemQueue;

public:
	static SyncCounter WorkedItems;
	static SyncCounter SkippedWorkedItems;

	TaskWorkerThread(IHeap& heap)
		: Thread("TaskWorkerThread")
		, m_TaskWorkerInterval(DurationMS(1))
		, m_WorkItemQueue(heap)
	{
	}

	~TaskWorkerThread()
	{
	}

	Result PushTask(WeakPointerT<WorkingEntity> taskItem)
	{
		if (taskItem == nullptr)
			return ResultCode::INVALID_ARG;

		return m_WorkItemQueue.Enqueue(taskItem);
	}

	CounterType GetQueuenWorkCount()
	{
		return m_WorkItemQueue.GetEnqueCount();
	}

	SyncCounter PrintCount;

	virtual void Run() override
	{
		PrintCount = 0;

		while (true)
		{
			auto loopInterval = UpdateInterval(m_TaskWorkerInterval);

			if (CheckKillEvent(loopInterval))
			{
				// Kill Event signaled
				break;
			}

			WeakPointerT<WorkingEntity> workItem;
			while ((m_WorkItemQueue.Dequeue(workItem)))
			{
				SharedPointerT<WorkingEntity> workObj;
				workObj = workItem.AsSharedPtr();


				// If disposed skip item
				if (workObj == nullptr)
				{
					SkippedWorkedItems.fetch_add(1,std::memory_order_relaxed);
					continue;
				}

				// Do some works
				workObj->pItem->Item = workObj->GetReferenceCount();
				// let other threads do some job
				const int RandMax = 1000;
				auto randVal = Util::Random.Rand(RandMax);
				if (randVal > ((RandMax * 2) / 3))
				{
					ThisThread::SleepFor(DurationMS(0));
				}
				else
				{
					auto randVal2 = Util::Max(randVal, (unsigned)50);
					for (unsigned int iRand = 0; iRand < randVal; iRand++)
					{
						randVal2 += Util::Random.Rand(100);
					}

					if (((PrintCount.fetch_add(1, std::memory_order_relaxed) + 1) % 10000) == 0)
					{
						printf("Processing %d", randVal2);
					}
				}
				workObj->pItem->Item = workObj->GetReferenceCount();

				WorkedItems.fetch_add(1, std::memory_order_relaxed);
			}
		}
	}

};

SyncCounter TaskWorkerThread::WorkedItems(0);
SyncCounter TaskWorkerThread::SkippedWorkedItems(0);


class EntityTaskManager
{
private:

	uint m_NumberOfWorker;
	uint m_NumberOfTestEntity;

	uint m_LatestAssignedWorkerID;

	std::vector<TaskWorkerThread*> m_Workers;

	SharedObjectManager m_ReferenceManager;
	std::unordered_map<uint, SharedPointerT<WorkingEntity>> m_EntityManager;

	IHeap& m_Heap;

public:

	EntityTaskManager(IHeap& heap)
		: m_NumberOfWorker(5)
		, m_NumberOfTestEntity(100)
		, m_LatestAssignedWorkerID(0)
		, m_ReferenceManager(heap)
		, m_Heap(heap)
	{

	}

	~EntityTaskManager()
	{

	}

	IHeap& GetHeap() { return m_Heap; }

	Result InitializeTaskManager()
	{
		for (uint worker = 0; worker < m_NumberOfWorker; worker++)
		{
			auto pWorker = new TaskWorkerThread(m_Heap);

			m_Workers.push_back(pWorker);

			pWorker->Start();
		}

		// setup test entities
		for (uint entity = 0; entity < m_NumberOfTestEntity; entity++)
		{
			uint entityID = entity + 1;
			auto entityPtr = new(GetHeap()) WorkingEntity(entityID);
			m_ReferenceManager.RegisterSharedObject(entityPtr);
			m_EntityManager.insert(std::make_pair(entityID, entityPtr));
		}

		return ResultCode::SUCCESS;
	}

	void TerminateTaskManager()
	{
		std::for_each(m_Workers.begin(), m_Workers.end(), [](TaskWorkerThread* pWorker)
		{
			pWorker->Stop(true);

			IHeap::Delete(pWorker);
		});

		m_Workers.clear();
	}

	// Enqueue event
	Result TestEnqueueEvent()
	{
		auto entityID = Util::Random.Rand(m_NumberOfTestEntity);
		auto itEntity = m_EntityManager.find(entityID);
		uint workID = 0;
		SharedPointerT<WorkingEntity> entity;
		if (itEntity == m_EntityManager.end())
		{
			auto newObject = new(GetHeap()) WorkingEntity(entityID);
			newObject->TestID = entityID;
			m_ReferenceManager.RegisterSharedObject(newObject);

			entity = SharedPointerT<WorkingEntity>(newObject);
			m_EntityManager.insert(std::make_pair(entityID, entity));
		}
		else
		{
			entity = itEntity->second;
		}

		auto isDelete = Util::Random.Rand(100) > 70;
		if (entity->GetWorkerThreadID() == 0)
		{
			// round robin
			m_LatestAssignedWorkerID = (m_LatestAssignedWorkerID + 1) % m_Workers.size();
			entity->AssignWorkerThreadID(m_LatestAssignedWorkerID);
		}

		workID = entity->GetWorkerThreadID();

		WeakPointerT<WorkingEntity> weakPointer;
		weakPointer = entity;

		m_Workers[workID]->PushTask(weakPointer);

		if (isDelete && itEntity != m_EntityManager.end())
		{
			m_EntityManager.erase(itEntity);
		}
		else
		{
			while (m_Workers[workID]->GetQueuenWorkCount() > 100)
			{
				ThisThread::SleepFor(DurationMS(10));
			}
		}

		return ResultCode::SUCCESS;
	}

	void Update()
	{
		m_ReferenceManager.Update();
	}

};


EntityTaskManager* entityManager = nullptr;
TEST_F(ThreadTest, EntityTaskManager)
{
	//const int64_t TEST_LENGTH = 999999;
	const int64_t TEST_LENGTH = TestScale * 9999999;

	entityManager = new EntityTaskManager(GetHeap());
	entityManager->InitializeTaskManager();

	for (int64_t ID = 0; ID < TEST_LENGTH; ID++)
	{
		entityManager->TestEnqueueEvent();
		entityManager->Update();
	};

	while ((TaskWorkerThread::WorkedItems + TaskWorkerThread::SkippedWorkedItems) < TEST_LENGTH)
	{
		ThisThread::SleepFor(DurationMS(1000));
		entityManager->Update();
	}

	entityManager->Update();
	entityManager->TerminateTaskManager();
}


TEST_F(ThreadTest, PagedQueue)
{
	const int64_t TEST_LENGTH = TestScale * 514;

	PageQueue<int64_t> queue(GetHeap());

	for (int64_t ID = 1; ID < TEST_LENGTH; ID++)
	{
		queue.Enqueue(ID);
	};

	int64_t testID = 1;
	int64_t item;
	while ((queue.Dequeue(item)) )
	{
		EXPECT_EQ(item, testID);
		Assert(item == testID);
		testID++;
	}

}


TEST_F(ThreadTest, PagedQueueThreadEnqueue)
{
	const uint64_t TEST_LENGTH = TestScale * 9999999;
	const int NUM_THREAD = 10;

	PageQueue<int64_t> queue(GetHeap(), 128);
	SyncCounter itemCounter;
	CounterType *testArray = new CounterType[TEST_LENGTH];
	memset(testArray, 0, sizeof(CounterType)*TEST_LENGTH);

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&](Thread* pThread)
		{
			do
			{
				auto count = itemCounter.fetch_add(1, std::memory_order_relaxed)+1;
				if (count <= TEST_LENGTH)
					queue.Enqueue(count);
			} while (itemCounter < TEST_LENGTH);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	std::for_each(m_Threads.begin(), m_Threads.end(), [](Thread* pThread)
	{
		if (pThread) pThread->Stop(false);
		IHeap::Delete(pThread);
	});
	m_Threads.clear();


	int64_t item;
	while ((queue.Dequeue(item)))
	{
		AssertRel(testArray[item-1] == 0);
		testArray[item-1] = 1;
	}

	for (uint item = 0; item < TEST_LENGTH; item++)
	{
		EXPECT_EQ(1, testArray[item]);
		AssertRel(testArray[item] == 1);
	}

	delete[] testArray;
}


TEST_F(ThreadTest, PagedQueueThreadEnqueueDequeue)
{
	const uint64_t TEST_LENGTH = TestScale * 999999;
	const int NUM_THREAD = 20;

	PageQueue<int64_t> queue(GetHeap(), 4);
	SyncCounter itemCounter;
	SyncCounter workDone;
	CounterType *testArray = new CounterType[TEST_LENGTH];
	memset(testArray, 0, sizeof(CounterType)*TEST_LENGTH);

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&](Thread* pThread)
		{
			do
			{
				auto count = itemCounter.fetch_add(1, std::memory_order_relaxed) + 1;
				if (count <= TEST_LENGTH)
					queue.Enqueue(count);
			} while (itemCounter < TEST_LENGTH);

			workDone.fetch_add(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}



	int64_t item;
	uint64_t readCount = 0;
	while (readCount < TEST_LENGTH || workDone.load(std::memory_order_relaxed) < NUM_THREAD)
	{
		if ((queue.Dequeue(item)))
		{
			item--;
			AssertRel(testArray[item] == 0);
			testArray[item] = 1;
			readCount++;
		}
	}


	std::for_each(m_Threads.begin(), m_Threads.end(), [](Thread* pThread)
	{
		if (pThread) pThread->Stop(false);
		IHeap::Delete(pThread);
	});
	m_Threads.clear();


	for (uint item = 0; item < TEST_LENGTH; item++)
	{
		EXPECT_EQ(1, testArray[item]);
		AssertRel(testArray[item] == 1);
	}

	delete[] testArray;
}

TEST_F(ThreadTest, PagedQueueThreadEnqueueThreadDequeue)
{
	const uint64_t TEST_LENGTH = TestScale * 99999;
	const int NUM_THREAD = 20;

	PageQueue<int64_t> queue(GetHeap(), 4);
	SyncCounter itemCounter;
	SyncCounter workDone;
	SyncCounter *testArray = new SyncCounter[TEST_LENGTH];
	memset(testArray, 0, sizeof(SyncCounter)*TEST_LENGTH);

	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&](Thread* pThread)
		{
			do
			{
				auto count = itemCounter.fetch_add(1, std::memory_order_relaxed) + 1;
				if (count <= TEST_LENGTH)
					queue.Enqueue(count);
			} while (itemCounter < TEST_LENGTH);

			workDone.fetch_add(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}

	SyncCounter readCount(0);
	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&](Thread* pThread)
		{
			int64_t item;
			auto readOrder = readCount.fetch_add(1,std::memory_order_relaxed);
			while (readOrder < TEST_LENGTH)
			{
				if ((queue.DequeueMT(item)))
				{
					item--;
					CounterType expected = 0;
					while (!testArray[item].compare_exchange_weak(expected, 1, std::memory_order_relaxed, std::memory_order_relaxed))
					{
						AssertRel(expected == 0);
						expected = 0;
					}
				}
				readOrder = readCount.fetch_add(1, std::memory_order_relaxed);
			}

			workDone.fetch_add(1, std::memory_order_relaxed);
		});

		pWorker->Start();
		m_Threads.push_back(pWorker);
	}


	std::for_each(m_Threads.begin(), m_Threads.end(), [](Thread* pThread)
	{
		if (pThread) pThread->Stop(false);
		IHeap::Delete(pThread);
	});
	m_Threads.clear();


	for (uint item = 0; item < TEST_LENGTH; item++)
	{
		EXPECT_EQ(1, testArray[item]);
		AssertRel(testArray[item] == 1);
	}

	delete[] testArray;
}


TEST_F(ThreadTest, PagedQueue_PerformanceCompare_PageQueue)
{
	const uint64_t TEST_LENGTH = TestScale * 999999;
	const int NUM_THREAD = 10;

	std::vector<Thread*> threads;
	PageQueue<int64_t> queue(GetHeap(), 1024);
	SyncCounter itemCounter;
	SyncCounter workDone;
	CounterType *testArray = new CounterType[TEST_LENGTH];
	memset(testArray, 0, sizeof(CounterType)*TEST_LENGTH);


	auto start = Util::Time.GetRawTimeMs();


	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&](Thread* pThread)
		{
			do
			{
				auto count = itemCounter.fetch_add(1, std::memory_order_relaxed) + 1;
				if (count <= TEST_LENGTH)
					AssertRel((queue.Enqueue(count)));
			} while (itemCounter < TEST_LENGTH);

			workDone.fetch_add(1);
		});

		pWorker->Start();
		threads.push_back(pWorker);
	}


	int64_t item;
	uint64_t readCount = 0;
	while (readCount < TEST_LENGTH || workDone.load(std::memory_order_relaxed) < NUM_THREAD)
	{
		if ((queue.Dequeue(item)))
		{
			item--;
			AssertRel(testArray[item] == 0);
			testArray[item] = 1;
			readCount++;
		}
	}

	std::for_each(threads.begin(), threads.end(), [](Thread* pThread)
	{
		if (pThread) pThread->Stop(false);
		IHeap::Delete(pThread);
	});
	threads.clear();

	auto end = Util::Time.GetRawTimeMs();
	printf("PageQueue Execution Time:      %15d\n", (end - start).count());

	delete[] testArray;
}

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
TEST_F(ThreadTest, PagedQueue_PerformanceCompare_Concurrent)
{
	const uint64_t TEST_LENGTH = TestScale * 999999;
	const int NUM_THREAD = 10;

	std::vector<Thread*> threads;
	Concurrency::concurrent_queue<int64_t> queue;
	SyncCounter itemCounter;
	SyncCounter workDone;
	CounterType *testArray = new CounterType[TEST_LENGTH];
	memset(testArray, 0, sizeof(CounterType)*TEST_LENGTH);


	auto start = Util::Time.GetRawTimeMs();


	for (uint worker = 0; worker < NUM_THREAD; worker++)
	{
		auto pWorker = new FunctorThread([&](Thread* pThread)
		{
			do
			{
				auto count = itemCounter.fetch_add(1, std::memory_order_relaxed) + 1;
				if (count <= TEST_LENGTH)
					queue.push(count);
			} while (itemCounter < TEST_LENGTH);

			workDone.fetch_add(1);
		});

		pWorker->Start();
		threads.push_back(pWorker);
	}


	int64_t item;
	uint64_t readCount = 0;
	while (readCount < TEST_LENGTH || workDone.load(std::memory_order_relaxed) < NUM_THREAD)
	{
		if (queue.try_pop(item))
		{
			item--;
			AssertRel(testArray[item] == 0);
			testArray[item] = 1;
			readCount++;
		}
	}

	std::for_each(threads.begin(), threads.end(), [](Thread* pThread)
	{
		if (pThread) pThread->Stop(false);
		IHeap::Delete(pThread);
	});
	threads.clear();

	auto end = Util::Time.GetRawTimeMs();
	printf("concurrent_queue Execution Time: %15d\n", (end - start).count());

	IHeap::Delete(testArray);
}
#endif





