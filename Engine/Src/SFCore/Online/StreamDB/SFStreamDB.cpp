////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"

#include "Online/StreamDB/SFStreamDB.h"
#include "Util/SFStringFormat.h"
#include "Util/SFTrace.h"

#ifdef USE_STREAMDB

#include "librdkafka/rdkafkacpp.h"



namespace SF
{
    namespace Log
    {
        LogChannel Kafka("Kafka", LogOutputType::Debug4);
    }

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDB
	//


	/**
		* @brief Unassigned partition.
		*
		* The unassigned partition is used by the producer API for messages
		* that should be partitioned using the configured or default partitioner.
		*/
	const int32_t StreamDB::PARTITION_UA = RdKafka::Topic::PARTITION_UA;

	/** @brief Special offsets */
	const int64_t StreamDB::OFFSET_BEGINNING = RdKafka::Topic::OFFSET_BEGINNING; /**< Consume from beginning */
	const int64_t StreamDB::OFFSET_END = RdKafka::Topic::OFFSET_END; /**< Consume from end */
	const int64_t StreamDB::OFFSET_STORED = RdKafka::Topic::OFFSET_STORED; /**< Use offset storage */
	const int64_t StreamDB::OFFSET_INVALID = RdKafka::Topic::OFFSET_INVALID; /**< Invalid offset */


	StreamDB::StreamDB()
	{

	}

	StreamDB::~StreamDB()
	{

	}

	Result StreamDB::Initialize(const String& brokers, const String& topic, int32_t partition)
	{
		m_Config.reset(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));

		if (!m_Config)
			return ResultCode::OUT_OF_MEMORY;

        m_Server = brokers;

		std::string errstr;
		if (m_Config->set("bootstrap.servers", brokers.data(), errstr) != RdKafka::Conf::CONF_OK)
		{
			SFLog(Kafka, Error, "Kafka server configuration has failed: {0}", errstr);
			return ResultCode::INVALID_ARG;
		}

		m_TopicConfig.reset(RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC));

		if (!m_TopicConfig)
			return ResultCode::OUT_OF_MEMORY;

		if (m_Config->set("default_topic_conf", m_TopicConfig.get(), errstr) != RdKafka::Conf::CONF_OK)
		{
			SFLog(Kafka, Error, "Kafka configuration has failed: {0}", errstr);
			return ResultCode::INVALID_ARG;
		}

        // TODO: need to implement partitioning.
		m_Partition = partition;

        m_Topic = topic;



		return ResultCode::SUCCESS;
	}

	Result StreamDB::UpdateTopicMetadata(RdKafka::Handle* handle)
	{
		if (handle == nullptr || !GetTopicHandle())
			return ResultCode::NOT_INITIALIZED;

		RdKafka::Metadata* metadata = nullptr;
		int32_t metadataTimeout = 5 * 1000;
		RdKafka::ErrorCode errorCode = handle->metadata(false, GetTopicHandle().get(), &metadata, metadataTimeout);
		if (errorCode != RdKafka::ErrorCode::ERR_NO_ERROR)
		{
			SFLog(Kafka, Error, "Kafka getting metadata has failed: {0}:{1}", int(errorCode), RdKafka::err2str(errorCode));
			return ResultCode::STREAM_NOT_EXIST;
		}

		if (metadata == nullptr)
		{
			SFLog(Kafka, Error, "Kafka getting metadata has failed: nullptr returned");
			return ResultCode::UNEXPECTED;
		}

		m_TopicMetadata.reset(metadata);

		SFLog(Kafka, Debug, "Metadata for {0}, brokerId:{1}, {2}", GetTopic(), metadata->orig_broker_id(), metadata->orig_broker_name());

		m_PartitionIds.Clear();

		// Iterate topics
		RdKafka::Metadata::TopicMetadataIterator it;
		for (it = metadata->topics()->begin();
			it != metadata->topics()->end();
			++it)
		{
            if ((*it)->err() == RdKafka::ERR_UNKNOWN_TOPIC_OR_PART)
            {
                SFLog(Kafka, Info, "Topic or partition doesn't exist");
                continue;
            }

			if ((*it)->err() != RdKafka::ERR_NO_ERROR)
			{
                errorCode = (*it)->err();
				SFLog(Kafka, Error, "Topic metadata error, topic:{0}, {1}:{2}", (*it)->topic(), int(errorCode), err2str(errorCode));
				continue;
			}

			if (GetTopic() != (*it)->topic().c_str())
				continue;

			SFLog(Kafka, Debug, "Topic metadata, topic:{0}", (*it)->topic());

			// Iterate topic's partitions
			RdKafka::TopicMetadata::PartitionMetadataIterator ip;
			for (ip = (*it)->partitions()->begin();
				ip != (*it)->partitions()->end();
				++ip)
			{
				SFLog(Kafka, Debug, " partition:{0}, leader:{1}", (*ip)->id(), (*ip)->leader());

				m_PartitionIds.push_back((*ip)->id());

				// Iterate partition's replicas
				RdKafka::PartitionMetadata::ReplicasIterator ir;
				for (ir = (*ip)->replicas()->begin();
					ir != (*ip)->replicas()->end();
					++ir)
				{
					SFLog(Kafka, Debug, "     Replica:{0}", *ir);
				}

				// Iterate partition's ISRs 
				RdKafka::PartitionMetadata::ISRSIterator iis;
				for (iis = (*ip)->isrs()->begin(); iis != (*ip)->isrs()->end(); ++iis)
				{
					SFLog(Kafka, Debug2, "     ISR:{0}", *iis);
				}
			}
		}

		return ResultCode::SUCCESS;
	}

	void StreamDB::SetTopicHandle(RdKafka::Topic* topic)
	{
		m_TopicHandle.reset(topic);
	}

	void StreamDB::Clear_Internal()
	{
		m_TopicHandle.reset();
		m_Config.reset();
		m_TopicConfig.reset();
	}



	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBProducer
	//


	class StreamDBSendReportCb : public RdKafka::DeliveryReportCb
	{
    private:

        StreamDB& m_Owner;

	public:

		StreamDBSendReportCb(StreamDB& owner)
            : m_Owner(owner)
		{}

		virtual ~StreamDBSendReportCb()
		{}

		virtual void dr_cb(RdKafka::Message& message) override;

	};

	void StreamDBSendReportCb::dr_cb(RdKafka::Message& message)
	{
		/* If message.err() is non-zero the message delivery failed permanently for the message. */
		if (message.err())
		{
			SFLog(Kafka, Error, "Kafka Message delivery failed, server:{0}, channel:{1}, partition:{2}  error:{3}", m_Owner.GetServer(), m_Owner.GetTopic(), m_Owner.GetPartition(), message.errstr());
		}
		else
		{
			//SFLog(Kafka, Debug1, "Kafka Message delivered to topic:{0}, partition:{1}", message.topic_name(), message.partition());
		}
	}





	StreamDBProducer::StreamDBProducer()
		: m_DeliveryCallback(new StreamDBSendReportCb(*this))
	{
		
	}

	StreamDBProducer::~StreamDBProducer()
	{
		Clear_Internal(); // Unlike regular cases, parent stuffs should be released first
		m_Producer.reset();
	}

	Result StreamDBProducer::Initialize(const String& serverAddress, const String& path, int32_t partition)
	{
		if (serverAddress.IsNullOrEmpty() || path.IsNullOrEmpty())
		{
			SFLog(Kafka, Error, "Stream producer has invalid parameter: {0}", serverAddress, path);
			return ResultCode::INVALID_ARG;
		}

		Result hr = super::Initialize(serverAddress, path, partition);
		if (!hr.IsSuccess())
			return hr;

		std::string errstr;
		if (GetConfig()->set("dr_cb", m_DeliveryCallback.get(), errstr) != RdKafka::Conf::CONF_OK) {
			SFLog(Kafka, Error, "Kafka callback registration has failed: {0}", errstr);
			return ResultCode::INVALID_ARG;
		}

		RdKafka::Producer* producer = RdKafka::Producer::create(GetConfig().get(), errstr);
		if (!producer)
		{
			SFLog(Kafka, Error, "Kafka producer creation has failed: {0}", errstr);
			return ResultCode::INVALID_ARG;
		}

		m_Producer.reset(producer);

		RdKafka::Topic* topicHandle = RdKafka::Topic::create(m_Producer.get(), GetTopic().data(), GetTopicConfig().get(), errstr);
		if (topicHandle == nullptr)
		{
			SFLog(Kafka, Error, "Kafka consumer topic creation has failed: {0}", errstr);
			return ResultCode::OUT_OF_MEMORY;
		}

		SetTopicHandle(topicHandle);

		// If the there is no data in the topic, getting metadata will fail.
		// Ignoring metadata update result
		UpdateTopicMetadata(m_Producer.get());

		return ResultCode::SUCCESS;
	}

	Result StreamDBProducer::SendRecord(const ArrayView<const uint8_t>& data)
	{
		if (!m_Producer)
			return ResultCode::NOT_INITIALIZED;

		if (data.size() == 0)
			return ResultCode::INVALID_ARG;

		if (GetTopic().IsNullOrEmpty())
			return ResultCode::NOT_INITIALIZED;

		RdKafka::ErrorCode err = m_Producer->produce(
			GetTopicHandle().get(),
			/* Any Partition: the builtin partitioner will be
			 * used to assign the message to a topic based
			 * on the message key, or random partition if
			 * the key is not set. */
			GetPartition(),
			RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
			/* Payload */
			(void*)data.data(), data.size(),
			NULL, 0 // Key
		);

		if (err != RdKafka::ERR_NO_ERROR)
		{
			SFLog(Kafka, Error, "Kafka Failed to send data, topic:{0}, error:{1}{2}", GetTopic(), int(err), RdKafka::err2str(err));

			if (err == RdKafka::ERR__QUEUE_FULL)
			{
				// change queue.buffering.max.messages if you want more
				return ResultCode::OUT_OF_RESERVED_MEMORY;
			}
			else
			{
				return ResultCode::UNEXPECTED;
			}
		}
		else
		{
			//SFLog(Kafka, Debug, "Kafka Enqueued message: {0}, size:{1}", GetTopic(), data.size());
		}

		// TODO:  I might want to do it on specific thread
		m_Producer->poll(0);

		return ResultCode::SUCCESS;
	}

	Result StreamDBProducer::Flush(DurationMS timeout)
	{
		if (!m_Producer)
			return ResultCode::NOT_INITIALIZED;

		auto res = m_Producer->flush(timeout.count());
		return res == RdKafka::ErrorCode::ERR_NO_ERROR ? ResultCode::SUCCESS : ResultCode::IO_TIMEDOUT;
	}






	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBConsumer
	//

	StreamMessageData::StreamMessageData(RdKafka::Message* messageData)
		: ArrayView<const uint8_t>(messageData->len(), reinterpret_cast<const uint8_t*>(messageData->payload()))
		, m_MessageData(messageData)
	{
	}

	StreamMessageData::~StreamMessageData()
	{

	}

	int64_t StreamMessageData::GetOffset() const
	{
		return m_MessageData->offset();
	}

	int64_t StreamMessageData::GetTimeStamp() const
	{
		return m_MessageData->timestamp().timestamp;
	}

	//size_t StreamMessageData::size() const
	//{
	//	if (m_MessageData)
	//		return m_MessageData->len();

	//	return 0;
	//}

	//const uint8_t* StreamMessageData::data() const
	//{
	//	if (m_MessageData)
	//		return reinterpret_cast<const uint8_t*>(m_MessageData->payload());

	//	return nullptr;
	//}


	StreamDBConsumer::StreamDBConsumer()
	{

	}

	StreamDBConsumer::~StreamDBConsumer()
	{
		if (m_Consumer)
		{
			m_Consumer->stop(GetTopicHandle().get(), GetPartition());

			m_Consumer->poll(1000);
		}

		Clear_Internal(); // Unlike regular cases, parent stuffs should be released first
		m_Consumer.reset();
	}

	Result StreamDBConsumer::Initialize(const String& serverAddress, const String& path, int32_t partition)
	{
		std::string errstr;

		if (serverAddress.IsNullOrEmpty() || path.IsNullOrEmpty())
		{
			SFLog(Kafka, Error, "Stream consumer has invalid parameter: {0}", serverAddress, path);
			return ResultCode::INVALID_ARG;
		}

		Result hr = super::Initialize(serverAddress, path, partition);
		if (!hr.IsSuccess())
			return hr;

		GetConfig()->set("enable.partition.eof", "true", errstr);

		RdKafka::Consumer* consumer = RdKafka::Consumer::create(GetConfig().get(), errstr);
		if (!consumer)
		{
			SFLog(Kafka, Error, "Kafka consumer creation has failed: {0}", errstr);
			return ResultCode::OUT_OF_MEMORY;
		}

		m_Consumer.reset(consumer);

		RdKafka::Topic* topicHandle = RdKafka::Topic::create(m_Consumer.get(), GetTopic().data(), GetTopicConfig().get(), errstr);
		if (topicHandle == nullptr)
		{
			SFLog(Kafka, Error, "Kafka consumer topic creation has failed: {0}", errstr);
			return ResultCode::OUT_OF_MEMORY;
		}

		SetTopicHandle(topicHandle);

		hr = UpdateTopicMetadata(m_Consumer.get());

        return hr;
	}


	Result StreamDBConsumer::RequestData(int64_t start_offset)
	{
		if (m_Consumer == nullptr)
			return ResultCode::NOT_INITIALIZED;

		// partition has never been set. Set one now
		if (GetPartition() <= 0 && GetPartitionList().size() > 0)
		{
			SetPartition(*GetPartitionList().begin());
		}

		RdKafka::ErrorCode resp = m_Consumer->start(GetTopicHandle().get(), GetPartition(), start_offset);
		if (resp != RdKafka::ERR_NO_ERROR)
		{
			SFLog(Kafka, Log, "Failed to start consumer: {0}:{1}", int(resp), RdKafka::err2str(resp));
			return ResultCode::FAIL;
		}

		m_IsDataRequested = true;

		return ResultCode::SUCCESS;
	}

	Result StreamDBConsumer::PollData(SFUniquePtr<StreamMessageData>& receivedMessageData, int32_t timeoutMS)
	{
		ScopeContext hr([this](Result hr)
			{
				if (m_Consumer)
					m_Consumer->poll(0);
			});

		if (!m_Consumer)
			return hr = ResultCode::NOT_INITIALIZED;

        if (m_PartitionIds.size() == 0)
        {
            SFLog(Kafka, Log, "Consumer::PollData, there are no partition, querying again");

            SFCheck(Kafka, UpdateTopicMetadata(m_Consumer.get()));
        }

		UniquePtr<RdKafka::Message> message(m_Consumer->consume(GetTopicHandle().get(), GetPartition(), timeoutMS));
		if (message == nullptr)
			return hr = ResultCode::NO_DATA_EXIST;

		switch (message->err())
		{
		case RdKafka::ERR__TIMED_OUT:
            SFLog(Kafka, Debug4, "Consume Timedout");
            hr = ResultCode::NO_DATA_EXIST;
			break;

		case RdKafka::ERR_NO_ERROR:

			/* Real message */
			SFLog(Kafka, Debug4, "Read msg at offset:{0}, size:{1}", message->offset(), message->len());

			receivedMessageData.reset(new(GetSystemHeap()) StreamMessageData(message.release()));
			break;

		case RdKafka::ERR__PARTITION_EOF:
			// Last message
            SFLog(Kafka, Debug4, "Consume ERR__PARTITION_EOF");
			hr = ResultCode::END_OF_STREAM;
			break;

		case RdKafka::ERR__UNKNOWN_TOPIC:
		case RdKafka::ERR__UNKNOWN_PARTITION:
        case RdKafka::ERR_UNKNOWN_TOPIC_OR_PART:
            SFLog(Kafka, Error, "Consume failed: part:{0}, stream:{1}, error:{2}", GetPartition(), GetTopic(), message->errstr());
			hr = ResultCode::STREAM_NOT_EXIST;
			break;

		default:
			SFLog(Kafka, Error, "Consume failed: {0}:{1}", int(message->err()), message->errstr());
			hr = ResultCode::UNEXPECTED;
		}

		return hr;
	}


	Result StreamDBConsumer::PollData(int32_t timeoutMS)
	{
		m_ReceivedMessageData.reset();
		return PollData(m_ReceivedMessageData, timeoutMS);
	}

	int64_t StreamDBConsumer::ToOffsetFromTail(int64_t offsetFromTail) const
	{
		if (offsetFromTail < 0)
			offsetFromTail = 0;

		return RdKafka::Consumer::OffsetTail(offsetFromTail);
	}



	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBGroupConsumer
	//

	StreamDBGroupConsumer::StreamDBGroupConsumer()
	{

	}

	StreamDBGroupConsumer::~StreamDBGroupConsumer()
	{
		if (m_Consumer)
		{
			m_Consumer->close();
		}

		Clear_Internal(); // Unlike regular cases, parent stuffs should be released first
		m_Consumer.reset();
	}

	Result StreamDBGroupConsumer::Initialize(const String& serverAddress, const String& consumerGroupId, const String& consumerGroupInstanceId, const String& path)
	{
		std::string errstr;

		Result hr = super::Initialize(serverAddress, path, -1);
		if (!hr.IsSuccess())
			return hr;

		GetConfig()->set("enable.partition.eof", "true", errstr);

		if (consumerGroupId.IsNullOrEmpty())
			return ResultCode::INVALID_ARG;

		GetConfig()->set("group.id", consumerGroupId.c_str(), errstr);
        if (!consumerGroupInstanceId.IsNullOrEmpty())
        {
            // My unique Id for static membership
            // https://www.confluent.io/blog/dynamic-vs-static-kafka-consumer-rebalancing/
            GetConfig()->set("group.instance.id", consumerGroupInstanceId.c_str(), errstr);
        }

		auto* consumer = RdKafka::KafkaConsumer::create(GetConfig().get(), errstr);
		if (!consumer)
		{
			SFLog(Kafka, Error, "Kafka consumer creation has failed: {0}", errstr);
			return ResultCode::OUT_OF_MEMORY;
		}

		m_Consumer.reset(consumer);

		RdKafka::Topic* topicHandle = RdKafka::Topic::create(m_Consumer.get(), GetTopic().data(), GetTopicConfig().get(), errstr);
		if (topicHandle == nullptr)
		{
			SFLog(Kafka, Error, "Kafka consumer topic creation has failed: {0}", errstr);
			return ResultCode::OUT_OF_MEMORY;
		}

		SetTopicHandle(topicHandle);

		return UpdateTopicMetadata(m_Consumer.get());
	}


	Result StreamDBGroupConsumer::Subscribe(bool bSeekToEnd)
	{
		if (m_Consumer == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (GetTopic().IsNullOrEmpty())
			return ResultCode::INVALID_ARG;

		std::vector<std::string> topics;
		topics.push_back(GetTopic().data());

		RdKafka::ErrorCode resp = m_Consumer->subscribe(topics);
		if (resp != RdKafka::ERR_NO_ERROR)
		{
			SFLog(Kafka, Debug, "Failed to Subscribe consumer: {0}:{1}", int(resp), RdKafka::err2str(resp));
			return ResultCode::FAIL;
		}

		// TODO: handle bSeekToEnd. I need to find assigned partition list and seek each of them to end

        SFLog(Kafka, Log, "Subscribed consumer: {0}", GetTopic());
		m_IsSubscribed = true;

		return ResultCode::SUCCESS;
	}

	Result StreamDBGroupConsumer::Unsubscribe()
	{
		if (m_Consumer == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (GetTopic().IsNullOrEmpty())
			return ResultCode::INVALID_ARG;

		RdKafka::ErrorCode resp = m_Consumer->unsubscribe();
		if (resp != RdKafka::ERR_NO_ERROR)
		{
			SFLog(Kafka, Debug, "Unsubscribe, Failed to unsubscribe consumer: {0}:{1}", int(resp), RdKafka::err2str(resp));
			return ResultCode::FAIL;
		}

		m_IsSubscribed = true;

		return ResultCode::SUCCESS;
	}

	Result StreamDBGroupConsumer::PollData(SFUniquePtr<StreamMessageData>& receivedMessageData, int32_t timeoutMS)
	{
		ScopeContext hr([this](Result hr)
			{
				//if (m_Consumer)
				//	m_Consumer->poll(0);
			});

		if (!m_Consumer)
			return hr = ResultCode::NOT_INITIALIZED;

		UniquePtr<RdKafka::Message> message(m_Consumer->consume(timeoutMS));
		if (message == nullptr)
			return hr = ResultCode::NO_DATA_EXIST;

		switch (message->err())
		{
		case RdKafka::ERR__TIMED_OUT:
			hr = ResultCode::NO_DATA_EXIST;
			break;

		case RdKafka::ERR_NO_ERROR:

			/* Real message */
			SFLog(Kafka, Debug4, "Read msg at offset:{0}, size:{1}", message->offset(), message->len());

			receivedMessageData.reset(new(GetSystemHeap()) StreamMessageData(message.release()));
			break;

		case RdKafka::ERR__PARTITION_EOF:
			// Last message
			hr = ResultCode::END_OF_STREAM;
			break;

		case RdKafka::ERR__UNKNOWN_TOPIC:
		case RdKafka::ERR__UNKNOWN_PARTITION:
        case RdKafka::ERR_UNKNOWN_TOPIC_OR_PART:
            SFLog(Kafka, Error, "Consume failed: part:{0}, stream:{1}, error:{2}", GetPartition(), GetTopic(), message->errstr());
			hr = ResultCode::STREAM_NOT_EXIST;
			break;

		default:
			SFLog(Kafka, Error, "Consume failed: {0}:{1}", int(message->err()), message->errstr());
			hr = ResultCode::UNEXPECTED;
		}

		return hr;
	}

	Result StreamDBGroupConsumer::CommitConsumeState()
	{
		if (!m_Consumer)
			return ResultCode::NOT_INITIALIZED;

		RdKafka::ErrorCode resp = m_Consumer->commitAsync();
		if (resp != RdKafka::ERR_NO_ERROR)
		{
			SFLog(Kafka, Debug, "CommitConsumeState, Failed to unsubscribe consumer: {0}:{1}", int(resp), RdKafka::err2str(resp));
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}


}

#endif
