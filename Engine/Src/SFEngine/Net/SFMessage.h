////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message Definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFAssert.h"
#include "Container/SFArray.h"
#include "MessageBus/SFMessageHeader.h"

namespace SF {
	


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Constants
	//
    constexpr int MAX_MESSAGE_SIZE = (1 << 14) - 1;
	constexpr int MAX_SUBFRAME_SIZE = 1200 - 128;

	constexpr int MSGTYPE_NONE			= 0;

	constexpr int MSGTYPE_RELIABLE		= 1;	// Reliable messages
	constexpr int MSGTYPE_BROADCAST		= 1;	// broadcast mode


	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Interface
	//

#pragma pack(push, 4)

    // packet for mobile
    struct PacketHeader
    {
        uint64_t PeerId;
    };


    namespace Message
    {
        constexpr size_t HeaderSize = sizeof(MessageHeader);
    }
#pragma pack(pop)


    // Message sequence
    struct MessageSequence
    {
        uint Sequence{};

        MessageSequence() = default;
        MessageSequence(uint InSequence) : Sequence(InSequence) {}
        MessageSequence(const MessageSequence& src) : Sequence(src.Sequence) {}


        static inline INT Difference(uint seq1, uint seq2)
        {
            const int SEQDIFF_MAX = NET_SEQUENCE_MASK >> 1;
            const int SEQDIFF_MIN = (-SEQDIFF_MAX - 1);

            //NET_SEQUEUCN_BITS
            seq1 = NET_SEQUENCE_MASK & seq1;
            seq2 = NET_SEQUENCE_MASK & seq2;
            auto diff = (INT)(seq1 - seq2);
            if (diff > SEQDIFF_MAX)
                diff -= NET_SEQUENCE_MASK + 1;
            else if (diff < SEQDIFF_MIN)
                diff += NET_SEQUENCE_MASK + 1;

            return diff;
        }

        static inline uint Normalize(uint seq)
        {
            seq = NET_SEQUENCE_MASK & seq;

            return seq;
        }

        void NormalizeInline() { Sequence = Normalize(Sequence); }

        operator uint() const { return Sequence; }
        MessageSequence& operator ++() { Sequence++; return *this; }
        friend MessageSequence operator ++(const MessageSequence& op) { return op.Sequence + 1; }

        bool operator == (const MessageSequence& src) const { return ((Sequence - src.Sequence) & NET_SEQUENCE_MASK) == 0; }
        bool operator != (const MessageSequence& src) const { return ((Sequence - src.Sequence) & NET_SEQUENCE_MASK) != 0; }

        int operator - (const MessageSequence& op) { return Difference(Sequence, op.Sequence); }
    };


} // SF

#define SFNET_ALLOC_MESSAGE_FROM_STACK(messageBufferVar, messageSize) \
		MessageHeader* messageBufferVar = reinterpret_cast<MessageHeader*>(alloca(messageSize));\
        memset(messageBufferVar, 0, sizeof(MessageHeader)); \
        messageBufferVar->MessageSize = messageSize;

