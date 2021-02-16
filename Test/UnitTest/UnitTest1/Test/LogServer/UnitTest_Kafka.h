////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 StormForge
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
#include "Util/SFToString.h"
#include "../SFTestBase.h"


// common setting class
class KafkaTest : public MyTestBase
{
protected:

#ifdef DEBUG
	const int MAX_TEST_VALUE = 100;
#else
	const int MAX_TEST_VALUE = 1100000;
#endif

	// Heap for test
	SF::Heap m_Heap;

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

	SF::SpinLock m_LockObject;

	unsigned m_NumberOfTest;
	int *m_TestValues;
	
	const char* m_StreamServerAddress[2] = 
		// copy serveraddress_sample.txt to serveraddress.txt and edit to your server address
		#include "LocalData/serveraddress.txt"
	;

public:

	KafkaTest()
		: m_Heap("KafkaTest", SF::GetSystemHeap())
		, m_NumberOfTest(0)
		, m_TestValues(nullptr)
	{

	}

	// Heap interface
	SF::IHeap& GetHeap() { return m_Heap; }


	void SetupRandomTestValue()
	{
		m_NumberOfTest = MAX_TEST_VALUE;
		m_TestValues = new(GetHeap()) int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			m_TestValues[iTest] = rand() % MAX_TEST_VALUE;
		}
	}

	void SetupReverseSequencialTestValue()
	{
		m_NumberOfTest = MAX_TEST_VALUE;
		m_TestValues = new(GetHeap()) int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			m_TestValues[iTest] = MAX_TEST_VALUE - iTest;
		}
	}

	void SetupSequencialTestValue()
	{
		m_NumberOfTest = MAX_TEST_VALUE;
		m_TestValues = new(GetHeap()) int[MAX_TEST_VALUE];
		for (int iTest = 0; iTest < MAX_TEST_VALUE; iTest++)
		{
			m_TestValues[iTest] = iTest+1;
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
		SF::IHeap::Delete(m_TestValues);
		m_TestValues = nullptr;
	}
};

