////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : network message router group
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;

#nullable enable

namespace SF
{


    public class SFMessageRouterGroup : SFIMessageRouter
    {
        List<SFIMessageRouter> m_MessageRouters = new List<SFIMessageRouter>();

        public override void Dispose()
        {
            foreach (var router in m_MessageRouters)
                router.Dispose();
        }

        public void AddUnique(SFIMessageRouter router)
        {
            if (m_MessageRouters.Contains(router))
                return;

			for (var i = 0; i < m_MessageRouters.Count; i++)
			{
				if (m_MessageRouters[i].GroupPriority < router.GroupPriority)
				{
					m_MessageRouters.Insert(i, router);
					return;
				}
			}
			m_MessageRouters.Add(router);
		}

        public void Remove(SFIMessageRouter router)
        {
            m_MessageRouters.Remove(router);
        }

        public override void RegisterMessageHandler(MessageID messageID, int priority, Action<SFMessage> handler)
        {
            throw new NotImplementedException("We don't support directly registering message handlers");
        }

        // This method will clear whole message handler with same priority
        public override void UnregisterMessageHandler(MessageID messageID, int priority)
        {
            throw new NotImplementedException("We don't support directly unregistering message handlers");
        }

        // This method will clear whole message handler with same priority
        public override void UnregisterMessageHandler(MessageID messageID, Action<SFMessage> handler)
        {
            throw new NotImplementedException("We don't support directly unregistering message handlers");
        }

        public override void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback)
        {
            foreach (var router in m_MessageRouters)
                router.HandleSentMessage(result, transId, messageID, callback);
        }

        /// <summary>
        /// Handle received message
        /// </summary>
        /// <param name="message">message to handle</param>
        public override void HandleRecvMessage(SFMessage message)
        {
            foreach (var router in m_MessageRouters)
                router.HandleRecvMessage(message);

        }
    }
}

#nullable restore
