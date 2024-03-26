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
using Google.FlatBuffers;

#nullable enable

namespace SF
{
    
    public struct MessageHeader
    {
        public MessageID MessageId; // ID & sequence
        public TransactionID TransactionId; // Payload size
        public Result TransactionResult;
        public UInt16 PayloadSize; // Payload size

        public void WriteHeader(Google.FlatBuffers.FlatBufferBuilder buffer)
        {
            // We can't use FlatBufferBuilder interface because we need to ignore alignment

            Google.FlatBuffers.ByteBuffer byteBuffer = buffer.DataBuffer;

            if (MessageId.Type == EMessageType.Result)
            {
                byteBuffer.PutInt(byteBuffer.Position, TransactionResult.Code); byteBuffer.Position -= sizeof(Int32);
            }

            // Update size
            PayloadSize = (ushort)(byteBuffer.Length - byteBuffer.Position + sizeof(UInt16) + sizeof(ulong) + sizeof(UInt32));

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

            if (MessageId.Type == EMessageType.Result)
            {
                TransactionResult.Code = buffer.GetInt(14);
                buffer.Position += sizeof(Int32);
            }
            else
            {
                TransactionResult.Code = 0;
            }
        }
    }

}

#nullable restore
