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
    struct MessageHeader
    {
        // Message ID
        MessageID	MessageId;

        // request transaction id
        TransactionID TransactionId;

        // Data length including header
        uint16_t MessageSize = 0;

        uint16_t GetHeaderSize() const
        {
            uint16_t headerSize = static_cast<uint16_t>(sizeof(MessageHeader));

            if (MessageId.IsInterServer())
                headerSize += sizeof(EntityUID);

            if (MessageId.GetMessageType() == EMessageType::Result)
                headerSize += sizeof(Result);

            return headerSize;
        }

        // Read and return result if it is transaction result 
        Result GetTransactionResult() const
        {
            uintptr_t offset = reinterpret_cast<uintptr_t>(this) + sizeof(MessageHeader);

            if (MessageId.IsInterServer())
                offset += sizeof(EntityUID);

            if (MessageId.GetMessageType() == EMessageType::Result)
            {
                return *reinterpret_cast<const Result*>(offset);
            }
            else
                return ResultCode::SUCCESS_FALSE;
        }

        void SetDestinationEntityUID(const EntityUID& requester)
        {
            uintptr_t offset = reinterpret_cast<uintptr_t>(this) + sizeof(MessageHeader);

            if (MessageId.IsInterServer())
            {
                *reinterpret_cast<EntityUID*>(offset) = requester;
            }
        }

        const EntityUID& GetDestinationEntityUID() const
        {
            uintptr_t offset = reinterpret_cast<uintptr_t>(this) + sizeof(MessageHeader);

            if (MessageId.IsInterServer())
            {
                return *reinterpret_cast<const EntityUID*>(offset);
            }
            else
            {
                return EntityUID::Invalid;
            }
        }

        constexpr MessageID GetMessageID() const { return MessageId.GetMessageID(); }

        constexpr uint16_t GetSequence() const
        {
            return MessageId.GetSequence();
        }

        SF_FORCEINLINE void SetSequence(uint sequence)
        {
            MessageId.IDSeq.Sequence = sequence;
        }

        SF_FORCEINLINE void SetIDNLen(uint id, uint msgLen)
        {
            MessageId.ID = id;
            MessageSize = (decltype(MessageSize))msgLen;
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
        MessageHeader* Clone(IHeap& heap);

        // Update size and write to flat packet builder
        void UpdateNWriteTo(::flatbuffers::FlatBufferBuilder& packetBuilder, Result result);

    };

    static_assert((sizeof(uint16_t) * 7) == sizeof(MessageHeader), "MessageHeader should fit");

#pragma pack(pop)

} // SF

