////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using SF;

#nullable enable

namespace SF.Net
{
 

	public class RPCAdapter
	{
 
		protected SF.IEndpoint? m_Endpoint = null;

		public SF.IEndpoint? Endpoint { get { return m_Endpoint; } set { m_Endpoint = value; } }


		public RPCAdapter()
		{
		}

        public RPCAdapter(SF.IEndpoint endpoint)
        {
            m_Endpoint = endpoint;
        }

        public TransactionID NewTransactionID()
        {
            return m_Endpoint?.NewTransactionID() ?? TransactionID.Empty;
        }

        public Result SendMessage(MessageID messageId, Google.FlatBuffers.FlatBufferBuilder builder, int packetOffset,
            TransactionID transactionId = default(TransactionID),
            Result result = default(Result),
            Action<SFMessage>? callback = null)
        {
            Result hr = ResultCode.SUCCESS;

            if (m_Endpoint == null)
            {
                return ResultCode.NET_NOT_CONNECTED;
            }

            builder.Finish(packetOffset);

            var packetHeader = new SF.MessageHeader()
            {
                MessageId = messageId,
                TransactionId = transactionId,
                TransactionResult = result,
            };
            packetHeader.WriteHeader(builder);

            var buf = builder.DataBuffer;
            var segment = buf.ToArraySegment(buf.Position, buf.Length - buf.Position);

            hr = m_Endpoint.SendMessage(transactionId, segment);
            m_Endpoint.HandleSentMessage(hr, transactionId, messageId, callback);

            return hr;
        }

    };

} // namespace SF.Net

#nullable restore
