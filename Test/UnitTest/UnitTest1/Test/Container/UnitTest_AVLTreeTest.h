////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : AVL tree test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "../SFTestBase.h"
#include <random>
#include <algorithm>


class AVLTreeTest : public MyTestBase
{
protected:

#ifdef DEBUG
	const int MAX_TEST_VALUE = 100;
#else
	const int MAX_TEST_VALUE = 1100000;
#endif
#ifdef DEBUG
	const unsigned offset = 1;
#else
	const unsigned offset = 601;
#endif

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

	SF::SpinLock m_LockObject;

	unsigned numberOfTest;
	std::vector<int> TestValues;

public:

	AVLTreeTest()
		: numberOfTest(0)
	{

	}

	void StopAllThread()
	{
		std::for_each( m_Threads.begin(), m_Threads.end(), []( SF::Thread* pThread )
		{
			if( pThread ) pThread->Stop( true );
			delete (pThread);
		});
		m_Threads.clear();
	}

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		numberOfTest = MAX_TEST_VALUE;
		TestValues.reserve(MAX_TEST_VALUE);
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			TestValues.push_back(iTest);
		}

		std::shuffle(TestValues.begin(), TestValues.end(), std::default_random_engine(1));

		MyTestBase::SetUp();
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

		StopAllThread();
	}
};

