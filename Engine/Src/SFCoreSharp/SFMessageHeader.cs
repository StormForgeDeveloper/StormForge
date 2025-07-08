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
        public EntityUID DestUID; // When MessageId.InterServer=true, this is the request destination UID
        public UInt16 PayloadSize; // Payload size

        public void WriteHeader(Google.FlatBuffers.FlatBufferBuilder buffer)
        {
            // We can't use FlatBufferBuilder interface because we need to ignore alignment

            Google.FlatBuffers.ByteBuffer byteBuffer = buffer.DataBuffer;

            if (MessageId.MessageType == EMessageType.Result)
            {
                byteBuffer.Position -= sizeof(Int32);
                byteBuffer.PutInt(byteBuffer.Position, TransactionResult.Code);
            }

            if (MessageId.InterServer)
            {
                byteBuffer.Position -= sizeof(UInt32);
                byteBuffer.PutUint(byteBuffer.Position, DestUID.UID);
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
            var offset = buffer.Position;
            MessageId.MessageIdRaw = buffer.GetUint(offset);
            TransactionId.TransactionId = buffer.GetUlong(offset + 4);
            PayloadSize = buffer.GetUshort(offset + 12);
            buffer.Position += HeaderBaseSize;

            if (MessageId.InterServer)
            {
                DestUID.UID = buffer.GetUint(buffer.Position);
                buffer.Position += sizeof(UInt32);
            }
            else
            {
                DestUID.UID = 0;
            }

            if (MessageId.MessageType == EMessageType.Result)
            {
                TransactionResult.Code = buffer.GetInt(buffer.Position);
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
