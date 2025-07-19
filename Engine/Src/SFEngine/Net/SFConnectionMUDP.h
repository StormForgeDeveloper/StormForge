////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net connection classes. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFCircularPageQueue.h"
#include "Net/SFConnectionUDPBase.h"
#include "Net/SFConnectionActions.h"


namespace SF {
namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Mobile UDP Network connection class
	//

	class ConnectionMUDP : public ConnectionUDPBase
	{
	public:

		using super = ConnectionUDPBase;

	protected:

		friend class ConnectionStateAction_SendSync;
		friend class ConnectionStateAction_SendSyncSvr;
		friend class ConnectionMessageAction_MUDPHandleSyncReliableServer;

	public:
		// Constructor
		ConnectionMUDP(SocketIO* ioHandler);
		virtual ~ConnectionMUDP();
	protected:

		// gathering
		virtual Result SendSync( uint uiSequence, uint64_t uiSyncMask );

		// We are using send sync mask rather than per message
		virtual Result SendReliableMessageAck(MessageID msgID) override { return ResultCode::SUCCESS; }

        virtual Result TickUpdate() override;
	};




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Client Mobile UDP Network connection class
	//

	class ConnectionMUDPClient : public ConnectionMUDP
	{
	public:
        typedef ConnectionMUDP super;

		class MyNetSocketIOAdapter : public SocketIOUDP
		{
		private:
            using super = SocketIOUDP;

			ConnectionMUDPClient &m_Owner;
			Result m_LastResult;

		public:

			MyNetSocketIOAdapter(ConnectionMUDPClient &owner);

			Result GetLastResult() { return m_LastResult; }

			// Send message to connection with network device
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

			virtual Result OnWriteReady() override;

            virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ*& pIOBuffer) override;
            virtual Result OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE* pIOBuffer) override;
        };


		class MyNetSocketIOManager
		{
		private:
			ConnectionMUDPClient &m_Owner;

			// Pending free items
			CircularPageQueue<MyNetSocketIOAdapter*> m_PendingFree;

			// There is a crash when you try to close connection on multiple thread
			CriticalSection m_ManagerLock;

			MyNetSocketIOAdapter* m_PendingFreeCache = nullptr;

			MyNetSocketIOAdapter* m_ActiveAdapter = nullptr;

		public:

			MyNetSocketIOManager(ConnectionMUDPClient& owner);

			void Init();

			Result NewIOHandler();

			void FreeCurrentHandler();

			void FlushFreedHandlers();

			bool ValidateNetIOAdapter();

			bool CanDelete();

			void Dispose();

			MyNetSocketIOAdapter* GetActiveNetIOAdapter() { return m_ActiveAdapter; }

			
		};

	private:

		// Net IO adapter.
		//MyNetSocketIOAdapter m_NetIOAdapter;

		MyNetSocketIOManager m_NetIOAdapterManager;

		// Sync tick counter
		TimeStampMS m_ReliableSyncTime;

		// Event actions
		ConnectionMessageAction_MUDPHandleSyncReliableClient m_HandleSyncReliableClient;
		ConnectionMessageAction_HandleTimeSyncRtn m_HandleTimeSyncRtn;

		ConnectionStateAction_TimeoutConnecting m_TimeoutConnecting;
		ConnectionStateAction_SendConnect m_SendConnect;
		ConnectionStateAction_TimeoutDisconnecting m_TimeoutDisconnecting;
		ConnectionStateAction_SendDisconnect m_SendDisconnect;

		ConnectionStateAction_SendSync m_ActSendSync;

        ConnectionStateAction_ValidateNetIOAdapter m_ValidateNetIO;

		// Client side CID generator
		static std::atomic<uint64_t> stm_CIDGen;

	public:
		// Constructor
		ConnectionMUDPClient();
		virtual ~ConnectionMUDPClient();

        SF_FORCEINLINE MyNetSocketIOManager& GetNetIOAdapterManager() { return m_NetIOAdapterManager; }

	protected:

		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote) override;

		// Send packet buffer to connection with network device
		//virtual Result SendBufferUDP(IOBUFFER_WRITE *pSendBuffer) override;
		//virtual Result EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer) override;

	public:

		virtual bool CanDelete() override;
		virtual void Dispose() override;


		// Connect to remote. InitConnection + Connect 
		// Local address will be auto detected
		// @local: NetClass and ID should be assigned
		// @remote: remote information. Address should to be assigned
		virtual Result Connect(PeerInfo local, const PeerInfo& remote) override;

		// Close connection
		virtual Result CloseConnection(const char* reason) override;

		// Pending recv New one
		Result PendingRecv();
	};

}  // namespace Net
} // namespace SF
