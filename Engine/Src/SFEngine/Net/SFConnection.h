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
#include "Net/SFNetMessageCollection.h"
#include "Net/SFNetPacketData.h"
#include "MessageBus/SFMessageHeader.h"

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
		using RecvMessageDelegates = EventDelegateList<Connection*, const MessageHeader*>;

        // Received message buffer size
        static constexpr size_t RecvMessageBufferSize = 512 * 1024;
        using RecvMessageQueue = StaticCircularBufferQueue<RecvMessageBufferSize>;
        using MessageItemReadPtr = RecvMessageQueue::ItemReadPtr;
        using MessageItemWritePtr = RecvMessageQueue::ItemWritePtr;


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

        // Local peer info
		PeerInfo m_LocalInfo;

        // Remote peer info
		PeerInfo m_RemoteInfo;

		// Connection ID
		uint64_t	m_CID;

		// Connection state
		Atomic<ConnectionState>	m_ConnectionState;

		// Connection time
		TimeStampMS	m_tConnectionTime;

        // Socket IO
		SocketIO* m_IOHandler = nullptr;

        // message queue with static buffer
        RecvMessageQueue m_RecvMessageQueue;

		// Event queue
		CircularPageQueueAtomic<uint64_t>	m_EventQueue;

		// connecting state time
		DurationMS	m_ulConnectingTimeOut;

		// Sequence 
		std::atomic<uint16_t> m_usSeqNone;

		// ZeroLength recv count
		uint32_t m_ulZeroLengthRecvCount;


		// Remote Socket address
		sockaddr_storage	m_sockAddrRemote;

		// For connection management
		bool		m_UseAddressMap : 1;
		bool		m_UsePeerIDMap : 1;

		// Thread error detection
		ThreadID m_RunningThreadID;

		// Message endpoint adapter
		mutable SharedPointerT<MessageEndpoint> m_MessageEndpoint;

        // sending heartbeat + timeout check
        ConnectionStateAction_Heartbeat m_Heartbeat;

	protected:

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

		//virtual Result SendRaw(const SharedPointerT<MessageData> &pMsg) = 0;

		void SetNetCtrlAction(NetCtrlIDs id, ConnectionMessageAction* action);

		void SetNetIOHandler(SocketIO* pValue) { m_IOHandler = pValue; }

		// Process network control message
		virtual Result ProcNetCtrl(const MsgNetCtrlBuffer* pNetCtrlBuffer);

	public:
		void AddStateAction(ConnectionState state, ConnectionAction* action);
		void RemoveStateAction(ConnectionState state, ConnectionAction* action);

	public:

		// Constructor
		Connection(SocketIO *ioHandler = nullptr);
		virtual ~Connection();

		virtual bool CanDelete() override;
		virtual void Dispose() override;


		//////////////////////////////////////////////////////////////////////////
		//
		//	inline implementations
		//

		// Get Connection info
        const PeerInfo& GetLocalInfo() const { return m_LocalInfo; }
        void SetLocalID(uint64_t newID) { m_LocalInfo.PeerID = newID; }
        const PeerInfo& GetRemoteInfo() const { return m_RemoteInfo; }
        PeerInfo& GetRemoteInfo() { return m_RemoteInfo; }
        void SetRemoteID(uint64_t newID) { m_RemoteInfo.PeerID = newID; }
        void SetRemoteInfo(NetClass newClass, uint64_t newID) { m_RemoteInfo.SetInfo(newClass, newID); }

		// Get Connection ID
        uint64_t GetCID() const { return m_CID; }
        void ClearCID() { m_CID = 0; }
		void SetCID(uint64_t cid) { m_CID = cid; }

        // Message endpoint
		const SharedPointerT<MessageEndpoint>& GetMessageEndpoint() const;

		// Get connection state
        const ConnectionState GetConnectionState() const { return m_ConnectionState.load(std::memory_order_acquire); }

		// Set local class
		inline void SetLocalClass(NetClass localClass)
        {
            m_LocalInfo.PeerClass = localClass;
            m_LocalInfo.PeerID = (uint)(-1);
        }

		// Get connection time
		TimeStampMS GetConnectionTime() const { return m_tConnectionTime; }

		// Get socket handle
		const SF_SOCKET GetSocket() const { return GetNetIOHandler() != nullptr ? GetNetIOHandler()->GetIOSocket() : INVALID_SOCKET; }
		const SocketType GetSocketType() const { return GetNetIOHandler() != nullptr ? GetNetIOHandler()->GetIOSockType() : SocketType::Stream; }

		SocketIO* GetNetIOHandler() const { return m_IOHandler; }

		// Get remote address
        const sockaddr_storage& GetRemoteSockAddr() const { return m_sockAddrRemote; }
        int GetRemoteSockAddrSize() const { return m_sockAddrRemote.ss_family == AF_INET6 ? (int)sizeof(sockaddr_in6) : (int)sizeof(sockaddr_in); }

		// Change remote Address
		void SetRemoteAddress(const sockaddr_storage& socAddr);

		// Get Recv queue
        RecvMessageQueue& GetRecvMessageQueue() { return m_RecvMessageQueue; }

		bool GetUsePeerIDMap() { return m_UsePeerIDMap; }
		void SetUsePeerIDMap(bool enable) { m_UsePeerIDMap = enable; }


		bool GetUseAddressMap() { return m_UseAddressMap; }
		void SetUseAddressMap(bool enable) { m_UseAddressMap = enable; }

		ThreadID GetRunningThreadID() const { return m_RunningThreadID; }
		void SetRunningThreadID(ThreadID threadID) { m_RunningThreadID = threadID; }

		// Get zero recv count
        inline uint32_t GetZeroRecvCount() const { return m_ulZeroLengthRecvCount; }
        inline void IncZeroRecvCount() { m_ulZeroLengthRecvCount++; }
        inline void ResetZeroRecvCount() { m_ulZeroLengthRecvCount = 0; }

		// Sequence generation
        inline uint16_t NewSeqNone() { return (uint16_t)(m_usSeqNone.fetch_add(1, std::memory_order_relaxed) + 1); }

        DurationMS GetConnectingTimeOut() const { return m_ulConnectingTimeOut; }
        void SetConnectingTimeOut(DurationMS ulConnectingTimeOut) { m_ulConnectingTimeOut = ulConnectingTimeOut; }

		TimeStampMS GetNetCtrlTime() { return m_ulNetCtrlTime; }
		TimeStampMS GetNetCtrlTryTime() { return m_ulNetCtrlTryTime; }

		// Update net ctrl time
		void UpdateNetCtrlTime();
		void UpdateNetCtrlTryTime();


		//////////////////////////////////////////////////////////////////////////
		//
		//	Event delegates
		//

		EventFireMode GetEventFireMode() const { return m_DelegateFireMode; }
		void SetEventFireMode(EventFireMode eventFireMode) { m_DelegateFireMode = eventFireMode; }

		ConnectionEventDeletates& GetConnectionEventDelegates() { return m_ConnectionEventDelegates; }
		RecvMessageDelegates& GetRecvMessageDelegates() { return m_RecvMessageDelegates; }




		//////////////////////////////////////////////////////////////////////////
		//
		//	
		//

		// Request time sync, round trip time will be recorded
		Result TimeSync();

		// Round trip delay
		DurationMS GetRoundTripDelay() { return m_RoundTripDelay; }

		void OnTimeSyncRtn(DurationMS roundTripTime);

        // called when a heartbeat packet  arrives
		void OnHeartbeatPacket();


		//////////////////////////////////////////////////////////////////////////
		//
		//	virtual implementations
		//

		Result ProcConnectionStateAction();

		// Make NetCtrl packet and send
        virtual Result MakeNetCtrl(MessageHeader* pHeader, uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0 = 0);
        virtual Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0 = 0) = 0;
        virtual Result SendPending(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0 = 0) = 0;

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
        virtual Result OnRecv(uint uiBuffSize, uint8_t* pBuff) = 0;
		virtual Result OnRecv(MessageHeader* pMsg);


		// Query connection event
        inline CounterType GetConnectionEventCount() const { return m_EventQueue.size(); }
		Result DequeueConnectionEvent(ConnectionEvent& curEvent);


		// Initialize connection
		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote);

		// Send message to connected entity
        virtual Result SendMsg(const MessageHeader* pMsg) = 0;
        virtual Result SendCollection(const MessageCollection* pCollection);

		// Message count currently in recv queue
        SF_FORCEINLINE uint32_t GetRecvMessageCount() const { return (uint32_t)m_RecvMessageQueue.GetItemCount(); }

		// Update function on game tick. provide general implementation of connection tick update.
		// this function will fire delegate events
		virtual Result UpdateGameTick();

        // Engine object tick function
		Result OnTick(EngineTaskTick tick) override;

		// Update net control, process connection heartbeat, ... etc
		virtual Result TickUpdate();

	private:

		//////////////////////////////////////////////////////////////////////////
		//
		//	Message/Event delegates
		//

        // event fire mode
		EventFireMode m_DelegateFireMode = EventFireMode::OnGameTick;

        // Event delegate
		ConnectionEventDeletates m_ConnectionEventDelegates;

        // Recv message delegate
		RecvMessageDelegates m_RecvMessageDelegates;
	};

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

        virtual flatbuffers::FlatBufferBuilder* GetBuilder() override { return nullptr; }

        virtual SharedPointerT<Connection> GetConnection() const override { return m_pConnection.AsSharedPtr<Connection>(); }
		virtual bool IsSameEndpoint(const EndpointAddress& messageEndpoint) override;
        virtual Result SendMsg(const MessageHeader* messageData) override;
    };

}  // namespace Net

	extern template class SharedPointerT <Net::Connection>;
	extern template class WeakPointerT < Net::Connection >;

} // namespace SF
