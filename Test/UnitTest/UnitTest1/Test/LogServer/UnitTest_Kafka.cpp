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



GTEST_TEST(Kafka, Producer)
{
    const char* topic = "MyTestTopic";
    uint8_t testData[] = {1,2,3,4,5,6,7,8,9};
    uint8_t testData1[] = { 'T', 'e', 's', 't', 'D', 'a', 't', 'a', 'D', 'a', 't', 'a', '\0' };
	uint8_t testData2[] = { 1,2,3,4,5,6,7,8,9, 123 };

    StreamDBProducer streamDB;

    GTEST_ASSERT_EQ(streamDB.Initialize("139.162.111.45:19092", topic), ResultCode::SUCCESS);


    GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData1)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData2)), ResultCode::SUCCESS);

    GTEST_ASSERT_EQ(streamDB.Flush(), ResultCode::SUCCESS);
    
}


GTEST_TEST(Kafka, Consumer)
{
	const char* topic = "MyTestTopic";

    StreamDBConsumer streamDB;

	GTEST_ASSERT_EQ(streamDB.Initialize("139.162.111.45:19092", topic), ResultCode::SUCCESS);


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
            
        }

    } while (true);

}


