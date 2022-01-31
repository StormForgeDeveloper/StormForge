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




namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class TelemetryComponent
	//

    class TelemetryComponent : public SharedObject
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

        TelemetryComponent();
        virtual ~TelemetryComponent();


        virtual Result Initialize(const String& brokers, const String& topic, int32_t partition = 0);

        
    };



}
