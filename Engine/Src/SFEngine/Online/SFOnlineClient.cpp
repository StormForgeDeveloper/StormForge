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
#include "Protocol/GameRPCSendAdapter.h"
#include "Protocol/Game_generated.h"
#include "Protocol/PlayInstanceRPCSendAdapter.h"
#include "Protocol/PlayInstance_generated.h"
#include "Protocol/Login_generated.h"
#include "SFProtocolHelper.h"
#include "Online/Telemetry/SFTelemetryService.h"
#include "Online/SFOnlineClientComponent.h"
#include "Online/HTTP/SFHTTPClient.h"
#include "Online/HTTP/SFHTTPClientSystem.h"
#include "Util/SFStringFormat.h"
#include "MessageBus/SFMessageHeader.h"
#include "Util/SFGuidHelper.h"

#include "Protocol/GameMessageID.h"
#include "Protocol/PlayInstanceMessageID.h"

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

            const MessageHeader2* messageHeader = reinterpret_cast<const MessageHeader2*>(recvData.data());

            uint expectedSize = messageHeader->MessageSize;
            if (recvData.size() != expectedSize)
            {
                SFLog(System, Warning, "ObjectDirectory received unexpected data size: expected:{0}, received:{1}", expectedSize, recvData.size());
                defCheck(ResultCode::INVALID_FORMAT);
            }

            const Flat::Login::LoginRes* response = ::flatbuffers::GetRoot<Flat::Login::LoginRes>(messageHeader->GetPayloadPtr());
            defCheckPtr(response);

            m_Owner.m_GameServerAddress = response->game_server_address()->c_str();
            m_Owner.m_AccountId = Guid(response->account_id()->low(), response->account_id()->high());
            m_Owner.m_AuthTicket = response->auth_ticket();
            Result loginResult = response->result();

            if (!loginResult)
            {
                defCheck(loginResult);
            }

            if (m_Owner.m_AccountId == 0 || m_Owner.m_AuthTicket == 0)
            {
                defCheck(ResultCode::UNEXPECTED);
            }

            Service::Telemetry->SetAccountID(m_Owner.m_AccountId);

            SFLog(Net, Debug3, "Logged in: gameserver:{0}, accountId:{1}", m_Owner.GetGameServerAddress(), m_Owner.m_AccountId);

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
            if (m_HttpClient->GetResultCode().IsSuccess())
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
                    ArrayView<const char> charView(recvData);
                    String resultString = charView;
                    SFLog(System, Error, "Login result parsing error:{0}, content:{1}", hr, resultString);

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

            SFLog(Game, Info, "RequestingLogin: {0}, {1}", m_Owner.GetUserId(), (const char*)base64Password.data());

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

            SFLog(Game, Info, "RequestingSteamLogin: {0}, {1}", m_Owner.GetSteamUserId(), (const char*)base64PlatformName.data());

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

        NetAddress m_GameServerNetAddress{};


        MessageDelegateMap m_MessageHandlerMap;

	public:

		ClientTask_JoinGameServer(OnlineClient& owner, uint64_t transactionId)
			: ClientTask(owner, transactionId)
		{
            m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
                Message::Game::MID_JoinGameServerRes,
                [this](const MessageHeader* pHeader)
                {
                    OnJoinGameServerRes(pHeader);
                });
		}

		const SharedPointerT<Net::Connection>& GetConnection()
		{
			return m_Owner.GetConnectionGame();
		}

        virtual void Dispose() override
        {
            SFLog(Net, Info, "Finished ClientTask_JoinGameServer res:{0}", GetResult());

            if (GetConnection() != nullptr)
            {
                GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
                GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));
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

            super::Dispose();
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

            WeakPointerT<ClientTask_JoinGameServer> WeakThis = AsSharedPtr<ClientTask_JoinGameServer>();
			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(this),
				[WeakThis](Net::Connection*, const Net::ConnectionEvent& evt)
				{
                    SharedPointerT<ClientTask_JoinGameServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameServer>();
                    if (This.IsValid())
                    {
                        This->OnConnectionEvent(evt);
                    }
				});

			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(&m_Owner),
				[WeakThis](Net::Connection*, const Net::ConnectionEvent& evt)
				{
                    SharedPointerT<ClientTask_JoinGameServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameServer>();
                    if (This.IsValid())
                    {
                        if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
                        {
                            This->GetOwner().ClearInstanceInfo();
                            This->GetOwner().UpdateOnlineStateByConnectionState();
                        }
                    }
				});

            GetConnection()->GetRecvMessageDelegates().AddDelegateUnique(uintptr_t(this), [WeakThis](Net::Connection* pConnection, const MessageHeader* pMessageHeader)
                {
                    SharedPointerT<ClientTask_JoinGameServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameServer>();
                    if (This.IsValid())
                    {
                        This->m_MessageHandlerMap.OnMessage(pMessageHeader);
                    }
                });

			AuthTicket authTicket = m_Owner.GetAuthTicket();
			String remoteAddress = m_Owner.GetGameServerAddress();
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
            Result result = NetAddress::ParseNameAddress(m_Owner.GetGameServerAddress(), netAddresses);
            if (!result)
            {
                SFLog(Net, Error, "Failed to get addresses: {0}, hr:{1}", m_Owner.GetGameServerAddress(), result);
                SetResult(result);
                GetConnection()->Disconnect("JoinGameServer failed");
                SetOnlineState(OnlineState::Disconnected);
                return;
            }

            if (netAddresses.size() == 0)
            {
                SFLog(Net, Error, "Failed to convert addresses: {0}", m_Owner.GetGameServerAddress());
                SetResult(ResultCode::NOT_EXIST);
                GetConnection()->Disconnect("JoinGameServer failed");
                SetOnlineState(OnlineState::Disconnected);
                return;
            }

            m_GameServerNetAddress = netAddresses[0];
			result = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, m_GameServerNetAddress, 0));
			if (result)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
				SetOnlineState(OnlineState::ConnectingToGameServer);
			}
			else
			{
				SFLog(Net, Error, "Failed to connect to game server:{0}, hr:{1}", m_GameServerNetAddress, result);
				SetOnlineState(OnlineState::Disconnected);
			}
		}

		virtual ~ClientTask_JoinGameServer()
		{
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			SFLog(Net, Info, "Game OnConnectionEvent  type:{0}, state:{1}", evt.Components.EventType, evt.Components.State);
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					SetOnlineState(OnlineState::JoiningToGameServer);
					GameRPCSendAdapter policy(GetConnection()->GetMessageEndpoint());
					Result res = policy.JoinGameServerCmd(intptr_t(this), m_Owner.GetAccountId(), m_Owner.GetAuthTicket(), 0);
					if (!res)
					{
						SFLog(Net, Error, "JoinGameServer command has failed {0}", res);
                        GetConnection()->Disconnect("JoinGameServer failed");
                        SetOnlineState(OnlineState::Disconnected);
                        SetResult(ResultCode::IO_DISCONNECTED);
                    }
				}
				else
				{
					GetConnection()->Disconnect("JoinGameServer failed");
				}
			}
			else if (evt.Components.EventType == Net::ConnectionEvent::EVT_DISCONNECTED)
			{
                SFLog(Net, Error, "Failed to connect to game server:{0}({1}), probably unreachable, hr:{2}", m_Owner.GetGameServerAddress(), m_GameServerNetAddress, evt.Components.hr);
                SetOnlineState(OnlineState::Disconnected);
                SetResult(ResultCode::IO_DISCONNECTED);
			}
		}


		void OnJoinGameServerRes(const MessageHeader* pHeader)
		{
            const auto* responseData = flatbuffers::GetRoot<Flat::Game::JoinGameServerRes>(pHeader->GetPayloadPtr());
			if (!responseData)
			{
				SFLog(Net, Error, "Game::JoinGameServerRes: Packet parsing error");
				SetResult(ResultCode::INVALID_FORMAT);
				Disconnect();
				return;
			}

            Result hr(responseData->result());
			if (!hr)
			{
				SFLog(Net, Error, "Game::JoinGameServerRes: failure: {0}", hr);
				SetResult(hr);
				Disconnect();
				return;
			}

            m_Owner.m_NickName = responseData->nick_name()->c_str();
			m_Owner.m_GameInstanceUID = SF::Flat::Helper::ParseGameInstanceUID(responseData->game_uid());
            m_Owner.m_PartyUID = responseData->party_uid();

            m_Owner.m_PartyLeaderId = SF::Flat::Helper::ParseAccountID(responseData->party_leader_id());
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

    private:

        MessageDelegateMap m_MessageHandlerMap;

	public:

		ClientTask_JoinGameInstanceServer(OnlineClient& owner, uint64_t transactionId)
			: ClientTask(owner, transactionId)
		{

            m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
                Message::PlayInstance::MID_JoinPlayInstanceRes,
                [this](const MessageHeader* pHeader)
                {
                    OnPlayInstanceJoinGameInstanceRes(pHeader);
                });

            m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
                Message::Game::MID_JoinGameInstanceRes,
                [this](const MessageHeader* pHeader)
                {
                    OnJoinGameInstanceRes(pHeader);
                });

		}

        virtual void Dispose() override
        {
            SFLog(Net, Info, "Finished ClientTask_JoinGameInstanceServer");

            if (m_Owner.GetConnectionGame() != nullptr)
                m_Owner.GetConnectionGame()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));

            if (m_Owner.GetOnlineState() != OnlineState::InGameInGameInstance)
            {
                m_Owner.ClearInstanceInfo();
                Disconnect();
            }

            if (GetConnection() == nullptr)
                return;

            GetConnection()->GetConnectionEventDelegates().RemoveDelegateAll(uintptr_t(this));
            GetConnection()->GetRecvMessageDelegates().RemoveDelegateAll(uintptr_t(this));

            super::Dispose();
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

            WeakPointerT<ClientTask_JoinGameInstanceServer> WeakThis = AsSharedPtr<ClientTask_JoinGameInstanceServer>();

			GetConnection()->GetConnectionEventDelegates().AddDelegateUnique(uintptr_t(this),
				[WeakThis](Net::Connection*, const Net::ConnectionEvent& evt)
				{
                    SharedPointerT<ClientTask_JoinGameInstanceServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameInstanceServer>();
                    if (This.IsValid())
                    {
                        This->OnConnectionEvent(evt);
                    }
				});

            GetConnection()->GetRecvMessageDelegates().AddDelegateUnique(uintptr_t(this), [WeakThis](Net::Connection* pConnection, const MessageHeader* pMessageHeader)
                {
                    SharedPointerT<ClientTask_JoinGameInstanceServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameInstanceServer>();
                    if (This.IsValid())
                    {
                        This->m_MessageHandlerMap.OnMessage(pMessageHeader);
                    }
                });

            m_Owner.GetConnectionGame()->GetRecvMessageDelegates().AddDelegateUnique(uintptr_t(this), [WeakThis](Net::Connection* pConnection, const MessageHeader* pMessageHeader)
                {
                    SharedPointerT<ClientTask_JoinGameInstanceServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameInstanceServer>();
                    if (This.IsValid())
                    {
                        This->m_MessageHandlerMap.OnMessage(pMessageHeader);
                    }
                });

			m_Owner.RegisterPlayInstanceHandlers();
			

			SetOnlineState(OnlineState::InGameJoiningGameInstance);
			GameRPCSendAdapter policy(m_Owner.GetConnectionGame()->GetMessageEndpoint());
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
		}

		void OnConnectionEvent(const Net::ConnectionEvent& evt)
		{
			SFLog(Net, Info, "GameInstance OnConnectionEvent  type:{0}, state:{1}", evt.Components.EventType, evt.Components.State);
			if (evt.Components.EventType == Net::ConnectionEvent::EVT_CONNECTION_RESULT)
			{
				if (evt.Components.hr)
				{
					PlayInstanceRPCSendAdapter policy(m_Owner.GetConnectionGameInstance()->GetMessageEndpoint());
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
                SFLog(Net, Error, "Failed to connect to game instance server:{0}, probably unreachable, hr:{1}", m_Owner.GetGameInstanceAddress(), evt.Components.hr);

				m_Owner.UpdateOnlineStateByConnectionState();
				SetResult(ResultCode::IO_DISCONNECTED);
			}
		}

		void OnJoinGameInstanceRes(const MessageHeader* pHeader)
		{
            const auto* responseData = flatbuffers::GetRoot<Flat::Game::JoinGameInstanceRes>(pHeader->GetPayloadPtr());
            if (!responseData)
			{
				SFLog(Net, Error, "JoinGameInstanceRes: Packet parsing error");
				SetResult(ResultCode::INVALID_FORMAT);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

            Result hr(responseData->result());
			if (!hr)
			{
				SFLog(Net, Error, "JoinGameInstanceRes: failure: {0}", hr);
				SetResult(hr);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

            m_Owner.SetupInstanceInfo();
            m_Owner.m_GameInstanceUID = SF::Flat::Helper::ParseGameInstanceUID(responseData->ins_uid());
            m_Owner.m_GameInstanceAddress = responseData->server_public_address()->c_str();
			
			SFLog(Net, Info, "Game instance joined: {0}, game:{1}, {2}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress);

			SetOnlineState(OnlineState::InGameConnectingGameInstance);

            DynamicArray<NetAddress> netAddresses;
            hr = NetAddress::ParseNameAddress(m_Owner.GetGameInstanceAddress(), netAddresses);
            if (!hr)
            {
                SFLog(Net, Error, "Failed to get addresses: gameId:{0}, game:{1}, hr:{2}", m_Owner.m_GameInstanceUID, m_Owner.m_GameInstanceAddress, hr);
                SetResult(hr);
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
            hr = GetConnection()->Connect(Net::PeerInfo(NetClass::Client, authTicket), Net::PeerInfo(NetClass::Unknown, netAddresses[0], 0));
			if (hr)
			{
				GetConnection()->SetTickGroup(EngineTaskTick::AsyncTick);
			}
		}

		void OnPlayInstanceJoinGameInstanceRes(const MessageHeader* pHeader)
		{
            const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::JoinPlayInstanceRes>(pHeader->GetPayloadPtr());
			if (!responseData)
			{
				SFLog(Net, Error, "PlayInstance::JoinPlayInstanceRes: Packet parsing error");
				SetResult(ResultCode::INVALID_FORMAT);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

            Result hr(responseData->result());
			if (!hr)
			{
				SFLog(Net, Error, "PlayInstance::JoinPlayInstanceRes: failure: {0}", hr);
				SetResult(hr);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

            PlayerID recvPlayerId = SF::Flat::Helper::ParseAccountID(responseData->player_id());
			if (m_Owner.GetPlayerID() != recvPlayerId)
			{
				SFLog(Net, Error, "PlayInstance::JoinPlayInstanceRes: failure: invalid playerId, owner:{0}, packet:{1}", m_Owner.GetPlayerID(), recvPlayerId);
				SetResult(ResultCode::INVALID_PLAYERID);
				SetOnlineState(OnlineState::InGameServer);
				return;
			}

            ActorMovement actorMovement = SF::Flat::Helper::ParseActorMovement(responseData->movement());

			SFLog(Net, Info, "PlayInstance::JoinPlayInstanceRes joined: {0}, F:{1:X}", m_Owner.m_GameInstanceUID, actorMovement.MoveFrame);

			m_Owner.InitMovement(actorMovement.ActorId, actorMovement);

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


        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::Game::MID_SelectCharacterRes,
            [this](const MessageHeader* pMsgData)
            {
                const auto* responseData = flatbuffers::GetRoot<Flat::Game::SelectCharacterRes>(pMsgData->GetPayloadPtr());
                if (responseData)
                {
                    m_CharacterId = SF::Flat::Helper::ParseCharacterID(responseData->character_id());
                }
            });


        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::Game::MID_LeaveGameInstanceRes,
            [this](const MessageHeader* pMsgData)
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


        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::MID_NewActorInViewS2CEvt,
            [this](const MessageHeader* pMsgData)
            {
                OnActorInView(pMsgData);
            });

        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::MID_RemoveActorFromViewS2CEvt,
            [this](const MessageHeader* pMsgData)
            {
                OnActorOutofView(pMsgData);
            });

        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::MID_ActorMovementS2CEvt,
            [this](const MessageHeader* pMsgData)
            {
                OnActorMovement(pMsgData);
            });

        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::MID_ActorMovementsS2CEvt,
            [this](const MessageHeader* pMsgData)
            {
                OnActorMovements(pMsgData);
            });

        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::MID_VoiceDataS2CEvt,
            [this](const MessageHeader* pMsgData)
            {
                OnVoiceData(pMsgData);
            });

        m_MessageHandlerMap.AddMessageDelegateUnique(uintptr_t(this),
            Message::PlayInstance::MID_PlayerStateChangedS2CEvt,
            [this](const MessageHeader* pMsgData)
            {
                OnPlayerStateChanged(pMsgData);
            });

        return hr;
    }

	void OnlineClient::ClearTasks()
	{
		m_CurrentTask.reset();
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

        m_Game->GetRecvMessageDelegates().AddDelegateUnique(uintptr_t(this), [this](Net::Connection* pConnection, const MessageHeader* pMessageHeader)
            {
                //SharedPointerT<ClientTask_JoinGameServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameServer>();
                //if (This.IsValid())
                {
                    m_MessageHandlerMap.OnMessage(pMessageHeader);
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

        m_GameInstance->GetRecvMessageDelegates().AddDelegateUnique(uintptr_t(this), [this](Net::Connection* pConnection, const MessageHeader* pMessageHeader)
            {
                //SharedPointerT<ClientTask_JoinGameServer> This = WeakThis.AsSharedPtr<ClientTask_JoinGameServer>();
                //if (This.IsValid())
                {
                    m_MessageHandlerMap.OnMessage(pMessageHeader);
                }
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

	Result OnlineClient::JoinGameInstance(uint64_t transactionId, GameInstanceUID gameInstanceId)
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
						GameRPCSendAdapter policy(m_Game->GetMessageEndpoint());
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
		if (m_CurrentTask.IsValid())
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
			m_CurrentTask = m_PendingTasks[0];
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
			PlayInstanceRPCSendAdapter policy(GetConnectionGameInstance()->GetMessageEndpoint());
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

        if (m_CurrentTask.IsValid())
        {
            m_CurrentTask->OnEngineTickUpdate();
        }

        return hr;
    }

    void OnlineClient::OnActorInView(const MessageHeader* pMsgData)
    {
        const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::NewActorInViewS2CEvt>(pMsgData->GetPayloadPtr());
        if (!responseData)
        {
            SFLog(Net, Info, "OnlineClient::OnActorInView Parsing error");
            return;
        }

        if (SF::Flat::Helper::ParseGameInstanceUID(responseData->play_instance_uid()) != m_GameInstanceUID)
        {
            SFLog(Net, Info, "Invalid instance id, ignoring movement");
            return;
        }

        ActorMovement actorMovement = SF::Flat::Helper::ParseActorMovement(responseData->movement());

        ActorID actorId = actorMovement.ActorId;
        OnlineActor* onlineActor{};
        if (!m_OnlineActorByActorId.Find(actorId, onlineActor))
        {
            onlineActor = new(GetHeap()) OnlineActor(actorId);
            m_OnlineActorByActorId.Emplace(actorId, onlineActor);
        }

        onlineActor->SetMovement(actorMovement);
    }

    void OnlineClient::OnActorOutofView(const MessageHeader* pMsgData)
    {
        const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::RemoveActorFromViewS2CEvt>(pMsgData->GetPayloadPtr());
        if (!responseData)
        {
            SFLog(Net, Info, "OnlineClient::OnActorOutofView Parsing error");
            return;
        }

        if (SF::Flat::Helper::ParseGameInstanceUID(responseData->play_instance_uid()) != m_GameInstanceUID)
        {
            SFLog(Net, Info, "Invalid instance id, ignoring movement");
            return;
        }

        OnlineActor* onlineActor{};
        m_OnlineActorByActorId.Remove(responseData->actor_id(), onlineActor);
        if (onlineActor)
        {
            IHeap::Delete(onlineActor);
        }
    }

    void OnlineClient::OnActorMovement(const MessageHeader* pMsgData)
    {
        const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::ActorMovementS2CEvt>(pMsgData->GetPayloadPtr());
        if (!responseData)
        {
            SFLog(Net, Error, "OnlineClient::OnPlayerMovement Parsing error");
            return;
        }

        if (SF::Flat::Helper::ParseGameInstanceUID(responseData->play_instance_uid()) != m_GameInstanceUID)
        {
            SFLog(Net, Warning, "Invalid instance id, ignoring movement");
            return;
        }

        ActorMovement actorMovement = SF::Flat::Helper::ParseActorMovement(responseData->movement());

        OnActorMovement(actorMovement);
    }

    void OnlineClient::OnActorMovements(const MessageHeader* pMsgData)
    {
        const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::ActorMovementsS2CEvt>(pMsgData->GetPayloadPtr());
        if (!responseData)
        {
            SFLog(Net, Error, "OnlineClient::OnPlayerMovements Parsing error");
            return;
        }

        if (SF::Flat::Helper::ParseGameInstanceUID(responseData->play_instance_uid()) != m_GameInstanceUID)
        {
            SFLog(Net, Warning, "Invalid instance id, ignoring movements");
            return;
        }

        auto movementOffsets = responseData->movement();
        if (movementOffsets)
        {
            for (auto movement : *movementOffsets)
            {
                ActorMovement actorMovement = SF::Flat::Helper::ParseActorMovement(movement);
                OnActorMovement(actorMovement);
            }
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
        const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::VoiceDataS2CEvt>(pMsgData->GetPayloadPtr());
        if (!responseData)
        {
            SFLog(Net, Error, "OnlineClient::OnPlayerMovements Parsing error");
            return;
        }

        OnlineActor* onlineActor{};
        if (m_OnlineActorByActorId.Find(responseData->actor_id(), onlineActor))
        {
            auto* voiceData = responseData->voice_data();
            onlineActor->OnComponentData("VoiceChat"_crc, responseData->frame_index(), ArrayView<const uint8_t>(voiceData->size(), voiceData->Data()));
        }
    }

	void OnlineClient::OnPlayerStateChanged(const MessageHeader* pMsgData)
	{
        const auto* responseData = flatbuffers::GetRoot<Flat::PlayInstance::PlayerStateChangedS2CEvt>(pMsgData->GetPayloadPtr());
		if (!responseData)
		{
			SFLog(Net, Error, "OnlineClient::OnPlayerStateChanged Parsing error");
			return;
		}

		if (SF::Flat::Helper::ParseGameInstanceUID(responseData->play_instance_uid()) != m_GameInstanceUID)
		{
			SFLog(Net, Warning, "Invalid instance id, ignoring movement");
			return;
		}

		// we only interested in my player state
		if (SF::Flat::Helper::ParseAccountID(responseData->player_id()) != m_AccountId)
			return;

		m_MyPlayerState = responseData->state();
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
