////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online gameplay session
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
	//	OnlineSessionGame class
	//

	class OnlineSessionGameplay : public OnlineSession
	{
	public:

		using super = OnlineSession;

	public:

        OnlineSessionGameplay(StringCrc32 gameId);
		virtual ~OnlineSessionGameplay();

	private:

		virtual void RegisterMessageHandlers() override;

	private:
        AccountID m_AccountId{};
        AuthTicket m_AuthTicket{};

        String m_NickName;
        CharacterID m_CharacterId{};
        uint64_t m_GameInstanceUID{};
        StringCrc32 m_MyPlayerState;
        uint64_t m_PartyUID{};
        uint64_t m_PartyLeaderId{};

        String m_GameInstanceAddress;

        TimeStampMS m_HeartbeatTimer{};

        // My actor movement
        ActorMovement m_OutgoingMovement;

        SortedMap<ActorID, OnlineActor*> m_OnlineActorByActorId;

        // tick time
        TimeStampMS m_TickTime;
        TimeStampMS m_PreviousTickTime;

        // Move frame
        uint32_t m_MoveFrame{};
        // Estimated server move frame
        uint32_t m_ServerMoveFrame{};

	};
}
