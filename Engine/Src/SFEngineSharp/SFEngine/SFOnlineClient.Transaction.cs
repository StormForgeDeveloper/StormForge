////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : OnlineClient interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using SF.Net;
#if UNITY_IOS
using AOT;
#endif

#nullable enable

namespace SF
{
    public partial class OnlineClient : SFObject
    {

        // pending request callback router
        class OnlineRequestCallbackRouter : SFIMessageRouter
        {
            Dictionary<ulong, Action<SFMessage>?> m_PendingRequests = new();

            public OnlineRequestCallbackRouter()
                : base(1000)
            {

            }

            public void AddPendingRequest(TransactionID transId, Action<SFMessage>? callback)
            {
                if (transId.TransactionId == 0 || callback ==  null)
                {
                    return;
                }

                m_PendingRequests[transId.TransactionId] = callback;
            }

            public override void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback)
            {
                //UnityEngine.Debug.Log($"SendSharp messageId:{messageID.ToString()}, transactionId:{transId.ToString()}");

                if (result.IsFailure || transId.TransactionId == 0 || callback == null)
                {
                    return;
                }

                m_PendingRequests[transId.TransactionId] = callback;
            }


            public override void HandleRecvMessage(SFMessage message)
            {
                TransactionID transactionId = message.TransactionId;

                if (message.TransactionResult.IsFailure)
                {
                    MessageID messageId = message.MessageId;
                    SF.Log.Error($"Server request has failed, transactionId:{transactionId.ToString()}, messageId:{messageId.ToString()}");
                }

                //UnityEngine.Debug.Log($"RecvSharp messageId:{message.MessageId.ToString()}, transactionId:{transactionId.ToString()}, result:{message.TransactionResult}");

                Action<SFMessage>? outCallback = null;
                m_PendingRequests.Remove(transactionId.TransactionId, out outCallback);
                if (outCallback != null)
                {
                    outCallback(message);
                }
            }
        }

        OnlineRequestCallbackRouter m_RequestCallbackRouter = new();

        OnlineTransactionIDGenerator m_OnlineTransactionIDGenerator = new();
        public TransactionID NewTransactionID()
        {
            return m_OnlineTransactionIDGenerator.NewTransactionID();
        }


    }
}

#nullable restore
