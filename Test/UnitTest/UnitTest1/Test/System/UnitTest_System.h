////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : UnitTest System
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"
#include "Math/SF3DMath.h"
#include "Util/SFRandom.h"
#include "Util/SFTimeUtil.h"
#include "../SFTestBase.h"


// common setting class
class SystemTest : public MyTestBase
{
protected:


public:

	SystemTest()
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

