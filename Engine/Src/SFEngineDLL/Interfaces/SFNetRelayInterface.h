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

	public:
		NetRelayNetwork();
		~NetRelayNetwork();

		RelayNetworkState GetRelayNetworkState();
		uint32_t GetRelayInstanceID() const;
		uint64_t GetLocalPlayerID() const;
		uint32_t GetLocalEndpointID() const;

		// Connect to remote. InitConnection + Connect 
		// @relayServerAddr: relay server address
		// @relayInstanceID:  relay server instance id
		// @myPlayerID: my player id, 
		uint32_t Connect(const char* relayServerAddr, uint32_t port, uint32_t relayInstanceID, uint64_t myPlayerID);

		// Disconnect connection
		uint32_t Disconnect(const char* reason);

		// Close connection
		uint32_t CloseConnection(const char* reason);

		// Send message to connected entity
		uint32_t Send(uint32_t targetEndpointMask, uint32_t payloadSize, const void* payloadData);

		// Recv message count
		size_t GetRecvMessageCount();

		// Get first data size
		size_t GetRecvDataSize();

		// buffer size 
		size_t RecvData(size_t bufferSize, void* dataBuffer);

	private:
		Net::RelayNetwork* m_Impl = nullptr;
	};
	

}; // namespace SF

