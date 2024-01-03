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
#include "Protocol/GameNetPolicy.h"
#include "Protocol/GameMsgClass.h"
#include "Protocol/PlayInstanceNetPolicy.h"
#include "Protocol/PlayInstanceMsgClass.h"
#include "Online/Telemetry/SFTelemetryService.h"
#include "Online/SFOnlineClientComponent.h"
#include "Online/HTTP/SFHTTPClient.h"
#include "Online/HTTP/SFHTTPClientSystem.h"
#include "SFFlat/Login_generated.h"
#include "Util/SFStringFormat.h"
#include "SFFlat/SFFlatPacketHeader.h"

namespace SF
{

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


    class ClientTask_HttpLogin : public OnlineClient::ClientTask
    {
    public:
        using super = ClientTask;

        HTTPClientPtr m_HttpClient;

    public:

        ClientTask_HttpLogin(OnlineClient& owner, uint64_t transactionId)
            : ClientTask(owner, transactionId)
        {
        }

        virtual ~ClientTask_HttpLogin()
        {
            SFLog(Net, Info, "Finished ClientTask_Login");

        }

        void Initialize() override
        {
            super::Initialize();

            SFLog(Net, Info, "Start ClientTask_HttpLogin");

            m_Owner.DisconnectAll();

            SetupRequest();

            SetOnlineState(OnlineState::LogingIn);
        }

        virtual Result SetupRequest() = 0;

        Result ParseResultPacket(const Array<uint8_t>& recvData)
        {
            Result hr;

            SFFlatPacketHeader header;
            header.ReadHeader(recvData);

            uint expectedSize = header.Size;
            if (recvData.size() != expectedSize)
            {
                SFLog(System, Warning, "ObjectDirectory received unexpected data size: expected:{0}, received:{1}", expectedSize, recvData.size());
                defCheck(ResultCode::INVALID_FORMAT);
            }

            const Flat::Login::LoginPacket* responsePacket = Flat::Login::GetLoginPacket((const void*)(recvData.data() + SFFlatPacketHeader::HeaderSize));
            if (responsePacket == nullptr)
            {
                defCheck(ResultCode::INVALID_FORMAT);
            }

            Flat::Login::PayloadData payloadType = responsePacket->payload_data_type();
            if (payloadType != Flat::Login::PayloadData::PayloadData_LoginResult)
            {
                defCheck(ResultCode::INVALID_FORMAT);
            }

            const SF::Flat::Login::LoginResult* resultData = responsePacket->payload_data_as_LoginResult();
            defCheckPtr(resultData);

            m_Owner.m_GameAddress = resultData->game_server_address()->c_str();
            m_Owner.m_AccountId = resultData->account_id();
            m_Owner.m_AuthTicket = resultData->auth_ticket();
            Result loginResult = resultData->result_code();

            if (!loginResult)
            {
                defCheck(loginResult);
            }

            if (m_Owner.m_AccountId == 0 || m_Owner.m_AuthTicket == 0)
            {
                defCheck(ResultCode::UNEXPECTED);
            }

            Service::Telemetry->SetAccountID(m_Owner.m_AccountId);

            SFLog(Net, Debug3, "Logged in: gameserver:{0}, accountId:{1}", m_Owner.m_GameAddress, m_Owner.m_AccountId);

            return hr;
        }

        void ProcessResult()
        {
            if (!m_HttpClient.IsValid())
                return;

            if (!m_HttpClient->IsCompleted())
            {
                SFLog(Net, Error, "Login process hasn't been processed properly");
                return;
            }

            Result hr;
            if (m_HttpClient->GetResultCode())
            {
                auto& recvData = m_HttpClient->GetResultContent();
                if (recvData.size() > 0)
                {
                    DynamicArray<uint8_t> decodedData;
                    decodedData.reserve(recvData.size());
                    hr = Util::Base64Decode(recvData.size(), recvData.data(), decodedData);
                    if (!hr.IsSuccess())
                    {
                        SFLog(System, Error, "Login result decoding error:{0}", hr);
                    }
                    else
                    {
                        hr = ParseResultPacket(decodedData);
                    }
                }
                else
                {
                    hr = ResultCode::INVALID_FORMAT;
                }

                if (!hr.IsSuccess())
                {
                    SFLog(System, Error, "Login result parsing error:{0}", hr);

                    SetOnlineState(OnlineState::Disconnected);
                    SetResult(hr);
                }
                else
                {
                    SetOnlineState(OnlineState::LoggedIn);
                    SetResult(ResultCode::SUCCESS);
                }
            }
            else
            {
                SFLog(System, Error, "Login request porocessing error:{0}", m_HttpClient->GetResultCode());

                SetOnlineState(OnlineState::Disconnected);
                SetResult(m_HttpClient->GetResultCode());
            }
        }


        void OnLoginSuccess()
        {
            SetOnlineState(OnlineState::LoggedIn);
            SetResult(ResultCode::SUCCESS);
        }
    };


    class ClientTask_HttpLoginBR : public ClientTask_HttpLogin
    {
    public:

        ClientTask_HttpLoginBR(OnlineClient& owner, uint64_t transactionId)
            : ClientTask_HttpLogin(owner, transactionId)
        {
        }

        virtual Result SetupRequest() override
        {
            Result hr;

            HTTPClientPtr httpClient = Service::HTTP->CreateHTTPClient();
            defCheckPtr(httpClient);

            DynamicArray<uint8_t> hashedPassword;
            defCheck(Util::SHA256Hash(m_Owner.GetPassword().GetLength(), (const uint8_t*)m_Owner.GetPassword().c_str(), hashedPassword));

            DynamicArray<uint8_t> base64Password;
            base64Password.reserve(hashedPassword.size() * 3);
            defCheck(Util::Base64Encode(hashedPassword.size(), hashedPassword.data(), base64Password));

            base64Password.push_back('\0');

            String url;
            url.Format("http://{0}/BR/Login/v1/idpw?AccessKey={1}&userId={2}&password={3}",
                m_Owner.GetLoginAddresses(), "8FACAEB9-E54D-4CDF-BF85-23F7AF0B9147", m_Owner.GetUserId(), (const char*)base64Password.data());
            httpClient->SetURL(url);
            httpClient->SetMethod(true);
            httpClient->SetOnFinishedCallback([this](HTTPClient* pClient)
                {
                    ProcessResult();
                });

            httpClient->SendRequest();

            m_HttpClient = httpClient;

            return hr;
        }
    };


    class ClientTask_HttpLoginSteam : public ClientTask_HttpLogin
    {
    public:
        ClientTask_HttpLoginSteam(OnlineClient& owner, uint64_t transactionId)
            : ClientTask_HttpLogin(owner, transactionId)
        {
        }

        virtual Result SetupRequest() override
        {
            Result hr;

            HTTPClientPtr httpClient = Service::HTTP->CreateHTTPClient();
            defCheckPtr(httpClient);

            DynamicArray<uint8_t> base64PlatformName;
            base64PlatformName.reserve(m_Owner.GetSteamUserName().GetLength() * 3);
            defCheck(Util::Base64Encode(m_Owner.GetSteamUserName().GetLength(), reinterpret_cast<const uint8_t*>(m_Owner.GetSteamUserName().data()), base64PlatformName));
            base64PlatformName.push_back('\0');

            String url;
            url.Format("http://{0}/BR/Login/v1/steam?AccessKey={1}&steamAccountId={2}&steamUserName={3}&steamUserToken={4}",
                m_Owner.GetLoginAddresses(), "8FACAEB9-E54D-4CDF-BF85-23F7AF0B9147", m_Owner.GetSteamUserId(), (const char*)base64PlatformName.data(), m_Owner.GetSteamUserToken());

            httpClient->SetURL(url);
            httpClient->SetMethod(true);
            httpClient->SetOnFinishedCallback([this](HTTPClient* pClient)
                {
                    ProcessResult();
                });

            httpClient->SendRequest();

            m_HttpClient = httpClient;

            return hr;
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
				[this](Net::Connection*, const MessageHeader* pHeader)
				{
					OnJoinGameServerRes(pHeader);
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

			AuthTicket authTicket = m_Owner.GetAuthTicket();
			String remoteAddress = m_Owner.GetGameAddress();
			if (authTicket == 0)
			{
				SFLog(Net, Error, "Join game server has failed, invalid auth ticket");
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

			if (remoteAddress.IsNullOrEmpty())
			{
				SFLog(Net, Error, "Join game server has failed, invalid remote address: {0}", remoteAddress);
				SetResult(ResultCode::INVALID_STATE);
				return;
			}

            DynamicArray<NetAddress> netAddresses;
            Result result = NetAddress::ParseNameAddress(m_Owner.GetGameAddress(), netAddresses);
            if (!result)
            {
                SFLog(Net, Error, "Failed to get addresses: {0}, hr:{1}", m_Owner.GetGameAddress(), result);
                SetResult(result);
                GetConnection()->Disconnect("JoinGameServer failed");
                SetOnlineState(OnlineState::Disconnected);
                return;
            }

            if (netAddresses.size() == 0)
            {
                SFLog(Net, Error, "Failed to convert addresses: {0}", m_Owner.GetGameAddress());
                SetResult(ResultCode::NOT_EXIST);
                GetConnection()->Disconnect("JoinGameServer failed");
                SetOnlineState(OnlineState::Disconnected);
                return;
            }


			result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, netAddresses[0], 0));
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
					auto res = policy.JoinGameServerCmd(intptr_t(this), m_Owner.GetAccountId(), m_Owner.GetAuthTicket(), 0);
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


		void OnJoinGameServerRes(const MessageHeader* pHeader)
		{
			Message::Game::JoinGameServerRes packet(pHeader);
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
				[this](Net::Connection*, const MessageHeader* pHeader)
				{
					OnPlayInstanceJoinGameInstanceRes(pHeader);
				});

			m_Owner.GetConnectionGame()->AddMessageDelegateUnique(uintptr_t(this),
				Message::Game::JoinGameInstanceRes::MID.GetMsgID(),
				[this](Net::Connection*, const MessageHeader* pHeader)
				{
					OnJoinGameInstanceRes(pHeader);
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

		void OnJoinGameInstanceRes(const MessageHeader* pHeader)
		{
			Message::Game::JoinGameInstanceRes packet(pHeader);
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
			m_Owner.m_GameInstanceAddress = packet.GetServerPublicAddress();
			
			SFLog(Net, Info, "Game instance joined: {0}, game:{1}, {2}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress);

			SetOnlineState(OnlineState::InGameConnectingGameInstance);

            DynamicArray<NetAddress> netAddresses;
            result = NetAddress::ParseNameAddress(m_Owner.GetGameInstanceAddress(), netAddresses);
            if (!result)
            {
                SFLog(Net, Error, "Failed to get addresses: {0}, game:{1}, hr:{2}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress, result);
                SetResult(result);
                SetOnlineState(OnlineState::InGameServer);
                return;
            }

            if (netAddresses.size() == 0)
            {
                SFLog(Net, Error, "Failed to convert addresses: {0}, game:{1}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress);
                SetResult(ResultCode::NOT_EXIST);
                SetOnlineState(OnlineState::InGameServer);
                return;
            }

			AuthTicket authTicket = m_Owner.GetAuthTicket();
			result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, netAddresses[0], 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}

		void OnPlayInstanceJoinGameInstanceRes(const MessageHeader* pHeader)
		{
			Message::PlayInstance::JoinPlayInstanceRes packet(pHeader);
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

			if (m_Owner.GetPlayerID() != packet.GetPlayerID())
			{
				SFLog(Net, Error, "PlayInstance::JoinPlayInstanceRes: failure: invalid playerId, owner:{0}, packet:{1}", m_Owner.GetPlayerID(), packet.GetPlayerID());
				SetResult(packet.GetResult());
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

			SFLog(Net, Info, "PlayInstance::JoinPlayInstanceRes joined: {0}, F:{1:X}", m_Owner.m_GameInstanceUID, packet.GetMovement().MoveFrame);

			m_Owner.InitMovement(packet.GetMovement().ActorId, packet.GetMovement());

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
		, m_OnlineStateChangedQueue(GetHeap())
        , m_OnlineActorByActorId(GetHeap())
        , m_ComponentManager(GetHeap())
	{
	}

	OnlineClient::~OnlineClient()
	{
		ClearTasks();
		DisconnectAll();
	}

    Result OnlineClient::InitializeObject()
    {
        Result hr;

        defCheck(super::InitializeObject());

        OnlineClientComponentInitializer::CreateComponentsFor(this);

        defCheck(m_ComponentManager.InitializeComponents());

        SetTickGroup(EngineTaskTick::AsyncTick);

        return hr;
    }

	void OnlineClient::ClearTasks()
	{
		m_CurrentTask.reset();
		for (auto& itTask : m_PendingTasks)
			IHeap::Delete(itTask);
		m_PendingTasks.Clear();
	}

	void OnlineClient::InitMovement(ActorID actorId, const ActorMovement& movement)
	{
		m_ServerMoveFrame = movement.MoveFrame;
		m_MoveFrame = movement.MoveFrame;

		m_MyPlayerState = nullptr;
        if (m_OutgoingMovement.IsValid())
        {
            m_OutgoingMovement->SetActorID(actorId);
            m_OutgoingMovement->InitMovement(movement);
        }
	}

	void OnlineClient::SetupInstanceInfo()
	{
		m_OutgoingMovement = new(GetHeap()) SendingActorMovementManager;
	}

	void OnlineClient::ClearInstanceInfo()
	{
		m_OutgoingMovement.reset();
        m_OnlineActorByActorId.Reset();
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
			[this](Net::Connection*, const MessageHeader* pMsgData)
			{
				Message::Game::SelectCharacterRes msg;
				if (msg.ParseMessage(pMsgData))
				{
					m_CharacterId = msg.GetCharacterID();
				}
			});


        m_Game->AddMessageDelegateUnique(uintptr_t(this),
            Message::Game::LeaveGameInstanceRes::MID.GetMsgID(),
            [this](Net::Connection*, const MessageHeader* pMsgData)
            {
                 m_GameInstanceUID = 0;
                 switch (GetOnlineState())
                 {
                 case OnlineState::InGameJoiningGameInstance:
                 case OnlineState::InGameConnectingGameInstance:
                 case OnlineState::InGameGameInstanceJoining:
                 case OnlineState::InGameInGameInstance:
                     SetOnlineState(OnlineState::InGameServer);
                     if (m_GameInstance.IsValid())
                     {
                         Disconnect(m_GameInstance);
                     }
                     break;
                 default:
                     break;
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
            [this](Net::Connection*, const MessageHeader* pMsgData)
            {
                OnActorInView(pMsgData);
            });

        m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::RemoveActorFromViewS2CEvt::MID.GetMsgID(),
            [this](Net::Connection*, const MessageHeader* pMsgData)
            {
                OnActorOutofView(pMsgData);
            });

        m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::ActorMovementS2CEvt::MID.GetMsgID(),
            [this](Net::Connection*, const MessageHeader* pMsgData)
            {
                OnActorMovement(pMsgData);
            });

        m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::ActorMovementsS2CEvt::MID.GetMsgID(),
            [this](Net::Connection*, const MessageHeader* pMsgData)
            {
                OnActorMovements(pMsgData);
            });

        m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::VoiceDataS2CEvt::MID.GetMsgID(),
            [this](Net::Connection*, const MessageHeader* pMsgData)
            {
                OnVoiceData(pMsgData);
            });



		m_GameInstance->AddMessageDelegateUnique(uintptr_t(this),
			Message::PlayInstance::PlayerStateChangedS2CEvt::MID.GetMsgID(),
			[this](Net::Connection*, const MessageHeader* pMsgData)
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


	Result OnlineClient::StartConnection(uint64_t transactionId, StringCrc32 gameId, const char* loginAddress, uint64_t steamUserId, const char* steamUserName, const char* steamUserToken, const char* userId, const char* password)
	{
        m_PreviousTickTime = Util::Time.GetTimeMs();

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

        m_SteamUserId = steamUserId;
        m_SteamUserName = steamUserName;
        m_SteamUserToken = steamUserToken;

        if (m_SteamUserId == 0)
        {
            m_UserId = userId;
            m_Password = password;
        }

        SFLog(Net, Info, "OnlineClient::StartConnection, {0}, {1}, steamUserId:{2}, {3}", gameId, loginAddress, steamUserId, steamUserName);

        if (m_SteamUserId != 0)
        {
            m_PendingTasks.push_back(new(GetHeap()) ClientTask_HttpLoginSteam(*this, transactionId));
        }
        else
        {
            m_PendingTasks.push_back(new(GetHeap()) ClientTask_HttpLoginBR(*this, transactionId));
        }
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
		Disconnect(m_Game);
		Disconnect(m_GameInstance);

		SetOnlineState(OnlineState::Disconnected);
	}

	Result OnlineClient::SendMovement(const ActorMovement& newMove)
	{
		ActorMovement newMove2 = newMove;
		newMove2.MoveFrame = m_MoveFrame;

		SFLog(Net, Debug7, "OnlineClient:SendMovement, {0}", newMove2);

		return GetSendMovementManager()->EnqueueMovement(newMove2);
	}

	void OnlineClient::UpdateGameTick()
	{
        DurationMS sinceLastTick = Util::TimeSince(m_PreviousTickTime);
        if (sinceLastTick > DurationMS(1000))
        {
            SFLog(Net, Warning, "OnlineClient::UpdateGameTick, too long online tick interval:{0}", sinceLastTick);
        }
        m_PreviousTickTime = Util::Time.GetTimeMs();

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
                FinishedTaskInfo temp{};
				if (m_FinishedTaskTransactionIds.IsFull())
					m_FinishedTaskTransactionIds.Dequeue(temp);

                FinishedTaskInfo finishedInfo{};
                finishedInfo.TransactionId = m_CurrentTask->GetTransactionID();
                finishedInfo.hr = m_CurrentTask->GetResult();

                // Sequence of task are queued int the PendingTasks, if one fails need to cancel whole task sequence
                if (!m_CurrentTask->GetResult())
                {
                    m_FinishedTaskTransactionIds.Enqueue(finishedInfo);
                    ClearTasks();
                }
                else
                {
                    if (m_PendingTasks.size() == 0 || m_CurrentTask->GetTransactionID() != m_PendingTasks[0]->GetTransactionID())
                    {
                        m_FinishedTaskTransactionIds.Enqueue(finishedInfo);
                    }
                    m_CurrentTask.reset();
                }
			}
		}

        FinishedTaskInfo transactionInfo{};
		while (m_FinishedTaskTransactionIds.Dequeue(transactionInfo))
		{
			if (m_OnlineTaskFinishedCallback)
				m_OnlineTaskFinishedCallback(transactionInfo.TransactionId, (int32_t)transactionInfo.hr);
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
        {
            SFLog(Net, Debug4, "OnlineClient::UpdateMovement deltaFrames:{0}, moveFrame:{1:X}, serverFrame:{2:X}", deltaFrames, m_MoveFrame, m_ServerMoveFrame);
        }

        if (deltaFrames == 0)
        {
            return 0;
        }

		m_TickTime += DurationMS(deltaFrames * ActorMovement::DeltaMSPerFrame);

		m_MoveFrame += deltaFrames;
		m_ServerMoveFrame += deltaFrames;

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

    Result OnlineClient::OnTick(EngineTaskTick tick)
    {
        Result hr;

        m_ComponentManager.TickUpdate();

        if (m_CurrentTask)
        {
            m_CurrentTask->OnEngineTickUpdate();
        }

        return hr;
    }

    void OnlineClient::OnActorInView(const MessageHeader* pMsgData)
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
        OnlineActor* onlineActor{};
        if (!m_OnlineActorByActorId.Find(actorId, onlineActor))
        {
            onlineActor = new(GetHeap()) OnlineActor(actorId);
            m_OnlineActorByActorId.Emplace(actorId, onlineActor);
        }

        onlineActor->SetMovement(msg.GetMovement());
    }

    void OnlineClient::OnActorOutofView(const MessageHeader* pMsgData)
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

        OnlineActor* onlineActor{};
        m_OnlineActorByActorId.Remove(msg.GetActorID(), onlineActor);
        if (onlineActor)
        {
            IHeap::Delete(onlineActor);
        }
    }

    void OnlineClient::OnActorMovement(const MessageHeader* pMsgData)
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

    void OnlineClient::OnActorMovements(const MessageHeader* pMsgData)
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

        OnlineActor* onlineActor{};
        if (m_OnlineActorByActorId.Find(actorId, onlineActor))
        {
            onlineActor->SetMovement(newMove);
        }
    }

    void OnlineClient::OnVoiceData(const MessageHeader* pMsgData)
    {
        Message::PlayInstance::VoiceDataS2CEvt msg(pMsgData);
        if (!msg.ParseMsg())
        {
            SFLog(Net, Error, "OnlineClient::OnPlayerMovements Parsing error");
            return;
        }

        OnlineActor* onlineActor{};
        if (m_OnlineActorByActorId.Find(msg.GetActorID(), onlineActor))
        {
            onlineActor->OnComponentData("VoiceChat"_crc, ArrayView<const uint8_t>(msg.GetVoiceData()));
        }
    }

	void OnlineClient::OnPlayerStateChanged(const MessageHeader* pMsgData)
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
}
