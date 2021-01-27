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


namespace SF
{
	namespace Net
	{
		class Connection;
	}

	class SendingActorMovementManager;
	class ReceivedActorMovementManager;



	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	OnlineClient class
	// 
	class OnlineClient : public EngineObject
	{
	public:

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
			InGameConnectingGameInstance,
			InGameJoiningGameInstance,
			InGameInGameInstance,

			// Disconnected
			Disconnected,
		};



		/////////////////////////////////////////////////////////////////////////////////////
		// 
		//	ClientTask class
		// 

		class ClientTask
		{
		public:
			using OnlineState = OnlineClient::OnlineState;

			ClientTask(OnlineClient& owner);
			virtual ~ClientTask();

			IHeap& GetHeap() { return m_Owner.GetHeap(); }

			void SetOnlineState(OnlineState newState);

			void SetResult(Result result) { m_Result = result; }
			Result GetResult() const { return m_Result; }

			virtual void TickUpdate() {}

		protected:

			OnlineClient& m_Owner;
			Result m_Result = ResultCode::SUCCESS;
		};

	public:

		OnlineClient();
		virtual ~OnlineClient();


		// Initialize and start connection process
		void StartConnection(StringCrc32 gameId, const char* loginAddress, const char* userId, const char* password);

		// Disconnect all connection
		void DisconnectAll();

		void UpdateGameTick();

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


		const SharedPointerT<Net::Connection>& GetConnectionLogin() const { return m_Login; }
		const SharedPointerT<Net::Connection>& GetConnectionGame() const { return m_Game; }
		const SharedPointerT<Net::Connection>& GetConnectionGameInstance() const { return m_GameInstance; }

	private:

		void SetOnlineState(OnlineState newState) { m_OnlineState = newState; }

		void Disconnect(SharedPointerT<Net::Connection>& pConn);

		void ClearTasks();

	private:

		friend ClientTask;
		friend class ClientTask_Login;
		friend class ClientTask_JoinGameServer;

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
		uint64_t m_GameInstanceUID;
		uint64_t m_PartyUID;
		uint64_t m_PartyLeaderId;

		// connections
		SharedPointerT<Net::Connection> m_Login;
		SharedPointerT<Net::Connection> m_Game;
		SharedPointerT<Net::Connection> m_GameInstance;


		UniquePtr<ClientTask> m_CurrentTask;
		DynamicArray<ClientTask*> m_PendingTasks;

		// My actor movement
		SharedPointerT<SendingActorMovementManager> m_OutgoingMovement;

		// PlayerId by movement
		DualSortedMap<PlayerID,SharedPointerT<ReceivedActorMovementManager>> m_IncomingMovements;
	};

}

