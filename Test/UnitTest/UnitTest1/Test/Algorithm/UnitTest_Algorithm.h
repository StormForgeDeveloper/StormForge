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
#include "String/SFToString.h"
#include "../SFTestBase.h"


// common setting class
class AlgorithmTest : public MyTestBase
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

	// Heap for test
	SF::Heap m_Heap;

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

	SF::SpinLock m_LockObject;

	unsigned numberOfTest;
	int *TestValues;

public:

	AlgorithmTest()
		: m_Heap("AlgorithmTest", SF::GetSystemHeap())
		, numberOfTest(0)
		, TestValues(nullptr)
	{

	}

	// Heap interface
	SF::IHeap& GetHeap() { return m_Heap; }


	void SetupRandomTestValue()
	{
		numberOfTest = MAX_TEST_VALUE;
		TestValues = new(GetHeap()) int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			TestValues[iTest] = rand() % MAX_TEST_VALUE;
		}
	}

	void SetupReverseSequencialTestValue()
	{
		numberOfTest = MAX_TEST_VALUE;
		TestValues = new(GetHeap()) int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			TestValues[iTest] = MAX_TEST_VALUE - iTest;
		}
	}

	void SetupSequencialTestValue()
	{
		numberOfTest = MAX_TEST_VALUE;
		TestValues = new(GetHeap()) int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			TestValues[iTest] = iTest+1;
		}
	}

	// Stop all thread
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
		MyTestBase::SetUp();
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

		StopAllThread();
		SF::IHeap::Delete(TestValues);
		TestValues = nullptr;
	}
};

