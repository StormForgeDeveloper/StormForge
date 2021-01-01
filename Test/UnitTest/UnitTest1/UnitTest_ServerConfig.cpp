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
#include "ServerConfig/SFServerConfigXML.h"
#include "ServerConfig/SFServerConfigZookeeper.h"



using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




GTEST_TEST(ServerConfig, XMLLoad)
{
	Heap testHeap("test", GetSystemHeap());
	ServerConfig serverConfig(testHeap);
	ServerConfigXML serverConfigXML(serverConfig);

	auto dirPath = Util::Path::GetFileDirectory(__FILE__);

	{
		auto filePath = Util::Path::Combine(dirPath, "ServerConfig_StressTest.xml");
		malloc(128);

		GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXML.LoadConfig(filePath));
	}

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(ServerConfig, ZookeeperStore)
{
	Heap testHeap("test", GetSystemHeap());
	Zookeeper zkInstance(testHeap);
	ServerConfig serverConfig(testHeap);
	ServerConfig serverConfigXML(testHeap);
	const char* zkConfigNodeName = "/UnitTest_ServerConfig_ZookeeperStore";
	zkInstance.Connect("SFTestZookeeper.com:41181");
	zkInstance.WaitForConnected();


	ServerConfigXML serverConfigXMLLoader(serverConfigXML);
	auto dirPath = Util::Path::GetFileDirectory(__FILE__);
	auto filePath = Util::Path::Combine(dirPath, "ServerConfig_StressTest.xml");
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXMLLoader.LoadConfig(filePath));

	ServerConfigZookeeper zookeeperStore(serverConfigXML, zkInstance);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zookeeperStore.StoreConfig(zkConfigNodeName));


	zkInstance.Close();
	zkInstance.WaitForDisconnected();

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(ServerConfig, ZookeeperLoad)
{
	Heap testHeap("test", GetSystemHeap());
	Zookeeper zkInstance(testHeap);
	ServerConfig serverConfig(testHeap);
	ServerConfig serverConfigXML(testHeap);
	const char* zkConfigNodeName = "/UnitTest_ServerConfig_ZookeeperStore";
	zkInstance.Connect("SFTestZookeeper.com:41181");
	zkInstance.WaitForConnected();


	ServerConfigXML serverConfigXMLLoader(serverConfigXML);
	auto dirPath = Util::Path::GetFileDirectory(__FILE__);
	auto filePath = Util::Path::Combine(dirPath, "ServerConfig_StressTest.xml");
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXMLLoader.LoadConfig(filePath));

	ServerConfigZookeeper zookeeperLoader(serverConfig, zkInstance);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zookeeperLoader.LoadConfig(zkConfigNodeName));
	GTEST_ASSERT_EQ(serverConfigXML, serverConfig);


	zkInstance.Close();
	zkInstance.WaitForDisconnected();

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}

GTEST_TEST(ServerConfig, Zookeeper)
{
	Heap testHeap("test", GetSystemHeap());
	Zookeeper zkInstance(testHeap);
	ServerConfig serverConfig(testHeap);
	ServerConfig serverConfigXML(testHeap);
	const char* zkConfigNodeName = "/UnitTest_ServerConfig_Zookeeper";
	zkInstance.Connect("SFTestZookeeper.com:41181");
	zkInstance.WaitForConnected();


	ServerConfigXML serverConfigXMLLoader(serverConfigXML);
	auto dirPath = Util::Path::GetFileDirectory(__FILE__);
	auto filePath = Util::Path::Combine(dirPath, "ServerConfig_StressTest.xml");
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXMLLoader.LoadConfig(filePath));

	ServerConfigZookeeper zookeeperStore(serverConfigXML, zkInstance);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zookeeperStore.StoreConfig(zkConfigNodeName));

	ServerConfigZookeeper zookeeperLoad(serverConfig, zkInstance);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zookeeperLoad.LoadConfig(zkConfigNodeName));
	GTEST_ASSERT_EQ(serverConfigXML, serverConfig);


	zkInstance.Close();
	zkInstance.WaitForDisconnected();

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



