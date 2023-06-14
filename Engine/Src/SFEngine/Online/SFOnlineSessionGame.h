////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online game session
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

	class OnlineSessionGame : public OnlineSession
	{
	public:

		using super = OnlineSession;

	public:

        OnlineSessionGame(IHeap& heap, StringCrc32 gameId);
		virtual ~OnlineSessionGame();

	private:

		virtual void RegisterMessageHandlers() override;

	private:

	};
}
