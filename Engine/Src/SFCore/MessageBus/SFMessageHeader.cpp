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
#include "MessageBus/SFMessageHeader.h"


namespace SF
{

    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Network Message header2
    //

    MessageHeader2* MessageHeader2::Clone(IHeap& heap)
    {
        MessageHeader2* pNewHeader = reinterpret_cast<MessageHeader2*>(heap.Alloc(MessageSize));
        if (pNewHeader)
        {
            memcpy(pNewHeader, this, MessageSize);
        }

        return pNewHeader;
    }

    void MessageHeader2::UpdateNWriteTo(::flatbuffers::FlatBufferBuilder& packetBuilder, Result result)
    {
        if (MessageId.GetMessageType() == MessageType::Result)
        {
            packetBuilder.PushBytes((const uint8_t*)&result, sizeof(Result));
        }

        // Update size
        MessageSize = (uint16_t)(packetBuilder.GetSize() + sizeof(MessageHeader2));

        packetBuilder.PushBytes((const uint8_t*)this, sizeof(MessageHeader2));
    }


} // SF
