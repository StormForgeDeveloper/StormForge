// UnitTest_Zookeeper.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Util/SFPath.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemory.h"

#include "Task/SFTask.h"
#include "SFEngine.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"

#define THREADED 1
#include "zookeeper.h"
#include "ServerConfig/SFServerConfig.h"
#include "ServerConfig/SFServerConfigJson.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




GTEST_TEST(ServerConfig, LoadTest)
{

	for (int iCount = 0; iCount < 5; iCount++)
	{
		Heap testHeap("test", GetSystemHeap());

		auto dirPath = Util::Path::GetFileDirectory(__FILE__);
		auto filePath = Util::Path::Combine(dirPath, "testConfig.cfg");

		ServerConfigJson loader(testHeap);
		ServerConfig::ServerService config;
		auto result = loader.LoadConfig(filePath, &config);
		EXPECT_EQ(ResultCode::SUCCESS, result);
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}




