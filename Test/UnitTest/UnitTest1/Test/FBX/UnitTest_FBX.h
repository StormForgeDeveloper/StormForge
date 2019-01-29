////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : FBX test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Thread/SFThread.h"
#include "Memory/SFMemoryManager.h"
#include "String/SFToString.h"
#include "Math/SF3DMath.h"
#include "Util/SFRandom.h"
#include "Util/SFTimeUtil.h"
#include "../SFTestBase.h"


// common setting class
class FBXTest : public MyTestBase
{
protected:
	//FbxManager* lSdkManager = NULL;
	//FbxScene* lScene = NULL;
	//bool lResult;

	//// Prepare the FBX SDK.
	//InitializeSdkObjects(lSdkManager, lScene);



public:

	FBXTest()
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

