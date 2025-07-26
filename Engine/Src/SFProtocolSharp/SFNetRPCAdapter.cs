////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using SF;
using System;
using System.Diagnostics;

#nullable enable

namespace SF.Net
{
 

	public class RPCAdapter
	{
 
		protected SF.IEndpoint? m_Endpoint = null;

		public SF.IEndpoint? Endpoint { get { return m_Endpoint; } set { m_Endpoint = value; } }
        public SF.EntityUID DestEntityUID { get; set; } = SF.EntityUID.Empty;

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

        public virtual Result SendMessage(MessageID messageId, Google.FlatBuffers.FlatBufferBuilder builder, int packetOffset,
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

            var messageHeader = new SF.MessageHeader()
            {
                MessageId = messageId,
                TransactionId = transactionId,
                TransactionResult = result,
            };

            // try to returning message to destination target directly
            hr = m_Endpoint.SendMessageWithRouting(ref messageHeader, builder);

            m_Endpoint.HandleSentMessage(hr, transactionId, messageId, callback);

            return hr;
        }

    };

} // namespace SF.Net

#nullable restore
