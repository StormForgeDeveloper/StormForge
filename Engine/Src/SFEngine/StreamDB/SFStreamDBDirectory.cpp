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

#include "Online/StreamDB/SFStreamDB.h"
#include "StreamDB/SFStreamDBDirectory.h"
#include "Util/SFStringFormat.h"
#include "Net/SFConnectionTCP.h"
#include "Protocol/PlayInstanceMessageID.h"

//#include "Protocol/PlayInstanceRPCSendAdapter.h"
//#include "Protocol/PlayInstanceMsgClass.h"

#ifdef USE_STREAMDB

#include "librdkafka/rdkafkacpp.h"



namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBDirectory
	//

	StreamDBDirectory::StreamDBDirectory(IHeap& heap, const StringCrc32& directoryType, const StringCrc64& name)
		: EngineObject(&heap, name)
		, m_DirectoryType(directoryType)
	{

	}

	StreamDBDirectory::~StreamDBDirectory()
	{

	}

	Result StreamDBDirectory::Initialize(const String& serverAddress)
	{
		return ResultCode::SUCCESS;
	}

	Result StreamDBDirectory::RequestStreamList()
	{
		return ResultCode::NOT_IMPLEMENTED;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBDirectory
	//

	StreamDBDirectoryBroker::StreamDBDirectoryBroker(IHeap& heap)
		: StreamDBDirectory(heap, "StreamBroker"_crc, "StreamDBDirectoryBroker"_crc64)
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
		Result hr;
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

		// Using async tick for 
		SetTickGroup(EngineTaskTick::AsyncTick);

		return hr;
	}

	Result StreamDBDirectoryBroker::RequestStreamList()
	{
		if (m_Consumer == nullptr)
			return ResultCode::NOT_INITIALIZED;

		m_FindRequested = true;

		return ResultCode::SUCCESS;
	}

	Result StreamDBDirectoryBroker::RequestStreamListInternal()
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
			if ((*it)->err() == RdKafka::ERR_UNKNOWN_TOPIC_OR_PART)
			{
				SFLog(Net, Info, "Topic or partition doesn't exit. topic:{0}", (*it)->topic());
				continue;
			}

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

	Result StreamDBDirectoryBroker::OnTick(EngineTaskTick tick)
	{
		ScopeContext hr;

		super::OnTick(tick);

		if (m_FindRequested)
		{
			m_FindRequested = false;
			if (!RequestStreamListInternal())
			{
                m_ResultMessage = MessageData::NewMessage(GetHeap(), Message::PlayInstance::MID_GetStreamListRes, 1024);
                assert(!"FIXME");
				//Message::PlayInstance::GetStreamListRes::Create(m_ResultMessage->GetMessageHeader(), 0, ResultCode::NO_DATA_EXIST,
				//	ArrayView<const char*>());
			}
			else
			{
				DynamicArray<const char*> TopicList;
				for (auto& itString : m_TopicList)
					TopicList.push_back(itString.data());

                m_ResultMessage = MessageData::NewMessage(GetHeap(), Message::PlayInstance::MID_GetStreamListRes, 1024);
                assert(!"FIXME");
     //           Message::PlayInstance::GetStreamListRes::Create(m_ResultMessage->GetMessageHeader(), 0, ResultCode::SUCCESS,
					//TopicList);
			}
		}

		return hr;
	}

	Result StreamDBDirectoryBroker::PollEvent(Event& evt)
	{
		// Nothing to do at this moment
		return ResultCode::SUCCESS_FALSE;
	}

	Result StreamDBDirectoryBroker::PollMessage(MessageDataPtr& pIMsg)
	{
		pIMsg = std::forward<MessageDataPtr>(m_ResultMessage);

		return pIMsg != nullptr ? ResultCode::SUCCESS : ResultCode::NO_DATA_EXIST;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDBDirectoryClient
	//

	StreamDBDirectoryClient::StreamDBDirectoryClient(IHeap& heap)
		: StreamDBDirectory(heap, "StreamDirectoryDB"_crc, "StreamDBDirectoryClient"_crc64)
	{
	}

	StreamDBDirectoryClient::~StreamDBDirectoryClient()
	{
		if (m_ConnectionDirectory != nullptr)
		{
			m_ConnectionDirectory->DisconnectNRelease("StreamDBDirectoryClient Initializing");
			m_ConnectionDirectory = nullptr;
		}
	}

	Result StreamDBDirectoryClient::Initialize(const String& serverAddress)
	{
		if (m_ConnectionDirectory != nullptr)
		{
			m_ConnectionDirectory->DisconnectNRelease("StreamDBDirectoryClient Initializing");
			m_ConnectionDirectory = nullptr;
		}

		m_ConnectionDirectory = new(GetHeap()) Net::ConnectionTCPClient(GetHeap());

		Net::PeerInfo local(NetClass::Client, 0);
		Net::PeerInfo remote(NetClass::Server, NetAddress(serverAddress), 0);
		auto result = m_ConnectionDirectory->Connect(local, remote);
		if (!result)
		{
			m_ConnectionDirectory->DisconnectNRelease("StreamDBDirectoryClient Initializing");
			m_ConnectionDirectory = nullptr;
			return result;
		}

		m_ConnectionDirectory->SetTickGroup(EngineTaskTick::AsyncTick);

		return result;
	}

	Result StreamDBDirectoryClient::RequestStreamList()
	{
		if (m_ConnectionDirectory == nullptr)
			return ResultCode::NOT_INITIALIZED;

		switch (m_ConnectionDirectory->GetConnectionState())
		{
		case Net::ConnectionState::DISCONNECTING:
		case Net::ConnectionState::DISCONNECTED:
			return ResultCode::IO_DISCONNECTED;
		case Net::ConnectionState::CONNECTING:
			return ResultCode::IO_SYSNOTREADY;
		default:
			break;
		}

        assert(!"FIXME");
		//return PlayInstanceRPCSendAdapter(m_ConnectionDirectory->GetMessageEndpoint()).GetStreamListCmd(0, 0);
        return ResultCode::NOT_IMPLEMENTED;
	}

	Result StreamDBDirectoryClient::PollEvent(Event& evt)
	{
		if (m_ConnectionDirectory == nullptr || m_ConnectionDirectory->GetConnectionState() == Net::ConnectionState::DISCONNECTED)
			return ResultCode::NO_DATA_EXIST;

		Net::ConnectionEvent connEvent;
		while (m_ConnectionDirectory->DequeueConnectionEvent(connEvent))
		{
			switch (connEvent.Components.EventType)
			{
			case Net::ConnectionEvent::EVT_CONNECTION_RESULT:
				evt = connEvent.Components.hr ? Event::Connected : Event::ConnectionFailed;
				return ResultCode::SUCCESS;
			case Net::ConnectionEvent::EVT_DISCONNECTED:
				evt = Event::Disconnected;
				return ResultCode::SUCCESS;
			default:
				// Skip
				break;
			}
		}

		return ResultCode::NO_DATA_EXIST;
	}

	Result StreamDBDirectoryClient::PollMessage(MessageDataPtr& pIMsg)
	{
		if (m_ConnectionDirectory == nullptr || m_ConnectionDirectory->GetConnectionState() == Net::ConnectionState::DISCONNECTED)
			return ResultCode::NO_DATA_EXIST;


        Net::Connection::MessageItemReadPtr itemPtr = m_ConnectionDirectory->GetRecvMessageQueue().DequeueRead();
        if (itemPtr)
        {
            // TODO: change PollMessage interface
            const MessageHeader* pHeader = reinterpret_cast<const MessageHeader*>(itemPtr.data());
            pIMsg = MessageData::NewMessage(GetHeap(), pHeader->MessageId, pHeader->MessageSize, reinterpret_cast<const uint8_t*>(pHeader));
            return ResultCode::SUCCESS;
        }
        else
        {
            return ResultCode::NO_DATA_EXIST;
        }
	}
}

#endif
