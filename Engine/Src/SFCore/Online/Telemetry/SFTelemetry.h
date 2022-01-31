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

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class StreamDB
	//

    class Telemetry : public SharedObject
    {
    public:




    public:

        Telemetry();
        virtual ~Telemetry();


        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0);

	};

}

