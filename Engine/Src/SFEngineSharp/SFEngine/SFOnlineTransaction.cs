////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online Transaction
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;


#nullable enable

namespace SF
{
    public class OnlineTransactionIDGenerator
    {
        // Request Id generation serial
        int m_RequestIdGen = 0;
        public TransactionID NewTransactionID()
        {
            int newId = Interlocked.Increment(ref m_RequestIdGen);
            if (newId == 0)
            {
                newId = Interlocked.Increment(ref m_RequestIdGen);
            }
            return new TransactionID() { TransactionId = (uint)newId };
        }


    }
}

#nullable restore
