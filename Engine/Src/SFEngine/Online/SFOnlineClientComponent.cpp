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
#include "Online/SFOnlineClient.h"
#include "Online/SFOnlineClientComponent.h"


namespace SF
{

    OnlineClientComponentInitializer* OnlineClientComponentInitializer::stm_InitializerHead{};

    OnlineClientComponentInitializer::OnlineClientComponentInitializer()
    {
        pNext = stm_InitializerHead;
        stm_InitializerHead = this;
    }

    OnlineClientComponentInitializer::~OnlineClientComponentInitializer()
    {
        // TODO: StaticLinkedList's thread sync has virtual and doesn't let the class instance be in zero initializer area.
        //  Fixme later.
        OnlineClientComponentInitializer** ppPrev = &stm_InitializerHead;
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

    Result OnlineClientComponentInitializer::CreateComponentsFor(OnlineClient* client)
    {
        for (OnlineClientComponentInitializer* pCur = stm_InitializerHead; pCur; pCur = pCur->pNext)
        {
            OnlineClientComponent* newComponent = pCur->Create(client);
            client->AddComponent(newComponent);
        }
        return ResultCode::SUCCESS;
    }



    OnlineClientComponent::OnlineClientComponent(StringCrc32 componentId, OnlineClient* pOwner)
        : super(componentId)
        , m_Owner(pOwner)
    {

    }

    OnlineClientComponent::~OnlineClientComponent()
    {

    }

}
