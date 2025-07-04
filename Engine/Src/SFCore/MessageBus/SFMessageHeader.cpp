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

    MessageHeader* MessageHeader::Clone(IHeap& heap)
    {
        MessageHeader* pNewHeader = reinterpret_cast<MessageHeader*>(heap.Alloc(MessageSize));
        if (pNewHeader)
        {
            memcpy(pNewHeader, this, MessageSize);
        }

        return pNewHeader;
    }

    void MessageHeader::UpdateNWriteTo(::flatbuffers::FlatBufferBuilder& packetBuilder, Result result)
    {
        if (MessageId.GetMessageType() == EMessageType::Result)
        {
            packetBuilder.PushBytes((const uint8_t*)&result, sizeof(Result));
        }

        // Update size
        MessageSize = (uint16_t)(packetBuilder.GetSize() + sizeof(MessageHeader));

        packetBuilder.PushBytes((const uint8_t*)this, sizeof(MessageHeader));
    }


} // SF
