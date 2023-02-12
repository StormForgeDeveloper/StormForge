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


namespace SF
{
	namespace Net
	{
		class Connection;
	}

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

		// TODO: Let's make it dynamic from 10 to 35 or even 60 for worst network.
		static constexpr uint32_t RemotePlayerSimulationDelay = 30;

		// Online State
		enum class OnlineState : uint8_t
		{
			None,

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

			// Disconnected
			Disconnected,
		};

		struct OnlineStateChangedEventArgs
		{
			OnlineState PrevState = OnlineState::None;
			OnlineState NewState = OnlineState::None;
		};

		typedef void(*ONLINESTATE_CHAGED_CALLBACK)(OnlineClient::OnlineState prevState, OnlineClient::OnlineState newState);
		typedef void(*ONLINE_TASK_FINISHED_CALLBACK)(uint64_t transactionId);


		/////////////////////////////////////////////////////////////////////////////////////
		// 
		//	ClientTask class
		// 

		class ClientTask
		{
		public:
			using OnlineState = OnlineClient::OnlineState;

			ClientTask(OnlineClient& owner, uint64_t transactionId);
			virtual ~ClientTask();

			IHeap& GetHeap() { return m_Owner.GetHeap(); }

			void SetOnlineState(OnlineState newState);

			uint64_t GetTransactionID() const { return m_TransactionId; }

			void SetResult(Result result) { m_Result = result; }
			Result GetResult() const { return m_Result; }

			virtual void Initialize() { m_Result = ResultCode::BUSY; }
			virtual void TickUpdate() {}

		protected:

			OnlineClient& m_Owner;
			Result m_Result = ResultCode::SUCCESS;
			uint64_t m_TransactionId{};
		};

	public:

		OnlineClient(IHeap& heap);
		virtual ~OnlineClient();


		// Initialize and start connection process
		Result StartConnection(uint64_t transactionId, StringCrc32 gameId, const char* loginAddress, uint64_t steamUserId, const char* steamUserName, const char* steamUserToken, const char* userId, const char* password);

		// Join game instance
		Result JoinGameInstance(uint64_t transactionId, uint64_t gameInstanceId);

		// Disconnect all connection
		void DisconnectAll();

		// Send new movement
		Result SendMovement(const ActorMovement& newMove);

		void UpdateGameTick();

		void UpdateTasks();
		void UpdateOnlineState();

		uint32_t UpdateMovement();

		// Online State
		SF_FORCEINLINE OnlineState GetOnlineState() const { return m_OnlineState; }

		SF_FORCEINLINE StringCrc32 GetGameId() const { return m_GameId; }
        SF_FORCEINLINE uint64_t GetSteamUserId() const { return m_SteamUserId; }
        SF_FORCEINLINE const String& GetSteamUserName() const { return m_SteamUserName; }
        SF_FORCEINLINE const String& GetSteamUserToken() const { return m_SteamUserToken; }
        SF_FORCEINLINE const String& GetUserId() const { return m_UserId; }
		SF_FORCEINLINE const String& GetPassword() const { return m_Password; }
		SF_FORCEINLINE const String& GetLoginAddresses() const { return m_LoginAddresses; }

		SF_FORCEINLINE uint64_t GetLoginEntityUID() const { return m_LoginEntityUID; }
		SF_FORCEINLINE const String& GetGameAddress() const { return m_GameAddress; }
		SF_FORCEINLINE AccountID GetAccountId() const { return m_AccountId; }
		SF_FORCEINLINE AuthTicket GetAuthTicket() const { return m_AuthTicket; }
		SF_FORCEINLINE PlayerID GetPlayerID() const { return m_AccountId; }
		ActorID GetActorID() const;

		SF_FORCEINLINE uint32_t GetCharacterId() const { return m_CharacterId; }

		SF_FORCEINLINE uint64_t GetGameInstanceUID() const { return m_GameInstanceUID; }
		SF_FORCEINLINE const String& GetGameInstanceAddress() const { return m_GameInstanceAddress; }

		SF_FORCEINLINE const SharedPointerT<Net::Connection>& GetConnectionLogin() const { return m_Login; }
		SF_FORCEINLINE const SharedPointerT<Net::Connection>& GetConnectionGame() const { return m_Game; }
		SF_FORCEINLINE const SharedPointerT<Net::Connection>& GetConnectionGameInstance() const { return m_GameInstance; }

		SF_FORCEINLINE const SharedPointerT<SendingActorMovementManager>& GetSendMovementManager() const { return m_OutgoingMovement; }
		Result GetMovementForPlayer(PlayerID playerId, ActorMovement& outMovement);
		Result GetMovementForPlayerAll(PlayerID playerId, ActorMovement& outMovement, ActorMovement& outReceivedMovement, ActorMovement& outExpectedMovement);
		Result GetMovementForActor(ActorID actorId, ActorMovement& outMovement);
		Result GetMovementForActorAll(ActorID actorId, ActorMovement& outMovement, ActorMovement& outReceivedMovement, ActorMovement& outExpectedMovement);

		SF_FORCEINLINE uint32_t GetCurrentMovementFrame() const { return m_MoveFrame; }
		SF_FORCEINLINE void SetMovementFrame(uint32_t moveFrame) { m_MoveFrame = moveFrame; }

		void SetStateChangeCallback(ONLINESTATE_CHAGED_CALLBACK callback) { m_OnlineStateChangedCallback = callback; }
		void SetTaskFinishedCallback(ONLINE_TASK_FINISHED_CALLBACK callback) { m_OnlineTaskFinishedCallback = callback; }

	private:

		void SetOnlineState(OnlineState newState);

		void Disconnect(SharedPointerT<Net::Connection>& pConn);

		void ClearTasks();

		void InitMovement(ActorID actorId, uint32_t newMoveFrame);
		void SetupInstanceInfo();
		void ClearInstanceInfo();
		void RegisterGameHandlers();
		void RegisterPlayInstanceHandlers();

		void OnActorInView(const MessageDataPtr& pMsgData);
		void OnActorOutofView(const MessageDataPtr& pMsgData);
		void OnActorMovement(const MessageDataPtr& pMsgData);
		void OnActorMovements(const MessageDataPtr& pMsgData);
		void OnActorMovement(const ActorMovement& movement);
		void OnPlayerStateChanged(const MessageDataPtr& pMsgData);

		void UpdateOnlineStateByConnectionState();

	private:

		friend ClientTask;
		friend class ClientTask_Login;
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

		uint64_t m_LoginEntityUID{};
		String m_GameAddress;
		AccountID m_AccountId{};
		AuthTicket m_AuthTicket{};

		String m_NickName;
		uint32_t m_CharacterId{};
		uint64_t m_GameInstanceUID{};
		StringCrc32 m_MyPlayerState;
		uint64_t m_PartyUID{};
		uint64_t m_PartyLeaderId{};

        String m_GameInstanceAddress;

		// connections
		SharedPointerT<Net::Connection> m_Login;
		SharedPointerT<Net::Connection> m_Game;
		SharedPointerT<Net::Connection> m_GameInstance;

		TimeStampMS m_HeartbeatTimer{};

		SFUniquePtr<ClientTask> m_CurrentTask;
		DynamicArray<ClientTask*> m_PendingTasks;
		CircularQueue<uint64_t, 4> m_FinishedTaskTransactionIds;

		// My actor movement
		SharedPointerT<SendingActorMovementManager> m_OutgoingMovement;

		// PlayerId by movement
		SortedMap<PlayerID,SharedPointerT<ReceivedMovementManager>> m_IncomingMovements;
		SortedMap<ActorID, SharedPointerT<ReceivedMovementManager>> m_IncomingMovementsByActor;

		// tick time
		TimeStampMS m_TickTime;

		// Move frame
		uint32_t m_MoveFrame{};
		// Estimated server move frame
		uint32_t m_ServerMoveFrame{};

        // Online status event queue
		CircularPageQueue<OnlineStateChangedEventArgs> m_OnlineStateChangedQueue;
		ONLINESTATE_CHAGED_CALLBACK m_OnlineStateChangedCallback{};
		ONLINE_TASK_FINISHED_CALLBACK m_OnlineTaskFinishedCallback{};
	};


}

template<> inline bool IsDefaultValue(const SF::OnlineClient::OnlineStateChangedEventArgs& value) { return value.PrevState == SF::OnlineClient::OnlineState::None && value.NewState == SF::OnlineClient::OnlineState::None; }

