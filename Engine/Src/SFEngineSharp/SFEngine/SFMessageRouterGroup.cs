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
using System.Runtime.InteropServices;
using System.Text;

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

            m_MessageRouters.Add(router);
        }

        public void Remove(SFIMessageRouter router)
        {
            m_MessageRouters.Remove(router);
        }

        public override void RegisterMessageHandler(int messageID, int priority, Action<SFMessage> handler)
        {
            throw new NotImplementedException("We don't support directly registering message handlers");
        }

        // This method will clear whole message handler with same priority
        public override void UnregisterMessageHandler(int messageID, int priority)
        {
            throw new NotImplementedException("We don't support directly unregistering message handlers");
        }

        // This method will clear whole message handler with same priority
        public override void UnregisterMessageHandler(int messageID, Action<SFMessage> handler)
        {
            throw new NotImplementedException("We don't support directly unregistering message handlers");
        }

        public override void HandleSentMessage(int result, int messageID)
        {
            foreach (var router in m_MessageRouters)
                router.HandleSentMessage(result, messageID);
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
