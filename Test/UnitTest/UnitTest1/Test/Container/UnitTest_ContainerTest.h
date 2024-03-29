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



class ContainerTest : public MyTestBase
{
protected:

#ifdef DEBUG
	uint32_t m_TestCount = 1000;
#else
	uint32_t m_TestCount = 999999;
#endif


public:

	ContainerTest()
	{
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
	}

};

