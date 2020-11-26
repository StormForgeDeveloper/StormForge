// UnitTest_Zookeeper.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"

#include "Task/SFTask.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "UnitTest_Kafka.h"

#include "StreamDB/SFStreamDB.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




TEST_F(KafkaTest, Producer)
{
    const char* topic = "MyTestTopic1";
    uint8_t testData[] = {1,2,3,4,5,6,7,8,9};
    uint8_t testData1[] = { 'T', 'e', 's', 't', 'D', 'a', 't', 'a', 'D', 'a', 't', 'a', '\0' };
	uint8_t testData2[] = { 1,2,3,4,5,6,7,8,9, 123 };

    StreamDBProducer streamDB;

    GTEST_ASSERT_EQ(streamDB.Initialize(m_StreamServerAddress, topic), ResultCode::SUCCESS);

    GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData1)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData2)), ResultCode::SUCCESS);

    GTEST_ASSERT_EQ(streamDB.Flush(), ResultCode::SUCCESS);
    
}


TEST_F(KafkaTest, Consumer)
{
	const char* topic = "MyTestTopic1";

    StreamDBConsumer streamDB;

	GTEST_ASSERT_EQ(streamDB.Initialize(m_StreamServerAddress, topic), ResultCode::SUCCESS);

    GTEST_ASSERT_EQ(streamDB.RequestData(), ResultCode::SUCCESS);

    Result hr;
    do {
		UniquePtr<ArrayView<uint8_t>> messageData;
        int32_t timeoutMS = 10;

        hr = streamDB.PollData(messageData, timeoutMS);
        if (hr == ResultCode::END_OF_STREAM)
        {
			break;
        }
        else if (!hr)
        {
            GTEST_ASSERT_EQ(hr, ResultCode::SUCCESS);
			break;
        }

        if (messageData)
        {
            // do your job
        }

    } while (true);

}

TEST_F(KafkaTest, Directory)
{
	StreamDBDirectory streamDB;

	GTEST_ASSERT_EQ(streamDB.Initialize(m_StreamServerAddress, ""), ResultCode::SUCCESS);

	GTEST_ASSERT_EQ(streamDB.RefreshTopicList(), ResultCode::SUCCESS);
}


