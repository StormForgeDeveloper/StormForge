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



	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClient class
	// 
	class OnlineClient : public EngineObject
	{
	public:

		using super = EngineObject;

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
		Result StartConnection(uint64_t transactionId, StringCrc32 gameId, const char* loginAddress, const char* userId, const char* password);

		// Join game instance
		Result JoinGameInstance(uint64_t transactionId, uint64_t gameInstanceId);

		// Disconnect all connection
		void DisconnectAll();

		void UpdateGameTick();

		void UpdateTasks();
		void UpdateOnlineState();

		void UpdateMovement(uint32_t deltaFrames);

		// Online State
		OnlineState GetOnlineState() const { return m_OnlineState; }

		StringCrc32 GetGameId() const { return m_GameId; }
		const String& GetUserId() const { return m_UserId; }
		const String& GetPassword() const { return m_Password; }
		const String& GetLoginAddresses() const { return m_LoginAddresses; }

		uint64_t GetLoginEntityUID() const { return m_LoginEntityUID; }
		const NetAddress& GetGameAddress() const { return m_GameAddress; }
		const NetAddress& GetGameAddress4() const { return m_GameAddress4; }
		AccountID GetAccountId() const { return m_AccountId; }
		AuthTicket GetAuthTicket() const { return m_AuthTicket; }
		PlayerID GetPlayerID() const { return m_AccountId; }

		uint32_t GetCharacterId() const { return m_CharacterId; }

		uint64_t GetGameInstanceUID() const { return m_GameInstanceUID; }
		const NetAddress& GetGameInstanceAddress4() const { return m_GameInstanceAddress4; }
		const NetAddress& GetGameInstanceAddress6() const { return m_GameInstanceAddress6; }

		const SharedPointerT<Net::Connection>& GetConnectionLogin() const { return m_Login; }
		const SharedPointerT<Net::Connection>& GetConnectionGame() const { return m_Game; }
		const SharedPointerT<Net::Connection>& GetConnectionGameInstance() const { return m_GameInstance; }

		const SharedPointerT<SendingActorMovementManager>& GetSendMovementManager() const { return m_OutgoingMovement; }
		Result GetMovementForPlayer(PlayerID playerId, ActorMovement& outMovement);
		Result GetMovementForPlayerAll(PlayerID playerId, ActorMovement& outMovement, ActorMovement& outReceivedMovement, ActorMovement& outExpectedMovement);
		Result GetExpectedMovementForPlayer(PlayerID playerId, ActorMovement& outMovement);
		Result GetReceivedMovementForPlayer(PlayerID playerId, ActorMovement& outMovement);

		uint32_t GetCurrentMovementFrame() const { return m_MoveFrame; }
		void SetMovementFrame(uint32_t moveFrame) { m_MoveFrame = moveFrame; }

		void SetStateChangeCallback(ONLINESTATE_CHAGED_CALLBACK callback) { m_OnlineStateChangedCallback = callback; }
		void SetTaskFinishedCallback(ONLINE_TASK_FINISHED_CALLBACK callback) { m_OnlineTaskFinishedCallback = callback; }

	private:

		void SetOnlineState(OnlineState newState);

		void Disconnect(SharedPointerT<Net::Connection>& pConn);

		void ClearTasks();

		void SetupInstanceInfo();
		void ClearInstanceInfo();
		void RegisterGameHandlers();
		void RegisterPlayInstanceHandlers();

		void OnPlayerInView(const MessageDataPtr& pMsgData);
		void OnPlayerOutofView(const MessageDataPtr& pMsgData);
		void OnPlayerMovement(const MessageDataPtr& pMsgData);
		void OnPlayerMovement(PlayerID playerId, const ActorMovement& movement);

		void UpdateOnlineStateByConnectionState();

	private:

		friend ClientTask;
		friend class ClientTask_Login;
		friend class ClientTask_JoinGameServer;
		friend class ClientTask_JoinGameInstanceServer;

		// Online state
		OnlineState m_OnlineState = OnlineState::None;

		StringCrc32 m_GameId;
		String m_UserId;
		String m_Password;

		String m_LoginAddresses;

		uint64_t m_LoginEntityUID{};
		NetAddress m_GameAddress;
		NetAddress m_GameAddress4;
		AccountID m_AccountId{};
		AuthTicket m_AuthTicket{};

		String m_NickName;
		uint32_t m_CharacterId{};
		uint64_t m_GameInstanceUID{};
		uint64_t m_PartyUID{};
		uint64_t m_PartyLeaderId{};

		NetAddress m_GameInstanceAddress4;
		NetAddress m_GameInstanceAddress6;

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
		SortedMap<PlayerID,SharedPointerT<ReceivedActorMovementManager>> m_IncomingMovements;

		// Move frame
		uint32_t m_MoveFrame{};

		CircularPageQueue<OnlineStateChangedEventArgs> m_OnlineStateChangedQueue;
		ONLINESTATE_CHAGED_CALLBACK m_OnlineStateChangedCallback{};
		ONLINE_TASK_FINISHED_CALLBACK m_OnlineTaskFinishedCallback{};
	};


}

template<> inline bool IsDefaultValue(const SF::OnlineClient::OnlineStateChangedEventArgs& value) { return value.PrevState == SF::OnlineClient::OnlineState::None && value.NewState == SF::OnlineClient::OnlineState::None; }

