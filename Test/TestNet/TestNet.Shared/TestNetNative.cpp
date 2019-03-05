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


#include "TestNetNative.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Util/SFLog.h"
#include "Util/SFRandom.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Net/SFConnectionMUDP.h"
#include "Net/SFMessage.h"
#include "Protocol/SFProtocol.h"

#include "SFEngine.h"

#include "Protocol/Message/GameMsgDebug.h"

#include "Protocol/Message/LoginMsgParsing.h"
#include "Protocol/Message/GameMsgParsing.h"



using namespace SF;


TestNetNative::TestNetNative()
	: EngineObject(new(GetEngineHeap()) IHeap("TestNetNative", &GetEngineHeap()), "TestNetNative")
{
}

TestNetNative::~TestNetNative()
{
	// I created IHeap manually, so I need to check manually
	GetHeap().ReportLeak();
}


void TestNetNative::Dispose()
{
	CloseAllConnections();
	super::Dispose();
}

void TestNetNative::CloseAllConnections()
{
	if (m_pConnection != nullptr)
	{
		m_pConnection->CloseConnection("TestNet Close connection");

		if (SF::Engine::GetInstance() != nullptr)
		{
			m_pConnection->DisconnectNRelease("TestNet close all connection");
		}
		else
		{
			m_pConnection->Dispose();
		}

		m_pConnection = nullptr;
	}
}


Result TestNetNative::Connect(const char* address, int port)
{
	CloseAllConnections();

	m_pConnection = new(Service::NetSystem->GetHeap()) Net::ConnectionMUDPClient(Service::NetSystem->GetHeap());

	NetAddress remoteAddress(address, port);

	auto result = m_pConnection->Connect(Net::PeerInfo(NetClass::Client, 0), Net::PeerInfo(NetClass::Unknown, remoteAddress, 0));
	if (result)
		m_pConnection->SetTickGroup(EngineTaskTick::AsyncTick);

	return result;
}

void TestNetNative::RequestRanking()
{
	if (m_pConnection == nullptr)
		return;

	if (m_pConnection->IsDisposed() || m_pConnection->GetConnectionState() != Net::ConnectionState::CONNECTED)
		return;

	MessageDataPtr pMsg = Message::Login::UpdateMyScoreCmd::Create(Service::NetSystem->GetHeap(), 0, Util::Random.Rand(0, 5000), RankingType::World, 10);

	m_pConnection->Send(pMsg);
}

void TestNetNative::HandleMessageHack(Message::MessageBase * pMsgBase)
{
	Net::ConnectionPtr pCon = m_pConnection;
	if (pCon == nullptr)
		return;

	if (pMsgBase == nullptr)
		return;

	auto pMsg = pMsgBase->GetMessage();
	if (pMsg == nullptr)
		return;

	auto msgID = pMsg->GetMessageHeader()->msgID.GetMsgID();
	if (msgID == SF::Message::Login::CreateRandomUserRes::MID.IDSeq.MsgID)
	{
		auto pMsg = (Message::Login::CreateRandomUserRes*)pMsgBase;

		if (pMsg->GetResult() != Result(ResultCode::SUCCESS))
		{
			SFLog(Game, Error, "Login Failed {0:X8}", pMsg->GetResult());
		}
		else
		{
			m_AccountID = pMsg->GetAccID();
			m_Ticket = pMsg->GetTicket();

			// Peer ID need to be assigned
			pCon->SetLocalID(m_Ticket);

			SFLog(Game, Info, "Logged in");

			MessageDataPtr pMsg = Message::Login::UpdateMyScoreCmd::Create(Service::NetSystem->GetHeap(), 0, Util::Random.Rand(0, 5000), RankingType::World, 10);
			pCon->Send(pMsg);
		}

	}
	else if (msgID == SF::Message::Login::UpdateMyScoreRes::MID.IDSeq.MsgID)
	{
		auto pMsg = (Message::Login::UpdateMyScoreRes*)pMsgBase;

		if (pMsg->GetResult() != Result(ResultCode::SUCCESS))
		{
			SFLog(Game, Error, "Update score Failed {0:X8}", pMsg->GetResult());
		}
		else
		{
			for (auto& itRank : pMsg->GetRanking())
			{
				SFLog(Game, Error, "Ranking score: Rank{0}, {1}, score:{2}", itRank.Ranking, (const char*)itRank.NickName, itRank.GetScore());
			}
		}
	}

}


Result TestNetNative::OnTick(EngineTaskTick tick)
{
	// Copy to local access pointer so that I can keep the pointer until the end of tick
	Net::ConnectionPtr pCon = m_pConnection;
	if (pCon == nullptr)
		return ResultCode::SUCCESS;


	Net::ConnectionEvent conEvent;
	while (pCon->DequeueConnectionEvent(conEvent))
	{
		MessageDataPtr pMsg;
		switch (conEvent.Components.EventType)
		{
		case Net::ConnectionEvent::EVT_STATE_CHANGE:
			SFLog(Game, Error, "Connection State Changed {0}", (int)conEvent.Components.State);
			break;
		case Net::ConnectionEvent::EVT_CONNECTION_RESULT:
			SFLog(Game, Error, "Connection Result {0:X8}", conEvent.Components.hr);
			pMsg = Message::Login::CreateRandomUserCmd::Create(Service::NetSystem->GetHeap(), 0, FixedString32("MyTownHero"), "testMyID");
			pCon->Send(pMsg);
			break;
		case Net::ConnectionEvent::EVT_DISCONNECTED:
			SFLog(Game, Error, "Disconnected");
			pCon->CloseConnection("Close because Disconnected");
			break;
		default:
			break;
		}
	}

	if (pCon->GetConnectionState() != Net::ConnectionState::CONNECTED)
		return ResultCode::SUCCESS;

	MessageDataPtr pIMsg;
	while (pCon->GetRecvMessage(pIMsg))
	{
		Message::MessageBase * pMsgBase = nullptr;
		Result hrParse = Protocol::ParseMessage(Service::NetSystem->GetHeap(), pIMsg, pMsgBase);
		if (!hrParse || pMsgBase == nullptr)
			continue;

		// If parseMessage handler released the message
		if (pMsgBase == nullptr)
			continue;

		HandleMessageHack(pMsgBase);

		IHeap::Delete(pMsgBase);

	}

	return ResultCode::SUCCESS;
}


