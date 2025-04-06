////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

#nullable enable

namespace SF
{

    static public class SFMessageParsingUtil
    {

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SFConnection.ON_MESSAGE_FUNCTION))]
#endif
        static public void OnMessageData(MessageID messageID, TransactionID transactionId, Result result, uint payloadSize, IntPtr payloadPtr)
        {
            SFMessage message = new SFMessage(messageID, transactionId, result, payloadSize, payloadPtr);
            stm_MessageDequeueConnection?.MessageRouter.HandleRecvMessage(message);
        }

        // IOS IL2CPP doesn't support native callback of instance, so it has to be static
        static public SFConnection? stm_MessageDequeueConnection = null;
        static public object stm_ParsingLock = new object();
    }
}

#nullable restore
