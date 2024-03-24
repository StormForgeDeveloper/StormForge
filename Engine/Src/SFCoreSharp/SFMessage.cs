////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

#nullable enable

namespace SF
{

    public class SFMessage : SFObject
    {
        MessageID m_MessageId;
        TransactionID m_TransactionId;

        Google.FlatBuffers.ByteBuffer m_byteBuffer;

        public SFMessage(MessageID messageID, TransactionID transactionId, uint payloadSize, IntPtr payloadPtr)
        {
            m_MessageId = messageID;
            m_TransactionId = transactionId;

            // TODO: for performance
            //unsafe
            //{
            //    var span = new Span<byte>((void*)payloadPtr, (int)payloadSize);
            //    m_byteBuffer = new Google.FlatBuffers.ByteBuffer(span, 0);
            //}

            var buffer = new byte[payloadSize];
            Marshal.Copy(payloadPtr, buffer, 0, buffer.Length);
            var readBuffer = new SF.Flat.ReadByteArrayAllocator(buffer, 0, buffer.Length);
            m_byteBuffer = new Google.FlatBuffers.ByteBuffer(readBuffer, 0);

        }

        public SFMessage(MessageID messageID, TransactionID transactionId, ArraySegment<byte> payloadData)
        {
            m_MessageId = messageID;
            m_TransactionId = transactionId;

            if (payloadData.Array == null)
                throw new Exception("Null pointer");

            var readBuffer = new SF.Flat.ReadByteArrayAllocator(payloadData.Array, payloadData.Offset, payloadData.Count);
            m_byteBuffer = new Google.FlatBuffers.ByteBuffer(readBuffer, 0);
        }

        public SFMessage()
        {
            var readBuffer = new Google.FlatBuffers.ByteArrayAllocator(new byte[0]);
            m_byteBuffer = new Google.FlatBuffers.ByteBuffer(readBuffer, 0);
        }

        public MessageID GetMessageID()
        {
            return m_MessageId;
        }

        public TransactionID GetTransactionID()
        {
            return m_TransactionId;
        }

    }
}

#nullable restore
