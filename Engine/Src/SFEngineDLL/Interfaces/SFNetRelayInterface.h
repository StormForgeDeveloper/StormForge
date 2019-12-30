////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description :  Interfaces
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "Interfaces/SFPublicInterface.h"
#include "Interfaces/SFPublicTypes.h"




namespace SF {

	namespace Net {
		class RelayNetwork;
	}


	// Interface 
	class SF_ENGINE_API NetRelayNetwork
	{
	public:

		using RecvHandler = std::function<void(uint32_t senderEndPoint, size_t payloadSize, const void* payloadData)>;

	public:
		NetRelayNetwork();
		~NetRelayNetwork();

		RelayNetworkState GetRelayNetworkState();
		uint32_t GetRelayInstanceID() const;
		PlayerID GetLocalPlayerID() const;
		uint32_t GetLocalEndpointID() const;

		// Connect to remote. InitConnection + Connect 
		// @relayServerAddr: relay server address
		// @relayInstanceID:  relay server instance id
		// @myPlayerID: my player id, 
		Result Connect(const NetAddress& relayServerAddr, uint32_t relayInstanceID, PlayerID myPlayerID, RecvHandler&& handler);

		// Disconnect connection
		Result Disconnect(const char* reason);

		// Close connection
		Result CloseConnection(const char* reason);

		// Send message to connected entity
		Result Send(uint32_t targetEndpointMask, size_t payloadSize, const void* payloadData);

	private:
		Net::RelayNetwork* m_Impl = nullptr;
	};
	

}; // namespace SF

