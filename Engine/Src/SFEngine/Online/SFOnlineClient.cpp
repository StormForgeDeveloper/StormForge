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
#include "Actor/Movement/SFActorMovementManager.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionTCP.h"
#include "Net/SFConnectionUDP.h"
#include "Protocol/LoginNetPolicy.h"
#include "Protocol/LoginMsgClass.h"
#include "Protocol/GameNetPolicy.h"
#include "Protocol/GameMsgClass.h"
#include "Protocol/PlayInstanceNetPolicy.h"
#include "Protocol/PlayInstanceMsgClass.h"

namespace SF
{

	constexpr uint32_t OnlineClient::RemotePlayerSimulationDelay;


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	ClientTask class
	// 

	OnlineClient::ClientTask::ClientTask(OnlineClient& owner, uint64_t transactionId)
		: m_Owner(owner)
		, m_TransactionId(transactionId)
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

		ClientTask_Login(OnlineClient& owner, uint64_t transactionId)
			: ClientTask(owner, transactionId)
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

			SFLog(Net, Info, "Start ClientTask_Login");

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
				[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
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
			SFLog(Net, Info, "Finished ClientTask_Login");

			if (GetConnection() == nullptr)
				return;

			GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->RemoveMessageDelegate(uintptr_t(this), Message::Login::LoginRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			SFLog(Net, Info, "Login OnConnectionEvent  type:{0}, state:{1}", evt.Components.EventType, evt.Components.State);

			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::LogingIn);
					NetPolicyLogin policy(GetConnection()->GetMessageEndpoint());
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
					//Disconnect();
					SetOnlineState(OnlineState::Disconnected);
				}
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
				//Disconnect();
				SetOnlineState(OnlineState::Disconnected);
				SetResult(ResultCode::IO_DISCONNECTED);
			}

		}

		void OnLoginRes(const SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::Login::LoginRes packet(pMsgData);
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

		ClientTask_JoinGameServer(OnlineClient& owner, uint64_t transactionId)
			: ClientTask(owner, transactionId)
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

			SFLog(Net, Info, "Starting ClientTask_JoinGameServer");

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
				[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnJoinGameServerRes(pMsgData);
				});

			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(&m_Owner),
				[pOnlineClient = &m_Owner](Net::Connection*, const Net::ConnectionEvent& evt)
				{
					if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
					{
						pOnlineClient->ClearInstanceInfo();
						pOnlineClient->UpdateOnlineStateByConnectionState();
					}
				});

			auto authTicket = m_Owner.GetAuthTicket();
			auto remoteAddress = m_Owner.GetGameAddress4();
			if (authTicket == 0)
			{
				SFLog(Net, Error, "Join game server has failed, invalid auth ticket");
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

			if (StrUtil::IsNullOrEmpty(remoteAddress.Address) || remoteAddress.Port == 0)
			{
				SFLog(Net, Error, "Join game server has failed, invalid remote address: {0}", remoteAddress);
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

			auto result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, m_Owner.GetGameAddress4(), 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
				SetOnlineState(OnlineState::ConnectingToGameServer);
			}
			else
			{
				SFLog(Net, Error, "Failed to connect to game server {0}", result);
				SetOnlineState(OnlineState::Disconnected);
			}
		}

		virtual ~ClientTask_JoinGameServer()
		{
			SFLog(Net, Info, "Finished ClientTask_JoinGameServer res:{0}", GetResult());

			if (GetConnection() != nullptr)
			{
				GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
				GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
				GetConnection()->RemoveMessageDelegate(uintptr_t(this), Message::Game::JoinGameServerRes::MID.GetMsgID());
			}

			if (m_Owner.GetOnlineState() == OnlineState::InGameServer)
			{
				m_Owner.Disconnect(m_Owner.m_Login);
				m_Owner.m_Login = nullptr;
			}
			else if (m_Owner.GetOnlineState() == OnlineState::LoggedIn)
			{
				m_Owner.Disconnect(m_Owner.m_Game);
				m_Owner.m_Game = nullptr;
				m_Owner.Disconnect(m_Owner.m_GameInstance);
				m_Owner.m_GameInstance = nullptr;
			}
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			SFLog(Net, Info, "Game OnConnectionEvent  type:{0}, state:{1}", evt.Components.EventType, evt.Components.State);
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::JoiningToGameServer);
					NetPolicyGame policy(GetConnection()->GetMessageEndpoint());
					auto res = policy.JoinGameServerCmd(intptr_t(this), m_Owner.GetAccountId(), m_Owner.GetAuthTicket(), m_Owner.GetLoginEntityUID());
					if (!res)
					{
						SetOnlineState(OnlineState::LoggedIn);
						SFLog(Net, Error, "JoinGameServer command has failed {0}", res);
					}
				}
				else
				{
					GetConnection()->Disconnect("JoinGameServer failed");
				}
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
				SetOnlineState(OnlineState::LoggedIn);
				SetResult(ResultCode::IO_DISCONNECTED);
			}
		}


		void OnJoinGameServerRes(const SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::Game::JoinGameServerRes packet(pMsgData);
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
			m_Owner.SetupInstanceInfo();
			m_Owner.RegisterGameHandlers();

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

		ClientTask_JoinGameInstanceServer(OnlineClient& owner, uint64_t transactionId)
			: ClientTask(owner, transactionId)
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

			SFLog(Net, Info, "Starting ClientTask_JoinGameInstanceServer");

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

			GetConnection()->AddMessageDelegateUnique(uintptr_t(this),
				Message::PlayInstance::JoinPlayInstanceRes::MID.GetMsgID(),
				[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnPlayInstanceJoinGameInstanceRes(pMsgData);
				});

			m_Owner.GetConnectionGame()->AddMessageDelegateUnique(uintptr_t(this),
				Message::Game::JoinGameInstanceRes::MID.GetMsgID(),
				[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
				{
					OnJoinGameInstanceRes(pMsgData);
				});

			m_Owner.RegisterPlayInstanceHandlers();
			

			SetOnlineState(OnlineState::InGameJoiningGameInstance);
			NetPolicyGame policy(m_Owner.GetConnectionGame()->GetMessageEndpoint());
			auto res = policy.JoinGameInstanceCmd(intptr_t(this), m_Owner.GetGameInstanceUID());
			if (!res)
			{
				SetResult(res);
				SetOnlineState(OnlineState::InGameServer);
				SFLog(Net, Error, "JoinGameInstance command has failed {0}", res);
			}
		}

		virtual ~ClientTask_JoinGameInstanceServer()
		{
			SFLog(Net, Info, "Finished ClientTask_JoinGameInstanceServer");

			if (m_Owner.GetOnlineState() != OnlineState::InGameInGameInstance)
			{
				m_Owner.ClearInstanceInfo();
				Disconnect();
			}

			if (GetConnection() == nullptr)
				return;

			GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
			GetConnection()->RemoveMessageDelegate(uintptr_t(this), Message::PlayInstance::JoinPlayInstanceRes::MID.GetMsgID());

			if (m_Owner.GetConnectionGame() != nullptr)
				m_Owner.GetConnectionGame()->RemoveMessageDelegate(uintptr_t(this), Message::Game::JoinGameInstanceRes::MID.GetMsgID());
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			SFLog(Net, Info, "GameInstance OnConnectionEvent  type:{0}, state:{1}", evt.Components.EventType, evt.Components.State);
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					NetPolicyPlayInstance policy(m_Owner.GetConnectionGameInstance()->GetMessageEndpoint());
					auto res = policy.JoinPlayInstanceCmd(intptr_t(this), m_Owner.GetGameInstanceUID(), m_Owner.GetPlayerID(), "??");
					if (!res)
					{
						SetResult(res);
						SetOnlineState(OnlineState::InGameServer);
						SFLog(Net, Error, "PlayInstance::JoinPlayInstance command has failed {0}", res);
						return;
					}

					SetOnlineState(OnlineState::InGameGameInstanceJoining);
				}
				else
				{
					GetConnection()->Disconnect("PlayInstance connection has failed");
					m_Owner.UpdateOnlineStateByConnectionState();
					SetResult(ResultCode::IO_DISCONNECTED);
				}
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
				m_Owner.UpdateOnlineStateByConnectionState();
				SetResult(ResultCode::IO_DISCONNECTED);
			}
		}

		void OnJoinGameInstanceRes(const SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::Game::JoinGameInstanceRes packet(pMsgData);
			auto result = packet.ParseMsg();
			if (!result)
			{
				SFLog(Net, Error, "JoinGameInstanceRes: Packet parsing error: {0}", result);
				SetResult(result);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "JoinGameInstanceRes: failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

			m_Owner.m_GameInstanceUID = packet.GetInsUID();
			m_Owner.m_GameInstanceAddress4 = packet.GetServerAddress4();
			m_Owner.m_GameInstanceAddress6 = packet.GetServerAddress6();

			SFLog(Net, Info, "Game instance joined: {0}, game:{1}, {2}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress4, m_Owner.m_GameInstanceAddress6);

			SetOnlineState(OnlineState::InGameConnectingGameInstance);

			auto authTicket = m_Owner.GetAuthTicket();
			result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, m_Owner.GetGameInstanceAddress4(), 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}

		void OnPlayInstanceJoinGameInstanceRes(const SharedPointerT<Message::MessageData>& pMsgData)
		{
			Message::PlayInstance::JoinPlayInstanceRes packet(pMsgData);
			auto result = packet.ParseMsg();
			if (!result)
			{
				SFLog(Net, Error, "PlayInstance::JoinPlayInstanceRes: Packet parsing error: {0}", result);
				SetResult(result);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

			if (!packet.GetResult())
			{
				SFLog(Net, Error, "PlayInstance::JoinPlayInstanceRes: failure: {0}", packet.GetResult());
				SetResult(packet.GetResult());
				SetOnlineState(OnlineState::InGameServer);
				return;
			}


			SFLog(Net, Info, "PlayInstance::JoinPlayInstanceRes joined: {0}, F:{1:X}", m_Owner.m_GameInstanceUID, packet.GetMovement().MoveFrame);

			m_Owner.InitMovement(packet.GetMovement().ActorId, packet.GetMovement().MoveFrame);
			m_Owner.OnActorMovement(packet.GetMovement());

			SetOnlineState(OnlineState::InGameInGameInstance);
			SetResult(ResultCode::SUCCESS);
		}
	};


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClient class
	// 

	OnlineClient::OnlineClient(IHeap& heap)
		: EngineObject(new(heap) IHeap("OnlineClient", &heap), "OnlineClient")
		, m_IncomingMovements(GetHeap())
		, m_IncomingMovementsByActor(GetHeap())
		, m_OnlineStateChangedQueue(GetHeap())
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
			IHeap::Delete(itTask);
		m_PendingTasks.Clear();
	}

	void OnlineClient::InitMovement(ActorID actorId, uint32_t newMoveFrame)
	{
		m_ServerMoveFrame = newMoveFrame;
		m_MoveFrame = newMoveFrame;

		m_MyPlayerState = nullptr;
		if (m_OutgoingMovement.IsValid())
			m_OutgoingMovement->SetActorID(actorId);
	}

	void OnlineClient::SetupInstanceInfo()
	{
		m_OutgoingMovement = new(GetHeap()) SendingActorMovementManager;
	}

	void OnlineClient::ClearInstanceInfo()
	{
		m_OutgoingMovement.reset();
		m_IncomingMovements.ClearMap();
		m_IncomingMovementsByActor.ClearMap();
	}

	void OnlineClient::RegisterGameHandlers()
	{
		if (m_Game == nullptr)
		{
			assert(false);
			return;
		}


		m_Game->AddMessageDelegateUnique(uintptr_t(this),
			Message::Game::SelectCharacterRes::MID.GetMsgID(),
			[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
			{
				Message::Game::SelectCharacterRes msg;
				if (msg.ParseMessage(pMsgData.get()))
				{
					m_CharacterId = msg.GetCharacterID();
				}
			});
	}

	void OnlineClient::RegisterPlayInstanceHandlers()
	{
		if (m_GameInstance == nullptr)
		{
			assert(false);
			return;
		}

		m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
			Message::PlayInstance::NewActorInViewS2CEvt::MID.GetMsgID(),
			[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
			{
				OnActorInView(pMsgData);
			});

		m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
			Message::PlayInstance::RemoveActorFromViewS2CEvt::MID.GetMsgID(),
			[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
			{
				OnActorOutofView(pMsgData);
			});

		m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
			Message::PlayInstance::ActorMovementS2CEvt::MID.GetMsgID(),
			[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
			{
				OnActorMovement(pMsgData);
			});

		m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
			Message::PlayInstance::ActorMovementsS2CEvt::MID.GetMsgID(),
			[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
			{
				OnActorMovements(pMsgData);
			});

		m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
			Message::PlayInstance::PlayerStateChangedS2CEvt::MID.GetMsgID(),
			[this](Net::Connection*, const SharedPointerT<Message::MessageData>& pMsgData)
			{
				OnPlayerStateChanged(pMsgData);
			});

		m_GameInstance->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(this),
			[this](Net::Connection*, const Net::ConnectionEvent& evt)
			{
				if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
				{
					UpdateOnlineStateByConnectionState();
				}
			});
	}


	Result OnlineClient::StartConnection(uint64_t transactionId, StringCrc32 gameId, const char* loginAddress, const char* userId, const char* password)
	{
		if (GetOnlineState() != OnlineState::None
			&& GetOnlineState() != OnlineState::Disconnected)
		{
			SFLog(Net, Error, "OnlineClient::StartConnection, Busy, invalid state:{0}", (uint32_t)GetOnlineState());
			return ResultCode::INVALID_STATE;
		}

		if (m_PendingTasks.size() > 0)
		{
			SFLog(Net, Error, "OnlineClient::StartConnection, Busy, we have running task, state:{0}", (uint32_t)GetOnlineState());
			return ResultCode::BUSY;
		}

		if (loginAddress != nullptr)
			m_LoginAddresses = loginAddress;

		m_GameId = gameId;
		m_UserId = userId;
		m_Password = password;

		SFLog(Net, Info, "OnlineClient::StartConnection login:{0}", loginAddress);

		m_PendingTasks.push_back(new(GetHeap()) ClientTask_Login(*this, transactionId));
		m_PendingTasks.push_back(new(GetHeap()) ClientTask_JoinGameServer(*this, transactionId));

		m_TickTime = Util::Time.GetRawTimeMs();

		return ResultCode::SUCCESS;
	}

	Result OnlineClient::JoinGameInstance(uint64_t transactionId, uint64_t gameInstanceId)
	{
		if (GetOnlineState() != OnlineState::InGameServer)
		{
			SFLog(Net, Error, "OnlineClient::JoinGameInstance, Busy, invalid state:{0}", (uint32_t)GetOnlineState());
			return ResultCode::INVALID_STATE;
		}

		if (m_PendingTasks.size() > 0)
		{
			SFLog(Net, Error, "OnlineClient::JoinGameInstance, Busy, we have running task, state:{0}", (uint32_t)GetOnlineState());
			return ResultCode::BUSY;
		}

		SFLog(Net, Info, "OnlineClient::JoinGameInstance gameinstanceUID:{0}", gameInstanceId);

		m_GameInstanceUID = gameInstanceId;

		if (m_GameInstanceUID != 0)
			m_PendingTasks.push_back(new(GetHeap()) ClientTask_JoinGameInstanceServer(*this, transactionId));

		return ResultCode::SUCCESS;
	}

	Result OnlineClient::GetMovementForPlayer(PlayerID playerId, ActorMovement& outMovement)
	{
		SharedPointerT<ReceivedMovementManager> movement;
		if (!m_IncomingMovements.Find(playerId, movement))
			return ResultCode::OBJECT_NOT_FOUND;

		outMovement = movement->GetMovementResult();
		return ResultCode::SUCCESS;
	}

	Result OnlineClient::GetMovementForPlayerAll(PlayerID playerId, ActorMovement& outMovement, ActorMovement& outReceivedMovement, ActorMovement& outExpectedMovement)
	{
		SharedPointerT<ReceivedMovementManager> movement;
		if (!m_IncomingMovements.Find(playerId, movement))
			return ResultCode::OBJECT_NOT_FOUND;

		outMovement = movement->GetMovementResult();
		outReceivedMovement = movement->GetReceivedMovement();
		outExpectedMovement = movement->GetMovementExpected();
		return ResultCode::SUCCESS;
	}

	void OnlineClient::SetOnlineState(OnlineState newState)
	{
		if (m_OnlineState == newState)
			return;

		auto prevState = m_OnlineState;

		m_OnlineState = newState;

		m_OnlineStateChangedQueue.Enqueue(OnlineStateChangedEventArgs{ prevState, newState });
	}

	ActorID OnlineClient::GetActorID() const
	{
		return m_OutgoingMovement.IsValid() ? m_OutgoingMovement->GetActorID() : 0;
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

	Result OnlineClient::SendMovement(const ActorMovement& newMove)
	{
		ActorMovement newMove2 = newMove;
		newMove2.MoveFrame = m_MoveFrame;

		SFLog(Net, Debug2, "OnlineClient:SendMovement, {0}", newMove2);

		return GetSendMovementManager()->EnqueueMovement(newMove2);
	}

	void OnlineClient::UpdateGameTick()
	{
		if (m_Login != nullptr)
		{
			m_Login->UpdateGameTick();

			if (m_Login != nullptr)
			{
				if (m_Login->GetConnectionState() == Net::ConnectionState::DISCONNECTED)
				{
					m_Login->DisconnectNRelease("Already Disconnected");
					m_Login = nullptr;
				}
			}
		}

		if (m_Game != nullptr)
		{
			m_Game->UpdateGameTick();

			if (m_Game != nullptr && m_Game->GetConnectionState() == Net::ConnectionState::DISCONNECTED)
			{
				m_Game->DisconnectNRelease("Already Disconnected");
				m_Game = nullptr;
			}

			if (m_Game != nullptr)
			{
				if (m_Game->GetConnectionState() == Net::ConnectionState::CONNECTED)
				{
					if (Util::TimeSince(m_HeartbeatTimer) > DurationMS(15 * 1000))
					{
						m_HeartbeatTimer = Util::Time.GetTimeMs();
						NetPolicyGame policy(m_Game->GetMessageEndpoint());
						policy.HeartbeatC2SEvt();
					}
				}
			}
		}

		if (m_GameInstance != nullptr)
		{
			m_GameInstance->UpdateGameTick();
		}

		UpdateTasks();
		UpdateOnlineState();
	}

	void OnlineClient::UpdateTasks()
	{
		if (m_CurrentTask)
		{
			m_CurrentTask->TickUpdate();
			if (m_CurrentTask->GetResult() != ResultCode::BUSY)
			{
				uint64_t temp{};
				if (m_FinishedTaskTransactionIds.IsFull())
					m_FinishedTaskTransactionIds.Dequeue(temp);
				m_FinishedTaskTransactionIds.Enqueue(m_CurrentTask->GetTransactionID());

				// Sequence of task are queued int the PendingTasks, if one fails need to cancel whole task sequence
				if (!m_CurrentTask->GetResult())
					ClearTasks();
				else
					m_CurrentTask.reset();
			}
		}

		uint64_t transId{};
		while (m_FinishedTaskTransactionIds.Dequeue(transId))
		{
			if (m_OnlineTaskFinishedCallback)
				m_OnlineTaskFinishedCallback(transId);
		}

		if (m_CurrentTask == nullptr && m_PendingTasks.size() > 0)
		{
			m_CurrentTask.reset(m_PendingTasks[0]);
			m_PendingTasks.RemoveAt(0);

			m_CurrentTask->Initialize();
		}
	}

	void OnlineClient::UpdateOnlineState()
	{
		OnlineStateChangedEventArgs args;
		while (m_OnlineStateChangedQueue.Dequeue(args))
		{
			SFLog(Net, Info, "OnlineStateChanged, {0} -> {1}", (uint32_t)args.PrevState, (uint32_t)args.NewState);
			if (m_OnlineStateChangedCallback)
			{
				m_OnlineStateChangedCallback(args.PrevState, args.NewState);
			}
		}
	}

	uint32_t OnlineClient::UpdateMovement()
	{
		auto newUpdateTimeStamp = Util::Time.GetRawTimeMs();

		DurationMS deltaTime = newUpdateTimeStamp - m_TickTime;
		uint32_t deltaFrames = deltaTime.count() / ActorMovement::DeltaMSPerFrame;

		if (deltaFrames > 0 && (m_MoveFrame % 200) == 0)
			SFLog(Net, Debug4, "OnlineClient::UpdateMovement deltaFrames:{0}, moveFrame:{1:X}, serverFrame:{2:X}", deltaFrames, m_MoveFrame, m_ServerMoveFrame);

		if (deltaFrames == 0)
			return 0;

		m_TickTime += DurationMS(deltaFrames * ActorMovement::DeltaMSPerFrame);

		m_MoveFrame += deltaFrames;
		m_ServerMoveFrame += deltaFrames;

		m_IncomingMovements.ForeachOrder(0, (uint)m_IncomingMovements.size(), 
			[moveFrame = m_MoveFrame - RemotePlayerSimulationDelay](const PlayerID playerId, const SharedPointerT<ReceivedMovementManager>& movement)
			{
				ActorMovement outMovement;
				movement->SimulateCurrentMove(moveFrame, outMovement);
				return true;
			});


		if (m_OutgoingMovement != nullptr && GetConnectionGameInstance() != nullptr)
		{
			NetPolicyPlayInstance policy(GetConnectionGameInstance()->GetMessageEndpoint());
			ActorMovement pMove{};
			if (m_MyPlayerState != nullptr) // If it is not null it means  the player is standing
			{
				while (m_OutgoingMovement->DequeueMovement(pMove))
				{
				}
			}
			else
			{
				while (m_OutgoingMovement->DequeueMovement(pMove))
				{
					policy.PlayerMovementC2SEvt(GetGameInstanceUID(), GetPlayerID(), pMove);
				}
			}
		}

		return deltaFrames;
	}

	void OnlineClient::OnActorInView(const MessageDataPtr& pMsgData)
	{
		Message::PlayInstance::NewActorInViewS2CEvt msg(pMsgData);
		if (!msg.ParseMsg())
		{
			SFLog(Net, Info, "OnlineClient::OnActorInView Parsing error");
			return;
		}

		if (msg.GetPlayInstanceUID() != m_GameInstanceUID)
		{
			SFLog(Net, Info, "Invalid instance id, ignoring movement");
			return;
		}

		auto actorId = msg.GetMovement().ActorId;
		SharedPointerT<ReceivedMovementManager> movement;
		if (!m_IncomingMovements.Find(msg.GetPlayerID(), movement))
		{
			movement = new(GetHeap()) ReceivedMovementManager(actorId);
			auto res = m_IncomingMovements.Insert(msg.GetPlayerID(), movement);
			assert(res);
		}

		m_IncomingMovementsByActor.Emplace(actorId, movement);

		movement->ResetMove(msg.GetMovement());
	}

	void OnlineClient::OnActorOutofView(const MessageDataPtr& pMsgData)
	{
		Message::PlayInstance::RemoveActorFromViewS2CEvt msg(pMsgData);
		if (!msg.ParseMsg())
		{
			SFLog(Net, Info, "OnlineClient::OnActorOutofView Parsing error");
			return;
		}

		if (msg.GetPlayInstanceUID() != m_GameInstanceUID)
		{
			SFLog(Net, Info, "Invalid instance id, ignoring movement");
			return;
		}

		SharedPointerT<ReceivedMovementManager> movement;
		m_IncomingMovements.Remove(msg.GetPlayerID(), movement);
		if (movement.IsValid())
		{
			m_IncomingMovementsByActor.Remove(movement->GetActorID(), movement);
		}
	}

	void OnlineClient::OnActorMovement(const MessageDataPtr& pMsgData)
	{
		Message::PlayInstance::ActorMovementS2CEvt msg(pMsgData);
		if (!msg.ParseMsg())
		{
			SFLog(Net, Error, "OnlineClient::OnPlayerMovement Parsing error");
			return;
		}

		if (msg.GetPlayInstanceUID() != m_GameInstanceUID)
		{
			SFLog(Net, Warning, "Invalid instance id, ignoring movement");
			return;
		}

		OnActorMovement(msg.GetMovement());
	}

	void OnlineClient::OnActorMovements(const MessageDataPtr& pMsgData)
	{
		Message::PlayInstance::ActorMovementsS2CEvt msg(pMsgData);
		if (!msg.ParseMsg())
		{
			SFLog(Net, Error, "OnlineClient::OnPlayerMovements Parsing error");
			return;
		}

		if (msg.GetPlayInstanceUID() != m_GameInstanceUID)
		{
			SFLog(Net, Warning, "Invalid instance id, ignoring movements");
			return;
		}

		for (auto& itMove : msg.GetMovement())
		{
			OnActorMovement(itMove);
		}
	}

	void OnlineClient::OnActorMovement(const ActorMovement& newMove)
	{
		auto actorId = newMove.ActorId;
		SFLog(Net, Debug3, "OnlineClient:OnPlayerMovement, actorId:{0}, serverFrame:{1:X}, move:{2}", actorId, m_ServerMoveFrame, newMove);

		// adjust move frame
		m_ServerMoveFrame = Math::Max(m_ServerMoveFrame, newMove.MoveFrame);

		SharedPointerT<ReceivedMovementManager>* pMovement;
		if (!m_IncomingMovementsByActor.FindRef(actorId, pMovement) || !pMovement->IsValid())
		{
			SFLog(Net, Debug3, "OnlineClient:OnPlayerMovement, missing actor movment mapping actorId:{0}", actorId);
			return;
		}

		(*pMovement)->EnqueueMovement(newMove);
	}

	void OnlineClient::OnPlayerStateChanged(const MessageDataPtr& pMsgData)
	{
		Message::PlayInstance::PlayerStateChangedS2CEvt msg(pMsgData);
		if (!msg.ParseMsg())
		{
			SFLog(Net, Error, "OnlineClient::OnPlayerStateChanged Parsing error");
			return;
		}

		if (msg.GetPlayInstanceUID() != m_GameInstanceUID)
		{
			SFLog(Net, Warning, "Invalid instance id, ignoring movement");
			return;
		}

		// we only interested in my player state
		if (msg.GetPlayerID() != m_AccountId)
			return;

		m_MyPlayerState = msg.GetState();
	}

	void OnlineClient::UpdateOnlineStateByConnectionState()
	{
		if (GetConnectionLogin() != nullptr && GetConnectionLogin()->GetConnectionState() == Net::ConnectionState::CONNECTED)
		{
			if (GetConnectionGame() != nullptr && GetConnectionGame()->GetConnectionState() == Net::ConnectionState::CONNECTED)
			{
				if (GetConnectionGameInstance() != nullptr && GetConnectionGameInstance()->GetConnectionState() == Net::ConnectionState::CONNECTED)
				{
					SetOnlineState(OnlineState::InGameInGameInstance);
				}
				else
				{
					SetOnlineState(OnlineState::InGameServer);
				}
			}
			else
			{
				Disconnect(m_GameInstance);
				SetOnlineState(OnlineState::LoggedIn);
			}
		}
		else
		{
			DisconnectAll();
			SetOnlineState(OnlineState::Disconnected);
		}

	}
}
