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
#include "String/SFStringCrc32.h"
#include "String/SFString.h"
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


        virtual Result Initialize(const String& brokers, const String& topic);


        const String& GetTopic() const { return m_StreamName; }

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

        virtual Result Initialize(const String& brokers, const String& topic) override;

        Result SendRecord(const Array<uint8_t>& data, int64_t timestamp = 0);

        Result Flush();


    private:

        UniquePtr<StreamDBSendReportCb> m_DeliveryCallback;

        UniquePtr<RdKafka::Producer> m_Producer;

    };


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBConsumer
	//

    class StreamDBConsumer : public StreamDB
    {
    public:

        using super = StreamDB;


        class StreamMessageData : public ArrayView<uint8_t>
        {
        public:

            StreamMessageData(RdKafka::Message* messageData);

            virtual ~StreamMessageData();

            int64_t GetOffset() const;
            int64_t GetTimeStamp() const;

        private:

            UniquePtr<RdKafka::Message> m_MessageData;
        };

    public:

        StreamDBConsumer();
        virtual ~StreamDBConsumer();

        virtual Result Initialize(const String& brokers, const String& topic) override;

        Result RequestData(int64_t start_offset = OFFSET_BEGINNING);

        Result PollData(UniquePtr<StreamMessageData>& receivedMessageData, int32_t timeoutMS = 0);
		Result PollData(int32_t timeoutMS = 0);

        const UniquePtr<StreamMessageData>& GetLatestReceivedData() const { return m_ReceivedMessageData; }

        int64_t ToOffsetFromTail(int64_t offsetFromTail) const;

    private:

        mutable int32_t m_Partition;

        UniquePtr<RdKafka::Consumer> m_Consumer;

        // Locally cached data
        UniquePtr<StreamMessageData> m_ReceivedMessageData;
    };

}
#endif

