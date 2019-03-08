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

	protected:

		ConnectionMessageAction_MUDPHandleAck m_HandleAck;
		ConnectionMessageAction_MUDPHandleNack m_HandleNack;
		ConnectionMessageAction_HandleHeartBit m_HandleHeartBit;
		ConnectionMessageAction_HandleTimeSync m_HandleTimeSync;
		ConnectionMessageAction_MUDPHandleConnect m_HandleConnect;
		ConnectionMessageAction_UDPHandleDisconnect m_HandleDisconnect;

		ConnectionStateAction_SendReliableQueue m_ActSendReliableQueue;
		ConnectionStateAction_SendReliableRetry m_ActSendReliableRetry;


		friend class ConnectionStateAction_SendReliableQueue;
		friend class ConnectionStateAction_SendReliableRetry;
		friend class ConnectionStateAction_SendSync;
		friend class ConnectionStateAction_SendSyncSvr;
		friend class ConnectionMessageAction_MUDPHandleSyncReliableServer;

	public:
		// Constructor
		ConnectionMUDP(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionMUDP();
	protected:

		// gathering
		virtual Result SendPending( uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID = 0 ) override;
		virtual Result SendPending(SharedPointerT<Message::MessageData>& pMsg )  override { return ConnectionUDPBase::SendPending(pMsg); }
		virtual Result SendSync( uint uiSequence, uint64_t uiSyncMask );

		virtual Result SendNetCtrl( uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID = 0 ) override;


		// Process network control message
		virtual Result ProcNetCtrl( const MsgNetCtrl* pNetCtrl ) override;


		Result OnGuarrentedMessageRecv(SharedPointerT<Message::MessageData>& pMsg);

		// On server side, update send queue will be handled by event handler
		// On client side, send queue need to be updated by connection
		//virtual Result ProcSendReliable();


	public:

		// called when incoming message occur
		virtual Result OnRecv(uint uiBuffSize, const uint8_t* pBuff) override;
		virtual Result OnRecv(SharedPointerT<Message::MessageData>& pMsg ) override;


		// Update net control, process connection heartbit, ... etc
		virtual Result TickUpdate() override;
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server Mobile UDP Network connection class
	//

	class ConnectionMUDPServer : public ConnectionMUDP
	{
	private:

		ConnectionMessageAction_MUDPHandleSyncReliableServer m_HandleSyncReliable;

		ConnectionStateAction_SendSyncSvr m_ActSync;

	public:
		// Constructor
		ConnectionMUDPServer(IHeap& heap, SocketIO* ioHandler);
		virtual ~ConnectionMUDPServer();

		// We need this for event handling
		Result UpdateSendQueue() override;
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

			ConnectionMUDPClient &m_Owner;
			Result m_LastResult;

		public:

			MyNetSocketIOAdapter(ConnectionMUDPClient &owner);

			Result GetLastResult() { return m_LastResult; }

			// Send message to connection with network device
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

			// called when receiving TCP message
			virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) override;

			virtual Result OnWriteReady() override;
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


		ConnectionMessageAction_HandleTimeSyncRtn m_HandleTimeSyncRtn;

		// Sync tick counter
		TimeStampMS m_ReliableSyncTime;


		// Event actions
		ConnectionMessageAction_MUDPHandleSyncReliableClient m_HandleSyncReliableClient;

		ConnectionStateAction_SendConnect m_SendConnect;
		ConnectionStateAction_SendHeartBit m_SendHeartBit;
		ConnectionStateAction_SendDisconnect m_SendDisconnect;

		ConnectionStateAction_SendSync m_ActSendSync;


		// Client side CID generator
		static std::atomic<uint64_t> stm_CIDGen;

	public:
		// Constructor
		ConnectionMUDPClient(IHeap& heap);
		virtual ~ConnectionMUDPClient();
	protected:


		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote) override;


		//virtual Result ProcSendReliable() override;


		// Send packet buffer to connection with network device
		//virtual Result SendBufferUDP(IOBUFFER_WRITE *pSendBuffer) override;
		virtual Result EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer) override;



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
        
		virtual Result TickUpdate() override;
	};


}  // namespace Net
} // namespace SF


