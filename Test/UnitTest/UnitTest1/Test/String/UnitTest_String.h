////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 StormForge
// 
// Author : KyungKun Ko
//
// Description : String test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"
#include "../SFTestBase.h"


// String test class
class StringTest : public MyTestBase
{
protected:


public:

	StringTest()
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

