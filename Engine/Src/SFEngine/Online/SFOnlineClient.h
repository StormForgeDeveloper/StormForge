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

#pragma once

#include "SFTypedefs.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "EngineObject/SFEngineObject.h"
#include "Container/SFDualSortedMap.h"
#include "Delegate/SFEventDelegate.h"
#include "Online/SFOnlineActor.h"
#include "SFOnlineClientComponent.h"
#include "Net/SFConnection.h"
#include "MessageBus/SFMessageDelegateMap.h"


namespace SF
{
	struct ActorMovement;
	class SendingActorMovementManager;
	class ReceivedActorMovementManager;
	class ActorMovementReplayManager;


	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClient class
	// 
	class OnlineClient : public EngineObject
	{
	public:

		using super = EngineObject;
		using ReceivedMovementManager = ActorMovementReplayManager;
		//using ReceivedMovementManager = ReceivedActorMovementManager;

		// Online State
		enum class OnlineState : uint8_t
		{
			None,

            // Disconnected
            Disconnected,

			// Login operations
			ConnectingToLogin,
			LogingIn,
			LoggedIn,

			// In game state
			ConnectingToGameServer,
			JoiningToGameServer,
			InGameServer,

			// In game instance state. the player still in game as well
			InGameJoiningGameInstance,
			InGameConnectingGameInstance,
			InGameGameInstanceJoining,
			InGameInGameInstance,
		};

		struct OnlineStateChangedEventArgs
		{
			OnlineState PrevState = OnlineState::None;
			OnlineState NewState = OnlineState::None;
		};

		typedef void(*ONLINESTATE_CHAGED_CALLBACK)(OnlineClient::OnlineState prevState, OnlineClient::OnlineState newState);
		typedef void(*ONLINE_TASK_FINISHED_CALLBACK)(uint64_t transactionId, int result);


		/////////////////////////////////////////////////////////////////////////////////////
		// 
		//	ClientTask class
		// 

		class ClientTask : public SharedObject
		{
		public:
			using OnlineState = OnlineClient::OnlineState;

			ClientTask(OnlineClient& owner, uint64_t transactionId);
			virtual ~ClientTask();

			IHeap& GetHeap() { return m_Owner.GetHeap(); }
            OnlineClient& GetOwner() { return m_Owner; }

			void SetOnlineState(OnlineState newState);

			uint64_t GetTransactionID() const { return m_TransactionId; }

			void SetResult(Result result) { m_Result = result; }
			Result GetResult() const { return m_Result; }

			virtual void Initialize() { m_Result = ResultCode::BUSY; }
			virtual void TickUpdate() {}
            virtual void OnEngineTickUpdate() {}

		protected:

			OnlineClient& m_Owner;
			Result m_Result = ResultCode::SUCCESS;
			uint64_t m_TransactionId{};
		};

	public:

		OnlineClient(IHeap& heap);
		virtual ~OnlineClient();

        virtual Result InitializeObject() override;

		// Initialize and start connection process
		Result StartConnection(uint64_t transactionId, StringCrc32 gameId, const char* loginAddress, uint64_t steamUserId, const char* steamUserName, const char* steamUserToken, const char* userId, const char* password);

		// Join game instance
		Result JoinGameInstance(uint64_t transactionId, GameInstanceUID gameInstanceId);

		// Disconnect all connection
		void DisconnectAll();

		// Send new movement
		Result SendMovement(const ActorMovement& newMove);

		void UpdateGameTick();

		void UpdateTasks();
		void UpdateOnlineState();

		uint32_t UpdateMovement();

        virtual Result OnTick(EngineTaskTick tick) override;

		// Online State
		SF_FORCEINLINE OnlineState GetOnlineState() const { return m_OnlineState; }

		SF_FORCEINLINE StringCrc32 GetGameId() const { return m_GameId; }
        SF_FORCEINLINE uint64_t GetSteamUserId() const { return m_SteamUserId; }
        SF_FORCEINLINE const String& GetSteamUserName() const { return m_SteamUserName; }
        SF_FORCEINLINE const String& GetSteamUserToken() const { return m_SteamUserToken; }
        SF_FORCEINLINE const String& GetUserId() const { return m_UserId; }
		SF_FORCEINLINE const String& GetPassword() const { return m_Password; }
		SF_FORCEINLINE const String& GetLoginAddresses() const { return m_LoginAddresses; }

		SF_FORCEINLINE const String& GetGameServerAddress() const { return m_GameServerAddress; }
		SF_FORCEINLINE const AccountID& GetAccountId() const { return m_AccountId; }
		SF_FORCEINLINE AuthTicket GetAuthTicket() const { return m_AuthTicket; }
		SF_FORCEINLINE const PlayerID& GetPlayerID() const { return m_AccountId; }
		ActorID GetActorID() const;

		SF_FORCEINLINE const CharacterID& GetCharacterId() const { return m_CharacterId; }

		SF_FORCEINLINE EntityUID GetGameInstanceUID() const { return m_GameInstanceUID; }
		SF_FORCEINLINE const String& GetGameInstanceAddress() const { return m_GameInstanceAddress; }

		SF_FORCEINLINE const SharedPointerT<Net::Connection>& GetConnectionGame() const { return m_Game; }
		SF_FORCEINLINE const SharedPointerT<Net::Connection>& GetConnectionGameInstance() const { return m_GameInstance; }

		SF_FORCEINLINE const SharedPointerT<SendingActorMovementManager>& GetSendMovementManager() const { return m_OutgoingMovement; }

		SF_FORCEINLINE uint32_t GetCurrentMovementFrame() const { return m_MoveFrame; }
		SF_FORCEINLINE void SetMovementFrame(uint32_t moveFrame) { m_MoveFrame = moveFrame; }

		void SetStateChangeCallback(ONLINESTATE_CHAGED_CALLBACK callback) { m_OnlineStateChangedCallback = callback; }
		void SetTaskFinishedCallback(ONLINE_TASK_FINISHED_CALLBACK callback) { m_OnlineTaskFinishedCallback = callback; }

        void AddComponent(OnlineClientComponent* pComponent) { m_ComponentManager.AddComponent(pComponent); }

	private:

		void SetOnlineState(OnlineState newState);

		void Disconnect(SharedPointerT<Net::Connection>& pConn);

		void ClearTasks();

		void InitMovement(ActorID actorId, const ActorMovement& movement);
		void SetupInstanceInfo();
		void ClearInstanceInfo();
		void RegisterGameHandlers();
		void RegisterPlayInstanceHandlers();

        void OnActorInView(const MessageHeader* pMsgData);
        void OnActorOutofView(const MessageHeader* pMsgData);
        void OnActorMovement(const MessageHeader* pMsgData);
        void OnActorMovements(const MessageHeader* pMsgData);
        void OnActorMovement(const ActorMovement& newMove);
        void OnVoiceData(const MessageHeader* pMsgData);

		void OnPlayerStateChanged(const MessageHeader* pMsgData);

		void UpdateOnlineStateByConnectionState();


	private:

		friend ClientTask;
		friend class ClientTask_Login;
        friend class ClientTask_HttpLogin;
		friend class ClientTask_JoinGameServer;
		friend class ClientTask_JoinGameInstanceServer;

		// Online state
		OnlineState m_OnlineState = OnlineState::None;

		StringCrc32 m_GameId;
        uint64_t m_SteamUserId{};
        String m_SteamUserName;
        String m_SteamUserToken;
		String m_UserId;
		String m_Password;

		String m_LoginAddresses;

		String m_GameServerAddress;
		AccountID m_AccountId{};
		AuthTicket m_AuthTicket{};

		String m_NickName;
		CharacterID m_CharacterId{};
		GameInstanceUID m_GameInstanceUID{};
		StringCrc32 m_MyPlayerState;
		uint64_t m_PartyUID{};
		AccountID m_PartyLeaderId{};

        String m_GameInstanceAddress;

		// connections
		SharedPointerT<Net::Connection> m_Game;
		SharedPointerT<Net::Connection> m_GameInstance;

		TimeStampMS m_HeartbeatTimer{};

		SharedPointerT<ClientTask> m_CurrentTask;
		DynamicArray<SharedPointerT<ClientTask>> m_PendingTasks;
        struct FinishedTaskInfo
        {
            uint64_t TransactionId = 0;
            Result hr;

            bool operator == (const FinishedTaskInfo& op) { return TransactionId == op.TransactionId && hr == op.hr; }
        };
		CircularQueue<FinishedTaskInfo, 4> m_FinishedTaskTransactionIds;

		// My actor movement
		SharedPointerT<SendingActorMovementManager> m_OutgoingMovement;

        SortedMap<ActorID, OnlineActor*> m_OnlineActorByActorId;

		// tick time
		TimeStampMS m_TickTime;
        TimeStampMS m_PreviousTickTime;

		// Move frame
		uint32_t m_MoveFrame{};
		// Estimated server move frame
		uint32_t m_ServerMoveFrame{};

        // Online status event queue
		CircularPageQueue<OnlineStateChangedEventArgs> m_OnlineStateChangedQueue;
		ONLINESTATE_CHAGED_CALLBACK m_OnlineStateChangedCallback{};
		ONLINE_TASK_FINISHED_CALLBACK m_OnlineTaskFinishedCallback{};

        ComponentManager m_ComponentManager;

        // message handler
        MessageDelegateMap m_MessageHandlerMap;

	};


}

template<> inline bool IsDefaultValue(const SF::OnlineClient::OnlineStateChangedEventArgs& value) { return value.PrevState == SF::OnlineClient::OnlineState::None && value.NewState == SF::OnlineClient::OnlineState::None; }

