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

#pragma once

#include "SFTypedefs.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "Container/SFDoubleLinkedList.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Audio/SFAudioService.h"
#include "Component/SFComponent.h"

namespace SF
{
    class OnlineActor;
    class OnlineActorComponent;

    /////////////////////////////////////////////////////////////////////////////////////
    // Online actor component initializer
    class OnlineActorComponentInitializer
    {
    public:
        OnlineActorComponentInitializer();
        virtual ~OnlineActorComponentInitializer();

        virtual OnlineActorComponent* Create(OnlineActor*) = 0;

        // create components for actor
        static Result CreateComponentsFor(OnlineActor* actor);
    private:

        OnlineActorComponentInitializer* pNext{};

        static OnlineActorComponentInitializer* stm_InitializerHead;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    // 
    class OnlineActorComponent : public Component
    {
    public:
        OnlineActorComponent(OnlineActor* pOwner, StringCrc32 name);
        virtual ~OnlineActorComponent();

        virtual Result OnComponentData(const Array<const uint8_t>&) { return ResultCode::SUCCESS_FALSE; }

        OnlineActor& GetOwner() const { assert(m_pOwner);  return *m_pOwner; }

    private:
        OnlineActor* m_pOwner{};
    };


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineActor class
	// 
	class OnlineActor
	{
	public:


        OnlineActor(ActorID actorId);
        virtual ~OnlineActor();

        ActorID GetActorId() const { return m_ActorId; }

        const ActorMovement& GetMovement() const { return m_Movement; }
        void SetMovement(const ActorMovement& movement);

        void AddComponent(OnlineActorComponent* pComponent) { m_ComponentManager.AddComponent(pComponent); }
        void OnComponentData(StringCrc32 name, const Array<const uint8_t>& );

        void TickUpdate();


    private:

        ActorID m_ActorId{};

        ComponentManager m_ComponentManager;

        ActorMovement m_Movement;

	};

}

