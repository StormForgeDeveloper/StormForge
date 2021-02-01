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
#include "Net/SFConnectionUDP.h"
#include "Protocol/Policy/LoginNetPolicy.h"
#include "Protocol/Message/LoginMsgClass.h"
#include "Protocol/Policy/GameNetPolicy.h"
#include "Protocol/Message/GameMsgClass.h"
#include "Protocol/Policy/PlayInstanceNetPolicy.h"
#include "Protocol/Message/PlayInstanceMsgClass.h"

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
		using super = ClientTask;

	public:

		ClientTask_Login(OnlineClient& owner)
			: ClientTask(owner)
		{
		}

		const SharedPointerT<Net::Connection>& GetConnection()
		{
			return m_Owner.GetConnectionLogin();
		}

		void Disconnect()
		{
			if (m_Owner.m_Login != nullptr)
				m_Owner.Disconnect(m_Owner.m_Login);
		}

		void Initialize() override
		{
			super::Initialize();

			m_Owner.DisconnectAll();

			m_Owner.m_Login = new(GetHeap()) Net::ConnectionTCPClient(GetHeap());
			GetConnection()->SetEventFireMode(Net::Connection::EventFireMode::OnGameTick);

			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(this),
				[this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					OnConnectionEvent(evt);
				});

			GetConnection()->AddMessageDelegateUnique(uintptr_t(this),
				Message::Login::LoginRes::MID.GetMsgID(),
				[this](Net::Connection*, SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnLoginRes(pMsgData);
				});



			SetOnlineState(OnlineState::ConnectingToLogin);

			NetAddress remoteAddress(m_Owner.GetLoginAddresses());
			auto authTicket = 0;
			auto result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, remoteAddress, 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}

		virtual ~ClientTask_Login()
		{
			if (GetConnection() == nullptr)
				return;

			GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->RemoveMessageDelegate(uintptr_t(this), Message::Login::LoginRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::LogingIn);
					Policy::NetPolicyLogin policy(GetConnection());
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
					GetConnection()->Disconnect("Login failed");
					Disconnect();
					SetOnlineState(OnlineState::Disconnected);
				}
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
				Disconnect();
				SetOnlineState(OnlineState::Disconnected);
				SetResult(ResultCode::IO_DISCONNECTED);
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
				Disconnect();
				SetOnlineState(OnlineState::Disconnected);
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "LoginRes: Login failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				Disconnect();
				SetOnlineState(OnlineState::Disconnected);
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
		using super = ClientTask;

	public:

		ClientTask_JoinGameServer(OnlineClient& owner)
			: ClientTask(owner)
		{
		}

		const SharedPointerT<Net::Connection>& GetConnection()
		{
			return m_Owner.GetConnectionGame();
		}

		void Disconnect()
		{
			if (m_Owner.m_Game != nullptr)
				m_Owner.Disconnect(m_Owner.m_Game);
		}

		void Initialize() override
		{
			super::Initialize();

			if (m_Owner.GetConnectionLogin() == nullptr || m_Owner.GetConnectionLogin()->GetConnectionState() != Net::ConnectionState::CONNECTED)
			{
				SFLog(Net, Error, "Join game server has requested without Login connection");
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

			Disconnect();

			m_Owner.m_Game = new(GetHeap()) Net::ConnectionTCPClient(GetHeap());
			GetConnection()->SetEventFireMode(Net::Connection::EventFireMode::OnGameTick);

			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(this),
				[this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					OnConnectionEvent(evt);
				});

			GetConnection()->AddMessageDelegateUnique(uintptr_t(this),
				Message::Game::JoinGameServerRes::MID.GetMsgID(),
				[this](Net::Connection*, SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnJoinGameServerRes(pMsgData);
				});


			SetOnlineState(OnlineState::ConnectingToGameServer);
			auto authTicket = 0;
			auto result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, m_Owner.GetGameAddress4(), 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}

		virtual ~ClientTask_JoinGameServer()
		{
			if (GetConnection() == nullptr)
				return;

			GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->RemoveMessageDelegate(uintptr_t(this), Message::Game::JoinGameServerRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::JoiningToGameServer);
					Policy::NetPolicyGame policy(GetConnection());
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
					GetConnection()->Disconnect("JoinGameServer failed");
					Disconnect();
				}
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
				Disconnect();
				SetOnlineState(OnlineState::Disconnected);
				SetResult(ResultCode::IO_DISCONNECTED);
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
				Disconnect();
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "Game::JoinGameServerRes: failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				Disconnect();
				return;
			}

			m_Owner.m_NickName = packet.GetNickName();
			m_Owner.m_GameInstanceUID = packet.GetGameUID();
			m_Owner.m_PartyUID = packet.GetPartyUID();
			m_Owner.m_PartyLeaderId = packet.GetPartyLeaderID();

			SFLog(Net, Info, "Game server joined: {0}, game:{1}, party:'{2}:{3}'", m_Owner.m_NickName, m_Owner.m_GameInstanceUID, m_Owner.m_PartyUID, m_Owner.m_PartyLeaderId);
			SetResult(ResultCode::SUCCESS);
			SetOnlineState(OnlineState::InGameServer);
		}
	};


	class ClientTask_JoinGameInstanceServer : public OnlineClient::ClientTask
	{
	public:
		using super = ClientTask;

	public:

		ClientTask_JoinGameInstanceServer(OnlineClient& owner)
			: ClientTask(owner)
		{
		}

		const SharedPointerT<Net::Connection>& GetConnection()
		{
			return m_Owner.GetConnectionGameInstance();
		}

		void Disconnect()
		{
			if (m_Owner.m_GameInstance != nullptr)
				m_Owner.Disconnect(m_Owner.m_GameInstance);
		}

		void Initialize() override
		{
			super::Initialize();

			if (m_Owner.GetConnectionGame() == nullptr || m_Owner.GetConnectionGame()->GetConnectionState() != Net::ConnectionState::CONNECTED)
			{
				SFLog(Net, Error, "Join game instance has requested without game connection");
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

			if (m_Owner.GetGameInstanceUID() == 0)
			{
				SFLog(Net, Error, "Join game instance has requested without game instance UID");
				SetResult(ResultCode::INVALID_ARG);
				return;
			}

			Disconnect();

			m_Owner.m_GameInstance = new(GetHeap()) Net::ConnectionUDPClient(GetHeap());
			GetConnection()->SetEventFireMode(Net::Connection::EventFireMode::OnGameTick);

			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(this),
				[this](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					OnConnectionEvent(evt);
				});

			m_Owner.GetConnectionGame()->AddMessageDelegateUnique(uintptr_t(this),
				Message::Game::JoinGameInstanceRes::MID.GetMsgID(),
				[this](Net::Connection*, SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnJoinGameInstanceRes(pMsgData);
				});


			SetOnlineState(OnlineState::InGameJoiningGameInstance);
			Policy::NetPolicyGame policy(m_Owner.GetConnectionGame());
			auto res = policy.JoinGameInstanceCmd(intptr_t(this), m_Owner.GetGameInstanceUID());
			if (!res)
			{
				Disconnect();
				SetOnlineState(OnlineState::InGameServer);
				SFLog(Net, Error, "JoinGameInstance command has failed {0}", res);
			}
		}

		virtual ~ClientTask_JoinGameInstanceServer()
		{
			if (GetConnection() == nullptr)
				return;

			GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));

			if (m_Owner.GetConnectionGame() != nullptr)
				m_Owner.GetConnectionGame()->RemoveMessageDelegate(uintptr_t(this), Message::Game::JoinGameInstanceRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::InGameInGameInstance);
				}
				else
				{
					GetConnection()->Disconnect("JoinGameServer failed");
					Disconnect();
					SetOnlineState(OnlineState::InGameServer);
				}
				SetResult(evt.Components.hr);
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
				Disconnect();
				SetOnlineState(OnlineState::InGameServer);
				SetResult(ResultCode::IO_DISCONNECTED);
			}
		}

		void OnJoinGameInstanceRes(SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::Game::JoinGameInstanceRes packet(Forward<MessageDataPtr>(pMsgData));
			auto result = packet.ParseMsg();
			if (!result)
			{
				SFLog(Net, Error, "JoinGameInstanceRes: Packet parsing error: {0}", result);
				SetResult(result);
				Disconnect();
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "JoinGameInstanceRes: failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				Disconnect();
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

			m_Owner.m_GameInstanceUID = packet.GetInsUID();
			m_Owner.m_GameInstanceAddress = packet.GetServerAddress();
			m_Owner.m_GameInstanceAddress4 = packet.GetServerAddress4();

			SFLog(Net, Info, "Game instance joined: {0}, game:{1}, {2}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress, m_Owner.m_GameInstanceAddress4);

			SetOnlineState(OnlineState::InGameConnectingGameInstance);

			auto authTicket = 0;
			result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, m_Owner.GetGameInstanceAddress4(), 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}
	};


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClient class
	// 

	OnlineClient::OnlineClient(IHeap& heap)
		: EngineObject(new(heap) IHeap("OnlineClient", &heap), "OnlineClient")
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
		for (auto& itTask : m_PendingTasks)
			delete itTask;
		m_PendingTasks.Clear();
	}

	Result OnlineClient::StartConnection(StringCrc32 gameId, const char* loginAddress, const char* userId, const char* password)
	{
		if (GetOnlineState() != OnlineState::None
			&& GetOnlineState() != OnlineState::Disconnected)
			return ResultCode::INVALID_STATE;

		if (m_PendingTasks.size() > 0)
			return ResultCode::BUSY;

		if (loginAddress != nullptr)
			m_LoginAddresses = loginAddress;

		m_GameId = gameId;
		m_UserId = userId;
		m_Password = password;

		m_PendingTasks.push_back(new(GetHeap()) ClientTask_Login(*this));
		m_PendingTasks.push_back(new(GetHeap()) ClientTask_JoinGameServer(*this));

		return ResultCode::SUCCESS;
	}

	Result OnlineClient::JoinGameInstance(uint64_t gameInstanceId)
	{
		if (GetOnlineState() != OnlineState::InGameServer)
			return ResultCode::INVALID_STATE;

		if (m_PendingTasks.size() > 0)
			return ResultCode::BUSY;

		m_GameInstanceUID = gameInstanceId;

		if (m_GameInstanceUID != 0)
			m_PendingTasks.push_back(new(GetHeap()) ClientTask_JoinGameInstanceServer(*this));

		return ResultCode::SUCCESS;
	}

	void OnlineClient::Disconnect(SharedPointerT<Net::Connection>& pConn)
	{
		if (pConn == nullptr)
			return;

		pConn->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
		pConn->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
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
		{
			m_Login->UpdateGameTick();
		}

		if (m_Game != nullptr)
		{
			m_Game->UpdateGameTick();

			if (m_Game->GetConnectionState() == Net::ConnectionState::CONNECTED
				&& Util::TimeSince(m_HeartbeatTimer) > DurationMS(15 * 1000))
			{
				m_HeartbeatTimer = Util::Time.GetTimeMs();
				Policy::NetPolicyGame policy(m_Game);
				policy.HeartbeatC2SEvt();
			}
		}

		if (m_GameInstance != nullptr)
		{
			m_GameInstance->UpdateGameTick();
		}


		if (m_CurrentTask)
		{
			m_CurrentTask->TickUpdate();
			if (m_CurrentTask->GetResult() != ResultCode::BUSY)
			{
				// Sequence of task are queued int the PendingTasks, if one fails need to cancel whole taks sequence
				if (!m_CurrentTask->GetResult())
					ClearTasks();
				else
					m_CurrentTask.reset();
			}
		}

		if (m_CurrentTask == nullptr && m_PendingTasks.size() > 0)
		{
			m_CurrentTask.reset(m_PendingTasks[0]);
			m_PendingTasks.RemoveAt(0);

			m_CurrentTask->Initialize();
		}
	}
}
