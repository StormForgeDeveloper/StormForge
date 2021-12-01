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

#pragma once

#include "SFTypedefs.h"

#define USE_STREAMDB

#ifdef USE_STREAMDB
#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Task/SFTask.h"



namespace RdKafka
{
    class Conf;
    class Topic;
    class Metadata;
    class Handle;
    class Producer;
    class Consumer;
    class Message;
    class KafkaConsumer;
}

namespace SF
{
    class StreamDBSendReportCb;

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDB
	//

    class StreamDB : public SharedObject
    {
    public:


        /**
         * @brief Unassigned partition.
         *
         * The unassigned partition is used by the producer API for messages
         * that should be partitioned using the configured or default partitioner.
         */
        static const int32_t PARTITION_UA;

        /** @brief Special offsets */
        static const int64_t OFFSET_BEGINNING; /**< Consume from beginning */
        static const int64_t OFFSET_END; /**< Consume from end */
        static const int64_t OFFSET_STORED; /**< Use offset storage */
        static const int64_t OFFSET_INVALID; /**< Invalid offset */


    public:

        StreamDB();
        virtual ~StreamDB();


        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0);

        const String& GetTopic() const { return m_StreamName; }
        int32_t GetPartition() const { return m_Partition; }
        void SetPartition(int32_t value) { m_Partition = value; }

        const UniquePtr<RdKafka::Conf>& GetConfig() const { return m_Config; }
        const UniquePtr<RdKafka::Conf>& GetTopicConfig() const { return m_TopicConfig; }

        const UniquePtr<RdKafka::Topic>& GetTopicHandle() const { return m_TopicHandle; }

        const Array<int32_t>& GetPartitionList() const { return m_PartitionIds; }

    protected:

        Result UpdateTopicMetadata(RdKafka::Handle* handle);

        void SetTopicHandle(RdKafka::Topic* topic);

        void Clear_Internal();

	protected:
		DynamicArray<int32_t> m_PartitionIds;

    private:

        int32_t m_Partition = -1;
        String m_StreamName;

        UniquePtr<RdKafka::Conf> m_Config;
        UniquePtr<RdKafka::Conf> m_TopicConfig;

        UniquePtr<RdKafka::Topic> m_TopicHandle;

        UniquePtr<RdKafka::Metadata> m_TopicMetadata;
    };




    ////////////////////////////////////////////////////////////////////////////////////////////
    //
    //  class StreamDBProducer
    //
    class StreamDBProducer : public StreamDB
    {
    public:

        using super = StreamDB;

    public:

        StreamDBProducer();

        virtual ~StreamDBProducer();

        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0) override;

        Result SendRecord(const ArrayView<const uint8_t>& data);

        Result Flush();


    private:

        UniquePtr<StreamDBSendReportCb> m_DeliveryCallback;

        UniquePtr<RdKafka::Producer> m_Producer;
    };


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBConsumer
	//

	class StreamMessageData : public ArrayView<const uint8_t>
	{
	public:

		StreamMessageData(RdKafka::Message* messageData);

		virtual ~StreamMessageData();

		int64_t GetOffset() const;
		int64_t GetTimeStamp() const;

	private:

		UniquePtr<RdKafka::Message> m_MessageData;
	};

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBConsumer
	//

    class StreamDBConsumer : public StreamDB
    {
    public:

        using super = StreamDB;


    public:

        StreamDBConsumer();
        virtual ~StreamDBConsumer();

        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0) override;

        bool IsDateRequested() const { return m_IsDataRequested; }

        Result RequestData(int64_t start_offset = OFFSET_BEGINNING);

        Result PollData(SFUniquePtr<StreamMessageData>& receivedMessageData, int32_t timeoutMS = 0);
		Result PollData(int32_t timeoutMS = 0);

        const SFUniquePtr<StreamMessageData>& GetLatestReceivedData() const { return m_ReceivedMessageData; }

        int64_t ToOffsetFromTail(int64_t offsetFromTail) const;

    private:

        UniquePtr<RdKafka::Consumer> m_Consumer;

        bool m_IsDataRequested = false;

        // Locally cached data. This is for C# interface to keep the message data even after returned pointer to c# system until next pool
        SFUniquePtr<StreamMessageData> m_ReceivedMessageData;
    };


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBGroupConsumer
    //          This is interface as group message consumer. Only one consumer in the group will receive the message
	//

	class StreamDBGroupConsumer : public StreamDB
	{
	public:

		using super = StreamDB;


	public:

        StreamDBGroupConsumer();
		virtual ~StreamDBGroupConsumer();

		virtual Result Initialize(const String& brokers, const String& consumerGroupId, const String& topic);

		SF_FORCEINLINE bool IsSubscribed() const { return m_IsSubscribed; }

		Result Subscribe(bool bSeekToEnd = false);
        Result Unsubscribe();

		Result PollData(SFUniquePtr<StreamMessageData>& receivedMessageData, int32_t timeoutMS = 0);

        Result CommitConsumeState();


	private:

		UniquePtr<RdKafka::KafkaConsumer> m_Consumer;

		bool m_IsSubscribed = false;
	};

}
#endif

