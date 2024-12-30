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
using System.Collections.Generic;
using System.Text;

#nullable enable

namespace SF
{
    public interface IEndpoint
    {
        public TransactionID NewTransactionID();
        public Result SendMessage(ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder);
        public void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback = null);

    }

    public class MemoryEndpoint : IEndpoint
    {
        ulong m_TransactionIdGen = 1;
        public TransactionID LastTransactionId { get; private set; } = TransactionID.Empty;
        public ArraySegment<byte>? LastMessage { get; private set; }


        public TransactionID NewTransactionID()
        {
            return new TransactionID(m_TransactionIdGen++);
        }

        public Result SendMessage(ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder)
        {
            messageHeader.WriteHeader(builder);

            var buf = builder.DataBuffer;
            var segment = buf.ToArraySegment(buf.Position, buf.Length - buf.Position);

            LastTransactionId = messageHeader.TransactionId;
            LastMessage = segment;
            return ResultCode.SUCCESS;
        }

        public void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback = null)
        {
        }

    }
}

#nullable restore
