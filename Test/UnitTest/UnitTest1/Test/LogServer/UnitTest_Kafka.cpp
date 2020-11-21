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

#include "rdkafka/rdkafkacpp.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



class StreamDB
{
private:
    class StreamDBDeliveryReportCb : public RdKafka::DeliveryReportCb
    {
    public:
        virtual void dr_cb(RdKafka::Message& message) override
        {
            /* If message.err() is non-zero the message delivery failed permanently for the message. */
            if (message.err())
            {
				SFLog(Net, Error, "Kafka Message delivery failed: {0}", message.errstr());
            }
            else
            {
				SFLog(Net, Info, "Kafka Message delivered to topic:{0}, partition:{1}", message.topic_name(), message.partition());
            }
        }

        
        StreamDBDeliveryReportCb()
        {

        }

        virtual ~StreamDBDeliveryReportCb()
        {

        }

    };

public:
	Result Initialize(const String& brokers, const String& strStreamName)
	{
        m_StreamName = strStreamName;
		m_Config.reset(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));

		std::string errstr;
		if (m_Config->set("bootstrap.servers", brokers.data(), errstr) !=
			RdKafka::Conf::CONF_OK) {
			SFLog(Net, Error, "Kafka server config has failed: {0}", errstr);
            return ResultCode::INVALID_ARG;
		}

		if (m_Config->set("dr_cb", &m_DeliveryCallback, errstr) != RdKafka::Conf::CONF_OK) {
            SFLog(Net, Error, "Kafka callback registration has failed: {0}", errstr);
            return ResultCode::INVALID_ARG;
		}

		RdKafka::Producer* producer = RdKafka::Producer::create(m_Config.get(), errstr);
		if (!producer)
        {
            SFLog(Net, Error, "Kafka producer creation has failed: {0}", errstr);
            return ResultCode::INVALID_ARG;
		}

        m_Producer.reset(producer);

        return ResultCode::SUCCESS;
	}

    Result SendRecord(const String& strTopic, const Array<uint8_t>& data, int64_t timestamp = 0)
    {
        if (!m_Producer)
        {
            return ResultCode::NOT_INITIALIZED;
        }

        if (strTopic.IsNullOrEmpty() || data.size() == 0)
        {
			return ResultCode::INVALID_ARG;
        }

        // Additional headers
		RdKafka::Headers* headers = RdKafka::Headers::create();
		headers->add("GameStream", m_StreamName.data());
		//headers->add("other header", "yes");
        //int64_t timestamp = 0; // default current time;

        RdKafka::ErrorCode err = m_Producer->produce(
            /* Topic name */
            strTopic.data(),
            /* Any Partition: the builtin partitioner will be
             * used to assign the message to a topic based
             * on the message key, or random partition if
             * the key is not set. */
            RdKafka::Topic::PARTITION_UA,
            /* Make a copy of the value */
            RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
            /* Payload */
            const_cast<uint8_t*>(data.data()), data.size(),
            NULL, 0, // Key
            timestamp, // Timestamp (0 means defaults to current time)
            headers,
            /* Per-message opaque value passed to
             * delivery report */
            NULL);

        if (err != RdKafka::ERR_NO_ERROR)
        {
            SFLog(Net, Error, "Kafka Failed to produce to topic: {0}, {1}", strTopic, RdKafka::err2str(err));

            delete headers; // Headers are automatically deleted on produce() success. 

            if (err == RdKafka::ERR__QUEUE_FULL)
            {
                 // change queue.buffering.max.messages if you want more
                return ResultCode::OUT_OF_RESERVED_MEMORY;
            }
        }
        else
        {
            SFLog(Net, Debug2, "Kafka Enqueued message: {0}, size:{1}", strTopic, data.size());
        }

        // TODO:  I might want to do it on specific thread
        m_Producer->poll(0);

        return ResultCode::SUCCESS;
    }

private:
    StreamDBDeliveryReportCb m_DeliveryCallback;
    UniquePtr<RdKafka::Conf> m_Config;
    UniquePtr<RdKafka::Producer> m_Producer;

    String m_StreamName;
};


GTEST_TEST(Kafka, Simple)
{

    const char* topic = "MyTopic";
    uint8_t testData[] = {1,2,3,4,5,6,7,8,9};

    StreamDB streamDB;

    streamDB.Initialize("139.162.111.45:19092", "TestStream1");

    streamDB.SendRecord(topic, ArrayView<uint8_t>(testData));
}


