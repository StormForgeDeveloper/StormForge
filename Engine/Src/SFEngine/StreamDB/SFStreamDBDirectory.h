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
#include "EngineObject/SFEngineObject.h"
#include "Net/SFConnection.h"


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
	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBDirectory
	//

	class StreamDBDirectory : public EngineObject
	{
	public:

		using super = EngineObject;

		enum class Event
		{
			Connected,
			ConnectionFailed,
			Disconnected
		};


	public:

        StreamDBDirectory(IHeap& heap, const StringCrc32& directoryType, const StringCrc64& name);
		virtual ~StreamDBDirectory();

		StringCrc32 GetDirectoryType() const { return m_DirectoryType; }

		virtual Result Initialize(const String& serverAddress);

		virtual Result RequestStreamList();

		virtual Result PollEvent(Event& evt) { return ResultCode::NO_DATA_EXIST; }
		virtual Result PollMessage(MessageDataPtr& pMsg) { return ResultCode::NO_DATA_EXIST; }


		const Array<String>& GetStreamList() const { return m_TopicList; }

	protected:

		StringCrc32 m_DirectoryType;

		DynamicArray<String> m_TopicList;
	};

	////////////////////////////////////////////////////////////////////////////////////////////
    //
    //  class StreamDBDirectoryBroker
    //

	class StreamDBDirectoryBroker : public StreamDBDirectory
	{
	public:

		using super = StreamDBDirectory;

	public:

        StreamDBDirectoryBroker(IHeap& heap);
        virtual ~StreamDBDirectoryBroker();

		virtual Result Initialize(const String& serverAddress) override;

		virtual Result RequestStreamList() override;

		Result OnTick(EngineTaskTick tick) override;

		virtual Result PollEvent(Event& evt) override;
		virtual Result PollMessage(MessageDataPtr& pIMsg) override;

	private:

		Result RequestStreamListInternal();


	private:

		UniquePtr<RdKafka::Conf> m_Config;
		UniquePtr<RdKafka::Conf> m_TopicConfig;

		UniquePtr<RdKafka::Topic> m_TopicHandle;
		UniquePtr<RdKafka::Consumer> m_Consumer;

		bool m_FindRequested = false;
		MessageDataPtr m_ResultMessage;
	};


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBDirectoryClient
	//

	class StreamDBDirectoryClient : public StreamDBDirectory
	{
	public:

		using super = StreamDBDirectory;

	public:

        StreamDBDirectoryClient(IHeap& heap);
		virtual ~StreamDBDirectoryClient();

		virtual Result Initialize(const String& serverAddress) override;

		virtual Result RequestStreamList() override;

		virtual Result PollEvent(Event& evt) override;
		virtual Result PollMessage(MessageDataPtr& pIMsg) override;

	private:

		Net::ConnectionPtr m_ConnectionDirectory;

	};




}
#endif

