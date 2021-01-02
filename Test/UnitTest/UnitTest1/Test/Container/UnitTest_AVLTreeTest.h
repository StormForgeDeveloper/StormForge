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
#include "Thread/SFThread.h"
#include "Memory/SFMemoryManager.h"
#include "../SFTestBase.h"



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
	int *TestValues;

public:

	AVLTreeTest()
		: numberOfTest(0)
		, TestValues(nullptr)
	{

	}

	void StopAllThread()
	{
		std::for_each( m_Threads.begin(), m_Threads.end(), []( SF::Thread* pThread )
		{
			if( pThread ) pThread->Stop( true );
			SF::IHeap::Delete(pThread);
		});
		m_Threads.clear();
	}

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		numberOfTest = MAX_TEST_VALUE;
		TestValues = new int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			TestValues[iTest] = rand() % MAX_TEST_VALUE;
		}

		MyTestBase::SetUp();
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

		StopAllThread();
		delete[] TestValues;
		TestValues = nullptr;
	}
};

