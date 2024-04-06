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
#include "Net/SFNetDef.h"

namespace SF
{

    class MemoryEndpoint : public MessageEndpoint
    {
    private:

        class FlatAllocator : public flatbuffers::Allocator
        {
            // Allocate `size` bytes of memory.
            virtual uint8_t* allocate(size_t size) override
            {
                return (uint8_t*)malloc(size);
            }

            // Deallocate `size` bytes of memory at `p` allocated by this allocator.
            virtual void deallocate(uint8_t* p, size_t size) override
            {
                free(p);
            }

            virtual uint8_t* reallocate_downward(uint8_t* old_p, size_t old_size,
                size_t new_size, size_t in_use_back,
                size_t in_use_front) override
            {
                assert(new_size > old_size);  // vector_downward only grows

                uint8_t* new_p = reinterpret_cast<uint8_t*>(realloc(old_p, new_size));

                memmove(new_p + new_size - in_use_back, old_p + old_size - in_use_back, in_use_back);

                return new_p;
            }

        };

        // Message allocator. basically same to original implementation except it uses realloc and memmove
        FlatAllocator m_FlatAllocator;

        // Builder for message build
        flatbuffers::FlatBufferBuilder m_Builder;

        // Last sent message. Because we manages FlatBufferBuilder, the last message will valid until next message build begins.
        const MessageHeader* m_LastMessage{};


    public:

        MemoryEndpoint()
            : m_Builder(4096, &m_FlatAllocator)
        {
        }

        ~MemoryEndpoint()
        {
            Clear();
        }

        void Clear();

        virtual flatbuffers::FlatBufferBuilder* GetBuilder() override { return &m_Builder; }

        const MessageHeader* GetLastMessage() const
        {
            return m_LastMessage;
        }

        virtual bool IsSameEndpoint(const EndpointAddress& messageEndpoint) override
        {
            return messageEndpoint.MessageServer == "localhost" && messageEndpoint.Channel == "0";
        }

        virtual Result SendMsg(const MessageHeader* messageData) override;
    };


} // SF

