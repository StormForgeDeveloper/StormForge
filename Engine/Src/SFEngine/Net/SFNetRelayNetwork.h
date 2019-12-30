////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 KyungKun Ko
// 
// Author : KyungKun Ko
//
// Description : network relay network
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFCircularPageQueue.h"
#include "EngineObject/SFEngineObject.h"
#include "Net/SFNetSocket.h"
#include "Net/SFNetRawUDP.h"
#include "Interfaces/SFPublicTypes.h"


namespace SF {
namespace Net {





	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network connection base class
	//

	class RelayNetwork : public EngineObject
	{
	public:

		using super = EngineObject;
		using RecvHandler = std::function<void(uint32_t senderEndPoint, size_t payloadSize, const void* payloadData)>;

	public:

		// Constructor
		RelayNetwork(IHeap& heap);
		virtual ~RelayNetwork();

		virtual bool CanDelete() override;
		virtual void Dispose() override;

		RelayNetworkState GetRelayNetworkState() const { return m_RelayNetworkState; }
		uint32_t GetRelayInstanceID() const { return m_RelayInstanceID; }
		PlayerID GetLocalPlayerID() const { return m_PlayerID; }
		uint32_t GetLocalEndpointID() const { return m_PlayerEndpointID; }

		// Connect to remote. InitConnection + Connect 
		// @relayServerAddr: relay server address
		// @relayInstanceID:  relay server instance id
		// @myPlayerID: my player id, 
		virtual Result Connect(const NetAddress& relayServerAddr, uint32_t relayInstanceID, PlayerID myPlayerID, RecvHandler&& recvHandler);

		// Disconnect connection
		virtual Result Disconnect(const char* reason);

		// Close connection
		Result CloseConnection(const char* reason);

		// Call Disconnect and Wait everything is ready to go away, and release itself
		//virtual void DisconnectNRelease(const char* reason);

		// Query connection event
		size_t GetRelayNetworkEventCount();
		Result DequeueRelayNetworkEvent(ConnectionEvent& curEvent);

		// Send message to connected entity
		virtual Result Send(uint32_t targetEndpointMask, size_t payloadSize, const void* payloadData);


		// Engine object
		Result OnTick(EngineTaskTick tick) override;


	protected:

		void SetRelayNetworkState(RelayNetworkState newState) { m_RelayNetworkState.store(newState, std::memory_order_release); }

		Result EnqueueRelayNetworkEvent(const ConnectionEvent& curEvent);

		// called when incoming message occur
		Result OnRecv(const sockaddr_storage& remoteAddr, SharedPointerT<Message::MessageData>& pMsg);

		Result OnJoinRelayInstanceResS2CEvt(MessageDataPtr&& pMsg);
		Result OnPlayerJoinS2CEvt(MessageDataPtr&& pMsg);
		Result OnPlayerLeftS2CEvt(MessageDataPtr&& pMsg);
		Result OnRelayPacketC2SEvt(MessageDataPtr&& pMsg);


		// Called on connection result
		virtual void OnRelayNetworkResult(Result hrConnect);


	private:

		//////////////////////////////////////////////////////////////////////////
		//
		//	
		//

		// Relay server address
		NetAddress m_ServerAddr;

		// RelaySocket address
		sockaddr_storage	m_RelaySockAddr;

		// Relay instance id
		uint32_t m_RelayInstanceID = 0;

		// local Player ID
		PlayerID m_PlayerID = 0;

		// relay endpoint ID
		uint32_t m_PlayerEndpointID = 0;

		// Connection state
		std::atomic<RelayNetworkState> m_RelayNetworkState;

		// Raw udp network
		RawUDP m_RawUDP;

		// Recv Message handler
		RecvHandler m_RecvHandler;

		// Event queue
		CircularPageQueueAtomic<uint64_t>	m_EventQueue;

		CriticalSection m_NetLock;
		// Players in the relay network
		DynamicArray<RelayPlayerInfo> m_Players;
	};


	typedef SharedPointerT <Connection> ConnectionPtr;

}  // namespace Net

	extern template class SharedPointerT <Net::RelayNetwork>;
	extern template class WeakPointerT < Net::RelayNetwork >;


}; // namespace SF



