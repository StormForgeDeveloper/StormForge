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
#include "Online/SFOnlineSessionGame.h"


namespace SF
{

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineSession class
	// 

    OnlineSessionGame::OnlineSessionGame(StringCrc32 gameId)
        : OnlineSession("OnlineSessionGame", gameId)
	{
	}

    OnlineSessionGame::~OnlineSessionGame()
	{
	}

    void OnlineSessionGame::RegisterMessageHandlers()
    {
        super::InitializeObject();
    }

}
