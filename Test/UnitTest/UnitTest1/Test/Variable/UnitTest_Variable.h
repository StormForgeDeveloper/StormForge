////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : Memory
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Thread/SFThread.h"
#include "Memory/SFMemoryManager.h"
#include "String/SFToString.h"
#include "../SFTestBase.h"
#include "Variable/SFVariable.h"
#include "Variable/SFVariableTable.h"
#include "Variable/SFVariableStack.h"


// common setting class
class VariableTest : public MyTestBase
{
protected:

	SF::SpinLock m_LockObject;


public:

	VariableTest()
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

