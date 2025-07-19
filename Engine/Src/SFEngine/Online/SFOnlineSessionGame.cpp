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

    OnlineSessionGameplay::OnlineSessionGameplay(StringCrc32 gameId)
        : OnlineSession("OnlineSessionGameplay", gameId)
        , m_OnlineActorByActorId()
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
