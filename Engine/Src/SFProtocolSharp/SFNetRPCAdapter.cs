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
using System.Runtime.InteropServices;
using SF;
using Google.FlatBuffers;

#nullable enable

namespace SF.Net
{
 

	public class RPCAdapter
	{
 
		protected SF.SFConnection? m_Connection = null;

		public SF.SFConnection? Connection { get { return m_Connection; } set { m_Connection = value; } }


		public RPCAdapter()
		{
		}

        public RPCAdapter(SF.SFConnection connection)
        {
            m_Connection = connection;
        }

        public TransactionID NewTransactionID()
        {
            return m_Connection?.NewTransactionID() ?? TransactionID.Empty;
        }

        public Result SendMessage(MessageID messageId, Google.FlatBuffers.FlatBufferBuilder builder, int packetOffset, TransactionID transactionId = default(TransactionID), Action<SFMessage>? callback = null)
        {
            Result hr = new Result();

            if (m_Connection == null)
            {
                return ResultCode.NET_NOT_CONNECTED;
            }

            builder.Finish(packetOffset);

            var packetHeader = new SF.MessageHeader()
            {
                MessageId = messageId,
                TransactionId = transactionId
            };
            packetHeader.WriteHeader(builder);

            var buf = builder.DataBuffer;
            var segment = buf.ToArraySegment(buf.Position, buf.Length - buf.Position);

            hr = m_Connection.SendMessage(transactionId, segment);
            m_Connection.HandleSentMessage(hr, transactionId, messageId, callback);

            return hr;
        }

    };

} // namespace SF.Net

#nullable restore
