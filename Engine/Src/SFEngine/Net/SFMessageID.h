////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message ID Definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"


namespace SF {
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message ID definition
	//
    constexpr uint NET_PROTOCOL_BITS = 7;

    constexpr uint NET_SEQUENCE_BITS = 12;
    constexpr uint NET_SEQUENCE_MASK = (1 << NET_SEQUENCE_BITS) - 1;
    constexpr uint NET_SEQUENCE_MAX_DIFF = NET_SEQUENCE_MASK >> 1;

    constexpr uint NET_ID_MASK = ~NET_SEQUENCE_MASK;

    enum class MessageType : uint8_t
    {
        NetCtrl,
        Event,
        Command,
        Result
    };


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
            // Server internal
            // 0 - None
            // 1 - Server internal traffic
            uint32_t InterServer : 1; //
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
            // Protocol ID
            uint32_t Protocol : NET_PROTOCOL_BITS;

            uint32_t : 0;
        } IDs;
        struct {
            uint32_t Sequence : NET_SEQUENCE_BITS;
            uint32_t MesssageIdPart : 32 - NET_SEQUENCE_BITS;
        } IDSeq;
        uint32_t ID;

        MessageType GetMessageType() const { return (MessageType)IDs.Type; }

        constexpr MessageID() : ID(0) {}
        constexpr MessageID(uint32_t uiID) : ID(uiID) {}
        constexpr MessageID(MessageType type, uint uiReliability, uint uiInterServer, uint uiProtocol, uint uiCode)
            : IDs({ 0, uiInterServer, uiReliability, (uint)type, uiCode, uiProtocol })
        {
        }

        constexpr MessageID(MessageType type, uint uiReliability, uint uiProtocol, uint uiCode)
            : IDs({ 0, 0, uiReliability, (uint)type, uiCode, uiProtocol })
        {
        }

        uint32_t SetMessageID(MessageType type, uint uiReliability, uint uiInterServer, uint uiProtocol, uint uiCode)
        {
            IDs.MsgCode = uiCode;
            IDs.Protocol = uiProtocol;
            IDs.InterServer = uiInterServer;
            IDs.Reliability = uiReliability;
            IDs.Type = (uint)type;
            IDs.Sequence = 0;// uiSeq;

            return ID;
        }

        SF_FORCEINLINE void ValidateMessageID(MessageType uiType, uint uiReliability, uint uiMobility, uint uiProtocol, uint uiCode) const
        {
#if DEBUG
            MessageID Temp;
            Temp.SetMessageID(uiType, uiReliability, uiMobility, uiProtocol, uiCode);
            assert(Temp == *this);
#endif
        }

        void SetSequence(uint sequence) { IDSeq.Sequence = sequence; }

        // Remove sequence from message id
        constexpr uint GetMessageID() const { return ID & NET_ID_MASK; }

        constexpr uint16_t GetSequence() const { return IDSeq.Sequence; }

        constexpr operator uint32_t() const { return ID; }

    };

    static_assert(sizeof(uint32_t) == sizeof(MessageID), "Message ID should fit in 4 bytes");

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

} // SF
