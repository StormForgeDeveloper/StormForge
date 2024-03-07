////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message2
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "Net/SFMessage.h"
#include "Net/SFNetSystem.h"
#include "MessageBus/SFMessage2.h"
#include "MessageBus/SFMessageDelegateMap.h"


namespace SF
{
    void MessageDelegateMap::OnMessage(const MessageHeader* pMsgHeader)
    {
        if (pMsgHeader != nullptr) // if it hasn't consumed yet, call next callback
        {
            RecvMessageDelegates* pMessageDelegate = nullptr;
            m_RecvMessageDelegatesByMsgId.Find(pMsgHeader->msgID.GetMsgID(), pMessageDelegate);
            if (pMessageDelegate)
                pMessageDelegate->Invoke(pMsgHeader);
        }

    }


    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Network Message header2
    //

    MessageDelegateMap2::MessageDelegateMap2()
        : m_RecvMessageDelegatesByMsgId(GetSystemHeap())
    {
    }

    MessageDelegateMap2::~MessageDelegateMap2()
    {
        m_RecvMessageDelegatesByMsgId.CommitChanges();
        m_RecvMessageDelegatesByMsgId.ForeachOrder(0, (uint32_t)m_RecvMessageDelegatesByMsgId.size(), [](uint32_t, RecvMessageDelegates* pDelegate)
            {
                IHeap::Delete(pDelegate);
                return true;
            });
        m_RecvMessageDelegatesByMsgId.clear();
    }

    Result MessageDelegateMap2::OnMessage(const MessageHeader2* pMsgHeader)
    {
        Result hr;

        if (pMsgHeader != nullptr) // if it hasn't consumed yet, call next callback
        {
            RecvMessageDelegates* pMessageDelegate = nullptr;
            m_RecvMessageDelegatesByMsgId.Find(pMsgHeader->MessageId.GetMsgIDOnly(), pMessageDelegate);
            if (pMessageDelegate)
                pMessageDelegate->Invoke(pMsgHeader);
            else
                return ResultCode::NOT_EXIST;
        }


        return hr;
    }

} // SF
