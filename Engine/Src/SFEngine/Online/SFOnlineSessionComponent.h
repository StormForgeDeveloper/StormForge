////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online session Component
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Component/SFComponent.h"


namespace SF
{
    class OnlineSession;
    class OnlineSessionComponent;


    /////////////////////////////////////////////////////////////////////////////////////
    // Online session component initializer
    class OnlineSessionComponentInitializer
    {
    public:

        OnlineSessionComponentInitializer();
        virtual ~OnlineSessionComponentInitializer();

        virtual OnlineSessionComponent* Create(OnlineSession*) = 0;

        // Create components to the client
        static Result CreateComponentsFor(OnlineSession* session);

    private:

        OnlineSessionComponentInitializer* pNext{};

        static OnlineSessionComponentInitializer* stm_InitializerHead;
    };


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineSessionComponent class
	// 
	class OnlineSessionComponent : public Component
	{
	public:

		using super = Component;

        OnlineSessionComponent(StringCrc32 componentId, OnlineSession* pOwner);
        virtual ~OnlineSessionComponent();

        SF_FORCEINLINE OnlineSession& GetOwner() { assert(m_Owner);  return *m_Owner; }

    private:
        OnlineSession* m_Owner{};
	};


}
