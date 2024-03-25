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
using System.Collections.Generic;

#nullable enable

namespace SF
{

    public class SFMessageRouter : SFIMessageRouter, IDisposable
    {
        class PriorityComparer<TKey> : IComparer<TKey>
            where TKey : IComparable
        {
            public int Compare(TKey? x, TKey? y)
            {
                if (x == null && y == null)
                    return 1;

                if (x == null || y == null)
                    return -1;

                int result = x.CompareTo(y);

                if (result == 0)
                    return 1;   // Handle equality as being greater
                else
                    return result;
            }
        }
        // Message handler map
        Dictionary<MessageID, SortedList<int, Action<SFMessage>>> m_MessageHandlerMap = new ();



        public SFMessageRouter(int groupPriority = 0)
			: base(groupPriority)
        {
        }

		public void Clear()
		{
			m_MessageHandlerMap.Clear();
		}

        public override void Dispose()
        {
            m_MessageHandlerMap.Clear();
        }

        public override void RegisterMessageHandler(MessageID messageID, int priority, Action<SFMessage> handler)
        {
            SortedList<int, Action<SFMessage>>? handlerList = null;
            lock(m_MessageHandlerMap)
            {
                if (!m_MessageHandlerMap.TryGetValue(messageID, out handlerList))
                {
                    handlerList = new SortedList<int, Action<SFMessage>>(new PriorityComparer<int>());
                    m_MessageHandlerMap.Add(messageID, handlerList);
                }
            }

            lock (handlerList)
            {
                handlerList.Add(priority, handler);
            }
        }

        // This method will clear whole message handler with same priority
        public override void UnregisterMessageHandler(MessageID messageID, int priority)
        {
            SortedList<int, Action<SFMessage>>? handlerList = null;
            lock (m_MessageHandlerMap)
            {
                if (!m_MessageHandlerMap.TryGetValue(messageID, out handlerList))
                {
                    // nothing to unregister
                    return;
                }
            }

            lock (handlerList)
            {
                handlerList.Remove(priority);
            }
        }

        // This method will clear whole message handler with same priority
        public override void UnregisterMessageHandler(MessageID messageID, Action<SFMessage> handler)
        {
            SortedList<int, Action<SFMessage>>? handlerList = null;
            lock (m_MessageHandlerMap)
            {
                if (!m_MessageHandlerMap.TryGetValue(messageID, out handlerList))
                {
                    // nothing to unregister
                    return;
                }
            }

            lock (handlerList)
            {
                var values = handlerList.Values;
                for (int iAction = 0; iAction < handlerList.Count;)
                {
                    var action = values[iAction];
                    if (action == handler)
                        handlerList.RemoveAt(iAction);
                    else
                        iAction++;
                }
            }
        }

        public override void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback)
        {
            if (OnMessageSent != null) OnMessageSent(result, transId, messageID, callback);
        }

        /// <summary>
        /// Handle received message
        /// </summary>
        /// <param name="message">message to handle</param>
        public override void HandleRecvMessage(SFMessage message)
        {
            if (OnMessageProcessing != null)
                OnMessageProcessing(message);

            SortedList<int, Action<SFMessage>>? handlerList = null;
            lock (m_MessageHandlerMap)
            {
                m_MessageHandlerMap.TryGetValue(message.MessageId, out handlerList);
            }

            if (handlerList != null)
            {
                lock (handlerList)
                {
                    foreach (var handler in handlerList)
                    {
                        handler.Value(message);
                    }
                }
            }

        }
    }
}

#nullable restore
