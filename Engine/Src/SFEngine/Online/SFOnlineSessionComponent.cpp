////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online client component
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Online/SFOnlineSession.h"
#include "Online/SFOnlineSessionComponent.h"


namespace SF
{

    OnlineSessionComponentInitializer* OnlineSessionComponentInitializer::stm_InitializerHead{};

    OnlineSessionComponentInitializer::OnlineSessionComponentInitializer()
    {
        pNext = stm_InitializerHead;
        stm_InitializerHead = this;
    }

    OnlineSessionComponentInitializer::~OnlineSessionComponentInitializer()
    {
        // TODO: StaticLinkedList's thread sync has virtual and doesn't let the class instance be in zero initializer area.
        // Fixme later.
        OnlineSessionComponentInitializer** ppPrev = &stm_InitializerHead;
        while (*ppPrev)
        {
            if ((*ppPrev) == this)
            {
                (*ppPrev) = pNext;
                break;
            }

            ppPrev = &((*ppPrev)->pNext);
        }
    }

    Result OnlineSessionComponentInitializer::CreateComponentsFor(OnlineSession* client)
    {
        for (OnlineSessionComponentInitializer* pCur = stm_InitializerHead; pCur; pCur = pCur->pNext)
        {
            OnlineSessionComponent* newComponent = pCur->Create(client);
            client->AddComponent(newComponent);
        }
        return ResultCode::SUCCESS;
    }



    OnlineSessionComponent::OnlineSessionComponent(StringCrc32 componentId, OnlineSession* pOwner)
        : super(componentId)
        , m_Owner(pOwner)
    {

    }

    OnlineSessionComponent::~OnlineSessionComponent()
    {

    }

}
