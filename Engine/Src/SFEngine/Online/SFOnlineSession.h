////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online session session
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "EngineObject/SFEngineObject.h"
#include "Container/SFDualSortedMap.h"
#include "Delegate/SFEventDelegate.h"
#include "Online/SFOnlineActor.h"
#include "SFOnlineSession.h"
#include "SFOnlineSessionComponent.h"

namespace SF
{
	struct ActorMovement;


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineSession class
	//

	class OnlineSession : public EngineObject
	{
	public:

		using super = EngineObject;

	public:

		OnlineSession(IHeap& heap, StringCrc32 sessionTypeName, StringCrc32 gameId);
		virtual ~OnlineSession();

        virtual Result InitializeObject() override;

		// Disconnect all connection
		void Disconnect();

		virtual void UpdateGameTick();

        virtual Result OnTick(EngineTaskTick tick) override;

		SF_FORCEINLINE StringCrc32 GetSessionTypeName() const { return m_SessionTypeName; }
        SF_FORCEINLINE StringCrc32 GetGameId() const { return m_GameId; }

		SF_FORCEINLINE const SharedPointerT<Net::Connection>& GetConnection() const { return m_Connection; }

        void AddComponent(OnlineSessionComponent* pComponent) { m_ComponentManager.AddComponent(pComponent); }

	protected:

		virtual void RegisterMessageHandlers();

	private:

        StringCrc32 m_SessionTypeName;
		StringCrc32 m_GameId;

		// connections
		SharedPointerT<Net::Connection> m_Connection;

        // Component manager for the session
        ComponentManager m_ComponentManager;
	};
}
