////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : MessageBus message header Definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Net/SFMessageID.h"
#include "Types/SFEngineTypedefs.h"
#include "Container/SFArray.h"
#include "flatbuffers/flatbuffer_builder.h"

namespace SF
{
	
    class RPCSendAdapter
    {
    protected:
        // Endpoint
        MessageEndpoint* m_Endpoint;
        // builder 
        flatbuffers::FlatBufferBuilder m_Builder;
        // External builder 
        flatbuffers::FlatBufferBuilder* m_pExternalBuilder{};

    public:
        // Constructor
        RPCSendAdapter(MessageEndpoint* pEndpoint);

        // Get builder for new message
        flatbuffers::FlatBufferBuilder& GetBuilderForNew();

        // Send message
        Result Send(TransactionID transactionId, Result result, MessageID messageId, flatbuffers::FlatBufferBuilder& fbb);
    };

} // SF

