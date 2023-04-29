////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online client Component
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Component/SFComponent.h"
#include "Container/SFDoubleLinkedList.h"



namespace SF
{
    class OnlineClient;
    class OnlineClientComponent;

    /////////////////////////////////////////////////////////////////////////////////////
// Online actor component initializer
    class OnlineClientComponentInitializer : public DoubleLinkedListStaticT<OnlineClientComponentInitializer*, ThreadSyncTraitNone>::Node
    {
    public:
        using super = DoubleLinkedListStaticT<OnlineClientComponentInitializer*, ThreadSyncTraitNone>::Node;

        OnlineClientComponentInitializer();
        virtual ~OnlineClientComponentInitializer();

        virtual OnlineClientComponent* Create(OnlineClient*) = 0;

        // Create components to the client
        static Result CreateComponentsFor(OnlineClient* client);

    private:
        static DoubleLinkedListStaticT<OnlineClientComponentInitializer*> stm_ComponentInitializers;
    };


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClientComponent class
	// 
	class OnlineClientComponent : public Component
	{
	public:

		using super = Component;

        OnlineClientComponent(StringCrc32 componentId, OnlineClient* pOwner);
        virtual ~OnlineClientComponent();

        SF_FORCEINLINE OnlineClient& GetOwner() { assert(m_Owner);  return *m_Owner; }

    private:
        OnlineClient* m_Owner{};
	};


}
