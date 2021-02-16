// UnitTest_TexturePng.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemory.h"
#include "Util/SFPath.h"

#include "Task/SFTask.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
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



GTEST_TEST(Asset, ResourceManagerLoadTexture)
{
	Heap testHeap("test", GetSystemHeap());

	auto dirPath = Util::Path::GetFileDirectory(__FILE__);
	auto filePath = Util::Path::Combine(dirPath, "../../data/testImage.jpg");

	// TODO: Enable when asset import is working
	//auto pTask = Service::ResourceManager->LoadAsset(filePath);
	//
	//pTask->Wait();

	//EXPECT_NE(nullptr, pTask->LoadedResource.get());

}
