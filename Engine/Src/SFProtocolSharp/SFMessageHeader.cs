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


using SF.Flat;
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Transactions;

#nullable enable

namespace SF
{
    
    [StructLayout(LayoutKind.Explicit, Size = 14)]
    public struct MessageHeader
    {
        [FieldOffset(0)] public MessageID MessageId; // ID & sequence
        [FieldOffset(4)] public TransactionID TransactionId; // Payload size
        [FieldOffset(12)] public UInt16 PayloadSize; // Payload size

        public void WriteHeader(Google.FlatBuffers.FlatBufferBuilder buffer)
        {
            // We can't use FlatBufferBuilder interface because we need to ignore alignment

            Google.FlatBuffers.ByteBuffer byteBuffer = buffer.DataBuffer;
            // Update size
            PayloadSize = (ushort)(byteBuffer.Length - byteBuffer.Position + Marshal.SizeOf<MessageHeader>());

            // Remember that flatbuffer store from end
            byteBuffer.Position -= sizeof(UInt16);
            byteBuffer.PutUshort(byteBuffer.Position, PayloadSize);

            byteBuffer.Position -= sizeof(ulong);
            byteBuffer.PutUlong(byteBuffer.Position, TransactionId.TransactionId);

            byteBuffer.Position -= sizeof(UInt32);
            byteBuffer.PutUint(byteBuffer.Position, MessageId.MessageIdRaw);
        }

        public void ReadHeader(Google.FlatBuffers.ByteBuffer buffer)
        {
            MessageId.MessageIdRaw = buffer.GetUint(0);
            TransactionId.TransactionId = buffer.GetUlong(4);
            PayloadSize = buffer.GetUshort(12);
            buffer.Position += Marshal.SizeOf<MessageHeader>();
        }
    }

}

#nullable restore
