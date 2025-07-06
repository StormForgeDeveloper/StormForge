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
    public abstract class IEndpoint
    {
        public abstract TransactionID NewTransactionID();
        public abstract Result SendMessage(ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder);
        public abstract Result SendMessage(string destTopic, ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder);
        public abstract void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback = null);
        public virtual void HandleSentMessage(Result result, TransactionID transId, string topic, MessageID messageID, Action<SFMessage>? callback = null)
        {
            HandleSentMessage(result, transId, messageID, callback);
        }

    }

    public class MemoryEndpoint : IEndpoint
    {
        ulong m_TransactionIdGen = 1;
        public TransactionID LastTransactionId { get; private set; } = TransactionID.Empty;
        public ArraySegment<byte>? LastMessage { get; private set; }


        public override TransactionID NewTransactionID()
        {
            return new TransactionID(m_TransactionIdGen++);
        }

        public override Result SendMessage(ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder)
        {
            messageHeader.WriteHeader(builder);

            var buf = builder.DataBuffer;
            var segment = buf.ToArraySegment(buf.Position, buf.Length - buf.Position);

            LastTransactionId = messageHeader.TransactionId;
            LastMessage = segment;

            HandleSentMessage(ResultCode.SUCCESS, messageHeader.TransactionId, string.Empty, messageHeader.MessageId);

            return ResultCode.SUCCESS;
        }

        public override Result SendMessage(string destTopic, ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder)
        {
            messageHeader.WriteHeader(builder);

            var buf = builder.DataBuffer;
            var segment = buf.ToArraySegment(buf.Position, buf.Length - buf.Position);

            LastTransactionId = messageHeader.TransactionId;
            LastMessage = segment;

            HandleSentMessage(ResultCode.SUCCESS, messageHeader.TransactionId, destTopic, messageHeader.MessageId);

            return ResultCode.SUCCESS;
        }

        public override void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback = null)
        {
        }

    }
}

#nullable restore
