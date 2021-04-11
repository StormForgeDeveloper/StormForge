////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionAction.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFCircularPageQueue.h"
#include "EngineObject/SFEngineObject.h"
#include "Net/SFConnectionActions.h"
#include "Net/SFNetSocket.h"
#include "Delegate/SFEventDelegate.h"
#include "Container/SFDualSortedMap.h"


namespace SF {

	class MessageEndpoint;

namespace Net {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network connection base class
	//

	class Connection : public EngineObject
	{
	public:

		using super = EngineObject;
		using ConnectionEventDeletates = EventDelegateList<Connection*, const ConnectionEvent&>;
		using RecvMessageDelegates = EventDelegateList<Connection*, const SharedPointerT<Message::MessageData>&>;
		using NetSyncMessageDelegates = EventDelegateList<Connection*>;

		enum class EventFireMode : uint8_t
		{
			Immediate, // Fire event ASAP regardless of thread
			OnGameTick, // Fire event on game tick thread, Owner should call UpdateGameTick for event fire
		};


	private:


		//////////////////////////////////////////////////////////////////////////
		//
		//	basic members implementations
		//

		PeerInfo m_LocalInfo;
		PeerInfo m_RemoteInfo;


		// Connection ID
		uint64_t	m_CID;

		// User data
		uint64_t	m_UData;

		// Connection state
		Atomic<ConnectionState>	m_ConnectionState;

		// Connection time
		TimeStampMS	m_tConnectionTime;

		IConnectionEventHandler *m_pEventHandler = nullptr;


		SocketIO* m_IOHandler = nullptr;

		// Recv Message Queue
		MsgQueue m_RecvQueue;

		// Event queue
		CircularPageQueueAtomic<uint64_t>	m_EventQueue;

		// heartbeat time
		DurationMS	m_ulHeartbeatTry;
		DurationMS	m_ulConnectingTimeOut;

		// Sequence 
		std::atomic<uint16_t> m_usSeqNone;

		// ZeroLength recv count
		uint32_t m_ulZeroLengthRecvCount;


		// Remote Socket address
		sockaddr_storage	m_sockAddrRemote;

		// For connection management
		bool		m_IsSocketOwner : 1;
		bool		m_UseAddressMap : 1;
		bool		m_UsePeerIDMap : 1;

		// Thread error detection
		ThreadID m_RunningThreadID;

		// Message endpoint adapter
		mutable SharedPointerT<MessageEndpoint> m_MessageEndpoint;

	protected:

		// Guaranteed sending wait queue
		MsgQueue			m_SendGuaQueue;


		// NetCtrl control time
		TimeStampMS m_ulNetCtrlTime;
		TimeStampMS m_ulNetCtrlTryTime;

		// Net control actions
		ConnectionMessageAction* m_NetCtrlAction[(int)NetCtrlIDs::NetCtrlCode_Max]{};

		// Update Tick actions
		// Connection actions by state
		// Too remove micro allocation it uses static buffer and manual construction/destruction
		typedef StaticArray<ConnectionAction*, 32> ConnectionActionArray;
		uint8_t m_Array2DBufferForConnectionAction[sizeof(ConnectionActionArray) * (int)ConnectionState::Max] = {0}; // Buffer for array

		// TODO: It might be helpful If I make a class wrapper for this.
		ConnectionActionArray *m_ActionsByState = nullptr;

		// Round trip delay between two peer, Updated with TimeSync command
		DurationMS m_RoundTripDelay;

	protected:
		void SetConnectionState(ConnectionState newState);
		void UpdateConnectionTime();

		// Add network event to queue
		virtual Result EnqueueConnectionEvent(const ConnectionEvent& evt);


		// Initialize packet synchronization
		virtual Result InitSynchronization();

		virtual Result SendRaw(const SharedPointerT<Message::MessageData> &pMsg) = 0;

		void SetNetCtrlAction(NetCtrlIDs id, ConnectionMessageAction* action);

		void SetNetIOHandler(SocketIO* pValue) { m_IOHandler = pValue; }

		// Process network control message
		virtual Result ProcNetCtrl(const MsgNetCtrl* pNetCtrl);

	public:
		void AddStateAction(ConnectionState state, ConnectionAction* action);
		void RemoveStateAction(ConnectionState state, ConnectionAction* action);

		// Only CONNECTED state is supported
		void SetStateTimeout(ConnectionState state, DurationMS timeout);

	public:

		// Constructor
		Connection(IHeap& heap, SocketIO *ioHandler = nullptr);
		virtual ~Connection();

		virtual bool CanDelete() override;
		virtual void Dispose() override;


		//////////////////////////////////////////////////////////////////////////
		//
		//	inline implementations
		//

		// Get Connection info
		const PeerInfo& GetLocalInfo() const;
		void SetLocalID(uint64_t newID);
		const PeerInfo& GetRemoteInfo() const;
		PeerInfo& GetRemoteInfo();
		void SetRemoteID(uint64_t newID);
		void SetRemoteInfo(NetClass newClass, uint64_t newID);

		// Get Connection ID
		uint64_t GetCID() const;
		void ClearCID();
		void SetCID(uint64_t cid) { m_CID = cid; }

		const SharedPointerT<MessageEndpoint>& GetMessageEndpoint() const;

		// Get connection state
		const ConnectionState GetConnectionState() const;

		// Set local class
		inline void SetLocalClass(NetClass uiLocalClass);

		// User data
		uint64_t GetUData();
		void SetUData(uint64_t UData);

		// Get connection time
		TimeStampMS GetConnectionTime();

		bool GetIsSocketOwner() const { return m_IsSocketOwner; }


		// Get socket handle
		const SF_SOCKET GetSocket() const { return GetNetIOHandler() != nullptr ? GetNetIOHandler()->GetIOSocket() : INVALID_SOCKET; }
		const SocketType GetSocketType() const { return GetNetIOHandler() != nullptr ? GetNetIOHandler()->GetIOSockType() : SocketType::Stream; }

		SocketIO* GetNetIOHandler() const { return m_IOHandler; }
		IHeap& GetIOHeap();

		// Get remote address
		const sockaddr_storage& GetRemoteSockAddr() const;
		int GetRemoteSockAddrSize() const;

		// Change remote Address
		void SetRemoteAddress(const sockaddr_storage& socAddr);

		// Get Recv queue
		MsgQueue& GetRecvQueue() { return m_RecvQueue; }

		MsgQueue& GetSendGuaQueue() { return m_SendGuaQueue; }


		bool GetUsePeerIDMap() { return m_UsePeerIDMap; }
		void SetUsePeerIDMap(bool enable) { m_UsePeerIDMap = enable; }


		bool GetUseAddressMap() { return m_UseAddressMap; }
		void SetUseAddressMap(bool enable) { m_UseAddressMap = enable; }

		ThreadID GetRunningThreadID() const { return m_RunningThreadID; }
		void SetRunningThreadID(ThreadID threadID) { m_RunningThreadID = threadID; }


		// Get zero recv count
		inline uint32_t GetZeroRecvCount();
		inline void IncZeroRecvCount();
		inline void ResetZeroRecvCount();


		// Sequence generation
		inline uint16_t NewSeqNone();

		// heartbeat time
		DurationMS GetHeartbeatTry();
		void SetHeartbeatTry(DurationMS ulHeartbeatTry);

		DurationMS GetConnectingTimeOut();
		void SetConnectingTimeOut(DurationMS ulConnectingTimeOut);


		TimeStampMS GetNetCtrlTime() { return m_ulNetCtrlTime; }
		TimeStampMS GetNetCtrlTryTime() { return m_ulNetCtrlTryTime; }


		// Update net ctrl time
		void UpdateNetCtrlTime();
		void UpdateNetCtrlTryTime();

		// Deprecated, use delegate function
		IConnectionEventHandler* GetEventHandler();

		// Connection event handler
		void SetEventHandler(IConnectionEventHandler *pEventHandler) { m_pEventHandler = pEventHandler; }


		//////////////////////////////////////////////////////////////////////////
		//
		//	Event delegates
		//

		EventFireMode GetEventFireMode() const { return m_DelegateFireMode; }
		void SetEventFireMode(EventFireMode eventFireMode) { m_DelegateFireMode = eventFireMode; }

		ConnectionEventDeletates& GetConnectionEventDelegates() { return m_ConnectionEventDelegates; }
		RecvMessageDelegates& GetRecvMessageDelegates() { return m_RecvMessageDelegates; }
		NetSyncMessageDelegates& GetNetSyncMessageDelegates() { return m_NetSyncMessageDelegates; }


		void AddMessageDelegateUnique(uintptr_t context, uint32_t msgId, RecvMessageDelegates::CallableType&& func)
		{
			RecvMessageDelegates* pDelegateList = nullptr;
			if (!m_RecvMessageDelegatesByMsgId.Find(msgId, pDelegateList))
			{
				pDelegateList = new(GetHeap()) RecvMessageDelegates(GetHeap());
				m_RecvMessageDelegatesByMsgId.Insert(msgId, pDelegateList);
				m_RecvMessageDelegatesByMsgId.CommitChanges();
			}

			pDelegateList->AddDelegateUnique(uintptr_t(context), Forward<RecvMessageDelegates::CallableType>(func));
		}

		void RemoveMessageDelegate(uintptr_t context, uint32_t msgId)
		{
			RecvMessageDelegates* pDelegateList = nullptr;
			if (m_RecvMessageDelegatesByMsgId.Find(msgId, pDelegateList))
			{
				pDelegateList->RemoveDelegateAll(uintptr_t(context));
			}
		}


		//////////////////////////////////////////////////////////////////////////
		//
		//	
		//

		// Request time sync, round trip time will be recorded
		Result TimeSync();

		// Round trip delay
		DurationMS GetRoundTripDelay() { return m_RoundTripDelay; }

		void OnTimeSyncRtn(DurationMS roundTripTime);


		void OnHeartbeatPacket();


		//////////////////////////////////////////////////////////////////////////
		//
		//	virtual implementations
		//

		Result ProcConnectionStateAction();

		// Make NetCtrl packet and send
		virtual Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, Message::MessageID returnMsgID, uint64_t UID = 0);
		virtual Result SendPending(uint uiCtrlCode, uint uiSequence, Message::MessageID returnMsgID, uint64_t UID = 0) { assert(false); return ResultCode::NOT_IMPLEMENTED; }

		// Clear Queue
		virtual Result ClearQueues();


		// Called on connection result
		virtual void OnConnectionResult(Result hrConnect);

		// Connect to remote. InitConnection + Connect 
		// Local address will be auto detected
		// @local: NetClass and ID should be assigned
		// @remote: remote information. Address should to be assigned
		virtual Result Connect(PeerInfo local, const PeerInfo& remote) = 0;

		// Disconnect connection
		virtual Result Disconnect(const char* reason);

		// Close connection
		virtual Result CloseConnection(const char* reason);

		// Call Disconnect and Wait everything is ready to go away, and release itself
		virtual void DisconnectNRelease(const char* reason);

		// called when incoming message occur
		virtual Result OnRecv(uint uiBuffSize, const uint8_t* pBuff) = 0;
		virtual Result OnRecv(SharedPointerT<Message::MessageData>& pMsg);


		// Query connection event
		CounterType GetConnectionEventCount();
		Result DequeueConnectionEvent(ConnectionEvent& curEvent);


		// Initialize connection
		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote);



		// Send message to connected entity
		virtual Result Send(const SharedPointerT<Message::MessageData> &pMsg) = 0;

		// Message count currently in recv queue
		virtual SysUInt GetRecvMessageCount();

		// Get received Message
		virtual Result GetRecvMessage(SharedPointerT<Message::MessageData> &pIMsg);

		// Update function on game tick. provide general implementation of connection tick update.
		// this function will fire delegate events
		virtual Result UpdateGameTick();

		Result OnTick(EngineTaskTick tick) override;



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Overridable
		//

		// Update net control, process connection heartbeat, ... etc
		virtual Result TickUpdate();

		// Update send queue, Reliable UDP
		virtual Result UpdateSendQueue() { return ResultCode::SUCCESS; }
		// Update Send buffer Queue, TCP and UDP client connection
		virtual Result UpdateSendBufferQueue() = 0;


	private:

		//////////////////////////////////////////////////////////////////////////
		//
		//	Event delegates
		//

		EventFireMode m_DelegateFireMode = EventFireMode::OnGameTick;

		ConnectionEventDeletates m_ConnectionEventDelegates;
		NetSyncMessageDelegates m_NetSyncMessageDelegates;
		RecvMessageDelegates m_RecvMessageDelegates;
		// Received message handler map by msgId
		DualSortedMap<uint32_t, RecvMessageDelegates*> m_RecvMessageDelegatesByMsgId;
	};

	#include "SFConnection.inl"

	typedef SharedPointerT <Connection> ConnectionPtr;



	////////////////////////////////////////////////////////////////////////////////
	//
	//	MessageEndpoint adapter
	//


	class MessageEndpointConnection : public MessageEndpoint
	{
	public:
		WeakPointerT<Connection> m_pConnection;

		MessageEndpointConnection(Connection* pConnection)
		{
			m_pConnection = SharedPointerT<Connection>(pConnection);
		}

		virtual bool IsSameEndpoint(const EndpointAddress& messageEndpoint) override;
		virtual Result Send(const SharedPointerT<Message::MessageData>& messageData) override;
	};


}  // namespace Net

	extern template class SharedPointerT <Net::Connection>;
	extern template class WeakPointerT < Net::Connection >;


}; // namespace SF



