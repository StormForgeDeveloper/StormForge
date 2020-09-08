// UnitTest_TexturePng.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemory.h"

#include "Task/SFTask.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"


#include "Service/SFEngineService.h"
#include "IO/SFFileInputStream.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


const uint TestScale = 5;
const uint TEST_COUNT = 4000000 * TestScale;



GTEST_TEST(Asset, ResourceManagerLoadTexture)
{
	Heap testHeap("test", GetSystemHeap());

	auto pTask = Service::ResourceManager->LoadAsset("data/testImage.jpg");
	
	pTask->Wait();

	EXPECT_NE(nullptr, *pTask->LoadedResource);

}
