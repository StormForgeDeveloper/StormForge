////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net connection classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Delegate/SFEventDelegate.h"
#include "Container/SFDualSortedMap.h"
#include "MessageBus/SFMessageHeader.h"

namespace SF {


    // Message delegates by MessageID
    class  MessageDelegateMap
    {
    public:
        using RecvMessageDelegates = EventDelegateList<const MessageHeader*>;

        MessageDelegateMap()
            : m_RecvMessageDelegatesByMsgId(GetSystemHeap())
        {
        }

        ~MessageDelegateMap()
        {
            m_RecvMessageDelegatesByMsgId.CommitChanges();
            m_RecvMessageDelegatesByMsgId.ForeachOrder(0, (uint32_t)m_RecvMessageDelegatesByMsgId.size(), [](uint32_t, RecvMessageDelegates* pDelegate)
                {
                    IHeap::Delete(pDelegate);
                    return true;
                });
            m_RecvMessageDelegatesByMsgId.clear();
        }

        void AddMessageDelegateUnique(uintptr_t context, uint32_t msgId, RecvMessageDelegates::CallableType&& func)
        {
            RecvMessageDelegates* pDelegateList = nullptr;
            if (!m_RecvMessageDelegatesByMsgId.Find(msgId, pDelegateList))
            {
                pDelegateList = new(GetSystemHeap()) RecvMessageDelegates(GetSystemHeap());
                m_RecvMessageDelegatesByMsgId.Insert(msgId, pDelegateList);
                m_RecvMessageDelegatesByMsgId.CommitChanges();
            }

            pDelegateList->AddDelegateUnique(uintptr_t(context), Forward<RecvMessageDelegates::CallableType>(func));
        }

        void RemoveMessageDelegate(uintptr_t context, uint32_t msgId)
        {
            RecvMessageDelegates* pDelegateList = nullptr;
            if (m_RecvMessageDelegatesByMsgId.Find(msgId, pDelegateList))
            {
                pDelegateList->RemoveDelegateAll(uintptr_t(context));
            }
        }

        void OnMessage(const MessageHeader* pMsgHeader);

    private:
        // Received message handler map by msgId
        DualSortedMap<uint32_t, RecvMessageDelegates*> m_RecvMessageDelegatesByMsgId;
    };




	// Message delegates by MessageID
    class  MessageDelegateMap2
    {
    public:
        using RecvMessageDelegates = EventDelegateList<const MessageHeader2*>;

        MessageDelegateMap2();
        ~MessageDelegateMap2();

        void AddMessageDelegateUnique(uintptr_t context, uint32_t msgId, RecvMessageDelegates::CallableType&& func)
        {
            RecvMessageDelegates* pDelegateList = nullptr;
            if (!m_RecvMessageDelegatesByMsgId.Find(msgId, pDelegateList))
            {
                pDelegateList = new(GetSystemHeap()) RecvMessageDelegates(GetSystemHeap());
                m_RecvMessageDelegatesByMsgId.Insert(msgId, pDelegateList);
                m_RecvMessageDelegatesByMsgId.CommitChanges();
            }

            pDelegateList->AddDelegateUnique(uintptr_t(context), Forward<RecvMessageDelegates::CallableType>(func));
        }

        void RemoveMessageDelegate(uintptr_t context, uint32_t msgId)
        {
            RecvMessageDelegates* pDelegateList = nullptr;
            if (m_RecvMessageDelegatesByMsgId.Find(msgId, pDelegateList))
            {
                pDelegateList->RemoveDelegateAll(uintptr_t(context));
            }
        }

        Result OnMessage(const MessageHeader2* pMsgHeader);

    private:
        // Received message handler map by msgId
        DualSortedMap<uint32_t, RecvMessageDelegates*> m_RecvMessageDelegatesByMsgId;
    };

} // namespace SF
