////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message2
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Net/SFMessage.h"
#include "Net/SFNetSystem.h"
#include "MessageBus/SFRPCSendAdapter.h"


namespace SF
{

    ////////////////////////////////////////////////////////////////////////////////
    //
    //	RPCSendAdapter
    //

    RPCSendAdapter::RPCSendAdapter(MessageEndpoint* pEndpoint)
        : m_Endpoint(pEndpoint)
        , m_Builder((pEndpoint && pEndpoint->GetBuilder()) ? 0 : 4096)
        , m_pExternalBuilder(pEndpoint ? pEndpoint->GetBuilder() : nullptr)
    {
    }

    flatbuffers::FlatBufferBuilder& RPCSendAdapter::GetBuilderForNew()
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

    Result RPCSendAdapter::Send(TransactionID transactionId, Result result, MessageID messageId, flatbuffers::FlatBufferBuilder& fbb)
    {
        Result hr;

        MessageHeaderWithBuffer messageHeader;
        messageHeader.MessageId = messageId;
        messageHeader.TransactionId = transactionId;

        SFCheckPtr(System,m_Endpoint);

        if (m_Endpoint->GetDestinationEntityUID().IsValid())
        {
            messageHeader.MessageId.IDs.InterServer = 1;
            messageHeader.SetDestinationEntityUID(m_Endpoint->GetDestinationEntityUID());
        }

        messageHeader.UpdateNWriteTo(fbb, result);

        const MessageHeader* pMessageHeader = reinterpret_cast<const MessageHeader*>(fbb.GetBufferPointer());
        return m_Endpoint->SendMsg(pMessageHeader);
    }

} // SF
