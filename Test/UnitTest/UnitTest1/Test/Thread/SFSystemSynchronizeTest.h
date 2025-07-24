////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 The Braves
// 
// Author : KyungKun Ko
//
// Description : System Synchronization test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemory.h"
#include "MemoryManager/SFIMemoryManager.h"
#include "../SFTestBase.h"




class SystemSynchronizationTest : public MyTestBase
{
protected:

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

	SF::SpinLock m_LockObject;

public:

	void StopAllThread()
	{
		std::for_each( m_Threads.begin(), m_Threads.end(), [](SF::Thread* pThread )
		{
			if( pThread ) pThread->Stop( true );
			delete (pThread);
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

	}
};





