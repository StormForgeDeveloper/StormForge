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
#include "Net/SFConnectionTCP.h"
#include "Net/SFConnectionUDP.h"
#include "Online/SFOnlineSessionComponent.h"
#include "Online/SFOnlineSession.h"


namespace SF
{

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineSession class
	// 

    OnlineSession::OnlineSession(StringCrc32 sessionTypeName, StringCrc32 gameId)
        : EngineObject("OnlineSession")
        , m_SessionTypeName(sessionTypeName)
        , m_GameId(gameId)
	{
	}

	OnlineSession::~OnlineSession()
	{
		Disconnect();
	}

    Result OnlineSession::InitializeObject()
    {
        Result hr;

        netCheck(super::InitializeObject());

        return hr;
    }

    // Disconnect all connection
    void OnlineSession::Disconnect()
    {
        if (m_Connection != nullptr)
        {
            m_Connection->Disconnect("Disconnect from code");
        }
    }

    void OnlineSession::RegisterMessageHandlers()
    {

    }

    void OnlineSession::UpdateGameTick()
    {

    }

    Result OnlineSession::OnTick(EngineTaskTick tick)
    {
        Result hr;

        netCheck(super::OnTick(tick));

        return hr;
    }

}
