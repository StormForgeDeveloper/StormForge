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

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"

#include "zookeeper.h"
#include "ZooKeeper/SFZooKeeper.h"



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


GTEST_TEST(Zookeeper, Simple)
{
	Heap testHeap("test", GetSystemHeap());
	ZooKeeper zkInstance(testHeap);

	zkInstance.Connect("127.0.0.1:2181");
	zkInstance.WaitForConnected();
	StaticArray<uint8_t, 128> valueBuffer(testHeap);
	String outPath;
	auto result = zkInstance.Create("/UnitTestTest", valueBuffer, nullptr, ZOO_EPHEMERAL, outPath);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, result);

	result = zkInstance.Exists("/UnitTestTest");
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, result);

	auto pTask = zkInstance.ACreate("/UnitTestTest2", valueBuffer, nullptr, ZOO_EPHEMERAL);
	pTask->Wait();

	GTEST_ASSERT_EQ(ResultCode::SUCCESS, pTask->ZKResult);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, zkInstance.Exists("/UnitTestTest2"));

	zkInstance.Close();
	zkInstance.WaitForDisconnected();
}

GTEST_TEST(Zookeeper, SimpleData)
{
	Heap testHeap("test", GetSystemHeap());
	ZooKeeper zkInstance(testHeap);

	zkInstance.Connect("127.0.0.1:2181");
	zkInstance.WaitForConnected();
	StaticArray<uint8_t, 128> valueBuffer(testHeap);

	valueBuffer.resize(10);
	for (int iValue = 0; iValue < valueBuffer.size(); iValue++)
	{
		valueBuffer[iValue] = (uint8_t)iValue;
	}

	const char* nodePath = "/UnitTestSimpleData";
	String outPath;
	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)zkInstance.Create(nodePath, valueBuffer, nullptr, ZOO_EPHEMERAL, outPath));
	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)zkInstance.Exists(nodePath));

	StaticArray<uint8_t, 128> getValueBuffer(testHeap);
	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)zkInstance.Get(nodePath, getValueBuffer, nullptr));

	for (int iValue = 0; iValue < valueBuffer.size(); iValue++)
	{
		GTEST_ASSERT_EQ(getValueBuffer[iValue], (uint8_t)iValue);
		valueBuffer[iValue] = (uint8_t)iValue * 2;
	}
	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)zkInstance.Set(nodePath, valueBuffer, -1));

	auto pGetTask = zkInstance.AGet(nodePath);
	pGetTask->Wait();
	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)pGetTask->ZKResult);
	for (int iValue = 0; iValue < pGetTask->ResultData.size(); iValue++)
	{
		GTEST_ASSERT_EQ(pGetTask->ResultData[iValue], (uint8_t)iValue * 2);
		valueBuffer[iValue] = (uint8_t)iValue * 3;
	}
	auto pSetTask = zkInstance.ASet(nodePath, valueBuffer, -1);
	pSetTask->Wait();
	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)pSetTask->ZKResult);

	GTEST_ASSERT_EQ((uint32_t)ResultCode::SUCCESS, (uint32_t)zkInstance.Get(nodePath, getValueBuffer, nullptr));
	for (int iValue = 0; iValue < valueBuffer.size(); iValue++)
	{
		GTEST_ASSERT_EQ(getValueBuffer[iValue], (uint8_t)iValue * 3);
	}

	zkInstance.Close();
	zkInstance.WaitForDisconnected();
}


