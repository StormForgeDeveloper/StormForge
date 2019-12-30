////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Public Interfaces
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Interfaces/SFNetRelayInterface.h"
#include "Net/SFNetRelayNetwork.h"


namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	NetRelayNetwork::NetRelayNetwork()
	{
		m_Impl = new(Service::NetSystem->GetHeap()) Net::RelayNetwork(Service::NetSystem->GetHeap());
		SharedReferenceInc inc(m_Impl);
		m_Impl->RegisterToEngineObjectManager();
	}

	NetRelayNetwork::~NetRelayNetwork()
	{
		if (m_Impl == nullptr)
			return;

		m_Impl->Disconnect("Destroy");
		m_Impl->CloseConnection("Destroy");
		m_Impl->SetTickFlags(0);

		SharedReferenceDec dec(m_Impl);
	}


	RelayNetworkState NetRelayNetwork::GetRelayNetworkState()
	{
		return m_Impl->GetRelayNetworkState();
	}

	uint32_t NetRelayNetwork::GetRelayInstanceID() const
	{
		return m_Impl->GetRelayInstanceID();
	}

	PlayerID NetRelayNetwork::GetLocalPlayerID() const
	{
		return m_Impl->GetLocalPlayerID();
	}

	uint32_t NetRelayNetwork::GetLocalEndpointID() const
	{
		return m_Impl->GetLocalEndpointID();
	}


	// Connect to remote. InitConnection + Connect 
	// @relayServerAddr: relay server address
	// @relayInstanceID:  relay server instance id
	// @myPlayerID: my player id, 
	Result NetRelayNetwork::Connect(const NetAddress& relayServerAddr, uint32_t relayInstanceID, PlayerID myPlayerID, RecvHandler&& handler)
	{
		return m_Impl->Connect(relayServerAddr, relayInstanceID, myPlayerID, std::forward<RecvHandler>(handler));
	}

	// Disconnect connection
	Result NetRelayNetwork::Disconnect(const char* reason)
	{
		return m_Impl->Disconnect(reason);
	}

	// Close connection
	Result NetRelayNetwork::CloseConnection(const char* reason)
	{
		return m_Impl->CloseConnection(reason);
	}

	// Send message to connected entity
	Result NetRelayNetwork::Send(uint32_t targetEndpointMask, size_t payloadSize, const void* payloadData)
	{
		return m_Impl->Send(targetEndpointMask, payloadSize, payloadData);
	}

	
}




