////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online game play session
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Online/SFOnlineSession.h"
#include "Net/SFConnection.h"
#include "Online/SFOnlineSessionComponent.h"
#include "Online/SFOnlineSessionGameplay.h"


namespace SF
{

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineSessionGameplay class
	// 

    OnlineSessionGameplay::OnlineSessionGameplay(IHeap& heap, StringCrc32 gameId)
        : OnlineSession(heap, "OnlineSessionGameplay", gameId)
        , m_OnlineActorByActorId(heap)
	{
	}

    OnlineSessionGameplay::~OnlineSessionGameplay()
	{
	}

    void OnlineSessionGameplay::RegisterMessageHandlers()
    {
        super::RegisterMessageHandlers();
    }

}
