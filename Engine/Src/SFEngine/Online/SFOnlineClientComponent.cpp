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

    DoubleLinkedListStaticT<OnlineClientComponentInitializer*> OnlineClientComponentInitializer::stm_ComponentInitializers{};

    OnlineClientComponentInitializer::OnlineClientComponentInitializer()
        : super(this)
    {
        stm_ComponentInitializers.Add(this);
    }

    OnlineClientComponentInitializer::~OnlineClientComponentInitializer()
    {
        stm_ComponentInitializers.Remove(this);
    }

    Result OnlineClientComponentInitializer::CreateComponentsFor(OnlineClient* client)
    {
        for (auto& itComponentInitializer : stm_ComponentInitializers)
        {
            OnlineClientComponent* newComponent = itComponentInitializer->Create(client);
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
