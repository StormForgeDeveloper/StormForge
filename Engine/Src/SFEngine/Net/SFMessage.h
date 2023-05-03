////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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


namespace SF {
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message ID definition
	//

	//
	//  Bit assignment of messageID
	//    2  1 1 1      7                 9                  11
	//   1 0 9 8 7  6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1  0 9 8 7 6 5 4 3 2 1 0
	//  +---+-+-+-+---------------+--------------------+----------------------+
	//  | T |G|M|E|   Policy      |       MsgCode      |        Seq           |
	//  +---+-+-+-+---------------+--------------------+----------------------+
	//
	//  where
	//
	//      T - Packet type
	//          00 - Net Control
	//          01 - Event
	//          10 - Command
	//          11 - Result
	//
	//      G - Reliability control bit - Only enabled when using TCP or connection based UDP
	//          0 - Not Guaranteed
	//          1 - Reliable message.
	//
	//      Encrypted
	//      Mobile - Mobility
	//      Policy - Protocol Policy ID
	//      MsgCode - Message ID, 0 is not used
	//      Seq - Sequence of the message
	//

#define NET_SEQUENCE_BITS		11
#define NET_SEQUENCE_MASK		((1<<NET_SEQUENCE_BITS)-1)
#define NET_SEQUENCE_MAX_DIFF	(NET_SEQUENCE_MASK >> 1)

#if !defined(SWIG)
	// Because we pass net class in sequence id, NetClass::Max must be fit in the bits
	static_assert((uint)NetClass::Max <= NET_SEQUENCE_MASK, "Too big net class value");
#endif

	union MessageID
	{
		struct MessageIDComponent {
			uint32_t Sequence : NET_SEQUENCE_BITS;
			uint32_t Encrypted		: 1;
			uint32_t Mobile			: 1;
			uint32_t Reliability	: 1;
			uint32_t Type			: 2;
			uint32_t MsgCode		: 9;
			uint32_t Policy			: 7;
			uint32_t				: 0;
		} IDs;
		struct {
			uint32_t Sequence : NET_SEQUENCE_BITS;
			uint32_t MsgID	    : 21;
		} IDSeq;
		uint32_t ID;

		constexpr MessageID() : ID(0) {}
		//inline tag_MessageID( const tag_MessageID& src );
		MessageID( uint32_t uiID ) : ID(uiID) {}
		constexpr MessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode );

		uint32_t SetMessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode );

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
		uint GetMsgID() const { return IDSeq.MsgID; }

		uint GetMsgIDOnly() const { return static_cast<uint32_t>(IDSeq.MsgID) << NET_SEQUENCE_BITS; }
#ifndef SWIG
		operator uint32_t() const { return ID; }
#endif
	} ;



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

		MSGTYPE_MOBILE			= 1,	// Mobile protocol
	};


	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Interface
	//

#pragma pack(push, 4)


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

        SF_FORCEINLINE size_t GetHeaderSize() const { return sizeof(MessageHeader) + (msgID.IDs.Mobile ? sizeof(uint64_t) : 0); }
        SF_FORCEINLINE uint64_t GetPeerID() const
        {
            return msgID.IDs.Mobile ?
                    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(this) + sizeof(MessageHeader))
                    :
                    0;
        }
        SF_FORCEINLINE void SetPeerID(uint64_t peerId)
        {
            if (msgID.IDs.Mobile)
            {
                *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(this) + sizeof(MessageHeader)) = peerId;
            }
        }

		void SetIDNLen(uint id, uint msgLen);

        SF_FORCEINLINE void* GetDataPtr() const
        {
            return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + GetHeaderSize());
        }
    };

#pragma pack(pop)




#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

    inline constexpr MessageID::MessageID(uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode)
        : IDs({ 0, 0, uiMobility, uiReliability, uiType, uiCode, uiPolicy })
    {
    }

    inline uint32_t MessageID::SetMessageID(uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode)
    {
        IDs.MsgCode = uiCode;
        IDs.Policy = uiPolicy;
        IDs.Mobile = uiMobility;
        IDs.Encrypted = 0;
        IDs.Reliability = uiReliability;
        IDs.Type = uiType;
        IDs.Sequence = 0;// uiSeq;

        return ID;
    }

    inline void MessageHeader::SetIDNLen(uint id, uint msgLen)
    {
        msgID.ID = id;
        Length = msgLen;
    }

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


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    namespace Message
    {
        static constexpr size_t HeaderSize = sizeof(MessageHeader);
        static constexpr size_t MobileHeaderSize = sizeof(MessageHeader) + sizeof(uint64_t);
    } // Message
} // SF




