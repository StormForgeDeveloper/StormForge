////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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


namespace SF {
namespace Net {





	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network connection base class
	//

	class Connection : public EngineObject
	{
	public:


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
		std::atomic<ConnectionState>	m_ConnectionState;

		// Connection time
		TimeStampMS	m_tConnectionTime;

		IConnectionEventHandler *m_pEventHandler = nullptr;


		SocketIO* m_IOHandler = nullptr;

		// Recv Message Queue
		MsgQueue m_RecvQueue;

		// Event queue
		CircularPageQueueAtomic<uint64_t>	m_EventQueue;

		// heart bit time
		DurationMS	m_ulHeartbitTry;
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

	protected:

		// Guaranteed sending wait queue
		MsgQueue			m_SendGuaQueue;


		// NetCtrl control time
		TimeStampMS m_ulNetCtrlTime;
		TimeStampMS m_ulNetCtrlTryTime;

		// Net control actions
		ConnectionMessageAction* m_NetCtrlAction[(int)NetCtrlIDs::NetCtrlCode_Max];

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

		// Set socket handle
		//void SetSocket(SOCKET socket, bool isSocketOwner) { m_Socket = socket; m_IsSocketOwner = isSocketOwner; }


		// Add network event to queue
		virtual Result EnqueueConnectionEvent(const ConnectionEvent& evt);


		// Initialize packet synchronization
		virtual Result InitSynchronization();


		virtual Result SendRaw(SharedPointerT<Message::MessageData> &pMsg) = 0;

		void SetNetCtrlAction(NetCtrlIDs id, ConnectionMessageAction* action);
		void AddStateAction(ConnectionState state, ConnectionAction* action);


		void SetNetIOHandler(SocketIO* pValue) { m_IOHandler = pValue; }


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
		const SOCKET GetSocket() const { return GetNetIOHandler() != nullptr ? GetNetIOHandler()->GetIOSocket() : INVALID_SOCKET; }

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

		// Heart bit time
		DurationMS GetHeartbitTry();
		void SetHeartbitTry(DurationMS ulHeartbitTry);

		DurationMS GetConnectingTimeOut();
		void SetConnectingTimeOut(DurationMS ulConnectingTimeOut);


		TimeStampMS GetNetCtrlTime() { return m_ulNetCtrlTime; }
		TimeStampMS GetNetCtrlTryTime() { return m_ulNetCtrlTryTime; }


		// Update net ctrl time
		void UpdateNetCtrlTime();
		void UpdateNetCtrlTryTime();

		IConnectionEventHandler* GetEventHandler();

		// Connection event handler
		void SetEventHandler(IConnectionEventHandler *pEventHandler) { m_pEventHandler = pEventHandler; }





		//////////////////////////////////////////////////////////////////////////
		//
		//	
		//

		// Request time sync, round trip time will be recorded
		Result TimeSync();

		// Round trip delay
		DurationMS GetRoundTripDelay() { return m_RoundTripDelay; }

		void OnTimeSyncRtn(DurationMS roundTripTime);


		void OnHeartBitPacket();


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

		// called when incoming message occure
		virtual Result OnRecv(uint uiBuffSize, const uint8_t* pBuff) = 0;
		virtual Result OnRecv(SharedPointerT<Message::MessageData>& pMsg);


		// Query connection event
		CounterType GetConnectionEventCount();
		Result DequeueConnectionEvent(ConnectionEvent& curEvent);


		// Initialize connection
		virtual Result InitConnection(const PeerInfo &local, const PeerInfo &remote);



		// Send message to connected entity
		virtual Result Send(SharedPointerT<Message::MessageData> &pMsg) = 0;

		// Message count currently in recv queue
		virtual SysUInt GetRecvMessageCount();

		// Get received Message
		virtual Result GetRecvMessage(SharedPointerT<Message::MessageData> &pIMsg);


		Result OnTick(EngineTaskTick tick) override;



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Overridable
		//

		// Update net control, process connection heartbit, ... etc
		virtual Result TickUpdate() = 0;

		// Update send queue, Reliable UDP
		virtual Result UpdateSendQueue() { return ResultCode::SUCCESS; }
		// Update Send buffer Queue, TCP and UDP client connection
		virtual Result UpdateSendBufferQueue() = 0;


	};

	#include "SFConnection.inl"

	typedef SharedPointerT <Connection> ConnectionPtr;

}  // namespace Net

	extern template class SharedPointerT <Net::Connection>;
	extern template class WeakPointerT < Net::Connection >;

	template<> inline SharedPointerT<Net::Connection> DefaultValue<SharedPointerT<Net::Connection>>() { return SharedPointerT<Net::Connection>(); }
	template<> inline WeakPointerT<Net::Connection> DefaultValue<WeakPointerT<Net::Connection>>() { return WeakPointerT<Net::Connection>(); }

	template<> inline SharedPointerAtomicT<Net::Connection> DefaultValue<SharedPointerAtomicT<Net::Connection>>() { return SharedPointerAtomicT<Net::Connection>(); }

}; // namespace SF



