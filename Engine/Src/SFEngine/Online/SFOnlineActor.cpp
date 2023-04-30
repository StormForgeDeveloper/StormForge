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
    DoubleLinkedListStaticT<OnlineActorComponentInitializer*> OnlineActorComponentInitializer::stm_ComponentInitializers{};

    OnlineActorComponentInitializer::OnlineActorComponentInitializer()
        : super(this)
    {
        stm_ComponentInitializers.Add(this);
    }

    OnlineActorComponentInitializer::~OnlineActorComponentInitializer()
    {
        stm_ComponentInitializers.Remove(this);
    }

    Result OnlineActorComponentInitializer::CreateComponentsFor(OnlineActor* actor)
    {
        for (auto& itComponentInitializer : stm_ComponentInitializers)
        {
            OnlineActorComponent* newComponent = itComponentInitializer->Create(actor);
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
