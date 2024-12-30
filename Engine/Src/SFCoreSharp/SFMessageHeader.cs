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
        // Uint32(MessageId), ulong(TransactionId), UInt16(PayloadSize).
        // UInt32(Result) is only when the message type is Result
        const int HeaderBaseSize = sizeof(UInt16) + sizeof(ulong) + sizeof(UInt32);

        public MessageID MessageId; // ID & sequence
        public TransactionID TransactionId; // transaction id
        public Result TransactionResult; // transaction result if it is result
        public UInt16 PayloadSize; // Payload size

        public void WriteHeader(Google.FlatBuffers.FlatBufferBuilder buffer)
        {
            // We can't use FlatBufferBuilder interface because we need to ignore alignment

            Google.FlatBuffers.ByteBuffer byteBuffer = buffer.DataBuffer;

            if (MessageId.Type == EMessageType.Result)
            {
                byteBuffer.Position -= sizeof(Int32);
                byteBuffer.PutInt(byteBuffer.Position, TransactionResult.Code);
            }

            // Update size
            PayloadSize = (ushort)(byteBuffer.Length - byteBuffer.Position + HeaderBaseSize);

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
            buffer.Position += HeaderBaseSize;

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
