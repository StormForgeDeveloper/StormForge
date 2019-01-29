////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 StormForge
// 
// Author : KyungKun Ko
//
// Description : Test base
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Util/SFLog.h"
#include "String/SFStrUtil.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemory.h"
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Math/SF3DMath.h"



using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;






// base test 
class MyTestBase : public testing::Test
{
public:
	
	SF::Heap m_Heap;

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

protected:

public:
	MyTestBase()
		: m_Heap("testHeap", SF::GetSystemHeap())
	{
	}

	virtual ~MyTestBase()
	{
		StopAllThread();
	}

	// Stop all thread
	void StopAllThread()
	{
		std::for_each(m_Threads.begin(), m_Threads.end(), [](SF::Thread* pThread)
		{
			if (pThread) pThread->Stop(true);
			SF::IHeap::Delete(pThread);
		});
		m_Threads.clear();
	}


	SF::IHeap& GetHeap() { return m_Heap; }

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		StopAllThread();
	}
};


// Time based test
class TimedTest : public MyTestBase
{
protected:
	// Expected execution time
	time_t ExpectedTime;

	// The UTC time (in seconds) when the test starts
	time_t start_time_;

public:
	TimedTest()
		:ExpectedTime(30)
	{
	}

	// set expected execution time
	void SetExpectedTime( time_t NewExpectedTime )
	{
		ExpectedTime = NewExpectedTime;
	}

	// Remember that SetUp() is run immediately before a test starts.
	// This is a good place to record the start time.
	virtual void SetUp()
	{
		start_time_ = time(NULL);
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	// check if the test was too slow.
	virtual void TearDown()
	{
		// Gets the time when the test finishes
		const time_t end_time = time(NULL);

		// Asserts that the test took no more than ~5 seconds.  Did you
		// know that you can use assertions in SetUp() and TearDown() as
		// well?
		EXPECT_TRUE(end_time - start_time_ <= ExpectedTime) << "The test took too long.";
	}
};


