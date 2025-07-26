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
using System.Transactions;

#nullable enable

namespace SF
{
    public abstract class IEndpoint
    {
        public SF.EntityUID DestEntityUID { get; set; } = SF.EntityUID.Empty;

        public abstract TransactionID NewTransactionID();
        public virtual Result SendMessageWithRouting(ref SF.MessageHeader messageHeader, Google.FlatBuffers.FlatBufferBuilder builder)
        {
            if (messageHeader.MessageId.MessageType == EMessageType.Result && messageHeader.TransactionId.EntityUID != 0)
            {
                // Service::ServerConfig->ServerEndpointAddress.Channel
                EntityUID requesterUID = new EntityUID(messageHeader.TransactionId.EntityUID);
                string destTopic = $"ent_{requesterUID.GetServerEntityUID().UID:X8}";
                messageHeader.DestUID = requesterUID;
                return SendMessage(destTopic, ref messageHeader, builder);
            }
            else if (DestEntityUID.IsValid)
            {
                string destTopic = $"ent_{DestEntityUID.GetServerEntityUID().UID:X8}";
                // Set interserver destination so that it can be routed to the correct entity.
                messageHeader.MessageId.SetInterServer(true);
                messageHeader.DestUID = DestEntityUID;
                return SendMessage(destTopic, ref messageHeader, builder);
            }
            else
            {
                return SendMessage(ref messageHeader, builder);
            }

        }
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
