////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : network message router
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;

#nullable enable

namespace SF
{


    public abstract class SFIMessageRouter : IDisposable
    {
		public int GroupPriority { get; private set; }

		public SFIMessageRouter(int groupPriority = 0)
		{
			GroupPriority = groupPriority;
		}

		/// <summary>
		/// Message event argument
		/// </summary>
		public delegate void delMessageIDEventHandler(Result sendResult, TransactionID transId, MessageID messageID, Action<SFMessage>? callback);
        public delegate void delMessageEventHandler(SFMessage message);

        public virtual void Dispose() { }

        /// <summary>
        /// When a message data is sent
        /// </summary>
        public delMessageIDEventHandler? OnMessageSent = null;

        /// <summary>
        /// When a message data is dequeued for processing
        /// </summary>
        public delMessageEventHandler? OnMessageProcessing = null;


        /// <summary>
        /// Register message handler
        /// </summary>
        /// <param name="messageID"></param>
        /// <param name="priority"></param>
        /// <param name="handler"></param>
        public virtual void RegisterMessageHandler(MessageID messageID, int priority, Action<SFMessage> handler) { }
        public virtual void RegisterMessageHandler(MessageID messageID, Action<SFMessage> handler) { RegisterMessageHandler(messageID, 0, handler); }

        /// <summary>
        /// Unregister whole message handlers of the messageID and priority. This method will clear whole message handlers with same priority
        /// </summary>
        /// <param name="messageID">Message ID</param>
        /// <param name="priority">Priority</param>
        public virtual void UnregisterMessageHandler(MessageID messageID, int priority) { }

        /// <summary>
        /// Unregister message handler. 
        /// </summary>
        /// <param name="messageID">Message ID</param>
        /// <param name="priority">Priority</param>
        public virtual void UnregisterMessageHandler(MessageID messageID, Action<SFMessage> handler) { }

        /// <summary>
        /// Callback called when a message is sent
        /// </summary>
        /// <param name="result">Send result</param>
        /// <param name="messageID">Message ID</param>
        public virtual void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback) { }


        /// <summary>
        /// Handle received message
        /// </summary>
        /// <param name="message">message to handle</param>
        public virtual void HandleRecvMessage(SFMessage message) { }
    }
}

#nullable restore
