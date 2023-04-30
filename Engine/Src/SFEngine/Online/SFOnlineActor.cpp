////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online actor
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Online/SFOnlineActor.h"



namespace SF
{
    OnlineActorComponentInitializer* OnlineActorComponentInitializer::stm_InitializerHead{};

    OnlineActorComponentInitializer::OnlineActorComponentInitializer()
    {
        pNext = stm_InitializerHead;
        stm_InitializerHead = this;
    }

    OnlineActorComponentInitializer::~OnlineActorComponentInitializer()
    {
        OnlineActorComponentInitializer** ppPrev = &stm_InitializerHead;
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

    Result OnlineActorComponentInitializer::CreateComponentsFor(OnlineActor* actor)
    {
        for (OnlineActorComponentInitializer* pCur = stm_InitializerHead; pCur; pCur = pCur->pNext)
        {
            OnlineActorComponent* newComponent = pCur->Create(actor);
            actor->AddComponent(newComponent);
        }

        return ResultCode::SUCCESS;
    }


    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	OnlineActorComponent
    // 

    OnlineActorComponent::OnlineActorComponent(StringCrc32 name)
        : Component(name)
    {

    }

    OnlineActorComponent::~OnlineActorComponent()
    {

    }


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineActor
	// 



    OnlineActor::OnlineActor(ActorID actorId)
        : m_ComponentManager(GetEngineHeap())
    {

        OnlineActorComponentInitializer::CreateComponentsFor(this);
        m_ComponentManager.InitializeComponents();
    }

    OnlineActor::~OnlineActor()
    {
        m_ComponentManager.ClearComponents();
    }

    void OnlineActor::SetMovement(const ActorMovement& movement)
    {
        if (m_Movement == movement)
            return;

        m_Movement = movement;
    }

    void OnlineActor::OnComponentData(StringCrc32 name, const Array<const uint8_t>& data)
    {
        OnlineActorComponent* pComponent = m_ComponentManager.GetComponent<OnlineActorComponent>(name);
        if (pComponent)
        {
            pComponent->OnComponentData(data);
        }
    }

    void OnlineActor::TickUpdate()
    {
        m_ComponentManager.TickUpdate();
    }

}
