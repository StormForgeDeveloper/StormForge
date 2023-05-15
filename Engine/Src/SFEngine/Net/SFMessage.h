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


namespace SF {
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message ID definition
	//


#define NET_SEQUENCE_BITS		12
#define NET_SEQUENCE_MASK		((1<<NET_SEQUENCE_BITS)-1)
#define NET_SEQUENCE_MAX_DIFF	(NET_SEQUENCE_MASK >> 1)

#if !defined(SWIG)
	// Because we pass net class in sequence id, NetClass::Max must be fit in the bits
	static_assert((uint)NetClass::Max <= NET_SEQUENCE_MASK, "Too big net class value");
#endif


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

    union MessageID
    {
        struct MessageIDComponent {
            // Seq - Sequence of the message
            uint32_t Sequence : NET_SEQUENCE_BITS;
            // Broadcast control bit, requested packet will be broadcasted through channel or spatial grid
            // 0 - Not Guaranteed
            // 1 - Reliable message.
            uint32_t Broadcast : 1; //
            // Reliability control bit - Only enabled when using TCP or connection based UDP
            // 0 - Not Guaranteed
            // 1 - Reliable message.
            uint32_t Reliability : 1;
            // Packet type
            // 00 - Net Control
            // 01 - Event
            // 10 - Command
            // 11 - Result
            uint32_t Type : 2;
            // MsgCode - Message ID, 0 is not used
            uint32_t MsgCode : 9;
            // Policy - Protocol Policy ID
            uint32_t Policy : 7;

            uint32_t : 0;
        } IDs;
        struct {
            uint32_t Sequence : NET_SEQUENCE_BITS;
            uint32_t MsgID : 32 - NET_SEQUENCE_BITS;
        } IDSeq;
        uint32_t ID;

        constexpr MessageID() : ID(0) {}
        constexpr MessageID(uint32_t uiID) : ID(uiID) {}
        constexpr MessageID(uint uiType, uint uiReliability, uint uiBroadcast, uint uiPolicy, uint uiCode)
            : IDs({ 0, uiBroadcast, uiReliability, uiType, uiCode, uiPolicy })
        {
        }

        uint32_t SetMessageID(uint uiType, uint uiReliability, uint uiBroadcast, uint uiPolicy, uint uiCode)
        {
            IDs.MsgCode = uiCode;
            IDs.Policy = uiPolicy;
            IDs.Broadcast = uiBroadcast;
            IDs.Reliability = uiReliability;
            IDs.Type = uiType;
            IDs.Sequence = 0;// uiSeq;

            return ID;
        }

        SF_FORCEINLINE void ValidateMessageID(uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode) const
        {
#if DEBUG
            MessageID Temp;
            Temp.SetMessageID(uiType, uiReliability, uiMobility, uiPolicy, uiCode);
            assert(Temp == *this);
#endif
        }

        void SetSequence(uint sequence) { IDSeq.Sequence = sequence; }

        // Only MsgID part, no sequence or length. result will be shifted
        constexpr uint GetMsgID() const { return IDSeq.MsgID; }

        // Remove sequence from message id
        constexpr uint GetMsgIDOnly() const { return static_cast<uint32_t>(IDSeq.MsgID) << NET_SEQUENCE_BITS; }

        constexpr operator uint32_t() const { return ID; }

    };

    static_assert(sizeof(uint32_t) == sizeof(MessageID), "Message ID should fit in 4 bytes");

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Constants
	//
	enum
	{
		MAX_MESSAGE_SIZE = (1 << 14) - 1,
		MAX_SUBFRAME_SIZE = 1200 - 64,

		MSGTYPE_NONE			= 0,	

		// Packet type
		MSGTYPE_NETCONTROL		= 0,	// Net Control
		MSGTYPE_EVENT			= 1,	// Event
		MSGTYPE_COMMAND			= 2,	// Command
		MSGTYPE_RESULT			= 3,	// Result

		MSGTYPE_RELIABLE		= 1,	// Reliable messages

		MSGTYPE_BROADCAST		= 1,	// broadcast mode
	};


	
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

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message base Header
	//
	struct MessageHeader
	{
		// Message ID
		MessageID	msgID;

		// Data length
		uint32_t		Length	: 16;

		// lower 16 bit of crc32 or sub frame sequence
		uint32_t		Crc32		: 16;

		// bit field termination
		uint32_t					: 0;

        constexpr size_t GetHeaderSize() const { return sizeof(MessageHeader); }

        SF_FORCEINLINE void SetIDNLen(uint id, uint msgLen)
        {
            msgID.ID = id;
            Length = msgLen;
        }

        SF_FORCEINLINE void* GetDataPtr() const
        {
            return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + GetHeaderSize());
        }

        SF_FORCEINLINE ArrayView<uint8_t> GetPayload() const
        {
            uint headerSize = (uint)GetHeaderSize();
            assert(Length >= headerSize);
            uint length = Length - headerSize;
            uint8_t* pDataPtr = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + headerSize);
            return ArrayView<uint8_t>(length, pDataPtr);
        }

        SF_FORCEINLINE uint GetPayloadSize() const
        {
            uint headerSize = (uint)GetHeaderSize();
            assert(Length >= headerSize);
            return Length - headerSize;
        }

        void UpdateChecksum();
        void UpdateChecksumNEncrypt();

        Result ValidateChecksum();
        Result ValidateChecksumNDecrypt();

        // Make a clone of this message
        MessageHeader* Clone(IHeap& heap);
    };

    static_assert((sizeof(uint32_t)*2) == sizeof(MessageHeader), "MessageHeader should fit in 8bytes");

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


    namespace Message
    {
        static constexpr size_t HeaderSize = sizeof(MessageHeader);
    } // Message
} // SF

#define SFNET_ALLOC_MESSAGE_FROM_STACK(messageBufferVar, messageSize) \
		MessageHeader* messageBufferVar = reinterpret_cast<MessageHeader*>(alloca(messageSize));\
        memset(messageBufferVar, 0, sizeof(MessageHeader)); \
        messageBufferVar->Length = messageSize;

