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
        [AOT.MonoPInvokeCallback(typeof(SFConnection.SET_MESSAGE_FUNCTION))]
#endif
        static public void MessageParseSetEventCallback(SFConnection.EventTypes eventType, int result, SFConnection.ConnectionState state)
        {
            System.Diagnostics.Debug.Assert(stm_Event.EventType == SFConnection.EventTypes.EVT_NONE);
            stm_Event.EventType = eventType;
            stm_Event.HResult.Code = result;
            stm_Event.State = state;
        }

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SFConnection.ON_MESSAGE_FUNCTION))]
#endif
        static public void OnMessageData(MessageID messageID, TransactionID transactionId, uint payloadSize, IntPtr payloadPtr)
        {
            SFMessage message = new SFMessage(messageID, transactionId, payloadSize, payloadPtr);
            stm_MessageDequeueConnection?.MessageRouter.HandleRecvMessage(message);
        }

        // IOS IL2CPP doesn't support native callback of instance, so it has to be static
        static public byte[] MessageBuffer = new byte[32 * 1024];
        static public SFConnection? stm_MessageDequeueConnection = null;
        static public object stm_ParsingLock = new object();
        static public SFConnection.Event stm_Event;


    }
}

#nullable restore
