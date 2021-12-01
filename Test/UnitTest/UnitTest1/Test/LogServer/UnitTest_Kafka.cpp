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

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "UnitTest_Kafka.h"

#include "StreamDB/SFStreamDB.h"
#include "StreamDB/SFStreamDBDirectory.h"

#include "Protocol/PlayInstanceMsgClass.h"


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

    GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<const uint8_t>(testData)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<const uint8_t>(testData1)), ResultCode::SUCCESS);
	GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<const uint8_t>(testData2)), ResultCode::SUCCESS);

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
        SFUniquePtr<StreamMessageData> messageData;
        int32_t timeoutMS = 10;

        hr = streamDB.PollData(messageData, timeoutMS);
        if (hr == ResultCode::END_OF_STREAM)
        {
			break;
        }
        else if (hr == ResultCode::NO_DATA_EXIST)
        {
            // data may not yet available, ignore
            continue;
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


TEST_F(KafkaTest, GroupConsumer)
{
	const char* group = "MyTestGroup";
	const char* topic = "MyTestGroupTopic1";
	const int TestDataCount = 1000;

	for (int iThread = 0; iThread < 3; iThread++)
	{
		SharedPointerT<StreamDBGroupConsumer> streamDB = new(GetHeap()) StreamDBGroupConsumer;

		EXPECT_EQ(streamDB->Initialize(m_StreamServerAddress[0], group, topic), ResultCode::SUCCESS);
		EXPECT_EQ(streamDB->Subscribe(), ResultCode::SUCCESS);

		auto* pThread = new(GetHeap()) FunctorTickThread([&, iThread, streamDB](Thread* pThread) -> bool
			{
				Result hr;
				SFUniquePtr<StreamMessageData> messageData;
				int32_t timeoutMS = 10;

				hr = streamDB->PollData(messageData, timeoutMS);
				if (hr == ResultCode::END_OF_STREAM)
				{
				}
				else if (hr == ResultCode::NO_DATA_EXIST)
				{
					// data may not yet available, ignore
				}
				else if (!hr)
				{
					EXPECT_EQ(hr, ResultCode::SUCCESS);
				}

				if (messageData)
				{
					int32_t* pData = (int32_t*)messageData->data();
					SFLog(System, Info, "Thread {0}, received: {1}", iThread, *pData);

					ThisThread::SleepFor(DurationMS(20));

					streamDB->CommitConsumeState();
				}

				ThisThread::SleepFor(DurationMS(100));

				return true;
			});

		pThread->Start();
		m_Threads.push_back(pThread);
	}


	StreamDBProducer streamDBProducer;

	EXPECT_EQ(streamDBProducer.Initialize(m_StreamServerAddress[0], topic), ResultCode::SUCCESS);

	ThisThread::SleepFor(DurationMS(1000));

	for (int iTestData = 0; iTestData < TestDataCount; iTestData++)
	{
		EXPECT_EQ(streamDBProducer.SendRecord(ArrayView<const uint8_t>(sizeof(iTestData), (const uint8_t*)&iTestData)), ResultCode::SUCCESS);
		ThisThread::SleepFor(DurationMS(12));
	}

	EXPECT_EQ(streamDBProducer.Flush(), ResultCode::SUCCESS);

	ThisThread::SleepFor(DurationMS(1000));

	StopAllThread();
}

TEST_F(KafkaTest, DirectoryBroker)
{
	auto streamDB = NewObject<StreamDBDirectoryBroker>(GetHeap());

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

    if (pMsg != nullptr)
    {
        auto msgId = pMsg->GetMessageHeader()->msgID;
        if (msgId.GetMsgIDOnly() == SF::Message::PlayInstance::FindStreamRes::MID)
        {
            SF::Message::PlayInstance::FindStreamRes msg(std::forward<MessageDataPtr>(pMsg));
            GTEST_ASSERT_EQ(msg.ParseMsg(), ResultCode::SUCCESS);

            // TODO:
            //msg.Get
        }
        else if (msgId.GetMsgIDOnly() == SF::Message::PlayInstance::GetStreamListRes::MID)
        {
            SF::Message::PlayInstance::GetStreamListRes msg(std::forward<MessageDataPtr>(pMsg));
            GTEST_ASSERT_EQ(msg.ParseMsg(), ResultCode::SUCCESS);

			SFLog(Net, Info, "Stream count:{0}", msg.GetStreamNames().size());
        }
    }

}

TEST_F(KafkaTest, DirectoryClient)
{
	SharedPointerT<StreamDBDirectoryClient> streamDB = NewObject<StreamDBDirectoryClient>(GetHeap());
    // TODO:
	//GTEST_ASSERT_EQ(streamDB->Initialize(m_StreamServerAddress[0]), ResultCode::SUCCESS);

	//GTEST_ASSERT_EQ(streamDB->RequestStreamList(), ResultCode::SUCCESS);

	//SF::MessageDataPtr pMsg;
	//auto StartTime = SF::Util::Time.GetRawTimeMs();
	//while (!streamDB->PollMessage(pMsg))
	//{
	//	auto CurTime = SF::Util::Time.GetRawTimeMs();
	//	GTEST_ASSERT_GE(DurationMS(2 * 60 * 1000), (CurTime - StartTime));
	//	ThisThread::SleepFor(DurationMS(100));
	//}

	//if (pMsg != nullptr)
	//{
	//	auto msgId = pMsg->GetMessageHeader()->msgID;
	//	if (msgId.GetMsgIDOnly() == SF::Message::Relay::FindStreamRes::MID)
	//	{
	//		SF::Message::Relay::FindStreamRes msg(std::forward<MessageDataPtr>(pMsg));
	//		GTEST_ASSERT_EQ(msg.ParseMsg(), ResultCode::SUCCESS);

	//		// TODO:
	//		//msg.Get
	//	}
	//	else if (msgId.GetMsgIDOnly() == SF::Message::Relay::GetStreamListRes::MID)
	//	{
	//		SF::Message::Relay::GetStreamListRes msg(std::forward<MessageDataPtr>(pMsg));
	//		GTEST_ASSERT_EQ(msg.ParseMsg(), ResultCode::SUCCESS);

	//		SFLog(Net, Info, "Stream count:{0}", msg.GetStreamNames().size());
	//	}
	//}
}

