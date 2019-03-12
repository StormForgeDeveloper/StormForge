////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net test
//	
//
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "Thread/SFThread.h"
#include "Memory/SFMemoryManager.h"
#include "String/SFToString.h"
#include "../SFTestBase.h"


#ifdef DEBUG
#define TestScale 1
#else
#define TestScale 10
#endif



class NetTest : public MyTestBase
{
public:


protected:


public:


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




