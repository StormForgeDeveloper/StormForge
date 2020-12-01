////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c)  Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StreamDB Directory warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"

#include "StreamDB/SFStreamDB.h"
#include "StreamDB/SFStreamDBDirectory.h"
#include "String/SFStringFormat.h"

#ifdef USE_STREAMDB

#include "rdkafka/rdkafkacpp.h"



namespace SF
{




	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBDirectoryBase
	//

	StreamDBDirectoryBase::StreamDBDirectoryBase(const StringCrc64& name)
		: EngineObject(nullptr, name)
	{

	}

	StreamDBDirectoryBase::~StreamDBDirectoryBase()
	{

	}

	Result StreamDBDirectoryBase::Initialize(const String& serverAddress)
	{
		return ResultCode::SUCCESS;
	}

	Result StreamDBDirectoryBase::FindStream()
	{
		return ResultCode::NOT_IMPLEMENTED;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBDirectory
	//

	StreamDBDirectoryBroker::StreamDBDirectoryBroker()
		: StreamDBDirectoryBase("StreamDBDirectoryBroker"_crc)
	{

	}

	StreamDBDirectoryBroker::~StreamDBDirectoryBroker()
	{
		m_TopicHandle.reset();
		m_Config.reset();
		m_TopicConfig.reset();
		m_Consumer.reset();
	}

	Result StreamDBDirectoryBroker::Initialize(const String& brokers)
	{
		std::string errstr;

		m_Config.reset(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
		if (!m_Config)
			return ResultCode::OUT_OF_MEMORY;

		if (m_Config->set("bootstrap.servers", brokers.data(), errstr) != RdKafka::Conf::CONF_OK)
		{
			SFLog(Net, Error, "Kafka server configuration has failed: {0}", errstr);
			return ResultCode::INVALID_ARG;
		}

		m_TopicConfig.reset(RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC));

		if (!m_TopicConfig)
			return ResultCode::OUT_OF_MEMORY;

		if (m_Config->set("default_topic_conf", m_TopicConfig.get(), errstr) != RdKafka::Conf::CONF_OK)
		{
			SFLog(Net, Error, "Kafka configuration has failed: {0}", errstr);
			return ResultCode::INVALID_ARG;
		}

		RdKafka::Consumer* consumer = RdKafka::Consumer::create(m_Config.get(), errstr);
		if (!consumer)
		{
			SFLog(Net, Error, "Kafka consumer creation has failed: {0}", errstr);
			return ResultCode::OUT_OF_MEMORY;
		}

		m_Consumer.reset(consumer);

		return ResultCode::SUCCESS;
	}

	Result StreamDBDirectoryBroker::FindStream()
	{

		if (m_Consumer == nullptr)
			return ResultCode::NOT_INITIALIZED;

		RdKafka::Metadata* metadata = nullptr;
		int32_t metadataTimeout = 15 * 1000;
		RdKafka::ErrorCode errorCode = m_Consumer->metadata(true, nullptr, &metadata, metadataTimeout);
		if (errorCode != RdKafka::ErrorCode::ERR_NO_ERROR)
		{
			SFLog(Net, Error, "Kafka getting metadata has failed: {0}", RdKafka::err2str(errorCode));
			return ResultCode::FAIL;
		}

		if (metadata == nullptr)
		{
			SFLog(Net, Error, "Kafka getting metadata has failed: nullptr returned");
			return ResultCode::UNEXPECTED;
		}

		SFLog(Net, Debug, "Metadata for brokerId:{0}, {1}", metadata->orig_broker_id(), metadata->orig_broker_name());

		m_TopicList.Clear();

		// Iterate topics
		RdKafka::Metadata::TopicMetadataIterator it;
		for (it = metadata->topics()->begin();
			it != metadata->topics()->end();
			++it)
		{
			if ((*it)->err() != RdKafka::ERR_NO_ERROR)
			{
				SFLog(Net, Debug, "Topic metadata error, topic:{0}, {1}", (*it)->topic(), err2str((*it)->err()));
				continue;
			}

			SFLog(Net, Debug, "Topic metadata, topic:{0}", (*it)->topic());

			m_TopicList.push_back((*it)->topic().c_str());
		}

		return ResultCode::SUCCESS;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBDirectoryClient
	//

	StreamDBDirectoryClient::StreamDBDirectoryClient()
		: StreamDBDirectoryBase("StreamDBDirectoryClient"_crc)
	{

	}

	StreamDBDirectoryClient::~StreamDBDirectoryClient()
	{

	}

	Result StreamDBDirectoryClient::Initialize(const String& serverAddress)
	{
		// TODO
		return ResultCode::NOT_IMPLEMENTED;
	}

	Result StreamDBDirectoryClient::FindStream()
	{
		// TODO
		return ResultCode::NOT_IMPLEMENTED;
	}


}

#endif
