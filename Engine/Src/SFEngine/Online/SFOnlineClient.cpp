////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Online client
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Online/SFOnlineClient.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionTCP.h"
#include "Protocol/Policy/LoginNetPolicy.h"
#include "Protocol/Message/LoginMsgClass.h"
#include "Protocol/Policy/GameNetPolicy.h"
#include "Protocol/Message/GameMsgClass.h"

namespace SF
{

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	ClientTask class
	// 

	OnlineClient::ClientTask::ClientTask(OnlineClient& owner)
		: m_Owner(owner)
	{

	}

	OnlineClient::ClientTask::~ClientTask()
	{

	}

	void OnlineClient::ClientTask::SetOnlineState(OnlineState newState)
	{
		m_Owner.SetOnlineState(newState);
	}



	class ClientTask_Login : public OnlineClient::ClientTask
	{
	public:

		ClientTask_Login(OnlineClient& owner)
			: ClientTask(owner)
		{
			m_Owner.ClearTasks();
			m_Owner.DisconnectAll();

			m_Owner.m_Login = new(GetHeap()) Net::ConnectionTCPClient(GetHeap());
			m_Owner.GetConnectionLogin()->SetEventFireMode(Net::Connection::EventFireMode::OnGameTick);


			m_Owner.GetConnectionLogin()->GetConnectionEventDelegates().AddDelegateUnique(this,
				[this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					OnConnectionEvent(evt);
				});


			m_Owner.GetConnectionLogin()->AddMessageDelegateUnique(this,
				Message::Login::LoginRes::MID.GetMsgID(),
				[this](Net::Connection*, SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnLoginRes(pMsgData);
				});


			m_Owner.GetConnectionLogin()->GetConnectionEventDelegates().AddDelegateUnique(this, [this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
						m_Owner.Disconnect(m_Owner.m_Login);
				});


			SetOnlineState(OnlineState::ConnectingToLogin);
			NetAddress remoteAddress(owner.GetLoginAddresses());
			auto authTicket = 0;
			auto result = owner.GetConnectionLogin()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, remoteAddress, 0));
			if (result)
			{
				owner.GetConnectionLogin()->SetTickGroup(EngineTaskTick::AsyncTick);
			}

		}

		virtual ~ClientTask_Login()
		{
			if (m_Owner.GetConnectionLogin() == nullptr)
				return;

			m_Owner.GetConnectionLogin()->GetConnectionEventDelegates().RemoveDelegateAll(this);
			m_Owner.GetConnectionLogin()->GetRecvMessageDelegates().RemoveDelegateAll(this);
			m_Owner.GetConnectionLogin()->RemoveMessageDelegate(this, Message::Login::LoginRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::LogingIn);
					Policy::NetPolicyLogin policy(m_Owner.GetConnectionLogin());
					auto res = policy.LoginCmd(intptr_t(this), m_Owner.GetGameId(), m_Owner.GetUserId(), m_Owner.GetPassword());
					if (!res)
					{
						m_Owner.DisconnectAll();
						SetOnlineState(OnlineState::Disconnected);
						SFLog(Net, Error, "Login command has failed {0}", res);
					}
				}
				else
				{
					m_Owner.GetConnectionLogin()->Disconnect("Login failed");
				}
			}
		}

		void OnLoginRes(SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::Login::LoginRes packet(Forward<MessageDataPtr>(pMsgData));
			auto result = packet.ParseMsg();
			if (!result)
			{
				SFLog(Net, Error, "LoginRes: Packet parsing error: {0}", result);
				SetResult(result);
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "LoginRes: Login failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				return;
			}

			m_Owner.m_LoginEntityUID = packet.GetLoginEntityUID();
			m_Owner.m_GameAddress = packet.GetGameServerAddr();
			m_Owner.m_GameAddress4 = packet.GetGameServerAddrIPV4();
			m_Owner.m_AccountId = packet.GetAccID();
			m_Owner.m_AuthTicket = packet.GetTicket();

			SFLog(Net, Info, "Logged in: {0},{1}, accountId:{2}", m_Owner.m_GameAddress, m_Owner.m_GameAddress4, m_Owner.m_AccountId);
			SetOnlineState(OnlineState::LoggedIn);
			SetResult(ResultCode::SUCCESS);
		}
	};



	class ClientTask_JoinGameServer : public OnlineClient::ClientTask
	{
	public:

		ClientTask_JoinGameServer(OnlineClient& owner)
			: ClientTask(owner)
		{
			if (m_Owner.GetConnectionLogin() == nullptr || m_Owner.GetConnectionLogin()->GetConnectionState() != Net::ConnectionState::CONNECTED)
			{
				SFLog(Net, Error, "Join game server has requested without Login connection");
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

			if (m_Owner.m_Game != nullptr)
				m_Owner.Disconnect(m_Owner.m_Game);

			m_Owner.m_Game = new(GetHeap()) Net::ConnectionTCPClient(GetHeap());
			m_Owner.GetConnectionGame()->SetEventFireMode(Net::Connection::EventFireMode::OnGameTick);


			m_Owner.GetConnectionGame()->GetConnectionEventDelegates().AddDelegateUnique(this,
				[this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					OnConnectionEvent(evt);
				});


			m_Owner.GetConnectionLogin()->AddMessageDelegateUnique(this,
				Message::Game::JoinGameServerRes::MID.GetMsgID(),
				[this](Net::Connection*, SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnJoinGameServerRes(pMsgData);
				});


			m_Owner.GetConnectionGame()->GetConnectionEventDelegates().AddDelegateUnique(this, [this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
						m_Owner.Disconnect(m_Owner.m_Game);
				});

			SetOnlineState(OnlineState::ConnectingToGameServer);
			NetAddress remoteAddress(owner.GetLoginAddresses());
			auto authTicket = 0;
			auto result = m_Owner.GetConnectionGame()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, remoteAddress, 0));
			if (result)
			{
				m_Owner.GetConnectionGame()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}

		virtual ~ClientTask_JoinGameServer()
		{
			if (m_Owner.GetConnectionGame() == nullptr)
				return;

			m_Owner.GetConnectionGame()->GetConnectionEventDelegates().RemoveDelegateAll(this);
			m_Owner.GetConnectionGame()->GetRecvMessageDelegates().RemoveDelegateAll(this);
			m_Owner.GetConnectionGame()->RemoveMessageDelegate(this, Message::Game::JoinGameServerRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::JoiningToGameServer);
					Policy::NetPolicyGame policy(m_Owner.GetConnectionGame());
					auto res = policy.JoinGameServerCmd(intptr_t(this), m_Owner.GetAccountId(), m_Owner.GetAuthTicket(), m_Owner.GetLoginEntityUID());
					if (!res)
					{
						m_Owner.DisconnectAll();
						SetOnlineState(OnlineState::Disconnected);
						SFLog(Net, Error, "JoinGameServer command has failed {0}", res);
					}
				}
				else
				{
					m_Owner.GetConnectionLogin()->Disconnect("JoinGameServer failed");
				}
			}
		}


		void OnJoinGameServerRes(SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::Game::JoinGameServerRes packet(Forward<MessageDataPtr>(pMsgData));
			auto result = packet.ParseMsg();
			if (!result)
			{
				SFLog(Net, Error, "Game::JoinGameServerRes: Packet parsing error: {0}", result);
				SetResult(result);
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "Game::JoinGameServerRes: failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				return;
			}

			m_Owner.m_NickName = packet.GetNickName();
			m_Owner.m_GameInstanceUID = packet.GetGameUID();
			m_Owner.m_PartyUID = packet.GetPartyUID();
			m_Owner.m_PartyLeaderId = packet.GetPartyLeaderID();
			//const MatchingQueueTicket& GetMatchingTicket() const { return m_MatchingTicket; };

			SFLog(Net, Info, "Game server joined: {0}, game:{1}, party:'{2}:{3}'", m_Owner.m_NickName, m_Owner.m_GameInstanceUID, m_Owner.m_PartyUID, m_Owner.m_PartyLeaderId);
			SetResult(ResultCode::SUCCESS);
			SetOnlineState(OnlineState::InGameServer);
		}
	};



	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClient class
	// 

	OnlineClient::OnlineClient()
		: EngineObject(new(GetEngineHeap()) IHeap("OnlineClient", &GetEngineHeap()), "OnlineClient")
		, m_IncomingMovements(GetHeap())
	{
	}

	OnlineClient::~OnlineClient()
	{
		ClearTasks();
		DisconnectAll();
	}

	void OnlineClient::ClearTasks()
	{
		m_CurrentTask.reset();
	}

	void OnlineClient::StartConnection(StringCrc32 gameId, const char* loginAddress, const char* userId, const char* password)
	{
		if (loginAddress != nullptr)
			m_LoginAddresses = loginAddress;

		m_GameId = gameId;
		m_UserId = userId;
		m_Password = password;


		m_OnlineState = OnlineState::None;

		m_PendingTasks.push_back(new(GetHeap()) ClientTask_Login(*this));
		m_PendingTasks.push_back(new(GetHeap()) ClientTask_JoinGameServer(*this));
		//m_PendingTasks.push_back(new(GetHeap()) ClientTask_Login(*this));

		// TODO: create async tasks
	}

	void OnlineClient::Disconnect(SharedPointerT<Net::Connection>& pConn)
	{
		if (pConn == nullptr)
			return;

		pConn->GetConnectionEventDelegates().RemoveDelegateAll(this);
		pConn->GetRecvMessageDelegates().RemoveDelegateAll(this);
		pConn->DisconnectNRelease("Disconnect All");
		pConn = nullptr;
	}

	void OnlineClient::DisconnectAll()
	{
		Disconnect(m_Login);
		Disconnect(m_Game);
		Disconnect(m_GameInstance);

		SetOnlineState(OnlineState::Disconnected);
	}

	void OnlineClient::UpdateGameTick()
	{
		if (m_Login != nullptr)
			m_Login->UpdateGameTick();

		if (m_Game != nullptr)
			m_Game->UpdateGameTick();

		if (m_GameInstance != nullptr)
			m_GameInstance->UpdateGameTick();


		if (m_CurrentTask)
		{
			m_CurrentTask->TickUpdate();
			if (m_CurrentTask->GetResult() != ResultCode::BUSY)
			{
				m_CurrentTask.reset();
			}
		}
		if (m_CurrentTask == nullptr && m_PendingTasks.size() > 0)
		{
			m_CurrentTask.reset(m_PendingTasks[0]);
			m_PendingTasks.RemoveAt(0);
		}
	}
}
