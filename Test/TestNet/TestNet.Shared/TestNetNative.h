////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StormForge
// 
// Author : KyungKun Ko
//
// Description : TestNet class
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

#include "Service/SFEngineService.h"
#include "Net/SFConnectionMUDP.h"




class TestNetNative : public SF::EngineObject
{
public:
	typedef SF::EngineObject super;

private:

	SF::Net::ConnectionPtr m_pConnection;
	SF::AccountID m_AccountID			= 0;
	SF::AuthTicket m_Ticket				= 0;


public:

	TestNetNative();

	~TestNetNative();

	virtual void Dispose() override;

	void CloseAllConnections();

	SF::Result Connect(const char* address, int port);

	void RequestRanking();

	void HandleMessageHack(SF::Message::MessageBase * pMsgBase);

	virtual SF::Result OnTick(SF::EngineTaskTick tick) override;
};

