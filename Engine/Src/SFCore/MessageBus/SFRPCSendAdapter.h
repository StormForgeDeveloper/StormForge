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
        RPCSendAdapter(MessageEndpoint* pEndpoint)
            : m_Endpoint(pEndpoint)
            , m_Builder(pEndpoint->GetBuilder() ? 0 : 4096)
            , m_pExternalBuilder(pEndpoint->GetBuilder())
        {
        }

        flatbuffers::FlatBufferBuilder& GetBuilderForNew()
        {
            if (m_pExternalBuilder == nullptr)
            {
                m_Builder.Clear();
                return m_Builder;
            }
            else
            {
                m_pExternalBuilder->Clear();
                return *m_pExternalBuilder;
            }
        }

        Result Send(TransactionID transactionId, Result result, MessageID messageId, flatbuffers::FlatBufferBuilder& fbb)
        {
            Result hr;

            MessageHeader2 messageHeader;
            messageHeader.MessageId = messageId;
            messageHeader.TransactionId = transactionId;

            messageHeader.UpdateNWriteTo(fbb, result);

            const MessageHeader2* pMessageHeader = reinterpret_cast<const MessageHeader2*>(fbb.GetBufferPointer());
            return m_Endpoint->SendMsg(pMessageHeader);
        }
    };

} // SF

