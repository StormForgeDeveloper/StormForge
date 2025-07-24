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
#include "MessageBus/SFMessageHeader.h"
#include "MessageBus/SFMessageDelegateMap.h"


namespace SF
{
    void MessageDelegateMap::OnMessage(const MessageHeader* pMsgHeader)
    {
        if (pMsgHeader != nullptr) // if it hasn't consumed yet, call next callback
        {
            RecvMessageDelegates* pMessageDelegate = nullptr;
            m_RecvMessageDelegatesByMsgId.Find(pMsgHeader->GetMessageID(), pMessageDelegate);
            if (pMessageDelegate)
                pMessageDelegate->Invoke(pMsgHeader);
        }

    }


    ////////////////////////////////////////////////////////////////////////////////
    //
    //	Network Message header2
    //

    MessageDelegateMap2::MessageDelegateMap2()
    {
    }

    MessageDelegateMap2::~MessageDelegateMap2()
    {
        m_RecvMessageDelegatesByMsgId.CommitChanges();
        m_RecvMessageDelegatesByMsgId.ForeachOrder(0, (uint32_t)m_RecvMessageDelegatesByMsgId.size(), [](uint32_t, RecvMessageDelegates* pDelegate)
            {
                delete (pDelegate);
                return true;
            });
        m_RecvMessageDelegatesByMsgId.clear();
    }

    Result MessageDelegateMap2::OnMessage(const MessageHeader* pMsgHeader)
    {
        Result hr;

        if (pMsgHeader != nullptr) // if it hasn't consumed yet, call next callback
        {
            RecvMessageDelegates* pMessageDelegate = nullptr;
            m_RecvMessageDelegatesByMsgId.Find(pMsgHeader->GetMessageID(), pMessageDelegate);
            if (pMessageDelegate)
                pMessageDelegate->Invoke(pMsgHeader);
            else
                return ResultCode::NOT_EXIST;
        }


        return hr;
    }

} // SF
