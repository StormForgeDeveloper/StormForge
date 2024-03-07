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
#include "Net/SFMessage.h"
#include "flatbuffers/flatbuffer_builder.h"

namespace SF {
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Interface
	//

#pragma pack(push, 2)

    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Network Packet Message base Header
    //
    struct MessageHeader2
    {
        // Message ID
        MessageID	MessageId;

        // request transaction id
        TransactionID TransactionId;

        // Data length including header
        uint32_t MessageSize = 0;

        constexpr size_t GetHeaderSize() const { return sizeof(MessageHeader2); }

        SF_FORCEINLINE void SetIDNLen(uint id, uint msgLen)
        {
            MessageId.ID = id;
            MessageSize = msgLen;
        }

        SF_FORCEINLINE void* GetPayloadPtr() const
        {
            return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + GetHeaderSize());
        }

        SF_FORCEINLINE ArrayView<uint8_t> GetPayload() const
        {
            uint headerSize = (uint)GetHeaderSize();
            assert(MessageSize >= headerSize);
            uint length = MessageSize - headerSize;
            uint8_t* pDataPtr = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + headerSize);
            return ArrayView<uint8_t>(length, pDataPtr);
        }

        SF_FORCEINLINE uint GetPayloadSize() const
        {
            uint headerSize = (uint)GetHeaderSize();
            assert(MessageSize >= headerSize);
            return MessageSize - headerSize;
        }

        // Make a clone of this message
        MessageHeader2* Clone(IHeap& heap);

        // Update size and write to flat packet builder
        void UpdateNWriteTo(::flatbuffers::FlatBufferBuilder& packetBuilder);

        void ReadFrom(const Array<uint8_t>& recvData);
    };

    static_assert((sizeof(uint64_t) * 2) == sizeof(MessageHeader2), "MessageHeader should fit");

#pragma pack(pop)

} // SF

