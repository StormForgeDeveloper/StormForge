////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Message header
//	
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Transactions;

#nullable enable

namespace SF
{
    public static partial class MessageProtocol
    {
        public static readonly uint None = 0;
        public static readonly uint Generic = 1;

        public static readonly uint Login = 3;
        public static readonly uint Game = 4;
        public static readonly uint PlayInstance = 5;
        public static readonly uint Telemetry = 6;
        public static readonly uint Relay = 7;

        //public static readonly uint GameExt = 12;
        //public static readonly uint PlayInstanceExt = 13;

        // client max 100
        public static readonly uint ClientMax = 50;
    }

    public enum MessageType
    {
        NetCtrl,
        Event,
        Command,
        Result
    }

    [StructLayout(LayoutKind.Explicit, Size = 4)]
    public struct MessageID
    {
        [FieldOffset(0)] public UInt32 MessageIdRaw;

        const uint NET_SEQUENCE_BITS = 12;
        const uint NET_SEQUENCE_MASK = (1 << (int)NET_SEQUENCE_BITS) - 1;
        const uint NET_SEQUENCE_MAX_DIFF = NET_SEQUENCE_MASK >> 1;

        const uint NET_PROTOCOL_BITS = 7;
        const uint NET_PROTOCOL_SHIFT = sizeof(UInt32) * 8 - NET_PROTOCOL_BITS;
        const uint NET_PROTOCOL_MASK = ((uint)(1 << (int)NET_PROTOCOL_BITS) - 1) << (int)NET_PROTOCOL_SHIFT;

        const uint NET_CODE_BITS = 9;
        const uint NET_CODE_SHIFT = NET_PROTOCOL_SHIFT - NET_CODE_BITS;
        const uint NET_CODE_MASK = ((uint)(1 << (int)NET_CODE_BITS) - 1) << (int)NET_CODE_SHIFT;

        const uint NET_TYPE_BITS = 2;
        const uint NET_TYPE_SHIFT = NET_CODE_SHIFT - NET_TYPE_BITS;
        const uint NET_TYPE_MASK = ((uint)(1 << (int)NET_TYPE_BITS) - 1) << (int)NET_TYPE_SHIFT;

        const uint NET_RELIABILITY_BITS = 1;
        const uint NET_RELIABILITY_SHIFT = NET_TYPE_SHIFT - NET_RELIABILITY_BITS;
        const uint NET_RELIABILITY_MASK = ((uint)(1 << (int)NET_RELIABILITY_BITS) - 1) << (int)NET_RELIABILITY_SHIFT;

        const uint NET_BROADCAST_BITS = 1;
        const uint NET_BROADCAST_SHIFT = NET_RELIABILITY_SHIFT - NET_BROADCAST_BITS;
        const uint NET_BROADCAST_MASK = ((uint)(1 << (int)NET_BROADCAST_BITS) - 1) << (int)NET_BROADCAST_SHIFT;

        public uint ProtocolId => ((MessageIdRaw & NET_PROTOCOL_MASK) >> (int)NET_PROTOCOL_SHIFT);
        public uint CodeIndex => ((MessageIdRaw & NET_CODE_MASK) >> (int)NET_CODE_SHIFT);
        public MessageType Type => (MessageType)((MessageIdRaw & NET_TYPE_MASK) >> (int)NET_TYPE_SHIFT);
        public UInt32 IDOnly => MessageIdRaw & (~NET_SEQUENCE_MASK);
        public UInt32 Sequence => MessageIdRaw & NET_SEQUENCE_MASK;

        public MessageID(UInt32 messageRawId)
        {
            MessageIdRaw = messageRawId;
        }

        public static MessageID MakeMessageID(MessageType type, uint uiReliability, uint uiProtocol, uint uiCode)
        {
            uint uiBroadcast = 0;// deprecated
            return new MessageID()
            {
                MessageIdRaw = (uint)0
                    | ((uiProtocol << (int)NET_PROTOCOL_SHIFT) & NET_PROTOCOL_MASK)
                    | ((uiCode << (int)NET_CODE_SHIFT) & NET_CODE_MASK)
                    | (((uint)type << (int)NET_TYPE_SHIFT) & NET_TYPE_MASK)
                    | ((uiReliability << (int)NET_RELIABILITY_SHIFT) & NET_RELIABILITY_MASK)
                    | ((uiBroadcast << (int)NET_BROADCAST_SHIFT) & NET_BROADCAST_MASK)

            };
        }

        public override int GetHashCode()
        {
            return (int)MessageIdRaw;
        }

        public bool Equals(MessageID p)
        {
            return MessageIdRaw == p.MessageIdRaw;
        }
        public override bool Equals(object? obj)
        {
            if (obj == null)
                return false; 
            return MessageIdRaw == ((MessageID)obj).MessageIdRaw;
        }

        public static bool operator ==(MessageID c1, MessageID c2)
        {
            return c1.MessageIdRaw == c2.MessageIdRaw;
        }

        public static bool operator !=(MessageID c1, MessageID c2)
        {
            return c1.MessageIdRaw != c2.MessageIdRaw;
        }

        public new string ToString()
        {
            return $"(MID:{Type},{ProtocolId},{CodeIndex})";
        }

    }

}

#nullable restore
