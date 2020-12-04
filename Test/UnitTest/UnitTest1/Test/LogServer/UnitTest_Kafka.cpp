////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : Stream test
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"

#include "Task/SFTask.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "UnitTest_Kafka.h"

#include "StreamDB/SFStreamDB.h"
#include "StreamDB/SFStreamDBDirectory.h"


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

    GTEST_ASSERT_EQ(streamDB.Initialize(m_StreamServerAddress[0], topic), ResultCode::SUCCESS);

    GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData1)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<uint8_t>(testData2)), ResultCode::SUCCESS);

    GTEST_ASSERT_EQ(streamDB.Flush(), ResultCode::SUCCESS);
    
}


TEST_F(KafkaTest, Consumer)
{
	const char* topic = "MyTestTopic1";

    StreamDBConsumer streamDB;

	GTEST_ASSERT_EQ(streamDB.Initialize(m_StreamServerAddress[0], topic), ResultCode::SUCCESS);

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

TEST_F(KafkaTest, DirectoryBroker)
{
	SharedPointerT<StreamDBDirectoryBroker> streamDB = new(GetHeap()) StreamDBDirectoryBroker();

	GTEST_ASSERT_EQ(streamDB->Initialize(m_StreamServerAddress[0]), ResultCode::SUCCESS);

	GTEST_ASSERT_EQ(streamDB->RequestStreamList(), ResultCode::SUCCESS);

    SF::MessageDataPtr pMsg;
    auto StartTime = SF::Util::Time.GetRawTimeMs();
    while (!streamDB->PollMessage(pMsg))
    {
        auto CurTime = SF::Util::Time.GetRawTimeMs();
        GTEST_ASSERT_GE(DurationMS(2 * 60 * 1000), (CurTime - StartTime));
        ThisThread::SleepFor(DurationMS(100));
    }



    SFLog(Net, Info, "Stream count:{0}", streamDB->GetStreamList().size());
}

TEST_F(KafkaTest, DirectoryClient)
{
	SharedPointerT<StreamDBDirectoryClient> streamDB = new(GetHeap()) StreamDBDirectoryClient();

	GTEST_ASSERT_EQ(streamDB->Initialize(m_StreamServerAddress[0]), ResultCode::SUCCESS);

	GTEST_ASSERT_EQ(streamDB->RequestStreamList(), ResultCode::SUCCESS);

	SF::MessageDataPtr pMsg;
	auto StartTime = SF::Util::Time.GetRawTimeMs();
	while (!streamDB->PollMessage(pMsg))
	{
		auto CurTime = SF::Util::Time.GetRawTimeMs();
		GTEST_ASSERT_GE(DurationMS(2 * 60 * 1000), (CurTime - StartTime));
		ThisThread::SleepFor(DurationMS(100));
	}



	SFLog(Net, Info, "Stream count:{0}", streamDB->GetStreamList().size());
}

