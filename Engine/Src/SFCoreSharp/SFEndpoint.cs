////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
#if UNITY_IOS
using AOT;
#endif

#nullable enable

namespace SF
{
    interface IEndpoint
    {
        public Result SendMessage(TransactionID transactionId, ArraySegment<byte> segment);
        public void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback = null);

    }

    public class MemoryEndpoint : IEndpoint
    {
        public TransactionID LastTransactionId { get; private set; }
        public ArraySegment<byte> LastMessage { get; private set; }

        public Result SendMessage(TransactionID transactionId, ArraySegment<byte> segment)
        {
            LastTransactionId = transactionId;
            LastMessage = segment;
            return ResultCode.SUCCESS;
        }

        public void HandleSentMessage(Result result, TransactionID transId, MessageID messageID, Action<SFMessage>? callback = null)
        {
        }

    }
}

#nullable restore
