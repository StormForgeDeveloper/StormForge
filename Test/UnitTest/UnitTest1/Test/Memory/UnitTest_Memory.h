////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 KyungKun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"
#include "../SFTestBase.h"


// common setting class
class MemoryTest : public MyTestBase
{
protected:

	SF::SpinLock m_LockObject;


public:

	MemoryTest()
	{

	}

    SF::IHeap& GetHeap() { return SF::GetSystemHeap(); }

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		MyTestBase::SetUp();

	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

	}
};

