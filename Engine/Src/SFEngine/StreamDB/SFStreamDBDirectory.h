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
#include "EngineObject/SFEngineObject.h"


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

	class StreamDBDirectoryBase : public EngineObject
	{
	public:

		using super = EngineObject;

	public:

        StreamDBDirectoryBase(const StringCrc64& name);
		virtual ~StreamDBDirectoryBase();

		virtual Result Initialize(const String& serverAddress);

		virtual Result FindStream();

		const Array<String>& GetStreamList() const { return m_TopicList; }

	protected:

		DynamicArray<String> m_TopicList;
	};

	////////////////////////////////////////////////////////////////////////////////////////////
    //
    //  class StreamDBDirectoryBroker
    //

	class StreamDBDirectoryBroker : public StreamDBDirectoryBase
	{
	public:

		using super = StreamDBDirectoryBase;

	public:

        StreamDBDirectoryBroker();
        virtual ~StreamDBDirectoryBroker();

		virtual Result Initialize(const String& serverAddress) override;

		virtual Result FindStream() override;


	private:

		UniquePtr<RdKafka::Conf> m_Config;
		UniquePtr<RdKafka::Conf> m_TopicConfig;

		UniquePtr<RdKafka::Topic> m_TopicHandle;
		UniquePtr<RdKafka::Consumer> m_Consumer;
	};


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class StreamDBDirectoryClient
	//

	class StreamDBDirectoryClient : public StreamDBDirectoryBase
	{
	public:

		using super = StreamDBDirectoryBase;

	public:

        StreamDBDirectoryClient();
		virtual ~StreamDBDirectoryClient();

		virtual Result Initialize(const String& serverAddress) override;

		virtual Result FindStream() override;


	private:

	};




}
#endif

