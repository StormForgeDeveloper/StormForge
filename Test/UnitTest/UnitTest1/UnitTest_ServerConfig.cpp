// UnitTest_Zookeeper.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemory.h"

#include "Task/SFTask.h"
#include "SFEngine.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"

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

	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXML.LoadConfig("ServerConfig_StressTest.xml"));

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


GTEST_TEST(ServerConfig, ZookeeperStore)
{
	Heap testHeap("test", GetSystemHeap());
	Zookeeper zkInstance(testHeap);
	ServerConfig serverConfig(testHeap);
	ServerConfig serverConfigXML(testHeap);
	const char* zkConfigNodeName = "/ServerConfig";
	zkInstance.Connect("127.0.0.1:2181");
	zkInstance.WaitForConnected();


	ServerConfigXML serverConfigXMLLoader(serverConfigXML);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXMLLoader.LoadConfig("ServerConfig_StressTest.xml"));

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
	zkInstance.Connect("127.0.0.1:2181");
	zkInstance.WaitForConnected();


	ServerConfigXML serverConfigXMLLoader(serverConfigXML);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXMLLoader.LoadConfig("ServerConfig_StressTest.xml"));

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
	zkInstance.Connect("127.0.0.1:2181");
	zkInstance.WaitForConnected();


	ServerConfigXML serverConfigXMLLoader(serverConfigXML);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, serverConfigXMLLoader.LoadConfig("ServerConfig_StressTest.xml"));

	ServerConfigZookeeper zookeeperStore(serverConfigXML, zkInstance);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zookeeperStore.StoreConfig(zkConfigNodeName));

	ServerConfigZookeeper zookeeperLoad(serverConfig, zkInstance);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zookeeperLoad.LoadConfig(zkConfigNodeName));
	GTEST_ASSERT_EQ(serverConfigXML, serverConfig);


	zkInstance.Close();
	zkInstance.WaitForDisconnected();

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}



